DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;

CREATE PROCEDURE check_version(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 4 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_db()
BEGIN
	DECLARE ret INT;
	CALL check_version(ret);
	IF ret = 1 THEN
		CREATE TABLE `logdata_servermonitor_item` (
			`LogTime` datetime NOT NULL,
			`AreaID` smallint NOT NULL,
			`GroupID` tinyint NOT NULL,
			`TemplateID` int NOT NULL,
			`ProduceCount` bigint NOT NULL,
			`DestroyCount` bigint NOT NULL
		);

		UPDATE version SET number = 5 where id = 'all';
	END IF;
END;

CALL update_db();

DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;
