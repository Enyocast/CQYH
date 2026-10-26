Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("npc.pkg")
LoadPackage("scene.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage('gameworld.pkg');
LoadPackage("role.pkg");
LoadPackage("title.pkg");
Include("script/newai/sub_tree/sub_tree.lh");

local g_oGameWorld = CGameWorld:GetInstance();


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
	local free_slot_count = role:GetItemBag():GetFreeSlots(CONSLOT_DEFAULT);
	if free_slot_count > 1 then
			return brvSuccess;
		else
			return brvFail;
	end	
end

function SubItem_1(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 100 then
		role:GetItemBag():ChangeYuanbao(username,100,false,2800253,1);
		role:GetItemBag():AddItem(2800253,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end

function SubItem_2(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 500 then
		role:GetItemBag():ChangeYuanbao(username,500,false,2800254,1);
		role:GetItemBag():AddItem(2800254,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end

function SubItem_3(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 1000 then
		role:GetItemBag():ChangeYuanbao(username,1000,false,2800255,1);
		role:GetItemBag():AddItem(2800255,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end

function SubItem_4(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 2000 then
		role:GetItemBag():ChangeYuanbao(username,2000,false,2800256,1);
		role:GetItemBag():AddItem(2800256,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end

function SubItem_5(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 5000 then
		role:GetItemBag():ChangeYuanbao(username,5000,false,2800257,1);
		role:GetItemBag():AddItem(2800257,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end

function SubItem_6(owner) --扣除相应的物资
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	role:GetItemBag():ChangeYuanbao(username,0,false,0,1);
	local pingzhen1 = role:GetItemBag():GetItemCount(2800253,false);
	local pingzhen2 = role:GetItemBag():GetItemCount(2800254,false);
	local pingzhen3 = role:GetItemBag():GetItemCount(2800255,false);
	local pingzhen4 = role:GetItemBag():GetItemCount(2800256,false);
	local pingzhen5 = role:GetItemBag():GetItemCount(2800257,false);
	local pingzhen6 = role:GetItemBag():GetItemCount(2800258,false);
	if pingzhen1 >= 1 or pingzhen2 >=1 or pingzhen3 >=1 or pingzhen4 >=1 or pingzhen5 >=1 or pingzhen6 >=1 then
		return brvSuccess;
	elseif yuanbao >= 10000 then
		role:GetItemBag():ChangeYuanbao(username,10000,false,2800258,1);
		role:GetItemBag():AddItem(2800258,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	else
		return brvFail; 
	end

end
--[[
function checklevel(owner) --检测VIP等级
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

function getitemcount(owner)--根据VIP等级进行消耗判断
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

Include("script/newai/6234/main.uh");




