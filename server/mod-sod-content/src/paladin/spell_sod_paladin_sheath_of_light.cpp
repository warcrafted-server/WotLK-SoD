/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "SpellMgr.h"

#include <algorithm>

class spell_sod_paladin_sheath_of_light : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_sheath_of_light);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player || eventInfo.GetActor() != player)
            return false;

        constexpr uint32 meleeFlags = PROC_FLAG_DONE_MELEE_AUTO_ATTACK
            | PROC_FLAG_DONE_SPELL_MELEE_DMG_CLASS;
        return (eventInfo.GetTypeMask() & meleeFlags) != 0;
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        if (!player)
            return;

        uint32 attackPowerPct = std::min<uint32>(SodPaladinSheathOfLightAttackPowerPct(), 1000);
        int32 spellDamage = int32(player->GetTotalAttackPowerValue(BASE_ATTACK)
            * float(attackPowerPct) / 100.0f);

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, spellDamage);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION,
            int32(SodPaladinSheathOfLightDurationSeconds() * IN_MILLISECONDS));
        player->CastCustomSpell(SPELL_SOD_PALADIN_SHEATH_OF_LIGHT_BUFF,
            values, player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_sheath_of_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_sheath_of_light::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_paladin_sheath_of_light()
{
    RegisterSpellScript(spell_sod_paladin_sheath_of_light);
}
