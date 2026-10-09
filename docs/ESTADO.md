# Estado del proyecto

**Mantén este archivo al día con cada cambio relevante, no al final de la tarea.** Es lo primero que
lee una sesión nueva. Última actualización: **2026-10-09**.

## 0. Trabajo en curso y cómo reanudarlo (2026-10-07)

El servidor se reinicia a diario a las 4:00 (hora de España); `/tmp` es tmpfs y se vacía. **Todo lo que
importa vive en el repo.** Tras un reinicio: `tools/cola/reanudar.sh` (cola de tareas del ejecutor + recogida
de fuentes de Wowhead) y, en una sesión nueva, leer `docs/guias/reanudar-tras-reinicio.md` y
`python3 tools/cola/cola.py status`. Las tareas están en `.agents/cola/` (estado en `estado.json`). Las
revisiones y los commits siguen siendo del orquestador.

**Prioridad del usuario:** probar a fondo el **druida feral** antes de pasar a otra clase (regla estricta: no se
toca ninguna otra clase hasta que él confirme el feral al 100 %; por error se añadió código de paladín el
2026-10-07, ya retirado — ver commit `d85f936` y copia en `/tmp/paladin_hoy/`, fuera del repo). Después de
cerrar el feral: el usuario pide ir directamente a por **todo el contenido de las 8 fases de SoD** (build
1.15.9), no solo la fase 2. Quiere que la mecánica de las runas sea lo más parecida posible a SoD.

**Estado del feral (2026-10-07):** las 14 runas (13 + Improved Barkskin) tienen código, sin compilar
(sintaxis OK, `check_syntax.py`: 41 OK, 0 errores), con adquisición: objetos reales de SoD, botín de WotLK con
tasas reales para Mangle/Savage Roar/Wild Strikes/Improved Swipe, Grizzby, oficiales de suministros y compra
en el Grabador (sustituto documentado del Rune Broker real, decisión ya tomada: no hay coordenadas de mundo
fiables para los Rune Brokers). Hecho: requisitos de uso de los ídolos (motor genérico y los 5 del druida) e
Improved Barkskin. **El feral está completo para fase 1**: no queda ninguna tarea bloqueante, solo fidelidad
extra pendiente de verificar (Lacerate/Aggressive Squashling, King of the Jungle/Supply Bag, Survival
Instincts/evento «Amaryllis», Improved Frenzied Regeneration) — no se ha podido confirmar su mecánica exacta
porque Wowhead usa páginas dinámicas que `WebFetch` no renderiza (sin herramienta de navegador en esta sesión);
mejor documentado sin implementar que inventado. Gore sí tiene su fuente real documentada en
`docs/runas/obtencion.md` (4 intendentes, verificados en wago.tools), aunque esos NPC no existen todavía en
el mundo. **Falta compilar y probar en juego** (nunca se ha hecho con este código).
Lifebloom `7009026` y Nourish `7009027` ya tienen specs, SQL y venta en el Grabador; la fuente real de SoD no está verificada. Sin compilar ni probar.
**2026-10-09:** el fallo de compilación del druida del 2026-10-07 (`RegisterSpellScript` sin definir, `AuraEffect` incompleto) ya no se reproduce: todos los `.cpp` de `server/` pasan `clang++ -fsyntax-only` con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make` (salvo los tests de gtest, que no entran en el build). Falta que el usuario compile de verdad. El checkout desplegado (`acore-test/.subrepos/WotLK-SoD`) está en `d9d5a6b`: Lifebloom y Nourish (`05cf830`) no llegarán al build hasta hacer push y desplegar.
Las demás clases (paladín 2, chamán, brujo) están `descartadas` en la cola hasta terminar el feral (el paladín 1 se ejecutó
por error; su código existe y pasa la sintaxis). Handoff completo en la memoria del proyecto (`handoff.md`).

**Datos:** catálogo (`docs/runas/catalogo-sod.json`), fuentes de Wowhead (`docs/runas/fuentes-sod.json`, 253 de
256 runas con objeto; faltan Lava Lash, Nature's Fury y una runa de mago), clasificación P/T/C/R
(`docs/runas/plan-implementacion.*`), cómo se consigue cada runa (`docs/runas/obtencion.md`). El usuario compila
y prueba: ver `docs/PRUEBAS.md` para lo que debe hacer.

## 1. Dónde estamos

- **Fase:** primer hito (fase 1 de SoD, nivel 25 de partida, hacia 80). **2026-10-06: compilado por el
  usuario, reino 2 arrancado con 29 runas, grabador, textos en español, addon y tooltip comprobados en
  juego; Ice Lance probada. El resto de las 29 runas, sin probar.** Datos de SoD de la build 1.15.9
  (wago.tools); **se implementa la fase 1** (decisiones 0002 y 0004); las demás fases no son objetivo hoy.
- **Dónde se trabaja:** `/home/stark/Repos/acore-sod`, en el servidor Debian `warcrafted`
  (`192.168.1.150`, usuario `stark`). **Es una máquina de producción.**
- **Dónde se compila:** `/home/stark/Repos/acore-test`, **solo lo hace el usuario**. Es el reino de
  **desarrollo** (id 2, puerto 8086, bases `*_test`, instalación en `/home/stark/Servers/acore-test`).
- **Última acción del usuario (2026-10-05):** instalación nueva de `acore-test`. Ha hecho solo el
  **paso 1** de `docs/guias/compilar-en-linux.md` §7: **crear las 3 bases `*_test` vacías**
  (según él; **no lo he verificado**). **Quedan pendientes, y los hace él:** el paso 2 (`cmake`), el
  3 (`make`) y el 4 (`make install`). **No sabemos aún si compila.**
- **Build antiguo:** el usuario ya ha borrado `acore-test/build/` (confirmado por él el 2026-10-05),
  así que el paso 2 (`cmake`) partirá de cero.
- **Copia de Windows:** era el sitio de trabajo anterior. La del servidor es idéntica (commit
  `3946088`, 140 archivos). El usuario la borrará a mano cuando compruebe que esta sesión funciona.
  A partir de ahora **la fuente de verdad es esta**.

## 2. Qué hay

| Pieza | Dónde | Notas |
|---|---|---|
| Core | `core/` → fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD` | Repo git independiente, ignorado por este. Commit `23e26289a`. |
| Motor de runas | `server/mod-rune-engraving/` | Copia propia de `mod-sod`, sin cambios aún. |
| Contenido | `server/mod-sod-content/` | Un solo módulo: mago (`src/mage/`) + mundo (`src/world/`). |
| Parche de cliente | `tools/sod-client/` | Generador MPQ + SQL de hechizos. **Nunca ejecutado.** |
| Bots | `upstream/mod-playerbots/` | **No se usa**: `acore-test` ya tiene su propio `mod-playerbots`. |
| Referencias | `upstream/azerothcore/mod-sod/` | Solo lectura. |

`acore-test/modules/` tiene dos enlaces simbólicos a nuestros módulos (`mod-rune-engraving`,
`mod-sod-content`) y **11 módulos ajenos** (`mod-individual-progression`, `mod-guildhouse`, …).
**No se ha comprobado que convivan con SoD.** `acore-test` está en la rama `Playerbot-SoD`
(remoto `sod`; `origin` sigue siendo `mod-playerbots/azerothcore-wotlk`).

Documentos clave: decisiones `docs/decisiones/0001`–`0005`, informes en `docs/investigacion/`
(viabilidad, opción SoD, **auditoría de `mod-sod`**), guía `docs/guias/compilar-en-linux.md`.

## 3. Pendiente, por orden

1. **Esperar a que el usuario haga los pasos 2–4** (`cmake`, `make`, `make install`) **y traiga el
   resultado.** Lo útil que puede traer es el *primer* error (`grep -n "error:" ~/sod-build.log | head`). Corregirlo delegando (§5).
2. **`agentrelay` ya está instalado** (v0.2.0 en `~/.local/bin`; `agentrelay doctor` todo `[ok]`,
   ejecutor Codex con gpt-6-luna, sesión de ChatGPT iniciada; comprobado el 2026-10-05). Se delega
   con `agentrelay run` (§5).
3. **Crear el repositorio `warcrafted-server/WotLK-SoD` en GitHub** (es ESTE proyecto, no el core; el core ya vive en su fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD`, y `core/` ya apunta a él) (el usuario: no hay `gh` ni
   token) y **subirlo desde aquí**. El `origin` de este clon apunta a un bundle que ya no existe
   (`/tmp/wotlk-sod.bundle`): cambiarlo a `git@github-warcrafted:warcrafted-server/WotLK-SoD.git`
   (alias SSH ya configurado en este servidor). Verificado que ese repositorio **no existía** el
   2026-10-05. **Mientras no se suba, este clon es la única copia fuera de Windows.**
4. **Las 12 runas de fase 1 del mago están escritas** (2026-10-05), **ninguna compilada ni probada**.
   Las 4 nuevas, ordenadas por `rune_id`: Fingers of Frost 7000009 (pecho, pasivo 400647 clon del
   talento 44543), Burnout 7000010 (pecho, 412286, clon de 44449 + script C++
   `spell_sod_mage_burnout`), Icy Veins 7000011 (piernas, 425121, clon de 12472) e Ice Lance 7000012
   (manos, 400640, clon de 30455). Iconos de las 4 verificados con Wowhead el
   2026-10-05 (`ability_mage_wintersgrasp`, `ability_mage_burnout`, `spell_frost_coldhearted`,
   `spell_frost_frostblast`; los 2 primeros estaban mal y se corrigieron). Los clones heredan sus efectos en el servidor con `inherit_server`
   (verificado en el SQL generado, no en juego). **Diferencias con SoD:** el chill de Blizzard no activa
   Fingers of Frost; Ice Lance hace x3 contra congelados (core) y no x5; sin Winter's Chill; con
   Icy Veins e Ice Lance reales (talento / nivel 66) el mago tendrá dos copias del hechizo.
5. **SQL de SoD: se aplica solo al arrancar el worldserver** (leído en `core/src/server/database/Updater/`,
   no ejecutado). El actualizador recorre `modules/<módulo>/data/sql/*db-world*/` (y `db-characters`)
   en profundidad, aplica cada `.sql` por orden global de **nombre de archivo** (los nombres no pueden
   repetirse entre módulos: es un error fatal) y lo reaplica si cambia su hash. Orden: `rune_engraving_schema.sql`
   (r) va antes que `sod_*` (s), así que las guardas de `sod_mage_runes.sql` ven ya las tablas del motor;
   no renombrar los de `sod_` a algo anterior a `rune_`. La configuración del reino de desarrollo
   (`Servers/acore-test/etc/worldserver.conf`) está bien: `RealmID 2`, puerto 8086, SOAP 7879, bases
   `acore_world_test`, `acore_characters_test`, `acore_playerbots_test` y `acore_auth` compartida;
   `Updates.AutoSetup 1` y `Updates.EnableDatabases 7`. La base de bots se rellena con el propio
   mecanismo de `mod-playerbots` (producción usa lo mismo; no verificado en este reino).
6. **Parche de cliente generado (2026-10-05), sin probar en juego:** `patch-z.mpq` y
   `patch-esES-z.mpq` escritos en la copia `datos/cliente-sod/` y guardados en
   `datos/parche-cliente/20261005-9ea0206/` (con `LEEME.txt`). Falta copiarlos al cliente del usuario
   (cada MPQ en su carpeta) y el addon RuneEngraver (`https://github.com/mod-sod/RuneEngraver`, clonado en `upstream/`). Detalle:
   **Parche de cliente y addon:** pasos, copia de seguridad y distribución en
   `docs/guias/preparar-cliente.md`. Los DBC del cliente **no están en este servidor**: el usuario
   decide dónde se genera. Nunca se ha ejecutado.
6b. **Textos en esES (hecho, sin probar en juego).** El usuario juega en español: el generador acepta
   `--locale esES` (lee y escribe en `Data/esES/`, partiendo del `Spell.dbc` español) y escribe las
   columnas esES (posición `enUS + 6` del DBC, **no** la columna `Name_Lang_esES` del esquema SQL, que
   es otra) desde `server/mod-sod-content/tools/sod_spells_es.json` (textos oficiales de wago.tools
   `&locale=esES`, tokens resueltos como en el inglés). Sin texto oficial se ve el inglés
   (900003, 900005 y los hechizos 9000xx). Objetos: `sod_content_locale_es.sql` (25 filas de
   `item_template_locale`, oficiales). **Pendiente:** criaturas y objetos de mundo propios (ids no
   están en wago.tools), facultades `rune_template` y el addon (en inglés), nombres de las 2
   facciones (hoy en inglés), y aplicar el SQL de locale (no verificado que el importador lo haga).
7. **Licencia del código original** del repositorio. Lo coherente es GPL v2 o posterior; decide el
   usuario.
8. **Más clases (en curso, 2026-10-05).** Catálogo oficial de las runas (wago.tools, build final
   1.15.9.70003): `tools/sod-data/extract_runes.py` genera `docs/runas/catalogo-sod.json` (661 runas de
   todas las ranuras) y una ficha por clase (`docs/runas/<clase>.md`, solo Chest/Legs/Hands: 106
   runas, entre 11 y 14 por clase). La clase sale de `SpellClassOptions` y tiene ruido: 4 correcciones
   explícitas en el script (`CLASS_OVERRIDES`; *Nature's Fury* como chamán es **probable**, sin segunda
   fuente). Decisiones del usuario: valores de la **versión final**, **escalados a nivel 80**,
   orden de clases indiferente. **Escalado:** Wowhead publica la fórmula de SoD, p. ej. Lifebloom =
   `4/100 × 7 × (38,95 + 0,607·L + 0,168·L²)` (poder de hechizo por nivel); permite evaluarla a L=80
   (×1,71 respecto a L=60) y mantener el coeficiente. Los efectos en % no se escalan. Las 12 runas del
   mago (valores de nivel 25) necesitan esa misma pasada. **Wowhead:** responde, pero cortó el acceso
   (HTTP 403) tras ~25 páginas seguidas en pocos minutos: usarlo con pausas largas y pocas
   peticiones, y dar por no verificada cualquier comprobación masiva. Falta la obtención de las
   runas (objeto/NPC), que wago no trae. No se ha implementado ninguna runa de otra clase.
   Equivalentes en WotLK 3.3.5a, solo por nombre exacto (`tools/sod-data/match_wotlk.py`,
   `docs/runas/equivalencias-wotlk.md/.json`): de las 106, 27 tienen hechizo activo equivalente, 41 son
   rango de un talento y 38 no existen en WotLK (Raging Blow, Starsurge, Sunfire, Skull Bash...). No
   garantiza que el hechizo haga lo mismo que la runa.
   **Política (decidida por el usuario, 2026-10-06): solo se implementan las runas que aportan algo**
   (las que en WotLK exigen talento, 41, y las que no existen, 38); las ~27 redundantes (el hechizo ya
   se aprende a esa clase) quedan fuera. El emparejamiento por nombre tiene falsos positivos (Lava
   Burst, Shadowstrike, Overload, Shadow Bolt Volley apuntan a otros hechizos): validar a mano.
   **Método:** un clon del rango más alto de WotLK (valores de nivel 80; un clon de rango máximo no
   escala con el nivel del jugador) + solo las diferencias claras de SoD (lanzamiento, cooldown,
   duración, coste), `inherit_server`, descripción heredada de la plantilla (concuerda siempre con los
   valores y trae el español), script del core enlazado si lo necesita. Los specs por clase van en
   `tools/sod_spells_<clase>.py` (lista `CLASS_SPEC_MODULES` en `sod_spells.py`), el SQL en
   `sod_<clase>_runes.sql` (nombre con prefijo `sod_`, por el orden de aplicación) y las bandas de
   `rune_id` salen de `server/mod-rune-engraving/docs/integrating-content.md`.
   **Hecho:** piloto de brujo, Chaos Bolt 7008001 (403629, clon de 59172, escuela Caos) y Haunt
   7008002 (403501, clon de 59164 con script `spell_warl_haunt`): solo SQL/Python/JSON, **sin
   compilar el cambio** y sin probar en juego. Diferencia: la parte de Chaos Bolt que atraviesa
   absorciones no se implementa. **Aviso:** el generador SALTA en silencio un `sod_spells.py` roto; los
   módulos de clase se importan sin ese silencio.
   **Pendientes (59):** `docs/runas/plan-implementacion.md` las clasifica por reglas simples: 8 pasivas (P),
   14 con proc (T), 37 que necesitan C++ (C). Ojo: la clasificación es heurística; Living Bomb de mago
   aparece pese a estar hecha (se excluyó por otro id).
   **Requisito del usuario (2026-10-06): todos los mensajes del servidor (comandos `.rune`, gossip del
   grabador, objetos y eventos) deben salir de tablas de cadenas, como mínimo en inglés y español de España.
   Hoy están en inglés dentro del C++** (~70 llamadas en `cs_rune.cpp`, `npc_rune_engraver.cpp`,
   `item_rune_unlock.cpp`, `sod_mage_azora_event.cpp` y otros). Pendiente; implica C++ y recompilar.
   Plan: primero las de nivel A (clon de un hechizo de WotLK, solo datos); el resto, tras compilar.
   (Antes: solo después de que el mago compile y funcione.)
8b. **Más clases (histórico):** (guerrero, chamán, etc.): solo después de que el mago compile y funcione.

## 4. Lo que ya sabemos (no lo vuelvas a investigar)

- **Qué es el proyecto:** SoD recreado sobre AzerothCore (cliente 3.3.5a, build 12340) con módulos.
  Ningún core soporta el cliente 1.15.x y el cliente WotLK Classic está retirado. HermesProxy se
  valoró y se descartó por ahora (beta, cliente 3.4.3 no descargable, no resuelve el parche).
- **El cliente 3.3.5a no puede aprender hechizos nuevos en tiempo de ejecución:** cada habilidad son
  dos mitades sincronizadas (servidor + parche MPQ). **Los jugadores tendrán que instalar el parche.**
- **`mod-sod` está parado desde 2026-06-22**, 0 estrellas y 0 forks: el mantenedor somos nosotros.
  De las 9 clases solo el mago tiene contenido (~11 habilidades, 2.715 líneas); el resto eran
  plantillas vacías. De las 12 runas de fase 1 del mago hay 8 hechas.
- **Fase 1 de SoD:** 3 ranuras de grabado (pecho, piernas, manos), 4 runas cada una = 12 por clase.
  SoD completo (8 fases, 218 runas mínimo, 9 raids) **no es objetivo**.
- **Niveles:** se empieza en 60 y se llegará al 80 (decisión 0002). **Ningún tope de nivel va como
  constante en el código**: siempre parámetro de configuración (patrón `SodMage.LivingBomb.ScalingCapLevel`).
- **Hechizos sustitutos:** la runa de Arcane Blast concede un hechizo sustituto (Arcane Burst) hasta
  que el mago aprende el real, a nivel 64. Las runas de escarcha probablemente tengan el mismo
  problema (no verificado).
- **Motor de runas:** se acopla al contenido **por base de datos, no por símbolos**, con SQL
  dinámico condicional que es un no-op si el motor no está. Once ranuras; el nivel mínimo de cada
  una es configurable. Rangos de `rune_id` reservados por clase (mago `7000000–7000999`).
- **Arquitectura:** core + motor + **un solo módulo de contenido** (decisión 0004). Una clase = un
  subdirectorio de `src/`. El SQL va plano en `data/sql/db-world/base/` con prefijo de clase.
- **El fork de Playerbots no es el AzerothCore oficial:** p. ej. `Player::removeSpell` tiene allí 3
  parámetros, sin `sendPacket`. **Comprueba siempre contra `core/`**, nunca contra el oficial.
- **Requisitos de compilación:** Clang ≥ 18 y MySQL 8.4 LTS. **Este servidor los cumple** (Debian 13,
  Clang 19.1.7, MySQL 8.4.11, CMake 3.31). 4 núcleos, 15 GB de RAM, con un reino en vivo.
- **`sod-client`:** busca `modules/mod-sod-*/` y nombra su salida `sod_<módulo sin «mod-sod-»>_spell_dbc.sql`;
  por eso `sod_content_spell_dbc.sql`. Los datos de SoD salen de **wago.tools** (receta y dos trampas
  en `server/mod-sod-content/docs/pulling-sod-data.md`). Wowhead no se deja leer por scraping.
- **Licencias:** todas las cabeceras de código dicen «GPL v2 o posterior» (core, Playerbots y
  `mod-sod`), aunque `mod-sod` incluya un `LICENSE` con texto de v3.
- **Comprobado:** 0 colisiones entre los 67 ids de nuestro SQL y `acore_world_test` (solo `SELECT`).
- **Los informes de subagentes baratos contenían errores de bulto** (afirmaciones falsas sobre
  proyectos, cifras sin fuente). **Verifica lo crítico en la fuente antes de darlo por bueno.**

## 5. Cómo delegar (importante)

El objetivo del usuario es **ahorrar tokens de Claude** dejando al orquestador la planificación, el
diseño y la revisión. **Delega por defecto**; ver `AGENTS.md`.

- **Con `agentrelay`** (instalado, §3.2): `agentrelay run`, y revisión con
  `agentrelay review`. En Linux el comando es `agentrelay`.
- **Si `agentrelay` no estuviera disponible** (`command -v agentrelay`): usa subagentes de Claude
  Code con un modelo más barato para lo mecánico y **dilo al usuario**. No hagas tú en silencio el
  trabajo no trivial.
- **Cómo encargar bien una tarea** (lección cara: el 2026-10-05 una tarea abierta consumió 7,5 M
  de tokens y 40 minutos sin escribir un archivo): un objetivo cerrado y pocos archivos; **tú aportas
  los datos ya masticados** (IDs, valores, URLs) en vez de pedir que los busque; validaciones que
  funcionen en su shell, mejor `python -c`.
- **Revisa siempre** el diff completo y el informe, y audita lo que importe. La autorrevisión del
  ejecutor no sustituye la tuya.

**Las 4 runas de escarcha:** encárgalas **de una en una**, tras sacar tú de wago.tools el ID real, la
descripción y los valores de cada hechizo (receta en `pulling-sod-data.md`). Sigue el patrón de la
runa de Arcane Blast (`server/mod-sod-content/src/mage/spell_sod_mage_arcane_blast_rune.cpp`,
`data/sql/db-world/base/sod_mage_arcane_blast_unlock.sql`, su fila en `sod_mage_runes.sql` y su
entrada en `tools/sod_spells.py`) y la receta de `docs/adding-a-spell.md` del módulo. **No
inventes** IDs ni valores: si wago.tools no responde, párate y dilo.

## 6. Qué NO hacer

- **No compiles**: ni `cmake`, ni `make`, ni `make install`. Pídeselo al usuario con el comando exacto.
- **No borres ni vacíes nada** en el servidor (build, bases de datos, binarios) sin que lo pida.
- **No toques producción:** `Servers/acore-playerbots`, `acore_auth` (compartida; incluida la fila
  del reino 2) ni las bases sin sufijo `_test`. Antes de tocar algo en vivo, comprueba a qué reino
  pertenece. Normas del servidor en `/home/stark/Repos/CLAUDE.md` (en catalán).
- **No pidas contraseñas ni tokens** ni cambies la configuración de usuario/correo/remoto de git.
- **No modifiques `upstream/` ni `acore-test` más allá de lo documentado** en la decisión 0005.
- **No hagas `git push`** sin que el usuario lo pida.
- **No digas «compilado» ni «funciona»** sin que se haya ejecutado de verdad.
