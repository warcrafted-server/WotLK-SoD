/* Declaraciones de las runas y la configuración de brujo. */

#ifndef MODULE_SOD_WARLOCK_H
#define MODULE_SOD_WARLOCK_H

#include "Config.h"

enum SodWarlockSpells
{
    SPELL_SOD_WARLOCK_UNSTABLE_AFFLICTION = 427717,
    SPELL_SOD_WARLOCK_SUMMON_FELGUARD = 427733,
    SPELL_SOD_WARLOCK_METAMORPHOSIS = 403789,
    SPELL_SOD_WARLOCK_INCINERATE = 412758,
    SPELL_SOD_WARLOCK_SHADOWFLAME = 426320,
};

inline bool SodWarlockEnabled()
{
    return sConfigMgr->GetOption<bool>("SodWarlock.Enable", true);
}

#endif // MODULE_SOD_WARLOCK_H
