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

// Golpe rápido: facultad instantánea que solo se puede usar con un arma a dos manos en la mano
// principal. El daño basado en el poder de ataque lo aporta el coeficiente de spell_bonus_data.
class spell_sod_warrior_quick_strike : public SpellScript
{
    PrepareSpellScript(spell_sod_warrior_quick_strike);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    SpellCastResult CheckWeapon()
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Item* weapon = caster ? caster->GetWeaponForAttack(BASE_ATTACK, true) : nullptr;
        if (!weapon || weapon->GetTemplate()->InventoryType != INVTYPE_2HWEAPON)
            return SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_warrior_quick_strike::CheckWeapon);
    }
};

void AddSC_sod_warrior_quick_strike()
{
    RegisterSpellScript(spell_sod_warrior_quick_strike);
}
