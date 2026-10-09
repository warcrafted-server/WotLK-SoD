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
};

inline bool SodWarlockEnabled()
{
    return sConfigMgr->GetOption<bool>("SodWarlock.Enable", true);
}

#endif // MODULE_SOD_WARLOCK_H
