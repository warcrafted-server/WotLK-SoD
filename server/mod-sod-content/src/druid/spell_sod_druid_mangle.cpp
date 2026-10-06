/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

class spell_sod_druid_mangle : public SpellScript
{
    PrepareSpellScript(spell_sod_druid_mangle);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    SpellCastResult CheckCast()
    {
        Player* player = GetCaster()->ToPlayer();
        if (!player)
            return SPELL_FAILED_DONT_REPORT;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form == FORM_CAT)
            return player->GetPower(POWER_ENERGY) >= int32(SodDruidMangleCatEnergyCost())
                ? SPELL_CAST_OK : SPELL_FAILED_NO_POWER;

        if (form == FORM_BEAR || form == FORM_DIREBEAR)
        {
            int32 rageCost = int32(SodDruidMangleBearRageCost() * 10);
            return player->GetPower(POWER_RAGE) >= rageCost
                ? SPELL_CAST_OK : SPELL_FAILED_NO_POWER;
        }

        return SPELL_FAILED_ONLY_SHAPESHIFT;
    }

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();
        if (!player)
            return;

        ShapeshiftForm form = player->GetShapeshiftForm();
        if (form == FORM_CAT)
            player->ModifyPower(POWER_ENERGY, -int32(SodDruidMangleCatEnergyCost()));
        else if (form == FORM_BEAR || form == FORM_DIREBEAR)
            player->ModifyPower(POWER_RAGE, -int32(SodDruidMangleBearRageCost() * 10));
    }

    void HandleMangle(SpellEffIndex /*effIndex*/)
    {
        Player* player = GetCaster()->ToPlayer();
        Unit* target = GetHitUnit();
        if (!player || !target)
            return;

        ShapeshiftForm form = player->GetShapeshiftForm();
        uint32 mangleSpell;
        if (form == FORM_CAT)
            mangleSpell = SPELL_DRUID_MANGLE_CAT;
        else if (form == FORM_BEAR || form == FORM_DIREBEAR)
            mangleSpell = SPELL_DRUID_MANGLE_BEAR;
        else
            return;

        // Keep WotLK's form-specific proc behavior while replacing its rank damage with SoD values.
        CustomSpellValues mangleValues;
        mangleValues.AddSpellMod(SPELLVALUE_BASE_POINT0, 0);
        mangleValues.AddSpellMod(SPELLVALUE_BASE_POINT1,
            int32(SodDruidMangleBleedDamagePct()));
        mangleValues.AddSpellMod(SPELLVALUE_BASE_POINT2,
            int32(SodDruidMangleDamagePct()));
        mangleValues.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidMangleBuffDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(mangleSpell, mangleValues, target, TRIGGERED_FULL_MASK);

        if (form == FORM_CAT)
            return;

        uint32 defense = player->GetDefenseSkillValue();
        uint32 threshold = uint32(player->GetLevel()) * SodDruidMangleDefenseSkillPerLevel();
        player->RemoveAurasDueToSpell(SPELL_SOD_DRUID_DEFENDERS_RESOLVE);
        if (defense <= threshold)
            return;

        int32 attackPower = int32(defense - threshold)
            * int32(SodDruidMangleAttackPowerPerDefense());
        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, attackPower);
        values.AddSpellMod(SPELLVALUE_BASE_POINT1, attackPower);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodDruidMangleBuffDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_DRUID_DEFENDERS_RESOLVE, values,
            player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_druid_mangle::CheckCast);
        OnCast += SpellCastFn(spell_sod_druid_mangle::HandleCast);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_druid_mangle::HandleMangle, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_sod_druid_mangle()
{
    RegisterSpellScript(spell_sod_druid_mangle);
}
