# Runas sin su fuente real de SoD

Estado a 2026-10-09 (runas ya implementadas: 107). Decisión del usuario (2026-10-09): **ninguna runa se descarta por no tener su fuente real**; mientras tanto se aprende con el Grabador (`.rune summon` › «Comprar runas», objeto-runa a 1 oro) y aquí se anotan para decidir qué hacer con cada una. Generado cruzando `docs/runas/fuentes-sod.json` (Wowhead) con `acore_world` (solo lectura) y el SQL del módulo.

## 1. Sin objeto-runa: hoy no se pueden comprar en el Grabador

Solo se obtienen con `.rune unlock <rune_id>` (o, las de escarcha del mago, se graban sin descubrirlas). **Hay que crearles su objeto y su venta**: son 20 runas (pendiente, en el plan de cada clase).

| rune_id | Clase | Runa | Objeto real de SoD |
|---|---|---|---|
| 7000009 | Mago | Fingers of Frost | 203747 |
| 7000010 | Mago | Burnout | 203748 |
| 7000011 | Mago | Icy Veins | 235598 |
| 7000012 | Mago | Ice Lance | 203745 |
| 7001001 | Guerrero | Devastate | 204703 |
| 7003001 | Cazador | Chimera Shot | 206168 |
| 7003002 | Cazador | Master Marksman | 206155 |
| 7003003 | Cazador | Explosive Shot | 206169 |
| 7004001 | Pícaro | Mutilate | 203990 |
| 7005001 | Sacerdote | Circle of Healing | 205949 |
| 7005002 | Sacerdote | Penance | 205951 |
| 7007002 | Chamán | Lava Lash | — |
| 7008001 | Brujo | Chaos Bolt | 205228 |
| 7008002 | Brujo | Haunt | 205230 |
| 7008003 | Brujo | Demonic Tactics | 205215 |
| 7008004 | Brujo | Unstable Affliction | 221482 |
| 7008005 | Brujo | Summon Felguard | 221499 |
| 7008006 | Brujo | Metamorphosis | 210980 |
| 7008007 | Brujo | Incinerate | 211477 |
| 7008008 | Brujo | Shadowflame | 213101 |

## 2. La fuente real existe en WotLK pero aún no está implementada

Criaturas, vendedores, objetos de mundo o misiones con el mismo id en este core: se pueden añadir como fuente real.

| rune_id | Clase | Runa | Fuente disponible en WotLK |
|---|---|---|---|
| 7003001 | Cazador | Chimera Shot | botín de Bristleback Battleboar; botín de Githyiss the Vile; botín de Scorpid Worker |
| 7003003 | Cazador | Explosive Shot | botín de Arra'chea; botín de Bjarn; botín de Edan the Howler; botín de Ghost Howl y 8 más |
| 7004001 | Pícaro | Mutilate | botín de Lord Melenas |
| 7005002 | Sacerdote | Penance | botín de Kobold Laborer |
| 7009004 | Druida | Savage Roar | objeto de mundo Kolkar's Booty; objeto de mundo Kolkars' Booty |
| 7009014 | Druida | Improved Barkskin | botín de Gnarled Thistleshrub; botín de Ground Pounder; botín de Land Rager; botín de Thistleshrub Dew Collector y 1 más |
| 7009018 | Druida | Fury of Stormrage | botín de Grellkin |

## 3. La fuente real solo existe en SoD

NPC, eventos, objetos de mundo o misiones que no están en 3.3.5a. Hoy: Grabador. Opciones por decidir: recrear el NPC o la misión, moverla a otra criatura de WotLK de la misma zona y nivel, o dejar solo el Grabador.

| rune_id | Clase | Runa | Fuente de SoD no disponible | ¿Hay otra fuente? |
|---|---|---|---|---|
| 7000001 | Mago | Regeneration | evento/creación Translate Spell Notes | no: solo Grabador |
| 7000003 | Mago | Living Flame | evento/creación Translate Spell Notes | no: solo Grabador |
| 7000004 | Mago | Enlightenment | evento/creación Translate Spell Notes | no: solo Grabador |
| 7000006 | Mago | Arcane Blast | evento/creación Arcane Shards - Give Rune | no: solo Grabador |
| 7000008 | Mago | Living Bomb | botín de Harvest Reaper Prototype; evento/creación Path of No Steps - Give Rune | no: solo Grabador |
| 7000009 | Mago | Fingers of Frost | evento/creación Translate Spell Notes | no: solo Grabador |
| 7000010 | Mago | Burnout | botín de Frozen Makrura; botín de Frozen Murloc; botín de Frozen Trogg | no: solo Grabador |
| 7001001 | Guerrero | Devastate | evento/creación Combine Rune Pieces | no: solo Grabador |
| 7002002 | Paladín | Avenger's Shield | botín de Dro'zem the Blasphemous | no: solo Grabador |
| 7002007 | Paladín | Improved Hammer of Wrath | vendedor Quartermaster Alandra; vendedor Quartermaster Falinar; vendedor Quartermaster Kyleen y 1 más | no: solo Grabador |
| 7002010 | Paladín | Wrath | botín de Vengeful Spirit | no: solo Grabador |
| 7002012 | Paladín | Light's Grace | vendedor Rix Xizzix | no: solo Grabador |
| 7002014 | Paladín | Aegis | evento/creación Wounded Adventurer - Give Paladin Rune | no: solo Grabador |
| 7002018 | Paladín | Hallowed Ground | botín de Undying Laborer; objeto de mundo Libram of Blessings | no: solo Grabador |
| 7002022 | Paladín | Divine Light | evento/creación Ada Gelhardt - Give Rune Rewards | no: solo Grabador |
| 7002023 | Paladín | Rebuke | evento/creación Liv Bradford - Give Paladin Rune | no: solo Grabador |
| 7002024 | Paladín | Sacred Shield | objeto de mundo Libram of Deliverance | no: solo Grabador |
| 7002026 | Paladín | Hand of Reckoning | objeto de mundo Sunken Reliquary | sí (botín/vendedor del módulo o de WotLK) |
| 7002027 | Paladín | Malleable Protection | evento/creación [DNT] Brother Atticus Give Rune | no: solo Grabador |
| 7003001 | Cazador | Chimera Shot | objeto de mundo Frostmane Loot Cache | sí (botín/vendedor del módulo o de WotLK) |
| 7003002 | Cazador | Master Marksman | botín de Fallenroot Poacher; botín de Razormane Poacher; botín de Venture Co. Poacher | no: solo Grabador |
| 7004001 | Pícaro | Mutilate | evento/creación Ba'so - Trade Letter for Rune; evento/creación Blackrat - Trade Letter for Rune; evento/creación Cutty - Trade Letter for Rune y 1 más | sí (botín/vendedor del módulo o de WotLK) |
| 7005001 | Sacerdote | Circle of Healing | evento/creación Dark Insight | no: solo Grabador |
| 7005002 | Sacerdote | Penance | objeto de mundo Rockjaw Footlocker | sí (botín/vendedor del módulo o de WotLK) |
| 7007001 | Chamán | Earth Shield | misión Hirzek | no: solo Grabador |
| 7007005 | Chamán | Feral Spirit | botín de Frijidar | no: solo Grabador |
| 7007006 | Chamán | Maelstrom Weapon | misión Catching Up | no: solo Grabador |
| 7007011 | Chamán | Shield Mastery | evento/creación Collect Galvanic Icon | no: solo Grabador |
| 7007015 | Chamán | Greater Ghost Wolf | botín de Primordial Anomaly | no: solo Grabador |
| 7007016 | Chamán | Way of Earth | botín de Decayed Elemental; botín de Desert Mirage | no: solo Grabador |
| 7007017 | Chamán | Molten Blast | botín de Frozen Makrura | sí (botín/vendedor del módulo o de WotLK) |
| 7007018 | Chamán | Power Surge | botín de Tam'kar | no: solo Grabador |
| 7007019 | Chamán | Decoy Totem | evento/creación Altar of the Wind Spirit Trial | no: solo Grabador |
| 7007020 | Chamán | Spirit of the Alpha | objeto de mundo Weathered Cache | no: solo Grabador |
| 7007021 | Chamán | Burn | vendedor Quartermaster Alandra; vendedor Quartermaster Falinar; vendedor Quartermaster Kyleen y 1 más | no: solo Grabador |
| 7007022 | Chamán | Mental Dexterity | botín de Enraged Voidwalker | no: solo Grabador |
| 7007023 | Chamán | Overcharged | botín de Twilight Dark Shaman | no: solo Grabador |
| 7007024 | Chamán | Rolling Thunder | objeto de mundo Chest | no: solo Grabador |
| 7007025 | Chamán | Static Shock | botín de Whirling Tempest | no: solo Grabador |
| 7007026 | Chamán | Coherence | evento/creación Polish | no: solo Grabador |
| 7008001 | Brujo | Chaos Bolt | botín de Frozen Makrura; botín de Frozen Murloc; botín de Frozen Trogg | no: solo Grabador |
| 7008002 | Brujo | Haunt | objeto de mundo Defias Stashbox; objeto de mundo Lost Stash; objeto de mundo Rockjaw Footlocker y 1 más | no: solo Grabador |
| 7008003 | Brujo | Demonic Tactics | evento/creación Gakin - Rune Reward | no: solo Grabador |
| 7008004 | Brujo | Unstable Affliction | vendedor Quartermaster Alandra; vendedor Quartermaster Falinar; vendedor Quartermaster Kyleen y 1 más | no: solo Grabador |
| 7008006 | Brujo | Metamorphosis | misión Raszel Ander | no: solo Grabador |
| 7008007 | Brujo | Incinerate | botín de Incinerator Gar'im | no: solo Grabador |
| 7008008 | Brujo | Shadowflame | botín de Seductress Ceeyna | no: solo Grabador |
| 7009001 | Druida | Wild Growth | evento/creación Give Extra Rune; misión Trial of The Owls | no: solo Grabador |
| 7009003 | Druida | Lacerate | botín de Aggressive Squashling; evento/creación Empty Snapjaw Nest - Give Rune; evento/creación Young Reef Crawler- Give Rune y 1 más | no: solo Grabador |
| 7009004 | Druida | Savage Roar | objeto de mundo Tangled Blight Pile | sí (botín/vendedor del módulo o de WotLK) |
| 7009006 | Druida | Survival Instincts | evento/creación [DNT] Amaryllis Give Rune B | no: solo Grabador |
| 7009008 | Druida | Gore | vendedor Quartermaster Alandra; vendedor Quartermaster Falinar; vendedor Quartermaster Kyleen y 1 más | no: solo Grabador |
| 7009015 | Druida | Living Seed | botín de Unleashed Nature Spirit; evento/creación Balance | no: solo Grabador |
| 7009016 | Druida | Gale Winds | botín de Namida Grimtotem | no: solo Grabador |
| 7009017 | Druida | Sunfire | objeto de mundo Lunar Chest | no: solo Grabador |
| 7009018 | Druida | Fury of Stormrage | objeto de mundo Bristleback Loot Cache | sí (botín/vendedor del módulo o de WotLK) |
| 7009019 | Druida | Dreamstate | objeto de mundo Blooming Satyrweed | no: solo Grabador |
| 7009020 | Druida | Tree of Life | objeto de mundo Gift of the Wisp | no: solo Grabador |
| 7009021 | Druida | Starsurge | evento/creación Give Rune of Stars | no: solo Grabador |
| 7009022 | Druida | Efflorescence | misión Wisdom of the Guardians | no: solo Grabador |
| 7009023 | Druida | Elune's Fires | evento/creación Elune's Favor | no: solo Grabador |
| 7009025 | Druida | Starfall | botín de Arcterris | no: solo Grabador |
| 7009027 | Druida | Nourish | misión The Lost Saplings | no: solo Grabador |

En SoD real casi todas se venden además en los Rune Brokers de las capitales (NPC de SoD); el Grabador es su sustituto.
