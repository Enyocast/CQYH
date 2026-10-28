LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("chat_def.pkg");
LoadPackage("id_def.pkg");
------------------------------------------------------------------------------------------------------
-- Cases cover NPC and role chat; each case tests five chat types

--Role team chat and private chat go directly to MS without GS forwarding
--GS forwards region, scene, and server-wide chat

--GS handles NPC region and scene chat directly; all other NPC chat goes to MS

--Chat types: Role, Npc, Doodad, Missile, Drop, Guild, Team, Channel
--Channel types: System, GM, Scene, Screen, Server
------------------------------------------------------------------------------------------------------

TestCase.Chat = {};

TestString = "abcdefg1234567898765432123456789";
function TestCase.Chat.RoleChat()

    -- Log in
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

	-- Private chat
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

    -- Scene
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

	--Region
	print("---------------------------------screen---------------------------------------");
	targetid = cctScreen;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send screen chat message");

	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_gsmsmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	-- Team
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

	--Server-wide broadcast
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
	
	 --Test complete; log out
    cleanup(user1);
    cleanup(user2);
end

function TestCase.Chat.NpcChat()

    -- Log in
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

	-- Team
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
	
	-- Private chat
	print("---------wisper-----------------");	
	targetid = user2id;
	summonnpc_and_say(user3, targetid, TestString);

	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	print(msg.szMessage);
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
	--Region
	print("---------screen-----------------");
	local oScene = role1:GetScene();
    local sceneTempID = oScene:GetSceneTempID();		
    local sceneID = oScene:GetSceneID();		
    
	targetid = cctScreen;
	summonnpc_and_say(user3, targetid, TestString);
	
	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	
    -- Scene
	print("---------scene-----------------");

	targetid = cctScene;
	--Make an NPC speak using a GM command
	summonnpc_and_say(user3, targetid, TestString);
	
	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");

	--Server-wide broadcast
	print("---------allserver-----------------");	
	targetid = cctServer;
	
	summonnpc_and_say(user3, targetid, TestString);
	msg = recv_msg(10, user2sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	check(msg.szMessage == TestString, "fail to receive correct msg content");

	--Test complete; log out
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
--This case tests chat across scenes and regions
--Users 1 and 2 are in the same region; user 3 is in another region of the same scene
--User 4 is in a different static scene from users 1, 2 and 3; user 5 is in a different dynamic scene
---------------------------------------------------------------------------------
function TestCase.Chat.MultiSceneChat()
	    
	-- Log in
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
		
	-- Users change maps
	--Users 1 and 2 are in the same region; user 3 is in another region of the same scene
	--User 4 is in a different static scene from users 1, 2 and 3; user 5 is in a different dynamic scene
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
	
	-- Region
    print("---------------------------------screen---------------------------------------");
	local oScene = role1:GetScene();
    local sceneTempID = oScene:GetSceneTempID();
    local sceneID = oScene:GetSceneID();

	-- User 1 speaks; user 2 receives it
	local targetid = cctScreen;
	ret =role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");

	msg = recv_msg(10, user2sessionid, protocol.g2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_gsmsmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	-- User 1 speaks; users 3, 4 and 5 do not receive it
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
	
	--Server-wide broadcast
    print("---------------------------------allserver---------------------------------------");	
	
	-- User 1 speaks; users 2, 3, 4 and 5 receive it
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
	
	-- Private chat
    print("---------------------------------wisper---------------------------------------");	

	-- User 1 speaks to user 3
	targetid = user3id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	-- User 3 receives it
	msg = recv_msg(10, user3sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	-- Users 2, 4 and 5 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- User 1 speaks to user 4
	targetid = user4id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	-- User 4 receives it
	msg = recv_msg(10, user4sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");

	-- Users 2, 3 and 5 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- User 1 speaks to user 5
	targetid = user5id;
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");

	-- User 5 receives it
	msg = recv_msg(10, user5sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");
	
	wait(30);
	-- Users 2, 3 and 4 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send wisper chat message");
	retMsgInfo = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user4sessionid, protocol.m2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
			check(v.msg == nil, "fail to recv allserver msg");
		end
	end
	
	-- Scene
    print("---------------------------------scene---------------------------------------");

	-- User 1 speaks; users 2 and 3 receive it
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
	
	-- User 1 speaks; users 4 and 5 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send scene chat message");
	
	retMsgInfo = recv_msg_and(10, user4sessionid, protocol.g2c_chat_message, user5sessionid, protocol.g2c_chat_message);
	check(retMsgInfo, "fail to recv chat_message");
	
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end

	-- Team
	print("---------------------------------team---------------------------------------");
	-- Users 1 and 4 form a team across static scenes
	local team_name = user_name1.."team";
	
    local teamid = CreateTeam(team_name, user1, role1);
    check(teamid, "failed to create team");
    
	InviteToTeam(user4, role4, user1, role1, 0);
	retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user4sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	targetid = teamid;
	
	-- User 1 speaks to the team; user 4 receives it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");
		
	msg = recv_msg(10, user4sessionid, protocol.m2c_chat_message);
	check(msg, "fail to recv chat_message");
	--check(msg.dwTargetID == targetid, "fail to receive msg with correct type");
	check(msg.szMessage == TestString, "fail to receive correct msg content");
	username = get_role_name_from_msmessage(msg);
	check(username == user_name1, "fail to receive msg from correct sender");	

	-- Users 2, 3 and 5 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");	
	retMsg = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user3sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
    check(retMsg, "failed to received chat msg");

	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end

	-- Invite user 3, who is in the same scene as user 1, to the team
	
	InviteToTeam(user3, role3, user1, role1, 0);
	retMsg = recv_msg_and(30, user1sessionid, protocol.m2c_team_add_member, user3sessionid, protocol.m2c_team_add_member, user4sessionid, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	-- User 1 speaks to the team; users 3 and 4 receive it
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
	
	-- Users 2 and 5 do not receive it
	ret = role1:Say(targetid, TestString);
	check(ret, "failed to send team chat message");	
	retMsg = recv_msg_and(10, user2sessionid, protocol.m2c_chat_message, user5sessionid, protocol.m2c_chat_message);
	check(retMsg, "fail to recv chat_message");	

	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.m2c_chat_message) then
				check(v.msg == nil, "fail to receive msg");
		end
	end	
	
	-- Test complete; log out
	cleanup(user1);
    cleanup(user2);
    cleanup(user3);
	cleanup(user4);
    cleanup(user5);
end



