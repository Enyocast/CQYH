LoadPackage("gameworld.pkg");
LoadPackage("role.pkg");
LoadPackage("achievement_def.pkg");
LoadPackage("spell.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("achievement_list.pkg");

function TestCase.Achievement()

    -- Log in
    local user_name1 = "achievement1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

	local user_name2 = "achievement2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");

	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user1sessionid = user1:GetSessionID();
	local user2sessionid = user2:GetSessionID();

	-- Achievement 1: reach level 2, obtain item 104, and carry more than 1,000 gold
	-- Achievement 2: enter scene 102, complete quest 102, and abandon more than 10 quests

	-- User1

	local ret = user1:CompleteAchievement(1);
	check(ret, "failed to send complete achievement");

	msg = recv_msg(10, user1sessionid, protocol.g2c_error_notify);
	check(msg, "failed to receive complete achievement error notify");

	-- select reward
	local ret = user1:GetAchievementReward(1);
	check(ret, "failed to send complete achievement");

	msg = recv_msg(10, user1sessionid, protocol.g2c_error_notify);
	check(msg, "failed to receive reward achievement error notify");

	-- fulfill condition
	ret = user1:GMCommand("AddExp(530000)");
	check(ret, "failed to add exp");
	wait(1);

	ret = user1:GMCommand("SetMoney(1, 1000)");
	check(ret, "failed to add money");
	wait(1);

	ret = user1:GMCommand("AddItem(104, 1)");
	check(ret, "failed to add item");
	wait(1);

	local ret = user1:CompleteAchievement(1);
	check(ret, "failed to send complete achievement");

	msg = recv_msg(10, user1sessionid, protocol.g2c_complete_achievement);
	check(msg, "failed to receive complete achievement");

	-- select reward
	local ret = user1:GetAchievementReward(1);
	check(ret, "failed to send complete achievement");

	print("-----------1-------------");

	msg = recv_msg_and(10, user1sessionid, protocol.g2c_add_title, user1sessionid, protocol.g2c_item_change);
	check(msg, "failed to receive achievement reward");

	print("---------2---------------");

	-- User2

	--local ret = user2:CompleteAchievement(2);
	--check(ret, "failed to send complete achievement");

	--msg = recv_msg(10, user2sessionid, protocol.g2c_error_notify);
	--check(msg, "failed to receive complete achievement error notify");

	-- fulfill condition

	--JumpToSceneBySceneTempID(user2, 102, 0);
	--wait(5);

	--ret = user2:GMCommand("CompleteQuest(102)");
	--check(ret, "failed to complete quest");
	-- wait(5);

	--ret = user2:GMCommand("SelfRole:SetVariable("..	ervtAbandonQuestCount..", 10);");
	--check(ret, "failed to add item");
	--wait(5);

	--local ret = user2:CompleteAchievement(2);
	--check(ret, "failed to send complete achievement");

	--msg = recv_msg(10, user2sessionid, protocol.g2c_complete_achievement);
	--check(msg, "failed to receive complete achievement")
end

function _achievement(achievement_data)

	print("-------------start to _achievement----------");

	-- Log in
    local user_name = "achieve1"..achievement_data["nAchievementID"]..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	local session_id = user:GetSessionID();
	local ret = 0;
	local msg;

	for i = 1, MAX_CON_PER_ACHIEVEMENT do
		print("--- i = "..i.."----");
		ret = complete_achievem(user, role, achievement_data.vecAchievementType[i-1], achievement_data.vecAchievementValue1[i-1], achievement_data.vecAchievementValue2[i-1], achievement_data.vecAchievementValue3[i-1]);
		check(ret, "complete_achievem fail");
		wait(5);
	end

	if achievement_data["nPreAchievementID1"] ~= -1 then
		ret = user:GMCommand("CompleteAchievement("..achievement_data["nAchievementID1"]..", "..g_oGameWorld:GetGameTime()..")");
		check(ret, "PreAchievementID1 fail");
	end

	if achievement_data["nPreAchievementID2"] ~= -1 then
		ret = user:GMCommand("CompleteAchievement("..achievement_data["nAchievementID2"]..", "..g_oGameWorld:GetGameTime()..")");
		check(ret, "PreAchievementID2 fail");
	end

	-- Accept quest
	ret = user:CompleteAchievement(achievement_data["nAchievementID"]);
	check(ret, "CompleteAchievement : "..achievement_data["nAchievementID"].. "fail");

    msg = recv_msg(15, session_id, protocol.g2c_complete_achievement);
    check(msg, "failed to recv g2c_complete_achievement");

	print("------achievement: "..achievement_data["nAchievementID"].." completed!!-------")

	g_AchievementList[achievement_data["nAchievementID"]].status = true;
end

function complete_achievem(user1, role1, Type, value1, value2, value3)

	print("--start to complete achievement with type: "..Type.." and value1: "..value1.."---");

	local ret = 0;
	local msg;
	local user1sessionid = user1:GetSessionID();

	if Type == adVariable then
		ret = complete_variable(user1, role1, Type, value1, value2, value3);
		check(ret, "fail to adVariable");
	elseif Type == adLevel or Type == adExperience then
		print("-----adLevel or adExperience--------");
		ret = user1:GMCommand("AddExp(630000)");
		check(ret, "fail to adLevel");

		msg = recv_msg(10, user1sessionid, protocol.g2c_exp_change);
		check(msg, "failed to receive g2c_exp_change in type: adLevel");
		ret = user1:GMCommand("AddExp(530000)");
		check(ret, "fail to adExperience");

		msg = recv_msg(10, user1sessionid, protocol.g2c_exp_change);
		check(msg, "failed to receive g2c_exp_change in type: adExperience");
	elseif Type == adPkValue then
		print("-----adpkvalue--------");
		ret = user1:GMCommand("SetPkValue(530000)");
		check(ret, "fail to adPkValue");
	elseif Type == adForceReputation then
		print("-----adForceReputation--------");
		ret = user1:GMCommand("SetReputation(" ..value1..",".. value2..")");
		check(ret, "fail to adForceReputation");
	elseif Type == adVariousForceCount then
		for i = 1, value1 do
			ret = user1:GMCommand("SetReputation("..(i-1)..", 10)");
			check(ret, "fail to adVariousForceCount");
		end
	elseif Type == adEquip then
		print("-----adEquip--------");
		ret = user1:GMCommand("AddItem("..value1..", 1)");
		check(ret, "fail to adEquip")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");
	elseif Type == adEquipColor then	-- 30004 Refined Shadow Warrior Belt, color 3
		print("-----adEquipColor--------");
		ret = user1:GMCommand("AddItem(30004, 1)");
		check(ret, "fail to adEquip")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");
	elseif Type == adEquipBodyColor then -- 30004 Refined Shadow Warrior Belt, color 3
		print("-----adEquipBodyColor--------");
		ret = user1:GMCommand("AddItem(30004, 1)");
		check(ret, "fail to adEquip")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");

		ret = user1:MoveItem(0,0,0, 7); -- Equip in the waist slot
		check(ret, "fail to add move item")

	elseif Type == adBankSlotCount then
		local remaincount = value2 - 16;  -- BANK_CONTAINER_SIZE = 16
		while (remaincount > 0) do
			ret = user1:GMCommand("SelfRole:GetItemBag().BuySlots(CONSLOT_BANK)");
			check(ret, "fail to adBankSlotCount");

			msg = recv_msg(10, user1sessionid, protocol.g2c_container_size_change);
			check(msg, "failed to receive g2c_container_size_change in type: adBankSlotCount");

			remaincount = remaincount - 1;
		end
	elseif Type == adItemBagSlotCount	then
		local remaincount = value2 - 30;  -- DEFAULT_CONTAINER_SIZE = 30
		while (remaincount > 0) do
			ret = user1:GMCommand("SelfRole:GetItemBag().BuySlots(CONSLOT_DEFAULT)");
			check(ret, "fail to adItemBagSlotCount");

			msg = recv_msg(10, user1sessionid, protocol.g2c_container_size_change);
			check(msg, "failed to receive g2c_container_size_change in type: adItemBagSlotCount");

			remaincount = remaincount - 1;
		end
	elseif Type == adTotalMoneyType_01 then
		ret = user1:GMCommand("AddMoney("..MONEYTYPE_01..",".. value1..", MONEYLOG_GM_COMMAND)");
		check(ret, "fail to adTotalMoneyType_01");

		msg = recv_msg(10, user1sessionid, protocol.g2c_money_change);
		check(msg, "failed to receive g2c_money_change in type: adTotalMoneyType_01");
	elseif Type == adTotalMoneyType_03 then
		ret = user1:GMCommand("AddMoney("..MONEYTYPE_03..",".. value1..", MONEYLOG_INVALID)");
		check(ret, "fail to adTotalMoneyType_03");

		msg = recv_msg(10, user1sessionid, protocol.g2c_money_change);
		check(msg, "failed to receive g2c_money_change in type: adTotalMoneyType_03");
	elseif Type == adTotalMoneyType_04 then
		ret = user1:GMCommand("AddMoney("..MONEYTYPE_04..",".. value1..", MONEYLOG_INVALID)");
		check(ret, "fail to adTotalMoneyType_04");

		msg = recv_msg(10, user1sessionid, protocol.g2c_money_change);
		check(msg, "failed to receive g2c_money_change in type: adTotalMoneyType_04");
	elseif Type == adKillPlayerTotalCount then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user2:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user1:CastSpell(0, role2:GetObjID(), role2:GetX(), role2:GetY(), role2:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user2sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user2:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sess2onid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtKillWarriorCount");
			wait(5);
		end
	elseif Type == adEnterScene then
		JumpToSceneBySceneTempID(user1, value1, 0);
	elseif Type == adCompleteQuest then
		local quest_data = GetQuestByID(value1);
		check(quest_data, "fail to get quest_data");

		_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
		wait(10);

		_CompleteQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime);
	elseif Type == adCompleteQuestCount then
		-- Traverse all quests
		local completecount = 0;

		local quest_data = CDataManager_Quest_DATA_:GetInstance():GetFirstData();
		while(quest_data and completecount < value2) do
				_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
				wait(10);

				_CompleteQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime);
				wait(5);

				quest_data = CDataManager_Quest_DATA_:GetInstance():GetNextData();
				completecount = completecount + 1;
		end

		check(completecount >= value2, "fail to complete adCompleteQuestCount with Type: Variable");
	elseif Type == adSpellLevel then
		ret = user1:GMCommand("LearnSpell("..value1..",".. value2..")");
		check(ret, "fail to adTotalMoneyType_03");

		msg = recv_msg(10, user1sessionid, protocol.g2c_role_learn_spell);
		check(msg, "failed to receive g2c_role_learn_spell in type: adSpellLevel");
	elseif Type == adLearnSpell then
		ret = user:GMCommand("LearnSpell("..value1..", 1)");
		check(ret, "fail to adTotalMoneyType_03");

		msg = recv_msg(10, user1sessionid, protocol.g2c_role_learn_spell);
		check(msg, "failed to receive g2c_role_learn_spell in type: adLearnSpell");
	elseif Type == adSpellCount then
		local remaincout = value1 - 8;	-- Remaining spell count
		local spell_data = CDataManager_SPELL_ENTRY_:GetInstance():GetFirstData();

		while (spell_data and spell_data.m_nAttrTable["satClass"] and remaincount > 0) do
			if (role.GetSpellBook().GetSpell(spell_data.m_nID) == nil) then
				ret = user:GMCommand("LearnSpell("..spell_data.m_nID..", 1)");
				check(ret, "fail to adSpellCount");

				msg = recv_msg(10, user1sessionid, protocol.g2c_role_learn_spell);
				check(msg, "failed to receive g2c_role_learn_spell in type: adSpellCount");

				remaincount = remaincount - 1;
			end

			spell_data = CDataManager_SPELL_VAR_:GetInstance():GetNextData();
		end

		check(remaincount == 0, "fail to adSpellCount");
	elseif Type == adRuneCount then

	elseif Type == adEquipPassiveSpellIDCount then
		local spell = CSpellConfig:GetInstance().FindSpellTemplate(value1, 1, 0);
		check(spell, "fail to get spell with type: adEquipPassiveSpellIDCount");
		check(spell.GetAttr(satCastType) == spctPassive, "fail to check passive spell type");

		if (role.GetSpellBook().GetSpell(spell_data.m_nID) == nil) then
			ret = user:GMCommand("LearnSpell("..value1..", 1)");
			check(ret, "fail to adEquipPassiveSpellIDCount");

			msg = recv_msg(10, user1sessionid, protocol.g2c_role_learn_spell);
			check(msg, "failed to receive g2c_role_learn_spell in type: adSpellCount");
		end
	elseif Type == adEquipPassiveSpellCount then
		local remaincount = value1;
		local spell_data = CDataManager_SPELL_ENTRY_:GetInstance():GetFirstData();

		while (spell_data and spell_data.m_nAttrTable["satClass"] == clsWarrior and remaincount > 0) do

			local spell = CSpellConfig:GetInstance().FindSpellTemplate(spell_data.m_nID, 1, 0);
			if ((spell.GetAttr(satCastType) == spctPassive) and role.GetSpellBook().GetSpell(spell_data.m_nID) == nil) then
				ret = user:GMCommand("LearnSpell("..spell_data.m_nID..", 1)");
				check(ret, "fail to adSpellCount");

				msg = recv_msg(10, user1sessionid, protocol.g2c_role_learn_spell);
				check(msg, "failed to receive g2c_role_learn_spell in type: adSpellCount");

				remaincount = remaincount - 1;
			end

			spell_data = CDataManager_SPELL_VAR_:GetInstance():GetNextData();
		end

		check(remaincount == 0, "fail to adEquipPassiveSpellCount");
	elseif Type == adTitle then
		ret = user:GMCommand("AddTitle("..value1..")");
		check(ret, "fail to adTitle");

		msg = recv_msg(10, user1sessionid, protocol.g2c_add_title);
		check(msg, "failed to receive g2c_add_title in type: adTitle");
	elseif Type == adTitleCount then
		local title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetFirstData();

		for i = 1, value1 do
			if title_data then
				ret = user:GMCommand("AddTitle("..title_data.m_nTemplateID..")");
				check(ret, "fail to adTitleCount");

				msg = recv_msg(10, user1sessionid, protocol.g2c_add_title);
				check(msg, "failed to receive g2c_add_title in type: adTitleCount");
			else
				check(false, "fail to add title, type: ");
			end

			title_data = CDataManager_TITLE_TEMPLATE_:GetInstance():GetNextData();
		end
	elseif Type == adFriendCount then
		local friendcount = 0;
		while (friendcount < value1) do
			local user_name2 = "adFriend"..friendcount..os.date("%H%M%S");
			local user2, role2 = startup(user_name2, user_name2);
			check(user2, "failed to create user");
			check(role2, "failed to create role");

			--user1: add user2 as a friend by RoleID
			ret = user1:AddFriend(role2:GetObjID(), "");
			check(ret, "failed to add friend");

			--user1: receive the add-friend response
			msg = recv_msg(5, session_id1, protocol.m2c_friend_add);
			check(msg, "faield to recv m2c_friend_add");
			check(msg.dwRoleID == role2:GetObjID(), "failed to recv correct friend add msg");
			check(msg.szRoleName == user_name2, "failed to recv correct friend add msg");
		end
	elseif Type == adLeaveStudentCount then

	elseif Type == adLeaveMaster then

	elseif Type == adGetItem then
		ret = user:GMCommand("AddItem("..value1..", 1)");
		check(ret, "fail to adGetItem")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adGetItem");
	elseif Type == adAchievement then
		ret = user:GMCommand("CompleteAchievement("..value1..","..g_oGameWorld:GetGameTime()..")");
		check(ret, "fail to adAchievement")

		msg = recv_msg(10, user1sessionid, protocol.g2c_complete_achievement);
		check(msg, "failed to receive g2c_complete_achievement in type: adAchievement");
	elseif Type == adAchievementCount	then
		local achievement_data = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetFirstData();

		for i = 1, value1 do
			if achievement_data then
				ret = user:GMCommand("CompleteAchievement("..achievement_data.nAchievementID..","..g_oGameWorld:GetGameTime()..")");
				check(ret, "fail to adAchievementCount")

				msg = recv_msg(10, user1sessionid, protocol.g2c_complete_achievement);
				check(msg, "failed to receive g2c_complete_achievement in type: adAchievementCount");
			else
				check(false, "fail to add AchievementCount");
			end

			title_data = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetNextData();
		end
	elseif Type == adCreateTime then

	else

	end

	wait(10);

	print("--successfullycomplete achievement with type: "..Type.." and value1: "..value1.."---");
	return 1;
end

function complete_variable(user, role, Type, value1, value2, value3)
	local i;
	local ret;
	local user1sessionid = user:GetSessionID();

	check(Type == adVariable, "fail to complete_variable, type wrong");

	if (value1 == ervtDestoryItemCount) then
		for i = 1, value2 do
			ret = user:GMCommand("AddItem(111, 1)");
			check(ret, "failed to send gm command");

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: adVariable and var: ervtDestoryItemCount");
			wait(5);

			ret = role:GetItemBag().DeleteItem(0, 0, 1);
			check(ret, "failed to delete item");

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_delete);
			check(msg, "failed to receive g2c_item_delete in type: adVariable and var: ervtDestoryItemCount");
			wait(5);
		end
	elseif (value1 == ervtPickMoneyTotal) then
		local cmd = "local oNpc = SummonNpc(101); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";
		local totalpick = 0;

		while (totalpic < value2) do
			ret = user:GMCommand(cmd);		-- Warrior: Barbaric Charge
			wait(3);

			msg = recv_msg(10, user1sessionid, protocol.g2c_pickup_money);
			check(msg, "failed to receive g2c_pickup_money in type: adVariable and var: ervtPickMoneyTotal");
			wait(5);

			totalpick = totalpick + msg.count;
		end
	elseif (value1 == ervtQuestMoneyTotal) then
		local quest_data = GetQuestByID(10);
		check(quest_data, "fail to get quest_data");

		_AcceptQuestWithoutConditionIndex(user, role, quest_data, 0, nTime, qatNpc, 0);
		wait(10);

		_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
	elseif (value1 == ervtSaleMoneyTotal) then
		ret = user:GMCommand("AddItem( 101, 1)");
		check(ret, "fail to ervtSaleMoneyTotal")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");

		ret = user:SellItem(0, 0);
		check(ret, "fail to sell item");

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_delete);
		check(msg, "failed to receive g2c_item_delete in type: ervtSaleMoneyTotal");
	elseif (value1 == ervtRelieveMoneyTotal) then
		local totalcost = 0;

		ret = user:GMCommand("AddMoney("..MONEYTYPE_01..", 10000000, MONEYLOG_GM_COMMAND)");	-- Add money
		check(ret, "fail to adTotalMoneyType_01");

		msg = recv_msg(10, user1sessionid, protocol.g2c_money_change);
		check(msg, "failed to receive g2c_money_change in type: adTotalMoneyType_01");

		while (totalcost < value2) do
			for i = 1, 10 do
				--Spawn an NPC using a GM command
				ret = user:GMCommand("SummonNpc(109)");
				check(ret, "failed to send gm command");

				--Check the spawned NPC
				msg = recv_msg(5, session_id, protocol.g2c_char_appear)
				check(msg, "Npc appear fail.")
			end

			msg = nil;
			while (msg == nil) do
				ret = user1:GMCommand("SetHp(1)");
				check(ret, "failed to send command SetHp");

				msg = recv_msg(10, user1sessionid, protocol.g2c_char_die);
				wait(5);
			end

			ret = user:CastSpell(8001, role:GetObjID(), role:GetX(), role:GetY(), role:GetZ());	-- Assume the skill ID for gold-funded resurrection is 8001
			check(ret, "failed to cast spell with type: ervtRelieveMoneyTotal");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtRelieveMoneyTotal");
			wait(5);
		end
	elseif (value1 == ervtRepairMoneyTotal) then	-- Assume equipment ID 102 is a weapon, since the main-hand item is removed. This is not fully implemented; the server does not yet deduct repair money.
		ret = user:GMCommand("AddItem(102, 1)");
		check(ret, "fail to adEquip")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");

		--Spawn an NPC using a GM command
		ret = user:GMCommand("SummonNpc(6003)");	-- Assume the repair NPC ID is 6003
		check(ret, "failed to send gm command");

		--Check the spawned NPC
		msg = recv_msg(5, session_id, protocol.g2c_char_appear)
		check(msg, "Npc appear fail.")
		local diag_npc_id = msg.stAppearData.dwCharID
		check(diag_npc_id ~= 0, "Npc appear fail.")

		--Select the NPC
		ret = user:InteractWithNpc(diag_npc_id);
		check(ret, "failed to interact with npc");

		local maxcost = 0;

		while (maxcost < value2) do
			ret = user:GMCommand("LoseAllDur(80)");
			check(ret, "fail to adEquip");

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: ervtRepairMoneyMax");

			ret = user1:GetItemBag().MoveItem(CONSLOT_EQUIPPED, NES_MAIN_HAND, CONSLOT_EQUIPMENT, 0);
			check(ret, "fail to move item");

			msg = recv_msg(10, user1sessionid, protocol.g2c_sync_role_avatar);
			check(msg, "failed to receive g2c_sync_role_avatar in type: ervtRepairMoneyMax");

			ret = user:GMCommand("RepairItem(CONSLOT_EQUIPMENT, 0)");
			check(ret, "fail to RepairItem");

			wait(5);
		end
	elseif (value1 == ervtRepairMoneyMax) then	-- Assume equipment ID 102 is a weapon, since the main-hand item is removed; the server does not yet deduct repair money.
		ret = user:GMCommand("AddItem(102, 1)");
		check(ret, "fail to adEquip")

		msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
		check(msg, "failed to receive g2c_item_change in type: adEquip");

		--Spawn an NPC using a GM command
		ret = user:GMCommand("SummonNpc(6003)");	-- Assume the repair NPC ID is 6003
		check(ret, "failed to send gm command");

		--Check the spawned NPC
		msg = recv_msg(5, session_id, protocol.g2c_char_appear)
		check(msg, "Npc appear fail.")
		local diag_npc_id = msg.stAppearData.dwCharID
		check(diag_npc_id ~= 0, "Npc appear fail.")

		--Select the NPC
		ret = user:InteractWithNpc(diag_npc_id);
		check(ret, "failed to interact with npc");

		local maxcost = 0;

		while (maxcost < value2) do
			ret = user:GMCommand("LoseAllDur(80)");
			check(ret, "fail to adEquip");

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: ervtRepairMoneyMax");

			ret = user1:GetItemBag().MoveItem(CONSLOT_EQUIPPED, NES_MAIN_HAND, CONSLOT_EQUIPMENT, 0);
			check(ret, "fail to move item");

			msg = recv_msg(10, user1sessionid, protocol.g2c_sync_role_avatar);
			check(msg, "failed to receive g2c_sync_role_avatar in type: ervtRepairMoneyMax");

			ret = user:GMCommand("RepairItem(CONSLOT_EQUIPMENT, 0)");
			check(ret, "fail to RepairItem");

			wait(5);
		end
	elseif (value1 == ervtSelfDieCount) then
		for i = 1, value1 do
			ret = user1:GMCommand("SetHp(0)");
			check(ret, "failed to send command SetHp");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtSelfDieCount");
			wait(5);

			ret = user1:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtSelfDieCount");
			wait(5);
		end
	elseif (value1 == ervtPVPKilledByPlayer) then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user1:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user2:CastSpell(0, role:GetObjID(), role:GetX(), role:GetY(), role:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user1:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtSelfDieCount");
			wait(5);
		end
	elseif (value1 == ervtPVPKilledByMonster) then
	    user:GMCommand("SummonNpc(109)");
		check(ret, "failed to send command SetHp");
		msg = recv_msg(5, user1sessionid, protocol.g2c_char_appear);
		check(msg, "failed to summon npc");

		for i = 1, value1 do
			ret = user1:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByMonster");
			wait(5);

			ret = user1:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtPVPKilledByMonster");
			wait(5);
		end
	elseif (value1 == ervtKilledByMonsterID101) then
		for i = 1, 10 do
			user1:GMCommand("SummonNpc(101)");
			msg = recv_msg(5, session_id, protocol.g2c_char_appear);
			check(msg, "failed to summon npc");
		end

		for i = 1, value2 do
			ret = user1:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			msg = recv_msg(20, user1sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtKilledByMonsterID101");
			wait(5);

			ret = user1:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sessionid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtPVPKilledByMonster");
		end
	elseif (value1 == ervtKillMonsterID101) then
		local cmd = "local oNpc = SummonNpc(101); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";

		for i = 1, value2 do
		    ret = user:GMCommand(cmd);		-- Warrior: Barbaric Charge
			wait(3);
		end
	elseif (value1 == ervtKillMonsterCount) then
		local cmd = "local oNpc = SummonNpc(101); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";

		for i = 1, value2 do
		    ret = user:GMCommand(cmd);		-- Warrior: Barbaric Charge
			wait(3);
		end
	elseif (value1 == ervtKillWarriorCount) then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user2:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user1:CastSpell(0, role2:GetObjID(), role2:GetX(), role2:GetY(), role2:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user2sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user2:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sess2onid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtKillWarriorCount");
			wait(5);
		end
	elseif (value1 == ervtKillMageCount) then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2, nil, clsMage);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user2:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user1:CastSpell(0, role2:GetObjID(), role2:GetX(), role2:GetY(), role2:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user2sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user2:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sess2onid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtKillWarriorCount");
			wait(5);
		end
	elseif (value1 == ervtKillRogueCount) then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2, nil, clsRogue);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user2:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user1:CastSpell(0, role2:GetObjID(), role2:GetX(), role2:GetY(), role2:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user2sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user2:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sess2onid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtKillWarriorCount");
			wait(5);
		end
	elseif (value1 == ervtKillArcherCount) then
		-- Log in
		local user_name2 = "achievement2"..os.date("%H%M%S");
		local user2, role2 = startup(user_name2, user_name2, nil, clsArcher);
		check(user2, "failed to create user");
		check(role2, "failed to create role");

		for i = 1, value1 do
			ret = user2:GMCommand("SetHp(1)");
			check(ret, "failed to send command SetHp");

			ret = user1:CastSpell(0, role2:GetObjID(), role2:GetX(), role2:GetY(), role2:GetZ());
			check(ret, "failed to cast spell");

			msg = recv_msg(10, user2sessionid, protocol.g2c_char_die);
			check(msg, "failed to receive g2c_char_die in type: ervtPVPKilledByPlayer");
			wait(5);

			ret = user2:GMCommand("Revive()");
			check(ret, "failed to send command Revive");

			msg = recv_msg(10, user1sess2onid, protocol.g2c_char_revive);
			check(msg, "failed to receive g2c_char_revive in type: ervtKillWarriorCount");
			wait(5);
		end
	elseif (value1 == ervtKillPkValuePlayerCount) then

	elseif (value1 == ervtEnterDungeonSceneCount) then
		for i = 1, value2 do
			JumpToSceneBySceneTempID(user, 102, 0);
			wait(5);

		    JumpToStartMap(user);
		end
	elseif (value1 == ervtCompleteMainQuestCount) then
		-- Traverse all quests
		local i = 0;

		local quest_data = CDataManager_Quest_DATA_:GetInstance():GetFirstData();
		while(quest_data and quest_data.nQuestType == qtBranch) do
			if (i < value2) then
				_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
				wait(10);

				_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
				wait(5);

				quest_data = CDataManager_Quest_DATA_:GetInstance():GetNextData();
				i = i + 1;
			end
		end

		check(i >= value2, "fail to complete ervtCompleteMainQuestCount with Type: Variable");
	elseif (value1 == ervtCompleteSubQuestCount) then
		-- Traverse all quests
		local i = 0;

		local quest_data = CDataManager_Quest_DATA_:GetInstance():GetFirstData();
		while(quest_data and quest_data.nQuestType == qtBranch) do
			if (i < value2) then
				_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
				wait(10);

				_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
				wait(5);

				quest_data = CDataManager_Quest_DATA_:GetInstance():GetNextData();
				i = i + 1;
			end
		end

		check(i >= value2, "fail to complete ervtCompleteSubQuestCount with Type: Variable");
	elseif (value1 == ervtCompleteHiddenQuestCount) then
		-- Traverse all quests
		local i = 0;

		local quest_data = CDataManager_Quest_DATA_:GetInstance():GetFirstData();
		while(quest_data and quest_data.nQuestType == qtHidden) do
			if (i < value2) then
				_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
				wait(10);

				_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
				wait(5);

				quest_data = CDataManager_Quest_DATA_:GetInstance():GetNextData();
				i = i + 1;
			end
		end

		check(i >= value2, "fail to complete ervtCompleteHiddenQuestCount with Type: Variable");
	elseif (value1 == ervtCompleteDailyQuestCount) then
		-- Traverse all quests
		local i = 0;

		local quest_data = CDataManager_Quest_DATA_:GetInstance():GetFirstData();
		while(quest_data and quest_data.nQuestType == qtDaily) do
			if (i < value2) then
				_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
				wait(10);

				_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
				wait(5);

				quest_data = CDataManager_Quest_DATA_:GetInstance():GetNextData();
				i = i + 1;
			end
		end

		check(i >= value2, "fail to complete ervtCompleteDailyQuestCount with Type: Variable");
	elseif (value1 == ervtAbandonQuestCount) then
		local quest_data = GetQuestByID(10);
		check(quest_data, "fail to get quest_data");

		_AcceptQuestWithoutConditionIndex(user1, role1, quest_data, 0, nTime, qatNpc, 0);
		wait(10);

		_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);

		ret = user1:AbandonQuest(10);
		check(ret, "fail to Abandon Quest");

		msg = recv_msg(10, user1sess2onid, protocol.g2c_abandon_quest);
		check(msg, "failed to receive g2c_abandon_quest in type: ervtAbandonQuestCount");
		wait(5);
	elseif (value1 == ervtMaxHPHit) then
		local cmd = "local oNpc = SummonNpc(109); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";
		local maxvalue = 0;

		while(maxvalue < value2) do
			ret = user:GMCommand(cmd);
			check(ret, "fail to ervtMaxHPHit");
			wait(5);

			msg = recv_msg(10, user1sess2onid, protocol.g2c_update_variable);
			if (msg and msg.wIndex == ervtMaxHPHit and maxvalue < msg.nValue) then
				maxvalue = msg.nvalue;
			end
		end
	elseif (value1 == ervtMaxHPBeHit) then
		for i = 1, 10 do
			--Spawn an NPC using a GM command
			ret = user:GMCommand("SummonNpc(109)");
			check(ret, "failed to send gm command");

			--Check the spawned NPC
			msg = recv_msg(5, session_id, protocol.g2c_char_appear)
			check(msg, "Npc appear fail.")
			local diag_npc_id = msg.stAppearData.dwCharID
		end

		local maxvalue = 0;

		while(maxvalue < value2) do
			ret = user:GMCommand(cmd);
			check(ret, "fail to ervtMaxHPHit");
			wait(5);

			msg = recv_msg(10, user1sess2onid, protocol.g2c_update_variable);
			if (msg and msg.wIndex == ervtMaxHPHit and maxvalue < msg.nValue) then
				maxvalue = msg.nvalue;
			end
		end
	elseif (value1 == ervtUseChaseSpellCount) then -- Assume the pursuit skill ID is 102
		local cmd = "local oNpc = SummonNpc(109); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";

		for i = 1, value2 do
			ret = user:GMCommand(cmd);
			check(ret, "fail to adEquip");
			wait(5);
		end
	elseif (value1 == ervtUseCounterSpellCount) then	-- Assume the counterattack skill ID is 102
		local cmd = "local oNpc = SummonNpc(109); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";

		for i = 1, value2 do
			ret = user:GMCommand(cmd);
			check(ret, "fail to adEquip");
			wait(5);
		end
	elseif (value1 == ervtUseTerminateSpellCount) then	-- Assume the finishing skill ID is 102
		local cmd = "local oNpc = SummonNpc(109); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";

		for i = 1, value2 do
			ret = user:GMCommand(cmd);
			check(ret, "fail to adEquip");
			wait(5);
		end
	elseif (value1 == ervtUseItemCount_Useable) then	-- Assume the consumable item ID is 102
		for i = 1, value2 do
			ret = user:GMCommand("AddItem(102, 1)");
			check(ret, "fail to adEquip")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: adEquip");

			ret = user:GetItemBag().UseItem(0,0, 102);
			check(ret, "fail to ervtUseItem101Count")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_delete);
			check(msg, "failed to receive g2c_item_delete in type:ervtUseItem101CountadEquip");
		end
	elseif (value1 == ervtUseItemCount_SpellBoke) then	-- Assume the consumable item ID is 102
		for i = 1, value2 do
			ret = user:GMCommand("AddItem(103, 1)");
			check(ret, "fail to adEquip")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: adEquip");

			ret = user:GetItemBag().UseItem(0,0, 103);
			check(ret, "fail to ervtUseItem101Count")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_delete);
			check(msg, "failed to receive g2c_item_delete in type:ervtUseItem101CountadEquip");
		end
	elseif (value1 == ervtUseItem101Count) then
		for i = 1, value2 do
			ret = user:GMCommand("AddItem(101, 1)");
			check(ret, "fail to adEquip")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_change);
			check(msg, "failed to receive g2c_item_change in type: adEquip");

			ret = user:GetItemBag().UseItem(0,0, 101);
			check(ret, "fail to ervtUseItem101Count")

			msg = recv_msg(10, user1sessionid, protocol.g2c_item_delete);
			check(msg, "failed to receive g2c_item_delete in type:ervtUseItem101CountadEquip");
		end
	elseif (value1 == ervtOnlineTime) then

	else
		check(false, "error type : "..value1.." in type: adVariable");
		return 0;
	end

	wait(5);
	return 1;
end


function TraverseAllAchievements()
	addco("TraversAchievement1", _TraverseAchievements);
end

function _TraverseAchievements()
	g_AchievementList = {};
	local runflag = true;

	-- Traverse all achievements
	local achievement_data = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetFirstData();
	while(achievement_data ~= nil) do

		g_AchievementList[achievement_data["nAchievementID"]] = {};
		g_AchievementList[achievement_data["nAchievementID"]].status = false;

		if achievement_data["nAchievementID"] ~= 0 then
			addco("achieve"..achievement_data["nAchievementID"], _achievement, achievement_data);
		end

		achievement_data = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetNextData();
	end

	while runflag do

		runflag  = false;
		local achievement_data1 = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetFirstData();

		while (achievement_data1 ~= nil) do
			if g_AchievementList[achievement_data1["nAchievementID"]].status == false then
				runflag = true;
				achievement_data1 = CDataManager_ACHIEVEMENT_DATA_:GetInstance():GetNextData();
			end
		end

		print("---come here6---");
		wait(5);
	end

	print("All Achievements traversed");
end
















