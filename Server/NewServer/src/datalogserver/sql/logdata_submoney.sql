CREATE TABLE `logdata_submoney` (
  `LogTime` datetime NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `GroupID` tinyint(1) NOT NULL,
  `RoleID` int(4) NOT NULL,
  `Reason` varchar(32) NOT NULL,
  `Param` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
