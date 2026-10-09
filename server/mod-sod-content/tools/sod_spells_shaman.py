#!/usr/bin/env python3
"""Shaman spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403 (shared WoW enum constants)

SKILL_ENHANCEMENT = 373
SKILL_RESTORATION = 374
SKILL_ELEMENTAL = 375


def build(idx):
    """Return Shaman spells cloned from the WotLK rank templates."""
    return [
        {  # Earth Shield: preserve the WotLK aura effects and proc script.
            "id": 408514, "client": True, "template": 49284,
            "skill_line": SKILL_RESTORATION,
            "name": "Earth Shield", "script": "spell_sha_earth_shield",
            "bonus": {"direct": 0.5371, "dot": 0, "ap": 0, "ap_dot": 0},
            "inherit_server": True,
            "overrides": {
                "ManaCostPct": 5,
                "SpellLevel": 0,
            },
        },
        {  # Lava Lash: keep the WotLK weapon damage and Flametongue script.
            "id": 408507, "client": True, "template": 60103,
            "skill_line": SKILL_ENHANCEMENT,
            "name": "Lava Lash", "script": "spell_sha_lava_lash",
            "inherit_server": True,
            "overrides": {
                "ManaCostPct": 1,
                "SpellLevel": 0,
            },
        },
        {  # Ráfaga de lava: WotLK conserva el crítico garantizado con Choque de llamas.
            "id": 408490, "client": True, "template": 60043,
            "skill_line": SKILL_ELEMENTAL,
            "name": "Lava Burst", "inherit_server": True,
            "desc": "You hurl molten lava at the target, dealing ${$m1/100*$<damagepower>} to ${$M1/100*$<damagepower>} Fire damage. If your Flame Shock is on the target, Lava Burst will deal a critical strike.",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Mareas vivas: conserva la sanación directa, periódica y su efecto en Sanación en cadena.
            "id": 408521, "client": True, "template": 61301,
            "skill_line": SKILL_RESTORATION,
            "name": "Riptide", "inherit_server": True,
            "desc": "Heals a friendly target for ${$m1/100*$<healpower>} to ${$M1/100*$<healpower>} and another ${5*$m2/100*$<healpower>} over $d. Your Chain Heals cast on that primary target within $d will increase the amount of the Chain Heal by $s3%. This spell also triggers Ancestral Awakening.",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Espíritu feral: WotLK ya invoca y controla a los dos lobos espirituales.
            "id": 440580, "client": True, "template": 51533,
            "skill_line": SKILL_ENHANCEMENT,
            "name": "Feral Spirit", "inherit_server": True,
            "desc": "Summons two Spirit Wolves under the command of the Shaman, lasting $d.",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # El aura disparada de Arma vorágine conserva el script nativo de modificadores.
            "id": 408505, "client": True, "template": 53817,
            "name": "Maelstrom Weapon", "inherit_server": True,
            "overrides": {
                "SpellLevel": 0,
                # Máscaras de familia: Descarga de relámpagos (0x1), Cadena de relámpagos (0x2),
                # Ola de sanación inferior (0x80) y Ráfaga de lava (palabra B, 0x1000).
                "EffectSpellClassMaskA_1": 0x83,
                "EffectSpellClassMaskB_1": 0x1000,
                "EffectSpellClassMaskC_1": 0,
            },
            # Conserva el filtrado de proc de WotLK para el aura disparada 53817.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 11,
                # Solo gastan carga los hechizos que reciben el modificador.
                "SpellFamilyMask0": 0x83, "SpellFamilyMask1": 0x1000,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 0, "SpellPhaseMask": 1,
                "HitMask": 0, "AttributesMask": 8,
                "DisableEffectsMask": 0, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Arma vorágine: aplica el aura nativa a los hechizos de SoD.
            "id": 408498, "client": True, "template": 51532,
            "skill_line": SKILL_ENHANCEMENT,
            "name": "Maelstrom Weapon", "inherit_server": True,
            "desc": "When you deal damage with a melee attack, you have a chance to reduce the cast time and mana cost of your next Lightning Bolt, Chain Lightning, Lesser Healing Wave, or Lava Burst spell by $408505s1%. Chance increased by $s2% while your main hand weapon is enchanted with Windfury Weapon and by another $s2% if wielding a two-handed weapon. Stacks up to $s3 times. Lasts $408505d.",
            "overrides": {
                "SpellLevel": 0,
                "EffectTriggerSpell_1": 408505,
            },
            # Conserva la cadencia y el filtrado de proc de WotLK para 51532.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 0, "ProcFlags": 0,
                "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0,
                "DisableEffectsMask": 0, "ProcsPerMinute": 10,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Maremotos: el proc nativo de WotLK ya responde a Sanación en cadena y Mareas vivas.
            "id": 432042, "client": True, "template": 51566,
            "skill_line": SKILL_RESTORATION,
            "name": "Tidal Waves", "inherit_server": True,
            # Copia de spell_proc -51562 (Sanación en cadena y Mareas Vivas); el id nuevo no la hereda.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 11,
                "SpellFamilyMask0": 256, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 16, "ProcFlags": 0,
                "SpellTypeMask": 0, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0,
                "DisableEffectsMask": 0, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "desc": "When you cast Chain Heal or Riptide you gain $s1 charges of Tidal Waves, which reduces the cast time of your Healing Wave by $432041s1%, reduces the cast time of your Chain Heal by $432041s3%, and increases the critical effect chance of your Lesser Healing Wave by $432041s2%.",
            "overrides": {
                "SpellLevel": 0,
            },
        },
        {  # Despertar ancestral: conserva el proc de WotLK que sana al aliado con menos salud.
            "id": 425858, "client": True, "template": 51558,
            "skill_line": SKILL_RESTORATION,
            "name": "Ancestral Awakening", "inherit_server": True,
            # Script y spell_proc de -51556; el id nuevo no los hereda.
            "script": "spell_sha_ancestral_awakening",
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 11,
                "SpellFamilyMask0": 192, "SpellFamilyMask1": 0,
                "SpellFamilyMask2": 16, "ProcFlags": 0,
                "SpellTypeMask": 2, "SpellPhaseMask": 2,
                "HitMask": 2, "AttributesMask": 0,
                "DisableEffectsMask": 0, "ProcsPerMinute": 0,
                "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
            "desc": "When you critically heal with your Healing Wave or Lesser Healing Wave you summon an Ancestral spirit to aid you, instantly healing the lowest percentage health party member within 40 yards for $s1% of the amount healed.",
            "overrides": {
                "SpellLevel": 0,
            },
        },
    ]
