# Plan: paladín completo (las 11 ranuras de SoD)

Encargo del usuario (2026-10-09): avanzar con la siguiente clase mientras él no puede probar el druida.
El paladín es la siguiente en la cola. Estado de partida (commit `eeb72d6`): 10 runas hechas
(`7002001`–`7002010`), sin compilar ni probar. Faltan 19.

## Convenciones (las mismas que el druida)
- Specs en `server/mod-sod-content/tools/sod_spells_paladin.py`; SQL en `sod_paladin_runes.sql`;
  C++ en `server/mod-sod-content/src/paladin/` (un `.cpp` por runa, declarado en `spell_sod_paladin.h`
  y registrado en `src/sod_content_loader.cpp`); configuración en `conf/mod_sod_content.conf.dist`
  (`SodPaladin.*`); textos esES en `tools/sod_spells_es.json`.
- `slot_mask` = `1 << ranura`: Cabeza 0 → 1, Espalda 3 → 8, Pecho 4 → 16, Muñecas 5 → 32, Manos 6 → 64,
  Cintura 7 → 128, Piernas 8 → 256, Pies 9 → 512. `class_mask` del paladín: 2.
- Datos base: `docs/runas/catalogo-sod.json` (descripción, puntos base, coste, enfriamiento). Wowhead con
  el UA de Firefox para contrastar; si el ejecutor no tiene red, usar el catálogo y marcar «no verificado».
- Tras aceptar cada tarea, el orquestador regenera `sod_content_spell_dbc.sql` (`build_patch.py --dry-run`
  con una raíz falsa en el scratchpad que enlaza `server/mod-*`; nunca sobre `acore-test/modules`),
  comprueba la sintaxis con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make`
  y hace commit con su entrada en `CHANGELOG.md` y `docs/PRUEBAS.md`.

## Pasos (ejecutor: AgentRelay; orquestador: revisión y commit)

| Paso | rune_id | Runas | Esfuerzo | Estado |
|---|---|---|---|---|
| 1 | 7002011–7002014 | Infusion of Light (Cintura), Light's Grace (Muñecas), Improved Sanctuary (Cabeza), Aegis (Pecho) | medium | hecho (Improved Sanctuary sin efecto, ver TODO) |
| 2 | 7002015–7002018 | Sheath of Light (Cintura), Guarded by the Light (Pies), Shock and Awe (Espalda), Hallowed Ground (Pecho) | high | hecho |
| 3 | 7002019–7002023 | Beacon of Light (Manos), Hammer of the Righteous (Muñecas), Shield of Righteousness (Espalda), Divine Light (Espalda), Rebuke (Piernas) | high | hecho |
| 4 | 7002024–7002027 | Sacred Shield (Pies), Inspiration Exemplar (Piernas), Hand of Reckoning (Manos), Malleable Protection (Cintura) | high | hecho |
| 5 | — | Adquisición de los objetos-runa del paladín (venta en el Grabador y botín real de `docs/runas/fuentes-sod.json`), como `sod_druid_acquisition.sql` | medium | pendiente |

**Hand of Sacrifice (462853), descartada:** en WotLK el paladín ya aprende Mano de sacrificio (6940) a nivel
46 y se empieza en 60 (política del 2026-10-06: las runas redundantes quedan fuera). Anotada en `TODO.md`.

Cada paso: criterio de terminado = runas en spec y SQL, scripts registrados, `check_syntax.py` sin errores,
filas en `docs/runas/obtencion.md`, simplificaciones anotadas en `TODO.md` (sección «Paladín»).
Ante un imprevisto de diseño, el ejecutor para y lo dice en su informe.
