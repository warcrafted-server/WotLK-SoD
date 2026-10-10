/* Declaraciones de los hechizos y la configuración de las runas de guerrero. */

#ifndef MODULE_SOD_WARRIOR_H
#define MODULE_SOD_WARRIOR_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodWarriorSpells
{
    SPELL_SOD_WARRIOR_BLOOD_FRENZY = 412507,
    SPELL_SOD_WARRIOR_FLAGELLATION = 402877,
    SPELL_SOD_WARRIOR_RAGING_BLOW = 402911,
    SPELL_SOD_WARRIOR_WARBRINGER = 425421,
    SPELL_SOD_WARRIOR_COMMANDING_SHOUT = 403215,
    SPELL_SOD_WARRIOR_CONSUMED_BY_RAGE = 425418,
    SPELL_SOD_WARRIOR_FRENZIED_ASSAULT = 425412,
    SPELL_SOD_WARRIOR_FRENZIED_ASSAULT_HASTE = 900052,
    SPELL_SOD_WARRIOR_FURIOUS_THUNDER = 403219,
    SPELL_SOD_WARRIOR_MEATHOOK = 403228,
    SPELL_SOD_WARRIOR_QUICK_STRIKE = 429765,
    SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY = 413404,
    SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_SPEED = 430472,
    SPELL_SOD_WARRIOR_SINGLE_MINDED_FURY_HASTE = 461470,
    // Hechizos nativos de WotLK que enganchan los scripts de esta tanda.
    SPELL_WARRIOR_REND = 772,
    SPELL_WARRIOR_CHARGE = 100,
    SPELL_WARRIOR_INTERCEPT = 20616,
    SPELL_WARRIOR_INTERVENE = 3411,
    SPELL_WARRIOR_ENRAGE = 12880,
    SPELL_WARRIOR_BERSERKER_RAGE = 18499,
    SPELL_WARRIOR_BLOODRAGE = 29131,
};

void AddSC_sod_warrior_blood_frenzy();
void AddSC_sod_warrior_flagellation();
void AddSC_sod_warrior_raging_blow();
void AddSC_sod_warrior_warbringer();
void AddSC_sod_warrior_consumed_by_rage();
void AddSC_sod_warrior_frenzied_assault();
void AddSC_sod_warrior_meathook();
void AddSC_sod_warrior_quick_strike();
void AddSC_sod_warrior_single_minded_fury();

inline bool SodWarriorEnabled()
{
    return sConfigMgr->GetOption<bool>("SodWarrior.Enable", true);
}

#endif // MODULE_SOD_WARRIOR_H
