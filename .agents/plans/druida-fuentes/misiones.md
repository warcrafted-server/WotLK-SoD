# Misiones de runas de druida de SoD: detalle para reimplementar

Consulta: 2026-10-18. Investigación solo lectura; nada se ha implementado ni probado. «No verificado» = no consta en ninguna fuente consultada.

## Fuentes y cómo se obtuvieron

- Wowhead, tooltip de misión/PNJ/objeto/objeto-item: `https://nether.wowhead.com/classic/tooltip/{quest,npc,item,object}/<id>?dataEnv=4&locale=0` (200, sin 403; pausas de 3 s). El tooltip de misión solo da título y resumen/objetivos; el de PNJ da nivel y coordenadas en %.
- `https://www.wowhead.com/classic/quest=<id>` con `curl` responde HTTP 202 con un reto de AWS WAF (cuerpo vacío): no sirve. Con la herramienta WebFetch sí devolvió la página (objetivos, ids de objetos, recompensas; sin NPC inicial, niveles, XP ni dinero). Páginas `npc=` de Wowhead: sin pestaña de misiones.
- Wiki de Warcraft (texto wiki en bruto, con `?action=raw`): `https://warcraft.wiki.gg/wiki/{Trial_of_The_Owls,The_Lost_Ancient,The_Lost_Saplings,Wisdom_of_the_Guardians,Rotting_Ancient,Rotten_Seed,Ancient_Sapling,Agon,Owl_Statue,Thin_Owl_Statue,Symbol_of_the_*_Owl,Treant_Avatar,Moonkin_Avatar,Hippogryph_Avatar,Child_of_Apa%27ro,Sacred_Stag_Heart,Blightbark,Sagefeather,Whisperwing,Shrine_of_the_*,Water_of_Elune%27ara}`. De aquí salen textos completos, niveles, XP, quien da la misión y la cadena.
- Warcraft Tavern: `https://www.warcrafttavern.com/wow-classic-sod/guides/wild-growth-rune/`, `https://warcrafttavern.com/wow-classic/guides/nourish-rune-season-of-discovery-sod`, `https://www.warcrafttavern.com/wow-classic-sod/guides/efflorescence-rune/` (coordenadas de guía, trucos, comentarios).
- Icy Veins (`icy-veins.com/wow-classic/season-of-discovery-druid-rune-slots-and-rune-locations`): **403**, se paró; no se usó.
- Conversión a mundo: `WorldMapArea.dbc` de `/home/stark/Servers/acore-test/data/dbc/`, misma fórmula que `coordenadas.md` (`X = Top + (Bottom-Top)·y%/100`, `Y = Left + (Right-Left)·x%/100`). Comprobada reproduciendo el valor de Namida Grimtotem de `coordenadas.md` (-4146, 827). **Z no verificado** en todos los casos (no se obtiene de un %). Precisión: unos metros.

## Corrección a la premisa de la petición

- «The Lost Saplings» **no** pide matar al Rotting Ancient. Eso es la misión previa **«The Lost Ancient» (79348)**, que se inicia con el objeto «Rotten Seed» (212693) que suelta el Rotting Ancient (216310) en Dustwallow Marsh, y se entrega a Orokai, que da después 79377. La cadena es: Rotting Ancient → Rotten Seed → The Lost Ancient → The Lost Saplings (fuente wiki: `previous = The Lost Ancient`).
- Los nombres de los guardianes de «Wisdom of the Guardians» en la wiki están cruzados (lista «Guardian of the Hinterlands» = Hippogryph Avatar y «Azshara» = Moonkin Avatar). Los datos de Wowhead (zona/coords de cada PNJ) dicen lo contrario y coherente con los santuarios: Hippogryph Avatar = Azshara, Moonkin Avatar = Hinterlands, Treant Avatar = Feralas. Se usa lo de Wowhead.

## Convención de ids

Todos los ids de SoD de esta nota (objetos ≥ 210000, PNJ ≥ 211200, misiones 78229/79348/79377/81924, objetos de mundo 4099xx/4410xx) **no existen en 3.3.5a**; hay que asignar ids propios. Los textos de los objetos-runa están en las secciones de cada misión. «Rune Broker» (compra a 1 cobre desde la fase 6) está documentado en Warcraft Tavern y queda fuera de este alcance.

---

## 1. Trial of The Owls (78229), runa Wild Growth

**Misión:** título «Trial of The Owls». Nivel de misión 25, nivel mínimo 1 (wiki: `level=25, levelreq=1`), clase Druida (`class=Druid` en la caja de la wiki; el Symbol y la runa llevan «Classes: Druid»). Sin misión previa listada. Añadida en parche 1.15.0 (fase 1).
- Da y entrega: **Loganaar** (12042), Druid Trainer, nivel 51 (tooltip Wowhead), Moonglade (zona 493), spawns (52.4, 40.4) y (52.4, 40.6) % -> mundo mapa 1 X≈7870, Y≈-2591 (Z no verificado). Facción Cenarion Circle.
- **Cómo se inicia:** la wiki anota «You must already possess at least one of the Symbols for Loganaar to offer the quest». Es decir, la misión la ofrece Loganaar solo si el jugador ya tiene al menos un Symbol (no verificado en otra fuente; los Symbols son BoP, únicos, solo druida).
- Objetivos: Symbol of the First Owl (210044), Symbol of the Second Owl (210043), Symbol of the Third Owl (210026). Los tres «Binds when picked up, Unique, Classes: Druid», ilvl 25.
- Descripción (wiki): «Let me see that symbol you carry, <name>. / It seems you have begun the trial of the owls. This marks a pivotal moment in your journey as a druid. / There are more symbols like this one; spread across Azeroth. To earn them, you must perform great feats of mind and body alike. / One owl sits beneath a great tree in the Eastern Kingdoms. Another is near a great tree here in Kalimdor. Yet another is at sea; off the coast of Hillsbrad. / Seek out these owls, <name>, and bring their symbols to me.»
- Texto de progreso: «How goes your trial, <name>?»
- Finalización: «I would like to congratulate you, <name>. What you've accomplished is no small feat. / To pass the trial of the owls is to demonstrate an attunement with all aspects of your druidic calling. / Take this rune as a mark of your achievement. I hope it will serve you well as a warden of the Emerald Dream.»
- Recompensa: **Rune of Wild Growth (210137)**, BoP, único, ilvl 25, clase Druida (enseña el grabado «Engrave Gloves - Wild Growth», spell de runa 408120, grabado 410028 según Warcraft Tavern); +100 reputación con Cenarion Circle (facción 609 según Wowhead); dinero «18» según plantilla de la wiki (`{{cost||18}}`; unidad **no verificado**, probablemente plata); **XP: no consta** en ninguna fuente («rune quest»).
- Visibilidad: ver arriba; ninguna fuente dice que la oculte a no druidas aparte de la restricción de clase de la caja.

### Objetivo 1: Symbol of the First Owl (Ashenvale)
- Objeto de mundo «Owl Statue» (id 410020 en Wowhead/wiki «Elinks-object2 410020|410089»; cuál de los dos ids es Ashenvale y cuál Duskwood: **no verificado**; el tooltip de objeto no trae coordenadas).
- Lugar: cerca de Forest Song, Ashenvale, NE, (87, 43) % según wiki; Warcraft Tavern también dice (89.0, 41.0). Mundo, desde (87,43): mapa 1, X≈3020, Y≈-3317 (Z no verificado). Un comentario de la guía dice que está más cerca de la entrada y otro que solo veía mobs nivel 60: **posición exacta dudosa**.
- Mecánica: tocar la estatua hace aparecer oleadas de enemigos de nivel 25. Wiki: «6 waves of 2-3 level 25 enemies»; Warcraft Tavern: «3 waves, 2 per wave, 6 total». **Discrepancia: nº de oleadas y de enemigos, y ids/tipos de los enemigos, no verificados.** Derrotarlos todos otorga el Symbol (210044).

### Objetivo 2: Symbol of the Second Owl (Duskwood)
- Estatua «Owl Statue» en Twilight Grove, Duskwood, (50, 35) % -> mapa 0, X≈-10347, Y≈-517 (Z no verificado). Al interactuar da el buff «Eyes of the Owl» (id de hechizo **no verificado**), necesario para ver a Agon.
- **Agon** (211200): jabalí fantasma, nivel 25, «Combat» (hostil), Brightwood Grove (Duskwood, zona 10). Wowhead lista ~90 puntos entre (60.2–70.8, 21.4–37.8) %, o sea un área de deambulación; centro aprox. (64, 30) % -> mapa 0, X≈-10257, Y≈-895. Solo visible con el buff. Habilidad: Infected Wound (id 3427, existe en 3.3.5a). Suelta el Symbol (210043); según un comentario, solo un objeto por muerte (cada jugador debe matarlo). Rareza/respawn/vida: no verificado.

### Objetivo 3: Symbol of the Third Owl (Hillsbrad)
- Dos objetos de mundo, ids 409942 y 409949, nombre en Wowhead «Twin Owl Statue» (la wiki los llama «Thin Owl Statue») en dos islas al sur de Hillsbrad Foothills (zona 267): (36, 75) % -> mapa 0, X≈-1200, Y≈-85 y (53, 81) % -> mapa 0, X≈-1328, Y≈-629 (Z no verificado; con esa Y/X son islas en el mar, coherente con «at sea»).
- Mecánica: activar las dos en menos de 2 minutos da el Symbol (210026). Requiere nadar rápido (Aquatic Form, spell 1066, o poción de natación según un comentario).

### Intermedios que no existen en 3.3.5a
Objetos 210044, 210043, 210026, 210137; objetos de mundo 410020, 410089, 409942, 409949; PNJ Agon (211200); hechizos 408120/410028 (runa y grabado) y el buff Eyes of the Owl; los enemigos de las oleadas (ids no verificados). Loganaar (12042) y Aquatic Form (1066) sí existen en WotLK (el id 12042 es el de Wowhead classic; no comprobado contra la BD de acore-test).

---

## 2. The Lost Saplings (79377), runa Nourish, precedida por The Lost Ancient (79348)

### Misión previa: The Lost Ancient (79348)
- Nivel 40, nivel mínimo 26 (wiki), categoría Druida. Se inicia con el objeto **Rotten Seed (212693)**: BoP, ilvl 1, requisito nivel 26 (wiki), «This Item Begins a Quest». Da: item; entrega: **Orokai**. Siguiente: The Lost Saplings.
- Objetivo (Wowhead): «Find someone who can tell you more about the rotten ancient seed.»
- Descripción (wiki): «A putrid seed is all that remains of the wandering ancient. Its outer coat is brittle, and the insides emit a foul odor. / Given its size, the ancient this seed came from must have been fairly young; at least by ancient standards. One has to wonder why such a creature would be found trudging through The Quagmire. / To find your answers, you should take this seed to someone with knowledge in the lore of ancients.»
- Finalización: «Ah, another lost youngling...»
- Recompensa: 1550 XP (wiki). Dinero: no consta.
- **Rotting Ancient (216310):** nivel 40, tipo Giant, mana, «Combat», Dustwallow Marsh (zona 15), el Quagmire. Wowhead: 25 puntos en (40–44.2, 30.8–44.8) %, concentrados en (40–44, 41–44) %; wiki: (43, 44); Warcraft Tavern: (45, 51) (discrepa, coordenada de guía). Centro (42, 42.5) % -> mapa 1, X≈-3521, Y≈-3180 (Z no verificado). Habilidad: Wild Regeneration (id 7948, existe en 3.3.5a). Suelta Rotten Seed 212693 (probabilidad **no verificado**; botín único).

### The Lost Saplings (79377)
- Nivel 40, nivel mínimo 26 (wiki), categoría Druida; previa The Lost Ancient. Añadida en 1.15.1 (fase 2). Clase restringida: no consta como campo; la runa es «Classes: Druid».
- Da y entrega: **Orokai** (216289), nivel 62, Moonglade (493), spawns (41.2,43.6), (41.4,43.4), (41.6,43.4), (41.6,43.6) % -> mapa 1, X≈7820, Y≈-2342 (Z no verificado). Facción Cenarion Circle. (El tooltip sin «Druid» ni «Trainer»; no es entrenador).
- Objetivos (Wowhead y wiki): encontrar y regar Summer Sapling, Spring Sapling, Fall Sapling y Winter Sapling (1 de cada) con **Water of Elune'ara (213036)**, objeto de misión proporcionado por la propia misión (Wowhead: «Provided item», wiki: «provided»), duración 1 hora de tiempo real, «Use: Give water to an ancient sapling», reutilización 1 min.
  - **Discrepancia:** la guía de Warcraft Tavern dice que se recoge el agua interactuando con «Crystal Waters of Lake Elune'ara» en (55.8, 66.5) % de Moonglade; Wowhead y la wiki dicen que la entrega Orokai. Lo segundo está en dos fuentes; la guía podría ser de una versión anterior. No verificado cuál es el hecho real.
- Descripción (wiki): «In times of unrest, seeds may take root in bitter soil. Ancients born this way are prone to corruption. They wander hostile lands; never finding peace. / I have sensed four saplings who may be spared such a fate. They are lost among the Eastern Kingdoms, with leaves like that of each season. / Please, take this water to them, so that they may be healed. / Be warned, the water's magic is delicate. Teleportation, or falling in battle, will destroy it. Its potency will also fade over time.»
- Progreso: «Make haste, <name>. My kin may yet be saved.»
- Finalización: «Your deeds have preserved centuries of life, <name>. I am immensely grateful. May you bring yet more healing upon this land in the times to come.»
- Recompensa: **Rune of Nourishing (213074)**, BoP, único, ilvl 40, Druida, grabado en cinturón («Engrave your belt with the Nourish rune»); 3150 XP y «50» de dinero (wiki; unidad no verificado); sin reputación listada. Wowhead no lista XP/dinero.
- Fallo: teletransporte, morir o agotar la hora del agua hacen fallar la misión (wiki). Comentarios: la misión también falla durante el barco/vuelo entre Kalimdor y Reinos del Este (trucos no verificados).

| Sapling (wiki) | PNJ (todos «Ancient Sapling», nivel 10, id propio) | Zona (id) | % mapa Wowhead | Mundo (mapa 0) |
|---|---|---|---|---|
| Winter | 216437 | Alterac Mountains, Strahnbrad (36) | (58–58.6, 43.4–43.8); guía (58.6, 43.8) | X≈682, Y≈-857 |
| Autumn/Fall | 216451 | Arathi Highlands, centro-sur (45) | (46.8, 71.4–72); guía (46.8, 71.6) | X≈-1852, Y≈-2551 |
| Spring | 216445 | Swamp of Sorrows, Misty Valley (8) | (11.2–11.4, 38.4–38.6) | X≈-10211, Y≈-2480 |
| Summer | 216448 | Stranglethorn Vale, sur (33) | (32.6, 65) | X≈-13934, Y≈141 |

Z no verificado. Neutrales (facción «Neutral»), al ser regados dicen «Ah...much better. Thank you, druid.» (wiki). Qué hace el sapling tras regarlo (desaparece, flags): no verificado.

### Intermedios que no existen en 3.3.5a
Objetos 212693, 213036, 213074; PNJ 216289, 216310, 216437, 216445, 216448, 216451; misiones 79348 y 79377.

---

## 3. Wisdom of the Guardians (81924), runa Efflorescence (+ Seed of Renewal)

**Misión:** nivel 50, nivel mínimo 45, categoría Druida; sin misión previa listada. Añadida en 1.15.2 (fase 3). Clase restringida como campo: no consta (la runa es Druida; la guía dice que cualquiera la ve con nivel 45: no verificado).
- Da y entrega: **Tyrisius** (221985), nivel 40, Feralas (357), una posición (57.2, 69) % -> mapa 1, X≈-5564, Y≈1466 (Z no verificado). Warcraft Tavern: «night elf in a tower in Feralas at 57.2, 69.0».
- Objetivos (Wowhead): «Guardian of Feralas» (221935), «Guardian of the Hinterlands» (221933), «Guardian of Azshara» (221928). Son los PNJ «avatar» (ver tabla).
- Descripción (wiki): «Whatever Kaldorei knowledge you seek will not be found among these ruins, <class>. Not anymore. / However, while the physical lies in ruin, the spiritual remains. / Seek the guardian spirits of Azshara, the Hinterlands, and Feralas. You will know them by their shrines. Prove yourself to them, and heed their words. Their wisdom will be passed on to you, so that it will not be lost to time as so much was here.»
- Progreso: «Have the spirits imparted their wisdom unto you?»
- Finalización: «You have proven a dedicated pupil, <name>. The work of preserving ancient knowledge is often arduous, but you have taken on the duty admirably. / There are many more mysteries in this world for you to uncover. I hope these tools will aid you in that journey.»
- Recompensa: **Rune of Efflorescence (220360)** (BoP, único, ilvl 50, Druida, grabado en brazales, «Swiftmend ahora también provoca Efflorescence…»); **Seed of Renewal (219326)** (trinket raro, BoP, requiere nivel 50: «Chance to embed a seed into enemy humanoids, beasts, or dragonkin hit by your abilities or spells. If the creature is slain within 30 seconds…, a Healing Blossom will grow from its corpse», 40 % proc, 2 min de reutilización); 4700 XP y «75» de dinero (wiki; unidad no verificado).

| Guardián (objetivo) | Avatar (kill credit) | Después aparece | Santuario (objeto) | % mapa | Mundo |
|---|---|---|---|---|---|
| Feralas | Treant Avatar 221935, nivel 50, Elemental, hostil | Blightbark 222705, élite nivel 50 (dice 3 frases, no se pelea) | Shrine of the Warden 441948, interactivo, (58.6, 52.2) | avatar (58.4–58.6, 52–52.2) | mapa 1, X≈-4785, Y≈1369 |
| Hinterlands | Moonkin Avatar 221933, nivel 50, Humanoide | Sagefeather 222704 | Shrine of the Moon 441946, libro, (66.2, 53.1) | avatar (66.2, 53) | mapa 0, X≈104, Y≈-4124 |
| Azshara | Hippogryph Avatar 221928, nivel 50, Bestia | Whisperwing 222703 | Shrine of the Beast 441947, libro, (34.6, 49) | avatar (34.4–34.6, 48.8–49) | mapa 1, X≈3685, Y≈-5032 |

Warcraft Tavern da las coordenadas del santuario de Feralas como (58.7, 52.4); Wowhead y la wiki (58.6, 52.2). El avatar nunca figura como PNJ élite en el tooltip («Normal»); los guardianes tras ellos sí «Elite» y neutrales. Vida, daño, respawn: no verificado.

### Mecánica por santuario
1. **Feralas (Shrine of the Warden):** interactuar da el buff «Duty of the Warden» (spell 446448); curarse con Remove Curse y Cure Poison hace que se transforme en «Mark of the Warden» (446467), para lo cual hay que estar maldecido y envenenado; acercarse al santuario con ese buff invoca al Treant Avatar. Texto del libro: «Cast out what rots away the body, and that which corrupts the spirit. Only then may you return.» Habilidad del avatar: Entangling Roots (11922). Al matarlo aparece el espíritu de Blightbark.
2. **Hinterlands (Shrine of the Moon):** lanzar Tranquility y después Hurricane sobre el santuario invoca al Moonkin Avatar. Texto: «The calm comes before the storm.» Habilidades: Rend (13445), Strike (13584), Tendon Rip (3604). Al matarlo aparece Sagefeather.
3. **Azshara (Shrine of the Beast):** matar a **Child of Apa'ro** (222580, ciervo blanco, nivel 50, bestia, inmune a magia, desollable) en Ursolan, norte de Azshara (zona 16): 18 puntos en (42–44.4, 27.4–38) %, centro (43, 31) % -> mapa 1, X≈4293, Y≈-5458. Suelta **Sacred Stag Heart (221326)** (BoP, «Present as an offering at the Shrine of the Beast»), que se ofrece en el santuario para invocar al Hippogryph Avatar (habilidad Rend 13445). Texto: «Hunt the white stag with tooth and claw.» Al matarlo aparece Whisperwing.

La misión se cumple al matar los tres avatares (el objetivo cuenta los PNJ 221935/221933/221928, no a los espíritus). Si la contabilización se hace al matar al avatar o al hablar con el espíritu: no verificado.

### Intermedios que no existen en 3.3.5a
Objetos 220360, 219326, 221326; PNJ 221985, 221935, 221933, 221928, 222580, 222703, 222704, 222705; objetos de mundo 441946, 441947, 441948; hechizos 446448 y 446467; misión 81924.

---

## Incertidumbres globales

- XP, dinero (unidades) y reputación solo de la wiki de Warcraft; Wowhead no los muestra en las fuentes consultadas.
- Oleadas de la estatua de Ashenvale (número, tipos, ids), ids de hechizos del buff «Eyes of the Owl» y de la runa, probabilidad de botín, respawns, Z de todos los puntos: no verificado.
- Cuál de los ids 410020/410089 es la estatua de Ashenvale o la de Duskwood: no verificado.
- Si cada misión se oculta a no druidas por un flag de clase (`RequiredClasses`): no verificado; solo hay restricción explícita en los objetos Symbol/runa.
- No se ha encontrado ningún `quest_template` SQL de SoD público (cf. `coordenadas.md`).
