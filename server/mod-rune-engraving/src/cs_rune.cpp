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
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Chat.h"
#include "ChatCommand.h"
#include "Player.h"
#include "RuneEngravingMgr.h"
#include "RuneStrings.h"
#include "ScriptMgr.h"

using namespace Acore::ChatCommands;

namespace
{
    // The dedicated Rune Engraver NPC (rune_engraving_schema.sql). `.rune summon`
    // spawns a TEMPORARY one at the caller: not saved to the DB, auto-despawns
    // after RUNE_ENGRAVER_SUMMON_MS, and gone on a server restart.
    constexpr uint32 RUNE_ENGRAVER_NPC       = 700000;
    constexpr uint32 RUNE_ENGRAVER_SUMMON_MS = 5 * 60 * 1000; // 5 minutes
}

// .rune commands — a headless path to drive the engine without the gossip NPC,
// useful for testing the engrave -> grant -> login-reapply loop. `.rune summon`
// conjures a temporary engraver gossip NPC for the caller.
class cs_rune : public CommandScript
{
public:
    cs_rune() : CommandScript("cs_rune") {}

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable runeTable =
        {
            { "summon",  HandleSummon,  SEC_PLAYER,        Console::No  },
            { "list",    HandleList,    SEC_GAMEMASTER,    Console::No  },
            { "slots",   HandleSlots,   SEC_GAMEMASTER,    Console::No  },
            { "engrave", HandleEngrave, SEC_GAMEMASTER,    Console::No  },
            { "clear",   HandleClear,   SEC_GAMEMASTER,    Console::No  },
            { "unlock",  HandleUnlock,  SEC_GAMEMASTER,    Console::No  },
            { "lock",    HandleLock,    SEC_GAMEMASTER,    Console::No  },
            { "unlocks", HandleUnlocks, SEC_GAMEMASTER,    Console::No  },
            { "reload",  HandleReload,  SEC_ADMINISTRATOR, Console::Yes },
        };
        static ChatCommandTable root = { { "rune", runeTable } };
        return root;
    }

    // Summons a temporary Rune Engraver at the caller. Ephemeral: not saved to the
    // DB, auto-despawns after a few minutes, and gone on a server restart. Any
    // player may summon their own; the gossip still enforces the engraving rules.
    static bool HandleSummon(ChatHandler* handler)
    {
        Player* player = handler->GetPlayer();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_COMMAND_INGAME));
            return false;
        }

        player->SummonCreature(RUNE_ENGRAVER_NPC, *player, TEMPSUMMON_TIMED_DESPAWN,
            RUNE_ENGRAVER_SUMMON_MS);
        handler->SendSysMessage(RuneStr(handler, RUNE_STRING_SUMMONED));
        return true;
    }

    static bool HandleList(ChatHandler* handler)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_ENGRAVED_RUNES_HEADER).c_str(), player->GetName());
        bool any = false;
        for (uint8 slot = 0; slot < RUNE_SLOT_MAX; ++slot)
        {
            uint32 runeId = sRuneEngravingMgr->GetEngraved(player->GetGUID(), slot);
            if (!runeId)
                continue;
            any = true;
            RuneTemplate const* rune = sRuneEngravingMgr->GetRune(runeId);
            std::string runeName = rune ? rune->Name : RuneStr(handler, RUNE_STRING_UNKNOWN_RUNE_NAME);
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_ENGRAVED_RUNE_ROW).c_str(),
                RuneSlotName(handler->GetPlayer(), slot), runeName,
                runeId, rune ? rune->SpellId : 0);
        }
        if (!any)
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_RUNES_ENGRAVED));
        return true;
    }

    static bool HandleSlots(ChatHandler* handler)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        uint8 level = player->GetLevel();
        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_SLOTS_HEADER).c_str(),
            player->GetName(), uint32(level));
        for (uint8 slot = 0; slot < RUNE_SLOT_MAX; ++slot)
        {
            uint32 minLevel = sRuneEngravingMgr->SlotMinLevel(slot);
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_SLOT_UNLOCK_LEVEL).c_str(),
                RuneSlotName(handler->GetPlayer(), slot), minLevel,
                RuneStr(handler, level >= minLevel ? RUNE_STRING_SLOT_OPEN : RUNE_STRING_SLOT_LOCKED));
        }
        return true;
    }

    static bool HandleEngrave(ChatHandler* handler, uint8 slot, uint32 runeId)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        EngraveResult result = sRuneEngravingMgr->Engrave(player, slot, runeId);
        if (result == EngraveResult::Success)
        {
            RuneTemplate const* rune = sRuneEngravingMgr->GetRune(runeId);
            std::string runeName = rune ? rune->Name : RuneStr(handler, RUNE_STRING_UNKNOWN_RUNE_NAME);
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_ENGRAVED_IN_SLOT).c_str(),
                runeName, uint32(slot), RuneSlotName(handler->GetPlayer(), slot));
            return true;
        }

        uint32 reasonString = RUNE_STRING_REASON_UNKNOWN_RUNE;
        switch (result)
        {
            case EngraveResult::PrereqMissing:   reasonString = RUNE_STRING_REASON_PREREQUISITE; break;
            case EngraveResult::SlotLevelTooLow: reasonString = RUNE_STRING_REASON_SLOT_LEVEL; break;
            case EngraveResult::DuplicateRune:   reasonString = RUNE_STRING_REASON_DUPLICATE; break;
            case EngraveResult::Locked:          reasonString = RUNE_STRING_REASON_LOCKED; break;
            case EngraveResult::WrongClass:      reasonString = RUNE_STRING_REASON_WRONG_CLASS; break;
            case EngraveResult::WrongSlot:       reasonString = RUNE_STRING_REASON_WRONG_SLOT; break;
            case EngraveResult::UnknownRune:     reasonString = RUNE_STRING_REASON_UNKNOWN_RUNE; break;
            default: break;
        }
        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_ENGRAVE_FAILED).c_str(),
            runeId, uint32(slot), RuneStr(handler, reasonString));
        return false;
    }

    static bool HandleClear(ChatHandler* handler, uint8 slot)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        if (sRuneEngravingMgr->RemoveRune(player, slot))
        {
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_CLEARED_SLOT).c_str(),
                uint32(slot), RuneSlotName(handler->GetPlayer(), slot));
            return true;
        }

        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_NOTHING_ENGRAVED).c_str(), uint32(slot));
        return false;
    }

    static bool HandleUnlock(ChatHandler* handler, uint32 runeId)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        if (sRuneEngravingMgr->UnlockRune(player, runeId))
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_UNLOCKED_FOR).c_str(), runeId, player->GetName());
        else
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_ALREADY_UNLOCKED_FOR).c_str(), runeId, player->GetName());
        return true;
    }

    static bool HandleLock(ChatHandler* handler, uint32 runeId)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        if (sRuneEngravingMgr->LockRune(player, runeId))
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_LOCKED_FOR).c_str(), runeId, player->GetName());
        else
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_NOT_UNLOCKED_FOR).c_str(), runeId, player->GetName());
        return true;
    }

    static bool HandleUnlocks(ChatHandler* handler)
    {
        Player* player = handler->getSelectedPlayerOrSelf();
        if (!player)
        {
            handler->SendSysMessage(RuneStr(handler, RUNE_STRING_NO_TARGET));
            return false;
        }

        std::vector<uint32> ids = sRuneEngravingMgr->GetUnlockedRunes(player->GetGUID());
        if (ids.empty())
        {
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_NO_UNLOCKED_RUNES).c_str(), player->GetName());
            return true;
        }

        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_UNLOCKED_RUNES_HEADER).c_str(), player->GetName());
        for (uint32 id : ids)
        {
            RuneTemplate const* rune = sRuneEngravingMgr->GetRune(id);
            std::string runeName = rune ? rune->Name : RuneStr(handler, RUNE_STRING_UNKNOWN_RUNE_NAME);
            handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_UNLOCKED_RUNE_ROW).c_str(), id, runeName);
        }
        return true;
    }

    static bool HandleReload(ChatHandler* handler)
    {
        sRuneEngravingMgr->LoadCatalog();
        handler->PSendSysMessage(RuneStr(handler, RUNE_STRING_CATALOG_RELOADED).c_str(),
            sRuneEngravingMgr->CatalogSize());
        return true;
    }
};

void AddSC_cs_rune()
{
    new cs_rune();
}
