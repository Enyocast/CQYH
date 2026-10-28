LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("data_manager.pkg")

TestCase.Item = {};

function TestCase.Item.Basic()
    local user_name = "Item" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
    --while equip_data do
        ----用GM指令增加一件物品
        --ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
        --check(ret, "failed to send gm command");
--
        ----检查增加的物品确实是GM指令所加的
        --msg = recv_msg(5, session_id, protocol.g2c_item_change);
        --check(msg, "failed to recv g2c_item_change");
--
        ----check(msg.stItem.nTemplateID==equip_data.m_nTemplateID, "failed to create correct item");
        --item = role:GetItemBag():GetItem(3,0);
        --check(item, "failed to get item");
        --check(item.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID, "failed to get correct item");
--
        ----删除新加的物品
        --ret = user:DeleteItem(3, 0, 1);
        --check(ret, "failed to send delete item msg");
--
        ----检查删除物品的回包
        --msg = recv_msg(5, session_id, protocol.g2c_item_delete);
        --check(msg, "failed to recv g2c_item_delete");
        --check(msg.byConSlot == 3 and msg.byItemSlot == 0, "failed to delete correct item");
--
        --print("AddItem OK " .. equip_data.m_nTemplateID);
        --equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetNextData();
    --end

	-- 先删除一次要加的物品
	item = role:GetItemBag():GetItem(2,0);
	if item then
		print("begin send delete item msg");
		ret = user:DeleteItem(2, 0, item.m_iteminfo.m_shCurDur, item.m_iteminfo.m_nTemplateID);
		check(ret, "failed to send delete item msg");
	end

    --用GM指令增加药水，下面的移动/拆分要用
    ret = user:GMCommand("AddItem(123,10)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    item = role:GetItemBag():GetItem(2,0);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    print("item num " .. item.m_iteminfo.m_shCurDur);
    check(item.m_iteminfo.m_shCurDur == 10, "item num error");
    --check(msg.stItem.nTemplateID==101, "failed to create correct item");
    --check(msg.stItem.nCurDur==10, "failed to create correct item");

    --登出
    cleanup(user);
    wait(5);

    --再次登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --移动物品
    ret = user:MoveItem(2, 0, 2, 1);
    check(ret, "failed to send move item msg");

    --检查移动物品的回包
    msg = recv_msg(5, session_id, protocol.g2c_item_swap);
    check(msg, "failed to recv g2c_item_swap");
    check(msg.wSrcConSlot==2 and
          msg.wSrcItemSlot==0 and
          msg.wDstConSlot==2 and
          msg.wDstItemSlot==1,
          "failed to get correct g2c_item_swap message");

    --拆分物品
    ret = user:SplitItem(2, 1, 2, 2, 5);
    check(ret, "failed to send split item msg");

    --检查拆分物品的回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    --check(msg.stItem.nTemplateID==123 and
    --      msg.stItem.nCurDur==5 and
    --      msg.stItem.byConSlot==2 and
   --       msg.stItem.byItemSlot==1,
      --    "failed to recv correct g2c_item_change after splitting");

    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    --check(msg.stItem.nTemplateID==123 and
	--msg.stItem.nCurDur==5 and
	--msg.stItem.byConSlot==2 and
	--msg.stItem.byItemSlot==2,
	--"failed to recv correct g2c_item_change after splitting");
	-- 新的检查方式,一次检查2个包
	item = role:GetItemBag():GetItem(2,2);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    check(item.m_iteminfo.m_shCurDur == 5, "item num error");

    item = role:GetItemBag():GetItem(2,1);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    check(item.m_iteminfo.m_shCurDur == 5, "item num error");

    --堆叠物品
    ret = user:MoveItem(2, 2, 2, 1);
    check(ret, "failed to send move item msg");

    --检查堆叠物品的回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    item = role:GetItemBag():GetItem(2,1);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    check(item.m_iteminfo.m_shCurDur == 10, "item num error");
    --check(msg.stItem.nTemplateID==123 and
          --msg.stItem.nCurDur==10 and
          --msg.stItem.byConSlot==2 and
          --msg.stItem.byItemSlot==1,
          --"failed to recv correct g2c_item_change after stacking");

    msg = recv_msg(5, session_id, protocol.g2c_item_delete);
    check(msg, "failed to recv g2c_item_delete");
    check(msg.byConSlot==2 and
          msg.byItemSlot==2,
          "failed to recv correct g2c_item_delete after stacking");

    --销毁物品
    ret = user:DeleteItem(2,1,10);
    check(ret, "failed to send delete item msg");

    --检查销毁物品的回包
    msg = recv_msg(5, session_id, protocol.g2c_item_delete);
    check(msg, "failed to recv g2c_item_delete");
    check(msg.byConSlot==2 and
          msg.byItemSlot==1,
          "failed to recv correct g2c_item_delete after deleting");

    --登出
    cleanup(user);
end


function TestCase.Item.RunScript()
    local user_name = "Attr" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

	--登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

   --用GM指令增加药水，下面的移动/拆分要用
    ret = user:GMCommand("AddItem(101,1)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	print("role-level:"..role:GetLevel());
	local currentLevel = role:GetLevel();

	role:GetItemBag():UseItem(2, 0, 101);

	wait(2);


    --登出
    cleanup(user);

	wait(2);

	user, role = startup(user_name, user_name);

	wait(2);

	print("role-level:"..role:GetLevel());
	check(currentLevel < role:GetLevel(), "use item failed");

	--登出
    cleanup(user);
end



function TestCase.Item.Attribute()
    local user_name = "Attr" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name);

    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    --用GM指令增加测试用武器
    ret = user:GMCommand("AddItem(190002,1)");
    check(ret, "failed to send gm command");

    --检查增加的物品属性
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    item = role:GetItemBag():GetItem(3,0);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 190002, "failed to get correct item");
    print("item attr count " .. item.m_iteminfo.m_byAttrCount);
    check(item.m_iteminfo.m_byAttrCount == 2, "item num error");
    --check(msg.stItem.byAttrCount>=8, "failed to create correct item");
    --check(msg.stItem.astAttrs[0].shParam>=95 and msg.stItem.astAttrs[0].shParam<=110, "failed to create correct item");

    --装备
    ret = user:MoveItem(3, 0, 0, 0);
    check(ret, "failed to send move item msg");

    --登出
    cleanup(user);
end

function TestCase.Item.Shop()
    local user_name = "Shop" .. os.date("%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    wait(2);
    --用GM指令召唤一个NPC
    ret = user:GMCommand("SummonNpc(6003)");
    check(ret, "failed to send gm command");

    --检查召唤出的NPC
    msg = recv_msg(5, session_id, protocol.g2c_char_appear)
    check(msg, "Npc appear fail.")
    local diag_npc_id = msg.stAppearData.dwCharID
    check(diag_npc_id ~= 0, "Npc appear fail.")

    --msg = recv_msg(5, session_id, protocol.g2c_sync_char_list);
    --check(msg, "failed to recv sync char list msg");

    --local diag_npc_id = get_npc_id_from_list(msg, 2001);
    --check(diag_npc_id ~= 0, "npc appear fail");

    --点选NPC
    ret = user:InteractWithNpc(diag_npc_id);
    check(ret, "failed to interact with npc");

    --购买商品
    ret = user:BuyItem(3);
    check(ret, "failed to send buy item msg");

    --检查回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --登出
    cleanup(user);
end

function TestCase.Item.Shop_2()
    local user_name = "Shop" .. os.date("%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
	local conSlot;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    wait(2);

		-- 清空包裹
	item = role:GetItemBag():GetItem(2, 0);
	while item do
		--
		ret = user:DeleteItem(2, 0, 1, item.m_iteminfo.m_nTemplateID);
		check(ret, "failed to send delete item msg");

		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(2, 0);
	end

	item = role:GetItemBag():GetItem(4, 0);
	while item ~= nil do
		--
		ret = user:DeleteItem(4, 0, 1);
		check(ret, "failed to send delete item msg");
		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(4, 0);
	end

	item = role:GetItemBag():GetItem(5, 0);
	while item ~= nil do
		--
		ret = user:DeleteItem(5, 0, 1);
		check(ret, "failed to send delete item msg");
		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(5, 0);
	end

	local npc_list = {6002,6003,6006};

	for i,npc_id in ipairs(npc_list) do
		--用GM指令召唤一个NPC
		ret = user:GMCommand("SummonNpc("..npc_id..")");
		check(ret, "failed to send gm command");

		--检查召唤出的NPC
		msg = recv_msg(5, session_id, protocol.g2c_char_appear)
		check(msg, "Npc appear fail.")
		local diag_npc_id = msg.stAppearData.dwCharID
		check(diag_npc_id ~= 0, "Npc appear fail.")

		--msg = recv_msg(5, session_id, protocol.g2c_sync_char_list);
		--check(msg, "failed to recv sync char list msg");

		--local diag_npc_id = get_npc_id_from_list(msg, 2001);
		--check(diag_npc_id ~= 0, "npc appear fail");

		--点选NPC
		ret = user:InteractWithNpc(diag_npc_id);
		check(ret, "failed to interact with npc");

		print(npc_id);
		local npc_data = CDataManager_NPC_DATA_:GetInstance():GetData(npc_id);
		print(npc_data.nShopID);
		local shop_data = CDataManager_SHOP_DATA_:GetInstance():GetData(npc_data.nShopID);

		--用GM指令加钱
		ret = user:GMCommand("AddMoney(1, 100000000, MONEYLOG_GM_COMMAND)");
		check(ret, "failed to send gm command");
		ret = user:GMCommand("AddMoney(3, 100000000, MONEYLOG_GM_COMMAND)");
		check(ret, "failed to send gm command");

		for i = 1, 256 do
			if shop_data.m_ShopItem[i-1].m_nItemID == 0 then
				break;
			end

			if shop_data.m_ShopItem[i-1].m_nItemID ~= -1 then


				print("deal item"..shop_data.m_ShopItem[i-1].m_nItemID);
				--购买商品
				ret = user:BuyItem(i-1);
				check(ret, "failed to send buy item msg");

				--检查回包
				msg = recv_msg(30, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				local item_data = CDataManager_ITEM_DATA_:GetInstance():GetData(shop_data.m_ShopItem[i-1].m_nItemID);
				if item_data == nil then
					item_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(shop_data.m_ShopItem[i-1].m_nItemID);
					if item_data == nil then
						check(false, "cannot find item in item.txt");
					end
				end

				-- 判断包裹位置
				if item_data.m_byType == 3 then -- 材料
					conSlot = 4;
				elseif item_data.m_byType == 9 then -- 任务
					conSlot = 5;
				elseif item_data.m_byType == 2 then
					conSlot = 3;		-- 装备
				else
					conSlot = 2;	-- 默认包裹
				end

				print("item bag position"..conSlot);
				ret = user:SellItem(conSlot,0);
				check(ret, "failed to send sell item msg");

				msg = recv_msg(30, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");


			end
		end

		wait(2);
	end

    --登出
    cleanup(user);
end

function TestCase.Item.Money()
    local user_name = "Money" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --用GM指令增加钱
    ret = user:GMCommand("SetMoney(0,1234)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==0, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --用GM指令增加钱
    ret = user:GMCommand("SetMoney(1,1234)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==1, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --用GM指令增加钱
    ret = user:GMCommand("SetMoney(2,1234)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==2, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --用GM指令增加钱
    ret = user:GMCommand("SetMoney(3,1234)");
    check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==3, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --登出
    cleanup(user);
end

function TestCase.Item.Sign()

    --登录
	local user_name1 = "SignItem" .. os.date("%H%M%S");
    user1, role1 = startup(user_name1, user_name1)
    check(user1, "failed to create user");
    check(role1, "failed to create role");

	local user_name2 = "SignItem" .. os.date("%H%M%S");

	user2, role2 = startup(user_name2, user_name2)
    check(user2, "failed to create user");
    check(role2, "failed to create role");

    local usersessionid1 = user1:GetSessionID();
    local usersessionid2 = user2:GetSessionID();
	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();

	 --用GM指令增加一件物品
    --ret = user1:GMCommand("AddItem(1000005,1)");  -- 开天
    --check(ret, "failed to send gm command");

    --检查增加的物品确实是GM指令所加的
    --local msg = recv_msg(5, usersessionid1, protocol.g2c_item_change);
    --check(msg, "failed to recv g2c_item_change");

	--对装备进行签名
	ret = g_RobotMessageHandler:DoSignItem(role1, 0, 0);
	check(ret, "fail to sign item");

	--检查签名的回包
    msg = recv_msg(5, usersessionid1, protocol.g2c_sign_item);
    check(msg, "failed to recv g2c_sign_item");

	ret = g_RobotMessageHandler:DoSayWithItem(role1, user_name2);
	check(ret, "fail to say with item");

	--检查聊天的回包
    msg = recv_msg(5, usersessionid2, protocol.m2c_chat_message);
	check(msg, "fail to receive chat message");
	local username = get_role_name_from_msmessage(msg);

	check(username == user_name1, "fail to receive wrong target name");

	local chatcontent = get_chat_content_from_msmessage(msg);
	--验证签名
	ret = user2:VerifyItem(user1id, chatcontent);
	check(ret, "failed to verify rsa signup");
end


function ItemFieldRangeCheck(item_data)
	if item_data.m_nTemplateID == 0 then
		return ;
	end
	check(item_data.m_byType > ITEMTYPE_INVALID and item_data.m_byType < ITEMTYPE_TOTAL, "item table  type error");
	check(item_data.m_bySubType > ITEMSUBTYPE_INVALID and item_data.m_bySubType < 16,
			"item table sub type error, temp_id: "..item_data.m_nTemplateID);

	--if then
	--end

	check(item_data.m_byRequireLevel > 0,
			"require level error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_byRequireClass >= 0 and item_data.m_byRequireClass <= 16,
			"require class error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_byRequireGender >= 0 and item_data.m_byRequireGender < 4,
			"require gender error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_byBindType > -1 and item_data.m_byBindType < BINDTYPE_BINDED,
			"bind type error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_byDurType > -1 and item_data.m_byDurType < 4,
			"dur type error, temp_id: "..item_data.m_nTemplateID);

	if item_data.m_byDurType == 0 then
		check(item_data.m_nDur >= 0, "item table dur error, temp_id: "
				..item_data.m_nTemplateID);
	else
		check(item_data.m_nDur > 0, "item table dur error, temp_id: "
			..item_data.m_nTemplateID);
	end

	check(item_data.m_byUseInCombat >= 0 and item_data.m_byUseInCombat < 3,
			"use type error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_nSellPrice >= 0 and item_data.m_nSellPrice < 1000000000,
			"sell price error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_nSpellID >= 0,
			"spell id error, temp_id: "..item_data.m_nTemplateID);

	check(item_data.m_nSpellLevel >= 0,
			"spell level error, temp_id: "..item_data.m_nTemplateID);
	if item_data.m_nSpellID > 0 then
		check(item_data.m_nSpellLevel > 0,
			"spell level error, temp_id: "..item_data.m_nTemplateID);
	end
end


function TestCase.Item.EquipCheck()
	local user_name = "Equip" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;
	local item2;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
    while equip_data do
		if equip_data.m_nTemplateID ~= 0 then
			print("Equip begin ID: "..equip_data.m_nTemplateID);
			-- 字段范围检测
			ItemFieldRangeCheck(equip_data);

			--用GM指令增加一件物品
			ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
			check(ret, "failed to send gm command");

			--检查增加的物品确实是GM指令所加的
			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");

			item = role:GetItemBag():GetItem(3,0);
			check(item, "failed to get item");
			check(item.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID,"failed to get correct item");

			-- 检测绑定属性
			--if equip_data.m_byBindType == 3 then
			--	print("bind type templateID "..equip_data.m_nTemplateID);
			--	check(item.m_iteminfo.m_byBindType == 10,"item bind fail");
			--end

			-- 检测叠加属性
			if equip_data.m_byDurType == 2 then
				check(nil, "equip field DurType error");
			else
				--再加一个同样的物品
				ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--检查增加的物品确实是GM指令所加的
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				item2 = role:GetItemBag():GetItem(3,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID,	"failed to get correct item");

				--删除新加的物品
				ret = user:DeleteItem(3, 1, 1);
				check(ret, "failed to send delete item msg");

				--检查删除物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == 3 and msg.byItemSlot == 1,"failed to delete correct item");
			end

			--删除新加的物品
			ret = user:DeleteItem(3, 0, 1);
			check(ret, "failed to send delete item msg");

			--检查删除物品的回包
			msg = recv_msg(5, session_id, protocol.g2c_item_delete);
			check(msg, "failed to recv g2c_item_delete");
			check(msg.byConSlot == 3 and msg.byItemSlot == 0,"failed to delete correct item");

			print("AddEquip OK " .. equip_data.m_nTemplateID);
		end

		equip_data = CDataManager_EQUIP_DATA_:GetInstance()
						:GetNextData();

    end

	--登出
    cleanup(user);
end

function TestCase.ItemCheck()
	local user_name = "Item" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;
	local item2;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	local item_data = CDataManager_ITEM_DATA_:GetInstance():GetFirstData();
    while item_data do
		if item_data.m_nTemplateID > 100 then
			print("Equip begin ID: "..item_data.m_nTemplateID);
			-- 字段范围检测
			ItemFieldRangeCheck(item_data);

			--用GM指令增加一件物品
			ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
			check(ret, "failed to send gm command");

			--检查增加的物品确实是GM指令所加的
			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");

			-- 判断包裹位置
			local conSlot = 2;	-- 默认包裹
			if item_data.m_byType == 3 then -- 材料
				conSlot = 4;
			elseif item_data.m_byType == 9 then -- 任务
				conSlot = 5;
			end

			-- 获取新增物品，开始检测逻辑
			item = role:GetItemBag():GetItem(conSlot,0);
			check(item, "failed to get item");
			check(item.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");

			-- 检测绑定属性
			--if item_data.m_byBindType == 3 then
			--	check(item.m_iteminfo.m_byBindType == 10,"item bind fail");
			--end

			-- 检测叠加属性
			if item_data.m_byDurType == 2 and item_data.m_nDur ~= 1 then
				-- 不到上限检测
				ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID..", "..item_data.m_nDur..")");
				check(ret, "failed to send gm command");
				-- 叠加数量过低
				if item_data.m_nDur - 2 < 0 then
					check(nil, "dur num error! type : 2 , num: " .. item_data.m_nDur);
				end

				--检查增加的物品确实是GM指令所加的
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				-- 超过上限分格子检测
				item = role:GetItemBag():GetItem(conSlot,1);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				print("dur num : "..item.m_iteminfo.m_shCurDur.." "..item_data.m_nDur);
				check(item.m_iteminfo.m_shCurDur == item_data.m_nDur,"ItemDurNum error");

				-- 第二个格子检测
				item2 = role:GetItemBag():GetItem(conSlot,0);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				check(item2.m_iteminfo.m_shCurDur == 1,"ItemDurNum error");

				--删除新加的物品
				ret = user:DeleteItem(conSlot, 1, 2);
				check(ret, "failed to send delete item msg");

				--检查删除物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_delete");

				item2 = role:GetItemBag():GetItem(conSlot,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				check(item2.m_iteminfo.m_shCurDur == item_data.m_nDur - 2, "ItemDurNum error");

				-- 合并，拆分检测

				-- 先拆分(其中包括堆叠)
				ret = user:SplitItem(conSlot, 1, conSlot, 0, 1);
				check(ret, "failed to send split item msg");

				--检查拆分物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				--
				item = role:GetItemBag():GetItem(conSlot,1);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID == item_data.m_nTemplateID, "failed to get correct item");
				check(item.m_iteminfo.m_shCurDur == item_data.m_nDur - 3, "item num error");

				item = role:GetItemBag():GetItem(conSlot,0);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID == item_data.m_nTemplateID, "failed to get correct item");
				check(item.m_iteminfo.m_shCurDur == 2, "item num error");

				-- 再移动
				ret = user:MoveItem(conSlot, 1, conSlot, 2);
				check(ret, "failed to send move item msg");

				--检查移动物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_swap);
				check(msg, "failed to recv g2c_item_swap");
				check(msg.wSrcConSlot==conSlot and msg.wSrcItemSlot==1 and
					  msg.wDstConSlot==conSlot and msg.wDstItemSlot==2,
					  "failed to get correct g2c_item_swap message");

				item = role:GetItemBag():GetItem(conSlot,2);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID == item_data.m_nTemplateID, "failed to get correct item");
				check(item.m_iteminfo.m_shCurDur == item_data.m_nDur - 3, "item num error");
				print("temp show2: "..item.m_iteminfo.m_shCurDur.." "..item_data.m_nDur);

				--
				item = role:GetItemBag():GetItem(conSlot,0);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID == item_data.m_nTemplateID, "failed to get correct item");
				check(item.m_iteminfo.m_shCurDur == 2, "item num error");
				print("temp show3: "..item.m_iteminfo.m_shCurDur.." "..item_data.m_nDur);
				--

				-- 最后合并
				ret = user:MoveItem(conSlot, 2, conSlot, 0);
				check(ret, "failed to send move item msg");
				--检查堆叠物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot==conSlot and msg.byItemSlot==2,
					  "failed to recv correct g2c_item_delete after stacking");

				item = role:GetItemBag():GetItem(conSlot,0);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID == item_data.m_nTemplateID, "failed to get correct item");
				print("temp show55:"..item.m_iteminfo.m_shCurDur.." "..item_data.m_nDur);
				check(item.m_iteminfo.m_shCurDur == item_data.m_nDur - 1, "item num error");

				-- 清空现场
				ret = user:DeleteItem(conSlot, 0, item.m_iteminfo.m_shCurDur);
				check(ret, "failed to send delete item msg");

				--检查删除物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 0,"failed to delete correct item");
			else	-- 无耐久，使用次数和装备耐久，应该都是不可叠加属性
				--再加一个同样的物品
				ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--检查增加的物品确实是GM指令所加的
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				item2 = role:GetItemBag():GetItem(conSlot,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");

				--删除新加的物品
				ret = user:DeleteItem(conSlot, 1, 1);
				check(ret, "failed to send delete item msg");

				--检查删除物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 1,"failed to delete correct item");

				--删除新加的物品
				ret = user:DeleteItem(conSlot, 0, 1);
				check(ret, "failed to send delete item msg");

				--检查删除物品的回包
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 0,"failed to delete correct item");
			end
		end

        print("AddItem OK " .. item_data.m_nTemplateID);
        item_data = CDataManager_ITEM_DATA_:GetInstance():GetNextData();
    end

	--登出
    cleanup(user);
end


function TestCase.UseDicPKValue()

	local user_name = "UseItem" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();


	ret = user:GMCommand("AddItem(100002, 1)");
	check(ret, "failed to send gm command");

	--检查增加的物品确实是GM指令所加的
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
	check(msg, "failed to recv g2c_item_change");

	item = role:GetItemBag():GetItem(2,0);
	check(item, "failed to get item");
	check(item.m_iteminfo.m_nTemplateID==100002,"failed to get correct item");
	role:GetItemBag():UseItem(2, 0, 100002);



	--登出
    cleanup(user);
end


function TestCase.Item.Use()
	local user_name = "Item" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;
	local conSlot;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	--ret = user:GMCommand("SetHp(2)");
	--check(ret, "failed to send gm command");

	ret = user:GMCommand("EnableCD(false)");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddExp(2000000)");
	check(ret, "failed to send gm command");

	-- 清空包裹
	item = role:GetItemBag():GetItem(2, 0);
	while item do
		--
		ret = user:DeleteItem(2, 0, 1);
		check(ret, "failed to send delete item msg");

		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(2, 0);
	end

	item = role:GetItemBag():GetItem(4, 0);
	while item ~= nil do
		--
		ret = user:DeleteItem(4, 0, 1);
		check(ret, "failed to send delete item msg");
		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(4, 0);
	end

	item = role:GetItemBag():GetItem(5, 0);
	while item ~= nil do
		--
		ret = user:DeleteItem(5, 0, 1);
		check(ret, "failed to send delete item msg");
		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(5, 0);
	end

	local item_data = CDataManager_ITEM_DATA_:GetInstance():GetFirstData();
	while item_data do
		-- 判断包裹位置

		if item_data.m_byType == 3 then -- 材料
			conSlot = 4;
		elseif item_data.m_byType == 9 then -- 任务
			conSlot = 5;
		else
			conSlot = 2;	-- 默认包裹
		end

		if item_data.m_nTemplateID >100 then
			-- 可使用的物品
			if item_data.m_byType == 1 then

				-- 选择职业
				if item_data.m_byRequireClass > 0 then
					user:GMCommand("SelfRole:SetClass("..((item_data.m_byRequireClass - 1)%4)..");");
				end

				print("UseItem Begin " .. item_data.m_nTemplateID);
				if item_data.m_nSpellID > 0 then
					ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
					check(ret, "failed to send gm command");

					--检查增加的物品确实是GM指令所加的
					msg = recv_msg(5, session_id, protocol.g2c_item_change);
					check(msg, "failed to recv g2c_item_change");

					item = role:GetItemBag():GetItem(conSlot,0);
					check(item, "failed to get item");
					print("item templateID: "..item.m_iteminfo.m_nTemplateID);
					check(item.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");

					role:GetItemBag():UseItem(conSlot, 0, item_data.m_nTemplateID);

					msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
					check(msg, "failed to recv g2c_char_prepare_spell");

					if item_data.m_byDurType == 2 then
						msg = recv_msg(10, session_id, protocol.g2c_item_delete);
						check(msg, "failed to recv g2c_item_delete");
					else
						msg = recv_msg(10, session_id, protocol.g2c_item_change);
						check(msg, "failed to recv g2c_item_delete");

						ret = user:DeleteItem(conSlot, 0, 1);
						check(ret, "failed to send delete item msg");
						msg = recv_msg(5, session_id, protocol.g2c_item_delete);
						check(msg, "failed to recv g2c_item_delete");
					end

				elseif item_data.m_szScript ~= 0 then
					print(item_data.m_szScript);
					--check(nil, "script ~= 0");
					-- 如果没有技能，就必然有脚本
				elseif item_data.m_szScript == 0 then
					check(nil, "script:use item can not use");
					-- 现在是允许的
				else
					check(nil, "use item can not use");
				end

			end
		end

		print("UseItem OK " .. item_data.m_nTemplateID);
        item_data = CDataManager_ITEM_DATA_:GetInstance():GetNextData();
	end

	--登出
    cleanup(user);
end




-- 根据子类型获取装备部位
function GetEquipPos(subType)
	if subType == ITEMSUBTYPE_EQUIP_WEAPON then
		return NES_MAIN_HAND;
	elseif subType == ITEMSUBTYPE_EQUIP_HAT then
		return NES_HEAD;
	elseif subType == ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR then
		return NES_SHOULDER;
	elseif subType == ITEMSUBTYPE_EQUIP_CHEST_ARMOR then
		return NES_BODY;
	elseif subType == ITEMSUBTYPE_EQUIP_PANTS then
		return NES_LEG;
	elseif subType == ITEMSUBTYPE_EQUIP_WRIST_ARMOR then
		return NES_ARM;
	elseif subType == ITEMSUBTYPE_EQUIP_BELT then
		return NES_WAIST;
	elseif subType == ITEMSUBTYPE_EQUIP_SHOES then
		return NES_FOOT;
	elseif subType == ITEMSUBTYPE_EQUIP_CLOAK then
		return NES_BACK;
	elseif subType == ITEMSUBTYPE_EQUIP_NECKLACE then
		return NES_NECK;
	elseif subType == ITEMSUBTYPE_EQUIP_RING then
		return NES_FINGER_L;
	elseif subType == ITEMSUBTYPE_EQUIP_BRACELET then
		return NES_WRIST_L;
	elseif subType == ITEMSUBTYPE_EQUIP_AVATAR then
		return NES_AVATAR;
	elseif subType == ITEMSUBTYPE_EQUIP_NECKLACE then
		return NES_NECK;
    else
        return nil;
	end
end





function TestCase.Item.EquipItem()
	local user_name = "Equip" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;
	local conSlot = 3;	-- 装备，没的选包裹

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	ret = user:GMCommand("EnableCD(false)");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddExp(2000000)");
	check(ret, "failed to send gm command");

	-- 清空包裹
	item = role:GetItemBag():GetItem(3, 0);
	while item do
		--
		ret = user:DeleteItem(3, 0, 1);
		check(ret, "failed to send delete item msg");

		msg = recv_msg(5, session_id, protocol.g2c_item_delete);
		check(msg, "failed to recv g2c_item_delete");
		item = role:GetItemBag():GetItem(3, 0);
	end

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
	while equip_data do
		if equip_data.m_nTemplateID >100 and equip_data.m_nTemplateID ~= 1999997 and equip_data.m_nTemplateID ~= 1999998 and equip_data.m_nTemplateID ~= 1999999 then
			-- 可使用的物品
			if equip_data.m_byType == 2 then
				-- 选择职业
				if equip_data.m_byRequireClass == 4 then
					user:GMCommand("SelfRole:SetClass(2);");
				elseif equip_data.m_byRequireClass > 0 then
					user:GMCommand("SelfRole:SetClass("..((equip_data.m_byRequireClass - 1)%4)..");");
				end
				print("UseEquip Begin " .. equip_data.m_nTemplateID);

				ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--检查增加的物品确实是GM指令所加的
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				local dstItemSlot = GetEquipPos(equip_data.m_bySubType);
				--堆叠物品
				ret = user:MoveItem(3, 0, 0, dstItemSlot);
				check(ret, "failed to send move item msg");

				msg = recv_msg(5, session_id, protocol.g2c_item_swap);
				check(msg, "failed to recv g2c_item_swap");

				if dstItemSlot < 11 then
					msg = recv_msg(5, session_id, protocol.g2c_sync_role_avatar);
					check(msg, "failed to recv g2c_sync_role_avatar");
				end

				-- 说不定有脱下来的...把之前脱下来的删了，再继续脱
				item = role:GetItemBag():GetItem(3, 0);
				if item then
					ret = user:DeleteItem(conSlot, 0, 1);
					check(ret, "failed to send delete item msg");
					msg = recv_msg(5, session_id, protocol.g2c_item_delete);
					check(msg, "failed to recv g2c_item_delete");
				end

				ret = user:MoveItem(0, dstItemSlot, 3, 0);
				check(ret, "failed to send move item msg");

				msg = recv_msg(5, session_id, protocol.g2c_item_swap);
				check(msg, "failed to recv g2c_item_swap");

				ret = user:DeleteItem(conSlot, 0, 1);
				check(ret, "failed to send delete item msg");
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");

			end
		end

		print("UseEquip OK " .. equip_data.m_nTemplateID);
        equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetNextData();
	end

	--登出
    cleanup(user);
end


function TestCase.Item.CD()
	local user_name = "ItCD" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local item;
	local conSlot;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	--用GM指令增加测试物品
    ret = user:GMCommand("AddItem(99, 1)");
    check(ret, "failed to send gm command");

    --检查物品回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--使用
	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--使用物品成功
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--再使用
	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--使用物品失败
	msg = recv_msg(5, session_id, protocol.g2c_error_notify);
	check(msg, "failed to recv g2c_error_notify");
	check(msg.nErrCode == error_code.errItemNotReady, "failed to recv correct err msg");

	--等35秒后再次使用
	wait(35);

	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--使用物品成功
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--登出
    cleanup(user);
end

function TestCase.Item.NovicePackage()
	local user_name = "NP" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	--用GM指令增加新手礼包
    ret = user:GMCommand("AddItem(1000011, 1)");
    check(ret, "failed to send gm command");

    --检查物品回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--使用
	ret = role:GetItemBag():UseItem(2, 0, 1000011);
	check(ret, "failed to use item");

	--使用物品成功
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    	--登出
    cleanup(user);
end

function TestCase.Item.RoleLogoutDLSaveItem()
	local user_name = "DLItem" .. os.date("%Y%H%M%S");

	--登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

	--用GM指令增加测试物品
    ret = user:GMCommand("AddItem(99, 1)");
    check(ret, "failed to send gm command");

    --检查物品回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --登出
    cleanup(user);

end

function TestCase.Item.TradeItem()
	local user_name1 = "TradeItem17" .. os.date("%Y%H%M%S");
	local user_name2 = "TradeItem18" .. os.date("%Y%H%M%S");

	--登录
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");
    local session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
    local session_id2 = user2:GetSessionID();

    local ret = user1:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");

	wait(10);

    ret = user2:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");

	wait(10);

	ret = user1:GMCommand("AddMoney(1, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(5);

	--用GM指令增加测试物品
    ret = user1:GMCommand("AddItem(101, 1)");
    check(ret, "failed to send gm command");

    --检查物品回包
    msg = recv_msg(5, session_id1, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    performance_trade_with_role(user1, user2, 101);

    --登出
    cleanup(user1);
    cleanup(user2);
end

function performance_trade_with_role(user, targetuser, itemid)
	local srcrole = user:GetPlayingRole()
	if srcrole == nil then
		return;
	end

	local targetrole = targetuser:GetPlayingRole()
	if targetrole == nil then
		return;
	end

    local session_id1 = user:GetSessionID();
    local session_id2 = targetuser:GetSessionID();

	--user: 请求交易
    ret = user:AskTrade(targetrole:GetObjID());
    check(ret, "failed to ask trade");

    --targetuser: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: 接受交易
    ret = targetuser:AcceptTrade(srcrole:GetObjID());
    check(ret, "failed to cancel trade");

    --user1: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user: 出1000块钱
    ret = user:SetTradeMoney(1000);
    check(ret, "failed to set trade money");

    --targetuser: 收到user出钱的消息
    msg = recv_msg(5, session_id2, protocol.g2c_trade_set_money);
    check(msg, "failed to recv g2c_trade_set_money");

    wait(2);

    --user: 锁定
    ret = user:LockTrade();
    check(ret, "failed to lock trade");

    --targetuser: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: 锁定
    ret = targetuser:LockTrade();
    check(ret, "failed to lock trade");

    --user: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user: 确认
    ret = user:ConfirmTrade();
    check(ret, "failed to lock trade");

    --targetuser: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: 确认
    ret = targetuser:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    --targetuser: 收到钱
    msg = recv_msg(5, session_id2, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_money_change");
    check(msg.nMoney == 1000, "failed to recv correct money (user2)");
end

function FindItemPosInEquipBag(nItemTemplateID)
    local bag = TargetRole:GetItemBag()
	for i = 0, 31 do
		local item = bag:GetItem(CONSLOT_DEFAULT, i);
		if item then
			if (item.m_pTemplate.m_nTemplateID == nItemTemplateID) then
				return i;
			end
		end
	end
	print("failed to find item "..nItemTemplateID.." pos in equip bag");
end

function TestCase.Item.TradeMoney()
	local user_name1 = "TradeMoney47" .. os.date("%Y%H%M%S");
	local user_name2 = "TradeMoney48" .. os.date("%Y%H%M%S");

	--登录
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");
    local session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
    local session_id2 = user2:GetSessionID();

    local session_id1 = user1:GetSessionID();
    local session_id2 = user2:GetSessionID();

    local ret = user1:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");

	wait(10);

    ret = user2:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");

	wait(10);

	-- 加钱

	local ret = user1:GMCommand("AddMoney(1, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	ret = user2:GMCommand("AddMoney(1, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(5);

	-- 加魂

	ret = user1:GMCommand("AddMoney(5, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	ret = user2:GMCommand("AddMoney(5, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(5);

	-- 升等级

	local ret = user1:GMCommand("SetLevel(10)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

	local ret = user2:GMCommand("SetLevel(10)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

	-- 境界每个人提升10次

	for changecount = 1, 10 do
	    ret = user1:ChangeSoul2Pts(true, true); --在线转化
		check(ret, "fail to send changesoul2pts");

	    msg = recv_msg(100, session_id1, protocol.g2c_spirit_exp_change);
		check(msg, "failed to recv g2c_spirit_exp_change");

		wait(1);
	end

	for changecount = 1, 10 do
	    ret = user2:ChangeSoul2Pts(true, true); --在线转化
		check(ret, "fail to send changesoul2pts");

	    msg = recv_msg(100, session_id2, protocol.g2c_spirit_exp_change);
		check(msg, "failed to recv g2c_spirit_exp_change");

		wait(1);
	end

	--user1: 请求交易
    ret = user1:AskTrade(role2:GetObjID());
    check(ret, "failed to ask trade");

    --user2: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: 接受交易
    ret = user2:AcceptTrade(role1:GetObjID());
    check(ret, "failed to accept trade");

    --user1: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: 出1000块钱
    ret = user1:SetTradeMoney(1000);
    check(ret, "failed to set trade money");

    --user2: 收到user1出钱的消息
    msg = recv_msg(5, session_id2, protocol.g2c_trade_set_money);
    check(msg, "failed to recv g2c_trade_set_money");

    wait(2);

    --user1: 锁定
    ret = user1:LockTrade();
    check(ret, "failed to lock trade");

    --user2: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: 锁定
    ret = user2:LockTrade();
    check(ret, "failed to lock trade");

    --user1: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: 确认
    ret = user1:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user2: 收到交易状态改变
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: 确认
    ret = user2:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user: 收到交易状态改变
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    --targetuser: 收到钱

    msg = recv_msg(5, session_id2, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_money_change");

	cleanup(user1);
	cleanup(user2);
end
