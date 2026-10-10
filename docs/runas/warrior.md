# Runas de Warrior

Build consultada: `1.15.9.70003`. Fecha de generación: 2026-10-05.

Estos datos corresponden a la build moderna y no están escalados a 3.3.5a.

## Chest

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Arremetida enfurecida / Raging Blow | 402911 | A ferocious strike that deals $s1% weapon damage, but can only be used while Enrage, Berserker Rage, or Bloodrage is active. Each other melee ability used while Enrage, Berserker Rage, or Bloodrage is active reduces Ragi | — | 8 s | 0 s | no |
| Belisario / Warbringer | 425421 | Your Charge, Intercept, and Intervene abilities are now usable while in combat and in any stance, and will all remove movement impairing effects when activated. | — | — | 0 s | no |
| Flagelación / Flagellation | 402877 | You gain Rage from Physical damage taken as if you were wearing no armor. | — | — | 0 s | no |
| Frenesí sangriento / Blood Frenzy | 412507 | Rend can now be used in Berserker stance, Rend's damage is increased by $s2%, and Rend deals additional damage equal to $s3% of your Attack Power each time it deals damage.  | — | — | 0 s | no |

## Legs

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Asalto frenético / Frenzied Assault | 425412 | While wielding 2-handed weapons, your attack speed is increased by $s1% and your successful melee hits generate $s2 additional Rage, or ${$m2*2} additional Rage if they are critical hits.  | — | — | 0 s | no |
| Consumido por la ira / Consumed By Rage | 425418 | Enrages you (activating abilities which require being Enraged) for $425415d  after you exceed $s1 Rage. In addition, Whirlwind also strikes with off-hand melee weapons while you are Enraged. | — | — | 0 s | no |
| Gancho / Meathook | 403228 | Throw out a hooked chain to restrain the target and pull them toward you. May not be used on enemies higher than level ${$PL+1} or which are marked as boss enemies. | 150 | 35 s | 0 s | no |
| Grito de orden / Commanding Shout | 403215 | The warrior shouts, increasing the Stamina of all party members within $a1 yards by $s1.  Lasts $d. | — | 0 s | 0 s | no |
| Trueno de furia / Furious Thunder | 403219 | Thunder Clap now increases the time between attacks by an additional $s1%, can be used in any stance, deals $s4% increased damage, and deals $s3% increased threat. | — | — | 0 s | no |

## Hands

| Runa (es / en) | Hechizo enseñado | Descripción (inglés) | Coste | Cooldown | Lanzamiento | Conflicto de clase |
|---|---|---|---:|---:|---:|:---:|
| Ataque de la victoria / Victory Rush | 402927 | Instantly attack the target causing ${1+$AP*$m3/100} damage and healing you for $s2% of your maximum health.  Only useable within $402975d after you kill an enemy that yields experience or honor. | — | 8 s | 0 s | no |
| Devastar / Devastate | 403195 | While you are in Defensive Stance and have a shield equipped, Sunder Armor also deals damage equal to $403196s1% of your equipped weapon's damage per second, increased by $403196s2% per application of Sunder Armor alread | — | — | 0 s | no |
| Furia enfocada / Single-Minded Fury | 413404 | While dual-wielding, your movement speed is increased by $430472s2% and you gain $461470s1% attack speed each time your melee auto-attack strikes the same target as your previous auto-attack, stacking up to $461470u time | — | — | 0 s | no |
| Golpe rápido / Quick Strike | 429765 | A reckless instant melee attack with your two-handed weapon dealing ${$AP*$m1/100} to ${$AP*$M1/100} physical damage. This ability benefits from and triggers all effects associated with Heroic Strike.    | 200 | 0 s | 0 s | no |

## Primera tanda (fase 1, 2026-10-10)

Se añaden Frenesí sangriento (`7001002`), Flagelación (`7001003`), Arremetida enfurecida
(`7001004`), Belisario (`7001005`) y Grito de orden (`7001006`). **Sin compilar ni probar.**
Desviaciones conocidas (detalle en `TODO.md` y casillas en `docs/PRUEBAS.md`):

- **Blood Frenzy:** `412507` usa las auras nativas 275 (Desgarrar en actitud rabiosa) y 108 con
  SpellModOp 22 (+100 % de daño periódico); el +4 % del poder de ataque por tick lo añade
  `spell_sod_warrior_blood_frenzy`.
- **Flagellation:** `402877` es el marcador; `unit_sod_warrior_flagellation` concede la ira del
  daño físico recibido sin armadura.
- **Raging Blow:** `402911` hace 115 % del arma y exige Enfurecer/Ira rabiosa/Ira sangrienta
  (`spell_sod_warrior_raging_blow`); `player_sod_warrior_raging_blow` recorta 1 s el enfriamiento.
- **Warbringer:** `425421` usa las auras nativas 262 y 275; `spell_sod_warrior_warbringer` quita
  raíces y ralentizaciones al usar Cargar, Interceptar o Intervenir.
- **Commanding Shout:** `403215` clona el Grito de orden de WotLK (47440); en 3.3.5a sube la
  salud máxima, no el aguante.

