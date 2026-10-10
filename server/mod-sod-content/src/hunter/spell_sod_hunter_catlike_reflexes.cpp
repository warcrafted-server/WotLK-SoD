/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_hunter.h"

#include "Player.h"
#include "SpellScript.h"

class spell_sod_hunter_catlike_reflexes : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_catlike_reflexes);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void ReduceFlankingStrikeCooldown()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_HUNTER_CATLIKE_REFLEXES))
            return;

        uint32 remainingMs = player->GetSpellCooldownDelay(SPELL_SOD_HUNTER_FLANKING_STRIKE);
        if (remainingMs)
            player->ModifySpellCooldown(SPELL_SOD_HUNTER_FLANKING_STRIKE,
                -static_cast<int32>(remainingMs / 2));
    }

    void Register() override
    {
        AfterCast += SpellCastFn(
            spell_sod_hunter_catlike_reflexes::ReduceFlankingStrikeCooldown);
    }
};

void AddSC_sod_hunter_catlike_reflexes()
{
    RegisterSpellScript(spell_sod_hunter_catlike_reflexes);
}
