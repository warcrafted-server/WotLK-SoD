# Plan: fuentes reales de obtención de las runas del druida (SoD original, sin Grabador)

Objetivo: cada runa de druida que hoy solo se compra en el Grabador (npc 700000) pasa a conseguirse como en SoD.
Una vez implementada la fuente de una runa, se quita del `npc_vendor` del Grabador (entry 700000) en el mismo commit.
Referencias: `docs/progreso/druida.md` §5, `docs/runas/fuentes-sod.json`, datos verificados en
`.agents/plans/druida-fuentes/fuentes.md`. Precedentes de código: mago (`server/mod-sod-content/src/mage/sod_mage_azora_event.cpp`,
`data/sql/db-world/base/sod_mage_*_unlock.sql`) y `src/world/` (oficiales de suministro). Ids propios en la banda 700200-700299
salvo que un id real de SoD esté libre. SQL sin DELETE (REPLACE/INSERT IGNORE). Validar con `tools/sod-data/validar_sql.sh`.
Cada paso: una tarea AgentRelay, revisión del orquestador, commit, fila en `docs/progreso/druida.md`, CHANGELOG/estado.

## Paso 0. Coordenadas (investigación)
Para PNJ/objetos de SoD que no existen en el core, hay que tener zona y coordenadas (mapa, x, y, z). Anotarlas en `fuentes.md`.
Estado: pendiente.

## Pasos de implementación (de menos a más complejo)
1. Botín de criatura única: Living Seed (Unleashed Nature Spirit 206245, lvl 7, Mulgore/Teldrassil), Gale Winds (Namida Grimtotem
   222286, lvl 43, Feralas), Starfall (Arcterris 228814, élite lvl 58, Winterspring).
2. Gore: 4 intendentes (Falinar 222684 Duskwood lvl25 16000 cobre; Kyleen 222685 Ashenvale lvl40 16842; Alandra 222686 Hinterlands
   lvl50 16842; Valdane 222687 Feralas lvl50 16000).
3. Rune Broker en las seis capitales (vende runas a 1 cobre): Berserk, Survival Instincts, Starsurge, Wild Growth, Skull Bash…
   Decidir el catálogo exacto según `fuentes.md` (contradicción de los emblemas sin resolver).
4. Misiones: Wild Growth (Trial of the Owls 78229), Nourish (The Lost Saplings 79377), Efflorescence (Wisdom of the Guardians 81924).
5. Objetos de mundo: Sunfire (Lunar Chest), Dreamstate (Blooming Satyrweed / Desiccated Seed Pod), Tree of Life (Gift of the Wisp).
6. Cadenas: Eclipse (Highway Robbery), Elune's Fires (Azshara), Survival Instincts (Amaryllis), Starsurge (Marshroom/Vodyanoi),
   King of the Jungle y Improved Frenzied Regeneration (emblemas 232456 y 232454), Lifebloom (ritual Adventurer's Remains),
   Berserk (por determinar).
7. Limpieza: objetos reales 206970 y 213074 en lugar de 7009026/7009027 (migrar sin romper los ya desbloqueados).
