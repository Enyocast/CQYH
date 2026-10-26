Include("script/stringtable/stringtable.lh");
LoadPackage("chat_def.pkg");
LoadPackage("role.pkg");
LoadPackage("item_bag.pkg");
LoadPackage('gameworld.pkg');
Include("script/newai/sub_tree/sub_tree.lh");

ROLE_KillNpcValue = 200  ;
local g_oGameWorld = CGameWorld:GetInstance();

function GetCount_MoChongKu(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local time1 = role:GetVariable(232);
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	
	if time1 < cDateTodayTime then
		role:SetVariable(1022,0);
	end
	
	local count = role:GetVariable(1022);
	return count;
end

-- 判断玩家是否达到进入条件
function CheckEnterCondition(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	-- 获取 进入次数
	local enter_count = role:GetVariable(1022);
	
	-- 获取 金币数量
	local moneyret = role:GetItemBag():GetMoney(1);
	
	-- 判断 次数小于1 (每天1次), 金币大于10万
	if (enter_count < 1) and (moneyret >= 100000) then
		return brvSuccess;
	end
	
	-- 自己写的代码, 判断日期, 只能判断1次
	--[[
	-- 获取上一次进入时间
	local dwVarValue = role:GetVariable(232);
	local dwOldDay = (dwVarValue + g_oGameWorld:GetTimeZone()) / 86400;
	local dwToday = (g_oGameWorld:GetGameTime() + g_oGameWorld:GetTimeZone()) / 86400;
	
	-- 浮点转int
	local dwOldDayInt = math.floor(dwOldDay)
	local dwTodayInt = math.floor(dwToday)
	
	-- 获取 金币数量
	local moneyret = role:GetItemBag():GetMoney(1);
	
	-- 判断 最后一次日期
	if (dwOldDayInt < dwTodayInt) and (moneyret >= 100000) then
		return brvSuccess;
	else
		return brvFail;
	end
	]]--
	
	return brvFail;
end

-- 扣除相应的物资
function SubItem(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local moneyret = role:GetItemBag():GetMoney(1);
	if moneyret >= 100000 then
		role:GetItemBag():SubMoney(1, 100000, MONEYLOG_TELEPORT_PLATFORM, 0);
		return brvSuccess;
	else
		return brvFail; 
	end
	
	return brvFail;
end

-- 增加魔虫窟次数
function IncCount_MoChongKu(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local result = role:IncCount_MoChongKu();
	if result == true then
		return brvSuccess;
	end
	
	return brvFail;
end

-- 热血代码
--[[
-- 获得当天总共进入的次数
function EnterCount(owner)

	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local time1 = role:GetVariable(232);
	
	local cDateCurrectTime = os.date("*t",os.time());
	
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	
	if time1 < cDateTodayTime then
		role:SetVariable(1022,0);
	end
	
	local number = role:GetVariable(1022);
	
	print("number == "..number);
	
	return number;
end

-- 获得当天VIP剩余次数
function GetVipCount(owner)

	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local level = role:GetVIPLevel();
	
	local time1 = role:GetVariable(232);
	
	local cDateCurrectTime = os.date("*t",os.time());
	
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	
	if time1 < cDateTodayTime then
		role:SetVariable(1022,0);
	end
	
	print("level == "..level);
	
	local number = role:GetVariable(1022);
	if number == 0 then
		return level;
	end
	
	local a = level  +1 - number;
	if a < 0 then
		a = 0;
	end
	
	print("a == "..a);
	
	return a;
end

--检测是否在队伍
function CheckTeam(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local teamid = role:GetTeamID();
	if teamid == 0 then
		return brvSuccess;
	end
	return brvFail;
end

-- 检测VIP等级
function checklevel(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local level = role:GetVIPLevel();
	local time1 = role:GetVariable(232);
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	if time1 < cDateTodayTime then
		role:SetVariable(1022,0);
	end
	local entercount = role:GetVariable(1022);
	if level >= entercount then
		return brvSuccess;
	else
		return brvFail;
	end
end

-- 根据VIP等级进行消耗判断
function getitemcount(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local level = role:GetVIPLevel();
	local time1 = role:GetVariable(232);
	local cDateCurrectTime = os.date("*t",os.time());
	local cDateTodayTime = os.time({year=cDateCurrectTime.year, month=cDateCurrectTime.month, day=cDateCurrectTime.day, hour=0,min=0,sec=0});
	if time1 < cDateTodayTime then
		role:SetVariable(1022,0);
	end
	local count = role:GetVariable(1022) - level;
	if count <= 1 then
		return count;
	else
		return (count-1)*2;
	end
end
]]--


Include("script/newai/6167_Mochongku/main.uh");


