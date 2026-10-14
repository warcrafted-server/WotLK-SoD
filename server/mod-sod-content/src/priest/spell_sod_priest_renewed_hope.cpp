/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_priest.h"

#include "Unit.h"

class spell_sod_priest_renewed_hope : public SpellScript
{
    PrepareSpellScript(spell_sod_priest_renewed_hope);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void IncreaseHealing(SpellEffIndex /*effectIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target || !caster->HasAura(SPELL_SOD_PRIEST_RENEWED_HOPE)
            || !target->HasAura(SPELL_SOD_PRIEST_WEAKENED_SOUL))
            return;

        uint32 healing = GetHitHeal();
        SetHitHeal(healing + CalculatePct(healing, 20));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_priest_renewed_hope::IncreaseHealing, EFFECT_ALL, SPELL_EFFECT_HEAL);
    }
};

void AddSC_sod_priest_renewed_hope()
{
    RegisterSpellScript(spell_sod_priest_renewed_hope);
}
