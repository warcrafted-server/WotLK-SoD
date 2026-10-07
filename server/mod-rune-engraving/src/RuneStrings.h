#pragma once

#include "Chat.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "RuneEngravingMgr.h"
#include "WorldSession.h"
#include <string>
#include <utility>

inline constexpr char RUNE_STRING_MODULE[] = "mod-rune-engraving";

enum RuneString : uint32
{
    RUNE_STRING_COMMAND_INGAME = 1, // In-game command requirement
    RUNE_STRING_SUMMONED, // Temporary engraver summoned
    RUNE_STRING_NO_TARGET, // Missing command target
    RUNE_STRING_ENGRAVED_RUNES_HEADER, // Engraved rune list header
    RUNE_STRING_ENGRAVED_RUNE_ROW, // Engraved rune list row
    RUNE_STRING_NO_RUNES_ENGRAVED, // Empty engraved rune list
    RUNE_STRING_SLOTS_HEADER, // Slot list header
    RUNE_STRING_SLOT_UNLOCK_LEVEL, // Slot unlock level row
    RUNE_STRING_SLOT_OPEN, // Available slot state
    RUNE_STRING_SLOT_LOCKED, // Locked slot state
    RUNE_STRING_ENGRAVED_IN_SLOT, // Successful engraving
    RUNE_STRING_ENGRAVE_FAILED, // Failed engraving format
    RUNE_STRING_REASON_UNKNOWN_RUNE, // Unknown rune reason
    RUNE_STRING_REASON_PREREQUISITE, // Missing prerequisite reason
    RUNE_STRING_REASON_SLOT_LEVEL, // Locked slot reason
    RUNE_STRING_REASON_DUPLICATE, // Duplicate rune reason
    RUNE_STRING_REASON_LOCKED, // Undiscovered rune reason
    RUNE_STRING_REASON_WRONG_CLASS, // Wrong class reason
    RUNE_STRING_REASON_WRONG_SLOT, // Wrong slot reason
    RUNE_STRING_CLEARED_SLOT, // Successful slot clear
    RUNE_STRING_NOTHING_ENGRAVED, // Empty slot clear
    RUNE_STRING_UNLOCKED_FOR, // Rune unlocked
    RUNE_STRING_ALREADY_UNLOCKED_FOR, // Rune already unlocked
    RUNE_STRING_LOCKED_FOR, // Rune locked
    RUNE_STRING_NOT_UNLOCKED_FOR, // Rune already locked
    RUNE_STRING_NO_UNLOCKED_RUNES, // Empty unlocked rune list
    RUNE_STRING_UNLOCKED_RUNES_HEADER, // Unlocked rune list header
    RUNE_STRING_UNLOCKED_RUNE_ROW, // Unlocked rune list row
    RUNE_STRING_CATALOG_RELOADED, // Catalog reload confirmation
    RUNE_STRING_UNKNOWN_RUNE_NAME, // Missing rune name

    RUNE_STRING_NPC_ROOT = 100, // Engraver root option
    RUNE_STRING_NPC_SLOT_LABEL, // Slot menu row
    RUNE_STRING_NPC_SLOT_LOCKED_SUFFIX, // Slot menu locked state
    RUNE_STRING_NPC_DEBUG_RESET, // Debug reset menu option
    RUNE_STRING_NPC_BACK, // Return to root menu
    RUNE_STRING_NPC_SLOT_LOCKED_NOTICE, // Locked slot notice
    RUNE_STRING_NPC_BACK_TO_SLOTS, // Return to slot menu
    RUNE_STRING_NPC_ENGRAVED_SUFFIX, // Currently engraved rune marker
    RUNE_STRING_NPC_NO_RUNES, // Empty rune menu
    RUNE_STRING_NPC_REMOVE_RUNE, // Remove engraved rune option
    RUNE_STRING_NPC_ENGRAVED, // Successful engraving notice
    RUNE_STRING_NPC_PREREQ_SHORT, // Engraving prerequisite error
    RUNE_STRING_NPC_SLOT_LEVEL, // Slot level error
    RUNE_STRING_NPC_DUPLICATE, // Duplicate rune error
    RUNE_STRING_NPC_UNDISCOVERED, // Undiscovered rune error
    RUNE_STRING_NPC_WRONG_CLASS, // Wrong class error
    RUNE_STRING_NPC_ENGRAVE_FAILED, // Generic engraving error
    RUNE_STRING_NPC_CLEARED, // Rune removal notice
    RUNE_STRING_NPC_DEBUG_RESET_DONE, // Debug reset result
    RUNE_STRING_NPC_PREREQ_LONG, // Engraving menu prerequisite error
    RUNE_STRING_NPC_SLOT_RUNE, // Engraved rune in the slot menu
    RUNE_STRING_NPC_BUY_RUNES = 121, // Rune Broker vendor option

    RUNE_STRING_SLOT_HEAD = 60, // Head slot label
    RUNE_STRING_SLOT_NECK, // Neck slot label
    RUNE_STRING_SLOT_SHOULDER, // Shoulder slot label
    RUNE_STRING_SLOT_CLOAK, // Cloak slot label
    RUNE_STRING_SLOT_CHEST, // Chest slot label
    RUNE_STRING_SLOT_WRIST, // Wrist slot label
    RUNE_STRING_SLOT_HANDS, // Hands slot label
    RUNE_STRING_SLOT_WAIST, // Waist slot label
    RUNE_STRING_SLOT_LEGS, // Legs slot label
    RUNE_STRING_SLOT_FEET, // Feet slot label
    RUNE_STRING_SLOT_RING, // Ring slot label
    RUNE_STRING_SLOT_UNKNOWN, // Invalid slot label

    RUNE_STRING_ITEM_UNAVAILABLE = 200, // Item script unavailable
    RUNE_STRING_RUNE_DISCOVERED, // Rune discovery notice
    RUNE_STRING_ALL_RUNES_DISCOVERED, // No new rune notice
    RUNE_STRING_ADDON_ENGRAVED, // Addon success status
    RUNE_STRING_ADDON_PREREQUISITE, // Addon prerequisite error
    RUNE_STRING_ADDON_SLOT_LEVEL, // Addon slot level error
    RUNE_STRING_ADDON_DUPLICATE, // Addon duplicate error
    RUNE_STRING_ADDON_LOCKED, // Addon undiscovered rune error
    RUNE_STRING_ADDON_WRONG_CLASS, // Addon class error
    RUNE_STRING_ADDON_WRONG_SLOT, // Addon slot error
    RUNE_STRING_ADDON_ENGRAVE_FAILED, // Addon generic error
    RUNE_STRING_ADDON_REMOVED, // Addon removal success
    RUNE_STRING_ADDON_NOTHING_TO_REMOVE, // Addon empty removal

    RUNE_STRING_REQUIREMENT_COMPLETED = 300, // Requirement objective completed
    RUNE_STRING_REQUIREMENT_INCOMPLETE, // Item use blocked with progress
    RUNE_STRING_REQUIREMENT_PROGRESS_HEADER, // Progress command header
    RUNE_STRING_REQUIREMENT_PROGRESS_ROW, // Progress command row
    RUNE_STRING_REQUIREMENT_NO_ITEMS, // No configured item requirements
    RUNE_STRING_REQUIREMENT_FORCED_COMPLETE, // GM completion confirmation
    RUNE_STRING_REQUIREMENT_RESET, // GM reset confirmation
    RUNE_STRING_REQUIREMENT_NO_ITEM // Item has no configured requirement
};

// ObjectMgr::GetModuleString(module, id, locale) returns a bogus pointer for an
// unknown id, so check the backing row before asking the session or handler.
inline bool RuneStringExists(uint32 id)
{
    return sObjectMgr->GetModuleString(RUNE_STRING_MODULE, id) != nullptr;
}

inline std::string RuneMissingString(uint32 id)
{
    return "[missing string " + std::to_string(id) + "]";
}

inline std::string RuneStr(Player const* player, uint32 id)
{
    if (player && RuneStringExists(id))
        if (WorldSession* session = player->GetSession())
            if (std::string const* value = session->GetModuleString(RUNE_STRING_MODULE, id))
                return *value;

    return RuneMissingString(id);
}

template<typename... Args>
inline std::string RuneFormat(Player const* player, uint32 id, Args&&... args)
{
    if (player && RuneStringExists(id))
        if (WorldSession* session = player->GetSession())
            if (std::string const* value = session->GetModuleString(RUNE_STRING_MODULE, id))
                return Acore::StringFormat(*value, std::forward<Args>(args)...);

    return RuneMissingString(id);
}

inline std::string RuneStr(ChatHandler* handler, uint32 id)
{
    if (handler && RuneStringExists(id))
        if (std::string const* value = handler->GetModuleString(RUNE_STRING_MODULE, id))
            return *value;

    return RuneMissingString(id);
}

template<typename... Args>
inline std::string RuneFormat(ChatHandler* handler, uint32 id, Args&&... args)
{
    if (handler && RuneStringExists(id))
        if (std::string const* value = handler->GetModuleString(RUNE_STRING_MODULE, id))
            return Acore::StringFormat(*value, std::forward<Args>(args)...);

    return RuneMissingString(id);
}

inline std::string RuneSlotName(Player const* player, uint8 slot)
{
    switch (slot)
    {
        case RUNE_SLOT_HEAD:     return RuneStr(player, RUNE_STRING_SLOT_HEAD);
        case RUNE_SLOT_NECK:     return RuneStr(player, RUNE_STRING_SLOT_NECK);
        case RUNE_SLOT_SHOULDER: return RuneStr(player, RUNE_STRING_SLOT_SHOULDER);
        case RUNE_SLOT_CLOAK:    return RuneStr(player, RUNE_STRING_SLOT_CLOAK);
        case RUNE_SLOT_CHEST:    return RuneStr(player, RUNE_STRING_SLOT_CHEST);
        case RUNE_SLOT_WRIST:    return RuneStr(player, RUNE_STRING_SLOT_WRIST);
        case RUNE_SLOT_HANDS:    return RuneStr(player, RUNE_STRING_SLOT_HANDS);
        case RUNE_SLOT_WAIST:    return RuneStr(player, RUNE_STRING_SLOT_WAIST);
        case RUNE_SLOT_LEGS:     return RuneStr(player, RUNE_STRING_SLOT_LEGS);
        case RUNE_SLOT_FEET:     return RuneStr(player, RUNE_STRING_SLOT_FEET);
        case RUNE_SLOT_RING:     return RuneStr(player, RUNE_STRING_SLOT_RING);
        default:                 return RuneStr(player, RUNE_STRING_SLOT_UNKNOWN);
    }
}
