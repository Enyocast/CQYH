



evtSceneInit =
{ batDebug,
{ batSequencer,
	{ batSetSceneVariable, param = { AMVI_JJC_BEGIN_TIME, 'GetCurrentTime(o)', 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_BEGIN_TIME, 0, 15, 0} },
	{ batSetSceneVariable, param = { AMVI_JJC_END_TIME, 'GetCurrentTime(o)', 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_END_TIME, 0, 315, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_READY, 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_ROLE_NUM, 0, 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_ROLE_ID_1, 0, 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_ROLE_ID_2, 0, 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_POTION_STAT_1, 0, 0, 0 } },
	{ batSetSceneVariable, param = { AMVI_JJC_POTION_STAT_2, 0, 0, 0 } },

	{ batPrint, param = {1}},

},
};

evtJJCBegin =
{ batDebug,
{ batParallel,
	{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_FIGHT, 0, 0 } },
	{ batRemoveAuraAllScene, param = { 1043, 0 } },
	--{ batSay, param = { cctScene, 50114, cltTvShow, 0 } },		-- 聊天
	{ batSequencer,
		{ batCheckSceneVariable, param = { boEQ, AMVI_JJC_ROLE_NUM, 1, 0 } },
		-- 结算
		{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_END, 0, 0 } },
		{ batSay, param = { cctScene, 50115, cltTvShow, 0 } },		-- 聊天
		{ JJCEnd, param = { ET_ONLY_ONE_ROLE } },

	},
	{ batPrint, param = {2}},
},
};


evtEnterScene =
{ batDebug,
{ batParallel,
	{ batSetSceneVariable, param = { AMVI_JJC_ROLE_NUM, 0, 1, 0 } },
	{ batRoleSetArenaStatus, param = { ARENA_STAT_FIGHT } },
	{ batAddAura, param = { tarRole, 1043, 0, 0 } },
	{ batSelector,
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsWarrior } },
			{ batAddAura, param = { tarRole, 65013, 0, 0 } },
		},
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsMage } },
			{ batAddAura, param = { tarRole, 65014, 0, 0 } },
		},
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsTaoist } },
			{ batAddAura, param = { tarRole, 65015, 0, 0 } },
		},
	},

	{ batPrint, param = {3}},

	{ batSequencer,
		{ batNot,
			{ batRoleCheckArenaJoinToday, },
		},
		{ batRoleSetArenaJoinToday, },
		{ batRoleSetRoleVariable, param = { 195, 0, 0, 0 } },
		{ batRoleSetRoleVariable, param = { 226, 'GetCurrentTime(o)', 0, 0 } },
	},

	{ batRoleSetRoleVariable, param = { 195, 0, 1, 0 } },
	-- 设置进入JJC次数
	{ batSequencer,
		{ batRoleCheckRoleVariable, param = { boEQ, 195, 1 } },
		{ batRoleSetRoleVariable, param = { 196, 0, 0, 0 } },
		{ batRoleSetRoleVariable, param = { 197, 0, 0, 0 } },
	},


	-- 设置阵营等
	{ batSelector,
		{ batSequencer,
			{ batCheckSceneVariable, param = { boEQ, AMVI_JJC_ROLE_NUM, 1, 0 } },
			{ batRoleSetFaction, param = { 1 } },
			{ batSetSceneVariable, param = { AMVI_JJC_ROLE_ID_1, 'GetRoleID(o)', 0, 0} },
		},
		{ batSequencer,
			{ batRoleSetFaction, param = { 2 } },
			{ batSetSceneVariable, param = { AMVI_JJC_ROLE_ID_2, 'GetRoleID(o)', 0, 0} },
		},
	},
},
};



evtLeaveScene =
{ batDebug,
{ batParallel,
	{ batPrint, param = {4}},
	{ batSetSceneVariable, param = { AMVI_JJC_ROLE_NUM, 0, -1 } },
	{ batRemoveAura, param = { tarRole, 1043, 0, 0 } },

	{ batSelector,
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsWarrior } },
			{ batRemoveAura, param = { tarRole, 65013, 0, 0 } },
		},
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsMage } },
			{ batRemoveAura, param = { tarRole, 65014, 0, 0 } },
		},
		{ batSequencer,
			{ batRoleCheckClass, param = { boEQ, clsTaoist } },
			{ batRemoveAura, param = { tarRole, 65015, 1, 0 } },
		},
	},

	{ batSelector,
		{ batSequencer,
			{ batCheckSceneVariable, param = { boEQ, AMVI_JJC_STATUS, ARENA_STAT_FIGHT } },
			{ batCheckSceneVariable, param = { boEQ, AMVI_JJC_ROLE_NUM, 1, 0 } },
			-- 结算
			{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_END, 0, 0 } },
			{ batSay, param = { cctScene, 50115, cltTvShow, 0 } },		-- 聊天
			{ JJCEnd, param = { ET_LEAVE_SCENE } },

		},
	},
	{ batRoleSetArenaStatus, param = { ARENA_STAT_NONE } },

},
};



evtRoleDie =
{ batDebug,
{ batParallel,
	{ batSequencer,
		{ batCheckSceneVariable, param = { boEQ, AMVI_JJC_STATUS, ARENA_STAT_FIGHT } },
		-- 先设置结束
		{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_END, 0, 0 } },
		{ batSay, param = { cctScene, 50115, cltTvShow, 0 } },    -- 聊天
		-- 结算
		{ JJCEnd, param = { ET_ROLE_DIE } },
	},
},
};


evtJJCEnd =
{ batDebug,
{ batParallel,
	{ batPrint, param = {6}},
	{ batSequencer,
		{ batCheckSceneVariable, param = { boNEQ, AMVI_JJC_STATUS, ARENA_STAT_END } },
		{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_END, 0, 0 } },
		{ batSay, param = { cctScene, 50115, cltTvShow, 0 } },		-- 聊天
		-- 结算
		{ JJCEnd, param = { ET_TIMEOUT } },
	},
	{ batSetSceneVariable, param = { AMVI_JJC_STATUS, ARENA_STAT_CLEAR, 0, 0 } },
	{ batWait, param = { 600000 } },
	{ batTeleportSceneRoleToReturnPos },

},
};








