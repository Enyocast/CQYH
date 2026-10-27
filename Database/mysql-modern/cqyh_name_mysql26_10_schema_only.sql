-- SCHEMA ONLY: matching structure for cqyh_name_mysql26_10_data_only.sql.
-- No seed rows; import the data-only file afterward.
-- CQYH_NAME database installer - modern MySQL
-- Live-tested on MySQL 9.7.1 with the default strict SQL mode enabled.
-- Source files originally exported from MySQL 5.1.56.
-- WARNING: This fresh-install script contains DROP TABLE IF EXISTS statements.
--          Importing it into a populated cqyh_name database DESTROYS existing data.
--          Take a backup and run only against a fresh/test database.
-- Dates previously using 0000-00-00 for "not deleted" are migrated to NULL.
-- The game-server code must likewise use NULL rather than writing zero dates.
-- Original table and account variants are intentionally preserved.

SET NAMES utf8mb4;
CREATE DATABASE IF NOT EXISTS `cqyh_name` CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `cqyh_name`;

SET @cqyh_previous_foreign_key_checks = @@FOREIGN_KEY_CHECKS;
SET FOREIGN_KEY_CHECKS = 0;




-- ----------------------------
-- Table structure for arena
-- ----------------------------
DROP TABLE IF EXISTS `arena`;
CREATE TABLE `arena`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `Fund` bigint UNSIGNED NULL DEFAULT NULL,
  `Rank` blob NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of arena
-- ----------------------------

-- ----------------------------
-- Table structure for auction
-- ----------------------------
DROP TABLE IF EXISTS `auction`;
CREATE TABLE `auction`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `AuctionID` int UNSIGNED NOT NULL,
  `Seller` int UNSIGNED NOT NULL,
  `Buyer` int UNSIGNED NOT NULL,
  `Price` bigint NOT NULL,
  `BuyoutPrice` bigint NOT NULL,
  `DepositPrice` bigint NOT NULL,
  `StartTime` datetime NOT NULL,
  `FinishTime` datetime NOT NULL,
  `Open` tinyint UNSIGNED NOT NULL,
  `AuctionStatus` tinyint UNSIGNED NOT NULL,
  `ItemBuffer` varbinary(64) NOT NULL,
  `ItemDetail` varchar(1024) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`AuctionID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of auction
-- ----------------------------

-- ----------------------------
-- Table structure for auction_deposit
-- ----------------------------
DROP TABLE IF EXISTS `auction_deposit`;
CREATE TABLE `auction_deposit`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `AuctionID` int UNSIGNED NOT NULL,
  `RoleID` int UNSIGNED NOT NULL,
  `DepositPrice` bigint NOT NULL,
  PRIMARY KEY (`AuctionID`, `RoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of auction_deposit
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_history
-- ----------------------------
DROP TABLE IF EXISTS `exchange_history`;
CREATE TABLE `exchange_history`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `HistoryTime` datetime NOT NULL,
  `Open` int NOT NULL,
  `Close` int NOT NULL,
  `High` int NOT NULL,
  `Low` int NOT NULL,
  `Volume` int NOT NULL,
  `TotalPrice` bigint NOT NULL,
  PRIMARY KEY (`GroupID`, `HistoryTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of exchange_history
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_log
-- ----------------------------
DROP TABLE IF EXISTS `exchange_log`;
CREATE TABLE `exchange_log`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `ExchangeTime` datetime NOT NULL,
  `SellerRoleID` int UNSIGNED NOT NULL,
  `SellerOrderID` bigint UNSIGNED NOT NULL,
  `BuyerRoleID` int UNSIGNED NOT NULL,
  `BuyerOrderID` bigint UNSIGNED NOT NULL,
  `Price` int NOT NULL,
  `Count` int NOT NULL,
  INDEX `IdxExchangeTime`(`ExchangeTime`) USING BTREE,
  INDEX `IdxGroupID`(`GroupID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of exchange_log
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_order
-- ----------------------------
DROP TABLE IF EXISTS `exchange_order`;
CREATE TABLE `exchange_order`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `OrderID` bigint UNSIGNED NOT NULL,
  `OrderTime` datetime NOT NULL,
  `OrderType` tinyint UNSIGNED NOT NULL,
  `OrderStatus` tinyint UNSIGNED NOT NULL,
  `RoleID` int UNSIGNED NOT NULL,
  `Price` int NOT NULL,
  `Count` int NOT NULL,
  `CurCount` int NOT NULL,
  `CurMoney` int NOT NULL,
  `BillingOrderID` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`OrderID`) USING BTREE,
  INDEX `IdxGroupID`(`GroupID`) USING BTREE,
  INDEX `IdxOrderTime`(`OrderTime`) USING BTREE,
  INDEX `IdxRoleID`(`RoleID`) USING BTREE,
  INDEX `IdxOrderStatus`(`OrderStatus`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of exchange_order
-- ----------------------------

-- ----------------------------
-- Table structure for friend
-- ----------------------------
DROP TABLE IF EXISTS `friend`;
CREATE TABLE `friend`  (
  `GroupID` tinyint NOT NULL,
  `RoleID` int UNSIGNED NOT NULL,
  `FriendID` int UNSIGNED NOT NULL,
  `FriendGroup` tinyint NOT NULL,
  `CreateTime` datetime NOT NULL,
  `Intimacy` int NULL DEFAULT 0,
  `TodayIntimacy` int NULL DEFAULT 0,
  `IntimacyLastModifiedTime` int NULL DEFAULT 0,
  PRIMARY KEY (`RoleID`, `FriendID`) USING BTREE,
  INDEX `IDX_RoleID`(`RoleID`) USING BTREE,
  INDEX `IDX_FriendID`(`FriendID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of friend
-- ----------------------------

-- ----------------------------
-- Table structure for gm
-- ----------------------------
DROP TABLE IF EXISTS `gm`;
CREATE TABLE `gm`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `ID` bigint UNSIGNED NOT NULL,
  `Time` datetime NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of gm
-- ----------------------------

-- ----------------------------
-- Table structure for group_ms
-- ----------------------------
DROP TABLE IF EXISTS `group_ms`;
CREATE TABLE `group_ms`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `RegisterIp` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `RegisterTime` datetime NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of group_ms
-- ----------------------------

-- ----------------------------
-- Table structure for guild
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `GuildID` int UNSIGNED NOT NULL,
  `Version` smallint UNSIGNED NOT NULL,
  `GuildName` varchar(25) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `LeaderID` int UNSIGNED NOT NULL,
  `CreaterName` varchar(21) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NULL DEFAULT NULL,
  `Announce` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `Notice` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL DEFAULT '',
  `MainData` blob NOT NULL,
  PRIMARY KEY (`GuildID`) USING BTREE,
  UNIQUE INDEX `GuildName`(`GuildName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of guild
-- ----------------------------

-- ----------------------------
-- Table structure for guild_member
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `RoleID` int UNSIGNED NOT NULL,
  `GuildID` int UNSIGNED NOT NULL,
  `Position` tinyint UNSIGNED NOT NULL,
  `Flag` tinyint UNSIGNED NOT NULL,
  `Salary` int NOT NULL,
  `DrawSalaryTime` datetime NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NULL DEFAULT NULL,
  `Pow` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`RoleID`) USING BTREE,
  INDEX `guild`(`GuildID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of guild_member
-- ----------------------------

-- ----------------------------
-- Table structure for guild_war
-- ----------------------------
DROP TABLE IF EXISTS `guild_war`;
CREATE TABLE `guild_war`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `IntruderID` int UNSIGNED NOT NULL,
  `DefenderID` int UNSIGNED NOT NULL,
  `BeginDayTime` datetime NOT NULL,
  `Result` int NOT NULL DEFAULT 0,
  INDEX `IdxBeginDayTime`(`BeginDayTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of guild_war
-- ----------------------------

-- ----------------------------
-- Table structure for logdata_accountlogin
-- ----------------------------
DROP TABLE IF EXISTS `logdata_accountlogin`;
CREATE TABLE `logdata_accountlogin`  (
  `LogTime` datetime NOT NULL,
  `GroupID` tinyint UNSIGNED NOT NULL,
  `AreaID` smallint NOT NULL,
  `SndaID` varchar(64) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `Action` varchar(10) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `IP` varchar(18) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  INDEX `Idx_SndaID_LogTime`(`SndaID`, `LogTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of logdata_accountlogin
-- ----------------------------

-- ----------------------------
-- Table structure for mail
-- ----------------------------
DROP TABLE IF EXISTS `mail`;
CREATE TABLE `mail`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `MailID` int UNSIGNED NOT NULL,
  `MailTime` datetime NOT NULL,
  `SenderRoleID` int UNSIGNED NOT NULL,
  `ReceiverRoleID` int UNSIGNED NOT NULL,
  `MailType` tinyint UNSIGNED NOT NULL,
  `IsNew` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `AttachLocked` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `MailSubject` varchar(61) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `MailContent` varchar(421) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `AttachType` tinyint UNSIGNED NOT NULL,
  `Attach` binary(64) NOT NULL,
  `AttachCDTime` int NULL DEFAULT 0,
  PRIMARY KEY (`MailID`) USING BTREE,
  INDEX `IdxReceiverRoleID`(`ReceiverRoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of mail
-- ----------------------------

-- ----------------------------
-- Table structure for master
-- ----------------------------
DROP TABLE IF EXISTS `master`;
CREATE TABLE `master`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `TeacherID` int UNSIGNED NOT NULL,
  `StudentID` int UNSIGNED NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NULL DEFAULT NULL,
  PRIMARY KEY (`TeacherID`, `StudentID`) USING BTREE,
  UNIQUE INDEX `student_id`(`StudentID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of master
-- ----------------------------

-- ----------------------------
-- Table structure for master_cz
-- ----------------------------
DROP TABLE IF EXISTS `master_cz`;
CREATE TABLE `master_cz`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `ID` bigint UNSIGNED NOT NULL,
  `cz` tinyint UNSIGNED NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NULL DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of master_cz
-- ----------------------------

-- ----------------------------
-- Table structure for ranklist
-- ----------------------------
DROP TABLE IF EXISTS `ranklist`;
CREATE TABLE `ranklist`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `RankListType` int NOT NULL,
  `RankKey` bigint NOT NULL,
  `RankValue` bigint NOT NULL,
  `UpdateTime` datetime NOT NULL,
  `LastRank` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`GroupID`, `RankListType`, `RankKey`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of ranklist
-- ----------------------------

-- ----------------------------
-- Table structure for role
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `RoleID` int UNSIGNED NOT NULL,
  `RoleName` varchar(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `UserName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NULL DEFAULT NULL,
  `LoginTime` datetime NOT NULL,
  `RoleDeleted` tinyint NOT NULL,
  `BaseData` blob NOT NULL,
  `RoleData` blob NOT NULL,
  PRIMARY KEY (`RoleID`) USING BTREE,
  UNIQUE INDEX `RoleName`(`RoleName`) USING BTREE,
  INDEX `IdxUserName`(`UserName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of role
-- ----------------------------

-- ----------------------------
-- Table structure for shop_log
-- ----------------------------
DROP TABLE IF EXISTS `shop_log`;
CREATE TABLE `shop_log`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `RoleID` int NOT NULL,
  `ItemTemplateID` int NOT NULL,
  `ItemCount` int NOT NULL,
  `Cost` int NOT NULL,
  `ShopTime` datetime NOT NULL,
  INDEX `IDX_RoleID`(`RoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of shop_log
-- ----------------------------

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `Index` int UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '序号',
  `UserName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '账号',
  `Password` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '密码',
  `Question` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '问题',
  `Answer` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '答案',
  `QQ` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT 'QQ号',
  `Invite` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '邀请码',
  `RegisterTime` datetime NOT NULL COMMENT '注册时间',
  `RealMoney` int NOT NULL DEFAULT 0 COMMENT '元宝数量',
  PRIMARY KEY (`Index`) USING BTREE,
  INDEX `IdxUserName` (`UserName`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 27 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of user
-- ----------------------------

-- ----------------------------
-- Table structure for variable
-- ----------------------------
DROP TABLE IF EXISTS `variable`;
CREATE TABLE `variable`  (
  `GroupID` tinyint UNSIGNED NOT NULL,
  `VarIndex` bigint NOT NULL,
  `VarValue` int NOT NULL,
  PRIMARY KEY (`GroupID`, `VarIndex`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of variable
-- ----------------------------

-- ----------------------------
-- Table structure for version
-- ----------------------------
DROP TABLE IF EXISTS `version`;
CREATE TABLE `version`  (
  `id` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `number` int NOT NULL COMMENT '正常应该写8, 卖家给的sql中log的文件执行完了是15',
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of version
-- ----------------------------


-- -----------------------------------------------------------------------------
-- Stored procedures - modern MySQL
-- -----------------------------------------------------------------------------

DELIMITER $$

DROP PROCEDURE IF EXISTS `move_data`$$
CREATE PROCEDURE `move_data`(
    IN p_dbname VARCHAR(64),
    IN p_groupid TINYINT UNSIGNED,
    IN p_tblname VARCHAR(64)
)
BEGIN
    DECLARE v_source_columns INT DEFAULT 0;
    DECLARE v_target_columns INT DEFAULT 0;
    DECLARE v_mismatched_columns INT DEFAULT 0;
    DECLARE v_group_column_count INT DEFAULT 0;
    DECLARE v_source_identifier VARCHAR(132);
    DECLARE v_target_identifier VARCHAR(266);

    -- Prevent accidental self-copy / subsequent deletion, and validate the target.
    IF p_dbname IS NULL OR p_dbname = ''
       OR p_tblname IS NULL OR p_tblname = ''
       OR p_groupid IS NULL THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'move_data: database, group, and table are required';
    END IF;

    IF p_dbname = DATABASE() THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'move_data: source and destination must differ';
    END IF;

    SELECT COUNT(*) INTO v_source_columns
    FROM information_schema.COLUMNS
    WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = p_tblname;

    SELECT COUNT(*) INTO v_target_columns
    FROM information_schema.COLUMNS
    WHERE TABLE_SCHEMA = p_dbname AND TABLE_NAME = p_tblname;

    IF v_source_columns = 0 OR v_source_columns <> v_target_columns THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'move_data: missing table or mismatched column count';
    END IF;

    SELECT COUNT(*) INTO v_group_column_count
    FROM information_schema.COLUMNS
    WHERE TABLE_SCHEMA = DATABASE()
      AND TABLE_NAME = p_tblname
      AND COLUMN_NAME = 'GroupID';

    IF v_group_column_count <> 1 THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'move_data: source table must have GroupID';
    END IF;

    -- SELECT * is safe only if both table definitions have matching column order/types.
    SELECT COUNT(*) INTO v_mismatched_columns
    FROM information_schema.COLUMNS AS src
    LEFT JOIN information_schema.COLUMNS AS dst
      ON dst.TABLE_SCHEMA = p_dbname
     AND dst.TABLE_NAME = p_tblname
     AND dst.ORDINAL_POSITION = src.ORDINAL_POSITION
    WHERE src.TABLE_SCHEMA = DATABASE()
      AND src.TABLE_NAME = p_tblname
      AND (
        dst.COLUMN_NAME IS NULL
        OR dst.COLUMN_NAME <> src.COLUMN_NAME
        OR dst.COLUMN_TYPE <> src.COLUMN_TYPE
        OR dst.IS_NULLABLE <> src.IS_NULLABLE
        OR NOT (dst.CHARACTER_SET_NAME <=> src.CHARACTER_SET_NAME)
        OR NOT (dst.COLLATION_NAME <=> src.COLLATION_NAME)
      );

    IF v_mismatched_columns <> 0 THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'move_data: column definitions/order differ';
    END IF;

    SET v_source_identifier = CONCAT('`', REPLACE(p_tblname, '`', '``'), '`');
    SET v_target_identifier = CONCAT('`', REPLACE(p_dbname, '`', '``'), '`.', v_source_identifier);

    -- The group argument has a numeric SQL type; identifiers are backtick-escaped.
    SET @cqyh_move_sql = CONCAT(
        'INSERT INTO ', v_target_identifier,
        ' SELECT * FROM ', v_source_identifier,
        ' WHERE `GroupID` = ', p_groupid
    );
    PREPARE cqyh_stmt FROM @cqyh_move_sql;
    EXECUTE cqyh_stmt;
    DEALLOCATE PREPARE cqyh_stmt;

    SET @cqyh_move_sql = CONCAT(
        'DELETE FROM ', v_source_identifier,
        ' WHERE `GroupID` = ', p_groupid
    );
    PREPARE cqyh_stmt FROM @cqyh_move_sql;
    EXECUTE cqyh_stmt;
    DEALLOCATE PREPARE cqyh_stmt;
END$$

DROP PROCEDURE IF EXISTS `move_group`$$
CREATE PROCEDURE `move_group`(
    IN p_dbname VARCHAR(64),
    IN p_groupid TINYINT UNSIGNED
)
BEGIN
    -- The batch is all-or-nothing for InnoDB tables, provided no concurrent DDL occurs.
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        RESIGNAL;
    END;

    START TRANSACTION;
    CALL move_data(p_dbname, p_groupid, 'arena');
    CALL move_data(p_dbname, p_groupid, 'auction');
    CALL move_data(p_dbname, p_groupid, 'auction_deposit');
    CALL move_data(p_dbname, p_groupid, 'exchange_history');
    CALL move_data(p_dbname, p_groupid, 'exchange_log');
    CALL move_data(p_dbname, p_groupid, 'exchange_order');
    CALL move_data(p_dbname, p_groupid, 'friend');
    CALL move_data(p_dbname, p_groupid, 'gm');
    CALL move_data(p_dbname, p_groupid, 'group_ms');
    CALL move_data(p_dbname, p_groupid, 'guild');
    CALL move_data(p_dbname, p_groupid, 'guild_member');
    CALL move_data(p_dbname, p_groupid, 'guild_war');
    CALL move_data(p_dbname, p_groupid, 'mail');
    CALL move_data(p_dbname, p_groupid, 'master');
    CALL move_data(p_dbname, p_groupid, 'master_cz');
    CALL move_data(p_dbname, p_groupid, 'ranklist');
    CALL move_data(p_dbname, p_groupid, 'role');
    CALL move_data(p_dbname, p_groupid, 'shop_log');
    CALL move_data(p_dbname, p_groupid, 'variable');
    COMMIT;
END$$

DROP PROCEDURE IF EXISTS `update_0`$$
CREATE PROCEDURE `update_0`()
BEGIN
    -- Idempotent bootstrap, without reviving the legacy MyISAM storage engine.
    CREATE TABLE IF NOT EXISTS `version` (
        `id` VARCHAR(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
        `number` INT NOT NULL,
        PRIMARY KEY (`id`)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci ROW_FORMAT=DYNAMIC;

    INSERT INTO `version` (`id`, `number`)
    SELECT 'all', 0
    WHERE NOT EXISTS (SELECT 1 FROM `version` WHERE `id` = 'all');
END$$

DROP PROCEDURE IF EXISTS `clear_table`$$
CREATE PROCEDURE `clear_table`()
BEGIN
    DECLARE v_partition_name VARCHAR(8);
    DECLARE v_table_name VARCHAR(64);
    DECLARE v_partition_exists INT DEFAULT 0;
    DECLARE v_i INT DEFAULT 0;

    -- Only truncate a partition that actually exists. The three related log tables
    -- are NOT included in this database export; absent tables are skipped.
    SET v_partition_name = CONCAT('p', DAYOFMONTH(DATE_SUB(CURRENT_DATE(), INTERVAL 8 DAY)));

    WHILE v_i < 3 DO
        SET v_table_name = CASE v_i
            WHEN 0 THEN 'logdata_item'
            WHEN 1 THEN 'logdata_money'
            ELSE 'logdata_rolelogout_basic'
        END;

        SELECT COUNT(*) INTO v_partition_exists
        FROM information_schema.PARTITIONS
        WHERE TABLE_SCHEMA = DATABASE()
          AND TABLE_NAME = v_table_name
          AND PARTITION_NAME = v_partition_name;

        IF v_partition_exists > 0 THEN
            SET @cqyh_cleanup_sql = CONCAT(
                'ALTER TABLE `', v_table_name, '` TRUNCATE PARTITION `',
                v_partition_name, '`'
            );
            PREPARE cqyh_cleanup_stmt FROM @cqyh_cleanup_sql;
            EXECUTE cqyh_cleanup_stmt;
            DEALLOCATE PREPARE cqyh_cleanup_stmt;
        END IF;
        SET v_i = v_i + 1;
    END WHILE;
END$$

DELIMITER ;

-- Restore the importer session's previous foreign-key check setting.
SET FOREIGN_KEY_CHECKS = @cqyh_previous_foreign_key_checks;
