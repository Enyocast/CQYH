DROP PROCEDURE IF EXISTS `check_version_0`;
DROP PROCEDURE IF EXISTS `update_1`;

CREATE PROCEDURE check_version_0(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 0 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_1()
BEGIN
	DECLARE ret INT;
	CALL check_version_0(ret);
	IF ret = 1 THEN
		CREATE TABLE `logdata_accountlogin` (
		  `LogTime` datetime NOT NULL,
		  `GroupID` tinyint(1) unsigned NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `SndaID` varchar(64) NOT NULL,
		  `Action` varchar(10) NOT NULL,
		  `IP` varchar(18) NOT NULL
		);

		CREATE TABLE `logdata_gm` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `RoleID` int(4) NOT NULL,
		  `RoleName` varchar(21) NOT NULL,
		  `Command` varchar(128) NOT NULL,
		  `Result` tinyint(1) NOT NULL
		);

		CREATE TABLE `logdata_item` (
		  `LogTime` datetime NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `ActionType` varchar(10) NOT NULL,
		  `TemplateID` int(4) unsigned NOT NULL,
		  `Guid` bigint(8) NOT NULL,
		  `ItemCount` tinyint(1) NOT NULL,
		  `SrcRoleID` int(4) NOT NULL,
		  `TargetRoleID` int(4) NOT NULL,
		  `Reason` varchar(30) NOT NULL
		);

		CREATE TABLE `logdata_money` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `SourceID` int(4) NOT NULL,
		  `TargetID` int(4) NOT NULL,
		  `Reason` varchar(32) NOT NULL,
		  `Param` tinyint(1) NOT NULL,
		  `Action` varchar(4) NOT NULL,
		  `MoneyType` tinyint(1) NOT NULL,
		  `MoneyCount` int(4) NOT NULL
		);

		CREATE TABLE `logdata_quest` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `RoleID` int(4) NOT NULL,
		  `QuestID` int(4) NOT NULL,
		  `Action` varchar(8) NOT NULL,
		  `Type` varchar(6) NOT NULL,
		  `QuestName` varchar(20) CHARACTER SET utf8 NOT NULL
		);

		CREATE TABLE `logdata_rolelogout_basic` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `RoleID` int(4) NOT NULL,
		  `SndaID` varchar(32) NOT NULL,
		  `SceneTemplateID` int(4) NOT NULL,
		  `SceneID` int(4) NOT NULL,
		  `Name` varchar(21) NOT NULL,
		  `Class` varchar(16) NOT NULL,
		  `Sex` varchar(16) NOT NULL,
		  `Level` tinyint(1) NOT NULL,
		  `Experience` int(4) NOT NULL,
		  `Money1` int(4) NOT NULL,
		  `Money2` int(4) NOT NULL,
		  `X` int(4) NOT NULL,
		  `Y` int(4) NOT NULL,
		  `Z` int(4) NOT NULL
		);

		CREATE TABLE `logdata_servermonitor_consecutivekillnpc` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `Level5_9` bigint(8) NOT NULL,
		  `Level10_14` bigint(8) NOT NULL,
		  `Level15_19` bigint(8) NOT NULL,
		  `Level20_24` bigint(8) NOT NULL,
		  `Level25_29` bigint(8) NOT NULL,
		  `Level30_34` bigint(8) NOT NULL,
		  `Level35_39` bigint(8) NOT NULL,
		  `Level40_44` bigint(8) NOT NULL,
		  `Level45_49` bigint(8) NOT NULL,
		  `Level50_54` bigint(8) NOT NULL,
		  `Level55_59` bigint(8) NOT NULL,
		  `Level60_64` bigint(8) NOT NULL,
		  `Level65_69` bigint(8) NOT NULL,
		  `Level70_74` bigint(8) NOT NULL,
		  `Level75_79` bigint(8) NOT NULL,
		  `Level80_84` bigint(8) NOT NULL,
		  `Level85_89` bigint(8) NOT NULL,
		  `Level90_94` bigint(8) NOT NULL,
		  `Level95_99` bigint(8) NOT NULL
		);

		CREATE TABLE `logdata_servermonitor_momentarykillnpc` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `Level5` bigint(8) NOT NULL,
		  `Level6` bigint(8) NOT NULL,
		  `Level7` bigint(8) NOT NULL,
		  `Level8` bigint(8) NOT NULL,
		  `Level9` bigint(8) NOT NULL,
		  `Level10` bigint(8) NOT NULL,
		  `Level11` bigint(8) NOT NULL,
		  `Level12` bigint(8) NOT NULL,
		  `Level13` bigint(8) NOT NULL,
		  `Level14` bigint(8) NOT NULL,
		  `Level15` bigint(8) NOT NULL,
		  `Level16` bigint(8) NOT NULL,
		  `Level17` bigint(8) NOT NULL,
		  `Level18` bigint(8) NOT NULL
		);

		CREATE TABLE `logdata_servermonitor_money` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `ProduceMoney01` bigint(8) NOT NULL,
		  `ProduceMoney02` bigint(8) NOT NULL,
		  `DestroyMoney01` bigint(8) NOT NULL,
		  `DestroyMoney02` bigint(8) NOT NULL
		);

		CREATE TABLE `logdata_servermonitor_npcdie` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `NpcID` bigint(8) NOT NULL,
		  `DieCount` bigint(8) NOT NULL
		);

		CREATE TABLE `logdata_servermonitor_questcomplete` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `CompleteCount` bigint(8) NOT NULL
		);
		
		CREATE TABLE `logdata_servermonitor_realmoney` (
		  `LogTime` datetime NOT NULL,
		  `AreaID` smallint(6) NOT NULL,
		  `GroupID` tinyint(1) NOT NULL,
		  `RealMoneyToMoney02` bigint(8) NOT NULL,
		  `RealMoneyToItem` bigint(8) NOT NULL
		);

		UPDATE version SET number = 1 where id = 'all';
	END IF;
END;

CALL update_1();

DROP PROCEDURE IF EXISTS `check_version_0`;
DROP PROCEDURE IF EXISTS `update_1`;
