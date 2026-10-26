
TestCase.Arena = {};

function TestCase.Arena.ArenaTeamTest()
    local msg;
    local ret = 0;
    local user_name = "ATm_Test1"..os.date("%H%M%S");
    local user_name2 = "ATm_Test2"..os.date("%H%M%S");
    local user_name3 = "ATm_Test3"..os.date("%H%M%S");
    
    local team_name = "ATM_team1"..os.date("%H%M%S");
    local team_name_2 = "ATM_team2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
	
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 1);
    check(ret, "failed to send join arena team answer");
    
    wait(5);
    
    ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id, 0);
    check(ret, "failed to send join arena team answer");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_3, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_error_notify);
    check(msg, "failed to recv m2c_error_notify");

	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_3, 0x0201, team_name_2);
    check(ret, "failed to send create arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_error_notify, session_id_3, protocol.g2c_error_notify);
    check(msg, "failed to recv m2c_error_notify or g2c_error_notify");

	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_2, 0x0201, team_name_2);
    check(ret, "failed to send create arena team");

	retMsg = recv_msg_and(30, session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_2, role_id_3);
    check(ret, "failed to send join arena team");

	msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to recv m2c_error_notify");
    
    ret = g_RobotMessageHandler:DoQueryArenaTeamInfo(role_2);
    check(ret, "failed to send Query arena team Info");

	msg = recv_msg(30, session_id_2, protocol.m2c_arena_team_info);
    check(msg, "failed to recv m2c_arena_team_info");
    check(msg.byMemberCount == 1, "failed byMemberCount");
    check(msg.wIconID == 0x0201, "failed wIconID");
    check(msg.stMemberList[0].dwRoleID == role_id_2, "failed dwRoleID");
    check(msg.dwArenaTeamID ~= role:GetArenaTeamID(), "failed dwArenaTeamID");

	ret = g_RobotMessageHandler:DoLeaveArenaTeam(role_2, role_id_2);
    check(ret, "failed to send Leave arena team");

	msg = recv_msg(30, session_id_2, protocol.m2c_leave_arena_team);
    check(msg, "failed to recv m2c_leave_arena_team");
    check(msg.dwRoleID == role_id_2, "failed to msg.dwRoleID");

    ret = g_RobotMessageHandler:DoQueryArenaTeamInfo(role_2);
    check(ret, "failed to send Query arena team Info");

	msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to recv m2c_error_notify");

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 0);
    check(ret, "failed to send join arena team answer");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_join_arena_team,
	session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_2:GetArenaTeamID(), "error deArenaTeamID");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoQueryArenaTeamInfo(role_2);
    check(ret, "failed to send Query arena team Info");

	msg = recv_msg(30, session_id_2, protocol.m2c_arena_team_info);
    check(msg, "failed to recv m2c_error_notify");
    check(msg.byMemberCount == 3, "failed byMemberCount");
    check(msg.wIconID == 0x0101, "failed wIconID");
    check(msg.stMemberList[0].dwRoleID == role_id, "failed dwRoleID");

	ret = g_RobotMessageHandler:DoLeaveArenaTeam(role_2, role_id_3);
    check(ret, "failed to send Leave arena team");
    
    msg = recv_msg(30, session_id_2, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_2);
	wait(5);
	
	user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();

	ret = g_RobotMessageHandler:DoLeaveArenaTeam(role, role_id_2);
    check(ret, "failed to send Leave arena team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_leave_arena_team, session_id_2, protocol.m2c_leave_arena_team,
	session_id_3, protocol.m2c_leave_arena_team);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoleID == role_id_2, "failed to msg.dwRoleID");
	end

	ret = g_RobotMessageHandler:DoQueryArenaTeamInfo(role_3);
    check(ret, "failed to send Query arena team Info");

	msg = recv_msg(30, session_id_3, protocol.m2c_arena_team_info);
    check(msg, "failed to recv m2c_error_notify");
    check(msg.byMemberCount == 2, "failed byMemberCount");
    check(msg.wIconID == 0x0101, "failed wIconID");
    check(msg.stMemberList[0].dwRoleID == role_id, "failed dwRoleID");

	ret = g_RobotMessageHandler:DoLeaveArenaTeam(role, role_id);
    check(ret, "failed to send Leave arena team");

	wait(5);
	check(role:GetArenaTeamID() == 0, "error dwArenaTeamID");
	check(role_2:GetArenaTeamID() == 0, "error dwArenaTeamID");
	check(role_3:GetArenaTeamID() == 0, "error dwArenaTeamID");

	ret = g_RobotMessageHandler:DoQueryArenaTeamInfo(role_3);
    check(ret, "failed to send Query arena team Info");

	msg = recv_msg(30, session_id_3, protocol.m2c_error_notify);
    check(msg, "failed to recv m2c_error_notify");

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.Arena.RoleArenaJoin()
    local msg;
    local ret = 0;
    local user_name = "RA_Test1"..os.date("%H%M%S");
    local user_name2 = "RA_Test2"..os.date("%H%M%S");
    local user_name3 = "RA_Test3"..os.date("%H%M%S");
    local team_name = user_name.."RA_team1";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
	
    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");
    
    ret = g_RobotMessageHandler:DoTeamJoin(role, role_id_2);
    check(ret, "failed to send Join team");

    msg = recv_msg(30, session_id, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");
    
    ret = g_RobotMessageHandler:DoTeamJoin(role_2, role_id);
    check(ret, "failed to send Join team");

    msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");

    ret = g_RobotMessageHandler:DoCancelJoinArenaReq(role);
    check(ret, "failed to send Cancel Join Arena Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_cancel_join_arena_ack);
    check(msg, "failed to recv m2c_cancel_join_arena_ack");
    
    ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");

	InviteToTeam(user, role, user_3, role_3, 0);

    ret = g_RobotMessageHandler:DoJoinArena(role_3, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_3, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_3);
	wait(5);
	
	user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    session_id_3 = user_3:GetSessionID();
    role_id_3 = role_3:GetObjID();

    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

    msg = recv_msg(30, session_id, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");

	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id, 0);
    check(ret, "failed to send join arena team answer");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
    
    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_3, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_queue");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoCancelJoinArenaReq(role_2);
    check(ret, "failed to send Cancel Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_cancel_join_arena_ack);
    check(msg, "failed to recv m2c_cancel_join_arena_ack");

    ret = g_RobotMessageHandler:DoCancelJoinArenaReq(role_3);
    check(ret, "failed to send Cancel Join Arena Req");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_cancel_join_arena_ack, session_id_3, protocol.m2c_cancel_join_arena_ack);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_3, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_queue");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
    cleanup(user_3);
	wait(5);
	
	user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    session_id_3 = user_3:GetSessionID();
    role_id_3 = role_3:GetObjID();

    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_3, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_queue");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.Arena.RoleArenaEnter()
    local msg;
    local ret = 0;
    local user_name = "RAE_Test1"..os.date("%H%M%S");
    local user_name2 = "RAE_Test2"..os.date("%H%M%S");
    local user_name3 = "RAE_Test3"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
	
	ret = user_2:GMCommand("SetPersonalArenaScore(1200)");
	check(ret, "exec GMCommand SelfRole:SetPersonalArenaScore(1200)");

    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");
        
    ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");

	msg = recv_msg(10, session_id, protocol.m2c_join_arena_confirm_req);
    check(msg == nil, "failed to received m2c_join_arena_confirm_req");

    ret = g_RobotMessageHandler:DoJoinArena(role_3, artRace);
    check(ret, "failed to send Join Arena Req");
    
    local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req,
									session_id_3, protocol.m2c_join_arena_confirm_req);
	check(retMsg, "failed to received m2c_join_arena_confirm_req");
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_2);
	wait(5);
	
	user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();

    ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_arena_ack");

    ret = g_RobotMessageHandler:DoCancelJoinArenaReq(role_2);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_cancel_join_arena_ack);
    check(msg, "failed to recv m2c_cancel_join_arena_ack");

    ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_3, 0);
    check(ret, "failed to send Join Battle Confirm");

    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_3, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.Arena.Team2ArenaEnter()
    local msg;
    local ret = 0;
    local user_name = "TAE2_Test1"..os.date("%H%M%S");
    local user_name2 = "TAE2_Test2"..os.date("%H%M%S");
    local user_name3 = "TAE2_Test3"..os.date("%H%M%S");
    local user_name4 = "TAE2_Test4"..os.date("%H%M%S");
    local user_name5 = "TAE2_Test5"..os.date("%H%M%S");
    local user_name6 = "TAE2_Test6"..os.date("%H%M%S");

    local team_name = user_name.."TAE2_team1";
    local team_name_2 = user_name2.."TAE2_team2";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    
    local user_5,role_5 = startup(user_name5, user_name5);
    check(user_5, "failed to create user5");
    check(role_5, "failed to create role5");
    local session_id_5 = user_5:GetSessionID();
    local role_id_5 = role_5:GetObjID();

    local user_6, role_6 = startup(user_name6, user_name6);
    check(user_6, "failed to create user6");
    check(role_6, "failed to create role6");
    local session_id_6 = user_6:GetSessionID();
    local role_id_6 = role_6:GetObjID();
    
    local team_name = user_name.."RAE_team1";
    local team_name_2 = user_name2.."RAE_team2";


	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_2:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_join_arena_team,
							session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user, role, user_2, role_2, 0);
	
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_2, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_4, 0x0101, team_name_2);
    check(ret, "failed to send create arena team");

	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_4, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_5);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_5, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_5, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, 
	session_id_5, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_5:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_6);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_6, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_6, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_join_arena_team,
							  session_id_6, protocol.m2c_join_arena_team, session_id_6, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_6:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user_4, role_4, user_5, role_5, 0);
	
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_team_join, session_id_5, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	InviteToTeam(user_4, role_4, user_6, role_6, 0);
	
	msg = recv_msg(30, session_id_6, protocol.m2c_team_join);
    check(msg, "failed to receive m2c_team_join");


	ret = g_RobotMessageHandler:DoJoinArena(role_4, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_queue, session_id_5, protocol.m2c_join_arena_queue,
									session_id_6, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	wait(5);
	
	ret = g_RobotMessageHandler:DoCancelJoinArenaReq(role_4);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id_4, protocol.m2c_cancel_join_arena_ack, session_id_5, protocol.m2c_cancel_join_arena_ack,
									session_id_6, protocol.m2c_cancel_join_arena_ack);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	LeaveTeam(user_6, role_6);
	wait(2);
	
	ret = g_RobotMessageHandler:DoJoinArena(role_4, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req, session_id_2, protocol.m2c_join_arena_confirm_req,
									session_id_4, protocol.m2c_join_arena_confirm_req, session_id_5, protocol.m2c_join_arena_confirm_req);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_4, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_5, 0);
    check(ret, "failed to send Join Arena Req");


    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_changescene_enter,
							  session_id_4, protocol.g2c_changescene_enter,
							  session_id_5, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
    cleanup(user_5);
    cleanup(user_6);
end

function InviteToArenaTeam(captain_user, captain_role, invited_user, invited_role)
	local ret = 0;
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(captain_role, invited_role:GetObjID());
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, invited_user:GetSessionID(), protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(invited_role, captain_role:GetObjID(), 0);
    check(ret, "failed to send join arena team answer");
    
	local retMsg = recv_msg_and(30, captain_user:GetSessionID(), protocol.m2c_join_arena_team, 
	invited_user:GetSessionID(), protocol.m2c_join_arena_team, invited_user:GetSessionID(), protocol.m2c_arena_team_info);
	
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    
    check(captain_role:GetArenaTeamID() == invited_role:GetArenaTeamID());
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	return ret;
end


function TeamArenaPrepare(user_table, role_table)
	local ret;
	local retMsg;
	
	for i = 1, 2 do
		for j = 1, 5 do
			local user_name = "AT_" .. i .. "_" .. j ..os.date("%H%M%S");
			user_table[i][j], role_table[i][j] = startup(user_name, user_name);
			check(user_table, "failed to create user" .. i .. j);
			check(role_table, "failed to create role" .. i .. j);
			
			ret = user_table[i][j]:GMCommand(".level 50");
			check(ret, "exec GMCommand .level 50");
		end
	end
	
	for i = 1, 2 do
		local team_name = "TEAM" .. i .. "-" .. role_table[i][1]:GetName();
		
		ret = g_RobotMessageHandler:DoCreateArenaTeam(role_table[i][1], 0x0101, team_name);
	    check(ret, "failed to send create arena team");
	
		retMsg = recv_msg_and(30, user_table[i][1]:GetSessionID(), protocol.m2c_join_arena_team, user_table[i][1]:GetSessionID(), protocol.m2c_arena_team_info);
	    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");
	
	    for k,v in pairs(retMsg) do
			check(v.msg, "fail to recv allserver msg");
		end
	end
	
	for i = 1, 2 do
		for j = 2, 5 do
		
			InviteToTeam(user_table[i][1], role_table[i][1], user_table[i][j], role_table[i][j], 0);
			
			retMsg = recv_msg(30, user_table[i][j]:GetSessionID(), protocol.m2c_team_join);
		    check(retMsg, "failed to received m2c_team_join");
		    
			ret = InviteToArenaTeam(user_table[i][1], role_table[i][1], user_table[i][j], role_table[i][j]);
			check(ret, "failed to InviteToArenaTeam");
		end
	end
	
	ret = g_RobotMessageHandler:DoJoinArena(role_table[1][1], 0);
    check(ret, "failed to send Join Arena Req");

	retMsg = recv_msg_and(30,	user_table[1][1]:GetSessionID(), protocol.m2c_join_arena_queue,
								user_table[1][2]:GetSessionID(), protocol.m2c_join_arena_queue,
								user_table[1][3]:GetSessionID(), protocol.m2c_join_arena_queue,
								user_table[1][4]:GetSessionID(), protocol.m2c_join_arena_queue,
								user_table[1][5]:GetSessionID(), protocol.m2c_join_arena_queue);
	
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArena(role_table[2][1], 0);
    check(ret, "failed to send Join Arena Req");

	
	retMsg = recv_msg_and(30,	user_table[1][1]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[1][2]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[1][3]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[1][4]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[1][5]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[2][1]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[2][2]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[2][3]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[2][4]:GetSessionID(), protocol.m2c_join_arena_confirm_req,
								user_table[2][5]:GetSessionID(), protocol.m2c_join_arena_confirm_req);
	
								
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	for i = 1, 2 do
		for j = 1, 5 do
			ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_table[i][j], 0);
			check(ret, "failed to send Join Arena Req");
		end
    end
    
    retMsg = recv_msg_and(30, user_table[1][1]:GetSessionID(), protocol.g2c_changescene_enter, 
							  user_table[1][2]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[1][3]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[1][4]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[1][5]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[1][1]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[2][2]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[2][3]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[2][4]:GetSessionID(), protocol.g2c_changescene_enter,
							  user_table[2][5]:GetSessionID(), protocol.g2c_changescene_enter);
							  
    check(retMsg, "failed to receive g2c_changescene_enter");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	return ret;
end

function TestCase.Arena.Team5ArenaEnter()
	local users =
	{
		[1] = {},
		[2] = {},
	};
	
	local roles =
	{
		[1] = {},
		[2] = {},
	};
	
	local ret = TeamArenaPrepare(users, roles);
	check(ret, "failed to TeamArenaPrepare");

end

function TestCase.Arena.Team3ArenaEnter()
    local msg;
    local ret = 0;
    local user_name = "TAE3_Test1"..os.date("%H%M%S");
    local user_name2 = "TAE3_Test2"..os.date("%H%M%S");
    local user_name3 = "TAE3_Test3"..os.date("%H%M%S");
    local user_name4 = "TAE3_Test4"..os.date("%H%M%S");
    local user_name5 = "TAE3_Test5"..os.date("%H%M%S");
    local user_name6 = "TAE3_Test6"..os.date("%H%M%S");

    local team_name = user_name.."TAE3_team1";
    local team_name_2 = user_name2.."TAE3_team2";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    
    local user_5,role_5 = startup(user_name5, user_name5);
    check(user_5, "failed to create user5");
    check(role_5, "failed to create role5");
    local session_id_5 = user_5:GetSessionID();
    local role_id_5 = role_5:GetObjID();

    local user_6, role_6 = startup(user_name6, user_name6);
    check(user_6, "failed to create user6");
    check(role_6, "failed to create role6");
    local session_id_6 = user_6:GetSessionID();
    local role_id_6 = role_6:GetObjID();
    
    local team_name = user_name.."RAE_team1";
    local team_name_2 = user_name2.."RAE_team2";


	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_2:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_join_arena_team,
							session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user, role, user_2, role_2, 0);
	
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	InviteToTeam(user, role, user_3, role_3, 0);
	msg = recv_msg(30, session_id_3, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");

	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_2, protocol.m2c_join_arena_queue,
									session_id_3, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_4, 0x0101, team_name_2);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_4, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_5);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_5, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_5, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, 
	session_id_5, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_5:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_6);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_6, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_6, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_join_arena_team,
							  session_id_6, protocol.m2c_join_arena_team, session_id_6, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_6:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user_4, role_4, user_5, role_5, 0);
	
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_team_join, session_id_5, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	InviteToTeam(user_4, role_4, user_6, role_6, 0);
	msg = recv_msg(30, session_id_6, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
	
	ret = g_RobotMessageHandler:DoJoinArena(role_4, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req, session_id_2, protocol.m2c_join_arena_confirm_req,
									session_id_3, protocol.m2c_join_arena_confirm_req, session_id_6, protocol.m2c_join_arena_confirm_req,
									session_id_4, protocol.m2c_join_arena_confirm_req, session_id_5, protocol.m2c_join_arena_confirm_req);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
    check(ret, "failed to send Join Arena Req");
    
    ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_3, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_4, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_5, 0);
    check(ret, "failed to send Join Arena Req");
    
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_6, 0);
    check(ret, "failed to send Join Arena Req");


    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_changescene_enter,
							  session_id_3, protocol.g2c_changescene_enter,
							  session_id_4, protocol.g2c_changescene_enter,
							  session_id_5, protocol.g2c_changescene_enter,
							  session_id_6, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
    cleanup(user_5);
    cleanup(user_6);
end

function TestCase.Arena.RoleArenaScore()
    local msg;
    local ret = 0;
    local user_name = "RAS_Test1"..os.date("%H%M%S");
    local user_name2 = "RAS_Test2"..os.date("%H%M%S");
    local user_name3 = "RAS_Test3"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
	
	ret = user_2:GMCommand("SetPersonalArenaScore(1050)");
	check(ret, "exec GMCommand SelfRole:SetPersonalArenaScore(1050)");
	
	JumpToStartMap(user);
	JumpToStartMap(user_2);
	JumpToStartMap(user_3);

	while role:GetPersonalArenaScore() < 950 do
		print("ScoreForRole:"..role:GetPersonalArenaScore());
		print("ScoreForRole_3:"..role_3:GetPersonalArenaScore());

		ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
		check(ret, "failed to send Join Arena Req");
	    
		msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
		check(msg, "failed to recv m2c_join_battle_ack");
	        
		ret = g_RobotMessageHandler:DoJoinArena(role_3, artRace);
		check(ret, "failed to send Join Arena Req");
	        
		local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req,
										session_id_3, protocol.m2c_join_arena_confirm_req);
		check(retMsg, "failed to received m2c_join_arena_confirm_req");
		for k,v in pairs(retMsg) do
			check(v.msg, "fail to recv allserver msg");
		end
		
		ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
		check(ret, "failed to send Join Battle Confirm");
	    
		ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_3, 0);
		check(ret, "failed to send Join Battle Confirm");

		retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
								  session_id_3, protocol.g2c_changescene_enter);  
		check(retMsg, "failed to receive g2c_changescene_enter");

		for k,v in pairs(retMsg) do
			check(v.msg, "fail to recv allserver msg");
		end
		
		wait(40);
		ret = user_3:GMCommand("SetHp(0)");
		check(ret, "exec GMCommand SelfRole:SetHp(0)");

		retMsg = recv_msg_and(30, session_id, protocol.g2c_scene_finish, session_id, protocol.m2c_sync_arena_score_for_role,
								  session_id_3, protocol.g2c_scene_finish, session_id_3, protocol.m2c_sync_arena_score_for_role);  
		check(retMsg, "failed to receive g2c_scene_finish or m2c_sync_arena_score_for_role");
		for k,v in pairs(retMsg) do
			check(v.msg, "fail to recv allserver msg");
		end
		
		JumpToStartMap(user);
		JumpToStartMap(user_3);
		wait(2);
	end
	
	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
	check(ret, "failed to send Join Arena Req");
	    
	msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
	check(msg, "failed to recv m2c_join_battle_ack");
	        
	ret = g_RobotMessageHandler:DoJoinArena(role_3, artRace);
	check(ret, "failed to send Join Arena Req");
	
	msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_queue);
	check(msg, "failed to recv m2c_join_arena_queue");

	ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
	check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req,
									session_id_2, protocol.m2c_join_arena_confirm_req);
	check(retMsg, "failed to received m2c_join_arena_confirm_req");
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
		
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
	check(ret, "failed to send Join Battle Confirm");
	
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
	check(ret, "failed to send Join Battle Confirm");

	retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_changescene_enter);  
	check(retMsg, "failed to receive g2c_changescene_enter");

	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	wait(40);
	
	ret = g_RobotMessageHandler:DoLeaveScene(role_2);
	check(ret, "failed to send DoLeaveScene");

	retMsg = recv_msg_and(30, session_id, protocol.g2c_scene_finish, session_id, protocol.m2c_sync_arena_score_for_role,
							  session_id_2, protocol.g2c_changescene_enter);  
	check(retMsg, "failed to receive g2c_scene_finish or m2c_sync_arena_score_for_role");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	wait(2);
	
	local nScore = role:GetPersonalArenaScore();
	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
	check(ret, "failed to send Join Arena Req");
	    
	msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
	check(msg, "failed to recv m2c_join_battle_ack");
	        
	ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
	check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req,
									session_id_2, protocol.m2c_join_arena_confirm_req);
	check(retMsg, "failed to received m2c_join_arena_confirm_req");
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
		
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
	check(ret, "failed to send Join Battle Confirm");
	
	msg = recv_msg(30, session_id, protocol.g2c_changescene_enter);
	check(msg, "failed to recv g2c_changescene_enter");

	retMsg = recv_msg_and(90, session_id, protocol.g2c_scene_finish, session_id, protocol.m2c_sync_arena_score_for_role);  
	check(retMsg, "failed to receive g2c_scene_finish or m2c_sync_arena_score_for_role");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	check(role:GetPersonalArenaScore() > nScore, "failed to get personalArenaScore");

	msg = recv_msg(310, session_id, protocol.g2c_changescene_enter);
	check(msg, "failed to recv g2c_changescene_enter");

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.Arena.Team2ArenaScore()
    local msg;
    local ret = 0;
    local user_name = "TAS1_Test1"..os.date("%H%M%S");
    local user_name2 = "TAS2_Test2"..os.date("%H%M%S");
    local user_name3 = "TAS2_Test3"..os.date("%H%M%S");
    local user_name4 = "TAS2_Test4"..os.date("%H%M%S");

    local team_name = user_name.."TAS2_team1";
    local team_name_2 = user_name2.."TAS2_team2";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    

	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_2:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user, role, user_2, role_2, 0);
	
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_2, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_4, 0x0101, team_name_2);
    check(ret, "failed to send create arena team");

	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_4, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, 
	session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user_4, role_4, user_3, role_3, 0);
	
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_team_join, session_id_3, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArena(role_4, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req, session_id_2, protocol.m2c_join_arena_confirm_req,
									session_id_4, protocol.m2c_join_arena_confirm_req, session_id_3, protocol.m2c_join_arena_confirm_req);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_4, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_3, 0);
    check(ret, "failed to send Join Arena Req");


    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_changescene_enter,
							  session_id_4, protocol.g2c_changescene_enter,
							  session_id_3, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = user_2:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");

	ret = user_4:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");

	ret = user_3:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");

	retMsg = recv_msg_and(30, session_id, protocol.g2c_scene_finish, session_id, protocol.m2c_sync_arena_score_for_team,
							  session_id_2, protocol.g2c_scene_finish, session_id_2, protocol.m2c_sync_arena_score_for_team,
							  session_id_3, protocol.g2c_scene_finish, session_id_3, protocol.m2c_sync_arena_score_for_team,
							  session_id_4, protocol.g2c_scene_finish, session_id_4, protocol.m2c_sync_arena_score_for_team);  
	check(retMsg, "failed to receive g2c_scene_finish or m2c_sync_arena_score_for_role");
	
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
end

function TestCase.Arena.Team3ArenaScore()
    local msg;
    local ret = 0;
    local user_name = "TAE3_Test1"..os.date("%H%M%S");
    local user_name2 = "TAE3_Test2"..os.date("%H%M%S");
    local user_name3 = "TAE3_Test3"..os.date("%H%M%S");
    local user_name4 = "TAE3_Test4"..os.date("%H%M%S");
    local user_name5 = "TAE3_Test5"..os.date("%H%M%S");
    local user_name6 = "TAE3_Test6"..os.date("%H%M%S");

    local team_name = user_name.."TAE3_team1";
    local team_name_2 = user_name2.."TAE3_team2";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    
    local user_5,role_5 = startup(user_name5, user_name5);
    check(user_5, "failed to create user5");
    check(role_5, "failed to create role5");
    local session_id_5 = user_5:GetSessionID();
    local role_id_5 = role_5:GetObjID();

    local user_6, role_6 = startup(user_name6, user_name6);
    check(user_6, "failed to create user6");
    check(role_6, "failed to create role6");
    local session_id_6 = user_6:GetSessionID();
    local role_id_6 = role_6:GetObjID();
    
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role, 0x0101, team_name);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_2);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_2, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_2, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, 
	session_id_2, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_2:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role, role_id_3);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_3, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_3, role_id, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_team, session_id_2, protocol.m2c_join_arena_team,
							session_id_3, protocol.m2c_join_arena_team, session_id_3, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role:GetArenaTeamID() == role_3:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user, role, user_2, role_2, 0);
	
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	InviteToTeam(user, role, user_3, role_3, 0);
	msg = recv_msg(30, session_id_3, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");

	ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_queue, session_id_2, protocol.m2c_join_arena_queue,
									session_id_3, protocol.m2c_join_arena_queue);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	
	ret = g_RobotMessageHandler:DoCreateArenaTeam(role_4, 0x0101, team_name_2);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_4, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_join_arena_team or m2c_arena_team_info");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_5);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_5, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_5, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, 
	session_id_5, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_5:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaTeam(role_4, role_id_6);
    check(ret, "failed to send join arena team");
    
    msg = recv_msg(30, session_id_6, protocol.m2c_join_arena_team_ask);
    check(msg, "failed to recv m2c_join_arena_team_ask");

	ret = g_RobotMessageHandler:DoJoinArenaTeamAnswer(role_6, role_id_4, 0);
    check(ret, "failed to send join arena team answer");
    
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_join_arena_team, session_id_5, protocol.m2c_join_arena_team,
							  session_id_6, protocol.m2c_join_arena_team, session_id_6, protocol.m2c_arena_team_info);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    check(role_4:GetArenaTeamID() == role_6:GetArenaTeamID());
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	InviteToTeam(user_4, role_4, user_5, role_5, 0);
	
	retMsg = recv_msg_and(30, session_id_4, protocol.m2c_team_join, session_id_5, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	InviteToTeam(user_4, role_4, user_6, role_6, 0);
	msg = recv_msg(30, session_id_6, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
	
	ret = g_RobotMessageHandler:DoJoinArena(role_4, artRace);
    check(ret, "failed to send Join Arena Req");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req, session_id_2, protocol.m2c_join_arena_confirm_req,
									session_id_3, protocol.m2c_join_arena_confirm_req, session_id_6, protocol.m2c_join_arena_confirm_req,
									session_id_4, protocol.m2c_join_arena_confirm_req, session_id_5, protocol.m2c_join_arena_confirm_req);
    check(retMsg, "failed to received m2c_join_arena_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_2, 0);
    check(ret, "failed to send Join Arena Req");
    
    ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_3, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_4, 0);
    check(ret, "failed to send Join Arena Req");

	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_5, 0);
    check(ret, "failed to send Join Arena Req");
    
	ret = g_RobotMessageHandler:DoJoinArenaConfirm(role_6, 0);
    check(ret, "failed to send Join Arena Req");


    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_changescene_enter,
							  session_id_3, protocol.g2c_changescene_enter,
							  session_id_4, protocol.g2c_changescene_enter,
							  session_id_5, protocol.g2c_changescene_enter,
							  session_id_6, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	wait(5);
	
	ret = user_2:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");

	ret = user_4:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");

	ret = user_5:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");
	
	ret = user_6:GMCommand("SetHp(0)");
	check(ret, "exec GMCommand SelfRole:SetHp(0)");


	retMsg = recv_msg_and(30, session_id, protocol.g2c_scene_finish, session_id, protocol.m2c_sync_arena_score_for_team,
							  session_id_2, protocol.g2c_scene_finish, session_id_2, protocol.m2c_sync_arena_score_for_team,
							  session_id_3, protocol.g2c_scene_finish, session_id_3, protocol.m2c_sync_arena_score_for_team,
							  session_id_4, protocol.g2c_scene_finish, session_id_4, protocol.m2c_sync_arena_score_for_team, 
							  session_id_5, protocol.g2c_scene_finish, session_id_5, protocol.m2c_sync_arena_score_for_team,  
							  session_id_6, protocol.g2c_scene_finish, session_id_6, protocol.m2c_sync_arena_score_for_team);  

	check(retMsg, "failed to receive g2c_scene_finish or m2c_sync_arena_score_for_role");
	
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
    cleanup(user_5);
    cleanup(user_6);
end

function TestCase.Arena.RoleArenaJoinAndCancelBattleQueue()
    local msg;
    local ret = 0;
    local user_name = "RA_Test1"..os.date("%H%M%S");
    local user_name2 = "RA_Test2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    
    ret = g_RobotMessageHandler:DoJoinArena(role, artRace);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");
    
    ret = g_RobotMessageHandler:DoJoinBattle(role, 1);
    check(ret, "failed to send create arena team");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to recv m2c_join_battle_queue");

    ret = g_RobotMessageHandler:DoJoinArena(role_2, artRace);
    check(ret, "failed to send Join Arena Req");
    

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_arena_confirm_req, 
									session_id, protocol.m2c_cancel_join_battle_ack, 
									session_id_2, protocol.m2c_join_arena_confirm_req);
    check(retMsg, "failed to received m2c_join_arena_confirm_req");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
end