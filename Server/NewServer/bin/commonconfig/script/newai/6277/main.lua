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
local A = 0;
local B = 5;
local C = 1;
local D = 7;

function get_Total(owner)
	local total = A * 10 + B;
	return total;
end
function get_ABC(owner)
	local total = C * 100 + D;
	return total;
end
--	return brvSuccess;
--	return brvFail;

function Buy_One(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();
	if A < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "您所兑换的物品，已经没有兑换次数了，请兑换其他物品。");
		return brvSuccess;
	end
	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 20000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 20000, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(99900026, 1, ITEMLOG_SCRIPT, 0, false);--增加屠龙
	A = A - 1;
	local msg = "恭喜"..role:GetName().."玩家兑换了牛年最牛逼的礼物------屠龙宝刀！"
	role:Say(cctServer, cltLighting, msg);
	return brvSuccess;
end

function Buy_Two(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();
	if B < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "您所兑换的物品，已经没有兑换次数了，请兑换其他物品。");
		return brvSuccess;
	end
	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 5000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 5000, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(2800363, 1, ITEMLOG_SCRIPT, 0, false);--增加斩月疾步印
	B = B - 1;
	local msg = "恭喜"..role:GetName().."玩家兑换了斩月疾步印！"
	role:Say(cctServer, cltLighting, msg);
	return brvSuccess;
end

function Buy_Three(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();
	if C < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "您所兑换的物品，已经没有兑换次数了，请兑换其他物品。");
		return brvSuccess;
	end
	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 2000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 2000, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(2800364, 1, ITEMLOG_SCRIPT, 0, false);--增加属性转移卷
	C = C - 1;
	local msg = "恭喜"..role:GetName().."玩家兑换了武器属性转移卷！"
	role:Say(cctServer, cltLighting, msg);
	return brvSuccess;
end

function Buy_Four(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();
	if D < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "您所兑换的物品，已经没有兑换次数了，请兑换其他物品。");
		return brvSuccess;
	end
	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 2000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 2000, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(2800365, 1, ITEMLOG_SCRIPT, 0, false);--增加幸运转移卷
	D = D - 1;
	local msg = "恭喜"..role:GetName().."玩家兑换了幸运转移卷！"
	role:Say(cctServer, cltLighting, msg);
	return brvSuccess;
end

function Buy_Five(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();

	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 20 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 20, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(2800138, 1, ITEMLOG_SCRIPT, 0, false);--增加疗伤药礼盒

	return brvSuccess;
end

function Buy_Six(owner)
	local role = CGameWorld:GetInstance():FindValidRole(get_ctx_role_id());
	local itemBag = role:GetItemBag();

	local count = itemBag:GetItemCount(2800357, false);--积分
	if count < 30 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "积分不足以兑换此物品，请检查您的积分数量。");
		return brvSuccess;
	end
	itemBag:DeleteItemId(2800357, 30, ITEMLOG_SCRIPT,false,0);--删除积分
	itemBag:AddItem(1800015, 1, ITEMLOG_SCRIPT, 0, false);--增加幽冥海4传送卷

	return brvSuccess;
end


Include("script/newai/6277/main.uh")
