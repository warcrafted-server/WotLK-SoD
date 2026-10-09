/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include <algorithm>

class spell_sod_paladin_shock_and_awe : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_shock_and_awe);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!player || eventInfo.GetActor() != player || !spellInfo || !damageInfo
            || damageInfo->GetDamage() == 0 || player->HasAura(SPELL_PALADIN_RIGHTEOUS_FURY))
            return false;

        return spellInfo->SpellFamilyName == SPELLFAMILY_PALADIN
            && spellInfo->SpellFamilyFlags.HasFlag(0x00200000, 0x00010000, 0);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        if (!player)
            return;

        uint32 intellectPct = std::min<uint32>(
            SodPaladinShockAndAweIntellectSpellDamagePct(), 1000);
        int32 spellDamage = int32(player->GetStat(STAT_INTELLECT)
            * float(intellectPct) / 100.0f);
        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, spellDamage);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, -int32(std::min<uint32>(
            SodPaladinShockAndAweThreatReductionPct(), 100)));
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodPaladinShockAndAweDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_PALADIN_SHOCK_AND_AWE_BUFF,
            values, player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_shock_and_awe::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_shock_and_awe::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_shock_and_awe()
{
    RegisterSpellScript(spell_sod_paladin_shock_and_awe);
}
