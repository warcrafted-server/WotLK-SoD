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
#include "SpellMgr.h"
#include "SpellScript.h"

class spell_sod_hunter_wyvern_strike : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_wyvern_strike);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    SpellCastResult CheckWyvernStingTalent()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player)
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        for (uint32 spellId = SPELL_SOD_HUNTER_WYVERN_STING_R1; spellId;
            spellId = sSpellMgr->GetNextSpellInChain(spellId))
            if (player->HasSpell(spellId))
                return SPELL_CAST_OK;

        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(
            spell_sod_hunter_wyvern_strike::CheckWyvernStingTalent);
    }
};

void AddSC_sod_hunter_wyvern_strike()
{
    RegisterSpellScript(spell_sod_hunter_wyvern_strike);
}
