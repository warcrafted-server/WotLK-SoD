/* Declaraciones de los hechizos y configuración de las runas de pícaro. */

#ifndef MODULE_SOD_ROGUE_H
#define MODULE_SOD_ROGUE_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodRogueSpells
{
    SPELL_SOD_ROGUE_DEADLY_BREW = 399965,
    SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND = 400014,
    SPELL_SOD_ROGUE_QUICK_DRAW = 398196,
    SPELL_SOD_ROGUE_SLAUGHTER_FROM_THE_SHADOWS = 424925,
    SPELL_SOD_ROGUE_BETWEEN_THE_EYES = 400009,
    SPELL_SOD_ROGUE_BLADE_DANCE = 400012,
    SPELL_SOD_ROGUE_ENVENOM = 399963,
    SPELL_SOD_ROGUE_CUTTHROAT = 462708,
    SPELL_SOD_ROGUE_MAIN_GAUCHE = 424919,
    SPELL_SOD_ROGUE_SABER_SLASH = 424785,
    SPELL_SOD_ROGUE_JUST_A_FLESH_WOUND_DODGE = 900066,
    SPELL_SOD_ROGUE_BLADE_DANCE_ATTACK_POWER = 900067,
    SPELL_SOD_ROGUE_SABER_SLASH_BLEED = 900068,
    SPELL_SOD_ROGUE_SHADOWSTRIKE = 399985,
    SPELL_SOD_ROGUE_POISONED_KNIFE = 425012,
    SPELL_SOD_ROGUE_SHADOWSTEP = 400029,
    SPELL_SOD_ROGUE_SHURIKEN_TOSS = 399986,
    SPELL_SOD_ROGUE_MASTER_OF_SUBTLETY = 425096,
    SPELL_SOD_ROGUE_ROLLING_WITH_THE_PUNCHES = 400016,
    SPELL_SOD_ROGUE_ROLLING_WITH_THE_PUNCHES_HEALTH = 900069,
    SPELL_SOD_ROGUE_WAYLAY = 408700,
    SPELL_SOD_ROGUE_COMBAT_POTENCY = 432259,
    SPELL_SOD_ROGUE_FOCUSED_ATTACKS = 432256,
    SPELL_SOD_ROGUE_HONOR_AMONG_THIEVES = 432264,
    SPELL_SOD_ROGUE_HONOR_AMONG_THIEVES_TRIGGER = 432266,
    SPELL_ROGUE_DEADLY_POISON = 2818,
    SPELL_ROGUE_TAUNT = 355,
    SPELL_ROGUE_BACKSTAB = 53,
    SPELL_ROGUE_AMBUSH = 8676,
    SPELL_ROGUE_FEINT = 1966,
};

void AddSC_sod_rogue_deadly_brew();
void AddSC_sod_rogue_just_a_flesh_wound();
void AddSC_sod_rogue_quick_draw();
void AddSC_sod_rogue_slaughter_from_the_shadows();
void AddSC_sod_rogue_between_the_eyes();
void AddSC_sod_rogue_blade_dance();
void AddSC_sod_rogue_envenom();
void AddSC_sod_rogue_main_gauche();
void AddSC_sod_rogue_saber_slash();
void AddSC_sod_rogue_shadowstrike();
void AddSC_sod_rogue_poisoned_knife();
void AddSC_sod_rogue_shadowstep();
void AddSC_sod_rogue_shuriken_toss();
void AddSC_sod_rogue_master_of_subtlety();
void AddSC_sod_rogue_rolling_with_the_punches();

inline bool SodRogueEnabled()
{
    return sConfigMgr->GetOption<bool>("SodRogue.Enable", true);
}

#endif // MODULE_SOD_ROGUE_H
