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

-- 自定义配置
ServerConfig.CC = {
	-- 自定义 [GM命令]
	-- bGmComandEnable = true,    -- 
	bGmComandEnable = false,      -- GM命令开关 (=false, 则所有人都可以打命令)
	
	-- GM角色名字
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
	
	-- 自定义 [Vip月卡]
	bCustomGameTimeCardEnable = false,    -- 
	-- bCustomGameTimeCardEnable = true,        -- Vip月卡功能开关
	nCustomFreeRoleLevel = 7,                -- 自由人物等级
	
	-- Vip月卡物品ID
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
	
	-- 运2项链物品ID
	nLuck2NecklaceItemID = {
		[0] = 99920007,  -- 白色虎齿项链
		[1] = 99920009,  -- 灯笼项链
		[2] = 0,
		[3] = 0,
		[4] = 0,
	},
	-- attribute.txt 配置中, "幸运1"属性的最大ID值
	nMinLuck2AttributelID = 32041,
	nMaxLuck2AttributelID = 32080,
	-- 限制时间/数量
	nItemDropLimitLuck2NecklaceDuration = 720,    -- 持续时间(小时)
	nItemDropLimitLuck2NecklaceCount = 3,         -- 总数量
	
	
};

