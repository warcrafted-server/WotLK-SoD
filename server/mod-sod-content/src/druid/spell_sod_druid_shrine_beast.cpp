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

#include "spell_sod_druid.h"

// El C++ del módulo no guarda textos para el jugador: todos salen de
// module_string. El ayudante de cadenas vive en la cabecera del mago y se
// incluye igual que en src/druid/spell_sod_druid_shrine_moon.cpp.
#include "../mage/spell_sod_mage.h"

#include "Chat.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GameObject.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "TemporarySummon.h"

// Santuario de la Bestia (Shrine of the Beast, 441947), en Azshara, parte D de
// la fuente real de Floración (7009022). Los datos y el texto están en
// .agents/plans/druida-fuentes/misiones.md §3 y las plantillas en
// sod_druid_efflorescence_source.sql. Mecánica (según esa fuente):
//
//   Con la misión 81924 activa y el objetivo del Hippogryph Avatar sin cumplir,
//   presentar el Sacred Stag Heart (221326) en el santuario (interactuar
//   teniéndolo en la mochila) consume el objeto e invoca al Hippogryph Avatar
//   (221928) como TempSummon hostil junto al santuario. Al morir deja al
//   espíritu Whisperwing (222703) durante 60 s.
//
// El corazón lo suelta el Child of Apa'ro (222580), que ya existe en la parte A.
// El disparo es la propia interacción (OnGossipHello), porque el santuario es un
// libro sin gossip: sin el corazón (o sin la misión pendiente) solo dice su
// frase, «Hunt the white stag with tooth and claw.», como mensaje del sistema
// (el texto va en module_string, ver sod_druid_shrine_beast.sql).
//
// Solo se invoca con 81924 activa, el objetivo de este guardián sin cumplir y
// ningún otro avatar de este santuario vivo. Si ya hay uno vivo no se gasta el
// corazón.
//
// La fuente no transcribe ninguna frase de Whisperwing: no se le pone
// creature_text (no se inventa).

namespace
{
enum SodDruidShrineBeast
{
    QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS = 81924,
    NPC_SOD_DRUID_HIPPOGRYPH_AVATAR         = 221928,
    NPC_SOD_DRUID_WHISPERWING               = 222703,

    ITEM_SOD_DRUID_SACRED_STAG_HEART        = 221326,

    // Habilidad del avatar (misiones.md §3); es un hechizo stock del core.
    SPELL_SOD_DRUID_REND                    = 13445,
};

// La frase del libro (misiones.md §3), en module_string.
constexpr uint32 STRING_SOD_DRUID_SHRINE_BEAST_BOOK = 1011;

// Un solo avatar vivo a la vez por santuario: se mira si hay alguno en el
// entorno inmediato del objeto. Sirve además como radio de la ofrenda: el
// avatar aparece «junto al santuario».
constexpr float SHRINE_BEAST_RANGE_YARDS = 15.0f;

// El avatar se queda como máximo cinco minutos si el jugador huye; su cuerpo
// desaparece en cuanto muere (el espíritu ya ha aparecido en JustDied).
constexpr uint32 AVATAR_DESPAWN_MS = 5 * 60 * 1000;

// El espíritu dura 60 s (misiones.md §3).
constexpr uint32 SPIRIT_DESPAWN_MS = 60 * 1000;

// Reutilización de Rend (13445) del avatar. No consta en la fuente: es
// provisional, igual que en las partes B y C.
constexpr uint32 REND_COOLDOWN_MS = 10 * 1000;

// La misión está activa y el objetivo de ESTE guardián sigue sin cumplir. Los
// tres objetivos de 81924 son créditos de muerte, de uno en uno, así que basta
// con leer el contador del objetivo del Hippogryph Avatar.
bool ShrineBeastQuestPending(Player* player)
{
    if (!player || player->GetQuestStatus(QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS)
            != QUEST_STATUS_INCOMPLETE)
        return false;

    return player->GetReqKillOrCastCurrentCount(
        QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS, NPC_SOD_DRUID_HIPPOGRYPH_AVATAR) == 0;
}

void ShowShrineBeastBook(Player* player)
{
    ChatHandler(player->GetSession()).SendSysMessage(
        SodStr(player, STRING_SOD_DRUID_SHRINE_BEAST_BOOK));
}

// Invoca al avatar en la posición del santuario y devuelve si lo ha hecho. No
// comprueba la misión ni el corazón: quien llama ya lo ha hecho.
bool SummonHippogryphAvatar(Player* player, WorldObject* shrine)
{
    if (!player || !shrine)
        return false;

    // Un solo avatar vivo a la vez por santuario (la tarea solo pide eso; el
    // cadáver del anterior no impide invocar otro).
    if (shrine->FindNearestCreature(NPC_SOD_DRUID_HIPPOGRYPH_AVATAR, SHRINE_BEAST_RANGE_YARDS, true))
        return false;

    TempSummon* avatar = shrine->SummonCreature(NPC_SOD_DRUID_HIPPOGRYPH_AVATAR,
        shrine->GetPositionX(), shrine->GetPositionY(), shrine->GetPositionZ(),
        shrine->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, AVATAR_DESPAWN_MS);
    if (!avatar)
        return false;

    if (avatar->AI())
        avatar->AI()->AttackStart(player);

    return true;
}

// 221928: el avatar. Hostil y de golpe cuerpo a cuerpo; lanza Desgarrar (13445)
// y al morir deja al espíritu de Whisperwing. El AI se engancha por entry (la
// plantilla de la parte A no lleva ScriptName), con un AllCreatureScript.
struct npc_sod_druid_hippogryph_avatar : public ScriptedAI
{
    npc_sod_druid_hippogryph_avatar(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        // Rend se aplica en el primer golpe y luego se refresca.
        _rendTimer = 0;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (_rendTimer <= diff)
        {
            DoCastVictim(SPELL_SOD_DRUID_REND);
            _rendTimer = REND_COOLDOWN_MS;
        }
        else
        {
            _rendTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->SummonCreature(NPC_SOD_DRUID_WHISPERWING,
            me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(),
            TEMPSUMMON_TIMED_DESPAWN, SPIRIT_DESPAWN_MS);
    }

private:
    uint32 _rendTimer = 0;
};

// Engancha el AI del avatar por entry. La plantilla 221928 se creó sin
// ScriptName (sod_druid_efflorescence_source.sql), así que un
// RegisterCreatureAI nunca la encontraría.
class sod_druid_shrine_beast_creature_ai : public AllCreatureScript
{
public:
    sod_druid_shrine_beast_creature_ai()
        : AllCreatureScript("sod_druid_shrine_beast_creature_ai") { }

    CreatureAI* GetCreatureAI(Creature* creature) const override
    {
        if (creature && SodDruidEnabled() && creature->GetEntry() == NPC_SOD_DRUID_HIPPOGRYPH_AVATAR)
            return new npc_sod_druid_hippogryph_avatar(creature);

        return nullptr;
    }
};
}

// 441947: el santuario. El ScriptName de la plantilla de la parte A ya es
// «sod_druid_shrine_beast», así que el nombre del GameObjectScript está fijado
// por esa fila. Interactuar con el corazón y la misión pendiente consume el
// objeto e invoca al avatar; en cualquier otro caso solo muestra la frase del
// libro.
class go_sod_druid_shrine_beast : public GameObjectScript
{
public:
    go_sod_druid_shrine_beast() : GameObjectScript("sod_druid_shrine_beast") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player || !go)
            return false;

        if (!SodDruidEnabled())
            return false; // módulo apagado: el santuario queda inerte

        // Sin la misión pendiente o sin el corazón no hay ofrenda que presentar.
        if (!ShrineBeastQuestPending(player)
                || !player->HasItemCount(ITEM_SOD_DRUID_SACRED_STAG_HEART, 1, false))
        {
            ShowShrineBeastBook(player);
            return true;
        }

        // Si ya hay un avatar vivo la ofrenda no se gasta: solo se repite la
        // frase del libro.
        if (!SummonHippogryphAvatar(player, go))
        {
            ShowShrineBeastBook(player);
            return true;
        }

        player->DestroyItemCount(ITEM_SOD_DRUID_SACRED_STAG_HEART, 1, true);
        return true;
    }
};

void AddSC_sod_druid_shrine_beast()
{
    new go_sod_druid_shrine_beast();
    new sod_druid_shrine_beast_creature_ai();
}
