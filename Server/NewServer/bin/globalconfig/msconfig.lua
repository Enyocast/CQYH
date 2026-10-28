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
	bNeedConnectGMServer = false,
	szRemoteGMAddress = "127.0.0.1",
	dwRemoteGMPort = 9010,

	-- scene
	nInitGSCount = 1,
	nInitGTCount = 1,
	nInitBSCount = 1,
	nInitDLCount = 0,
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
	bOABillingEnable = false,
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

-- Custom configuration
ServerConfig.CC = {
	-- Custom GM commands
	-- bGmComandEnable = true,    -- 
	bGmComandEnable = false,      -- GM command switch (false allows everyone to issue commands)
	
	-- GM character names
	GmRoleName = {
	    szRoleName0 = "11",
	    szRoleName1 = "22",
	    szRoleName2 = "33",
	    szRoleName3 = "qweqwe",
	    szRoleName4 = "asdasd",
	    szRoleName5 = "AA",
	    szRoleName6 = "bb",
	    szRoleName7 = "qqa",
	    szRoleName8 = "",
	    szRoleName9 = "",
	},
	
	-- Custom VIP monthly card
	bCustomGameTimeCardEnable = false,    -- 
	-- bCustomGameTimeCardEnable = true,        -- VIP monthly-card feature switch
	nCustomFreeRoleLevel = 7,                -- Free character level
	
	-- VIP monthly-card item IDs
	nCustomGameTimeCardTemplateID = {
	    [0] = 2000001,
	    [1] = 2000002,
	    [2] = 2000003,
	    [3] = 2000004,
	    [4] = 2000005,
	    [5] = 0,
	    [6] = 0,
	    [7] = 0,
	    [8] = 0,
	    [9] = 0,
	},
	
	-- Luck +2 necklace item IDs
	nLuck2NecklaceItemID = {
		[0] = 99920007,  -- White Tiger Tooth Necklace
		[1] = 99920009,  -- Lantern Necklace
		[2] = 0,
		[3] = 0,
		[4] = 0,
	},
	-- Maximum ID for the "Luck +1" attribute in attribute.txt
	nMinLuck2AttributelID = 32041,
	nMaxLuck2AttributelID = 32080,
	-- Limit duration / count
	nItemDropLimitLuck2NecklaceDuration = 720,    -- Duration (hours)
	nItemDropLimitLuck2NecklaceCount = 3,         -- Total count
	
	
};

