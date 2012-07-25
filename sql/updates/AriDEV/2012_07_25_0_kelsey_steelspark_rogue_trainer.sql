-- (42366) Kelsey Steelspark <Rogue Trainer>
SET @Kelsey = 42366;
SET @GKelsey = XXXXX;  -- GUID WILL BY ADDED LATER BY ARIDEV AT FULL RELEASE OF SKYFIREDB 434

DELETE FROM creature WHERE id=@Kelsey;
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, MovementType) VALUES
(@GKelsey, @Kelsey, 0, 1, 1, -5141.02, 502.714, 395.6284, 5.445427, 120, 0, 0);


DELETE FROM creature_template WHERE entry=@Kelsey;
INSERT INTO creature_template (entry, difficulty_entry_1, difficulty_entry_2, difficulty_entry_3, KillCredit1, KillCredit2, modelid1, modelid2, modelid3, modelid4, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, exp, exp_unk, faction_A, faction_H, npcflag, speed_walk, speed_run, scale, rank, mindmg, maxdmg, dmgschool, attackpower, dmg_multiplier, baseattacktime, rangeattacktime, unit_class, unit_flags, dynamicflags, family, trainer_type, trainer_spell, trainer_class, trainer_race, minrangedmg, maxrangedmg, rangedattackpower, type, type_flags, type_flags2, lootid, pickpocketloot, skinloot, resistance1, resistance2, resistance3, resistance4, resistance5, resistance6, spell1, spell2, spell3, spell4, spell5, spell6, spell7, spell8, PetSpellDataId, VehicleId, mingold, maxgold, AIName, MovementType, InhabitType, HoverHeight, Health_mod, Mana_mod, Armor_mod, RacialLeader, questItem1, questItem2, questItem3, questItem4, questItem5, questItem6, movementId, RegenHealth, equipment_id, mechanic_immune_mask, flags_extra, ScriptName, WDBVerified) VALUES
(@Kelsey, 0, 0, 0, 0, 0, 31159, 0, 0, 0, 'Kelsey Steelspark', 'Rogue Trainer', '', 11621, 20, 20, 3, 0, 875, 875, 51, 1, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 4, 33024, 2048, 0, 0, 0, 4, 0, 0, 0, 0, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 26, '', 0, 3, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 42366, 0, 0, '', 15595);

DELETE FROM npc_trainer WHERE entry=@Kelsey;
INSERT INTO npc_trainer (entry, spell, spellcost, reqskill, reqskillvalue, reqlevel) VALUES
(@Kelsey, 1784, 135, 0, 0, 5), -- Stealth
(@Kelsey, 2098, 57, 0, 0, 3); -- Eviscerate

DELETE FROM gossip_menu WHERE entry=11621 AND text_id=16229;
INSERT INTO gossip_menu (entry, text_id) VALUES
(11621, 16229);

DELETE FROM gossip_menu_option WHERE  menu_id=11621 AND id=0;
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, box_coded, box_money, box_text) VALUES
(11621, 0, 3, 'I require rogue training.', 0, 0, '');
