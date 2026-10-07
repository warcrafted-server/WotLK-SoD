/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_art_of_war : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_art_of_war);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return (eventInfo.GetHitMask() & PROC_HIT_CRITICAL) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* actor = eventInfo.GetActor();
        Player* player = actor ? actor->ToPlayer() : nullptr;
        int32 reductionMs = SodPaladinArtOfWarCooldownReductionMs();
        if (!player || reductionMs <= 0)
            return;

        for (uint32 spellId : SPELL_PALADIN_EXORCISM_RANKS)
        {
            uint32 remainingMs = player->GetSpellCooldownDelay(spellId);
            if (!remainingMs)
                continue;

            int32 reduction = std::min(remainingMs, uint32(reductionMs));
            player->ModifySpellCooldown(spellId, -reduction);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_art_of_war::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_paladin_art_of_war::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_art_of_war()
{
    RegisterSpellScript(spell_sod_paladin_art_of_war);
}
