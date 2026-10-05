# 0005 — Entorno de pruebas en el servidor Debian

- **Fecha:** 2026-10-05
- **Estado:** ACEPTADA (decisión del usuario, tomada tras ser avisado de las consecuencias)

## Contexto

El desarrollo se hace desde Windows, pero compilar y probar exige el servidor Debian
`warcrafted` (`192.168.1.150`, usuario `stark`), que es una máquina **en producción**: tiene un
reino activo con jugadores. Su `CLAUDE.md` (`/home/stark/Repos/CLAUDE.md`) fija dos reinos con un
único `authserver` y una `acore_auth` compartida:

| Reino | id | Binarios | Puerto | SOAP | Bases de datos |
|---|---|---|---|---|---|
| IceTracks (**producción**) | 1 | `Servers/acore-playerbots` | 8085 | 7878 | `acore_world`, `acore_characters`, `acore_playerbots` |
| Desarrollo (**pruebas**) | 2 | `Servers/acore-test` | 8086 | 7879 | las mismas con sufijo `_test` |

Norma del servidor: todo se prueba primero en desarrollo y solo pasa a producción cuando es
estable; antes de tocar algo en vivo, comprobar a qué reino pertenece.

## Decisión

- **Directorio del proyecto:** `/home/stark/Repos/acore-sod` (clon de este repositorio).
- **Compilación:** dentro de `/home/stark/Repos/acore-test`, con sus módulos propios, que
  instala en `/home/stark/Servers/acore-test`. **Instalación nueva**: el usuario borra el `build/`
  y las bases `*_test` de instalaciones anteriores «para no mezclar conceptos».
- **Quién compila y quién borra:** **solo el usuario.** El orquestador nunca ejecuta `cmake`,
  `make` ni `make install`, y **no borra ni vacía nada** en el servidor (ni build, ni bases, ni
  binarios): lo pide y el usuario lo lanza. Se ofreció una copia de seguridad previa; el usuario
  prefirió gestionarlo él.
- **Core:** `acore-test` pasa a la rama `Playerbot-SoD` de nuestro fork (mismo commit
  `23e26289a` que tenía en `Playerbot`, así que no cambia ningún archivo). `origin` sigue siendo
  `mod-playerbots/azerothcore-wotlk`; el fork es un remoto nuevo llamado `sod`.
- **Módulos nuestros:** dos enlaces simbólicos en `acore-test/modules/`, ignorados por git:
  `mod-rune-engraving` y `mod-sod-content`, que apuntan a `acore-sod/server/`. La fuente única
  sigue siendo `acore-sod`.
- **No se enlaza `mod-playerbots` de este proyecto:** `acore-test` ya tiene el suyo
  (`warcrafted-server/mod-playerbots`) y habría dos módulos iguales.

## Consecuencias que el usuario conoce y acepta

- **El reino de pruebas (id 2) pasa a ser el de SoD**, sobre bases `*_test` nuevas: lo que había
  en ellas se pierde por decisión del usuario (eran 448 MB en `acore_world_test`, 37 MB en
  `acore_characters_test`, con 1004 personajes, y 74 MB en `acore_playerbots_test`).
- **Nunca se tocan** `acore_auth` (compartida con producción, incluida la fila del reino 2), las
  bases sin sufijo `_test`, ni `Servers/acore-playerbots`. Se conservan `Servers/acore-test/data/`
  (3,1 GB de datos del cliente) y `etc/` (configuración).
- SoD se compila **junto a los otros 11 módulos** de `acore-test` (`mod-individual-progression`,
  `mod-guildhouse`, …). **No se ha comprobado que convivan.** Un conflicto de símbolos o de scripts
  aparecería al compilar o al arrancar.
- Quien compila comparte máquina con producción: 4 núcleos, 15 GB de RAM.

## Verificado (solo lectura, 2026-10-05)

- Debian 13, Clang 19.1.7, GCC 14.2 (insuficiente, pero se usa Clang), CMake 3.31, MySQL 8.4.11,
  Git 2.47, Python 3.13. **Cumple los requisitos de AzerothCore.**
- **0 colisiones de ids** entre el SQL de `mod-sod-content` y `acore_world_test`: se comprobaron
  67 (25 hechizos, 25 objetos, 7 objetos de mundo, 10 criaturas) con `SELECT`.
- `acore-sod/core` clonado en `Playerbot-SoD` @ `23e26289a`; `acore-test` en la misma rama y
  commit, con 0 cambios sin confirmar.

## No verificado

- Que el conjunto compile (nada se ha compilado jamás en este proyecto).
- Que SoD y los demás módulos no choquen en tiempo de ejecución.
- Que el importador de AzerothCore aplique solo el SQL de nuestros módulos: **no se aplica nada
  todavía**; primero se compila y se mira si arranca.

## Cómo volver atrás

Para el código: `cd /home/stark/Repos/acore-test && git checkout Playerbot` y quitar los dos
enlaces (`rm modules/mod-rune-engraving modules/mod-sod-content`). **Lo borrado de las bases y
del `build/` no se recupera** salvo que el usuario haya hecho su propia copia.
