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
#include "Player.h"
#include "RuneEngravingMgr.h"
#include "RuneStrings.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "StringConvert.h"
#include "StringFormat.h"
#include "Tokenize.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <string>
#include <string_view>
#include <vector>

// Server side of the optional RuneEngraver client addon. The addon talks to the
// engine over the native addon channel (no framework, no core edits): the client
// self-whispers `LANG_ADDON` messages prefixed `RUNE\t`, which reach us through
// PlayerScript::OnPlayerBeforeSendChatMessage; we reply with addon whispers the
// addon renders. The protocol mirrors the data the gossip NPC builds, so the
// panel is just another front-end onto RuneEngravingMgr. See docs/addon-ui.md.
//
// Wire framing: a 3.3.5a addon message is "<prefix>\t<body>"; our prefix is RUNE
// and the body is `~`-separated. Lines stay short (one per slot/rune) so each is
// well under the 255-char addon-message cap.

namespace
{
    constexpr char const* RUNE_WIRE_PREFIX = "RUNE\t";

    // Send one "RUNE\t<body>" line to the player as a self-whisper addon message.
    void SendLine(Player* player, std::string const& body)
    {
        WorldPacket data;
        std::string msg = RUNE_WIRE_PREFIX + body;
        ChatHandler::BuildChatPacket(data, CHAT_MSG_WHISPER, LANG_ADDON, player, player, msg);
        player->GetSession()->SendPacket(&data);
    }

    std::string ResultText(Player const* player, EngraveResult result)
    {
        switch (result)
        {
            case EngraveResult::Success:         return RuneStr(player, RUNE_STRING_ADDON_ENGRAVED);
            case EngraveResult::PrereqMissing:   return RuneStr(player, RUNE_STRING_ADDON_PREREQUISITE);
            case EngraveResult::SlotLevelTooLow: return RuneStr(player, RUNE_STRING_ADDON_SLOT_LEVEL);
            case EngraveResult::DuplicateRune:   return RuneStr(player, RUNE_STRING_ADDON_DUPLICATE);
            case EngraveResult::Locked:          return RuneStr(player, RUNE_STRING_ADDON_LOCKED);
            case EngraveResult::WrongClass:      return RuneStr(player, RUNE_STRING_ADDON_WRONG_CLASS);
            case EngraveResult::WrongSlot:       return RuneStr(player, RUNE_STRING_ADDON_WRONG_SLOT);
            default:                             return RuneStr(player, RUNE_STRING_ADDON_ENGRAVE_FAILED);
        }
    }

    // Push the full panel model: a BEGIN header, one SLOT line per slot with a
    // RUNE line per engravable rune, an optional MSG status line, then END. Uses
    // the same manager calls the gossip NPC makes. `note` (a result/feedback
    // string) is sent inside the block so the client rebuilds model + status
    // atomically; empty = no status line (e.g. a plain REQ).
    void SendPanelState(Player* player, std::string const& note = "")
    {
        SendLine(player, Acore::StringFormat("BEGIN~{}~{}",
            sRuneEngravingMgr->MeetsPrereq(player) ? 1 : 0, player->GetLevel()));

        for (uint8 slot = 0; slot < RUNE_SLOT_MAX; ++slot)
        {
            SendLine(player, Acore::StringFormat("SLOT~{}~{}~{}~{}",
                uint32(slot), RuneSlotName(player, slot),
                sRuneEngravingMgr->SlotMinLevel(slot),
                sRuneEngravingMgr->GetEngraved(player->GetGUID(), slot)));

            for (auto const& [rune, locked] : sRuneEngravingMgr->GetSlotRuneStates(player, slot))
            {
                std::string icon = rune->Icon.empty() ? "inv_misc_questionmark" : rune->Icon;
                // SpellId lets the addon show the real spell tooltip; Name stays
                // last as it may contain '~'.
                SendLine(player, Acore::StringFormat("RUNE~{}~{}~{}~{}~{}~{}",
                    uint32(slot), rune->RuneId, icon, locked ? 1 : 0,
                    rune->SpellId,
                    sRuneEngravingMgr->GetRuneName(*rune, player->GetSession()->GetSessionDbLocaleIndex())));
            }
        }

        if (!note.empty())
            SendLine(player, std::string("MSG~") + note);

        SendLine(player, "END");
    }
}

class rune_engraving_addon : public PlayerScript
{
public:
    rune_engraving_addon() : PlayerScript("rune_engraving_addon") {}

    void OnPlayerBeforeSendChatMessage(Player* player, uint32& /*type*/, uint32& lang, std::string& msg) override
    {
        if (!player || lang != uint32(LANG_ADDON) || !sRuneEngravingMgr->IsEnabled())
            return;

        if (msg.rfind(RUNE_WIRE_PREFIX, 0) != 0)
            return;

        std::string body = msg.substr(5); // strip "RUNE\t"
        std::vector<std::string_view> tok = Acore::Tokenize(body, '~', false);
        if (tok.empty())
            return;

        std::string_view const& cmd = tok[0];
        if (cmd == "REQ")
        {
            SendPanelState(player);
        }
        else if (cmd == "ENG" && tok.size() >= 3)
        {
            uint8 slot = uint8(Acore::StringTo<uint32>(tok[1]).value_or(RUNE_SLOT_MAX));
            uint32 runeId = Acore::StringTo<uint32>(tok[2]).value_or(0);
            EngraveResult result = sRuneEngravingMgr->Engrave(player, slot, runeId);
            // On success the client already shows its own "you have learned X"
            // notification, so only surface a status line for failures.
            SendPanelState(player, result == EngraveResult::Success ? "" : ResultText(player, result));
        }
        else if (cmd == "DEL" && tok.size() >= 2)
        {
            uint8 slot = uint8(Acore::StringTo<uint32>(tok[1]).value_or(RUNE_SLOT_MAX));
            bool removed = sRuneEngravingMgr->RemoveRune(player, slot);
            SendPanelState(player, RuneStr(player, removed ?
                RUNE_STRING_ADDON_REMOVED : RUNE_STRING_ADDON_NOTHING_TO_REMOVE));
        }

        // We've consumed this addon whisper — blank it so it isn't echoed/processed.
        msg.clear();
    }
};

void AddSC_rune_engraving_addon()
{
    new rune_engraving_addon();
}
