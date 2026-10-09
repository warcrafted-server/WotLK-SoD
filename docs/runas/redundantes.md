# Runas que coinciden con algo que la clase ya aprende en WotLK

Estado a 2026-10-09. Decisión del usuario (2026-10-09): **ninguna se descarta**; se analizan una a una y él decide.
Cruce de las 253 runas del catálogo (todas las fases, `docs/runas/catalogo-sod.json`) con los instructores de clase
de `acore_world` (`trainer` + `trainer_spell`, solo lectura) y con `Talent.dbc` del cliente 3.3.5a, por nombre en
español. El cruce por nombre no detecta runas con otro nombre y efecto parecido. **Las diferencias se basan en la
descripción de SoD del catálogo; la comparación con el hechizo de WotLK es preliminar y está sin verificar en juego.**

Recordatorio: se empieza en nivel 60 y se llegará al 80 (decisión 0002).

## 1. El instructor la enseña a nivel 60 o menos: no aporta nada desde el primer día

| Clase | Runa | WotLK (id, nivel) | Diferencia con SoD | Estado | Opciones |
|---|---|---|---|---|---|
| Paladín | Hand of Sacrifice | 6940, 46 | Ninguna relevante: mismo 30 % transferido, mismos 12 s y mismo tope de vida. | Sin implementar | Dejarla sin efecto, o darle una mejora propia (p. ej. menos enfriamiento). |
| Paladín | Hand of Reckoning | 62124, 16 | SoD añade mejoras de Furia recta (amenaza, maná al ser curado, reducción de daño bajo el 35 % de vida). | **Implementada** (`7002026`) solo con la parte pasiva | Mantener como está. |
| Chamán | Water Shield | 52127, 20 | SoD da maná en % del máximo (por 5 s y al ser golpeado); WotLK da cantidades fijas por rango. | Sin implementar | Implementar la versión porcentual como sustituta, o dejarla sin efecto. |
| Chamán | Fire Nova | 1535, 12 | Ninguna: en 3.3.5a Nova de Fuego ya hace estallar el tótem de fuego. | Sin implementar | Dejarla sin efecto. |
| Cazador | Aspect of the Viper | 34074, 20 | SoD: maná según la velocidad del arma y un % del máximo periódico; WotLK es parecido (escala con el arma). | Sin implementar | Comparar valores; probablemente sin efecto. |
| Cazador | Steady Shot | 56641, 50 | SoD: daño de arma en %; WotLK, daño fijo más arma. | Sin implementar | Dejarla sin efecto o ajustar el daño. |
| Guerrero | Victory Rush | 34428, 6 | SoD cura un % de la vida máxima; en 3.3.5a, solo daño. | Sin implementar | Implementar la curación como mejora sobre 34428. |

## 2. El instructor la enseña entre los niveles 61 y 80: la runa la adelanta

Útiles de 60 hasta el nivel indicado; a partir de ahí el jugador tendría dos copias del hechizo (ya pasa con
Ice Lance y Arcane Blast del mago). Opciones generales: (a) dejar la runa y quitarla o desactivarla cuando se
aprenda la de WotLK, (b) que la runa modifique la de WotLK en lugar de duplicarla, (c) aceptar el duplicado.

| Clase | Runa | WotLK (id, nivel) | Diferencia notable con SoD | ¿Implementada? |
|---|---|---|---|---|
| Druida | Lacerate | 33745, 66 | SoD suma daño de arma por acumulación. | Sí (`7009003`) |
| Druida | Lifebloom | 33763, 64 | Devuelve la mitad del coste al terminar (igual que WotLK). | Sí (`7009026`) |
| Druida | Savage Roar | 52610, 75 | Duración por punto distinta. | Sí (`7009004`) |
| Druida | Nourish | 50464, 80 | +20 % con HoT activo (igual). | Sí (`7009027`) |
| Cazador | Kill Shot | 53351, 71 | Sin alcance mínimo y reinicio bajo el 20 %. | No |
| Mago | Arcane Blast | 30451, 64 | Bonifica los demás hechizos Arcanos. | Sí (`7000006`) |
| Mago | Ice Lance | 30455, 66 | Acumulación de daño recibido de la siguiente Lanza. | Sí (`7000012`) |
| Mago | Frostfire Bolt | 44614, 75 | Daño periódico adicional. | No |
| Mago | Molten Armor | 30482, 62 | Daño de fuego al ser golpeado. | No |
| Paladín | Sacred Shield | 53601, 80 | Bonificación a Destello de Luz. | Sí (`7002024`) |
| Paladín | Shield of Righteousness | 53600, 75 | Daño según valor de bloqueo (igual). | Sí (`7002021`) |
| Sacerdote | Prayer of Mending | 33076, 68 | Igual en esencia. | No |
| Sacerdote | Mind Sear | 48045, 75 | Igual en esencia. | No |
| Sacerdote | Shadow Word: Death | 32379, 62 | Igual en esencia. | No |
| Sacerdote | Binding Heal | 32546, 64 | Igual en esencia. | No |
| Pícaro | Envenom | 32645, 62 | Aumenta la frecuencia de Veneno instantáneo. | No |
| Pícaro | Fan of Knives | 51723, 80 | Más daño con dagas. | No |
| Chamán | Lava Burst | 51505, 75 | Igual en esencia. | Sí (`7007003`) |
| Brujo | Incinerate | 29722, 64 | +% de daño de Fuego durante unos segundos. | Sí (`7008007`) |
| Guerrero | Commanding Shout | 469, 68 | Igual en esencia. | No |
| Guerrero | Enraged Regeneration | 55694, 75 | Igual en esencia. | No |
| Guerrero | Intervene | 3411, 70 | Reduce la amenaza del protegido. | No |

## 3. En WotLK es un talento (90 runas)

No son redundantes: la runa da el efecto sin gastar puntos. Riesgo a revisar en cada una: si el jugador tiene
además el talento, ¿se suman los dos efectos? (p. ej. Mangle, Wild Growth, Avenger's Shield, Riptide, Chaos Bolt).
La lista completa sale de la columna «talento» del cruce; se revisarán al implementar cada clase.
