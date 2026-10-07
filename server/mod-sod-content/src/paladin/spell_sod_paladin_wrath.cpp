/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include <cmath>

class spell_sod_paladin_wrath : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_wrath);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        if (!spellMod)
            spellMod = new SpellModifier(aurEff->GetBase());

        spellMod->op = SPELLMOD_CRITICAL_CHANCE;
        spellMod->type = SPELLMOD_FLAT;
        spellMod->spellId = GetId();
        spellMod->mask[0] = SOD_PALADIN_WRATH_SPELL_MASK_0;
        spellMod->mask[1] = SOD_PALADIN_WRATH_SPELL_MASK_1;
        spellMod->mask[2] = 0;
        spellMod->value = static_cast<int32>(std::lround(
            player->GetUnitCriticalChance(BASE_ATTACK, nullptr)));
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(
            spell_sod_paladin_wrath::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_wrath()
{
    RegisterSpellScript(spell_sod_paladin_wrath);
}
