# 0003 — Core base: fork propio del AzerothCore de Playerbots

- **Fecha:** 2026-10-05
- **Estado:** ACEPTADA (decisión del usuario)
- **Sustituye en parte a:** [0001](0001-core-y-version-de-cliente.md), que daba por hecho un
  AzerothCore oficial sin tocar.

## Decisión

El core es **nuestro fork del AzerothCore de Playerbots**:

- Fork: https://github.com/warcrafted-server/azerothcore-wotlk, **rama `Playerbot-SoD`**.
- Origen: https://github.com/mod-playerbots/azerothcore-wotlk, rama `Playerbot`, que a su vez
  deriva de https://github.com/azerothcore/azerothcore-wotlk.
- Se trabaja en `core/` (repositorio git independiente, ignorado por este repositorio) con tres
  remotos: `origin` (nuestro fork), `playerbots` (el intermedio) y `acore` (el oficial).
- Nuestros parches al core van **solo en `Playerbot-SoD`**, nunca en `Playerbot`, para poder
  seguir fusionando las novedades de Playerbots sin conflictos.

## Por qué un fork

- **Playerbots lo exige.** `mod-playerbots` necesita cambios en el core que no caben en un
  módulo; no funciona con AzerothCore oficial.
- Tener el fork propio deja la puerta abierta a **parchear el core si algún día un módulo no
  basta**, que era la preocupación del usuario.

## Cuánto se aparta del oficial (medido el 2026-10-05)

El fork de Playerbots lleva 618 commits propios, pero el cambio real es pequeño:
**33 archivos, +754 / −149 líneas**. Casi todo es CI (flujos de GitHub) y la capa de base de
datos (`src/server/database`, 501 líneas); el código de juego que cambia son unas 49 líneas. En
la medición iba **180 commits por detrás** de AzerothCore (base común del 2026-09-23).

Nuestro fork, al crearse, coincidía con `Playerbot` (commit `23e26289a`) y llevaba 4 commits más
que el clon que medí, que son la fusión de ese mismo día: está al día.

## Costes que se asumen

- **Dependemos de que el equipo de Playerbots siga fusionando AzerothCore.** Si lo abandonan,
  esa fusión pasa a ser nuestra.
- **Cada línea que añadamos al core es una línea que reconciliar en cada fusión.** Regla: solo
  se parchea el core cuando ningún hook de módulo permite hacerlo.
- Las firmas del core **no son las del AzerothCore oficial**. Ejemplo ya encontrado:
  `Player::removeSpell` tiene allí tres parámetros, sin el `sendPacket` del oficial. El motor de
  runas lo llama con tres y compila con ambos, pero **toda comprobación de compatibilidad debe
  hacerse contra nuestro `core/`**, no contra el oficial.

## Verificado y no verificado

- **Verificado (estático, contra nuestro `core/`):** las cabeceras que incluye
  `mod-rune-engraving`, la firma de `learnSpell`/`removeSpell` y los 10 hooks que sobrescribe.
- **No verificado:** que compile. Falta un build real (ver
  [guía de compilación](../guias/compilar-en-linux.md)).
- **No verificado:** que `mod-playerbots` y nuestros módulos convivan sin conflicto de scripts o
  de identificadores. Los bots no conocen las runas de SoD; no se ha estudiado qué hacen con
  ellas.
