# Auditoría de `mod-sod`: qué hay realmente

Fecha: **5 de octubre de 2026**. Auditoría hecha sobre los repositorios clonados en
`upstream/azerothcore/mod-sod/`, leyendo el código y la documentación. Resuelve la condición
pendiente de la [decisión 0001](../decisiones/0001-core-y-version-de-cliente.md).

## 1. Veredicto en una frase

**El motor está bien hecho y es aprovechable; el contenido está casi todo por escribir.**
De las nueve clases de SoD, **solo el mago tiene contenido real** (unas 11 habilidades); las
demás son copias literales de una plantilla vacía.

## 2. Actividad: el proyecto está parado

| Repositorio | Último commit | Commits |
|---|---|---|
| `mod-sod-mage` | 2026-06-22 | 38 |
| `mod-rune-engraving` | 2026-06-22 | 22 |
| `mod-sod-world` | 2026-06-22 | 22 |
| `sod-installer` | 2026-06-19 | 16 |
| `sod-class-templates` | 2026-06-19 | 2 |
| `mod-sod-warrior` | 2026-06-19 | **1** |
| `mod-sod-druid` | 2026-06-19 | **1** |
| `mod-sod-shaman` | 2026-06-19 | **1** |

**Nada se ha tocado desde el 22 de junio de 2026**, más de tres meses. Con 0 estrellas y 0
forks, hay que asumir que **el proyecto está efectivamente abandonado** y que, si lo adoptamos,
pasamos a ser nosotros los mantenedores. No es un argumento para descartarlo —la licencia GPL v3
lo permite y el código es bueno— pero sí para no contar con ayuda externa.

## 3. Los módulos de clase vacíos: confirmado

`mod-sod-warrior`, `mod-sod-druid` y `mod-sod-shaman` son **idénticos entre sí**: 24 archivos,
**31 líneas** de C++/H, y todos los directorios SQL con solo `.gitkeep`. Son el esqueleto
generado desde la plantilla, sin una sola habilidad.

Comparado con el mago: **61 archivos, 2.715 líneas** de C++/H y 13 archivos SQL.

No he clonado los otros cinco módulos (paladín, cazador, pícaro, sacerdote, brujo), pero dado
que los tres comprobados son copias idénticas de 1 commit, lo razonable es asumir que están
igual. El `mod-sod-deathknight` es además irrelevante: **SoD no tenía Death Knight**.

## 4. Lo que sí está hecho: el mago

Según su propio README (que se describe como «early / proof of concept»), implementado y
funcionando en juego:

- Parte del kit de sanación «Chronomancy»: **Regeneration**, **Mass Regeneration**,
  **Temporal Beacon** (convierte daño Arcano en sanación).
- **Arcane Surge** (consume todo el maná, daño escalado hasta +300%).
- **Living Flame**, **Living Bomb**, **Enlightenment**, **Arcane Blast**, **Nether Vortex**,
  **Rewind Time**, **Living Spark**, **Arcane Burst**.
- Evento **Azora**, cristales arcanos, notas de hechizo, drops.

Son ~11 habilidades con guion propio en C++. Valores de sanación fieles a SoD donde están
implementados, pero **sin pasada de balance**. Documenta como pendientes Chronostatic
Preservation, Rewind Time completo y Temporal Anomaly.

## 5. El motor de runas: la buena noticia

`mod-rune-engraving`, ~2.000 líneas de C++, es la pieza que más valor aporta, y está bien
diseñada:

- **Acoplamiento por base de datos, no por símbolos.** Como los módulos de AzerothCore se
  enlazan estáticamente, cualquier llamada C++ entre módulos sería dependencia de compilación.
  El motor lo evita: el contenido inserta filas en `rune_template` con SQL dinámico condicional,
  y **si el motor no está, el SQL es un no-op limpio**. Las dos partes son independientes.
- **Ranuras de grabado abstractas** (Head, Neck, Shoulder, Cloak, Chest, Wrist, Hands, Waist,
  Legs, Feet, Ring), independientes del equipo, con `slot_mask` de bits.
- Hechizos concedidos como **temporales** (`learnSpell(..., temporary=true)`), así que
  desgrabar nunca borra un hechizo aprendido por otra vía.
- **Reglas de SoD aplicadas**: nivel mínimo por ranura con los cortes de fase reales
  (P1=1, P2=26, P3=41, P4=51), y una misma runa no puede grabarse en dos ranuras.
- **Solo servidor, sin parche de cliente obligatorio**: el addon es opcional y hay un NPC de
  gossip como alternativa.
- **Bandas de `rune_id` reservadas** por clase (mago 7000000–7000999, guerrero 7001000–7001999,
  etc.), documentadas como fuente única de verdad: no habrá colisiones al añadir clases.
- **Tests de Google Test** sobre la lógica pura de elegibilidad, dentro del target `unit_tests`
  de AzerothCore y **sin editar el core**.
- Siete documentos de diseño, incluido un `gotchas.md` con problemas reales de despliegue
  (coordenada Z del NPC, el SQL que no se puede proteger con `WHERE EXISTS`, que la BD necesita
  reinicio del worldserver). **Eso solo lo escribe quien lo ha puesto en marcha de verdad.**

Es honesto además sobre sus límites: documenta que `Engrave`, `ApplyAll`, `LoadPlayer` y los
flujos de desbloqueo **no están testeados** porque necesitarían un arnés con base de datos.

## 6. El obstáculo que no estaba en el análisis previo

Hay una restricción técnica de fondo que conviene entender antes de estimar nada:

> **El cliente 3.3.5a no puede aprender hechizos nuevos en tiempo de ejecución.**

Por eso cada habilidad se entrega en **dos mitades que deben ir sincronizadas**: datos y
guiones en el servidor, y un **parche MPQ del cliente** que le permite representar el hechizo.
Consecuencias prácticas:

- Hace falta el pipeline `sod-client` (Python + `pympq`) para generar un **único**
  `patch-z.mpq` consolidado: WoW reemplaza DBCs enteros por parche, así que las filas de
  `Item.dbc` **no se pueden repartir** entre varios MPQ. Todos los módulos contribuyen a un
  solo parche.
- **Los jugadores necesitan ese parche instalado.** No es un servidor al que te conectas sin
  tocar nada.
- No se pueden crear visuales nuevos sin arte propio: se reutilizan `SpellVisualID` e
  `SpellIconID` existentes (Regeneration reusa el rayo de Drain Mana, etc.).

Esto no rompe el proyecto, pero sí dice que **no es solo trabajo de servidor**.

## 7. Lo que abarata mucho el trabajo restante

La infraestructura para añadir clases ya existe y está documentada:

- `sod-class-templates`: esqueletos copiables para hechizo, runa, ítem, texto localizado y
  configuración, con `<PLACEHOLDER>` y `TODO`.
- Un **generador** (`tools/sod_spells.py`) produce las dos mitades desde una sola definición.
- `docs/pulling-sod-data.md` documenta la receta para sacar valores reales de SoD desde
  **[wago.tools](https://wago.tools)** (DB2 del cliente moderno de Classic Era en CSV), y avisa
  de las dos trampas: los enums de tipo de aura/efecto modernos **difieren** de 3.3.5a, y los
  base points se guardan como valor − 1.

Es decir: **el camino para añadir una clase está trazado y hay un ejemplo completo que seguir
(el mago).** Eso cambia mucho la estimación: no es investigar, es repetir un patrón conocido.
Y es justo el tipo de trabajo acotado y repetitivo que se puede delegar a un ejecutor barato.

Dato llamativo: wago.tools saca los valores del **cliente moderno de Classic Era**. Es decir,
el cliente 1.15.x que no nos servía para emular **sí nos sirve como fuente de datos**, sin
necesidad de suscripción.

## 8. Conclusión y confirmación de la decisión

**Se confirma la opción D**, con el alcance corregido:

- Lo que se hereda: un motor de runas sólido, el pipeline de parcheo de cliente, las plantillas
  y un módulo de clase completo como referencia. Eso es trabajo real ya hecho, y es la parte
  difícil.
- Lo que hay que escribir: **el contenido de ocho clases**, más el balance. No es un fin de
  semana.
- Lo que se asume: mantenimiento propio de `mod-sod`, y que los jugadores instalen un parche
  de cliente.

Nada de esto desaconseja el proyecto; al contrario, se parte de una base mejor de lo que suele
encontrarse. Pero conviene no llamar «instalar SoD» a lo que en realidad es **reimplementar
SoD clase por clase sobre un motor ya construido**.

Propuesta de alcance: **no intentar SoD completo.** Un primer hito realista es
**fase 1 (nivel máximo 25) con dos o tres clases**, partiendo del mago que ya funciona. Eso da
un servidor jugable de verdad y valida el pipeline completo antes de comprometer meses.

## 9. Las cifras de SoD oficial: el esfuerzo por clase

Verificado tras cerrar las secciones anteriores. Esto permite estimar el trabajo con rigor.

### Fase 1 (nivel máximo 25)

- **Tres ranuras de grabado**: pecho, piernas y manos.
- **12 runas por clase**: cuatro por ranura. Nueve clases ⇒ **108 runas en la fase 1**.
- Contenido asociado: raid de **Blackfathom Deeps** (10 jugadores) y el evento PvP
  **Battle for Ashenvale**.

Las 12 del mago, cruzadas con lo que hay implementado en `mod-sod-mage`:

| Ranura | Runas de SoD | Estado en `mod-sod-mage` |
|---|---|---|
| Pecho | Regeneration, Enlightenment | ✅ implementadas |
| Pecho | Fingers of Frost, Burnout | ❌ faltan |
| Manos | Rewind Time, Arcane Blast, Living Bomb | ✅ implementadas |
| Manos | Ice Lance | ❌ falta |
| Piernas | Living Flame, Mass Regeneration, Arcane Surge | ✅ implementadas |
| Piernas | Icy Veins | ❌ falta |

**8 de 12 (67 %) de la fase 1 del mago ya están hechas.** Las cuatro que faltan son de
escarcha; el módulo cubrió el kit arcano y de fuego. Es un hueco pequeño y bien delimitado.

### El conjunto de SoD completo

| Fase | Nivel máx. | Fecha | Runas nuevas por clase |
|---|---|---|---|
| 1 | 25 | 30-11-2023 | 12 (verificado) |
| 2 | 40 | 08-02-2024 | ~6 |
| 3 | 50 | 04-04-2024 | 6 |
| 4 | 60 | 11-07-2024 | + runas de anillo (15, compartidas) |
| 5–8 | 60 | sep. 2024 – abr. 2025 | no verificado |

SoD completo son **8 fases, 18 meses de contenido de Blizzard y 218 runas como mínimo**, más
ocho raids reescaladas (Blackfathom, Gnomeregan, Sunken Temple, Molten Core, BWL, ZG, AQ,
Naxxramas, Scarlet Enclave). Reproducir eso **no es un objetivo realista** para este proyecto, y
conviene decirlo ahora.

### Lo que esto implica para el alcance

El hito de **fase 1 con tres clases** son ~36 runas, de las cuales **8 ya existen**: quedan
**~28 habilidades por implementar**, siguiendo un patrón ya demostrado y con generador. Eso es
un objetivo medible y acotado, no una incógnita.

## 10. Pendiente
- Comprobar que `mod-rune-engraving` compila contra un AzerothCore actual. **No verificado**:
  no tiene `CMakeLists.txt` propio en la raíz, lo que es normal en módulos de AzerothCore, pero
  hay que confirmarlo con un build real.
- Confirmar si los otros cinco módulos de clase están igual de vacíos (asumido, no comprobado).

## 11. Fuentes

- [Warcraft Wiki — Season of Discovery](https://warcraft.wiki.gg/wiki/World_of_Warcraft_Classic:_Season_of_Discovery)
- [Warcraft Tavern — runas de mago en SoD](https://www.warcrafttavern.com/wow-classic/guides/season-of-discovery-mage-rune-engravings/)
  (de aquí salen las tres ranuras de la fase 1 y las 12 runas del mago, cuatro por ranura)
- [Wowhead — guía de runas de SoD](https://www.wowhead.com/classic/guides/season-of-discovery/runes)
- [Wowhead — preview de la fase 3: 6 runas por clase](https://www.wowhead.com/classic/news/season-of-discovery-phase-3-preview-6-runes-per-class-pve-event-8-raid-bosses-338252)
- Repositorios auditados: [github.com/mod-sod](https://github.com/mod-sod), clonados en
  `upstream/azerothcore/mod-sod/`.

Nota de método: Wowhead no se deja leer por scraping (devuelve solo la navegación), así que las
cifras por ranura se tomaron de Warcraft Tavern y **se cruzaron contra el código real** del
módulo, que es la verificación que de verdad importa aquí.
