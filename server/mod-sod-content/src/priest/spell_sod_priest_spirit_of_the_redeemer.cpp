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

class spell_sod_priest_spirit_of_the_redeemer : public SpellScript
{
    PrepareSpellScript(spell_sod_priest_spirit_of_the_redeemer);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    SpellCastResult CheckTalent()
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->HasAura(SPELL_SOD_PRIEST_SPIRIT_OF_REDEMPTION_TALENT))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(
            spell_sod_priest_spirit_of_the_redeemer::CheckTalent);
    }
};

void AddSC_sod_priest_spirit_of_the_redeemer()
{
    RegisterSpellScript(spell_sod_priest_spirit_of_the_redeemer);
}
