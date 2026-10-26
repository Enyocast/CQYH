
evtSingleNpcDie_10= 
{ batSequencer,
	{batSelector,
		{batSequencer,
			{ batCheckSceneVariable, param={ boLT , 3, 3 },},
		   	{ batWait, param={15000},
		   	},
	   	},
	   	{ batWait, param={30000},},
	},
	{ batSpawnSingleNpc, param={ 8 },},
};

evtSingleNpcDie_8= 
{ batSequencer,
	{batSelector,
		{batSequencer,
			{ batCheckSceneVariable, param={ boLT , 3, 3 },},
		   	{ batWait, param={15000},
		   	},
	   	},
	   	{ batWait, param={30000},},
	},
	{ batSpawnSingleNpc, param={ 5 },},
};

evtSingleNpcDie_5= 
{ batSequencer,
	{batSelector,
		{batSequencer,
			{ batCheckSceneVariable, param={ boLT , 3, 3 },},
		   	{ batWait, param={15000},
		   	},
	   	},
	   	{ batWait, param={30000},},
	},
	{ batSpawnSingleNpc, param={ 10 },},
};

evtSingleNpcDie_3= 
{ batSequencer,
    -- { batCheckCDTimer, param={ COOLDOWN_AI , 10},
    -- },
    -- { batSetCDTimer , param={ COOLDOWN_AI , 10,60000},
    -- },
    { batWait, param={30000},
   	},
	{ batSpawnSingleNpc, param={ 1 },},
	{ batSpawnSingleNpc, param={ 2 },},
	{ batSpawnSingleNpc, param={ 4 },},
};


evtTouchVolume_2 = 
{ batSequencer,
	{ batCheckSceneVariable, param={ boLT , 3, 1 },}, 
	{ batSetSceneVariable, param={ 8, 1 },
	},
};