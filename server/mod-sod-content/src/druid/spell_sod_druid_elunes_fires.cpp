/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

namespace
{
uint32 GetExtensionSpell(uint32 spellId, uint32& seconds)
{
    switch (spellId)
    {
        case 48464: case 48465: // Starfire
            seconds = SodDruidElunesFiresMoonfireSeconds();
            return 8921;
        case SPELL_DRUID_WRATH:
            seconds = SodDruidElunesFiresSunfireSeconds();
            return 414684;
        case SPELL_DRUID_REGROWTH:
            seconds = SodDruidElunesFiresRejuvenationSeconds();
            return 774;
        case SPELL_DRUID_SHRED:
            seconds = SodDruidElunesFiresRipSeconds();
            return 49800;
        default:
            seconds = 0;
            return 0;
    }
}
}

class spell_sod_druid_elunes_fires : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_elunes_fires);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetActionTarget() || !eventInfo.GetSpellInfo())
            return false;

        uint32 seconds = 0;
        return GetExtensionSpell(eventInfo.GetSpellInfo()->Id, seconds) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* actor = eventInfo.GetActor();
        Unit* target = eventInfo.GetActionTarget();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!actor || !target || !spellInfo)
            return;

        uint32 seconds = 0;
        uint32 const dotSpell = GetExtensionSpell(spellInfo->Id, seconds);
        Aura* dot = target->GetAuraOfRankedSpell(dotSpell, actor->GetGUID());
        if (!dot || !seconds)
            return;

        int32 const extended = dot->GetDuration() + int32(seconds * IN_MILLISECONDS);
        dot->SetDuration(std::min(extended, dot->GetMaxDuration()));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_elunes_fires::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_druid_elunes_fires::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_druid_elunes_fires()
{
    RegisterSpellScript(spell_sod_druid_elunes_fires);
}
