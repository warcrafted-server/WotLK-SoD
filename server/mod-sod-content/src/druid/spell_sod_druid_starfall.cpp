/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

class spell_sod_druid_starfall : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_starfall);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return SPELL_FAILED_DONT_REPORT;

        uint32 const cost = caster->GetCreateMana() * SodDruidStarfallManaCostPct() / 100;
        return caster->GetPower(POWER_MANA) >= int32(cost)
            ? SPELL_CAST_OK : SPELL_FAILED_NO_POWER;
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint32 const cost = caster->GetCreateMana() * SodDruidStarfallManaCostPct() / 100;
        caster->ModifyPower(POWER_MANA, -int32(cost));
        caster->AddSpellCooldown(GetSpellInfo()->Id, 0,
            SodDruidStarfallCooldownSeconds() * IN_MILLISECONDS);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_druid_starfall::CheckCast);
        AfterCast += SpellCastFn(spell_sod_druid_starfall::HandleAfterCast);
    }
};

class spell_sod_druid_starfall_aura : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_starfall_aura);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void SetDuration(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Aura* aura = GetAura())
        {
            int32 const duration = int32(SodDruidStarfallDurationSeconds() * IN_MILLISECONDS);
            aura->SetMaxDuration(duration);
            aura->SetDuration(duration);
        }
    }

    void CalculatePeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* caster = GetCaster();
        if (caster)
            caster->CastSpell(caster, SPELL_SOD_DRUID_STARFALL_DAMAGE, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_sod_druid_starfall_aura::SetDuration,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_druid_starfall_aura::CalculatePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_druid_starfall_aura::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_druid_starfall()
{
    RegisterSpellScript(spell_sod_druid_starfall);
    RegisterSpellScript(spell_sod_druid_starfall_aura);
}
