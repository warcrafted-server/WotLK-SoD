/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_priest.h"

#include "CellImpl.h"
#include "GridNotifiers.h"
#include "Unit.h"

class spell_sod_priest_shared_pain : public SpellScript
{
    PrepareSpellScript(spell_sod_priest_shared_pain);

    bool Load() override
    {
        return SodPriestEnabled();
    }

    void SpreadPain()
    {
        Unit* caster = GetCaster();
        Unit* primaryTarget = GetHitUnit();
        if (!caster || !primaryTarget || !primaryTarget->IsAlive()
            || !caster->HasAura(SPELL_SOD_PRIEST_SHARED_PAIN))
            return;

        std::list<Unit*> targets;
        Acore::AnyUnfriendlyUnitInObjectRangeCheck check(primaryTarget, caster, 15.0f);
        Acore::UnitListSearcher<Acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(primaryTarget, targets, check);
        Cell::VisitObjects(primaryTarget, searcher, 15.0f);

        uint8 additionalTargets = 0;
        for (Unit* target : targets)
        {
            if (!target || target == primaryTarget)
                continue;

            caster->AddAura(GetSpellInfo()->Id, target);
            if (++additionalTargets == 2)
                break;
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_sod_priest_shared_pain::SpreadPain);
    }
};

void AddSC_sod_priest_shared_pain()
{
    RegisterSpellScript(spell_sod_priest_shared_pain);
}
