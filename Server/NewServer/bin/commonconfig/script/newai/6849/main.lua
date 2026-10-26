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



--[[
nWeapon_Shengxing_Type ={}
  --装备类型
    {
		[0] = ITEMSUBTYPE_EQUIP_WEAPON,		 --武器		 1		
		[1] = ITEMSUBTYPE_EQUIP_HAT,		--帽子		2	  
		[2] = ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR,	--肩甲	3			  	
		[3] = ITEMSUBTYPE_EQUIP_CHEST_ARMOR,	--胸甲	4		  	
		[4] = ITEMSUBTYPE_EQUIP_WRIST_ARMOR, --护腕5
		[5] = ITEMSUBTYPE_EQUIP_BELT,	--腰带			 6 		
		[6] = ITEMSUBTYPE_EQUIP_SHOES,	--鞋子			7	  
		[7] = ITEMSUBTYPE_EQUIP_CLOAK,	--披风			  8	
		[8] = ITEMSUBTYPE_EQUIP_NECKLACE, --项链		9
		[9] = ITEMSUBTYPE_EQUIP_RING,	--戒指			  	10
		[10] = ITEMSUBTYPE_EQUIP_BRACELET,	--手镯	11
    },]]--
	




local g_oGameWorld = CGameWorld:GetInstance();

function Get_Jinbi(owner) --获取合成消耗的金币
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	local Type = weapon_one.m_pTemplate.m_bySubType;
	local cost = 0;
	
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one == 1 then  
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_WoMa[one] *2;		
			return cost;			
		else
			cost = g_GWConfig.nWeapon_Shengxing_WoMa[one];
			return cost;
		end
	elseif dang_one >= 2  and dang_one <= 5 then
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_Other[one] *2*(dang_one -1);	
		else
			cost = g_GWConfig.nWeapon_Shengxing_Other[one]*(dang_one -1);
		end
		if one <= 4 then 
			return cost;
		elseif one > 4 then
			return 0;
		end	
	end		

end

function Get_Yuanbao(owner) --获取合成消耗的元宝
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);	
	local Type = weapon_one.m_pTemplate.m_bySubType;
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	local cost = 0;	
	if one == 10 or two == 10 then
	--	role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
	--	role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one >= 2  and dang_one <= 5 then
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_Other[one] *2*(dang_one -1);			
		else
			cost = g_GWConfig.nWeapon_Shengxing_Other[one]*(dang_one -1);
		end
		if one > 4 then 
			return cost;
		elseif one <= 4 then
			return 0;
		end			
	else 
		return 0;
	end			

end


function Check_Money(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local jinbi = role:GetItemBag():GetMoney(1);
	local Type = weapon_one.m_pTemplate.m_bySubType;
	local dang_one = math.modf( itemid_one / 10000000);
	local one = itemid_one % 100;
	local cost = 0;
	
	if dang_one == 1 then    
		if Type == 1 or Type == 2 or Type == 4 then
			 cost = g_GWConfig.nWeapon_Shengxing_WoMa[one] *2;
		else
			 cost = g_GWConfig.nWeapon_Shengxing_WoMa[one];
		end
		if jinbi < cost then
			return brvFail;
		else
			return brvSuccess ; 
		end	
	elseif dang_one >= 2  and dang_one <= 5 then
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_Other[one] *2*(dang_one -1);
		else
			cost = g_GWConfig.nWeapon_Shengxing_Other[one]*(dang_one -1);
		end
		if one < 4 then 
			if jinbi < cost then
				return brvFail;
			else
				return brvSuccess ; 
			end	
		elseif one >= 4 then
			if yuanbao < cost then
				return brvFail;
			else
				return brvSuccess ; 
			end
		else 
			return brvFail;	
		end
	else 
		return brvFail;
	end
end

function Change_Money(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local qianghua = weapon_one.m_iteminfo.m_byLevelupPhyPoint + weapon_one.m_iteminfo.m_byLevelupMagPoint + weapon_one.m_iteminfo.m_byLevelupTaoPoint;
	local xingyun = weapon_one.m_iteminfo.m_byLuck;
	local mingwen1 = weapon_one.m_iteminfo.m_wRune[0];
	local mingwen2 = weapon_one.m_iteminfo.m_wRune[1];
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local username = role:GetUserName();
	local yuanbao = role:GetItemBag():GetMoney(3);
	local jinbi = role:GetItemBag():GetMoney(1);
	local Type = weapon_one.m_pTemplate.m_bySubType;
	local dang_one = math.modf( itemid_one / 10000000);
	local one = itemid_one % 100;
	local cost = 0;
	local VIP = role:GetVIPLevel();
	if dang_one == 1 then    
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_WoMa[one]*2;
		else
			cost = g_GWConfig.nWeapon_Shengxing_WoMa[one];
		end
		role:GetItemBag():SubMoney(1, cost, MONEYLOG_SHENGXING, 0,0);
		role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, MONEYLOG_SHENGXING, 0);
		role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 1, 1, MONEYLOG_SHENGXING, 0);
		if VIP == 0 then			
			role:GetItemBag(): AddItem(itemid_one +1,1,MONEYLOG_SHENGXING,0,false);
		elseif qianghua == 0 and xingyun ==0 and mingwen1 ==0 and mingwen2 ==0 then
			role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_two); --VIP继承
		else
			role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_one);		
		end	
		local msg = "升星成功，恭喜获得"..role:GetItemBag():GetItemName(itemid_one + 1).."!"
			role:Say(role:GetObjID(), cltTvShow, msg);
		return brvSuccess;
	elseif dang_one >= 2  and dang_one <= 5 then
		if Type == 1 or Type == 2 or Type == 4 then
			cost = g_GWConfig.nWeapon_Shengxing_Other[one] *2*(dang_one -1);
		else
			cost = g_GWConfig.nWeapon_Shengxing_Other[one]*(dang_one -1);
		end
		if one < 4 then 
			role:GetItemBag():SubMoney(1, cost, MONEYLOG_SHENGXING, 0,0);
			role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, MONEYLOG_SHENGXING, 0);
			role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 1, 1, MONEYLOG_SHENGXING, 0);
			if VIP == 0 then
				role:GetItemBag(): AddItem(itemid_one +1,1,MONEYLOG_SHENGXING,0,false);
			elseif qianghua == 0 and xingyun ==0 and mingwen1 ==0 and mingwen2 ==0 then
				role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_two);	
			else
				role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_one);				
			end	
			local msg = "升星成功，恭喜获得"..role:GetItemBag():GetItemName(itemid_one + 1).."!"
				role:Say(role:GetObjID(), cltTvShow, msg);
			return brvSuccess;
		elseif one >= 4 then
			role:GetItemBag():ChangeYuanbao(username,cost,false,itemid_one,1);
			role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 0, 1, MONEYLOG_SHENGXING, 0);
			role:GetItemBag():DeleteItemPos(CONSLOT_DEFAULT, 1, 1, MONEYLOG_SHENGXING, 0);			
			if VIP == 0 then
				role:GetItemBag(): AddItem(itemid_one +1,1,MONEYLOG_SHENGXING,0,false);
			elseif qianghua == 0 and xingyun ==0 and mingwen1 ==0 and mingwen2 ==0 then
				role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_two);	
			else
				role:GetItemBag(): AddItem1(itemid_one +1,1,MONEYLOG_SHENGXING,0,false,weapon_one);
			end
			local msg = "升星成功，恭喜获得"..role:GetItemBag():GetItemName(itemid_one + 1).."!"
				role:Say(role:GetObjID(), cltTvShow, msg);
			return brvSuccess;
		else 
			return brvFail;
		end
	else 
		return brvFail;		
	end
end


function Check_Weapon_one(owner)  --屠龙武器	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 1 or Type_two ~= 1 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end

function Check_Weapon_two(owner)  --屠龙帽子	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 2 or Type_two ~= 2 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end

function Check_Weapon_three(owner)  --屠龙肩甲	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 3 or Type_two ~= 3 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end

function Check_Weapon_four(owner)  --屠龙胸甲	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 4 or Type_two ~= 4 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end

function Check_Weapon_five(owner)  --屠龙护腕	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 5 or Type_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_six(owner)  --屠龙腰带	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 6 or Type_two ~= 6 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_seven(owner)  --屠龙鞋子	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 3 or  dang_two ~= 3 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 7 or Type_two ~= 7 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_eight(owner)  --屠龙披风	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 8 or Type_two ~= 8 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_nine(owner)  --屠龙项链	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 9 or Type_two ~= 9 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_ten(owner)  --屠龙戒指	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 10 or Type_two ~= 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end


function Check_Weapon_elven(owner)  --屠龙手镯	--检测两件装备是否为相同装备且均为可合成装备 若是，返回成功
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local weapon_one = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 0);
	local weapon_two = role:GetItemBag():GetItem(CONSLOT_DEFAULT, 1);
	if weapon_one == nil or weapon_two ==nil then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请在背包第一格与第二格放入能够升星的装备。");
		return brvFail;
	end
	local itemid_one = weapon_one.m_iteminfo.m_nTemplateID;
	local itemid_two = weapon_two.m_iteminfo.m_nTemplateID;
	local dang_one = math.modf( itemid_one / 10000000);
	local dang_two = math.modf( itemid_two / 10000000);
	local Type_one = weapon_one.m_pTemplate.m_bySubType;
	local Type_two = weapon_two.m_pTemplate.m_bySubType;
	
	local one = itemid_one % 100;
	local two = itemid_two % 100;
	if one == 10 or two == 10 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入星级为1~9的装备。");
		return brvFail;		
	elseif itemid_one ~= itemid_two or itemid_one > 59990000 or itemid_one < 19920000 or itemid_two > 59990000 or itemid_two < 19920000 then 
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入能够升星的装备。");
		return brvFail;
	elseif dang_one ~= 5 or  dang_two ~= 5 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "请放入屠龙档装备。");
		return brvFail;
	elseif Type_one ~= 11 or Type_two ~= 11 then
		role:GetScene():Say(role:GetObjID(), cltTvShow, "装备类型不符合。");
		return brvFail;
	else
		return brvSuccess; 
	end
end




Include("script/newai/6839/main.uh")