/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_mage.h"

class spell_sod_mage_advanced_warding : public AuraScript
{
    PrepareAuraScript(spell_sod_mage_advanced_warding);

    bool Load() override
    {
        return SodMageEnabled();
    }

    bool IsRuneActive() const
    {
        Unit* caster = GetCaster();
        return caster && caster->HasAura(SPELL_SOD_MAGE_ADVANCED_WARDING);
    }

    void CalculateAbsorbAmount(AuraEffect const* /*aurEff*/, int32& amount,
        bool& canBeRecalculated)
    {
        if (!IsRuneActive())
            return;

        amount *= 2;
        canBeRecalculated = false;
    }

    void RefundMana(AuraEffect* /*aurEff*/, DamageInfo& /*damageInfo*/,
        uint32& /*absorbAmount*/)
    {
        Unit* target = GetTarget();
        if (!_manaShieldPending || !target)
            return;

        int32 manaSpent = _manaBeforeShield - target->GetPower(POWER_MANA);
        if (IsRuneActive() && manaSpent > 0)
            target->ModifyPower(POWER_MANA, manaSpent / 2);

        _manaShieldPending = false;
    }

    void RecordManaBeforeShield(AuraEffect* /*aurEff*/, DamageInfo& /*damageInfo*/,
        uint32& /*absorbAmount*/)
    {
        Unit* target = GetTarget();
        _manaShieldPending = IsRuneActive() && target;
        if (_manaShieldPending)
            _manaBeforeShield = target->GetPower(POWER_MANA);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_mage_advanced_warding::CalculateAbsorbAmount,
            EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_mage_advanced_warding::CalculateAbsorbAmount,
            EFFECT_0, SPELL_AURA_MANA_SHIELD);
        OnEffectManaShield += AuraEffectManaShieldFn(
            spell_sod_mage_advanced_warding::RecordManaBeforeShield, EFFECT_0);
        AfterEffectManaShield += AuraEffectManaShieldFn(
            spell_sod_mage_advanced_warding::RefundMana, EFFECT_0);
    }

private:
    int32 _manaBeforeShield = 0;
    bool _manaShieldPending = false;
};

void AddSC_sod_mage_advanced_warding()
{
    RegisterSpellScript(spell_sod_mage_advanced_warding);
}
