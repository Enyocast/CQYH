evtSceneInit = 
{ batParallel,
	{ load_all_npc },
};

evtTouchVolume_4 = 
{ batSequencer, 
    { batPrint, param={ 11111 },
    },
    { batCheckSceneVariable, param={boEQ, 2, 1 },
    },
    { batRoleTeleport , param={ 92409, 48152, 6017, 152},
    },
};

evtTouchVolume_5 = 
{ batSequencer, 
    { batCheckSceneVariable, param={boEQ, 3, 1 },
    },
    { batRoleTeleport , param={ 91956, 48420, 6017, 152},
    },
};

evtTouchVolume_6 = 
{ batSequencer, 
    { batCheckSceneVariable, param={boEQ, 4, 1 },
    },
    { batRoleTeleport , param={ 91956, 49870, 6017, 152},
    },
};

evtTouchVolume_1 = 
{ batSequencer, 
    { batCheckSceneVariable, param={boEQ, 2, 1 },
    },
    { batRoleTeleport , param={ 55572, 44798, 6880, 152},
    },
};

evtTouchVolume_2 = 
{ batSequencer, 
    { batCheckSceneVariable, param={boEQ, 3, 1 },
    },
    { batRoleTeleport , param={ 55022, 45527, 6880, 152},
    },
};

evtTouchVolume_3 = 
{ batSequencer, 
    { batCheckSceneVariable, param={boEQ, 4, 1 },
    },
    { batRoleTeleport , param={ 55024, 46973, 6880, 152},
    },
};

evtTouchVolume_8 = 
{ batSequencer, 
    { batRoleTeleport , param={ 54936, 46162, 6880, 152},
    },
};

evtTouchVolume_7 = 
{ batSequencer, 
    { batRoleIsSabacGuildMember},
    { batRoleTeleport , param={ 91871, 49223, 6017, 152},
    },
};

evtSabacBeforeStart = 
{ batParallel,
	{ batSay, param = { cctGroup, 2010, cltLighting, 10 } },
	{ batWait, param = { 5 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2010, cltLighting, 5 } },
	{ batWait, param = { 2 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2010, cltLighting, 3 } },
	{ batWait, param = { 1 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2010, cltLighting, 2 } },
	{ batWait, param = { 1 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2010, cltLighting, 1 } },
};

evtSabacStart = 
{ batParallel,
	{ batSay, param = { cctGroup, 2011, cltLighting } },
	{ batSetSceneVariable, param={ 5, 1 },
    },
	{ batPrint , param={ 111111 },
    },
    { batSetSceneVariable, param={ 6, 1 },
    },
    { batWait, param = { 5 * 60 * 1000 } },
    { batSay, param = { cctGroup, 2015, cltLighting, 5} },
};


evtSabacBeforeEnd = 
{ batParallel,
	{ batSay, param = { cctGroup, 2012, cltLighting, 10 } },
	{ batWait, param = { 5 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2012, cltLighting, 5 } },
	{ batWait, param = { 2 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2012, cltLighting, 3 } },
	{ batWait, param = { 1 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2012, cltLighting, 2 } },
	{ batWait, param = { 1 * 60 * 1000 } },
	{ batSay, param = { cctGroup, 2012, cltLighting, 1 } },
};


evtSabacEnd = 
{ batParallel,
	{ batSay, param = { cctGroup, 2016, cltLighting } },
	{ batSetSceneVariable, param={ 5, 0 },
    },
    { batSetSceneVariable, param={ 6, 0 },
    },
	{ batWait , param = { 5000 } },
	{ batPrint , param={ 222222 },
    },
	{ batSpawnSingleNpc , param = { 9 } },
	{ batSpawnSingleNpc , param = { 20 } },	
	{ batSpawnSingleNpc , param = { 15 } },	
	{ batSpawnSingleNpc , param = { 18 } },	
	{ batSpawnSingleNpc , param = { 13 } },	
	{ batSpawnSingleNpc , param = { 17 } },	
	{ batSpawnSingleNpc , param = { 19 } },	
	{ batSpawnSingleNpc , param = { 29 } },	
};

