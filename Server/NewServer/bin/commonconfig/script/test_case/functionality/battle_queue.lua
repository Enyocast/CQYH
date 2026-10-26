TestCase.BattleQueue = {};

function TestCase.BattleQueue.BattleQueueJoinTest()
    local msg;
    local ret = 0;
    local user_name = "BQ_Test1"..os.date("%H%M%S");
    local user_name2 = "BQ_Test2"..os.date("%H%M%S");
    local user_name3 = "BQ_Test3"..os.date("%H%M%S");

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

    ret = g_RobotMessageHandler:DoJoinBattle(role, 1);
    check(ret, "failed to send Join Battle Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to recv m2c_join_battle_queue");
    
    ret = g_RobotMessageHandler:DoTeamJoin(role, role_id_2);
    check(ret, "failed to send Join team");

    msg = recv_msg(30, session_id, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");
    
    ret = g_RobotMessageHandler:DoTeamJoin(role_2, role_id);
    check(ret, "failed to send Join team");

    msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");

    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(role);
    check(ret, "failed to send Join Battle Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to recv m2c_cancel_join_battle_ack");

	InviteToTeam(user_2, role_2, user_3, role_3, 0);

	local retMsg = recv_msg_and(30, session_id_2, protocol.m2c_team_join, session_id_3, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    ret = g_RobotMessageHandler:DoJoinBattle(role_3, 1);
    check(ret, "failed to send Join Battle Req");

	msg = recv_msg(30, session_id_3, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_3);
	wait(5);
	
	user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    session_id_3 = user_3:GetSessionID();
    role_id_3 = role_3:GetObjID();

    ret = g_RobotMessageHandler:DoJoinBattle(role_2, 1);
    check(ret, "failed to send Join Battle Req");

	retMsg = recv_msg_and(30, session_id_2, protocol.m2c_join_battle_queue, session_id_3, protocol.m2c_join_battle_queue);
    check(retMsg, "failed to received m2c_join_battle_queue");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoTeamLeave(role_2, role_id_3);
    check(ret, "failed to send Leave team");

    msg = recv_msg(30, session_id_2, protocol.m2c_error_notify);
    check(msg, "failed to received m2c_error_notify");

    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(role_3);
    check(ret, "failed to send Join Battle Req");

	retMsg = recv_msg_and(30, session_id_2, protocol.m2c_cancel_join_battle_ack, session_id_3, protocol.m2c_cancel_join_battle_ack);
    check(retMsg, "failed to received m2c_cancel_join_battle_ack");
    
    ret = g_RobotMessageHandler:DoJoinBattle(role_2, 1);
    check(ret, "failed to send Join Battle Req");

	retMsg = recv_msg_and(30, session_id_2, protocol.m2c_join_battle_queue, session_id_3, protocol.m2c_join_battle_queue);
    check(retMsg, "failed to received m2c_join_battle_queue");

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

    ret = g_RobotMessageHandler:DoJoinBattle(role_2, 1);
    check(ret, "failed to send Join Battle Req");

	retMsg = recv_msg_and(30, session_id_2, protocol.m2c_join_battle_queue, session_id_3, protocol.m2c_join_battle_queue);
    check(retMsg, "failed to received m2c_join_battle_queue");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(5);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
end

function TestCase.BattleQueue.BattleQueueStartTest_1()
    local msg;
    local ret = 0;
    local user_name = "BQ1_Test1"..os.date("%H%M%S");
    local user_name2 = "BQ1_Test2"..os.date("%H%M%S");
    local user_name3 = "BQ1_Test3"..os.date("%H%M%S");
    local user_name4 = "BQ1_Test4"..os.date("%H%M%S");
    local user_name5 = "BQ1_Test5"..os.date("%H%M%S");
    local user_name6 = "BQ1_Test6"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
    user:GMCommand('level 20');
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    user_2:GMCommand('level 20');
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
    user_3:GMCommand('level 20');

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    user_4:GMCommand('level 20');

    local user_5,role_5 = startup(user_name5, user_name5);
    check(user_5, "failed to create user5");
    check(role_5, "failed to create role5");
    local session_id_5 = user_5:GetSessionID();
    local role_id_5 = role_5:GetObjID();
    user_5:GMCommand('level 20');

    local user_6, role_6 = startup(user_name6, user_name6);
    check(user_6, "failed to create user6");
    check(role_6, "failed to create role6");
    local session_id_6 = user_6:GetSessionID();
    local role_id_6 = role_6:GetObjID();
    user_6:GMCommand('level 20');
    
    wait(5);
    
    ret = g_RobotMessageHandler:DoJoinBattle(role, 1);
    check(ret, "failed to send create arena team");
    
    ret = g_RobotMessageHandler:DoJoinBattle(role_2, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_3, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_4, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_5, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_6, 1);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_battle_confirm_req, session_id_2, protocol.m2c_join_battle_confirm_req,
									session_id_3, protocol.m2c_join_battle_confirm_req, session_id_4, protocol.m2c_join_battle_confirm_req,
									session_id_5, protocol.m2c_join_battle_confirm_req, session_id_6, protocol.m2c_join_battle_confirm_req);
    check(retMsg, "failed to received m2c_join_battle_confirm_req");
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_2, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_3, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_4, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_5, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_6, 0);
    check(ret, "failed to send Join Battle Confirm");

    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, session_id_2, protocol.g2c_changescene_enter, 
			  session_id_3, protocol.g2c_changescene_enter, session_id_4, protocol.g2c_changescene_enter,
			  session_id_5, protocol.g2c_changescene_enter, session_id_6, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    wait(10);
    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
    cleanup(user_5);
    cleanup(user_6);
end

function TestCase.BattleQueue.BattleQueueStartTest_2()
    local msg, ret;
    local user = {};
    
    for i=1,11 do 
        user[i] = {};
        user[i].name = "BQ2_T"..i..os.date("%H%M%S");
        user[i].user, user[i].role = startup(user[i].name, user[i].name);
        check(user[i].user, "failed to create user");
        check(user[i].role, "failed to create role");
        user[i].session_id = user[i].user:GetSessionID();
        user[i].role_id = user[i].role:GetObjID();
        user[i].user:GMCommand('level 20');
    end
    
    wait(5);

    ---------------------------------
    for i = 2, 3 do
        InviteToTeam(user[1].user, user[1].role, user[i].user, user[i].role, 0);
	    msg = recv_msg(30, user[i].session_id, protocol.m2c_team_join);
        check(msg, "failed to received m2c_team_add_member or m2c_team_join");
    end
    
    ret = g_RobotMessageHandler:DoJoinBattle(user[1].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[1].session_id, protocol.m2c_join_battle_queue, 
	                       user[2].session_id, protocol.m2c_join_battle_queue,
						   user[3].session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to received m2c_join_battle_ack");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ---------------------------------
    InviteToTeam(user[4].user, user[4].role, user[5].user, user[5].role, 0);
    msg = recv_msg_and(30, user[4].session_id, protocol.m2c_team_join, user[5].session_id, protocol.m2c_team_join);
    check(msg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(msg) do
	    check(v.msg, "fail to recv msg "..k);
    end

    ret = g_RobotMessageHandler:DoJoinBattle(user[4].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[4].session_id, protocol.m2c_join_battle_queue, 
	                       user[5].session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to received m2c_join_battle_queue");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv msg "..k);
	end

    ---------------------------------
    for i = 7, 9 do
        InviteToTeam(user[6].user, user[6].role, user[i].user, user[i].role, 0);
	    msg = recv_msg(30, user[i].session_id, protocol.m2c_team_join);
        check(msg, "failed to received m2c_team_add_member or m2c_team_join");
    end

    ret = g_RobotMessageHandler:DoJoinBattle(user[6].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[6].session_id, protocol.m2c_join_battle_queue, 
	                       user[7].session_id, protocol.m2c_join_battle_queue,
	                       user[8].session_id, protocol.m2c_join_battle_queue,
						   user[9].session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to received m2c_join_battle_ack");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ---------------------------------

    ret = g_RobotMessageHandler:DoJoinBattle(user[10].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[1].session_id, protocol.m2c_join_battle_confirm_req, 
						   user[4].session_id, protocol.m2c_join_battle_confirm_req,
						   user[6].session_id, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv msg "..k);
	end
    -----------------------------
	
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[1].role, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[2].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[3].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[4].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[5].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[10].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg_and(30, user[1].session_id, protocol.g2c_changescene_enter, 
                           user[2].session_id, protocol.g2c_changescene_enter, 
			               user[3].session_id, protocol.g2c_changescene_enter, 
			               user[4].session_id, protocol.g2c_changescene_enter,
			               user[5].session_id, protocol.g2c_changescene_enter, 
			               user[10].session_id, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");

    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end
    wait(5);
    -----------------------------
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[11].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, user[11].session_id, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user[11].user);
	wait(5);
	
	user[11].user, user[11].role = startup(user[11].name, user[11].name);
    check(user[11].user, "failed to create user10");
    check(user[11].role, "failed to create role10");
    user[11].session_id = user[11].user:GetSessionID();
    user[11].role_id = user[11].role:GetObjID();

	ret = g_RobotMessageHandler:DoJoinBattle(user[11].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, user[11].session_id, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[11].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, user[11].session_id, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");
	wait(5);

    -----------------------------
    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(user[6].role);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[6].session_id, protocol.m2c_cancel_join_battle_ack, 
	                          user[7].session_id, protocol.m2c_cancel_join_battle_ack,
							  user[8].session_id, protocol.m2c_cancel_join_battle_ack, 
							  user[9].session_id, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to received m2c_cancel_join_battle_ack");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
	LeaveTeam(user[8].user, user[8].role);
	LeaveTeam(user[9].user, user[9].role);
	wait(5);
	
	------------------------------
	ret = g_RobotMessageHandler:DoJoinBattle(user[6].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg_and(30, user[6].session_id, protocol.m2c_join_battle_confirm_req, 
	                          user[7].session_id, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[6].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[7].role, 0);
    check(ret, "failed to send Join Battle Confirm");

	msg = recv_msg_and(30, user[6].session_id, protocol.g2c_changescene_enter, 
	                          user[7].session_id, protocol.g2c_changescene_enter);
    check(msg, "failed to received g2c_changescene_enter");
    for k,v in pairs(msg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ---------------------------
	ret = g_RobotMessageHandler:DoJoinBattle(user[8].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, user[8].session_id, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");

	ret = g_RobotMessageHandler:DoJoinBattle(user[9].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, user[9].session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to received m2c_join_battle_confirm_req");
	wait(60);
	
	ret = g_RobotMessageHandler:DoCancelJoinBattleReq(user[9].role);
    check(ret, "failed to send DoCancelJoinBattleReq");
    
	msg = recv_msg(30, user[9].session_id, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to received m2c_join_battle_confirm_req");

	ret = g_RobotMessageHandler:DoJoinBattle(user[9].role, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, user[9].session_id, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[9].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, user[9].session_id, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(user[8].role, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, user[8].session_id, protocol.m2c_error_notify);  
    check(msg, "failed to receive m2c_error_notify");
    
    ret = g_RobotMessageHandler:DoJoinBattle(user[8].role, 1);
    check(ret, "failed to send DoJoinBattle");

	msg = recv_msg(30, user[8].session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to received m2c_join_battle_queue");

	wait(5);
	
	for i=1, 11 do
        cleanup(user[i].user);	
	end
end

function TestCase.BattleQueue.BattleQueueStartTest_3()
    local msg;
    local ret = 0;
    local user_name = "BQ3_Test1"..os.date("%H%M%S");
    local user_name2 = "BQ3_Test2"..os.date("%H%M%S");
    local user_name3 = "BQ3_Test3"..os.date("%H%M%S");
    local user_name4 = "BQ3_Test4"..os.date("%H%M%S");
    local user_name5 = "BQ3_Test5"..os.date("%H%M%S");
    local user_name6 = "BQ3_Test6"..os.date("%H%M%S");
    local user_name7 = "BQ3_Test7"..os.date("%H%M%S");
    local user_name8 = "BQ3_Test8"..os.date("%H%M%S");
    local user_name9 = "BQ3_Test9"..os.date("%H%M%S");
    local user_name10 = "BQ3_Test10"..os.date("%H%M%S");
    local user_name11 = "BQ3_Test11"..os.date("%H%M%S");


    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    local role_id = role:GetObjID();
    user:GMCommand('level 20');
	
    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    user_2:GMCommand('level 20');
    
    local user_3, role_3 = startup(user_name3, user_name3);
    check(user_3, "failed to create user3");
    check(role_3, "failed to create role3");
    local session_id_3 = user_3:GetSessionID();
    local role_id_3 = role_3:GetObjID();
    user_3:GMCommand('level 20');

    local user_4, role_4 = startup(user_name4, user_name4);
    check(user_4, "failed to create user4");
    check(role_4, "failed to create role4");
    local session_id_4 = user_4:GetSessionID();
    local role_id_4 = role_4:GetObjID();
    user_4:GMCommand('level 20');
    
    local user_5,role_5 = startup(user_name5, user_name5);
    check(user_5, "failed to create user5");
    check(role_5, "failed to create role5");
    local session_id_5 = user_5:GetSessionID();
    local role_id_5 = role_5:GetObjID();
    user_5:GMCommand('level 20');

    local user_6, role_6 = startup(user_name6, user_name6);
    check(user_6, "failed to create user6");
    check(role_6, "failed to create role6");
    local session_id_6 = user_6:GetSessionID();
    local role_id_6 = role_6:GetObjID();
    user_6:GMCommand('level 20');
    
    local user_7, role_7 = startup(user_name7, user_name7);
    check(user_7, "failed to create user7");
    check(role_7, "failed to create role7");
    local session_id_7 = user_7:GetSessionID();
    local role_id_7 = role_7:GetObjID();
    user_7:GMCommand('level 20');

    local user_8, role_8 = startup(user_name8, user_name8);
    check(user_8, "failed to create user8");
    check(role_8, "failed to create role8");
    local session_id_8 = user_8:GetSessionID();
    local role_id_8 = role_8:GetObjID();
    user_8:GMCommand('level 20');
    
    local user_9, role_9 = startup(user_name9, user_name9);
    check(user_9, "failed to create user9");
    check(role_9, "failed to create role9");
    local session_id_9 = user_9:GetSessionID();
    local role_id_9 = role_9:GetObjID();
    user_9:GMCommand('level 20');

    local user_10, role_10 = startup(user_name10, user_name10);
    check(user_10, "failed to create user10");
    check(role_10, "failed to create role10");
    local session_id_10 = user_10:GetSessionID();
    local role_id_10 = role_10:GetObjID();
    user_10:GMCommand('level 20');
    
    local user_11, role_11 = startup(user_name11, user_name11);
    check(user_11, "failed to create user11");
    check(role_11, "failed to create role11");
    local session_id_11 = user_11:GetSessionID();
    local role_id_11 = role_11:GetObjID();
    user_11:GMCommand('level 20');

    wait(5);

    InviteToTeam(user, role, user_2, role_2, 0);
	local retMsg = recv_msg_and(30, session_id, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
        for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
    
    InviteToTeam(user, role, user_3, role_3, 0);
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_add_member, 
							  session_id_3, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    InviteToTeam(user, role, user_4, role_4, 0);
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_add_member, 
							  session_id_3, protocol.m2c_team_add_member, session_id_4, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    InviteToTeam(user, role, user_5, role_5, 0);
	retMsg = recv_msg_and(30, session_id, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_add_member, 
							  session_id_3, protocol.m2c_team_add_member, session_id_4, protocol.m2c_team_add_member,
							  session_id_5, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    ret = g_RobotMessageHandler:DoJoinBattle(role, 1);
    check(ret, "failed to send create arena team");
    
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_battle_queue, session_id_2, protocol.m2c_join_battle_queue,
							session_id_3, protocol.m2c_join_battle_queue, session_id_4, protocol.m2c_join_battle_queue,
							session_id_5, protocol.m2c_join_battle_queue);
    check(retMsg, "failed to received m2c_join_battle_ack");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    
    InviteToTeam(user_6, role_6, user_7, role_7, 0);
	local retMsg = recv_msg_and(30, session_id_6, protocol.m2c_team_join, session_id_7, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    

    InviteToTeam(user_6, role_6, user_8, role_8, 0);
	retMsg = recv_msg_and(30, session_id_6, protocol.m2c_team_add_member, session_id_7, protocol.m2c_team_add_member, 
							  session_id_8, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    InviteToTeam(user_6, role_6, user_9, role_9, 0);
	retMsg = recv_msg_and(30, session_id_6, protocol.m2c_team_add_member, session_id_7, protocol.m2c_team_add_member, 
							  session_id_8, protocol.m2c_team_add_member, session_id_9, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
    
    ret = g_RobotMessageHandler:DoJoinBattle(role_6, 1);
    check(ret, "failed to send create arena team");

   
	retMsg = recv_msg_and(30, session_id, protocol.m2c_join_battle_confirm_req, session_id_2, protocol.m2c_join_battle_confirm_req,
									session_id_3, protocol.m2c_join_battle_confirm_req, session_id_4, protocol.m2c_join_battle_confirm_req,
									session_id_5, protocol.m2c_join_battle_confirm_req, session_id_6, protocol.m2c_join_battle_confirm_req, 
									session_id_7, protocol.m2c_join_battle_confirm_req, session_id_8, protocol.m2c_join_battle_confirm_req, 
									session_id_9, protocol.m2c_join_battle_confirm_req);
    check(retMsg, "failed to received m2c_join_battle_confirm_req");
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_2, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_3, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_4, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_5, 0);
    check(ret, "failed to send Join Battle Confirm");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_6, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_7, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_8, 0);
    check(ret, "failed to send Join Battle Confirm");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_9, 0);
    check(ret, "failed to send Join Battle Confirm");

    retMsg = recv_msg_and(30, session_id, protocol.g2c_changescene_enter, session_id_2, protocol.g2c_changescene_enter, 
			  session_id_3, protocol.g2c_changescene_enter, session_id_4, protocol.g2c_changescene_enter,
			  session_id_5, protocol.g2c_changescene_enter, session_id_6, protocol.g2c_changescene_enter, 
			  session_id_7, protocol.g2c_changescene_enter, session_id_8, protocol.g2c_changescene_enter, 
			  session_id_9, protocol.g2c_changescene_enter);  
    check(retMsg, "failed to receive g2c_changescene_enter");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	ret = g_RobotMessageHandler:DoJoinBattle(role_10, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, session_id_10, protocol.m2c_join_battle_confirm_req);
    check(retMsg, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_10, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, session_id_10, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");

	ret = g_RobotMessageHandler:DoJoinBattle(role_11, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(15, session_id_11, protocol.m2c_join_battle_confirm_req);
    check(msg == nil, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(role_11);
    check(ret, "failed to send Join Battle Req");
    
    msg = recv_msg(30, session_id_11, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to recv m2c_cancel_join_battle_ack");
    
    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_10, 0);
    check(ret, "failed to send Join Battle Confirm");

	msg = recv_msg(30, session_id_10, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_10);
	wait(5);
	
	ret = g_RobotMessageHandler:DoJoinBattle(role_11, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(15, session_id_11, protocol.m2c_join_battle_confirm_req);
    check(msg == nil, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(role_11);
    check(ret, "failed to send Join Battle Req");
    
    msg = recv_msg(30, session_id_11, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to recv m2c_cancel_join_battle_ack");

    user_10, role_10 = startup(user_name10, user_name10);
    check(user_10, "failed to create user10");
    check(role_10, "failed to create role10");
    session_id_10 = user_10:GetSessionID();
    role_id_10 = role_10:GetObjID();
    
    local nSceneTempID = role_10:GetSceneTempID();
    check(nSceneTempID == 103, "error SceneTempID");

    cleanup(user_10);
	wait(5);
	
	user_10, role_10 = startup(user_name10, user_name10);
    check(user_10, "failed to create user10");
    check(role_10, "failed to create role10");
    session_id_10 = user_10:GetSessionID();
    role_id_10 = role_10:GetObjID();
    
    nSceneTempID = role_10:GetSceneTempID();
    check(nSceneTempID ~= 103, "error SceneTempID");

	ret = g_RobotMessageHandler:DoJoinBattle(role_11, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, session_id_11, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");

	ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_11, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, session_id_11, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");
	wait(5);

    ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_11, 0);
    check(ret, "failed to send Join Battle Confirm");

	msg = recv_msg(30, session_id_11, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");
	cleanup(user_11);
	wait(5);

	ret = g_RobotMessageHandler:DoJoinBattle(role_10, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(15, session_id_10, protocol.m2c_join_battle_confirm_req);
    check(msg == nil, "failed to received m2c_join_battle_confirm_req");

    ret = g_RobotMessageHandler:DoCancelJoinBattleReq(role_10);
    check(ret, "failed to send Join Battle Req");
    
    msg = recv_msg(30, session_id_10, protocol.m2c_cancel_join_battle_ack);
    check(msg, "failed to recv m2c_cancel_join_battle_ack");
	wait(120);
	
	ret = g_RobotMessageHandler:DoJoinBattle(role_10, 1);
    check(ret, "failed to send create arena team");

	msg = recv_msg(30, session_id_10, protocol.m2c_join_battle_confirm_req);
    check(msg, "failed to received m2c_join_battle_confirm_req");

	ret = g_RobotMessageHandler:DoJoinBattleConfirm(role_10, 0);
    check(ret, "failed to send Join Battle Confirm");

    msg = recv_msg(30, session_id_10, protocol.g2c_changescene_enter);  
    check(msg, "failed to receive g2c_changescene_enter");
	wait(5);
	
    user_11, role_11 = startup(user_name11, user_name11);
    check(user_11, "failed to create user11");
    check(role_11, "failed to create role11");
    session_id_11 = user_11:GetSessionID();
    role_id_11 = role_11:GetObjID();
    
    nSceneTempID = role_11:GetSceneTempID();
    check(nSceneTempID ~= 103, "error SceneTempID");
	wait(5);

    cleanup(user);
    cleanup(user_2);
    cleanup(user_3);
    cleanup(user_4);
    cleanup(user_5);
    cleanup(user_6);
    cleanup(user_7);
    cleanup(user_8);
    cleanup(user_9);
    cleanup(user_10);
    cleanup(user_11);
end


function TestCase.BattleQueue.BattleQueueJoinAndCancelArenaQueue()
    local msg;
    local ret = 0;
    local user_name = "BAQ1_Test1"..os.date("%H%M%S");
    local user_name2 = "BAQ2_Test1"..os.date("%H%M%S");
    local user_name3 = "BAQ3_Test1"..os.date("%H%M%S");
    local user_name4 = "BAQ4_Test1"..os.date("%H%M%S");
    local user_name5 = "BAQ5_Test1"..os.date("%H%M%S");
    local user_name6 = "BAQ6_Test1"..os.date("%H%M%S");

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
    
    ret = g_RobotMessageHandler:DoJoinBattle(role, 1);
    check(ret, "failed to send create arena team");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_battle_queue);
    check(msg, "failed to recv m2c_join_battle_queue");

    ret = g_RobotMessageHandler:DoJoinArena(role);
    check(ret, "failed to send Join Arena Req");
    
    msg = recv_msg(30, session_id, protocol.m2c_join_arena_queue);
    check(msg, "failed to recv m2c_join_battle_ack");

    ret = g_RobotMessageHandler:DoJoinBattle(role_2, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_3, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_4, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_5, 1);
    check(ret, "failed to send create arena team");

    ret = g_RobotMessageHandler:DoJoinBattle(role_6, 1);
    check(ret, "failed to send create arena team");

	local retMsg = recv_msg_and(30, session_id, protocol.m2c_join_battle_confirm_req, session_id_2, protocol.m2c_join_battle_confirm_req,
									session_id_3, protocol.m2c_join_battle_confirm_req, session_id_4, protocol.m2c_join_battle_confirm_req,
									session_id_5, protocol.m2c_join_battle_confirm_req, session_id_6, protocol.m2c_join_battle_confirm_req,
									session_id, protocol.m2c_cancel_join_arena_ack);
    check(retMsg, "failed to received m2c_join_battle_confirm_req");
    
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