# 0004 — Arquitectura: tres capas, no un módulo por clase

- **Fecha:** 2026-10-05
- **Estado:** ACEPTADA (propuesta por el orquestador a petición del usuario, que la dio por
  buena al aportar el fork y pedir seguir)

## Contexto

`mod-sod` original tiene un módulo por clase (diez), más motor, mundo, instalador y generador de
parche. El usuario planteó que serían demasiados de mantener y de parchear.

Los datos lo respaldan: cada módulo vacío tiene **24 archivos para 31 líneas de código**
(plantillas de CI, de incidencias, `.editorconfig`, `CONTRIBUTING`, cargador, `.conf`…), repetido
diez veces. Esa estructura existía para que la comunidad contribuyera clase a clase y se
instalara solo lo deseado; **a este proyecto no le sirve**: somos los únicos mantenedores y el
upstream está parado desde el 2026-06-22.

## Decisión

Tres capas, por responsabilidad:

| Capa | Dónde | Qué es |
|---|---|---|
| **Core** | `core/` (fork `Playerbot-SoD`) | Solo lo que un módulo no puede hacer. Ver [0003](0003-core-fork-de-playerbots.md). |
| **Motor** | `server/mod-rune-engraving/` | La mecánica genérica del grabado de runas, sin contenido. |
| **Contenido** | `server/mod-sod-content/` | **Todas las clases y el mundo** en un solo módulo. |
| **Herramienta** | `tools/sod-client/` | Generador del parche MPQ del cliente y del SQL de hechizos. |

### Estructura del módulo de contenido

- Una clase = un subdirectorio de `src/` (`src/mage/`; en el futuro `src/warrior/`, …).
  Verificado: `CollectSourceFiles` de AzerothCore recorre los subdirectorios de forma recursiva.
- **El SQL se queda plano** en `data/sql/db-world/base/` con prefijo de clase
  (`sod_mage_*.sql`), porque el importador de AzerothCore no recorre subdirectorios (esto es
  una precaución, no lo he comprobado en el código).
- Un único cargador (`Addmod_sod_contentScripts()`), un único `.conf` por secciones y un único
  `tools/sod_spells.py`.
- Cada clase se activa o desactiva por configuración (el mago ya lo hace con `SodMage.Enabled`),
  no instalando o quitando módulos.
- El módulo de mundo (`mod-sod-world`, 682 líneas) se **ha plegado** en `src/world/`.

### Por qué el motor sigue separado

Es estable (~2.000 líneas, con tests), genérico y está bien acotado: el contenido se acopla a él
**por base de datos y no por símbolos**. Cuanto más código se mete en el core, más duele cada
fusión. Se mantiene el acoplamiento por BD y sus guardas de SQL; **quitarlas, ahora que somos
dueños de ambos lados, es una simplificación posible pero no urgente** y no se hace sin motivo.

### Dos copias propias, no usar `upstream/` directamente

El motor y el generador se copian a `server/` y `tools/` con su `ORIGEN.md`. Razón: el original
tiene 0 estrellas y 0 forks; si desaparece, el proyecto debe seguir siendo reproducible.

## Qué se cambió (2026-10-05)

Detalle fechado en `server/mod-sod-content/ORIGEN.md`. En resumen: fusión de mago + mundo,
cargador único, `.conf` único, manifiestos fusionados sin ids duplicados (25 objetos, 4
visuales) y `sod_mage_spell_dbc.sql` renombrado a `sod_content_spell_dbc.sql`, que es lo que
`sod-client` generará para un módulo llamado `mod-sod-content`.

## Lo que NO está verificado

- **Nada se ha compilado.** Se comprobó que los 21 `AddSC_*` declarados en el cargador tienen
  definición, pero es una comprobación por texto.
- **`sod-client` no se ha ejecutado con esta estructura.** Por lectura de su código, busca
  `modules/mod-sod-*/` (encaja con `mod-sod-content`) y nombra su salida a partir del módulo.
  Necesita los DBC del cliente 3.3.5a, que no están en esta máquina.
- Las etiquetas `source` de `rune_template` y los comentarios de los `.sql` siguen diciendo
  `mod-sod-mage`: son identificadores de datos y no se tocan sin motivo.
