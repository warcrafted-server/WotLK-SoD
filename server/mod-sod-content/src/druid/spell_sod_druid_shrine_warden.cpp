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

#include "Creature.h"
#include "CreatureAI.h"
#include "GameObject.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
#include "TemporarySummon.h"

#include <mutex>
#include <unordered_map>

// Santuario del Celador (Shrine of the Warden, 441948), en Feralas, parte B de la
// fuente real de Floración (7009022). Los datos y los textos están en
// .agents/plans/druida-fuentes/misiones.md §3 y las plantillas en
// sod_druid_efflorescence_source.sql. Mecánica (según esa fuente):
//
//   1. Interactuar con el santuario con la misión 81924 activa aplica «Duty of
//      the Warden» (446448).
//   2. Con ese buff, curarse una maldición Y un veneno (en cualquier orden) lo
//      transforma en «Mark of the Warden» (446467). No importa qué hechizo haga
//      el dispel: se cuenta cualquier aura de tipo maldición o veneno que el
//      jugador pierda por dispensa mientras tiene Duty.
//   3. Con Mark, acercarse al santuario o interactuar de nuevo invoca al Treant
//      Avatar (221935) como TempSummon hostil junto al santuario. Al morir deja
//      al espíritu Blightbark (222705) durante 60 s.
//
// Solo se invoca con 81924 activa, el objetivo de este guardián sin cumplir y
// ningún otro avatar de este santuario vivo.
//
// La fuente no da las frases de Blightbark: no se le pone texto (no se inventa).

namespace
{
enum SodDruidShrineWarden
{
    QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS = 81924,
    GO_SOD_DRUID_SHRINE_OF_THE_WARDEN       = 441948,
    NPC_SOD_DRUID_TREANT_AVATAR             = 221935,
    NPC_SOD_DRUID_BLIGHTBARK                = 222705,

    SPELL_SOD_DRUID_DUTY_OF_THE_WARDEN      = 446448,
    SPELL_SOD_DRUID_MARK_OF_THE_WARDEN      = 446467,
    SPELL_SOD_DRUID_ENTANGLING_ROOTS        = 11922,

    MAP_SOD_DRUID_FERALAS                   = 1,
};

// Radio para encontrar el santuario y para no acumular avatares: el avatar
// aparece «junto al santuario» (misiones.md §3), igual que en el resto del módulo.
constexpr float SHRINE_WARDEN_RANGE_YARDS = 15.0f;

// El avatar se queda como máximo cinco minutos si el jugador huye; su cuerpo
// desaparece en cuanto muere (el espíritu ya ha aparecido en JustDied).
constexpr uint32 AVATAR_DESPAWN_MS = 5 * 60 * 1000;

// El espíritu dura 60 s (misiones.md §3).
constexpr uint32 SPIRIT_DESPAWN_MS = 60 * 1000;

// Reutilización de Enredaderas (11922) del avatar.
constexpr uint32 ROOTS_COOLDOWN_MS = 6 * 1000;

// Cada cuánto se comprueba, como mucho, la cercanía al santuario.
constexpr uint32 PROXIMITY_CHECK_MS = 1000;

// Bit 1: ya se ha curado una maldición con Duty activo. Bit 2: un veneno.
constexpr uint8 WARDEN_CLEANSED_CURSE  = 0x1;
constexpr uint8 WARDEN_CLEANSED_POISON = 0x2;

std::unordered_map<ObjectGuid, uint8> sWardenCleansed;
std::mutex sWardenCleansedMutex;

// La misión está activa y el objetivo de ESTE guardián sigue sin cumplir. Los
// tres objetivos de 81924 son créditos de muerte, de uno en uno, así que basta
// con leer el contador del objetivo del Treant Avatar.
bool ShrineWardenQuestPending(Player* player)
{
    if (!player || player->GetQuestStatus(QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS)
            != QUEST_STATUS_INCOMPLETE)
        return false;

    return player->GetReqKillOrCastCurrentCount(
        QUEST_SOD_DRUID_WISDOM_OF_THE_GUARDIANS, NPC_SOD_DRUID_TREANT_AVATAR) == 0;
}

void ResetWardenCleansed(ObjectGuid guid)
{
    std::lock_guard<std::mutex> guard(sWardenCleansedMutex);
    sWardenCleansed.erase(guid);
}

// Invoca al avatar en la posición del santuario (o del jugador). No comprueba la
// misión: quien llama ya lo ha hecho.
void SummonTreantAvatar(Player* player, WorldObject* source)
{
    if (!player || !source)
        return;

    // Un solo avatar vivo a la vez por santuario (la tarea solo pide eso; el
    // cadáver del anterior no impide invocar otro).
    if (source->FindNearestCreature(NPC_SOD_DRUID_TREANT_AVATAR, SHRINE_WARDEN_RANGE_YARDS, true))
        return;

    TempSummon* avatar = source->SummonCreature(NPC_SOD_DRUID_TREANT_AVATAR,
        source->GetPositionX(), source->GetPositionY(), source->GetPositionZ(),
        source->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, AVATAR_DESPAWN_MS);
    if (avatar && avatar->AI())
        avatar->AI()->AttackStart(player);
}

// 221935: el avatar. Hostil y de golpe cuerpo a cuerpo; lanza Enredaderas (11922)
// y al morir deja al espíritu de Blightbark. El AI se engancha por entry (la
// plantilla de la parte A no lleva ScriptName), con un AllCreatureScript.
struct npc_sod_druid_treant_avatar : public ScriptedAI
{
    npc_sod_druid_treant_avatar(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _rootsTimer = ROOTS_COOLDOWN_MS;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (_rootsTimer <= diff)
        {
            DoCastVictim(SPELL_SOD_DRUID_ENTANGLING_ROOTS);
            _rootsTimer = ROOTS_COOLDOWN_MS;
        }
        else
        {
            _rootsTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->SummonCreature(NPC_SOD_DRUID_BLIGHTBARK,
            me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(),
            TEMPSUMMON_TIMED_DESPAWN, SPIRIT_DESPAWN_MS);
    }

private:
    uint32 _rootsTimer = ROOTS_COOLDOWN_MS;
};

// Engancha el AI del avatar por entry. La plantilla 221935 se creó sin
// ScriptName (sod_druid_efflorescence_source.sql), así que un
// RegisterCreatureAI nunca la encontraría.
class sod_druid_shrine_warden_creature_ai : public AllCreatureScript
{
public:
    sod_druid_shrine_warden_creature_ai()
        : AllCreatureScript("sod_druid_shrine_warden_creature_ai") { }

    CreatureAI* GetCreatureAI(Creature* creature) const override
    {
        if (creature && SodDruidEnabled() && creature->GetEntry() == NPC_SOD_DRUID_TREANT_AVATAR)
            return new npc_sod_druid_treant_avatar(creature);

        return nullptr;
    }
};
}

// 441948: el santuario. El ScriptName de la plantilla de la parte A ya es
// «sod_druid_shrine_warden», así que el nombre del GameObjectScript está fijado
// por esa fila y no puede ser el habitual «go_...».
class go_sod_druid_shrine_warden : public GameObjectScript
{
public:
    go_sod_druid_shrine_warden() : GameObjectScript("sod_druid_shrine_warden") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player || !go)
            return false;

        if (!SodDruidEnabled())
            return false; // módulo apagado: el santuario queda inerte

        if (!ShrineWardenQuestPending(player))
            return false; // sin la misión activa, el santuario no hace nada

        if (player->HasAura(SPELL_SOD_DRUID_MARK_OF_THE_WARDEN))
        {
            SummonTreantAvatar(player, go);
            return true;
        }

        // Aún sin Marca: (re)aplica el Deber y reinicia su progreso de dispensa.
        ResetWardenCleansed(player->GetGUID());
        player->AddAura(SPELL_SOD_DRUID_DUTY_OF_THE_WARDEN, player);
        return true;
    }
};

// Transforma «Duty of the Warden» en «Mark of the Warden» cuando el jugador se
// quita de encima, estando bajo Duty, una maldición y un veneno. Se cuenta
// cualquier dispensa (el hechizo que la haga es indiferente): toda aura de tipo
// maldición o veneno que se va con AURA_REMOVE_BY_ENEMY_SPELL. Se exige una de
// cada tipo, y el orden da igual, por eso se guardan dos bits por jugador.
class unit_sod_druid_shrine_warden : public UnitScript
{
public:
    unit_sod_druid_shrine_warden()
        : UnitScript("unit_sod_druid_shrine_warden", true, { UNITHOOK_ON_AURA_REMOVE }) { }

    void OnAuraRemove(Unit* unit, AuraApplication* aurApp, AuraRemoveMode mode) override
    {
        if (!SodDruidEnabled() || !unit || !aurApp || !aurApp->GetBase())
            return;

        Player* player = unit->ToPlayer();
        if (!player)
            return;

        Aura* aura = aurApp->GetBase();

        // Al perder Duty (por transformación, expiración o muerte) se reinicia el
        // progreso: no debe valer una dispensa hecha con el buff anterior.
        if (aura->GetId() == SPELL_SOD_DRUID_DUTY_OF_THE_WARDEN)
        {
            ResetWardenCleansed(player->GetGUID());
            return;
        }

        if (mode != AURA_REMOVE_BY_ENEMY_SPELL) // solo dispensa, no expiración ni muerte
            return;

        SpellInfo const* spellInfo = aura->GetSpellInfo();
        if (!spellInfo || !player->HasAura(SPELL_SOD_DRUID_DUTY_OF_THE_WARDEN))
            return;

        uint8 bit = 0;
        if (spellInfo->Dispel == DISPEL_CURSE)
            bit = WARDEN_CLEANSED_CURSE;
        else if (spellInfo->Dispel == DISPEL_POISON)
            bit = WARDEN_CLEANSED_POISON;

        if (!bit)
            return;

        bool complete;
        {
            std::lock_guard<std::mutex> guard(sWardenCleansedMutex);
            uint8& cleansed = sWardenCleansed[player->GetGUID()];
            cleansed |= bit;
            complete = cleansed == (WARDEN_CLEANSED_CURSE | WARDEN_CLEANSED_POISON);
        }

        if (!complete)
            return;

        ResetWardenCleansed(player->GetGUID());
        player->RemoveAurasDueToSpell(SPELL_SOD_DRUID_DUTY_OF_THE_WARDEN);
        player->AddAura(SPELL_SOD_DRUID_MARK_OF_THE_WARDEN, player);
    }
};

// Acercarse al santuario con la Marca también invoca al avatar (misiones.md §3).
// Se comprueba por jugador y como mucho una vez por segundo. El santuario solo
// existe en el mapa de Feralas, así que basta con mirar ahí: la distancia de 15 m
// ya garantiza que el jugador está junto a él, y no se da por buena una zona
// concreta del mapa (no consta cuál resuelve el terreno en ese punto).
class player_sod_druid_shrine_warden : public PlayerScript
{
public:
    player_sod_druid_shrine_warden()
        : PlayerScript("player_sod_druid_shrine_warden",
            { PLAYERHOOK_ON_UPDATE, PLAYERHOOK_ON_LOGOUT }) { }

    void OnPlayerUpdate(Player* player, uint32 diff) override
    {
        if (!player || !SodDruidEnabled())
            return;

        if (!player->HasAura(SPELL_SOD_DRUID_MARK_OF_THE_WARDEN))
        {
            _checkTimers.erase(player->GetGUID());
            return;
        }

        if (player->GetMapId() != MAP_SOD_DRUID_FERALAS || !ShrineWardenQuestPending(player))
        {
            _checkTimers.erase(player->GetGUID());
            return;
        }

        uint32& timer = _checkTimers[player->GetGUID()];
        timer += diff;
        if (timer < PROXIMITY_CHECK_MS)
            return;

        timer = 0;

        if (GameObject* shrine = player->FindNearestGameObject(
                GO_SOD_DRUID_SHRINE_OF_THE_WARDEN, SHRINE_WARDEN_RANGE_YARDS))
            SummonTreantAvatar(player, shrine);
    }

    void OnPlayerLogout(Player* player) override
    {
        if (!player)
            return;

        _checkTimers.erase(player->GetGUID());
        ResetWardenCleansed(player->GetGUID());
    }

private:
    std::unordered_map<ObjectGuid, uint32> _checkTimers;
};

void AddSC_sod_druid_shrine_warden()
{
    new go_sod_druid_shrine_warden();
    new sod_druid_shrine_warden_creature_ai();
    new unit_sod_druid_shrine_warden();
    new player_sod_druid_shrine_warden();
}
