/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "ObjectAccessor.h"
#include "SpellScript.h"
#include "Unit.h"

#include <map>

namespace
{
std::map<ObjectGuid, ObjectGuid> AlphaTargets;
}

class spell_sod_shaman_spirit_of_the_alpha : public SpellScript
{
    PrepareSpellScript(spell_sod_shaman_spirit_of_the_alpha);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void LimitToOneTarget()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        auto itr = AlphaTargets.find(caster->GetGUID());
        if (itr != AlphaTargets.end() && itr->second != target->GetGUID())
        {
            if (Unit* previousTarget = ObjectAccessor::GetUnit(*caster, itr->second))
                previousTarget->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_SPIRIT_OF_THE_ALPHA, caster->GetGUID());
        }

        AlphaTargets[caster->GetGUID()] = target->GetGUID();

        // Loyal Beta solo si el espíritu va a otro objetivo.
        if (target != caster)
            caster->CastSpell(caster, SPELL_SOD_SHAMAN_LOYAL_BETA, true);
        else
            caster->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_LOYAL_BETA);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_sod_shaman_spirit_of_the_alpha::LimitToOneTarget);
    }
};

void AddSC_sod_shaman_spirit_of_the_alpha()
{
    RegisterSpellScript(spell_sod_shaman_spirit_of_the_alpha);
}
