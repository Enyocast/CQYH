ServerConfig.MS = {
    Log = {
		nLogLevelMask = lltAll - lltDebug,
		nLogOutputMask = lotFile,
		bEnableLogThread = true,
		bFlushFile = true,
        bPrintThreadID = true;
    },

    Net = {
		nMaxAcceptor = 8,
		nMaxConnector = 64,
		nMaxSessionCount = 64,
		nSendBufSize = 1024 * 1024 * 64,
		nRecvBufSize = 1024 * 1024 * 64,
		nPacketBufferSize = 1024 * 256,

		nSmallPacketCount = 1024 * 1024,
		nLargePacketCount = 1024 * 64,
    },

	-- object init count
	nInitSceneCount = 1024,
	nInitRoleCount = 1024 * 256,
	nInitUserCount= 1024 * 64,

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
	dwOnlineRoleNumPort = 8991,

	-- gm
	bNeedConnectGMServer = false,
	szRemoteGMAddress = "127.0.0.1",
	dwRemoteGMPort = 9010,

    -- scene
   	nInitGSCount = 0,
   	nInitGTCount = 0,
	nInitBSCount = 0,
	nInitDLCount = 0,
	nInitMMCount = 0,

	-- scene clean,unit:s
	nSceneCleanTime = 300,

    -- team
	nInitTeamCount = 8192,
	nInitOnlineRoleCount = 1024 * 64,

	--server_group
	bDBRegisterGroup = true,

	nInitGroup = 0,

	-- billing
	bOABillingEnable = true,
	nOABillingRequestCount = 1024,
	nOABillingResultCount = 8192,
	szConfigFile = "oa_billing\\oa_billing_external.conf",

	-- time
	bTimeCardEnabled = true,
	bMonthCardEnabled = false,
	nTimeCardBillingPeriod = 900,
	nFreeRoleLevel = 7,
	nFreeRoleTime = 86400,
	nFreeRoleSceneID = 143,
	nFreeRoleScenePosX = 148701184,
	nFreeRoleScenePosY = 76218368,
	nFreeRoleScenePosZ = 44777472,
	nFreeRoleSceneFaceDirection = 7168,

	-- reward system
	bOAAwardEnable = true,

	-- fcm
	bFcmEnable = true,
	nFcmCallbackCount = 8192,
};
