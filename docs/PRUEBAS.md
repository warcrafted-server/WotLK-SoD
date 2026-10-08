# Qué hacer ahora

El objetivo es que Marc pueda compilar, instalar el parche y el addon, arrancar el reino de desarrollo y probar las runas pendientes. El reino de desarrollo es el reino 2. El orquestador no arranca el servidor ni aplica SQL. Estado del documento: 2026-10-07.

1. **Compilar** los cambios C++ indicados en «Qué hay que recompilar y qué no»: `cd ~/Repos/acore-test/build && nice -n 19 make -j3 2>&1 | tee ~/sod-build.log && make install`. Si falla, pásame las primeras líneas con `error:`.
2. **Copiar el parche y el addon.** Desde el servidor, copia `patch-z.mpq`, `esES/patch-esES-z.mpq` y la carpeta `RuneEngraver/` (addon propio y traducido) desde `datos/parche-cliente/20261006-final/`. Cliente 3.3.5a build 12340 en español (`esES`): `patch-z.mpq` va a `<cliente>/Data/`, `esES/patch-esES-z.mpq` a `<cliente>/Data/esES/` y `RuneEngraver` a `<cliente>/Interface/AddOns/RuneEngraver`. Descarga el cliente no incluye ni el addon ni el parche; son aparte. Borra `<cliente>/Cache/WDB` y deja `Data/esES/realmlist.wtf` con `set realmlist logon.warcrafted.com`. Si tu cliente 3.3.5 ya tiene parches de otro reino, usa una copia: no mezcles parches. Para transferir los archivos, usa `scp`/SFTP desde `/home/stark/Repos/acore-sod/datos/parche-cliente/20261006-final/`.
3. **Preparar y arrancar.** `make install` solo deja los `.dist`; crea los `.conf` de ambos módulos (sin ellos el log se llena de «Missing property SodMage.Enable», inofensivo porque el valor por defecto es 1): `cd ~/Servers/acore-test/etc/modules && cp mod_sod_content.conf.dist mod_sod_content.conf && cp mod_rune_engraving.conf.dist mod_rune_engraving.conf`. Arranca `worldserver` de `Servers/acore-test`. Al arrancar aplica solo el SQL de los módulos, por orden de nombre: `rune_engraving_schema.sql` antes que `sod_*`.
4. **Comprobar el arranque.** Busca en el log `RuneEngraving: loaded N rune(s) into the catalog`. Según los SQL del repo debería ser **N = 29**; apunta el N real. Si falla el SQL o N es 0, pásame las líneas del log con `error` o `RuneEngraving`.
5. **Entrar y probar.** Usa una cuenta del `authserver` (`account create`), crea un personaje de la clase que vas a probar, súbelo con GM (`.character level <n>`) y entra por el reino **Desarrollo**. Sigue las casillas de pendientes de abajo. Con el personaje conectado y el addon activo, `.rune summon` crea al grabador (mujer humana, «Rune Engraver») en tus mismos pies, por unos minutos; puede quedar tapada por el personaje o la cámara. Aleja la cámara, usa `/targetfriend` o `/target Rune Engraver` y haz clic derecho: aparece un menú con las ranuras (Pecho, Manos, Piernas) y las runas que puedes grabar. `.rune slots` muestra cada ranura abierta o bloqueada (Pecho 4, Manos 6, Piernas 8). Graba con `.rune engrave <ranura> <rune_id>`; consulta `.rune list`. Comprueba que el hechizo aparece en el libro con icono y texto en español, se puede lanzar, hace daño o cura, y su coste y enfriamiento son razonables. Anota qué runa falla, qué esperabas y qué ocurrió.

## Pendiente de probar

Todas estas comprobaciones siguen pendientes salvo las confirmaciones fechadas en «Hecho». Cada casilla conserva las sospechas, diferencias y observaciones conocidas; las runas nuevas de Balance/Restauración se incluyen como **sin compilar ni probar**. Números entre paréntesis son índices de ranura para `.rune engrave`.


### Motor y Grabador

- [ ] Prueba de requisitos: el motor ofrece `.rune progress`, `.rune complete <objeto>` y `.rune resetprogress <objeto>`. Con `RuneEngraving.Requirements.Enable = 0` se saltan los requisitos. Comprobar si funcionan en juego.
- [ ] Los requisitos de uso de SoD de los ídolos (por ejemplo, «20 sangrados a humanoides») están solo como texto y no se comprueban.
- [ ] Comprobar compra de objetos-runa desde `.rune summon` > «Comprar runas» a 1 oro; sustituye a los Rune Brokers de SoD. Ya no basta con `.rune engrave`: hay que comprar el objeto y usarlo para desbloquear la runa. `.rune unlock <rune_id>` permite saltarse la compra.

### Mago

- [ ] Fingers of Frost — `rune_id 7000009`, Pecho (4). Sospecha: el chill de Blizzard no activa Fingers of Frost.
- [ ] Burnout — `rune_id 7000010`, Pecho (4). Tiene script propio sin probar.
- [ ] Icy Veins — `rune_id 7000011`, Piernas (8). Con la Icy Veins real (talento) el mago tendrá dos copias del hechizo.
- [ ] Ice Lance — `rune_id 7000012`, Manos (6). Tiene script propio sin probar; hace x3 contra congelados (core) y no x5 como SoD. Debe hacer unos 221-255 de daño a nivel 80 y bastante menos a nivel bajo (a nivel 6, de 12 a 50 de media).
- [ ] Probar si el chill de Blizzard activa Fingers of Frost y si las dos copias reales/de runa de Icy Veins e Ice Lance se comportan correctamente.
- [ ] Comprobar las diferencias conocidas: sin Winter's Chill; Fingers of Frost no se activa con el chill de Blizzard; Ice Lance multiplica x3 contra congelados y no x5.

### Otras clases de fase 1

- [ ] Guerrero — Devastate `7001001`, Manos (6).
- [ ] Paladín — Divine Storm `7002001`, Pecho (4); Avenger's Shield `7002002`, Piernas (8); Aura Mastery `7002003`, Piernas (8); Crusader Strike `7002004`, Manos (6). Comprobar que Divine Storm funciona sin el talento; Avenger's Shield también está pendiente de comprobar su daño.
- [ ] Cazador — Chimera Shot `7003001`, Manos (6); Master Marksman `7003002`, Pecho (4); Explosive Shot `7003003`, Manos. Explosive Shot requiere solo SQL y parche, no recompilar.
- [ ] Pícaro — Mutilate `7004001`, Manos (6). Comprobar que funciona sin el talento.
- [ ] Sacerdote — Circle of Healing `7005001`, Manos (6); Penance `7005002`, Manos (6). Sospecha: Penance no tiene script del core y puede quedarse sin parte del efecto.
- [ ] Chamán — Earth Shield `7007001`, Piernas (8); Lava Lash `7007002`, Manos (6).
- [ ] Brujo — Chaos Bolt `7008001`, Manos (6); Haunt `7008002`, Manos (6); Demonic Tactics `7008003`, Pecho (4). Comprobar que Haunt funciona sin el talento y el daño de Chaos Bolt.
- [ ] Probar las pasivas Demonic Tactics `7008003`, Master Marksman `7003002` y Survival of the Fittest `7009002`.
- [ ] Comprobar el daño de Avenger's Shield, Circle of Healing y Wild Growth creciendo con el nivel (a 80 coinciden con WotLK).
- [ ] Comprobar nombres de NPC y misiones del mundo de SoD en español.

### Druida feral

- [ ] Wild Growth `7009001`, Manos (6); Survival of the Fittest `7009002`, Pecho (4). Wild Growth también está en las pruebas de crecimiento con nivel (a 80 coincide con WotLK).
- [ ] Lacerate `7009003`, Piernas (8): aparece en el libro con icono y texto, se lanza, y su daño periódico crece con el nivel. Diferencia conocida con SoD: sin el daño de arma por acumulación.
- [ ] Savage Roar `7009004`, Piernas (8).
- [ ] Berserk `7009005`, Cintura (7). Diferencias conocidas con SoD: sin multiobjetivo de Lacerate, sin quitar el miedo ni inmunidad.
- [ ] Survival Instincts `7009006`, Pies (9). Diferencias conocidas con SoD: sin regeneración al esquivar ni sanación no física.
- [ ] Mangle `7009007`, Manos (6): probar en gato y oso.
- [ ] Gore `7009008`, Cabeza (0).
- [ ] Wild Strikes `7009009`, Pecho (4): probar con un grupo en forma felina.
- [ ] King of the Jungle `7009010`, Pies (9).
- [ ] Skull Bash `7009011`, Manos (6): carga e interrupción a menos de 13 yd.
- [ ] Improved Frenzied Regeneration `7009012`, Muñecas (5).
- [ ] Improved Swipe `7009013`, Espalda (3): comprobar la muerte de objetivos dormidos en gato.
- [ ] Improved Barkskin `7009014`, ranura no indicada en el texto original: comprobar uso sobre aliados y en forma, sin ralentizar ataques ni lanzamiento.
- [ ] Los objetos-runa del druida ya existen con su id real de SoD y se consiguen como indica `docs/runas/obtencion.md`: botín con las tasas reales (bajas, del 0,2 al 2 %) de criaturas de WotLK, Grizzby y oficiales de suministros.
- [ ] Requisitos de uso de ídolos del druida: Wild Strikes (curar 10 bestias distintas), Savage Roar (20 sangrados a humanoides), Mangle (50 de ira en oso 60 s seguidos), Improved Barkskin (5 muertes con daño de Naturaleza bajo Piel de corteza) e Improved Swipe (5 muertes de dormidos en gato); con `RuneEngraving.Requirements.Enable = 0` se saltan.
- [ ] Fidelidad extra aún pendiente de verificar (sin inventar mecánica): Lacerate/Aggressive Squashling, King of the Jungle/Supply Bag, Survival Instincts/evento «Amaryllis», Improved Frenzied Regeneration. No se pudo confirmar la mecánica exacta porque Wowhead usa páginas dinámicas que WebFetch no renderiza (sin herramienta de navegador en esa sesión); es mejor documentarlo sin implementar que inventar. Gore tiene su fuente real documentada en `docs/runas/obtencion.md` (4 intendentes, verificados en wago.tools), aunque esos NPC todavía no existen en el mundo.
- [ ] Las diferencias con SoD de las siete runas de C++ nuevas están descritas en el informe de cada tarea (`agentrelay show`).

### Druida Balance/Restauración

Las runas siguientes se han cotejado con `sod_druid_runes.sql`; todas están **sin compilar ni probar**. El número entre paréntesis es el índice de ranura del SQL.

- [ ] Living Seed — `7009015`, Pecho (4).
- [ ] Gale Winds — `7009016`, Cabeza (0).
- [ ] Sunfire — `7009017`, Manos (6).
- [ ] Fury of Stormrage — `7009018`, Pecho (4).
- [ ] Dreamstate — `7009019`, Pies (9).
- [ ] Tree of Life — `7009020`, Espalda (3).
- [ ] Starsurge — `7009021`, Piernas (8).
- [ ] Efflorescence — `7009022`, Muñecas (5).
- [ ] Elune's Fires — `7009023`, Muñecas (5).
- [ ] Eclipse — `7009024`, Cintura (7).
- [ ] Starfall — `7009025`, Espalda (3).
- [ ] Lifebloom — `7009026`, Piernas (8); icono y texto, sanación periódica, sanación final y retorno de maná. Sin compilar ni probar.
- [ ] Nourish — `7009027`, Cintura (7); icono y texto, sanación y efectos de hechizos del core. Sin compilar ni probar.

## Qué hay que recompilar y qué no

**Sí requiere recompilar** todo el C++ nuevo desde la última compilación: traducciones, las 7 runas de C++ de druida (segunda tanda), Improved Barkskin, la compra de runas en el Grabador, el motor de requisitos de uso de los ídolos (`.rune progress`, `.rune complete <objeto>`, `.rune resetprogress <objeto>`), los requisitos de los ídolos del druida y algo de trabajo del paladín (Art of War, Righteous Vengeance, Fanaticism...). La sintaxis de los 47 archivos pasa con clang; no se ha compilado ni enlazado nada. Si falla, pásame las líneas con `error:`.

Después de compilar y de regenerar `build_patch.py`, copia de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq` desde `datos/parche-cliente/20261006-final/` y reinicia el reino 2. Los MPQ traen los iconos de bolsa de los objetos nuevos. Las siete runas de la segunda tanda son Mangle 7009007 (Manos, 6), Gore 7009008 (Cabeza, 0), Wild Strikes 7009009 (Pecho, 4), King of the Jungle 7009010 (Pies, 9), Skull Bash 7009011 (Manos, 6), Improved Frenzied Regeneration 7009012 (Muñecas, 5) e Improved Swipe 7009013 (Espalda, 3). El interruptor es `SodDruid.Enable` en `mod_sod_content.conf`, que `make install` deja solo como `.dist`: si quieres cambiar valores copia las secciones nuevas al `.conf`.

El parche se regeneró sin «Rango N» en los clones; queda pendiente copiar de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`.

La primera tanda feral (Lacerate 7009003, Savage Roar 7009004, Berserk 7009005 y Survival Instincts 7009006) requiere **solo SQL y parche, no recompilar**: copia de nuevo `patch-z.mpq` y `esES/patch-esES-z.mpq`, y reinicia el reino. Wild Growth 7009001 y Survival of the Fittest 7009002 ya estaban. También requiere solo SQL y parche, sin recompilar, Explosive Shot `7003003` (Manos): copiar de nuevo ambos MPQ y reiniciar; lo mismo para comprobar el daño de Chaos Bolt, Haunt, Avenger's Shield, Circle of Healing y Wild Growth que crece con el nivel (a 80 coinciden con WotLK), y los nombres de NPC y misiones del mundo de SoD en español.

Al probar adquisición de runas, la compra en el Grabador es C++ nuevo y requiere recompilar. Los objetos se consiguen con botín y tasas del 0,2 al 2 % de criaturas WotLK, Grizzby y oficiales de suministros; la compra al Grabador (`.rune summon` > «Comprar runas») cuesta 1 oro y sustituye a los Rune Brokers de SoD. Pasos: recompilar, copiar los MPQ y reiniciar el reino. Para desbloquear la runa hay que comprar el objeto y usarlo; `.rune unlock <rune_id>` permite saltarse ese paso. Los requisitos de uso de SoD (p. ej. «20 sangrados a humanoides») están solo como texto y no se comprueban.

## Hecho (ya confirmado, no repetir)

Estas pruebas las confirmó Marc; no hay que repetirlas.

- **2026-10-06, tras compilar:** textos en español, addon y tooltip correctos. `.rune slots` dice «nivel 1» en Pecho, Manos y Piernas: es lo configurado (`RuneEngraving.SlotMinLevel.*` = 1, como la fase 1 de SoD), no depende de ser GM. Los números 4, 6 y 8 son los índices de ranura para `.rune engrave`.
- **2026-10-06:** el primer arranque del reino 2 falló por una comilla sin escapar en «Avenger's Shield» (`sod_content_spell_dbc.sql`, línea 102); corregido en el generador y el arranque posterior funcionó. El servidor arranca con 29 runas; `.rune summon` y el menú funcionan; Ice Lance se lanza y hace daño; el hechizo sale en la barra.
