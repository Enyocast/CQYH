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

	-- no start npc 此项暂时没有配，先注掉
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

	-- 任务职业需求
	if quest_data.nClassLimit ~= 4 then
		nCount = nCount + 1;
	end

	-- 性别需求
	if quest_data.nSexLimit ~= 0 then
		nCount = nCount + 1;
	end

	-- 杀怪数检查(放在检查任务npc前面，防止由于释放技能，移动距离过大，导致与npc距离过大)
	for nNpcIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if  quest_data.vecCheckKillNpcID[nNpcIndex] ~= 0 and quest_data.vecCheckKillNpcCnt[nNpcIndex] ~= 0 then
			nCount = nCount + 1;
        end
    end

	--任务结束的NPC ID
	if quest_data.nFinishNpc ~= 0 then
		nCount = nCount + 1;
	end

	-- 任务完成的BUF检查
	if quest_data.nCheckBuffID ~= 0 then
		nCount = nCount + 1;
	end

	-- 任务物品检查
    for nItemIndex = 0, MAX_CONDITION_PER_QUEST - 1 do
        if quest_data.vecCheckItemID[nItemIndex] ~= 0 then
            nCount = nCount + 1;
        end
    end

	-- 需求变量ID1, 需求变量值1（判断相等）需要判断 Role, Scene, Quest
	if quest_data.nCheckVarID1 ~= -1 then
		nCount = nCount + 1;
	end

	-- 需求变量ID2, 需求变量值2（判断相等）需要判断 Role, Scene, Quest
	if quest_data.nCheckVarID2 ~= -1 then
		nCount = nCount + 1;
	end

	-- 货币奖励类型, 货币奖励数量
	if quest_data.nAwardMoneyType ~= 0 and quest_data.nAwardMoneyAmount ~= 0 then
		nCount = nCount + 1;
	end

	return nCount;
end

function TestCase.ShareQuest()
	-- 10, 11配成共享任务，12, 13 配成非共享任务
	--用户只接10 12, 不接11 13
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

	-- 创造条件让1满足任务10
	questdata = GetQuestByID(10);
	check(questdata, "fail to get quest");
	_AcceptQuestWithoutConditionIndex(user1, role1, questdata, 0, 1, qatNpc, 0);

	-- 创造条件让1满足任务12
	questdata = GetQuestByID(12);
	check(questdata, "fail to get quest");
	_AcceptQuestWithoutConditionIndex(user1, role1, questdata, 0, 1, qatNpc, 0);

	print("--------------no team---------------------------------");
	-- 没有队伍的时候共享
	ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestNoShareTeam, "failed to recv errQuestNoShareTeam");

 	print("--------------create team---------------------------------");
    -- 组队
    local team_name = username1.."team";
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");

	print("--------------create team success---------------------------------");
    -- 队伍只有1个人时，申请共享任务
    ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestShareUnavailable, "failed to recv errQuestShareUnavailable");

	print("--------------enter team---------------------------------");
    --加入队伍
   	InviteToTeam(user2, role2, user1, role1, 0);
	local retMsg = recv_msg_and(30, session_id1, protocol.m2c_team_add_member, session_id2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    -- 队伍人数大于2时，申请共享接过的非共享任务
    ret = user1:ShareQuest(12, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestCannotShare, "failed to recv errQuestCannotShare");

	print("--------------share no accepted quest---------------------------------");
    -- 队伍人数大于2时，申请未接过的共享任务
    --(此种情况服务器返回unknownerror,暂时不踢人，如果以后踢人的话，此消息收不到)

    ret = user1:ShareQuest(11, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id1, protocol.g2c_error_notify);
	check(msg.nErrCode == error_code.errQuestAlreadyCompleted, "failed to recv errUnknownError");

	-- 创造条件让用户2满足接任务条件，申请接受共享任务ID
	questdata = GetQuestByID(10);
	_AcceptQuestWithoutConditionIndex(user2, role2, questdata, 0, -1, qatNpc, 0);

    ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id2, protocol.g2c_share_quest);
    check(msg, "fail to recv share quest");

	-- 用户2 确认任务
	ret = user2:AcceptQuest(msg.nQuestID, qatShare, msg.nSrcID)
	check(ret, "fail to share quest ack");

    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "fail to recv share quest");

	print("--------------jump scene--------------------------------");
	-- 用户2跳场景
	ret = user2:GMCommand("Jump(102,0)");
	check(ret, "failed to jump to scene");

	 msg = recv_msg(30, session_id2, protocol.g2c_leave_scene);
	 check(msg, "failed to  recv g2c_leave_scene");

     msg = recv_msg(30, session_id2, protocol.g2c_enter_scene);
     check(msg, "failed to  recv g2c_enter_scene");

     msg = recv_msg(30, session_id2, protocol.g2c_char_appear);
     check(msg, "failed to  recv g2c_char_appear");

 	print("--------------not in the same scene--------------------------------");
    -- 队伍人数大于2，但是不在同一场景， 检测能否收到共享任务
	ret = user1:ShareQuest(10, qatShare);
	check(ret, "fail to share quest");

    msg = recv_msg(5, session_id2, protocol.g2c_error_notify);
    check(msg == nil, "fail to recv share quest");

    cleanup(user1);
    cleanup(user2);
end


function TestCase.PublishQuest()				-- 师徒共享任务

    local user_name1 = "Pub1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

    local user_name2 = "Pub2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    local session_id2 = user2:GetSessionID();
	local roleid2 = role2:GetObjID();

	-- 拜师

	-- 变成师傅
	BecomeMasterByMyself(user1, role1);
	wait(5);

	-- 提交申请
	TestSubmitApp(role1, session_id1, role2, session_id2);

	-- 同意拜师
	TestAgreeApp(role1, session_id1, role2, session_id2);

	local ret = user1:ShareQuest(203, qatPublish);
	check(ret, "fail to publish quest");

	-- 检查共享任务消息回包
	msg = recv_msg(5, session_id2, protocol.m2c_publish_quest);
	check(msg, "failed to recv m2c_publish_quest");
	check(msg.nQuestID == 203,"fail to recv correct quest id  ");
	check(msg.dwMasterRoleID == roleid1,"fail to recv correct roleid  ");

	-- 确认共享
	ret = user2:ConfirmPublishQuest(203, roleid1);
	check(ret, "fail to confirm quest");

	-- 检查接任务的回包
    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "failed to recv g2c_accept_quest");
	check(msg.nQuestID == 203,"fail to recv correct quest id  ");

end

-- 测试任务系统的新增任务类型和新增任务奖励类型
-- 包括：限时任务
-- 完成任务时奖励道具
-- 任务20为限时任务，完成以后奖励称号1
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

	-- 用户1 确认延时25秒交任务
	ret = user1:AcceptQuest(20, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

	wait(25);	-- 限时任务20秒

	ret = user1:CompleteQuest(20, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errQuestTimeLimit, "failed to recv errUnknownError");

	-- 用户2 确认延时15秒交任务
	ret = user2:AcceptQuest(20, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id2, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

	wait(15);	-- 限时任务20秒

	local ret = user2:CompleteQuest(20, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id2, protocol.g2c_complete_quest);
    check(msg, "failed to recv g2c_complete_quest");
end

-- 测试任务系统的新增任务类型和新增任务奖励类型
-- 任务21为谈话任务,完成以后增加300魂
function TestCase.Quest.QuestChat()
	local user_name1 = "QuestChat"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- 召唤npc
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

	-- 交任务
	local ret = user1:CompleteQuest(21, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_complete_quest);
    check(msg, "failed to recv g2c_complete_quest");
end

-- 测试任务系统的新增任务类型和新增任务奖励类型
-- 包括：探索任务
-- 完成任务时奖励魂
-- 任务22为搜索任务，grid坐标为
function TestCase.Quest.QuestExplor()
	local user_name1 = "QuestTime1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- 用户1 交任务
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

	-- 交任务，收获魂
	local ret = user2:CompleteQuest(21, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg_and(30, session_id1, protocol.g2c_complete_quest, session_id1, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_complete_quest");
end

-- 测试任务系统的新增任务类型
-- 物品id为101，挂脚本,完成任务101

-- 测试任务系统的新增任务类型
-- 包括：引导任务
-- 任务23为客户端变量任务
function TestCase.Quest.QuestClientVar()
	local user_name1 = "QuestClient1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    local session_id1 = user1:GetSessionID();
	local roleid1 = role1:GetObjID();

	local ret, msg;

	-- 用户1 接任务
	ret = user1:AcceptQuest(23, qatNpc, 0)
	check(ret, "fail to send acceptquest");

    msg = recv_msg(5, session_id1, protocol.g2c_accept_quest);
    check(msg, "fail to recv accept quest");

   	ret = user1:CompleteQuest(23, 0);
	check(ret, "failed to complete quest");

    msg = recv_msg(30, session_id1, protocol.g2c_error_notify);
    check(msg, "failed to recv g2c_error_notify");
    check(msg.nErrCode == error_code.errQuestLimitVar, "failed to recv errQuestLimitVar");

	-- 0号变量为客户端变量
	ret = user1:UpdateClientVariable(1,1);
	check(ret, "failed to update client value");
	wait(10);

   	-- 1号变量为客户端变量
	ret = user1:GMCommand("SetQV(23, 1, 1)");
	check(ret, "failed to summon npc 6009");
	wait(10);

   	ret = user1:CompleteQuest(23, 0);
	check(ret, "failed to complete quest");

   	-- 收任务完成的消息
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

    --测试完成，登出
    cleanup(user1);

	--再次上线，测试数据的解包
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

    --ret = user1:SelectDialogOption(2);  -- 批次领奖
	--check(msg, "failed to Select Dialog Option");

	--wait(10);

	--msg = recv_msg(10, session_id1, protocol.g2c_item_change);
	--check(msg, "failed to receive g2c_item_change");
    --check(msg.stItem.nTemplateID==3194, "failed to create correct item");

    ret = user1:AwardUseNumber("131129171328494787900595075918");	   -- 推广码领奖
	check(msg, "failed to send AwardUseNumber");

	wait(20);

	msg = recv_msg(10, session_id1, protocol.g2c_item_change);
	check(msg, "failed to receive g2c_item_change");
    check(msg.stItem.nTemplateID==3194, "failed to create correct item");

end
