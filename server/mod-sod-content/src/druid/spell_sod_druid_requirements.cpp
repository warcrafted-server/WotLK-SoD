/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include "spell_sod_druid.h"

#include "../../../mod-rune-engraving/src/RuneRequirementMgr.h"
#include "SpellInfo.h"
#include "SpellAuras.h"
#include "Unit.h"

#include <algorithm>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace
{
constexpr uint32 ITEM_MANGLE = 206954;
constexpr uint32 SPELL_BARKSKIN = 22812;

struct PendingHit
{
    ObjectGuid Victim;
    ObjectGuid Player;
    bool BleedHumanoid = false;
    bool BarkskinNature = false;
    bool CatSleeping = false;
};

struct PendingKill
{
    ObjectGuid Player;
    bool BarkskinNature = false;
    bool CatSleeping = false;
};

struct RageStreak
{
    uint32 ElapsedMs = 0;
    uint32 CheckedSeconds = 0;
};

thread_local PendingHit sPendingHit;
std::mutex sHealedBeastsMutex;
std::unordered_map<ObjectGuid, std::unordered_set<ObjectGuid>> sHealedBeasts;
std::mutex sPendingKillsMutex;
std::unordered_map<ObjectGuid, PendingKill> sPendingKills;

Player* GetDruidOwner(Unit* unit)
{
    if (!unit)
        return nullptr;

    Player* player = unit->GetCharmerOrOwnerPlayerOrPlayerItself();
    return player && player->IsClass(CLASS_DRUID) ? player : nullptr;
}

bool IsSleeping(Unit const* unit)
{
    if (!unit)
        return false;

    if (unit->IsSitState() || unit->getStandState() == UNIT_STAND_STATE_SLEEP)
        return true;

    uint64 const sleepMask = 1ULL << MECHANIC_SLEEP;
    for (auto const& aura : unit->GetAppliedAuras())
    {
        SpellInfo const* spellInfo = aura.second->GetBase()->GetSpellInfo();
        if (spellInfo && (spellInfo->GetAllEffectsMechanicMask() & sleepMask))
            return true;
    }

    return false;
}

bool HasPeriodicDamageEffect(SpellInfo const* spellInfo)
{
    if (!spellInfo)
        return false;

    return std::any_of(spellInfo->GetEffects().begin(), spellInfo->GetEffects().end(),
        [](SpellEffectInfo const& effect)
        {
            return effect.Effect == SPELL_EFFECT_APPLY_AURA
                && (effect.ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE
                    || effect.ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE_PERCENT
                    || effect.ApplyAuraName == SPELL_AURA_PERIODIC_LEECH);
        });
}

void SetPendingHit(Unit* victim, Unit* attacker, bool bleedHumanoid,
    SpellSchoolMask schoolMask, bool canKill)
{
    sPendingHit = {};
    if (!victim)
        return;

    sPendingHit.Victim = victim->GetGUID();
    Player* player = GetDruidOwner(attacker);
    if (!player)
        return;

    sPendingHit.Player = player->GetGUID();
    sPendingHit.BleedHumanoid = bleedHumanoid && victim->ToCreature()
        && victim->GetCreatureType() == CREATURE_TYPE_HUMANOID;
    if (!canKill || !victim->ToCreature() || !player->IsHostileTo(victim))
        return;

    sPendingHit.BarkskinNature = (schoolMask & SPELL_SCHOOL_MASK_NATURE)
        && player->HasAura(SPELL_BARKSKIN);
    sPendingHit.CatSleeping = attacker == player
        && player->GetShapeshiftForm() == FORM_CAT && IsSleeping(victim);
}
}

class unit_sod_druid_requirements : public UnitScript
{
public:
    unit_sod_druid_requirements() : UnitScript("unit_sod_druid_requirements", true,
        { UNITHOOK_ON_HEAL, UNITHOOK_ON_DAMAGE, UNITHOOK_MODIFY_PERIODIC_DAMAGE_AURAS_TICK,
          UNITHOOK_MODIFY_MELEE_DAMAGE, UNITHOOK_MODIFY_SPELL_DAMAGE_TAKEN,
          UNITHOOK_ON_UNIT_DEATH }) { }

    void OnHeal(Unit* healer, Unit* receiver, uint32& gain) override
    {
        if (!receiver)
            return;

        if (sPendingHit.Victim == receiver->GetGUID())
            sPendingHit = {};

        if (!SodDruidEnabled())
            return;

        Player* player = healer ? healer->ToPlayer() : nullptr;
        Creature* creature = receiver->ToCreature();
        if (!gain || !player || !player->IsClass(CLASS_DRUID) || !creature
            || creature->GetCreatureType() != CREATURE_TYPE_BEAST)
            return;

        bool inserted;
        {
            std::lock_guard<std::mutex> guard(sHealedBeastsMutex);
            inserted = sHealedBeasts[player->GetGUID()].insert(creature->GetGUID()).second;
        }
        if (inserted)
            sRuneRequirements->OnEvent(player, "druid_heal_beasts");
    }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage,
        SpellInfo const* spellInfo) override
    {
        if (!SodDruidEnabled() || !target || !spellInfo)
        {
            sPendingHit = {};
            return;
        }

        bool const bleed = damage && (spellInfo->GetAllEffectsMechanicMask()
            & (1ULL << MECHANIC_BLEED));
        bool const canKill = damage && damage >= target->GetHealth()
            && HasPeriodicDamageEffect(spellInfo);
        SetPendingHit(target, attacker,
            bleed, spellInfo->GetSchoolMask(), canKill);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage,
        SpellInfo const* spellInfo) override
    {
        if (!SodDruidEnabled() || damage <= 0 || !target || !spellInfo)
        {
            sPendingHit = {};
            return;
        }

        SetPendingHit(target, attacker, false, spellInfo->GetSchoolMask(),
            uint32(damage) >= target->GetHealth());
    }

    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
    {
        if (!SodDruidEnabled() || !damage || !target)
        {
            sPendingHit = {};
            return;
        }

        SetPendingHit(target, attacker, false, SPELL_SCHOOL_MASK_NORMAL,
            damage >= target->GetHealth());
    }

    void OnDamage(Unit* attacker, Unit* victim, uint32& damage) override
    {
        PendingHit const hit = sPendingHit;
        sPendingHit = {};
        if (!SodDruidEnabled() || !damage || !victim
            || hit.Victim != victim->GetGUID())
            return;

        bool const potentialKill = victim->ToCreature() && victim->IsAlive()
            && damage >= victim->GetHealth();
        if (potentialKill)
        {
            std::lock_guard<std::mutex> guard(sPendingKillsMutex);
            sPendingKills.erase(victim->GetGUID());
        }

        if (hit.Player == ObjectGuid::Empty)
            return;

        Player* player = GetDruidOwner(attacker);
        if (!player || player->GetGUID() != hit.Player)
            return;

        if (hit.BleedHumanoid && victim->ToCreature()
            && victim->GetCreatureType() == CREATURE_TYPE_HUMANOID)
            sRuneRequirements->OnEvent(player, "druid_bleed_humanoids");

        if (!potentialKill || !player->IsHostileTo(victim))
            return;

        if (!hit.BarkskinNature && !hit.CatSleeping)
            return;

        std::lock_guard<std::mutex> guard(sPendingKillsMutex);
        sPendingKills[victim->GetGUID()] = { player->GetGUID(),
            hit.BarkskinNature, hit.CatSleeping };
    }

    void OnUnitDeath(Unit* unit, Unit* /*killer*/) override
    {
        if (!unit)
            return;

        std::lock_guard<std::mutex> guard(sPendingKillsMutex);
        sPendingKills.erase(unit->GetGUID());
    }
};

class player_sod_druid_requirements : public PlayerScript
{
public:
    player_sod_druid_requirements() : PlayerScript("player_sod_druid_requirements",
        { PLAYERHOOK_ON_CREATURE_KILL, PLAYERHOOK_ON_CREATURE_KILLED_BY_PET,
          PLAYERHOOK_ON_UPDATE, PLAYERHOOK_ON_LOGOUT }) { }

    void OnPlayerCreatureKill(Player* killer, Creature* killed) override
    {
        HandleConfirmedKill(killer, killed);
    }

    void OnPlayerCreatureKilledByPet(Player* owner, Creature* killed) override
    {
        HandleConfirmedKill(owner, killed);
    }

    void HandleConfirmedKill(Player* player, Creature* killed)
    {
        if (!SodDruidEnabled() || !player || !killed || !player->IsClass(CLASS_DRUID))
            return;

        PendingKill hit;
        {
            std::lock_guard<std::mutex> guard(sPendingKillsMutex);
            auto const itr = sPendingKills.find(killed->GetGUID());
            if (itr == sPendingKills.end())
                return;
            hit = itr->second;
            sPendingKills.erase(itr);
        }

        if (hit.Player != player->GetGUID())
            return;

        if (hit.BarkskinNature)
            sRuneRequirements->OnEvent(player, "druid_barkskin_nature_kill");
        if (hit.CatSleeping)
            sRuneRequirements->OnEvent(player, "druid_cat_sleeping_kill");
    }

    void OnPlayerUpdate(Player* player, uint32 diff) override
    {
        if (!player || !player->IsClass(CLASS_DRUID) || !SodDruidEnabled()
            || !sRuneRequirements->IsEnabled())
        {
            if (player)
            {
                std::lock_guard<std::mutex> guard(_rageStreaksMutex);
                _rageStreaks.erase(player->GetGUID());
            }
            return;
        }

        ShapeshiftForm const form = player->GetShapeshiftForm();
        if ((form != FORM_BEAR && form != FORM_DIREBEAR)
            || player->GetPower(POWER_RAGE) < 500) // Core stores Rage in tenths.
        {
            std::lock_guard<std::mutex> guard(_rageStreaksMutex);
            _rageStreaks.erase(player->GetGUID());
            return;
        }

        uint32 elapsedSeconds;
        bool reportProgress = false;
        {
            std::lock_guard<std::mutex> guard(_rageStreaksMutex);
            RageStreak& streak = _rageStreaks[player->GetGUID()];
            streak.ElapsedMs = uint32(std::min<uint64>(60000,
                uint64(streak.ElapsedMs) + diff));
            elapsedSeconds = streak.ElapsedMs / 1000;
            if (elapsedSeconds > streak.CheckedSeconds)
            {
                streak.CheckedSeconds = elapsedSeconds;
                reportProgress = true;
            }
        }

        if (!reportProgress)
            return;

        uint32 const progress = sRuneRequirements->GetProgress(player, ITEM_MANGLE);
        if (elapsedSeconds > progress)
            sRuneRequirements->OnEvent(player, "druid_bear_rage_streak", 0, 0,
                elapsedSeconds - progress);
    }

    void OnPlayerLogout(Player* player) override
    {
        if (!player)
            return;

        ObjectGuid const guid = player->GetGUID();
        {
            std::lock_guard<std::mutex> guard(_rageStreaksMutex);
            _rageStreaks.erase(guid);
        }
        std::lock_guard<std::mutex> guard(sHealedBeastsMutex);
        sHealedBeasts.erase(guid);
    }

private:
    std::mutex _rageStreaksMutex;
    std::unordered_map<ObjectGuid, RageStreak> _rageStreaks;
};

void AddSC_sod_druid_requirements()
{
    new unit_sod_druid_requirements();
    new player_sod_druid_requirements();
}
