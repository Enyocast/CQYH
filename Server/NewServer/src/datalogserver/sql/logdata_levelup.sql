CREATE TABLE `logdata_levelup` (
  `LogTime` datetime NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `GroupID` tinyint(1) NOT NULL,
  `RoleID` int(4) NOT NULL,
  `Level` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;