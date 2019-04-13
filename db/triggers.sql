/** Characters + Quests **/

DROP TRIGGER IF EXISTS update_cache_characters_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_insert`
AFTER INSERT ON characters
FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_quests_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_quests_update`
AFTER UPDATE ON quests
FOR EACH ROW BEGIN
	CALL update_cache_characters_quest(NEW.id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_quests_characters_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_quests_characters_insert`
AFTER INSERT ON quests_characters
FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.character_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_quests_characters_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_quests_characters_update`
AFTER UPDATE ON quests_characters
FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
	CALL update_cache_characters(NEW.character_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_quests_characters_delete;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_quests_characters_delete`
AFTER DELETE ON quests_characters
FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
END $$
DELIMITER ;




/** Charactergroups + Charactergroupsquests **/

DROP TRIGGER IF EXISTS update_cache_charactergroups_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_charactergroups_insert`
AFTER INSERT ON charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(NEW.id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_charactergroupsquests_update`
AFTER UPDATE ON charactergroupsquests
FOR EACH ROW BEGIN
	CALL update_cache_charactergroups_charactergroupsquest(NEW.id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_charactergroupsquests_groups_insert`
AFTER INSERT ON charactergroupsquests_groups
FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(NEW.charactergroup_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_charactergroupsquests_groups_update`
AFTER UPDATE ON charactergroupsquests_groups
FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(OLD.charactergroup_id);
	CALL update_cache_charactergroups(NEW.charactergroup_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_charactergroupsquests_groups_delete;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_charactergroupsquests_groups_delete`
AFTER DELETE ON charactergroupsquests_groups
FOR EACH ROW BEGIN
	CALL update_cache_charactergroups(OLD.charactergroup_id);
END $$
DELIMITER ;




/** Characters + Charactergroups **/

DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_charactergroups_insert`
AFTER INSERT ON characters_charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_characters(NEW.character_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_charactergroups_update`
AFTER UPDATE ON characters_charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
	CALL update_cache_characters(NEW.character_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_characters_charactergroups_delete;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_charactergroups_delete`
AFTER DELETE ON characters_charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_characters(OLD.character_id);
END $$
DELIMITER ;




/** Cache Charactergroups **/

DROP TRIGGER IF EXISTS update_cache_cache_charactergroups_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_cache_charactergroups_insert`
AFTER INSERT ON cache_charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_characters_charactergroup(NEW.charactergroup_id);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_cache_charactergroups_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_cache_charactergroups_update`
AFTER UPDATE ON cache_charactergroups
FOR EACH ROW BEGIN
	CALL update_cache_characters_charactergroup(NEW.charactergroup_id);
END $$
DELIMITER ;




/** XP-levels **/

DROP TRIGGER IF EXISTS update_cache_characters_xplevels_insert;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_xplevels_insert`
AFTER INSERT ON xplevels
FOR EACH ROW BEGIN
    CALL update_cache_characters_xplevels(NEW.seminary_id, NEW.xps, NULL);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_characters_xplevels_update;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_xplevels_update`
AFTER UPDATE ON xplevels
FOR EACH ROW BEGIN
    CALL update_cache_characters_xplevels(NEW.seminary_id, OLD.xps, NEW.xps);
END $$
DELIMITER ;

DROP TRIGGER IF EXISTS update_cache_characters_xplevels_delete;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' TRIGGER `update_cache_characters_xplevels_delete`
AFTER DELETE ON xplevels
FOR EACH ROW BEGIN
    CALL update_cache_characters_xplevels(OLD.seminary_id, OLD.xps, NULL);
END $$
DELIMITER ;
