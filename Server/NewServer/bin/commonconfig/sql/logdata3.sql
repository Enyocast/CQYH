


DROP PROCEDURE IF EXISTS `check_version_2`;
DROP PROCEDURE IF EXISTS `update_3`;

CREATE PROCEDURE check_version_2(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 2 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_3()
BEGIN
	DECLARE ret INT;
	CALL check_version_2(ret);
	IF ret = 1 THEN
		ALTER TABLE `logdata_item` MODIFY COLUMN `ActionType` varchar(20) NOT NULL AFTER `RoleID`;

		UPDATE version SET number = 3 where id = 'all';
	END IF;
END;

CALL update_3();

DROP PROCEDURE IF EXISTS `check_version_2`;
DROP PROCEDURE IF EXISTS `update_3`;
