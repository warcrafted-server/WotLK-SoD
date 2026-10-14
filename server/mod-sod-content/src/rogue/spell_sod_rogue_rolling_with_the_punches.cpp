/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Player.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_rolling_with_the_punches : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_rolling_with_the_punches);

    bool Load() override
    {
        return SodRogueEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        return player && (eventInfo.GetHitMask() & (PROC_HIT_DODGE | PROC_HIT_PARRY));
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        Aura* healthAura = player->GetAura(SPELL_SOD_ROGUE_ROLLING_WITH_THE_PUNCHES_HEALTH,
            player->GetGUID());
        if (healthAura)
            healthAura->ModStackAmount(1);
        else
            player->CastSpell(player, SPELL_SOD_ROGUE_ROLLING_WITH_THE_PUNCHES_HEALTH,
                TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(
            spell_sod_rogue_rolling_with_the_punches::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_rogue_rolling_with_the_punches::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_rogue_rolling_with_the_punches()
{
    RegisterSpellScript(spell_sod_rogue_rolling_with_the_punches);
}
