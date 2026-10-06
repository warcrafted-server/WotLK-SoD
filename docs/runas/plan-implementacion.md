# Plan de implementación de runas de SoD

El catálogo contiene runas de grabado, almas de la temporada final y hechizos sueltos que no son runas. La categoría se determina por `slot_id`; no se deducen fases.

P = pasiva sencilla; T = proc o disparo; C = requiere C++ o no encaja en las reglas; R = hechizo activo redundante por nombre exacto en WotLK. La clasificación P/T/C/R se aplica solo a runas; las almas usan P/T/C, sin R.

## Totales por categoría

| Categoría | Total | Implementadas | Pendientes |
|---|---:|---:|---:|
| Runa | 256 | 30 | 226 |
| Alma | 206 | — | — |
| Racial | 11 | — | — |
| Ruido | 188 | — | — |
| **Total** | **661** | — | — |

## Runas por ranura y clase

| Ranura | Brujo | Cazador | Chamán | Druida | Guerrero | Mago | Paladín | Pícaro | Sacerdote | Total |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Pecho (Chest) | 3 | 4 | 5 | 4 | 4 | 4 | 3 | 4 | 3 | 34 |
| Piernas (Legs) | 3 | 4 | 4 | 4 | 5 | 4 | 6 | 3 | 3 | 36 |
| Manos (Hands) | 4 | 4 | 5 | 4 | 4 | 3 | 3 | 5 | 4 | 36 |
| Muñecas (Bracer) | 4 | 3 | 4 | 3 | 3 | 4 | 4 | 3 | 4 | 32 |
| Cintura (Waist) | 3 | 5 | 3 | 3 | 3 | 4 | 3 | 3 | 3 | 30 |
| Pies (Feet) | 4 | 3 | 3 | 3 | 4 | 3 | 3 | 3 | 4 | 30 |
| Cabeza (Helm) | 3 | 3 | 3 | 3 | 4 | 4 | 3 | 3 | 3 | 29 |
| Espalda (Cloak) | 3 | 3 | 3 | 3 | 3 | 3 | 4 | 4 | 3 | 29 |
| **Total** | 27 | 29 | 30 | 27 | 30 | 29 | 29 | 28 | 27 | 256 |

## Implementadas y pendientes por ranura

| Ranura | Implementadas | Pendientes | Total |
|---|---:|---:|---:|
| Pecho | 8 | 26 | 34 |
| Piernas | 8 | 28 | 36 |
| Manos | 13 | 23 | 36 |
| Muñecas | 1 | 31 | 32 |
| Cintura | 0 | 30 | 30 |
| Pies | 0 | 30 | 30 |
| Cabeza | 0 | 29 | 29 |
| Espalda | 0 | 29 | 29 |

## Runas pendientes por nivel

| Nivel | Runas pendientes |
|---|---:|
| P — Pasiva | 20 |
| T — Proc o disparo | 39 |
| C — Requiere C++ | 116 |
| R — Redundante en WotLK | 51 |

## Resumen por clase y categoría

| Clase | Runas | Almas | Raciales | Ruido |
|---|---:|---:|---:|---:|
| Brujo | 27 | 0 | 0 | 27 |
| Cazador | 29 | 0 | 0 | 28 |
| Chamán | 30 | 0 | 0 | 17 |
| Druida | 27 | 0 | 0 | 35 |
| Guerrero | 30 | 0 | 0 | 7 |
| Mago | 29 | 0 | 0 | 24 |
| Paladín | 29 | 0 | 0 | 12 |
| Pícaro | 28 | 0 | 0 | 27 |
| Sacerdote | 27 | 0 | 11 | 11 |
| Desconocida | 0 | 206 | 0 | 0 |

## Almas por nivel (sin R)

| Nivel | Almas |
|---|---:|
| P — Pasiva | 0 |
| T — Proc o disparo | 0 |
| C — Requiere C++ | 206 |
| Sin clasificar | 0 |

## Brujo: runas pendientes (24)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 427712 | Pandemic | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 412689 | Everlasting Affliction | Piernas | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 426316 | Shadow and Flame | Cintura | Talento | T | Tiene una probabilidad de proc configurada. |
| 427713 | Backdraft | Cabeza | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 403666 | Lake of Fire | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403668 | Master Channeler | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425463 | Demonic Grace | Piernas | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425464 | Demonic Pact | Piernas | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403789 | Metamorphosis | Manos | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 427733 | Summon Felguard | Muñecas | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 427717 | Unstable Affliction | Muñecas | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 1226981 | Grimoire of Synergy | Cintura | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426243 | Invocation | Cintura | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412798 | Dance of the Wicked | Pies | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440870 | Decimation | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412732 | Demonic Knowledge | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426195 | Vengeance | Cabeza | Talento | C | La descripción indica una mecánica compleja («metamorphosis»). |
| 440882 | Infernal Armor | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440892 | Mark of Chaos | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403511 | Soul Siphon | Espalda | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403628 | Shadow Bolt Volley | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 427726 | Immolation Aura | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412758 | Incinerate | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 426320 | Shadowflame | Pies | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Cazador: runas pendientes (26)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 458479 | Wyvern Strike | Pies | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 415428 | Catlike Reflexes | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 440529 | Resourcefulness | Espalda | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 425713 | Cobra Strikes | Pecho | Talento | T | Tiene una probabilidad de proc configurada. |
| 415370 | Lone Wolf | Pecho | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 415399 | Sniper Training | Piernas | Talento | T | Usa un aura asociada a proc o activación. |
| 409504 | Expose Weakness | Cintura | Talento | T | Tiene una probabilidad de proc configurada. |
| 415405 | Rapid Killing | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 409368 | Beast Mastery | Pecho | Talento | C | La descripción indica una mecánica compleja («taunt»). |
| 415320 | Flanking Strike | Piernas | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 425738 | Serpent Spread | Piernas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425711 | Carve | Manos | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 458393 | Cobra Slayer | Manos | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415358 | Raptor Fury | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 428717 | T.N.T. | Muñecas | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415352 | Melee Specialist | Cintura | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409687 | Dual Wield Specialization | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415413 | Lock and Load | Cabeza | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440533 | Hit and Run | Espalda | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440520 | Improved Volley | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409593 | Kill Shot | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428726 | Focus Fire | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415423 | Aspect of the Viper | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409593 | Kill Shot | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 437123 | Steady Shot | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409541 | Trap Launcher | Pies | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Chamán: runas pendientes (28)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 415813 | Greater Ghost Wolf | Piernas | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 432134 | Static Shock | Muñecas | Talento | T | Tiene una probabilidad de proc configurada. |
| 408696 | Spirit of the Alpha | Pies | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 432042 | Tidal Waves | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 408496 | Dual Wield Specialization | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415236 | Healing Rain | Pecho | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 408524 | Shield Mastery | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 436364 | Two-Handed Mastery | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409324 | Ancestral Guidance | Piernas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408531 | Way of Earth | Piernas | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 408521 | Riptide | Muñecas | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432056 | Rolling Thunder | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408498 | Maelstrom Weapon | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425858 | Ancestral Awakening | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425874 | Decoy Totem | Pies | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 415140 | Mental Dexterity | Cabeza | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415096 | Coherence | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440580 | Feral Spirit | Espalda | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 440569 | Storm, Earth, and Fire | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408438 | Overload | Pecho | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408490 | Lava Burst | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425339 | Molten Blast | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408307 | Nature's Fury | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408510 | Water Shield | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 432140 | Overcharged | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408339 | Fire Nova | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415100 | Power Surge | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415231 | Burn | Cabeza | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Druida: runas pendientes (25)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 407995 | Mangle | Manos | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414684 | Sunfire | Manos | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431389 | Improved Frenzied Regeneration | Muñecas | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 417135 | Gale Winds | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431388 | Improved Barkskin | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 439510 | Improved Swipe | Espalda | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414799 | Fury of Stormrage | Pecho | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 408258 | Dreamstate | Pies | Talento | T | Tiene una probabilidad de proc configurada. |
| 439733 | Tree of Life | Espalda | Talento | T | Tiene una probabilidad de proc configurada. |
| 414677 | Living Seed | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 407977 | Wild Strikes | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 417157 | Starsurge | Piernas | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 410176 | Skull Bash | Manos | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 417149 | Efflorescence | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 414719 | Elune's Fires | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 417141 | Berserk | Cintura | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 408248 | Eclipse | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 417046 | King of the Jungle | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408024 | Survival Instincts | Pies | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 439748 | Starfall | Espalda | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 414644 | Lacerate | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408124 | Lifebloom | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407988 | Savage Roar | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408247 | Nourish | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417145 | Gore | Cabeza | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Guerrero: runas pendientes (29)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 29787 | Focused Rage | Cintura | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 402922 | Precise Timing | Cintura | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 403218 | Endless Rage | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 425418 | Consumed By Rage | Piernas | Sin equivalente | T | Uno de sus efectos dispara otro hechizo. |
| 413404 | Single-Minded Fury | Manos | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 426978 | Sword and Board | Muñecas | Talento | T | Tiene una probabilidad de proc configurada. |
| 427065 | Wrecking Crew | Muñecas | Talento | T | Tiene una probabilidad de proc configurada. |
| 413380 | Blood Surge | Cintura | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 403338 | Intervene | Pies | Talento | T | Tiene una probabilidad de proc configurada. |
| 426980 | Shield Mastery | Cabeza | Talento | T | Usa un aura asociada a proc o activación. |
| 426953 | Taste for Blood | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 412507 | Blood Frenzy | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402877 | Flagellation | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402911 | Raging Blow | Pecho | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 425421 | Warbringer | Pecho | Talento | C | La descripción indica una mecánica compleja («stance»). |
| 425412 | Frenzied Assault | Piernas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403219 | Furious Thunder | Piernas | Sin equivalente | C | La descripción indica una mecánica compleja («stance»). |
| 403228 | Meathook | Piernas | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 429765 | Quick Strike | Manos | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 426940 | Rampage | Muñecas | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412513 | Gladiator Stance | Pies | Sin equivalente | C | La descripción indica una mecánica compleja («stance»). |
| 426972 | Vigilance | Cabeza | Talento | C | La descripción indica una mecánica compleja («taunt»). |
| 440484 | Fresh Meat | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440488 | Shockwave | Espalda | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440113 | Sudden Death | Espalda | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403215 | Commanding Shout | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 402927 | Victory Rush | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 402913 | Enraged Regeneration | Pies | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 426490 | Rallying Cry | Pies | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Mago: runas pendientes (18)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 400613 | Living Bomb | Manos | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 412322 | Spell Power | Pies | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 428739 | Deep Freeze | Cabeza | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 400588 | Missile Barrage | Cintura | Talento | T | Tiene una probabilidad de proc configurada. |
| 400731 | Brain Freeze | Pies | Talento | T | Tiene una probabilidad de proc configurada. |
| 428878 | Balefire Bolt | Muñecas | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 409069 | — | Cintura | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412532 | Spellfrost Bolt | Cintura | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 436516 | Chronostatic Preservation | Pies | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412115 | Advanced Warding | Cabeza | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400624 | Hot Streak | Cabeza | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 428885 | Temporal Anomaly | Cabeza | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 400610 | Arcane Barrage | Espalda | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 428861 | Displacement | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428741 | Molten Armor | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401502 | Frostfire Bolt | Cintura | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 440802 | Frozen Orb | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400615 | Overheat | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Paladín: runas pendientes (24)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 429144 | Purifying Power | Muñecas | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407880 | Inspiration Exemplar | Piernas | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 407613 | Beacon of Light | Manos | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 429152 | Improved Hammer of Wrath | Muñecas | Pasivo | T | Tiene una probabilidad de proc configurada. |
| 428909 | Light's Grace | Muñecas | Talento | T | Tiene una probabilidad de proc configurada. |
| 458287 | Hallowed Ground | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 407632 | Hammer of the Righteous | Muñecas | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 426065 | Infusion of Light | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 458318 | Malleable Protection | Cintura | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426158 | Sheath of Light | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415059 | Guarded by the Light | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426157 | The Art of War | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 429142 | Fanaticism | Cabeza | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 429133 | Improved Sanctuary | Cabeza | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440672 | Righteous Vengeance | Espalda | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 462834 | Shock and Awe | Espalda | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425589 | Aegis | Pecho | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462853 | Hand of Sacrifice | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425609 | Rebuke | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407631 | Hand of Reckoning | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412019 | Sacred Shield | Pies | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 429139 | Wrath | Cabeza | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 458856 | Divine Light | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 440658 | Shield of Righteousness | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Pícaro: runas pendientes (27)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 462708 | Cutthroat | Manos | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 424785 | Saber Slash | Manos | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 400029 | Shadowstep | Cintura | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 408700 | Waylay | Pies | Talento | T | Tiene una probabilidad de proc configurada. |
| 432259 | Combat Potency | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 432256 | Focused Attacks | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 432264 | Honor Among Thieves | Cabeza | Talento | T | Tiene una probabilidad de proc configurada. |
| 399965 | Deadly Brew | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400014 | Just a Flesh Wound | Pecho | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 398196 | Quick Draw | Pecho | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 424925 | Slaughter from the Shadows | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400009 | Between the Eyes | Piernas | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 424919 | Main Gauche | Manos | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 432276 | Carnage | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432271 | Cut to the Chase | Muñecas | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432273 | Unfair Advantage | Muñecas | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425012 | Poisoned Knife | Cintura | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 399986 | Shuriken Toss | Cintura | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425096 | Master of Subtlety | Pies | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400016 | Rolling with the Punches | Pies | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 436564 | Blunderbuss | Espalda | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 412096 | Crimson Tempest | Espalda | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 400012 | Blade Dance | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 399963 | Envenom | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 399985 | Shadowstrike | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409240 | Fan of Knives | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409240 | Fan of Knives | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Sacerdote: runas pendientes (25)

| ID | Nombre | Ranura | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|
| 401969 | Shared Pain | Piernas | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431670 | Despair | Muñecas | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 413248 | Serendipity | Pecho | Talento | T | Tiene una probabilidad de proc configurada. |
| 415739 | Strength of Soul | Pecho | Sin equivalente | T | Uno de sus efectos dispara otro hechizo. |
| 431664 | Surge of Light | Muñecas | Talento | T | Tiene una probabilidad de proc configurada. |
| 413251 | Pain and Suffering | Cabeza | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 425198 | Twisted Faith | Pecho | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402799 | Homunculi | Piernas | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425207 | Power Word: Barrier | Muñecas | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425266 | Empowered Renew | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 431655 | Mind Spike | Cintura | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425280 | Renewed Hope | Cintura | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425294 | Dispersion | Pies | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 402004 | Pain Suppression | Pies | Talento | C | La descripción indica una mecánica compleja («stance»). |
| 425284 | Spirit of the Redeemer | Pies | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425204 | Void Plague | Pies | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 431622 | Divine Aegis | Cabeza | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402789 | Eye of the Void | Cabeza | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 402000 | Soul Warding | Espalda | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402668 | Vampiric Touch | Espalda | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 401859 | Prayer of Mending | Piernas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 413259 | Mind Sear | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401955 | Shadow Word: Death | Manos | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 431681 | Void Zone | Muñecas | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401937 | Binding Heal | Espalda | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Raciales y ruido (sin clasificar)

- **Raciales (11, slot_id 459695 y 1219274):** fuera del sistema de grabado de runas; no se les asigna nivel.
- **Ruido (188):** `slot_id` ajeno a las ocho ranuras y a Soul Engraving; no se les asigna nivel.
