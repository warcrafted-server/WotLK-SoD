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

class spell_sod_rogue_quick_draw : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_quick_draw);

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_quick_draw::CheckRogueRune);
    }
};

void AddSC_sod_rogue_quick_draw()
{
    RegisterSpellScript(spell_sod_rogue_quick_draw);
}
