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

-- Check whether the player meets the entry requirements
function CheckEnterCondition(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	-- Get the entry count
	local enter_count = role:GetVariable(1022);
	
	-- Get the gold amount
	local moneyret = role:GetItemBag():GetMoney(1);
	
	-- Require fewer than one entry (once per day) and more than 100,000 gold
	if (enter_count < 1) and (moneyret >= 100000) then
		return brvSuccess;
	end
	
	-- Custom date check; can only check once
	--[[
	-- Get the last entry time
	local dwVarValue = role:GetVariable(232);
	local dwOldDay = (dwVarValue + g_oGameWorld:GetTimeZone()) / 86400;
	local dwToday = (g_oGameWorld:GetGameTime() + g_oGameWorld:GetTimeZone()) / 86400;
	
	-- Convert float to int
	local dwOldDayInt = math.floor(dwOldDay)
	local dwTodayInt = math.floor(dwToday)
	
	-- Get the gold amount
	local moneyret = role:GetItemBag():GetMoney(1);
	
	-- Check the last entry date
	if (dwOldDayInt < dwTodayInt) and (moneyret >= 100000) then
		return brvSuccess;
	else
		return brvFail;
	end
	]]--
	
	return brvFail;
end

-- Deduct the required materials
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

-- Increment the Demon Insect Cave entry count
function IncCount_MoChongKu(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local result = role:IncCount_MoChongKu();
	if result == true then
		return brvSuccess;
	end
	
	return brvFail;
end

-- Re Xue code
--[[
-- Get the total number of entries today
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

-- Get remaining VIP entries today
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

--Check whether the player is in a team
function CheckTeam(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local teamid = role:GetTeamID();
	if teamid == 0 then
		return brvSuccess;
	end
	return brvFail;
end

-- Check VIP level
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

-- Check the cost according to VIP level
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


