/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Group.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

namespace
{
constexpr uint32 ANCESTRAL_GUIDANCE_DAMAGE_PCT = 25;
constexpr uint32 ANCESTRAL_GUIDANCE_HEALING_PCT = 100;
constexpr float ANCESTRAL_GUIDANCE_RADIUS = 40.0f;
constexpr uint8 ANCESTRAL_GUIDANCE_MAX_TARGETS = 3;

std::map<ObjectGuid, ObjectGuid> RecentFlameShockTargets;

Unit* GetRecentFlameShockTarget(Player* caster)
{
    if (!caster)
        return nullptr;

    auto itr = RecentFlameShockTargets.find(caster->GetGUID());
    if (itr == RecentFlameShockTargets.end())
        return nullptr;

    Unit* target = ObjectAccessor::GetUnit(*caster, itr->second);
    if (!target || !target->IsAlive()
        || !target->GetAuraOfRankedSpell(SPELL_SHAMAN_FLAME_SHOCK, caster->GetGUID()))
        return nullptr;

    return target;
}

void AddGuidanceHealingTargets(Player* caster, std::vector<std::pair<float, Player*>>& targets)
{
    auto consider = [caster, &targets](Player* member)
    {
        if (!member || !member->IsInWorld() || !member->IsAlive()
            || !member->IsInMap(caster) || !member->IsWithinDistInMap(caster, ANCESTRAL_GUIDANCE_RADIUS))
            return;

        targets.emplace_back(caster->GetDistance(member), member);
    };

    if (Group* group = caster->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
            consider(itr->GetSource());
    }
    else
        consider(caster);

    std::sort(targets.begin(), targets.end(), [](auto const& left, auto const& right)
    {
        return left.first < right.first;
    });
}
}

class spell_sod_shaman_ancestral_guidance : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_ancestral_guidance);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player || eventInfo.GetActor() != player)
            return false;

        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (spellInfo && (spellInfo->Id == SPELL_SOD_SHAMAN_ANCESTRAL_GUIDANCE
            || spellInfo->Id == SPELL_SOD_SHAMAN_ANCESTRAL_GUIDANCE_DAMAGE))
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        HealInfo* healInfo = eventInfo.GetHealInfo();
        return (damageInfo && damageInfo->GetDamage() > 0)
            || (healInfo && healInfo->GetEffectiveHeal() > 0);
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            uint32 convertedHeal = CalculatePct(damageInfo->GetDamage(), ANCESTRAL_GUIDANCE_DAMAGE_PCT);
            if (!convertedHeal)
                return;

            std::vector<std::pair<float, Player*>> targets;
            AddGuidanceHealingTargets(player, targets);
            SpellInfo const* sourceSpell = sSpellMgr->GetSpellInfo(SPELL_SOD_SHAMAN_ANCESTRAL_GUIDANCE);
            if (!sourceSpell)
                return;

            uint8 count = 0;
            for (auto const& entry : targets)
            {
                if (count >= ANCESTRAL_GUIDANCE_MAX_TARGETS)
                    break;

                HealInfo healInfo(player, entry.second, convertedHeal, sourceSpell, SPELL_SCHOOL_MASK_NATURE);
                player->HealBySpell(healInfo);
                ++count;
            }
            return;
        }

        HealInfo* healInfo = eventInfo.GetHealInfo();
        Unit* target = GetRecentFlameShockTarget(player);
        if (!healInfo || !target || !player->IsValidAttackTarget(target))
            return;

        uint32 convertedDamage = CalculatePct(healInfo->GetEffectiveHeal(), ANCESTRAL_GUIDANCE_HEALING_PCT);
        if (convertedDamage)
            player->CastCustomSpell(SPELL_SOD_SHAMAN_ANCESTRAL_GUIDANCE_DAMAGE,
                SPELLVALUE_BASE_POINT0, int32(convertedDamage), target, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_ancestral_guidance::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_ancestral_guidance::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_shaman_ancestral_guidance_flame_shock : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_ancestral_guidance_flame_shock);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetTarget();
        if (caster && target)
            RecentFlameShockTargets[caster->GetGUID()] = target->GetGUID();
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        auto itr = RecentFlameShockTargets.find(caster->GetGUID());
        if (itr != RecentFlameShockTargets.end() && itr->second == target->GetGUID())
            RecentFlameShockTargets.erase(itr);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_shaman_ancestral_guidance_flame_shock::HandleApply,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_shaman_ancestral_guidance_flame_shock::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_ancestral_guidance()
{
    RegisterSpellScript(spell_sod_shaman_ancestral_guidance);
    RegisterSpellScript(spell_sod_shaman_ancestral_guidance_flame_shock);
}
