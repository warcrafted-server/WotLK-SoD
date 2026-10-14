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

namespace
{
void RefreshShortestDamageOverTime(Unit* caster, Unit* target)
{
    if (!SodPriestEnabled() || !caster || !target || !caster->HasAura(SPELL_SOD_PRIEST_PAIN_AND_SUFFERING))
        return;

    Aura* shadowWordPain = target->GetAuraOfRankedSpell(589, caster->GetGUID());
    Aura* voidPlague = target->GetAura(SPELL_SOD_PRIEST_VOID_PLAGUE, caster->GetGUID());
    Aura* vampiricTouch = target->GetAuraOfRankedSpell(34914, caster->GetGUID());

    Aura* shortest = nullptr;
    for (Aura* aura : { shadowWordPain, voidPlague, vampiricTouch })
        if (aura && (!shortest || aura->GetDuration() < shortest->GetDuration()))
            shortest = aura;

    if (shortest)
        shortest->RefreshDuration();
}
}

class spell_sod_priest_pain_and_suffering : public SpellScript
{
    PrepareSpellScript(spell_sod_priest_pain_and_suffering);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void RefreshOnHit()
    {
        RefreshShortestDamageOverTime(GetCaster(), GetHitUnit());
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_priest_pain_and_suffering::RefreshOnHit);
    }
};

class spell_sod_priest_pain_and_suffering_mind_flay : public AuraScript
{
    PrepareAuraScript(spell_sod_priest_pain_and_suffering_mind_flay);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void RefreshOnTick(AuraEffect const* /*aurEff*/)
    {
        RefreshShortestDamageOverTime(GetCaster(), GetTarget());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_priest_pain_and_suffering_mind_flay::RefreshOnTick,
            EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

void AddSC_sod_priest_pain_and_suffering()
{
    RegisterSpellScript(spell_sod_priest_pain_and_suffering);
    RegisterSpellScript(spell_sod_priest_pain_and_suffering_mind_flay);
}
