/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "SpellMgr.h"

class spell_sod_druid_dreamstate : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_dreamstate);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetActor()->IsPlayer()
            || !eventInfo.GetSpellInfo() || !eventInfo.GetDamageInfo())
            return false;

        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return spellInfo->Id == SPELL_DRUID_STARSURGE
            || (eventInfo.GetHitMask() & PROC_HIT_CRITICAL) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* actor = eventInfo.GetActor();
        if (!actor)
            return;

        CustomSpellValues regenValues;
        regenValues.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidDreamstateManaRegenDurationSeconds() * IN_MILLISECONDS));
        regenValues.AddSpellMod(SPELLVALUE_BASE_POINT0,
            int32(SodDruidDreamstateManaRegenPct()) - 1);
        actor->CastCustomSpell(SPELL_SOD_DRUID_DREAMSTATE_REGEN,
            regenValues, actor, TRIGGERED_FULL_MASK);

        Unit* target = eventInfo.GetActionTarget();
        if (!target || target->IsPlayer())
            return;

        CustomSpellValues damageValues;
        damageValues.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidDreamstateDamageTakenDurationSeconds() * IN_MILLISECONDS));
        damageValues.AddSpellMod(SPELLVALUE_BASE_POINT0,
            int32(SodDruidDreamstateDamageTakenPct()) - 1);
        damageValues.AddSpellMod(SPELLVALUE_BASE_POINT1,
            int32(SodDruidDreamstateDamageTakenPct()) - 1);
        actor->CastCustomSpell(SPELL_SOD_DRUID_DREAMSTATE_MAGIC,
            damageValues, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_dreamstate::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_druid_dreamstate::HandleProc,
            EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

void AddSC_sod_druid_dreamstate()
{
    RegisterSpellScript(spell_sod_druid_dreamstate);
}
