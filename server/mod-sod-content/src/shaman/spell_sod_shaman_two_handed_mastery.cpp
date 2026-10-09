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
#include "ItemTemplate.h"
#include "Player.h"
#include "SpellScript.h"
#include "Unit.h"

class spell_sod_shaman_two_handed_mastery : public AuraScript
{
    PrepareAuraScript(spell_sod_shaman_two_handed_mastery);

    bool Load() override
    {
        return SodShamanEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        return player && eventInfo.GetActor() == player && damageInfo
            && damageInfo->GetDamage() > 0 && eventInfo.GetActionTarget();
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!player || !damageInfo)
            return;

        Item* weapon = player->GetWeaponForAttack(damageInfo->GetAttackType(), true);
        if (weapon && damageInfo->GetAttackType() == BASE_ATTACK
            && weapon->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
            player->CastSpell(player, SPELL_SOD_SHAMAN_TWO_HANDED_MASTERY_BUFF, true);
        else
            player->RemoveAurasDueToSpell(SPELL_SOD_SHAMAN_TWO_HANDED_MASTERY_BUFF);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_shaman_two_handed_mastery::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_shaman_two_handed_mastery::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_shaman_two_handed_mastery()
{
    RegisterSpellScript(spell_sod_shaman_two_handed_mastery);
}
