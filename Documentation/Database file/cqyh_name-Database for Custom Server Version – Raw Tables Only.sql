/*
 Navicat Premium Data Transfer

 Source Server         : cqyh
 Source Server Type    : MySQL
 Source Server Version : 50156
 Source Host           : localhost:3306
 Source Schema         : cqyh_name

 Target Server Type    : MySQL
 Target Server Version : 50156
 File Encoding         : 65001

 Date: 12/01/2026 12:33:31
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for arena
-- ----------------------------
DROP TABLE IF EXISTS `arena`;
CREATE TABLE `arena`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `Fund` bigint(10) UNSIGNED NULL DEFAULT NULL,
  `Rank` blob NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of arena
-- ----------------------------

-- ----------------------------
-- Table structure for auction
-- ----------------------------
DROP TABLE IF EXISTS `auction`;
CREATE TABLE `auction`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `AuctionID` int(11) UNSIGNED NOT NULL,
  `Seller` int(11) UNSIGNED NOT NULL,
  `Buyer` int(11) UNSIGNED NOT NULL,
  `Price` bigint(20) NOT NULL,
  `BuyoutPrice` bigint(20) NOT NULL,
  `DepositPrice` bigint(20) NOT NULL,
  `StartTime` datetime NOT NULL,
  `FinishTime` datetime NOT NULL,
  `Open` tinyint(3) UNSIGNED NOT NULL,
  `AuctionStatus` tinyint(3) UNSIGNED NOT NULL,
  `ItemBuffer` varbinary(64) NOT NULL,
  `ItemDetail` varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`AuctionID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of auction
-- ----------------------------

-- ----------------------------
-- Table structure for auction_deposit
-- ----------------------------
DROP TABLE IF EXISTS `auction_deposit`;
CREATE TABLE `auction_deposit`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `AuctionID` int(10) UNSIGNED NOT NULL,
  `RoleID` int(10) UNSIGNED NOT NULL,
  `DepositPrice` bigint(20) NOT NULL,
  PRIMARY KEY (`AuctionID`, `RoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of auction_deposit
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_history
-- ----------------------------
DROP TABLE IF EXISTS `exchange_history`;
CREATE TABLE `exchange_history`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `HistoryTime` datetime NOT NULL,
  `Open` int(10) NOT NULL,
  `Close` int(10) NOT NULL,
  `High` int(10) NOT NULL,
  `Low` int(10) NOT NULL,
  `Volume` int(10) NOT NULL,
  `TotalPrice` bigint(20) NOT NULL,
  PRIMARY KEY (`GroupID`, `HistoryTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of exchange_history
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_log
-- ----------------------------
DROP TABLE IF EXISTS `exchange_log`;
CREATE TABLE `exchange_log`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `ExchangeTime` datetime NOT NULL,
  `SellerRoleID` int(10) UNSIGNED NOT NULL,
  `SellerOrderID` bigint(20) UNSIGNED NOT NULL,
  `BuyerRoleID` int(10) UNSIGNED NOT NULL,
  `BuyerOrderID` bigint(20) UNSIGNED NOT NULL,
  `Price` int(11) NOT NULL,
  `Count` int(11) NOT NULL,
  INDEX `IdxExchangeTime`(`ExchangeTime`) USING BTREE,
  INDEX `IdxGroupID`(`GroupID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of exchange_log
-- ----------------------------

-- ----------------------------
-- Table structure for exchange_order
-- ----------------------------
DROP TABLE IF EXISTS `exchange_order`;
CREATE TABLE `exchange_order`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `OrderID` bigint(20) UNSIGNED NOT NULL,
  `OrderTime` datetime NOT NULL,
  `OrderType` tinyint(3) UNSIGNED NOT NULL,
  `OrderStatus` tinyint(3) UNSIGNED NOT NULL,
  `RoleID` int(10) UNSIGNED NOT NULL,
  `Price` int(11) NOT NULL,
  `Count` int(11) NOT NULL,
  `CurCount` int(11) NOT NULL,
  `CurMoney` int(11) NOT NULL,
  `BillingOrderID` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`OrderID`) USING BTREE,
  INDEX `IdxGroupID`(`GroupID`) USING BTREE,
  INDEX `IdxOrderTime`(`OrderTime`) USING BTREE,
  INDEX `IdxRoleID`(`RoleID`) USING BTREE,
  INDEX `IdxOrderStatus`(`OrderStatus`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of exchange_order
-- ----------------------------

-- ----------------------------
-- Table structure for friend
-- ----------------------------
DROP TABLE IF EXISTS `friend`;
CREATE TABLE `friend`  (
  `GroupID` tinyint(3) NOT NULL,
  `RoleID` int(4) UNSIGNED NOT NULL,
  `FriendID` int(4) UNSIGNED NOT NULL,
  `FriendGroup` tinyint(3) NOT NULL,
  `CreateTime` datetime NOT NULL,
  `Intimacy` int(11) NULL DEFAULT 0,
  `TodayIntimacy` int(11) NULL DEFAULT 0,
  `IntimacyLastModifiedTime` int(11) NULL DEFAULT 0,
  PRIMARY KEY (`RoleID`, `FriendID`) USING BTREE,
  INDEX `IDX_RoleID`(`RoleID`) USING BTREE,
  INDEX `IDX_FriendID`(`FriendID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of friend
-- ----------------------------

-- ----------------------------
-- Table structure for gm
-- ----------------------------
DROP TABLE IF EXISTS `gm`;
CREATE TABLE `gm`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `ID` bigint(10) UNSIGNED NOT NULL,
  `Time` datetime NOT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of gm
-- ----------------------------

-- ----------------------------
-- Table structure for group_ms
-- ----------------------------
DROP TABLE IF EXISTS `group_ms`;
CREATE TABLE `group_ms`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `RegisterIp` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `RegisterTime` datetime NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of group_ms
-- ----------------------------

-- ----------------------------
-- Table structure for guild
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `GuildID` int(4) UNSIGNED NOT NULL,
  `Version` smallint(5) UNSIGNED NOT NULL,
  `GuildName` varchar(25) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `LeaderID` int(4) UNSIGNED NOT NULL,
  `CreaterName` varchar(21) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Announce` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Notice` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `MainData` blob NOT NULL,
  PRIMARY KEY (`GuildID`) USING BTREE,
  UNIQUE INDEX `GuildName`(`GuildName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of guild
-- ----------------------------

-- ----------------------------
-- Table structure for guild_member
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `RoleID` int(4) UNSIGNED NOT NULL,
  `GuildID` int(4) UNSIGNED NOT NULL,
  `Position` tinyint(1) UNSIGNED NOT NULL,
  `Flag` tinyint(1) UNSIGNED NOT NULL,
  `Salary` int(4) NOT NULL,
  `DrawSalaryTime` datetime NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Pow` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`RoleID`) USING BTREE,
  INDEX `guild`(`GuildID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of guild_member
-- ----------------------------

-- ----------------------------
-- Table structure for guild_war
-- ----------------------------
DROP TABLE IF EXISTS `guild_war`;
CREATE TABLE `guild_war`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `IntruderID` int(11) UNSIGNED NOT NULL,
  `DefenderID` int(11) UNSIGNED NOT NULL,
  `BeginDayTime` datetime NOT NULL,
  `Result` int(10) NOT NULL DEFAULT 0,
  INDEX `IdxBeginDayTime`(`BeginDayTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of guild_war
-- ----------------------------

-- ----------------------------
-- Table structure for mail
-- ----------------------------
DROP TABLE IF EXISTS `mail`;
CREATE TABLE `mail`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `MailID` int(10) UNSIGNED NOT NULL,
  `MailTime` datetime NOT NULL,
  `SenderRoleID` int(10) UNSIGNED NOT NULL,
  `ReceiverRoleID` int(10) UNSIGNED NOT NULL,
  `MailType` tinyint(3) UNSIGNED NOT NULL,
  `IsNew` tinyint(3) UNSIGNED NOT NULL DEFAULT 1,
  `AttachLocked` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `MailSubject` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `MailContent` varchar(420) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `AttachType` tinyint(3) UNSIGNED NOT NULL,
  `Attach` binary(64) NOT NULL,
  `AttachCDTime` int(11) NULL DEFAULT 0,
  PRIMARY KEY (`MailID`) USING BTREE,
  INDEX `IdxReceiverRoleID`(`ReceiverRoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of mail
-- ----------------------------

-- ----------------------------
-- Table structure for master
-- ----------------------------
DROP TABLE IF EXISTS `master`;
CREATE TABLE `master`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `TeacherID` int(10) UNSIGNED NOT NULL,
  `StudentID` int(10) UNSIGNED NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`TeacherID`, `StudentID`) USING BTREE,
  UNIQUE INDEX `student_id`(`StudentID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of master
-- ----------------------------

-- ----------------------------
-- Table structure for master_cz
-- ----------------------------
DROP TABLE IF EXISTS `master_cz`;
CREATE TABLE `master_cz`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `ID` bigint(10) UNSIGNED NOT NULL,
  `cz` tinyint(1) UNSIGNED NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of master_cz
-- ----------------------------

-- ----------------------------
-- Table structure for ranklist
-- ----------------------------
DROP TABLE IF EXISTS `ranklist`;
CREATE TABLE `ranklist`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `RankListType` int(4) NOT NULL,
  `RankKey` bigint(20) NOT NULL,
  `RankValue` bigint(20) NOT NULL,
  `UpdateTime` datetime NOT NULL,
  `LastRank` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`GroupID`, `RankListType`, `RankKey`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of ranklist
-- ----------------------------

-- ----------------------------
-- Table structure for role
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `RoleID` int(4) UNSIGNED NOT NULL,
  `RoleName` varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `UserName` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `CreateTime` datetime NOT NULL,
  `DeleteTime` datetime NOT NULL,
  `LoginTime` datetime NOT NULL,
  `RoleDeleted` tinyint(1) NOT NULL,
  `BaseData` blob NOT NULL,
  `RoleData` blob NOT NULL,
  PRIMARY KEY (`RoleID`) USING BTREE,
  UNIQUE INDEX `RoleName`(`RoleName`) USING BTREE,
  INDEX `IdxUserName`(`UserName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of role
-- ----------------------------

-- ----------------------------
-- Table structure for shop_log
-- ----------------------------
DROP TABLE IF EXISTS `shop_log`;
CREATE TABLE `shop_log`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `RoleID` int(11) NOT NULL,
  `ItemTemplateID` int(11) NOT NULL,
  `ItemCount` int(11) NOT NULL,
  `Cost` int(11) NOT NULL,
  `ShopTime` datetime NOT NULL,
  INDEX `IDX_RoleID`(`RoleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of shop_log
-- ----------------------------

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `Index` int(4) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '序号',
  `UserName` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '账号',
  `Password` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '密码',
  `Question` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '问题',
  `Answer` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '答案',
  `Invite` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '邀请码',
  `EMail` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '邮件',
  `RegisterTime` datetime NOT NULL COMMENT '注册时间',
  `RealMoney` int(8) NOT NULL DEFAULT 0 COMMENT '元宝数量',
  PRIMARY KEY (`Index`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of user
-- ----------------------------

-- ----------------------------
-- Table structure for variable
-- ----------------------------
DROP TABLE IF EXISTS `variable`;
CREATE TABLE `variable`  (
  `GroupID` tinyint(3) UNSIGNED NOT NULL,
  `VarIndex` bigint(20) NOT NULL,
  `VarValue` int(11) NOT NULL,
  PRIMARY KEY (`GroupID`, `VarIndex`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of variable
-- ----------------------------

-- ----------------------------
-- Table structure for version
-- ----------------------------
DROP TABLE IF EXISTS `version`;
CREATE TABLE `version`  (
  `id` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `number` int(4) NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = COMPACT;

-- ----------------------------
-- Records of version
-- ----------------------------
INSERT INTO `version` VALUES ('all', 8);

-- ----------------------------
-- Procedure structure for move_data
-- ----------------------------
DROP PROCEDURE IF EXISTS `move_data`;
delimiter ;;
CREATE PROCEDURE `move_data`(IN dbname VARCHAR(64), IN groupid TINYINT, IN tblname VARCHAR(64))
BEGIN
  SET @s = CONCAT('INSERT INTO ', dbname, '.', tblname, ' SELECT * FROM ', tblname, ' WHERE GroupID=', groupid, ';');
  PREPARE stmt FROM @s;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
  
  SET @s = CONCAT('DELETE FROM ', tblname, ' WHERE GroupID=', groupid, ';');
  PREPARE stmt FROM @s;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for move_group
-- ----------------------------
DROP PROCEDURE IF EXISTS `move_group`;
delimiter ;;
CREATE PROCEDURE `move_group`(IN dbname VARCHAR(64), IN groupid TINYINT)
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
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for update_0
-- ----------------------------
DROP PROCEDURE IF EXISTS `update_0`;
delimiter ;;
CREATE PROCEDURE `update_0`()
BEGIN
	CREATE TABLE `version` (`id` VARCHAR(64) NOT NULL,`number` INT(4) NOT NULL) ENGINE=MYISAM DEFAULT CHARSET=utf8;
	INSERT INTO `version` VALUES('all', 0);
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
