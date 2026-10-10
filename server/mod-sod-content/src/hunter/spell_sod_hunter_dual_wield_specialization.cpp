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

// Con la runa y un arma en la mano izquierda, Golpe de raptor realiza también un ataque
// inmediato con esa arma. El aura 122 de la propia runa aumenta el daño de mano izquierda.
class spell_sod_hunter_dual_wield_specialization_raptor_strike : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_dual_wield_specialization_raptor_strike);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void HandleAfterHit()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetHitUnit();
        if (!player || !target || !player->HasAura(SPELL_SOD_HUNTER_DUAL_WIELD_SPECIALIZATION)
            || !player->GetWeaponForAttack(OFF_ATTACK))
            return;

        player->AttackerStateUpdate(target, OFF_ATTACK, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(
            spell_sod_hunter_dual_wield_specialization_raptor_strike::HandleAfterHit);
    }
};

void AddSC_sod_hunter_dual_wield_specialization()
{
    RegisterSpellScript(spell_sod_hunter_dual_wield_specialization_raptor_strike);
}
