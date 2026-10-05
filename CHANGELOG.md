# Registro de cambios

Formato: más reciente arriba. Una entrada por cambio relevante, con su fecha.

## 2026-10-05 (sesión de continuación)

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
