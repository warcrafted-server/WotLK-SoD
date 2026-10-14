/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Player.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "Unit.h"

#include <algorithm>

namespace
{
Player* GetProtectedRogue(Unit* target)
{
    Player* player = target ? target->ToPlayer() : nullptr;
    if (!SodRogueEnabled() || !player || !player->IsClass(CLASS_ROGUE)
        || !player->HasAura(SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND)
        || !player->HasAura(SPELL_SOD_ROGUE_BLADE_DANCE))
        return nullptr;

    return player;
}

uint32 GetPhysicalReductionPct(Player const* player)
{
    uint32 const baseline = player->GetLevel() * 5;
    uint32 const defense = player->GetSkillValue(SKILL_DEFENSE);
    uint32 const bonus = defense > baseline ? (defense - baseline) / 12 : 0;
    return std::min<uint32>(100, 20 + bonus);
}

void ApplyPhysicalReduction(Player const* player, uint32& damage)
{
    uint32 const reduction = GetPhysicalReductionPct(player);
    damage = uint32(uint64(damage) * (100 - reduction) / 100);
}

void ApplyPhysicalReduction(Player const* player, int32& damage)
{
    uint32 const reduction = GetPhysicalReductionPct(player);
    damage = int32(int64(damage) * (100 - reduction) / 100);
}
}

class spell_sod_rogue_just_a_flesh_wound : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_just_a_flesh_wound);

    void GateAuraAmount(AuraEffect const* /*aurEff*/, int32& amount,
        bool& /*canBeRecalculated*/)
    {
        if (!SodRogueEnabled())
            amount = 0;
    }

    void ApplyDodgeAura(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* owner = GetTarget();
        if (SodRogueEnabled() && owner && !owner->HasAura(SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND_DODGE))
            owner->CastSpell(owner, SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND_DODGE, true);
    }

    void RemoveDodgeAura(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* owner = GetTarget())
            owner->RemoveAurasDueToSpell(SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND_DODGE);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_rogue_just_a_flesh_wound::GateAuraAmount,
            EFFECT_0, SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_rogue_just_a_flesh_wound::GateAuraAmount,
            EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_rogue_just_a_flesh_wound::GateAuraAmount,
            EFFECT_2, SPELL_AURA_MOD_THREAT);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_rogue_just_a_flesh_wound::ApplyDodgeAura,
            EFFECT_0, SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_rogue_just_a_flesh_wound::RemoveDodgeAura,
            EFFECT_0, SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_rogue_just_a_flesh_wound_feint : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_just_a_flesh_wound_feint);

    void ReplaceFeintWithTaunt(SpellEffIndex effectIndex)
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue
            || !rogue->HasAura(SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND))
            return;

        PreventHitDefaultEffect(effectIndex);
        if (Unit* target = rogue->GetSelectedUnit())
            rogue->CastSpell(target, SPELL_ROGUE_TAUNT, true);
    }

    void RemoveFeintThreatReduction(SpellEffIndex effectIndex)
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (SodRogueEnabled() && rogue
            && rogue->HasAura(SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND))
            PreventHitDefaultEffect(effectIndex);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_rogue_just_a_flesh_wound_feint::ReplaceFeintWithTaunt,
            EFFECT_0, SPELL_EFFECT_THREAT);
        OnEffectHit += SpellEffectFn(
            spell_sod_rogue_just_a_flesh_wound_feint::RemoveFeintThreatReduction,
            EFFECT_1, SPELL_EFFECT_APPLY_AURA);
    }
};

class unit_sod_rogue_just_a_flesh_wound : public UnitScript
{
public:
    unit_sod_rogue_just_a_flesh_wound() : UnitScript("unit_sod_rogue_just_a_flesh_wound", true,
        { UNITHOOK_MODIFY_PERIODIC_DAMAGE_AURAS_TICK, UNITHOOK_MODIFY_MELEE_DAMAGE,
          UNITHOOK_MODIFY_SPELL_DAMAGE_TAKEN }) { }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* /*attacker*/, uint32& damage,
        SpellInfo const* spellInfo) override
    {
        Player* player = GetProtectedRogue(target);
        if (!player || !damage || !spellInfo
            || !(spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL))
            return;

        ApplyPhysicalReduction(player, damage);
    }

    void ModifyMeleeDamage(Unit* target, Unit* /*attacker*/, uint32& damage) override
    {
        Player* player = GetProtectedRogue(target);
        if (!player || !damage)
            return;

        ApplyPhysicalReduction(player, damage);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* /*attacker*/, int32& damage,
        SpellInfo const* spellInfo) override
    {
        Player* player = GetProtectedRogue(target);
        if (!player || damage <= 0 || !spellInfo
            || !(spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL))
            return;

        ApplyPhysicalReduction(player, damage);
    }
};

void AddSC_sod_rogue_just_a_flesh_wound()
{
    RegisterSpellScript(spell_sod_rogue_just_a_flesh_wound);
    RegisterSpellScript(spell_sod_rogue_just_a_flesh_wound_feint);
    new unit_sod_rogue_just_a_flesh_wound();
}
