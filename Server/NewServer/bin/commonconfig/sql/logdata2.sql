


DROP PROCEDURE IF EXISTS `check_version_1`;
DROP PROCEDURE IF EXISTS `update_2`;

CREATE PROCEDURE check_version_1(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 1 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_2()
BEGIN
	DECLARE ret INT;
	CALL check_version_1(ret);
	IF ret = 1 THEN
		DROP TABLE IF EXISTS `logdata_item`;
		CREATE TABLE `logdata_item` (
		  `LogTime` datetime NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `RoleID` int(4) unsigned NOT NULL,
		  `ActionType` varchar(4) NOT NULL,
		  `Guid` bigint(8) unsigned NOT NULL,
		  `TemplateID` int(4) unsigned NOT NULL,
		  `ItemCount` int(4) NOT NULL,
		  `Reason` varchar(30) NOT NULL,
		  `UserDefinedID` bigint(8) unsigned NOT NULL
		);

		UPDATE version SET number = 2 where id = 'all';
	END IF;
END;

CALL update_2();

DROP PROCEDURE IF EXISTS `check_version_1`;
DROP PROCEDURE IF EXISTS `update_2`;
