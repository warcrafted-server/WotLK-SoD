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
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_unfair_advantage : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_unfair_advantage);

    bool Load() override
    {
        Player* rogue = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        return SodRogueEnabled() && rogue && rogue->IsClass(CLASS_ROGUE);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHitMask() & (PROC_HIT_DODGE | PROC_HIT_PARRY);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* rogue = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        Unit* attacker = eventInfo.GetActor();
        if (!rogue || !attacker || !attacker->IsAlive() || attacker == rogue)
            return;

        rogue->CastSpell(attacker, SPELL_SOD_ROGUE_UNFAIR_ADVANTAGE_STRIKE,
            TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_rogue_unfair_advantage::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_rogue_unfair_advantage::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_rogue_unfair_advantage()
{
    RegisterSpellScript(spell_sod_rogue_unfair_advantage);
}
