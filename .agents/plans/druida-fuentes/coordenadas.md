# Coordenadas de spawn de PNJ de SoD (para el druida)

Consulta: 2026-10-18. Fuente única de coordenadas: `https://nether.wowhead.com/classic/tooltip/npc/<id>?dataEnv=4&locale=0` (devuelve porcentajes de mapa; es la capa de datos de Wowhead Classic/SoD). Las páginas `www.wowhead.com/classic/npc=<id>` vía WebFetch solo dan la lista de zonas, sin coordenadas, respawn, modelo ni botín. Pausas de 3 s, sin 403.

Búsqueda de un repositorio público con `creature.sql` de SoD (AzerothCore/CMaNGOS): una búsqueda web no encontró ninguno. **No hay URL ni commit que citar.** En `upstream/azerothcore/mod-sod` no aparece ninguno de estos ids.

## Conversión a coordenadas de mundo (3.3.5a)

Método: límites de `WorldMapArea.dbc` de `/home/stark/Servers/acore-test/data/dbc/` (solo lectura). `x = Top + (Bottom-Top)·y%/100`, `y = Left + (Right-Left)·x%/100` (x del mundo corresponde al % vertical). Comprobado con un caso conocido (Darkshire a ~73,44 % sale ~(-10509,-1138), real ~(-10517,-1140)). Límites usados: Mulgore (area 215, mapa 1), Feralas 357 (1), Winterspring 618 (1), Duskwood 10 (0), Ashenvale 331 (1), Hinterlands 47 (0).
Limitaciones: la **z no se puede obtener** de un porcentaje (no verificado; habría que leerla de un PNJ cercano de la BD o in-game). El mapa de zona de SoD es el mismo que el de WotLK para estas zonas, pero la precisión es de unos pocos metros, valores redondeados al metro. Mapa 1 = Kalimdor, 0 = Reinos del Este.

## Resultados

Campos no consultables (respawn, modelo, flags de facción en BD, inmunidades): **no verificado** salvo lo indicado.

### Unleashed Nature Spirit (206245)
- Nivel 7, Elemental, no élite.
- Zonas: Mulgore y Teldrassil (2 spawns listados en cada una, según la página de Wowhead).
- Mulgore (el tooltip solo devuelve esta zona): (37.6, 49.6) y (37.8, 49.4) % -> mapa 1, x=-1972, y=116 y x=-1965, y=106. Z no verificado.
- Teldrassil: **coordenadas no obtenidas** (el tooltip no devuelve la segunda zona). No verificado.
- Botín: Rune of Natural Potential (206963, runa Living Seed) 2/2 en la muestra de Wowhead (~100 %, muestra mínima). Vende: nada consta.
- Facción/amistad, respawn, modelo: no verificado.

### Namida Grimtotem (222286)
- Nivel 43, Humanoide, **élite**. Feralas.
- Spawns (%): (66.4,38.4), (66.6,38.2), (66.8,38.6) -> mapa 1, aprox. x=-4146, y=827 / x=-4137, y=813 / x=-4155, y=799. Z no verificado.
- Botín: Rune of the Windstorm (220754, Gale Winds) 1/1 en la muestra (no es porcentaje fiable).
- Facción (Grimtotem, hostil al jugador es una suposición), respawn, modelo: no verificado.

### Arcterris (228814)
- Nivel **58** según el tooltip de Wowhead (otras guías dicen 59), Bestia, **élite**. Winterspring.
- 10 puntos listados (patrulla o área, no un único spawn): (62,18), (63.2,17.4), (63.2,17.6), (63.4,16), (63.6,17.8), (63.8,16.4), (63.8,16.6), (64.6,18.2), (65,18.8), (65.2,20.4). Convertido: del punto (62,18) -> x=7681, y=-4719; (63.4,16) -> x=7776, y=-4818; (65.2,20.4) -> x=7568, y=-4946. Centro aproximado (63.7,17.7) -> x~7700, y~-4860, mapa 1. Z no verificado.
- Botín: Rune of the Falling Star (227749, Starfall) 2/3 en la muestra. Familia de bestia, modelo, respawn: no verificado.
- Contexto de guías (Warcraft Tavern, vía `fuentes.md`): Hidden Grove, ~63,18; recomendable grupo.

### Intendentes de Gore (objeto 221517, Rune of Bloodshed, SoD Phase 3, ilvl 50, liga al recoger, solo druida)
Todos: Humanoide, no élite, facción de reputación **Emerald Wardens** (según el tooltip). Precios del campo `cost` de Wowhead (en cobre, supuesto no confirmado). El «nivel» de abajo es el del PNJ; el requisito de nivel/reputación para comprar **no verificado** (los datos solo traen el nivel del PNJ).

| Id | Nombre | Nivel | Zona (mapa) | % mapa | Mundo aprox. (x, y) | Precio runa |
|---|---|---|---|---|---|---|
| 222684 | Quartermaster Falinar | 25 | Duskwood (0) | (45.6,51.2), (46.8,47.6) | (-10638, -398), (-10574, -430) | 16000 (1g 60s) |
| 222685 | Quartermaster Kyleen | 40 | Ashenvale (1) | (89.4,40.6), (89.6,40.4), (89.6,40.6) | (3112, -3455), (3120, -3467) | 16842 (1g 68s 42c) |
| 222686 | Quartermaster Alandra | 50 | Hinterlands (0) | (61.4,34.4), (61.4,34.6) | (584, -3939) | 16842 |
| 222687 | Quartermaster Valdane | 50 | Feralas (1) | (48.4,12.4), (48.4,12.6), (48.6,12.4), (48.6,12.6) | (-2941, 2078), (-2951, 2064) | 16000 |

Dos spawns por intendente en Falinar son dos puntos distintos (~60 m de separación): puede ser un cambio de posición por fase u hora; no verificado. Z, respawn, modelo, otros artículos que venden: no verificado.

## No verificado (resumen)
- Z de todos los puntos; respawn; modelo; flags de facción reales.
- Coordenadas de Teldrassil del Unleashed Nature Spirit.
- Requisito de nivel/reputación de los intendentes y la unidad del precio.
- Existencia de un repositorio público con `creature.sql` de SoD (no encontrado).

## Unleashed Nature Spirit en Teldrassil

Consulta: 2026-10-18. Fuente: HTML de `https://www.wowhead.com/classic/npc=206245` (con `curl -L` y User-Agent de navegador; WebFetch no ve el JSON). Contiene `mapperData = {"141":[{"count":2,"coords":[[67,58],[67,58.6]],"uiMapId":1438,"uiMapName":"Teldrassil"}],"215":[{...Mulgore: [37.6,49.6],[37.8,49.4]}]}`, coherente con los datos de Mulgore ya recogidos. El endpoint `nether.wowhead.com/.../tooltip/npc/206245` solo devuelve Mulgore con `dataEnv=0` y `Entity not found` con `dataEnv` 1, 2, 3 y 5 (el 4 ya se probó antes).

- Teldrassil (WorldMapArea area 141, mapa 1): (67, 58) % y (67, 58.6) %.
- Mundo (mapa 1), con límites del DBC (Left 3814.58, Right -1277.08, Top 11831.25, Bottom 8437.5) y el mismo método de arriba: **(x=9863, y=403)** y **(x=9843, y=403)**. Z no verificado. Los dos puntos están a ~20 m uno del otro.
- Verosimilitud: no comprobado contra un PNJ conocido de esa zona; solo se aplicó la misma fórmula que en el resto de entradas.
- La guía de Warcraft Tavern probada (URL adivinada) dio 404; no se contrastó con guías.
