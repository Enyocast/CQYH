local spawn_coordinate_table =
	{
		{ x = 14752, y = 14120 },    -- 1
		{ x = 14754, y = 40712 },    -- 2
		{ x = 14754, y = 67515 },    -- 3
		{ x = 36478, y = 14120 },    -- 4
		{ x = 36470, y = 40700 },    -- 5
		{ x = 36470, y = 67500 },    -- 6
		{ x = 62387, y = 14115 },    -- 7
		{ x = 62371, y = 40705 },    -- 8
		{ x = 62375, y = 67512 },    -- 9
	};


function _wave_end(scene,wave_id,spawn_coordinate_table)
	local spawn_x = spawn_coordinate_table[wave_id].x;
	local spawn_y = spawn_coordinate_table[wave_id].y;

	local _end_table = 
		{ batSequencer,
			{ batSay, param = { cctScene, 50025, cltTvShow, wave_id } },
			{ batWait, param = { 1000,1000 } },
			{ add_exp, param = { wave_id }  },
			{ batSetSceneVariable, param = { 2, wave_id + 1 } },
			{ batWait, param = { 2000, 2000 } },
			{ show_current_time },
			--------------------------test---------------
			{ batWait, param = { 1000,1000 } },
			---------------------------------------------
			{ check_record, param = { wave_id } },
			--------------------------test---------------
			{ batWait, param = { 2000,2000 } },
			---------------------------------------------			
			{ batSpawnNpc, param = { 6123, spawn_x, spawn_y, 4400 } },
			{ batSay, param = { cctScene, 50030, cltTvShow } },

		};

	return _end_table;
end

function _monster_spawn(scene,wave_id,group_id)
	local group_id2 = group_id + 1;

	local _spawn_table = 
		{ batSequencer,
			{ batWait, param = { 2000,2000 } },
			{ batRandom, param = { 1000, 1000 },	
				{ batSequencer,
					{ batSay, param = { cctScene, 50023, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },
					{ batSay, param = { cctScene, 50023, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },
					{ batSay, param = { cctScene, 50023, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },			
					{ batSpawnMediumGroup, param={ group_id } },
		
				},
				{ batSequencer,
					{ batSay, param = { cctScene, 50024, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },
					{ batSay, param = { cctScene, 50024, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },
					{ batSay, param = { cctScene, 50024, cltTvShow, wave_id } },
					{ batWait, param={ 2000,2000 } },
					{ batSpawnMediumGroup, param={ group_id2 } },
				},
			},
		};

	return _spawn_table;
end


evtSceneInit = 
{ batParallel,
	{ save_start_time, param = {scene} },
};

evtEnterScene = 
{ batParallel,
	{ save_role_id, param = {scene} },
	{ batSequencer,
		{ batRoleCheckDailyVariable, param = { 185 } },
		{ batRoleUpdateDailyVariable, param = { 185, 0 } },
	},
};

evtTouchVolume_1  =  
{ batSequencer,
	-- { batPrint, param = { 111111 } },
	{ batWait, param={5000,5000 } },
	{ batSay, param = { cctScene, 50047, cltTvShow, 1 } },
	{ batWait, param={2000,2000 } },
	{ batSay, param = { cctScene, 50021, cltTvShow, 1 } },
	{ batWait, param={2000,2000 } },
	{ batSay, param = { cctScene, 50028, cltTvShow, 1 } },
	{ batWait, param={2000,2000 } },
	{ batSay, param = { cctScene, 50022, cltTvShow, 1 } },
	{ batWait, param={2000,2000 } },
	{ batSay, param = { cctScene, 50029, cltTvShow, 1 } },
	{ batWait, param={3000,3000 } },

	{ batRandom, param = { 1000, 1000 },	
		{ batSequencer,
			{ batSay, param = { cctScene, 50023, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },
			{ batSay, param = { cctScene, 50023, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },
			{ batSay, param = { cctScene, 50023, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },			
			{ batSpawnMediumGroup, param={ 1 } },
			
			-- { send_kill_info },
		},
		{ batSequencer,
			{ batSay, param = { cctScene, 50024, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },
			{ batSay, param = { cctScene, 50024, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },
			{ batSay, param = { cctScene, 50024, cltTvShow, 1 } },
			{ batWait, param={2000,2000 } },
			{ batSpawnMediumGroup, param={ 2 } },
			-- { send_kill_info },
		},
	},
};

---------------------------------spawn wave 2  -----------
evtTouchVolume_2  = 
{ batSequencer,
	_monster_spawn(scene,2,3),
};


---------------------------------spawn wave 2 -----------

---------------------------------spawn wave 3  -----------
evtTouchVolume_3  = 
{ batSequencer,
	_monster_spawn(scene,3,5),
};


---------------------------------spawn wave 3 -----------

---------------------------------spawn wave 4 -----------
evtTouchVolume_4  = 
{ batSequencer,
	_monster_spawn(scene,4,7),
};


---------------------------------spawn wave  4 -----------

---------------------------------spawn wave  5 -----------
evtTouchVolume_5  = 
{ batSequencer,
	_monster_spawn(scene,5,9),
};

---------------------------------spawn wave  5 -----------

---------------------------------spawn wave  6 -----------
evtTouchVolume_6  = 
{ batSequencer,
	_monster_spawn(scene,6,11),
};

---------------------------------spawn wave 6 -----------

---------------------------------spawn wave 7  -----------
evtTouchVolume_7  = 
{ batSequencer,
	_monster_spawn(scene,7,13),
};

---------------------------------spawn wave  7 -----------

---------------------------------spawn wave  8 -----------
evtTouchVolume_8  = 
{ batSequencer,
	_monster_spawn(scene,8,15),
};

---------------------------------spawn wave  8 -----------

---------------------------------spawn wave  9 -----------
evtTouchVolume_9  = 
{ batSequencer,
	_monster_spawn(scene,9,17),
};

---------------------------------spawn wave  9 -----------



--------------------------------wave 1 end---------------
evtMediumGroupDie_1 =
{ batSequencer,
	_wave_end(scene,1,spawn_coordinate_table),
};

evtMediumGroupDie_2 =
{ batSequencer,
	_wave_end(scene,1,spawn_coordinate_table),
};
--------------------------------wave 1 end---------------





--------------------------------wave 2 end---------------
evtMediumGroupDie_3 =
{ batSequencer,
	_wave_end(scene,2,spawn_coordinate_table),
};

evtMediumGroupDie_4 =
{ batSequencer,
	_wave_end(scene,2,spawn_coordinate_table),
};
--------------------------------wave 2 end---------------





--------------------------------wave 3 end---------------
evtMediumGroupDie_5 =
{ batSequencer,
	_wave_end(scene,3,spawn_coordinate_table),
};

evtMediumGroupDie_6 =
{ batSequencer,
	_wave_end(scene,3,spawn_coordinate_table),
};
--------------------------------wave 3 end---------------




--------------------------------wave 4 end---------------
evtMediumGroupDie_7 =
{ batSequencer,
	_wave_end(scene,4,spawn_coordinate_table),
};

evtMediumGroupDie_8 =
{ batSequencer,
	_wave_end(scene,4,spawn_coordinate_table),
};
--------------------------------wave 4 end---------------




--------------------------------wave 5 end---------------
evtMediumGroupDie_9 =
{ batSequencer,
	_wave_end(scene,5,spawn_coordinate_table),
};

evtMediumGroupDie_10 =
{ batSequencer,
	_wave_end(scene,5,spawn_coordinate_table),
};
--------------------------------wave 5 end---------------


--------------------------------wave 6 end---------------
evtMediumGroupDie_11 =
{ batSequencer,
	_wave_end(scene,6,spawn_coordinate_table),
};

evtMediumGroupDie_12 =
{ batSequencer,
	_wave_end(scene,6,spawn_coordinate_table),
};
--------------------------------wave 6 end---------------




--------------------------------wave 7 end---------------
evtMediumGroupDie_13 =
{ batSequencer,
	_wave_end(scene,7,spawn_coordinate_table),
};

evtMediumGroupDie_14 =
{ batSequencer,
	_wave_end(scene,7,spawn_coordinate_table),
};
--------------------------------wave 7 end---------------



--------------------------------wave 8 end---------------
evtMediumGroupDie_15 =
{ batSequencer,
	_wave_end(scene,8,spawn_coordinate_table),
};

evtMediumGroupDie_16 =
{ batSequencer,
	_wave_end(scene,8,spawn_coordinate_table),
};
--------------------------------wave 8 end---------------



--------------------------------wave 9 end---------------
evtMediumGroupDie_17 =
{ batSequencer,
	{ batSay, param = { cctScene, 50025, cltTvShow, 9 } },
	{ batWait, param = { 1000,1000 } },
	{ add_exp, param = { 9 }  },
	{ batWait, param={2000,2000 } },
	{ show_current_time },
	--------------------------test---------------
	{ batWait, param={2000,2000 } },
	---------------------------------------------
	{ check_record, param = { 9 } },
	{ batSetSceneVariable, param = { 2, 10 } },
	{ batWait, param={3000,3000 } },
	{ batSay, param = { cctScene, 50027, cltTvShow, 9 } },
	{ batSpawnNpc, param = { 6123, spawn_coordinate_table[9].x, spawn_coordinate_table[9].y, 4400 } },
};

evtMediumGroupDie_18 =
{ batSequencer,

	{ batSay, param = { cctScene, 50025, cltTvShow, 9 } },
	{ batWait, param = { 1000,1000 } },
	{ add_exp, param = { 9 }  },
	{ batWait, param={2000,2000 } },
	{ show_current_time },
	--------------------------test---------------
	{ batWait, param={2000,2000 } },
	---------------------------------------------
	{ check_record, param = { 9 } },
	{ batSetSceneVariable, param = { 2, 10 } },
	{ batWait, param={3000,3000 } },
	{ batSay, param = { cctScene, 50027, cltTvShow, 9 } },
	{ batSpawnNpc, param = { 6123, spawn_coordinate_table[9].x, spawn_coordinate_table[9].y, 4400 } },

};
--------------------------------wave 9 end---------------


