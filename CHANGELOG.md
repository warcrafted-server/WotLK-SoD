# Registro de cambios

Formato: más reciente arriba. Una entrada por cambio relevante, con su fecha.

## 2026-10-09

- Paladín: runas Sacred Shield `7002024`, Inspiration Exemplar `7002025`, Hand of Reckoning `7002026` y Malleable Protection `7002027` (paso 4). Malleable Protection rehecha en la revisión: usaba el aura 332 (no existe en 3.3.5a), una plantilla inexistente (5573) y no definía el hechizo de poder de ataque 460171; ahora alarga Protección divina con un script enganchado a 498. Los auxiliares clonados de Rejuvenecimiento pasan a familia de paladín. Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Beacon of Light `7002019`, Hammer of the Righteous `7002020`, Shield of Righteousness `7002021`, Divine Light `7002022` y Rebuke `7002023` (paso 3). Corregido en la revisión: Rebuke y el escudo de Divine Light ya no heredan la familia de pícaro o mago de su plantilla; iconos inexistentes o genéricos sustituidos por los reales del cliente. Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Sheath of Light `7002015`, Guarded by the Light `7002016`, Shock and Awe `7002017` y Hallowed Ground `7002018` (paso 2), con valores contrastados en Wowhead. Corregido en la revisión: los beneficios de poder con hechizos ya no suben el daño físico (escuelas 126). Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Infusion of Light `7002011`, Light's Grace `7002012`, Improved Sanctuary `7002013` y Aegis `7002014` (paso 1 de `.agents/plans/paladin/`). Corregido en la revisión: máscaras y reembolso de Choque Sagrado, enfriamiento (en WotLK ya es de 6 s), orden de rangos de Expiación e iconos. Improved Sanctuary aún sin efecto (ver `TODO.md`). Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: recupera del historial (`d85f936`) las 6 runas retiradas el 2026-10-07 (The Art of War, Righteous Vengeance, Improved Hammer of Wrath, Purifying Power, Fanaticism, Wrath), con su configuración y su registro en el loader; SQL de hechizos regenerado. Pasan `clang++ -fsyntax-only` con los flags reales; sin compilar ni probar.
- Lacerate (`7009003`): los worgen Moonrage de Silverpine (1769, 1770, 1782, 1924) sueltan la runa con un 1,0661 %, tasa conjunta de Wowhead para el Unbalanced Idol de SoD. Solo SQL; sin probar en juego.
- `ESTADO.md`: los mensajes del servidor ya salen de tablas de cadenas (inglés y esES); se corrige la nota que lo daba por pendiente.
- `TODO.md`: anota lo que falta del druida (Thrash (Cat), Tiger's Fury). Quita la distribución de parches (ya se publican con el launcher) y la fuente de Lacerate en Silverpine (hecha).

## 2026-10-08

- Añade las runas de druida Lifebloom `7009026` y Nourish `7009027`, con venta en el Grabador y textos oficiales resumidos en español. Sin compilar ni probar en juego.

## 2026-10-05 (sesión de continuación)

- Generador de cliente en Linux: `tools/sod-client/stormlib_shim.py` (ctypes sobre `libstorm`) y rutas
  insensibles a mayúsculas; `--dry-run` ejecutado con éxito sobre una copia del cliente.
- Clave `inherit_server` en los specs: el SQL del servidor de un hechizo clonado lleva todas las
  columnas de su plantilla. Activada en 400647, 412286, 425121 y 400640. `sod_content_spell_dbc.sql`
  regenerado con ellos.

- Español (esES): opción `--locale` en el generador, columnas esES de `Spell.dbc` y `Faction.dbc`,
  `sod_spells_es.json` (textos oficiales) y `sod_content_locale_es.sql` (25 objetos). Sin probar.

- Primer parche de cliente generado (esES) en una copia del cliente y guardado en `datos/parche-cliente/`.
  El MPQ contiene los DBC esperados; sin probar en juego.

- Addon `RuneEngraver` clonado en `upstream/` (commit fijado en `preparar-entorno.sh`); guía de compilación con la opción de apartar los módulos ajenos.

- Catálogo de runas de SoD: `tools/sod-data/extract_runes.py` y `docs/runas/` (JSON + una ficha por clase).
- Iconos de las runas Fingers of Frost y Burnout corregidos (verificados con Wowhead).

- `tools/sod-data/match_wotlk.py` y `docs/runas/equivalencias-wotlk.*`: equivalentes de las 106 runas en WotLK 3.3.5a.
- Primera compilación completa de `acore-test` con nuestros módulos: sin errores (hecha por el usuario).

- Piloto de runas de otra clase (brujo): Chaos Bolt y Haunt (`sod_spells_warlock.py`, `sod_warlock_runes.sql`); `sod_spells.py` carga los specs por clase.

- Runa Chimera Shot de cazador (clon de WotLK, sin compilar ni probar); Explosive Shot sigue pendiente.
- Runas castables de guerrero, paladín, pícaro, sacerdote, chamán y druida (11, clones de WotLK, sin compilar ni probar). Penance sin script del core (exige su cadena de rangos). Cazador pendiente: el coste de Explosive Shot es 3,5 % y `ManaCostPct` es entero.

### Cambiado
- `ESTADO.md`: `agentrelay` ya está instalado y operativo (corrige lo anterior); el `build/` antiguo
  de `acore-test` ya lo ha borrado el usuario.

## 2026-10-05 (traspaso al servidor)

### Añadido
- `docs/ESTADO.md`: estado vivo del proyecto (dónde estamos, pendiente por orden, lo ya sabido,
  cómo delegar y qué no hacer). Es lo primero que lee una sesión nueva.
- Sección 0 de `AGENTS.md`: normas de arranque del orquestador, con la obligación de delegar y
  permiso para ampliar `AGENTS.md` y crear `.agents/`.
- `docs/guias/prompt-de-arranque.md`: prompt para abrir una sesión nueva en este directorio.

### Notas
- El usuario ha hecho el paso 1 de la guía (3 bases `*_test` vacías); `cmake`, `make` e `install`
  siguen pendientes y los hace él.
- (Corregido después: `agentrelay` sí estaba instalado; ver la entrada de la sesión de continuación.)

## 2026-10-05 (servidor de pruebas)

### Añadido
- Proyecto portado al servidor Debian: `/home/stark/Repos/acore-sod` (clon de este repositorio),
  con `core/` (fork `Playerbot-SoD`) y `upstream/` reconstruidos con `tools/preparar-entorno.sh`.
- `acore-test` preparado para compilar: remoto `sod` y rama `Playerbot-SoD` (mismo commit que
  tenía), y enlaces a `mod-rune-engraving` y `mod-sod-content` en `modules/`.
- Decisión `0005` (entorno de pruebas) y sección 7 de la guía de compilación, con los comandos
  concretos.

### Verificado
- El servidor cumple los requisitos de AzerothCore (Debian 13, Clang 19, MySQL 8.4).
- 0 colisiones de ids entre nuestro SQL y `acore_world_test` (67 ids comprobados).

### Notas
- El reino de desarrollo (id 2) pasará a ser el de SoD, con **instalación nueva**: el usuario borra
  el `build/` y las bases `*_test` anteriores. El orquestador no compila **ni borra** nada.
- Anotadas en la guía las opciones de CMake del `build/` anterior, que se pierden al borrarlo.

## 2026-10-05

### Añadido
- Proyecto creado: servidor tipo Season of Discovery sobre AzerothCore (cliente 3.3.5a, build
  12340) con módulos propios.
- Informes de investigación en `docs/investigacion/` (viabilidad, opción SoD, auditoría de
  `mod-sod`) y decisiones `0001`–`0004` en `docs/decisiones/`.
- `server/mod-sod-content/`: módulo único de contenido (clases y mundo), fusión de `mod-sod-mage`
  y `mod-sod-world`, con una clase por subdirectorio de `src/`.
- `server/mod-rune-engraving/`: copia propia del motor de runas.
- `tools/sod-client/`: copia propia del generador del parche de cliente.
- `tools/preparar-entorno.sh`: reconstruye `core/` y `upstream/` con commits fijados.
- `docs/guias/compilar-en-linux.md`: guía de compilación (sin probar).

### Cambiado
- Core: fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD`, en lugar del
  AzerothCore oficial (decisión 0003).
- `.claude/` deja de versionarse (contenía rutas locales).

### Pendiente
- **Nada se ha compilado ni ejecutado todavía.**
- Las 4 runas de escarcha del mago (Fingers of Frost, Burnout, Ice Lance, Icy Veins).
- Ejecutar `tools/sod-client/build_patch.py` con la estructura nueva (necesita el cliente 3.3.5a).
- Decidir la licencia del código original del repositorio.
