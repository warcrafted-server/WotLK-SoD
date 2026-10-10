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
    SPELL_SOD_HUNTER_SERPENT_SPREAD = 425738,
    SPELL_SOD_HUNTER_SNIPER_TRAINING = 415399,
    // Mejora acumulable que concede Instrucción de francotirador (sólo cliente).
    SPELL_SOD_HUNTER_SNIPER_TRAINING_BUFF = 415401,
    // Lanzamiento instantáneo de Disparo de puntería con la acumulación máxima (sólo servidor).
    SPELL_SOD_HUNTER_SNIPER_TRAINING_INSTANT = 900058,
    SPELL_SOD_HUNTER_CARVE = 425711,
    SPELL_SOD_HUNTER_COBRA_SLAYER = 458393,
    SPELL_SOD_HUNTER_ASPECT_OF_THE_VIPER = 415423,
    // Hechizos nativos de WotLK que usan los scripts de estas runas.
    SPELL_SOD_HUNTER_GROWL = 2649,
    SPELL_SOD_HUNTER_TAUNT = 355,
    // Primera fila de cada cadena de rangos: los scripts enganchan el id negativo.
    SPELL_SOD_HUNTER_MULTI_SHOT_R1 = 2643,
    SPELL_SOD_HUNTER_SERPENT_STING_R1 = 1978,
    SPELL_SOD_HUNTER_MONGOOSE_BITE_R1 = 1495,
    SPELL_SOD_HUNTER_AIMED_SHOT = 19434,
};

void AddSC_sod_hunter_beast_mastery();
void AddSC_sod_hunter_lone_wolf();
void AddSC_sod_hunter_kill_shot();
void AddSC_sod_hunter_serpent_spread();
void AddSC_sod_hunter_sniper_training();
void AddSC_sod_hunter_carve();
void AddSC_sod_hunter_cobra_slayer();

inline bool SodHunterEnabled()
{
    return sConfigMgr->GetOption<bool>("SodHunter.Enable", true);
}

#endif // MODULE_SOD_HUNTER_H
