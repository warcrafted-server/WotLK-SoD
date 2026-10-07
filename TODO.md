# Pendiente (cadenas de misión y contenido no implementado)

Runas y objetos cuya fuente real de Season of Discovery es una **cadena de misión** con NPC, objetos
o zonas que no existen en este core. Hoy se compran todas en el Grabador (`.rune summon`) para poder
jugarlas ya; aquí se documenta la cadena real, verificada en Wowhead, para implementarla más adelante.

Cuando se implemente una de estas entradas, bórrala de aquí y anota el cambio en `CHANGELOG.md`.

## Druida feral

### Tree of Life

La runa 7009020 (hechizo SoD 439733, capa) se implementa como una pasiva activada al grabarla:
aplica los bonos numéricos de curación, maná y estadísticas, además del aura de sanación al grupo
cercano. No cambia el modelo del personaje porque no se añadió un `ShapeshiftFormID` al core; por
ello tampoco reproduce la barra/forma de árbol, la inmunidad a Polymorph ni la liberación de
efectos de movimiento al cambiar de forma. El hechizo dañino tampoco queda bloqueado mientras la
runa está activa. La forma real transforma al druida en árbol y bloquea los hechizos dañinos.

### Survival Instincts (runa de Instinto, pies, hechizo SoD 408024, objeto 213119)

Cadena de misión «Amaryllis la Tejedora» (Amaryllis Webb), en Pantano de las Penas (Swamp of
Sorrows) (25, 54). Verificado en la guía de Wowhead
[Survival Instincts Rune Guide](https://www.wowhead.com/classic/guide/season-of-discovery/classes/druid/survival-instincts-rune)
(consultado 2026-10-07):

1. Recoger 3 bichos, uno por zona (las coordenadas son aproximadas, el bicho puede aparecer en un
   radio alrededor):
   - **Araña Arbórea** (Arbor Tarantula) en Vale de Stranglethorn (45, 19), junto al campamento
     maderero.
   - **Gorgojo del Heno** (Hay Weevil) en Tierras Altas de Arathi (31, 28), en granjas y establos.
   - **Recolector de Carne** (Flesh Picker) en Desolace (51, 59).
2. Entregar los 3 bichos a Amaryllis la Tejedora en Pantano de las Penas (25, 54) **sin tener el
   inventario lleno** (si se entrega con el inventario lleno, consume los bichos sin dar la runa).
3. Recompensa: la runa de Instinto.

No depende del orden en que se recojan los bichos. Nivel recomendado por Wowhead: 30 (aunque hay
testimonios de haberlo hecho antes).

### King of the Jungle (runa del Rey de la Selva, cintura o pies según ranura, hechizo SoD 417046,
objeto 213118, fase 2 de SoD)

Cadena de misión de «Reliquias de Dalaran», con un agente de Dalaran inicial y jinetes oscuros
(Dark Riders) repartidos por 7 zonas. Verificado en la guía de Wowhead
[King of the Jungle Rune Guide](https://www.wowhead.com/classic/guide/season-of-discovery/classes/druid/king-of-the-jungle-rune)
(consultado 2026-10-07):

1. Conseguir el «Sello de Ariden» (Ariden's Sigil) del Agente de Dalaran, en un campamento
   (Campamento de Ariden) al noroeste de Vado de la Muerte (Deadwind Pass), justo al norte de la
   bifurcación del camino que viene de Pantano de las Penas.
2. Matar a los Jinetes Oscuros (npc 218931, nivel 41 élite; se puede matar en grupo/banda, pero
   cada jugador debe golpearlo para que le cuente el botín) en 7 zonas, cada uno suelta una
   reliquia distinta para una submisión distinta:
   - Vado de la Muerte (Deadwind Pass) (43, 29)
   - Bosque Crepuscular (Duskwood) (23, 47)
   - Pantano de las Penas (Swamp of Sorrows) (69, 28)
   - Tierras Altas de Arathi (Arathi Highlands) (60, 40)
   - Tierras Baldías (Badlands) (58, 54)
   - Los Baldíos (The Barrens) (52, 36)
   - Desolace (65, 25)
3. Entregar las reliquias para completar la cadena; recompensa final: la runa del Rey de la Selva.

No hace falta el Sello de Ariden para que los Jinetes Oscuros suelten las reliquias, solo para
**invocarlos** (según un comentario; no verificado del todo). No montar al matar al jinete o no se
obtiene el buff necesario («Presencia Oscura»).

### Lacerate (runa de Laceración, piernas, hechizo SoD 414644, objeto 208687) — alternativa más simple

Tiene una fuente directa en SoD, más simple que las dos anteriores: el objeto **«Ídolo
Desequilibrado»** (Unbalanced Idol, id SoD 210195, ídolo alternativo que también enseña Lacerate)
lo sueltan Worgen y Osos comunes de **Bosque de Argénteo Lunar (Silverpine Forest)**. Comprobado en
la base de datos de este core (`acore_world`, usuario de solo lectura, 2026-10-07): **no existe
ningún Worgen humanoide común en Silverpine Forest en WotLK 3.3.5a** (el único «Worgen» del juego es
el Nightbane Worgen, exclusivo de la mazmorra Karazhan). Sí hay dos osos cuyas coordenadas
(`creature_template` 1778 «Ferocious Grizzled Bear» y 1797 «Giant Grizzled Bear», mapa 0, X entre
-300 y 1300, Y entre 1100 y 2000) son compatibles con esa zona, pero no he confirmado con una
segunda fuente que esas coordenadas sean exactamente Silverpine (podrían ser Tirisfal Glades,
zona vecina). Pendiente: confirmar la zona exacta de esas dos entradas de criatura (comparando con
un mapa de referencia o con `WorldSafeLocs`/`areatriggers` de esa zona) y, si se confirma, añadir el
botín del ídolo en
`server/mod-sod-content/data/sql/db-world/base/sod_druid_acquisition.sql`. Es tarea pequeña, no
cadena de misión — hacerla antes que las dos anteriores en cuanto se confirme la zona.

Hay una segunda vía alternativa para Alianza (pesca): comprar «Cebo de Albacora Arcoíris»
(Rainbow Fin Albacore Chum, objeto 208855) a Khara Deepwater en Lago Thom (Loch Modan), y usarlo
cerca de un Young Threshadon; o pescar en Costa Oscura (Darkshore) cerca de la ruta de vuelo para
obtener «Golosinas de Cangrejo» (Crab Treats) y dárselas a los Jóvenes Cangrejos de Arrecife (Young
Reef Crawlers) cercanos. Es más compleja que la fuente de Silverpine; no priorizar.

### Starfall

La runa 7009025 (hechizo SoD 439748, espalda) se simplifica como daño Arcano de área que pulsa cada
segundo durante 10 s en un radio de 30 yardas; se conserva la curva de daño y su coeficiente
periódico de 0,127. La versión real invoca hasta 20 estrellas que seleccionan objetivos y también
dañan enemigos cercanos al impacto; el servidor no reproduce los proyectiles, el máximo de 20
estrellas ni el daño de salpicadura de 5 yardas. Valores contrastados en la
[ficha de Wowhead](https://www.wowhead.com/classic/spell=439748), consulta del 2026-10-07.

## Otras clases

(Vacío por ahora; se añadirá cuando se investiguen fuentes de otras clases con el mismo problema.)
