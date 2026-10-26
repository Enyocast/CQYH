Include("script/newai/sub_tree/sub_tree.lh")
LoadPackage("chat_def.pkg")
LoadPackage("global_config.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("npc.pkg")	
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("character.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("item.pkg")
Include("script/stringtable/stringtable.lh")
Include("script/newai/sub_tree/sub_tree.lh")
Include("script/include/btnod.lua")

local g_oGameWorld = CGameWorld:GetInstance();


-------------------- 分割线

-- 打孔
function AddSocket(slot)
	-- 11-头盔, 12-衣服, 13-腰带, 14-鞋子, 15-护肩, 16-护腕, 17-披风
	local RoleObj = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	-- 返回值
	local nResult = RoleObj:GetItemBag():EquipAddSocket(slot);
	
	-- 判断返回值
	if nResult == 1802 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "物品不存在");
		return brvFail;
	end
	if nResult == 1816 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "当前正在摆摊中");
		return brvFail;
	end
	if nResult == 1817 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "当前正在交易中");
		return brvFail;
	end
	if nResult == 1836 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "死亡状态无法操作");
		return brvFail;
	end
	if nResult == 10001 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "装备不存在");
		return brvFail;
	end
	if nResult == 10002 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "该装备不能打孔");
		return brvFail;
	end
	if nResult == 10003 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "该装备无法再继续打孔");
		return brvFail;
	end
	if nResult == 10004 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "打孔位置未知错误");
		return brvFail;
	end
	if nResult == 10005 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "获取打孔材料消耗数量错误");
		return brvFail;
	end
	if nResult == 10006 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "打孔材料数量不够");
		return brvFail;
	end
	if nResult == 20000 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "打孔成功");
		return brvFail;
	end
	
	return brvSuccess;
end

function AddSocket_TouKui()
	AddSocket(11);
	return brvSuccess;
end
function AddSocket_YiFu()
	AddSocket(12);
	return brvSuccess;
end
function AddSocket_YaoDai()
	AddSocket(13);
	return brvSuccess;
end
function AddSocket_XieZi()
	AddSocket(14);
	return brvSuccess;
end
function AddSocket_HuJian()
	AddSocket(15);
	return brvSuccess;
end
function AddSocket_HuWan()
	AddSocket(16);
	return brvSuccess;
end
function AddSocket_PiFeng()
	AddSocket(17);
	return brvSuccess;
end

-------------------- 分割线


-- 雕色
function SetSocketColor(slot, color)
	-- [第1孔位] => 21-头盔, 22-衣服, 23-腰带, 24-鞋子, 25-护肩, 26-护腕, 27-披风
	-- [第2孔位] => 31-头盔, 32-衣服, 33-腰带, 34-鞋子, 35-护肩, 36-护腕, 37-披风
	local RoleObj = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	-- 返回值
	local nResult = RoleObj:GetItemBag():SetSocketColor(slot, color);

	-- 判断返回值
	if nResult == 1802 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "物品不存在");
		return brvFail;
	end
	if nResult == 1816 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "当前正在摆摊中");
		return brvFail;
	end
	if nResult == 1817 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "当前正在交易中");
		return brvFail;
	end
	if nResult == 1836 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "死亡状态无法操作");
		return brvFail;
	end
	
	--if nResult == 10001 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "装备不存在");
	--	return brvFail;
	--end
	--if nResult == 10002 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "该装备不能打孔");
	--	return brvFail;
	--end
	--if nResult == 10003 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "该装备无法再继续打孔");
	--	return brvFail;
	--end
	--if nResult == 10004 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "打孔位置未知错误");
	--	return brvFail;
	--end
	--if nResult == 10005 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "获取打孔材料消耗数量错误");
	--	return brvFail;
	--end
	--if nResult == 10006 then
	--	RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "打孔材料数量不够");
	--	return brvFail;
	--end
	if nResult == 30000 then
		RoleObj:GetScene():Say(RoleObj:GetObjID(), cltTvShow, "雕色成功");
		return brvFail;
	end
	
	return brvSuccess;
end


-------------------- 分割线


-- 第1孔位 头盔
function SetSocketColorFirst_TouKui_Red()
	SetSocketColor(21, 1);
	return brvSuccess;
end
function SetSocketColorFirst_TouKui_Yellow()
	SetSocketColor(21, 2);
	return brvSuccess;
end
function SetSocketColorFirst_TouKui_Blue()
	SetSocketColor(21, 3);
	return brvSuccess;
end
function SetSocketColorFirst_TouKui_Green()
	SetSocketColor(21, 4);
	return brvSuccess;
end
function SetSocketColorFirst_TouKui_Purple()
	SetSocketColor(21, 5);
	return brvSuccess;
end

-- 第1孔位 衣服
function SetSocketColorFirst_YiFu_Red()
	SetSocketColor(22, 1);
	return brvSuccess;
end
function SetSocketColorFirst_YiFu_Yellow()
	SetSocketColor(22, 2);
	return brvSuccess;
end
function SetSocketColorFirst_YiFu_Blue()
	SetSocketColor(22, 3);
	return brvSuccess;
end
function SetSocketColorFirst_YiFu_Green()
	SetSocketColor(22, 4);
	return brvSuccess;
end
function SetSocketColorFirst_YiFu_Purple()
	SetSocketColor(22, 5);
	return brvSuccess;
end

-- 第1孔位 腰带
function SetSocketColorFirst_YaoDai_Red()
	SetSocketColor(23, 1);
	return brvSuccess;
end
function SetSocketColorFirst_YaoDai_Yellow()
	SetSocketColor(23, 2);
	return brvSuccess;
end
function SetSocketColorFirst_YaoDai_Blue()
	SetSocketColor(23, 3);
	return brvSuccess;
end
function SetSocketColorFirst_YaoDai_Green()
	SetSocketColor(23, 4);
	return brvSuccess;
end
function SetSocketColorFirst_YaoDai_Purple()
	SetSocketColor(23, 5);
	return brvSuccess;
end

-- 第1孔位 鞋子
function SetSocketColorFirst_XieZi_Red()
	SetSocketColor(24, 1);
	return brvSuccess;
end
function SetSocketColorFirst_XieZi_Yellow()
	SetSocketColor(24, 2);
	return brvSuccess;
end
function SetSocketColorFirst_XieZi_Blue()
	SetSocketColor(24, 3);
	return brvSuccess;
end
function SetSocketColorFirst_XieZi_Green()
	SetSocketColor(24, 4);
	return brvSuccess;
end
function SetSocketColorFirst_XieZi_Purple()
	SetSocketColor(24, 5);
	return brvSuccess;
end

-- 第1孔位 护肩
function SetSocketColorFirst_HuJian_Red()
	SetSocketColor(25, 1);
	return brvSuccess;
end
function SetSocketColorFirst_HuJian_Yellow()
	SetSocketColor(25, 2);
	return brvSuccess;
end
function SetSocketColorFirst_HuJian_Blue()
	SetSocketColor(25, 3);
	return brvSuccess;
end
function SetSocketColorFirst_HuJian_Green()
	SetSocketColor(25, 4);
	return brvSuccess;
end
function SetSocketColorFirst_HuJian_Purple()
	SetSocketColor(25, 5);
	return brvSuccess;
end

-- 第1孔位 护腕
function SetSocketColorFirst_HuWan_Red()
	SetSocketColor(26, 1);
	return brvSuccess;
end
function SetSocketColorFirst_HuWan_Yellow()
	SetSocketColor(26, 2);
	return brvSuccess;
end
function SetSocketColorFirst_HuWan_Blue()
	SetSocketColor(26, 3);
	return brvSuccess;
end
function SetSocketColorFirst_HuWan_Green()
	SetSocketColor(26, 4);
	return brvSuccess;
end
function SetSocketColorFirst_HuWan_Purple()
	SetSocketColor(26, 5);
	return brvSuccess;
end

-- 第1孔位 披风
function SetSocketColorFirst_PiFeng_Red()
	SetSocketColor(27, 1);
	return brvSuccess;
end
function SetSocketColorFirst_PiFeng_Yellow()
	SetSocketColor(27, 2);
	return brvSuccess;
end
function SetSocketColorFirst_PiFeng_Blue()
	SetSocketColor(27, 3);
	return brvSuccess;
end
function SetSocketColorFirst_PiFeng_Green()
	SetSocketColor(27, 4);
	return brvSuccess;
end
function SetSocketColorFirst_PiFeng_Purple()
	SetSocketColor(27, 5);
	return brvSuccess;
end


-------------------- 分割线


-- 第2孔位 头盔
function SetSocketColorSecond_TouKui_Red()
	SetSocketColor(31, 1);
	return brvSuccess;
end
function SetSocketColorSecond_TouKui_Yellow()
	SetSocketColor(31, 2);
	return brvSuccess;
end
function SetSocketColorSecond_TouKui_Blue()
	SetSocketColor(31, 3);
	return brvSuccess;
end
function SetSocketColorSecond_TouKui_Green()
	SetSocketColor(31, 4);
	return brvSuccess;
end
function SetSocketColorSecond_TouKui_Purple()
	SetSocketColor(31, 5);
	return brvSuccess;
end

-- 第2孔位 衣服
function SetSocketColorSecond_YiFu_Red()
	SetSocketColor(32, 1);
	return brvSuccess;
end
function SetSocketColorSecond_YiFu_Yellow()
	SetSocketColor(32, 2);
	return brvSuccess;
end
function SetSocketColorSecond_YiFu_Blue()
	SetSocketColor(32, 3);
	return brvSuccess;
end
function SetSocketColorSecond_YiFu_Green()
	SetSocketColor(32, 4);
	return brvSuccess;
end
function SetSocketColorSecond_YiFu_Purple()
	SetSocketColor(32, 5);
	return brvSuccess;
end

-- 第2孔位 腰带
function SetSocketColorSecond_YaoDai_Red()
	SetSocketColor(33, 1);
	return brvSuccess;
end
function SetSocketColorSecond_YaoDai_Yellow()
	SetSocketColor(33, 2);
	return brvSuccess;
end
function SetSocketColorSecond_YaoDai_Blue()
	SetSocketColor(33, 3);
	return brvSuccess;
end
function SetSocketColorSecond_YaoDai_Green()
	SetSocketColor(33, 4);
	return brvSuccess;
end
function SetSocketColorSecond_YaoDai_Purple()
	SetSocketColor(33, 5);
	return brvSuccess;
end

-- 第2孔位 鞋子
function SetSocketColorSecond_XieZi_Red()
	SetSocketColor(34, 1);
	return brvSuccess;
end
function SetSocketColorSecond_XieZi_Yellow()
	SetSocketColor(34, 2);
	return brvSuccess;
end
function SetSocketColorSecond_XieZi_Blue()
	SetSocketColor(34, 3);
	return brvSuccess;
end
function SetSocketColorSecond_XieZi_Green()
	SetSocketColor(34, 4);
	return brvSuccess;
end
function SetSocketColorSecond_XieZi_Purple()
	SetSocketColor(34, 5);
	return brvSuccess;
end

-- 第2孔位 护肩
function SetSocketColorSecond_HuJian_Red()
	SetSocketColor(35, 1);
	return brvSuccess;
end
function SetSocketColorSecond_HuJian_Yellow()
	SetSocketColor(35, 2);
	return brvSuccess;
end
function SetSocketColorSecond_HuJian_Blue()
	SetSocketColor(35, 3);
	return brvSuccess;
end
function SetSocketColorSecond_HuJian_Green()
	SetSocketColor(35, 4);
	return brvSuccess;
end
function SetSocketColorSecond_HuJian_Purple()
	SetSocketColor(35, 5);
	return brvSuccess;
end

-- 第2孔位 护腕
function SetSocketColorSecond_HuWan_Red()
	SetSocketColor(36, 1);
	return brvSuccess;
end
function SetSocketColorSecond_HuWan_Yellow()
	SetSocketColor(36, 2);
	return brvSuccess;
end
function SetSocketColorSecond_HuWan_Blue()
	SetSocketColor(36, 3);
	return brvSuccess;
end
function SetSocketColorSecond_HuWan_Green()
	SetSocketColor(36, 4);
	return brvSuccess;
end
function SetSocketColorSecond_HuWan_Purple()
	SetSocketColor(36, 5);
	return brvSuccess;
end

-- 第2孔位 披风
function SetSocketColorSecond_PiFeng_Red()
	SetSocketColor(37, 1);
	return brvSuccess;
end
function SetSocketColorSecond_PiFeng_Yellow()
	SetSocketColor(37, 2);
	return brvSuccess;
end
function SetSocketColorSecond_PiFeng_Blue()
	SetSocketColor(37, 3);
	return brvSuccess;
end
function SetSocketColorSecond_PiFeng_Green()
	SetSocketColor(37, 4);
	return brvSuccess;
end
function SetSocketColorSecond_PiFeng_Purple()
	SetSocketColor(37, 5);
	return brvSuccess;
end


-------------------- 分割线

-- 查询节点
function QueryRoleRootCount()
	local roleObj = g_oGameWorld:FindValidRole(get_ctx_role_id());
	
	local msg_Warrior = string.format("战士节点-[普通-%d]-[高级-%d]", roleObj:GetRuneRootCount(rrrNormal,clsWarrior), roleObj:GetRuneRootCount(rrrAdvanced,clsWarrior));
	roleObj:GetScene():Say(roleObj:GetObjID(), cltDialog, msg_Warrior);
	
	local msg_Mage = string.format("法师节点-[普通-%d]-[高级-%d]", roleObj:GetRuneRootCount(rrrNormal,clsMage), roleObj:GetRuneRootCount(rrrAdvanced,clsMage));
	roleObj:GetScene():Say(roleObj:GetObjID(), cltDialog, msg_Mage);
	
	local msg_Taoist = string.format("道士节点-[普通-%d]-[高级-%d]", roleObj:GetRuneRootCount(rrrNormal,clsTaoist), roleObj:GetRuneRootCount(rrrAdvanced,clsTaoist));
	roleObj:GetScene():Say(roleObj:GetObjID(), cltDialog, msg_Taoist);
	
	local msg_Luck = string.format("祝福油节点-[%d]", roleObj:GetLuckRootCount());
	roleObj:GetScene():Say(roleObj:GetObjID(), cltDialog, msg_Luck);
	
	return brvSuccess;
end


function testZS()
	print("function - testZS");
	return brvSuccess;
end
function testFS()
	print("function - testFS");
	return brvSuccess;
end
function testDS()
	print("function - testDS");
	return brvSuccess;
end


-------------------- 分割线

-- 默认代码
--[[
-- 雕色 普通
function DiaoSe_PuTong(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local woma = role:GetItemBag():GetItemCount(2800075,false);
	local item_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	
	local rea = false;
	if item_one == nil  then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格放入能够雕色的宝石。");
		return brvFail;
	end
	
	local id_one = item_one.m_iteminfo.m_nTemplateID;
	
	for i = 0,5 do --宝石是否能够雕色判定
		if id_one == g_GWConfig.nBaoShi_PuTong[i]  then
			rea = true;
			break;
		else
			rea = false;
		end	
		print(i);
	end
	
	if rea == false then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格放入能够雕色的宝石。");
		return brvFail;
	elseif woma < 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "沃玛精华不足一个。");
		return brvFail;
	elseif yuanbao < 100 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;	
	end
	
	role:GetItemBag():DeleteItemId(2800075,1,ITEMLOG_SCRIPT,false,0);
	role:GetItemBag():ChangeYuanbao(username,100,false,6192,1);
	role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, ITEMLOG_SCRIPT, 0);
	role:GetItemBag():BaoShi_DiaoSe(4800504);
	
	return brvSuccess;
end

-- 雕色 特殊
function DiaoSe_TeShu(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local woma = role:GetItemBag():GetItemCount(2800075,false);
	local item_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local rea = false;
	if item_one == nil  then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格放入能够雕色的宝石。");
		return brvFail;
	end
	
	local id_one = item_one.m_iteminfo.m_nTemplateID;
	
	for i = 0,8 do --宝石是否能够雕色判定
		if id_one == g_GWConfig.nBaoShi_TeShu[i]  then
			rea = true;
			break;
		else
			rea = false;
		end	
	end
	
	if rea == false then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格放入能够雕色的宝石。");
		return brvFail;
	elseif woma < 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "沃玛精华不足一个。");
		return brvFail;
	elseif yuanbao < 1000 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "元宝不足。");
		return brvFail;	
	end
	role:GetItemBag():DeleteItemId(2800075,5,ITEMLOG_SCRIPT,false,0);
	role:GetItemBag():ChangeYuanbao(username,1000,false,id_one,1);
	role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, ITEMLOG_SCRIPT, 0);
	role:GetItemBag():BaoShi_DiaoSe(4800505);
	
	return brvSuccess;
end
]]--


Include("script/newai/6192/main.uh")