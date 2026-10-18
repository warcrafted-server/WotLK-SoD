# Fuentes SoD originales: runas de druida (lote A)

Consulta: 2026-10-18. Fuentes: datos Wowhead ya volcados en `docs/runas/fuentes-sod.json` y tooltips en vivo
`nether.wowhead.com/classic/tooltip/{item,spell,quest}/<id>?dataEnv=4&locale=0` (las páginas HTML dan 202 vacío; el tooltip sí responde).
La fase sale de la etiqueta «SoD Phase N» del tooltip del objeto-runa. Zonas por ID de área de Wowhead: 10 Duskwood, 331 Ashenvale, 47 Hinterlands, 357 Feralas, 141 Teldrassil, 215 Mulgore.
Rune Broker: NPC 233335 (Orgrimmar/Stormwind según ubicación listada 1657/1637 = Darnassus/Thunder Bluff... ver incertidumbres) y 233428; en la lista de vendedores el coste «[1]» o con ítem de canje.

| Runa | Objeto-runa (id) | Fase | Obtención en SoD original |
|---|---|---|---|
| 7009001 Wild Growth (408120) | Rune of Wild Growth (210137) | 1 | Misión «Trial of The Owls» (78229, nivel 25, req. 1, Moonglade): traer los símbolos del Primer, Segundo y Tercer Búho a Loganaar. Además Rune Broker (233335/233428, lvl 60, coste «1»). Hechizo auxiliar de entrega 424631 «Give Extra Rune». |
| 7009005 Berserk (417141) | Rune of Berserk (213117) | no verificado (ilvl 40, sin etiqueta de fase; probablemente 2) | Solo constan los Rune Broker (coste «1», sin requisito). Ninguna misión, botín ni objeto de mundo en Wowhead. |
| 7009006 Survival Instincts (408024) | Rune of Instinct (213119) | 2 | Rune Broker (coste «1»). Evento/misión de Amaryllis (Swamp of Sorrows): el objeto tiene hechizo «[DNT] Amaryllis Give Rune B» (434877), pero no se pudo obtener el nombre/id de la misión: no verificado. |
| 7009008 Gore (417145) | Rune of Bloodshed (221517) | 3 | Intendentes: Falinar (222684, Duskwood, req. nivel 25, 16000 cobre = 1g60), Kyleen (222686? no: 222685, Ashenvale, nivel 40, 16842), Alandra (222686, Hinterlands, nivel 50, 16842), Valdane (222687, Feralas, nivel 50, 16000). Además Rune Broker (coste «1»). |
| 7009010 King of the Jungle (417046) | Rune of the Jungle King (213118) | 2 | Rune Broker: canje por 1 «Emblem of the Violet Eye» (232456; «prueba de victoria sobre los Dark Riders», canjeable en el Rune Broker). Botín: Supply Bag (217014, nivel 40, fase 2) lo contiene 132/982 (~13,4 %). |
| 7009011 Skull Bash (410176) | Rune of Skull Bash (206992) | 1 | Vendedores nivel 30: Elaine Compton (213077, área 1519 Stormwind, 20000 = 2g), Jornah (214070, 1637 Orgrimmar, 18823), Dokimi (214096, 1638 Thunder Bluff, 21052), Gishah (214098, 1497 Undercity, 21176), Tamelyn Aldridge (214099, 1537 Ironforge, 20000), Marcy Baker (214101, 1657 Darnassus, 17777). Rune Broker (coste «1»). Requisito exacto (oficial de suministros / rango 4) no verificado. |
| 7009012 Improved Frenzied Regeneration (431389) | Rune of Primal Energy (221516) | 3 | Rune Broker: canje por 1 «Emblem of the Wild Gods» (232454; «prueba de asistir al Shadowtooth Emissary»). |
| 7009015 Living Seed (414677) | Rune of Natural Potential (206963) | 1 | Botín de Unleashed Nature Spirit (206245, nivel 7, Mulgore 215 / Teldrassil 141): 2/2 en la muestra (~100 %, muestra muy pequeña). Rune Broker (coste «1»). |
| 7009016 Gale Winds (417135) | Rune of the Windstorm (220754) | 3 | Botín de Namida Grimtotem (222286, nivel 43, Feralas): 1/1 en la muestra. Rune Broker (coste «1»). |

## Incertidumbres / no verificado
- Coste del Rune Broker: Wowhead lo da como «[1]» sin unidad; no sé si es 1 cobre, 1 token u otra cosa. En 7009010 y 7009012 se sustituye por el ítem de canje (Emblem). No verificado el precio real en oro.
- Ubicación de los Rune Broker: ids de área 1657 (Darnassus), 1637 (Orgrimmar), además de zonas -1/12/14/215/1; solo sé que están en «capitales» según el tooltip del Emblem. Ciudades exactas no verificadas.
- Berserk: sin etiqueta de fase; Wowhead no muestra más fuente que el Rune Broker.
- Survival Instincts: nombre/id de la misión de Amaryllis no encontrado (solo el hechizo 434877); no verificado.
- Gore y Skull Bash: requisito de rango/oficial no consta en los datos locales; las descripciones del enunciado («rango 4») no pude confirmarlas. Ids de zona Falinar/Kyleen/Alandra/Valdane tomados del JSON local.
- Corregir lectura de Gore: Kyleen = 222685 (Ashenvale), Alandra = 222686 (Hinterlands).
- Wowhead HTML devuelve 202 vacío; se usó solo el tooltip. Porcentajes de botín proceden de muestras pequeñas (Living Seed 2/2, Namida 1/1).
- Los emblems 232456/232454 y los canjes son de fase tardía (los objetos de runa 213118 y 221516 son fases 2 y 3 como runas, pero los Emblem pueden ser de fases posteriores): fase de los Emblem no verificada.
# Fuentes de obtención en SoD original: runas de druida (lote B)

Consultado el 2026-10-18. Wowhead Classic bloquea el HTML con curl (HTTP 202 vacío); sí responde `nether.wowhead.com/classic/tooltip/{item,spell,quest}/<id>?dataEnv=4&locale=0` (da fase y texto) y WebFetch a algunas páginas. Los datos de vendedores/drops/misiones proceden de `docs/runas/fuentes-sod.json` (ya extraído de Wowhead) y de las guías de Warcraft Tavern.

## Rune Broker (válido para TODAS las runas, desde Fase 6)
- Wowhead: PNJ 233335 (Darnasus, Dun Morogh, Elwynn) y 233428 (Orgrimmar, Durotar, Mulgore); nivel 60 en la ficha. Por zonas del JSON; las guías dicen «ciudades principales y zonas iniciales» (Stormwind, Ironforge, Orgrimmar, Thunder Bluff citadas por una guía; Darnasus por la zona 1657).
- Precio: 1 cobre por runa (Warcraft Tavern: «a partir de la Fase 6»; Wowhead lo recoge como coste 1). Sin requisito de nivel de runa documentado.
- Excepción en Wowhead: Eclipse pide 1 «Emblem of Dishonor» (232455) en vez de dinero (idem King of the Jungle: «Emblem of the Violet Eye» 232456; Improved Frenzied Regeneration: «Emblem of the Wild Gods» 232454). Los emblemas se compran en Booty Bay (Pix Xizzix, 5 Tarnished Undermine Real, según Tavern/Wowhead) o se obtienen por la misión original. Contradicción: Tavern dice que desde Fase 6 todo cuesta 1 cobre; el JSON de Wowhead sí exige el emblema para esas tres. No verificado cuál rige hoy.

## Tabla por runa

| id interno | Runa | Hechizo | Objeto-runa (id) | Ranura / fase añadida | Obtención original |
|---|---|---|---|---|---|
| 7009017 | Sunfire | 414684 | Rune of the Sun (206989) | Manos / Fase 1 (tooltip «SoD Phase 1») | Nivel ~4 con Moonfire. Mulgore (aprox. 36,70) o Teldrassil (aprox. 53,78): lanzar Moonfire a 3 Lunar Stones a la vez; aparece el Lunar Chest (objeto 404433; 3/3 con el objeto). Coordenadas discutidas en comentarios. |
| 7009019 | Dreamstate | 408258 | Rune of the Dreamer (213120) | Pies / Fase 2 (tooltip) | Desolace, nivel rec. 32. Desiccated Seed Pod de centauros Kolkar (Kolkar Village ~73,48) -> mojar en agua (estanque junto a Sargeron ~66,29) = Satyrweed Bulb -> interactuar con montones de Sandy Loam cerca de Sargeron (~74-78,16-21). Wowhead lo da como objeto «Blooming Satyrweed» 404402 (zona 405 Desolace); Tavern no lo nombra. |
| 7009020 | Tree of Life | 439733 | Rune of the World Tree (227746) | Espalda / Fase 4 (Tavern; el tooltip no lleva etiqueta de fase; wiki.gg: parche 1.15.3, 2024-07-09) | Felwood, nivel 60. Vengeful Wisp (Tavern ~46,19, noroeste de Felwood junto a Jadefire Run; wiki.gg dice Irontree Woods): hacer que te siga, matar sátiros en Jadefire Run hasta el buff Shimmering Light, hablar otra vez y recoger el objeto «Gift of the Wisp» (464128). |
| 7009021 | Starsurge | 417157 | Rune of the Stars (210500) | Piernas / Fase 1 (tooltip) | Wetlands (noroeste). Nivel rec. 20. Grugimdern (enano, ~36.8,15.2) te da un Marshroom; con él hablar con Vodyanoi (rana en un tocón, estanque ~31.2,18.2) -> «Give Rune of Stars» (hechizo 426068) da el objeto. |
| 7009022 | Efflorescence | 417149 | Rune of Efflorescence (220360) | Muñecas / Fase 3 (tooltip) | Misión «Wisdom of the Guardians» (81924, nivel 50, req. 45; Tyrisius, elfo de la noche, torre en Feralas ~57.2,69.0). Requisitos: «Guardian of Feralas/Hinterlands/Azshara». Whisperwing (Azshara: Sacred Stag Heart de un Child of Apa'ro, santuario ~34.6,49.0), Sagefeather (Hinterlands: Tranquility y Hurricane sobre el Shrine of the Moon ~66.2,53.2), Blightbark (Feralas: Shrine of the Warden ~58.7,52.4, con Remove Curse/Cure Poison). Recompensa: runa + trinket Seed of Renewal. Los tres guardianes son nivel 50. |
| 7009023 | Elune's Fires | 414719 | Rune of the Moon Goddess (221020) | Muñecas / Fase 3 (tooltip) | Azshara oeste, nivel rec. 48. Traveller's Knapsack (~20.6,62.0) -> leer Keldara's Log -> 3 Satyrweed Samples -> Satyrweed Tincture (Mortar and Pestle) -> hibernar un Thunderhead Hippogryph verde con Satyr Corruption (~17,60) y usar la tintura. El hechizo «Elune's Favor» 446288 es el que crea el objeto (evento final). |
| 7009024 | Eclipse | 408248 | Rune of Eclipse (212548) | Cintura / Fase 2 (tooltip) | Nivel 30. Cadena «Highway Robbery» (Extinguished Campfire, Desolace 47,54) -> «On the Lam» (Bibbly F'utzbuckle, Desolace 63,39) -> «Cherry for Your Thoughts?» / «No Honor Among Thieves» (Tokal, Booty Bay 27,77) -> Arathi Highlands: bote al muelle, derrotar a Illari Duskfeather (elfa de la noche nivel 40; las elfas de la noche no pelean) -> Illari's Key de la Dropped Pouch -> Illari's Loot Cache -> Jewel-Encrusted Box (212553; Wowhead: 143/1630 en cajas, nivel req. 30). Rune Broker: Emblem of Dishonor (232455, «prueba de confrontar a Illari Duskfeather»). |
| 7009025 | Starfall | 439748 | Rune of the Falling Star (227749) | Espalda / Fase 4 | Winterspring NE (~63,18, Hidden Grove): matar a Arcterris, élite, nivel 58 (Tavern) o 59 (otras fuentes). Wowhead: lo suelta 2 de 3 veces. Recomendable grupo. |
| 7009026 | Lifebloom | 408124 | Rune of Life (206970) | Piernas / Fase 1 (tooltip) | Nivel rec. 8. Con un compañero sanador: clic en «Adventurer's Remains», «Begin the ritual», el compañero hace clic en el portal; loot del Adventurer's Spirit. Ubicaciones: Dun Morogh ~43,49.6; Elwynn ~52.2,84.7; Teldrassil Oracle Glade ~32,35 (Alianza); Durotar Kolkar Crag ~48,79.5; Mulgore Venture Co. Mine ~60,33 (Horda). Compañero: sacerdote, paladín/chamán o druida según facción. Sin objeto/mundo registrado en Wowhead (el JSON solo lista Rune Broker). |
| 7009027 | Nourish | 408247 | Rune of Nourishing (213074) | Cintura / Fase 2 (tooltip) | Misión «The Lost Saplings» (79377, nivel 40, req. 26): Orokai, Moonglade (~41.6,43.6). Inicio: matar al Rotting Ancient en Dustwallow Marsh (~45,51) para iniciar «The Lost Ancient». Agua de Elune'ara (~55.8,66.5) y regar 4 brotes en 1 h: Swamp of Sorrows (~10,39), STV sur (~33,65), Arathi (~47,72), Alterac/Strahnbrad (~58,44). No vale teletransportarse ni morir. |

Aviso: Wowhead muestra el tooltip del objeto de la runa con «SoD Phase N» solo para algunas. Tree of Life y Starfall no la llevan.

## Thrash (Cat) y Tiger's Fury
- **Thrash (Cat)**: hechizo 417448 (cat, 40 energía, 8 m, 15 s de sangrado; en Wowhead lleva el flag «Not In Spellbook»). 417453 es un hechizo pasivo/oculto que hace «Overrides Actionbar Spell» (según WebFetch de la página de Wowhead). El catálogo local lo asigna a `slot_417437`, sin nombre, y base_level/spell_level 1. No he encontrado en ninguna guía de runas de Warcraft Tavern ni Icy Veins una runa llamada Thrash. Lo más probable (no verificado) es que se aprenda con otra runa o habilidad: la candidata es Improved Swipe (415452), que en el catálogo dice «While in Cat Form, your Swipe becomes Swipe (Cat)» pero habla de Swipe, no de Thrash. NO verificado cómo ni en qué fase se obtiene.
- **Tiger's Fury** (417045): en el catálogo, la ranura es de habilidad de clase (`slot_5217`, etc.), no de grabado; la runa que lo modifica es **King of the Jungle** (417046, pies, Fase 2), que lo convierte en +15 % de daño físico y 60 de energía sin GCD (Icy Veins/Tavern lo confirman: 30 s de reutilización). Es hechizo base de clase (nivel 1, entrenador) y no una runa. Gore (cabeza) lo resetea con 16 % de probabilidad.

## Lista completa de runas de druida de SoD (Warcraft Tavern, página de Fase 6/8)
- Fase 1: Pecho: Fury of Stormrage, Living Seed, Survival of the Fittest, Wild Strikes. Piernas: Lacerate, Lifebloom, Savage Roar, Starsurge. Manos: Mangle, Sunfire, Wild Growth, Skull Bash.
- Fase 2: Cintura: Berserk, Eclipse, Nourish. Pies: Dreamstate, King of the Jungle, Survival Instincts.
- Fase 3: Muñecas: Efflorescence, Elune's Fires, Improved Frenzied Regeneration. Cabeza: Gale Winds, Gore, Improved Barkskin.
- Fase 4: Espalda: Improved Swipe, Starfall, Tree of Life. Anillo: Feral Combat, Dagger, Fist Weapon, Mace, Pole Weapon, Defense, Nature, Arcane Specialization (Specialization, no son de clase de ataque).
- Fase 5: Anillo: Healing Specialization, Meditation Specialization.
- Fase 6: nada nuevo; los Rune Brokers venden todo a 1 cobre.
- Fases 7 y 8: sin runas nuevas según Tavern. En Fase 7 aparecen los encantamientos de hombro «Soul of …» (35 de druida en `almas-sod.md`: Soul of the Gentle Paw, Ferocious, Shifter, Territorial, Beast, Lacerator, Furious, Mangler, Innervator, Nurturer, Tranquil, Dreamwalker, Grove Tender, Feathered Sage, Benevolent Seer, Lifeweaver, Illuminator, Predatory Instincts, Ripper, Claw, Prideful, Barbaric, Frenetic, Exsanguinator, Thornkeeper, Lunatic, Starcaller, Night, Keepers, Wrathful, Graceful, Astral Ascendant, Cometcaller, Forest, Animalistic Expertise). Son encantamientos de hombro (no runas de grabado); su método de obtención en Argent Dawn: no verificado.

## Comparación con la lista del encargo (27 + Thrash)
- Las 27 runas de ranura coinciden con la lista de la guía: 4 pecho + 4 piernas + 4 manos + 3 cintura + 3 pies + 3 muñeca + 3 cabeza + 3 espalda = 27. No falta ninguna runa de ranura de clase.
- En el encargo «Gale Winds» aparece dos veces. Gale Winds, Gore y Improved Barkskin son las tres de cabeza.
- Faltan frente a la lista: nada de clase. Fuera de las 27: anillos (Specialization), Thrash (417453, sin ranura nombrada) y las Soul of… (hombros).
- Los datos de obtención de las 19 runas «sin fuente real» (TODO.md) están en `docs/runas/fuentes-sod.json`; esta tabla cubre las 10 pedidas.

## Incertidumbres / no verificado
- HTML de Wowhead no accesible con curl (202); no he leído las pestañas «Dropped by / Sold by» directamente, solo el JSON local y los tooltips.
- Precio real del Rune Broker (1 cobre) viene de guías de terceros (2024) y de un campo `cost` de Wowhead cuyo significado exacto (cobre) no está confirmado; los emblemas para Eclipse, King of the Jungle y Improved Frenzied Regeneration contradicen la afirmación «todo a 1 cobre».
- Ubicaciones exactas de los Rune Broker: solo por ids de zona del JSON y una guía.
- Fase exacta de Tree of Life y Starfall (Fase 4 según Tavern; no etiquetadas en Wowhead). Nombre del objeto de mundo de Dreamstate (Blooming Satyrweed vs. Sandy Loam). Coordenadas de guías con comentarios de lectores que las discuten.
- Thrash (Cat): cómo se aprende y en qué fase, no encontrado. Elune's Favor (446288): cómo funciona exactamente, no encontrado.
- Nivel de Arcterris (58 vs. 59) y cuántos jugadores requiere.
- Qué contienen los «Soul of…»: solo por almas-sod; método de obtención no verificado.

Fuentes: https://www.warcrafttavern.com/wow-classic-sod/guides/druid-runes/ y las guías individuales de Eclipse, Efflorescence, Elune's Fires, Starsurge, Dreamstate, Lifebloom, Nourish (vía búsqueda), Tree of Life (wiki.gg), Starfall; https://nether.wowhead.com/classic/tooltip/item/<id>.
