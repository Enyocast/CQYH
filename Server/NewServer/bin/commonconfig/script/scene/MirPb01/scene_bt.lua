--[[evtSceneInit = 
{ batSequencer,
	{ batSetSceneVariable, param={ 10, 0 } },--记录怪物攻城的漏怪数量
	{ batSetSceneVariable, param={ 11, 0 } },--记录怪物攻城的状态 0代表攻城阶段 1代表攻城失败
};

evtSceneInit = 
{ batParallel,
 	{ batSequencer,
		-- 沃玛教主级别
 		{ batWait, param = { 'get_wait_time(SpawnDate_1)' } },	--10月1号晚上8点50开放通知
		{ batSay, param = { cctScene, 666721, cltTvShow } },
		{ batWait, param = { 7 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666722, cltTvShow } },
		{ batWait, param = { 2 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666723, cltTvShow } },
		{ batWait, param = { 1 * 60 * 1000 } },
		{ batSay, param = { cctScene, 666724, cltTvShow } },
		{ batSetSceneVariable, param={ 10, 0 } },
		{ batSetSceneVariable, param={ 11, 0 } },
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波

		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别	
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别	
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月2号
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},	
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月3号
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		-- 祖玛教主级别		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月4号检测
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月5号检测
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月6号检测
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别		
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
	--  10月7号检测
 	{ batSequencer,
		-- 沃玛教主级别
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
 		{ batSpawnNpc , param = { 9713, 29000, 57300, 8000 } },	--刷新第一波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9714, 29000, 57300, 8000 } },	--刷新第二波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9715, 29000, 57300, 8000 } },	--刷新第三波沃玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 祖玛教主级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9728, 29000, 57300, 8000 } },	--刷新第一波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9729, 29000, 57300, 8000 } },	--刷新第二波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9730, 29000, 57300, 8000 } },	--刷新第三波祖玛教主
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
		
		-- 烈焰恶魔级别			
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},		
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
 		{ batSpawnNpc , param = { 9743, 29000, 57300, 8000 } },	--刷新第一波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9744, 29000, 57300, 8000 } },	--刷新第二波烈焰恶魔
 		{ batWait, param = { 10 * 60 * 1000 } }, 				--等待10分钟进入下一波
				
		{ batSelector,
			{ batCheckSceneVariable, param={ boEQ,11, 0 } },
			{ batSay, param = { cctScene, 666726, cltTvShow } },
		},			
		{ batCheckSceneVariable, param={ boEQ,11, 0 } },
		{ batSpawnNpc , param = { 9745, 29000, 57300, 8000 } },	--刷新第三波烈焰恶魔
	},
 };	
]]--