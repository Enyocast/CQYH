AreaConfig = {};

AreaConfig.Common = {
	szCertServerAddr = "172.30.66.35",
};

AreaConfig.MS = { 
	szAddress = "172.30.66.52",
		
	-- scene
	nInitGSCount = 12,
	nInitGTCount = 6,
	nInitBSCount = 1,
	nInitDLCount = 1,
	
	--server_group
	bDBRegisterGroup = true,
	nInitGroup = Group0 + Group1 + Group2 + Group3 + Group4 + Group5,
	
	bNeedConnectGMServer = true,
		
	bOABillingEnable = false,
	bTimeCardEnabled = false,
	bMonthCardEnabled = false,
	szConfigFile = "oa_billing\\oa_billing.conf",
	bOAAwardEnable = false,
	bFcmEnable = false,
}

-- gm via maintaintool
-- .run return g_ServerConfig.GroupConfig[1].nMaxRoleCount;
-- .run g_ServerConfig.GroupConfig[1].nMaxRoleCount = 10000
AreaConfig.GroupConfig = {}
AreaConfig.GroupConfig[1] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 1,
	bClearGlobalData = false,
}
AreaConfig.GroupConfig[2] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 2,
	bClearGlobalData = false,
}
AreaConfig.GroupConfig[3] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 3,
	bClearGlobalData = false,
}
AreaConfig.GroupConfig[4] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 4,
	bClearGlobalData = false,
}
AreaConfig.GroupConfig[5] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 5,
	bClearGlobalData = false,
}
AreaConfig.GroupConfig[6] = 
{
	nMaxRoleCount = 30000,
	bPrecreateRole = false,
	szStartDate = "2020-01-01",
	dwStartDate = 0,
	nMappedGroupID = 6,
	bClearGlobalData = false,
}

AreaConfig.GT = {
	WhiteList = {
		{ szIP = "172.30.68.0", szMask = "255.255.255.0" },
		{ szIP = "172.30.66.0", szMask = "255.255.255.0" },
		{ szIP = "0.0.0.0", szMask = "255.255.255.0" },
	},
}

AreaConfig.NS = {
	szAddress = "172.30.66.35",
}

AreaConfig.DB = {
	bUseIndependentDB = true,	
	szDBIPAddress = "172.30.66.24",
	dwDBPort = 3306,
	szDBAccount = "cqyh",
	szDBPassword = "cqyh88888888",
	szDBName = "cqyh",
	szDBCharset = "utf8",
	
	-- mysql log db
	szLogDBIPAddress = "172.30.66.24",
	dwLogDBPort = 3306,
	szLogDBAccount = "cqyh",
	szLogDBPassword = "cqyh88888888",
	szLogDBName = "cqyh",
	szLogDBCharset = "utf8",

	-- mysql db , slaver
	szSlaverDBIPAddress = "172.30.66.24",
	dwSlaverDBPort = 3306,
	szSlaverDBAccount = "cqyh",
	szSlaverDBPassword = "cqyh88888888",
	szSlaverDBName = "cqyh",
	szSlaverDBCharset = "utf8",
}

AreaConfig.LS = {
	--authorize
	bOAAuthorizeEnable = false,
	szConfigFile = "oa_authorize\\oa_authorize.conf",
}

AreaConfig.GW = {
	DebugOption = {
		anticheat = false,
	},
}
