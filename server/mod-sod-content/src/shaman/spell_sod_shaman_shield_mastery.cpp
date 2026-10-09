/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_shaman.h"

#include "Item.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool IsShockSpell(SpellInfo const* spellInfo)
{
    if (!spellInfo || spellInfo->SpellFamilyName != 11)
        return false;

    return (spellInfo->SpellFamilyFlags[0] & 0x10100000) != 0;
}
}

class spell_sod_shaman_shield_mastery : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_shield_mastery);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return false;

        if (eventInfo.GetActionTarget() == player && (eventInfo.GetHitMask() & PROC_HIT_BLOCK))
            return true;

        return eventInfo.GetActor() == player && IsShockSpell(eventInfo.GetSpellInfo());
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (eventInfo.GetActionTarget() == player && (eventInfo.GetHitMask() & PROC_HIT_BLOCK))
        {
            Item* shield = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (!shield || shield->GetTemplate()->InventoryType != INVTYPE_SHIELD)
                return;

            int32 manaRestore = player->GetMaxPower(POWER_MANA) * 8 / 100;
            if (manaRestore > 0)
                player->ModifyPower(POWER_MANA, manaRestore);

            int32 armor = int32(shield->GetTemplate()->Armor * 30 / 100);
            if (armor > 0)
                player->CastCustomSpell(SPELL_SOD_SHAMAN_SHIELD_MASTERY_ARMOR,
                    SPELLVALUE_BASE_POINT0, armor, player, true, nullptr, aurEff);
        }

        if (eventInfo.GetActor() != player || !IsShockSpell(eventInfo.GetSpellInfo()))
            return;

        uint32 defense = player->GetSkillValue(SKILL_DEFENSE);
        uint32 defenseCap = player->GetMaxSkillValueForLevel();
        if (defense <= defenseCap)
            return;

        int32 spellDamage = int32((defense - defenseCap) * 4);
        player->CastCustomSpell(SPELL_SOD_SHAMAN_SHIELD_MASTERY_SPELL_DAMAGE,
            SPELLVALUE_BASE_POINT0, spellDamage, player, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_shield_mastery::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_shield_mastery::HandleProc,
            EFFECT_2, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_shaman_shield_mastery()
{
    RegisterSpellScript(spell_sod_shaman_shield_mastery);
}
