# Runas de Warlock

Build consultada: `1.15.9.70003`. Fecha de generación: 2026-10-05.

Estos datos corresponden a la build moderna y no están escalados a 3.3.5a.

## Chest

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Lago de Fuego / Lake of Fire | 403666 | Your Rain of Fire is no longer channeled, but gains a $s5 sec cooldown. | — | — | 0 s | no |
| Maestro canalizador / Master Channeler | 403668 | Your Drain Life is no longer channeled, lasts $403677d with a $403677d cooldown, costs $s2% more mana, and heals you for $s1% more each time it deals damage. | — | — | 0 s | no |
| Tácticas demoníacas / Demonic Tactics | 412727 | Increases the melee and spell critical strike chance of you and your pet by $s1%. | — | — | 0 s | no |

## Legs

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Aflicción eterna / Everlasting Affliction | 412689 | Drain Life, Drain Soul, Shadowbolt, Shadow Cleave, Searing Pain, Incinerate, and Haunt refresh the duration of your Corruption on the target back to its maximum duration. | — | — | 0 s | no |
| Gracia demoníaca / Demonic Grace | 425463 | Surge with fel energy, increasing your pet's and your own dodge chance by $s1%, and your chance to critically strike with all attacks by $s2%. Lasts $d. | — | 20 s | 0 s | no |
| Pacto demoníaco / Demonic Pact | 425464 | Your Fire and Shadow spells deal $s2% more damage, and your pet's critical strikes apply the Demonic Pact effect to your party or raid members for $425467d. Demonic Pact increases spell damage and healing by $s1% of your | — | — | 0 s | no |

## Hands

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Descarga de caos / Chaos Bolt | 403629 | Sends a bolt of chaotic fire at the enemy, dealing ${$<power>*$m1/100} to ${$<power>*$M1/100} Chaos damage.  Chaos Bolt always hits, cannot be resisted, and its knowledge causes all your Fire spells to pierce through abs | 7% | 12 s | 2500 ms | no |
| Metamorfosis / Metamorphosis | 403789 | Transform into a Demon, increasing Armor by $403816s1%, Health by $403816s6%, reducing the chance you will be critically hit by $403816s2%, increasing your threat by $403816s3%, increasing mana gained from Life Tap by $4 | 100% | 0 s | 0 s | no |
| Poseer / Haunt | 403501 | Unleash a ghostly soul on an enemy, dealing ${$<power>*$m1/100} to ${$<power>*$M1/100} damage, and increasing all Shadow damage over time you deal to that target by $s2% for $d. When the Haunt ends or is dispelled, you w | 12% | 12 s | 0 s | no |
| Salva de descarga de las Sombras / Shadow Bolt Volley | 403628 | Your Shadow Bolt now strikes up to $s1 targets within a chain distance of $s2 yards, but for $s3% reduced damage. | — | — | 0 s | no |

## Notas de implementación (2026-10-09)

Las tablas de arriba son el catálogo de SoD tal cual (solo ranuras de Pecho, Piernas y Manos). Esto es lo que
hay implementado de verdad en `server/mod-sod-content/`, y dónde se desvía de SoD. **Nada de esto está
compilado ni probado en juego.**

Piloto (`7008001`–`7008002`): Chaos Bolt y Haunt, clones de WotLK (ver `CHANGELOG.md`).
Primera tanda (`7008004`–`7008008`): Unstable Affliction, Summon Felguard, Metamorphosis, Incinerate y
Shadowflame. Metamorphosis solo da la forma (sin Shadow Cleave, Menace ni Demon Charge).

Segunda tanda, **sin C++ nuevo** (solo SQL, el enumerado de ids y `tools/sod_spells_warlock.py`); reutiliza los
manejadores nativos del core:

| Runa | rune_id | Ranura | Hechizo enseñado | Plantilla WotLK | Script del core | Desviación respecto a SoD |
|---|---|:---:|:---:|:---:|:---:|---|
| Backdraft / Explosión de humo | 7008009 | Cabeza (0) | 427713 + buff 427714 | 47260 + 54277 | aura 109 (proceso de Conflagrar) | Conflagrar **sigue consumiendo Inmolar**: ese consumo vive en el core (`AURA_STATE_CONFLAGRATE`, `SpellEffects.cpp`) y ningún hook de módulo lo evita (ver `TODO.md`). |
| Decimation / Exterminio | 7008010 | Pies (9) | 440870 + buff 440873 | 63158 + 63167 | `spell_warl_decimation` (fila `spell_proc` propia sobre 440870) | Ninguna conocida: el enfriamiento cero de Fuego de alma y el umbral de salud del 35 % los aplica el core. Cuchilla de las Sombras no existe en 3.3.5a. |
| Demonic Pact / Pacto demoníaco | 7008011 | Piernas (8) | 425464 | 47236 | `spell_warl_demonic_pact` sobre el aura de mascota nativa 54909 | El +10 % de daño de Fuego y Sombras va por aura 79 propia y el efecto de grupo o banda depende del aura de mascota 54909 (el módulo inserta su `spell_pet_auras`). |
| Everlasting Affliction / Aflicción eterna | 7008012 | Piernas (8) | 412689 + disparador 412698 | 47201 + 47422 | `spell_warl_everlasting_affliction` (sobre 412698) | SoD refresca Corrupción también con Cuchilla de las Sombras y Dolor abrasador; ninguno existe en 3.3.5a, así que solo funcionan los hechizos de WotLK. |
| Demonic Knowledge / Conocimiento demoníaco | 7008013 | Pies (9) | 412732 | 35693 | `spell_warl_demonic_knowledge` sobre el aura de mascota 900048 | El aura de mascota vale el **3 %** (la nativa 35696 valía el 12 %). El id auxiliar 900048 continúa la serie de auxiliares del chamán (900042–900047). |

Datos generados y comprobaciones:

- SQL de hechizos regenerado con `tools/sod-client/build_patch.py`: 9 filas nuevas en `spell_dbc`, 3 en
  `spell_script_names` y 1 en `spell_proc` (la de Decimation).
- Parche de cliente en `datos/parche-cliente/20261009-brujo/` (pendiente de publicar con el launcher).
- `check_syntax.py`: 86 archivos, 0 errores.
- Pendiente: compilar, aplicar el SQL, copiar los MPQ, reiniciar el reino 2 y probar (pasos en
  `docs/PRUEBAS.md`).

