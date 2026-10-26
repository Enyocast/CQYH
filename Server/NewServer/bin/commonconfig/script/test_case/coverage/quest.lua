

function CoverageTestCase.TraversAllQuests()
	addco("TraversAll", _TraversAllQuests);
end

function _TraversAllQuests()
    local ret;
    g_traversstatus = {};

    local questcountmeanwhile = 1; -- 同时跑的任务数
    local nquestcount = 0;
	local runflag = true;
    g_queststatus = {};

	-- 遍历所有任务
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

	-- 测试不满足接任务条件情况
	g_nQuestConfigCount = getquestacceptconfigcount(quest_data);
	check(g_nQuestConfigCount ~= 0, "fail to check quest_data");

	for nQuestIndex = 1,g_nQuestConfigCount do
		user_name = "Accept"..os.date("%H%M%S");
		_CompleteQuest(user_name, quest_data, nQuestIndex, 1, -1, -1);
	end

	g_nQuestConfigCount = getquestcompleteconfigcount(quest_data);

	print("=============configurenum = "..g_nQuestConfigCount.."=================================");

	-- 测试不满足交任务条件情况
	for nQuestIndex = 1, g_nQuestConfigCount do
		user_name = "Complete"..os.date("%H%M%S");
		_CompleteQuest(user_name, quest_data, 0, 1, nQuestIndex, 1); -- 创造接任务成功条件,测交任务
	end

	-- 测试满足接任务和交任务的条件下，重复任务的重复完成 (普通任务的重复接已经在_AcceptConditionIndex 中完成)
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

	-- 配置项数目
	local nCount = 0;
	local session_id = user:GetSessionID();

	g_gametime = g_oGameWorld:GetGameTime();
	local tm = get_localtime_ex(g_gametime);
	local gametime = g_gametime;

	-- 冻结时间
	user:GMCommand("g_oGameWorld:SetFreezeTime(true)");
	wait(3);

	-- 是否重复接任务
	nCount = nCount + 1;
	if nCount == nIndex then
		-- 使用GM命令设置此任务已经完成
		ret = user:GMCommand("CompleteQuest("..questdata.nQuestID..");");
		wait(3);
	    check(ret, "failed to CompleteQuest");
	end

	print("@@@@@@@@@@@@@@@@@@@@@@@ come here1 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	-- 任务职业需求
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

	-- 性别需求
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

	 -- 关系需求
	 -- 暂不作考虑

	-- 判断前置任务1,不满足前置任务能否完成当前任务(如果在测试重复接受任务时已经使用Meet满足过条件，此项pass)
	if questdata.nPreQuestID1 ~= 0 then
		print("==========questdata.nPreQuestID1 = "..questdata.nPreQuestID1.."===================");
		nCount = nCount + 1;
		if nCount ~= nIndex and nIndex ~= 1 and nCompletingTime == 1 then

			--	使用GM命令标志来设置完成标志
			ret = user:GMCommand("CompleteQuest("..questdata.nPreQuestID1..");");
			wait(3);
	        check(ret, "failed to CompleteQuest");
			print("==================successfully completed nPreQuestID1=="..questdata.nPreQuestID1.."==================================");
		else
			print("==================unable to fullfil nPreQuestID1====================================");
		end
	end

	-- 判断前置任务2,不满足前置任务能否完成当前任务(如果在测试重复接受任务时已经使用Meet满足过条件，此项pass)
	if questdata.nPreQuestID2 ~= 0 then
		print("==========questdata.nPreQuestID2 = "..questdata.nPreQuestID2.."===================");
		nCount = nCount + 1;
		if nCount ~= nIndex and nIndex ~= 1 and nCompletingTime == 1 then

			--	使用GM命令标志来设置完成标志
			user:GMCommand("CompleteQuest("..questdata.nPreQuestID2..");");
			wait(3);
			print("==================successfully completed nPreQuestID2=="..questdata.nPreQuestID2.."==================================");
		else
			print("==================unable to fullfil nPreQuestID2====================================");
		end
	end

	-- 开始任务的NPC ID
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

	-- 年限制
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

	-- 月限制
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
				if tm.tm_mon > questdata.nMonthLimit then  -- 现在的时间大于任务要求时间
					gametime = gametime - ((tm.tm_mon + 1) - questdata.nMonthLimit)*31*24*3600;
				else	-- 现在的时间小于任务要求时间,所以要多加一年
					gametime = gametime - ((tm.tm_mon + 13) - questdata.nMonthLimit)*31*24*3600 + 365*24*3600;
				end
			end
		end
	end

	-- 星期重复任务允许接受的开始时间
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

	-- 月份重复任务允许接受的开始时间
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

	-- 允许接受时间范围开始
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

	-- 开始任务的Item ID
	if questdata.nStartItemID ~= 0 then
	   	print("@@@@@@@@@@@@@@@@@@@@@@@ come here nStartItemID @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		if nCount ~= nIndex then
			ret = user:GMCommand("AddItem(" .. questdata.nStartItemID .. ", 1)");
			check(ret, "failed to send gm command");

			msg = recv_msg(5, session_id, protocol.g2c_item_change);
			check(msg, "failed to recv g2c_item_change");
		else
			-- 查找身上是否有此物品
			local itembag = role:GetItemBag();
			check(itembag, "failed to get itembag");

			local nItemCount = itembag.GetItemCount(questdata.nStartItemID);
			check(nItemCount == 0, "failed to get nStartItemID");
			print("==================unable to fullfil nStartItemID====================================");
		end
	end

	-- 任务最低等级需求
	if questdata.nMinLevelLimit ~= 0 then
		print("@@@@@@@@@@@@@@@@@@@@@@@ come here 5 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		nCount = nCount + 1;
		-- 在测试最高等级时，不受最低等级影响
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

	 -- 任务最高等级需求
	if questdata.nMaxLevelLimit ~= 0 then
		nCount = nCount + 1;
		local exp = GetMaxExpByLevel(questdata.nMaxLevelLimit + 1);
		check(exp ~= nil, "fail to get exp by level");

		-- 在测试最低等级时，不受最高等级影响
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

	-- 这个需要additem 和 useitem, 暂且注释掉
	-- 需求BUFF ID 和 LEVEL
	--if questdata.nBuffIDLimit ~= 0 then
	--	nCount = nCount + 1;
	--	if nCount ~= nIndex then
	----		ret = role:CastSpellToSelf(109);	-- 109号技能，对应109号的buf,配对应buf时注意与quest_data.nBuffLevelLimit对应
	--		check(ret, "fail to cast spell to myself");
	--	else
	--		print("==================unable to fullfil nBuffIDLimit====================================");
	--	end
	--end

	-- 需求货币类型, 需求货币数量（不扣除）
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

	-- 需求Npc势力声望
	if questdata.nReputationForceID ~= -1 then

		-- 需求最低声望(在测试需求最高声望时需要pass)
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

		-- 需求最高声望(在测试最低声望时需要pass)
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

	-- 机器人在接受g2c_item_change时会甭，暂时把物品注掉
	-- 身上道具需求
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

	-- 需求变量ID1, 需求变量值1（判断相等）接任务时只判断Role Scene, 不考虑Quest
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

	-- 需求变量ID2, 需求变量值2（判断相等）接任务时只判断Role Scene, 不考虑Quest
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

	-- 接任务获得货币类型
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
			-- 已经完成的次数超过允许完成的次数
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

	-- 任务职业需求
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

	-- 性别需求
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

	-- 杀怪数检查(放在检查任务npc前面，防止由于释放技能，移动距离过大，导致与npc距离过大)
	for nNpcIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if  quest_data.vecCheckKillNpcID[nNpcIndex] ~= 0 and quest_data.vecCheckKillNpcCnt[nNpcIndex] ~= 0 then
			print("************* Quest is: "..quest_data.nQuestID.. "*******   quest_data.vecCheckKillNpcID[nNpcIndex] : " ..quest_data.vecCheckKillNpcID[nNpcIndex].."********quest_data.vecCheckKillNpcCnt[nNpcIndex] = "..quest_data.vecCheckKillNpcCnt[nNpcIndex].."******");
			nCount = nCount + 1;
			if nCount ~= nIndex then
				for nNpcCount = 1, quest_data.vecCheckKillNpcCnt[nNpcIndex] + 4 do
					-- 招怪, 杀怪
					local cmd = "local oNpc = SummonNpc(" ..quest_data.vecCheckKillNpcID[nNpcIndex].."); oNpc:SetHp(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ()); wait(1); SelfRole:CastSpell(1002, oNpc, oNpc:GetX(), oNpc:GetY(), oNpc:GetZ());";
					ret = user:GMCommand(cmd); -- 战士，野蛮冲撞
					wait(3);
				end
			else
				print("================unable to fullfil vecCheckKillNpcID================================================");
			end
        end
    end

	--任务结束的NPC ID
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
			-- 多数情况下，结束任务的npc会与开始任务的npc一致
			-- 导致接任务时已经设置过interact npc，及时交任务时不设置npc  也能过
			-- 因此测试结束npc 时，刷一个错误npcid

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

	-- 任务完成的BUF检查
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

	-- 需求变量ID1, 需求变量值1（判断相等）需要判断 Role, Scene, Quest
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

	-- 需求变量ID2, 需求变量值2（判断相等）需要判断 Role, Scene, Quest
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

	-- 货币奖励类型, 货币奖励数量
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
    local questcountmeanwhile = 1; -- 同时跑的任务数
    local nquestcount = 0;
	local runflag = true;
	local i;

    g_queststatus = {}; -- 每个任务的状态
    g_acceptstatus = {}; -- 检测接受任务时,每个index对应协程的状态
    g_completestatus = {}; -- 检测交任务时,每个index对应协程的状态
    g_traversstatus = {}; -- 检测遍历任务时,每个index对应协程的状态

	-- 遍历所有任务
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

	-- 配置项数目
	local nCount = 0;

	-- 是否重复接任务
	nCount = nCount + 1;

	-- 任务职业需求
	if questdata.nClassLimit ~= 4 then
		nCount = nCount + 1;
	end

	-- 性别需求
	if questdata.nSexLimit ~= 0 then
		nCount = nCount + 1;
	end

	 -- 关系需求
	 -- 暂不作考虑

	-- 判断前置任务1,不满足前置任务能否完成当前任务(如果在测试重复接受任务时已经使用Meet满足过条件，此项pass)
	if questdata.nPreQuestID1 ~= 0 then
		nCount = nCount + 1;
	end

	-- 判断前置任务2,不满足前置任务能否完成当前任务(如果在测试重复接受任务时已经使用Meet满足过条件，此项pass)
	if questdata.nPreQuestID2 ~= 0 then
		nCount = nCount + 1;
	end

	-- 开始任务的NPC ID
	if questdata.nStartNpcID ~= 0 then
		nCount = nCount + 1;
	end

	-- 开始任务的Item ID
	if questdata.nStartItemID ~= 0 then
		nCount = nCount + 1;
	end

	-- 任务最低等级需求
	if questdata.nMinLevelLimit ~= 0 then
		nCount = nCount + 1;
	end

	 -- 任务最高等级需求
	if questdata.nMaxLevelLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- 这个需要additem 和 useitem, 暂且注释掉
	-- 需求BUFF ID 和 LEVEL
	--if questdata.nBuffIDLimit ~= 0 then
	--	nCount = nCount + 1;
	--end

	-- 需求货币类型, 需求货币数量（不扣除）
	if questdata.nMoneyTypeLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- 需求Npc势力声望
	if questdata.nReputationForceID ~= -1 then

		-- 需求最低声望(在测试需求最高声望时需要pass)
		if questdata.nReputationMinLimit ~= 0 then
			nCount = nCount + 1;
		end

		-- 需求最高声望(在测试最低声望时需要pass)
		if questdata.nReputationMaxLimit ~= 0 then
			nCount = nCount + 1;
		end
	end

	-- 机器人在接受g2c_item_change时会甭，暂时把物品注掉
	-- 身上道具需求
	--for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
	--	if questdata.vecItemLimitID[nItemIndex] ~= 0 and questdata.vecItemLimitCnt[nItemIndex] ~= 0 then
	--		nCount = nCount + 1;
	--  end
	--end

	-- 需求变量ID1, 需求变量值1（判断相等）接任务时只判断Role Scene, 不考虑Quest
	if questdata.nLimitVarID1 ~= -1 then
		nCount = nCount + 1;
	end

	-- 需求变量ID2, 需求变量值2（判断相等）接任务时只判断Role Scene, 不考虑Quest
	if questdata.nLimitVarID2 ~= -1 then
		nCount = nCount + 1;
	end

	-- 接任务获得货币类型
	if questdata.nOfferMoneyType ~= 0 then
		nCount = nCount + 1;
	end

	return nCount;
end

