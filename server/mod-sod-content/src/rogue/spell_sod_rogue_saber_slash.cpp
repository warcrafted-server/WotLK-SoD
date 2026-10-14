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
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_saber_slash : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_saber_slash);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SOD_ROGUE_SABER_SLASH_BLEED });
    }

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void ApplyBleed()
    {
        Unit* rogue = GetCaster();
        Unit* target = GetHitUnit();
        if (SodRogueEnabled() && rogue && target && target->IsAlive())
            rogue->CastSpell(target, SPELL_SOD_ROGUE_SABER_SLASH_BLEED, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_saber_slash::CheckRogueRune);
        AfterHit += SpellHitFn(spell_sod_rogue_saber_slash::ApplyBleed);
    }
};

void AddSC_sod_rogue_saber_slash()
{
    RegisterSpellScript(spell_sod_rogue_saber_slash);
}
