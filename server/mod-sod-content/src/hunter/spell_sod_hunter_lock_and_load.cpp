/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_hunter.h"

#include "AllSpellScript.h"
#include "Player.h"
#include "SpellInfo.h"
#include "Unit.h"

namespace
{
constexpr uint32 HUNTER_TRAP_PLACEMENT_MASK = 0x80;

bool IsHunterTrapPlacement(SpellInfo const* spellInfo)
{
    if (!spellInfo || spellInfo->SpellFamilyName != SPELLFAMILY_HUNTER)
        return false;

    // Las facultades de colocar trampas de Spell.dbc 3.3.5a usan la máscara A 0x80
    // y uno de los cuatro efectos de invocación de objeto.
    if (!(spellInfo->SpellFamilyFlags[0] & HUNTER_TRAP_PLACEMENT_MASK))
        return false;

    return spellInfo->HasEffect(SPELL_EFFECT_SUMMON_OBJECT_SLOT1)
        || spellInfo->HasEffect(SPELL_EFFECT_SUMMON_OBJECT_SLOT2)
        || spellInfo->HasEffect(SPELL_EFFECT_SUMMON_OBJECT_SLOT3)
        || spellInfo->HasEffect(SPELL_EFFECT_SUMMON_OBJECT_SLOT4);
}
}

// El guion nativo activa Lock and Load al detonarse una trampa. SoD lo activa al colocarla;
// se concede el beneficio de WotLK al lanzar la facultad que crea la trampa.
class all_sod_hunter_lock_and_load : public AllSpellScript
{
public:
    all_sod_hunter_lock_and_load()
        : AllSpellScript("all_sod_hunter_lock_and_load", { ALLSPELLHOOK_ON_CAST }) { }

    void OnSpellCast(Spell* /*spell*/, Unit* caster, SpellInfo const* spellInfo,
        bool /*skipCheck*/) override
    {
        Player* player = caster ? caster->ToPlayer() : nullptr;
        if (!player || !SodHunterEnabled() || !player->HasAura(SPELL_SOD_HUNTER_LOCK_AND_LOAD)
            || !IsHunterTrapPlacement(spellInfo))
            return;

        player->CastSpell(player, SPELL_SOD_HUNTER_LOCK_AND_LOAD_TRIGGER, true);
        // Evita que el proc nativo vuelva a conceder el beneficio cuando la trampa se active.
        player->CastSpell(player, SPELL_SOD_HUNTER_LOCK_AND_LOAD_MARKER, true);
    }
};

void AddSC_sod_hunter_lock_and_load()
{
    new all_sod_hunter_lock_and_load();
}
