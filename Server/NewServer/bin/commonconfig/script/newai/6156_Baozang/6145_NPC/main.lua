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


function Option_one(title)--称号1兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local suipian = role:GetItemBag():GetItemCount(2800101,false);
	if yuanbao < 1000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif suipian < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "补天碎片不足 1 个。");
		return brvFail;		
	end
	role:GetItemBag():ChangeYuanbao(username,1000,false,106,1);
	role:GetItemBag():DeleteItemId(2800101,1,ITEMLOG_SCRIPT,false,0);
	role:GetTitle():AddTitle(106);
	role:GetTitle():EquipTile(106);
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
	
end

function Option_two(title)--称号2兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	if title ~= 106 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请装备指定称号再进行兑换。");
		return brvFail;
	end
	local yuanbao = role:GetItemBag():GetMoney(3);
	local suipian = role:GetItemBag():GetItemCount(2800101,false);
	if yuanbao < 4000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif suipian < 4 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "补天碎片不足 4 个。");
		return brvFail;	
	end
	role:GetItemBag():ChangeYuanbao(username,4000,false,44,1);
	role:GetItemBag():DeleteItemId(2800101,4,ITEMLOG_SCRIPT,false,0);
	role:GetTitle():UnEquipTitle();
	role:GetTitle():DeleteTitle(106,0);
	role:GetTitle():AddTitle(44);
	role:GetTitle():EquipTile(44);	
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
end

	
function Option_three(owner)--称号3兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	if title ~= 44 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请装备指定称号再进行兑换。");
		return brvFail;
	end
	local yuanbao = role:GetItemBag():GetMoney(3);
	local suipian = role:GetItemBag():GetItemCount(2800101,false);
	if yuanbao < 8000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif suipian < 8 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "补天碎片不足 8 个。");
		return brvFail;	
	end
	role:GetItemBag():ChangeYuanbao(username,8000,false,45,1);
	role:GetItemBag():DeleteItemId(2800101,8,ITEMLOG_SCRIPT,false,0);
	role:GetTitle():DeleteTitle(44,0);
	role:GetTitle():AddTitle(45);
	role:GetTitle():EquipTile(45);	
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
end
	
function Option_four(owner)--称号4兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	if title ~= 45 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请装备指定称号再进行兑换。");
		return brvFail;
	end
	local yuanbao = role:GetItemBag():GetMoney(3);
	local suipian = role:GetItemBag():GetItemCount(2800101,false);
	if yuanbao < 16000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif suipian < 16 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "补天碎片不足 16 个。");
		return brvFail;	
	end
	role:GetItemBag():ChangeYuanbao(username,16000,false,46,1);
	role:GetItemBag():DeleteItemId(2800101,16,ITEMLOG_SCRIPT,false,0);
	role:GetTitle():DeleteTitle(45,0);
	role:GetTitle():AddTitle(46);
	role:GetTitle():EquipTile(46);	
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
end

function Option_five(owner)--称号5兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	if title ~= 46 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请装备指定称号再进行兑换。");
		return brvFail;
	end
	local yuanbao = role:GetItemBag():GetMoney(3);
	local suipian = role:GetItemBag():GetItemCount(2800101,false);
	if yuanbao < 32000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	elseif suipian < 32 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "补天碎片不足 32 个。");
		return brvFail;	
	end
	role:GetItemBag():ChangeYuanbao(username,32000,false,47,1);
	role:GetItemBag():DeleteItemId(2800101,32,ITEMLOG_SCRIPT,false,0);
	role:GetTitle():DeleteTitle(46,0);
	role:GetTitle():AddTitle(47);
	role:GetTitle():EquipTile(47);	
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
end


function Option_six(owner)--称号6兑换
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	role:GetItemBag():ChangeYuanbao(username,0,false,0,0);
	local title = role:GetTitle():GetEquipedTitleID();
	if title == 71 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "您已拥有此称号。");
		return brvFail;
	end
	local yuanbao = role:GetItemBag():GetMoney(3);
	if yuanbao < 5000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;
	end
	role:GetItemBag():ChangeYuanbao(username,5000,false,71,1);
	role:GetTitle():AddTitle(71);
	role:GetTitle():EquipTile(71);	
	role:GetScene():Say(role:GetObjID(), cltTvShow, "兑换成功！");
	return brvSuccess;
end
Include("script/newai/6145_NPC/main.uh");