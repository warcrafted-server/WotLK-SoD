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
bool SodWearingShield(Player* player)
{
    Item* shield = player ? player->GetShield() : nullptr;
    return shield && shield->GetTemplate()->InventoryType == INVTYPE_SHIELD;
}

// Mientras dure la actitud, concede el bono de escudo (900053) solo con escudo y mantiene la
// penalización (900054). El id 412513 usa la forma 24 de SoD, que 3.3.5a no conoce: el core la
// registra como forma desconocida y el cliente no muestra una actitud propia (ver TODO.md).
void UpdateGladiatorStance(Player* player)
{
    if (!player)
        return;

    if (SodWearingShield(player))
        player->CastSpell(player, SPELL_SOD_WARRIOR_GLADIATOR_STANCE_SHIELD, true);
    else
        player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_GLADIATOR_STANCE_SHIELD);

    player->CastSpell(player, SPELL_SOD_WARRIOR_GLADIATOR_STANCE_PENALTY, true);
}

void RemoveGladiatorStance(Player* player)
{
    if (!player)
        return;

    player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_GLADIATOR_STANCE_SHIELD);
    player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_GLADIATOR_STANCE_PENALTY);
}
}

class spell_sod_warrior_gladiator_stance : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_gladiator_stance);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        UpdateGladiatorStance(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        UpdateGladiatorStance(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        RemoveGladiatorStance(GetTarget() ? GetTarget()->ToPlayer() : nullptr);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_warrior_gladiator_stance::HandleApply,
            EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_warrior_gladiator_stance::HandlePeriodic,
            EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_warrior_gladiator_stance::HandleRemove,
            EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_warrior_gladiator_stance()
{
    RegisterSpellScript(spell_sod_warrior_gladiator_stance);
}
