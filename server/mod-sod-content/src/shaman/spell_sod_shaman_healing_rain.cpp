/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "DynamicObject.h"
#include "Group.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Unit.h"

#include <algorithm>
#include <cmath>

namespace
{
bool IsAmongFirstFivePartyMembers(Player* caster, Player* target, DynamicObject* area)
{
    if (!caster || !target || !area)
        return false;

    uint8 eligibleCount = 0;
    bool targetSelected = false;
    auto considerMember = [&](Player* member)
    {
        if (!member || !member->IsInWorld() || !member->IsAlive()
            || !member->IsWithinDistInMap(area, area->GetRadius()))
            return;

        if (eligibleCount < 5)
        {
            ++eligibleCount;
            if (member == target)
                targetSelected = true;
        }
    };

    if (Group* group = caster->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
            considerMember(itr->GetSource());
    }
    else
        considerMember(caster);

    return targetSelected;
}
}

class spell_sod_shaman_healing_rain : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_healing_rain);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandlePeriodicHeal(AuraEffect const* aurEff)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Player* target = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!caster || !target || !target->IsAlive())
            return;

        DynamicObject* area = caster->GetDynObject(SPELL_SOD_SHAMAN_HEALING_RAIN);
        if (!IsAmongFirstFivePartyMembers(caster, target, area))
            return;

        SpellInfo const* spellInfo = GetAura()->GetSpellInfo();
        if (!spellInfo)
            return;

        float level = float(caster->GetLevel());
        float baseTick = (29.8882f + 0.690312f * level + 0.136267f * level * level) * 0.15f;
        uint32 baseHeal = uint32(std::max(1.0f, std::round(baseTick)));
        uint32 healAmount = caster->SpellHealingBonusDone(target, spellInfo, baseHeal,
            DOT, aurEff->GetEffIndex());

        HealInfo healInfo(caster, target, healAmount, spellInfo, SPELL_SCHOOL_MASK_NATURE);
        caster->HealBySpell(healInfo);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_shaman_healing_rain::HandlePeriodicHeal,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_shaman_healing_rain()
{
    RegisterSpellScript(spell_sod_shaman_healing_rain);
}
