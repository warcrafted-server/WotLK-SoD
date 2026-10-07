/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

#include "SpellInfo.h"
#include "SpellMgr.h"

namespace
{
bool IsEclipseTrigger(uint32 spellId)
{
    switch (spellId)
    {
        case 2912: case 8949: case 8950: case 8951: case 9875: case 9876:
        case 25298: case 26986: case 48464: case 48465: // Starfire ranks
        case 5176: case 5177: case 5178: case 5179: case 5180: case 6780:
        case 8905: case 9912: case 26984: case 26985: case 48459: case 48461: // Wrath ranks
            return true;
        default:
            return false;
    }
}
}

class spell_sod_druid_eclipse : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_eclipse);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetActor() && eventInfo.GetActor()->IsPlayer()
            && eventInfo.GetSpellInfo() && IsEclipseTrigger(eventInfo.GetSpellInfo()->Id);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* actor = eventInfo.GetActor();
        if (!actor)
            return;

        Aura* buff = actor->GetAura(SPELL_SOD_DRUID_ECLIPSE_BUFF);
        if (!buff)
            actor->CastSpell(actor, SPELL_SOD_DRUID_ECLIPSE_BUFF, TRIGGERED_FULL_MASK);
        else if (buff->GetStackAmount() < SodDruidEclipseMaxStacks())
            buff->ModStackAmount(1);

        if (Aura* refreshed = actor->GetAura(SPELL_SOD_DRUID_ECLIPSE_BUFF))
            refreshed->SetDuration(int32(SodDruidEclipseDurationSeconds() * IN_MILLISECONDS));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_eclipse::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_druid_eclipse::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_sod_druid_eclipse_buff : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_eclipse_buff);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        if (!spellMod)
        {
            SpellInfo const* starfire = sSpellMgr->GetSpellInfo(SPELL_DRUID_STARFIRE);
            SpellInfo const* wrath = sSpellMgr->GetSpellInfo(SPELL_DRUID_WRATH);
            if (!starfire || !wrath)
                return;

            spellMod = new SpellModifier(GetAura());
            spellMod->op = aurEff->GetEffIndex() == EFFECT_0 ? SPELLMOD_CRITICAL_CHANCE
                : aurEff->GetEffIndex() == EFFECT_1 ? SPELLMOD_CASTING_TIME
                : SPELLMOD_NOT_LOSE_CASTING_TIME;
            spellMod->type = aurEff->GetEffIndex() == EFFECT_1
                ? SPELLMOD_FLAT : SPELLMOD_PCT;
            spellMod->spellId = GetId();
            spellMod->mask = starfire->SpellFamilyFlags | wrath->SpellFamilyFlags;
        }

        if (aurEff->GetEffIndex() == EFFECT_0)
            spellMod->value = int32(SodDruidEclipseCritChancePct());
        else if (aurEff->GetEffIndex() == EFFECT_1)
            spellMod->value = -int32(SodDruidEclipseCastTimeReductionMs());
        else
            spellMod->value = int32(SodDruidEclipsePushbackReductionPct());
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_druid_eclipse_buff::HandleSpellMod,
            EFFECT_ALL, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_druid_eclipse()
{
    RegisterSpellScript(spell_sod_druid_eclipse);
    RegisterSpellScript(spell_sod_druid_eclipse_buff);
}
