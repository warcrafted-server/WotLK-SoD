/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_paladin.h"

#include <algorithm>

class spell_sod_paladin_beacon_of_light : public SpellScript
{
    PrepareSpellScript(spell_sod_paladin_beacon_of_light);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        uint32 healingPct = std::min<uint32>(SodPaladinBeaconOfLightHealingPct(), 100);
        uint32 durationSeconds = SodPaladinBeaconOfLightDurationSeconds();
        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, int32(healingPct) - 1);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(durationSeconds * IN_MILLISECONDS));
        caster->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_AURA,
            values, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_paladin_beacon_of_light::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_sod_paladin_beacon_of_light()
{
    RegisterSpellScript(spell_sod_paladin_beacon_of_light);
}
