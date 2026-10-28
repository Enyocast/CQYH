Include("script/stringtable/stringtable.lh");
LoadPackage("chat_def.pkg");
LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");
LoadPackage('gameworld.pkg');
Include("script/newai/sub_tree/sub_tree.lh");

local g_oGameWorld = CGameWorld:GetInstance();

function EnterCount(owner)--Get the total number of entries today
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local time1 = role:GetVariable(232);
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	if time1 < cDateTodayTime then
		role:SetVariable(1008,0);
	end
	local number = role:GetVariable(1008);
	return number;
end

function CheckTeam(owner)--Check whether the player is in a team
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local teamid = role:GetTeamID();
	if teamid == 0 then
		return brvSuccess;
	end
	return brvFail;
end

function CheckEnterCondition(owner)--Check whether the player meets the entry requirements
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local number = role:GetVariable(1008);
	if number == 0 then
		return brvSuccess;
	else
		return brvFail;
	end
	end
Include("script/newai/6104_Teleport/main.uh");


