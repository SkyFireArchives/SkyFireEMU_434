###############
# SPELL_RANKS #
###############
-- REMOVE: Arcane Intellect Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=1472;

-- REMOVE: Bite Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=17254;

-- REMOVE: Prowl Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=24451;

-- REMOVE: Surge of Light Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=33150;

-- REMOVE: Prayer of Mending Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=41635;

-- REMOVE: Blade Barrier Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=51789;

-- REMOVE: Wilder Quiver <NNF> Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=53215;

-- UPDATE: Tactical Mastery Spell_Ranks
DELETE FROM spell_ranks WHERE first_spell_id=12295;
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES
(12295, 12295, 1),
(12295, 12676, 2);

####################
# SPELL_PROC_EVENT #
####################

-- REMOVE: Surge of Light Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=33150;

-- REMOVE: Surge of Light Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=33151;

-- REMOVE: Surge of Light Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=33154;

-- REMOVE: Prayer of Mending Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=48110;

-- REMOVE: Prayer of Mending Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=48111;

-- REMOVE: Wilder Quiver Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=53216;

-- REMOVE: Lock Jaw Spell_Proc_Event
DELETE FROM spell_proc_event WHERE entry=48628;

######################
# SPELL_LINKED_SPELL #
######################

-- REMOVE: Burn Spell_Linked_Spell
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=45246;

-- REMOVE: Hungering Cold Spell_Linked_Spell
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=51209;

###################
# FIXED BY ARIDEV #
###################

