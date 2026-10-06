# Plan de implementación de runas de SoD

El plan incluye las filas del catálogo de todas las clases y ranuras. Los emparejamientos nuevos usan el nombre inglés exacto en los DBC locales; las coincidencias ya documentadas se conservan.

P = pasiva sencilla; T = proc o disparo; C = requiere C++ o no encaja en las reglas; R = equivalente activo por nombre en WotLK, pendiente de decisión. Las filas de clase desconocida quedan sin clasificar.

Las fases solo se asignan cuando el nombre de ranura del catálogo lo permite: pecho, piernas y manos = fase 1; muñecas, cintura y pies = fase 2; cabeza = fase 3. No se deduce una fase para cuello ni para identificadores `slot_<id>`. 

## Resumen por fase

| Fase | Pendientes | Implementadas | Total |
|---|---:|---:|---:|
| Fase 1 | 77 | 29 | 106 |
| desconocida | 554 | 1 | 555 |

## Resumen por clase

| Clase | P | T | C | R | Sin clasificar | Implementadas | Total |
|---|---:|---:|---:|---:|---:|---:|---:|
| Brujo | 1 | 3 | 20 | 27 | 0 | 3 | 54 |
| Caballero de la Muerte | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Cazador | 3 | 5 | 15 | 31 | 0 | 3 | 57 |
| Chamán | 1 | 3 | 15 | 26 | 0 | 2 | 47 |
| Druida | 14 | 3 | 11 | 32 | 0 | 2 | 62 |
| Guerrero | 3 | 8 | 15 | 10 | 0 | 1 | 37 |
| Mago | 3 | 2 | 9 | 28 | 0 | 11 | 53 |
| Paladín | 1 | 4 | 11 | 20 | 0 | 5 | 41 |
| Pícaro | 0 | 7 | 20 | 27 | 0 | 1 | 55 |
| Sacerdote | 2 | 7 | 14 | 24 | 0 | 2 | 49 |
| Desconocida | 0 | 0 | 0 | 0 | 206 | 0 | 206 |

## Ranuras encontradas por clase

Se conserva el identificador `slot_<id>` cuando el catálogo no proporciona un nombre.

| Ranura | Fase | Clase | Runas |
|---|---|---|---:|
| Pecho | Fase 1 | Druida | 4 |
| Pecho | Fase 1 | Cazador | 4 |
| Pecho | Fase 1 | Mago | 4 |
| Pecho | Fase 1 | Paladín | 3 |
| Pecho | Fase 1 | Sacerdote | 3 |
| Pecho | Fase 1 | Pícaro | 4 |
| Pecho | Fase 1 | Chamán | 5 |
| Pecho | Fase 1 | Brujo | 3 |
| Pecho | Fase 1 | Guerrero | 4 |
| Piernas | Fase 1 | Druida | 4 |
| Piernas | Fase 1 | Cazador | 4 |
| Piernas | Fase 1 | Mago | 4 |
| Piernas | Fase 1 | Paladín | 6 |
| Piernas | Fase 1 | Sacerdote | 3 |
| Piernas | Fase 1 | Pícaro | 3 |
| Piernas | Fase 1 | Chamán | 4 |
| Piernas | Fase 1 | Brujo | 3 |
| Piernas | Fase 1 | Guerrero | 5 |
| Manos | Fase 1 | Druida | 4 |
| Manos | Fase 1 | Cazador | 4 |
| Manos | Fase 1 | Mago | 3 |
| Manos | Fase 1 | Paladín | 3 |
| Manos | Fase 1 | Sacerdote | 4 |
| Manos | Fase 1 | Pícaro | 5 |
| Manos | Fase 1 | Chamán | 5 |
| Manos | Fase 1 | Brujo | 4 |
| Manos | Fase 1 | Guerrero | 4 |
| slot_0 | desconocida | Druida | 4 |
| slot_0 | desconocida | Paladín | 1 |
| slot_0 | desconocida | Sacerdote | 1 |
| slot_0 | desconocida | Pícaro | 1 |
| slot_0 | desconocida | Guerrero | 1 |
| slot_10177 | desconocida | Mago | 1 |
| slot_10191 | desconocida | Mago | 1 |
| slot_10192 | desconocida | Mago | 1 |
| slot_10193 | desconocida | Mago | 1 |
| slot_10197 | desconocida | Mago | 1 |
| slot_10199 | desconocida | Mago | 1 |
| slot_10223 | desconocida | Mago | 1 |
| slot_10225 | desconocida | Mago | 1 |
| slot_10312 | desconocida | Paladín | 1 |
| slot_10313 | desconocida | Paladín | 1 |
| slot_10314 | desconocida | Paladín | 1 |
| slot_10318 | desconocida | Paladín | 1 |
| slot_10412 | desconocida | Chamán | 1 |
| slot_10413 | desconocida | Chamán | 1 |
| slot_10414 | desconocida | Chamán | 1 |
| slot_1058 | desconocida | Druida | 1 |
| slot_1082 | desconocida | Druida | 1 |
| slot_1088 | desconocida | Brujo | 1 |
| slot_10927 | desconocida | Sacerdote | 1 |
| slot_10928 | desconocida | Sacerdote | 1 |
| slot_10929 | desconocida | Sacerdote | 1 |
| slot_1106 | desconocida | Brujo | 1 |
| slot_11267 | desconocida | Pícaro | 1 |
| slot_11268 | desconocida | Pícaro | 1 |
| slot_11269 | desconocida | Pícaro | 1 |
| slot_11279 | desconocida | Pícaro | 1 |
| slot_11280 | desconocida | Pícaro | 1 |
| slot_11281 | desconocida | Pícaro | 1 |
| slot_11289 | desconocida | Pícaro | 1 |
| slot_11290 | desconocida | Pícaro | 1 |
| slot_11303 | desconocida | Pícaro | 1 |
| slot_11314 | desconocida | Chamán | 1 |
| slot_11315 | desconocida | Chamán | 1 |
| slot_11580 | desconocida | Guerrero | 1 |
| slot_11581 | desconocida | Guerrero | 1 |
| slot_11659 | desconocida | Brujo | 1 |
| slot_11660 | desconocida | Brujo | 1 |
| slot_11661 | desconocida | Brujo | 1 |
| slot_11677 | desconocida | Brujo | 1 |
| slot_11678 | desconocida | Brujo | 1 |
| slot_11699 | desconocida | Brujo | 1 |
| slot_11700 | desconocida | Brujo | 1 |
| slot_1219274 | desconocida | Sacerdote | 2 |
| slot_1219955 | desconocida | Desconocida | 206 |
| slot_13795 | desconocida | Cazador | 1 |
| slot_13809 | desconocida | Cazador | 1 |
| slot_13813 | desconocida | Cazador | 1 |
| slot_139 | desconocida | Sacerdote | 1 |
| slot_14260 | desconocida | Cazador | 1 |
| slot_14261 | desconocida | Cazador | 1 |
| slot_14262 | desconocida | Cazador | 1 |
| slot_14263 | desconocida | Cazador | 1 |
| slot_14264 | desconocida | Cazador | 1 |
| slot_14265 | desconocida | Cazador | 1 |
| slot_14266 | desconocida | Cazador | 1 |
| slot_1430 | desconocida | Druida | 1 |
| slot_14302 | desconocida | Cazador | 1 |
| slot_14303 | desconocida | Cazador | 1 |
| slot_14304 | desconocida | Cazador | 1 |
| slot_14305 | desconocida | Cazador | 1 |
| slot_14310 | desconocida | Cazador | 1 |
| slot_14311 | desconocida | Cazador | 1 |
| slot_14316 | desconocida | Cazador | 1 |
| slot_14317 | desconocida | Cazador | 1 |
| slot_1463 | desconocida | Mago | 1 |
| slot_1499 | desconocida | Cazador | 1 |
| slot_1515 | desconocida | Cazador | 4 |
| slot_1535 | desconocida | Chamán | 1 |
| slot_16316 | desconocida | Chamán | 1 |
| slot_16342 | desconocida | Chamán | 1 |
| slot_16356 | desconocida | Chamán | 1 |
| slot_16362 | desconocida | Chamán | 1 |
| slot_18647 | desconocida | Brujo | 1 |
| slot_19386 | desconocida | Cazador | 1 |
| slot_1966 | desconocida | Pícaro | 1 |
| slot_19801 | desconocida | Cazador | 1 |
| slot_2090 | desconocida | Druida | 1 |
| slot_2091 | desconocida | Druida | 1 |
| slot_2136 | desconocida | Mago | 1 |
| slot_2137 | desconocida | Mago | 1 |
| slot_2138 | desconocida | Mago | 1 |
| slot_22812 | desconocida | Druida | 1 |
| slot_24132 | desconocida | Cazador | 1 |
| slot_24133 | desconocida | Cazador | 1 |
| slot_25299 | desconocida | Druida | 1 |
| slot_25300 | desconocida | Pícaro | 1 |
| slot_25302 | desconocida | Pícaro | 1 |
| slot_25307 | desconocida | Brujo | 1 |
| slot_25315 | desconocida | Sacerdote | 1 |
| slot_25780 | desconocida | Paladín | 1 |
| slot_2589 | desconocida | Pícaro | 1 |
| slot_2590 | desconocida | Pícaro | 1 |
| slot_2591 | desconocida | Pícaro | 1 |
| slot_2645 | desconocida | Chamán | 1 |
| slot_2812 | desconocida | Paladín | 1 |
| slot_28609 | desconocida | Mago | 1 |
| slot_2973 | desconocida | Cazador | 1 |
| slot_3029 | desconocida | Druida | 1 |
| slot_3627 | desconocida | Druida | 1 |
| slot_412783 | desconocida | Brujo | 1 |
| slot_412784 | desconocida | Brujo | 1 |
| slot_415449 | desconocida | Druida | 3 |
| slot_415449 | desconocida | Cazador | 5 |
| slot_415449 | desconocida | Mago | 4 |
| slot_415449 | desconocida | Paladín | 3 |
| slot_415449 | desconocida | Sacerdote | 3 |
| slot_415449 | desconocida | Pícaro | 3 |
| slot_415449 | desconocida | Chamán | 3 |
| slot_415449 | desconocida | Brujo | 3 |
| slot_415449 | desconocida | Guerrero | 3 |
| slot_415450 | desconocida | Druida | 3 |
| slot_415450 | desconocida | Cazador | 3 |
| slot_415450 | desconocida | Mago | 3 |
| slot_415450 | desconocida | Paladín | 3 |
| slot_415450 | desconocida | Sacerdote | 4 |
| slot_415450 | desconocida | Pícaro | 3 |
| slot_415450 | desconocida | Chamán | 3 |
| slot_415450 | desconocida | Brujo | 4 |
| slot_415450 | desconocida | Guerrero | 4 |
| slot_417345 | desconocida | Druida | 3 |
| slot_417345 | desconocida | Cazador | 3 |
| slot_417345 | desconocida | Mago | 4 |
| slot_417345 | desconocida | Paladín | 3 |
| slot_417345 | desconocida | Sacerdote | 3 |
| slot_417345 | desconocida | Pícaro | 3 |
| slot_417345 | desconocida | Chamán | 3 |
| slot_417345 | desconocida | Brujo | 3 |
| slot_417345 | desconocida | Guerrero | 4 |
| slot_417346 | desconocida | Druida | 3 |
| slot_417346 | desconocida | Cazador | 3 |
| slot_417346 | desconocida | Mago | 4 |
| slot_417346 | desconocida | Paladín | 4 |
| slot_417346 | desconocida | Sacerdote | 4 |
| slot_417346 | desconocida | Pícaro | 3 |
| slot_417346 | desconocida | Chamán | 4 |
| slot_417346 | desconocida | Brujo | 4 |
| slot_417346 | desconocida | Guerrero | 3 |
| slot_417347 | desconocida | Druida | 3 |
| slot_417347 | desconocida | Cazador | 3 |
| slot_417347 | desconocida | Mago | 3 |
| slot_417347 | desconocida | Paladín | 4 |
| slot_417347 | desconocida | Sacerdote | 3 |
| slot_417347 | desconocida | Pícaro | 4 |
| slot_417347 | desconocida | Chamán | 3 |
| slot_417347 | desconocida | Brujo | 3 |
| slot_417347 | desconocida | Guerrero | 3 |
| slot_417437 | desconocida | Druida | 1 |
| slot_459695 | desconocida | Sacerdote | 9 |
| slot_475 | desconocida | Mago | 1 |
| slot_498 | desconocida | Paladín | 1 |
| slot_5201 | desconocida | Druida | 1 |
| slot_5217 | desconocida | Druida | 1 |
| slot_53 | desconocida | Pícaro | 1 |
| slot_543 | desconocida | Mago | 1 |
| slot_5573 | desconocida | Paladín | 1 |
| slot_5614 | desconocida | Paladín | 1 |
| slot_5615 | desconocida | Paladín | 1 |
| slot_5740 | desconocida | Brujo | 1 |
| slot_5782 | desconocida | Brujo | 1 |
| slot_6074 | desconocida | Sacerdote | 1 |
| slot_6075 | desconocida | Sacerdote | 1 |
| slot_6076 | desconocida | Sacerdote | 1 |
| slot_6077 | desconocida | Sacerdote | 1 |
| slot_6078 | desconocida | Sacerdote | 1 |
| slot_6143 | desconocida | Mago | 1 |
| slot_6213 | desconocida | Brujo | 1 |
| slot_6215 | desconocida | Brujo | 1 |
| slot_6219 | desconocida | Brujo | 1 |
| slot_6343 | desconocida | Guerrero | 1 |
| slot_6768 | desconocida | Pícaro | 1 |
| slot_6793 | desconocida | Druida | 1 |
| slot_686 | desconocida | Brujo | 1 |
| slot_689 | desconocida | Brujo | 1 |
| slot_695 | desconocida | Brujo | 1 |
| slot_699 | desconocida | Brujo | 1 |
| slot_703 | desconocida | Pícaro | 1 |
| slot_705 | desconocida | Brujo | 1 |
| slot_709 | desconocida | Brujo | 1 |
| slot_710 | desconocida | Brujo | 1 |
| slot_7641 | desconocida | Brujo | 1 |
| slot_7651 | desconocida | Brujo | 1 |
| slot_774 | desconocida | Druida | 1 |
| slot_8042 | desconocida | Chamán | 1 |
| slot_8044 | desconocida | Chamán | 1 |
| slot_8045 | desconocida | Chamán | 1 |
| slot_8046 | desconocida | Chamán | 1 |
| slot_8198 | desconocida | Guerrero | 1 |
| slot_8204 | desconocida | Guerrero | 1 |
| slot_8205 | desconocida | Guerrero | 1 |
| slot_8412 | desconocida | Mago | 1 |
| slot_8413 | desconocida | Mago | 1 |
| slot_8457 | desconocida | Mago | 1 |
| slot_8458 | desconocida | Mago | 1 |
| slot_8461 | desconocida | Mago | 1 |
| slot_8462 | desconocida | Mago | 1 |
| slot_8494 | desconocida | Mago | 1 |
| slot_8495 | desconocida | Mago | 1 |
| slot_8498 | desconocida | Chamán | 1 |
| slot_8499 | desconocida | Chamán | 1 |
| slot_8631 | desconocida | Pícaro | 1 |
| slot_8632 | desconocida | Pícaro | 1 |
| slot_8633 | desconocida | Pícaro | 1 |
| slot_8637 | desconocida | Pícaro | 1 |
| slot_8676 | desconocida | Pícaro | 1 |
| slot_8721 | desconocida | Pícaro | 1 |
| slot_8724 | desconocida | Pícaro | 1 |
| slot_8725 | desconocida | Pícaro | 1 |
| slot_879 | desconocida | Paladín | 1 |
| slot_8910 | desconocida | Druida | 1 |
| slot_8936 | desconocida | Druida | 1 |
| slot_8938 | desconocida | Druida | 1 |
| slot_8939 | desconocida | Druida | 1 |
| slot_8940 | desconocida | Druida | 1 |
| slot_8941 | desconocida | Druida | 1 |
| slot_9750 | desconocida | Druida | 1 |
| slot_9839 | desconocida | Druida | 1 |
| slot_9840 | desconocida | Druida | 1 |
| slot_9841 | desconocida | Druida | 1 |
| slot_9845 | desconocida | Druida | 1 |
| slot_9846 | desconocida | Druida | 1 |
| slot_9849 | desconocida | Druida | 1 |
| slot_9850 | desconocida | Druida | 1 |
| slot_9856 | desconocida | Druida | 1 |
| slot_9857 | desconocida | Druida | 1 |
| slot_9858 | desconocida | Druida | 1 |

## Brujo: runas no implementadas (51)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 427712 | Pandemic | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 412689 | Everlasting Affliction | Piernas | Fase 1 | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 426316 | Shadow and Flame | slot_415449 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 427713 | Backdraft | slot_417345 | desconocida | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 403666 | Lake of Fire | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403668 | Master Channeler | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425463 | Demonic Grace | Piernas | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425464 | Demonic Pact | Piernas | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403789 | Metamorphosis | Manos | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412789 | Demonic Howl | slot_412784 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 1226981 | Grimoire of Synergy | slot_415449 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426243 | Invocation | slot_415449 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412798 | Dance of the Wicked | slot_415450 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440870 | Decimation | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412732 | Demonic Knowledge | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426195 | Vengeance | slot_417345 | desconocida | Talento | C | La descripción indica una mecánica compleja («metamorphosis»). |
| 427733 | Summon Felguard | slot_417346 | desconocida | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 427717 | Unstable Affliction | slot_417346 | desconocida | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440882 | Infernal Armor | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440892 | Mark of Chaos | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403511 | Soul Siphon | slot_417347 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403828 | Menace | slot_5782 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 442226 | Menace | slot_6213 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 442233 | Menace | slot_6215 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 403628 | Shadow Bolt Volley | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403841 | Shadow Cleave | slot_1088 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403842 | Shadow Cleave | slot_1106 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403844 | Shadow Cleave | slot_11659 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403848 | Shadow Cleave | slot_11660 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403851 | Shadow Cleave | slot_11661 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 460699 | Rain of Fire | slot_11677 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 460700 | Rain of Fire | slot_11678 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403688 | Drain Life | slot_11699 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403689 | Drain Life | slot_11700 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 465352 | Banish | slot_18647 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403852 | Shadow Cleave | slot_25307 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412788 | Demon Charge | slot_412783 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 426320 | Shadowflame | slot_415450 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 427726 | Immolation Aura | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412758 | Incinerate | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 460692 | Rain of Fire | slot_5740 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 460698 | Rain of Fire | slot_6219 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403835 | Shadow Cleave | slot_686 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403677 | Drain Life | slot_689 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403839 | Shadow Cleave | slot_695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403685 | Drain Life | slot_699 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403840 | Shadow Cleave | slot_705 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403686 | Drain Life | slot_709 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 457569 | Banish | slot_710 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403843 | Shadow Cleave | slot_7641 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 403687 | Drain Life | slot_7651 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Caballero de la Muerte: runas no implementadas (0)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|

## Cazador: runas no implementadas (54)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 458479 | Wyvern Strike | slot_415450 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 415428 | Catlike Reflexes | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 440529 | Resourcefulness | slot_417347 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 425713 | Cobra Strikes | Pecho | Fase 1 | Talento | T | Tiene una probabilidad de proc configurada. |
| 415370 | Lone Wolf | Pecho | Fase 1 | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 415399 | Sniper Training | Piernas | Fase 1 | Talento | T | Usa un aura asociada a proc o activación. |
| 409504 | Expose Weakness | slot_415449 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 415405 | Rapid Killing | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 409368 | Beast Mastery | Pecho | Fase 1 | Talento | C | La descripción indica una mecánica compleja («taunt»). |
| 415320 | Flanking Strike | Piernas | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 425738 | Serpent Spread | Piernas | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425711 | Carve | Manos | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 458393 | Cobra Slayer | Manos | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 458436 | Wyvern Strike | slot_19386 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 458481 | Wyvern Strike | slot_24132 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 458482 | Wyvern Strike | slot_24133 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 415352 | Melee Specialist | slot_415449 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409687 | Dual Wield Specialization | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415413 | Lock and Load | slot_417345 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415358 | Raptor Fury | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 428717 | T.N.T. | slot_417346 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440533 | Hit and Run | slot_417347 | desconocida | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440520 | Improved Volley | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409593 | Kill Shot | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409521 | Immolation Trap | slot_13795 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409520 | Frost Trap | slot_13809 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409532 | Explosive Trap | slot_13813 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415336 | Raptor Strike | slot_14260 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415337 | Raptor Strike | slot_14261 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415338 | Raptor Strike | slot_14262 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415340 | Raptor Strike | slot_14263 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415341 | Raptor Strike | slot_14264 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415342 | Raptor Strike | slot_14265 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415343 | Raptor Strike | slot_14266 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409524 | Immolation Trap | slot_14302 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409526 | Immolation Trap | slot_14303 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409528 | Immolation Trap | slot_14304 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409530 | Immolation Trap | slot_14305 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409512 | Freezing Trap | slot_14310 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409519 | Freezing Trap | slot_14311 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409534 | Explosive Trap | slot_14316 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409535 | Explosive Trap | slot_14317 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409510 | Freezing Trap | slot_1499 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 411624 | Tame Beast | slot_1515 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 411624 | Tame Beast | slot_1515 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 411624 | Tame Beast | slot_1515 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 411624 | Tame Beast | slot_1515 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 1218134 | Tranquilizing Shot | slot_19801 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415335 | Raptor Strike | slot_2973 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415423 | Aspect of the Viper | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409593 | Kill Shot | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 437123 | Steady Shot | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409541 | Trap Launcher | slot_415450 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428726 | Focus Fire | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Chamán: runas no implementadas (45)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 415813 | Greater Ghost Wolf | Piernas | Fase 1 | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 408696 | Spirit of the Alpha | slot_415450 | desconocida | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 432042 | Tidal Waves | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 432134 | Static Shock | slot_417346 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 408496 | Dual Wield Specialization | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415236 | Healing Rain | Pecho | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 408524 | Shield Mastery | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 436364 | Two-Handed Mastery | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 409324 | Ancestral Guidance | Piernas | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408531 | Way of Earth | Piernas | Fase 1 | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 408498 | Maelstrom Weapon | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425858 | Ancestral Awakening | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425874 | Decoy Totem | slot_415450 | desconocida | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 415140 | Mental Dexterity | slot_417345 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408521 | Riptide | slot_417346 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432056 | Rolling Thunder | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415096 | Coherence | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440580 | Feral Spirit | slot_417347 | desconocida | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 440569 | Storm, Earth, and Fire | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408438 | Overload | Pecho | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408490 | Lava Burst | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425339 | Molten Blast | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408307 | Nature's Fury | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408510 | Water Shield | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408688 | Earth Shock | slot_10412 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408689 | Earth Shock | slot_10413 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408690 | Earth Shock | slot_10414 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408344 | Fire Nova | slot_11314 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408345 | Fire Nova | slot_11315 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408341 | Fire Nova | slot_1535 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461635 | Rockbiter Weapon | slot_16316 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461634 | Flametongue Weapon | slot_16342 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461633 | Frostbrand Weapon | slot_16356 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461636 | Windfury Weapon | slot_16362 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415233 | Ghost Wolf | slot_2645 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408339 | Fire Nova | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415100 | Power Surge | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415231 | Burn | slot_417345 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 432140 | Overcharged | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408681 | Earth Shock | slot_8042 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408683 | Earth Shock | slot_8044 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408685 | Earth Shock | slot_8045 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408687 | Earth Shock | slot_8046 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408342 | Fire Nova | slot_8498 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408343 | Fire Nova | slot_8499 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Druida: runas no implementadas (60)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 407995 | Mangle | Manos | Fase 1 | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414684 | Sunfire | Manos | Fase 1 | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414687 | Sunfire | slot_0 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414689 | Sunfire | slot_0 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407993 | Mangle | slot_1082 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407993 | Mangle | slot_3029 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 417135 | Gale Winds | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431388 | Improved Barkskin | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431389 | Improved Frenzied Regeneration | slot_417346 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 439510 | Improved Swipe | slot_417347 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 417448 | Thrash (Cat) | slot_417437 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407993 | Mangle | slot_5201 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407993 | Mangle | slot_9849 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407993 | Mangle | slot_9850 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 414799 | Fury of Stormrage | Pecho | Fase 1 | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 408258 | Dreamstate | slot_415450 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 439733 | Tree of Life | slot_417347 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 414677 | Living Seed | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 407977 | Wild Strikes | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 417157 | Starsurge | Piernas | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 410176 | Skull Bash | Manos | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 417141 | Berserk | slot_415449 | desconocida | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 408248 | Eclipse | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 417046 | King of the Jungle | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 408024 | Survival Instincts | slot_415450 | desconocida | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 417149 | Efflorescence | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 414719 | Elune's Fires | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 439748 | Starfall | slot_417347 | desconocida | Talento | C | La descripción indica una mecánica compleja («summon»). |
| 414644 | Lacerate | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408124 | Lifebloom | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407988 | Savage Roar | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428708 | Frenzied Regeneration | slot_0 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 411128 | Swipe | slot_0 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417058 | Rejuvenation | slot_1058 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417059 | Rejuvenation | slot_1430 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417060 | Rejuvenation | slot_2090 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417061 | Rejuvenation | slot_2091 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428713 | Barkskin | slot_22812 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417068 | Rejuvenation | slot_25299 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417062 | Rejuvenation | slot_3627 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 408247 | Nourish | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417145 | Gore | slot_417345 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417045 | Tiger's Fury | slot_5217 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417045 | Tiger's Fury | slot_6793 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417057 | Rejuvenation | slot_774 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417063 | Rejuvenation | slot_8910 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436937 | Regrowth | slot_8936 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436938 | Regrowth | slot_8938 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436939 | Regrowth | slot_8939 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436940 | Regrowth | slot_8940 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436942 | Regrowth | slot_8941 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436943 | Regrowth | slot_9750 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417064 | Rejuvenation | slot_9839 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417065 | Rejuvenation | slot_9840 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417066 | Rejuvenation | slot_9841 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417045 | Tiger's Fury | slot_9845 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 417045 | Tiger's Fury | slot_9846 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436944 | Regrowth | slot_9856 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436945 | Regrowth | slot_9857 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 436946 | Regrowth | slot_9858 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Guerrero: runas no implementadas (36)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 29787 | Focused Rage | slot_415449 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 402922 | Precise Timing | slot_415449 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 403218 | Endless Rage | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 425418 | Consumed By Rage | Piernas | Fase 1 | Sin equivalente | T | Uno de sus efectos dispara otro hechizo. |
| 413404 | Single-Minded Fury | Manos | Fase 1 | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 413380 | Blood Surge | slot_415449 | desconocida | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 403338 | Intervene | slot_415450 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 426980 | Shield Mastery | slot_417345 | desconocida | Talento | T | Usa un aura asociada a proc o activación. |
| 426953 | Taste for Blood | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 426978 | Sword and Board | slot_417346 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 427065 | Wrecking Crew | slot_417346 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 412507 | Blood Frenzy | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402877 | Flagellation | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402911 | Raging Blow | Pecho | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 425421 | Warbringer | Pecho | Fase 1 | Talento | C | La descripción indica una mecánica compleja («stance»). |
| 425412 | Frenzied Assault | Piernas | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403219 | Furious Thunder | Piernas | Fase 1 | Sin equivalente | C | La descripción indica una mecánica compleja («stance»). |
| 403228 | Meathook | Piernas | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 429765 | Quick Strike | Manos | Fase 1 | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 429765 | Quick Strike | slot_0 | desconocida | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412513 | Gladiator Stance | slot_415450 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («stance»). |
| 426972 | Vigilance | slot_417345 | desconocida | Talento | C | La descripción indica una mecánica compleja («taunt»). |
| 426940 | Rampage | slot_417346 | desconocida | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 440484 | Fresh Meat | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 440488 | Shockwave | slot_417347 | desconocida | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440113 | Sudden Death | slot_417347 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 403215 | Commanding Shout | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 402927 | Victory Rush | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461826 | Thunder Clap | slot_11580 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461810 | Thunder Clap | slot_11581 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 402913 | Enraged Regeneration | slot_415450 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 426490 | Rallying Cry | slot_415450 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461830 | Thunder Clap | slot_6343 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461829 | Thunder Clap | slot_8198 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461828 | Thunder Clap | slot_8204 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 461827 | Thunder Clap | slot_8205 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Mago: runas no implementadas (42)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 400613 | Living Bomb | Manos | Fase 1 | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 412322 | Spell Power | slot_415450 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 428739 | Deep Freeze | slot_417345 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 400588 | Missile Barrage | slot_415449 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 400731 | Brain Freeze | slot_415450 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 409069 | — | slot_415449 | desconocida | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412532 | Spellfrost Bolt | slot_415449 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 436516 | Chronostatic Preservation | slot_415450 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 412115 | Advanced Warding | slot_417345 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400624 | Hot Streak | slot_417345 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 428885 | Temporal Anomaly | slot_417345 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 428878 | Balefire Bolt | slot_417346 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 400610 | Arcane Barrage | slot_417347 | desconocida | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412113 | Remove Greater Curse | slot_475 | desconocida | Sin equivalente | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 412209 | Frost Ward | slot_10177 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412121 | Mana Shield | slot_10191 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412122 | Mana Shield | slot_10192 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412123 | Mana Shield | slot_10193 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400622 | Fire Blast | slot_10197 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400623 | Fire Blast | slot_10199 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412231 | Fire Ward | slot_10223 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412232 | Fire Ward | slot_10225 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412116 | Mana Shield | slot_1463 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400618 | Fire Blast | slot_2136 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400619 | Fire Blast | slot_2137 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400616 | Fire Blast | slot_2138 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412210 | Frost Ward | slot_28609 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401502 | Frostfire Bolt | slot_415449 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428861 | Displacement | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 428741 | Molten Armor | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 440802 | Frozen Orb | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400615 | Overheat | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412214 | Fire Ward | slot_543 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412202 | Frost Ward | slot_6143 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400620 | Fire Blast | slot_8412 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 400621 | Fire Blast | slot_8413 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412218 | Fire Ward | slot_8457 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412230 | Fire Ward | slot_8458 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412205 | Frost Ward | slot_8461 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412207 | Frost Ward | slot_8462 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412118 | Mana Shield | slot_8494 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412120 | Mana Shield | slot_8495 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Paladín: runas no implementadas (36)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 429144 | Purifying Power | slot_417346 | desconocida | Talento | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 407880 | Inspiration Exemplar | Piernas | Fase 1 | Sin equivalente | T | Usa un aura asociada a proc o activación. |
| 407613 | Beacon of Light | Manos | Fase 1 | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 429152 | Improved Hammer of Wrath | slot_417346 | desconocida | Pasivo | T | Tiene una probabilidad de proc configurada. |
| 428909 | Light's Grace | slot_417346 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 458287 | Hallowed Ground | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426065 | Infusion of Light | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 458318 | Malleable Protection | slot_415449 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426158 | Sheath of Light | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 415059 | Guarded by the Light | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 426157 | The Art of War | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 429142 | Fanaticism | slot_417345 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 429133 | Improved Sanctuary | slot_417345 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 407632 | Hammer of the Righteous | slot_417346 | desconocida | Talento | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 440672 | Righteous Vengeance | slot_417347 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 462834 | Shock and Awe | slot_417347 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425589 | Aegis | Pecho | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462853 | Hand of Sacrifice | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425609 | Rebuke | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407631 | Hand of Reckoning | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407788 | Avenging Wrath | slot_0 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415071 | Exorcism | slot_10312 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415072 | Exorcism | slot_10313 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415073 | Exorcism | slot_10314 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 429146 | Holy Wrath | slot_10318 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 407627 | Righteous Fury | slot_25780 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 429145 | Holy Wrath | slot_2812 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 412019 | Sacred Shield | slot_415450 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 429139 | Wrath | slot_417345 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 458856 | Divine Light | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 440658 | Shield of Righteousness | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 458312 | Divine Protection | slot_498 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 458371 | Divine Protection | slot_5573 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415069 | Exorcism | slot_5614 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415070 | Exorcism | slot_5615 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 415068 | Exorcism | slot_879 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Pícaro: runas no implementadas (54)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 462708 | Cutthroat | Manos | Fase 1 | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 424785 | Saber Slash | Manos | Fase 1 | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 400029 | Shadowstep | slot_415449 | desconocida | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 408700 | Waylay | slot_415450 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 432259 | Combat Potency | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 432256 | Focused Attacks | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 432264 | Honor Among Thieves | slot_417345 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 399965 | Deadly Brew | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400014 | Just a Flesh Wound | Pecho | Fase 1 | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 398196 | Quick Draw | Pecho | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 424925 | Slaughter from the Shadows | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400009 | Between the Eyes | Piernas | Fase 1 | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 424919 | Main Gauche | Manos | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 410412 | Tease | slot_11303 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 410412 | Tease | slot_1966 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 410412 | Tease | slot_25302 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 425012 | Poisoned Knife | slot_415449 | desconocida | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 399986 | Shuriken Toss | slot_415449 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425096 | Master of Subtlety | slot_415450 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 400016 | Rolling with the Punches | slot_415450 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432276 | Carnage | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432271 | Cut to the Chase | slot_417346 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 432273 | Unfair Advantage | slot_417346 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 436564 | Blunderbuss | slot_417347 | desconocida | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 412096 | Crimson Tempest | slot_417347 | desconocida | Sin equivalente | C | Incluye un efecto DUMMY y requiere lógica propia en C++. |
| 410412 | Tease | slot_6768 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 410412 | Tease | slot_8637 | desconocida | Sin equivalente | C | La descripción indica una mecánica compleja («taunt»). |
| 400012 | Blade Dance | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 399963 | Envenom | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 399985 | Shadowstrike | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 457437 | Vanish | slot_0 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462721 | Ambush | slot_11267 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462722 | Ambush | slot_11268 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462723 | Ambush | slot_11269 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462714 | Backstab | slot_11279 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462715 | Backstab | slot_11280 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462716 | Backstab | slot_11281 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462729 | Garrote | slot_11289 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462730 | Garrote | slot_11290 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462717 | Backstab | slot_25300 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462710 | Backstab | slot_2589 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462711 | Backstab | slot_2590 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462712 | Backstab | slot_2591 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409240 | Fan of Knives | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 409240 | Fan of Knives | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462709 | Backstab | slot_53 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462724 | Garrote | slot_703 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462726 | Garrote | slot_8631 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462727 | Garrote | slot_8632 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462728 | Garrote | slot_8633 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462718 | Ambush | slot_8676 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462713 | Backstab | slot_8721 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462719 | Ambush | slot_8724 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 462720 | Ambush | slot_8725 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Sacerdote: runas no implementadas (47)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 401969 | Shared Pain | Piernas | Fase 1 | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 431670 | Despair | slot_417346 | desconocida | Sin equivalente | P | Solo aplica auras pasivas, sin proc, lanzamiento ni reutilización. |
| 413248 | Serendipity | Pecho | Fase 1 | Talento | T | Tiene una probabilidad de proc configurada. |
| 415739 | Strength of Soul | Pecho | Fase 1 | Sin equivalente | T | Uno de sus efectos dispara otro hechizo. |
| 413251 | Pain and Suffering | slot_417345 | desconocida | Talento | T | Uno de sus efectos dispara otro hechizo. |
| 431664 | Surge of Light | slot_417346 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 19243 | Desperate Prayer | slot_459695 | desconocida | Talento | T | Tiene una probabilidad de proc configurada. |
| 19293 | Elune's Grace | slot_459695 | desconocida | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 19266 | Touch of Weakness | slot_459695 | desconocida | Sin equivalente | T | Tiene una probabilidad de proc configurada. |
| 425198 | Twisted Faith | Pecho | Fase 1 | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402799 | Homunculi | Piernas | Fase 1 | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425266 | Empowered Renew | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 431655 | Mind Spike | slot_415449 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425280 | Renewed Hope | slot_415449 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 425294 | Dispersion | slot_415450 | desconocida | Talento | C | Los datos no encajan en las reglas simples; se asigna C por prudencia. |
| 402004 | Pain Suppression | slot_415450 | desconocida | Talento | C | La descripción indica una mecánica compleja («stance»). |
| 425284 | Spirit of the Redeemer | slot_415450 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425204 | Void Plague | slot_415450 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 431622 | Divine Aegis | slot_417345 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402789 | Eye of the Void | slot_417345 | desconocida | Sin equivalente | C | Es una habilidad activa nueva sin equivalente en WotLK. |
| 425207 | Power Word: Barrier | slot_417346 | desconocida | Sin equivalente | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402000 | Soul Warding | slot_417347 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 402668 | Vampiric Touch | slot_417347 | desconocida | Talento | C | Incluye un aura DUMMY y requiere lógica propia en C++. |
| 401859 | Prayer of Mending | Piernas | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 413259 | Mind Sear | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401955 | Shadow Word: Death | Manos | Fase 1 | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401977 | Shadowfiend | slot_0 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425274 | Renew | slot_10927 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425275 | Renew | slot_10928 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425276 | Renew | slot_10929 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19280 | Devouring Plague | slot_1219274 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19280 | Devouring Plague | slot_1219274 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425268 | Renew | slot_139 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425277 | Renew | slot_25315 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 431681 | Void Zone | slot_417346 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 401937 | Binding Heal | slot_417347 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19280 | Devouring Plague | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 6346 | Fear Ward | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19275 | Feedback | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19285 | Hex of Weakness | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19312 | Shadowguard | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 19305 | Starshards | slot_459695 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425269 | Renew | slot_6074 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425270 | Renew | slot_6075 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425271 | Renew | slot_6076 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425272 | Renew | slot_6077 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |
| 425273 | Renew | slot_6078 | desconocida | Activo | R | Tiene un hechizo WotLK con el mismo nombre exacto; se marca como redundante para decisión del usuario. |

## Clase desconocida: runas sin clasificar (206)

| ID | Nombre | Ranura | Fase | Tipo | Nivel | Razón |
|---:|---|---|---|---|---|---|
| 1220368 | Soul of Animalistic Expertise | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219976 | Soul of Enmity | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220170 | Soul of Fiery Convergence | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220334 | Soul of Predatory Instincts | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220146 | Soul of Temporal Longing | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220060 | Soul of the Abyssal | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219992 | Soul of the Aftershock | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220090 | Soul of the Alpha Tamer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220078 | Soul of the Alternator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220210 | Soul of the Altruist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220250 | Soul of the Ancestors | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220295 | Soul of the Ancestral Warden | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220212 | Soul of the Arbiter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220150 | Soul of the Arcanist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220120 | Soul of the Archbishop | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220046 | Soul of the Arsonist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220220 | Soul of the Ascendant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220362 | Soul of the Astral Ascendant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219994 | Soul of the Avoidant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220342 | Soul of the Barbaric | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220188 | Soul of the Bastion | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219960 | Soul of the Battle Forecaster | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220307 | Soul of the Beast | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220086 | Soul of the Beast Tender | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220328 | Soul of the Benevolent Seer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220023 | Soul of the Black Belt | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219962 | Soul of the Bloodseeker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220030 | Soul of the Bloodthirsty | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220082 | Soul of the Bounty Hunter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220002 | Soul of the Butcher | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220110 | Soul of the Celebrant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220044 | Soul of the Chaos Harbinger | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220266 | Soul of the Chieftain | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220144 | Soul of the Chronohealer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220338 | Soul of the Claw | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220364 | Soul of the Cometcaller | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220138 | Soul of the Contemnor | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220297 | Soul of the Corrupt | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220160 | Soul of the Cryomancer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220104 | Soul of the Deadly Striker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219968 | Soul of the Deathbound | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220130 | Soul of the Deathdealer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220035 | Soul of the Decimator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219978 | Soul of the Deflective | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220052 | Soul of the Demonic Exorcist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220050 | Soul of the Demonlord | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219966 | Soul of the Destroyer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220118 | Soul of the Devotee | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220206 | Soul of the Dominus | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220322 | Soul of the Dreamwalker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220096 | Soul of the Echoes | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220014 | Soul of the Efficient | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220288 | Soul of the Elder | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220282 | Soul of the Elemental Master | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220258 | Soul of the Elemental Seer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220164 | Soul of the Elementalist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220291 | Soul of the Elements | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220020 | Soul of the Equilibrist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220152 | Soul of the Eternal Caretaker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220162 | Soul of the Evoker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220224 | Soul of the Excommunicator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219998 | Soul of the Executioner | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220200 | Soul of the Exemplar | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220228 | Soul of the Exile | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220346 | Soul of the Exsanguinator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220112 | Soul of the Faithful | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220326 | Soul of the Feathered Sage | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220026 | Soul of the Fencer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220301 | Soul of the Ferocious | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220276 | Soul of the Flamebringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220056 | Soul of the Flamewraith | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220058 | Soul of the Fleshfeaster | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220366 | Soul of the Forest | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220344 | Soul of the Frenetic | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220312 | Soul of the Furious | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220268 | Soul of the Furycharged | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220299 | Soul of the Gentle Paw | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219990 | Soul of the Gladiator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220360 | Soul of the Graceful | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220324 | Soul of the Grove Tender | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220194 | Soul of the Guardian | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220106 | Soul of the Hastened Healer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220076 | Soul of the Hazard Harrier | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220088 | Soul of the Hound Master | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220092 | Soul of the Huntsman | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220176 | Soul of the Igniter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220332 | Soul of the Illuminator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219982 | Soul of the Incessant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220048 | Soul of the Infernal Shepherd | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220316 | Soul of the Innervator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220202 | Soul of the Inquisitor | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220192 | Soul of the Ironclad | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220218 | Soul of the Judicator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220216 | Soul of the Justicar | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220356 | Soul of the Keepers | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220168 | Soul of the Kindler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220100 | Soul of the Kineticist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220016 | Soul of the Knife Juggler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220310 | Soul of the Lacerator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220293 | Soul of the Lava Sage | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220244 | Soul of the Lavawalker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220098 | Soul of the Lethal Lasher | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220330 | Soul of the Lifeweaver | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220226 | Soul of the Lightbringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220182 | Soul of the Lightwarden | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220350 | Soul of the Lunatic | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220242 | Soul of the Maelstrombringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220166 | Soul of the Magical Armorer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220040 | Soul of the Malevolent | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220314 | Soul of the Mangler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220128 | Soul of the Mind Breaker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220070 | Soul of the Misleader | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220355 | Soul of the Night | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220318 | Soul of the Nurturer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220000 | Soul of the Opportunist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220068 | Soul of the Pain Spreader | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220054 | Soul of the Pained | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220196 | Soul of the Peacekeeper | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220122 | Soul of the Penitent | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220172 | Soul of the Perpetual Blaze | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220004 | Soul of the Phantom | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220140 | Soul of the Plaguebringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220022 | Soul of the Poised Brawler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220148 | Soul of the Precognitive | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220072 | Soul of the Preyseeker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220340 | Soul of the Prideful | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219972 | Soul of the Pristine Blocker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220180 | Soul of the Pristine Blocker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220174 | Soul of the Pyromaniac | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220184 | Soul of the Radiant Defender | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220279 | Soul of the Raging Flame | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220190 | Soul of the Reckoner | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220034 | Soul of the Refined | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220108 | Soul of the Refined | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220198 | Soul of the Refined | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220264 | Soul of the Refined | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220116 | Soul of the Resonant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220094 | Soul of the Retaliator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220222 | Soul of the Retributor | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219980 | Soul of the Revenger | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220142 | Soul of the Reverberant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220336 | Soul of the Ripper | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220066 | Soul of the Ritualist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220038 | Soul of the Rotbringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219970 | Soul of the Sanguinist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219974 | Soul of the Savage | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220006 | Soul of the Scoundrel | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220214 | Soul of the Sealbearer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220274 | Soul of the Seismic Smasher | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219986 | Soul of the Sentinel | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220114 | Soul of the Serendipitous | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220018 | Soul of the Shadow Master | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220042 | Soul of the Shadowmancer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220074 | Soul of the Sharpshooter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220234 | Soul of the Shield Master | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220186 | Soul of the Shieldbearer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220303 | Soul of the Shifter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220010 | Soul of the Shiv Savant | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220238 | Soul of the Shock-Absorber | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220124 | Soul of the Soul Warder | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219988 | Soul of the Southpaw | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220204 | Soul of the Sovereign | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220154 | Soul of the Spellbider | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220132 | Soul of the Spirit Font | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220286 | Soul of the Spirit Guide | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220262 | Soul of the Spirithealer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220240 | Soul of the Spiritual Bulwark | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220252 | Soul of the Spiritweaver | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220012 | Soul of the Stalker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220352 | Soul of the Starcaller | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220270 | Soul of the Stormbreaker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220256 | Soul of the Stormtender | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220102 | Soul of the Strategist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220028 | Soul of the Swashbuckler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219957 | Soul of the Tactician | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220272 | Soul of the Tempest | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220230 | Soul of the Templar | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220305 | Soul of the Territorial | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220348 | Soul of the Thornkeeper | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220008 | Soul of the Thrill Seeker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219984 | Soul of the Thunderbringer | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219964 | Soul of the Titan | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220178 | Soul of the Torcher | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220236 | Soul of the Totemic Protector | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220248 | Soul of the Totemkeeper | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219996 | Soul of the Toxicologist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220080 | Soul of the Toxinologist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220320 | Soul of the Tranquil | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220032 | Soul of the Transfusionist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220284 | Soul of the Tribesman | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220084 | Soul of the Trick Shooter | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220246 | Soul of the True Alpha | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220126 | Soul of the Twilight Walker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220064 | Soul of the Umbral Blade | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220136 | Soul of the Unwavering Defiler | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220208 | Soul of the Vindicator | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220260 | Soul of the Vitalist | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220062 | Soul of the Voidborne | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220278 | Soul of the Volcano | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1219958 | Soul of the War Veteran | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220156 | Soul of the Wardshaper | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220254 | Soul of the Waterwalker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220232 | Soul of the Windwalker | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220358 | Soul of the Wrathful | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220134 | Soul of the Zealot | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
| 1220158 | Soul of Winter's Grasp | slot_1219955 | desconocida | Sin clasificar | — | El catálogo no aporta una clase que permita clasificar esta runa. |
