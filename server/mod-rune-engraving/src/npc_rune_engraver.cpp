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
#include "Creature.h"
#include "GossipDef.h"
#include "Player.h"
#include "RuneEngravingMgr.h"
#include "RuneStrings.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include <mutex>
#include <unordered_map>
#include <utility>

// The gossip `sender` field tags which menu an item belongs to, so a single
// OnGossipSelect can route slot picks, rune picks, removals, and navigation
// without colliding action-ID ranges.
enum RuneGossipSender
{
    SENDER_SLOT      = 1, // action = RuneSlot      -> open that slot's rune list
    SENDER_RUNE      = 2, // action = rune_id       -> engrave it in the selected slot
    SENDER_UNENGRAVE = 3, // action = RuneSlot      -> clear that slot
    SENDER_BACK      = 4, // action = 0             -> back to the slot list
    SENDER_RESET     = 5, // action = 0             -> debug: reset quests + unlocks
    SENDER_OPEN      = 6, // action = 0             -> root: open the rune engraving menu
    SENDER_ROOT      = 7, // action = 0             -> back to the root gossip
    SENDER_BUY_RUNES = 8, // action = 0             -> open the engraver's rune stock
};

// The slot a player is currently browsing, so a SENDER_RUNE pick knows where to
// engrave. Confined to gossip interaction (single map thread per player), but
// guarded for parity with the rest of the module.
static std::unordered_map<ObjectGuid, uint8> sBrowsingSlot;
static std::mutex sBrowsingMutex;

template<typename... Args>
static void SendRuneMessage(ChatHandler& handler, uint32 id, Args&&... args)
{
    handler.SendSysMessage(RuneFormat(&handler, id, std::forward<Args>(args)...));
}

class npc_rune_engraver : public CreatureScript
{
public:
    npc_rune_engraver() : CreatureScript("npc_rune_engraver") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        ShowRootMenu(player, creature);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        switch (sender)
        {
            case SENDER_SLOT:
                SetBrowsingSlot(player->GetGUID(), uint8(action));
                ShowRuneMenu(player, creature, uint8(action));
                break;
            case SENDER_RUNE:
            {
                uint8 slot = GetBrowsingSlot(player->GetGUID());
                ChatHandler handler(player->GetSession());
                switch (sRuneEngravingMgr->Engrave(player, slot, action))
                {
                    case EngraveResult::Success:
                    {
                        RuneTemplate const* rune = sRuneEngravingMgr->GetRune(action);
                        std::string runeName = rune
                            ? sRuneEngravingMgr->GetRuneName(*rune, player->GetSession()->GetSessionDbLocaleIndex())
                            : RuneStr(player, RUNE_STRING_UNKNOWN_RUNE_NAME);
                        SendRuneMessage(handler, RUNE_STRING_NPC_ENGRAVED,
                            runeName, RuneSlotName(player, slot));
                        break;
                    }
                    case EngraveResult::PrereqMissing:
                        SendRuneMessage(handler, RUNE_STRING_NPC_PREREQ_SHORT);
                        break;
                    case EngraveResult::SlotLevelTooLow:
                        SendRuneMessage(handler, RUNE_STRING_NPC_SLOT_LEVEL,
                            RuneSlotName(player, slot), sRuneEngravingMgr->SlotMinLevel(slot));
                        break;
                    case EngraveResult::DuplicateRune:
                        SendRuneMessage(handler, RUNE_STRING_NPC_DUPLICATE);
                        break;
                    case EngraveResult::Locked:
                        SendRuneMessage(handler, RUNE_STRING_NPC_UNDISCOVERED);
                        break;
                    case EngraveResult::WrongClass:
                        SendRuneMessage(handler, RUNE_STRING_NPC_WRONG_CLASS);
                        break;
                    default:
                        SendRuneMessage(handler, RUNE_STRING_NPC_ENGRAVE_FAILED);
                        break;
                }
                ShowRuneMenu(player, creature, slot);
                break;
            }
            case SENDER_UNENGRAVE:
                if (sRuneEngravingMgr->RemoveRune(player, uint8(action)))
                {
                    ChatHandler handler(player->GetSession());
                    SendRuneMessage(handler, RUNE_STRING_NPC_CLEARED,
                        RuneSlotName(player, uint8(action)));
                }
                ShowRuneMenu(player, creature, uint8(action));
                break;
            case SENDER_RESET:
            {
                // Guard against a stale menu if the debug flag was turned off.
                if (sRuneEngravingMgr->DebugMenu())
                {
                    RuneResetSummary summary = sRuneEngravingMgr->ResetGatedProgress(player);
                    ChatHandler handler(player->GetSession());
                    SendRuneMessage(handler, RUNE_STRING_NPC_DEBUG_RESET_DONE,
                        summary.RunesLocked, summary.QuestsReset, summary.ItemsRestored);
                }
                ShowSlotMenu(player, creature);
                break;
            }
            case SENDER_OPEN:
            {
                // Engine could have been disabled, or the player may not yet meet
                // the learn-Engraving prerequisite -- keep the gossip open on the
                // root either way so quests / vendor stay reachable.
                if (!sRuneEngravingMgr->IsEnabled())
                {
                    ShowRootMenu(player, creature);
                    break;
                }
                if (!sRuneEngravingMgr->MeetsPrereq(player))
                {
                    ChatHandler handler(player->GetSession());
                    SendRuneMessage(handler, RUNE_STRING_NPC_PREREQ_LONG);
                    ShowRootMenu(player, creature);
                    break;
                }
                ShowSlotMenu(player, creature);
                break;
            }
            case SENDER_ROOT:
                ShowRootMenu(player, creature);
                break;
            case SENDER_BUY_RUNES:
                player->GetSession()->SendListInventory(creature->GetGUID());
                break;
            case SENDER_BACK:
            default:
                ShowSlotMenu(player, creature);
                break;
        }
        return true;
    }

private:
    static void SetBrowsingSlot(ObjectGuid guid, uint8 slot)
    {
        std::lock_guard<std::mutex> guard(sBrowsingMutex);
        sBrowsingSlot[guid] = slot;
    }

    static uint8 GetBrowsingSlot(ObjectGuid guid)
    {
        std::lock_guard<std::mutex> guard(sBrowsingMutex);
        auto it = sBrowsingSlot.find(guid);
        return it != sBrowsingSlot.end() ? it->second : RUNE_SLOT_MAX;
    }

    // Root gossip: a single engraver entry when the engine is enabled
    // plus the NPC's own quests. The rune flow now lives one level down so the
    // initial menu stays uncluttered on these quest-giver / vendor NPCs.
    void ShowRootMenu(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sRuneEngravingMgr->IsEnabled())
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER,
                RuneStr(player, RUNE_STRING_NPC_ROOT), SENDER_OPEN, 0);

        AddGossipItemFor(player, GOSSIP_ICON_VENDOR,
            RuneStr(player, RUNE_STRING_NPC_BUY_RUNES), SENDER_BUY_RUNES, 0);

        // Surface the NPC's quests (a content module's turn-ins) -- the custom
        // gossip would otherwise replace the default menu and hide them. Generic;
        // no content coupling.
        player->PrepareQuestMenu(creature->GetGUID());

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }

    // Second level: one entry per engraving slot, annotated with its current rune.
    void ShowSlotMenu(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        for (uint8 slot = 0; slot < RUNE_SLOT_MAX; ++slot)
        {
            std::string text = RuneFormat(
                player, RUNE_STRING_NPC_SLOT_LABEL, RuneSlotName(player, slot));

            uint32 minLevel = sRuneEngravingMgr->SlotMinLevel(slot);
            if (player->GetLevel() < minLevel)
            {
                text += RuneFormat(player, RUNE_STRING_NPC_SLOT_LOCKED_SUFFIX, minLevel);
            }
            else
            {
                uint32 runeId = sRuneEngravingMgr->GetEngraved(player->GetGUID(), slot);
                if (runeId)
                    if (RuneTemplate const* rune = sRuneEngravingMgr->GetRune(runeId))
                        text += RuneFormat(
                            player, RUNE_STRING_NPC_SLOT_RUNE,
                            sRuneEngravingMgr->GetRuneName(
                                *rune, player->GetSession()->GetSessionDbLocaleIndex()));
            }

            AddGossipItemFor(player, GOSSIP_ICON_TALK, text, SENDER_SLOT, slot);
        }

        // Debug aid (off by default): revert quest + rune-unlock progress so the
        // discovery flow can be re-tested without GM commands.
        if (sRuneEngravingMgr->DebugMenu())
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1,
                RuneStr(player, RUNE_STRING_NPC_DEBUG_RESET), SENDER_RESET, 0);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT,
            RuneStr(player, RUNE_STRING_NPC_BACK), SENDER_ROOT, 0);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }

    // Per-slot: the runes this player may engrave here, plus remove / back.
    void ShowRuneMenu(Player* player, Creature* creature, uint8 slot)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!RuneEngravingMgr::IsValidSlot(slot))
        {
            ShowSlotMenu(player, creature);
            return;
        }

        // Level-gated slot: show the unlock notice instead of the rune list.
        uint32 minLevel = sRuneEngravingMgr->SlotMinLevel(slot);
        if (player->GetLevel() < minLevel)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                RuneFormat(player, RUNE_STRING_NPC_SLOT_LOCKED_NOTICE, minLevel),
                SENDER_BACK, 0);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                RuneStr(player, RUNE_STRING_NPC_BACK_TO_SLOTS), SENDER_BACK, 0);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return;
        }

        uint32 currentRuneId = sRuneEngravingMgr->GetEngraved(player->GetGUID(), slot);
        std::vector<RuneTemplate const*> runes = sRuneEngravingMgr->GetRunesForSlot(player, slot);

        for (RuneTemplate const* rune : runes)
        {
            std::string text = sRuneEngravingMgr->GetRuneName(
                *rune, player->GetSession()->GetSessionDbLocaleIndex());
            if (rune->RuneId == currentRuneId)
                text += RuneStr(player, RUNE_STRING_NPC_ENGRAVED_SUFFIX);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, text, SENDER_RUNE, rune->RuneId);
        }

        if (runes.empty())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT,
                RuneStr(player, RUNE_STRING_NPC_NO_RUNES), SENDER_BACK, 0);

        if (currentRuneId)
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1,
                RuneStr(player, RUNE_STRING_NPC_REMOVE_RUNE), SENDER_UNENGRAVE, slot);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT,
            RuneStr(player, RUNE_STRING_NPC_BACK_TO_SLOTS), SENDER_BACK, 0);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }
};

void AddSC_npc_rune_engraver()
{
    new npc_rune_engraver();
}
