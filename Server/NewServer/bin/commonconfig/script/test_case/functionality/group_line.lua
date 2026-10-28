
TestCase.Group = {};

function TestCase.Group.Scene()
	-- Log in
    local user_name1 = "gpS1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1, 1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "gpS2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2, 1);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
	
	local user_name3 = "gpS3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3, 2);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

    local user_name4 = "gpS4"..os.date("%H%M%S");
    local user4, role4 = startup(user_name4, user_name4, 2);
    check(user4, "failed to create user");
    check(role4, "failed to create role");
	
	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user3id = role3:GetObjID();
	local user4id = role4:GetObjID();	
		
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();
	local user3sessionid = user3:GetSessionID();	
	local user4sessionid = user4:GetSessionID();
		
	local scene1 = role1:GetScene();
	local scene2 = role2:GetScene();
	local scene3 = role3:GetScene();
	local scene4 = role4:GetScene();
	
	check(scene1:GetGroupID() == 1, "error login group");
	check(scene2:GetGroupID() == 1, "error login group");
	check(scene3:GetGroupID() == 2, "error login group");
	check(scene4:GetGroupID() == 2, "error login group");
	
	check(scene1:GetSceneTempID() == scene2:GetSceneTempID() and scene1:GetSceneID() == scene2:GetSceneID(), "error scene")
	check(scene3:GetSceneTempID() == scene4:GetSceneTempID() and scene3:GetSceneID() == scene4:GetSceneID(), "error scene")

	
	-- Test complete; log out
	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
	cleanup(user4);
end

function TestCase.Group.Chat()
	local TestString = "abcdefg1234567898765432123456789";
    local user_name1 = "gpC1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1, 1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "gpC2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2, 1);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
	
	local user_name3 = "gpC3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3, 1);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

    local user_name4 = "gpC4"..os.date("%H%M%S");
    local user4, role4 = startup(user_name4, user_name4, 2);
    check(user4, "failed to create user");
    check(role4, "failed to create role");
	
	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user3id = role3:GetObjID();
	local user4id = role4:GetObjID();	
		
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();
	local user3sessionid = user3:GetSessionID();	
	local user4sessionid = user4:GetSessionID();
	
	ret = user1:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");
	wait(5);
	
	ret = user2:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");
	wait(5);
	
	ret = user3:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");
	wait(5);
	
	ret = user4:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");
	wait(5);
	
	JumpToSceneBySceneTempID(user3, 102, 0);	          
    --
    
    wait(5);
	local targetid = cctScene;
	
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	
	wait(10);
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user3sessionid, protocol.g2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	wait(10);
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user4sessionid, protocol.g2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	--
	wait(10);
	targetid = cctServer;
	
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	local retMsg = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message); --, user4sessionid, protocol.m2c_chat_message
	check(retMsg, "fail to recv chat_message");
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv all cctServer msg");
	end

	wait(5);
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user4sessionid, protocol.m2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	--
	wait(10);
	targetid = cctServer;
	
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	retMsg = recv_msg_and(5, user2sessionid, protocol.m2c_chat_message, user3sessionid, 
		protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message);
	check(retMsg, "fail to recv chat_message");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv all area msg");
	end

	--
	wait(10);
	targetid = user3id;
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(20, user3sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user2sessionid, protocol.m2c_chat_message);
	check(msg == nil, "fail to recv chat_message");

	--
	targetid = user4id;
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(5, user4sessionid, protocol.m2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	-- Test complete; log out
	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
	cleanup(user4);
end

function TestCase.Group.Team()
	local TestString = "abcdefg1234567898765432123456789";
    local user_name1 = "gpT1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1, 1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "gpT2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2, 1);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
	
	local user_name3 = "gpT3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3, 2);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user3id = role3:GetObjID();
		
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();
	local user3sessionid = user3:GetSessionID();	
	
    InviteToTeam(user1, role1, user2, role2);

    local retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_join, user2sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    local k, v;
    for k,v in pairs(retMsg) do
		check(v.msg, "failed to receive m2c_team_join");
		check(v.msg.byMemberCount == 2);
	end
    
    ret = g_RobotMessageHandler:DoTeamJoin(role1, user3id);
    check(ret, "failed to send create team");

    msg = recv_msg(30, user1sessionid, protocol.t2c_robot_disconnected);
    check(msg, "failed to  recv t2c_robot_disconnected");
	
	cleanup(user1);
	wait(5);
	
	user1, role1 = startup(user_name1, user_name1, 1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");
    
    ret = g_RobotMessageHandler:DoTeamJoin(role3, user1id);
    check(ret, "failed to send create team");
    
    msg = recv_msg(30, user3sessionid, protocol.t2c_robot_disconnected);
    check(msg, "failed to  recv t2c_robot_disconnected");

	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
end

function TestCase.Group.Line()
    local user_name1 = "gpL1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1, 1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "gpL2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2, 1);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
	
	local user_name3 = "gpL3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3, 2);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

    local user_name4 = "gpL4"..os.date("%H%M%S");
    local user4, role4 = startup(user_name4, user_name4, 2);
    check(user4, "failed to create user");
    check(role4, "failed to create role");
	
	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user3id = role3:GetObjID();
	local user4id = role4:GetObjID();	
		
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();
	local user3sessionid = user3:GetSessionID();	
	local user4sessionid = user4:GetSessionID();
	
	check(role1:GetSceneTempID() == role2:GetSceneTempID() and role1:GetSceneID() == role2:GetSceneID(), "error scene");
	check(role3:GetSceneTempID() == role4:GetSceneTempID() and role3:GetSceneID() == role4:GetSceneID(), "error scene");
	check(role1:GetSceneID() ~= role3:GetSceneID(), "error scene");

	ret = g_RobotMessageHandler:DoQueryLineReq(role1);
    check(ret, "failed to send QueryLineReq");

	local msg = recv_msg(30, user1sessionid, protocol.m2c_query_line_ack);
    check(msg, "failed to  recv t2c_robot_disconnected");
	
	ret = g_RobotMessageHandler:DoQueryLineReq(role3);
    check(ret, "failed to send QueryLineReq");

	local msg = recv_msg(30, user3sessionid, protocol.m2c_query_line_ack);
    check(msg, "failed to  recv t2c_robot_disconnected");
	
	ret = g_RobotMessageHandler:DoChangeLine(role1, 2);
	check(ret, "failed to send QueryLineReq");

	ret = g_RobotMessageHandler:DoChangeLine(role3, 2);
	check(ret, "failed to send QueryLineReq");

	wait(5);
	
	check(role1:GetSceneID() ~= role2:GetSceneID(), "error scene");
	check(role1:GetSceneTempID() == role2:GetSceneTempID(), "error scene");
	check(role3:GetSceneID() ~= role4:GetSceneID(), "error scene");
	check(role3:GetSceneTempID() == role4:GetSceneTempID(), "error scene");
	
	check(role1:GetSceneID() ~= role3:GetSceneID(), "error scene");
	check(role1:GetSceneID() ~= role4:GetSceneID(), "error scene");
	check(role2:GetSceneID() ~= role3:GetSceneID(), "error scene");
	check(role2:GetSceneID() ~= role4:GetSceneID(), "error scene");
	
	ret = g_RobotMessageHandler:DoChangeLine(role2, 2);
	check(ret, "failed to send QueryLineReq");

	ret = g_RobotMessageHandler:DoChangeLine(role4, 2);
	check(ret, "failed to send QueryLineReq");

	wait(5);
	
	check(role1:GetSceneID() == role2:GetSceneID(), "error scene");
	check(role1:GetSceneTempID() == role2:GetSceneTempID(), "error scene");
	check(role3:GetSceneID() == role4:GetSceneID(), "error scene");
	check(role3:GetSceneTempID() == role4:GetSceneTempID(), "error scene");
	
	check(role1:GetSceneID() ~= role3:GetSceneID(), "error scene");
	check(role1:GetSceneID() ~= role4:GetSceneID(), "error scene");
	check(role2:GetSceneID() ~= role3:GetSceneID(), "error scene");
	check(role2:GetSceneID() ~= role4:GetSceneID(), "error scene");

	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
    cleanup(user4);
end

function TestCase.Group.LineState()
	local ret, msg;
	local user_name = {};
	local user = {};
	local role = {};
	local session_id = {};

	for i = 1, 2 do
		user_name[i] = "LS"..os.date("%H%M%S")..i;
	    user[i], role[i] = startup(user_name[i], user_name[i], 1);
	    check(user[i], "failed to create user "..i);
		check(role[i], "failed to create role "..i);

		session_id[i] = user[i]:GetSessionID();

		ret = user[i]:GMCommand("Jump(3, 0, 1000, 1000)");
	    check(ret, "failed to execute gm command");

	    msg = recv_msg(30, session_id[i], protocol.g2c_enter_scene);
	    check(msg, "failed to  recv g2c_enter_scene");
	end

	ret = g_RobotMessageHandler:DoQueryLineReq(role[1]);
	check(ret, "failed to DoQueryLineReq");

	msg = recv_msg(30, session_id[1], protocol.m2c_query_line_ack);
	check(msg, "failed to recv m2c_query_line_ack");
	check(msg.dwSceneTempID == 3, "error dwSceneTempID");
	print('state '..msg.LineSceneData[0].byState);
	check(msg.LineSceneData[0].byState == lssNormal, "error LineSceneData[0].byState");

	for i = 3, 3 do
		user_name[i] = "LS"..os.date("%H%M%S")..i;
	    user[i], role[i] = startup(user_name[i], user_name[i], 1);
	    check(user[i], "failed to create user "..i);
		check(role[i], "failed to create role "..i);

		session_id[i] = user[i]:GetSessionID();

		ret = user[i]:GMCommand("Jump(3, 0, 1000, 1000)");
	    check(ret, "failed to execute gm command");

	    msg = recv_msg(30, session_id[i], protocol.g2c_enter_scene);
	    check(msg, "failed to  recv g2c_enter_scene");
	end

	ret = g_RobotMessageHandler:DoQueryLineReq(role[1]);
	check(ret, "failed to DoQueryLineReq");

	msg = recv_msg(30, session_id[1], protocol.m2c_query_line_ack);
	check(msg, "failed to recv m2c_query_line_ack");
	check(msg.dwSceneTempID == 3, "error dwSceneTempID");
	check(msg.LineSceneData[0].byState == lssBusy, "error LineSceneData[0].byState");

	for i = 4, 4 do
		user_name[i] = "LS"..os.date("%H%M%S")..i;
	    user[i], role[i] = startup(user_name[i], user_name[i], 1);
	    check(user[i], "failed to create user "..i);
		check(role[i], "failed to create role "..i);

		session_id[i] = user[i]:GetSessionID();

		ret = user[i]:GMCommand("Jump(3, 0, 1000, 1000)");
	    check(ret, "failed to execute gm command");

	    msg = recv_msg(30, session_id[i], protocol.g2c_enter_scene);
	    check(msg, "failed to  recv g2c_enter_scene");
	end

	ret = g_RobotMessageHandler:DoQueryLineReq(role[1]);
	check(ret, "failed to DoQueryLineReq");

	msg = recv_msg(30, session_id[1], protocol.m2c_query_line_ack);
	check(msg, "failed to recv m2c_query_line_ack");
	check(msg.dwSceneTempID == 3, "error dwSceneTempID");
	check(msg.LineSceneData[0].byState == lssFull, "error LineSceneData[0].byState");

	for i = 1, 4 do
		cleanup(user[i]);
	end

end