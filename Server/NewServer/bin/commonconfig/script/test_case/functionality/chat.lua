LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("chat_def.pkg");
LoadPackage("id_def.pkg");
------------------------------------------------------------------------------------------------------
-- case覆盖npc的聊天和role的聊天，每个case要测5种聊天类型

--对于role得聊天，不经过gs中转，直接发到ms的是：组队，私聊
--经过gs转发的是： 区域(region)，场景(scene)和全服广播(server)

--对于npc的聊天，gs直接处理的是区域(region)，场景(scene)，其余的全部发往ms

--聊天的类型为 Role Npc Doodad Missile Drop Guild Team Channel
--Channel 的类型为:System GM Scene Screen Server,
------------------------------------------------------------------------------------------------------

TestCase.Chat = {};

TestString = "abcdefg1234567898765432123456789";
function TestCase.Chat.RoleChat()

    -- 登陆
    local user_name1 = "testgs1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "testgs2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");

	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();

	-- 秘聊
    print("---------------------------------wisper---------------------------------------");	
	targetid = user2id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");

	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	
	check(msg, "fail to recv chat_message");
	check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
		
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

    -- 场景
    print("---------------------------------scene---------------------------------------");
	ret = user1:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");
	wait(10);
        
	ret = user2:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");
	wait(10);

	local targetid = cctScene;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	
	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_gsmsmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	--区域
	print("---------------------------------screen---------------------------------------");
	targetid = cctScreen;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send screen chat message");

	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_gsmsmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	-- 组队
    print("---------------------------------team---------------------------------------");	
	local team_name = user_name1.."team";
	
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");
    
	InviteToTeam(user2, role2, user1, role1, 0);
	local retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user2sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	targetid = teamid;
	
	ret = role1:Say(targetid, TestString);
	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");	

	wait(10);    -- chat interval

	--全服广播
    print("---------------------------------allserver---------------------------------------");	
	local targetid = cctServer;
	local ret = role1:Say(targetid, TestString);
	check(ret, "failed to send all server chat message");
	
	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	print("test complete");
	
	 --测试完成，登出
    cleanup(user1);
    cleanup(user2);
end

function TestCase.Chat.NpcChat()

    -- 登陆
    local user_name1 = "testgs1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "testgs2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");

    local user_name3 = "npc"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

	local user1id = role1:GetObjID();
	local user2id = role2:GetObjID();
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();

	ret = user1:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");
	wait(10);
        
	ret = user2:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");
	wait(10);

	ret = user3:GMCommand("Jump(114, 0, 35763, 18876, 19503)");
	check(ret, "failed to jump to scene");
	wait(10);

	-- 组队
	print("---------team-----------------");	
	local team_name = user_name1.."team";
	
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");
   
	InviteToTeam(user2, role2, user1, role1, 0);
	local retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user2sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	local targetid = teamid;
	summonnpc_and_say(user3, targetid, TestString);

	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
	-- 秘聊
	print("---------wisper-----------------");	
	targetid = user2id;
	summonnpc_and_say(user3, targetid, TestString);

	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	print(msg.szMessage);
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
	--区域
	print("---------screen-----------------");
	local oScene = role1:GetScene();
    local sceneTempID = oScene:GetSceneTempID();		
    local sceneID = oScene:GetSceneID();		
    
	targetid = cctScreen;
	summonnpc_and_say(user3, targetid, TestString);
	
	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
    -- 场景
	print("---------scene-----------------");

	targetid = cctScene;
	--用GM指令产生NPC说话
	summonnpc_and_say(user3, targetid, TestString);
	
	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");

	--全服广播
	print("---------allserver-----------------");	
	targetid = cctServer;
	
	summonnpc_and_say(user3, targetid, TestString);
	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");

	--测试完成，登出
    cleanup(user1);
    cleanup(user2);
    cleanup(user3);
end

function summonnpc_and_say(user, targetid, TestString)

	local command = "local oScene = SelfRole:GetScene(); local oNpc = oScene:SpawnNpc(1, SelfRole:GetLevel(), nqNormal, SelfRole:GetX(), SelfRole:GetY(), SelfRole:GetZ(), SelfRole:GetFaceDirection(), 0, nil);oNpc:Say(" ..targetid..",'" ..TestString.."');"
	
	ret = user:GMCommand(command);
	check(ret, "failed to jump to scene");
end


---------------------------------------------------------------------------------
--本Case负责不同场景和区域的交互聊天
--user1 2在同一区域，3 在同一场景的不同区域
--user 4 在与 1 2 3在不同的静态场景， user5与 1 2 3在不同的动态场景 
---------------------------------------------------------------------------------
function TestCase.Chat.MultiSceneChat()
	    
	-- 登陆
    local user_name1 = "testgs1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

    local user_name2 = "testgs2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role");
	
	local user_name3 = "testgs3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3);
    check(user3, "failed to create user");
    check(role3, "failed to create role");

    local user_name4 = "testgs4"..os.date("%H%M%S");
    local user4, role4 = startup(user_name4, user_name4);
    check(user4, "failed to create user");
    check(role4, "failed to create role");

    local user_name5 = "testgs5"..os.date("%H%M%S");
    local user5, role5 = startup(user_name5, user_name5);
    check(user5, "failed to create user");
    check(role5, "failed to create role");
	
	local user1id = role1:GetObjID();
	local user3id = role3:GetObjID();
	local user4id = role4:GetObjID();
	local user5id = role5:GetObjID();	
		
	local user1sessionid = user1:GetSessionID();	
	local user2sessionid = user2:GetSessionID();
	local user3sessionid = user3:GetSessionID();	
	local user4sessionid = user4:GetSessionID();
	local user5sessionid = user5:GetSessionID();	
		
	-- 用户跳地图
	--user1 2在同一区域，3 在同一场景的不同区域
	--user 4 在与 1 2 3在不同的静态场景， user5与 1 2 3在不同的动态场景 
	ret = user1:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");
	
	ret = user2:GMCommand("Jump xsc");
	check(ret, "failed to jump to scene");

	ret = user3:GMCommand("Jump(114,0,32000,8876)");
	check(ret, "failed to jump to scene");
    
    msg = recv_msg(20, user3sessionid, protocol.g2c_leave_scene, user3sessionid, protocol.g2c_enter_scene, user3sessionid, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_leave_scene");
		
	ret = user4:GMCommand("Jump(101,1,4200, 4240, 4367)");
	check(ret, "failed to jump to scene");

    msg = recv_msg(20, user4sessionid, protocol.g2c_leave_scene, user4sessionid, protocol.g2c_enter_scene, user4sessionid, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_leave_scene");
	
	ret = user5:GMCommand("Jump xs03");
	check(ret, "failed to jump to scene");
   
    msg = recv_msg(20, user5sessionid, protocol.g2c_leave_scene, user5sessionid, protocol.g2c_enter_scene, user5sessionid, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_leave_scene");
	
	-- 区域
    print("---------------------------------screen---------------------------------------");
	local oScene = role1:GetScene();
    local sceneTempID = oScene:GetSceneTempID();
    local sceneID = oScene:GetSceneID();

	-- 用户1说话, 2 能收到
	local targetid = cctScreen;
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");

	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_gsmsmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	-- 用户1说话, 3,4 5 收不到	
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(10, user3sessionid, protocol.g2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(10, user4sessionid, protocol.g2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	msg = recv_msg(10, user5sessionid, protocol.g2c_chat_message);
	check(msg == nil, "fail to recv chat_message");
	
	--全服广播
    print("---------------------------------allserver---------------------------------------");	
	
	-- 用户1 说话， 2 3 4 5都能收到
	targetid = cctServer;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send all server chat message");
	
	local retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
		
	local k, v;
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg, "fail to recv allserver msg");
			--check(v.msg.dwTargetID == targetid, "fail to receive msg with correct type");
			check(v.msg.szMessage == TestString, "fail to receive correct msg content");
			username = get_role_name_from_msmessage(v.msg);
			check(username == user_name1, "fail to receive msg from correct sender");
		end
	end
	
	-- 秘聊
    print("---------------------------------wisper---------------------------------------");	

	-- 用户1对3说话
	targetid = user3id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	-- 用户3能收到
	msg = recv_msg(10, user3sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	-- 用户2 4 5收不到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- 用户1对4说话
	targetid = user4id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	-- 用户4能收到
	msg = recv_msg(10, user4sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	-- 用户2 3 5收不到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- 用户1对5说话
	targetid = user5id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");

	-- 用户5能收到
	msg = recv_msg(10, user5sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	wait(30);
	-- 用户2 3 4收不到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- 场景
    print("---------------------------------scene---------------------------------------");

	-- 用户1说话, 2 3能收到
	targetid = cctScene;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");

	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.g2c_chat_message, user3sessionid, protocol.g2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
				check(msg.szMessage == TestString, "fail to receive correct msg content");
				username = get_role_name_from_gsmsmessage(msg);
				check(username == user_name1, "fail to receive msg from correct sender");
		end
	end
	
	-- 用户1说话, 4 5 收不到	
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	
	retMsgInfo = recv_msg_and(10, user4sessionid, protocol.g2c_chat_message, user5sessionid, protocol.g2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end

	-- 组队
	print("---------------------------------team---------------------------------------");
	-- 用户1 和 4 跨静态场景组队		
	local team_name = user_name1.."team";
	
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");
    
	InviteToTeam(user4, role4, user1, role1, 0);
	retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user4sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	targetid = teamid;
	
	-- 用户1 向队伍说话， 4 能收到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");
		
	msg = recv_msg(10, user4sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");	

	-- 用户2 3 5收不到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");	
	retMsg = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
    check(retMsg, "failed to received chat msg");

	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end

	-- 再邀请与1在统一场景的3加入队伍
	
	InviteToTeam(user3, role3, user1, role1, 0);
	retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user3sessionid, protocol.m2c_team_add_member, user4sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	-- 用户1 向队伍说话，3 4 能收到
	ret = role1:Say(targetid, TestString);
	retMsg = recv_msg_and(10, user3sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message);
	check(retMsg, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
				check(msg.szMessage == TestString, "fail to receive correct msg content");
				username = get_role_name_from_gsmsmessage(msg);
				check(username == user_name1, "fail to receive msg from correct sender");
		end
	end
	
	-- 用户2 5收不到
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");	
	retMsg = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsg, "fail to recv chat_message");	

	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end	
	
	-- 测试完成，登出
	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
	cleanup(user4);
    cleanup(user5);
end



