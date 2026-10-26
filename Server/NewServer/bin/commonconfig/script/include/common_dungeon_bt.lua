
evtSceneInit = 
{ batSequencer, 
	{ batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 1 },
    },
    { batWait, param={ DUNGEON_INIT_DURATION },
    },
    { batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 2 },
    },
    { batWait, param={ DUNGEON_MAX_DURATION },
    },
    { batSay, param={ cctScene, strCommonDungeonTimeOut },
    },
	{ batFinishScene, param={ DUNGEON_CLOSE_WAIT_DURATION },
    },
    { batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 5 },
    },
};

evtLeaveScene = 
{ batSequencer, 
	{ batCheckSceneRuning, 
	},
    { batCheckInTeam,
    },
    { batRoleLeaveTeam,
    },
};

evtBossDie = 
{ batSequencer,
    { batFinishScene, param={ DUNGEON_CLOSE_WAIT_DURATION },
    },
	{ batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 3 },
    },
	{ batWait, param={ DUNGEON_FINISH_WAIT_DURATION },
    },
    { batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 4 },
    },
	{ batCalculateDungeonScore, 
	},
	{ batWait, param={ DUNGEON_REWARD_WAIT_DURATION },
    },
	{ batSetSceneVariable, param={ DUNGEON_STAGE_VAR_INDEX, 5 },
    },
};
