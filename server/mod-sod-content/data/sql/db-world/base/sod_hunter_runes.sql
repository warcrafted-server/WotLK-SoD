-- mod-sod-content: Hunter rune definitions.
-- The rune engine is optional, so this file is a no-op when its table is absent.

SET @rune_tbl := (
    SELECT COUNT(*)
    FROM information_schema.tables
    WHERE table_schema = DATABASE()
      AND table_name = 'rune_template'
);

SET @sql := IF(@rune_tbl > 0,
'INSERT INTO `rune_template`
    (`rune_id`, `spell_id`, `class_mask`, `slot_mask`, `name`, `icon`, `description`, `source`, `enabled`)
 VALUES
    (7003001, 409433, 4, 64, ''Chimera Shot'', ''ability_hunter_chimerashot2'',
    ''You deal weapon damage, refreshing the current Sting on your target and triggering an effect.'',
    ''mod-sod-hunter'', 1),
    (7003002, 409428, 4, 16, ''Master Marksman'', ''ability_hunter_mastermarksman'',
    ''Increases your critical strike chance by 5%, and reduces the Mana cost of all your Shot abilities by 25%.'',
    ''mod-sod-hunter'', 1),
    (7003003, 409552, 4, 64, ''Explosive Shot'', ''ability_hunter_explosiveshot'',
     ''Fires an explosive charge that deals Fire damage to nearby enemies, repeating every second for 2 seconds.'',
     ''mod-sod-hunter'', 1),
    (7003004, 409368, 4, 16, ''Beast Mastery'', ''ability_hunter_beastmastery'',
     ''Your pet's damage and health are increased by 15%, and its Focus regeneration by 50%. In addition, your pet's Growl now also Taunts the target to attack it.'',
     ''mod-sod-hunter'', 1),
    (7003005, 425713, 4, 16, ''Cobra Strikes'', ''ability_hunter_cobrastrikes'',
     ''Your critical hits with Shot and Strike abilities and with Mongoose Bite cause your pet's next 2 special attacks to critically hit.'',
     ''mod-sod-hunter'', 1),
    (7003006, 415370, 4, 16, ''Lone Wolf'', ''ability_hunter_pet_wolf'',
     ''You deal 25% increased damage with all attacks while you do not have an active pet.'',
     ''mod-sod-hunter'', 1),
    (7003007, 415320, 4, 256, ''Flanking Strike'', ''ability_hunter_swiftstrike'',
     ''You and your pet deal simultaneous instant 100% melee damage. Afterward, you deal 8% increased damage for 10 sec, stacking up to 5 times. Your pet's Basic attacks have a 50% chance to reset the cooldown on Flanking Strike.'',
     ''mod-sod-hunter'', 1),
    (7003008, 409593, 4, 256, ''Kill Shot'', ''ability_hunter_assassinate2'',
     ''You attempt to finish off a wounded target with a ranged attack that has no minimum range. Kill Shot's cooldown is reset if used on an enemy that has 20% or less health.'',
     ''mod-sod-hunter'', 1),
    (7003009, 425738, 4, 256, ''Serpent Spread'', ''ability_hunter_serpentswiftness'',
     ''Targets hit by your Multi-Shot are also afflicted by your Serpent Sting.'',
     ''mod-sod-hunter'', 1),
    (7003010, 415399, 4, 256, ''Sniper Training'', ''ability_hunter_snipertraining'',
     ''Your Shot abilities gain increased critical strike chance while you have not moved, stacking up to its maximum. At full stacks your Aimed Shot becomes instant.'',
     ''mod-sod-hunter'', 1),
    (7003011, 425711, 4, 64, ''Carve'', ''ability_warrior_cleave'',
     ''A sweeping attack that strikes all enemies in front of you with your melee weapons for 65% weapon damage. Your primary target takes 50% increased damage.'',
     ''mod-sod-hunter'', 1),
    (7003012, 458393, 4, 64, ''Cobra Slayer'', ''ability_hunter_swiftstrike'',
     ''Mongoose Bite has a chance to activate on each melee attack, rising with each attack and guaranteed when an enemy dodges. Mongoose Bite also deals additional damage equal to a percentage of your Attack Power.'',
     ''mod-sod-hunter'', 1),
    (7003013, 415423, 4, 128, ''Aspect of the Viper'', ''ability_hunter_aspectoftheviper'',
     ''The hunter takes on the aspect of the viper, causing auto attacks to regenerate mana but reducing the total damage done. Only one Aspect can be active at a time.'',
     ''mod-sod-hunter'', 1),
    (7003014, 409504, 4, 128, ''Expose Weakness'', ''ability_hunter_snipershot'',
     ''Your melee and ranged criticals increase your attack power by 5% of your current Agility for 7 sec.'',
     ''mod-sod-hunter'', 1),
    (7003015, 415352, 4, 128, ''Melee Specialist'', ''ability_hunter_swiftstrike'',
     ''Your Raptor Strike is now instant, and Mongoose Bite and Raptor Strike have a 40% chance on each attack to reset the cooldowns of Mongoose Bite and Raptor Strike.'',
     ''mod-sod-hunter'', 1),
    (7003016, 437123, 4, 128, ''Steady Shot'', ''ability_hunter_steadyshot'',
     ''A steady shot that causes 100% ranged weapon damage.'',
     ''mod-sod-hunter'', 1),
    (7003017, 409687, 4, 512, ''Dual Wield Specialization'', ''ability_dualwield'',
     ''Increases the damage done by your offhand weapon by 60% and causes your Raptor Strike to strike with both weapons when dual-wielding.'',
     ''mod-sod-hunter'', 1),
    (7003018, 409541, 4, 512, ''Trap Launcher'', ''spell_frost_stun'',
     ''Your Freezing, Immolation, and Explosive Traps can now be placed at any location within the range of Trap Launcher. Additionally, your Fire-based and Frost-based traps now have separate shared cooldowns.'',
     ''mod-sod-hunter'', 1),
    (7003019, 458479, 4, 512, ''Wyvern Strike'', ''ability_hunter_swiftstrike'',
     ''Replaces Wyvern Sting with Wyvern Strike, a vicious strike that deals weapon damage and causes the target to bleed over time. Requires the Wyvern Sting talent.'',
     ''mod-sod-hunter'', 1),
    (7003020, 415428, 4, 1, ''Catlike Reflexes'', ''ability_hunter_beastmastery'',
     ''Increases your chance to dodge by 20% and your pet's chance to dodge by 9%. In addition, reduces the cooldown of Flanking Strike by 50%.'',
     ''mod-sod-hunter'', 1),
    (7003021, 415413, 4, 1, ''Lock and Load'', ''ability_hunter_mastermarksman'',
     ''Each time you place a trap, your next Shot ability except Scatter Shot costs no mana and does not incur a cooldown.'',
     ''mod-sod-hunter'', 1),
    (7003022, 415405, 4, 1, ''Rapid Killing'', ''ability_hunter_assassinate2'',
     ''Reduces the cooldown on Rapid Fire by 80%. Rapid Fire grants 20% increased melee attack speed, and your next Shot after killing a target worth experience or honor deals 40% increased damage.'',
     ''mod-sod-hunter'', 1),
    (7003023, 428726, 4, 32, ''Focus Fire'', ''ability_hunter_beastmastery'',
     ''Consumes all applications of Frenzy from your pet, increasing your ranged attack speed by 3% and granting your pet 4 Focus per application. Lasts 20 sec. Your pet gains Frenzy each time it uses a Basic Attack.'',
     ''mod-sod-hunter'', 1),
    (7003024, 415358, 4, 32, ''Raptor Fury'', ''ability_hunter_swiftstrike'',
     ''Raptor Strike increases the damage done by Raptor Strike and Mongoose Bite by 10%. The effect stacks. Subsequent doses do not extend its duration.'',
     ''mod-sod-hunter'', 1),
    (7003025, 428717, 4, 32, ''T.N.T.'', ''ability_hunter_assassinate2'',
     ''Increases the damage done by Explosive Shot and all your damaging traps by 9%. Additionally, the initial damage of Explosive Trap and the total periodic damage of your Immolation Trap are increased by 25% of your melee or ranged Attack Power.'',
     ''mod-sod-hunter'', 1),
    (7003026, 440533, 4, 8, ''Hit and Run'', ''ability_hunter_swiftstrike'',
     ''After using Raptor Strike, you gain 100% movement speed for the duration of the effect. Your pet''s damaging abilities increase the target''s melee attack power by 14 and reduce its armor by 50 for the duration of the effect. Rabid enemies will not flee and will ignore Fear and Horror effects.'',
     ''mod-sod-hunter'', 1),
    (7003027, 440520, 4, 8, ''Improved Volley'', ''ability_hunter_steadyshot'',
     ''Reduces the mana cost of Volley by 50%, reduces its cooldown by 100%, increases its damage by 100%, and prevents pushback from damaging attacks. Volley also deals 3% of your ranged Attack Power as additional damage each time it deals damage.'',
     ''mod-sod-hunter'', 1),
    (7003028, 440529, 4, 8, ''Resourcefulness'', ''ability_hunter_snipershot'',
     ''Reduces the mana cost of your Traps by 100% and their cooldowns by 40%.'',
     ''mod-sod-hunter'', 1)
 ON DUPLICATE KEY UPDATE
    `spell_id`    = VALUES(`spell_id`),
    `class_mask`  = VALUES(`class_mask`),
    `slot_mask`   = VALUES(`slot_mask`),
    `name`        = VALUES(`name`),
    `icon`        = VALUES(`icon`),
    `description` = VALUES(`description`),
    `source`      = VALUES(`source`),
    `enabled`     = VALUES(`enabled`)','DO 0');

PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Scripts propios sobre hechizos de SoD de esta tanda. El emisor (sod-client) también escribe
-- las filas de 425713, 415370 y 409593; aquí quedan para que el módulo sea autosuficiente.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (425713, 'spell_hun_cobra_strikes'),
    (415370, 'spell_sod_hunter_lone_wolf'),
    (409593, 'spell_sod_hunter_kill_shot'),
    (415399, 'spell_sod_hunter_sniper_training'),
    (425711, 'spell_sod_hunter_carve'),
    (458393, 'spell_sod_hunter_cobra_slayer');

-- Aspecto de la víbora reutiliza el manejador nativo de WotLK sobre el hechizo clonado.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`)
VALUES (415423, 'spell_hun_ascpect_of_the_viper');

-- Ganchos de la segunda tanda sobre hechizos de WotLK (id negativo = todos los rangos).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-2643, 'spell_sod_hunter_serpent_spread'),
    (-1495, 'spell_sod_hunter_cobra_slayer_mongoose_bite');

-- Tercera tanda: reinicios de Mordedura de mangosta y Golpe de raptor (id negativo = todos
-- los rangos) y el segundo ataque de Golpe de raptor con mano izquierda.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (415352, 'spell_sod_hunter_melee_specialist'),
    (-1495, 'spell_sod_hunter_melee_specialist_mongoose_bite'),
    (-2973, 'spell_sod_hunter_melee_specialist_raptor_strike'),
    (-2973, 'spell_sod_hunter_dual_wield_specialization_raptor_strike');

-- Bestialidad hace que el Bramido de la mascota provoque al objetivo (id negativo = todos los
-- rangos de 2649).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-2649, 'spell_sod_hunter_beast_mastery_growl');

-- Aura de mascota de Bestialidad: el familiar la recibe al tener la runa (spell_pet_auras es
-- tabla base del core). No se toca ninguna fila de Blizzard: sólo se inserta la nuestra.
DELETE FROM `spell_pet_auras` WHERE `spell` IN (409368);
INSERT INTO `spell_pet_auras` (`spell`, `effectId`, `pet`, `aura`) VALUES
    (409368, 0, 0, 900056);

-- Reflejos felinos mejora la esquiva del familiar; Enfocar fuego le da el proc de sus ataques básicos.
DELETE FROM `spell_pet_auras` WHERE `spell` IN (415428, 428726);
INSERT INTO `spell_pet_auras` (`spell`, `effectId`, `pet`, `aura`) VALUES
    (415428, 0, 0, 900061),
    (428726, 0, 0, 900063);

-- Ganchos propios y nativo copiado para la cuarta tanda del cazador.
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (458479, 'spell_sod_hunter_wyvern_strike'),
    (415320, 'spell_sod_hunter_catlike_reflexes'),
    (415413, 'spell_hun_lock_and_load'),
    (900062, 'spell_sod_hunter_rapid_killing_rapid_fire_buff'),
    (428726, 'spell_sod_hunter_focus_fire');

-- Salva mejorada suma daño a cada impacto de Volley (id negativo = todos los rangos del trigger).
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
    (-42243, 'spell_sod_hunter_improved_volley');
