/* Declaraciones de los hechizos y la configuración de las runas de cazador. */

#ifndef MODULE_SOD_HUNTER_H
#define MODULE_SOD_HUNTER_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodHunterSpells
{
    SPELL_SOD_HUNTER_BEAST_MASTERY = 409368,
    // Aura de mascota que Bestialidad recibe vía spell_pet_auras (sólo servidor).
    SPELL_SOD_HUNTER_BEAST_MASTERY_PET = 900056,
    SPELL_SOD_HUNTER_COBRA_STRIKES = 425713,
    SPELL_SOD_HUNTER_COBRA_STRIKES_BUFF = 425714,
    SPELL_SOD_HUNTER_LONE_WOLF = 415370,
    // Bono de daño que Lobo solitario aplica sin mascota activa (sólo servidor).
    SPELL_SOD_HUNTER_LONE_WOLF_DAMAGE = 900057,
    SPELL_SOD_HUNTER_FLANKING_STRIKE = 415320,
    SPELL_SOD_HUNTER_KILL_SHOT = 409593,
    // Hechizos nativos de WotLK que usan los scripts de estas runas.
    SPELL_SOD_HUNTER_GROWL = 2649,
    SPELL_SOD_HUNTER_TAUNT = 355,
};

void AddSC_sod_hunter_beast_mastery();
void AddSC_sod_hunter_lone_wolf();
void AddSC_sod_hunter_kill_shot();

inline bool SodHunterEnabled()
{
    return sConfigMgr->GetOption<bool>("SodHunter.Enable", true);
}

#endif // MODULE_SOD_HUNTER_H
