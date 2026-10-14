/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_rogue.h"

#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_rogue_deadly_brew : public AuraScript
{
    PrepareAuraScript(spell_sod_rogue_deadly_brew);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_ROGUE_DEADLY_POISON });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return SodRogueEnabled() && eventInfo.GetActionTarget();
    }

    void ApplyDeadlyPoison(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (!SodRogueEnabled())
            return;

        Unit* caster = GetTarget();
        Unit* target = eventInfo.GetActionTarget();
        if (!caster || !target)
            return;

        // El guion nativo de WotLK usa 3409 (Veneno entorpecedor); SoD pide aplicar Veneno mortal.
        uint32 poisonSpellId = sSpellMgr->GetFirstSpellInChain(SPELL_ROGUE_DEADLY_POISON);
        for (uint32 nextSpellId = poisonSpellId; nextSpellId;
            nextSpellId = sSpellMgr->GetNextSpellInChain(nextSpellId))
        {
            SpellInfo const* poisonSpell = sSpellMgr->GetSpellInfo(nextSpellId);
            if (!poisonSpell || poisonSpell->SpellLevel > caster->GetLevel())
                break;

            poisonSpellId = nextSpellId;
        }

        caster->CastSpell(target, poisonSpellId, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_rogue_deadly_brew::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_rogue_deadly_brew::ApplyDeadlyPoison, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_rogue_deadly_brew()
{
    RegisterSpellScript(spell_sod_rogue_deadly_brew);
}
