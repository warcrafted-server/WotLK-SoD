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
    duration_6000 = idx["dur"][6000]
    duration_10000 = idx["dur"][10000]
    duration_15000 = idx["dur"][15000]
    duration_20000 = idx["dur"][20000]
    duration_perm = idx["dur"][-1]
    range_self = idx["range"][0.0]
    icon_demonic_tactics = idx["icon"]["spell_shadow_demonictactics"]
    icon_life_drain = idx["icon"]["spell_shadow_lifedrain02"]
    icon_shadow_and_flame = idx["icon"]["spell_shadow_shadowandflame"]
    icon_rain_of_fire = idx["icon"]["spell_shadow_rainoffire"]
    icon_shadow_bolt = idx["icon"]["spell_shadow_shadowbolt"]
    icon_demonic_grace = idx["icon"]["ability_warlock_avoidance"]
    icon_invocation = idx["icon"]["spell_shadow_lastingafflictions"]
    icon_dance_of_the_wicked = idx["icon"]["spell_shadow_siphonmana"]
    icon_vengeance = idx["icon"]["spell_shadow_metamorphosis"]
    icon_immolation_aura = idx["icon"]["spell_fire_immolation"]

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
        # --- Tercera tanda (fase 3): Soul Siphon, Shadow and Flame, Lake of Fire, Master
        # Channeler y Shadow Bolt Volley. ---
        {  # Soul Siphon: clona el talento de WotLK 17805 r2, que ya aplica el +6 % por efecto
           # de Sombras del objetivo sobre Drenar vida y Drenar alma hasta el 18 % (el core lo
           # resuelve por aura 112 con MiscValue 4993). Añade en el tercer efecto el −2000 ms de
           # tiempo de activación (aura 107 + SpellModOp 19) sobre Drenar alma: su canal pasa de
           # 3 s a 1 s por tick. El ramal de SoD «por debajo del 20 % de salud» no existe en
           # WotLK y no se reproduce; ver TODO.md.
            "id": 403511, "client": True, "template": 17805,
            "skill_line": SKILL_AFFLICTION,
            "name": "Soul Siphon", "inherit_server": True,
            "desc": "Causes your Drain Soul to deal damage 3 times faster and increases the amount drained by your Drain Life and Drain Soul spells by an additional 6% for each of your Warlock Shadow effects afflicting the target, up to a maximum of 18% additional effect. In addition, your Drain Soul can now trigger your Nightfall talent.",
            "overrides": {
                "SpellLevel": 0,
                # EFFECT_2: aura 107 (modificador plano) + SpellModOp 19 (tiempo de activación),
                # −2000 ms sobre Drenar alma (máscara de familia 0x4000).
                "Effect_3": 6, "EffectAura_3": 107,
                "EffectBasePoints_3": -2000, "EffectDieSides_3": 0,
                "EffectMiscValue_3": 19, "EffectSpellClassMaskA_3": 16384,
                "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
        },
        {  # Shadow and Flame: pasiva con aura 42 (proc) que aplica el beneficio 426311. El filtro
           # «solo críticos de Fuego y Sombras» vive en la fila spell_proc de este id.
            "id": 426316, "client": True, "template": 774,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Shadow and Flame", "inherit_server": True,
            "desc": "Your critical strikes with Fire and Shadow spells increase your Fire and Shadow damage done by $426311s1% for $426311d.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_shadow_and_flame,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "Effect_1": 6, "EffectAura_1": 42,
                "EffectBasePoints_1": 6, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 426311, "EffectMiscValue_1": 0,
                "EffectSpellClassMaskA_1": 0, "EffectSpellClassMaskB_1": 0,
                "EffectSpellClassMaskC_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            # Copia del patrón de Burnout: daño con hechizos hecho con golpe crítico. Las máscaras
            # de familia van completas (cualquier hechizo de brujo), no solo Fuego/Sombras: WotLK
            # no ofrece un conjunto exacto de esas dos escuelas y no se inventa.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 5,
                "SpellFamilyMask0": 0xFFFFFFFF, "SpellFamilyMask1": 0xFFFFFFFF,
                "SpellFamilyMask2": 0xFFFFFFFF, "ProcFlags": PROC_DONE_MAGIC_NEG,
                "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 2, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Beneficio de Shadow and Flame: +10 % al daño de Fuego y Sombras durante 10 s.
            "id": 426311, "client": True, "template": 774,
            "name": "Shadow and Flame", "inherit_server": True,
            "desc": "Increases all Fire and Shadow damage done by $s1%.",
            "aura_desc": "Increases all Fire and Shadow damage done by $s1%.",
            "overrides": {
                "Attributes": 0, "AttributesEx": 0,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_shadow_and_flame,
                "CastingTimeIndex": cast_instant, "DurationIndex": idx["dur"][10000],
                "RangeIndex": range_self, "SchoolMask": 4, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "Effect_1": 6, "EffectAura_1": 79,
                "EffectBasePoints_1": 10, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 36, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Lake of Fire: la pasiva añade 8 s de enfriamiento (SpellModOp 11) a Lluvia de Fuego.
           # SoD también la deja sin canalizar con el aura moderna 332, que no existe en 3.3.5a;
           # quitar el canal exige cambiar el DBC del hechizo base y no se puede desde un módulo.
            "id": 403666, "client": True, "template": 774,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Lake of Fire", "inherit_server": True,
            "desc": "Your Rain of Fire is no longer channeled, but gains a 8 sec cooldown.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_rain_of_fire,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 4, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                # Aura 107 (plano) + SpellModOp 11 (enfriamiento), +8000 ms sobre Lluvia de Fuego
                # (máscara 0x20). Sumar enfriamiento es un valor plano, no porcentual.
                "Effect_1": 6, "EffectAura_1": 107,
                "EffectBasePoints_1": 8000, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 11, "EffectSpellClassMaskA_1": 32,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                # Aura 4 dummy: mantiene el 8 en el tooltip ($s5).
                "Effect_2": 6, "EffectAura_2": 4,
                "EffectBasePoints_2": 8, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Master Channeler: la pasiva encarece Drenar vida un 100 % (SpellModOp 14) y el script
           # C++ propio añade el 50 % de sanación por tick. La conversión de canal a duración no
           # se implementa (ver TODO.md).
            "id": 403668, "client": True, "template": 774,
            "skill_line": SKILL_AFFLICTION,
            "name": "Master Channeler", "inherit_server": True,
            "desc": "Your Drain Life is no longer channeled, lasts with a cooldown, costs 100% more mana, and heals you for 50% more each time it deals damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_life_drain,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 32, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                # Aura 108 + SpellModOp 14 (coste en %), +100 % a Drenar vida (0x8).
                "Effect_1": 6, "EffectAura_1": 108,
                "EffectBasePoints_1": 100, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 14, "EffectSpellClassMaskA_1": 8,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                # Aura 4 dummy: mantiene el 50 % de sanación en el tooltip ($s1).
                "Effect_2": 6, "EffectAura_2": 4,
                "EffectBasePoints_2": 50, "EffectDieSides_2": 0,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Shadow Bolt Volley: dos SpellMods sobre Descarga de las Sombras: +5 objetivos en
           # cadena (aura 107 + SpellModOp 17) y −30 % de daño (aura 108 + SpellModOp 0).
            "id": 403628, "client": True, "template": 774,
            "skill_line": SKILL_DESTRUCTION,
            "name": "Shadow Bolt Volley", "inherit_server": True,
            "desc": "Your Shadow Bolt now strikes up to $s1 targets within a chain distance of 10 yards, but for $s3% reduced damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_shadow_bolt,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 32, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                # Aura 107 (plano) + SpellModOp 17 (objetivos de cadena), +5 sobre Descarga (0x1).
                "Effect_1": 6, "EffectAura_1": 107,
                "EffectBasePoints_1": 5, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 17, "EffectSpellClassMaskA_1": 1,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                # Aura 108 (porcentaje) + SpellModOp 0 (daño), −30 % sobre Descarga (0x1).
                "Effect_2": 6, "EffectAura_2": 108,
                "EffectBasePoints_2": -30, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "EffectSpellClassMaskA_2": 1,
                "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        # --- Cuarta tanda (fase 4): Gracia demoníaca, Invocación, Danza de los malditos,
        # Venganza y Aura de Inmolación. ---
        {  # Gracia demoníaca: se activa (enfriamiento 20 s) y durante 6 s da +20 % de
           # esquiva al brujo y a su mascota y +20 % de crítico con todos los ataques al
           # brujo. El crítico global es el aura 290 de 3.3.5a; la esquiva (49) va al
           # caster y a la mascota.
            "id": 425463, "client": True, "template": 774,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Demonic Grace",
            "desc": "Surge with fel energy, increasing your pet's and your own dodge chance by $s1%, and your chance to critically strike with all attacks by $s2%. Lasts $d.",
            "overrides": {
                "Attributes": 0,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_demonic_grace,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_6000,
                "RangeIndex": range_self, "SchoolMask": 32, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 20000, "CategoryRecoveryTime": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 49,
                "EffectBasePoints_1": 20, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "ImplicitTargetB_1": TARGET_UNIT_PET,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 290,
                "EffectBasePoints_2": 20, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 0, "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Venganza: se activa (enfriamiento 180 s) y durante 20 s aumenta un 30 % la salud
           # máxima. El core ya resta la salud al expirar (aura 133). El catálogo pide el aura
           # 34, pero en 3.3.5a el aura 34 es un aumento plano y el porcentaje es el 133
           # (como en el chamán); se anota en el informe.
            "id": 426195, "client": True, "template": 774,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Vengeance",
            "desc": "When activated, this ability temporarily grants you a $s1% increase to your maximum health for $d. After the effect expires, the health is lost. Additionally, while in Metamorphosis, Vengeance causes your wings to slow your falling speed.",
            "overrides": {
                "Attributes": 0,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_vengeance,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_20000,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "RecoveryTime": 180000, "CategoryRecoveryTime": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 133,
                "EffectBasePoints_1": 30, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Invocación: pasiva. El script propio (spell_sod_warlock_invocation, enganchado a
           # las auras de los DoT) inflige un pulso de daño al objetivo al aplicar o refrescar
           # Corrupción, Inmolar, Maldición de agonía, Aflicción inestable, Llama de las Sombras
           # o Succionar vida. El 6 del efecto es el umbral de 6 s de SoD para el refresco.
            "id": 426243, "client": True, "template": 774,
            "skill_line": SKILL_AFFLICTION,
            "name": "Invocation",
            "desc": "Applying Corruption, Immolate, Curse of Agony, Unstable Affliction, Shadowflame, or Siphon Life will cause you to deal instant damage to the target equal to one tick of the spell's periodic damage. Refreshing any of those spells when it has less than $s1 seconds duration remaining will cause you to deal instant damage to the target equal to the spell's remaining periodic damage.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_invocation,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 1, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 4,
                "EffectBasePoints_1": 6, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Danza de los malditos: pasiva con proc por crítico. Al asestar un crítico aplica
           # el beneficio 900050 al brujo y a su mascota, con esquiva igual al 70 % (efecto del
           # catálogo) de la probabilidad de crítico con hechizos. El script calcula el importe.
            "id": 412798, "client": True, "template": 774,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Dance of the Wicked", "script": "spell_sod_warlock_dance_of_the_wicked",
            "desc": "You and your demon pet gain dodge chance equal to $s1% of your spell critical strike chance each time you deal a critical strike to an enemy, and also both regain $412800s2% of maximum mana.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_dance_of_the_wicked,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 32, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "ProcChance": 100,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 4,
                "EffectBasePoints_1": 70, "EffectDieSides_1": 0,
                "EffectMiscValue_1": 0, "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
            # Sólo dispara con golpes críticos (HitMask 2) de daño mágico del brujo.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": PROC_DONE_MAGIC_NEG, "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 2, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 0, "Cooldown": 0, "Charges": 0,
            },
        },
        {  # Aura de Inmolación: pasiva. El aura 42 dispara el daño 427725 cuando un enemigo
           # ataca cuerpo a cuerpo (como mucho una vez por segundo, vía enfriamiento del proc);
           # además reduce un 10 % el daño mágico recibido (aura 87, escuelas mágicas 126) y
           # aumenta un 10 % el daño de Fuego infligido (aura 79, escuela 4).
            "id": 427726, "client": True, "template": 774,
            "skill_line": SKILL_DEMONOLOGY,
            "name": "Immolation Aura",
            "desc": "Burns nearby enemies for ${$<power>*$427725m1/100} damage every time an enemy makes a melee attack against you (no more than once per sec), reduces all magic damage taken by $s2%, and increases Fire damage done by $s3%. Lasts $d.",
            "overrides": {
                "Attributes": SPELL_ATTR0_PASSIVE,
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "SpellIconID": icon_immolation_aura,
                "CastingTimeIndex": cast_instant, "DurationIndex": duration_perm,
                "RangeIndex": range_self, "SchoolMask": 4, "SpellLevel": 0,
                "EquippedItemClass": -1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "ProcChance": 100,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 42,
                "EffectBasePoints_1": 20, "EffectDieSides_1": 0,
                "EffectTriggerSpell_1": 427725, "EffectMiscValue_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_CASTER,
                "Effect_2": EFFECT_APPLY_AURA, "EffectAura_2": 87,
                "EffectBasePoints_2": -10, "EffectDieSides_2": 0,
                "EffectMiscValue_2": 126, "ImplicitTargetA_2": TARGET_UNIT_CASTER,
                "Effect_3": EFFECT_APPLY_AURA, "EffectAura_3": 79,
                "EffectBasePoints_3": 10, "EffectDieSides_3": 0,
                "EffectMiscValue_3": 4, "ImplicitTargetA_3": TARGET_UNIT_CASTER,
            },
            # 0x8 ataque cuerpo a cuerpo recibido + 0x20 hechizo con clase de daño melee
            # recibido; el enfriamiento de 1 s limita el proc a una vez por segundo.
            "proc": {
                "SchoolMask": 0, "SpellFamilyName": 0,
                "SpellFamilyMask0": 0, "SpellFamilyMask1": 0, "SpellFamilyMask2": 0,
                "ProcFlags": 40, "SpellTypeMask": 1, "SpellPhaseMask": 2,
                "HitMask": 0, "AttributesMask": 0, "DisableEffectsMask": 0,
                "ProcsPerMinute": 0, "Chance": 100, "Cooldown": 1000, "Charges": 0,
            },
        },
        {  # Daño de Aura de Inmolación: clon del daño de Aura de Inmolación de WotLK (50590,
           # el hechizo de Metamorfosis), que ya es un área de Fuego centrada en el lanzador.
           # inherit_server copia la fila completa (daño y escalado por nivel incluidos).
            "id": 427725, "client": True, "template": 50590,
            "name": "Immolation Aura", "inherit_server": True,
            "overrides": {
                "SpellClassSet": 5, "SpellClassMask_1": 0,
                "SpellClassMask_2": 0, "SpellClassMask_3": 0,
                "Attributes": SPELL_ATTR0_DO_NOT_DISPLAY,
                "SpellIconID": icon_immolation_aura, "SpellLevel": 0,
            },
        },
        # Auxiliares de servidor (client: False): filas sólo en spell_dbc.
        {  # Daño instantáneo de Invocación: el script fija su importe (un pulso del DoT), sin
           # amenaza y sin volver a aplicar modificadores del lanzador (ya van en el pulso).
            "id": 900049, "client": False, "template": None,
            "name": "Invocation",
            "overrides": {
                "Attributes": SPELL_ATTR0_DO_NOT_DISPLAY,
                "AttributesEx": SPELL_ATTR1_NO_THREAT,
                "AttributesEx3": 0x20000000,
                "DurationIndex": duration_perm, "RangeIndex": range_self,
                "SchoolMask": 32, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 5, "SpellLevel": 0, "DefenseType": 1,
                "Effect_1": EFFECT_SCHOOL_DAMAGE,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ENEMY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
        {  # Beneficio de Danza de los malditos: esquiva que fija el script (70 % del crítico
           # con hechizos). Duración auxiliar de 10 s (no consta en el catálogo); ver TODO.
            "id": 900050, "client": False, "template": None,
            "name": "Dance of the Wicked",
            "overrides": {
                "Attributes": SPELL_ATTR0_DO_NOT_DISPLAY,
                "DurationIndex": duration_15000, "RangeIndex": range_self,
                "SchoolMask": 1, "PowerType": 0, "ManaCost": 0, "ManaCostPct": 0,
                "SpellClassSet": 5, "SpellLevel": 0,
                "Effect_1": EFFECT_APPLY_AURA, "EffectAura_1": 49,
                "EffectBasePoints_1": 0, "EffectDieSides_1": 0,
                "ImplicitTargetA_1": TARGET_UNIT_TARGET_ALLY,
                "Effect_2": 0, "EffectAura_2": 0, "ImplicitTargetA_2": 0,
                "Effect_3": 0, "EffectAura_3": 0, "ImplicitTargetA_3": 0,
            },
        },
    ]
