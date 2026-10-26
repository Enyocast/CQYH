Include("script/stringtable/stringtable.lh");
LoadPackage("chat_def.pkg");
LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");
LoadPackage('gameworld.pkg');
Include("script/newai/sub_tree/sub_tree.lh");

local g_oGameWorld = CGameWorld:GetInstance();

function EnterCount(owner)--获得当天总共进入的次数
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

function CheckTeam(owner)--检测是否在队伍
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local teamid = role:GetTeamID();
	if teamid == 0 then
		return brvSuccess;
	end
	return brvFail;
end

function CheckEnterCondition(owner)--判断玩家是否达到进入条件
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local number = role:GetVariable(1008);
	if number == 0 then
		return brvSuccess;
	else
		return brvFail;
	end
	end
Include("script/newai/6104_Teleport/main.uh");


