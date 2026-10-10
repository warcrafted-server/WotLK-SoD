/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_hunter.h"

#include "Pet.h"
#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_hunter_focus_fire : public SpellScript
{
    PrepareSpellScript(spell_sod_hunter_focus_fire);

    bool Load() override
    {
        return SodHunterEnabled();
    }

    SpellCastResult CheckPetFrenzy()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Pet* pet = player ? player->GetPet() : nullptr;
        return pet && pet->HasAura(SPELL_SOD_HUNTER_FOCUS_FIRE_PET_FRENZY)
            ? SPELL_CAST_OK : SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
    }

    void PreventPlaceholderEffects(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
    }

    void ConsumeFrenzyAndApplyBuff()
    {
        Player* player = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        Pet* pet = player ? player->GetPet() : nullptr;
        Aura* frenzy = pet ? pet->GetAura(SPELL_SOD_HUNTER_FOCUS_FIRE_PET_FRENZY) : nullptr;
        if (!player || !pet || !frenzy)
            return;

        uint8 stacks = frenzy->GetStackAmount();
        if (!stacks)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 3);
        player->CastCustomSpell(SPELL_SOD_HUNTER_FOCUS_FIRE_RANGED_HASTE,
            values, player, TRIGGERED_FULL_MASK);
        pet->ModifyPower(POWER_FOCUS, 4 * stacks);
        pet->RemoveAurasDueToSpell(SPELL_SOD_HUNTER_FOCUS_FIRE_PET_FRENZY);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_sod_hunter_focus_fire::CheckPetFrenzy);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_hunter_focus_fire::PreventPlaceholderEffects, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_hunter_focus_fire::PreventPlaceholderEffects, EFFECT_1, SPELL_EFFECT_DUMMY);
        AfterCast += SpellCastFn(spell_sod_hunter_focus_fire::ConsumeFrenzyAndApplyBuff);
    }
};

void AddSC_sod_hunter_focus_fire()
{
    RegisterSpellScript(spell_sod_hunter_focus_fire);
}
