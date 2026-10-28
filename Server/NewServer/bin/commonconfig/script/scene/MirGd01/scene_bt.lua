
evtGuildBuildingUpgrade =
{ batParallel,
	{ UpgradeBuilding },
};

evtGuildBuildingUpdate =
{ batParallel,
	{ UpdateBuilding },
};

evtGuildBuildingDel =
{ batParallel,
	{ DeleteBuilding },
};


evtSceneInit =
{ batParallel,
	{ InitGuildBuilding },
};


evtEnterScene =
{ batSelector,
	{ batSequencer,
		{ batSelector,
			{ batRoleCheckSelfScene,},
			{ batRoleCheckAllianceScene,},
		},

		{ batParallel,
			{ batRoleSetFaction, param={ GUILD_WAR_FACTION_D },
			},
			{ batRoleSetReputation, param={ REPUTATION_TYPE, 19999 },
			},
		--	{ batSetSceneVariable, param={ 1, 0, 1 },
		--	},
		},

	},

    { batSequencer,
        { batParallel,
            { batRoleSetFaction, param={ GUILD_WAR_FACTION_A },
            },
            { batRoleSetReputation, param={ REPUTATION_TYPE, -19999 },
            },
		--	{ batSetSceneVariable, param={ 2, 0, 1 },
        --  },
        },
    },
};

evtLeaveScene =
{ batParallel,
    { batRoleSetFaction, param={ RAW_FACTION },
    },
    { batRoleSetReputation, param={ REPUTATION_TYPE, 19999 },
    },
	--{ batSelector,
	--	{ batSequencer,
	--		{ batSelector,
	--			{ batRoleCheckSelfScene,},
	--			{ batRoleCheckAllianceScene,},
	--		},

	--		{ batParallel,
	--			{ batSetSceneVariable, param={ 1, 0, -1 },
	--			},
	--		},
	--	},
	--	{ batSequencer,
	--		{ batParallel,
	--			{ batSetSceneVariable, param={ 2, 0, -1 },
	--			},
	--		},
	--	},
	--},
	-- param 2 is aura id,
	--{ batRemoveAura, param={ tarSelf, 0, false },
	--},
};

evtGuildWarBegin =
{ batParallel,
	{ batSequencer,
		{ batCheckSceneVariable, param = { boEQ, 7, 0 } },
		{ batSetSceneVariable, param = { 7, 1, 0 } },		-- Set sound effects off
	},
};

evtGuildWarEnd =
{ batSequencer,
	{ batSetSceneVariable, param = { 7, 0, 0 } },		-- Set sound effects off
    { batSceneRoleSetFaction, param={ RAW_FACTION },
    },
    { batSetReputationToFaction, param={ RAW_FACTION, REPUTATION_TYPE, 19999 },
    },
    { batWait, param={ WAIT_TO_TELEPORT_TIME, 0 },
    },
    { batTpOtherGuildRoleToReturnPos,
    },
};





--evtSingleNpcDie_10=
--{ batSequencer,
	--{batSelector,
		--{batSequencer,
			--{ batCheckSceneVariable, param={ boLT , 3, 3 },},
		   	--{ batWait, param={15000},
		   	--},
--	   	},
--	   	{ batWait, param={30000},},
--	},
--	{ batSpawnSingleNpc, param={ 8 },},
--};

--evtSingleNpcDie_8=
--{ batSequencer,
--	{batSelector,
--		{batSequencer,
--			{ batCheckSceneVariable, param={ boLT , 3, 3 },},
--		   	{ batWait, param={15000},
--		   	},
--	   	},
--	   	{ batWait, param={30000},}
--	},
--	{ batSpawnSingleNpc, param={ 5 },},
--};

--evtSingleNpcDie_5=
--{ batSequencer,
--	{batSelector,
--		{batSequencer,
--			{ batCheckSceneVariable, param={ boLT , 3, 3 },},
--		   	{ batWait, param={15000},
--		   	},
--	   	},
--	   	{ batWait, param={30000},},
--	},
--	{ batSpawnSingleNpc, param={ 10 },},
--};

--evtSingleNpcDie_3=
--{ batSequencer,
--    -- { batCheckCDTimer, param={ COOLDOWN_AI , 10},
--    -- },
--    -- { batSetCDTimer , param={ COOLDOWN_AI , 10,60000},
--    -- },
--    { batWait, param={30000},
--   	},
--	{ batSpawnSingleNpc, param={ 1 },},
--	{ batSpawnSingleNpc, param={ 2 },},
--	{ batSpawnSingleNpc, param={ 4 },},
--};


--evtTouchVolume_2 =
--{ batSequencer,
--	{ batCheckSceneVariable, param={ boLT , 3, 1 },},
--	{ batSetSceneVariable, param={ 8, 1 },
--	},
--};
