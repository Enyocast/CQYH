ServerConfig.GM_PWD = {

	nGMUserNum = 3,
	gmUserList = {
		[1] = {
			dwUserID = 1,
			szName 	= "zhangliping",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GM,
			MacList = {
				[0] = { szMac = "00-50-56-38-B3-CF" },
				[1] = { szMac = "" },
			},
		},
		[2] = {
			dwUserID = 2,
			szName 	= "zhonglaili",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GM,
			MacList = {
				[0] = { szMac = "00-50-56-38-B3-CF" },
				[1] = { szMac = "00-50-56-38-B3-CF" },
			},
		},
		[3] = {
			dwUserID = 3,
			szName 	= "huanghui",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
			MacList = {
				[0] = { szMac = "10-60-4B-6F-98-7E" },
				[1] = { szMac = "10-60-4B-6F-98-7E" },
			},
		},

	},

	nLDUserNum = 3,
	LDUserList = {
		[1] = {
			dwUserID = 10001,
			szName 	= "chenkai",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
			MacList = {
				[0] = { szMac = "10-60-4B-6F-98-7F" },
				[1] = { szMac = "10-60-4B-6F-98-7F" },
			},
		},
		[2] = {
			dwUserID = 10002,
			szName 	= "zhangjingxuan",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
			MacList = {
				[0] = { szMac = "10-60-4B-6F-98-7F" },
				[1] = { szMac = "10-60-4B-6F-98-7F" },
			},
		},
		[3] = {
			dwUserID = 10003,
			szName 	= "shujian",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
			MacList = {
				[0] = { szMac = "10-60-4B-6F-98-7F" },
				[1] = { szMac = "10-60-4B-6F-98-7F" },
			},
		},
	},

	nCRMNum = 3,
	CRMList = {
		[1] = {
			dwUserID = 90001,
			szName 	= "crm1",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GUEST,
			MacList = {
				[0] = { szMac = "" },
				[1] = { szMac = "" },
			},
		},
		[2] = {
			dwUserID = 90002,
			szName 	= "crm2",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GUEST,
			MacList = {
				[0] = { szMac = "" },
				[1] = { szMac = "" },
			},
		},
		[3] = {
			dwUserID = 90003,
			szName 	= "crm3",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GUEST,
			MacList = {
				[0] = { szMac = "" },
				[1] = { szMac = "" },
			},
		},
	},

	IpWhiteList = {
		{ szIP = "127.0.0.1", szMask = "255.255.255.255" },
		{ szIP = "192.168.0.181", szMask = "255.255.255.0" },
		{ szIP = "0.0.0.0", szMask = "255.255.255.0" },
	},

	gmCmdList = {
		[GM_CMD_QUERY_ROLE_BASE_INFO] = {
			szDescript = "查询角色ID",
			nPermission = GM_PERMISSION_GUEST,
		},
		[GM_CMD_QUERY_ROLE_DATA] = {
			szDescript = "从库查询角色数据",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_FORBID_CHAT] = {
			szDescript = "禁言",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_FREEZE_ROLE] = {
			szDescript = "冻结角色",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_KICK_ROLE] = {
			szDescript = "踢人下线",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_ANNOUNCE] = {
			szDescript = "发布公告",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_GET_ANNOUNCE_LIST] = {
			szDescript = "获取已发送公告",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_DEL_ANNOUNCE] = {
			szDescript = "删除公告",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_SEND_MAIL] = {
			szDescript = "发送邮件",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_BLACK_HOUSE] = {
			szDescript = "关小黑屋",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_LOG] = {
			szDescript = "查询日志",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_EXE_GAME_CMD] = {
			szDescript = "lua gm语句执行权限",	-- 建议最高权限
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_LOAD_ROLE] = {
			szDescript = "主库查询角色数据，可修改",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_MODIFY_ROLE] = {
			szDescript = "修改角色数据",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_QUERY_MAIL_DETAIL] = {
			szDescript = "查看邮件详细数据",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_QUERY_NAME_TO_ID] = {
			szDescript = "批量查询角色ID",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_ROLE_EXE_GM_CMD] = {
			szDescript = "对角色执行GM指令",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_FIX_ROLE] = {
			szDescript = "修正角色数据",	-- 建议最高权限
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_LOAD_MAIL] = {
			szDescript = "加载角色邮件列表",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_DEL_MAIL] = {
			szDescript = "删除角色邮件",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_ADD_MAIL_CD] = {
			szDescript = "冻结角色邮件",
			nPermission = GM_PERMISSION_GM,
		},
	},

}


