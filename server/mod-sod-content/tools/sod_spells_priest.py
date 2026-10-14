#!/usr/bin/env python3
"""Priest spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403

SKILL_HOLY = 56
SKILL_DISCIPLINE = 613
SKILL_SHADOW = 78


def build(idx):
    """Return Priest spells cloned from the level-80 WotLK ranks."""
    return [
        {  # Circle of Healing keeps its target filter and healing coefficient.
            "id": 401946, "client": True, "template": 48089,
            "skill_line": SKILL_HOLY,
            "name": "Circle of Healing", "script": "spell_pri_circle_of_healing",
            "inherit_server": True,
            "scale_to_level": {"effects": [1], "level": 80},
            "bonus": {"direct": 0.402, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            "overrides": {
                "ManaCostPct": 56,
                "SpellLevel": 0,
            },
        },
        {  # Penance's core script requires the original WotLK rank chain.
            "id": 402174, "client": True, "template": 53007,
            "skill_line": SKILL_DISCIPLINE,
            "name": "Penance", "inherit_server": True,
            # El script del core va ligado a -47540 (primer rango); el id nuevo no lo hereda.
            "script": "spell_pri_penance",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Serendipia reutiliza el proc de WotLK y su aura de reducción del tiempo de lanzamiento.
            "id": 413248, "client": True, "template": 63737,
            "skill_line": SKILL_HOLY,
            "name": "Serendipity", "inherit_server": True,
            "desc": "Healing with Flash Heal reduces the cast time of your next Lesser Heal, Heal, Greater Heal, or Prayer of Healing by $413247s1% for $413247d, stacking up to $413247u times.",
            "overrides": {
                "SpellLevel": 0,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 413247,
            },
            # Copia de spell_proc -63730; la runa activa el proc en cada Sanación relámpago.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 6,
                "SpellFamilyMask0": 0x800, "SpellFamilyMask1": 0x4,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 100, "Charges": 0,
            },
        },
        {  # Aura de celeridad de lanzamiento que activa Serendipia.
            "id": 413247, "client": True, "template": 63734,
            "skill_line": SKILL_HOLY,
            "name": "Serendipity", "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
                "CumulativeAura": 3,
            },
        },
        {  # La mecánica queda pendiente porque faltan los datos del auxiliar 409317.
            "id": 415739, "client": True, "template": 774,
            "skill_line": SKILL_HOLY,
            "name": "Strength of Soul",
            "desc": "Lesser Heal, Heal, Greater Heal, and Flash Heal reduce the remaining duration of Weakened Soul on targets they heal. Damage absorbed by your Power Word: Shield also generates Rage and triggers Righteous Fury as if it were a heal.",
            "overrides": {
                "SpellLevel": 0,
                "SpellClassSet": 6,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Effect_1": 0, "EffectAura_1": 0,
                "Effect_2": 0, "EffectAura_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
        {  # Mantiene el modificador nativo de WotLK condicionado por Palabra de las Sombras: dolor.
            "id": 425198, "client": True, "template": 51167,
            "skill_line": SKILL_SHADOW,
            "name": "Twisted Faith", "inherit_server": True,
            "desc": "Mind Flay and Mind Blast deal $s2% increased damage to targets afflicted with your Shadow Word: Pain.",
            "overrides": {
                "SpellLevel": 0,
                # El efecto 2 nativo aplica el aumento de daño; los efectos de intelecto se retiran.
                "Effect_1": 0, "EffectAura_1": 0,
                "Effect_2": 6, "EffectAura_2": 112,
                "EffectBasePoints_2": 50, "EffectDieSides_2": 0,
                "Effect_3": 0, "EffectAura_3": 0,
            },
        },
        {  # Aproximación jugable con el esbirro de WotLK más cercano disponible.
            "id": 402799, "client": True, "template": 34433,
            "skill_line": SKILL_SHADOW,
            "name": "Homunculi", "inherit_server": True,
            "desc": "Summons a Shadowfiend to attack your current target. This WotLK approximation summons one familiar instead of three Homunculi.",
            "overrides": {
                "SpellLevel": 0,
                "RecoveryTime": 120000,
                "DurationIndex": idx["dur"][120000],
            },
        },
        {  # El motor nativo de WotLK conserva los saltos y el escudo con cargas de Rezo de alivio.
            "id": 401859, "client": True, "template": 48113,
            "skill_line": SKILL_HOLY,
            "name": "Prayer of Mending", "inherit_server": True,
            "desc": "Places a spell on the target that heals them the next time they take damage or receive healing. When the heal occurs, Prayer of Mending jumps to another party or raid member.",
            "bonus": {"direct": 0.8057, "dot": 0.0, "ap": 0.0, "ap_dot": 0.0},
            # Copia de spell_proc -33076; el id nuevo no hereda el disparador nativo.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 0, "SpellTypeMask": 664232, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "overrides": {
                "SpellLevel": 0, "ManaCostPct": 15, "RecoveryTime": 10000,
                "SpellClassSet": 6,
                "SpellClassMask_1": 0, "SpellClassMask_2": 0x20, "SpellClassMask_3": 0x400,
                "EffectBasePoints_1": 74, "EffectDieSides_1": 0,
                "EffectBasePoints_2": 5, "EffectDieSides_2": 0,
            },
        },
    ]
