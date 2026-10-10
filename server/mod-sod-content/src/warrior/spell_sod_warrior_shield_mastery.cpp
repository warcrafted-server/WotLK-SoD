/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Item.h"
#include "ItemTemplate.h"
#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool SodWarriorWearingShield(Player* player)
{
    Item* shield = player ? player->GetShield() : nullptr;
    return shield && shield->GetTemplate()->InventoryType == INVTYPE_SHIELD;
}
}

// Maestría con escudos: el sondeo de 2 s (aura 226) concede el bono de daño físico (auxiliar
// 900055, aura 79 de escuela física) solo mientras el guerrero empuñe un escudo, y lo retira en
// caso contrario. La reducción de la duración del desarme (aura 234) la aplica el propio
// hechizo, sin script.
class spell_sod_warrior_shield_mastery : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_shield_mastery);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (SodWarriorWearingShield(player))
            player->CastSpell(player, SPELL_SOD_WARRIOR_SHIELD_MASTERY_BUFF, true);
        else
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SHIELD_MASTERY_BUFF);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (player)
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_SHIELD_MASTERY_BUFF);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_warrior_shield_mastery::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_warrior_shield_mastery::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_warrior_shield_mastery()
{
    RegisterSpellScript(spell_sod_warrior_shield_mastery);
}
