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

// Trinchar: el golpe de barrido reparte el daño del arma entre los enemigos contiguos del
// objetivo. El objetivo principal recibe un 50 % más, el valor que el efecto dummy 3 sólo
// muestra en el tooltip ($s3).
class spell_sod_hunter_carve : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_carve);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    void IncreasePrimaryDamage(SpellEffIndex /*effIndex*/)
    {
        if (GetHitUnit() != GetExplTargetUnit())
            return;

        SetHitDamage(GetHitDamage() + int32(CalculatePct(GetHitDamage(), 50)));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_sod_hunter_carve::IncreasePrimaryDamage,
            EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
    }
};

void AddSC_sod_hunter_carve()
{
    RegisterSpellScript(spell_sod_hunter_carve);
}
