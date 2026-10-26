Include("script/include/btnod.lua")

LoadPackage("achievement_def.pkg")
LoadPackage("achievement_list.pkg")
LoadPackage("role.pkg")
LoadPackage("robot_message_handler.pkg")
LoadPackage("data_manager.pkg")

function performance_achievement_complete(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local data_count = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetDataCount();
	local nRandIndex = math.random(1, data_count - 1);
	local nIndex = 0;

	local achievement = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetFirstData();
	while achievement ~= nil do

		if nRandIndex == nIndex then
			user:CompleteAchievement(achievement.nAchievementID);
			break;
		end

		nIndex = nIndex + 1;
		achievement =  CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetNextData();
	end

	return ;
end


function performance_achievement_compare(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local solo_role = CGeneralMgr:GetInstance():GetRandRole(role:GetObjID());
	user:CompareAchievement(solo_role.dwRoleID);
end

function performance_achievement_reward(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local AchID = role:GetAsimovRole():RandCompleteAchievement();
	user:GetAchievementReward(AchID);
end


