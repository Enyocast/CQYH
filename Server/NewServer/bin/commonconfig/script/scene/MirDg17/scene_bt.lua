


evtLeaveScene =
{ batParallel,
	{ batSequencer,
		{ batRoleCheckRoleArenaStatus, param = { ARENA_STAT_WAIT } },
		{ batRoleSetArenaStatus, param = { ARENA_STAT_NONE } },
		{ batRoleQuitArena, },
	},
};

evtRoleDie =
{ batParallel,
	{ batSequencer,
		{ batRoleCheckRoleArenaStatus, param = { ARENA_STAT_WAIT } },
		{ batRoleSetArenaStatus, param = { ARENA_STAT_NONE } },
		{ batRoleQuitArena, },
	},
};

