/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_hunter.h"

#include "Player.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
// Rango más alto de Picadura de serpiente que conoce el cazador. Propagar serpientes aplica la
// Picadura real del cazador, no una copia fija, caminando la cadena de rangos.
uint32 GetSerpentStingRank(Player* player)
{
    uint32 known = 0;
    for (uint32 id = SPELL_SOD_HUNTER_SERPENT_STING_R1; id; id = sSpellMgr->GetNextSpellInChain(id))
        if (player->HasSpell(id))
            known = id;

    return known;
}
}

// Propagar serpientes: cada objetivo golpeado por Multidisparo (id negativo -2643 enlaza todos
// los rangos) recibe la Picadura de serpiente del cazador si tiene la runa grabada.
class spell_sod_hunter_serpent_spread : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_serpent_spread);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetHitUnit();
        if (!caster || !target || !caster->HasAura(SPELL_SOD_HUNTER_SERPENT_SPREAD))
            return;

        uint32 const stingId = GetSerpentStingRank(caster);
        if (stingId)
            caster->CastSpell(target, stingId, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sod_hunter_serpent_spread::HandleHit,
            EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
    }
};

void AddSC_sod_hunter_serpent_spread()
{
    RegisterSpellScript(spell_sod_hunter_serpent_spread);
}
