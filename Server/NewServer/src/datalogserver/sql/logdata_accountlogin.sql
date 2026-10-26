CREATE TABLE `logdata_accountlogin` (
  `LogTime` datetime NOT NULL,
  `GroupID` tinyint(1) unsigned NOT NULL,
  `AreaID` tinyint(1) NOT NULL,
  `SndaID` varchar(64) NOT NULL,
  `Action` varchar(6) NOT NULL,
  `IP` varchar(18) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
