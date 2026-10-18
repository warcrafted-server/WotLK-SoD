# Progreso: druida

Estado a 2026-10-18. Druida completo en código (27 runas), **sin compilar ni probar en juego**.

**Fuentes de este documento**
- Nombres de criaturas, objetos y runas en español: base de desarrollo `acore_world_test` (reino 2) y `rune_template_locale`. La base de producción (`acore_world`) aún no tiene el contenido de SoD.
- Qué se implementa y qué no: SQL del módulo en `server/mod-sod-content/data/sql/db-world/base/` (commit `fdf51f4`).
- Probabilidades: las tasas de Wowhead guardadas en `docs/runas/fuentes-sod.json`, las mismas que usa el SQL.
- Lo que no aparece en la base de datos (misiones, objetos de mundo) figura en inglés y marcado como «sin nombre en BD».

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
| 7009005 | Rabia | Cintura | Runa de Rabia (213117) | Corredor de runas (seis capitales), 1 oro | Vendedor |
| 7009006 | Instintos de supervivencia | Pies | Runa de instinto (213119) | Grabador, 1 oro | Grabador |
| 7009007 | Destrozar | Manos | Ídolo de ira osuna (206954) | Botín de 8 criaturas de Mulgore, Thunder Bluff y Teldrassil | Botín |
| 7009008 | Cornada | Cabeza | Runa de Escabechina (221517) | Intendentes (Falinar, Kyleen, Alandra y Valdane), 1 oro 60 plata | Vendedor |
| 7009009 | Golpes descontrolados | Pecho | Ídolo de las fieras (210534) | Botín de los Tótem Siniestro de Crestagua | Botín |
| 7009010 | Rey de la selva | Pies | Runa del rey de la selva (213118) | Grabador, 1 oro | Grabador |
| 7009011 | Testarazo | Manos | Runa de Testarazo (206992) | Oficiales de suministro (rango 4) y Grabador, 2 oro | Vendedor |
| 7009012 | Regeneración frenética mejorada | Muñecas | Runa de energía primigenia (221516) | Corredor de runas (seis capitales), 1 oro | Vendedor |
| 7009013 | Flagelo mejorado | Espalda | Ídolo de la cazadora (227444) | Botín de los Ravasaurio de Un'Goro | Botín |
| 7009014 | Piel de corteza mejorada | Cabeza | Ídolo de arrastrapiés furibundo (220915) | Botín de los Cardizal de Tanaris | Botín |
| 7009015 | Semilla viviente | Pecho | Runa de Potencial natural (206963) | Botín de Espíritu de la naturaleza desatado (206245), 100 % | Botín |
| 7009016 | Vientos galernos | Cabeza | Runa de la tormenta de viento (220754) | Botín de Namida Tótem Siniestro (222286), 100 % | Botín |
| 7009017 | Fuego solar | Manos | Runa del Sol (206989) | Grabador, 1 oro | Grabador |
| 7009018 | Furia de Tempestira | Pecho | Ídolo lunar (208414) | Botín de Grellín (4 %, solo druidas) | Botín |
| 7009019 | Estado onírico | Pies | Runa del soñador (213120) | Grabador, 1 oro | Grabador |
| 7009020 | Árbol de la vida | Capa | Runa del Árbol del Mundo (227746) | Grabador, 1 oro | Grabador |
| 7009021 | Oleada de estrellas | Piernas | Runa de las estrellas (210500) | Grabador, 1 oro | Grabador |
| 7009022 | Floración | Muñecas | Runa de Floración (220360; el Grabador la sigue vendiendo) | Misión *Wisdom of the Guardians* (81924, §10) | Misión |
| 7009023 | Fuegos de Elune | Muñecas | Runa de la diosa de la luna (221020) | Grabador, 1 oro | Grabador |
| 7009024 | Eclipse | Cintura | Runa de Eclipse (212548) | Grabador, 1 oro | Grabador |
| 7009025 | Lluvia de estrellas | Espalda | Runa de la estrella fugaz (227749) | Botín de Arcterris (228814), 66,67 % | Botín |
| 7009026 | Flor de vida | Piernas | Runa de Flor de vida (7009026, propia) | Grabador, 1 oro | Grabador |
| 7009027 | Nutrir | Cintura | Runa de Nutrir (213074, real de SoD; el Grabador sigue vendiendo la 7009027 propia) | Cadena de misión *The Lost Ancient* (79348) y *The Lost Saplings* (79377) | Misión |

**Totales:** 10 runas de botín, 5 de vendedor (Testarazo también se vende en el Grabador), 10 solo en el Grabador y 2 por misión (Nutrir §9 y Floración §10).

**Pruebas:** por decisión del usuario, el Grabador sigue vendiendo todas las runas de druida aunque ya tengan fuente real (las filas están al final de `sod_druid_acquisition.sql`). Cuando acaben las pruebas se vuelven a quitar las que tengan fuente real; la columna «Cómo se consigue hoy» describe la fuente real, no el Grabador.

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

**Nota:** la criatura no existía en el core; la crea `sod_druid_living_seed_source.sql` con dos spawns en Mulgore (mapa 1, (-1972, 116) y (-1965, 106)) y dos en Teldrassil ((9863, 403) y (9843, 403)), respawn 300 s. La z no se conoce y el SQL la toma del PNJ de mapa 1 más cercano en distancia plana, así que conviene revisarla en juego. El modelo (28980, el ent de «Angry Oak Spirit») es un sustituto stock, no el de SoD.

### Vientos galernos (7009016), ítem Runa de la tormenta de viento (220754)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Namida Tótem Siniestro (222286) | Feralas | 100 % | Solo druidas. Nivel 43, élite. Muestra de Wowhead 1/1, sin fiabilidad |

**Nota:** la criatura no existía en el core; la crea `sod_druid_gale_winds_source.sql`. Su plantilla copia los valores de «Grimtotem Shaman» (7727, nivel 43-44, humanoide, facción 16, mismo campamento) y su modelo (6833) es un sustituto stock, no el de SoD. Wowhead lista tres puntos de Feralas ((-4146, 827), (-4137, 813) y (-4155, 799)) que son la misma criatura patrullando: se ha creado un solo spawn en el primero (guid 8820020, respawn 3600 s) y no se ha inventado la ruta. La z no se conoce y el SQL la toma del PNJ de mapa 1 más cercano en distancia plana, así que conviene revisarla en juego.

### Furia de Tempestira (7009018), ítem Ídolo lunar (208414)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Grellín (1989) | Teldrassil | 4 % | Solo druidas. Requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar) |

**Nota:** requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar).

### Lluvia de estrellas (7009025), ítem Runa de la estrella fugaz (227749)

| Criatura (id) | Zona | Probabilidad | Nota |
|---|---|---|---|
| Arcterris (228814) | Vallefresno | 66,67 % | Solo druidas. Nivel 58, élite. Muestra de Wowhead 2/3, sin fiabilidad |

**Nota:** la criatura no existía en el core; la crea `sod_druid_starfall_source.sql`. Su plantilla copia los valores de «Elder Shardtooth» (7445, nivel 57-58, bestia, facción 16, mismo Vallefresno) y su modelo (8837, un oso) es un sustituto stock, no el de SoD. Wowhead lista diez puntos de Vallefresno repartidos en algo más de 200 m alrededor de (7700, -4860) que son la misma criatura patrullando o cubriendo una zona: se ha creado un solo spawn en ese centro (guid 8820030, respawn 3600 s por ser élite) y no se ha inventado la ruta. La z no se conoce y el SQL la toma del PNJ de mapa 1 más cercano en distancia plana, así que conviene revisarla en juego.

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
| Cornada (7009008) | Falinar (222684) | Bosque del Ocaso | 16000 cobre (1 oro 60 plata) |
| Cornada (7009008) | Kyleen (222685) | Vallefresno | 16842 cobre en Wowhead, sin confirmar la unidad; en el core 16000 |
| Cornada (7009008) | Alandra (222686) | Tierras del Interior | 16842 cobre en Wowhead, sin confirmar la unidad; en el core 16000 |
| Cornada (7009008) | Valdane (222687) | Feralas | 16000 cobre (1 oro 60 plata) |
| Rabia (7009005) | Corredor de runas (700201) | Una en cada capital (seis) | 1 oro |
| Regeneración frenética mejorada (7009012) | Corredor de runas (700201) | Una en cada capital (seis) | 1 oro; Wowhead pide 1 emblema (232454) |

Los cuatro intendentes de Cornada son de la facción Guardianes Esmeralda. El core no permite precios distintos por vendedor, así que los cuatro cobran el precio único del ítem (16000 cobre) y la diferencia de 842 cobre de Kyleen y Alandra queda sin efecto.

El Corredor de runas (`sod_world_rune_broker.sql`) es un solo PNJ (700201) con seis spawns, uno en cada capital, a 4 yardas del oficial de suministros de esa ciudad. En SoD vende desde la fase 6 a 1 cobre; aquí cuesta 1 oro por decisión del usuario (lo dice una guía de 2024, sin URL en el repositorio), y el core cobra el `BuyPrice` del ítem: las dos runas van a 1 cobre. Aquí solo vende las runas de las que no tenemos otra fuente real; cada clase irá añadiendo las suyas con filas de `npc_vendor` del entry 700201. Para Regeneración frenética mejorada, Wowhead no da cobre sino 1 unidad del ítem 232454 (Emblem of the Wild Gods), que no existe en este core: la contradicción entre la guía y Wowhead queda sin resolver.

---

## 5. Misiones y fuentes de SoD pendientes

**Dos cadenas de misión están programadas**: Nutrir (§9) y Floración (§10, aún no completable). El resto sigue sin programar; sus misiones están en la base de datos del juego, pero sin nombre en español.

| Runa | Fuente real de SoD | Estado | Cómo se consigue hoy |
|---|---|---|---|
| Crecimiento salvaje | Misión *Trial of the Owls* (78229, nivel 25) | Sin programar | Grabador |
| Rey de la selva | Canje en Rune Broker con el ítem 232456. Supply Bag (217014) | Sin programar | Grabador |
| Eclipse | Jewel-Encrusted Box (212553, ~9 % en la muestra) y canje en Rune Broker | Sin programar | Grabador |
| Árbol de la vida | Gift of the Wisp (464128, Felwood) | Sin programar | Grabador |
| Fuego solar | Lunar Chest (404433, Mulgore y Teldrassil) | Sin programar | Grabador |
| Estado onírico | Blooming Satyrweed (404402, Desolace) | Sin programar | Grabador |
| Fuegos de Elune | Evento *Elune's Favor* (446288) | Sin programar | Grabador |
| Instintos de supervivencia | Rune Broker y evento *Amaryllis* | Sin programar | Grabador |
| Oleada de estrellas | Rune Broker | Sin programar | Grabador |
| Flor de vida (Lifebloom) | Objeto propio (7009026). En SoD es 206970 | Sin verificar | Grabador |

Los nombres de los objetos de mundo no están en la base de datos. Quedan en inglés.

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
- **Misiones:** Nutrir (7009027) ya tiene su cadena programada (§9) y Floración (7009022) las partes A a C (§10). Las demás runas de misión se consiguen por el Grabador hasta que se programen.
- **Rune Broker:** existe desde este cambio como «Corredor de runas» (npc 700201, `sod_world_rune_broker.sql`), con un spawn en cada capital. Hoy solo vende Rabia y Regeneración frenética mejorada, las dos runas de las que no tenemos otra fuente real; para las demás fuentes que Wowhead atribuye al Rune Broker, el Grabador sigue haciendo de sustituto.
- **Tasas de Wowhead:** algunas vienen de muestras pequeñas (1/15, 2/2, 1/1).
- **Semilla viviente (7009015):** la criatura es nueva en el core y la crea `sod_druid_living_seed_source.sql`. Su z se calcula con el PNJ de mapa 1 más cercano, así que hay que revisarla en juego. Las coordenadas de Teldrassil vienen de Wowhead convertidas con `WorldMapArea.dbc`, sin contrastar con un PNJ conocido. El modelo es un sustituto stock, no el de SoD.
- **Vientos galernos (7009016):** la criatura es nueva en el core y la crea `sod_druid_gale_winds_source.sql`. Su z se calcula con el PNJ de mapa 1 más cercano, así que hay que revisarla en juego. De los tres puntos de Wowhead solo se ha creado uno (el PNJ patrulla y la ruta no se conoce) y el modelo es un sustituto stock, no el de SoD.
- **Lluvia de estrellas (7009025):** la criatura es nueva en el core y la crea `sod_druid_starfall_source.sql`. Su z se calcula con el PNJ de mapa 1 más cercano, así que hay que revisarla en juego. De los diez puntos de Wowhead solo se ha creado uno (el PNJ patrulla o cubre una zona y la ruta no se conoce), el modelo es un sustituto stock y el botín sale del 66,67 % de una muestra de 2/3, sin fiabilidad.
- **Nutrir (7009027):** la cadena es nueva en el core y la crea `sod_druid_nourish_source.sql` (PNJ 216310, 216289, 216437, 216445, 216448 y 216451, misiones 79348 y 79377 y objetos 212693, 213036 y 213074, todos ids reales de SoD). Su z se calcula con el PNJ del mismo mapa más cercano, así que hay que revisarla en juego. Los modelos (5849, 1460 y 9590) son sustitutos stock, la probabilidad de botín del 100 % es una suposición, la XP y la unidad del dinero no están verificadas y el crédito de misión lo da un C++ propio. Detalle en §9.
- **Cornada (7009008):** los cuatro intendentes son PNJ nuevos y los crea `sod_druid_gore_source.sql`. Su z se calcula con el PNJ del mismo mapa más cercano, así que hay que revisarla en juego. El subnombre «Quartermaster» y el modelo (una elfa de la noche stock, la de Jaeana) son suposiciones razonables: Wowhead no da el subnombre exacto y el modelo de SoD no está en 3.3.5a. Wowhead da precios distintos por intendente (16000 y 16842 cobre, sin confirmar la unidad) y el core solo admite el precio del ítem: la diferencia de 842 cobre no se aplica. El requisito de nivel de compra no está verificado y no se ha inventado.
- **Rabia (7009005) y Regeneración frenética mejorada (7009012):** el Corredor de runas es un PNJ nuevo y lo crea `sod_world_rune_broker.sql`: un solo `creature_template` (700201, nivel 60, facción 35) y seis spawns a 4 yardas del oficial de suministros de cada capital, con la z y la orientación de ese oficial. Hay que revisar las seis posiciones en juego (`.npc move`). El modelo es un sustituto stock (7099, el mercader goblin de Grizzby), no el de SoD. Precio: 1 oro para las dos por decisión del usuario (el vendedor cobra el `BuyPrice` del ítem), pero Wowhead solo da ese «1» para Rabia: para Regeneración frenética mejorada pide 1 unidad del ítem 232454 (Emblem of the Wild Gods), que no existe en el core. La contradicción con la guía de 2024 (1 cobre desde la fase 6) queda sin resolver.
- **Producción:** `acore_world` no tiene el contenido SoD. Hace falta aplicarlo con el despliegue.
- **Documentación desfasada:** [docs/runas/obtencion.md](../runas/obtencion.md) dice que Lacerar, Rugido salvaje, Destrozar, Furia de Tempestira y Supervivencia del más fuerte también se venden en el Grabador. El commit `fdf51f4` los quitó de ahí. Esa tabla tampoco tiene las filas 7009009 a 7009014, y sigue dando Rabia (7009005) y Regeneración frenética mejorada (7009012) como compra en el Grabador cuando ya las vende el Corredor de runas a 1 cobre.

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
| Rabia (7009005) | Corredor de runas, 1 oro | Una en cada capital, junto al oficial de suministros (mapas 0 y 1) | Cualquiera | — | — |
| Instintos de supervivencia (7009006) | Grabador, 1 oro | — | Cualquiera | — | — |
| Destrozar (7009007) | Rageclaw | Teldrassil, mapa 1, (9843, 1496), spawn único | 10 | ~3,5 (1 spawn) | Rabia ≥ 50 en oso durante 60 s |
| Cornada (7009008) | Falinar (intendente) | Bosque del Ocaso, mapa 0, (-10638, -398); Kyleen: Vallefresno, mapa 1, (3112, -3455); Alandra: Tierras del Interior, mapa 0, (584, -3939); Valdane: Feralas, mapa 1, (-2941, 2078) | Cualquiera | — | — |
| Golpes descontrolados (7009009) | Tótem Siniestro Mercenario | Montañas Crestagua, mapa 1, (55, -769) | 14–15 | ~39 (33 spawns) | Curar a 10 bestias distintas |
| Rey de la selva (7009010) | Grabador, 1 oro | — | Cualquiera | — | — |
| Testarazo (7009011) | Grabador, 2 oro | — | Cualquiera | — | — |
| Regeneración frenética mejorada (7009012) | Corredor de runas, 1 oro | Una en cada capital, junto al oficial de suministros (mapas 0 y 1) | Cualquiera | — | — |
| Flagelo mejorado (7009013) | Venomhide Ravasaur | Cráter de Un'Goro, mapa 1, (-7254, -1995) | 50–51 | ~28 (22 spawns) | 5 objetivos dormidos muertos en forma felina |
| Piel de corteza mejorada (7009014) | Enraizador Cardizal | Tanaris, mapa 1, (-8888, -2246) | 49–50 | ~19 (11 spawns) | 5 muertes con Naturaleza bajo Piel de corteza |
| Semilla viviente (7009015) | Espíritu de la naturaleza desatado | Mulgore, mapa 1, (-1972, 116) y (-1965, 106); Teldrassil, (9863, 403) y (9843, 403) | 7 | 1 (100 %) | — |
| Vientos galernos (7009016) | Namida Tótem Siniestro | Feralas, mapa 1, (-4146, 827) | 43 (élite) | 1 (100 %) | — |
| Fuego solar (7009017) | Grabador, 1 oro | — | Cualquiera | — | — |
| Furia de Tempestira (7009018) | Grellín | Teldrassil, mapa 1, (10465, 967) | 3–4 | ~25 (31 spawns) | Derrotar 6 criaturas con Fuego lunar |
| Estado onírico (7009019) | Grabador, 1 oro | — | Cualquiera | — | — |
| Árbol de la vida (7009020) | Grabador, 1 oro | — | Cualquiera | — | — |
| Oleada de estrellas (7009021) | Grabador, 1 oro | — | Cualquiera | — | — |
| Floración (7009022) | Cadena de misión *Wisdom of the Guardians* | Tyrisius: Feralas, mapa 1, (-5564, 1466); los avatares los invocan los santuarios de Feralas y Tierras del Interior (Azshara, sin programar) | 45–50 | — | — |
| Fuegos de Elune (7009023) | Grabador, 1 oro | — | Cualquiera | — | — |
| Eclipse (7009024) | Grabador, 1 oro | — | Cualquiera | — | — |
| Lluvia de estrellas (7009025) | Arcterris | Vallefresno, mapa 1, (7700, -4860) | 58 (élite) | ~1,5 (66,67 %) | — |
| Flor de vida (7009026) | Grabador, 1 oro | — | Cualquiera | — | — |
| Nutrir (7009027) | Cadena de misión *The Lost Ancient* → *The Lost Saplings* | Rotting Ancient: Marisma de Dustwallow, mapa 1, (-3521, -3180); entrega en Orokai: Claro de la Luna, mapa 1, (7820, -2342) | 26–40 | — | — |

**Recomendación general:** para las 10 runas del Grabador, y para Supervivencia del más fuerte, Cornada y las dos del Corredor de runas, lo más fácil es comprar. Para las de botín, la que menos muertes cuesta es Destrozar (Rageclaw). Como es un spawn único, en la práctica depende de cuánto tarde en repetir (300 s).

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

**Semilla viviente (7009015)**, ítem Runa de Potencial natural (206963): Espíritu de la naturaleza desatado (206245), Mulgore, mapa 1, (-1972, 116) y (-1965, 106), nivel 7, 100 %, ~1 muerte, 2 spawns en Mulgore y 2 en Teldrassil (300 s de respawn, (9863, 403) y (9843, 403)). Solo druidas.

**Vientos galernos (7009016)**, ítem Runa de la tormenta de viento (220754): Namida Tótem Siniestro (222286), Feralas, mapa 1, (-4146, 827), nivel 43 (élite), 100 %, ~1 muerte, 1 spawn (los tres puntos de Wowhead son la misma criatura patrullando), 3600 s de respawn. Solo druidas. Muestra de Wowhead 1/1, sin fiabilidad.

**Furia de Tempestira (7009018)**, ítem Ídolo lunar (208414): Grellín (1989), Teldrassil, mapa 1, (10465, 967), nivel 3–4, 4 %, ~25 muertes, 31 spawns. Requisito de uso aplicado (derrotar a 6 criaturas afectadas por tu Fuego lunar).

**Lluvia de estrellas (7009025)**, ítem Runa de la estrella fugaz (227749): Arcterris (228814), Vallefresno, mapa 1, (7700, -4860), nivel 58 (élite), 66,67 %, ~1,5 muertes, 1 spawn (los diez puntos de Wowhead son la misma criatura patrullando o cubriendo una zona), 3600 s de respawn. Solo druidas. Muestra de Wowhead 2/3, sin fiabilidad.

### 8.3. Vendedores

- **Supervivencia del más fuerte (7009002):** Grizzby (npc 211653), Los Baldíos (Ratchet), 3 oro 15 plata 78 cobre. Sin requisito de nivel en la base.
- **Testarazo (7009011):** 2 oro en el Grabador. También lo venden los seis oficiales de suministro si tienes el rango 4 con su ciudad (Elaine Compton, Jornah, Dokimi, Gishah, Tamelyn Aldridge y Marcy Baker).
- **Cornada (7009008):** 1 oro 60 plata (16000 cobre). La venden cuatro intendentes de los Guardianes Esmeralda: Falinar (npc 222684, Bosque del Ocaso), Kyleen (222685, Vallefresno), Alandra (222686, Tierras del Interior) y Valdane (222687, Feralas). Wowhead da 16842 cobre para Kyleen y Alandra, sin confirmar la unidad, pero el core no permite precios distintos por vendedor: los cuatro cobran el precio único del ítem (16000).
- **Rabia (7009005) y Regeneración frenética mejorada (7009012):** 1 oro (en SoD, 1 cobre). Las vende el Corredor de runas (npc 700201) en las seis capitales, a 4 yardas del oficial de suministros. Wowhead recoge el coste de Rabia como «1», pero para Regeneración frenética mejorada pide 1 unidad del ítem 232454 (Emblem of the Wild Gods), que no existe en el core; la contradicción queda anotada en `sod_world_rune_broker.sql`.

### 8.4. Notas sobre el nivel

- Los `spell_dbc` de las runas tienen `BaseLevel` de WotLK (0, 1, 20, 60, 75, 80…) que no sirve como nivel de uso. No he encontrado en el repo un nivel mínimo para usar las runas. Hasta que se confirme en juego, las runas del Grabador son usables a cualquier nivel.
- Los `RequiredLevel` de todos los ítems son 1, salvo el ítem de Supervivencia del más fuerte, que no tiene nivel mínimo en la base (`RequiredLevel` = 1 con precio 31578).

---

## 9. Cadena de misión de Nutrir (7009027)

Implementada en `server/mod-sod-content/data/sql/db-world/base/sod_druid_nourish_source.sql` y `src/druid/spell_sod_druid_water_of_eluneara.cpp`. Datos y textos: `.agents/plans/druida-fuentes/misiones.md` §2. Sin compilar ni probar en juego.

1. **Rotting Ancient** (216310, nivel 40, Marisma de Dustwallow, mapa 1, (-3521, -3180), respawn 600 s) suelta la **Rotten Seed** (212693) solo a druidas, al 100 % (la probabilidad real no consta).
2. La semilla inicia **The Lost Ancient** (79348, nivel 40, mínimo 26; 1550 XP), que se entrega a **Orokai** (216289, Claro de la Luna, mapa 1, (7820, -2342)).
3. Orokai da **The Lost Saplings** (79377, tiempo 1 h): con el **Water of Elune'ara** (213036) hay que regar los cuatro Ancient Saplings en los Reinos del Este: Winter 216437 (Montañas de Alterac, (682, -857)), Fall 216451 (Tierras Altas de Arathi, (-1852, -2551)), Spring 216445 (Pantano de las Penas, (-10211, -2480)) y Summer 216448 (Vega de Tuercespina, (-13934, 141)). Recompensa: **Rune of Nourishing** (213074), que desbloquea la runa 7009027, y XP aproximada a 3150.
4. La z de todos los spawns sale del PNJ más cercano del mismo mapa y debe revisarse en juego. Dinero de recompensa: 0 (la unidad del dato de SoD, 50, no consta).
5. No verificado: probabilidad de la semilla, si el agua la da Orokai o se recoge en el lago (Wowhead y la wiki dicen lo primero; una guía, lo segundo), y el modelo de cada criatura (stock).

## 10. Misión de Floración (7009022)

Datos y textos: `.agents/plans/druida-fuentes/misiones.md` §3. Sin compilar ni probar en juego.

- **Parte A (Tyrisius y las plantillas):** `server/mod-sod-content/data/sql/db-world/base/sod_druid_efflorescence_source.sql`, la misión 81924, los tres avatares, los tres espíritus y los tres santuarios sin lógica todavía.
- **Parte B (lógica de un santuario):** solo el Shrine of the Warden de Feralas, en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_warden.sql` y `src/druid/spell_sod_druid_shrine_warden.cpp` (registrado en `src/sod_content_loader.cpp`).
- **Parte C (lógica de un santuario):** solo el Shrine of the Moon de Tierras del Interior, en `src/druid/spell_sod_druid_shrine_moon.cpp` (registrado en `src/sod_content_loader.cpp`) y, en el SQL, la frase del libro en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_moon.sql`.
- **Parte D (lógica de un santuario):** solo el Shrine of the Beast de Azshara, en `src/druid/spell_sod_druid_shrine_beast.cpp` (registrado en `src/sod_content_loader.cpp`) y, en el SQL, la frase del libro en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_beast.sql`.

**La misión ya es completable en teoría**: los tres santuarios tienen lógica (Feralas, Tierras del Interior y Azshara). Sigue **sin compilar ni probar en juego**.

### Parte A: Tyrisius y las plantillas

1. **Tyrisius** (221985, nivel 40, Feralas, mapa 1, (-5564, 1466), respawn 300 s) da y entrega **Wisdom of the Guardians** (81924, nivel 50, mínimo 45, categoría Druida, sin misión previa). XP aproximada a 4700: se usa el índice 4 de QuestXP.dbc de nivel 50 (5100), una aproximación de +400. Dinero 0 (la unidad del dato de SoD, 75, no consta).
2. Objetivos (crédito de muerte, 1 de cada): **Treant Avatar** (221935, Feralas), **Moonkin Avatar** (221933, Tierras del Interior) y **Hippogryph Avatar** (221928, Azshara). Nivel 50, no élite y hostiles. **No tienen spawn**: los invoca su santuario.
3. **Santuarios**: Shrine of the Warden (441948, Feralas, mapa 1, (-4785, 1369)), Shrine of the Moon (441946, Tierras del Interior, mapa 0, (104, -4124)) y Shrine of the Beast (441947, Azshara, mapa 1, (3685, -5032)). Son objetos interactivos, con el ScriptName ya puesto (`sod_druid_shrine_warden`, `sod_druid_shrine_moon` y `sod_druid_shrine_beast`). Los tres tienen lógica (partes B, C y D). Al morir un avatar aparece su espíritu: **Blightbark** (222705), **Sagefeather** (222704) y **Whisperwing** (222703), élite nivel 50, neutrales y no atacables.
4. **Child of Apa'ro** (222580, ciervo, Azshara, mapa 1, (4293, -5458), respawn 1800 s): hostil, desollable e inmune a la magia; suelta **Sacred Stag Heart** (221326) al 100 %, solo a druidas y solo con 81924 activa. El corazón se ofrece en el Santuario de la Bestia (parte D).
5. Recompensa a elegir: **Rune of Efflorescence** (220360), que desbloquea la runa 7009022 (el Grabador la sigue vendiendo para las pruebas), o **Seed of Renewal** (219326, trinket raro **sin efecto implementado**: sus estadísticas están a 0).
6. No verificado: probabilidad y condiciones reales del botín del corazón (se usa 100 % solo con la misión activa), botín de desuello (se copia el de «Hakkari Frostwing», 5291), estadísticas y efecto del trinket (a 0), frases de Blightbark (no constan), modelos (todos stock), la z de los cinco spawns y las coordenadas de los santuarios.
7. Los marcadores `<name>` y `<class>` de la fuente se escriben como `$N` y `$C` (la sintaxis del cliente). Nutrir los dejó literales; es un error que aquí no se repite.

### Parte B: santuario del Celador (Feralas, 441948)

Solo el santuario de Feralas. Lógica en `server/mod-sod-content/src/druid/spell_sod_druid_shrine_warden.cpp` (registrado como `AddSC_sod_druid_shrine_warden` en `src/sod_content_loader.cpp`) y, en el SQL, los dos hechizos propios en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_warden.sql`. La parte A no se toca.

1. **Interactuar** con el santuario (441948) con la misión 81924 activa y el objetivo del Treant Avatar sin cumplir aplica **Duty of the Warden** (446448) y reinicia su progreso de dispensa. Sin la misión activa el santuario no hace nada.
2. Con Duty, **curarse una maldición Y un veneno** (en cualquier orden) lo transforma en **Mark of the Warden** (446467). No se ata a ningún hechizo concreto: se cuenta cualquier aura de tipo maldición o veneno que el jugador pierda **por dispensa** (`AURA_REMOVE_BY_ENEMY_SPELL`), que es como el core marca el dispel de `Remove Curse`/`Cure Poison` y sus equivalentes. Al perder Duty (expiración, muerte o transformación) se borra el progreso.
3. Con Mark, **acercarse** al santuario (a ≤15 m, comprobado como mucho una vez por segundo y solo en el mapa 1, el de Feralas) **o interactuar** de nuevo invoca al **Treant Avatar** (221935) como `TempSummon` hostil junto al santuario, que ataca al jugador. No se invoca si ya hay un avatar vivo a menos de 15 m del santuario (la comprobación es por cercanía, no por mapa: uno que haya perseguido a un jugador lejos del santuario no lo bloquea). El avatar lanza **Enredaderas (11922)** y, al morir, deja a **Blightbark** (222705) 60 s. La Marca no se consume al invocar (la fuente no dice que se gaste).
4. Los dos hechizos (446448 y 446467) son auras propias sin efecto de combate: `APPLY_AURA` con `SPELL_AURA_DUMMY` sobre el lanzador. Sus índices de lanzamiento, alcance y duración y sus iconos (`SpellIconID` 10 y 2013, dos iconos de naturaleza) están comprobados contra los DBC del cliente; la duración (índice 30 = 30 min) es provisional, la real de SoD no consta.
5. **No verificado / pendiente:**
   - **Sin compilar ni probar en juego.** Los dos comandos de validación (`tools/sod-data/validar_sql.sh` y `python3 tools/sod-data/check_syntax.py`) pasan, pero `check_syntax.py` usa una plantilla del módulo para este archivo (no está todavía en `compile_commands.json`), así que no es una compilación completa.
   - **Nombre e icono de los buffs en el cliente:** las dos filas de `spell_dbc` están escritas a mano en el SQL de la parte B (no se han añadido al generador `server/mod-sod-content/tools/sod_spells_druid.py` para no duplicarlas). Para que el cliente los muestre hay que añadirlos al `.py` y regenerar el parche de cliente; mientras tanto, no añadirlos también al `.py`.
   - **Frases de Blightbark:** no constan en `misiones.md`, así que no se le añade `creature_text` (no se inventan).
   - **Duración de Duty y Mark, y si Mark hereda lo que le quedaba a Duty:** no consta en la fuente; Mark se aplica con su propia duración.
   - **Comportamiento exacto del aggro del avatar** (se le hace atacar al invocarlo), el radio de «acercarse» (15 m, elegido a ojo) y que la Marca no se gaste al invocar: no verificados.
   - **Cómo se cuenta el crédito de la misión** (al matar al avatar, no al hablar con el espíritu): no verificado, igual que en la parte A.

### Parte C: santuario de la Luna (Tierras del Interior, 441946)

Solo el santuario de Tierras del Interior. Toda la lógica va en `server/mod-sod-content/src/druid/spell_sod_druid_shrine_moon.cpp` (registrado como `AddSC_sod_druid_shrine_moon` en `src/sod_content_loader.cpp`). En el SQL solo hace falta la frase del libro, en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_moon.sql` (`module_string` 1010 y su fila en esES): los dos hechizos de la secuencia son stock del core y la fuente no transcribe ninguna frase de Sagefeather, así que no se añade `creature_text`. La parte A no se toca.

1. Con la misión 81924 activa y el objetivo del Moonkin Avatar sin cumplir, **lanzar Tranquility y después Hurricane sobre el santuario** invoca al **Moonkin Avatar** (221933) como `TempSummon` hostil junto al santuario, que ataca al jugador. El disparo se engancha con un `PlayerScript` del lanzamiento de hechizo (`PLAYERHOOK_ON_SPELL_CAST`, en vez de un `SpellScript`), porque Tranquility y Hurricane tienen rangos y hay que leer el destino de Hurricane. El orden importa: Tranquility («la calma») deja una marca por jugador y Hurricane («la tormenta») la consume. Cada hechizo se identifica por el primero de su cadena, así que cualquier rango vale. La marca solo se pone si Tranquility se lanza con el jugador a ≤40 m del santuario (mapa 0) y caduca a los 30 s; Hurricane debe quedar centrado a ≤10 m del objeto, y para eso se usa el destino del hechizo (es un área en el suelo).
2. No se invoca sin la misión activa ni si ya hay un avatar vivo a menos de 15 m del santuario (la comprobación es por cercanía, no por mapa: uno que haya perseguido a un jugador lejos del santuario no lo bloquea).
3. El avatar lanza **Rend (13445)**, **Strike (13584)** y **Tendon Rip (3604)** y, al morir, deja a **Sagefeather** (222704) 60 s.
4. El santuario (441946) es un libro: el ScriptName `sod_druid_shrine_moon` de la parte A se enlaza con un `GameObjectScript` que **no es el disparador de la invocación** (lo es la secuencia de hechizos). Interactuar con él **sin** la misión pendiente muestra el texto de la fuente («The calm comes before the storm.») como mensaje del sistema, desde `module_string` (el C++ del módulo no guarda textos para el jugador).
5. **No verificado / pendiente:**
   - **Sin compilar ni probar en juego.** `python3 tools/sod-data/check_syntax.py` pasa para este archivo, pero usa una plantilla del módulo (no está en `compile_commands.json`), así que no es una compilación completa.
   - **Ventana calma→tormenta** (30 s, provisional para cubrir el canal de Tranquility): no consta en la fuente. Las distancias (≤40 m para Tranquility y ≤10 m para el centro de Hurricane) vienen del encargo, no de `misiones.md`, que solo dice «sobre el santuario».
   - **Reutilización de las tres habilidades del avatar** (10 s Rend, 6 s Strike, 15 s Tendon Rip): no consta en la fuente; son provisionales.
   - **Frases de Sagefeather:** no constan en `misiones.md` (solo se dice que Blightbark, el de Feralas, dice tres), así que no se le añade `creature_text` (no se inventan).
   - **Traducción al español de la frase del libro** («La calma precede a la tormenta.»): es nuestra, no consta ninguna oficial.
   - **Si el juego exige que Tranquility o Hurricane alcancen el objeto**, más allá de la distancia de lanzamiento: no verificado.
   - **Cómo se cuenta el crédito de la misión** (al matar al avatar, no al hablar con el espíritu): no verificado, igual que en las partes A y B.

### Parte D: santuario de la Bestia (Azshara, 441947)

Solo el santuario de Azshara. Toda la lógica va en `server/mod-sod-content/src/druid/spell_sod_druid_shrine_beast.cpp` (registrado como `AddSC_sod_druid_shrine_beast` en `src/sod_content_loader.cpp`). En el SQL solo hace falta la frase del libro, en `server/mod-sod-content/data/sql/db-world/base/sod_druid_shrine_beast.sql` (`module_string` 1011 y su fila en esES): la mecánica no necesita ningún hechizo propio (el disparo es la interacción) y la fuente no transcribe ninguna frase de Whisperwing, así que no se añade `creature_text`. La parte A no se toca.

1. Con la misión 81924 activa, el objetivo del Hippogryph Avatar sin cumplir y el **Sacred Stag Heart (221326)** en la mochila, **interactuar** con el santuario (441947) consume el corazón e invoca al **Hippogryph Avatar** (221928) como `TempSummon` hostil junto al santuario, que ataca al jugador. El disparo es `OnGossipHello` (el santuario es un libro, no hay hechizo ni secuencia que enganchar).
2. No se invoca sin la misión activa, sin el corazón, ni si ya hay un avatar vivo a menos de 15 m del santuario (la comprobación es por cercanía, no por mapa). Si ya hay uno vivo **no se gasta el corazón**: solo se repite la frase del libro.
3. El avatar lanza **Rend (13445)** y, al morir, deja a **Whisperwing** (222703) 60 s.
4. Interactuar **sin el corazón** (o sin la misión pendiente) muestra el texto de la fuente («Hunt the white stag with tooth and claw.») como mensaje del sistema, desde `module_string` (el C++ del módulo no guarda textos para el jugador).
5. **No verificado / pendiente:**
   - **Sin compilar ni probar en juego.** `python3 tools/sod-data/check_syntax.py` pasa para este archivo, pero usa una plantilla del módulo (no está en `compile_commands.json`), así que no es una compilación completa.
   - **Cuándo y cómo se consume el corazón** (al interactuar, sin condiciones extra de fase de misión) y **que la ofrenda no se gaste si ya hay un avatar vivo**: lo fija el encargo, no `misiones.md`, que solo dice que se ofrece.
   - **Qué pasa si se interactúa con un avatar vivo sin el corazón** (aquí se muestra la frase del libro): no consta.
   - **Reutilización de Rend** (10 s): no consta en la fuente; es provisional, como en las partes B y C.
   - **Frases de Whisperwing:** no constan en `misiones.md`, así que no se le añade `creature_text` (no se inventan).
   - **Traducción al español de la frase del libro** («Caza al venado blanco con dientes y garras.»): es nuestra, no consta ninguna oficial.
   - **Cómo se cuenta el crédito de la misión** (al matar al avatar, no al hablar con el espíritu): no verificado, igual que en las partes A, B y C.

## Pendiente de encontrar información

- **Rabia (Berserk, 417141, objeto Rune of Berserk 213117):** Wowhead solo muestra el Rune Broker como vendedor. No consta ninguna fuente anterior a la fase 6; falta por encontrar.
- **Regeneración frenética mejorada (431389, objeto Rune of Primal Energy 221516):** solo consta el Rune Broker, con 1 unidad del Emblem of the Wild Gods (232454) como coste. Falta por encontrar la fuente anterior a la fase 6.
