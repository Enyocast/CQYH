ServerConfig.MS = {
	Log = {
		nLogLevelMask = lltAll,
		nLogOutputMask = lotConsole + lotFile + lotTrace,
		bEnableLogThread = false,
		bFlushFile = true,
		bPrintThreadID = false;
	},

	Net = {
		nMaxAcceptor = 16,
		nMaxConnector = 32,
		nMaxSessionCount = 32,
		nSendBufSize = 1024 * 1024 * 1,
		nRecvBufSize = 1024 * 1024 * 1,
		nPacketBufferSize = 1024 * 1,

		nSmallPacketCount = 2048,
		nLargePacketCount = 128,
	},

	-- object init count
	nInitSceneCount = 256,
	nInitRoleCount = 64,
	nInitUserCount= 64,

	-- net
	szAddress = "0.0.0.0",

	dwGTPort = 8904,
	dwGSPort = 8905,
	dwDBPort = 8902,
	dwLSPort = 8903,
	dwBSPort = 8906,
	dwDLPort = 8908,
	dwMMPort = 8910, -- name server take 8909
	dwGMPort = 9010,
	dwLCPort = 9701,
	dwGpkPort = 9702,
	dwOnlineRoleNumPort = 8991,

	-- gm
	bNeedConnectGMServer = true,
	szRemoteGMAddress = "127.0.0.1",
	dwRemoteGMPort = 9010,

	-- scene
	nInitGSCount = 1,
	nInitGTCount = 1,
	nInitBSCount = 1,
	nInitDLCount = 1,
	nInitMMCount = 0,

	-- scene clean,unit:s
	nSceneCleanTime = 200,
	
	-- line scene recycle
	-- unit: ms
	nLineSceneRecyclePeriod = 1000,--60 * 60 * 2 * 1000,
	-- unit: ms
	nLineSceneRecycleWarnTime = 60 * 1000,
	-- unit: percentage
	nLineSceneRecycleLowThreshold = 10, --40,
	-- unit: percentage
	nLineSceneRecycleHighThreshold = 90, --70,

	-- team
	nInitTeamCount = 128,
	nInitOnlineRoleCount = 128,

	--server_group
	bDBRegisterGroup = false,

	nInitGroup = Group1,

	-- billing
	bOABillingEnable = true,
	nOABillingRequestCount = 1024,
	nOABillingResultCount = 8192,
	szConfigFile = "oa_billing\\oa_billing.conf",
	dwWaitCloseTime = 300,

	-- time
	bTimeCardEnabled = false,
	bMonthCardEnabled = false,
	nTimeCardBillingPeriod = 1800,

	-- reward system
	bOAAwardEnable = false,

	-- fcm
	bFcmEnable = false,
	nFcmCallbackCount = 8192,

	-- launch server
	szLaunchServerAddress = "127.0.0.1",	
	nLaunchServerReportInterval = 20000,
};
