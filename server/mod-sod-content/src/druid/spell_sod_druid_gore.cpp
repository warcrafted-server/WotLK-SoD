/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_druid.h"

class spell_sod_druid_gore : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_gore);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo || spellInfo->SpellFamilyName != SPELLFAMILY_DRUID)
            return false;

        return roll_chance_i(int32(SodDruidGoreProcChance()));
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* actor = eventInfo.GetActor();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        Player* player = actor ? actor->ToPlayer() : nullptr;
        if (!player || !spellInfo)
            return;

        uint32 const rageGain = SodDruidGoreRageAmount() * 10;
        if ((spellInfo->SpellFamilyFlags[1] & 0x00000040) ||
            (spellInfo->SpellFamilyFlags[1] & 0x00100100) ||
            (spellInfo->SpellFamilyFlags[0] & 0x00000800))
        {
            player->RemoveSpellCooldown(SPELL_SOD_DRUID_MANGLE, true);
            player->ModifyPower(POWER_RAGE, int32(rageGain));
            return;
        }

        if ((spellInfo->SpellFamilyFlags[1] & 0x00000400) ||
            (spellInfo->SpellFamilyFlags[0] & 0x00008000))
        {
            for (uint32 spellId : SPELL_DRUID_TIGERS_FURY_RANKS)
                player->RemoveSpellCooldown(spellId, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_gore::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_druid_gore::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_druid_gore()
{
    RegisterSpellScript(spell_sod_druid_gore);
}
