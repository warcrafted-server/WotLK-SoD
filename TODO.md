# Pendiente (cadenas de misión y contenido no implementado)

Runas y objetos cuya fuente real de Season of Discovery es una **cadena de misión** con NPC, objetos
o zonas que no existen en este core. Hoy se compran todas en el Grabador (`.rune summon`) para poder
jugarlas ya; aquí se documenta la cadena real, verificada en Wowhead, para implementarla más adelante.

Cuando se implemente una de estas entradas, bórrala de aquí y anota el cambio en `CHANGELOG.md`.

## Druida: lo que falta

Las 27 runas de las 11 ranuras tienen código (comparado con `docs/runas/catalogo-sod.json` el
2026-10-09). Falta:

- **Thrash (Cat)** (hechizo SoD 417448, ranura-fase 417437): no implementada. Comprobar en qué fase
  y ranura entra antes de hacerla.
- **Tiger's Fury** (417045): modificación de SoD asociada a King of the Jungle; la runa existe pero no
  cambia Tiger's Fury.
- Compilar y probar en juego las 27 runas (`docs/PRUEBAS.md`).
- Fidelidad: las entradas de abajo (Tree of Life, cadenas de misión, Starfall, Eclipse).

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

### Lacerate: vía de pesca (no prioritaria)

La fuente principal (worgen Moonrage de Silverpine) ya está implementada. Queda sin hacer la vía de
pesca de SoD: «Cebo de Albacora Arcoíris» (objeto 208855) de Khara Deepwater en Lago Thom, usado
junto a un Young Threshadon, o «Golosinas de Cangrejo» para los Young Reef Crawlers de Costa Oscura.

### Starfall

La runa 7009025 (hechizo SoD 439748, espalda) se simplifica como daño Arcano de área que pulsa cada
segundo durante 10 s en un radio de 30 yardas, con coeficiente periódico de 0,127. La versión real
invoca hasta 20 estrellas que seleccionan objetivos y también
dañan enemigos cercanos al impacto; el servidor no reproduce los proyectiles, el máximo de 20
estrellas ni el daño de salpicadura de 5 yardas. Valores contrastados en la
[ficha de Wowhead](https://www.wowhead.com/classic/spell=439748), consulta del 2026-10-07.

### Eclipse

La duración del beneficio de la runa 7009024 (hechizo SoD 408248, cintura) no se ha podido
confirmar con precisión; se configura en 15 s como aproximación. La mecánica simplificada acumula
los beneficios de crítico, tiempo de lanzamiento y retroceso hasta cuatro veces. Consulta del
2026-10-07; comprobar la duración y el comportamiento de las cargas en juego.

## Paladín

Las runas 7002011–7002014 ya están implementadas. Queda probarlas en juego y revisar estas
simplificaciones:

- **Improved Sanctuary: hoy no tiene efecto en juego.** En este core la reducción de daño de
  Blessing of Sanctuary (20911/25899) no está en la bendición: la aplica el aura compartida 68066
  (`spell_gen_damage_reduction_aura`, también de Renewed Hope y Vigilance), así que el SpellMod de
  la runa no la cambia. Falta un script de módulo sobre 20911/25899 (vía `spell_script_names`) que,
  si el lanzador tiene la runa, aplique una reducción extra con un hechizo propio de servidor, y la
  parte de daño por valor de bloqueo (20 %) sobre el proc de la bendición.
- **Hand of Sacrifice (462853): descartada.** En WotLK el paladín ya aprende Mano de sacrificio (6940) a nivel 46
  y se empieza en 60; política del 2026-10-06: las runas redundantes quedan fuera.
- **Infusion of Light:** no reduce el enfriamiento de Choque Sagrado porque en WotLK ya es de 6 s.
- **Light's Grace** reutiliza el aura auxiliar 31834 de WotLK con duración de 15 s. No se ha
  hecho una compilación real ni comprobado en juego que el aura consuma el beneficio exactamente
  tras el siguiente Holy Light.
- **Aegis** dispara los rangos de proc de Redoubt y Reckoning existentes en WotLK. No se ha
  hecho una compilación real ni probado en juego la interacción con los rangos de talentos.

## Otras clases

(Vacío por ahora; se añadirá cuando se investiguen fuentes de otras clases con el mismo problema.)
