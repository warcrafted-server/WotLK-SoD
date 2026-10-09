/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "Player.h"
#include "SpellInfo.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_hand_of_reckoning : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_hand_of_reckoning);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckHealProc(ProcEventInfo& eventInfo)
    {
        Player* paladin = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        HealInfo const* healInfo = eventInfo.GetHealInfo();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return paladin && paladin->HasAura(SPELL_PALADIN_RIGHTEOUS_FURY)
            && eventInfo.GetActor() && eventInfo.GetActor() != paladin
            && eventInfo.GetActionTarget() == paladin && healInfo
            && healInfo->GetEffectiveHeal() > 0 && spellInfo && spellInfo->IsPositive();
    }

    void HandleHealProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* paladin = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        HealInfo const* healInfo = eventInfo.GetHealInfo();
        if (!paladin || !healInfo)
            return;

        uint32 manaPct = std::min<uint32>(SodPaladinHandOfReckoningManaRestorePct(), 100);
        int32 mana = int32(CalculatePct(healInfo->GetEffectiveHeal(), manaPct));
        if (mana > 0)
            paladin->ModifyPower(POWER_MANA, mana);
    }

    void CalculateAbsorbAmount(AuraEffect const* /*aurEff*/, int32& amount,
        bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void HandleAbsorb(AuraEffect* /*aurEff*/, DamageInfo& damageInfo, uint32& absorbAmount)
    {
        Player* paladin = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!paladin || !paladin->HasAura(SPELL_PALADIN_RIGHTEOUS_FURY)
            || !damageInfo.GetDamage())
            return;

        uint32 thresholdPct = std::min<uint32>(
            SodPaladinHandOfReckoningDamageThresholdPct(), 100);
        uint32 reductionPct = std::min<uint32>(
            SodPaladinHandOfReckoningDamageReductionPct(), 100);
        uint32 allowedHealth = CalculatePct(paladin->GetMaxHealth(), thresholdPct);
        uint32 health = paladin->GetHealth();
        uint32 damage = damageInfo.GetDamage();
        uint32 remainingHealth = damage >= health ? 0 : health - damage;
        if (remainingHealth >= allowedHealth)
            return;

        uint32 damageToReduce = health < allowedHealth ? damage : allowedHealth - remainingHealth;
        absorbAmount = CalculatePct(damageToReduce, reductionPct);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(
            spell_sod_paladin_hand_of_reckoning::CheckHealProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_hand_of_reckoning::HandleHealProc,
            EFFECT_0, SPELL_AURA_DUMMY);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_paladin_hand_of_reckoning::CalculateAbsorbAmount,
            EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(
            spell_sod_paladin_hand_of_reckoning::HandleAbsorb, EFFECT_1);
    }
};

void AddSC_sod_paladin_hand_of_reckoning()
{
    RegisterSpellScript(spell_sod_paladin_hand_of_reckoning);
}
