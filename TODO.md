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

Las runas 7002015–7002023 están implementadas, pendientes de compilación real y prueba en juego.
Simplificaciones:

- **Sheath of Light:** reutiliza el aura de daño con hechizos, actualizada con el 30 % del poder de
  ataque al acertar un golpe cuerpo a cuerpo. La ficha de [Wowhead](https://www.wowhead.com/classic/spell=426158)
  indica una duración de 1 min (consulta del 2026-10-09).
- **Guarded by the Light:** cada impacto cuerpo a cuerpo renueva el aura de 15 s; recupera el 5 %
  del maná máximo cada 3 s y reduce la sanación realizada un 50 %. Valores contrastados con la
  [ficha de Wowhead](https://www.wowhead.com/classic/spell=415058) (consulta del 2026-10-09).
- **Shock and Awe:** aplica el beneficio de 1 min con 200 % del intelecto como daño con hechizos y
  30 % menos de amenaza tras el daño de Choque Sagrado, solo sin Furia justa. No implementa el
  beneficio Sunlight condicional a Infusion of Light; requiere añadir daño extra para Golpe de
  cruzado, Tormenta divina y ataques contra criaturas. Valores contrastados con las fichas de
  [Shock and Awe](https://www.wowhead.com/classic/spell=462834) y su
  [aura](https://www.wowhead.com/classic/spell=462832) en Wowhead (consulta del 2026-10-09).
- **Hallowed Ground:** calcula la sanación al recibir cada evento de daño periódico de Consagración
  y usa el objeto de área dinámica de ese rango para localizar a los miembros del grupo. No se ha
  probado que el evento informe el daño final deseado ni la interacción con varios enemigos.
  Consagración tiene radio de 8 yardas según la [ficha del rango 8 en Wowhead](https://www.wowhead.com/wotlk/spell=48819/consecration)
  (consulta del 2026-10-09); el código usa el radio del objeto de área dinámica.

Las runas 7002024–7002027 están implementadas, pendientes de compilación real y prueba en juego.
Simplificaciones y datos por revisar:

- **Sacred Shield:** el escudo de absorción conserva el hechizo auxiliar 58597 y su implementación
  de absorción de WotLK. La sanación adicional de Destello de Luz usa la sanación efectiva dividida en
  pulsos de 1 s durante 12 s. No se ha igualado el cálculo de absorción con la fórmula de SoD ni se
  fuerza la restricción de un único objetivo; comprobar ambas diferencias en juego. La ficha
  consultada de [Sacred Shield](https://www.wowhead.com/classic-ptr/spell=412019/sacred-shield)
  muestra un bloqueo de 6 s; el encargo y los datos locales indican 5 s, que es el valor configurado.
- **Inspiration Exemplar:** disipa miedo y sueño cada 4 s entre miembros del grupo en un radio
  configurable de 10 yardas. El catálogo confirma el intervalo; el radio es una aproximación porque
  no se encontró un valor publicado. Revisar su alcance y las mecánicas de sueño en juego.
- **Hand of Reckoning:** se implementan el reembolso del 25 % del maná recibido por sanación y la
  reducción del 20 % del golpe que cruza el umbral del 35 %, mientras Furia recta está activa. La
  amenaza Sagrada del 80 % ya existe en WotLK; se omite la facultad activa porque Mano de expiación
  (62124) ya se aprende en el core. Valores contrastados con [Hand of Reckoning](https://www.wowhead.com/classic/spell=409911/hand-of-reckoning)
  y [Righteous Fury de SoD](https://www.wowhead.com/classic-ptr/spell=407627/righteous-fury), consulta del 2026-10-09.
- **Malleable Protection:** en WotLK Protección divina (498) ya reduce el daño un 50 % y permite
  actuar, que es lo que la runa hace en SoD; la runa solo la alarga un 50 % (de 12 a 18 s) con un script
  enganchado a 498 y da 4 p. de poder de ataque por punto de defensa sobre 5 × nivel durante 15 s al
  activar Escudo Sagrado (hechizo 460171). La versión de SoD sustituye el botón con el aura 332, que no
  existe en 3.3.5a (máximo 316). Valores contrastados con [Malleable Protection](https://www.wowhead.com/classic/spell=458318/malleable-protection),
  consulta del 2026-10-09.
- **Beacon of Light:** el script del módulo lanza el aura original de WotLK (53563), porque el
  proc del core busca ese id y los auxiliares 53651–53654. Se conserva la transferencia de sanación
  del core, con el porcentaje y la duración de SoD. No se ha comprobado en juego qué hechizos de
  sanación adicionales al Holy Light, Flash of Light y Holy Shock reciben una copia adecuada.
- **Divine Light:** conserva las interacciones de Holy Light al clonar el rango 13 de WotLK. Un aura
  temporal detecta la sanación efectiva y crea el escudo 458857 con el 50 % de la sanación excesiva;
  cada escudo nuevo sustituye al anterior. El escudo dura 15 s según la ficha de
  [Divine Light](https://www.wowhead.com/classic/spell=458856) y su
  [aura](https://www.wowhead.com/classic/spell=458857), consultadas el 2026-10-09.
- **Hammer of the Righteous:** conserva el efecto del talento de WotLK 53595; no se ha probado en
  juego que el número de objetivos y el daño por segundo coincidan con SoD.
- **Shield of Righteousness:** conserva el daño basado en el valor de bloqueo del rango 2 de WotLK y
  fija el daño plano adicional en 179. No se ha probado en juego el escalado del daño por bloqueo.
- **Rebuke:** reutiliza la interrupción de Kick (1766), con escuela Sagrada, coste de maná del 10 %,
  reutilización de 15 s y bloqueo de escuela durante 3 s. No se ha probado en juego.

## Chamán

- [ ] Regenerar el SQL de hechizos y el parche de cliente y probar las seis runas nuevas `7007003–7007008` en el reino de desarrollo. Se clonan comportamientos de WotLK; no se han probado. Esta tanda no añade scripts C++ que requieran recompilar. La obtención de SoD no está verificada y la compra al Grabador es provisional.
- [ ] Verificar Maelstrom Weapon: el aura auxiliar SoD `408505` conserva el manejador nativo de `53817`, y las máscaras limitan el modificador a Descarga de relámpagos, Cadena de relámpagos, Ola de sanación inferior y Ráfaga de lava. Falta comprobar en juego las bonificaciones de probabilidad de Viento furioso y arma a dos manos del texto de SoD.
- [ ] Verificar que Ancestral Awakening solo se activa con críticos de Ola de sanación y Ola de sanación inferior como indica SoD; el efecto se hereda del talento de WotLK.
- [ ] El interruptor `SodShaman.Enable` lo consultan los scripts de las cinco runas nuevas `7007009–7007013`; las seis anteriores siguen reutilizando comportamientos nativos.
- [ ] Wowhead no respondió durante esta tarea (curl terminó con error DNS 6); datos y descripciones se tomaron de `docs/runas/catalogo-sod.json` y no se contrastaron en la web.
- [ ] Regenerar el SQL de hechizos y el parche de cliente, compilar y probar las cinco runas `7007009–7007013` en el reino de desarrollo. Aún no están compiladas ni probadas; la obtención por el Grabador sigue siendo provisional.
- [ ] Dual Wield Specialization concede Doble empuñadura y simula el segundo golpe de Golpe de tormenta con un ataque de mano izquierda. El aumento de golpe se aplica de forma permanente mientras la runa está activa, incluso sin arma secundaria; confirmar si es aceptable. Valores contrastados en [Dual Wield Specialization](https://www.wowhead.com/classic/spell=408496) el 2026-10-09.
- [ ] Overload repite el importe final de daño o sanación a mitad con hechizos auxiliares sin amenaza; comprobar especialmente los rebotes de Cadena de relámpagos y Sanación en cadena, y que los auxiliares no vuelvan a activar Overload. Valores contrastados en [Overload](https://www.wowhead.com/classic/spell=408438) el 2026-10-09.
- [ ] Shield Mastery usa los valores actuales verificados de SoD: 8 % de maná, 30 % de armadura del escudo por acumulación (máximo 5, 15 s), +10 % de bloqueo, +15 % de valor de bloqueo y +4 de daño con hechizos por punto de Defensa sobre 5 × nivel durante 15 s. Se consultó [Shield Mastery](https://www.wowhead.com/classic/spell=408524) y [su hechizo auxiliar](https://www.wowhead.com/classic/spell=408525) el 2026-10-09; revisar en juego la mecánica del escudo.
- [ ] Two-Handed Mastery concede +45 % de velocidad de ataque, +10 % de poder de ataque y +10 % de golpe con hechizos durante 10 s tras un golpe con arma a dos manos. Simplificación: el aura genérica de velocidad también afecta a ambas manos hasta que un golpe con arma de una mano la elimina. Valores contrastados en [Two-Handed Mastery](https://www.wowhead.com/classic/spell=436364) el 2026-10-09.
- [ ] Healing Rain sustituye el área moderna de SoD por un aura persistente de WotLK y calcula sanación periódica para hasta cinco miembros del grupo. Se consultaron [Healing Rain](https://www.wowhead.com/classic/spell=415236) y [su efecto de sanación](https://www.wowhead.com/classic/spell=415242) el 2026-10-09; comprobar el área en juego.
- [ ] Regenerar el SQL de hechizos y el parche de cliente, compilar y probar las cuatro runas `7007014–7007017`; no están compiladas ni probadas. La obtención del Grabador es provisional. Wowhead no respondió (curl terminó con error DNS 6); se usó el catálogo local.
- [ ] Ancestral Guidance usa 25 % del daño, convierte el 100 % de la sanación efectiva en daño y busca hasta tres miembros del grupo a 40 yd; el radio se contrastó con [Ancestral Guidance](https://www.wowhead.com/classic/spell=409337) el 2026-10-09. Comprobar que las conversiones no se encadenen y que se use el último objetivo de Choque de llamas.
- [ ] Greater Ghost Wolf aplica el 10 % de reducción mientras el aura 2645 está activa; el valor se contrastó con [Ghost Wolf](https://www.wowhead.com/classic/spell=415233) el 2026-10-09. Su uso en interiores requiere quitar `SPELL_ATTR0_ONLY_OUTDOORS` del hechizo 2645 en el core; no se ha parcheado.
- [ ] Way of Earth implementa +65 % de amenaza, +25 % de salud máxima, −10 % de daño recibido, −6 % de probabilidad de recibir críticos cuerpo a cuerpo y −20 yd al alcance de cinco hechizos; Choque de tierra provoca, se limita al alcance cuerpo a cuerpo y usa una reutilización separada de los otros choques. Los valores se contrastaron con [el hechizo auxiliar Way of Earth](https://www.wowhead.com/classic/spell=408680) y [la descripción de la runa](https://www.wowhead.com/classic/spell=409955) el 2026-10-09. Los bonos solo están activos con Muerdepiedras en mano principal y un escudo.
- [ ] Molten Blast clona Cone of Cold 120, limita el cono a 10 objetivos y usa los valores de daño, coeficiente, coste y enfriamiento contrastados con [Molten Blast](https://www.wowhead.com/classic/spell=425339) el 2026-10-09. La amenaza alta descrita por SoD aún no está implementada: la fuente consultada no publica un multiplicador y no se ha inventado; queda por verificar en juego.
- [ ] Regenerar el SQL de hechizos y el parche de cliente, compilar y probar las cinco runas `7007018–7007022`; el código de esta tanda aún no se ha compilado ni probado. La adquisición provisional es la compra al Grabador.
- [ ] Power Surge implementa el 5 % de proc del catálogo, los reinicios, las auras de lanzamiento instantáneo y el maná periódico equivalente al 2 % del intelecto. Duración de las auras instantáneas: 10 s (`415105` y `468526`, tooltip de Wowhead consultado el 2026-10-09; existe además una versión combinada `440285` de 15 s que no se usa).
- [ ] Decoy Totem reutiliza la criatura WotLK Sentry Totem (3968), concede inmunidad a raíces y ralentizaciones y absorbe el siguiente ataque físico con una protección. No transfiere realmente el ataque ni su daño al tótem; es una simplificación para evitar parchear el core. La inmunidad dura provisionalmente 10 s, igual que el tótem, porque no se verificó la duración de `436391d`.
- [ ] Spirit of the Alpha limita el aura de amenaza del 45 % a un objetivo durante 30 min. Si se lanza sobre otro, el chamán gana Loyal Beta (`443320`): +5 % de daño físico, de fuego, de escarcha y de naturaleza y −30 % de amenaza, 30 min (tooltip de Wowhead, 2026-10-09).
- [ ] Burn duplica el daño directo y periódico de Choque de llamas, añade 6 s a su duración y concede un 150 % del intelecto como daño mágico con Lengua de Fuego en la mano principal. No propaga Choque de llamas a cinco objetivos: el SpellMod moderno de objetivos en cadena no lo implementa para este hechizo en WotLK.
- [ ] Mental Dexterity activa un 150 % del intelecto como poder de ataque y un 35 % del poder de ataque total tras el aumento como daño con hechizos al dañar con Golpe de tormenta, durante 30 s (`415144`, tooltip de Wowhead, 2026-10-09).
- [ ] Los auxiliares nuevos usan IDs `900042–900047`: los IDs `900029–900041` ya existían en los datos locales al revisar esta tanda, aunque la petición esperaba que estuvieran libres.
- [ ] Consultar `spell_script_names` y `spell_proc` de las plantillas WotLK antes de regenerar el SQL: `mysql acore_world` no pudo conectar al socket local, por lo que no se verificaron esas filas.
- **Dual Wield Specialization:** los bonos de golpe se aplican siempre, no solo con dos armas. Golpe de
  tormenta ya golpea con ambas armas en WotLK, así que la runa no añade golpe extra.
- **Overload:** las copias (900032–900036) usan la mitad del daño o la sanación final del hechizo original y
  no vuelven a aplicar el poder con hechizos; pueden ser críticas.

## Otras clases

(Vacío por ahora; se añadirá cuando se investiguen fuentes de otras clases con el mismo problema.)
