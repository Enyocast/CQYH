CREATE TABLE `logdata_quest` (
  `LogTime` datetime NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `GroupID` tinyint(1) NOT NULL,
  `RoleID` int(4) NOT NULL,
  `QuestID` int(4) NOT NULL,
  `Action` varchar(8) NOT NULL,
  `Type` varchar(6) NOT NULL,
  `QuestName` varchar(20) CHARACTER SET utf8 NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;