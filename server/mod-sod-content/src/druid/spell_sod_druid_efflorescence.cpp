/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

#include "Group.h"

class spell_sod_druid_efflorescence : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_efflorescence);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return eventInfo.GetActor() && eventInfo.GetActor()->IsPlayer()
            && eventInfo.GetActionTarget() && spellInfo
            && spellInfo->Id == SPELL_DRUID_SWIFTMEND;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* actor = eventInfo.GetActor();
        Unit* center = eventInfo.GetActionTarget();
        if (!actor || !center)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidEfflorescenceDurationSeconds() * IN_MILLISECONDS));
        actor->CastCustomSpell(SPELL_SOD_DRUID_EFFLORESCENCE_AURA,
            values, center, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_efflorescence::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_druid_efflorescence::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_druid_efflorescence_aura : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_efflorescence_aura);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void CalculatePeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Unit* center = GetTarget();
        Unit* caster = GetCaster();
        if (!center || !caster || !center->IsInWorld())
            return;

        float const radius = SodDruidEfflorescenceRadiusYards();
        Group* group = caster->ToPlayer() ? caster->ToPlayer()->GetGroup() : nullptr;
        if (group)
        {
            for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
            {
                Player* member = itr->GetSource();
                if (member && member->IsInWorld() && member->IsWithinDistInMap(center, radius))
                    caster->CastSpell(member, 417148, TRIGGERED_FULL_MASK);
            }
        }
        else if (center->IsFriendlyTo(caster))
            caster->CastSpell(center, 417148, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_druid_efflorescence_aura::CalculatePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_druid_efflorescence_aura::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_druid_efflorescence()
{
    RegisterSpellScript(spell_sod_druid_efflorescence);
    RegisterSpellScript(spell_sod_druid_efflorescence_aura);
}
