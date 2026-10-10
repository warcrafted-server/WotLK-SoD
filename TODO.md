# Pendiente (cadenas de misión y contenido no implementado)

Runas y objetos cuya fuente real de Season of Discovery es una **cadena de misión** con NPC, objetos
o zonas que no existen en este core. Hoy se compran todas en el Grabador (`.rune summon`) para poder
jugarlas ya; aquí se documenta la cadena real, verificada en Wowhead, para implementarla más adelante.

Cuando se implemente una de estas entradas, bórrala de aquí y anota el cambio en `CHANGELOG.md`.

## Revisión pendiente con el usuario (2026-10-09)

- **Runas sin su fuente real de SoD:** `docs/runas/fuentes-no-disponibles.md`. Ninguna se descarta: se compran en el
  Grabador. Además, 33 runas implementadas aún no tienen objeto-runa y no se pueden comprar (sección 1): crearlo.
- **Runas que coinciden con algo que la clase ya aprende:** `docs/runas/redundantes.md`, para decidir una a una.
  Hasta entonces no se descartan: Hand of Sacrifice, Water Shield y Fire Nova quedan pendientes de esa decisión.

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
- **Hand of Sacrifice (462853): pendiente de decisión** (`docs/runas/redundantes.md`).
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
- [ ] El interruptor `SodShaman.Enable` lo consultan los scripts propios de `7007009–7007013` y `7007023–7007025`, `7007027`; las runas anteriores siguen reutilizando comportamientos nativos.
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
- [ ] Regenerar el SQL de hechizos y el parche de cliente, compilar y probar las runas `7007023–7007027` en el reino de desarrollo. Esta tanda no se ha compilado ni probado; la obtención por el Grabador sigue siendo provisional.
- [ ] Overcharged restaura la carga consumida por Escudo de relámpagos y reduce su cooldown nativo a 3 s; combinado con Rolling Thunder o Static Shock conserva hasta nueve cargas. El proc nativo golpea al atacante y el script añade el daño de la misma carga a los demás enemigos en 8 yd. Verificar que no se duplique el objetivo principal.
- [ ] Rolling Thunder añade cargas hasta 9 con probabilidad del 50 % en golpes de Descarga y Cadena de relámpagos. Choque de tierra libera las cargas por encima de 3, lanza el daño de Escudo de relámpagos una vez por carga y restaura el 2 % del maná máximo por carga.
- [ ] Static Shock clona el talento WotLK 51527 y conserva su manejador nativo de daño; el script propio limita el proc al 12 % con una mano secundaria vacía y al 6 % al empuñar dos armas. Overcharged evita que este proc consuma cargas.
- [ ] Coherence usa SpellModOp 20 con modificadores derivados para dejar el multiplicador por salto en 65 % y 80 %, y SpellModOp 17 para un objetivo adicional. Verificar esos resultados en juego.
- [ ] Storm, Earth, and Fire aplica −25 % al cooldown de Cadena de relámpagos y +60 % al daño periódico de Choque de llamas con SpellModOp 11 y 22. Un hook en el aura 6474 de Tótem Nexo Terrestre lanza Pillaterra (64695); comprobar su duración y selección de objetivos.

## Brujo

- [ ] Compilar y probar `7008004–7008008` (el SQL de hechizos ya está regenerado); esta tanda no se ha compilado ni probado. La adquisición al Grabador es provisional y no se verificaron las fuentes reales de SoD.
- [ ] Unstable Affliction conserva el manejador nativo de disipación de WotLK. No se implementó la exclusión mutua con Immolate que describe SoD; comprobar daño, silencio y conflicto con Immolate en juego.
- [ ] Metamorphosis clona Demon Form de WotLK (47241), desbloqueado por el talento 59672. Conserva su forma de tanque, pero no implementa Shadow Cleave, Menace ni Demon Charge; las auras modernas de SoD no existen en WotLK 3.3.5a. Confirmar también armadura, salud, reducción de críticos, amenaza y conversión de Life Tap.
- [ ] Incinerate y Shadowflame reutilizan los hechizos y scripts nativos de WotLK; comprobar en juego el aumento de daño de Fuego y la aplicación del daño periódico de Shadowflame.
- [ ] Wowhead no se consultó en esta ejecución; se usaron los datos facilitados en el encargo y el catálogo local.
- [ ] Backdraft (Explosión de humo) `7008009`: se implementa con el aura 109 (disparo sobre Conflagrar) y el buff 427714 (30 % de celeridad, 15 s). SoD dice que Conflagrar «ya no consume Inmolar»; ese consumo vive en el core (`AURA_STATE_CONFLAGRATE` en `SpellEffects.cpp`) y no se puede evitar desde un módulo, así que queda pendiente (requeriría parchear el core).
- [ ] Decimation `7008010`: reutiliza el manejador nativo `spell_warl_decimation` (umbral de salud 35 %) y su fila `spell_proc` copiada al id 440870; comprobar en juego el enfriamiento cero de Fuego de alma, la reducción de lanzamiento del buff 440873 y que ese lanzamiento no cuesta fragmento.
- [ ] Demonic Pact `7008011`: el +10 % de daño de Fuego y Sombras va por aura 79 y el efecto de grupo depende del aura de mascota nativa 54909 (script `spell_warl_demonic_pact` de WotLK); el módulo inserta el `spell_pet_auras` 425464→54909.
- [ ] Aflicción eterna `7008012`: el script nativo `spell_warl_everlasting_affliction` (sobre el disparador 412698) refresca Corrupción sólo con los hechizos de WotLK; SoD además incluye Cuchilla de las Sombras y Dolor abrasador, que no existen en 3.3.5a.
- [ ] Conocimiento demoníaco `7008013`: usa el aura de mascota 900048 (3 %) en lugar de la nativa 35696 (12 %); el script nativo calcula el importe a partir del aguante más intelecto. El id auxiliar 900048 continúa la serie del chamán (900042–900047).
- [ ] Compilar y probar `7008009–7008013`; el SQL de hechizos y el parche de cliente ya están regenerados el 2026-10-09 (`datos/parche-cliente/20261009-brujo/`, sin publicar). La compra al Grabador es provisional y no se verificaron las fuentes reales de SoD.
- [ ] `src/warlock/spell_sod_warlock.h` (catálogo de ids y `SodWarlock.Enable`) lo incluyen ya `spell_sod_warlock_soul_siphon.cpp` y `spell_sod_warlock_master_channeler.cpp`, y ambos están registrados en `sod_content_loader.cpp`. El bloque `SodWarlock.Enable` sí está en `mod_sod_content.conf.dist` (línea 420), pero el `mod_sod_content.conf` vivo del reino de desarrollo es anterior y no lo tiene: da igual mientras nadie lea la clave, porque `SodWarlockEnabled()` usa `true` por defecto.
- [ ] Tercera tanda `7008014–7008018` (fase 3): necesita recompilar el módulo (Soul Siphon y Master Channeler añaden C++), además de regenerar el SQL y el parche de cliente. Adquisición provisional por el Grabador (1 oro).
- [ ] Soul Siphon `7008014`: reutiliza el talento de WotLK 17805 r2 (aura 112 con MiscValue 4993) para el +6 % por efecto de las Sombras y el máximo del 18 %, y un SpellModOp 19 (−2000 ms sobre Drenar alma) para el canal 3 veces más rápido. El script propio sólo añade que Drenar alma pueda activar Ocaso (usa la probabilidad del talento 18094/18095 y lanza Trance de las Sombras 17941). **No se implementa** el ramal de SoD «cuando Drenar alma se lanza sobre un objetivo por debajo del 20 % de salud, gana un 50 % por efecto hasta 150 %»: no existe equivalente en WotLK y exigiría reescribir el reparto con las dummies modernas del catálogo. Tampoco se reproduce que el bonus nativo del core se limite a Drenar vida/Drenar alma: es comportamiento del propio core.
- [ ] Shadow and Flame `7008015`: aura 42 + beneficio 426311 (+10 % a Fuego y Sombras durante 10 s) con fila `spell_proc` por crítico. El filtro de familia va completo (0xFFFFFFFF en las tres máscaras), así que proca con cualquier hechizo de brujo y no sólo de Fuego/Sombras: el cliente de 3.3.5a no ofrece un conjunto de bits para esas dos escuelas y no se inventa.
- [ ] Lake of Fire `7008016`: sólo añade 8 s de reutilización (SpellModOp 11) a Lluvia de fuego. **No se implementa «ya no se canaliza»**: el aura moderna 332 del catálogo no existe en 3.3.5a y quitar el canal exige cambiar el DBC del hechizo base (o parchear el core). Queda como runa parcial: mientras no se resuelva, Lluvia de fuego canaliza y además tiene reutilización.
- [ ] Master Channeler `7008017`: SpellModOp 14 (coste +100 %) sobre Drenar vida y script propio `spell_sod_warlock_master_channeler` que añade el 50 % de sanación por tick. **No se implementan** «ya no se canaliza» ni la duración/reutilización nuevas (los valores `403677d` no constan en los datos locales), así que no se toca el canal del hechizo base.
- [ ] Shadow Bolt Volley `7008018`: SpellModOp 17 (+5 objetivos de cadena) y SpellModOp 0 (−30 % de daño) sobre Descarga de las Sombras. Pendiente comprobar en juego que el SpellMod de cadena funciona sobre un hechizo que en WotLK no es encadenado.
- [ ] Cuarta tanda `7008019–7008023` (fase 4): necesita recompilar el módulo (Invocation y Dance of the Wicked añaden C++), regenerar el SQL y el parche de cliente. Adquisición provisional por el Grabador (1 oro).
- [ ] Demonic Grace `7008019`: se activa (20 s de reutilización, 6 s de duración) con +20 % de esquiva (aura 49) al brujo y a su mascota y +20 % de crítico global (aura 290) al brujo. Sin C++ propio.
- [ ] Invocation `7008020`: pasiva; el script `spell_sod_warlock_invocation` (enganchado con ids negativos a las auras de Corrupción 172, Inmolar 348, Maldición de agonía 980, Aflicción inestable 30108 y el DoT de Llama de las Sombras 47960, y con el id 35195 de Succionar vida) inflige al instante un pulso del daño periódico al aplicar o refrescar el DoT. **No se implementa** la rama «refrescar con menos de 6 s de duración inflige el daño periódico restante»: el core reinicia la duración antes de que el aviso lo vea, así que siempre se aplica un pulso. **No verificado**: que 35195 sea el primer rango de la cadena de Succionar vida (sin MySQL en el entorno); si el core lo rechaza, el enganche de ese hechizo no carga.
- [ ] Dance of the Wicked `7008021`: pasiva con proc por crítico (HitMask 2) que aplica el beneficio 900050 al brujo y a su mascota, con esquiva igual al 70 % (efecto del catálogo) de la probabilidad de crítico con hechizos de Sombras. **No se implementa** la recuperación de maná de SoD (`$412800s2%`): su valor no consta en el catálogo local y no se inventa. Duración del beneficio: 15 s (tooltip de Wowhead del hechizo 412800, consultado el 2026-10-10).
- [ ] Vengeance `7008022`: se activa (180 s de reutilización, 20 s de duración) y da +30 % de salud máxima. El catálogo pide el aura 34, pero en 3.3.5a el aura 34 es un aumento plano de salud y el porcentaje es el aura 133 (como en el chamán Way of Earth), así que se usa 133. El core ya resta la salud al expirar. **No se implementa** la caída lenta durante Metamorfosis.
- [ ] Immolation Aura `7008023`: pasiva; el aura 42 dispara el daño 427725 al recibir un ataque cuerpo a cuerpo, con enfriamiento de proc de 1 s (no más de una vez por segundo), y añade −10 % de daño mágico recibido (aura 87, escuelas mágicas) y +10 % de daño de Fuego (aura 79). El daño 427725 clona 50590 (el de Aura de Inmolación de Metamorfosis de WotLK), sin C++ propio.
- [ ] Quinta tanda `7008024–7008027` (fase 5): necesita recompilar el módulo (Infernal Armor y Grimoire of Synergy añaden C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro).
- [ ] Infernal Armor `7008024`: activa (3 % de maná, 10 s de duración, 60 s de reutilización); el efecto aura 87 (escuelas mágicas) reduce el daño mágico recibido un porcentaje igual al 60 % de la reducción de daño físico por armadura del brujo, calculado en `spell_sod_warlock_infernal_armor` con la fórmula de armadura del core (`0,1 × armadura / (8,5 × nivel + 40)`, normalizada y con tope del 75 %). SoD trae −21 como importe de ejemplo a nivel 60 (la ficha usa $s2 = 60 %); no se pudo verificar el valor exacto de SoD, así que se reproduce la fórmula del core y se anota.
- [ ] Mark of Chaos `7008025`: pasiva; el aura 109 de 440892 dispara la marca 461615 sobre el enemigo al lanzar las maldiciones (las máscaras A/B/C se copian de SoD). El debuff 461615 usa aura 22 (−27 a las resistencias, escuelas mágicas) y aura 87 (+4 % de daño recibido, escuelas mágicas). **No se implementa** el escalado con el nivel que describe SoD (`$max($min($PL+19,75),27)` y `$max($min(($PL-8)*0.125+4,10),4)`): van fijos en el mínimo del catálogo. Los efectos 1 y 2 de 440892 (dummies que enlazaban el hechizo 440895, ajeno a la mecánica) se conservan como dummies sin disparo.
- [ ] Pandemic `7008026`: pasiva; el crítico del daño periódico lo aporta el aura nativa 286 (`SPELL_AURA_ABILITY_PERIODIC_CRIT`) con las máscaras de familia de SoD, que cubren Corrupción, Aflicción inestable, Maldición de agonía, Inmolar, Maldición del Apocalipsis y Succionar vida. **Se omite** el segundo efecto del catálogo (aura 108 + SpellModOp 15): en 3.3.5a el SpellModOp 15 es el bono de daño crítico, no el crítico periódico, y el core ya resuelve el crítico con el aura 286.
- [ ] Grimoire of Synergy `7008027`: pasiva con proc del 10 % por daño infligido (valor del tooltip de Wowhead del hechizo 426301, consultado el 2026-10-10; el catálogo local daba 6). El beneficio 426303 (+10 % a todo el daño, 15 s) se aplica al "otro": si proca el brujo (aura 1226981) va a su mascota y si proca el demonio (aura auxiliar de servidor 900051, recibida al invocarlo vía `spell_pet_auras 1226981 → 900051`) va al dueño. Para la parte del demonio hay que invocar la mascota **después** de grabar la runa; el auxiliar 900051 sigue la serie de ids de servidor 9000xx.

## Guerrero

- [ ] Primera tanda `7001002–7001006` (fase 1): necesita recompilar el módulo (Blood Frenzy, Flagellation, Raging Blow y Warbringer añaden C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Blood Frenzy `7001002`: pasiva; el aura 275 (con la máscara de Desgarrar 0x20) deja lanzar Desgarrar en actitud rabiosa y el aura 108 con SpellModOp 22 (daño periódico) sube un 100 % su daño periódico, todo con auras nativas. El daño extra igual al 4 % del poder de ataque lo añade `spell_sod_warrior_blood_frenzy` en cada tick de Desgarrar. El valor del AP se fija al aplicar el sangrado (el core no recalcula el importe por tick).
- [ ] Flagellation `7001003`: pasiva de marcador; el script de unidad `unit_sod_warrior_flagellation` (enganches `ModifyMeleeDamage` y `ModifySpellDamageTaken`) concede la ira del daño físico recibido como si no hubiera armadura, reconstruyendo con `Unit::CalcArmorReducedDamage` la parte mitigada. Cubre ataques automáticos y facultades físicas con arma; usa la armadura actual del guerrero.
- [ ] Raging Blow `7001004`: activa, 115 % del daño del arma, 8 s de enfriamiento y sin coste de ira (el catálogo no fija coste). El script de hechizo `spell_sod_warrior_raging_blow` exige Enfurecer (12880), Ira rabiosa (18499) o Ira sangrienta (29131). El reductor de enfriamiento vive en `player_sod_warrior_raging_blow`, que resta 1 s al lanzar una facultad de escuela física; «facultad cuerpo a cuerpo» se aproxima a los hechizos físicos y por tanto también cuenta Ira rabiosa/Ira sangrienta. Ira sangrienta solo se detecta con su rango que aplica aura (29131): la versión de rango 1 (2687) solo energiza al instante.
- [ ] Warbringer `7001005`: pasiva; el aura 262 con MiscValue 1 hace Cargar usable en combate y el aura 275 (máscaras 0x1, 0x40000000 y 0x10000) anula el requisito de actitud de Cargar, Interceptar e Intervenir. El script `spell_sod_warrior_warbringer` (enganchado con ids negativos a los tres hechizos) quita raíces y ralentizaciones al activarlos. El catálogo trae MiscValue 0 para el aura 262; aquí se usa 1 porque el core de 3.3.5a solo levanta el requisito de combate con ese valor.
- [ ] Commanding Shout `7001006`: clon del Grito de orden de WotLK (47440). Diferencia conocida: en 3.3.5a el grito sube la salud máxima (aura 230) y SoD pide aguante (aura 29); se conserva el comportamiento nativo del cliente en vez de inventar un importe de aguante.
- [ ] Segunda tanda `7001007–7001011` (fase 1): necesita recompilar el módulo (Consumed By Rage, Frenzied Assault, Meathook y Quick Strike añaden C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Consumed By Rage `7001007`: pasiva de marcador con aura 226 (periodic dummy, 1 s); `spell_sod_warrior_consumed_by_rage` aplica Enfurecer nativo (12880) al superar 60 de ira (`GetPower(POWER_RAGE)` guarda la ira en décimas, de ahí el umbral 600). Diferencia conocida: 12880 dura 4 s, no los 12 s de la ficha, y se reintenta en cada sondeo mientras la ira siga por encima del umbral. El golpe de mano izquierda de Torbellino mientras está enfurecido lo aporta el Torbellino nativo (disparo 44949).
- [ ] Frenzied Assault `7001008`: pasiva con aura 226 (periodic dummy, 2 s) y aura dummy 4; `spell_sod_warrior_frenzied_assault` concede o retira la celeridad auxiliar 900052 (aura 138, +40 %) al empuñar o soltar un arma a dos manos, y con el proc del aura dummy (proc `PROC_MELEE_HITS`) añade 2 de ira por golpe certero (4 en crítico). La celeridad se revisa con un sondeo cada 2 s (puede tardar en reflejarse al cambiar de arma); no se pudo verificar un mecanismo exacto en SoD.
- [ ] Furious Thunder `7001009`: pasiva con auras nativas sobre Atronar (máscara 0x80): aura 107 + SpellModOp 12 (−6 % al efecto de ralentización, o sea +6 % de tiempo entre ataques), aura 275 (usable en cualquier actitud) y aura 108 + SpellModOp 3 (+100 % de daño). **Se omite** el +75 % de amenaza (aura 108 + SpellModOp 2): el catálogo pide cuatro efectos y `spell_dbc` de 3.3.5a solo tiene tres, y no cabe en un auxiliar sin lógica extra.
- [ ] Meathook `7001010`: activa (15 de ira, 35 s de enfriamiento; el coste es el de `docs/runas/warrior.md`, el catálogo solo trae el 0 %). El arrastre lo hace el efecto nativo 124 (`SPELL_EFFECT_PULL_TOWARDS`), en lugar del efecto DUMMY 3 del catálogo, que no tiene comportamiento por sí solo. `spell_sod_warrior_meathook` restringe el objetivo: como mucho un nivel por encima del lanzador y ni jefes de banda ni de mazmorra. **No se implementa** el «restringir» (enraizar) al objetivo, que exigiría un aura o script extra que el catálogo no aporta.
- [ ] Quick Strike `7001011`: activa (20 de ira, sin enfriamiento; coste de `docs/runas/warrior.md`, el catálogo solo trae el 0 %), instantánea, con `DefenseType` cuerpo a cuerpo. `spell_sod_warrior_quick_strike` exige un arma a dos manos en la mano principal. El daño es una SCHOOL_DAMAGE basada en el poder de ataque (coeficiente 0,29 = $m1/100 del catálogo), con la máscara de Golpe heroico (0x40) para heredar sus talentos, y se engancha el script del core `spell_warr_heroic_strike` a 429765 para activar los efectos asociados a Golpe heroico. Diferencia conocida: el daño no usa el arma (el catálogo solo trae el efecto 2 con puntos base 29).
- [ ] Tercera tanda `7001012–7001016` (fase 1): necesita recompilar el módulo (Single-Minded Fury añade C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Single-Minded Fury `7001012`: pasiva con aura 226 (periodic dummy, 2 s) y aura dummy 4; `spell_sod_warrior_single_minded_fury` concede o retira la velocidad de movimiento 430472 (aura 129, +10 %) según haya doble empuñadura, y en cada ataque automático que golpea al mismo objetivo que el anterior aplica o renueva la celeridad 461470 (aura 138, +4 %, hasta 5 acumulaciones de 10 s); si el objetivo cambia, la retira. Los valores de los dos auxiliares se tomaron del DBC de SoD 1.15.9 (`datos/wago/1.15.9.70003`); no se pudieron contrastar en Wowhead (respuesta 403).
- [ ] Victory Rush `7001013`: clon del de WotLK 34428; el daño por poder de ataque ya lo aplica el core por los flags de familia de la plantilla (`SpellFlags[1] & 0x100`), así que no se añade `spell_bonus_data`. Se añaden la sanación de SoD (efecto 136, 30 %) y 8 s de enfriamiento. **Pendiente**: el estado que lo habilita tras matar (Victorioso, 32216) es nativo de WotLK; no se ha comprobado que el core lo conceda al aprender la runa por el Grabador.
- [ ] Blood Surge `7001014`: pasiva con aura 42 que dispara la marca 413399 al acertar Golpe heroico (0x40), Sed de sangre (0x400) o Torbellino (0x4), con un 30 % de probabilidad (fila `spell_proc` propia). La marca 413399 clona el ¡Embate! de WotLK (46916), conserva su proc y añade −100 % al coste (SpellModOp 14 sobre la máscara de Embate). **No se implementa** que Embate golpee con ambas armas: el dato extraído del cliente de SoD solo trae instantáneo y sin coste.
- [ ] Focused Rage `7001015`: pasiva; clon del talento de WotLK 29787 (aura 107, SpellModOp 14) con el valor de SoD (−30 = −3 de ira) en un id nuevo `413405`. El id de SoD (29787) ya existe en el cliente de 3.3.5a y el generador no permite crear una fila con un id existente, así que no se reutiliza; se conserva la máscara de familia del talento.
- [ ] Precise Timing `7001016`: pasiva con auras nativas 108 (SpellModOp 10, −100 % de tiempo de lanzamiento) y 107 (SpellModOp 11, +6000 ms de enfriamiento sobre Embate) con la máscara de Embate 0x200000. Sin C++.
- [ ] Cuarta tanda `7001017–7001021` (fase 1): necesita recompilar el módulo (Gladiator Stance añade C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Enraged Regeneration `7001017`: clon del de WotLK 55694. Ya sana un 3 % de la salud máxima cada segundo durante 10 s (aura 20), exige estar enfurecido (estado de aura 17, que cubren Enfurecer, Ira rabiosa e Ira sangrienta) y es usable aturdido (inmunidad al aturdimiento nativa del efecto 2). Sin C++.
- [ ] Gladiator Stance `7001018`: activa y permanente; el aura 36 (forma 24) la marca como actitud y el sondeo de 1 s (aura 226) mantiene dos auxiliares: 900053 con escudo (+10 % de daño de todas las escuelas y +10 % de probabilidad de bloqueo, más el aura 275 con todas las máscaras para poder usar facultades restringidas a otras actitudes) y 900054 (−30 % de armadura y −30 % de amenaza). El script `spell_sod_warrior_gladiator_stance` alterna el bono de escudo según se empuñe uno. **Diferencias conocidas**: la forma 24 no existe en el cliente de 3.3.5a (el core registra «Unknown Shapeshift Type» al aplicarla y el cliente no muestra una actitud propia) y **no se implementa** el bono de ira de los ataques automáticos contra enemigos que no te tienen como objetivo. Los valores 10/10/30/30 se tomaron del DBC de SoD 1.15.9 (`datos/wago/1.15.9.70003`); no se pudieron contrastar con Wowhead.
- [ ] Intervene `7001019`: clon del de WotLK 3411, que ya corre hacia el aliado, intercepta el siguiente ataque y le reduce la amenaza. Se copia al id nuevo el script del core `spell_warr_intervene` (lanza el disparo 59667). Sin C++ propio.
- [ ] Rallying Cry `7001020`: activa (10 s de duración, 3 min de enfriamiento); clon del Grito de orden (47440) con la salud fija del efecto (aura 230) cambiada a porcentaje (aura 133, +15 %). Conserva el objetivo de raid (56), el radio y el coste de ira (10) nativos de 3.3.5a. Sin C++.
- [ ] Endless Rage `7001021`: clon del talento de WotLK 29623 (aura 213) como pasiva gratuita; +25 % de ira por todo el daño infligido. Sin C++.
- [ ] Gladiator Stance `7001018`, riesgo comprobado en el core (2026-10-10): la forma 24 existe en `SpellShapeshiftForm.dbc` (sin hechizos de actitud), así que no hay caída del servidor, pero `HandleAuraModShapeshift` registra «Unknown Shapeshift Type: 24» cada vez que se aplica, y las habilidades con requisito de actitud pueden fallar al no ser una de las tres nativas. Probar en juego.
- [ ] Quinta tanda `7001022–7001026` (fase 1): necesita recompilar el módulo (Shield Mastery añade C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Shield Mastery `7001022`: pasiva; el aura 234 reduce un 51 % la duración del desarme nativo (mecánico 3) y el sondeo de 2 s (aura 226) concede o retira el bono de daño físico 900055 (aura 79 de escuela física, +9 %) según se empuñe un escudo. Diferencia conocida: SoD cita el hechizo 426981 para el bono, que no se pudo obtener, así que se implementa con el auxiliar de servidor 900055 con el valor 9 del catálogo. La retirada del bono puede tardar hasta 2 s.
- [ ] Taste for Blood `7001023`: pasiva con aura 42 que dispara 426969 al infligir Desgarrar daño; la fila `spell_proc` se copia de -56636 (familia 4, máscara de Desgarrar 0x20, enfriamiento 5800 ms) y la probabilidad del 100 % va en `ProcChance`. La marca 426969 clona el beneficio de WotLK 60503 (aura 262 sobre Abrumar); su duración (9 s) es la de WotLK, no verificada contra SoD. Sin C++.
- [ ] Vigilance `7001024`: clon de WotLK 50720 con el script del core `spell_warr_vigilance`, que aplica la reducción de daño, redirige el 10 % de la amenaza (59665) y reinicia Provocar al ser golpeado el objetivo. **No se reproducen** los efectos del catálogo (aura 42 con disparo 18350 —inexistente en 3.3.5a—, aura 226 y aura 87): el comportamiento del clon de WotLK coincide con la ficha (3 % de reducción, 10 % de amenaza, reinicio de Provocar, 30 min, un solo objetivo). Sin C++ propio.
- [ ] Rampage `7001025`: activa (30 s, 90 s de enfriamiento) con aura 166 (+15 % de poder de ataque) construida sobre 774. El requisito «solo mientras estás enfurecido» se impone con `CasterAuraState` 17 (estado Enrage), que aplican Enfurecer (12880), Ira rabiosa (18499) e Ira sangrienta (29131) por su `DispelType` 9. Sin C++.
- [ ] Sword and Board `7001026`: pasiva con aura 42 que dispara 426979 al infligir daño Devastar (palabra B 0x40) o Revancha (palabra A 0x400); la fila `spell_proc` se copia de -46951 y la probabilidad del 30 % va en `ProcChance`. Reutiliza el script del core `spell_warr_sword_and_board` (reinicia el enfriamiento de Embate con escudo) y la marca 426979 clona el beneficio de WotLK 50227 (−100 % de coste). El segundo efecto del talento de WotLK (aura 107, SpellModOp 7 sobre Devastar) **se omite** para reproducir el único efecto del catálogo. Sin C++ propio.
- [ ] Sexta tanda `7001027–7001030` (fase 1): necesita recompilar el módulo (Wrecking Crew, Fresh Meat y Shockwave añaden C++), además de regenerar el SQL de hechizos y el parche de cliente. Adquisición provisional por el Grabador (1 oro). Sin compilar ni probar.
- [ ] Wrecking Crew `7001027`: pasiva con aura 42 que dispara el beneficio 427066 al asestar un crítico cuerpo a cuerpo; la fila `spell_proc` limita el proc con `HitMask` 2 (crítico) sobre ataques automáticos y facultades físicas (`PROC_MELEE_HITS`), probabilidad 100 %. El beneficio 427066 (12 s) aplica +10 % al daño de Golpe mortal (palabra A 0x2000000), Sed de sangre (palabra B 0x400) y Embate con escudo (palabra B 0x200) con el aura 108 y SpellModOp 0 (daño total), y `spell_sod_warrior_wrecking_crew` aplica Enfurecer nativo (12880) al concederse. **Diferencia conocida**: el Enfurecer es el nativo de WotLK (12880, 12 s), que añade su propio bono de daño (+2 %) además del de la ficha; no se reproduce un «DispelType» de enfurecimiento propio. El icono `spell_shadow_unholyfrenzy` y el +10 %/12 s se tomaron de Wowhead (hechizo 427066, consultado el 2026-10-10).
- [ ] Fresh Meat `7001028`: pasiva con dos auras dummy (el segundo efecto del catálogo no se usa); el proc de la fila `spell_proc` filtra por familia 4 y las máscaras de Golpe mortal (A 0x2000000), Sed de sangre (B 0x400) y Embate con escudo (B 0x200) al infligir daño (`ProcFlags` 0x10), con probabilidad 100 %. `spell_sod_warrior_fresh_meat` aplica Enfurecer nativo (12880) y el beneficio 440483 (+10 % de daño físico, aura 79 de escuela física, 12 s). **Diferencia conocida**: la ficha da un 100 % la primera vez y un 10 % después; aquí «la primera vez» es el primer proc tras equipar la runa (el catálogo no da un identificador de objetivo para distinguirlo). El Enfurecer es el nativo 12880. El +10 %/12 s se tomaron de Wowhead (hechizo 440483, consultado el 2026-10-10).
- [ ] Shockwave `7001029`: activa (15 de ira, 20 s de enfriamiento de categoría) que clona el talento de WotLK 46968 (cono frontal de 10 m, aturde 4 s, `inherit_server`). El catálogo da el daño como el 50 % del poder de ataque, pero el core solo aplica ese coeficiente al id 46968 exacto (`Spell::EffectSchoolDMG`), así que `spell_sod_warrior_shockwave` lo añade sobre el efecto de daño; el dummy 3 se ajusta a 49 (50 en la ficha) y queda solo para el cliente. **No se parchea el core**: el dato del catálogo y la coincidencia con la plantilla WotLK están verificados contra `core/src/server/game/Spells/SpellEffects.cpp`. Conserva el requisito de actitud defensiva del talento WotLK.
- [ ] Sudden Death `7001030`: pasiva con familia genérica (0, como el talento de WotLK 29725) con aura 42 que dispara 440114 al golpear cuerpo a cuerpo (`ProcFlags` `PROC_MELEE_HITS`, probabilidad 10 % en `ProcChance` y en `spell_proc`); el efecto 1 es un dummy con puntos base 9 y `DieSides` 1 para que el script de Ejecutar del core (`spell_warr_execute`, que busca aura 42 + familia genérica + icono 1989) lea `CalcValue` 10 y retenga 10 de ira (× 10 = 100). El beneficio 440114 clona WotLK 52437 (aura 262 sobre la máscara de Ejecutar 0x20000000) con 10 s de duración, tomados de Wowhead (hechizo 440114, consultado el 2026-10-10). Sin C++ propio.

## Otras clases

(Vacío por ahora; se añadirá cuando se investiguen fuentes de otras clases con el mismo problema.)
