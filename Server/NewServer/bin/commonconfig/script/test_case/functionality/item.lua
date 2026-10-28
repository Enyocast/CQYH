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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
    --while equip_data do
        ----Add an item using a GM command
        --ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
        --check(ret, "failed to send gm command");
--
        ----Check that the added item came from the GM command
        --msg = recv_msg(5, session_id, protocol.g2c_item_change);
        --check(msg, "failed to recv g2c_item_change");
--
        ----check(msg.stItem.nTemplateID==equip_data.m_nTemplateID, "failed to create correct item");
        --item = role:GetItemBag():GetItem(3,0);
        --check(item, "failed to get item");
        --check(item.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID, "failed to get correct item");
--
        ----Remove the newly added item
        --ret = user:DeleteItem(3, 0, 1);
        --check(ret, "failed to send delete item msg");
--
        ----Check the remove-item response
        --msg = recv_msg(5, session_id, protocol.g2c_item_delete);
        --check(msg, "failed to recv g2c_item_delete");
        --check(msg.byConSlot == 3 and msg.byItemSlot == 0, "failed to delete correct item");
--
        --print("AddItem OK " .. equip_data.m_nTemplateID);
        --equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetNextData();
    --end

	-- First remove the item to be added
	item = role:GetItemBag():GetItem(2,0);
	if item then
		print("begin send delete item msg");
		ret = user:DeleteItem(2, 0, item.m_iteminfo.m_shCurDur, item.m_iteminfo.m_nTemplateID);
		check(ret, "failed to send delete item msg");
	end

    --Add potions using a GM command for the move and split tests below
    ret = user:GMCommand("AddItem(123,10)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    item = role:GetItemBag():GetItem(2,0);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    print("item num " .. item.m_iteminfo.m_shCurDur);
    check(item.m_iteminfo.m_shCurDur == 10, "item num error");
    --check(msg.stItem.nTemplateID==101, "failed to create correct item");
    --check(msg.stItem.nCurDur==10, "failed to create correct item");

    --Log out
    cleanup(user);
    wait(5);

    --Log in again
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --Move item
    ret = user:MoveItem(2, 0, 2, 1);
    check(ret, "failed to send move item msg");

    --Check the move-item response
    msg = recv_msg(5, session_id, protocol.g2c_item_swap);
    check(msg, "failed to recv g2c_item_swap");
    check(msg.wSrcConSlot==2 and
          msg.wSrcItemSlot==0 and
          msg.wDstConSlot==2 and
          msg.wDstItemSlot==1,
          "failed to get correct g2c_item_swap message");

    --Split item
    ret = user:SplitItem(2, 1, 2, 2, 5);
    check(ret, "failed to send split item msg");

    --Check the split-item response
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
	-- New check: inspect two packets at once
	item = role:GetItemBag():GetItem(2,2);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    check(item.m_iteminfo.m_shCurDur == 5, "item num error");

    item = role:GetItemBag():GetItem(2,1);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 123, "failed to get correct item");
    check(item.m_iteminfo.m_shCurDur == 5, "item num error");

    --Stack items
    ret = user:MoveItem(2, 2, 2, 1);
    check(ret, "failed to send move item msg");

    --Check the stack-item response
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

    --Destroy item
    ret = user:DeleteItem(2,1,10);
    check(ret, "failed to send delete item msg");

    --Check the destroy-item response
    msg = recv_msg(5, session_id, protocol.g2c_item_delete);
    check(msg, "failed to recv g2c_item_delete");
    check(msg.byConSlot==2 and
          msg.byItemSlot==1,
          "failed to recv correct g2c_item_delete after deleting");

    --Log out
    cleanup(user);
end


function TestCase.Item.RunScript()
    local user_name = "Attr" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

	--Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

   --Add potions using a GM command for the move and split tests below
    ret = user:GMCommand("AddItem(101,1)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	print("role-level:"..role:GetLevel());
	local currentLevel = role:GetLevel();

	role:GetItemBag():UseItem(2, 0, 101);

	wait(2);


    --Log out
    cleanup(user);

	wait(2);

	user, role = startup(user_name, user_name);

	wait(2);

	print("role-level:"..role:GetLevel());
	check(currentLevel < role:GetLevel(), "use item failed");

	--Log out
    cleanup(user);
end



function TestCase.Item.Attribute()
    local user_name = "Attr" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);

    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    --Add a test weapon using a GM command
    ret = user:GMCommand("AddItem(190002,1)");
    check(ret, "failed to send gm command");

    --Check the added item attributes
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    item = role:GetItemBag():GetItem(3,0);
    check(item, "failed to get item");
    check(item.m_iteminfo.m_nTemplateID == 190002, "failed to get correct item");
    print("item attr count " .. item.m_iteminfo.m_byAttrCount);
    check(item.m_iteminfo.m_byAttrCount == 2, "item num error");
    --check(msg.stItem.byAttrCount>=8, "failed to create correct item");
    --check(msg.stItem.astAttrs[0].shParam>=95 and msg.stItem.astAttrs[0].shParam<=110, "failed to create correct item");

    --Equip
    ret = user:MoveItem(3, 0, 0, 0);
    check(ret, "failed to send move item msg");

    --Log out
    cleanup(user);
end

function TestCase.Item.Shop()
    local user_name = "Shop" .. os.date("%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    wait(2);
    --Spawn an NPC using a GM command
    ret = user:GMCommand("SummonNpc(6003)");
    check(ret, "failed to send gm command");

    --Check the spawned NPC
    msg = recv_msg(5, session_id, protocol.g2c_char_appear)
    check(msg, "Npc appear fail.")
    local diag_npc_id = msg.stAppearData.dwCharID
    check(diag_npc_id ~= 0, "Npc appear fail.")

    --msg = recv_msg(5, session_id, protocol.g2c_sync_char_list);
    --check(msg, "failed to recv sync char list msg");

    --local diag_npc_id = get_npc_id_from_list(msg, 2001);
    --check(diag_npc_id ~= 0, "npc appear fail");

    --Select the NPC
    ret = user:InteractWithNpc(diag_npc_id);
    check(ret, "failed to interact with npc");

    --Buy an item
    ret = user:BuyItem(3);
    check(ret, "failed to send buy item msg");

    --Check the response
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --Log out
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    wait(2);

		-- Clear the inventory
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
		--Spawn an NPC using a GM command
		ret = user:GMCommand("SummonNpc("..npc_id..")");
		check(ret, "failed to send gm command");

		--Check the spawned NPC
		msg = recv_msg(5, session_id, protocol.g2c_char_appear)
		check(msg, "Npc appear fail.")
		local diag_npc_id = msg.stAppearData.dwCharID
		check(diag_npc_id ~= 0, "Npc appear fail.")

		--msg = recv_msg(5, session_id, protocol.g2c_sync_char_list);
		--check(msg, "failed to recv sync char list msg");

		--local diag_npc_id = get_npc_id_from_list(msg, 2001);
		--check(diag_npc_id ~= 0, "npc appear fail");

		--Select the NPC
		ret = user:InteractWithNpc(diag_npc_id);
		check(ret, "failed to interact with npc");

		print(npc_id);
		local npc_data = CDataManager_NPC_DATA_:GetInstance():GetData(npc_id);
		print(npc_data.nShopID);
		local shop_data = CDataManager_SHOP_DATA_:GetInstance():GetData(npc_data.nShopID);

		--Add money using a GM command
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
				--Buy an item
				ret = user:BuyItem(i-1);
				check(ret, "failed to send buy item msg");

				--Check the response
				msg = recv_msg(30, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				local item_data = CDataManager_ITEM_DATA_:GetInstance():GetData(shop_data.m_ShopItem[i-1].m_nItemID);
				if item_data == nil then
					item_data = CDataManager_EQUIP_DATA_:GetInstance():GetData(shop_data.m_ShopItem[i-1].m_nItemID);
					if item_data == nil then
						check(false, "cannot find item in item.txt");
					end
				end

				-- Check the inventory slot
				if item_data.m_byType == 3 then -- Materials
					conSlot = 4;
				elseif item_data.m_byType == 9 then -- Quest
					conSlot = 5;
				elseif item_data.m_byType == 2 then
					conSlot = 3;		-- Equip
				else
					conSlot = 2;	-- Default inventory
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

    --Log out
    cleanup(user);
end

function TestCase.Item.Money()
    local user_name = "Money" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --Add money using a GM command
    ret = user:GMCommand("SetMoney(0,1234)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==0, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --Add money using a GM command
    ret = user:GMCommand("SetMoney(1,1234)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==1, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --Add money using a GM command
    ret = user:GMCommand("SetMoney(2,1234)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==2, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --Add money using a GM command
    ret = user:GMCommand("SetMoney(3,1234)");
    check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    msg = recv_msg(5, session_id, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.nMoneyType==3, "failed to create correct money");
    check(msg.nMoney==1234, "failed to create correct money");

    --Log out
    cleanup(user);
end

function TestCase.Item.Sign()

    --Log in
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

	 --Add an item using a GM command
    --ret = user1:GMCommand("AddItem(1000005,1)");  -- Heaven Splitter
    --check(ret, "failed to send gm command");

    --Check that the added item came from the GM command
    --local msg = recv_msg(5, usersessionid1, protocol.g2c_item_change);
    --check(msg, "failed to recv g2c_item_change");

	--Sign the equipment
	ret = g_RobotMessageHandler:DoSignItem(role1, 0, 0);
	check(ret, "fail to sign item");

	--Check the signature response
    msg = recv_msg(5, usersessionid1, protocol.g2c_sign_item);
    check(msg, "failed to recv g2c_sign_item");

	ret = g_RobotMessageHandler:DoSayWithItem(role1, user_name2);
	check(ret, "fail to say with item");

	--Check the chat response
    msg = recv_msg(5, usersessionid2, protocol.m2c_chat_message);
	check(msg, "fail to receive chat message");
	local username = get_role_name_from_msmessage(msg);

	check(username == user_name1, "fail to receive wrong target name");

	local chatcontent = get_chat_content_from_msmessage(msg);
	--Verify the signature
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	local equip_data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
    while equip_data do
		if equip_data.m_nTemplateID ~= 0 then
			print("Equip begin ID: "..equip_data.m_nTemplateID);
			-- Check field ranges
			ItemFieldRangeCheck(equip_data);

			--Add an item using a GM command
			ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
			check(ret, "failed to send gm command");

			--Check that the added item came from the GM command
			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");

			item = role:GetItemBag():GetItem(3,0);
			check(item, "failed to get item");
			check(item.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID,"failed to get correct item");

			-- Check the binding attribute
			--if equip_data.m_byBindType == 3 then
			--	print("bind type templateID "..equip_data.m_nTemplateID);
			--	check(item.m_iteminfo.m_byBindType == 10,"item bind fail");
			--end

			-- Check the stacking attribute
			if equip_data.m_byDurType == 2 then
				check(nil, "equip field DurType error");
			else
				--Add another identical item
				ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--Check that the added item came from the GM command
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				item2 = role:GetItemBag():GetItem(3,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==equip_data.m_nTemplateID,	"failed to get correct item");

				--Remove the newly added item
				ret = user:DeleteItem(3, 1, 1);
				check(ret, "failed to send delete item msg");

				--Check the remove-item response
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == 3 and msg.byItemSlot == 1,"failed to delete correct item");
			end

			--Remove the newly added item
			ret = user:DeleteItem(3, 0, 1);
			check(ret, "failed to send delete item msg");

			--Check the remove-item response
			msg = recv_msg(5, session_id, protocol.g2c_item_delete);
			check(msg, "failed to recv g2c_item_delete");
			check(msg.byConSlot == 3 and msg.byItemSlot == 0,"failed to delete correct item");

			print("AddEquip OK " .. equip_data.m_nTemplateID);
		end

		equip_data = CDataManager_EQUIP_DATA_:GetInstance()
						:GetNextData();

    end

	--Log out
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	local item_data = CDataManager_ITEM_DATA_:GetInstance():GetFirstData();
    while item_data do
		if item_data.m_nTemplateID > 100 then
			print("Equip begin ID: "..item_data.m_nTemplateID);
			-- Check field ranges
			ItemFieldRangeCheck(item_data);

			--Add an item using a GM command
			ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
			check(ret, "failed to send gm command");

			--Check that the added item came from the GM command
			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");

			-- Check the inventory slot
			local conSlot = 2;	-- Default inventory
			if item_data.m_byType == 3 then -- Materials
				conSlot = 4;
			elseif item_data.m_byType == 9 then -- Quest
				conSlot = 5;
			end

			-- Get the added item and start checking
			item = role:GetItemBag():GetItem(conSlot,0);
			check(item, "failed to get item");
			check(item.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");

			-- Check the binding attribute
			--if item_data.m_byBindType == 3 then
			--	check(item.m_iteminfo.m_byBindType == 10,"item bind fail");
			--end

			-- Check the stacking attribute
			if item_data.m_byDurType == 2 and item_data.m_nDur ~= 1 then
				-- Check below the limit
				ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID..", "..item_data.m_nDur..")");
				check(ret, "failed to send gm command");
				-- Stack count is too low
				if item_data.m_nDur - 2 < 0 then
					check(nil, "dur num error! type : 2 , num: " .. item_data.m_nDur);
				end

				--Check that the added item came from the GM command
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				-- Check splitting into slots above the limit
				item = role:GetItemBag():GetItem(conSlot,1);
				check(item, "failed to get item");
				check(item.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				print("dur num : "..item.m_iteminfo.m_shCurDur.." "..item_data.m_nDur);
				check(item.m_iteminfo.m_shCurDur == item_data.m_nDur,"ItemDurNum error");

				-- Check the second slot
				item2 = role:GetItemBag():GetItem(conSlot,0);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				check(item2.m_iteminfo.m_shCurDur == 1,"ItemDurNum error");

				--Remove the newly added item
				ret = user:DeleteItem(conSlot, 1, 2);
				check(ret, "failed to send delete item msg");

				--Check the remove-item response
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_delete");

				item2 = role:GetItemBag():GetItem(conSlot,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");
				check(item2.m_iteminfo.m_shCurDur == item_data.m_nDur - 2, "ItemDurNum error");

				-- Check merging and splitting

				-- First split (including stacking)
				ret = user:SplitItem(conSlot, 1, conSlot, 0, 1);
				check(ret, "failed to send split item msg");

				--Check the split-item response
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

				-- Then move
				ret = user:MoveItem(conSlot, 1, conSlot, 2);
				check(ret, "failed to send move item msg");

				--Check the move-item response
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

				-- Finally merge
				ret = user:MoveItem(conSlot, 2, conSlot, 0);
				check(ret, "failed to send move item msg");
				--Check the stack-item response
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

				-- Clean up
				ret = user:DeleteItem(conSlot, 0, item.m_iteminfo.m_shCurDur);
				check(ret, "failed to send delete item msg");

				--Check the remove-item response
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 0,"failed to delete correct item");
			else	-- No durability: usage count and equipment durability should both be non-stackable attributes
				--Add another identical item
				ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--Check that the added item came from the GM command
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				item2 = role:GetItemBag():GetItem(conSlot,1);
				check(item2, "failed to get item");
				check(item2.m_iteminfo.m_nTemplateID==item_data.m_nTemplateID,"failed to get correct item");

				--Remove the newly added item
				ret = user:DeleteItem(conSlot, 1, 1);
				check(ret, "failed to send delete item msg");

				--Check the remove-item response
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 1,"failed to delete correct item");

				--Remove the newly added item
				ret = user:DeleteItem(conSlot, 0, 1);
				check(ret, "failed to send delete item msg");

				--Check the remove-item response
				msg = recv_msg(5, session_id, protocol.g2c_item_delete);
				check(msg, "failed to recv g2c_item_delete");
				check(msg.byConSlot == conSlot and msg.byItemSlot == 0,"failed to delete correct item");
			end
		end

        print("AddItem OK " .. item_data.m_nTemplateID);
        item_data = CDataManager_ITEM_DATA_:GetInstance():GetNextData();
    end

	--Log out
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();


	ret = user:GMCommand("AddItem(100002, 1)");
	check(ret, "failed to send gm command");

	--Check that the added item came from the GM command
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
	check(msg, "failed to recv g2c_item_change");

	item = role:GetItemBag():GetItem(2,0);
	check(item, "failed to get item");
	check(item.m_iteminfo.m_nTemplateID==100002,"failed to get correct item");
	role:GetItemBag():UseItem(2, 0, 100002);



	--Log out
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

    --Log in
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

	-- Clear the inventory
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
		-- Check the inventory slot

		if item_data.m_byType == 3 then -- Materials
			conSlot = 4;
		elseif item_data.m_byType == 9 then -- Quest
			conSlot = 5;
		else
			conSlot = 2;	-- Default inventory
		end

		if item_data.m_nTemplateID >100 then
			-- Usable item
			if item_data.m_byType == 1 then

				-- Select class
				if item_data.m_byRequireClass > 0 then
					user:GMCommand("SelfRole:SetClass("..((item_data.m_byRequireClass - 1)%4)..");");
				end

				print("UseItem Begin " .. item_data.m_nTemplateID);
				if item_data.m_nSpellID > 0 then
					ret = user:GMCommand("AddItem(" .. item_data.m_nTemplateID .. ", 1)");
					check(ret, "failed to send gm command");

					--Check that the added item came from the GM command
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
					-- If there is no skill, there must be a script
				elseif item_data.m_szScript == 0 then
					check(nil, "script:use item can not use");
					-- Currently allowed
				else
					check(nil, "use item can not use");
				end

			end
		end

		print("UseItem OK " .. item_data.m_nTemplateID);
        item_data = CDataManager_ITEM_DATA_:GetInstance():GetNextData();
	end

	--Log out
    cleanup(user);
end




-- Get the equipment slot by subtype
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
	local conSlot = 3;	-- Equipment: no choice of inventory

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	ret = user:GMCommand("EnableCD(false)");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("AddExp(2000000)");
	check(ret, "failed to send gm command");

	-- Clear the inventory
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
			-- Usable item
			if equip_data.m_byType == 2 then
				-- Select class
				if equip_data.m_byRequireClass == 4 then
					user:GMCommand("SelfRole:SetClass(2);");
				elseif equip_data.m_byRequireClass > 0 then
					user:GMCommand("SelfRole:SetClass("..((equip_data.m_byRequireClass - 1)%4)..");");
				end
				print("UseEquip Begin " .. equip_data.m_nTemplateID);

				ret = user:GMCommand("AddItem(" .. equip_data.m_nTemplateID .. ", 1)");
				check(ret, "failed to send gm command");

				--Check that the added item came from the GM command
				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");

				local dstItemSlot = GetEquipPos(equip_data.m_bySubType);
				--Stack items
				ret = user:MoveItem(3, 0, 0, dstItemSlot);
				check(ret, "failed to send move item msg");

				msg = recv_msg(5, session_id, protocol.g2c_item_swap);
				check(msg, "failed to recv g2c_item_swap");

				if dstItemSlot < 11 then
					msg = recv_msg(5, session_id, protocol.g2c_sync_role_avatar);
					check(msg, "failed to recv g2c_sync_role_avatar");
				end

				-- There may be unequipped items; remove previously unequipped items before continuing
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

	--Log out
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	--Add a test item using a GM command
    ret = user:GMCommand("AddItem(99, 1)");
    check(ret, "failed to send gm command");

    --Check the item response
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--Use
	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--Item use succeeds
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--Use again
	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--Item use fails
	msg = recv_msg(5, session_id, protocol.g2c_error_notify);
	check(msg, "failed to recv g2c_error_notify");
	check(msg.nErrCode == error_code.errItemNotReady, "failed to recv correct err msg");

	--Wait 35 seconds, then use again
	wait(35);

	ret = role:GetItemBag():UseItem(2, 0, 99);
	check(ret, "failed to use item");

	--Item use succeeds
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--Log out
    cleanup(user);
end

function TestCase.Item.NovicePackage()
	local user_name = "NP" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	session_id = user:GetSessionID();

	--Add a starter gift pack using a GM command
    ret = user:GMCommand("AddItem(1000011, 1)");
    check(ret, "failed to send gm command");

    --Check the item response
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--Use
	ret = role:GetItemBag():UseItem(2, 0, 1000011);
	check(ret, "failed to use item");

	--Item use succeeds
	msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

	--Log out
    cleanup(user);
end

function TestCase.Item.RoleLogoutDLSaveItem()
	local user_name = "DLItem" .. os.date("%Y%H%M%S");

	--Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

	--Add a test item using a GM command
    ret = user:GMCommand("AddItem(99, 1)");
    check(ret, "failed to send gm command");

    --Check the item response
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --Log out
    cleanup(user);

end

function TestCase.Item.TradeItem()
	local user_name1 = "TradeItem17" .. os.date("%Y%H%M%S");
	local user_name2 = "TradeItem18" .. os.date("%Y%H%M%S");

	--Log in
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

	--Add a test item using a GM command
    ret = user1:GMCommand("AddItem(101, 1)");
    check(ret, "failed to send gm command");

    --Check the item response
    msg = recv_msg(5, session_id1, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    performance_trade_with_role(user1, user2, 101);

    --Log out
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

	--user: request trade
    ret = user:AskTrade(targetrole:GetObjID());
    check(ret, "failed to ask trade");

    --targetuser: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: accept trade
    ret = targetuser:AcceptTrade(srcrole:GetObjID());
    check(ret, "failed to cancel trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user: offer 1,000
    ret = user:SetTradeMoney(1000);
    check(ret, "failed to set trade money");

    --targetuser: receive the user money offer notification
    msg = recv_msg(5, session_id2, protocol.g2c_trade_set_money);
    check(msg, "failed to recv g2c_trade_set_money");

    wait(2);

    --user: lock
    ret = user:LockTrade();
    check(ret, "failed to lock trade");

    --targetuser: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: lock
    ret = targetuser:LockTrade();
    check(ret, "failed to lock trade");

    --user: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user: confirm
    ret = user:ConfirmTrade();
    check(ret, "failed to lock trade");

    --targetuser: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --targetuser: confirm
    ret = targetuser:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    --targetuser: receive money
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

	--Log in
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

	-- Add money

	local ret = user1:GMCommand("AddMoney(1, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	ret = user2:GMCommand("AddMoney(1, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(5);

	-- Add soul

	ret = user1:GMCommand("AddMoney(5, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	ret = user2:GMCommand("AddMoney(5, 1000000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(5);

	-- Increase level

	local ret = user1:GMCommand("SetLevel(10)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

	local ret = user2:GMCommand("SetLevel(10)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

	-- Raise each character’s realm 10 times

	for changecount = 1, 10 do
	    ret = user1:ChangeSoul2Pts(true, true); --Online conversion
		check(ret, "fail to send changesoul2pts");

	    msg = recv_msg(100, session_id1, protocol.g2c_spirit_exp_change);
		check(msg, "failed to recv g2c_spirit_exp_change");

		wait(1);
	end

	for changecount = 1, 10 do
	    ret = user2:ChangeSoul2Pts(true, true); --Online conversion
		check(ret, "fail to send changesoul2pts");

	    msg = recv_msg(100, session_id2, protocol.g2c_spirit_exp_change);
		check(msg, "failed to recv g2c_spirit_exp_change");

		wait(1);
	end

	--user1: request trade
    ret = user1:AskTrade(role2:GetObjID());
    check(ret, "failed to ask trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: accept trade
    ret = user2:AcceptTrade(role1:GetObjID());
    check(ret, "failed to accept trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: offer 1,000
    ret = user1:SetTradeMoney(1000);
    check(ret, "failed to set trade money");

    --user2: receive user1 money offer notification
    msg = recv_msg(5, session_id2, protocol.g2c_trade_set_money);
    check(msg, "failed to recv g2c_trade_set_money");

    wait(2);

    --user1: lock
    ret = user1:LockTrade();
    check(ret, "failed to lock trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: lock
    ret = user2:LockTrade();
    check(ret, "failed to lock trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: confirm
    ret = user1:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: confirm
    ret = user2:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    --targetuser: receive money

    msg = recv_msg(5, session_id2, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_money_change");

	cleanup(user1);
	cleanup(user2);
end
