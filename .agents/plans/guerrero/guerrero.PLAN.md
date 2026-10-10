# Plan: guerrero (runas base de SoD pendientes)

Encargo del usuario (2026-10-10): seguir con el resto de clases hasta la fase 8. Las 253 runas base de las 8 ranuras del
catálogo; aquí las que faltan del guerrero. Las runas «Soul of…» van después (`docs/runas/almas-sod.md`).

## Convenciones
Las del chamán y el brujo (`.agents/plans/chaman/`, `.agents/plans/brujo/`), con la familia de WotLK 4. Los encargos se
generan con `python3 tools/sod-data/gen_tareas_clase.py warrior <salida>` y llevan los ids de WotLK, talentos, instructor y
scripts/`spell_proc` del core ya consultados. Tras cada tarea: `python3 tools/sod-data/revisar_runas.py warrior 4`,
`tools/sod-data/regenerar_sql_hechizos.sh`, sintaxis con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make`,
CHANGELOG y commit. Lanzar con `agentrelay run .agents/plans/guerrero/tareas/warriorN.json`.

## Pasos

| Paso | Runas | Esfuerzo | Estado |
|---|---|---|---|
| 1 | Blood Frenzy (7001002), Flagellation (7001003), Raging Blow (7001004), Warbringer (7001005), Commanding Shout (7001006) | high | pendiente |
| 2 | Consumed By Rage (7001007), Frenzied Assault (7001008), Furious Thunder (7001009), Meathook (7001010), Quick Strike (7001011) | high | hecho |
| 3 | Single-Minded Fury (7001012), Victory Rush (7001013), Blood Surge (7001014), Focused Rage (7001015), Precise Timing (7001016) | high | pendiente |
| 4 | Enraged Regeneration (7001017), Gladiator Stance (7001018), Intervene (7001019), Rallying Cry (7001020), Endless Rage (7001021) | high | pendiente |
| 5 | Shield Mastery (7001022), Taste for Blood (7001023), Vigilance (7001024), Rampage (7001025), Sword and Board (7001026) | high | pendiente |
| 6 | Wrecking Crew (7001027), Fresh Meat (7001028), Shockwave (7001029), Sudden Death (7001030) | high | pendiente |
| 7 | Adquisición de los objetos-runa (como `sod_shaman_acquisition.sql`) | medium | pendiente |
