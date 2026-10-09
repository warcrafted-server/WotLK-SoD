/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

#include "GridNotifiersImpl.h"

#include <chrono>
#include <list>

class spell_sod_shaman_overcharged_lightning_shield : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_overcharged_lightning_shield);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    void HandleAfterProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* owner = GetTarget();
        if (!owner || !owner->HasAura(SPELL_SOD_SHAMAN_OVERCHARGED))
            return;

        Aura* lightningShield = aurEff->GetBase();
        // Restaura la carga que el proc nativo acaba de consumir sin aumentar el máximo.
        uint8 const remainingCharges = lightningShield->GetCharges();
        lightningShield->SetCharges(remainingCharges < 9 ? remainingCharges + 1 : 9);
        lightningShield->AddProcCooldown(std::chrono::steady_clock::now() + std::chrono::seconds(3));

        uint32 const damageSpell = sSpellMgr->GetSpellWithRank(
            SPELL_SHAMAN_LIGHTNING_SHIELD_DAMAGE_R1, aurEff->GetSpellInfo()->GetRank());
        if (!damageSpell)
            return;

        // El proc nativo ya golpea al atacante. Este complemento alcanza a los otros enemigos cercanos.
        std::list<Unit*> targets;
        Acore::AnyUnfriendlyUnitInObjectRangeCheck check(owner, owner, 8.0f);
        Acore::UnitListSearcher<Acore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(owner, targets, check);
        Cell::VisitObjects(owner, searcher, 8.0f);

        for (Unit* target : targets)
            if (target && target != eventInfo.GetActor())
                owner->CastSpell(target, damageSpell, true, nullptr, aurEff);
    }

    void Register() override
    {
        AfterEffectProc += AuraEffectProcFn(
            spell_sod_shaman_overcharged_lightning_shield::HandleAfterProc,
            EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

void AddSC_sod_shaman_overcharged()
{
    RegisterSpellScript(spell_sod_shaman_overcharged_lightning_shield);
}
