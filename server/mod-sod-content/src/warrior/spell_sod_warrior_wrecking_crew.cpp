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

// Equipo de demolición: al aplicarse el beneficio 427066 se aplica Enfurecer nativo de WotLK
// (12880), cuyo DispelType 9 concede el estado de aura que exigen las facultades «que requieren
// estar enfurecido» y que detecta Arremetida enfurecida. El +10 % a Golpe mortal, Sed de sangre
// y Embate con escudo lo aplica el propio 427066 (aura 108 + SpellModOp 3).
class spell_sod_warrior_wrecking_crew : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_wrecking_crew);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (target && !target->HasAura(SPELL_WARRIOR_ENRAGE))
            target->CastSpell(target, SPELL_WARRIOR_ENRAGE, true);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_warrior_wrecking_crew::HandleApply,
            EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_warrior_wrecking_crew()
{
    RegisterSpellScript(spell_sod_warrior_wrecking_crew);
}
