/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_warrior.h"

#include "Item.h"
#include "ItemTemplate.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Unit.h"

namespace
{
bool WieldingTwoHandedWeapon(Player* player)
{
    Item* weapon = player ? player->GetWeaponForAttack(BASE_ATTACK, true) : nullptr;
    return weapon && weapon->GetTemplate()->InventoryType == INVTYPE_2HWEAPON;
}
}

// Asalto frenético: mientras el guerrero empuñe un arma a dos manos mantiene la celeridad
// auxiliar 900052 (aura 138), que el sondeo periódico concede o retira. El proc del aura dummy
// añade 2 de ira por golpe cuerpo a cuerpo con éxito, o 4 si el golpe es crítico.
class spell_sod_warrior_frenzied_assault : public AuraScript
{
    PrepareAuraScript(spell_sod_warrior_frenzied_assault);

    bool Load() override
    {
        return SodWarriorEnabled();
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        if (WieldingTwoHandedWeapon(player))
            player->CastSpell(player, SPELL_SOD_WARRIOR_FRENZIED_ASSAULT_HASTE, true);
        else
            player->RemoveAurasDueToSpell(SPELL_SOD_WARRIOR_FRENZIED_ASSAULT_HASTE);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        return player && WieldingTwoHandedWeapon(player) && damageInfo && damageInfo->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!player)
            return;

        int32 rage = aurEff->GetAmount();
        if (eventInfo.GetHitMask() & PROC_HIT_CRITICAL)
            rage *= 2;

        if (rage > 0)
            player->ModifyPower(POWER_RAGE, rage * 10);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_warrior_frenzied_assault::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        DoCheckProc += AuraCheckProcFn(spell_sod_warrior_frenzied_assault::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_warrior_frenzied_assault::HandleProc,
            EFFECT_1, SPELL_AURA_DUMMY);
    }
};

void AddSC_sod_warrior_frenzied_assault()
{
    RegisterSpellScript(spell_sod_warrior_frenzied_assault);
}
