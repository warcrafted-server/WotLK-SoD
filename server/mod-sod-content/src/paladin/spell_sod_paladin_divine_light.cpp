/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_paladin.h"

#include <algorithm>

class spell_sod_paladin_divine_light : public SpellScript
{
    PrepareSpellScript(spell_sod_paladin_divine_light);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void ApplyHealWatcher()
    {
        Unit* caster = GetCaster();
        if (caster)
            caster->CastCustomSpell(SPELL_SOD_PALADIN_DIVINE_LIGHT_WATCH,
                SPELLVALUE_AURA_DURATION, 3000, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_sod_paladin_divine_light::ApplyHealWatcher);
    }
};

class spell_sod_paladin_divine_light_watch : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_divine_light_watch);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        HealInfo* healInfo = eventInfo.GetHealInfo();
        return spellInfo && spellInfo->Id == SPELL_SOD_PALADIN_DIVINE_LIGHT
            && healInfo && healInfo->GetHeal();
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetTarget();
        Unit* target = eventInfo.GetActionTarget();
        HealInfo* healInfo = eventInfo.GetHealInfo();
        if (caster)
            caster->RemoveAurasDueToSpell(SPELL_SOD_PALADIN_DIVINE_LIGHT_WATCH);
        if (!caster || !target || !healInfo)
            return;

        int32 overheal = int32(healInfo->GetHeal()) - int32(healInfo->GetEffectiveHeal());
        uint32 shieldPct = std::min<uint32>(SodPaladinDivineLightOverhealShieldPct(), 100);
        int32 absorb = CalculatePct(overheal, int32(shieldPct));
        if (absorb <= 0)
            return;

        target->RemoveAurasDueToSpell(SPELL_SOD_PALADIN_DIVINE_LIGHT_SHIELD);
        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, absorb);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodPaladinDivineLightShieldDurationSeconds() * IN_MILLISECONDS));
        caster->CastCustomSpell(SPELL_SOD_PALADIN_DIVINE_LIGHT_SHIELD,
            values, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_divine_light_watch::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_divine_light_watch::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_divine_light()
{
    RegisterSpellScript(spell_sod_paladin_divine_light);
    RegisterSpellScript(spell_sod_paladin_divine_light_watch);
}
