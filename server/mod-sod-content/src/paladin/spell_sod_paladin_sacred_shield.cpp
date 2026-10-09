/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include "spell_sod_paladin.h"

#include "Player.h"
#include "Spell.h"
#include "SpellInfo.h"
#include "Unit.h"

#include <algorithm>
#include <chrono>

namespace
{
bool IsFlashOfLight(SpellInfo const* spellInfo)
{
    return spellInfo && spellInfo->SpellFamilyName == SPELLFAMILY_PALADIN
        && spellInfo->SpellIconID == 242
        && (spellInfo->SpellFamilyFlags[0] & 0x40000000);
}

void EnsureSacredShieldWatcher(Player* player)
{
    if (!player)
        return;

    if (player->HasSpell(SPELL_SOD_PALADIN_SACRED_SHIELD))
    {
        if (!player->HasAura(SPELL_SOD_PALADIN_SACRED_SHIELD_WATCH))
            player->CastSpell(player, SPELL_SOD_PALADIN_SACRED_SHIELD_WATCH, true);
    }
    else
        player->RemoveAurasDueToSpell(SPELL_SOD_PALADIN_SACRED_SHIELD_WATCH);
}
}

class spell_sod_paladin_sacred_shield : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_sacred_shield);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckDamageProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        return damageInfo && damageInfo->GetDamage() > 0
            && GetTarget() && GetCaster() && GetCaster()->IsPlayer();
    }

    void HandleDamageProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        Unit* target = GetTarget();
        if (!caster || !target)
            return;

        auto const now = std::chrono::steady_clock::now();
        if (_cooldownEnd > now)
            return;

        _cooldownEnd = now + std::chrono::seconds(SodPaladinSacredShieldCooldownSeconds());
        caster->CastSpell(target, SPELL_PALADIN_SACRED_SHIELD_ABSORB,
            true, nullptr, aurEff);

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, int32(std::min<uint32>(
            SodPaladinSacredShieldFlashOfLightCritPct(), 100)) - 1);
        values.AddSpellMod(SPELLVALUE_AURA_DURATION, int32(
            SodPaladinSacredShieldFlashOfLightCritSeconds() * IN_MILLISECONDS));
        caster->CastCustomSpell(SPELL_SOD_PALADIN_SACRED_SHIELD_CRIT,
            values, caster, TRIGGERED_FULL_MASK, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_sacred_shield::CheckDamageProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_sacred_shield::HandleDamageProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }

    std::chrono::steady_clock::time_point _cooldownEnd =
        std::chrono::steady_clock::time_point::min();
};

class spell_sod_paladin_sacred_shield_watch : public AuraScript
{
    PrepareAuraScript(spell_sod_paladin_sacred_shield_watch);

    bool Load() override
    {
        return SodPaladinEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        HealInfo const* healInfo = eventInfo.GetHealInfo();
        SpellInfo const* spellInfo = healInfo ? healInfo->GetSpellInfo() : nullptr;
        Unit* target = eventInfo.GetActionTarget();
        return player && eventInfo.GetActor() == player && target && healInfo
            && healInfo->GetEffectiveHeal() > 0 && IsFlashOfLight(spellInfo)
            && target->HasAura(SPELL_SOD_PALADIN_SACRED_SHIELD, player->GetGUID());
    }

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        HealInfo const* healInfo = eventInfo.GetHealInfo();
        Unit* target = eventInfo.GetActionTarget();
        if (!healInfo || !target)
            return;

        uint32 duration = std::max<uint32>(SodPaladinSacredShieldHotDurationSeconds(), 1);
        uint32 totalHealing = CalculatePct(healInfo->GetEffectiveHeal(),
            std::min<uint32>(SodPaladinSacredShieldFlashOfLightHealPct(), 1000));
        uint32 tickHealing = totalHealing / duration;
        if (!tickHealing)
            return;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_BASE_POINT0, int32(tickHealing));
        values.AddSpellMod(SPELLVALUE_AURA_DURATION, int32(duration * IN_MILLISECONDS));
        GetTarget()->CastCustomSpell(SPELL_SOD_PALADIN_SACRED_SHIELD_HOT,
            values, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_paladin_sacred_shield_watch::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_sod_paladin_sacred_shield_watch::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class player_sod_paladin_sacred_shield : public PlayerScript
{
public:
    player_sod_paladin_sacred_shield() : PlayerScript("player_sod_paladin_sacred_shield") { }

    void OnPlayerLearnSpell(Player* player, uint32 spellId) override
    {
        if (spellId == SPELL_SOD_PALADIN_SACRED_SHIELD)
            EnsureSacredShieldWatcher(player);
    }

    void OnPlayerForgotSpell(Player* player, uint32 spellId) override
    {
        if (spellId == SPELL_SOD_PALADIN_SACRED_SHIELD)
            EnsureSacredShieldWatcher(player);
    }

    void OnPlayerLogin(Player* player) override
    {
        EnsureSacredShieldWatcher(player);
    }
};

void AddSC_sod_paladin_sacred_shield()
{
    RegisterSpellScript(spell_sod_paladin_sacred_shield);
    RegisterSpellScript(spell_sod_paladin_sacred_shield_watch);
    new player_sod_paladin_sacred_shield();
}
