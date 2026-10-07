/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 */

#include "RuneRequirementMgr.h"
#include "Chat.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Player.h"
#include "RuneEngravingMgr.h"
#include "RuneStrings.h"
#include "StringFormat.h"
#include "WorldSession.h"
#include <algorithm>
#include <limits>
#include <unordered_map>

RuneRequirementMgr* RuneRequirementMgr::instance()
{
    static RuneRequirementMgr instance;
    return &instance;
}

void RuneRequirementMgr::ApplyConfig()
{
    _enabled = sConfigMgr->GetOption<bool>("RuneEngraving.Requirements.Enable", true);
}

void RuneRequirementMgr::LoadRequirements()
{
    std::lock_guard<std::mutex> guard(_requirementsMutex);
    _requirements.clear();

    QueryResult tableResult = WorldDatabase.Query(
        "SELECT 1 FROM `information_schema`.`tables` "
        "WHERE `table_schema` = DATABASE() AND `table_name` = 'rune_item_requirement'");
    if (!tableResult)
    {
        LOG_INFO("module", "RuneEngraving: rune_item_requirement table is absent; item requirements are disabled.");
        return;
    }

    QueryResult result = WorldDatabase.Query(
        "SELECT `item_id`, `req_key`, `param1`, `param2`, `target_count`, `text_id` "
        "FROM `rune_item_requirement` "
        "ORDER BY `item_id`, `req_key`, `param1`, `param2`");
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        Requirement requirement;
        uint32 itemId = fields[0].Get<uint32>();
        requirement.ReqKey = fields[1].Get<std::string>();
        requirement.Param1 = fields[2].Get<uint32>();
        requirement.Param2 = fields[3].Get<uint32>();
        requirement.Target = fields[4].Get<uint32>();
        requirement.TextId = fields[5].Get<uint32>();
        if (!requirement.Target || !requirement.TextId)
        {
            LOG_ERROR("module", "RuneEngraving: ignoring invalid requirement for item {} (target/text id must be nonzero).", itemId);
            continue;
        }
        _requirements[itemId].push_back(std::move(requirement));
    } while (result->NextRow());

    LOG_INFO("module", "RuneEngraving: loaded requirements for {} rune item(s).", _requirements.size());
}

void RuneRequirementMgr::LoadPlayer(Player* player)
{
    if (!player || !player->GetSession())
        return;

    ObjectGuid guid = player->GetGUID();
    uint32 guidLow = guid.GetCounter();
    uint64 generation;
    std::unordered_map<uint32, uint32> targets;
    {
        std::lock_guard<std::mutex> guard(_requirementsMutex);
        for (auto const& [itemId, requirements] : _requirements)
            if (!requirements.empty())
                targets[itemId] = requirements.front().Target;
    }
    {
        std::lock_guard<std::mutex> guard(_stateMutex);
        generation = ++_nextGeneration;
        PlayerState& state = _players[guid];
        state = PlayerState{};
        state.Generation = generation;
    }

    player->GetSession()->GetQueryProcessor().AddCallback(
        CharacterDatabase.AsyncQuery(Acore::StringFormat(
            "SELECT `item_id`, `progress` FROM `character_rune_progress` WHERE `guid` = {}", guidLow))
        .WithCallback([this, guid, guidLow, generation, targets = std::move(targets)](QueryResult result)
        {
            std::unordered_map<uint32, uint32> stored;
            if (result)
                do
                {
                    Field* fields = result->Fetch();
                    uint32 itemId = fields[0].Get<uint32>();
                    stored[itemId] = fields[1].Get<uint32>();
                } while (result->NextRow());
            std::unordered_map<uint32, uint32> original = stored;
            for (auto& [itemId, progress] : stored)
            {
                auto target = targets.find(itemId);
                if (target != targets.end())
                    progress = std::min(progress, target->second);
            }

            {
                std::lock_guard<std::mutex> guard(_stateMutex);
                auto playerState = _players.find(guid);
                if (playerState == _players.end() || playerState->second.Generation != generation)
                    return;

                PlayerState& state = playerState->second;
                for (auto const& [itemId, amount] : state.PendingAdds)
                {
                    uint64 value = uint64(stored[itemId]) + amount;
                    auto target = targets.find(itemId);
                    if (target != targets.end())
                        stored[itemId] = uint32(std::min<uint64>(value, target->second));
                    else
                        stored[itemId] = uint32(std::min<uint64>(value, std::numeric_limits<uint32>::max()));
                }
                for (auto const& [itemId, value] : state.Overrides)
                    stored[itemId] = value;

                state.Progress = stored;
                state.Loaded = true;
                state.PendingAdds.clear();
                state.Overrides.clear();
            }

            for (auto const& [itemId, progress] : stored)
            {
                auto previous = original.find(itemId);
                if ((previous == original.end() && progress != 0)
                    || (previous != original.end() && previous->second != progress))
                    SaveProgress(guidLow, itemId, progress);
            }
        }));
}

void RuneRequirementMgr::UnloadPlayer(ObjectGuid guid)
{
    std::lock_guard<std::mutex> guard(_stateMutex);
    _players.erase(guid);
}

void RuneRequirementMgr::DeleteCharacterData(CharacterDatabaseTransaction trans, uint32 guidLow)
{
    trans->Append("DELETE FROM `character_rune_progress` WHERE `guid` = {}", guidLow);

    ObjectGuid guid = ObjectGuid::Create<HighGuid::Player>(guidLow);
    std::lock_guard<std::mutex> guard(_stateMutex);
    _players.erase(guid);
}

void RuneRequirementMgr::OnEvent(Player* player, std::string const& reqKey,
    uint32 param1, uint32 param2, uint32 amount)
{
    if (!player || !_enabled || !amount)
        return;

    std::unordered_map<uint32, uint64> increments;
    std::unordered_map<uint32, uint32> targets;
    std::unordered_map<uint32, uint32> textIds;
    {
        std::lock_guard<std::mutex> guard(_requirementsMutex);
        for (auto const& [itemId, requirements] : _requirements)
            for (Requirement const& requirement : requirements)
                if (requirement.ReqKey == reqKey
                    && (!requirement.Param1 || requirement.Param1 == param1)
                    && (!requirement.Param2 || requirement.Param2 == param2))
                {
                    ++increments[itemId];
                    targets[itemId] = requirements.front().Target;
                    textIds[itemId] = requirements.front().TextId;
                }
    }

    std::vector<std::pair<uint32, uint32>> changed;
    std::vector<uint32> completed;
    for (auto const& [itemId, matches] : increments)
    {
        if (!targets[itemId] || sRuneEngravingMgr->HasItemRuneUnlocked(player->GetGUID(), itemId))
            continue;

        std::lock_guard<std::mutex> guard(_stateMutex);
        auto playerState = _players.find(player->GetGUID());
        if (playerState == _players.end())
            continue;

        PlayerState& state = playerState->second;
        uint32 oldProgress = state.Progress[itemId];
        uint32 target = targets[itemId];
        if (oldProgress >= target)
            continue;

        uint64 increment = uint64(amount) * matches;
        uint32 newProgress = uint32(std::min<uint64>(uint64(oldProgress) + increment, target));
        if (newProgress == oldProgress)
            continue;

        state.Progress[itemId] = newProgress;
        if (state.Loaded)
            changed.emplace_back(itemId, newProgress);
        else
        {
            auto override = state.Overrides.find(itemId);
            if (override != state.Overrides.end())
                override->second = newProgress;
            else
                state.PendingAdds[itemId] += increment;
        }

        if (newProgress >= target)
            completed.push_back(textIds[itemId]);
    }

    for (auto const& [itemId, progress] : changed)
        SaveProgress(player->GetGUID().GetCounter(), itemId, progress);

    ChatHandler handler(player->GetSession());
    for (uint32 textId : completed)
        handler.SendSysMessage(RuneFormat(player, RUNE_STRING_REQUIREMENT_COMPLETED,
            RuneStr(player, textId)));
}

bool RuneRequirementMgr::IsComplete(Player const* player, uint32 itemId) const
{
    if (!HasRequirement(itemId))
        return true;
    uint32 target = GetTarget(itemId);
    return player && target && GetProgress(player, itemId) >= target;
}

uint32 RuneRequirementMgr::GetProgress(Player const* player, uint32 itemId) const
{
    if (!player)
        return 0;
    std::lock_guard<std::mutex> guard(_stateMutex);
    auto state = _players.find(player->GetGUID());
    if (state == _players.end())
        return 0;
    auto progress = state->second.Progress.find(itemId);
    return progress != state->second.Progress.end() ? progress->second : 0;
}

uint32 RuneRequirementMgr::GetTarget(uint32 itemId) const
{
    std::lock_guard<std::mutex> guard(_requirementsMutex);
    auto requirement = _requirements.find(itemId);
    return requirement != _requirements.end() && !requirement->second.empty()
        ? requirement->second.front().Target : 0;
}

uint32 RuneRequirementMgr::GetTextId(uint32 itemId) const
{
    std::lock_guard<std::mutex> guard(_requirementsMutex);
    auto requirement = _requirements.find(itemId);
    return requirement != _requirements.end() && !requirement->second.empty()
        ? requirement->second.front().TextId : 0;
}

bool RuneRequirementMgr::HasRequirement(uint32 itemId) const
{
    std::lock_guard<std::mutex> guard(_requirementsMutex);
    auto requirement = _requirements.find(itemId);
    return requirement != _requirements.end() && !requirement->second.empty();
}

std::vector<RuneItemProgress> RuneRequirementMgr::GetPlayerRequirements(Player const* player) const
{
    std::vector<uint32> itemIds;
    {
        std::lock_guard<std::mutex> guard(_requirementsMutex);
        itemIds.reserve(_requirements.size());
        for (auto const& [itemId, requirements] : _requirements)
            if (!requirements.empty())
                itemIds.push_back(itemId);
    }
    std::sort(itemIds.begin(), itemIds.end());

    std::vector<RuneItemProgress> result;
    result.reserve(itemIds.size());
    for (uint32 itemId : itemIds)
        result.push_back({ itemId, GetProgress(player, itemId), GetTarget(itemId) });
    return result;
}

void RuneRequirementMgr::Complete(Player* player, uint32 itemId)
{
    if (!player)
        return;
    uint32 target = GetTarget(itemId);
    if (!target)
        return;

    bool save = false;
    {
        std::lock_guard<std::mutex> guard(_stateMutex);
        auto playerState = _players.find(player->GetGUID());
        if (playerState == _players.end())
            return;
        PlayerState& state = playerState->second;
        uint32& progress = state.Progress[itemId];
        save = progress != target;
        progress = target;
        if (!state.Loaded)
        {
            state.PendingAdds.erase(itemId);
            state.Overrides[itemId] = target;
            save = false;
        }
    }
    if (save)
        SaveProgress(player->GetGUID().GetCounter(), itemId, target);
}

void RuneRequirementMgr::Reset(Player* player, uint32 itemId)
{
    if (!player || !HasRequirement(itemId))
        return;

    bool save = false;
    {
        std::lock_guard<std::mutex> guard(_stateMutex);
        auto playerState = _players.find(player->GetGUID());
        if (playerState == _players.end())
            return;
        PlayerState& state = playerState->second;
        auto progress = state.Progress.find(itemId);
        save = progress != state.Progress.end() && progress->second != 0;
        state.Progress[itemId] = 0;
        if (!state.Loaded)
        {
            state.PendingAdds.erase(itemId);
            state.Overrides[itemId] = 0;
            save = false;
        }
    }
    if (save)
        SaveProgress(player->GetGUID().GetCounter(), itemId, 0);
}

void RuneRequirementMgr::SaveProgress(uint32 guid, uint32 itemId, uint32 progress) const
{
    CharacterDatabase.Execute(
        "REPLACE INTO `character_rune_progress` (`guid`, `item_id`, `progress`) VALUES ({}, {}, {})",
        guid, itemId, progress);
}
