/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_hunter.h"

#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_hunter_improved_volley : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_improved_volley);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void AddBonusDamage(SpellEffIndex /*effIndex*/)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_HUNTER_IMPROVED_VOLLEY))
            return;

        int32 const damage = GetHitDamage();
        int32 const rangedAttackPower = int32(player->GetTotalAttackPowerValue(RANGED_ATTACK));
        int32 const attackPowerBonus = int32(CalculatePct(rangedAttackPower, 3));
        SetHitDamage(damage + damage + attackPowerBonus);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_hunter_improved_volley::AddBonusDamage,
            EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_sod_hunter_improved_volley()
{
    RegisterSpellScript(spell_sod_hunter_improved_volley);
}
