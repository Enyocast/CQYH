DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;

CREATE PROCEDURE check_version(OUT ret INT)
BEGIN
	DECLARE ver INT;
	SET ret = 0;
	SELECT number INTO ver FROM `version` WHERE id = 'all';
	IF ver = 0 THEN
		SET ret = 1;
	END IF;
END;

CREATE PROCEDURE update_db()
BEGIN
	DECLARE ret INT;
	CALL check_version(ret);
	IF ret = 1 THEN
		CREATE TABLE `arena` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `Fund` bigint(10) unsigned DEFAULT NULL,
		  `Rank` blob
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `auction` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `AuctionID` int(11) NOT NULL,
		  `Seller` int(11) NOT NULL,
		  `Buyer` int(11) NOT NULL,
		  `Price` int(11) NOT NULL,
		  `BuyoutPrice` int(11) NOT NULL,
		  `FinishTime` datetime NOT NULL,
		  `ItemBuffer` varbinary(64) NOT NULL,
		  PRIMARY KEY (`AuctionID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `exchange_history` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `HistoryTime` datetime NOT NULL,
		  `Open` int(10) NOT NULL,
		  `Close` int(10) NOT NULL,
		  `High` int(10) NOT NULL,
		  `Low` int(10) NOT NULL,
		  `Volume` int(10) NOT NULL,
		  `TotalPrice` bigint(20) NOT NULL,
		  PRIMARY KEY (`GroupID`,`HistoryTime`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `exchange_log` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `ExchangeTime` datetime NOT NULL,
		  `SellerRoleID` int(10) unsigned NOT NULL,
		  `SellerOrderID` bigint(20) unsigned NOT NULL,
		  `BuyerRoleID` int(10) unsigned NOT NULL,
		  `BuyerOrderID` bigint(20) unsigned NOT NULL,
		  `Price` int(11) NOT NULL,
		  `Count` int(11) NOT NULL,
		  KEY `IdxExchangeTime` (`ExchangeTime`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `exchange_order` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `OrderID` bigint(20) unsigned NOT NULL,
		  `OrderTime` datetime NOT NULL,
		  `OrderType` tinyint(3) unsigned NOT NULL,
		  `OrderStatus` tinyint(3) unsigned NOT NULL,
		  `RoleID` int(10) unsigned NOT NULL,
		  `Price` int(11) NOT NULL,
		  `Count` int(11) NOT NULL,
		  `CurCount` int(11) NOT NULL,
		  `CurMoney` int(11) NOT NULL,
		  `BillingOrderID` varchar(32) NOT NULL,
		  PRIMARY KEY (`OrderID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `friend` (
		  `GroupID` tinyint(3) NOT NULL,
		  `RoleID` int(4) unsigned NOT NULL,
		  `FriendID` int(4) unsigned NOT NULL,
		  `FriendGroup` tinyint(3) NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  PRIMARY KEY (`RoleID`,`FriendID`),
		  KEY `IDX_RoleID` (`RoleID`),
		  KEY `IDX_FriendID` (`FriendID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `gm` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `ID` bigint(10) unsigned NOT NULL,
		  `Time` datetime NOT NULL,
		  PRIMARY KEY (`ID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `group_ms` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `RegisterIp` varchar(32) NOT NULL,
		  `RegisterTime` datetime NOT NULL
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `guild` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `GuildID` int(4) unsigned NOT NULL,
		  `Version` smallint(5) unsigned NOT NULL,
		  `GuildName` varchar(25) NOT NULL,
		  `LeaderID` int(4) unsigned NOT NULL,
		  `CreaterName` varchar(21) NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `Announce` varchar(100) NOT NULL,
		  `Notice` varchar(200) NOT NULL DEFAULT '',
		  `MainData` blob NOT NULL,
		  PRIMARY KEY (`GuildID`),
		  UNIQUE KEY `GuildName` (`GuildName`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `guild_member` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `RoleID` int(4) unsigned NOT NULL,
		  `GuildID` int(4) unsigned NOT NULL,
		  `Position` tinyint(1) unsigned NOT NULL,
		  `Flag` tinyint(1) unsigned NOT NULL,
		  `Salary` int(4) NOT NULL,
		  `DrawSalaryTime` datetime NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  `Pow` int(4) NOT NULL DEFAULT '0',
		  PRIMARY KEY (`RoleID`),
		  KEY `guild` (`GuildID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `guild_war` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `IntruderID` int(11) unsigned NOT NULL,
		  `DefenderID` int(11) unsigned NOT NULL,
		  `BeginDayTime` datetime NOT NULL
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `mail` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `MailID` int(10) unsigned NOT NULL,
		  `MailTime` datetime NOT NULL,
		  `SenderRoleID` int(10) unsigned NOT NULL,
		  `ReceiverRoleID` int(10) unsigned NOT NULL,
		  `MailType` tinyint(3) unsigned NOT NULL,
		  `IsNew` tinyint(3) unsigned NOT NULL DEFAULT '1',
		  `AttachLocked` tinyint(3) unsigned NOT NULL DEFAULT '0',
		  `MailSubject` varchar(60) NOT NULL,
		  `MailContent` varchar(420) NOT NULL,
		  `AttachType` tinyint(3) unsigned NOT NULL,
		  `Attach` binary(64) NOT NULL,
		  PRIMARY KEY (`MailID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `master` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `TeacherID` int(10) unsigned NOT NULL,
		  `StudentID` int(10) unsigned NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  PRIMARY KEY (`TeacherID`,`StudentID`),
		  UNIQUE KEY `student_id` (`StudentID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `master_cz` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `ID` bigint(10) unsigned NOT NULL,
		  `cz` tinyint(1) unsigned NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
		  PRIMARY KEY (`ID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `ranklist` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `RankListType` int(4) NOT NULL,
		  `RankKey` bigint(20) NOT NULL,
		  `RankValue` bigint(20) NOT NULL,
		  `UpdateTime` datetime NOT NULL,
		  `LastRank` int(4) NOT NULL DEFAULT '0',
		  PRIMARY KEY (`GroupID`,`RankListType`,`RankKey`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `role` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `RoleID` int(4) unsigned NOT NULL,
		  `RoleName` varchar(12) NOT NULL,
		  `UserName` varchar(64) NOT NULL,
		  `CreateTime` datetime NOT NULL,
		  `DeleteTime` datetime NOT NULL,
		  `LoginTime` datetime NOT NULL,
		  `RoleDeleted` tinyint(1) NOT NULL,
		  `BaseData` blob NOT NULL,
		  `RoleData` blob NOT NULL,
		  PRIMARY KEY (`RoleID`),
		  UNIQUE KEY `RoleName` (`RoleName`),
		  KEY `IdxUserName` (`UserName`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `shop_log` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `RoleID` int(11) NOT NULL,
		  `ItemTemplateID` int(11) NOT NULL,
		  `ItemCount` int(11) NOT NULL,
		  `Cost` int(11) NOT NULL,
		  `ShopTime` datetime NOT NULL,
		  KEY `IDX_RoleID` (`RoleID`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
		
		CREATE TABLE `variable` (
		  `GroupID` tinyint(3) unsigned NOT NULL,
		  `VarIndex` bigint(20) NOT NULL,
		  `VarValue` int(11) NOT NULL,
		  PRIMARY KEY (`GroupID`,`VarIndex`)
		) ENGINE=InnoDB DEFAULT CHARSET=utf8;

		UPDATE version SET number = 1 where id = 'all';
	END IF;
END;

CALL update_db();

DROP PROCEDURE IF EXISTS `check_version`;
DROP PROCEDURE IF EXISTS `update_db`;


DROP PROCEDURE IF EXISTS `move_data`;
DROP PROCEDURE IF EXISTS `move_group`;

DELIMITER $$

CREATE PROCEDURE move_data(IN dbname VARCHAR(64), IN groupid TINYINT, IN tblname VARCHAR(64))
BEGIN
  SET @s = CONCAT('INSERT INTO ', dbname, '.', tblname, ' SELECT * FROM ', tblname, ' WHERE GroupID=', groupid, ';');
  PREPARE stmt FROM @s;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
  
  SET @s = CONCAT('DELETE FROM ', tblname, ' WHERE GroupID=', groupid, ';');
  PREPARE stmt FROM @s;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
END$$

CREATE PROCEDURE move_group(IN dbname VARCHAR(64), IN groupid TINYINT)
BEGIN
  CALL move_data(dbname, groupid, 'arena');
  CALL move_data(dbname, groupid, 'auction');
  CALL move_data(dbname, groupid, 'exchange_history');
  CALL move_data(dbname, groupid, 'exchange_log');
  CALL move_data(dbname, groupid, 'exchange_order');
  CALL move_data(dbname, groupid, 'friend');
  CALL move_data(dbname, groupid, 'gm');
  CALL move_data(dbname, groupid, 'guild');
  CALL move_data(dbname, groupid, 'guild_member');
  CALL move_data(dbname, groupid, 'guild_war');
  CALL move_data(dbname, groupid, 'mail');
  CALL move_data(dbname, groupid, 'master');
  CALL move_data(dbname, groupid, 'master_cz');
  CALL move_data(dbname, groupid, 'ranklist');
  CALL move_data(dbname, groupid, 'role');
  CALL move_data(dbname, groupid, 'shop_log');
  CALL move_data(dbname, groupid, 'variable');
END$$

DELIMITER ;