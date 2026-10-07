# Pruebas pendientes

Qué debe hacer Marc para probar lo hecho hasta ahora, con instrucciones exactas. Se actualiza en
cuanto Marc confirma un paso o se añade algo probable; lo ya confirmado se mueve a «Hecho». **Nada
de lo listado se ha probado en juego.** Estado a 2026-10-06 (tarde).

## Dónde está cada cosa

- Parche listo (regenerado el 2026-10-06 en el servidor, copia en `datos/parche-cliente/20261006-final/`):
  `patch-z.mpq`, `esES/patch-esES-z.mpq` y la carpeta `RuneEngraver/` (el addon, ahora propio y traducido). Sin parche el cliente no
  muestra ni los hechizos ni sus iconos; sin addon solo funciona el NPC y `.rune`.
- Descargar el cliente **no** incluye el addon ni el parche: son aparte.

## Paso 1 · Cliente (en tu PC)

Cliente 3.3.5a build 12340, idioma `esES`. Copiar del servidor (por `scp`/SFTP, desde
`/home/stark/Repos/acore-sod/datos/parche-cliente/20261006-final/`):

1. `patch-z.mpq` a `<cliente>/Data/`.
2. `esES/patch-esES-z.mpq` a `<cliente>/Data/esES/`.
3. Carpeta `addons/RuneEngraver` a `<cliente>/Interface/AddOns/RuneEngraver`.
4. Borrar `<cliente>/Cache/WDB`.
5. `Data/esES/realmlist.wtf` con `set realmlist logon.warcrafted.com`.

Si tu cliente es un 3.3.5 ya parcheado por otro reino, usa una copia: no mezcles parches.

## Paso 2 · Servidor de desarrollo (reino 2)

Lo haces tú (el orquestador no arranca ni aplica SQL):

1. **Compilar: hoy SÍ** (cambió C++: cadenas traducidas del motor de runas y del contenido). Si falla, pásame las primeras líneas con `error:`:
   `cd ~/Repos/acore-test/build && nice -n 19 make -j3 2>&1 | tee ~/sod-build.log && make install`.
2. Crear los `.conf` de los dos módulos (`make install` solo deja los `.dist`; sin ellos el log se llena de
   «Missing property SodMage.Enable», inofensivo porque el valor por defecto es 1):
   `cd ~/Servers/acore-test/etc/modules && cp mod_sod_content.conf.dist mod_sod_content.conf && cp mod_rune_engraving.conf.dist mod_rune_engraving.conf`.
3. Arrancar `worldserver` de `Servers/acore-test`. Al arrancar aplica solo el SQL de los módulos (orden
   por nombre: `rune_engraving_schema.sql` antes que `sod_*`).
4. En el log buscar `RuneEngraving: loaded N rune(s) into the catalog`. Según los SQL del repo
   debería ser **N = 29**; apunta el N real.
5. Si falla el SQL o N es 0, pásame las líneas del log con `error` o `RuneEngraving`.

## Paso 3 · Cuenta y personaje

Cuenta en el `authserver` (`account create`), personaje de la clase a probar, subido con GM
(`.character level <n>`). Entrar por el reino **Desarrollo**.

## Paso 4 · Probar una runa

Con el personaje conectado y el addon activo:

1. `.rune summon` crea al grabador (mujer humana, «Rune Engraver») **en tus mismos pies**, unos minutos; puede quedar tapada por tu personaje o la cámara. Alejar la cámara, o `/targetfriend`, o `/target Rune Engraver`, y clic derecho: sale un menú con las ranuras (Pecho, Manos, Piernas) y las runas que puedes grabar.
2. `.rune slots` muestra cada ranura abierta o bloqueada (Pecho 4, Manos 6, Piernas 8).
3. Grabar: `.rune engrave <ranura> <rune_id>`; ver `.rune list`.
4. Comprobar: el hechizo aparece en el libro con **icono y texto en español**, se puede lanzar,
   hace daño o cura, y el coste y el enfriamiento son razonables.
5. Anotar lo que falla: qué runa, qué esperabas y qué ocurrió.

| Clase | Runa (rune_id · ranura) |
|---|---|
| Mago | Fingers of Frost 7000009 · 4 · Burnout 7000010 · 4 · Icy Veins 7000011 · 8 · Ice Lance 7000012 · 6 |
| Guerrero | Devastate 7001001 · 6 |
| Paladín | Divine Storm 7002001 · 4 · Avenger's Shield 7002002 · 8 · Aura Mastery 7002003 · 8 · Crusader Strike 7002004 · 6 |
| Cazador | Chimera Shot 7003001 · 6 · Master Marksman 7003002 · 4 |
| Pícaro | Mutilate 7004001 · 6 |
| Sacerdote | Circle of Healing 7005001 · 6 · Penance 7005002 · 6 |
| Chamán | Earth Shield 7007001 · 8 · Lava Lash 7007002 · 6 |
| Brujo | Chaos Bolt 7008001 · 6 · Haunt 7008002 · 6 · Demonic Tactics 7008003 · 4 |
| Druida | Wild Growth 7009001 · 6 · Survival of the Fittest 7009002 · 4 |

Sospechosas de fallar: **Penance** (sin script del core, puede quedarse sin parte del efecto),
**Fingers of Frost** y **Burnout** (scripts propios sin probar nunca) y las que dependían de talentos
que el personaje no tiene (Divine Storm, Mutilate, Haunt: comprobar que funcionan sin el talento).

## Qué comprobar con lo nuevo (tras compilar y copiar el parche)

- Menú del grabador y comandos `.rune` en **español** si el cliente está en esES, con nombres de ranura (Pecho, Manos, Piernas) y de runa traducidos.
- Addon en español (botón, panel, pie «N/M runas recogidas»).
- Pasar el ratón por un objeto equipado con runa grabada: sale «Grabado: <runa>» y su descripción.
- **Ice Lance** (7000012): debe hacer unos 221-255 a nivel 80 y bastante menos a nivel bajo (a nivel 6, de 12 a 50 de media).
- Con las pasivas: Demonic Tactics 7008003, Master Marksman 7003002, Survival of the Fittest 7009002 (ver tabla).

## Pendiente de probar (sin compilar)

Solo SQL y parche, **no hace falta recompilar**: copiar de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`, reiniciar el reino y comprobar: Explosive Shot (rune 7003003, Manos), daño de Chaos Bolt, Haunt, Avenger's Shield, Circle of Healing y Wild Growth que crece con el nivel (a 80 coinciden con WotLK), y nombres de NPC y misiones del mundo de SoD en español.

## Adquisición de las runas del druida (C++ pequeño en el Grabador): RECOMPILAR

Los objetos-runa del druida ya existen con su id real de SoD y se consiguen como indica `docs/runas/obtencion.md`: botín con las tasas reales (bajas, del 0,2 al 2 %) de criaturas de WotLK, Grizzby y oficiales de suministros, y **compra al Grabador (`.rune summon` > «Comprar runas»)** a 1 oro, que sustituye a los Rune Brokers de SoD. Pasos: recompilar, copiar los MPQ (traen los iconos de bolsa de los objetos nuevos), reiniciar el reino; ya no basta con `.rune engrave`: hay que **comprar el objeto y usarlo** para desbloquear la runa. Con `.rune unlock <rune_id>` se salta. Los requisitos de uso de SoD (p. ej. «20 sangrados a humanoides») están solo como texto y no se comprueban.

## Druida feral, segunda tanda (C++): RECOMPILAR

Siete runas nuevas con código propio (`src/druid/`, interruptor `SodDruid.Enable` en `mod_sod_content.conf`, que `make install` deja solo como `.dist`: si quieres cambiar valores copia las secciones nuevas al `.conf`): Mangle 7009007 (Manos, 6), Gore 7009008 (Cabeza, 0), Wild Strikes 7009009 (Pecho, 4), King of the Jungle 7009010 (Pies, 9), Skull Bash 7009011 (Manos, 6), Improved Frenzied Regeneration 7009012 (Muñecas, 5), Improved Swipe 7009013 (Espalda, 3). Pasos: compilar (`cd ~/Repos/acore-test/build && nice -n 19 make -j3 2>&1 | tee ~/sod-build.log && make install`; si falla, pásame las líneas con `error:`), copiar de nuevo los dos MPQ, reiniciar el reino. Probar con un druida: Mangle en gato y en oso, Skull Bash (carga e interrupción a menos de 13 yd), Wild Strikes con un grupo en forma felina, Improved Swipe. **Sin compilar ni probar**; las diferencias con SoD están en el informe de cada tarea (`agentrelay show`).

## Druida feral (prioridad), primera tanda, solo SQL y parche, sin recompilar

Copiar de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq` y reiniciar el reino. Runas nuevas del druida (`.rune engrave <ranura> <id>`): Lacerate 7009003 (ranura 8), Savage Roar 7009004 (8), Berserk 7009005 (7), Survival Instincts 7009006 (9); ya estaban Wild Growth 7009001 (6) y Survival of the Fittest 7009002 (4). Comprobar que salen en el libro con icono y texto, que se lanzan y que Lacerate hace daño periódico que crece con el nivel. **Diferencias conocidas con SoD** (no son fallos): Lacerate sin el daño de arma por acumulación; Berserk sin multiobjetivo de Lacerate, sin quitar el miedo ni inmunidad; Survival Instincts sin regeneración al esquivar ni sanación no física.

## Hecho

- 2026-10-06, tras compilar: textos en español, addon y tooltip correctos. `.rune slots` dice «nivel 1» en Pecho, Manos y Piernas: es lo configurado (`RuneEngraving.SlotMinLevel.*` = 1, como la fase 1 de SoD), no depende de ser GM. Los números 4, 6 y 8 son los índices de ranura para `.rune engrave`.
- Pendiente de comprobar: al regenerar el parche (sin «Rango N» en los clones) copiar de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`.
- 2026-10-06, servidor arranca con 29 runas; `.rune summon` y el menú funcionan; Ice Lance se lanza y hace daño; el hechizo sale en la barra.
- 2026-10-06, primer arranque del reino 2: el SQL falló en `sod_content_spell_dbc.sql` línea 102 (comilla sin escapar en «Avenger's Shield»). Corregido en el generador; **repetir el arranque** (paso 2).
