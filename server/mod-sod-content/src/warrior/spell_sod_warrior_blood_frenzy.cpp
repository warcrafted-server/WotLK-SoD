/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Player.h"
#include "SpellAuraEffects.h"
#include "Unit.h"

// Frenesí sangriento: cada tick de Desgarrar añade un daño extra igual al 4 % del poder de
// ataque del guerrero. Los otros dos efectos de la runa (Desgarrar en actitud rabiosa y
// +100 % de daño periódico) los resuelve el core con las auras nativas 275 y 108 del hechizo.
class spell_sod_warrior_blood_frenzy : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_blood_frenzy);

    bool Load() override
    {
        Player* caster = GetCaster() ? GetCaster()->ToPlayer() : nullptr;
        return SodWarriorEnabled() && caster && caster->HasAura(SPELL_SOD_WARRIOR_BLOOD_FRENZY);
    }

    void AddAttackPowerDamage(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        amount += int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.04f);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_warrior_blood_frenzy::AddAttackPowerDamage,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

void AddSC_sod_warrior_blood_frenzy()
{
    RegisterSpellScript(spell_sod_warrior_blood_frenzy);
}
