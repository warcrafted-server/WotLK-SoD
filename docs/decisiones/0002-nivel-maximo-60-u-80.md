# 0002 — Nivel máximo: ¿60 de Classic u 80 de WotLK?

- **Fecha:** 2026-10-05
- **Estado:** PROPUESTA — nivel 60, con la puerta al 80 deliberadamente abierta

## La duda

Al emular SoD sobre AzerothCore (WotLK 3.3.5a), el core **permite nivel 80 de serie**: ya trae
las zonas de TBC y Northrend, los talentos hasta 80 y todo el contenido de WotLK. La pregunta es
si quedarse en el **60 de Classic** o aprovechar el **80** que el core regala.

No es una pregunta técnica, es de diseño: nada obliga a elegir el 60.

## Lo que dice el código auditado

Dos hallazgos relevantes en `upstream/azerothcore/mod-sod/`:

1. **El motor de runas no está atado a 60.** `mod-rune-engraving` define **once ranuras**
   (Head, Neck, Shoulder, Cloak, Chest, Wrist, Hands, Waist, Legs, Feet, Ring) —muchas más que
   las tres de la fase 1 de SoD— y el nivel mínimo de cada una es **configurable**
   (`RuneEngraving.SlotMinLevel.*`). Por defecto todas están abiertas desde nivel 1; hay un
   bloque comentado que las mapea a los cortes de fase de SoD (1/26/41/51). El motor **no
   presupone ningún tope**.
2. **El contenido del mago sí asume 60, pero de forma configurable.** Los hechizos se registran
   con `SpellLevel = 0` (sin requisito de nivel) y el único límite explícito es
   `SodMage.LivingBomb.ScalingCapLevel = 60`, con el comentario «SoD Living Bomb is level 60»:
   existe para que la runa no supere al hechizo real. Es un parámetro, no una restricción
   estructural.

Conclusión técnica: **ir a 80 no rompe nada del trabajo heredado.** Es una decisión de diseño
libre, no una limitación.

## El problema real: el equilibrio, no el código

Lo que no es gratis es lo de siempre en los servidores Classic+:

- Las runas de SoD están **calibradas para el 60** y para el poder de objeto de Classic. Más allá
  del 60, el jugador obtiene talentos de TBC/WotLK y equipo muy superior, y el valor relativo de
  cada runa se desdibuja: unas se vuelven irrelevantes y otras, desproporcionadas.
- La auditoría ya constató que `mod-sod-mage` **no tiene pasada de balance** ni a nivel 60.
  Extender a 80 multiplicaría ese trabajo sin haber validado el caso base.
- A nivel 80 se compite con el propio WotLK: las runas pierden su razón de ser frente a los
  árboles de talentos completos y las habilidades de las dos expansiones.

Y el motivo de proyecto, que pesa más: **ya tienes un AzerothCore de WotLK a nivel 80.** Si este
servidor también llega al 80, se parece a lo que ya tienes y el proyecto pierde su identidad.
El valor de hacer SoD es precisamente el de ser **otra cosa**.

## Decisión propuesta

**Nivel máximo 60, contenido de Classic.** Razones:

1. Es lo que da identidad al proyecto frente al AzerothCore que ya existe.
2. Es donde las runas tienen sentido: son el sustituto del poder que da subir de nivel.
3. Es el único alcance donde se puede llegar a un equilibrio defendible con el esfuerzo
   disponible.
4. SoD se diseñó así. Cuanto menos se invente, menos hay que ajustar a ciegas.

En la práctica, el primer hito sigue siendo **fase 1, nivel 25** (ver
[decisión 0001](0001-core-y-version-de-cliente.md)); el 60 es el techo del proyecto, no el punto
de partida.

## Lo que esto implica

- Hay que **limitar el nivel máximo a 60** en la configuración de AzerothCore
  (`MaxPlayerLevel`), no dejar el 80 por defecto.
- Las zonas de TBC y Northrend siguen existiendo en el cliente y el core. Quedan **fuera de
  alcance**, no eliminadas: no se diseña contenido para ellas.
- Las ranuras del motor se configuran con los cortes de SoD (1/26/41/51), no abiertas desde
  nivel 1.

## Lo que no se cierra

**La puerta al 80 queda abierta a propósito.** Como el motor no presupone tope y los límites son
configuración, subir a 80 más adelante es cambiar parámetros y añadir contenido, no rehacer nada.
Si algún día interesa un «SoD extendido» hasta 80, se podrá hacer sin deshacer este trabajo.

Lo que no se debe hacer es **empezar** por ahí: sería asumir el coste de equilibrar dos
expansiones antes de tener una sola fase jugable.

## Revisar cuando

Exista la fase 1 jugable y equilibrada, y haya ganas de extender el proyecto más allá de Classic.
