/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Creature.h"
#include "ObjectAccessor.h"
#include "SpellScript.h"
#include "Unit.h"

#include <map>

namespace
{
constexpr uint32 DECOY_TOTEM_CREATURE = 3968; // Sentry Totem, una criatura-tótem existente en WotLK.
constexpr uint32 DECOY_TOTEM_HEALTH = 4;
constexpr uint32 DECOY_TOTEM_DURATION_MS = 10000;
std::map<ObjectGuid, ObjectGuid> DecoyTotems;
}

class spell_sod_shaman_decoy_totem : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_decoy_totem);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void SummonDecoy()
    {
        Unit* target = GetHitUnit();
        if (!target)
            return;

        Creature* totem = target->SummonCreature(DECOY_TOTEM_CREATURE, target->GetPosition(),
            TEMPSUMMON_TIMED_DESPAWN, DECOY_TOTEM_DURATION_MS);
        if (!totem)
            return;

        totem->SetFaction(target->GetFaction());
        totem->SetMaxHealth(DECOY_TOTEM_HEALTH);
        totem->SetHealth(DECOY_TOTEM_HEALTH);
        totem->SetReactState(REACT_PASSIVE);
        DecoyTotems[target->GetGUID()] = totem->GetGUID();
        target->CastSpell(target, SPELL_SOD_SHAMAN_DECOY_TOTEM_PROTECTION, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_shaman_decoy_totem::SummonDecoy);
    }
};

class spell_sod_shaman_decoy_totem_protection : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_decoy_totem_protection);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void CalculateAbsorb(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = -1;
    }

    void RedirectPhysicalAttack(AuraEffect* /*aurEff*/, DamageInfo& damageInfo, uint32& absorbAmount)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto itr = DecoyTotems.find(target->GetGUID());
        if (itr == DecoyTotems.end() || damageInfo.GetSchoolMask() != SPELL_SCHOOL_MASK_NORMAL)
        {
            absorbAmount = 0;
            return;
        }

        absorbAmount = damageInfo.GetDamage();
        if (Creature* totem = ObjectAccessor::GetCreature(*target, itr->second))
        {
            totem->SetHealth(0);
            totem->DespawnOrUnsummon();
        }
        DecoyTotems.erase(itr);
        target->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_DECOY_TOTEM_PROTECTION);
    }

    void ForgetTotem(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (!target)
            return;

        auto itr = DecoyTotems.find(target->GetGUID());
        if (itr == DecoyTotems.end())
            return;

        if (Creature* totem = ObjectAccessor::GetCreature(*target, itr->second))
            totem->DespawnOrUnsummon();
        DecoyTotems.erase(itr);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(
            spell_sod_shaman_decoy_totem_protection::CalculateAbsorb,
            EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(
            spell_sod_shaman_decoy_totem_protection::RedirectPhysicalAttack,
            EFFECT_0);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_shaman_decoy_totem_protection::ForgetTotem,
            EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_sod_shaman_decoy_totem()
{
    RegisterSpellScript(spell_sod_shaman_decoy_totem);
    RegisterSpellScript(spell_sod_shaman_decoy_totem_protection);
}
