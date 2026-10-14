# Registro de cambios

Formato: más reciente arriba. Una entrada por cambio relevante, con su fecha.

## 2026-10-14

- Sacerdote: runas Renewed Hope `7005013`, Dispersion `7005014`, Pain Suppression `7005015`, Spirit of the Redeemer `7005016`, Void Plague `7005017` (tanda 3 de `.agents/plans/sacerdote/`). Renewed Hope con guion propio; Spirit of the Redeemer sin evitar la transformación automática del talento (ver TODO.md). Ejecución terminada en el árbol tras un bloqueo del ejecutor; SQL validado. Sin compilar ni probar.
- Sacerdote: runas Shared Pain `7005008`, Mind Sear `7005009`, Shadow Word: Death `7005010`, Empowered Renew `7005011`, Mind Spike `7005012` (tanda 2 de `.agents/plans/sacerdote/`). Mind Sear, Shadow Word: Death, Empowered Renew y Mind Spike aproximados (ver TODO.md); script de Mind Sear añadido. SQL validado. Sin compilar ni probar.
- Sacerdote: runas Serendipity `7005003`, Strength of Soul `7005004`, Twisted Faith `7005005`, Homunculi `7005006`, Prayer of Mending `7005007` (tanda 1 de `.agents/plans/sacerdote/`). Strength of Soul sin efecto (valor de 409317 no consta en wago ni Wowhead); Homunculi con un solo esbirro; script de Penance añadido. SQL validado. Sin compilar ni probar.
- Pícaro: adquisición de 27 runas generada con `gen_rune_acquisition.py --class rogue` (28 objetos con su id real de SoD, venta en el Grabador y botín real de WotLK solo para esta clase en 1 criaturas). Sin aplicar ni probar.
- Pícaro: runas Fan of Knives `7004027` (tanda 6 de `.agents/plans/picaro/`). Clon de Abanico de cuchillos de WotLK (52874) con daño y reutilización de SoD. SQL validado. Sin compilar ni probar.
- Pícaro: runas Carnage `7004022`, Cut to the Chase `7004023`, Unfair Advantage `7004024`, Blunderbuss `7004025`, Crimson Tempest `7004026` (tanda 5 de `.agents/plans/picaro/`). Valores de Carnage (15 %) y Unfair Advantage (100 % del arma, 1 punto de combo) de Wowhead; Blunderbuss y Crimson Tempest por verificar en juego. SQL validado. Sin compilar ni probar.
- Pícaro: runas Rolling with the Punches `7004017`, Waylay `7004018`, Combat Potency `7004019`, Focused Attacks `7004020`, Honor Among Thieves `7004021` (tanda 4 de `.agents/plans/picaro/`). Rolling with the Punches completada por el orquestador (+5 % de salud por carga, 30 s, de Wowhead). SQL validado. Sin compilar ni probar.
- Pícaro: runas Shadowstrike `7004012`, Poisoned Knife `7004013`, Shadowstep `7004014`, Shuriken Toss `7004015`, Master of Subtlety `7004016` (tanda 3 de `.agents/plans/picaro/`). Shadowstep y Shuriken Toss aproximados (ver TODO.md). SQL validado. Sin compilar ni probar.
- Pícaro: runas Blade Dance `7004007`, Envenom `7004008`, Cutthroat `7004009`, Main Gauche `7004010`, Saber Slash `7004011` (tanda 2 de `.agents/plans/picaro/`). Cutthroat sin ataque frontal ni Emboscada sin sigilo; Main Gauche y Saber Slash parciales (ver TODO.md). SQL validado con validar_sql.sh. Sin compilar ni probar.
- Pícaro: runas Deadly Brew `7004002`, Just a Flesh Wound `7004003`, Quick Draw `7004004`, Slaughter from the Shadows `7004005`, Between the Eyes `7004006` (tanda 1 de `.agents/plans/picaro/`). Deadly Brew sin el proc de Veneno instantáneo; Just a Flesh Wound aproxima la esquiva (requiere Danza de hojas); fórmula de daño de Between the Eyes sin verificar. SQL validado con `validar_sql.sh`; sin compilar ni probar.

## 2026-10-11

- Corregido: el worldserver se paraba al reaplicar `sod_hunter_runes.sql` (`Data too long for column 'description'`: `rune_template.description` es `varchar(255)`). Acortadas las descripciones largas de 7 runas (cazador 7003026, chamán 7007016, guerrero 7001004, 7001012, 7001018, 7001024 y 7001028); el texto completo sigue en el tooltip del hechizo.
- Añadido: `tools/sod-data/validar_sql.sh`, que aplica el SQL de world de nuestros módulos dos veces sobre una MySQL privada y desechable (esquema y actualizaciones de acore-test) y falla ante cualquier error. Pasa limpio: 46 archivos, sin errores.
- Corregido: el worldserver no arrancaba (`ERROR 1064 … near 's damage and health`): `sod_hunter_runes.sql` (5 descripciones) y `sod_warrior_runes.sql` (2) llevaban un apóstrofo sin duplicar suficiente dentro de la sentencia dinámica y cortaban la cadena. Revisados todos los `.sql` del módulo con un analizador de comillas; no aplicado a ninguna base de datos.
- Corregido: el worldserver no arrancaba (`ERROR 1264 … EffectSpellClassMaskB_1`): el generador escribía en `sod_content_spell_dbc.sql` máscaras de 32 bits con signo (`-2147483648`, hechizo 428717 del cazador) en columnas `unsigned`. `emit_spell_sql` convierte ahora los negativos de columnas sin signo; comprobado en todas las filas del SQL (0 negativos en columnas unsigned). No aplicado a ninguna base de datos.
- Cambiado: el Grabador del druida solo vende las runas sin fuente real implementada. Se retiran de su stock (con `DELETE` para las filas ya aplicadas) las 8 que ya tienen botín o vendedor real: Lacerate, Savage Roar, Mangle, Wild Strikes, Improved Swipe, Improved Barkskin, Fury of Stormrage y Survival of the Fittest (vendedor 211653). El resto sigue a 1 oro hasta que tengan fuente real.
- Corregido: Living Seed, Tree of Life, Efflorescence y Fury of Stormrage compartían icono con Sunfire y entre sí; ahora cada una tiene el suyo (`ability_druid_naturalperfection`, `ability_druid_treeoflife`, `spell_nature_naturetouchgrow`, `spell_nature_lightning`), tanto en la runa como en el hechizo (necesita parche de cliente nuevo). Sin compilar ni probar.

## 2026-10-10

- Corregido: las 12 runas de Balance y Restauración del druida (`7009014`–`7009025`) se aprendían de inicio porque no tenían objeto. Ahora cada una tiene su objeto real de SoD (venta en el Grabador y, en Improved Barkskin y Fury of Stormrage, botín real) y queda bloqueada hasta usarlo. `gen_rune_acquisition.py` admite `--runes` y `--output`. Sin compilar ni probar; hace falta parche de cliente nuevo para los objetos.
- Corregido: Gore y Dreamstate del druida usaban el icono de interrogación (`ability_druid_ravage` y `ability_druid_dreamstate`; el hechizo necesita parche de cliente nuevo).
- Añadido: `tools/sod-data/gen_rune_locale.py` y `sod_runes_locale_es.sql` con el nombre y la descripción esES de 133 runas que se veían en inglés. Sin compilar ni probar.
- Corregido: el buff de Fury of Stormrage (`900017`) no tenía fila en `spell_script_names` y el worldserver registraba «Script … is not assigned in the database». Sin compilar ni probar.
- Cazador: runas Raptor Fury `7003024`, T.N.T. `7003025`, Hit and Run `7003026`, Improved Volley `7003027`, Resourcefulness `7003028` (tanda 5 de `.agents/plans/cazador/`). Raptor Fury, T.N.T. y Hit and Run con efectos parciales o sin implementar por falta de datos (ver TODO.md). Sin compilar ni probar.
- Cazador: runas Wyvern Strike `7003019`, Catlike Reflexes `7003020`, Lock and Load `7003021`, Rapid Killing `7003022`, Focus Fire `7003023` (tanda 4 de `.agents/plans/cazador/`). Wyvern Strike y Focus Fire con fidelidad parcial (ver TODO.md); corregida la fila spell_proc sin SchoolMask. Sin compilar ni probar.
- Cazador: runas Expose Weakness `7003014`, Melee Specialist `7003015`, Steady Shot `7003016`, Dual Wield Specialization `7003017`, Trap Launcher `7003018` (tanda 3 de `.agents/plans/cazador/`). Trap Launcher sin separar enfriamientos de trampas (requiere core). Sin compilar ni probar.
- Cazador: runas Serpent Spread `7003009`, Sniper Training `7003010`, Carve `7003011`, Cobra Slayer `7003012`, Aspect of the Viper `7003013` (tanda 2 de `.agents/plans/cazador/`). Sniper Training con guion propio (sin copiar el talento de WotLK); Serpent Spread con la Picadura de serpiente aprendida. Corregido sod_dbc.set_int para máscaras de 32 bits sin signo. Sin compilar ni probar.
- Cazador: runas Beast Mastery `7003004`, Cobra Strikes `7003005`, Lone Wolf `7003006`, Flanking Strike `7003007`, Kill Shot `7003008` (tanda 1 de `.agents/plans/cazador/`). Cobra Strikes: el beneficio copia el script y el spell_proc del core (sin ellos las cargas no se gastaban). Flanking Strike y Kill Shot simplificados. Sin compilar ni probar.
- Guerrero: adquisición de 29 runas generada con `gen_rune_acquisition.py --class warrior` (29 objetos con su id real de SoD, venta en el Grabador y botín real de WotLK solo para esta clase en 31 criaturas). Sin aplicar ni probar.
- Guerrero: runas Wrecking Crew `7001027`, Fresh Meat `7001028`, Shockwave `7001029`, Sudden Death `7001030` (tanda 6 de `.agents/plans/guerrero/`). Sudden Death copia el spell_proc del core (gasta el beneficio al ejecutar); Fresh Meat y Shockwave con aproximaciones documentadas. Sin compilar ni probar.
- Guerrero: runas Shield Mastery `7001022`, Taste for Blood `7001023`, Vigilance `7001024`, Rampage `7001025`, Sword and Board `7001026` (tanda 5 de `.agents/plans/guerrero/`). Duración de Taste for Blood (9 s) contrastada con Wowhead; el +9 % de Shield Mastery sin verificar. Sin compilar ni probar.
- Guerrero: runas Enraged Regeneration `7001017`, Gladiator Stance `7001018`, Intervene `7001019`, Rallying Cry `7001020`, Endless Rage `7001021` (tanda 4 de `.agents/plans/guerrero/`). Gladiator Stance usa la forma 24, inexistente en 3.3.5a (solo error en el log, sin caída; ver TODO). Sin compilar ni probar.
- Guerrero: runas Single-Minded Fury `7001012`, Victory Rush `7001013`, Blood Surge `7001014`, Focused Rage `7001015`, Precise Timing `7001016` (tanda 3 de `.agents/plans/guerrero/`). Blood Surge sin el golpe con ambas armas de Embate; Victory Rush depende de que el core conceda el estado Victorioso. Sin compilar ni probar.
- Guerrero: runas Consumed By Rage `7001007`, Frenzied Assault `7001008`, Furious Thunder `7001009`, Meathook `7001010`, Quick Strike `7001011` (tanda 2 de `.agents/plans/guerrero/`). Furious Thunder sin el +75 % de amenaza y Meathook sin enraizar (límites de 3.3.5a). Sin compilar ni probar.
- Guerrero: runas Blood Frenzy `7001002`, Flagellation `7001003`, Raging Blow `7001004`, Warbringer `7001005` y Commanding Shout `7001006` (tanda 1 de `.agents/plans/guerrero/`). Sin compilar ni probar; Commanding Shout sube salud máxima (WotLK) en vez de aguante.
- Brujo, completo (27 runas `7008001`–`7008027`): adquisición generada con `tools/sod-data/gen_rune_acquisition.py --class warlock` (28 objetos con su id real de SoD, venta en el Grabador y botín real de WotLK solo para brujos) y `obtencion.md` actualizado con la nueva herramienta `tools/sod-data/actualizar_obtencion.py`. Sin aplicar ni probar.
- Brujo: runas Infernal Armor `7008024`, Mark of Chaos `7008025`, Pandemic `7008026` y Grimoire of Synergy `7008027` (paso 5). Corregido en la revisión: la probabilidad de Grimoire of Synergy es del 10 % (Wowhead, hechizo 426301), no 6 %. Mark of Chaos sin escalado con el nivel. Sin compilar ni probar.
- Brujo: runas Demonic Grace `7008019`, Invocation `7008020`, Dance of the Wicked `7008021`, Vengeance `7008022` e Immolation Aura `7008023` (paso 4). Corregido en la revisión: la duración de Dance of the Wicked es de 15 s (Wowhead), no 10 s. Invocation simplificada (un pulso del daño periódico) y sin Siphon Life, que en WotLK es un talento pasivo. Sin compilar ni probar.
- Brujo: runas Soul Siphon `7008014`, Shadow and Flame `7008015`, Lake of Fire `7008016`, Master Channeler `7008017` y Shadow Bolt Volley `7008018` (paso 3, hecho por DeepSeek en ~15 min). Lake of Fire y Master Channeler son parciales (el aura 332 que quita el canal no existe en 3.3.5a); Soul Siphon sin el ramal bajo el 20 % de vida. Sin compilar ni probar.
- Herramientas nuevas: `tools/sod-data/revisar_runas.py` (revisión automática de las runas de una clase) y `tools/sod-data/regenerar_sql_hechizos.sh` (regenera el SQL de hechizos sin tocar `acore-test`).
- Corregido con el revisor: **Living Seed del druida no hacía nada** (le faltaban el script `spell_dru_living_seed` y su `spell_proc`, ligados al id de WotLK); **Earth Shield del chamán** curaba sin el enfriamiento de 3,5 s del core; el beneficio de **Backdraft** del brujo no copiaba su regla de consumo de cargas; iconos inexistentes en la tabla de runas del druida (Sunfire, Fury of Stormrage, Starfall); familia de dos auxiliares del paladín.

## 2026-10-09

- Brujo: runas Backdraft `7008009`, Decimation `7008010`, Demonic Pact `7008011`, Everlasting Affliction `7008012` y Demonic Knowledge `7008013` (segunda tanda de `.agents/plans/brujo/`), clones de plantillas de WotLK que reutilizan los manejadores nativos del core (`spell_warl_decimation`, `spell_warl_everlasting_affliction`, `spell_warl_demonic_knowledge`): **sin C++ nuevo** (enumerado de ids, `tools/sod_spells_warlock.py` y SQL). SQL de hechizos regenerado (9 filas de `spell_dbc`, 3 de `spell_script_names` y la de `spell_proc` de Decimation) y parche de cliente creado en `datos/parche-cliente/20261009-brujo/` (sin publicar). `check_syntax.py`: 86 archivos, 0 errores. Limitaciones en `TODO.md` y `docs/runas/warlock.md`: Conflagrar sigue consumiendo Inmolar (exige parchear el core) y Everlasting Affliction no cubre Cuchilla de las Sombras ni Dolor abrasador (no existen en 3.3.5a). Sin compilar ni probar.
- Política nueva (decidida por el usuario): ninguna runa se descarta. `docs/runas/fuentes-no-disponibles.md` lista las runas sin su fuente real de SoD (se compran en el Grabador) y las 33 que aún no tienen objeto-runa; `docs/runas/redundantes.md` analiza las que coinciden con hechizos o talentos de WotLK, para decidir una a una.
- Brujo: runas Unstable Affliction `7008004`, Summon Felguard `7008005`, Metamorphosis `7008006`, Incinerate `7008007` y Shadowflame `7008008` (paso 1 de `.agents/plans/brujo/`). El ejecutor se quedó sin saldo a mitad; el orquestador lo terminó: el +40 % de daño de Fuego de Incinerate no estaba implementado (efecto vacío) e icono de Shadowflame inexistente. Metamorphosis solo da la forma, sin Shadow Cleave, Menace ni Demon Charge. Sin compilar ni probar.
- Chamán: adquisición de 26 runas (`sod_shaman_acquisition.sql`, paso 6): objetos con su id real de SoD, venta en el Grabador y botín real de WotLK (Overload, Lava Burst, Storm, Earth, and Fire) solo para chamanes. Lava Lash sin objeto (no figura en las fuentes). Sin aplicar ni probar.
- Chamán: runas Overcharged `7007023`, Rolling Thunder `7007024`, Static Shock `7007025`, Coherence `7007026` y Storm, Earth, and Fire `7007027` (paso 5), con valores de Wowhead aportados por el orquestador. Corregido en la revisión: el salto extra de Coherence valía 0 (la plantilla tiene `DieSides` 0). Sin compilar ni probar.
- Chamán: runas Power Surge `7007018`, Decoy Totem `7007019`, Spirit of the Alpha `7007020`, Burn `7007021` y Mental Dexterity `7007022` (paso 4). Completado en la revisión con valores de Wowhead (tooltips consultados el 2026-10-09): duraciones de Power Surge (10 s) y Mental Dexterity (30 s) y el beneficio Loyal Beta (443320) de Spirit of the Alpha. Limitaciones en `TODO.md` (Decoy Totem no redirige el ataque al tótem; Burn no propaga Choque de llamas). Sin compilar ni probar.
- Corregido: el generador descarta en silencio las claves de `overrides` que no son columnas de `spell_dbc`. `StackAmount` (columna real `CumulativeAura`) se perdía, así que el beneficio de Eclipse del druida (900023) no se acumulaba; arreglado en druida y chamán. El coeficiente de Molten Blast pasa a `spell_bonus_data`. SQL de hechizos regenerado.
- Chamán: runas Ancestral Guidance `7007014`, Greater Ghost Wolf `7007015`, Way of Earth `7007016` y Molten Blast `7007017` (paso 3). Limitaciones documentadas en `TODO.md`: Lobo fantasmal sigue sin poder usarse en interiores (exige cambiar el hechizo 2645 en core y cliente) y Molten Blast sin amenaza extra (sin valor verificable). Sin compilar ni probar.
- Chamán: runas Dual Wield Specialization `7007009`, Overload `7007010`, Shield Mastery `7007011`, Two-Handed Mastery `7007012` y Healing Rain `7007013` (paso 2). Corregido en la revisión: Dual Wield Specialization añadía un golpe extra a Golpe de tormenta (que en WotLK ya golpea con ambas armas); las copias de Overload no tenían efectos en el servidor (`inherit_server`) y habrían sumado dos veces el poder con hechizos. SQL de hechizos regenerado (incluye el arreglo de 460171). Sin compilar ni probar.
- Paladín: Malleable Protection reutiliza Defender's Resolve (460171), que ya definía el druida; se elimina la definición duplicada del mismo id. Pendiente de regenerar el SQL de hechizos con el siguiente paso.
- Chamán: runas Lava Burst `7007003`, Riptide `7007004`, Feral Spirit `7007005`, Maelstrom Weapon `7007006`, Tidal Waves `7007007` y Ancestral Awakening `7007008` (paso 1 de `.agents/plans/chaman/`), clones de WotLK. Corregido en la revisión: Tidal Waves y Ancestral Awakening no tenían su `spell_proc` ni script (ligados al id de WotLK) y nunca se habrían activado; Maelstrom Weapon gastaba cargas con hechizos que no modifica. Paladín: Light's Grace tenía el mismo fallo de `spell_proc`, corregido. Sin compilar ni probar.
- Paladín: adquisición de las 27 runas (`sod_paladin_acquisition.sql`, paso 5): objetos con su id real de SoD, venta en el Grabador y botín real de WotLK para Aura Mastery, Crusader Strike y Hand of Reckoning, solo para paladines; 27 objetos añadidos al manifiesto del cliente. Lacerate: añadida la condición «solo druidas» al botín de los worgen Moonrage. Sin aplicar ni probar.
- Paladín: runas Sacred Shield `7002024`, Inspiration Exemplar `7002025`, Hand of Reckoning `7002026` y Malleable Protection `7002027` (paso 4). Malleable Protection rehecha en la revisión: usaba el aura 332 (no existe en 3.3.5a), una plantilla inexistente (5573) y no definía el hechizo de poder de ataque 460171; ahora alarga Protección divina con un script enganchado a 498. Los auxiliares clonados de Rejuvenecimiento pasan a familia de paladín. Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Beacon of Light `7002019`, Hammer of the Righteous `7002020`, Shield of Righteousness `7002021`, Divine Light `7002022` y Rebuke `7002023` (paso 3). Corregido en la revisión: Rebuke y el escudo de Divine Light ya no heredan la familia de pícaro o mago de su plantilla; iconos inexistentes o genéricos sustituidos por los reales del cliente. Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Sheath of Light `7002015`, Guarded by the Light `7002016`, Shock and Awe `7002017` y Hallowed Ground `7002018` (paso 2), con valores contrastados en Wowhead. Corregido en la revisión: los beneficios de poder con hechizos ya no suben el daño físico (escuelas 126). Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: runas Infusion of Light `7002011`, Light's Grace `7002012`, Improved Sanctuary `7002013` y Aegis `7002014` (paso 1 de `.agents/plans/paladin/`). Corregido en la revisión: máscaras y reembolso de Choque Sagrado, enfriamiento (en WotLK ya es de 6 s), orden de rangos de Expiación e iconos. Improved Sanctuary aún sin efecto (ver `TODO.md`). Pasan `clang++ -fsyntax-only`; sin compilar ni probar.
- Paladín: recupera del historial (`d85f936`) las 6 runas retiradas el 2026-10-07 (The Art of War, Righteous Vengeance, Improved Hammer of Wrath, Purifying Power, Fanaticism, Wrath), con su configuración y su registro en el loader; SQL de hechizos regenerado. Pasan `clang++ -fsyntax-only` con los flags reales; sin compilar ni probar.
- Lacerate (`7009003`): los worgen Moonrage de Silverpine (1769, 1770, 1782, 1924) sueltan la runa con un 1,0661 %, tasa conjunta de Wowhead para el Unbalanced Idol de SoD. Solo SQL; sin probar en juego.
- `ESTADO.md`: los mensajes del servidor ya salen de tablas de cadenas (inglés y esES); se corrige la nota que lo daba por pendiente.
- `TODO.md`: anota lo que falta del druida (Thrash (Cat), Tiger's Fury). Quita la distribución de parches (ya se publican con el launcher) y la fuente de Lacerate en Silverpine (hecha).

## 2026-10-08

- Añade las runas de druida Lifebloom `7009026` y Nourish `7009027`, con venta en el Grabador y textos oficiales resumidos en español. Sin compilar ni probar en juego.

## 2026-10-05 (sesión de continuación)

- Generador de cliente en Linux: `tools/sod-client/stormlib_shim.py` (ctypes sobre `libstorm`) y rutas
  insensibles a mayúsculas; `--dry-run` ejecutado con éxito sobre una copia del cliente.
- Clave `inherit_server` en los specs: el SQL del servidor de un hechizo clonado lleva todas las
  columnas de su plantilla. Activada en 400647, 412286, 425121 y 400640. `sod_content_spell_dbc.sql`
  regenerado con ellos.

- Español (esES): opción `--locale` en el generador, columnas esES de `Spell.dbc` y `Faction.dbc`,
  `sod_spells_es.json` (textos oficiales) y `sod_content_locale_es.sql` (25 objetos). Sin probar.

- Primer parche de cliente generado (esES) en una copia del cliente y guardado en `datos/parche-cliente/`.
  El MPQ contiene los DBC esperados; sin probar en juego.

- Addon `RuneEngraver` clonado en `upstream/` (commit fijado en `preparar-entorno.sh`); guía de compilación con la opción de apartar los módulos ajenos.

- Catálogo de runas de SoD: `tools/sod-data/extract_runes.py` y `docs/runas/` (JSON + una ficha por clase).
- Iconos de las runas Fingers of Frost y Burnout corregidos (verificados con Wowhead).

- `tools/sod-data/match_wotlk.py` y `docs/runas/equivalencias-wotlk.*`: equivalentes de las 106 runas en WotLK 3.3.5a.
- Primera compilación completa de `acore-test` con nuestros módulos: sin errores (hecha por el usuario).

- Piloto de runas de otra clase (brujo): Chaos Bolt y Haunt (`sod_spells_warlock.py`, `sod_warlock_runes.sql`); `sod_spells.py` carga los specs por clase.

- Runa Chimera Shot de cazador (clon de WotLK, sin compilar ni probar); Explosive Shot sigue pendiente.
- Runas castables de guerrero, paladín, pícaro, sacerdote, chamán y druida (11, clones de WotLK, sin compilar ni probar). Penance sin script del core (exige su cadena de rangos). Cazador pendiente: el coste de Explosive Shot es 3,5 % y `ManaCostPct` es entero.

### Cambiado
- `ESTADO.md`: `agentrelay` ya está instalado y operativo (corrige lo anterior); el `build/` antiguo
  de `acore-test` ya lo ha borrado el usuario.

## 2026-10-05 (traspaso al servidor)

### Añadido
- `docs/ESTADO.md`: estado vivo del proyecto (dónde estamos, pendiente por orden, lo ya sabido,
  cómo delegar y qué no hacer). Es lo primero que lee una sesión nueva.
- Sección 0 de `AGENTS.md`: normas de arranque del orquestador, con la obligación de delegar y
  permiso para ampliar `AGENTS.md` y crear `.agents/`.
- `docs/guias/prompt-de-arranque.md`: prompt para abrir una sesión nueva en este directorio.

### Notas
- El usuario ha hecho el paso 1 de la guía (3 bases `*_test` vacías); `cmake`, `make` e `install`
  siguen pendientes y los hace él.
- (Corregido después: `agentrelay` sí estaba instalado; ver la entrada de la sesión de continuación.)

## 2026-10-05 (servidor de pruebas)

### Añadido
- Proyecto portado al servidor Debian: `/home/stark/Repos/acore-sod` (clon de este repositorio),
  con `core/` (fork `Playerbot-SoD`) y `upstream/` reconstruidos con `tools/preparar-entorno.sh`.
- `acore-test` preparado para compilar: remoto `sod` y rama `Playerbot-SoD` (mismo commit que
  tenía), y enlaces a `mod-rune-engraving` y `mod-sod-content` en `modules/`.
- Decisión `0005` (entorno de pruebas) y sección 7 de la guía de compilación, con los comandos
  concretos.

### Verificado
- El servidor cumple los requisitos de AzerothCore (Debian 13, Clang 19, MySQL 8.4).
- 0 colisiones de ids entre nuestro SQL y `acore_world_test` (67 ids comprobados).

### Notas
- El reino de desarrollo (id 2) pasará a ser el de SoD, con **instalación nueva**: el usuario borra
  el `build/` y las bases `*_test` anteriores. El orquestador no compila **ni borra** nada.
- Anotadas en la guía las opciones de CMake del `build/` anterior, que se pierden al borrarlo.

## 2026-10-05

### Añadido
- Proyecto creado: servidor tipo Season of Discovery sobre AzerothCore (cliente 3.3.5a, build
  12340) con módulos propios.
- Informes de investigación en `docs/investigacion/` (viabilidad, opción SoD, auditoría de
  `mod-sod`) y decisiones `0001`–`0004` en `docs/decisiones/`.
- `server/mod-sod-content/`: módulo único de contenido (clases y mundo), fusión de `mod-sod-mage`
  y `mod-sod-world`, con una clase por subdirectorio de `src/`.
- `server/mod-rune-engraving/`: copia propia del motor de runas.
- `tools/sod-client/`: copia propia del generador del parche de cliente.
- `tools/preparar-entorno.sh`: reconstruye `core/` y `upstream/` con commits fijados.
- `docs/guias/compilar-en-linux.md`: guía de compilación (sin probar).

### Cambiado
- Core: fork `warcrafted-server/azerothcore-wotlk`, rama `Playerbot-SoD`, en lugar del
  AzerothCore oficial (decisión 0003).
- `.claude/` deja de versionarse (contenía rutas locales).

### Pendiente
- **Nada se ha compilado ni ejecutado todavía.**
- Las 4 runas de escarcha del mago (Fingers of Frost, Burnout, Ice Lance, Icy Veins).
- Ejecutar `tools/sod-client/build_patch.py` con la estructura nueva (necesita el cliente 3.3.5a).
- Decidir la licencia del código original del repositorio.
