/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Creature.h"
#include "SpellScript.h"
#include "Unit.h"

// Gancho: el arrastre lo hace el efecto nativo 124 (arrastrar hacia el lanzador). Aquí solo
// se restringe el objetivo: no se puede usar contra enemigos de más de un nivel por encima del
// guerrero ni contra jefes de banda o mazmorra.
class spell_sod_warrior_meathook : public SpellScript
{
    PrepareSpellScript(spell_sod_warrior_meathook);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    SpellCastResult CheckTarget()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!caster || !target)
            return SPELL_FAILED_BAD_TARGETS;

        if (target->GetLevel() > caster->GetLevel() + 1)
            return SPELL_FAILED_HIGHLEVEL;

        if (Creature* creature = target->ToCreature())
            if (creature->isWorldBoss() || creature->IsDungeonBoss())
                return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_warrior_meathook::CheckTarget);
    }
};

void AddSC_sod_warrior_meathook()
{
    RegisterSpellScript(spell_sod_warrior_meathook);
}
