-- (44937) Training Dummy
SET @TDUMMY = 44937;

DELETE FROM creature_template WHERE entry=@TDUMMY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(@TDUMMY, 0, 0, 0, 0, 0, 3019, 0, 0, 0, 'Training Dummy', '', '', 0, 3, 3, 0, 7, 7, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 131072, 132, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 15595);

DELETE FROM creature WHERE id=@TDUMMY AND map=530;
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, MovementType) VALUES
(XXXXX, @TDUMMY, 530, 1, 1, 10373.3, -6377.87, 37.28583, 1.291544, 120, 0, 0),
(XXXXX, @TDUMMY, 530, 1, 1, 10334.4, -6386.11, 36.51433, 2.391101, 120, 0, 0),
(XXXXX, @TDUMMY, 530, 1, 1, 10381.8, -6381.9, 37.83083, 0.9773844, 120, 0, 0),
(XXXXX, @TDUMMY, 530, 1, 1, 10328.4, -6393.98, 37.14723, 2.635447, 120, 0, 0),
(XXXXX, @TDUMMY, 530, 1, 1, 10325, -6403.6, 37.23173, 2.932153, 120, 0, 0);
-- GUID WILL BY ADDED LATER BY ARIDEV AT FULL RELEASE OF SKYFIREDB 434

DELETE FROM creature_template_addon WHERE entry=@TDUMMY;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@TDUMMY, 0, 0, 0, 1, 0, '83470');
