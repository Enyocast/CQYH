local BOSS_COUNT = 3;

local SCENE_REWARD_MONEY_POOL_VAR = 1;
local SCENE_BOSS_DIE_COUNT_VAR = 2;
local SCENE_BOSS_COUNT_VAR = 3;

local MONEY_COST_EACH_BOX = 10000; -- Configurable
local TICKET_COST = 20000;

evtSceneInit =
{ batSequencer,
	{ batSetSceneVariable, param = { SCENE_BOSS_COUNT_VAR, BOSS_COUNT, 0, 0 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 5 } },
    { batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 6 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 7 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 8 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 9 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 10 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 11 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 12 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 13 } },
	{ batWait, param = { 330000 , 330000 } },
	{ batSpawnMediumGroup, param={ 14 } },
};

evtEnterScene = 
{ batSequencer,
	{ batRoleCheckRoleVariable, param = { boGT, 183, 0 } },
	{ batRoleSubMoney , param = { tarRole, 1, TICKET_COST, MONEYLOG_BT_03 } },
	{ batRoleSetRoleVariable, param = { 183, 0 } },
	{ batSetSceneVariable, param = { SCENE_REWARD_MONEY_POOL_VAR, 0, TICKET_COST} },
	{ batRoleSetRoleVariable, param = { 219, 'CGameWorld:GetInstance():GetGameTime()', 0 } },
    { batRoleCheckDailyVariable, param = { 221 } },
	{ batRoleAddActivityPts , param = { 40 , aprBaoku } },
	{ batRoleUpdateDailyVariable, param = { 221 } },
};

evtRoleDie  =  
{ batSequencer,
	{ batRoleAddMoney , param={ tarRoleKiller , 1 , 7000, MONEYLOG_BT_03 } },
	{ send_kill_info },
};

