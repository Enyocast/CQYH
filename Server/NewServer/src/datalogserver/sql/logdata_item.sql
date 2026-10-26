CREATE TABLE `logdata_item` (
  `LogTime` datetime NOT NULL,
  `GroupID` tinyint(1) NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `ActionType` varchar(8) NOT NULL,
  `TemplateID` int(4) unsigned NOT NULL,
  `Guid` bigint(8) NOT NULL,
  `ItemCount` tinyint(1) NOT NULL,
  `SrcRoleID` int(4) NOT NULL,
  `TargetRoleID` int(4) NOT NULL,
  `Reason` varchar(30) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;