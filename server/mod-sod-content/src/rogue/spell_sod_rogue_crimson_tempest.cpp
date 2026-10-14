/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "Player.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_crimson_tempest : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_crimson_tempest);

    uint8 _comboPoints = 0;

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void CaptureComboPoints()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (caster)
            _comboPoints = target ? caster->GetComboPoints(target) : caster->GetComboPoints();
        if (_comboPoints > 5)
            _comboPoints = 5;
    }

    void SetBleedDuration(SpellEffIndex /*effectIndex*/)
    {
        Aura* bleed = GetHitAura();
        if (!bleed || !_comboPoints)
            return;

        int32 const duration = (int32(_comboPoints) + 1) * 2 * IN_MILLISECONDS;
        bleed->SetMaxDuration(duration);
        bleed->SetDuration(duration);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_crimson_tempest::CheckRogueRune);
        BeforeCast += SpellCastFn(spell_sod_rogue_crimson_tempest::CaptureComboPoints);
        OnEffectHitTarget += SpellEffectFn(spell_sod_rogue_crimson_tempest::SetBleedDuration,
            EFFECT_1, SPELL_EFFECT_APPLY_AURA);
    }
};

void AddSC_sod_rogue_crimson_tempest()
{
    RegisterSpellScript(spell_sod_rogue_crimson_tempest);
}
