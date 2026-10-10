#!/usr/bin/env python3
"""Warlock spell specs for the consolidated SoD client and server data."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)

SKILL_AFFLICTION = 355
SKILL_DEMONOLOGY = 354
SKILL_DESTRUCTION = 593
TARGET_UNIT_PET = 5


def build(idx):
    """Return Warlock spells cloned from the level-80 WotLK talent ranks."""
    cast_instant = idx["cast"][0]
    duration_15000 = idx["dur"][15000]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    icon_demonic_tactics = idx["icon"]["spell_shadow_demonictactics"]

    return [
        {  # Chaos Bolt: retain WotLK rank effects; apply the confirmed SoD cooldown.
            "id": 403629, "client": True, "template": 59172,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Chaos Bolt", "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 12000,
                "SpellLevel": 0,
                "SchoolMask": 124,
            },
        },
        {  # Haunt: preserve the WotLK dummy aura expected by spell_warl_haunt.
            "id": 403501, "client": True, "template": 59164,
            "skill_line": SKILL_AFFLICTION,
            "name": "Haunt", "script": "spell_warl_haunt",
            "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "overrides": {
                "CastingTimeIndex": cast_instant,
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 12000,
                "DurationIndex": duration_15000,
                "SpellLevel": 0,
            },
        },
        {  # Demonic Tactics: preserve the WotLK rank-5 effects and also target the pet.
            "id": 412727, "client": True, "template": 30248,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Demonic Tactics", "inherit_server": True,
            "desc": "Increases the melee and spell critical strike chance of you and your pet by 10%.",
            "aura_desc": "Increases the melee and spell critical strike chance of you and your pet by 10%.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SpellIconID": icon_demonic_tactics,
                "SpellLevel": 0,
                "ImplicitTargetB_1": TARGET_UNIT_PET,
                "ImplicitTargetB_2": TARGET_UNIT_PET,
                "ImplicitTargetB_3": TARGET_UNIT_PET,
            },
        },
        {  # Aflicción inestable conserva el manejador de disipación de rango 5 de WotLK.
            "id": 427717, "client": True, "template": 47843,
            "skill_line": SKILL_AFFLICTION,
            "name": "Unstable Affliction", "script": "spell_warl_unstable_affliction",
            "inherit_server": True,
            "bonus": {"direct": 0.0, "dot": 0.2, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Shadow energy slowly destroys the target, causing Shadow damage over 18 sec. If dispelled, it damages and silences the dispeller.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": idx["dur"][18000],
                "ManaCostPct": 15,
                "SpellLevel": 0,
            },
        },
        {  # Invocar guardia vil reutiliza la invocación y el control nativos de WotLK.
            "id": 427733, "client": True, "template": 30146,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Summon Felguard", "inherit_server": True,
            "desc": "Summons a Felguard under your command. The Felguard benefits from talents and effects that affect your other demon minions.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "ManaCostPct": 80,
                "SpellLevel": 0,
            },
        },
        {  # La runa concede la forma demoníaca; 47241 es la forma otorgada por el talento 59672.
            "id": 403789, "client": True, "template": 47241,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Metamorphosis", "inherit_server": True,
            "desc": "Transform into a Demon, increasing your Armor and threat. This tank form changes the effects of some Warlock abilities.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": duration_perm,
                "ManaCostPct": 100,
                "SpellLevel": 0,
            },
        },
        {  # Incinerar conserva el hechizo de Fuego de WotLK y aplica coste y bonificación de SoD.
            "id": 412758, "client": True, "template": 47838,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Incinerate", "inherit_server": True,
            "bonus": {"direct": 0.714, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Burn your enemy and increase all Fire damage you deal by 40% for 15 sec.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "DurationIndex": duration_15000,
                "ManaCostPct": 14,
                "SpellLevel": 0,
                # El efecto 2 de 47838 está vacío: el +40 % de daño de Fuego (aura 79, escuela 4) va al lanzador.
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 79,
                "EffectBasePoints_2": 39, "EffectDieSides_2": 1, "EffectMiscValue_2": 4,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
            },
        },
        {  # El manejador nativo de Llama de las Sombras aplica el daño periódico de WotLK.
            "id": 426320, "client": True, "template": 61290,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Shadowflame", "script": "spell_warl_shadowflame",
            "inherit_server": True,
            "bonus": {"direct": 0.1064, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "desc": "Burns the enemy with Shadowflame and applies additional Shadowflame damage over time.",
            "overrides": {
                "CategoryRecoveryTime": 0,
                "RecoveryTime": 0,
                "ManaCostPct": 27,
                "SpellLevel": 0,
            },
        },
        # --- Runas de fase 2: toda la mecánica vive en scripts nativos del core (sin C++ nuevo). ---
        {  # Backdraft: aura 109 (disparo al golpear) que aplica el buff de celeridad sobre el brujo.
            "id": 427713, "client": True, "template": 47260,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Backdraft", "inherit_server": True,
            "desc": "Your Conflagrate ability also grants $427714s1% spellcasting haste for $427714d and no longer consumes Immolate.",
            "overrides": {
                # EFFECT_0: APPLY_AURA + ADD_TARGET_TRIGGER; 99 + 1 = 100 % de probabilidad de disparo.
                "Effect_1": 6, "EffectAura_1": 109,
                "EffectBasePoints_1": 99, "EffectDieSides_1": 1,
                "EffectTriggerSpell_1": 427714, "EffectMiscValue_1": 12,
                # Sólo Conflagrar dispara el buff: palabra B, 0x800000.
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 8388608,
                "EffectSpellClassMaskC_1": 0,
            },
        },
        {  # Buff de Backdraft: aura 65 (velocidad de lanzamiento) para todos los hechizos, 15 s.
            "id": 427714, "client": True, "template": 54277,
            "name": "Backdraft", "inherit_server": True,
            # Copia de spell_proc 54274: qué hechizos gastan las cargas; el id nuevo no la hereda.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 5,
                "SpellFamilyMask0": 357, "SpellFamilyMask1": 131264, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 0, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 8, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "aura_desc": "Spellcasting haste increased by $w1%.",
            "overrides": {
                # El talento de WotLK usaba aura 108 enmascarada; la runa usa aura 65 y sin máscara.
                "EffectAura_1": 65, "EffectBasePoints_1": 30, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
                # El efecto 2 de 54277 (aura 108 + SPELLMOD_GLOBAL_COOLDOWN) no existe en SoD.
                "Effect_2": 0, "EffectAura_2": 0, "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "ImplicitTargetA_2": 0,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
            },
        },
        {  # Exterminio: el script nativo spell_warl_decimation exige objetivo por debajo del 35 %.
            "id": 440870, "client": True, "template": 63158,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Decimation", "script": "spell_warl_decimation",
            "inherit_server": True,
            "desc": "Your Soul Fire spell no longer has a cooldown. Additionally, when your Shadow Bolt, Shadow Cleave, Incinerate, or Soul Fire hits a target that is at or below $s2% health, the cast time of your Soul Fire spell is reduced by $s1% for $440873d. Soul Fires cast under the effect of Decimation cost no shard.",
            "overrides": {
                # EFFECT_0: aura 42 (proc) que aplica el buff 440873.
                "EffectBasePoints_1": 40, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 440873, "EffectMiscValue_1": 0,
                # EFFECT_1: dummy con el umbral del 35 % (palabra A, 0x1); sólo alimenta el tooltip.
                "Effect_2": 6, "EffectAura_2": 4, "EffectBasePoints_2": 35, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_2": 1, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
                # EFFECT_2: aura 108 + SPELLMOD_COOLDOWN (11) sobre Piro de alma (palabra B, 0x80).
                "Effect_3": 6, "EffectAura_3": 108, "EffectBasePoints_3": -100,
                "EffectDieSides_3": 0, "EffectMiscValue_3": 11,
                "EffectSpellClassMaskA_3": 0, "EffectSpellClassMaskB_3": 128,
                "EffectSpellClassMaskC_3": 0, "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
            # Conserva la fila `spell_proc` de la plantilla (-63156): máscaras de Piro de alma,
            # sólo daño (SpellTypeMask=1) y al golpear (SpellPhaseMask=2). DisableEffectsMask=2
            # es el valor de la fila nativa: desactiva el efecto 2 (el dummy del umbral).
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 5,
                "SpellFamilyMask0": 1, "SpellFamilyMask1": 192,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0,
                "DisableEffectsMask": 2, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Buff de Exterminio: 10 s (índice 1 heredado de 63167).
            "id": 440873, "client": True, "template": 63167,
            "name": "Decimation", "inherit_server": True,
            "aura_desc": "Your Soul Fire cast time is reduced by $s1%, and costs no shard.",
            "overrides": {
                "EffectBasePoints_1": -40, "EffectDieSides_1": 0,
                # Piro de alma (palabra B, 0x80).
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 128,
                "EffectSpellClassMaskC_1": 0,
                # La plantilla de WotLK repetía el −40 % como aura 256 (palabra A/B/C); SoD deja sólo B.
                "EffectBasePoints_2": -40, "EffectDieSides_2": 0,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 128,
                "EffectSpellClassMaskC_2": 0,
            },
        },
        {  # Pacto demoníaco: el buff visible (48090) lo lanza el aura de familiar 54909 desde el core.
            "id": 425464, "client": True, "template": 47236,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Demonic Pact", "inherit_server": True,
            "desc": "Your Fire and Shadow spells deal $s2% more damage, and your pet's critical strikes apply the Demonic Pact effect to your party or raid members for $48090d. Demonic Pact increases spell damage and healing by $s1% of your spell damage or ${$PL/2}, whichever is higher. Does not work on Subjugated demons.",
            "overrides": {
                # EFFECT_0: dummy. No se tocan SpellIconID (3220) ni SpellClassSet (5): el script del
                # core los usa para encontrar este dummy (familia 5 + icono 3220 + índice 0). Tampoco
                # se toca EffectMiscValue_1 (12); sólo se quitan las máscaras de talento de WotLK.
                "EffectBasePoints_1": 10, "EffectDieSides_1": 0,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
                # EFFECT_1: aura 79 (daño de escuela) con +10 % a Fuego y Sombras.
                "EffectAura_2": 79, "EffectBasePoints_2": 10, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 36,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
                # EFFECT_2 y EFFECT_3 del talento (aura 107 y aura 79 de +1 %) no existen en la runa.
                "Effect_3": 0, "EffectAura_3": 0, "EffectBasePoints_3": 0, "EffectDieSides_3": 0,
                "EffectMiscValue_3": 0, "ImplicitTargetA_3": 0,
                "EffectSpellClassMaskA_3": 0, "EffectSpellClassMaskB_3": 0,
                "EffectSpellClassMaskC_3": 0,
            },
        },
        {  # Aflicción eterna: aura 109 que refresca Corrupción al golpear con los hechizos de la lista.
            "id": 412689, "client": True, "template": 47201,
            "skill_line": SKILL_AFFLICTION,
            "name": "Everlasting Affliction", "inherit_server": True,
            "desc": "Drain Life, Drain Soul, Shadowbolt, Shadow Cleave, Searing Pain, Incinerate, and Haunt refresh the duration of your Corruption on the target back to its maximum duration.",
            "overrides": {
                # EFFECT_0: aura 109 (disparo) al 100 % con las máscaras de SoD.
                "EffectAura_1": 109, "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 412698, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "EffectSpellClassMaskA_1": 16649, "EffectSpellClassMaskB_1": 262208,
                "EffectSpellClassMaskC_1": 131072,
                # EFFECT_1 del talento de WotLK (aura 107 de +1 % de daño) no existe en la runa.
                "Effect_2": 0, "EffectAura_2": 0, "EffectBasePoints_2": 0, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "ImplicitTargetA_2": 0,
                "EffectSpellClassMaskA_2": 0, "EffectSpellClassMaskB_2": 0,
                "EffectSpellClassMaskC_2": 0,
            },
        },
        {  # Disparo de Aflicción eterna: el script nativo refresca Corrupción.
            # Debe ser `client: True` para que el emisor materialice la fila completa (168
            # columnas) clonando 47422; con `client: False` sólo se emiten los `overrides`
            # declarados y el hechizo se quedaría sin efecto 77, así que el script no dispararía.
            "id": 412698, "client": True, "template": 47422,
            "name": "Everlasting Affliction", "inherit_server": True,
            "script": "spell_warl_everlasting_affliction",
            # Sin overrides de efectos: 47422 ya es efecto 77 (script), familia 5 y blanco 6, justo
            # lo que exige spell_warl_everlasting_affliction. Sólo cambian id, nombre y descripción.
            "overrides": {},
        },
        {  # Conocimiento demoníaco: dummy que el script nativo busca por familia 5 + icono 1876.
            "id": 412732, "client": True, "template": 35693,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Demonic Knowledge", "inherit_server": True,
            "desc": "Increases your spell damage and healing by a value equal to $s1% of your Demon pet's total Stamina plus Intellect.",
            "overrides": {
                # El importe alimenta el tooltip (3 %) y el valor inicial del aura del familiar.
                # Las máscaras de 35693 son del talento de WotLK: se van a 0 como en SoD.
                "EffectBasePoints_1": 3, "EffectDieSides_1": 0,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
            },
        },
        {  # Aura del familiar de Conocimiento demoníaco: id auxiliar de servidor (no existe en 3.3.5a).
            "id": 900048, "client": True, "template": 35696,
            "name": "Demonic Knowledge", "inherit_server": True,
            "script": "spell_warl_demonic_knowledge",
            "aura_desc": "Increases Master's spell power by $s1% of the active demon's Stamina plus Intellect.",
            "overrides": {
                # 3 % (SoD) en vez del 12 % de WotLK; el script lee el importe como base + die.
                "EffectBasePoints_1": 3, "EffectDieSides_1": 0,
            },
        },
    ]
