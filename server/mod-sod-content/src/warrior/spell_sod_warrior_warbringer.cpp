/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Spell.h"
#include "Unit.h"

// Belisario: el aura pasiva del hechizo ya hace que Cargar, Interceptar e Intervenir se puedan
// usar en combate y en cualquier actitud (auras nativas 262 y 275). Este script, enganchado a
// los tres hechizos, les quita al activarlos los efectos que reducen la movilidad (raíces y
// ralentizaciones).
class spell_sod_warrior_warbringer : public SpellScript
{
    PrepareSpellScript(spell_sod_warrior_warbringer);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void RemoveMovementImpairing()
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->HasAura(SPELL_SOD_WARRIOR_WARBRINGER))
            return;

        caster->RemoveAurasWithMechanic((1ULL << MECHANIC_ROOT) | (1ULL << MECHANIC_SNARE));
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_sod_warrior_warbringer::RemoveMovementImpairing);
    }
};

void AddSC_sod_warrior_warbringer()
{
    RegisterSpellScript(spell_sod_warrior_warbringer);
}
