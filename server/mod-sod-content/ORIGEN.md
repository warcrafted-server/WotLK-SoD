# Procedencia de este módulo

**mod-sod-content** es el módulo de contenido de todas las clases y del mundo. Nace de la
fusión de dos módulos de terceros, ambos con `LICENSE` con texto de **GPL v3**, pero las cabeceras de los fuentes dicen «GPL v2 o posterior» (comprobado el 2026-10-05), copiados a `server/` porque `upstream/`
es de solo lectura. Se copiaron sin su historial de git.

| Parte | Origen | Commit de partida |
|---|---|---|
| `src/mage/`, SQL `sod_mage_*`, manifiestos de mago | https://github.com/mod-sod/mod-sod-mage | `7fd10e20d4277bcc6ec5f6934b2ed1d2033e7335` (2026-06-22) |
| `src/world/`, SQL `sod_world_*`, manifiestos de mundo | https://github.com/mod-sod/mod-sod-world | `6530bb56887c8749d5d7f615e2da2167d221c12a` (2026-06-22) |

## Estructura

Una clase = un subdirectorio de `src/` (`src/mage/`, y en el futuro `src/warrior/`, …). El
SQL se queda plano en `data/sql/db-world/base/` con prefijo de clase (`sod_mage_*.sql`), porque
el importador de AzerothCore no recorre subdirectorios. Un único cargador
(`src/sod_content_loader.cpp`), un único `.conf` por secciones y un único `tools/sod_spells.py`.

## Cambios respecto a los originales

Uno por línea y con fecha, para poder reconciliar con el upstream si vuelve a moverse.

- 2026-10-05 — Fusión de `mod-sod-mage` y `mod-sod-world` en un único módulo; módulo renombrado
  a `mod-sod-content`; fuentes de mago movidas a `src/mage/` y las de mundo a `src/world/`.
- 2026-10-05 — Cargador único `Addmod_sod_contentScripts()` (antes uno por módulo).
- 2026-10-05 — `.conf` único (`mod_sod_content.conf.dist`) con la sección de mundo añadida.
- 2026-10-05 — Manifiestos `client_items.json` y `client_displays.json` fusionados (sin ids
  duplicados), y añadidos `client_creature_displays.json` y `client_factions.json` del mundo.
- 2026-10-05 — `sod_mage_spell_dbc.sql` renombrado a `sod_content_spell_dbc.sql`: es el nombre
  que genera `sod-client` para este módulo (`sod_<módulo sin «mod-sod-»>_spell_dbc.sql`).
- 2026-10-05 — Eliminado `.github/` (plantillas y flujo de publicación de la wiki del repo original).
- Las etiquetas `source` de `rune_template` y los comentarios de los `.sql` siguen diciendo
  `mod-sod-mage`: son identificadores de datos, no se tocan hasta que haya motivo.
