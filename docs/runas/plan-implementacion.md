# Plan de implementación de runas de fase 1

Se incluyen runas de tipo talento y sin equivalente que aún no están implementadas. Las runas activas ya disponibles en WotLK quedan fuera del plan.

## Resumen por nivel

| Nivel | Runas |
|---|---:|
| P — Pasiva | 8 |
| T — Proc o trigger | 14 |
| C — Requiere C++ | 37 |

## Resumen por clase

| Clase | P | T | C | Total |
|---|---:|---:|---:|---:|
| Brujo | 1 | 1 | 5 | 7 |
| Cazador | 1 | 4 | 5 | 10 |
| Chamán | 1 | 0 | 6 | 7 |
| Druida | 3 | 1 | 4 | 8 |
| Guerrero | 0 | 2 | 8 | 10 |
| Mago | 1 | 0 | 0 | 1 |
| Paladín | 0 | 2 | 1 | 3 |
| Pícaro | 0 | 2 | 6 | 8 |
| Sacerdote | 1 | 2 | 2 | 5 |
| **Total** | 8 | 14 | 37 | 59 |

Los casos que no encajan en las reglas simples se asignan a C por prudencia.

## P — Pasivas (8)

| Clase | Runa | Ranura | Tipo | Razón |
|---|---|---|---|---|
| Druida | Survival of the Fittest | Pecho | Talento | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Druida | Mangle | Manos | Talento | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Druida | Sunfire | Manos | Sin equivalente | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Cazador | Master Marksman | Pecho | Talento | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Mago | Living Bomb | Manos | Talento | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Sacerdote | Shared Pain | Piernas | Sin equivalente | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Chamán | Greater Ghost Wolf | Piernas | Sin equivalente | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| Brujo | Demonic Tactics | Pecho | Talento | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |

## T — Proc o trigger (14)

| Clase | Runa | Ranura | Tipo | Razón |
|---|---|---|---|---|
| Druida | Fury of Stormrage | Pecho | Sin equivalente | Tiene una probabilidad de proc configurada. |
| Cazador | Cobra Strikes | Pecho | Talento | Tiene una probabilidad de proc configurada. |
| Cazador | Lone Wolf | Pecho | Sin equivalente | Tiene una probabilidad de proc configurada. |
| Cazador | Sniper Training | Piernas | Talento | Usa un aura asociada a proc o activación. |
| Cazador | Explosive Shot | Manos | Talento | Usa un aura asociada a proc o activación. |
| Paladín | Inspiration Exemplar | Piernas | Sin equivalente | Usa un aura asociada a proc o activación. |
| Paladín | Beacon of Light | Manos | Talento | Uno de sus efectos dispara otro hechizo. |
| Sacerdote | Serendipity | Pecho | Talento | Tiene una probabilidad de proc configurada. |
| Sacerdote | Strength of Soul | Pecho | Sin equivalente | Uno de sus efectos dispara otro hechizo. |
| Pícaro | Cutthroat | Manos | Sin equivalente | Tiene una probabilidad de proc configurada. |
| Pícaro | Saber Slash | Manos | Sin equivalente | Tiene una probabilidad de proc configurada. |
| Brujo | Everlasting Affliction | Piernas | Talento | Uno de sus efectos dispara otro hechizo. |
| Guerrero | Consumed By Rage | Piernas | Sin equivalente | Uno de sus efectos dispara otro hechizo. |
| Guerrero | Single-Minded Fury | Manos | Sin equivalente | Usa un aura asociada a proc o activación. |

## C — Requiere C++ (37)

| Clase | Runa | Ranura | Tipo | Razón |
|---|---|---|---|---|
| Druida | Living Seed | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Druida | Wild Strikes | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Druida | Starsurge | Piernas | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Druida | Skull Bash | Manos | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Cazador | Beast Mastery | Pecho | Talento | La descripción indica una mecánica compleja («taunt»). |
| Cazador | Flanking Strike | Piernas | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Cazador | Serpent Spread | Piernas | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Cazador | Carve | Manos | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Cazador | Cobra Slayer | Manos | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Paladín | Hallowed Ground | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Sacerdote | Twisted Faith | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Sacerdote | Homunculi | Piernas | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Pícaro | Deadly Brew | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Pícaro | Just a Flesh Wound | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Pícaro | Quick Draw | Pecho | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Pícaro | Slaughter from the Shadows | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Pícaro | Between the Eyes | Piernas | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Pícaro | Main Gauche | Manos | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Chamán | Dual Wield Specialization | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Chamán | Healing Rain | Pecho | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Chamán | Shield Mastery | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Chamán | Two-Handed Mastery | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Chamán | Ancestral Guidance | Piernas | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Chamán | Way of Earth | Piernas | Sin equivalente | La descripción indica una mecánica compleja («taunt»). |
| Brujo | Lake of Fire | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Brujo | Master Channeler | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Brujo | Demonic Grace | Piernas | Sin equivalente | Es una habilidad activa nueva sin equivalente en WotLK. |
| Brujo | Demonic Pact | Piernas | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Brujo | Metamorphosis | Manos | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Guerrero | Blood Frenzy | Pecho | Talento | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Guerrero | Flagellation | Pecho | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Guerrero | Raging Blow | Pecho | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Guerrero | Warbringer | Pecho | Talento | La descripción indica una mecánica compleja («stance»). |
| Guerrero | Frenzied Assault | Piernas | Sin equivalente | Incluye un aura DUMMY y requiere lógica propia en C++. |
| Guerrero | Furious Thunder | Piernas | Sin equivalente | La descripción indica una mecánica compleja («stance»). |
| Guerrero | Meathook | Piernas | Sin equivalente | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| Guerrero | Quick Strike | Manos | Sin equivalente | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
