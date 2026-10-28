LoadPackage("npc.pkg")

function goto_shop_npc(user, owner)
	local scene = owner:GetScene();
	local scene_id = scene:GetSceneTempID();
	local shop_npc_list = g_shop_npc[scene_id];

	local npc_count = table.getn(shop_npc_list);
	if npc_count <= 0 then
		return nil;
	end

	local rand_index = math.random(1, npc_count);
	local npc_info = shop_npc_list[rand_index];

--	local npc = g_GameWorld:FindNpc(npc_id);

--	if npc ~= nil then
--		JumpToScene(user, owner, scene:GetSceneTempID(), scene_id, npc:GetX(), npc:GetY(), npc:GetZ());
--		user:InteractNpc(npc_id);
--	end

--	return npc;
end


function do_move_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:GMCommand("additem 101 10");
	user:MoveItem(CONSLOT_DEFAULT, 0, CONSLOT_DEFAULT, 1);
end

function do_split_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:GMCommand("additem 101 10");
	user:SplitItem(CONSLOT_DEFAULT, 0, CONSLOT_DEFAULT, 10, 2);
end

function do_delete_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
	local item_bag = role:GetItemBag();

	local item = item_bag:GetItem(CONSLOT_DEFAULT, 0);

	if item ~= nil then
		local item_count = item.m_iteminfo.m_nCurDur;

		if item_count >= 1 then
			user:DeleteItem(CONSLOT_DEFAULT, 0, item_count);
		end
	end
end

function do_pickup_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
end

function do_buy_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	goto_npc(user, 6683, 'callback_buy_item_action');
	-- interact with npc.
	--local npc = goto_shop_npc(user, role);

	--if npc == nil then
	--	return;
	--end

	--local npc_data = npc:GetNpcData();

	--user:BuyItem(npc_data.nShopID, 0, 1);

end

function callback_buy_item_action(npc)
	print('callback_buy_item_action: '.. npc:GetObjID());
end

function do_sell_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);
	user:SellItem(0, 0);
end

function do_use_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:UseItem(CONSLOT_DEFAULT, 0);
end

function do_view_sold_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);

	user:ViewSoldItem();
end

function do_buy_back_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);

	user:BuyBackItem(0);
end

function do_repair_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);
end

function do_repair_all_equipped_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);

	user:RepairAllEquippedItem();
end

function do_refine_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);
end

function do_buy_container_slot_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);

	user:BuyContainerSlot(CONSLOT_DEFAULT, 1);
end

function do_organize_bag_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:OrganizeBag(CONSLOT_DEFAULT);
end

function do_identify_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	do_delete_item_action(owner);

	user:GMCommand("additem 99991233");
	user:IdentifyItem(CONSLOT_DEFAULT, 0);
end

function do_randomize_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	do_identify_item_action(owner);

	user:RandomizeItem(CONSLOT_DEFAULT, 0);
end

function do_confirm_randomize_item_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:ConfirmRandomizeItem();
end

function do_use_moneytype01_only_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:UseMoneyType01Only(true);
	user:UseMoneyType01Only(false);
end

function do_check_npc_shop_data_action(owner)
    local role = Cast(owner, 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	-- interact with npc.
	goto_shop_npc(user, role);
end










