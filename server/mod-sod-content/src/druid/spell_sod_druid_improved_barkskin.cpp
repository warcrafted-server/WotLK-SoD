/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "Player.h"
#include "Unit.h"

class spell_sod_druid_improved_barkskin : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_improved_barkskin);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void SelectTarget(WorldObject*& target)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player || !player->HasAura(SPELL_SOD_DRUID_IMPROVED_BARKSKIN))
            return;

        Unit* selected = player->GetSelectedUnit();
        if (selected && selected != player && selected->IsAlive()
            && selected->IsInMap(player) && selected->IsFriendlyTo(player))
            target = selected;
    }

    void Register() override
    {
        // Barkskin targets the caster in DBC, so redirect all its aura effects together.
        OnObjectTargetSelect += SpellObjectTargetSelectFn(
            spell_sod_druid_improved_barkskin::SelectTarget, EFFECT_0, TARGET_UNIT_CASTER);
        OnObjectTargetSelect += SpellObjectTargetSelectFn(
            spell_sod_druid_improved_barkskin::SelectTarget, EFFECT_1, TARGET_UNIT_CASTER);
        OnObjectTargetSelect += SpellObjectTargetSelectFn(
            spell_sod_druid_improved_barkskin::SelectTarget, EFFECT_2, TARGET_UNIT_CASTER);
    }
};

void AddSC_sod_druid_improved_barkskin()
{
    RegisterSpellScript(spell_sod_druid_improved_barkskin);
}
