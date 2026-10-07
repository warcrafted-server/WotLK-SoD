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

#ifndef MOD_RUNE_REQUIREMENT_MGR_H
#define MOD_RUNE_REQUIREMENT_MGR_H

#include "DatabaseEnvFwd.h"
#include "ObjectGuid.h"
#include "Define.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class Player;

struct RuneItemProgress
{
    uint32 ItemId = 0;
    uint32 Progress = 0;
    uint32 Target = 0;
};

class RuneRequirementMgr
{
public:
    static RuneRequirementMgr* instance();

    void ApplyConfig();
    bool IsEnabled() const { return _enabled; }
    void LoadRequirements();
    void LoadPlayer(Player* player);
    void UnloadPlayer(ObjectGuid guid);
    void DeleteCharacterData(CharacterDatabaseTransaction trans, uint32 guidLow);

    void OnEvent(Player* player, std::string const& reqKey, uint32 param1 = 0,
        uint32 param2 = 0, uint32 amount = 1);
    bool IsComplete(Player const* player, uint32 itemId) const;
    uint32 GetProgress(Player const* player, uint32 itemId) const;
    uint32 GetTarget(uint32 itemId) const;
    uint32 GetTextId(uint32 itemId) const;
    bool HasRequirement(uint32 itemId) const;
    std::vector<RuneItemProgress> GetPlayerRequirements(Player const* player) const;
    void Complete(Player* player, uint32 itemId);
    void Reset(Player* player, uint32 itemId);

private:
    struct Requirement
    {
        std::string ReqKey;
        uint32 Param1 = 0;
        uint32 Param2 = 0;
        uint32 Target = 0;
        uint32 TextId = 0;
    };

    struct PlayerState
    {
        uint64 Generation = 0;
        bool Loaded = false;
        std::unordered_map<uint32, uint32> Progress;
        std::unordered_map<uint32, uint64> PendingAdds;
        std::unordered_map<uint32, uint32> Overrides;
    };

    RuneRequirementMgr() = default;
    void SaveProgress(uint32 guid, uint32 itemId, uint32 progress) const;

    bool _enabled = true;
    mutable std::mutex _requirementsMutex;
    std::unordered_map<uint32, std::vector<Requirement>> _requirements;
    mutable std::mutex _stateMutex;
    std::unordered_map<ObjectGuid, PlayerState> _players;
    uint64 _nextGeneration = 0;
};

#define sRuneRequirements RuneRequirementMgr::instance()

#endif // MOD_RUNE_REQUIREMENT_MGR_H
