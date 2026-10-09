/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "DynamicObject.h"
#include "Group.h"
#include "SpellInfo.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_hallowed_ground : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_hallowed_ground);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!player || eventInfo.GetActor() != player || !spellInfo || !damageInfo
            || damageInfo->GetDamage() == 0 || spellInfo->SpellFamilyName != SPELLFAMILY_PALADIN)
            return false;

        return spellInfo->SpellFamilyFlags.HasFlag(
            SOD_PALADIN_WRATH_CONSECRATION_MASK_0, 0, 0);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!player || !spellInfo || !damageInfo)
            return;

        DynamicObject* area = player->GetDynObject(spellInfo->Id);
        if (!area || !area->IsInWorld())
            return;

        uint32 healingPct = std::min<uint32>(SodPaladinHallowedGroundHealingPct(), 1000);
        uint32 healing = CalculatePct(damageInfo->GetDamage(), healingPct);
        if (!healing)
            return;

        auto healMember = [player, area, spellInfo, healing](Player* member)
        {
            if (!member || !member->IsInWorld() || !member->IsAlive()
                || !member->IsWithinDistInMap(area, area->GetRadius()))
                return;

            HealInfo healInfo(player, member, healing, spellInfo, SPELL_SCHOOL_MASK_HOLY);
            player->HealBySpell(healInfo);
        };

        if (Group* group = player->GetGroup())
        {
            for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
                healMember(itr->GetSource());
        }
        else
            healMember(player);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_hallowed_ground::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_hallowed_ground::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_hallowed_ground()
{
    RegisterSpellScript(spell_sod_paladin_hallowed_ground);
}
