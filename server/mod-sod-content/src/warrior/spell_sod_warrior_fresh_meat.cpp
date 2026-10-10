/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Random.h"
#include "SpellScript.h"
#include "Unit.h"

// Carne fresca: al infligir daño con Sed de sangre, Golpe mortal o Embate con escudo (proc de
// la fila spell_proc por familia 4 y sus máscaras) aplica Enfurecer nativo (12880) y el
// beneficio 440483 (+10 % de daño físico durante 12 s). La ficha de SoD da un 100 % la primera
// vez y un 10 % las siguientes; «la primera vez» se interpreta aquí como el primer proc tras
// equipar la runa, porque el catálogo no permite distinguir por objetivo.
class spell_sod_warrior_fresh_meat : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_fresh_meat);

    bool _firstProc = true;

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* target = GetTarget();
        if (!target)
            return;

        if (!_firstProc && !roll_chance_i(10))
            return;

        _firstProc = false;

        if (!target->HasAura(SPELL_WARRIOR_ENRAGE))
            target->CastSpell(target, SPELL_WARRIOR_ENRAGE, true);
        target->CastSpell(target, SPELL_SOD_WARRIOR_FRESH_MEAT_ENRAGE, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(
            spell_sod_warrior_fresh_meat::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_warrior_fresh_meat()
{
    RegisterSpellScript(spell_sod_warrior_fresh_meat);
}
