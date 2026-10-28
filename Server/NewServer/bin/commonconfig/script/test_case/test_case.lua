TestCase = {};
CoverageTestCase = {};
PerfTestCase = {};

function get_scene_type(scene_temp_id)
	local scene_data = CDataManager_SCENE_DATA_:GetInstance():GetData(scene_temp_id);
	return scene_data.nType;
end

function run()
    for k,v in pairs(TestCase) do
		if type(v) == "function" then
	        addco(k, v);
	    elseif type(v) == "table" then
			for kk, vv in pairs(v) do
				if type(vv) == "function" then
					addco(k.."."..kk, vv);
				end
			end
	    end
    end    
end

function create_user(user_name, user_type, password, group_id)
    if not g_RunningCoName then
        return
    end
    return _create_user(user_name, user_type, password, group_id, g_RunningCoName);
end

function destory_user(user)
    if not g_RunningCoName then
        return
    end
    return _destory_user(user, g_RunningCoName);
end

function startup(user_name, role_name, group_id, cls, sex, port, nSceneTempID, bConnectBS)
    local ret;
    local msg;
    local role_id = 0;
    
    if group_id == nil then
		group_id = GROUP_ID;
    end

	local new_user = create_user(user_name, "pt", "1", group_id);
    
    if cls == nil then
		cls = clsWarrior;
    end

	if sex == nil then
		sex = cstMale;
	end

    if (port == nil) then
        port = SERVER_PORT;
    end

	if(bConnectBS == nil) then
		bConnectBS = true
	end
	
	ret = new_user:ConnectServer(SERVER_IP_ADDR, port, bConnectBS, true);
	check(ret, "failed to connected to server");

	msg = recv_msg(60, new_user:GetSessionID(), protocol.t2c_sync_role_list);
	check(msg, "failed to  recv t2c_sync_role_list");

    for i = 0, (msg.byCount - 1) do
        if msg.RoleData[i].szRoleName == role_name then
            role_id = msg.RoleData[i].dwRoleID;
			print(msg.RoleData[i].dwRoleID);
        end
    end

    if role_id == 0 then
        role_id = create_role(new_user, role_name, cls, sex);
        check(role_id, "failed to create role");
    end
    
	ret = enter_scene(new_user, role_id);
	check(ret, "failed to enter scene");

	msg = recv_msg(60, new_user:GetSessionID(), protocol.g2c_sync_game_data_begin)
	check(msg, "failed to recv g2c_attr_sync_begin");

	msg = recv_msg(60, new_user:GetSessionID(), protocol.g2c_sync_game_data_end)
	check(msg, "failed to recv g2c_attr_sync_end");

	msg = recv_msg(60, new_user:GetSessionID(), protocol.g2c_enter_scene)
	check(msg, "failed to recv g2c_enter_scene");

	msg = recv_msg(60, new_user:GetSessionID(), protocol.g2c_char_appear)
	check(msg, "failed to recv g2c_char_appear");

	--if (nSceneTempID == 1) then
        --ret = new_user:GMCommand("Jump(1, 0, 12000, 12000)");
        --check(ret, "failed to jump (1, 0, 12000, 12000)");
--
        --msg = recv_msg(20, new_user:GetSessionID(), protocol.g2c_leave_scene);
        --check(msg, "failed to  recv g2c_leave_scene");
--
        --msg = recv_msg(10, new_user:GetSessionID(), protocol.g2c_changescene_enter);
        --check(msg, "failed to  recv g2c_changescene_enter");
--
        --msg = recv_msg(10, new_user:GetSessionID(), protocol.g2c_enter_scene);
        --check(msg, "failed to  recv g2c_enter_scene");
--
        --msg = recv_msg(10, new_user:GetSessionID(), protocol.g2c_char_appear);
        --check(msg, "failed to  recv g2c_char_appear");
    --elseif(nSceneTempID == 100) then
	
	if nSceneTempID then
		JumpToSceneBySceneTempID(new_user, nSceneTempID, 0);
	end

	local role = new_user:GetPlayingRole();
	check(role, "failed to get playing role");

    return new_user, role;
end

function cleanup(user)
    local user_name = user:GetUserName();
    local session_id = user:GetSessionID();

    if (user:IsConnected()) then
        ret = user:Logout();
        check(ret, "failed to logout");
        
		msg = recv_msg(10, session_id, protocol.g2c_logout_timer, session_id, protocol.t2c_robot_disconnected);
		if(msg == nil) then
			msg = recv_msg(30, session_id, protocol.t2c_robot_disconnected);
			check(msg, "failed to receive t2c_robot_disconnected");
		elseif msg.wMsg == protocol.g2c_logout_timer then
			msg = recv_msg(msg.byDelayTime + 5, session_id, protocol.t2c_robot_disconnected);
			check(msg, "failed to receive t2c_robot_disconnected");
		end
    end

    destory_user(user);

    check(ret, "failed to delete user");
end

function login(user_name)
    check(g_user_mgr, "nil user mgr");

    local user = create_user(user_name, "pt", "a", GROUP_ID);
    check(user, "nil user");

    local session_id = user:GetSessionID();
    check(session_id, "error session_id");

    ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");

    msg = recv_msg(30, session_id, protocol.b2c_robot_connected);
    check(msg, "failed to receive b2c_robot_connected");

    msg = recv_msg(30, session_id, protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    ret = user:Login();
    check(ret, "failed to login");

    msg = recv_msg(30, session_id, protocol.t2c_login_ack);
    check(msg, "failed to receive t2c_login_ack");

    msg = recv_msg(30, session_id, protocol.t2c_sync_role_list);
    check(msg, "failed to  recv t2c_sync_role_list");

    return user;
end

CommandList = {
    "addco('shut', TestShutdownBegin)",
    "TestShutdownEnd()", 
    "TestRobot(5000)",
    "TestChat(1, 100, 100)", 
	--"Command_Login(5)",
	--"Command_GameLogic(1)",
	--"Command_DBLoad(5)",
	--"Command_DBOperate(1)",
	"TraverseAllAchievements()",  -- 遍历成就系统
}

Include("script/test_case/functionality/healingwell.lua");
Include("script/test_case/functionality/login.lua");
Include("script/test_case/functionality/item.lua");
Include("script/test_case/functionality/drop.lua");
Include("script/test_case/functionality/stall.lua");
Include("script/test_case/functionality/quest.lua");
Include("script/test_case/functionality/spell.lua");
Include("script/test_case/functionality/move.lua");
Include("script/test_case/functionality/framework.lua");
Include("script/test_case/functionality/jump.lua");
Include("script/test_case/functionality/team.lua");
Include("script/test_case/functionality/teamjump.lua");
Include("script/test_case/functionality/chat.lua");
--Include("script/test_case/functionality/server_test.lua");
Include("script/test_case/functionality/ai_table_btnod.lua");
Include("script/test_case/functionality/balanceserver.lua");
Include("script/test_case/functionality/friend.lua");
Include("script/test_case/functionality/score.lua");
Include("script/test_case/functionality/title.lua");
Include("script/test_case/functionality/master.lua");
Include("script/test_case/functionality/guild.lua");
Include("script/test_case/functionality/group_line.lua");
Include("script/test_case/functionality/trade.lua");
Include("script/test_case/functionality/achievement.lua");
Include("script/test_case/functionality/arena_team.lua");
Include("script/test_case/functionality/battle_queue.lua");
Include("script/test_case/functionality/reputation.lua");
Include("script/test_case/functionality/blackmarket.lua");
Include("script/test_case/functionality/mail.lua");
Include("script/test_case/functionality/hero.lua");
Include("script/test_case/functionality/ranklist.lua");
Include("script/test_case/functionality/weather.lua");
Include("script/test_case/functionality/spirit.lua");
Include("script/test_case/functionality/adventure.lua");
Include("script/test_case/functionality/gm.lua");

Include("script/test_case/coverage/quest.lua");
Include("script/test_case/coverage/combat.lua");

Include("script/test_case/performance/performance_base.lua");
Include("script/test_case/performance/test_login.lua");
Include("script/test_case/performance/test_db_operate.lua");
Include("script/test_case/performance/test_game_logic.lua");
Include("script/test_case/performance/create_role.lua");
