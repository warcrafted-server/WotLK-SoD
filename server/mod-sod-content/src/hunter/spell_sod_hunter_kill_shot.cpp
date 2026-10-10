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

// Disparo mortal: clon del hechizo de WotLK con el coste (3 %), la reutilización (12 s) y los
// coeficientes de daño de SoD. Tras el lanzamiento, si el objetivo se queda al 20 % de salud o
// menos, se restablece su tiempo de reutilización (rasgo de SoD que WotLK no tiene).
class spell_sod_hunter_kill_shot : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_kill_shot);

    void HandleAfterCast()
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetExplTargetUnit();
        if (!caster || !target || !SodHunterEnabled())
            return;

        if (target->GetHealthPct() <= 20.0f)
            caster->RemoveSpellCooldown(SPELL_SOD_HUNTER_KILL_SHOT, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sod_hunter_kill_shot::HandleAfterCast);
    }
};

void AddSC_sod_hunter_kill_shot()
{
    RegisterSpellScript(spell_sod_hunter_kill_shot);
}
