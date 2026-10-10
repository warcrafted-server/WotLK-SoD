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
#include "SpellScript.h"
#include "Unit.h"

// Lobo solitario: pasiva con aura periódica dummy (226, 1 s) que mantiene el bono de daño
// 900057 (+25 % a todas las escuelas) mientras el cazador no tiene mascota activa, y lo retira
// en cuanto invoca una. La comprobación es por sondeo: puede tardar hasta 1 s en reflejarse.
class spell_sod_hunter_lone_wolf : public AuraScript
{
    PrepareAuraScript(spell_sod_hunter_lone_wolf);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (player->GetPet())
            player->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_LONE_WOLF_DAMAGE);
        else if (!player->HasAura(SPELL_SOD_HUNTER_LONE_WOLF_DAMAGE))
            player->CastSpell(player, SPELL_SOD_HUNTER_LONE_WOLF_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_sod_hunter_lone_wolf::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_hunter_lone_wolf()
{
    RegisterSpellScript(spell_sod_hunter_lone_wolf);
}
