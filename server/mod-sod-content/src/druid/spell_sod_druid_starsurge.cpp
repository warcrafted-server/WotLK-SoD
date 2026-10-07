/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

class spell_sod_druid_starsurge : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_starsurge);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandleAfterCast()
    {
        if (Unit* caster = GetCaster())
            caster->AddSpellCooldown(SPELL_DRUID_STARSURGE, 0,
                SodDruidStarsurgeCooldownSeconds() * IN_MILLISECONDS);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_sod_druid_starsurge::HandleAfterCast);
    }
};

void AddSC_sod_druid_starsurge()
{
    RegisterSpellScript(spell_sod_druid_starsurge);
}
