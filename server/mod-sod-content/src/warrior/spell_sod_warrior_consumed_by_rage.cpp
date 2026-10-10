/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

// Consumido por la ira: al superar el umbral de ira (60) el guerrero se enfurece. Se aplica
// Enfurecer nativo de WotLK (12880) durante su duración; es el mismo estado que exige
// Arremetida enfurecida y el que activa las facultades que requieren estar enfurecido.
class spell_sod_warrior_consumed_by_rage : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_consumed_by_rage);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player || player->HasAura(SPELL_WARRIOR_ENRAGE))
            return;

        if (int32(player->GetPower(POWER_RAGE)) > aurEff->GetAmount() * 10)
            player->CastSpell(player, SPELL_WARRIOR_ENRAGE, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_warrior_consumed_by_rage::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_warrior_consumed_by_rage()
{
    RegisterSpellScript(spell_sod_warrior_consumed_by_rage);
}
