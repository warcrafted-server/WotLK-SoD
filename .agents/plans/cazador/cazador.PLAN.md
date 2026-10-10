# Plan: cazador (runas base de SoD pendientes)

Encargo del usuario (2026-10-10): seguir con el resto de clases hasta la fase 8. Las 253 runas base de las 8 ranuras del
catálogo; aquí las que faltan del cazador. Las runas «Soul of…» van después (`docs/runas/almas-sod.md`).

## Convenciones
Las del chamán y el brujo (`.agents/plans/chaman/`, `.agents/plans/brujo/`), con la familia de WotLK 9. Los encargos se
generan con `python3 tools/sod-data/gen_tareas_clase.py hunter <salida>` y llevan los ids de WotLK, talentos, instructor y
scripts/`spell_proc` del core ya consultados. Tras cada tarea: `python3 tools/sod-data/revisar_runas.py hunter 9`,
`tools/sod-data/regenerar_sql_hechizos.sh`, sintaxis con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make`,
CHANGELOG y commit. Lanzar con `agentrelay run .agents/plans/cazador/tareas/hunterN.json`.

## Pasos

| Paso | Runas | Esfuerzo | Estado |
|---|---|---|---|
| 1 | Beast Mastery (7003004), Cobra Strikes (7003005), Lone Wolf (7003006), Flanking Strike (7003007), Kill Shot (7003008) | high | hecho |
| 2 | Serpent Spread (7003009), Sniper Training (7003010), Carve (7003011), Cobra Slayer (7003012), Aspect of the Viper (7003013) | high | hecho |
| 3 | Expose Weakness (7003014), Melee Specialist (7003015), Steady Shot (7003016), Dual Wield Specialization (7003017), Trap Launcher (7003018) | high | hecho |
| 4 | Wyvern Strike (7003019), Catlike Reflexes (7003020), Lock and Load (7003021), Rapid Killing (7003022), Focus Fire (7003023) | high | pendiente |
| 5 | Raptor Fury (7003024), T.N.T. (7003025), Hit and Run (7003026), Improved Volley (7003027), Resourcefulness (7003028) | high | pendiente |
| 6 | Adquisición de los objetos-runa (como `sod_shaman_acquisition.sql`) | medium | pendiente |
