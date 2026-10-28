--[[evtSceneInit = 
{ batSequencer,
	{ batSetSceneVariable, param={ 10, 0 } },--Record the number of monsters that escaped during the siege
	{ batSetSceneVariable, param={ 11, 0 } },--Record the monster siege state: 0 means siege in progress, 1 means siege failed
};

evtSceneInit = 
{ batParallel,
 	{ batSequencer,
		-- Woma leader tier
		{ batWait, param = { 'get_wait_time(SpawnDate_1)' } },	--Opening announcement at 8:50 p.m. on October 1
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave

		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 2
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_2)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 3
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_3)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 4 check
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_4)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 5 check
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_5)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 6 check
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_6)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
	--  October 7 check
 	{ batSequencer,
		-- Woma leader tier
 		{ batWait, param = { 'get_wait_time(SpawnDate_7)' } },
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--Spawn the first wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--Spawn the second wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--Spawn the third wave of Woma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Zuma leader tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--Spawn the first wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--Spawn the second wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--Spawn the third wave of Zuma leader monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
		
		-- Flame demon tier
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--Spawn the first wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--Spawn the second wave of Flame demon monsters
		{ batWait, param = { 10 * 60 * 1000 } }, 				--Wait 10 minutes before the next wave
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--Spawn the third wave of Flame demon monsters
	},
 };	
]]--