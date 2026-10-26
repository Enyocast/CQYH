ServerConfig = {};

ServerConfig.Common = {
    nAreaID = 1,
    szAreaName = '电信一区',
	nReconnectTime = 10000,
	nServerPingTimeout = 5000 * 1000,
	nServerPingInterval = 1000,
	nShareMemDisconnectTimeout = 500000,
	szIntranetAddr = '255.255.255.255',
	szIntranetMask = '255.255.255.255',
	szCertServerAddr = "127.0.0.1",
	dwCSPort = 8111,
	
	szGuardAddress = "0.0.0.0",
	dwGuardPort = 8810,
	nRegisterGuardTimeout = 120 * 1000,
	nPingGuardTimeout = 5 * 1000,
	szReportAbsolutePath = "C:\\report\\",

	IpWhiteList = {
		{ szIP = "127.0.0.1", szMask = "255.255.255.255" },
		{ szIP = "127.0.0.1", szMask = "255.255.255.255" },
		{ szIP = "0.0.0.0", szMask = "255.255.255.0" },
	},

	szSuperGMUserName = "holimion",
	UserWhiteList = {
		{ szUserName = "holimion" },
		{ szUserName = "3400123456" },
	},

};
