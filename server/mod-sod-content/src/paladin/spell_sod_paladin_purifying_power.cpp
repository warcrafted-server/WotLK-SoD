/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_purifying_power : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_purifying_power);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleCooldownModifierApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        AuraEffect* effect = GetEffect(EFFECT_0);
        if (!effect)
            return;

        uint32 reductionPct = std::min<uint32>(SodPaladinPurifyingPowerCooldownReductionPct(), 100);
        effect->ChangeAmount(-static_cast<int32>(reductionPct));
    }

    void HandleHolyWrathApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        uint32 spellId = player->HasSpell(10318)
            ? SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R2
            : SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R1;
        player->learnSpell(spellId, true);
    }

    void HandleHolyWrathRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetTarget()->ToPlayer();
        if (!player)
            return;

        player->removeSpell(SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R1, SPEC_MASK_ALL, true);
        player->removeSpell(SPELL_SOD_PALADIN_PURIFYING_POWER_HOLY_WRATH_R2, SPEC_MASK_ALL, true);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_purifying_power::HandleCooldownModifierApply,
            EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_purifying_power::HandleHolyWrathApply,
            EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_paladin_purifying_power::HandleHolyWrathRemove,
            EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_sod_paladin_purifying_power_holy_wrath : public SpellScript
{
    PrepareSpellScript(spell_sod_paladin_purifying_power_holy_wrath);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SOD_PALADIN_PURIFYING_POWER_STUN });
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target || !caster->HasAura(SPELL_SOD_PALADIN_PURIFYING_POWER))
            return;

        if (target->GetCreatureTypeMask() & CREATURE_TYPEMASK_DEMON_OR_UNDEAD)
            caster->CastSpell(target, SPELL_SOD_PALADIN_PURIFYING_POWER_STUN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(
            spell_sod_paladin_purifying_power_holy_wrath::HandleDamage,
            EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_sod_paladin_purifying_power_stun : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_purifying_power_stun);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Aura* aura = GetAura();
        if (!aura)
            return;

        int32 durationMs = static_cast<int32>(SodPaladinPurifyingPowerStunSeconds() * IN_MILLISECONDS);
        aura->SetMaxDuration(durationMs);
        aura->SetDuration(durationMs);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_paladin_purifying_power_stun::HandleApply,
            EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_paladin_purifying_power()
{
    RegisterSpellScript(spell_sod_paladin_purifying_power);
    RegisterSpellScript(spell_sod_paladin_purifying_power_holy_wrath);
    RegisterSpellScript(spell_sod_paladin_purifying_power_stun);
}
