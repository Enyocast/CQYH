ServerConfig.GM_PWD = {

	nGMUserNum = 5,
	gmUserList = {
		[1] = {
			dwUserID = 1,
			szName 	= "hehe",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
		},
		[2] = {
			dwUserID = 2,
			szName 	= "gaga",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_A,
		},
		[3] = {
			dwUserID = 3,
			szName 	= "g4",
			szPwd 	= "321",
			nPermission	= GM_PERMISSION_GM,
		},
		[4] = {
			dwUserID = 4,
			szName 	= "g51",
			szPwd 	= "321",
			nPermission	= GM_PERMISSION_GM,
		},
		[5] = {
			dwUserID = 5,
			szName 	= "hellosd",
			szPwd 	= "321",
			nPermission	= GM_PERMISSION_GM,
		},

	},

	nLDUserNum = 2,
	LDUserList = {
		[1] = {
			dwUserID = 10001,
			szName 	= "ld01",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GUEST,
		},
		[2] = {
			dwUserID = 10002,
			szName 	= "ld02",
			szPwd 	= "123",
			nPermission	= GM_PERMISSION_GUEST,
		},
	},

	gmCmdList = {
		[GM_CMD_QUERY_ROLE_ID] = {
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
		[GM_CMD_LOG] = {
			szDescript = "查询日志",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_EXE_GM_STR] = {
			szDescript = "lua gm语句执行权限",	-- 建议最高权限
			nPermission = GM_PERMISSION_A,
		},
		[GM_CMD_LOAD_ROLE] = {
			szDescript = "主库查询角色数据，可修改",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_MODIFY_ROLE] = {
			szDescript = "修改角色数据",
			nPermission = GM_PERMISSION_GM,
		},
		[GM_CMD_QUERY_NAME_TO_ID] = {
			szDescript = "批量查询角色ID",
			nPermission = GM_PERMISSION_GM,
		},
	},

}


