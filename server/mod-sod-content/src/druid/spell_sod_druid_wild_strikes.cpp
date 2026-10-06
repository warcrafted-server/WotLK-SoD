/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 */

#include "spell_sod_druid.h"

#include "Map.h"
#include "Random.h"
#include "SpellMgr.h"
#include "Timer.h"

namespace
{
bool IsFeralForm(Player const* player)
{
    ShapeshiftForm form = player->GetShapeshiftForm();
    return form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR;
}

void UpdateWildStrikesMembers(Player* druid, bool refresh)
{
    Map* map = druid->GetMap();
    if (!map)
        return;

    bool feralForm = IsFeralForm(druid);
    float radius = SodDruidWildStrikesRadiusYards();
    int32 duration = int32(SodDruidWildStrikesBuffDurationSeconds() * IN_MILLISECONDS);

    Map::PlayerList const& players = map->GetPlayers();
    for (auto itr = players.begin(); itr != players.end(); ++itr)
    {
        Player* ally = itr->GetSource();
        if (!ally)
            continue;

        bool eligible = feralForm && druid->IsInSameRaidWith(ally)
            && druid->IsWithinDistInMap(ally, radius)
            && !ally->HasAura(SPELL_DRUID_WINDFURY_TOTEM_EFFECT);
        bool hasWildStrikes = ally->HasAura(SPELL_SOD_DRUID_WILD_STRIKES_BUFF, druid->GetGUID());

        if (!eligible)
        {
            if (hasWildStrikes)
                ally->RemoveAura(SPELL_SOD_DRUID_WILD_STRIKES_BUFF, druid->GetGUID());
            continue;
        }

        if (!refresh && hasWildStrikes)
            continue;

        CustomSpellValues values;
        values.AddSpellMod(SPELLVALUE_AURA_DURATION, duration);
        druid->CastCustomSpell(SPELL_SOD_DRUID_WILD_STRIKES_BUFF, values,
            ally, TRIGGERED_FULL_MASK);
    }
}

void RemoveWildStrikesMembers(Player* druid)
{
    Map* map = druid->GetMap();
    if (!map)
        return;

    Map::PlayerList const& players = map->GetPlayers();
    for (auto itr = players.begin(); itr != players.end(); ++itr)
        if (Player* ally = itr->GetSource())
            ally->RemoveAura(SPELL_SOD_DRUID_WILD_STRIKES_BUFF, druid->GetGUID());
}
}

class spell_sod_druid_wild_strikes : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_wild_strikes);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Player* druid = GetTarget() ? GetTarget()->ToPlayer() : nullptr;
        if (!druid)
            return;

        _elapsedMs += aurEff->GetAmplitude();
        uint32 refreshMs = SodDruidWildStrikesRefreshMs();
        bool refresh = !refreshMs || _elapsedMs >= refreshMs;
        if (refresh)
            _elapsedMs = 0;

        UpdateWildStrikesMembers(druid, refresh);
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* druid = GetTarget() ? GetTarget()->ToPlayer() : nullptr)
            UpdateWildStrikesMembers(druid, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* druid = GetTarget() ? GetTarget()->ToPlayer() : nullptr)
            RemoveWildStrikesMembers(druid);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(
            spell_sod_druid_wild_strikes::HandlePeriodic,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        AfterEffectApply += AuraEffectApplyFn(
            spell_sod_druid_wild_strikes::HandleApply,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(
            spell_sod_druid_wild_strikes::HandleRemove,
            EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }

private:
    uint32 _elapsedMs = 0;
};

class spell_sod_druid_wild_strikes_proc : public AuraScript
{
    PrepareAuraScript(spell_sod_druid_wild_strikes_proc);

    bool Load() override
    {
        return SodDruidEnabled();
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* attacker = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        Unit* target = eventInfo.GetActionTarget();
        if (!attacker || !target || !eventInfo.GetDamageInfo()
            || attacker->HasAura(SPELL_DRUID_WINDFURY_TOTEM_EFFECT))
            return false;

        uint32 now = getMSTime();
        if (_hasProcced && getMSTimeDiff(_lastProcMs, now) < SodDruidWildStrikesProcCooldownMs())
            return false;

        return roll_chance_i(int32(SodDruidWildStrikesProcChance()));
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Player* attacker = eventInfo.GetActor() ? eventInfo.GetActor()->ToPlayer() : nullptr;
        Unit* target = eventInfo.GetActionTarget();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!attacker || !target || !damageInfo)
            return;

        _lastProcMs = getMSTime();
        _hasProcced = true;

        WeaponAttackType attackType = damageInfo->GetAttackType();
        uint32 extraAttackSpell = attackType == OFF_ATTACK
            ? SPELL_DRUID_WINDFURY_ATTACK_OFFHAND : SPELL_DRUID_WINDFURY_ATTACK_MAINHAND;

        // Match the core's Windfury weapon bonus conversion to weapon damage.
        float bonusAttackPower = attacker->GetTotalAttackPowerValue(attackType)
            * SodDruidWildStrikesAttackPowerPct() / 100.0f;
        int32 bonusDamage = int32(bonusAttackPower * attacker->GetAttackTime(attackType) / 1000.0f);
        attacker->CastCustomSpell(extraAttackSpell, SPELLVALUE_BASE_POINT0,
            bonusDamage, target, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_sod_druid_wild_strikes_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(
            spell_sod_druid_wild_strikes_proc::HandleProc,
            EFFECT_0, SPELL_AURA_DUMMY);
    }

private:
    uint32 _lastProcMs = 0;
    bool _hasProcced = false;
};

void AddSC_sod_druid_wild_strikes()
{
    RegisterSpellScript(spell_sod_druid_wild_strikes);
    RegisterSpellScript(spell_sod_druid_wild_strikes_proc);
}
