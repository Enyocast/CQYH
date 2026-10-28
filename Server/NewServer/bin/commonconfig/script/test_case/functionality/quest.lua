LoadPackage("id_def.pkg");
LoadPackage("quest_list.pkg");
LoadPackage("quest_def.pkg");
LoadPackage("variable.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("robot_message_handler.pkg")
LoadPackage("master.pkg")

TestCase.Quest = {};

function _TestQuest(quest_id)
	local quest_data = CDataManager_QUEST_DATA_:GetInstance():GetData(quest_id);
	check(quest_data, "failed to get quest data "..quest_id);

	if quest_data.nClassLimit ~= nil then
		local user_name = "QstCls"..os.date("%H%M%S");
		local user, role = startup(user_name, user_name);
		local session_id = user:GetSessionID();

		_MeetAcceptQuestCondition(user, role, quest_data);

		cleanup(user);
	end
end

function TestCase.Quest.AcceptQuest()
    local ret, msg;
    local user_name = "AcpQuest"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    local session_id = user:GetSessionID();

	-- error quest id
    ret = user:AcceptQuest(111111, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

	-- error quest id
    ret = user:AcceptQuest(-1, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

	-- no start npc
    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestNpcTooFar, "failed to recv errQuestNpcTooFar ");

	-- No start NPC: this is not configured yet, so leave it commented out
	ret = user:GMCommand("SummonNpc(6009)");
	check(ret, "failed to summon npc 6009");

	msg = recv_msg(30, session_id, protocol.g2c_char_appear);
	check(msg, "failed to recv g2c_char_appear");
	local npc_id = msg.stAppearData.dwCharID;

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestNpcTooFar, "failed to recv errQuestNpcTooFar");

	-- wrong level
	ret = user:InteractWithNpc(npc_id);
	check(ret, "failed to interact with npc");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestLevel, "failed to recv errQuestLevel");

	-- not enough money
	ret = user:GMCommand("AddExp(530000)");
	check(ret, "failed to add exp");

	ret = user:GMCommand("SetMoney(1, 0)");
	check(ret, "failed to add exp");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestNotEnoughMoney, "failed to recv errQuestNotEnoughMoney");

	-- low reputation
	ret = user:GMCommand("AddMoney(1, 1000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	ret = user:GMCommand("SetReputation(0, 0)");
	check(ret, "failed to set reputation");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestLowReputation, "failed to recv errQuestLowReputation");

	-- high reputation
	ret = user:GMCommand("SetReputation(0, 120)");
	check(ret, "failed to set reputation");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestHighReputation, "failed to recv errQuestHighReputation");

	-- accept successfully
	ret = user:GMCommand("SetReputation(0, 80)");
	check(ret, "failed to set reputation");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_money_change);
    check(msg.nMoneyType == 1, "failed to recv g2c_money_change");
    check(msg.nMoney == 2000, "failed to recv g2c_money_change");

    msg = recv_msg(30, session_id, protocol.g2c_accept_quest);
    check(msg.nQuestID == 10, "failed to recv g2c_accept_quest");

    cleanup(user)
end

function TestCase.Quest.CompleteQuest()
    local ret, msg;
    local user_name = "ComQuest"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    local session_id = user:GetSessionID();

	-- complete error quest id
	ret = user:CompleteQuest(1, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

	-- complete error quest id
	ret = user:CompleteQuest(-1, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

	-- complete error quest id
	ret = user:CompleteQuest(0, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

	-- accept quest
	ret = user:GMCommand("SummonNpc(6009)");
	check(ret, "failed to summon npc 6009");

	msg = recv_msg(30, session_id, protocol.g2c_char_appear);
	check(msg, "failed to recv g2c_char_appear");
	local npc_id = msg.stAppearData.dwCharID;

	ret = user:InteractWithNpc(npc_id);
	check(ret, "failed to interact with npc");

	ret = user:GMCommand("AddExp(530000)");
	check(ret, "failed to add exp");

	ret = user:GMCommand("SetReputation(0, 80)");
	check(ret, "failed to set reputation");

    ret = user:AcceptQuest(10, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id, protocol.g2c_accept_quest);
    check(msg.nQuestID == 10, "failed to recv g2c_accept_quest");

	ret = user:GMCommand("SetMoney(1, 0)");
	check(ret, "failed to set money");

    msg = recv_msg(30, session_id, protocol.g2c_money_change);
    check(msg.nMoneyType == 1, "failed to recv g2c_money_change");
    check(msg.nMoney == 0, "failed to recv g2c_money_change");

	local old_exp = role:GetExp();
	print("old_exp "..old_exp);

	ret = user:CompleteQuest(10, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id, protocol.g2c_money_change);
    check(msg.nMoneyType == 1, "failed to recv g2c_money_change");
    check(msg.nMoney == 1000, "failed to recv g2c_money_change");

    msg = recv_msg(30, session_id, protocol.g2c_exp_change);
    print("new exp = "..msg.dwExp);
    check(msg.dwExp == old_exp + 1000, "failed to recv g2c_exp_change");

    msg = recv_msg(30, session_id, protocol.g2c_modify_reputation);
    check(msg.byForceID == 0, "failed to recv g2c_modify_reputation");
    check(msg.shReputation == 130, "failed to recv g2c_modify_reputation");

    msg = recv_msg(30, session_id, protocol.g2c_complete_quest);
    check(msg.nQuestID == 10, "failed to recv g2c_complete_quest");

	-- complete again
	ret = user:CompleteQuest(10, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errUnknownError, "failed to recv errUnknownError");

    cleanup(user)
end

function TestCase.Quest.InteractWithNpc()
    local ret, msg
    local user_name = "diag"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    local session_id = user:GetSessionID();

    ret = user:GMCommand("SummonNpc(2)");
    check(ret, "failed to summon npc");

    msg = recv_msg(3, session_id, protocol.g2c_char_appear);
    check(msg, "Npc appear fail.");
    local npc_id = msg.stAppearData.dwCharID;

    ret = user:InteractWithNpc(npc_id);
    check(ret, "failed to interact with npc");

    msg = recv_msg(10, session_id, protocol.g2c_interact_result);
    check(msg, "Fail to recv g2c_interact_result.")
    check(msg.szDialogContent == '<#Dft>', "Check diag default msg fail.")

    cleanup(user)
end

function getquestcompleteconfigcount(quest_data)
	local nCount = 0;

	-- Quest class requirement
	if quest_data.nClassLimit ~= 4 then
		nCount = nCount + 1;
	end

	-- Gender requirement
	if quest_data.nSexLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- Check kill count before checking the quest NPC to avoid moving too far from it while casting skills
	for nNpcIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if  quest_data.vecCheckKillNpcID[nNpcIndex] ~= 0 and quest_data.vecCheckKillNpcCnt[nNpcIndex] ~= 0 then
			nCount = nCount + 1;
        end
    end

	--Quest completion NPC ID
	if quest_data.nFinishNpc ~= 0 then
		nCount = nCount + 1;
	end

	-- Check buffs at quest completion
	if quest_data.nCheckBuffID ~= 0 then
		nCount = nCount + 1;
	end

	-- Check quest items
    for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if quest_data.vecCheckItemID[nItemIndex] ~= 0 then
            nCount = nCount + 1;
        end
    end

	-- Required variable ID 1 and value 1 (equality check); check Role, Scene and Quest
	if quest_data.nCheckVarID1 ~= -1 then
		nCount = nCount + 1;
	end

	-- Required variable ID 2 and value 2 (equality check); check Role, Scene and Quest
	if quest_data.nCheckVarID2 ~= -1 then
		nCount = nCount + 1;
	end

	-- Reward currency type and amount
	if quest_data.nAwardMoneyType ~= 0 and quest_data.nAwardMoneyAmount ~= 0 then
		nCount = nCount + 1;
	end

	return nCount;
end

function TestCase.ShareQuest()
	-- Configure quests 10 and 11 as shareable and 12 and 13 as non-shareable
	--The user accepts only quests 10 and 12, not 11 or 13
	local msg;
	local questdata;

	local username1 = "ShQ1"..os.date("%H%M%S");
	user1, role1 = startup(username1, username1);
	check(user1, "fail to login");
	check(role1, "fail to login");
	local session_id1 = user1:GetSessionID();

	local username2 = "ShQ2"..os.date("%H%M%S");
	user2, role2 = startup(username2, username2);
	check(user2, "fail to login");
	check(role2, "fail to login");
	local session_id2 = user2:GetSessionID();

	-- Create conditions for user 1 to meet quest 10 requirements
	questdata = GetQuestByID(10);
	check(questdata, "fail to get quest");
	_AcceptQuestWithoutConditionIndex(user1, role1, questdata, 0, 1, qatNpc, 0);

	-- Create conditions for user 1 to meet quest 12 requirements
	questdata = GetQuestByID(12);
	check(questdata, "fail to get quest");
	_AcceptQuestWithoutConditionIndex(user1, role1, questdata, 0, 1, qatNpc, 0);

	print("--------------no team---------------------------------");
	-- Share without a team
	ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestNoShareTeam, "failed to recv errQuestNoShareTeam");

 	print("--------------create team---------------------------------");
    -- Team
    local team_name = username1.."team";
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");

	print("--------------create team success---------------------------------");
    -- Request a shared quest when the team has only one member
    ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestShareUnavailable, "failed to recv errQuestShareUnavailable");

	print("--------------enter team---------------------------------");
    --Join the team
   	InviteToTeam(user2, role2, user1, role1, 0);
	local retMsg = recv_msg_and(30, session_id1, protocol.m2c_team_add_member, session_id2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    -- With more than two team members, request sharing of an accepted non-shareable quest
    ret = user1:ShareQuest(12, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestCannotShare, "failed to recv errQuestCannotShare");

	print("--------------share no accepted quest---------------------------------");
    -- With more than two team members, request an unaccepted shareable quest
    --(The server returns unknownerror and does not currently kick the player; if it does in future, this message will not arrive)

    ret = user1:ShareQuest(11, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
	check(msg.nErrCode == error_code.errQuestAlreadyCompleted, "failed to recv errUnknownError");

	-- Make user 2 meet the acceptance requirements and request the shared quest ID
	questdata = GetQuestByID(10);
	_AcceptQuestWithoutConditionIndex(user2, role2, questdata, 0, -1, qatNpc, 0);

    ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id2, protocol.g2c_share_quest);
    check(msg, "fail to recv share quest");

	-- User 2 confirms the quest
	ret = user2:AcceptQuest(msg.nQuestID, qatShare, msg.nSrcID)
	check(ret, "fail to share quest ack");

    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "fail to recv share quest");

	print("--------------jump scene--------------------------------");
	-- User 2 changes scene
	ret = user2:GMCommand("Jump(102,0)");
	check(ret, "failed to jump to scene");

	 msg = recv_msg(30, session_id2, protocol.g2c_leave_scene);
	 check(msg, "failed to  recv g2c_leave_scene");

     msg = recv_msg(30, session_id2, protocol.g2c_enter_scene);
     check(msg, "failed to  recv g2c_enter_scene");

     msg = recv_msg(30, session_id2, protocol.g2c_char_appear);
     check(msg, "failed to  recv g2c_char_appear");

 	print("--------------not in the same scene--------------------------------");
    -- With more than two team members in different scenes, check whether the shared quest is received
	ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id2, protocol.g2c_error_notify);
    check(msg == nil, "fail to recv share quest");

    cleanup(user1);
    cleanup(user2);
end


function TestCase.PublishQuest()				-- Master-apprentice shared quest

    local user_name1 = "Pub1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

    local user_name2 = "Pub2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    local session_id2 = user2:GetSessionID();
	local roleid2 = role2:GetObjID();

	-- Become an apprentice

	-- Become a master
	BecomeMasterByMyself(user1, role1);
	wait(5);

	-- Submit application
	TestSubmitApp(role1, session_id1, role2, session_id2);

	-- Accept the apprenticeship
	TestAgreeApp(role1, session_id1, role2, session_id2);

	local ret = user1:ShareQuest(203, qatPublish);
	check(ret, "fail to publish quest");

	-- Check the shared quest response
	msg = recv_msg(5, session_id2, protocol.m2c_publish_quest);
	check(msg, "failed to recv m2c_publish_quest");
	check(msg.nQuestID == 203,"fail to recv correct quest id  ");
	check(msg.dwMasterRoleID == roleid1,"fail to recv correct roleid  ");

	-- Confirm sharing
	ret = user2:ConfirmPublishQuest(203, roleid1);
	check(ret, "fail to confirm quest");

	-- Check the quest acceptance response
    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "failed to recv g2c_accept_quest");
	check(msg.nQuestID == 203,"fail to recv correct quest id  ");

end

-- Test new quest and reward types
-- Includes timed quests
-- Award items on quest completion
-- Quest 20 is timed and awards title 1 on completion
function TestCase.Quest.QuestTimeLimit()
	local user_name1 = "QuestTime1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local user_name2 = "QuestTime2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    local session_id2 = user2:GetSessionID();
	local roleid2 = role2:GetObjID();

	local ret, msg;

	-- User 1 confirms, then waits 25 seconds before completing the quest
	ret = user1:AcceptQuest(20, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

	wait(25);	-- Quest time limit: 20 seconds

	ret = user1:CompleteQuest(20, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestTimeLimit, "failed to recv errUnknownError");

	-- User 2 confirms, then waits 15 seconds before completing the quest
	ret = user2:AcceptQuest(20, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

	wait(15);	-- Quest time limit: 20 seconds

	local ret = user2:CompleteQuest(20, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id2, protocol.g2c_complete_quest);
    check(msg, "failed to recv g2c_complete_quest");
end

-- Test new quest and reward types
-- Quest 21 is a conversation quest that awards 300 soul on completion
function TestCase.Quest.QuestChat()
	local user_name1 = "QuestChat"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- Spawn an NPC
	ret = user1:GMCommand("SummonNpc(6085)");
	check(ret, "failed to summon npc 6085");

	msg = recv_msg(30, session_id1, protocol.g2c_char_appear);
	check(msg, "failed to recv g2c_char_appear");
	npc_id = msg.stAppearData.dwCharID;

	ret = user1:InteractWithNpc(npc_id);
	check(ret, "failed to interact with npc");

	ret = user1:AcceptQuest(21, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

	ret = user1:TalkToNpc(21, npc_id);
	check(ret, "failed to talk to npc");

	wait(3);

	-- Complete the quest
	local ret = user1:CompleteQuest(21, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_complete_quest);
    check(msg, "failed to recv g2c_complete_quest");
end

-- Test new quest and reward types
-- Includes exploration quests
-- Award soul on quest completion
-- Quest 22 is a search quest; grid coordinates:
function TestCase.Quest.QuestExplor()
	local user_name1 = "QuestTime1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- User 1 completes the quest
	ret = user1:AcceptQuest(21, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

   	ret = user1:CompleteQuest(21, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_error_notify);
    check(msg, "failed to recv g2c_error_notify");

    ret = user1:GMCommand("Jump(1, 0, 12000, 12000)");
	check(ret, "failed to jump to scene");

     msg = recv_msg(30, session_id1, protocol.g2c_leave_scene);
	 check(msg, "failed to  recv g2c_leave_scene");

     msg = recv_msg(30, session_id1, protocol.g2c_enter_scene);
     check(msg, "failed to  recv g2c_enter_scene");

     msg = recv_msg(30, session_id1, protocol.g2c_char_appear);
     check(msg, "failed to  recv g2c_char_appear");

     ret = user1:ExploreZone();
     check(ret, "failed to send explorezone");

     wait(3);

	-- Complete the quest and receive soul
	local ret = user2:CompleteQuest(21, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg_and(30, session_id1, protocol.g2c_complete_quest, session_id1, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_complete_quest");
end

-- Test new quest types
-- Item ID 101 runs a script that completes quest 101

-- Test new quest types
-- Includes tutorial quests
-- Quest 23 is a client-variable quest
function TestCase.Quest.QuestClientVar()
	local user_name1 = "QuestClient1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- User 1 accepts the quest
	ret = user1:AcceptQuest(23, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

   	ret = user1:CompleteQuest(23, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_error_notify);
    check(msg, "failed to recv g2c_error_notify");
    check(msg.nErrCode == error_code.errQuestLimitVar, "failed to recv errQuestLimitVar");

	-- Variable 0 is a client variable
	ret = user1:UpdateClientVariable(1,1);
	check(ret, "failed to update client value");
	wait(10);

	-- Variable 1 is a client variable
	ret = user1:GMCommand("SetQV(23, 1, 1)");
	check(ret, "failed to summon npc 6009");
	wait(10);

   	ret = user1:CompleteQuest(23, 0);
	check(ret, "failed to complete quest");

	-- Receive the quest completion message
    msg = recv_msg(30, session_id1, protocol.g2c_complete_quest);
    check(msg, "failed to recv g2c_complete_quest");
    check(msg.nQuestID == 23, "failed to recv g2c_complete_quest");
end

function TestCase.Quest.AcceptQuest283()
	local user_name1 = "QuestClient1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	ret = user1:AcceptQuest(283, qatNpc, 0);
    check(ret, "failed to accept quest");

    msg = recv_msg(30, session_id1, protocol.g2c_accept_quest);
    check(msg.nQuestID == 283, "failed to recv g2c_accept_quest");
end

function TestCase.Quest.TestDailyQuest()
	local user_name1 = "DailyQuest"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	ret = user1:GenerateDailyQuest();
    check(ret, "failed to generate quest");

    msg = recv_msg(10, session_id1, protocol.g2c_brush_daily_quest);
    check(msg == nil, "failed to recv correct g2c_brush_daily_quest");

	local ret = user1:GMCommand("SetLevel(25)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

	ret = user1:GenerateDailyQuest();
    check(ret, "failed to generate quest");

    msg = recv_msg(10, session_id1, protocol.g2c_brush_daily_quest);
    check(msg, "failed to recv correct g2c_brush_daily_quest");

	wait(10);

    --Test complete; log out
    cleanup(user1);

	--Log in again and test data unpacking
    user1, role1 = startup(user_name1, user_name1);

	wait(10);
    cleanup(user1);
end

function TestCase.Quest.TestCircleQuest()
	local user_name1 = "Circle"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret = user1:GenerateCircleQuest();
	check(ret, "failed to generate quest");

	--local msg = recv_msg(10, session_id1, protocol.g2c_notify_next_circle_quest);
    --check(msg == nil, "failed to recv correct g2c_notify_next_circle_quest");

	--local ret = user1:GMCommand("SetLevel(25)");
    --check(ret, "exec GMCommand SetLevel error: user1");

	--wait(1);

	--ret = user1:GenerateCircleQuest();
	--check(ret, "failed to generate quest");

	--msg = recv_msg(10, session_id1, protocol.g2c_notify_next_circle_quest);
    --check(msg == nil, "failed to recv correct g2c_notify_next_circle_quest");
    cleanup(user1);
end

function TestCase.Quest.TestAward()

	local user_name1 = "testaward110";
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	ret = user1:GMCommand("SummonNpc(6105)");
	check(ret, "failed to summon npc 6105");

	msg = recv_msg(30, session_id1, protocol.g2c_char_appear);
	check(msg, "failed to recv g2c_char_appear");
	local npc_id = msg.stAppearData.dwCharID;

	ret = user1:InteractWithNpc(npc_id);
	check(ret, "failed to interact with npc");

	msg = recv_msg(30, session_id1, protocol.g2c_interact_result);
	check(msg, "failed to recv g2c_interact_result");

	wait(2);

    --ret = user1:SelectDialogOption(2);  -- Claim batch reward
	--check(msg, "failed to Select Dialog Option");

	--wait(10);

	--msg = recv_msg(10, session_id1, protocol.g2c_item_change);
	--check(msg, "failed to receive g2c_item_change");
    --check(msg.stItem.nTemplateID==3194, "failed to create correct item");

    ret = user1:AwardUseNumber("131129171328494787900595075918");	   -- Claim promotion-code reward
	check(msg, "failed to send AwardUseNumber");

	wait(20);

	msg = recv_msg(10, session_id1, protocol.g2c_item_change);
	check(msg, "failed to receive g2c_item_change");
    check(msg.stItem.nTemplateID==3194, "failed to create correct item");

end
