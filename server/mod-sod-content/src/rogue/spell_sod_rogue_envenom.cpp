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
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_envenom : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_envenom);

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void SetInstantPoisonBonusDuration()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetExplTargetUnit();
        if (!rogue || !target)
            return;

        uint8 const comboPoints = rogue->GetComboPoints(target);
        if (!comboPoints)
            return;

        if (Aura* envenom = rogue->GetAura(SPELL_SOD_ROGUE_ENVENOM, rogue->GetGUID()))
        {
            int32 const duration = (1 + comboPoints) * IN_MILLISECONDS;
            envenom->SetMaxDuration(duration);
            envenom->SetDuration(duration);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_envenom::CheckRogueRune);
        AfterHit += SpellHitFn(spell_sod_rogue_envenom::SetInstantPoisonBonusDuration);
    }
};

void AddSC_sod_rogue_envenom()
{
    RegisterSpellScript(spell_sod_rogue_envenom);
}
