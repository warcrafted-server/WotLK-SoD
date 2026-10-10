# Plan: brujo completo (las 11 ranuras de SoD)

Encargo del usuario (2026-10-09): «avanza todo lo que puedas» tras el chamán; el brujo es la siguiente clase de la
cola. Estado de partida: 3 runas (`7008001` Chaos Bolt, `7008002` Haunt, `7008003` Demonic Tactics), sin compilar.

## Convenciones
Las del chamán (`.agents/plans/chaman/chaman.PLAN.md`), con `class_mask` 256, familia 5, `src/warlock/`,
`spell_sod_warlock.h`, `SodWarlock.*` y `sod_warlock_runes.sql`. Revisión de cada paso con el revisor automático
(iconos, auras 0–316, familias, columnas inexistentes, `DieSides`, scripts y `spell_proc` de las plantillas, ids
duplicados), regeneración del SQL de hechizos, sintaxis con los flags reales y commit.

## Pasos

| Paso | rune_id | Runas | Esfuerzo | Estado |
|---|---|---|---|---|
| 1 | 7008004–7008008 | Unstable Affliction, Summon Felguard, Metamorphosis, Incinerate, Shadowflame (clones de WotLK) | medium | hecho |
| 2 | 7008009–7008013 | Backdraft, Decimation, Demonic Pact, Everlasting Affliction, Demonic Knowledge (talentos de WotLK) | medium | hecho (DeepSeek, `748aad8`) |
| 3 | 7008014–7008018 | Soul Siphon, Shadow and Flame, Lake of Fire, Master Channeler, Shadow Bolt Volley | high | hecho |
| 4 | 7008019–7008023 | Demonic Grace, Invocation, Dance of the Wicked, Vengeance, Immolation Aura | high | hecho |
| 5 | 7008024–7008027 | Infernal Armor, Mark of Chaos, Pandemic, Grimoire of Synergy | high | pendiente |
| 6 | — | Adquisición de los objetos-runa del brujo (como `sod_shaman_acquisition.sql`) | medium | pendiente |

## Cómo seguir
Los encargos de los pasos 2–5 están listos en `tareas/war2.json`…`war5.json` (con ids de WotLK, scripts y
`spell_proc` del core ya verificados). Lanzar con `agentrelay run .agents/plans/brujo/tareas/warN.json`.
El 2026-10-09 a las 12:36 el ejecutor (Codex) se quedó sin cuota gratuita y sin saldo en la clave de pago; la única
alternativa que ofrece AgentRelay es DeepSeek (`agentrelay use cline deepseek-v4-flash`, necesita su clave): decide
el usuario. El paso 6 (adquisición) falta por preparar, como `sha6.json` del chamán.

