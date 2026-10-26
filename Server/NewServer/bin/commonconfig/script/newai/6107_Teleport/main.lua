Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
Include("script/newai/sub_tree/sub_tree.lh")
LoadPackage("npc.pkg")
LoadPackage("scene.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage('gameworld.pkg');
LoadPackage("global_config.pkg")
LoadPackage("role.pkg");
LoadPackage("title.pkg");
local g_oGameWorld = CGameWorld:GetInstance();

local MaxCount = 937;
function check_time(owner)
	local a = os.time();
	local b = os.time({year = 2022,month = 9,day = 1, hour = 14, min = 0, sec = 0});
	if a >= b then 
		return brvSuccess;
	else
		return brvFail;
	end

end

function buy_libao1(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local level = role:GetLevel();
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local count = role:GetItemBag():GetItemCount(2800368,false);
	local a = os.time();
	local b = os.time({year = 2022,month = 9,day = 1, hour = 14, min = 0, sec = 0});
	if count >= 1 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "冲级礼包只能购买一个，您已拥有此礼包。");
		return brvFail;	
	elseif a - b > 604800 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "开区时间大于7天，无法购买冲级礼包。");
		return brvFail;		
	elseif yuanbao < 10000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif level >= 30 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "等级大于30级，无法购买冲级礼包。");
		return brvFail;
	else 
		role:GetItemBag():ChangeYuanbao(username,10000,false,2800368,1);
		role:GetItemBag():AddItem(2800368,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	end	
end

--[[function buy_libao2(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local level = role:GetLevel();
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local count = role:GetItemBag():GetItemCount(2800273,false);
	local coune = role:GetItemBag():GetItemCount(2800274,false);
	local a = os.time();
	local b = os.time({year = 2021,month = 3,day = 20, hour = 14, min = 0, sec = 0});
	if count >= 1 or coune >= 1 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "冲级礼包只能购买一个，您已拥有此礼包。");
		return brvFail;	
	elseif a - b > 604800 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "开区时间大于7天，无法购买冲级礼包。。");
		return brvFail;
	elseif yuanbao < 10000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif level >= 30 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "等级大于30级，无法购买冲级礼包。");
		return brvFail;
	else 
		role:GetItemBag():ChangeYuanbao(username,10000,false,2800274,1);
		role:GetItemBag():AddItem(2800274,1,ITEMLOG_SCRIPT,0,false);
		return brvSuccess;
	end	
end]]--
--[[function CheckCount(owner)
	if MaxCount > 0 then
		return brvSuccess;
	else
		return brvFail;
	end

end]]--

function GetBuyCount(owner)
	return MaxCount;
end

function AddBuy(owner)
	MaxCount = MaxCount -1;
	return brvSuccess;
end
Include("script/newai/6107_Teleport/main.uh")