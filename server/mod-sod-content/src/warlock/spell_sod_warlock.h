/* Declaraciones de las runas y la configuración de brujo. */

#ifndef MODULE_SOD_WARLOCK_H
#define MODULE_SOD_WARLOCK_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodWarlockSpells
{
    SPELL_SOD_WARLOCK_UNSTABLE_AFFLICTION = 427717,
    SPELL_SOD_WARLOCK_SUMMON_FELGUARD = 427733,
    SPELL_SOD_WARLOCK_METAMORPHOSIS = 403789,
    SPELL_SOD_WARLOCK_INCINERATE = 412758,
    SPELL_SOD_WARLOCK_SHADOWFLAME = 426320,
    // Segunda tanda: estas runas no aportan C++ propio, reutilizan manejadores nativos del core
    // (spell_warl_decimation, spell_warl_everlasting_affliction y spell_warl_demonic_knowledge).
    SPELL_SOD_WARLOCK_BACKDRAFT = 427713,
    SPELL_SOD_WARLOCK_BACKDRAFT_HASTE = 427714,
    SPELL_SOD_WARLOCK_DECIMATION = 440870,
    SPELL_SOD_WARLOCK_DECIMATION_BUFF = 440873,
    SPELL_SOD_WARLOCK_DEMONIC_PACT = 425464,
    SPELL_SOD_WARLOCK_EVERLASTING_AFFLICTION = 412689,
    SPELL_SOD_WARLOCK_EVERLASTING_AFFLICTION_TRIGGER = 412698,
    SPELL_SOD_WARLOCK_DEMONIC_KNOWLEDGE = 412732,
    SPELL_SOD_WARLOCK_DEMONIC_KNOWLEDGE_PET_AURA = 900048,
    // Tercera tanda (fase 3): Soul Siphon, Shadow and Flame, Lake of Fire, Master Channeler y
    // Shadow Bolt Volley. Sólo Soul Siphon y Master Channeler necesitan C++ propio; las otras
    // tres son datos (procs y SpellMods sobre hechizos de WotLK).
    SPELL_SOD_WARLOCK_SOUL_SIPHON = 403511,
    SPELL_SOD_WARLOCK_SHADOW_AND_FLAME = 426316,
    SPELL_SOD_WARLOCK_SHADOW_AND_FLAME_BUFF = 426311,
    SPELL_SOD_WARLOCK_LAKE_OF_FIRE = 403666,
    SPELL_SOD_WARLOCK_MASTER_CHANNELER = 403668,
    SPELL_SOD_WARLOCK_SHADOW_BOLT_VOLLEY = 403628,
    // Cuarta tanda (fase 4): Gracia demoníaca, Invocación, Danza de los malditos, Venganza
    // y Aura de Inmolación. Sólo Invocación y Danza de los malditos necesitan C++ propio.
    SPELL_SOD_WARLOCK_DEMONIC_GRACE = 425463,
    SPELL_SOD_WARLOCK_VENGEANCE = 426195,
    SPELL_SOD_WARLOCK_INVOCATION = 426243,
    SPELL_SOD_WARLOCK_INVOCATION_DAMAGE = 900049,
    SPELL_SOD_WARLOCK_DANCE_OF_THE_WICKED = 412798,
    SPELL_SOD_WARLOCK_DANCE_OF_THE_WICKED_BUFF = 900050,
    SPELL_SOD_WARLOCK_IMMOLATION_AURA = 427726,
    SPELL_SOD_WARLOCK_IMMOLATION_AURA_DAMAGE = 427725,
    // Hechizos nativos de WotLK que usan los scripts de esta tanda.
    SPELL_WARLOCK_DRAIN_SOUL = 1120,
    SPELL_WARLOCK_DRAIN_LIFE = 689,
    SPELL_WARLOCK_NIGHTFALL = 18094,
    SPELL_WARLOCK_SHADOW_TRANCE = 17941,
};

void AddSC_sod_warlock_soul_siphon();
void AddSC_sod_warlock_master_channeler();
void AddSC_sod_warlock_invocation();
void AddSC_sod_warlock_dance_of_the_wicked();

inline bool SodWarlockEnabled()
{
    return sConfigMgr->GetOption<bool>("SodWarlock.Enable", true);
}

#endif // MODULE_SOD_WARLOCK_H
