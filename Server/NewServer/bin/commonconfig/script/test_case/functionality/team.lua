LoadPackage("item.pkg");

TestCase.Team = {};
TestCase.Room = {};

function CreateTeam(teamName, user, role)

    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
    local ret = 0;
    local msg;
	
	ret = g_RobotMessageHandler:DoTeamJoin(role, role_id);
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");

    local teamID = msg.dwTeamID;
    print("teamID:"..teamID);

    check(msg.dwLeadID == role_id, "error leader");
    check(msg.byMemberCount == 1, "error team member count");    
    check(msg.stTeamMemberList[0].dwRoleID == role_id, "error team memberID");

    return teamID;
end

function LeaveTeam(user, role)
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
    local ret = 0;
    local msg;
    local team_id = 0;

	ret = g_RobotMessageHandler:DoTeamLeave(role, role_id);
    check(ret, "failed to send Leave team");

    msg = recv_msg(30, session_id, protocol.m2c_team_leave);
    check(msg, "failed to received m2c_team_leave");
    team_id = msg.dwTeamID;

    return team_id;
end

function InviteToTeam(userReq, roleReq, userTarget, roleTarget, answer)
	
	local session_id = userReq:GetSessionID();
    local target_session_id = userTarget:GetSessionID();

    local role_id = roleReq:GetObjID();
	local target_role_id = roleTarget:GetObjID();

    local role_name = roleReq:GetName();
    local ret = 0;
    local msg;
    local ret_team_id = 0;

    if(answer == nil ) then
		answer = 0;
    end

	ret = g_RobotMessageHandler:DoTeamJoin(roleReq, target_role_id);
    check(ret, "failed to send create team");

    msg = recv_msg(30, target_session_id, protocol.m2c_team_answer);
    check(msg, "failed to received m2c_team_answer");
    check(msg.dwAnswerRequestRoleID == role_id, "error role");
    check(msg.szRequestRoleName == role_name, "error roleName");
	
	ret = g_RobotMessageHandler:DoTeamAnswer(roleTarget, msg.dwAnswerRequestRoleID, msg.byAnswerType, answer);
    check(ret, "failed to send team answer");
end


function TestCase.Team.Create()

    local msg;
    local user_name = "Tm_Crt"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
	
    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to create team");

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    wait(2);
    cleanup(user);
end


function TestCase.Team.Enter()

    local msg;
    local ret = 0;
    local user_name = "Tm_Entf1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user1, role1 = startup(user_name, user_name);
    check(user1, "failed to create user");
    check(role1, "failed to create role");
    local session_id_1 = user1:GetSessionID();
    local role_id_1 = role1:GetObjID();
	
    local user_name2 = "Tm_Entf2"..os.date("%H%M%S");		
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    local session_id_2 = user2:GetSessionID();
    local role_id_2 = role2:GetObjID();

    local team_id = CreateTeam(team_name, user1, role1);
    check(team_id, "failed to create team");

    InviteToTeam(user2, role2, user1, role1, 1);

	wait(5);

    InviteToTeam(user2, role2, user1, role1, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    local nCount = 0;
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_add_member) then
			check(v.msg.dwTeamID == team_id, "failed to leave team");
			check(v.msg.stAddMember.dwRoleID == role_id_2);
			check(v.msg.stAddMember.szRoleName == user_name2);
		else
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwLeadID == role_id_1, "failed to received err teamInfo");
			check(v.msg.byMemberCount == 2, "failed to received err teamInfo");
			check(v.msg.stTeamMemberList[0].dwRoleID == role_id_1 or v.msg.stTeamMemberList[1].dwRoleID == role_id_1, "failed to received err teamInfo");
			check(v.msg.stTeamMemberList[0].dwRoleID == role_id_2 or v.msg.stTeamMemberList[1].dwRoleID == role_id_2, "failed to received err teamInfo");
		end
	end

    ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");

    InviteToTeam(user, role, user_2, role_2, 1);
	wait(5);

    InviteToTeam(user, role, user_2, role_2, 0);
	
	retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    nCount = 0;
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_add_member) then
			check(v.msg.dwTeamID == team_id, "failed to leave team");
			check(v.msg.stAddMember.dwRoleID == role_id_2);
			check(v.msg.stAddMember.szRoleName == user_name2);
		else
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwLeadID == role_id_1, "failed to received err teamInfo");
			check(v.msg.byMemberCount == 2, "failed to received err teamInfo");
			check(v.msg.stTeamMemberList[0].dwRoleID == role_id_1 or v.msg.stTeamMemberList[1].dwRoleID == role_id_1, "failed to received err teamInfo");
			check(v.msg.stTeamMemberList[0].dwRoleID == role_id_2 or v.msg.stTeamMemberList[1].dwRoleID == role_id_2, "failed to received err teamInfo");
		end
	end
    
	ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
end


function TestCase.Team.Leave()

    local msg;
	local retMsg;
    local ret = 0;
    local user_name = "Tm_Leave1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_Leave2"..os.date("%H%M%S");
    local user_name3 = "Tm_Leave3"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
	
    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to create team");

    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();

	InviteToTeam(user_2, role_2, user, role, 0);
	
	retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	ret = g_RobotMessageHandler:DoTeamLeave(role_2, role_id_2);
    check(ret, "failed to send Leave team");

    retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_remove_member, session_id_2, protocol.m2c_team_leave);
    check(retMsg, "failed to received g2c_teaminfo");
    
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_leave) then
			check(v.msg.dwTeamID == team_id, "failed to leave team");
		else
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwRemoveMemberID == role_id_2, "failed to received err teamInfo");
		end
    end

    wait(2);
    
    --third user
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user2");
    check(role_3, "failed to create role2");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();

	InviteToTeam(user_3, role_3, user, role, 0);
	retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_3, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	ret = g_RobotMessageHandler:DoTeamLeave(role, role_id_1);
    check(ret, "failed to send Leave team");

    local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_leave, session_id_3, protocol.m2c_team_remove_member, session_id_3, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received m2c_team_leave or m2c_team_remove_member or m2c_team_changeinfo");
    
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_leave) then
			check(v.msg.dwTeamID == team_id, "failed to leave team");
		elseif(v.msgID == protocol.m2c_team_remove_member) then
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwRemoveMemberID == role_id_1, "failed to received err teamInfo");
		else
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwLeadID == role_id_3, "failed to received err teamInfo");
		end
    end

    ret = LeaveTeam(user_3, role_3);
    check(ret == team_id, "failed to leave team");

    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end;

function TestCase.Team.Kick()

    local msg;
	local retMsg;
    local ret = 0;
    local user_name = "Tm_Kick1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_Kick2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
	
    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to create team");

    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();

	InviteToTeam(user_2, role_2, user, role, 0);
	
	retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	ret = g_RobotMessageHandler:DoTeamLeave(role_2, role_id_1);
    check(ret, "failed to send Leave team");

	msg = recv_msg(30, session_id_2, protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");
	wait(5);

	user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();
	check(role_2:GetTeamID() == team_id, "failed to online teaminfo");

	ret = g_RobotMessageHandler:DoTeamLeave(role, role_id_2);
    check(ret, "failed to send Leave team");

    retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_remove_member, session_id_2, protocol.m2c_team_leave);
    check(retMsg, "failed to received g2c_teaminfo");
    
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_leave) then
			check(v.msg.dwTeamID == team_id, "failed to leave team");
		else
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwRemoveMemberID == role_id_2, "failed to received err teamInfo");
		end
    end

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    cleanup(user);
    cleanup(user_2);
end;


function TestCase.Team.Join()

    local msg;
    local ret = 0;
    local user_name = "Tm_Join1"..os.date("%H%M%S");
    local team_name = user_name.."team";
	local team_id = 0;

    local user_name2 = "Tm_Join2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();

    InviteToTeam(user_2, role_2, user, role, 1);
	wait(5);
	InviteToTeam(user_2, role_2, user, role, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    local nCount = 0;
    local k, v;
    for k,v in pairs(retMsg) do
		check(v.msgID == protocol.m2c_team_join, "failed to receive m2c_team_join");
		team_id = v.msg.dwTeamID;
		check(v.msg.byMemberCount == 2);
		check(v.msg.dwLeadID == role_id_2, "error leader");
		check(v.msg.byMemberCount == 2, "error team member count");    
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_1 or v.msg.stTeamMemberList[1].dwRoleID == role_id_1, "failed to received err teamInfo");
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_2 or v.msg.stTeamMemberList[1].dwRoleID == role_id_2, "failed to received err teamInfo");
	end

	ret = g_RobotMessageHandler:DoTeamJoin(role_2, role_id_1);
    check(ret, "failed to send create team");
	msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to receive m2c_error_notify");

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
end


function TestCase.Team.OffLine()

    local msg;
    local ret = 0;
	local team_id;
    local user_name = "Tm_off1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_off2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();

	InviteToTeam(user_2, role_2, user, role, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    local nCount = 0;
    local k, v;
    for k,v in pairs(retMsg) do
		check(v.msgID == protocol.m2c_team_join, "failed to receive m2c_team_join");
		team_id = v.msg.dwTeamID;
		check(v.msg.byMemberCount == 2);
		check(v.msg.dwLeadID == role_id_2, "error leader");
		check(v.msg.byMemberCount == 2, "error team member count");    
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_1 or v.msg.stTeamMemberList[1].dwRoleID == role_id_1, "failed to received err teamInfo");
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_2 or v.msg.stTeamMemberList[1].dwRoleID == role_id_2, "failed to received err teamInfo");
	end

	wait(5);
	cleanup(user);

    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id_1 = user:GetSessionID();
    role_id_1 = role:GetObjID();
	check(role:GetTeamID() == team_id, "failed to online teaminfo");

    wait(5);
	ret = user_2:Logout();
    check(ret, "failed to logout");

    local retMsg = recv_msg_and(30,session_id_2, protocol.t2c_robot_disconnected, session_id_1, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received t2c_robot_disconnected or m2c_team_changeinfo");
    
    local k, v;
    for k,v in pairs(retMsg) do
		if(v.msgID == protocol.m2c_team_changeinfo) then
			check(v.msg.dwTeamID == team_id, "failed to received err teamInfo");
			check(v.msg.dwLeadID == role_id_1, "failed to received err teamInfo");
		end
    end
	
    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    cleanup(user);
end;

function TestCase.Team.SyncMember()

    local msg;
    local ret = 0;
    local user_name = "Tm_Sync1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_Sync2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
    user:GMCommand("jump hhc");
	   
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    user_2:GMCommand("jump hhc");

	InviteToTeam(user_2, role_2, user, role, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    local nCount = 0;
    local k, v;
    for k,v in pairs(retMsg) do
		check(v.msgID == protocol.m2c_team_join, "failed to receive m2c_team_join");
		team_id = v.msg.dwTeamID;
		check(v.msg.byMemberCount == 2);
		check(v.msg.dwLeadID == role_id_2, "error leader");
		check(v.msg.byMemberCount == 2, "error team member count");    
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_1 or v.msg.stTeamMemberList[1].dwRoleID == role_id_1, "failed to received err teamInfo");
		check(v.msg.stTeamMemberList[0].dwRoleID == role_id_2 or v.msg.stTeamMemberList[1].dwRoleID == role_id_2, "failed to received err teamInfo");
	end

    retMsg = recv_msg_and(10, session_id_1, protocol.m2c_team_sync_memberinfo, session_id_2, protocol.m2c_team_sync_memberinfo)
    check(retMsg, "failed to received m2c_team_sync_memberinfo");
    for k,v in pairs(retMsg) do
		check(v.msg, "failed to received all message");
	end

    retMsg = recv_msg_and(5, session_id_1, protocol.g2c_team_sync_member, session_id_2, protocol.g2c_team_sync_member)
    check(retMsg, "failed to received g2c_team_sync_member");
    for k,v in pairs(retMsg) do
		check(v.msg, "failed to received all message");
	end
	
	wait(2);

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");

    ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");
    
    wait(2);
    cleanup(user);
    cleanup(user_2);
end;

function TestCase.Team.AdjacentData()

    local msg;
    local ret = 0;
    local user_name = "Tm_adjacent1"..os.date("%H%M%S");
    local team_name = user_name.."team";
	local team_id = 0;

    local user_name2 = "Tm_adjacent2"..os.date("%H%M%S");
	local user_name3 = "Tm_adjacent3"..os.date("%H%M%S");


    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
    user:GMCommand("jump hhc");
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    user_2:GMCommand("jump hhc");

	local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
    user_3:GMCommand("jump hhc");
    
    wait(10);

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role);
    check(ret, "failed to send DoAdjacentNoTeamRole");

	msg = recv_msg(30, session_id_1, protocol.g2c_sync_adjacent_role_noteam);
    check(msg, "failed to receive g2c_sync_adjacent_role_noteam");
    check(msg.byCount == 3, "receive g2c_sync_adjacent_role_noteam content error");

    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to CreateTeam");

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role_2);
    check(ret, "failed to send create team");

	msg = recv_msg(30, session_id_2, protocol.g2c_sync_adjacent_role_noteam);
    check(msg, "failed to receive g2c_sync_adjacent_role_noteam");
    check(msg.byCount == 2, "receive g2c_sync_adjacent_role_noteam content error");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role_2);
    check(ret, "failed to send DoAdjacentTeam");

	msg = recv_msg(30, session_id_2, protocol.g2c_sync_adjacent_team);
    check(msg, "failed to receive g2c_sync_adjacent_team");
    check(msg.byCount == 1, "receive g2c_sync_adjacent_team content error");

	local team_id_2 = CreateTeam(team_name, user_2, role_2);
    check(team_id_2, "failed to CreateTeam");

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role_3);
    check(ret, "failed to send DoAdjacentNoTeamRole");

	msg = recv_msg(30, session_id_3, protocol.g2c_sync_adjacent_role_noteam);
    check(msg, "failed to receive g2c_sync_adjacent_role_noteam");
    check(msg.byCount == 1, "receive g2c_sync_adjacent_role_noteam content error");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role_3);
    check(ret, "failed to send DoAdjacentTeam");

	msg = recv_msg(30, session_id_3, protocol.g2c_sync_adjacent_team);
    check(msg, "failed to receive g2c_sync_adjacent_team");
    check(msg.byCount == 2, "receive g2c_sync_adjacent_team content error");

	ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");
	wait(5);

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role_3);
    check(ret, "failed to send DoAdjacentNoTeamRole");

	msg = recv_msg(30, session_id_3, protocol.g2c_sync_adjacent_role_noteam);
    check(msg, "failed to receive g2c_sync_adjacent_role_noteam");
    check(msg.byCount == 2, "receive g2c_sync_adjacent_role_noteam content error");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role_3);
    check(ret, "failed to send DoAdjacentTeam");

	msg = recv_msg(30, session_id_3, protocol.g2c_sync_adjacent_team);
    check(msg, "failed to receive g2c_sync_adjacent_team");
    check(msg.byCount == 1, "receive g2c_sync_adjacent_team content error");

	InviteToTeam(user_3, role_3, user, role, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_join, session_id_3, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role);
    check(ret, "failed to send DoAdjacentNoTeamRole");

	msg = recv_msg(30, session_id_1, protocol.g2c_sync_adjacent_role_noteam);
    check(msg, "failed to receive g2c_sync_adjacent_role_noteam");
    check(msg.byCount == 0, "receive g2c_sync_adjacent_role_noteam content error");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role);
    check(ret, "failed to send DoAdjacentTeam");

	msg = recv_msg(30, session_id_1, protocol.g2c_sync_adjacent_team);
    check(msg, "failed to receive g2c_sync_adjacent_team");
    check(msg.byCount == 2, "receive g2c_sync_adjacent_team content error");
	wait(4);

	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role);
    check(ret, "failed to send DoAdjacentNoTeamRole");
	
	ret = g_RobotMessageHandler:DoAdjacentNoTeamRole(role);
    check(ret, "failed to send DoAdjacentNoTeamRole");

	msg = recv_msg(30, session_id_1, protocol.g2c_error_notify);
	check(msg, "failed to receive g2c_error_notify");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role);
    check(ret, "failed to send DoAdjacentTeam");

	ret = g_RobotMessageHandler:DoAdjacentTeam(role);
    check(ret, "failed to send DoAdjacentTeam");

	msg = recv_msg(30, session_id_1, protocol.g2c_error_notify);
    check(msg, "failed to receive g2c_error_notify");

    ret = LeaveTeam(user, role);
	team_id = ret;

    ret = LeaveTeam(user_2, role_2);
    check(ret == team_id_2, "failed to leave team");

    ret = LeaveTeam(user_3, role_3);
    check(ret == team_id, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
	cleanup(user_3);
end

function TestCase.Room.Create()

    local msg;
    local user_name = "Rm_Crt1"..os.date("%H%M%S");
    local user_name_2 = "Rm_Crt2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();

	local user_2, role_2 = startup(user_name_2, user_name_2);
    check(user_2, "failed to create user");
    check(role_2, "failed to create role");
    local session_id_2 = user_2:GetSessionID();

	ret = g_RobotMessageHandler:DoRoomCreate(role, 102, esdNormal, 5, 1, 20, 15)
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
    
    local teamID = msg.dwTeamID;

	msg = recv_msg(30, session_id, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
    check(msg.dwRoomID > 0, "failed to create Room");
    
    local roomID = msg.dwRoomID;
    
    ret = g_RobotMessageHandler:DoRoomInfoReq(role, roomID);
    check(ret, "failed to send create team");
    
    msg = recv_msg(30, session_id, protocol.m2c_room_info_ack);
    check(msg, "failed to received m2c_room_info_ack");
	check(msg.stRoomItem.dwRoomID == roomID, "error roomId");
	check(msg.stRoomItem.dwSceneTempID == 102, "error dwSceneTempID");
	check(msg.stRoomItem.bySceneDifficulty == esdNormal, "error bySceneDifficulty");
	check(msg.stRoomItem.byLevel == 10, "error byLevel");
	check(msg.stRoomItem.byMemberLimit == 5, "error byMemberLimit");
	check(msg.stRoomItem.byMemberCount == 1, "error byMemberCount");
	
	ret = g_RobotMessageHandler:DoRoomDestroy(role);
    check(ret, "failed to send create team");
    
    msg = recv_msg(30, session_id, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
    check(msg.dwRoomID == 0, "failed to destroy Room");

	InviteToTeam(user, role, user_2, role_2);
	wait(5);
	
	ret = g_RobotMessageHandler:DoRoomCreate(role, 102, esdNormal, 5, 1, 20, 15)
    check(ret, "failed to send create team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_team_changeinfo, session_id_2, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received m2c_team_changeinfo");

	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID > 0,"fail to create room");
		roomID = v.msg.dwRoomID;
	end

    ret = LeaveTeam(user_2, role_2);
    check(ret == teamID, "failed to leave team");

    ret = LeaveTeam(user, role);
    check(ret == teamID, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
end

function TestCase.Room.List()

    local msg;
    local user_name = "Rm_Lst1"..os.date("%H%M%S");
    local user_name_2 = "Rm_Lst2"..os.date("%H%M%S");
    local user_name_3 = "Rm_Lst3"..os.date("%H%M%S");
    local user_name_4 = "Rm_Lst4"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();

	local user_2, role_2 = startup(user_name_2, user_name_2);
    check(user_2, "failed to create user");
    check(role_2, "failed to create role");
    local session_id_2 = user_2:GetSessionID();
    
    local user_3, role_3 = startup(user_name_3, user_name_3);
    check(user_3, "failed to create user");
    check(role_3, "failed to create role");
    local session_id_3 = user_3:GetSessionID();

	local user_4, role_4 = startup(user_name_4, user_name_4);
    check(user_4, "failed to create user");
    check(role_4, "failed to create role");
    local session_id_4 = user_4:GetSessionID();

	ret = g_RobotMessageHandler:DoRoomListReq(role, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    local curRoomCount = msg.byCount;
    
	ret = g_RobotMessageHandler:DoRoomCreate(role_2, 102, esdNormal, 2, 1, 20, 15)
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id_2, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
    
	msg = recv_msg(30, session_id_2, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
    check(msg.dwRoomID > 0, "failed to create Room");
    local role_2_room_id = msg.dwRoomID;
    
    ret = g_RobotMessageHandler:DoRoomListReq(role, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 1, "failed to received m2c_room_list_ack");

	ret = g_RobotMessageHandler:DoRoomCreate(role_3, 102, esdNormal, 5, 1, 20, 15)
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id_3, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
    
	msg = recv_msg(30, session_id_3, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
    check(msg.dwRoomID > 0, "failed to create Room");

	ret = g_RobotMessageHandler:DoRoomListReq(role, 4);
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 2, "failed to received m2c_room_list_ack");

	InviteToTeam(user_2, role_2, user, role);
	wait(5);
	
	ret = g_RobotMessageHandler:DoRoomListReq(role_4, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id_4, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 2, "failed to received m2c_room_list_ack");

	ret = g_RobotMessageHandler:DoRoomInfoReq(role_4, role_2_room_id);
    check(ret, "failed to send DoRoomInfoReq");
    
    msg = recv_msg(30, session_id_4, protocol.m2c_room_info_ack);
    check(msg, "failed to received m2c_room_info_ack");
	check(msg.stRoomItem.dwRoomID == role_2_room_id, "error roomId");
	check(msg.stRoomItem.dwSceneTempID == 102, "error dwSceneTempID");
	check(msg.stRoomItem.bySceneDifficulty == esdNormal, "error bySceneDifficulty");
	check(msg.stRoomItem.byLevel == 10, "error byLevel");
	check(msg.stRoomItem.byMemberLimit == 2, "error byMemberLimit");
	check(msg.stRoomItem.byMemberCount == 2, "error byMemberCount");
	
	ret = g_RobotMessageHandler:DoTeamJoin(role_4, role_2:GetObjID());
    check(ret, "failed to send DoTeamJoin team");

	msg = recv_msg(30, session_id_4, protocol.m2c_error_notify);
    check(msg, "failed to receive m2c_error_notify");

	ret = g_RobotMessageHandler:DoRoomCreate(role_4, 102, esdNormal, 5, 1, 20, 15)
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id_4, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
    
	msg = recv_msg(30, session_id_4, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
    check(msg.dwRoomID > 0, "failed to create Room");

	ret = g_RobotMessageHandler:DoRoomListReq(role, 4)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 3, "failed to received m2c_room_list_ack");

	ret = g_RobotMessageHandler:DoRoomListReq(role, 1)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == 0, "failed to received m2c_room_list_ack");

	ret = g_RobotMessageHandler:DoRoomDestroy(role);
    check(ret, "failed to send Destroy room");
    
    msg = recv_msg(30, session_id, protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");
	cleanup(user);
	
	wait(5);
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    ret = g_RobotMessageHandler:DoRoomDestroy(role_2);
    check(ret, "failed to send Destroy room");

    local retMsg = recv_msg_and(30, session_id, protocol.m2c_team_changeinfo, session_id_2, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received m2c_team_changeinfo");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID == 0,"fail to Destroy room");
		check(v.msg.dwTeamID > 0,"fail to Destroy room");
		check(v.msg.dwLeadID == role_2:GetObjID(),"fail to Destroy room");
	end
	
	ret = g_RobotMessageHandler:DoRoomListReq(role, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 2, "failed to received m2c_room_list_ack");

	ret = g_RobotMessageHandler:DoTeamJoin(role, role_3:GetObjID());
    check(ret, "failed to send DoTeamJoin team");

	msg = recv_msg(30, session_id, protocol.m2c_error_notify);
    check(msg, "failed to receive m2c_error_notify");

	ret = g_RobotMessageHandler:DoRoomDestroy(role_3);
    check(ret, "failed to send Destroy room");

    msg = recv_msg(30, session_id_3, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_changeinfo");
	check(msg.dwRoomID == 0,"fail to Destroy room");
	
	ret = g_RobotMessageHandler:DoRoomListReq(role, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount + 1, "failed to received m2c_room_list_ack");

    ret = LeaveTeam(user_4, role_4);
    check(ret > 0, "failed to leave team");
	wait(5);

	ret = g_RobotMessageHandler:DoRoomListReq(role, 0)
    check(ret, "failed to send RoomListReq");
	
	msg = recv_msg(30, session_id, protocol.m2c_room_list_ack);
    check(msg, "failed to received m2c_room_list_ack");
    check(msg.byCount == curRoomCount, "err m2c_room_list_ack msg for byCount");
	
	ret = LeaveTeam(user_3, role_3);
    check(ret > 0, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
end

function TestCase.Room.Ready()

    local msg;
    local ret;
    local user_name = "Rm_Rr1"..os.date("%H%M%S");
    local user_name_2 = "Rm_Rr2"..os.date("%H%M%S");
    local user_name_3 = "Rm_Rr3"..os.date("%H%M%S");
    local user_name_4 = "Rm_Rr4"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();

	local user_2, role_2 = startup(user_name_2, user_name_2);
    check(user_2, "failed to create user");
    check(role_2, "failed to create role");
    local session_id_2 = user_2:GetSessionID();
    
    local user_3, role_3 = startup(user_name_3, user_name_3);
    check(user_3, "failed to create user");
    check(role_3, "failed to create role");
    local session_id_3 = user_3:GetSessionID();

	local user_4, role_4 = startup(user_name_4, user_name_4);
    check(user_4, "failed to create user");
    check(role_4, "failed to create role");
    local session_id_4 = user_4:GetSessionID();

	InviteToTeam(user, role, user_2, role_2);
	wait(2);
	
	InviteToTeam(user, role, user_3, role_3);
	wait(2);

	ret = g_RobotMessageHandler:DoRoomCreate(role, 102, esdNormal, 4, 1, 20, 15)
    check(ret, "failed to send create team");
    
	local retMsg = recv_msg_and(30, session_id, protocol.m2c_team_changeinfo, session_id_2, protocol.m2c_team_changeinfo,
	session_id_3, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received m2c_team_changeinfo");
	
	local roomID = 0;
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID > 0,"fail to Create room");
		check(v.msg.dwTeamID > 0,"fail to Create room");
		check(v.msg.dwLeadID == role:GetObjID(),"fail to Create room");
		
		if(roomID == 0) then
			roomID = v.msg.dwRoomID;
		else
			check(v.msg.dwRoomID == roomID, "error roomID");
		end
	end
	
	ret = g_RobotMessageHandler:DoRoomReady(role_2, 1);
    check(ret, "failed to send create team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_room_ready_change, session_id_2, protocol.m2c_room_ready_change,
	session_id_3, protocol.m2c_room_ready_change);
    check(retMsg, "failed to received m2c_room_ready_change");

	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID == roomID,"error m2c_room_ready_change msg for roomID");
		check(v.msg.dwRoleID == role_2:GetObjID(),"error m2c_room_ready_change msg for roleID");
		check(v.msg.byReady == 1,"error m2c_room_ready_change msg for byReady");	
	end
	
	InviteToTeam(user, role, user_4, role_4);
	
	msg = recv_msg(30, session_id_4, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
	check(msg.dwRoomID == roomID, "error m2c_team_join msg for roomID");
	
	ret = g_RobotMessageHandler:DoRoomInfoReq(role_4, roomID);
    check(ret, "failed to send DoRoomInfoReq");
    
    msg = recv_msg(30, session_id_4, protocol.m2c_room_info_ack);
    check(msg, "failed to received m2c_room_info_ack");
	check(msg.stRoomItem.dwRoomID == roomID, "error roomId");
	check(msg.stRoomItem.dwSceneTempID == 102, "error dwSceneTempID");
	check(msg.stRoomItem.bySceneDifficulty == esdNormal, "error bySceneDifficulty");
	check(msg.stRoomItem.byLevel == 10, "error byLevel");
	check(msg.stRoomItem.byMemberLimit == 4, "error byMemberLimit");
	check(msg.stRoomItem.byMemberCount == 4, "error byMemberCount");
	
	local i = 0;
	while i < 4 do
		if msg.lstRoomMember[i] ~= nil and msg.lstRoomMember[i].dwRoleID == role_2:GetObjID() then
			check(msg.lstRoomMember[i].byReady == 1, "error ready info");
		elseif msg.lstRoomMember[i] ~= nil then
			check(msg.lstRoomMember[i].byReady == 0, "error ready info");
		end
		i = i + 1;
	end
    
    ret = g_RobotMessageHandler:DoRoomReady(role_4, 1);
    check(ret, "failed to send create team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_room_ready_change, session_id_2, protocol.m2c_room_ready_change,
	session_id_3, protocol.m2c_room_ready_change, session_id_4, protocol.m2c_room_ready_change);
    check(retMsg, "failed to received m2c_room_ready_change");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID == roomID,"error m2c_room_ready_change msg for roomID");
		check(v.msg.dwRoleID == role_4:GetObjID(),"error m2c_room_ready_change msg for roleID");
		check(v.msg.byReady == 1,"error m2c_room_ready_change msg for byReady");	
	end

    ret = g_RobotMessageHandler:DoRoomStart(role);
    check(ret, "failed to send DoRoomStart");

	msg = recv_msg(30, session_id, protocol.m2c_error_notify);
    check(msg, "failed to receive m2c_error_notify");

    ret = g_RobotMessageHandler:DoRoomReady(role_4, 0);
    check(ret, "failed to send create team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_room_ready_change, session_id_2, protocol.m2c_room_ready_change,
	session_id_3, protocol.m2c_room_ready_change, session_id_4, protocol.m2c_room_ready_change);
    check(retMsg, "failed to received m2c_room_ready_change");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoomID == roomID,"error m2c_room_ready_change msg for roomID");
		check(v.msg.dwRoleID == role_4:GetObjID(),"error m2c_room_ready_change msg for roleID");
		check(v.msg.byReady == 0,"error m2c_room_ready_change msg for byReady");	
	end
	
	ret = LeaveTeam(user_4, role_4);
    check(ret > 0, "failed to leave team");

	ret = LeaveTeam(user_3, role_3);
    check(ret > 0, "failed to leave team");

	ret = LeaveTeam(user_2, role_2);
    check(ret > 0, "failed to leave team");

    ret = LeaveTeam(user, role);
    check(ret > 0, "failed to leave team");

    wait(2);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
end

function TestCase.Room.Start()

    local msg;
    local ret;
    local user_name = "Rm_St1"..os.date("%H%M%S");
    local user_name_2 = "Rm_St2"..os.date("%H%M%S");
    local user_name_3 = "Rm_St3"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();

	local user_2, role_2 = startup(user_name_2, user_name_2);
    check(user_2, "failed to create user");
    check(role_2, "failed to create role");
    local session_id_2 = user_2:GetSessionID();
    
   	local user_3, role_3 = startup(user_name_3, user_name_3);
    check(user_3, "failed to create user");
    check(role_3, "failed to create role");
    local session_id_3 = user_3:GetSessionID();
 
	InviteToTeam(user, role, user_2, role_2);
	wait(2);
	
	ret = g_RobotMessageHandler:DoRoomCreate(role, 102, esdNormal, 5, 1, 20, 15)
    check(ret, "failed to send create team");
    
	local retMsg = recv_msg_and(30, session_id, protocol.m2c_team_changeinfo, session_id_2, protocol.m2c_team_changeinfo);
    check(retMsg, "failed to received m2c_team_changeinfo");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");				
	end
	
	ret = g_RobotMessageHandler:DoRoomReady(role_2, 1);
    check(ret, "failed to send create team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_room_ready_change, session_id_2, protocol.m2c_room_ready_change);
    check(retMsg, "failed to received m2c_room_ready_change");

	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoleID == role_2:GetObjID(),"error m2c_room_ready_change msg for roleID");
		check(v.msg.byReady == 1,"error m2c_room_ready_change msg for byReady");	
	end
	
	ret = g_RobotMessageHandler:DoRoomAutoEnter(role_3);
    check(ret, "failed to send create team");

	msg = recv_msg(30, session_id_3, protocol.m2c_error_notify);
    check(msg, "failed to receive m2c_error_notify");

	ret = user_3:GMCommand("SetLevel(11)");
    check(ret, "exec GMCommand SummonNpc error");

	msg = recv_msg(30, session_id_3, protocol.g2c_role_level_up);
    check(msg, "failed to receive g2c_role_level_up");
    check(msg.byLevel == 11, "error g2c_role_level_up msg for byLevel");

	ret = g_RobotMessageHandler:DoRoomAutoEnter(role_3);
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id, protocol.m2c_team_answer);
    check(msg, "failed to received m2c_team_answer");
    check(msg.dwAnswerRequestRoleID == role_3:GetObjID(), "error m2c_team_answer msg for dwAnswerRequestRoleID");
	
	ret = g_RobotMessageHandler:DoTeamAnswer(role, msg.dwAnswerRequestRoleID, msg.byAnswerType, 0);
    check(ret, "failed to send team answer");

	msg = recv_msg(30, session_id_3, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_join");
    wait(5);
    
    ret = g_RobotMessageHandler:DoRoomReady(role_3, 1);
    check(ret, "failed to send create team");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_room_ready_change, session_id_2, protocol.m2c_room_ready_change,
	session_id_3, protocol.m2c_room_ready_change);
    check(retMsg, "failed to received m2c_room_ready_change");

	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		check(v.msg.dwRoleID == role_3:GetObjID(),"error m2c_room_ready_change msg for roleID");
		check(v.msg.byReady == 1,"error m2c_room_ready_change msg for byReady");	
	end

	ret = g_RobotMessageHandler:DoRoomStart(role);
    check(ret, "failed to send DoRoomStart");

	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_changeinfo,  session_id_2, protocol.m2c_team_changeinfo,
							  session_id_3, protocol.m2c_team_changeinfo,session_id, protocol.g2c_leave_scene, 
							  session_id, protocol.g2c_changescene_enter,session_id, protocol.g2c_enter_scene, 
							  session_id_2, protocol.g2c_leave_scene, session_id_2, protocol.g2c_changescene_enter, 
							  session_id_2, protocol.g2c_enter_scene, session_id_3, protocol.g2c_leave_scene, 
							  session_id_3, protocol.g2c_changescene_enter, session_id_3, protocol.g2c_enter_scene);
    check(retMsg, "failed to received m2c_team_changeinfo or jump msg");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
		if v.msgID == m2c_team_changeinfo then
			check(v.msg.dwRoomID == 0, "error m2c_team_changeinfo msg for roomID");
		end
	end

    wait(2);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.Team.TeamActivity()

	local msg;
	local ret;
	local user_name = "St12"..os.date("%H%M%S");
	local user_name_2 = "St22"..os.date("%H%M%S");

	local user1, role1 = startup(user_name, user_name);
	check(user1, "failed to create user");
	check(role1, "failed to create role");
	local session_id1 = user1:GetSessionID();
    local roleid1 = role1:GetObjID();

    local team_name = user_name.."team";

	local team_id = CreateTeam(team_name, user1, role1);
	check(team_id, "failed to create team");

	wait(5);
	
	ret = g_RobotMessageHandler:DoTeamChangeActivityInfo(role1, 1, 1);
	check(ret, "failed to send create team");
	
	wait(1);
	
	ret = g_RobotMessageHandler:DoTeamQueryActivityTeam(role1, 1, 1, 0);
	check(ret, "failed to send create team");	

	retMsg = recv_msg(30, session_id1, protocol.m2c_activity_query_team);
    check(retMsg, "failed to received m2c_activity_query_team");
	check(retMsg.dwActivityType == 1, "failed to check retMsg.dwActivityType");
	check(retMsg.nActivityID == 1, "failed to check retMsg.nActivityID");
	
	print "==========================================="	
	print (retMsg.stRoomTeam[0].nTeamID)
	print (team_id)
	check(retMsg.stRoomTeam[0].nTeamID == team_id, "failed to check retMsg.stRoomTeam");
	check(retMsg.stRoomTeam[0].nMemberID[0] == roleid1, "failed to check retMsg.stRoomTeam");

	ret = g_RobotMessageHandler:DoTeamRemoveActivityTeam(role1);
	check(ret, "failed to send remove team");		

	wait(1);
	ret = g_RobotMessageHandler:DoTeamQueryActivityTeam(role1, 1, 1, 0);
	check(ret, "failed to send create team");	

	retMsg = recv_msg(30, session_id1, protocol.m2c_activity_query_team);
    check(retMsg, "failed to received m2c_activity_query_team");
	check(retMsg.dwActivityType == 1, "failed to check retMsg.dwActivityType");
	check(retMsg.stRoomTeam[0].nTeamID == 0, "failed to check retMsg.stRoomTeam");
	check(retMsg.stRoomTeam[0].nMemberID[0] == 0, "failed to check retMsg.stRoomTeam");

end

function TestCase.Team.TeamAuction()
	local user_name1 = "Ta3"..os.date("%H%M%S");
	local user_name2 = "Ta4"..os.date("%H%M%S");
	
	local user1, role1 = startup(user_name1, user_name1, 1);
	check(user1, "failed to create user1");
	check(role1, "failed to create role1");
	local session_id1 = user1:GetSessionID();
    local roleid1 = role1:GetObjID();
    
  	local user2, role2 = startup(user_name2, user_name2, 1);
	check(user2, "failed to create user2");
	check(role2, "failed to create role2");
	local session_id2 = user2:GetSessionID();
    local roleid2 = role2:GetObjID();
    
    local team_name = user_name1.."team";
	local team_id = CreateTeam(team_name, user1, role1);
	check(team_id, "failed to create team");

	wait(5);

    InviteToTeam(user2, role2, user1, role1, 0);

	local msg = recv_msg_and(30, session_id1, protocol.m2c_team_add_member, session_id2, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_add_member or m2c_team_join");

	-- assign type change
   	ret = g_RobotMessageHandler:DoTeamChangeInfo(role1, 10, 1, roleid1, 1);
    check(ret, "failed to send create team");

    msg = recv_msg(30, session_id2, protocol.m2c_team_changeinfo);
    check(msg, "failed to received m2c_team_join");
    check(msg.byAssignType == 1, "failed to check byAssignType");
    check(msg.byAuctionItemColorLimit == 1, "failed to received m2c_team_join");
	
	-- role 1 and role 2 change scene
	ret = user1:GMCommand("Jump lgsm");
    check(ret, "exec GMCommand Jump lgz error");	

	ret = user2:GMCommand("Jump lgsm");
    check(ret, "exec GMCommand Jump lgz error");	
	
	wait(10);
	
    -- summonnpc and kill
	ret = user2:GMCommand("SummonNpc(5104, 1, 6)");
    check(ret, "exec GMCommand SummonNpc error");

	msg = recv_msg(40, session_id1, protocol.g2c_char_appear);
	check(msg, "failed to summon npc");
	check(msg.stAppearData.dwCharID ~= 0, "failed to summon npc with id");

	local npcid = msg.stAppearData.dwCharID;
    
    -- set focus
    
    ret = g_RobotMessageHandler:DoSelectFocus(role2, npcid);
    check(ret, "failed to send SelectFocus");

	msg = recv_msg(40, session_id2, protocol.g2c_char_select_focus);
	check(msg, "failed to recv protocol.g2c_char_select_focus");
    
	wait(3);
	
	ret = user2:GMCommand("kill");
    check(ret, "exec GMCommand kill error");

	wait(10);
	
    --msg = recv_msg(30, session_id2, protocol.g2c_sync_drop_list);	-- At least two drops should be received here, including one non-money drop
    --check(msg, "failed to received g2c_sync_drop_list");

	ret = g_RobotMessageHandler:DoPickUpItem(role2, 0, 1);
	check(ret, "failed to send DoPickUpItem");			

    --for k,v in pairs(msg) do
	--	if v.msg ~= nil then
	--		local itemcount = get_drop_list_item_count_from_gsmessage(v.msg);
	--		for index = 0, itemcount - 1 do
	--			local itemdata = get_drop_list_item_from_gsmessage(v.msg, index);	
	--			if  itemdata.nTemplateID ~= 0 and itemdata.nTemplateID ~= 1 and itemdata.nTemplateID ~= 2 then
	--				print("===================");
	--				print(itemdata.nTemplateID);
	--				print(itemdata.dwDropID);			
	--				print("===================");
	--
	--			end
	--		end	
	--	end	
	--end
    
    
    -- begin auction and bid begin
    msg = recv_msg_and(100, session_id1, protocol.g2c_team_auction_add_item, session_id1, protocol.g2c_team_auction_begin, session_id2, protocol.g2c_team_auction_add_item, session_id1, protocol.g2c_team_auction_begin);
    check(msg, "failed to received begin auction");
    
    -- use1 bid
    ret = g_RobotMessageHandler:DoTeamAuctionBid(role1, 0, 100);
    check(ret, "failed to send DoTeamAuctionBid");    

    msg = recv_msg_and(30, session_id1, protocol.g2c_team_auction_notify, session_id2, protocol.g2c_team_auction_notify);
    check(msg, "failed to received begin auction");

	wait(10);

    -- use2 bid
    ret = g_RobotMessageHandler:DoTeamAuctionBid(role2, 0, 200);
    check(ret, "failed to send DoTeamAuctionBid");    

    msg = recv_msg_and(30, session_id1, protocol.g2c_team_auction_notify, session_id2, protocol.g2c_team_auction_notify);
    check(msg, "failed to received begin auction");

	wait(10);

    -- use1 bid
    ret = g_RobotMessageHandler:DoTeamAuctionBid(role1, 0, 300);
    check(ret, "failed to send DoTeamAuctionBid");    

    msg = recv_msg_and(30, session_id1, protocol.g2c_team_auction_notify, session_id2, protocol.g2c_team_auction_notify);
    check(msg, "failed to received begin auction");	
    
    -- bid end

	wait(10);

    msg = recv_msg_and(30, session_id1, protocol.g2c_team_auction_end, session_id2, protocol.g2c_team_auction_end);
    check(msg, "failed to received begin end");	
    check(msg.dwRoleID == roleid1);
    check(msg.nItemID == itemid);    
    
    -- Error case: continue bidding after the auction ends
    --ret = g_RobotMessageHandler:DoTeamAuctionBid(role1, );
    --check(ret, "failed to send DoTeamAuctionBid");   
end
