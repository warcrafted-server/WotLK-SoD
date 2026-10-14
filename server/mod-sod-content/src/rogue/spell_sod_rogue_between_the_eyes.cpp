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

class spell_sod_rogue_between_the_eyes : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_between_the_eyes);

    SpellCastResult CheckRogueRune()
    {
        Player* rogue = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        if (!SodRogueEnabled() || !rogue || !rogue->IsClass(CLASS_ROGUE))
            return SPELL_FAILED_CASTER_AURASTATE;

        return SPELL_CAST_OK;
    }

    void ScaleDamageByComboPoints(SpellEffIndex /*effectIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        uint8 const comboPoints = caster && target ? caster->GetComboPoints(target) : 0;
        if (comboPoints)
            SetHitDamage(GetHitDamage() * comboPoints);
    }

    void SetStunDurationFromComboPoints(SpellEffIndex /*effectIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        uint8 const comboPoints = caster && target ? caster->GetComboPoints(target) : 0;
        Aura* stun = GetHitAura();
        if (!stun || !comboPoints)
            return;

        int32 const duration = int32(comboPoints) * IN_MILLISECONDS;
        stun->SetMaxDuration(duration);
        stun->SetDuration(duration);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_rogue_between_the_eyes::CheckRogueRune);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_rogue_between_the_eyes::ScaleDamageByComboPoints,
            EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_rogue_between_the_eyes::SetStunDurationFromComboPoints,
            EFFECT_2, SPELL_EFFECT_APPLY_AURA);
    }
};

void AddSC_sod_rogue_between_the_eyes()
{
    RegisterSpellScript(spell_sod_rogue_between_the_eyes);
}
