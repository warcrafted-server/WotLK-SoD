/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_slaughter_from_the_shadows : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_slaughter_from_the_shadows);

    void GateCostReduction(AuraEffect const* /*aurEff*/, int32& amount,
        bool& /*canBeRecalculated*/)
    {
        if (!SodRogueEnabled())
            amount = 0;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_rogue_slaughter_from_the_shadows::GateCostReduction,
            EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER);
    }
};

class spell_sod_rogue_slaughter_targets : public SpellScript
{
    PrepareSpellScript(spell_sod_rogue_slaughter_targets);

    void IncreaseDamageAgainstNpc(SpellEffIndex /*effectIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!SodRogueEnabled() || !caster || !caster->IsPlayer()
            || !caster->HasAura(SPELL_SOD_ROGUE_SLAUGHTER_FROM_THE_SHADOWS)
            || !target || target->IsControlledByPlayer())
            return;

        SetHitDamage(GetHitDamage() + GetHitDamage() * 70 / 100);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_rogue_slaughter_targets::IncreaseDamageAgainstNpc,
            EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
    }
};

void AddSC_sod_rogue_slaughter_from_the_shadows()
{
    RegisterSpellScript(spell_sod_rogue_slaughter_from_the_shadows);
    RegisterSpellScript(spell_sod_rogue_slaughter_targets);
}
