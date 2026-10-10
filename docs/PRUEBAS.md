# Qué hacer ahora

El objetivo es que Marc pueda compilar, instalar el parche y el addon, arrancar el reino de desarrollo y probar las runas pendientes. El reino de desarrollo es el reino 2. El orquestador no arranca el servidor ni aplica SQL. Estado del documento: 2026-10-09.

1. **Compilar** los cambios C++ indicados en «Qué hay que recompilar y qué no»: `cd ~/Repos/acore-test/build && nice -n 19 make -j3 2>&1 | tee ~/sod-build.log && make install`. Si falla, pásame las primeras líneas con `error:`.
2. **Copiar el parche y el addon.** Desde el servidor, copia `patch-z.mpq`, `esES/patch-esES-z.mpq` y la carpeta `RuneEngraver/` (addon propio y traducido) desde `datos/parche-cliente/20261006-final/`. Cliente 3.3.5a build 12340 en español (`esES`): `patch-z.mpq` va a `<cliente>/Data/`, `esES/patch-esES-z.mpq` a `<cliente>/Data/esES/` y `RuneEngraver` a `<cliente>/Interface/AddOns/RuneEngraver`. Descarga el cliente no incluye ni el addon ni el parche; son aparte. Borra `<cliente>/Cache/WDB` y deja `Data/esES/realmlist.wtf` con `set realmlist logon.warcrafted.com`. Si tu cliente 3.3.5 ya tiene parches de otro reino, usa una copia: no mezcles parches. Para transferir los archivos, usa `scp`/SFTP desde `/home/stark/Repos/acore-sod/datos/parche-cliente/20261006-final/`.
3. **Preparar y arrancar.** `make install` solo deja los `.dist`; crea los `.conf` de ambos módulos (sin ellos el log se llena de «Missing property SodMage.Enable», inofensivo porque el valor por defecto es 1): `cd ~/Servers/acore-test/etc/modules && cp mod_sod_content.conf.dist mod_sod_content.conf && cp mod_rune_engraving.conf.dist mod_rune_engraving.conf`. Arranca `worldserver` de `Servers/acore-test`. Al arrancar aplica solo el SQL de los módulos, por orden de nombre: `rune_engraving_schema.sql` antes que `sod_*`.
4. **Comprobar el arranque.** Busca en el log `RuneEngraving: loaded N rune(s) into the catalog`. El recuento estático de filas `rune_template` en los SQL del repositorio es **N = 75**; todavía no se ha verificado en el arranque, así que apunta el N real. Si falla el SQL o N es 0, pásame las líneas del log con `error` o `RuneEngraving`.
5. **Entrar y probar.** Usa una cuenta del `authserver` (`account create`), crea un personaje de la clase que vas a probar, súbelo con GM (`.character level <n>`) y entra por el reino **Desarrollo**. Sigue las casillas de pendientes de abajo. Con el personaje conectado y el addon activo, `.rune summon` crea al grabador (mujer humana, «Rune Engraver») en tus mismos pies, por unos minutos; puede quedar tapada por el personaje o la cámara. Aleja la cámara, usa `/targetfriend` o `/target Rune Engraver` y haz clic derecho: aparece un menú con las ranuras (Pecho, Manos, Piernas) y las runas que puedes grabar. `.rune slots` muestra cada ranura abierta o bloqueada (Pecho 4, Manos 6, Piernas 8). Graba con `.rune engrave <ranura> <rune_id>`; consulta `.rune list`. Comprueba que el hechizo aparece en el libro con icono y texto en español, se puede lanzar, hace daño o cura, y su coste y enfriamiento son razonables. Anota qué runa falla, qué esperabas y qué ocurrió.

## Pendiente de probar

Todas estas comprobaciones siguen pendientes salvo las confirmaciones fechadas en «Hecho». Cada casilla conserva las sospechas, diferencias y observaciones conocidas; las runas nuevas de Balance/Restauración se incluyen como **sin compilar ni probar**. Números entre paréntesis son índices de ranura para `.rune engrave`.


### Motor y Grabador

- [ ] Prueba de requisitos: el motor ofrece `.rune progress`, `.rune complete <objeto>` y `.rune resetprogress <objeto>`. Con `RuneEngraving.Requirements.Enable = 0` se saltan los requisitos. Comprobar si funcionan en juego.
- [ ] Los requisitos de uso de SoD de los ídolos (por ejemplo, «20 sangrados a humanoides») están solo como texto y no se comprueban.
- [ ] Comprobar compra de objetos-runa desde `.rune summon` > «Comprar runas» a 1 oro; sustituye a los Rune Brokers de SoD. Ya no basta con `.rune engrave`: hay que comprar el objeto y usarlo para desbloquear la runa. `.rune unlock <rune_id>` permite saltarse la compra.

### Mago

- [ ] Fingers of Frost — `rune_id 7000009`, Pecho (4). Sospecha: el chill de Blizzard no activa Fingers of Frost.
- [ ] Burnout — `rune_id 7000010`, Pecho (4). Tiene script propio sin probar.
- [ ] Icy Veins — `rune_id 7000011`, Piernas (8). Con la Icy Veins real (talento) el mago tendrá dos copias del hechizo.
- [ ] Ice Lance — `rune_id 7000012`, Manos (6). Tiene script propio sin probar; hace x3 contra congelados (core) y no x5 como SoD. Debe hacer unos 221-255 de daño a nivel 80 y bastante menos a nivel bajo (a nivel 6, de 12 a 50 de media).
- [ ] Probar si el chill de Blizzard activa Fingers of Frost y si las dos copias reales/de runa de Icy Veins e Ice Lance se comportan correctamente.
- [ ] Comprobar las diferencias conocidas: sin Winter's Chill; Fingers of Frost no se activa con el chill de Blizzard; Ice Lance multiplica x3 contra congelados y no x5.

### Otras clases de fase 1

- [ ] Guerrero — Devastate `7001001`, Manos (6).
- [ ] Paladín — Divine Storm `7002001`, Pecho (4); Avenger's Shield `7002002`, Piernas (8); Aura Mastery `7002003`, Piernas (8); Crusader Strike `7002004`, Manos (6). Comprobar que Divine Storm funciona sin el talento; Avenger's Shield también está pendiente de comprobar su daño.
- [ ] Cazador — Chimera Shot `7003001`, Manos (6); Master Marksman `7003002`, Pecho (4); Explosive Shot `7003003`, Manos. Explosive Shot requiere solo SQL y parche, no recompilar.
- [ ] Pícaro — Mutilate `7004001`, Manos (6). Comprobar que funciona sin el talento.
- [ ] Sacerdote — Circle of Healing `7005001`, Manos (6); Penance `7005002`, Manos (6). Sospecha: Penance no tiene script del core y puede quedarse sin parte del efecto.
- [ ] Chamán — Earth Shield `7007001`, Piernas (8); Lava Lash `7007002`, Manos (6).
- [ ] Brujo — Chaos Bolt `7008001`, Manos (6); Haunt `7008002`, Manos (6); Demonic Tactics `7008003`, Pecho (4). Comprobar que Haunt funciona sin el talento y el daño de Chaos Bolt.
- [ ] Probar las pasivas Demonic Tactics `7008003`, Master Marksman `7003002` y Survival of the Fittest `7009002`.
- [ ] Comprobar el daño de Avenger's Shield, Circle of Healing y Wild Growth creciendo con el nivel (a 80 coinciden con WotLK).
- [ ] Comprobar nombres de NPC y misiones del mundo de SoD en español.

### Brujo (runas nuevas; sin compilar ni probar)

- [ ] Unstable Affliction `7008004`, Muñecas (5): comprobar daño periódico durante 18 s, coste del 15 % y que disiparla daña y silencia al disipador. El límite de una Unstable Affliction o Immolate por brujo y objetivo puede diferir del comportamiento de SoD.
- [ ] Summon Felguard `7008005`, Muñecas (5): comprobar coste del 80 %, invocación, control y beneficios de talentos/efectos de demonios.
- [ ] Metamorphosis `7008006`, Manos (6): comprobar forma de demonio, armadura, salud, amenaza, críticos recibidos, Life Tap y las habilidades alteradas. El clon reutiliza Demon Form de WotLK y no implementa las facultades nuevas Shadow Cleave, Menace ni Demon Charge.
- [ ] Incinerate `7008007`, Muñecas (5): comprobar daño, coste del 14 %, duración de 15 s y aumento del 40 % al daño de Fuego.
- [ ] Shadowflame `7008008`, Pies (9): comprobar el impacto de Shadowflame, su daño periódico y coste del 27 %.
- [ ] Comprobar nombres e iconos en español y que el Grabador venda las cinco runas por 1 oro. La fuente de adquisición de SoD no está verificada.
- [ ] Backdraft `7008009`, Cabeza (0): comprobar que Conflagrar otorga un 30 % de celeridad con hechizos durante 15 s. Diferencia conocida: Conflagrar sigue consumiendo Inmolar; quitar ese consumo exige tocar el core (ver `TODO.md`).
- [ ] Decimation `7008010`, Pies (9): comprobar que Fuego de alma ya no tiene enfriamiento y que, al golpear con Descarga de las Sombras, Incinerar o Fuego de alma a un objetivo al 35 % de salud o menos, el tiempo de lanzamiento de Fuego de alma se reduce un 40 % durante 10 s y ese lanzamiento no cuesta fragmento. Cuchilla de las Sombras no existe en 3.3.5a.
- [ ] Demonic Pact `7008011`, Piernas (8): comprobar el +10 % de daño de Fuego y Sombras y que los críticos de la mascota aplican el efecto de grupo o banda. Reutiliza el script nativo de WotLK sobre el aura de mascota 54909.
- [ ] Everlasting Affliction `7008012`, Piernas (8): comprobar que Drenar vida, Drenar alma, Descarga de las Sombras, Incinerar y Poseer devuelven Corrupción a su duración máxima. Diferencia: SoD incluye además Cuchilla de las Sombras y Dolor abrasador, que no existen en 3.3.5a.
- [ ] Demonic Knowledge `7008013`, Pies (9): comprobar que el daño y la sanación con hechizos suben un 3 % del aguante más intelecto totales de la mascota demoníaca. Diferencia: usa el aura de mascota 900048 al 3 % en vez de la nativa 35696 (12 %).
- [ ] Comprobar nombres e iconos en español de estas cinco runas y que el Grabador las venda por 1 oro. La fuente de adquisición de SoD no está verificada.
- [ ] Soul Siphon `7008014`, Espalda (3): comprobar que Drenar alma inflige daño 3 veces más rápido (tick de 1 s) y que drena un 6 % más por cada efecto de las Sombras tuyo en el objetivo, hasta un máximo del 18 %. Diferencia conocida: el ramal de SoD «por debajo del 20 % de salud» (50 % por efecto hasta 150 %) no se implementa (ver `TODO.md`). Con el talento Ocaso aprendido, comprobar que Drenar alma puede aplicarte Trance de las Sombras.
- [ ] Shadow and Flame `7008015`, Cintura (7): provocar críticos con hechizos de Fuego y de las Sombras y comprobar que el daño de ambas escuelas sube un 10 % durante 10 s. Diferencia conocida: la fila `spell_proc` proca con cualquier hechizo de brujo, no solo de Fuego/Sombras, porque 3.3.5a no ofrece ese par de escuelas exacto (ver `TODO.md`).
- [ ] Lake of Fire `7008016`, Pecho (4): comprobar que Lluvia de fuego gana 8 s de tiempo de reutilización. Diferencia conocida: sigue canalizándose; quitar el canal exige cambiar el DBC del hechizo base y no se puede desde un módulo (ver `TODO.md`).
- [ ] Master Channeler `7008017`, Pecho (4): comprobar que Drenar vida cuesta un 100 % más de maná y que te sana un 50 % más por tick. Diferencia conocida: sigue canalizándose y no cambia su duración ni su reutilización (ver `TODO.md`).
- [ ] Shadow Bolt Volley `7008018`, Manos (6): comprobar que Descarga de las Sombras golpea hasta 5 objetivos en cadena dentro de 10 m con un 30 % menos de daño. Verificar que el SpellMod de objetivos en cadena surte efecto sobre un hechizo que en WotLK no es encadenado.
- [ ] Estas cinco runas nuevas sí necesitan recompilar el módulo: Soul Siphon y Master Channeler añaden scripts C++ propios (`spell_sod_warlock_soul_siphon`, `spell_sod_warlock_master_channeler`).
- [ ] Demonic Grace `7008019`, Piernas (8): comprobar +20 % de esquiva al brujo y a su mascota y +20 % de crítico con todos los ataques durante 6 s, con 20 s de reutilización. La esquiva de la mascota solo se aplica si está invocada al lanzar.
- [ ] Invocation `7008020`, Cintura (7): aplicar o refrescar Corrupción, Inmolar, Maldición de agonía, Aflicción inestable, Llama de las Sombras o Succionar vida debe infligir al instante un pulso del daño periódico. Diferencia conocida: la rama «refrescar con menos de 6 s inflige el daño periódico restante» se simplifica a un pulso (ver `TODO.md`); Succionar vida usa el id 35195 de WotLK, cuya cadena de rangos no se pudo verificar.
- [ ] Dance of the Wicked `7008021`, Pies (9): al asestar un crítico, comprobar que el brujo y su mascota ganan esquiva igual al 70 % de la probabilidad de crítico con hechizos. Diferencia conocida: la recuperación de maná de SoD no está implementada (su porcentaje no consta en el catálogo) y la duración del beneficio es provisional (10 s); ver `TODO.md`.
- [ ] Vengeance `7008022`, Cabeza (0): activar y comprobar +30 % de salud máxima durante 20 s, con 180 s de reutilización y que la salud se pierde al expirar. Diferencia conocida: el catálogo pide el aura 34, pero en 3.3.5a se usa el aura 133 (porcentaje); no se implementa la caída lenta en Metamorfosis.
- [ ] Immolation Aura `7008023`, Muñecas (5): comprobar que al recibir un ataque cuerpo a cuerpo quema a los enemigos cercanos (como mucho una vez por segundo), reduce un 10 % el daño mágico recibido y aumenta un 10 % el daño de Fuego infligido. Reutiliza el daño de Aura de Inmolación de WotLK.
- [ ] Estas cinco runas (fase 4) también necesitan recompilar el módulo: Invocation y Dance of the Wicked añaden scripts C++ propios (`spell_sod_warlock_invocation`, `spell_sod_warlock_dance_of_the_wicked`).
- [ ] Infernal Armor `7008024`, Espalda (3): activar (3 % de maná, 10 s de duración, 60 s de reutilización) y comprobar que recibes menos daño mágico. Simplificación conocida: la reducción es el 60 % de la reducción de daño físico por armadura del brujo, calculada con la fórmula de armadura del core (el importe de la ficha de SoD era un ejemplo a nivel 60). El texto de la ficha usa $s2 (el 60 %). Ver `TODO.md`.
- [ ] Mark of Chaos `7008025`, Espalda (3): lanzar maldiciones de brujo y comprobar que el objetivo recibe Marca de caos (−27 a las resistencias Arcano, Fuego, Escarcha, Naturaleza y Sombras y +4 % de daño con hechizos de esas escuelas durante 2 min). Diferencia conocida: SoD escala ambos valores con el nivel; aquí van fijos en el mínimo del catálogo. Comprobar que Maldición de las Sombras y Maldición de los Elementos quedan excluidas.
- [ ] Pandemic `7008026`, Cabeza (0): con la runa activa, comprobar que el daño periódico de Corrupción, Aflicción inestable, Maldición de agonía, Inmolar, Maldición del Apocalipsis y Succionar vida puede dar golpes críticos. Diferencia conocida: se usa el aura nativa 286 de crítico periódico del core; se omite el segundo efecto del catálogo porque el SpellModOp 15 de 3.3.5a es el bono de daño crítico, no el crítico periódico (ver `TODO.md`).
- [ ] Grimoire of Synergy `7008027`, Cintura (7): comprobar que al infligir daño el brujo o su demonio, con un 10 % de probabilidad, el otro gana +10 % de daño durante 15 s. La parte del demonio llega por un aura auxiliar de servidor 900051 que el familiar recibe al invocarse, así que hay que invocarlo después de grabar la runa. Ver `TODO.md`.
- [ ] Estas cuatro runas (fase 5) necesitan recompilar el módulo: Infernal Armor y Grimoire of Synergy añaden scripts C++ propios (`spell_sod_warlock_infernal_armor`, `spell_sod_warlock_grimoire_of_synergy`).

### Chamán (runas nuevas; sin compilar ni probar)

- [ ] Lava Burst `7007003`, Manos (6): comprobar el lanzamiento de 2 s, el crítico garantizado sobre un objetivo con Choque de llamas, el daño, el coste del 10 % y la reutilización de 8 s.
- [ ] Riptide `7007004`, Muñecas (5): comprobar la sanación directa y periódica durante 15 s, el coste del 18 %, la reutilización de 6 s, la mejora a Sanación en cadena y la interacción con Despertar ancestral.
- [ ] Feral Spirit `7007005`, Espalda (3): comprobar el coste del 12 %, que aparecen dos lobos, duran 45 s y obedecen al chamán; reutilización de 180 s.
- [ ] Maelstrom Weapon `7007006`, Cintura (7): comprobar las acumulaciones por daño cuerpo a cuerpo y que reducen lanzamiento y coste de Descarga de relámpagos, Cadena de relámpagos, Ola de sanación inferior y Ráfaga de lava. Comprobar también las bonificaciones de probabilidad con Viento furioso y arma a dos manos.
- [ ] Tidal Waves `7007007`, Cabeza (0): lanzar Sanación en cadena y Mareas vivas; comprobar que se obtienen dos cargas y sus efectos en Ola de sanación, Sanación en cadena y Ola de sanación inferior.
- [ ] Ancestral Awakening `7007008`, Pies (9): provocar críticos con Ola de sanación y Ola de sanación inferior y comprobar que el miembro del grupo con menor porcentaje de salud, dentro de 40 m, recibe el 30 % de la sanación.
- [ ] Confirmar que los seis iconos y nombres aparecen correctamente en español y que la compra provisional al Grabador desbloquea cada runa.
- [ ] Dual Wield Specialization `7007009`, Pecho (4): comprobar que se aprende Doble empuñadura, el aumento de golpe, el 60 % de daño adicional de la mano izquierda y que Golpe de tormenta genera también un ataque de mano izquierda. Comprobar si el aumento de golpe se aplica sin arma secundaria.
- [ ] Overload `7007010`, Pecho (4): probar Descarga de relámpagos, Cadena de relámpagos, Sanación en cadena, Ola de sanación y Ráfaga de lava; cada una debe repetir aproximadamente un 60 % de las veces con la mitad del resultado, sin coste adicional, amenaza ni procs recursivos.
- [ ] Shield Mastery `7007011`, Pecho (4): bloquear con escudo y comprobar el 8 % de maná, el 30 % de la armadura del escudo por acumulación (máximo 5, 15 s), el 10 % de probabilidad de bloqueo y el 15 % de valor de bloqueo. Lanzar Choque de tierra y Choque de llamas con Defensa por encima de 5 × nivel y comprobar el poder con hechizos durante 15 s.
- [ ] Two-Handed Mastery `7007012`, Pecho (4): golpear con arma a dos manos y comprobar durante 10 s el 45 % de velocidad, el 10 % de poder de ataque y el 10 % de golpe con hechizos. El aura genérica de velocidad también afecta a ambas manos hasta que un golpe con arma de una mano la elimina.
- [ ] Healing Rain `7007013`, Pecho (4): comprobar lanzamiento de 2 s, coste del 21 % de maná base, reutilización de 10 s, duración de 10 s y sanación cada segundo en un radio de 15 m alrededor del objetivo; no debe sanar más de cinco miembros del grupo.
- [ ] Ancestral Guidance `7007014`, Piernas (8): durante 10 s, comprobar que el 25 % del daño sana hasta a tres miembros del grupo en 40 yd y que el 100 % de la sanación efectiva se convierte en daño sobre el último objetivo de Choque de llamas. Revisar daño periódico, golpes automáticos, sanaciones y que las conversiones no se encadenen. El radio de 40 yd se contrastó con [Ancestral Guidance](https://www.wowhead.com/classic/spell=409337) el 2026-10-09.
- [ ] Greater Ghost Wolf `7007015`, Piernas (8): comprobar la reducción del 10 % mientras Lobo fantasmal está activo y el comportamiento dentro de edificios. La reducción del 10 % se contrastó con [Ghost Wolf](https://www.wowhead.com/classic/spell=415233) el 2026-10-09; el uso en interiores sigue limitado por el atributo del hechizo del core.
- [ ] Way of Earth `7007016`, Piernas (8): con Muerdepiedras en la mano principal y un escudo, comprobar +65 % de amenaza, +25 % de salud máxima, −10 % de daño recibido y −6 % de probabilidad de recibir críticos cuerpo a cuerpo. Comprobar que los cinco hechizos indicados pierden 20 yd de alcance y que Choque de tierra provoca, tiene alcance cuerpo a cuerpo y conserva una reutilización independiente de los demás choques. Valores contrastados con [el hechizo auxiliar Way of Earth](https://www.wowhead.com/classic/spell=408680) y [la descripción de la runa](https://www.wowhead.com/classic/spell=409955) el 2026-10-09.
- [ ] Molten Blast `7007017`, Manos (6): comprobar el cono de daño de Fuego, el límite de 10 objetivos, el coste del 18 % de maná, los 6 s de reutilización y el 10 % de probabilidad de reinicio con el daño periódico de Choque de llamas. El daño usa Cone of Cold (120) como plantilla. La amenaza alta descrita por SoD aún no está implementada: la página consultada no publica su multiplicador. Los datos se contrastaron con [Molten Blast](https://www.wowhead.com/classic/spell=425339) el 2026-10-09.
- [ ] Power Surge `7007018`, Cintura (7): comprobar la probabilidad del 5 % en ticks de Choque de llamas y sanación de Mareas vivas, los reinicios de Ráfaga de lava y Cadena de relámpagos, los lanzamientos instantáneos y el maná periódico equivalente al 2 % del intelecto. Las duraciones auxiliares no se han podido verificar en el catálogo.
- [ ] Decoy Totem `7007019`, Pies (9): comprobar el tótem de 4 p. de salud durante 10 s, la protección frente al siguiente golpe físico y la inmunidad a raíces y ralentizaciones. Simplificación: el golpe queda absorbido por la protección y no se redirige como ataque real al tótem. La inmunidad dura provisionalmente 10 s, igual que el tótem, porque no se pudo verificar la duración de `436391d`.
- [ ] Spirit of the Alpha `7007020`, Pies (9): comprobar el aumento de amenaza del 45 % durante 30 min y que solo afecta a un objetivo a la vez. Beta leal no está implementada: sus porcentajes no constan en el catálogo local.
- [ ] Burn `7007021`, Cabeza (0): con la runa activa, comprobar que Choque de llamas dura 6 s más e inflige el doble de daño directo y periódico, y que Arma Lengua de Fuego en la mano principal concede daño con hechizos igual al 150 % del intelecto. La propagación a cinco objetivos no está implementada.
- [ ] Mental Dexterity `7007022`, Cabeza (0): al infligir daño con Golpe de tormenta, comprobar el poder de ataque equivalente al 150 % del intelecto y el daño con hechizos equivalente al 35 % del poder de ataque total. La duración auxiliar está fijada provisionalmente en 15 s; el valor de `415144d` no consta en el catálogo local.
- [ ] Overcharged `7007023`, Muñecas (5): comprobar que Escudo de relámpagos conserva hasta 9 cargas, se activa como máximo cada 3 s e inflige daño a enemigos adicionales en 8 yardas. El atacante principal ya recibe el proc nativo de WotLK; comprobar que no recibe daño duplicado.
- [ ] Rolling Thunder `7007024`, Muñecas (5): lanzar Descarga de relámpagos y Cadena de relámpagos para comprobar la probabilidad del 50 % de sumar una carga hasta 9. Con más de 3 cargas, lanzar Choque de tierra y comprobar el daño por carga liberada y la restauración del 2 % del maná máximo por carga.
- [ ] Static Shock `7007025`, Muñecas (5): comprobar las 9 cargas de Escudo de relámpagos, la probabilidad del 12 % con una mano secundaria vacía y del 6 % con dos armas, el daño al objetivo y el consumo de una carga. Con Overcharged activo, comprobar que las cargas no se consumen.
- [ ] Coherence `7007026`, Espalda (11): comprobar la efectividad por salto del 65 % para Sanación en cadena y del 80 % para Cadena de relámpagos, más un objetivo en ambos hechizos. Los porcentajes se implementan mediante los SpellModOp de WotLK y deben contrastarse en juego.
- [ ] Storm, Earth, and Fire `7007027`, Espalda (11): comprobar −25 % al tiempo de reutilización de Cadena de relámpagos, el enraizamiento de 5 s del Tótem Nexo Terrestre al aplicarse el aura del tótem y +60 % al daño periódico de Choque de llamas.
- [ ] Confirmar los textos esES, los iconos y que la compra provisional al Grabador desbloquea las cinco runas `7007023–7007027`.
- [ ] Adquisición del chamán: comprar y usar los 26 objetos de runa en el Grabador; comprobar que Bristleback Shaman (2953) y Scorpid Worker (3124) pueden soltar Dyadic Icon, Mudsnout Shaman (2373) Kajaric Icon y Deadwood Shaman (7158) Voltaic Icon, y que los botines solo aparecen para chamanes.

### Paladín (recuperadas el 2026-10-09, sin compilar ni probar)

- [ ] Adquisición: comprobar que el Grabador vende los 27 objetos de runa del paladín por 1 oro y que caen Libram of Banishment (211472) de Defias Night Runner/Defias Night Blade/Defias Enchanter, Libram of Judgement (205420) de Defias Thug/Frostmane Troll Whelp y Libram of Justice (208851) de Leprithus/Ghoul/Defias Drone.

- [ ] The Art of War `7002005`, Pies (9): los críticos cuerpo a cuerpo abaratan Exorcismo un 80 % y le quitan 2 s de enfriamiento.
- [ ] Righteous Vengeance `7002006`, Espalda (3): los críticos añaden un 30 % como daño periódico durante 8 s.
- [ ] Improved Hammer of Wrath `7002007`, Muñecas (5): Martillo de cólera reinicia su enfriamiento si el objetivo queda por debajo del 10 % de vida.
- [ ] Purifying Power `7002008`, Muñecas (5): Exorcismo y Cólera sagrada con un 50 % menos de enfriamiento; aturden 2 s a no-muertos y demonios.
- [ ] Fanaticism `7002009`, Cabeza (0): +18 % de crítico en hechizos Sagrados; las curaciones críticas repiten un 60 % en 12 s.
- [ ] Wrath `7002010`, Cabeza (0).
- [ ] Infusion of Light `7002011`, Cintura (7): Choque Sagrado (talento) hace un 50 % más de daño y curación; un crítico devuelve su coste de maná y le quita 3 s de enfriamiento.
- [ ] Light's Grace `7002012`, Muñecas (5): tras una Luz Sagrada, la siguiente tarda 0,5 s menos (15 s).
- [ ] Improved Sanctuary `7002013`, Cabeza (0): **se sabe que hoy no tiene efecto** (ver `TODO.md`); solo comprobar que se graba sin errores.
- [ ] Aegis `7002014`, Pecho (4): +30 % de valor de bloqueo; con el talento Baluarte, 10 % de probabilidad de activarlo al recibir golpes y siempre al hacer un crítico cuerpo a cuerpo; con Expiación, un 2 % por punto.
- [ ] Sheath of Light `7002015`, Cintura (7): un impacto cuerpo a cuerpo da daño con hechizos igual al 30 % del poder de ataque durante 1 min; comprobar que el efecto se renueva.
- [ ] Guarded by the Light `7002016`, Pies (9): los impactos cuerpo a cuerpo renuevan 15 s; comprobar el 5 % de maná máximo cada 3 s y la reducción de sanación del 50 %.
- [ ] Shock and Awe `7002017`, Espalda (3): sin Furia justa, el daño de Choque Sagrado da daño con hechizos igual al 200 % del intelecto y reduce la amenaza un 30 % durante 1 min. Si Infusion of Light está grabada, Sunlight aún no está implementada (ver `TODO.md`).
- [ ] Hallowed Ground `7002018`, Pecho (4): Consagración sana a los miembros del grupo dentro de su área por el 200 % del daño de cada pulso; comprobar objetivos múltiples y miembros fuera del área.
- [ ] Beacon of Light `7002019`, Manos (6): marca a un aliado (60 min, uno solo a la vez); tus curaciones a otros miembros del grupo le curan un 75 %.
- [ ] Hammer of the Righteous `7002020`, Muñecas (5): golpea al objetivo y a 2 cercanos con daño Sagrado; 6 s de enfriamiento, coste 6 %.
- [ ] Shield of Righteousness `7002021`, Espalda (3): daño Sagrado según el valor de bloqueo + 179; 6 s de enfriamiento.
- [ ] Divine Light `7002022`, Espalda (3): curación grande (61 % de maná base, 8 s de enfriamiento); el 50 % de la sobrecuración queda como escudo de absorción 15 s; comprobar que se beneficia de talentos de Luz Sagrada.
- [ ] Rebuke `7002023`, Piernas (8): interrumpe y bloquea la escuela 3 s, cuerpo a cuerpo, 15 s de enfriamiento, coste 10 % de maná (no energía).
- [ ] Sacred Shield `7002024`, Pies (9): sobre un aliado 60 s; al recibir daño gana un escudo (como mucho cada 5 s) y Destello de Luz le cura un 100 % extra en 12 s. Diferencia: no se limita a un solo objetivo.
- [ ] Inspiration Exemplar `7002025`, Piernas (8): durante 120 s quita miedo y sueño a los miembros del grupo a 10 yd cada 4 s.
- [ ] Hand of Reckoning `7002026`, Manos (6): pasiva; con Furia recta, las curaciones de otros te devuelven un 25 % en maná y el golpe que te deja por debajo del 35 % se reduce un 20 %.
- [ ] Malleable Protection `7002027`, Cintura (7): Protección divina dura 18 s en vez de 12; Escudo Sagrado da poder de ataque por la defensa sobre 5 × nivel durante 15 s.

### Druida feral

- [ ] Wild Growth `7009001`, Manos (6); Survival of the Fittest `7009002`, Pecho (4). Wild Growth también está en las pruebas de crecimiento con nivel (a 80 coincide con WotLK).
- [ ] Lacerate `7009003`, Piernas (8): aparece en el libro con icono y texto, se lanza, y su daño periódico crece con el nivel. Diferencia conocida con SoD: sin el daño de arma por acumulación. Fuente nueva (solo SQL): matar worgen Moonrage en Silverpine (~1 % por muerte; con `.npc add 1770` o `.go creature` se puede probar rápido) debe soltar la Runa de Lacerar.
- [ ] Savage Roar `7009004`, Piernas (8).
- [ ] Berserk `7009005`, Cintura (7). Diferencias conocidas con SoD: sin multiobjetivo de Lacerate, sin quitar el miedo ni inmunidad.
- [ ] Survival Instincts `7009006`, Pies (9). Diferencias conocidas con SoD: sin regeneración al esquivar ni sanación no física.
- [ ] Mangle `7009007`, Manos (6): probar en gato y oso.
- [ ] Gore `7009008`, Cabeza (0).
- [ ] Wild Strikes `7009009`, Pecho (4): probar con un grupo en forma felina.
- [ ] King of the Jungle `7009010`, Pies (9).
- [ ] Skull Bash `7009011`, Manos (6): carga e interrupción a menos de 13 yd.
- [ ] Improved Frenzied Regeneration `7009012`, Muñecas (5).
- [ ] Improved Swipe `7009013`, Espalda (3): comprobar la muerte de objetivos dormidos en gato.
- [ ] Improved Barkskin `7009014`, ranura no indicada en el texto original: comprobar uso sobre aliados y en forma, sin ralentizar ataques ni lanzamiento.
- [ ] Los objetos-runa del druida ya existen con su id real de SoD y se consiguen como indica `docs/runas/obtencion.md`: botín con las tasas reales (bajas, del 0,2 al 2 %) de criaturas de WotLK, Grizzby y oficiales de suministros.
- [ ] Requisitos de uso de ídolos del druida: Wild Strikes (curar 10 bestias distintas), Savage Roar (20 sangrados a humanoides), Mangle (50 de ira en oso 60 s seguidos), Improved Barkskin (5 muertes con daño de Naturaleza bajo Piel de corteza) e Improved Swipe (5 muertes de dormidos en gato); con `RuneEngraving.Requirements.Enable = 0` se saltan.
- [ ] Fidelidad extra aún pendiente de verificar (sin inventar mecánica): King of the Jungle/Supply Bag, Survival Instincts/evento «Amaryllis», Improved Frenzied Regeneration. No se pudo confirmar la mecánica exacta porque Wowhead usa páginas dinámicas que WebFetch no renderiza (sin herramienta de navegador en esa sesión); es mejor documentarlo sin implementar que inventar. Gore tiene su fuente real documentada en `docs/runas/obtencion.md` (4 intendentes, verificados en wago.tools), aunque esos NPC todavía no existen en el mundo.
- [ ] Las diferencias con SoD de las siete runas de C++ nuevas están descritas en el informe de cada tarea (`agentrelay show`).

### Druida Balance/Restauración

Las runas siguientes se han cotejado con `sod_druid_runes.sql`; todas están **sin compilar ni probar**. El número entre paréntesis es el índice de ranura del SQL.

- [ ] Living Seed — `7009015`, Pecho (4).
- [ ] Gale Winds — `7009016`, Cabeza (0).
- [ ] Sunfire — `7009017`, Manos (6).
- [ ] Fury of Stormrage — `7009018`, Pecho (4).
- [ ] Dreamstate — `7009019`, Pies (9).
- [ ] Tree of Life — `7009020`, Espalda (3).
- [ ] Starsurge — `7009021`, Piernas (8).
- [ ] Efflorescence — `7009022`, Muñecas (5).
- [ ] Elune's Fires — `7009023`, Muñecas (5).
- [ ] Eclipse — `7009024`, Cintura (7).
- [ ] Starfall — `7009025`, Espalda (3).
- [ ] Lifebloom — `7009026`, Piernas (8); icono y texto, sanación periódica, sanación final y retorno de maná. Sin compilar ni probar.
- [ ] Nourish — `7009027`, Cintura (7); icono y texto, sanación y efectos de hechizos del core. Sin compilar ni probar.

## Qué hay que recompilar y qué no

**Sí requiere recompilar** todo el C++ nuevo desde la última compilación: traducciones, las 7 runas de C++ de druida (segunda tanda), Improved Barkskin, la compra de runas en el Grabador, el motor de requisitos de uso de los ídolos (`.rune progress`, `.rune complete <objeto>`, `.rune resetprogress <objeto>`), los requisitos de los ídolos del druida y los scripts del paladín (incluidas Sheath of Light, Guarded by the Light, Shock and Awe y Hallowed Ground). La sintaxis de los archivos pasa con clang; no se ha compilado ni enlazado nada. Si falla, pásame las líneas con `error:`.

Después de compilar y de regenerar `build_patch.py`, copia de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq` desde `datos/parche-cliente/20261006-final/` y reinicia el reino 2. Los MPQ traen los iconos de bolsa de los objetos nuevos. Las siete runas de la segunda tanda son Mangle 7009007 (Manos, 6), Gore 7009008 (Cabeza, 0), Wild Strikes 7009009 (Pecho, 4), King of the Jungle 7009010 (Pies, 9), Skull Bash 7009011 (Manos, 6), Improved Frenzied Regeneration 7009012 (Muñecas, 5) e Improved Swipe 7009013 (Espalda, 3). El interruptor es `SodDruid.Enable` en `mod_sod_content.conf`, que `make install` deja solo como `.dist`: si quieres cambiar valores copia las secciones nuevas al `.conf`.

El parche se regeneró sin «Rango N» en los clones; queda pendiente copiar de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`.

Las cinco runas nuevas del brujo (Backdraft 7008009, Decimation 7008010, Demonic Pact 7008011, Everlasting Affliction 7008012 y Demonic Knowledge 7008013) **no necesitan recompilar**: son solo SQL y parche. Reinicia el reino 2 para que se aplique el SQL regenerado y copia `patch-z.mpq` y `esES/patch-esES-z.mpq` desde `datos/parche-cliente/20261009-brujo/` (ese parche aún no está publicado).

La primera tanda feral (Lacerate 7009003, Savage Roar 7009004, Berserk 7009005 y Survival Instincts 7009006) requiere **solo SQL y parche, no recompilar**: copia de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`, y reinicia el reino. Wild Growth 7009001 y Survival of the Fittest 7009002 ya estaban. También requiere solo SQL y parche, sin recompilar, Explosive Shot `7003003` (Manos): copiar de nuevo ambos MPQ y reiniciar; lo mismo para comprobar el daño de Chaos Bolt, Haunt, Avenger's Shield, Circle of Healing y Wild Growth que crece con el nivel (a 80 coinciden con WotLK), y los nombres de NPC y misiones del mundo de SoD en español.

Al probar adquisición de runas, la compra en el Grabador es C++ nuevo y requiere recompilar. Los objetos se consiguen con botín y tasas del 0,2 al 2 % de criaturas WotLK, Grizzby y oficiales de suministros; la compra al Grabador (`.rune summon` > «Comprar runas») cuesta 1 oro y sustituye a los Rune Brokers de SoD. Pasos: recompilar, copiar los MPQ y reiniciar el reino. Para desbloquear la runa hay que comprar el objeto y usarlo; `.rune unlock <rune_id>` permite saltarse ese paso. Los requisitos de uso de SoD (p. ej. «20 sangrados a humanoides») están solo como texto y no se comprueban.

## Hecho (ya confirmado, no repetir)

Estas pruebas las confirmó Marc; no hay que repetirlas.

- **2026-10-06, tras compilar:** textos en español, addon y tooltip correctos. `.rune slots` dice «nivel 1» en Pecho, Manos y Piernas: es lo configurado (`RuneEngraving.SlotMinLevel.*` = 1, como la fase 1 de SoD), no depende de ser GM. Los números 4, 6 y 8 son los índices de ranura para `.rune engrave`.
- **2026-10-06:** el primer arranque del reino 2 falló por una comilla sin escapar en «Avenger's Shield» (`sod_content_spell_dbc.sql`, línea 102); corregido en el generador y el arranque posterior funcionó. El servidor arranca con 29 runas; `.rune summon` y el menú funcionan; Ice Lance se lanza y hace daño; el hechizo sale en la barra.
