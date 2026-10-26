CREATE TABLE `logdata_conslot` (
  `LogTime` datetime NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `GroupID` tinyint(1) NOT NULL,
  `RoleID` int(4) NOT NULL,
  `ConType` varchar(14) NOT NULL,
  `ConSize` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;