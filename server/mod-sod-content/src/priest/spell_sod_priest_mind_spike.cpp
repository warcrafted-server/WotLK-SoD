/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_priest.h"

#include "SpellAuras.h"
#include "Unit.h"

class spell_sod_priest_mind_spike : public AuraScript
{
    PrepareAuraScript(spell_sod_priest_mind_spike);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void SetStackedCritAmount(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Aura* aura = aurEff->GetBase();
        AuraEffect* critEffect = aura ? aura->GetEffect(EFFECT_1) : nullptr;
        if (!aura || !critEffect)
            return;

        critEffect->ChangeAmount(30 * aura->GetStackAmount(), false);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_priest_mind_spike::SetStackedCritAmount,
            EFFECT_1, SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

class spell_sod_priest_mind_spike_mind_blast : public SpellScript
{
    PrepareSpellScript(spell_sod_priest_mind_spike_mind_blast);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void ConsumeStack()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (Aura* aura = target->GetAura(SPELL_SOD_PRIEST_MIND_SPIKE, caster->GetGUID()))
            aura->ModStackAmount(-1, AURA_REMOVE_BY_ENEMY_SPELL);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_priest_mind_spike_mind_blast::ConsumeStack);
    }
};

void AddSC_sod_priest_mind_spike()
{
    RegisterSpellScript(spell_sod_priest_mind_spike);
    RegisterSpellScript(spell_sod_priest_mind_spike_mind_blast);
}
