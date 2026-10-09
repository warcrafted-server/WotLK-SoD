/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Player.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_shaman_mental_dexterity : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_mental_dexterity);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        return player && eventInfo.GetActor() == player && spellInfo && damageInfo
            && damageInfo->GetDamage() > 0 && spellInfo->SpellFamilyName == 11
            && (spellInfo->SpellFamilyFlags[1] & 0x01000010);
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32 const attackPower = int32(player->GetStat(STAT_INTELLECT) * 1.5f);
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_MENTAL_DEXTERITY_ATTACK_POWER);
        player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_MENTAL_DEXTERITY_SPELL_DAMAGE);
        int32 const spellDamage = int32(
            (player->GetTotalAttackPowerValue(BASE_ATTACK) + attackPower) * 0.35f);

        CustomSpellValues attackPowerValues;
        attackPowerValues.AddSpellMod(SPELLVALUE_BASE_POINT0, attackPower);
        player->CastCustomSpell(SPELL_SOD_SHAMAN_MENTAL_DEXTERITY_ATTACK_POWER,
            attackPowerValues, player, TRIGGERED_FULL_MASK);

        CustomSpellValues spellDamageValues;
        spellDamageValues.AddSpellMod(SPELLVALUE_BASE_POINT0, spellDamage);
        player->CastCustomSpell(SPELL_SOD_SHAMAN_MENTAL_DEXTERITY_SPELL_DAMAGE,
            spellDamageValues, player, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_mental_dexterity::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_mental_dexterity::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_shaman_mental_dexterity()
{
    RegisterSpellScript(spell_sod_shaman_mental_dexterity);
}
