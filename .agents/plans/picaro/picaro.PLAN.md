# Plan: pícaro (runas base de SoD pendientes)

Encargo del usuario (2026-10-10): seguir con el resto de clases hasta la fase 8. Las 253 runas base de las 8 ranuras del
catálogo; aquí las que faltan del pícaro. Las runas «Soul of…» van después (`docs/runas/almas-sod.md`).

## Convenciones
Las del chamán y el brujo (`.agents/plans/chaman/`, `.agents/plans/brujo/`), con la familia de WotLK 8. Los encargos se
generan con `python3 tools/sod-data/gen_tareas_clase.py rogue <salida>` y llevan los ids de WotLK, talentos, instructor y
scripts/`spell_proc` del core ya consultados. Tras cada tarea: `python3 tools/sod-data/revisar_runas.py rogue 8`,
`tools/sod-data/regenerar_sql_hechizos.sh`, sintaxis con los flags reales de `acore-test/build/modules/CMakeFiles/modules.dir/flags.make`,
CHANGELOG y commit. Lanzar con `agentrelay run .agents/plans/picaro/tareas/rogueN.json`.

## Pasos

| Paso | Runas | Esfuerzo | Estado |
|---|---|---|---|
| 1 | Deadly Brew (7004002), Just a Flesh Wound (7004003), Quick Draw (7004004), Slaughter from the Shadows (7004005), Between the Eyes (7004006) | high | hecho |
| 2 | Blade Dance (7004007), Envenom (7004008), Cutthroat (7004009), Main Gauche (7004010), Saber Slash (7004011) | high | hecho |
| 3 | Shadowstrike (7004012), Poisoned Knife (7004013), Shadowstep (7004014), Shuriken Toss (7004015), Master of Subtlety (7004016) | high | hecho |
| 4 | Rolling with the Punches (7004017), Waylay (7004018), Combat Potency (7004019), Focused Attacks (7004020), Honor Among Thieves (7004021) | high | hecho |
| 5 | Carnage (7004022), Cut to the Chase (7004023), Unfair Advantage (7004024), Blunderbuss (7004025), Crimson Tempest (7004026) | high | hecho |
| 6 | Fan of Knives (7004027) | high | pendiente |
| 7 | Adquisición de los objetos-runa (como `sod_shaman_acquisition.sql`) | medium | pendiente |
