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

#include <algorithm>

class spell_sod_paladin_fanaticism : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_fanaticism);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleHolyCritApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraEffect* effect = GetEffect(EFFECT_0);
        if (effect)
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinFanaticismHolyCritChancePct(), 100)));
    }

    void HandleHealingPctApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraEffect* effect = GetEffect(EFFECT_1);
        if (effect)
            effect->ChangeAmount(static_cast<int32>(std::min<uint32>(
                SodPaladinFanaticismHealingPct(), 100)));
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        HealInfo* healInfo = eventInfo.GetHealInfo();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return healInfo && healInfo->GetHeal() &&
            (healInfo->GetHitMask() & PROC_HIT_CRITICAL) && spellInfo &&
            spellInfo->Id != SPELL_SOD_PALADIN_FANATICISM_HOT;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* target = eventInfo.GetActionTarget();
        HealInfo* healInfo = eventInfo.GetHealInfo();
        if (!target || !healInfo || !healInfo->GetHeal())
            return;

        uint32 healingPct = std::min<uint32>(SodPaladinFanaticismHealingPct(), 100);
        int32 tickAmount = CalculatePct(static_cast<int32>(healInfo->GetHeal()),
            static_cast<int32>(healingPct)) / 4;
        if (tickAmount <= 0)
            return;

        GetTarget()->CastCustomSpell(SPELL_SOD_PALADIN_FANATICISM_HOT,
            SPELLVALUE_BASE_POINT0, tickAmount, target, true, nullptr, GetEffect(EFFECT_1));
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_fanaticism::HandleHolyCritApply,
            EFFECT_0, SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_fanaticism::HandleHealingPctApply,
            EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_fanaticism::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_fanaticism::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_fanaticism()
{
    RegisterSpellScript(spell_sod_paladin_fanaticism);
}
