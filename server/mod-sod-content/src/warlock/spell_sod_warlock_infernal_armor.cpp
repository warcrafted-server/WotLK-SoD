/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warlock.h"

#include "Unit.h"

#include <algorithm>

// Armadura infernal: reduce el daño mágico recibido un porcentaje igual al 60 % de la
// reducción de daño físico por armadura del brujo (aura 87, escuelas mágicas 126). El
// importe se calcula con la propia fórmula de armadura del core, usando el nivel del
// objetivo como referencia; el 60 va en el efecto dummy que alimenta el texto de la runa.
class spell_sod_warlock_infernal_armor : public AuraScript
{
    PrepareAuraScript(spell_sod_warlock_infernal_armor);

    bool Load() override
    {
        return SodWarlockEnabled();
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        float levelModifier = float(target->GetLevel());
        if (levelModifier > 59.0f)
            levelModifier += 4.5f * (levelModifier - 59.0f);

        float armor = std::max(0.0f, float(target->GetArmor()));
        float damageReduction = 0.1f * armor / (8.5f * levelModifier + 40.0f);
        damageReduction = damageReduction / (1.0f + damageReduction);
        damageReduction = std::min(damageReduction, 0.75f);

        amount = -int32(damageReduction * 100.0f * 0.6f);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_warlock_infernal_armor::CalculateAmount,
            EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
    }
};

void AddSC_sod_warlock_infernal_armor()
{
    RegisterSpellScript(spell_sod_warlock_infernal_armor);
}
