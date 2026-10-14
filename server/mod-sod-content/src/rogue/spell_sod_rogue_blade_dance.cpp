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

class spell_sod_rogue_blade_dance : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_blade_dance);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SOD_ROGUE_BLADE_DANCE_ATTACK_POWER });
    }

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void ApplyComboScaling()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Unit* target = GetExplTargetUnit();
        if (!rogue || !target)
            return;

        uint8 const comboPoints = rogue->GetComboPoints(target);
        if (!comboPoints)
            return;

        int32 const duration = (10 + 4 * comboPoints) * IN_MILLISECONDS;
        if (Aura* dance = rogue->GetAura(SPELL_SOD_ROGUE_BLADE_DANCE, rogue->GetGUID()))
        {
            dance->SetMaxDuration(duration);
            dance->SetDuration(duration);
        }

        int32 const defense = int32(rogue->GetSkillValue(SKILL_DEFENSE));
        int32 const baseline = int32(rogue->GetLevel()) * 5;
        int32 const attackPower = std::max(0, defense - baseline) * 4;
        rogue->CastCustomSpell(SPELL_SOD_ROGUE_BLADE_DANCE_ATTACK_POWER,
            SPELLVALUE_BASE_POINT0, attackPower, rogue, true);

        if (Aura* bonus = rogue->GetAura(SPELL_SOD_ROGUE_BLADE_DANCE_ATTACK_POWER, rogue->GetGUID()))
        {
            bonus->SetMaxDuration(duration);
            bonus->SetDuration(duration);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_blade_dance::CheckRogueRune);
        AfterHit += SpellHitFn(spell_sod_rogue_blade_dance::ApplyComboScaling);
    }
};

void AddSC_sod_rogue_blade_dance()
{
    RegisterSpellScript(spell_sod_rogue_blade_dance);
}
