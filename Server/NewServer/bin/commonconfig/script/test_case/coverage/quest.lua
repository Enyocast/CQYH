

function CoverageTestCase.TraversAllQuests()
	addco("TraversAll", _TraversAllQuests);
end

function _TraversAllQuests()
    local ret;
    g_traversstatus = {};

    local questcountmeanwhile = 1; -- Number of quests run concurrently
    local nquestcount = 0;
	local runflag = true;
    g_queststatus = {};

	-- Traverse all quests
	local quest_data = CDataManager_QUEST_DATA_:GetInstance():GetFirstData();

	while(quest_data ~= nil) do
		print("**************quest_data.nQuestID = "..quest_data.nQuestID.."*********************");

		if quest_data.nQuestID ~= 0 then
			nquestcount = nquestcount + 1;
			addco("Travers"..quest_data.nQuestID, _TraversSingleQuest, quest_data, nquestcount);

			g_queststatus[nquestcount] = {};
			g_queststatus[nquestcount].status = false;
			g_queststatus[nquestcount].ID = quest_data.nQuestID;
		end

		if quest_data.nQuestID ~= 0 and nquestcount % questcountmeanwhile == 0 then
			while runflag do
				runflag = false;
				for i = (nquestcount- questcountmeanwhile + 1), nquestcount do
					if g_queststatus[i].status == false then
						runflag = true;
					end
				end

				wait(1);
			end
		end

		runflag = true;
		quest_data = CDataManager_QUEST_DATA_:GetInstance():GetNextData();
	end
end

function _TraversSingleQuest(quest_data, nindex)
	local ret;
	local user_name;
	local user;
	local role;
	local nQuestIndex;
	g_nQuestConfigCount = 0;

	-- Test when quest acceptance requirements are not met
	g_nQuestConfigCount = getquestacceptconfigcount(quest_data);
	check(g_nQuestConfigCount ~= 0, "fail to check quest_data");

	for nQuestIndex = 1,g_nQuestConfigCount do
		user_name = "Accept"..os.date("%H%M%S");
		_CompleteQuest(user_name, quest_data, nQuestIndex, 1, -1, -1);
	end

	g_nQuestConfigCount = getquestcompleteconfigcount(quest_data);

	print("=============configurenum = "..g_nQuestConfigCount.."=================================");

	-- Test when quest completion requirements are not met
	for nQuestIndex = 1, g_nQuestConfigCount do
		user_name = "Complete"..os.date("%H%M%S");
		_CompleteQuest(user_name, quest_data, 0, 1, nQuestIndex, 1); -- Create conditions for successful acceptance, then test completion
	end

	-- Test repeated completion of repeatable quests when acceptance and completion conditions are met (repeated acceptance of ordinary quests is tested in _AcceptConditionIndex)
	if quest_data.nQuestID >= REPEAT_QUEST_START_ID and quest_data.nQuestID <= (REPEAT_QUEST_START_ID + MAX_REPEAT_QUEST_COUNT) then
		user_name = "Quests"..os.date("%H%M%S");
		user, role = startup(user_name, user_name);

		for nTime = 1, quest_data.nMaxCompletedCount do
			print("============QuestID = "..quest_data.nQuestID.."===========nTime = "..nTime .. "======================");

			_AcceptQuestWithoutConditionIndex(user, role, quest_data, 0, nTime, qatNpc, 0);
			print("========================accept quest==============================");

			_CompleteQuestWithoutConditionIndex(user, role, quest_data, 0, nTime);
			print("========================complete quest==============================");
		end
	end

	g_queststatus[nindex].status = true;
end

function _AcceptQuestWithoutConditionIndex(user, role, questdata, nIndex, nCompletingTime, nAcceptType, nSrcID)

	-- Number of configuration entries
	local nCount = 0;
	local session_id = user:GetSessionID();

	g_gametime = g_oGameWorld:GetGameTime();
	local tm = get_localtime_ex(g_gametime);
	local gametime = g_gametime;

	-- Freeze time
	user:GMCommand("g_oGameWorld:SetFreezeTime(true)");
	wait(3);

	-- Whether to accept the quest again
	nCount = nCount + 1;
	if nCount == nIndex then
		-- Use a GM command to mark this quest completed
		ret = user:GMCommand("CompleteQuest("..questdata.nQuestID..");");
		wait(3);
	    check(ret, "failed to CompleteQuest");
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here1 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Quest class requirement
	if questdata.nClassLimit ~= 4 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SelfRole:SetClass("..questdata.nClassLimit..");");
		else
			local nClass = questdata.nClassLimit + 1;
			nClass = nClass % 4;
			user:GMCommand("SelfRole:SetClass("..nClass..");");
			print("==================unable to fullfil nClassLimit====================================");
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 2 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Gender requirement
	if questdata.nSexLimit ~= 0 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SelfRole:SetSex("..questdata.nSexLimit..");");
			wait(1);
		else
			local nSex = 2;
			if questdata.nSexLimit == 2 then
				nSex = 1;
			end
			user:GMCommand("SelfRole:SetSex("..nSex..");");
			wait(1);
			print("==================unable to fullfil nSexLimit====================================");
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 3 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	 -- Relationship requirement
	 -- Not considered for now

	-- Check prerequisite quest 1: whether the current quest can be completed without it (pass if Meet already satisfied it during the repeated acceptance test)
	if questdata.nPreQuestID1 ~= 0 then
		print("==========questdata.nPreQuestID1 = "..questdata.nPreQuestID1.."===================");
		nCount = nCount + 1;
		if nCount ~= nIndex and nIndex ~= 1 and nCompletingTime == 1 then

			--	Use a GM command flag to set the completion flag
			ret = user:GMCommand("CompleteQuest("..questdata.nPreQuestID1..");");
			wait(3);
	        check(ret, "failed to CompleteQuest");
			print("==================successfully completed nPreQuestID1=="..questdata.nPreQuestID1.."==================================");
		else
			print("==================unable to fullfil nPreQuestID1====================================");
		end
	end

	-- Check prerequisite quest 2: whether the current quest can be completed without it (pass if Meet already satisfied it during the repeated acceptance test)
	if questdata.nPreQuestID2 ~= 0 then
		print("==========questdata.nPreQuestID2 = "..questdata.nPreQuestID2.."===================");
		nCount = nCount + 1;
		if nCount ~= nIndex and nIndex ~= 1 and nCompletingTime == 1 then

			--	Use a GM command flag to set the completion flag
			user:GMCommand("CompleteQuest("..questdata.nPreQuestID2..");");
			wait(3);
			print("==================successfully completed nPreQuestID2=="..questdata.nPreQuestID2.."==================================");
		else
			print("==================unable to fullfil nPreQuestID2====================================");
		end
	end

	-- Starting quest NPC ID
	if questdata.nStartNpcID ~= 0 then
	  	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nStartNpcID @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SummonNpc("..questdata.nStartNpcID..")");
			msg = recv_msg(40, session_id, protocol.g2c_char_appear);
			check(msg, "failed to summon npc");
			check(msg.stAppearData.dwCharID ~= 0, "failed to summon npc with id");

			ret = user:InteractWithNpc(msg.stAppearData.dwCharID);
			check(ret, "failed to interact with npc");
			msg = recv_msg(40, session_id, protocol.g2c_interact_result);
			check(msg, "failed to summon npc");
		else
			print("==================unable to fullfil nStartNpcID====================================");
		end
	end

	-- Year limit
	if questdata.nYearLimit ~= 0 then
	   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nYearLimit @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		if nCount == nIndex then
			if tm.tm_year == questdata.nYearLimit then
				gametime = gametime - 370*24*3600;
			end
			print("==================unable to fullfil nYearLimit====================================");
		else
			print("tm.tm_year = "..tm.tm_year);
			print("questdata.nYearLimit = "..questdata.nYearLimit);

			if tm.tm_year ~= questdata.nYearLimit then
				gametime = gametime + (questdata.nYearLimit - (tm.tm_year + 1900))*365*24*3600;
			end
		end
	end

	-- Month limit
	if questdata.nMonthLimit ~= -1 then
	   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nMonthLimit @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		if nCount == nIndex then
			if tm.tm_mon == questdata.nMonthLimit then
				gametime = gametime - 40*24*3600;
			end
			print("==================unable to fullfil nMonthLimit====================================");
		else
			if tm.tm_mon ~= questdata.nMonthLimit then
				if tm.tm_mon > questdata.nMonthLimit then  -- Current time is later than the quest requirement
					gametime = gametime - ((tm.tm_mon + 1) - questdata.nMonthLimit)*31*24*3600;
				else	-- Current time is earlier than the quest requirement, so add one year
					gametime = gametime - ((tm.tm_mon + 13) - questdata.nMonthLimit)*31*24*3600 + 365*24*3600;
				end
			end
		end
	end

	-- Acceptance start time for weekly repeatable quests
	--if questdata.nStartWeekday ~= -1 then
	--   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nStartWeekday @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	--	local endweekday = (questdata.nStartWeekday + questdata.nWeekdayDuration) % 7;
	--	nCount = nCount + 1;
	--	if nCount == nIndex then
	--		if (questdata.nStartWeekday <= endweekday) and (tm.tm_wday >= questdata.nStartWeekday) and (tm.tm_wday <= endweekday) then
	--			local gametime = g_gametime - (tm.tm_wday - questdata.nStartWeekday + 1)*24*3600;
	--			user:GMCommand("g_oGameWorld:SetGameTime(..gametime..)");
	--			wait(5);
	--		elseif (questdata.nStartWeekday > endweekday) and ((tm.tm_wday <= questdata.nStartWeekday) or (tm.tm_wday >= endweekday)) then
	--			local gametime = g_gametime - (endweekday- tm.tm_wday - questdata.nStartWeekday + 1)*30*24*3600;
	--			user:GMCommand("g_oGameWorld:SetGameTime(..gametime..)");
	--			wait(5);
	--		end
	--	else
	--		print("==================unable to fullfil nStartWeekday====================================");
	--	end
	--end

	-- Acceptance start time for monthly repeatable quests
	--if questdata.nStartMonthday ~= 0 then
	--   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nStartMonthday @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	--	nCount = nCount + 1;
	--	if nCount == nIndex then
	--		if tm.tm_mday > questdata.nStartMonthday and tm.tm_mday < (questdata.nStartMonthday + questdata.nMonthdayDuration) then
	--			gametime = gametime + (questdata.nStartMonthday - tm.tm_mday - 1)*12*3600;
	--		end
	--		print("==================unable to fullfil nStartMonthday====================================");
	--	else
	--		if tm.tm_mday <= questdata.nStartMonthday or tm.tm_mday >= (questdata.nStartMonthday + questdata.nMonthdayDuration) then
	--			gametime = gametime + (questdata.nStartMonthday + questdata.nMonthdayDuration - 1 - tm.tm_mday)*24*3600;
	--			print("==================questdata.nMonthdayDuration= "..questdata.nMonthdayDuration.."===================================");
	--		end
	--	end
	--end

	-- Start of the allowed acceptance time range
	--if questdata.dwAcceptStartTime ~= 0 then
	--   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here dwAcceptStartTime @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	--	local daytime = gametime % 86400;
	--	nCount = nCount + 1;
	--	if nCount == nIndex then
	--		if (gametime >= questdata.dwAcceptStartTime) and (gametime <= questdata.dwAcceptEndTime) and (daytime >= questdata.nAcceptStartDayTime) and (daytime <= questdata.nAcceptEndDayTime) then
	--			gametime = questdata.dwAcceptStartTime - 365*12*30*24*3600;
	--		end
	--		print("==================unable to fullfil dwAcceptStartTime====================================");
	--	else
	--		gametime = gametime + questdata.dwAcceptStartTime + questdata.dwAcceptEndTime/2;
	--	end
	--end

	-- Starting quest item ID
	if questdata.nStartItemID ~= 0 then
	   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nStartItemID @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		if nCount ~= nIndex then
			ret = user:GMCommand("AddItem(" .. questdata.nStartItemID .. ", 1)");
			check(ret, "failed to send gm command");

			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");
		else
			-- Check whether the character has this item
			local itembag = role:GetItemBag();
			check(itembag, "failed to get itembag");

			local nItemCount = itembag.GetItemCount(questdata.nStartItemID);
			check(nItemCount == 0, "failed to get nStartItemID");
			print("==================unable to fullfil nStartItemID====================================");
		end
	end

	-- Minimum quest level requirement
	if questdata.nMinLevelLimit ~= 0 then
		print("@@@@@@@@@@@@@@@@@@@@@@@ come here 5 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		-- Ignore the minimum level when testing the maximum
		if nCount ~= nIndex - 1 then
			if nCount ~= nIndex then
				local exp = GetMaxExpByLevel(questdata.nMinLevelLimit);
				check(exp ~= nil, "fail to get exp by level");
				exp = exp + 2;
				ret = user:GMCommand("AddExp("..exp..")");
				check(ret, "failed to add exp");
			else
				print("==================unable to fullfil nMinLevelLimit====================================");
			end
		end
	end

	 -- Maximum quest level requirement
	if questdata.nMaxLevelLimit ~= 0 then
		nCount = nCount + 1;
		local exp = GetMaxExpByLevel(questdata.nMaxLevelLimit + 1);
		check(exp ~= nil, "fail to get exp by level");

		-- Ignore the maximum level when testing the minimum
		if nCount ~= nIndex + 1 and nIndex ~= 0 then
			if nCount ~= nIndex then
				exp = exp - 2;
				ret = user:GMCommand("AddExp("..exp..")");
				check(ret, "failed to add exp");
			else
				exp = exp + 2;
				ret = user:GMCommand("AddExp("..exp..")");
				check(ret, "failed to add exp");
				print("==================unable to fullfil nMaxLevelLimit====================================");
			end
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 6 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- This requires additem and useitem, so leave it commented out for now
	-- Required buff ID and level
	--if questdata.nBuffIDLimit ~= 0 then
	--	nCount = nCount + 1;
	--	if nCount ~= nIndex then
	----		ret = role:CastSpellToSelf(109);	-- Skill 109 corresponds to buff 109; ensure the configured buff matches quest_data.nBuffLevelLimit
	--		check(ret, "fail to cast spell to myself");
	--	else
	--		print("==================unable to fullfil nBuffIDLimit====================================");
	--	end
	--end

	-- Required currency type and amount (not deducted)
	if questdata.nMoneyTypeLimit ~= 0 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			ret = user:GMCommand("AddMoney("..questdata.nMoneyTypeLimit..", "..questdata.nMoneyAmountLimit..", MONEYLOG_GM_COMMAND)");
			check(ret, "failed to add money");
		else
			print("==================unable to fullfil nMoneyTypeLimit====================================");
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 7 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Required NPC faction reputation
	if questdata.nReputationForceID ~= -1 then

		-- Minimum reputation requirement (must pass when testing the maximum)
		if questdata.nReputationMinLimit ~= 0 then

			print("==================questdata.nReputationMinLimit=="..questdata.nReputationMinLimit.."====================================");
			print("==================questdata.nReputationForceID=="..questdata.nReputationForceID.."====================================");

			nCount = nCount + 1;
			if nCount ~= nIndex then
				ret = user:GMCommand("SetReputation("..questdata.nReputationForceID ..","..questdata.nReputationMinLimit..")");
				check(ret, "failed to set reputation");
			else if nCount ~= nIndex - 1 then
					local nReputation = questdata.nReputationMinLimit - 1;
					ret = user:GMCommand("SetReputation("..questdata.nReputationForceID ..","..nReputation..")");
					check(ret, "failed to set reputation");
					print("==================unable to fullfil ReputationMinLimit====================================");
				end
			end
			wait(1);
		end

		-- Maximum reputation requirement (must pass when testing the minimum)
		if questdata.nReputationMaxLimit ~= 0 then
			nCount = nCount + 1;
			if nCount ~= nIndex and nCount ~= nIndex + 1 then
				ret = user:GMCommand("SetReputation("..questdata.nReputationForceID ..","..questdata.nReputationMaxLimit..")");
				check(ret, "failed to set reputation");
			else if nCount ~= nIndex + 1 then
					local nReputation = questdata.nReputationMaxLimit + 1;
					ret = user:GMCommand("SetReputation("..questdata.nReputationForceID ..","..nReputation..")");
					check(ret, "failed to set reputation");
					print("==================unable to fullfil nReputationMaxLimit====================================");
				 end
			end
			wait(1);
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 8 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- The bot crashes when receiving g2c_item_change; temporarily comment out the item
	-- Required items carried
	--for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
	--	if questdata.vecItemLimitID[nItemIndex] ~= 0 and questdata.vecItemLimitCnt[nItemIndex] ~= 0 then
	--		nCount = nCount + 1;
	--		if nCount ~= nIndex then
	--			ret = user:GMCommand("AddItem(" .. questdata.vecItemLimitID[nItemIndex] .. ", " .. questdata.vecItemLimitCnt[nItemIndex] .. ")");
	--			check(ret, "failed to send gm command");

	--			msg = recv_msg(5, session_id, protocol.g2c_item_change);
	--			check(msg, "failed to recv g2c_item_change");
	--		else
	--			print("==================unable to fullfil vecItemLimitID====================================");
	--		end
	--	end
	--end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nLimitVarID1 = "..questdata.nLimitVarID1.."@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Required variable ID 1 and value 1 (equality check); acceptance checks only Role and Scene, not Quest
	if questdata.nLimitVarID1 ~= -1 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			local nVariableType = get_variable_type(questdata.nLimitVarID1);
			local nVariableIndex = get_variable_index(questdata.nLimitVarID1);

			if nVariableType == vtRole then
				print("******************vtRole*****************************************");
				ret = user:GMCommand("SelfRole:SetVariable("..nVariableIndex..","..questdata.nLimitVarValue1..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtScene then
				ret = user:GMCommand("local oScene = SelfRole:GetScene();oScene::SetVariable("..nVariableIndex..","..quest_data.nLimitVarValue1..");");
				check(ret, "fail to SetVariable ");
			end
			wait(1);
		else
			print("==================unable to fullfil nLimitVarID1====================================");
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 9 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Required variable ID 2 and value 2 (equality check); acceptance checks only Role and Scene, not Quest
	if questdata.nLimitVarID2 ~= -1 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			local nVariableType = get_variable_type(questdata.nLimitVarID2);
			local nVariableIndex = get_variable_index(questdata.nLimitVarID2);
			if nVariableType == vtRole then
				print("******************vtRole*****************************************");
				ret = user:GMCommand("SelfRole:SetVariable("..nVariableIndex..","..questdata.nLimitVarValue2..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtScene then
				ret = user:GMCommand("local oScene = SelfRole:GetScene();oScene::SetVariable("..nVariableIndex..","..questdata.nLimitVarValue2..");");
				check(ret, "fail to SetVariable ");
			end
			wait(1);
		else
			print("==================unable to fullfil nLimitVarID2s====================================");
		end
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here 10 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- Currency type awarded upon quest acceptance
	if questdata.nOfferMoneyType ~= 0 then
		nCount = nCount + 1;
		if nCount == nIndex then
			ret = user:GMCommand("AddMoney("..questdata.nMoneyTypeLimit..",1000000000, MONEYLOG_GM_COMMAND)"); -- MAX_MONEY
			check(ret, "failed to add money");
			print("==================unable to fullfil nOfferMoneyType====================================");
		end
	end

	user:GMCommand("g_oGameWorld:SetGameTime("..gametime..")");
	wait(5);

	if 	nCompletingTime ~= -1 then

		print("==================request to accept quest, id ="..questdata.nQuestID.."===================");
		print("==================index = "..nIndex .."===================");
		ret = user:AcceptQuest(questdata.nQuestID, nAcceptType, nSrcID);
		check(ret, "fail to send accept quest");

		if nIndex <= nCount then
			-- The completion count exceeds the allowed count
			if nIndex ~= 0 or (nCompletingTime > questdata.nMaxCompletedCount and questdata.nQuestID <= MAX_NORMAL_QUEST_COUNT) then
				msg = recv_msg(30, session_id, protocol.g2c_error_notify);
				check(msg.nErrCode ~= error_code.errSuccess, "failed to recv errSuccess");
			else
				msg = recv_msg(40, session_id, protocol.g2c_accept_quest);
				check(msg.nQuestID == questdata.nQuestID, "failed to recv g2c_accept_quest");
				print("===============accept successfully, id = ".. questdata.nQuestID .."===================================");
			end
		end
	end
end

function _CompleteQuestWithoutConditionIndex(user, role, quest_data, nIndex, nCompletingTime)

	local nCount = 0;
	local msg;
	local session_id = user:GetSessionID();

	-- Quest class requirement
	if quest_data.nClassLimit ~= 4 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SelfRole:SetClass("..quest_data.nClassLimit..");");
		else
			print("================unable to fullfil nClassLimit================================================");
			local nClass = (quest_data.nClassLimit + 1) % 4;
			user:GMCommand("SelfRole:SetClass("..nClass..");");
		end
	end

	-- Gender requirement
	if quest_data.nSexLimit ~= 0 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SelfRole:SetSex("..quest_data.nSexLimit..");");
			wait(1);
		else
			local nSex = 2;
			if quest_data.nSexLimit == 2 then
				nSex = 1;
			end

			user:GMCommand("SelfRole:SetSex("..nSex..");");
			wait(1);
			print("================unable to fullfil nSexLimit================================================");
		end
	end

	-- Check kill count before checking the quest NPC to avoid moving too far from the NPC while casting skills
	for nNpcIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if  quest_data.vecCheckKillNpcID[nNpcIndex] ~= 0 and quest_data.vecCheckKillNpcCnt[nNpcIndex] ~= 0 then
			print("************* Quest is: "..quest_data.nQuestID.. "*******   quest_data.vecCheckKillNpcID[nNpcIndex] : " ..quest_data.vecCheckKillNpcID[nNpcIndex].."********quest_data.vecCheckKillNpcCnt[nNpcIndex] = "..quest_data.vecCheckKillNpcCnt[nNpcIndex].."******");
			nCount = nCount + 1;
			if nCount ~= nIndex then
				for nNpcCount = 1, quest_data.vecCheckKillNpcCnt[nNpcIndex] + 4 do
					-- Spawn and kill monsters
					local cmd = "local oNpc = SummonNpc(" ..quest_data.vecCheckKillNpcID[nNpcIndex].."); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";
					ret = user:GMCommand(cmd); -- Warrior: Barbaric Charge
					wait(3);
				end
			else
				print("================unable to fullfil vecCheckKillNpcID================================================");
			end
        end
    end

	--Quest completion NPC ID
	if quest_data.nFinishNpc ~= 0 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			user:GMCommand("SummonNpc("..quest_data.nFinishNpc..")");
			msg = recv_msg(5, session_id, protocol.g2c_char_appear);
			check(msg, "failed to summon npc");

			ret = user:InteractWithNpc(msg.stAppearData.dwCharID);
			check(ret, "failed to interact with npc");
			msg = recv_msg(5, session_id, protocol.g2c_interact_result);
			check(msg, "failed to summon npc");

		else
			-- In most cases, the completion NPC is the same as the starting NPC
			-- The interaction NPC set during acceptance can therefore allow completion even without setting it again
			-- Therefore spawn an incorrect NPC ID when testing the completion NPC

			local npcid = quest_data.nFinishNpc - 1;
			user:GMCommand("SummonNpc(".. npcid ..")");
			msg = recv_msg(5, session_id, protocol.g2c_char_appear);
			check(msg, "failed to summon npc");

			ret = user:InteractWithNpc(msg.stAppearData.dwCharID);
			check(ret, "failed to interact with npc");
			msg = recv_msg(5, session_id, protocol.g2c_interact_result);
			check(msg, "failed to summon npc");

			print("================unable to fullfil nFinishNpc1================================================");
		end
	end

	-- Check buffs at quest completion
	if quest_data.nCheckBuffID ~= 0 then
		nCount = nCount + 1;
		if nCount ~= nIndex and quest_data.nCheckBuffID == 109 then
			ret = user:CastSpellToSelf(quest_data.nCheckBuffID);
			check(ret, "fail to cast spell to self");
			wait(1);
		else
			print("================unable to fullfil nCheckBuffID================================================");
		end
	end

    for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if quest_data.vecCheckItemID[nItemIndex] ~= 0 then
            nCount = nCount + 1;
            if nCount ~= nIndex then
				ret = user:GMCommand("AddItem("..quest_data.vecCheckItemID[nItemIndex]..","..quest_data.vecCheckItemCnt[nItemIndex]..")");
				check(ret, "failed to send gm command");

				msg = recv_msg(5, session_id, protocol.g2c_item_change);
				check(msg, "failed to recv g2c_item_change");
			else
				print("================unable to fullfil vecCheckItemID================================================");
			end
        end
    end

	-- Required variable ID 1 and value 1 (equality check); check Role, Scene and Quest
	if quest_data.nCheckVarID1 ~= -1 then
		nCount = nCount + 1;

		if nCount ~= nIndex then
			local nVariableType = get_variable_type(quest_data.nCheckVarID1);
			local nVariableIndex = get_variable_index(quest_data.nCheckVarID1);
			if nVariableType == vtRole then
				ret = user:GMCommand("SelfRole:SetVariable("..nVariableIndex..","..quest_data.nCheckVarValue1..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtScene then
				ret = user:GMCommand("local oScene = SelfRole:GetScene();oScene::SetVariable("..nVariableIndex..","..quest_data.nCheckVarValue1..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtQuest then
				ret = user:GMCommand("local oQuestList = SelfRole:GetQuestList();local oQuest = oQuestList:GetAcceptedQuest("..quest_data.nQuestID..");oQuestList:SetVariable("..oQuest..","..nVariableIndex..","..quest_data.nCheckVarValue1..")");
				check(ret, "fail to SetVariable ");
			end
			wait(1);
		else
			print("================unable to fullfil nCheckVarID1================================================");
		end
	end

	-- Required variable ID 2 and value 2 (equality check); check Role, Scene and Quest
	if quest_data.nCheckVarID2 ~= -1 then
		nCount = nCount + 1;
		if nCount ~= nIndex then
			local nVariableType = get_variable_type(quest_data.nCheckVarID2);
			local nVariableIndex = get_variable_index(quest_data.nCheckVarID2);
			if nVariableType == vtRole then
				ret = user:GMCommand("SelfRole:SetVariable("..nVariableIndex..","..quest_data.nCheckVarValue2..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtScene then
				ret = user:GMCommand("local oScene = SelfRole:GetScene();oScene::SetVariable("..nVariableIndex..","..quest_data.nCheckVarValue2..");");
				check(ret, "fail to SetVariable ");
			elseif nVariableType == vtQuest then
				ret = user:GMCommand("local oQuestList = SelfRole:GetQuestList();local oQuest = oQuestList:GetAcceptedQuest("..nQuestID..");oQuestList:SetVariable("..oQuest..","..nVariableIndex..","..quest_data.nCheckVarValue2..")");
				check(ret, "fail to SetVariable ");
			end
			wait(1);
		else
			print("================unable to fullfil nLimitVarID2================================================");
		end
	end

	-- Reward currency type and amount
	if quest_data.nAwardMoneyType ~= 0 and quest_data.nAwardMoneyAmount ~= 0 then
		nCount = nCount + 1;
		if nCount == nIndex then
			ret = user:GMCommand("AddMoney("..quest_data.nAwardMoneyType..",1000000000, MONEYLOG_GM_COMMAND)");
			check(ret, "failed to add money");
			wait(1);

			print("================unable to fullfil nAwardMoneyType================================================");
		end
	end

	print("--------------------prepare to complete quest = "..quest_data.nQuestID.."--------------------------------");
	print("--------------------nindex = ".. nIndex .. "--------------------------------");

	ret = user:CompleteQuest(quest_data.nQuestID, 0);
	check(ret, "fail to complete quest");

	if nIndex <= nCount then

		if nIndex ~= 0 or nCompletingTime > quest_data.nMaxCompletedCount then
			msg = recv_msg(30, session_id, protocol.g2c_error_notify);
			check(msg.nErrCode ~= error_code.errSuccess, "failed to recv errSuccess");
		else
			msg = recv_msg(30, session_id, protocol.g2c_complete_quest);
			check(msg.nQuestID == quest_data.nQuestID, "failed to recv g2c_complete_quest");
			print("=======================complete successfully==============================");
		end
	end

end

function GetQuestByID(nQuestID)

	local quest_data = CDataManager_QUEST_DATA_:GetInstance():GetFirstData();

	while(quest_data ~= nil) do
		if quest_data.nQuestID == nQuestID then
			return quest_data;
		end

		quest_data = CDataManager_QUEST_DATA_:GetInstance():GetNextData();
	end

	return nil;
end

function GetMaxExpByLevel(nLevel)
	local level_data = CDataManager_LEVEL_DATA_:GetInstance():GetFirstData();
	local exp = 0;
	while level_data do
		if level_data.m_nLevel < nLevel then
			exp = exp + level_data.m_nMaxExp;
		else
			return exp;
		end
		level_data = CDataManager_LEVEL_DATA_:GetInstance():GetNextData();
	end
	return nil;
end

function MeetQuest()
	addco("MeetQuest", _MeetQuest);
end

function _MeetQuest()
    local user_name;
    local questcountmeanwhile = 1; -- Number of quests run concurrently
    local nquestcount = 0;
	local runflag = true;
	local i;

    g_queststatus = {}; -- Status of each quest
    g_acceptstatus = {}; -- Coroutine status for each index when testing quest acceptance
    g_completestatus = {}; -- Coroutine status for each index when testing quest completion
    g_traversstatus = {}; -- Coroutine status for each index when testing quest traversal

	-- Traverse all quests
	local quest_data = CDataManager_QUEST_DATA_:GetInstance():GetFirstData();

	while(quest_data ~= nil) do
		if quest_data.nQuestID ~= 0 then
			user_name = "Meet"..quest_data.nQuestID..os.date("%H%M%S");

			print("=============MeetQuest.quest_data.nQuestID = "..quest_data.nQuestID.."=========");
			nquestcount = nquestcount + 1;
			addco("Meet"..nquestcount..os.date("%H%M%S"), _CompleteQuest, user_name, quest_data, 0, 1, 0, 1, nquestcount);

			g_queststatus[nquestcount] = {};
			g_queststatus[nquestcount].ID = quest_data.nQuestID;
			g_queststatus[nquestcount].status = false;
		end

		if quest_data.nQuestID ~= 0 and nquestcount % questcountmeanwhile == 0 then
			while runflag do
				runflag = false;
				for i = (nquestcount- questcountmeanwhile + 1), nquestcount do
					if g_queststatus[i].status == false then
						--print("--------g_queststatus["..i..".status == " ..g_queststatus[i].status.."------");
						runflag = true;
					end
				end

				wait(1);

			end
		end

		runflag = true;
		quest_data = CDataManager_QUEST_DATA_:GetInstance():GetNextData();
	end
end

function _CompleteQuest(username, quest_data, acceptindex, accepttime, completeindex, completetime, index)

	user, role = startup(username, username);
	check(user, "fail to login");
	check(role, "fail to login");

	JumpToSceneBySceneTempID(user, 102, 0);

	if acceptindex ~= -1 then
		print("==================come here1============================");
		_AcceptQuestWithoutConditionIndex(user, role, quest_data, acceptindex, accepttime, qatNpc, 0);
	end

	wait(1);

	if completeindex ~= -1 then
		print("==================come here2============================");
		_CompleteQuestWithoutConditionIndex(user, role, quest_data, completeindex, completetime);
	end

	cleanup(user);

	if g_queststatus[index] ~= nil then
		g_queststatus[index].status = true;
	end
end

function getquestacceptconfigcount(questdata)

	-- Number of configuration entries
	local nCount = 0;

	-- Whether to accept the quest again
	nCount = nCount + 1;

	-- Quest class requirement
	if questdata.nClassLimit ~= 4 then
		nCount = nCount + 1;
	end

	-- Gender requirement
	if questdata.nSexLimit ~= 0 then
		nCount = nCount + 1;
	end

	 -- Relationship requirement
	 -- Not considered for now

	-- Check prerequisite quest 1: whether the current quest can be completed without it (pass if Meet already satisfied it during the repeated acceptance test)
	if questdata.nPreQuestID1 ~= 0 then
		nCount = nCount + 1;
	end

	-- Check prerequisite quest 2: whether the current quest can be completed without it (pass if Meet already satisfied it during the repeated acceptance test)
	if questdata.nPreQuestID2 ~= 0 then
		nCount = nCount + 1;
	end

	-- Starting quest NPC ID
	if questdata.nStartNpcID ~= 0 then
		nCount = nCount + 1;
	end

	-- Starting quest item ID
	if questdata.nStartItemID ~= 0 then
		nCount = nCount + 1;
	end

	-- Minimum quest level requirement
	if questdata.nMinLevelLimit ~= 0 then
		nCount = nCount + 1;
	end

	 -- Maximum quest level requirement
	if questdata.nMaxLevelLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- This requires additem and useitem, so leave it commented out for now
	-- Required buff ID and level
	--if questdata.nBuffIDLimit ~= 0 then
	--	nCount = nCount + 1;
	--end

	-- Required currency type and amount (not deducted)
	if questdata.nMoneyTypeLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- Required NPC faction reputation
	if questdata.nReputationForceID ~= -1 then

		-- Minimum reputation requirement (must pass when testing the maximum)
		if questdata.nReputationMinLimit ~= 0 then
			nCount = nCount + 1;
		end

		-- Maximum reputation requirement (must pass when testing the minimum)
		if questdata.nReputationMaxLimit ~= 0 then
			nCount = nCount + 1;
		end
	end

	-- The bot crashes when receiving g2c_item_change; temporarily comment out the item
	-- Required items carried
	--for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
	--	if questdata.vecItemLimitID[nItemIndex] ~= 0 and questdata.vecItemLimitCnt[nItemIndex] ~= 0 then
	--		nCount = nCount + 1;
	--  end
	--end

	-- Required variable ID 1 and value 1 (equality check); acceptance checks only Role and Scene, not Quest
	if questdata.nLimitVarID1 ~= -1 then
		nCount = nCount + 1;
	end

	-- Required variable ID 2 and value 2 (equality check); acceptance checks only Role and Scene, not Quest
	if questdata.nLimitVarID2 ~= -1 then
		nCount = nCount + 1;
	end

	-- Currency type awarded upon quest acceptance
	if questdata.nOfferMoneyType ~= 0 then
		nCount = nCount + 1;
	end

	return nCount;
end

