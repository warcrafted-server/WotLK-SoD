/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "SpellScript.h"
#include "Unit.h"

// Ola de choque: el cliente y la ficha de SoD dan el daño como el 50 % del poder de ataque
// ($m3/100), pero el core solo aplica ese coeficiente al id 46968 exacto
// (Spell::EffectSchoolDMG), así que el clon 440488 lo añade aquí sobre el efecto de daño de la
// plantilla. El dummy 50 del tercer efecto queda solo para la ficha del cliente.
class spell_sod_warrior_shockwave : public SpellScript
{
    PrepareSpellScript(spell_sod_warrior_shockwave);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        SetEffectValue(int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.5f));
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(
            spell_sod_warrior_shockwave::HandleDamage,
            EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_sod_warrior_shockwave()
{
    RegisterSpellScript(spell_sod_warrior_shockwave);
}
