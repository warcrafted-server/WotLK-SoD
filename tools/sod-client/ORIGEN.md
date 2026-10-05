# Procedencia de esta herramienta

**Generador del parche de cliente** (MPQ y SQL de hechizos). Copia propia de
https://github.com/mod-sod/sod-client.

- Commit de partida: `204627b008b3299948b63876fa949588d9522089`
- Licencia: `LICENSE` con texto de **GPL v3** (no se han revisado las cabeceras de sus fuentes). Copiado sin historial de git.
- Busca los módulos con el patrón `modules/mod-sod-*/`, que encaja con `mod-sod-content`.
  **No se ha ejecutado nunca con la estructura nueva**: necesita los DBC del cliente 3.3.5a.

## Cambios respecto al original

- 2026-10-05 — Eliminado `.github/` (flujo de publicación de la wiki del repo original).
- 2026-10-05 — Añadido `stormlib_shim.py` (ctypes sobre libstorm) y rutas insensibles a mayúsculas para ejecutar en Linux.
- 2026-10-05 — Añadida la clave inherit_server (SQL del servidor con todas las columnas de la plantilla clonada).
- 2026-10-05 — Añadida la opción --locale y las columnas esES de Spell.dbc/Faction.dbc desde sod_spells_es.json.
