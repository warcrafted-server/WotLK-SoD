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
// incluye igual que en src/world/item_sod_world_phylactery.cpp.
#include "../mage/spell_sod_mage.h"

#include "Chat.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GameObject.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "Timer.h"

#include <mutex>
#include <unordered_map>

// Santuario de la Luna (Shrine of the Moon, 441946), en Tierras del Interior,
// parte C de la fuente real de Floración (7009022). Los datos y el texto están
// en .agents/plans/druida-fuentes/misiones.md §3 y las plantillas en
// sod_druid_efflorescence_source.sql. Mecánica (según esa fuente):
//
//   Lanzar Tranquility y después Hurricane sobre el santuario, con la misión
//   81924 activa y el objetivo del Moonkin Avatar sin cumplir, invoca al Moonkin
//   Avatar (221933) como TempSummon hostil junto al santuario. Al morir deja al
//   espíritu Sagefeather (222704) durante 60 s.
//
// El orden importa («The calm comes before the storm»): primero la calma
// (Tranquility) y solo después la tormenta (Hurricane). El disparo es la
// secuencia de hechizos, no la interacción: se engancha con un PlayerScript del
// lanzamiento de hechizo (PLAYERHOOK_ON_SPELL_CAST), porque son hechizos con
// rangos y hay que ver el destino de Hurricane (el centro del área). El
// santuario es un libro sin gossip y no dispara nada al interactuar: sin la
// misión pendiente solo dice su frase, como mensaje del sistema (el texto va en
// module_string, ver sod_druid_shrine_moon.sql).
//
// Solo se invoca con 81924 activa, el objetivo de este guardián sin cumplir y
// ningún otro avatar de este santuario vivo.
//
// La fuente no transcribe ninguna frase de Sagefeather: no se le pone
// creature_text (no se inventa).

namespace
{
enum SodDruidShrineMoon
{
    QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS = 81924,
    GO_SOD_DRUID_SHRINE_OF_THE_MOON        = 441946,
    NPC_SOD_DRUID_MOONKIN_AVATAR           = 221933,
    NPC_SOD_DRUID_SAGEFEATHER              = 222704,

    // Tranquility es un hechizo con rangos: se identifica por el primero de su
    // cadena. Hurricane se reutiliza del encabezado del módulo
    // (SPELL_DRUID_HURRICANE, primer rango 16914).
    SPELL_SOD_DRUID_TRANQUILITY            = 740,

    // Habilidades del avatar (misiones.md §3); son hechizos stock del core.
    SPELL_SOD_DRUID_REND                   = 13445,
    SPELL_SOD_DRUID_STRIKE                 = 13584,
    SPELL_SOD_DRUID_TENDON_RIP             = 3604,

    MAP_SOD_DRUID_HINTERLANDS              = 0,
};

// La frase del libro (misiones.md §3), en module_string.
constexpr uint32 STRING_SOD_DRUID_SHRINE_MOON_BOOK = 1010;

// Distancias del disparo: Hurricane debe quedar centrado a menos de 10 m del
// santuario y Tranquility se lanza a menos de 40 m de él (la fuente solo dice
// «sobre el santuario»). Los 40 m sirven además de radio con el que se busca el
// objeto desde el jugador, porque el alcance de Hurricane (30 m) cabe dentro.
constexpr float HURRICANE_DST_RANGE_YARDS = 10.0f;
constexpr float SHRINE_RANGE_YARDS        = 40.0f;

// Un solo avatar vivo a la vez por santuario: se mira si hay alguno en el
// entorno inmediato del objeto.
constexpr float AVATAR_PRESENCE_RANGE_YARDS = 15.0f;

// El avatar se queda como máximo cinco minutos si el jugador huye; su cuerpo
// desaparece en cuanto muere (el espíritu ya ha aparecido en JustDied).
constexpr uint32 AVATAR_DESPAWN_MS = 5 * 60 * 1000;

// El espíritu dura 60 s (misiones.md §3).
constexpr uint32 SPIRIT_DESPAWN_MS = 60 * 1000;

// Ventana entre la calma y la tormenta: el canal de Tranquility dura 8 s y no
// se puede lanzar Hurricane mientras se canaliza, así que la ventana debe cubrir
// ese hueco. El valor (30 s) es provisional: la fuente no da ninguno.
constexpr uint32 CALM_TO_STORM_WINDOW_MS = 30 * 1000;

// Reutilización de las habilidades del avatar. No consta en la fuente: son
// provisionales.
constexpr uint32 REND_COOLDOWN_MS = 10 * 1000;
constexpr uint32 STRIKE_COOLDOWN_MS = 6 * 1000;
constexpr uint32 TENDON_RIP_COOLDOWN_MS = 15 * 1000;

// La misión está activa y el objetivo de ESTE guardián sigue sin cumplir. Los
// tres objetivos de 81924 son créditos de muerte, de uno en uno, así que basta
// con leer el contador del objetivo del Moonkin Avatar.
bool ShrineMoonQuestPending(Player* player)
{
    if (!player || player->GetQuestStatus(QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS)
            != QUEST_STATUS_INCOMPLETE)
        return false;

    return player->GetReqKillOrCastCurrentCount(
        QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS, NPC_SOD_DRUID_MOONKIN_AVATAR) == 0;
}

// Invoca al avatar en la posición del santuario. No comprueba la misión: quien
// llama ya lo ha hecho.
void SummonMoonkinAvatar(Player* player, WorldObject* shrine)
{
    if (!player || !shrine)
        return;

    // Un solo avatar vivo a la vez por santuario (la tarea solo pide eso; el
    // cadáver del anterior no impide invocar otro).
    if (shrine->FindNearestCreature(NPC_SOD_DRUID_MOONKIN_AVATAR, AVATAR_PRESENCE_RANGE_YARDS, true))
        return;

    TempSummon* avatar = shrine->SummonCreature(NPC_SOD_DRUID_MOONKIN_AVATAR,
        shrine->GetPositionX(), shrine->GetPositionY(), shrine->GetPositionZ(),
        shrine->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, AVATAR_DESPAWN_MS);
    if (avatar && avatar->AI())
        avatar->AI()->AttackStart(player);
}

// Engancha el AI del avatar por entry. La plantilla 221933 se creó sin
// ScriptName (sod_druid_efflorescence_source.sql), así que un
// RegisterCreatureAI nunca la encontraría.
struct npc_sod_druid_moonkin_avatar : public ScriptedAI
{
    npc_sod_druid_moonkin_avatar(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        // Rend se aplica en el primer golpe y luego se refresca.
        _rendTimer = 0;
        _strikeTimer = STRIKE_COOLDOWN_MS;
        _tendonRipTimer = TENDON_RIP_COOLDOWN_MS;
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

        if (_strikeTimer <= diff)
        {
            DoCastVictim(SPELL_SOD_DRUID_STRIKE);
            _strikeTimer = STRIKE_COOLDOWN_MS;
        }
        else
        {
            _strikeTimer -= diff;
        }

        if (_tendonRipTimer <= diff)
        {
            DoCastVictim(SPELL_SOD_DRUID_TENDON_RIP);
            _tendonRipTimer = TENDON_RIP_COOLDOWN_MS;
        }
        else
        {
            _tendonRipTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->SummonCreature(NPC_SOD_DRUID_SAGEFEATHER,
            me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(),
            TEMPSUMMON_TIMED_DESPAWN, SPIRIT_DESPAWN_MS);
    }

private:
    uint32 _rendTimer = 0;
    uint32 _strikeTimer = STRIKE_COOLDOWN_MS;
    uint32 _tendonRipTimer = TENDON_RIP_COOLDOWN_MS;
};

class sod_druid_shrine_moon_creature_ai : public AllCreatureScript
{
public:
    sod_druid_shrine_moon_creature_ai()
        : AllCreatureScript("sod_druid_shrine_moon_creature_ai") { }

    CreatureAI* GetCreatureAI(Creature* creature) const override
    {
        if (creature && SodDruidEnabled() && creature->GetEntry() == NPC_SOD_DRUID_MOONKIN_AVATAR)
            return new npc_sod_druid_moonkin_avatar(creature);

        return nullptr;
    }
};
}

// 441946: el santuario. El ScriptName de la plantilla de la parte A ya es
// «sod_druid_shrine_moon», así que el nombre del GameObjectScript está fijado
// por esa fila y no puede ser el habitual «go_...». No es el disparador de la
// invocación (lo es la secuencia de hechizos): sin la misión pendiente el libro
// solo dice su frase, como mensaje del sistema.
class go_sod_druid_shrine_moon : public GameObjectScript
{
public:
    go_sod_druid_shrine_moon() : GameObjectScript("sod_druid_shrine_moon") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (!player || !SodDruidEnabled())
            return false; // módulo apagado: el santuario queda inerte

        if (!ShrineMoonQuestPending(player))
            ChatHandler(player->GetSession()).SendSysMessage(
                SodStr(player, STRING_SOD_DRUID_SHRINE_MOON_BOOK));

        return true;
    }
};

// La secuencia de invocación. Tranquility («la calma») deja una marca por
// jugador solo si se lanza junto al santuario; Hurricane («la tormenta») la
// consume y, si la marca es reciente, invoca al avatar. Se identifica cada
// hechizo por el primero de su cadena, así que cualquier rango vale.
class player_sod_druid_shrine_moon : public PlayerScript
{
public:
    player_sod_druid_shrine_moon()
        : PlayerScript("player_sod_druid_shrine_moon",
            { PLAYERHOOK_ON_SPELL_CAST, PLAYERHOOK_ON_LOGOUT }) { }

    void OnPlayerSpellCast(Player* player, Spell* spell, bool /*skipCheck*/) override
    {
        if (!player || !spell || !SodDruidEnabled())
            return;

        SpellInfo const* spellInfo = spell->GetSpellInfo();
        if (!spellInfo)
            return;

        // El santuario solo existe en el mapa de Tierras del Interior: fuera de
        // él (o sin la misión pendiente) no hay nada que llevar.
        if (player->GetMapId() != MAP_SOD_DRUID_HINTERLANDS || !ShrineMoonQuestPending(player))
        {
            std::lock_guard<std::mutex> guard(_calmCastMutex);
            _calmCastMs.erase(player->GetGUID());
            return;
        }

        uint32 const firstInChain = sSpellMgr->GetFirstSpellInChain(spellInfo->Id);

        if (firstInChain == SPELL_SOD_DRUID_TRANQUILITY)
        {
            // «La calma»: solo cuenta si el jugador está lo bastante cerca del
            // santuario.
            if (player->FindNearestGameObject(GO_SOD_DRUID_SHRINE_OF_THE_MOON, SHRINE_RANGE_YARDS))
            {
                std::lock_guard<std::mutex> guard(_calmCastMutex);
                _calmCastMs[player->GetGUID()] = getMSTime();
            }
            return;
        }

        if (firstInChain != SPELL_DRUID_HURRICANE)
            return;

        // «La tormenta»: cierra la secuencia, aunque no llegue a invocar.
        uint32 calmMs;
        {
            std::lock_guard<std::mutex> guard(_calmCastMutex);
            auto it = _calmCastMs.find(player->GetGUID());
            if (it == _calmCastMs.end())
                return;

            calmMs = it->second;
            _calmCastMs.erase(it);
        }

        if (getMSTimeDiff(calmMs, getMSTime()) > CALM_TO_STORM_WINDOW_MS)
            return;

        GameObject* shrine = player->FindNearestGameObject(
            GO_SOD_DRUID_SHRINE_OF_THE_MOON, SHRINE_RANGE_YARDS);
        if (!shrine)
            return;

        // «Sobre el santuario»: Hurricane es un área en el suelo, así que su
        // centro es el destino del hechizo y tiene que caer a menos de 10 m del
        // objeto. Si el hechizo no llevase destino, se usa la posición del
        // jugador.
        WorldLocation const* dst = spell->m_targets.GetDstPos();
        float const centerDistance = dst ? dst->GetExactDist2d(shrine) : player->GetExactDist2d(shrine);
        if (centerDistance > HURRICANE_DST_RANGE_YARDS)
            return;

        SummonMoonkinAvatar(player, shrine);
    }

    void OnPlayerLogout(Player* player) override
    {
        if (!player)
            return;

        std::lock_guard<std::mutex> guard(_calmCastMutex);
        _calmCastMs.erase(player->GetGUID());
    }

private:
    std::unordered_map<ObjectGuid, uint32> _calmCastMs;
    // El lanzamiento corre en el hilo del mapa y el cierre de sesión en el del
    // mundo (igual que en el santuario del Celador).
    std::mutex _calmCastMutex;
};

void AddSC_sod_druid_shrine_moon()
{
    new go_sod_druid_shrine_moon();
    new sod_druid_shrine_moon_creature_ai();
    new player_sod_druid_shrine_moon();
}
