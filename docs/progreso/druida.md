# Progreso: druida

Estado a 2026-10-18. Druida completo en código (27 runas), **sin compilar ni probar en juego**.

**Fuentes de este documento**
- Nombres de criaturas, objetos y runas en español: base de desarrollo `acore_world_test` (reino 2) y `rune_template_locale`. La base de producción (`acore_world`) aún no tiene el contenido de SoD.
- Qué se implementa y qué no: SQL del módulo en `server/mod-sod-content/data/sql/db-world/base/` (commit `fdf51f4`).
- Probabilidades: las tasas de Wowhead guardadas en `docs/runas/fuentes-sod.json`, las mismas que usa el SQL.
- Lo que no aparece en la base de datos (misiones, Rune Broker, objetos de mundo) figura en inglés y marcado como «sin nombre en BD».

**Leyenda de estado**
- **Botín:** la runa cae de criaturas del servidor.
- **Vendedor:** la compra un NPC real del servidor.
- **Grabador:** se compra al Grabador de runas (sustituto de los Rune Broker). Es la única vía para la mecánica no programada.

---

## 1. Resumen de las 27 runas

| Id | Runa | Ranura | Ítem (id) | Cómo se consigue hoy | Estado |
|---|---|---|---|---|---|
| 7009001 | Crecimiento salvaje | Manos | Runa de Crecimiento salvaje (210137) | Grabador, 1 oro. Real de SoD: misión Trial of the Owls (sin programar) | Grabador |
| 7009002 | Supervivencia del más fuerte | Pecho | Runa de supervivencia (210817) | Grizzby (Ratchet), 3 oro 15 plata 78 cobre | Vendedor |
| 7009003 | Lacerar | Piernas | Runa de Lacerar (208687) | Botín de los Canosos y Correoscuros Furia Lunar, 1,07 % | Botín |
| 7009004 | Rugido salvaje | Piernas | Ídolo de ferocidad (208689) | Botín de Zarparrío y otros, más el Botín de Kolkar | Botín |
| 7009005 | Rabia | Cintura | Runa de Rabia (213117) | Grabador, 1 oro | Grabador |
| 7009006 | Instintos de supervivencia | Pies | Runa de instinto (213119) | Grabador, 1 oro | Grabador |
| 7009007 | Destrozar | Manos | Ídolo de ira osuna (206954) | Botín de 8 criaturas de Mulgore, Thunder Bluff y Teldrassil | Botín |
| 7009008 | Cornada | Cabeza | Runa de Escabechina (221517) | Grabador, 1 oro 60 plata | Grabador |
| 7009009 | Golpes descontrolados | Pecho | Ídolo de las fieras (210534) | Botín de los Tótem Siniestro de Crestagua | Botín |
| 7009010 | Rey de la selva | Pies | Runa del rey de la selva (213118) | Grabador, 1 oro | Grabador |
| 7009011 | Testarazo | Manos | Runa de Testarazo (206992) | Oficiales de suministro (rango 4) y Grabador, 2 oro | Vendedor |
| 7009012 | Regeneración frenética mejorada | Muñecas | Runa de energía primigenia (221516) | Grabador, 1 oro | Grabador |
| 7009013 | Flagelo mejorado | Espalda | Ídolo de la cazadora (227444) | Botín de los Ravasaurio de Un'Goro | Botín |
| 7009014 | Piel de corteza mejorada | Cabeza | Ídolo de arrastrapiés furibundo (220915) | Botín de los Cardizal de Tanaris | Botín |
| 7009015 | Semilla viviente | Pecho | Runa de Potencial natural (206963) | Botín de Espíritu de la naturaleza desatado (206245), 100 % | Botín |
| 7009016 | Vientos galernos | Cabeza | Runa de la tormenta de viento (220754) | Grabador, 1 oro | Grabador |
| 7009017 | Fuego solar | Manos | Runa del Sol (206989) | Grabador, 1 oro | Grabador |
| 7009018 | Furia de Tempestira | Pecho | Ídolo lunar (208414) | Botín de Grellín (4 %, solo druidas) | Botín |
| 7009019 | Estado onírico | Pies | Runa del soñador (213120) | Grabador, 1 oro | Grabador |
| 7009020 | Árbol de la vida | Capa | Runa del Árbol del Mundo (227746) | Grabador, 1 oro | Grabador |
| 7009021 | Oleada de estrellas | Piernas | Runa de las estrellas (210500) | Grabador, 1 oro | Grabador |
| 7009022 | Floración | Muñecas | Runa de Floración (220360) | Grabador, 1 oro | Grabador |
| 7009023 | Fuegos de Elune | Muñecas | Runa de la diosa de la luna (221020) | Grabador, 1 oro | Grabador |
| 7009024 | Eclipse | Cintura | Runa de Eclipse (212548) | Grabador, 1 oro | Grabador |
| 7009025 | Lluvia de estrellas | Espalda | Runa de la estrella fugaz (227749) | Grabador, 1 oro | Grabador |
| 7009026 | Flor de vida | Piernas | Runa de Flor de vida (7009026, propia) | Grabador, 1 oro | Grabador |
| 7009027 | Nutrir | Cintura | Runa de Nutrir (7009027, propia) | Grabador, 1 oro | Grabador |

**Totales:** 8 runas de botín, 2 de vendedor (Testarazo también se vende en el Grabador), 17 solo en el Grabador. Ninguna se consigue por misión.

---

## 2. Botín: criatura por criatura

Probabilidad por muerte de la criatura. Las zonas son los nombres en español del cliente, que no están en la base de datos.

### Lacerar (7009003), ítem Runa de Lacerar (208687)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Canoso Furia Lunar (1769) | Bosque de Argénteos | 1,0661 % | Solo druidas |
| Correoscuro Furia Lunar (1770) | Bosque de Argénteos | 1,0661 % | Solo druidas |
| Almanegra Furia Lunar (1782) | Bosque de Argénteos | 1,0661 % | Solo druidas |
| Aullasangre Furia Lunar (1924) | Bosque de Argénteos | 1,0661 % | Solo druidas |

En SoD estos worgen sueltan un Unbalanced Idol. Aquí sueltan la runa directamente.

### Rugido salvaje (7009004), ítem Ídolo de ferocidad (208689)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Gnoll Zarparrío (117) | Páramo de Poniente | 0,3503 % | Solo druidas |
| Bastardo Zarparrío (123) | Páramo de Poniente | 0,2155 % | Solo druidas |
| Tosco Zarparrío (124) | Páramo de Poniente | 0,4360 % | Solo druidas |
| Bandido Zarparrío (452) | Páramo de Poniente | 0,3433 % | Solo druidas |
| Explorador Zarparrío (500) | Páramo de Poniente | 0,2552 % | Solo druidas |
| Chamán Zarparrío (1065) | Páramo de Poniente | 6,6667 % | Muestra de 1/15 |
| Grimson el Pálido (1972) | Bosque de Argénteos | 1,5936 % | Solo druidas |
| Madre del cubil (6788) | Costa Oscura | 19,7595 % | Solo druidas |
| Botín de Kolkar (objetos 3642, 152608, 152618) | Los Baldíos | 1/3 y 1/4 (25–33,33 %) | Ver nota |

**Nota:** el Botín de Kolkar da 1/3 (33,3333 %) para el objeto 152608, y 1/4 (25 %) para los objetos 3642 y 152618, según las probabilidades reales de SoD.

### Mangle (7009007), ítem Ídolo de ira osuna (206954)

| Criatura (id) | Zona | Probabilidad |
|---|---|---|
| Lobo alfa de pradera (2960) | Mulgore, Cima del Trueno | 0,5054 % |
| Hechicera Viento Furioso (2964) | Mulgore | 0,1638 % |
| Matriarca Viento Furioso (2965) | Mulgore, Cima del Trueno | 0,1474 % |
| Aguilón garrudo (2971) | Mulgore, Cima del Trueno | 0,6246 % |
| Controlador de Ventura y Cía. (2979) | Mulgore | 1,2687 % |
| Intruso Erizapúas (3232) | Mulgore | 1,4916 % |
| Merodeador de las estepas (3566) | Mulgore, Cima del Trueno | 0,3878 % |
| Garrafuria (7318) | Teldrassil | 28,7535 % |

### Golpes descontrolados (7009009), ítem Ídolo de las fieras (210534)

| Criatura (id) | Zona | Probabilidad |
|---|---|---|
| Rufián Tótem Siniestro (11910) | Montañas Crestagua | 2,2115 % |
| Mercenario Tótem Siniestro (11911) | Montañas Crestagua | 2,5397 % |
| Tosco Tótem Siniestro (11912) | Montañas Crestagua | 1,8458 % |
| Hechicero Tótem Siniestro (11913) | Montañas Crestagua | 1,7765 % |

### Flagelo mejorado (7009013), ítem Ídolo de la cazadora (227444)

| Criatura (id) | Zona | Probabilidad |
|---|---|---|
| Ravasaurio (6505) | Cráter de Un'Goro | 1,5504 % |
| Corredor ravasaurio (6506) | Cráter de Un'Goro | 1,7032 % |
| Cazador ravasaurio (6507) | Cráter de Un'Goro | 2,2936 % |
| Ravasaurio pellejo venenoso (6508) | Cráter de Un'Goro | 3,6055 % |

### Piel de corteza mejorada (7009014), ítem Ídolo de arrastrapiés furibundo (220915)

| Criatura (id) | Zona | Probabilidad |
|---|---|---|
| Furibundo de la tierra (5465) | Tanaris | 2,5000 % |
| Colector de rocío Cardizal (5481) | Tanaris | 2,4778 % |
| Enraizador Cardizal (5485) | Tanaris | 5,2720 % |
| Cardizal nudoso (5490) | Tanaris | 4,3365 % |
| Aporreador de tierra (9396) | Tanaris | 1,4354 % |

### Semilla viviente (7009015), ítem Runa de Potencial natural (206963)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Espíritu de la naturaleza desatado (206245) | Mulgore, Teldrassil | 100 % | Solo druidas. Muestra de Wowhead 2/2, sin fiabilidad |

**Nota:** la criatura no existía en el core; la crea `sod_druid_living_seed_source.sql` con dos spawns en Mulgore (mapa 1, (-1972, 116) y (-1965, 106), respawn 300 s). La z no se conoce y el SQL la toma del PNJ de mapa 1 más cercano en distancia plana, así que conviene revisarla en juego. Los dos spawns de Teldrassil no se han añadido porque sus coordenadas no se conocen. El modelo (28980, el ent de «Angry Oak Spirit») es un sustituto stock, no el de SoD.

### Furia de Tempestira (7009018), ítem Ídolo lunar (208414)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Grellín (1989) | Teldrassil | 4 % | Solo druidas. Requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar) |

**Nota:** requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar).

---

## 3. Requisitos de uso de los ídolos

El ídolo no se usa hasta cumplir el requisito. Solo se aplican los que están en el código.

| Ídolo (id) | Runa | Requisito | ¿Se aplica? |
|---|---|---|---|
| Ídolo de ira osuna (206954) | Destrozar | Rabia ≥ 50 en forma de oso durante 60 s seguidos. Si baja, se reinicia | Sí |
| Ídolo de las fieras (210534) | Golpes descontrolados | Curar a 10 bestias distintas | Sí |
| Ídolo de ferocidad (208689) | Rugido salvaje | 20 golpes de sangrado a humanoides | Sí |
| Ídolo de la cazadora (227444) | Flagelo mejorado | Matar 5 objetivos dormidos en forma felina | Sí |
| Ídolo de arrastrapiés furibundo (220915) | Piel de corteza mejorada | Matar 5 enemigos con daño de Naturaleza bajo Piel de corteza | Sí |
| Ídolo lunar (208414) | Furia de Tempestira | Derrotar 6 criaturas afectadas por tu Fuego lunar | Sí |

---

## 4. Vendedores

| Runa | Vendedor (id) | Zona | Precio |
|---|---|---|---|
| Supervivencia del más fuerte (7009002) | Grizzby (211653) | Los Baldíos (Ratchet) | 31578 cobre (3 oro 15 plata 78 cobre) |
| Testarazo (7009011) | Elaine Compton (213077), Jornah (214070), Dokimi (214096), Gishah (214098), Tamelyn Aldridge (214099), Marcy Baker (214101) | Una ciudad cada uno | 2 oro en el Grabador. Los oficiales piden rango de suministro 4 |

---

## 5. Misiones y fuentes de SoD pendientes

**Ninguna misión está programada.** Las misiones están en la base de datos del juego, pero sin nombre en español.

| Runa | Fuente real de SoD | Estado | Cómo se consigue hoy |
|---|---|---|---|
| Crecimiento salvaje | Misión *Trial of the Owls* (78229, nivel 25) | Sin programar | Grabador |
| Nutrir | Misión *The Lost Saplings* (79377, nivel 40) | Sin programar | Grabador |
| Regeneración frenética mejorada | Canje en Rune Broker con el ítem 232454 | Sin programar | Grabador |
| Rey de la selva | Canje en Rune Broker con el ítem 232456. Supply Bag (217014) | Sin programar | Grabador |
| Eclipse | Jewel-Encrusted Box (212553, ~9 % en la muestra) y canje en Rune Broker | Sin programar | Grabador |
| Árbol de la vida | Gift of the Wisp (464128, Felwood) | Sin programar | Grabador |
| Lluvia de estrellas | *Arcterris* (228814, Vallefresco, nivel 58) | Sin programar | Grabador |
| Vientos galernos | *Namida Grimtotem* (222286, Feralas, nivel 43) | Sin programar | Grabador |
| Fuego solar | Lunar Chest (404433, Mulgore y Teldrassil) | Sin programar | Grabador |
| Estado onírico | Blooming Satyrweed (404402, Desolace) | Sin programar | Grabador |
| Floración | Misión *Wisdom of the Guardians* (81924, nivel 50) | Sin programar | Grabador |
| Fuegos de Elune | Evento *Elune's Favor* (446288) | Sin programar | Grabador |
| Cornada | Cuatro intendentes que venden la runa: Falinar (nivel 25, 16000 cobre), Kyleen (nivel 40, 16842), Alandra (nivel 50, 16842), Valdane (nivel 50, 16000) | Sin programar | Grabador |
| Rabia | Rune Broker | Sin programar | Grabador |
| Instintos de supervivencia | Rune Broker y evento *Amaryllis* | Sin programar | Grabador |
| Oleada de estrellas | Rune Broker | Sin programar | Grabador |
| Lifebloom y Nutrir | Objetos propios (7009026 y 7009027). En SoD son 206970 y 213074 | Sin verificar | Grabador |

Los nombres de Rune Broker, de los intendentes y de los objetos de mundo no están en la base de datos. Quedan en inglés.

---

## 6. Cómo comprar en el Grabador hoy

1. `.rune summon`. Cualquier jugador lo puede usar. El Grabador aparece durante 5 minutos.
2. Hablar con el Grabador de runas (npc 700000) y abrir la opción de compra.
3. Comprar el ítem de la runa. Cuesta 1 oro salvo que se indique otro precio.
4. Usar el ítem. Desbloquea la runa y el ítem se consume.
5. Grabar la runa en su ranura desde el Grabador.

---

## 7. Pendiente y limitaciones

- **Sin compilar ni probar.** El druida necesita compilar, desplegar el parche de cliente y probarse en juego.
- **Misiones:** ninguna programada. Las runas de misión se consiguen por el Grabador hasta que se programen.
- **Rune Broker:** no existe en el servidor. El Grabador hace de sustituto.
- **Tasas de Wowhead:** algunas vienen de muestras pequeñas (1/15, 2/2, 1/1).
- **Semilla viviente (7009015):** la criatura es nueva en el core y la crea `sod_druid_living_seed_source.sql`. Su z se calcula con el PNJ de mapa 1 más cercano, así que hay que revisarla en juego. Faltan los dos spawns de Teldrassil (coordenadas desconocidas) y el modelo es un sustituto stock, no el de SoD.
- **Producción:** `acore_world` no tiene el contenido SoD. Hace falta aplicarlo con el despliegue.
- **Documentación desfasada:** [docs/runas/obtencion.md](../runas/obtencion.md) dice que Lacerar, Rugido salvaje, Destrozar, Furia de Tempestira y Supervivencia del más fuerte también se venden en el Grabador. El commit `fdf51f4` los quitó de ahí. Esa tabla tampoco tiene las filas 7009009 a 7009014.

---

## 8. Guía rápida: cómo conseguir cada runa

**Criterios**
- **Muertes esperadas** = 100 / probabilidad. Es el número medio de muertes para conseguir una runa con ese mob. Un mob con pocos spawns tarda más en repetir, aunque tenga muertes esperadas bajas.
- **Nivel recomendado** = rango de nivel del mob, para pelearlo sin dificultad. El ítem o la runa no tienen nivel mínimo en la base de datos (`RequiredLevel` = 1 en todos).
- **Coordenadas** = posición media de los spawns en la base de desarrollo (mapa 0 = Reinos del Este, mapa 1 = Kalimdor). La base no guarda el área, así que la zona es deducida de esas coordenadas.
- **Grabador** (npc 700000): no tiene spawn fijo, lo invoca `.rune summon`. Cualquier nivel.

### 8.1. Qué es lo más fácil por runa

| Runa (id) | Forma más fácil | Zona exacta | Nivel recomendado | Muertes esperadas | Requisito de uso |
|---|---|---|---|---|---|
| Crecimiento salvaje (7009001) | Grabador, 1 oro | Cualquier ciudad con `.rune summon` | Cualquiera | — | — |
| Supervivencia del más fuerte (7009002) | Grizzby, 31578 cobre | Los Baldíos, Ratchet (npc 211653) | Cualquiera | — | — |
| Lacerar (7009003) | Worgen Furia Lunar | Bosque de Argénteos, mapa 0, x 300–1150, y 900–1900 | 10–16 | ~94 (4 mobs, ~119 spawns) | — |
| Rugido salvaje (7009004) | Madre del cubil | Costa Oscura, mapa 1, (6663, -430), spawn único | 18–19 | ~5 (1 spawn) | 20 golpes de sangrado a humanoides |
| Rabia (7009005) | Grabador, 1 oro | — | Cualquiera | — | — |
| Instintos de supervivencia (7009006) | Grabador, 1 oro | — | Cualquiera | — | — |
| Destrozar (7009007) | Rageclaw | Teldrassil, mapa 1, (9843, 1496), spawn único | 10 | ~3,5 (1 spawn) | Rabia ≥ 50 en oso durante 60 s |
| Cornada (7009008) | Grabador, 1 oro 60 plata | — | Cualquiera | — | — |
| Golpes descontrolados (7009009) | Tótem Siniestro Mercenario | Montañas Crestagua, mapa 1, (55, -769) | 14–15 | ~39 (33 spawns) | Curar a 10 bestias distintas |
| Rey de la selva (7009010) | Grabador, 1 oro | — | Cualquiera | — | — |
| Testarazo (7009011) | Grabador, 2 oro | — | Cualquiera | — | — |
| Regeneración frenética mejorada (7009012) | Grabador, 1 oro | — | Cualquiera | — | — |
| Flagelo mejorado (7009013) | Venomhide Ravasaur | Cráter de Un'Goro, mapa 1, (-7254, -1995) | 50–51 | ~28 (22 spawns) | 5 objetivos dormidos muertos en forma felina |
| Piel de corteza mejorada (7009014) | Enraizador Cardizal | Tanaris, mapa 1, (-8888, -2246) | 49–50 | ~19 (11 spawns) | 5 muertes con Naturaleza bajo Piel de corteza |
| Semilla viviente (7009015) | Espíritu de la naturaleza desatado | Mulgore, mapa 1, (-1972, 116) y (-1965, 106) | 7 | 1 (100 %) | — |
| Vientos galernos (7009016) | Grabador, 1 oro | — | Cualquiera | — | — |
| Fuego solar (7009017) | Grabador, 1 oro | — | Cualquiera | — | — |
| Furia de Tempestira (7009018) | Grellín | Teldrassil, mapa 1, (10465, 967) | 3–4 | ~25 (31 spawns) | Derrotar 6 criaturas con Fuego lunar |
| Estado onírico (7009019) | Grabador, 1 oro | — | Cualquiera | — | — |
| Árbol de la vida (7009020) | Grabador, 1 oro | — | Cualquiera | — | — |
| Oleada de estrellas (7009021) | Grabador, 1 oro | — | Cualquiera | — | — |
| Floración (7009022) | Grabador, 1 oro | — | Cualquiera | — | — |
| Fuegos de Elune (7009023) | Grabador, 1 oro | — | Cualquiera | — | — |
| Eclipse (7009024) | Grabador, 1 oro | — | Cualquiera | — | — |
| Lluvia de estrellas (7009025) | Grabador, 1 oro | — | Cualquiera | — | — |
| Flor de vida (7009026) | Grabador, 1 oro | — | Cualquiera | — | — |
| Nutrir (7009027) | Grabador, 1 oro | — | Cualquiera | — | — |

**Recomendación general:** para las 17 runas del Grabador y para Supervivencia del más fuerte, lo más fácil es comprar. Para las de botín, la que menos muertes cuesta es Destrozar (Rageclaw). Como es un spawn único, en la práctica depende de cuánto tarde en repetir (300 s).

### 8.2. Botín: todas las fuentes con su zona y nivel

**Lacerar (7009003)**: Canoso, Correoscuro, Almanegra y Aullasangre Furia Lunar. Mapa 0, Bosque de Argénteos, nivel 10–16. Probabilidad de 1,0661 % cada una. Muertes esperadas de la runa: ~94.

**Rugido salvaje (7009004)**, ítem Ídolo de ferocidad (208689):

| Criatura (id) | Zona exacta | Nivel | Probabilidad | Muertes esperadas | Spawns |
|---|---|---|---|---|---|
| Madre del cubil (6788) | Costa Oscura, mapa 1, (6663, -430) | 18–19 | 19,7595 % | ~5 | 1 |
| Chamán Zarparrío (1065) | Páramo de Poniente, mapa 0, (-9885, 1559) | 12–13 | 6,6667 % | ~15 | 1 |
| Grimson el Pálido (1972) | Bosque de Argénteos, mapa 0, (411, 990) | 15 | 1,5936 % | ~63 | 1 |
| Tosco Zarparrío (124) | Páramo de Poniente | 15–16 | 0,4360 % | ~229 | 26 |
| Gnoll Zarparrío (117) | Páramo de Poniente | 11–12 | 0,3503 % | ~285 | 24 |
| Bandido Zarparrío (452) | Páramo de Poniente | 16–17 | 0,3433 % | ~291 | 40 |
| Explorador Zarparrío (500) | Páramo de Poniente | 12–13 | 0,2552 % | ~392 | 23 |
| Bastardo Zarparrío (123) | Páramo de Poniente | 14 | 0,2155 % | ~464 | 45 |
| Cofres Botín de Kolkar (3642, 152608, 152618) | Los Baldíos, mapa 1 | — | 1/3 (33,33 %) para 152608; 1/4 (25 %) para 3642 y 152618 | ~3–4 | 3 cofres |

**Mangle (7009007)**, ítem Ídolo de ira osuna (206954):

| Criatura (id) | Zona exacta | Nivel | Probabilidad | Muertes esperadas | Spawns |
|---|---|---|---|---|---|
| Garrafuria (7318) | Teldrassil, mapa 1, (9843, 1496) | 10 | 28,7535 % | ~3,5 | 1 |
| Intruso Erizapúas (3232) | Mulgore, mapa 1, (-999, -1099) | 9–10 | 1,4916 % | ~67 | 28 |
| Controlador de Ventura y Cía. (2979) | Mulgore, mapa 1, (-1607, -1077) | 9–10 | 1,2687 % | ~79 | 67 |
| Aguilón garrudo (2971) | Mulgore, mapa 1, (-1123, -651) | 8–10 | 0,6246 % | ~160 | 19 |
| Lobo alfa de pradera (2960) | Mulgore, mapa 1, (-1524, -771) | 9–10 | 0,5054 % | ~198 | 103 |
| Merodeador de las estepas (3566) | Mulgore, mapa 1, (-929, -502) | 9 | 0,3878 % | ~258 | 106 |
| Hechicera Viento Furioso (2964) | Mulgore, mapa 1, (-839, 64) | 9–10 | 0,1638 % | ~611 | 47 |
| Matriarca Viento Furioso (2965) | Mulgore, mapa 1, (-827, 78) | 10–11 | 0,1474 % | ~678 | 47 |

**Golpes descontrolados (7009009)**, ítem Ídolo de las fieras (210534). Todas en Montañas Crestagua, mapa 1:

| Criatura (id) | Coordenadas (media) | Nivel | Probabilidad | Muertes esperadas | Spawns |
|---|---|---|---|---|---|
| Mercenario Tótem Siniestro (11911) | (55, -769) | 14–15 | 2,5397 % | ~39 | 33 |
| Rufián Tótem Siniestro (11910) | (77, -756) | 14–15 | 2,2115 % | ~45 | 17 |
| Hechicero Tótem Siniestro (11913) | (123, -517) | 15–16 | 1,7765 % | ~56 | 17 |
| Tosco Tótem Siniestro (11912) | (114, -498) | 15–16 | 1,8458 % | ~54 | 24 |

**Destrozar (7009007)**: ver la tabla de Mangle arriba.

**Flagelo mejorado (7009013)**, ítem Ídolo de la cazadora (227444). Todas en Cráter de Un'Goro, mapa 1:

| Criatura (id) | Coordenadas (media) | Nivel | Probabilidad | Muertes esperadas | Spawns |
|---|---|---|---|---|---|
| Ravasaurio pellejo venenoso (6508) | (-7254, -1995) | 50–51 | 3,6055 % | ~28 | 22 |
| Cazador ravasaurio (6507) | (-7268, -1934) | 49–50 | 2,2936 % | ~44 | 19 |
| Corredor ravasaurio (6506) | (-7764, -1815) | 49–50 | 1,7032 % | ~59 | 21 |
| Ravasaurio (6505) | (-7753, -1801) | 48–49 | 1,5504 % | ~64 | 38 |

**Piel de corteza mejorada (7009014)**, ítem Ídolo de arrastrapiés furibundo (220915). Todas en Tanaris, mapa 1:

| Criatura (id) | Coordenadas (media) | Nivel | Probabilidad | Muertes esperadas | Spawns |
|---|---|---|---|---|---|
| Enraizador Cardizal (5485) | (-8888, -2246) | 49–50 | 5,2720 % | ~19 | 11 |
| Cardizal nudoso (5490) | (-8889, -2230) | 48–49 | 4,3365 % | ~23 | 8 |
| Colector de rocío Cardizal (5481) | (-8909, -2240) | 47–48 | 2,4778 % | ~40 | 14 |
| Furibundo de la tierra (5465) | (-8361, -3538) | 45–47 | 2,5000 % | ~40 | 5 |
| Aporreador de tierra (9396) | (-7095, -3622) | 41–43 | 1,4354 % | ~70 | 2 |

**Semilla viviente (7009015)**, ítem Runa de Potencial natural (206963): Espíritu de la naturaleza desatado (206245), Mulgore, mapa 1, (-1972, 116) y (-1965, 106), nivel 7, 100 %, ~1 muerte, 2 spawns en Mulgore (300 s de respawn) y 2 más en Teldrassil sin coordenadas conocidas. Solo druidas.

**Furia de Tempestira (7009018)**, ítem Ídolo lunar (208414): Grellín (1989), Teldrassil, mapa 1, (10465, 967), nivel 3–4, 4 %, ~25 muertes, 31 spawns. Requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar).

### 8.3. Vendedores

- **Supervivencia del más fuerte (7009002):** Grizzby (npc 211653), Los Baldíos (Ratchet), 3 oro 15 plata 78 cobre. Sin requisito de nivel en la base.
- **Testarazo (7009011):** 2 oro en el Grabador. También lo venden los seis oficiales de suministro si tienes el rango 4 con su ciudad (Elaine Compton, Jornah, Dokimi, Gishah, Tamelyn Aldridge y Marcy Baker).

### 8.4. Notas sobre el nivel

- Los `spell_dbc` de las runas tienen `BaseLevel` de WotLK (0, 1, 20, 60, 75, 80…) que no sirve como nivel de uso. No he encontrado en el repo un nivel mínimo para usar las runas. Hasta que se confirme en juego, las runas del Grabador son usables a cualquier nivel.
- Los `RequiredLevel` de todos los ítems son 1, salvo el ítem de Supervivencia del más fuerte, que no tiene nivel mínimo en la base (`RequiredLevel` = 1 con precio 31578).
