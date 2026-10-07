/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"
#include "SpellMgr.h"
#include "Unit.h"

class spell_sod_paladin_righteous_vengeance : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_righteous_vengeance);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SOD_PALADIN_RIGHTEOUS_VENGEANCE_DOT });
    }

    void HandleDamagePctApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraEffect* effect = GetEffect(EFFECT_0);
        if (effect)
            effect->ChangeAmount(static_cast<int32>(SodPaladinRighteousVengeanceDamagePct()));
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        return eventInfo.GetActionTarget() && damageInfo && damageInfo->GetDamage();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* target = eventInfo.GetActionTarget();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        Unit* caster = GetTarget();
        if (!target || !caster || !damageInfo || !damageInfo->GetDamage())
            return;

        int32 amount = CalculatePct(static_cast<int32>(damageInfo->GetDamage()), aurEff->GetAmount()) / 4;
        target->CastDelayedSpellWithPeriodicAmount(
            caster, SPELL_SOD_PALADIN_RIGHTEOUS_VENGEANCE_DOT,
            SPELL_AURA_PERIODIC_DAMAGE, amount);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_righteous_vengeance::HandleDamagePctApply,
            EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_righteous_vengeance::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_righteous_vengeance::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_righteous_vengeance()
{
    RegisterSpellScript(spell_sod_paladin_righteous_vengeance);
}
