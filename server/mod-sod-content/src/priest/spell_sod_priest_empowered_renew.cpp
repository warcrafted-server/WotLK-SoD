/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_priest.h"

#include "SpellAuras.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_priest_empowered_renew : public AuraScript
{
    PrepareAuraScript(spell_sod_priest_empowered_renew);

    int32 initialTickAmount = 0;

    void CacheInitialAmount(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        initialTickAmount = aurEff->GetAmount();
    }

    void IncreaseHealingPerTick(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();
        AuraEffect* renewEffect = const_cast<AuraEffect*>(aurEff);
        if (!SodPriestEnabled() || !caster || !caster->HasAura(SPELL_SOD_PRIEST_EMPOWERED_RENEW))
        {
            renewEffect->ChangeAmount(initialTickAmount, false);
            return;
        }

        int32 tickNumber = std::max<int32>(1, aurEff->GetTickNumber());
        int32 bonusPercent = 15 * tickNumber;
        renewEffect->ChangeAmount(initialTickAmount + initialTickAmount * bonusPercent / 100, false);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_priest_empowered_renew::CacheInitialAmount,
            EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_priest_empowered_renew::IncreaseHealingPerTick,
            EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

void AddSC_sod_priest_empowered_renew()
{
    RegisterSpellScript(spell_sod_priest_empowered_renew);
}
