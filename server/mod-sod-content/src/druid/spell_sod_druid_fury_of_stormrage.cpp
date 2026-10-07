/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "SpellInfo.h"
#include "SpellMgr.h"

class spell_sod_druid_fury_of_stormrage : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_fury_of_stormrage);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        SpellInfo const* wrath = sSpellMgr->GetSpellInfo(SPELL_DRUID_WRATH);
        if (!wrath || !wrath->SpellFamilyFlags)
            return;

        if (!spellMod)
        {
            spellMod = new SpellModifier(GetAura());
            spellMod->op = SPELLMOD_COST;
            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = GetId();
            spellMod->mask = wrath->SpellFamilyFlags;
        }

        if (aurEff->GetEffIndex() == EFFECT_0)
            spellMod->value = -int32(SodDruidFuryOfStormrageWrathCostReductionPct());
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* actor = eventInfo.GetActor();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        SpellInfo const* wrath = sSpellMgr->GetSpellInfo(SPELL_DRUID_WRATH);
        if (!actor || !actor->IsPlayer() || !spellInfo || !wrath
            || spellInfo->SpellFamilyName != SPELLFAMILY_DRUID)
            return false;

        flag96 const& wrathMask = wrath->SpellFamilyFlags;
        if (!spellInfo->SpellFamilyFlags.HasFlag(wrathMask[0], wrathMask[1], wrathMask[2]))
            return false;

        return roll_chance_i(int32(SodDruidFuryOfStormrageProcChance()));
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* actor = eventInfo.GetActor();
        if (!actor)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidFuryOfStormrageBuffDurationSeconds() * IN_MILLISECONDS));
        actor->CastCustomSpell(SPELL_SOD_DRUID_FURY_OF_STORMRAGE_BUFF,
            values, actor, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_druid_fury_of_stormrage::HandleSpellMod,
            EFFECT_0, SPELL_AURA_DUMMY);
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_fury_of_stormrage::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_druid_fury_of_stormrage::HandleProc,
            EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class spell_sod_druid_fury_of_stormrage_buff : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_fury_of_stormrage_buff);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleSpellMod(AuraEffect const* /*aurEff*/, SpellModifier*& spellMod)
    {
        if (!spellMod)
        {
            spellMod = new SpellModifier(GetAura());
            spellMod->op = SPELLMOD_CASTING_TIME;
            spellMod->type = SPELLMOD_PCT;
            spellMod->spellId = GetId();
            spellMod->mask = flag96(SPELL_DRUID_HEALING_TOUCH_FAMILY_MASK0, 0, 0);
        }

        spellMod->value = -100;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        return spellInfo && spellInfo->SpellFamilyName == SPELLFAMILY_DRUID
            && spellInfo->SpellFamilyFlags.HasFlag(SPELL_DRUID_HEALING_TOUCH_FAMILY_MASK0, 0, 0);
    }

    void Consume(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* actor = eventInfo.GetActor())
            actor->RemoveAurasDueToSpell(SPELL_SOD_DRUID_FURY_OF_STORMRAGE_BUFF);
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_druid_fury_of_stormrage_buff::HandleSpellMod,
            EFFECT_1, SPELL_AURA_DUMMY);
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_fury_of_stormrage_buff::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_druid_fury_of_stormrage_buff::Consume,
            EFFECT_2, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_druid_fury_of_stormrage()
{
    RegisterSpellScript(spell_sod_druid_fury_of_stormrage);
    RegisterSpellScript(spell_sod_druid_fury_of_stormrage_buff);
}
