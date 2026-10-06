/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

#include "Player.h"
#include "Timer.h"
#include "Unit.h"

class spell_sod_druid_skull_bash : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_skull_bash);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    SpellCastResult CheckCast()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player)
            return SPELL_FAILED_DONT_REPORT;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form == FORM_CAT)
            return player->GetPower(POWER_ENERGY) >= SodDruidSkullBashEnergyCost()
                ? SPELL_CAST_OK : SPELL_FAILED_NO_POWER;

        if (form == FORM_BEAR || form == FORM_DIREBEAR)
        {
            int32 rageCost = int32(SodDruidSkullBashRageCost() * 10);
            return player->GetPower(POWER_RAGE) >= rageCost
                ? SPELL_CAST_OK : SPELL_FAILED_NO_POWER;
        }

        return SPELL_FAILED_ONLY_SHAPESHIFT;
    }

    void HandleCast()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!player)
            return;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form == FORM_CAT)
            player->ModifyPower(POWER_ENERGY, -int32(SodDruidSkullBashEnergyCost()));
        else if (form == FORM_BEAR || form == FORM_DIREBEAR)
            player->ModifyPower(POWER_RAGE, -int32(SodDruidSkullBashRageCost() * 10));
    }

    void HandleInterrupt(SpellEffIndex /*effIndex*/)
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetHitUnit();
        if (!player || !target)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidSkullBashSchoolLockoutSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_DRUID_SKULL_BASH_INTERRUPT, values,
            target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_druid_skull_bash::CheckCast);
        OnCast += SpellCastFn(spell_sod_druid_skull_bash::HandleCast);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_druid_skull_bash::HandleInterrupt, EFFECT_0, SPELL_EFFECT_CHARGE);
    }
};

void AddSC_sod_druid_skull_bash()
{
    RegisterSpellScript(spell_sod_druid_skull_bash);
}
