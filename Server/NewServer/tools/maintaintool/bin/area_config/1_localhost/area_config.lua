AreaConfig = {};

AreaConfig.MS = { --test1224aae
	szAddress = "127.0.0.1",
		
	-- scene
	nInitGSCount = 2,
	nInitGTCount = 1,
	nInitBSCount = 1,
	nInitDLCount = 1,
	
	--server_group
	bDBRegisterGroup = true,
	nInitGroup = Group0 + Group1,
	
-- gm via maintaintool
-- .run return g_ServerConfig.MS.GroupConfig[1].bPrecreateRole;
-- .run g_ServerConfig.MS.GroupConfig[1].bPrecreateRole = 1
	GroupConfig = {
		[0] = {
			nMaxRoleCount = 30000,
			bPrecreateRole = false,
		},
		[1] = {
			nMaxRoleCount = 30000,
			bPrecreateRole = false,
			nMappedGroupID = 1,
			bClearGlobalData = false,
		},
		[2] = {
			nMaxRoleCount = 10000,
			bPrecreateRole = false,
			nMappedGroupID = 2,
			bClearGlobalData = false,
		},
		[3] = {
			nMaxRoleCount = 10000,
			bPrecreateRole = false,
			nMappedGroupID = 3,
			bClearGlobalData = false,
		},
		[4] = {
			nMaxRoleCount = 10000,
			bPrecreateRole = false,
			nMappedGroupID = 4,
			bClearGlobalData = false,
		},
		[5] = {
			nMaxRoleCount = 10000,
			bPrecreateRole = false,
			nMappedGroupID = 5,
			bClearGlobalData = false,
		},
		[6] = {
			nMaxRoleCount = 10000,
			bPrecreateRole = false,
			nMappedGroupID = 6,
			bClearGlobalData = false,
		},
	},
		
	bOABillingEnable = false,
	bTimeCardEnabled = false,
	bMonthCardEnabled = false,
	szConfigFile = "oa_billing\\oa_billing.conf",
	bOAAwardEnable = true,
	bFcmEnable = false,
};

--[[
AreaConfig.GT = {
	WhiteList = {
		{ szIP = "172.30.68.31", szMask = "255.255.255.255" },
	},
}
--]]

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
