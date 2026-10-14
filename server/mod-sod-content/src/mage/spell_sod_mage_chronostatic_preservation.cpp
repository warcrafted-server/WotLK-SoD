/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_mage.h"

// La primera activación guarda la carga durante 20 s; la siguiente la libera
// sobre el aliado elegido. Flash Heal es el sustituto disponible en WotLK.
class spell_sod_mage_chronostatic_preservation : public SpellScript
{
    PrepareSpellScript(spell_sod_mage_chronostatic_preservation);

    bool Load() override
    {
        return SodMageEnabled();
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SOD_MAGE_CHRONOSTATIC_STORAGE,
            SPELL_MAGE_CHRONOSTATIC_FLASH_HEAL });
    }

    void HandleHeal(SpellEffIndex /*effIndex*/)
    {
        PreventHitDefaultEffect(EFFECT_0);

        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (!caster->HasAura(SPELL_SOD_MAGE_CHRONOSTATIC_STORAGE))
        {
            caster->CastSpell(caster, SPELL_SOD_MAGE_CHRONOSTATIC_STORAGE, true);
            return;
        }

        caster->RemoveAurasDueToSpell(SPELL_SOD_MAGE_CHRONOSTATIC_STORAGE);

        // La liberación no debe volver a cobrar el 24 % de maná del hechizo.
        int32 manaRefund = int32(CalculatePct(caster->GetCreateMana(), 24));
        if (manaRefund > 0)
            caster->ModifyPower(POWER_MANA, manaRefund);

        caster->CastSpell(target, SPELL_MAGE_CHRONOSTATIC_FLASH_HEAL, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_mage_chronostatic_preservation::HandleHeal,
            EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_sod_mage_chronostatic_preservation()
{
    RegisterSpellScript(spell_sod_mage_chronostatic_preservation);
}
