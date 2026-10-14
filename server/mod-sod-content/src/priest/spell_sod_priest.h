/* Declaraciones de hechizos y configuración de las runas de sacerdote. */

#ifndef MODULE_SOD_PRIEST_H
#define MODULE_SOD_PRIEST_H

#include "Config.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

enum SodPriestSpells
{
    SPELL_SOD_PRIEST_SERENDIPITY = 413248,
    SPELL_SOD_PRIEST_SERENDIPITY_BUFF = 413247,
    SPELL_SOD_PRIEST_STRENGTH_OF_SOUL = 415739,
    SPELL_SOD_PRIEST_TWISTED_FAITH = 425198,
    SPELL_SOD_PRIEST_HOMUNCULI = 402799,
    SPELL_SOD_PRIEST_PRAYER_OF_MENDING = 401859,
    SPELL_SOD_PRIEST_SHARED_PAIN = 401969,
    SPELL_SOD_PRIEST_MIND_SEAR = 413259,
    SPELL_SOD_PRIEST_SHADOW_WORD_DEATH = 401955,
    SPELL_SOD_PRIEST_EMPOWERED_RENEW = 425266,
    SPELL_SOD_PRIEST_MIND_SPIKE = 431655,
    SPELL_SOD_PRIEST_RENEWED_HOPE = 425280,
    SPELL_SOD_PRIEST_DISPERSION = 425294,
    SPELL_SOD_PRIEST_PAIN_SUPPRESSION = 402004,
    SPELL_SOD_PRIEST_SPIRIT_OF_THE_REDEEMER = 425284,
    SPELL_SOD_PRIEST_VOID_PLAGUE = 425204,
    SPELL_SOD_PRIEST_WEAKENED_SOUL = 6788,
    SPELL_SOD_PRIEST_SPIRIT_OF_REDEMPTION_TALENT = 20711,
};

void AddSC_sod_priest_shared_pain();
void AddSC_sod_priest_empowered_renew();
void AddSC_sod_priest_mind_spike();
void AddSC_sod_priest_renewed_hope();
void AddSC_sod_priest_spirit_of_the_redeemer();

inline bool SodPriestEnabled()
{
    return sConfigMgr->GetOption<bool>("SodPriest.Enable", true);
}

#endif // MODULE_SOD_PRIEST_H
