# Registro de cambios

Formato: más reciente arriba. Una entrada por cambio relevante, con su fecha.

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
