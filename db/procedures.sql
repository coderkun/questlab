DROP PROCEDURE IF EXISTS update_cache_characters_quest;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_characters_quest(
	IN QUESTID INT(11)
)
BEGIN
	DECLARE CHARACTERID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE characters_cursor CURSOR FOR
		SELECT character_id
		FROM quests_characters
		WHERE quest_id = QUESTID AND status = 3;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN characters_cursor;
	get_characters: LOOP
		FETCH characters_cursor INTO CHARACTERID;
		IF done = TRUE THEN
			LEAVE get_characters;
		END IF;
		CALL update_cache_characters(CHARACTERID);
	END LOOP get_characters;
END $$
DELIMITER ;


DROP PROCEDURE IF EXISTS update_cache_characters_charactergroup;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_characters_charactergroup(
	IN CHARACTERGROUPID INT(11)
)
BEGIN
	DECLARE CHARACTERID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE characters_cursor CURSOR FOR
		SELECT character_id
		FROM characters_charactergroups
		WHERE charactergroup_id = CHARACTERGROUPID;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN characters_cursor;
	get_characters: LOOP
		FETCH characters_cursor INTO CHARACTERID;
		IF done = TRUE THEN
			LEAVE get_characters;
		END IF;
		CALL update_cache_characters(CHARACTERID);
	END LOOP get_characters;
END $$
DELIMITER ;


DROP PROCEDURE IF EXISTS update_cache_characters_xplevels;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_characters_xplevels(
    IN SEMINARYID INT(11),
    IN XPS_LOWER INT(11),
    IN XPS_UPPER INT(11)
)
BEGIN
    DECLARE CHARACTERID INT;
    DECLARE done INT DEFAULT FALSE;
    DECLARE characters_cursor CURSOR FOR
        SELECT cache_characters.character_id
        FROM charactertypes
        INNER JOIN characters ON characters.charactertype_id = charactertypes.id
        INNER JOIN cache_characters ON cache_characters.character_id = characters.id
        WHERE charactertypes.seminary_id = SEMINARY_ID AND cache_characters.xps >= LEAST(XPS_LOWER, IFNULL(XPS_UPPER,XPS_LOWER)) AND (XPS_UPPER IS NULL OR cache_characters.xps <= GREATEST(XPS_LOWER, XPS_UPPER));
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    -- Get upper XPs
    IF XPS_UPPER IS NULL THEN
        SELECT MIN(xps) INTO XPS_UPPER
        FROM xplevels
        WHERE seminary_id = SEMINARYID AND xps > XPS_LOWER;
    END IF;

    SET done = 0;
    OPEN characters_cursor;
    get_characters: LOOP
        FETCH characters_cursor INTO CHARACTERID;
        IF done = TRUE THEN
            LEAVE get_characters;
        END IF;
        CALL update_cache_characters(CHARACTERID);
    END LOOP get_characters;
END $$
DELIMITER ;


DROP PROCEDURE IF EXISTS update_cache_characters;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_characters(
	IN CHARACTERID INT(11)
)
BEGIN
	DECLARE QUESTXPS INT UNSIGNED;
	DECLARE GROUPSXPS INT UNSIGNED;
	DECLARE TOTALXPS INT UNSIGNED;
	DECLARE XPLEVELID INT;
	DECLARE AVATARID INT;
	
	/* XPs */
	SELECT IFNULL(SUM(quests.xps),0) INTO QUESTXPS
	FROM quests_characters
	LEFT JOIN quests ON quests.id = quests_characters.quest_id
	WHERE quests_characters.character_id = CHARACTERID AND quests_characters.status = 3;
	SELECT IFNULL(SUM(cache_charactergroups.xps),0) INTO GROUPSXPS
	FROM characters_charactergroups
	LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = characters_charactergroups.charactergroup_id
	WHERE characters_charactergroups.character_id = CHARACTERID;
	SET TOTALXPS = QUESTXPS + GROUPSXPS;

	/* XP-level */
	SELECT (
		SELECT id
		FROM xplevels
		WHERE seminary_id = charactertypes.seminary_id AND xps = (
			SELECT MAX(xplevels_sub.xps)
			FROM xplevels AS xplevels_sub
			WHERE xplevels_sub.seminary_id = charactertypes.seminary_id AND xps <= TOTALXPS
		)
	) INTO XPLEVELID
	FROM characters
	LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id
	WHERE characters.id = CHARACTERID;
	
	/* Avatar */
	SELECT avatars.id INTO AVATARID
	FROM characters
	LEFT JOIN avatars ON avatars.charactertype_id = characters.charactertype_id AND avatars.xplevel_id = XPLEVELID
	WHERE characters.id = CHARACTERID;
	
	/* Set values */
	REPLACE INTO cache_characters
	(character_id, xps, quest_xps, xplevel_id, avatar_id)
	VALUES
	(CHARACTERID, TOTALXPS, QUESTXPS, XPLEVELID, AVATARID);
END $$
DELIMITER ;




DROP PROCEDURE IF EXISTS update_cache_charactergroups_charactergroupsquest;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_charactergroups_charactergroupsquest(
	IN CHARACTERGROUPSQUESTID INT(11)
)
BEGIN
	DECLARE CHARACTERGROUPID INT;
	DECLARE done INT DEFAULT FALSE;
	DECLARE charactergroups_cursor CURSOR FOR
		SELECT charactergroup_id
		FROM charactergroupsquests_groups
		WHERE charactergroupsquest_id = CHARACTERGROUPSQUESTID;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
	SET done = 0;
	OPEN charactergroups_cursor;
	get_charactergroups: LOOP
		FETCH charactergroups_cursor INTO CHARACTERGROUPID;
		IF done = TRUE THEN
			LEAVE get_charactergroups;
		END IF;
		CALL update_cache_charactergroups(CHARACTERGROUPID);
	END LOOP get_charactergroups;
END $$
DELIMITER ;


DROP PROCEDURE IF EXISTS update_cache_charactergroups;
DELIMITER $$
CREATE DEFINER = 'questlab'@'localhost' PROCEDURE update_cache_charactergroups(
	IN CHARACTERGROUPID INT(11)
)
BEGIN
	/* XPs */
	REPLACE INTO cache_charactergroups
	(charactergroup_id, xps)
	SELECT charactergroups.id, IFNULL(SUM(ROUND(charactergroupsquests.xps * charactergroupsquests_groups.xps_factor)),0) AS xps
	FROM charactergroups
	LEFT JOIN charactergroupsquests_groups ON charactergroupsquests_groups.charactergroup_id = charactergroups.id
	LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id
	WHERE charactergroups.id = CHARACTERGROUPID;
END $$
DELIMITER ;
