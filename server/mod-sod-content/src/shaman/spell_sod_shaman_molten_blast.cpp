/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

#include "Random.h"

class spell_sod_shaman_molten_blast_flame_shock : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_molten_blast_flame_shock);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !SodShamanEnabled() || !player->HasSpell(SPELL_SOD_SHAMAN_MOLTEN_BLAST))
            return;

        if (roll_chance_i(10))
            player->RemoveSpellCooldown(SPELL_SOD_SHAMAN_MOLTEN_BLAST, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_shaman_molten_blast_flame_shock::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

void AddSC_sod_shaman_molten_blast()
{
    RegisterSpellScript(spell_sod_shaman_molten_blast_flame_shock);
}
