/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "Group.h"
#include "Player.h"
#include "Unit.h"

#include <algorithm>

class spell_sod_paladin_inspiration_exemplar : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_inspiration_exemplar);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    void SetInterval(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = int32(std::max<uint32>(SodPaladinInspirationExemplarIntervalSeconds(), 1)
            * IN_MILLISECONDS);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* paladin = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!paladin)
            return;

        float radius = std::max(SodPaladinInspirationExemplarRadiusYards(), 0.0f);
        uint64 const fearAndSleepMask = (1ULL << MECHANIC_FEAR) | (1ULL << MECHANIC_SLEEP);
        auto dispelNearby = [paladin, radius, fearAndSleepMask](Player* member)
        {
            if (member && member->IsInWorld() && paladin->IsWithinDistInMap(member, radius))
                member->RemoveAurasWithMechanic(fearAndSleepMask);
        };

        if (Group* group = paladin->GetGroup())
        {
            for (GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
                dispelNearby(itr->GetSource());
        }
        else
            dispelNearby(paladin);
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(
            spell_sod_paladin_inspiration_exemplar::SetInterval,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_paladin_inspiration_exemplar::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

void AddSC_sod_paladin_inspiration_exemplar()
{
    RegisterSpellScript(spell_sod_paladin_inspiration_exemplar);
}
