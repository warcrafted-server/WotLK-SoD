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

class spell_sod_paladin_art_of_war : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_art_of_war);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleCostModifierApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraEffect* effect = GetEffect(EFFECT_0);
        if (!effect)
            return;

        uint32 reductionPct = std::min<uint32>(SodPaladinArtOfWarManaCostReductionPct(), 100);
        effect->ChangeAmount(-static_cast<int32>(reductionPct));
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() != nullptr;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        uint32 reductionMs = SodPaladinArtOfWarCooldownReductionSeconds() * 1000;
        if (!reductionMs)
            return;

        for (uint32 spellId : SPELL_PALADIN_EXORCISM_RANKS)
        {
            uint32 remainingMs = player->GetSpellCooldownDelay(spellId);
            if (!remainingMs)
                continue;

            uint32 reduction = std::min(remainingMs, reductionMs);
            player->ModifySpellCooldown(spellId, -static_cast<int32>(reduction));
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_art_of_war::HandleCostModifierApply,
            EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_art_of_war::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_art_of_war::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_art_of_war()
{
    RegisterSpellScript(spell_sod_paladin_art_of_war);
}
