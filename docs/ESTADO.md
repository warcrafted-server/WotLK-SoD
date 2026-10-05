# Estado del proyecto

**Mantén este archivo al día con cada cambio relevante, no al final de la tarea.** Es lo primero que
lee una sesión nueva. Última actualización: **2026-10-05**, traspaso del desarrollo desde Windows al
servidor Debian.

## 1. Dónde estamos

- **Fase:** primer hito en construcción (fase 1 de SoD, nivel 25). **Nada se ha compilado ni
  ejecutado jamás.** Todo lo verificado hasta ahora es estático (lectura de código, cabeceras,
  firmas, hooks) o consultas `SELECT` de solo lectura.
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
   (manos, 400640, clon de 30455). **Sin verificar:** los nombres de icono de las 4
   (`spell_frost_chillingblast`, `spell_fire_burnout`, `spell_frost_coldhearted`,
   `spell_frost_frostblast`). Los clones heredan sus efectos en el servidor con `inherit_server`
   (verificado en el SQL generado, no en juego). **Diferencias con SoD:** el chill de Blizzard no activa
   Fingers of Frost; Ice Lance hace x3 contra congelados (core) y no x5; sin Winter's Chill; con
   Icy Veins e Ice Lance reales (talento / nivel 66) el mago tendrá dos copias del hechizo.
5. **Aplicar el SQL de SoD.** No se ha aplicado nada. Falta decidir el orden y comprobar si el
   importador de AzerothCore aplica solo `data/sql/db-world/base/` de los módulos (no verificado).
6. **Parche de cliente y addon:** pasos, copia de seguridad y distribución en
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
8. **Más clases** (guerrero, chamán, etc.): solo después de que el mago compile y funcione.

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
