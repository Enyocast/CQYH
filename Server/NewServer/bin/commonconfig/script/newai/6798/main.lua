Include("script/newai/sub_tree/sub_tree.lh")
LoadPackage("chat_def.pkg")
LoadPackage("global_config.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
Include("script/stringtable/stringtable.lh")
Include("script/newai/sub_tree/sub_tree.lh")

local sign_indexvariable = 141;

local sign_reward_table = 
		{
			0,
			321,
			301,
			302,
			322,
			303,
			323,
			363,
		};

local collection_variable = 143;
local collection_reward = 373;
local collection_check_table = 
		{
			321,
			301,
			302,
			322,
			303,
			323,
		};

STR_EXTRA_EXP = 666525;
STR_CONFIRM_EXTRA_EXP_1 = 50081;
STR_CONFIRM_EXTRA_EXP_2 = 645206;
STR_NO_EXTRA_EXP = 645204;
STR_LEVEL_LIMIT = 645205;

ROLE_LEVEL_LIMIT = 10;

g_oGameWorld = CGameWorld:GetInstance();
LevelDataManager = CDataManager_ROLE_LEVEL_DATA_:GetInstance();


function show_result(owner)
	local roleid = get_ctx_role_id();
	local role = g_oGameWorld:FindValidRole(roleid);
	local level = role:GetLevel();

	local level_diff = g_oGameWorld:GetAverageLevel(role:GetServerGroup()) - level;
	if level_diff < 0 then
		level_diff = 0;
	end

	if level_diff <= 5 then
		local ret = call_bt_action(batRoleOpenDialog, STR_CONFIRM_EXTRA_EXP_1, 30000, 0, 0);
		if ret then
			return brvSuccess;
		else
			return brvFail;
		end
	else
		local level_data = LevelDataManager:GetData(level);
		local extra_exp =  level_data.m_nDailyExtraExp * (g_GWConfig.nLevelDiffExtraExpRate[level_diff] - RATE_MAX) / RATE_MAX;
--		print(g_oGameWorld:GetAverageLevel(role:GetServerGroup()));
--		print(level_data.m_nDailyExtraExp);
--		print("show_result "..level_diff.." "..extra_exp);
		local ret = call_bt_action(batRoleOpenDialog, STR_CONFIRM_EXTRA_EXP_2, 30000, level_diff, extra_exp);
		if ret then
			return brvSuccess;
		else
			return brvFail;
		end
	end

end

Include("script/newai/6798/main.uh")