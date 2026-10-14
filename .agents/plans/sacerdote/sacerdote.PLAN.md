# Plan: sacerdote (runas base de SoD pendientes)

Encargo del usuario (2026-10-10): seguir con el resto de clases hasta la fase 8. Las 253 runas base de las 8 ranuras del
catálogo; aquí las que faltan del sacerdote. Las runas «Soul of…» van después (`docs/runas/almas-sod.md`).

## Convenciones
Las del chamán y el brujo (`.agents/plans/chaman/`, `.agents/plans/brujo/`), con la familia de WotLK 6. Los encargos se
generan con `python3 tools/sod-data/gen_tareas_clase.py priest <salida>` y llevan los ids de WotLK, talentos, instructor y
scripts/`spell_proc` del core ya consultados. Tras cada tarea: `python3 tools/sod-data/revisar_runas.py priest 6`,
`tools/sod-data/regenerar_sql_hechizos.sh`, sintaxis con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make`,
CHANGELOG y commit. Lanzar con `agentrelay run .agents/plans/sacerdote/tareas/priestN.json`.

## Pasos

| Paso | Runas | Esfuerzo | Estado |
|---|---|---|---|
| 1 | Serendipity (7005003), Strength of Soul (7005004), Twisted Faith (7005005), Homunculi (7005006), Prayer of Mending (7005007) | high | hecho |
| 2 | Shared Pain (7005008), Mind Sear (7005009), Shadow Word: Death (7005010), Empowered Renew (7005011), Mind Spike (7005012) | high | hecho |
| 3 | Renewed Hope (7005013), Dispersion (7005014), Pain Suppression (7005015), Spirit of the Redeemer (7005016), Void Plague (7005017) | high | hecho |
| 4 | Divine Aegis (7005018), Eye of the Void (7005019), Pain and Suffering (7005020), Despair (7005021), Power Word: Barrier (7005022) | high | hecho |
| 5 | Surge of Light (7005023), Void Zone (7005024), Binding Heal (7005025), Soul Warding (7005026), Vampiric Touch (7005027) | high | pendiente |
| 6 | Adquisición de los objetos-runa (como `sod_shaman_acquisition.sql`) | medium | pendiente |
