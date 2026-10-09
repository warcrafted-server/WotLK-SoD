# Plan: chamán completo (las 11 ranuras de SoD)

Encargo del usuario (2026-10-09): tras el paladín, avanzar con la siguiente clase de la cola (chamán) todo lo
posible. Estado de partida: 2 runas (`7007001` Earth Shield, `7007002` Lava Lash), sin compilar ni probar.

## Convenciones
Las del paladín (`.agents/plans/paladin/paladin.PLAN.md`), con `class_mask` 64, `src/shaman/`,
`spell_sod_shaman.h`, `SodShaman.*` y `sod_shaman_runes.sql`. Las tareas incluyen las reglas aprendidas al
revisar el paladín: auras válidas solo 0–316, familia de la plantilla, iconos existentes en el cliente, todo
hechizo lanzado por un script definido, `spell_script_names` para scripts sobre hechizos de WotLK, ids
auxiliares desde 900029. Tras aceptar cada paso, el orquestador regenera el SQL de hechizos (`--dry-run` con
raíz falsa), comprueba la sintaxis con los flags reales, actualiza `CHANGELOG.md` y hace commit.

## Pasos

| Paso | rune_id | Runas | Esfuerzo | Estado |
|---|---|---|---|---|
| 1 | 7007003–7007008 | Lava Burst, Riptide, Feral Spirit, Maelstrom Weapon, Tidal Waves, Ancestral Awakening (clones de WotLK) | medium | hecho |
| 2 | 7007009–7007013 | Dual Wield Specialization, Overload, Shield Mastery, Two-Handed Mastery, Healing Rain | high | hecho |
| 3 | 7007014–7007017 | Ancestral Guidance, Greater Ghost Wolf, Way of Earth, Molten Blast | high | pendiente |
| 4 | 7007018–7007022 | Power Surge, Decoy Totem, Spirit of the Alpha, Burn, Mental Dexterity | high | pendiente |
| 5 | 7007023–7007027 | Overcharged, Rolling Thunder, Static Shock, Coherence, Storm, Earth, and Fire | high | pendiente |
| 6 | — | Adquisición de los objetos-runa del chamán (como `sod_paladin_acquisition.sql`) | medium | pendiente |

**Descartadas:** Water Shield (408510; en WotLK se aprende a nivel 20, id 52127) y Fire Nova (408339; en
3.3.5a Nova de Fuego 1535 ya es el hechizo base que hace estallar el tótem de fuego), por redundantes (política
del 2026-10-06). **Nature's Fury (408307):** sin objeto en SoD y clase dudosa en el catálogo; no se implementa.
