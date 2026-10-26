
TestCase.Login = {};

function TestCase.Login.Normal()
    local user_name = "LoNor"..os.date("%H%M%S");
    local user = login(user_name);
    
    cleanup(user);
end

function TestCase.Login.CreateGMRole()
	local name_table = {
		{ user_name = "3400224448", role_name = "1GM.传奇之光", class = clsWarrior, sex = cstMale },
		{ user_name = "3400225096", role_name = "2GM.冷漠红太狼", class = clsMage, sex = cstFemale },
		{ user_name = "3400225479", role_name = "3GM.冷漠大灰狼", class = clsRogue, sex = cstMale },
		{ user_name = "3400225723", role_name = "44GM.传奇之火", class = clsArcher, sex = cstFemale },
		{ user_name = "3400225949", role_name = "5GM.传奇永恒", class = clsWarrior, sex = cstMale },
		{ user_name = "3400226109", role_name = "6GM.传奇盛典", class = clsMage, sex = cstFemale },
		{ user_name = "3400226268", role_name = "7GM.传奇霸主", class = clsRogue, sex = cstMale },
		{ user_name = "3400226530", role_name = "8GM.传奇豆豆", class = clsArcher, sex = cstFemale },
		{ user_name = "3400226712", role_name = "9GM.大麦龙", class = clsWarrior, sex = cstMale },
		{ user_name = "3400226840", role_name = "0GM.小米粒", class = clsMage, sex = cstFemale },
	};

	for _, n in pairs(name_table) do
		local user = startup(n.user_name, n.role_name, 1, n.class, n.sex );

		cleanup(user);
	end
end

function TestCase.Login.MultiGate()
    local ret;
    local msg;
    local user_test = "test"..os.date("%H%M%S");
    local user_name_1 = "mg1"..os.date("%Y%H%M%S");
    local user_name_2 = "mg2"..os.date("%Y%H%M%S");

    local new_user = create_user(user_test, "pt", "1", GROUP_ID);
    ret = new_user:ConnectServer(SERVER_IP_ADDR, 8702, false);

    msg = recv_msg(30, new_user:GetSessionID(), protocol.t2c_robot_connected);

    if msg ~= nil then
	local user1 = startup(user_name_1, user_name_1);
	local user2 = startup(user_name_2, user_name_2, nil, nil, nil, 8702);
	ret = user2:GMCommand("JumpTo()");    
	wait(5);
	cleanup(user1);
	cleanup(user2);
    end

    cleanup(new_user);
end

function TestCase.Login.Overtime1()
    local ret;
    local msg;
    local user_name = "LOt1"..os.date("%H%M%S");
    
    check(g_user_mgr, "nil user mgr");

    local user = create_user(user_name, "pt", "a", GROUP_ID);
    check(user, "nil user");
    
    ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");
    
    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    msg = recv_msg(40, user:GetSessionID(), protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");

    cleanup(user);
end

function TestCase.Login.Overtime2()
    local ret;
    local msg;
    local user_name = "LOt2"..os.date("%H%M%S");

    check(g_user_mgr, "nil user mgr");

    local user = create_user(user_name, "pt", "a", GROUP_ID);
    check(user, "nil user");

    ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");

    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    ret = user:Login();
    check(ret, "failed to login");

    msg = recv_msg(100, user:GetSessionID(), protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");

    cleanup(user);
end

function TestCase.Login.Overtime3()
    local ret;
    local msg;
    local user_name = "LOt3"..os.date("%H%M%S");
    local role_id = 0;

    local user = login(user_name);
    check(user, "can't login");

    local session_id = user:GetSessionID();

    if user:GetRoleCount() == 0 then
    	role_id = create_role(user, user_name);
	    check(role_id, "failed to create role");
    else
    	local role = user:GetRoleByIndex(0);
	    check(role, "failed to get role");
	    role_id = role:GetObjID();
    end
    
    ret = user:SelectRole(role_id);
    check(ret, "select role error");

    msg = recv_msg(15, session_id, protocol.g2c_sync_game_data_begin);
    check(msg, "failed to receive g2c_attr_sync_end");

    msg = recv_msg(15, session_id, protocol.g2c_sync_game_data_end);
    check(msg, "failed to receive g2c_attr_sync_end");

    msg = recv_msg(310, session_id, protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");

    cleanup(user);
end

function TestCase.Login.CreateRole()
    local ret;
    local msg;
    local user_name = "cr"..os.date("%Y%H%M%S");
    local role_name = {
        [1] = user_name.."_0", 
        [2] = user_name.."_1",
        [3] = user_name.."_2",
        [4] = user_name.."_3",
        [5] = user_name.."_4"
    };

-- create first role
    local user = login(user_name);
    local session_id = user:GetSessionID();

    ret = user:CreateRole(role_name[1], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");
    
    cleanup(user);
    wait(5);

-- try to create the same name role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 1, "error role count");

    role = user:GetRoleByIndex(0);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[1], "error role name");

    ret = user:CreateRole(role_name[1], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_error_notify);
    print(msg.nErrCode);
    print(error_code.errLoginCreateRoleDupeName);
    check(msg.nErrCode == error_code.errLoginCreateRoleDupeName, "failed to  recv errLoginCreateRoleDupeName");

    cleanup(user);
    wait(5);

-- create second role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 1, "error role count");
    
    role = user:GetRoleByIndex(0);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[1], "error role name");
    
    ret = user:CreateRole(role_name[2], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");

    cleanup(user);
    wait(5);

-- create third role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 2, "error role count");
    
    role = user:GetRoleByIndex(0);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[1], "error role name");

    role = user:GetRoleByIndex(1);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[2], "error role name");

    ret = user:CreateRole(role_name[3], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");

    cleanup(user);
    wait(5);

-- create fourth role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 3, "error role count");
    
    ret = user:CreateRole(role_name[4], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");

    cleanup(user);
    wait(5);

-- check fourth role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 4, "error role count");
    
    role = user:GetRoleByIndex(0);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[1], "error role name");
    
    role = user:GetRoleByIndex(1);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[2], "error role name");

    role = user:GetRoleByIndex(2);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[3], "error role name");

    role = user:GetRoleByIndex(3);
    check(role, "failed to find created role");
    check(role:GetName() == role_name[4], "error role name");

    cleanup(user);
    wait(5);

-- try to Create fifth role
    user = login(user_name);
    session_id = user:GetSessionID();

    check(user:GetRoleCount() == 4, "error role count");
    
    ret = user:CreateRole(role_name[5], 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_robot_disconnected);
    check(msg, "failed to  recv t2c_robot_disconnected");

    cleanup(user);
end

function TestCase.Login.CreateRoleWithCensoredWord()
    local ret, msg;
    local user_name = "cr"..os.date("%H%M%S");
    local role_name = {
        [1] = {name = "毛泽东", ret = true}, 
        [2] = {name = "邓小平", ret = true},
        [3] = {name = "江泽民", ret = true},
		[4] = {name = "胡锦涛", ret = true},
        [5] = {name = "习近平", ret = true},
        [6] = {name = "李洪志", ret = true},
        [7] = {name = "朱剑丘", ret = false},
    };

    local user = login(user_name);
    local session_id = user:GetSessionID();

	for i = 1, #role_name do 
		ret = user:CreateRole(role_name[i].name, 1, 1, 1, 1, 1);
		check(ret, "failed to create role "..role_name[i].name);

		if role_name[i].ret then
			msg = recv_msg(30, session_id, protocol.t2c_error_notify);
			check(msg.nErrCode == error_code.errLoginCreateRoleCensoredWord, "failed to  recv t2c_error_notify with role name "..role_name[i].name);
		else
			msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
			check(msg, "failed to  recv t2c_create_role_ack with role name "..role_name[i].name);
		end
	end
	    
    cleanup(user);
end

function TestCase.Login.TestStartup()
    local user_name = "test"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);

    wait(5);

    cleanup(user);
    
    wait(3);

    local user, role = startup(user_name, user_name);

    wait(5);

    cleanup(user);
end;

function TestCase.Login.OATestStartup()
	local i = 2;
	local userList = {};
	local roleList = {};
	
	while i <= 5 do
		local user_name = "gmjy000"..i;
		userList[i], roleList[i] = startup(user_name, user_name);
		i = i + 1;
	end
	wait(5);
	
	i = 2;
	while i <= 5 do
	    cleanup(userList[i]);
		i = i + 1;
	end
	
    wait(3);
	
	i = 2;
	while i <= 5 do
		local user_name = "gmjy000"..i;
		userList[i], roleList[i] = startup(user_name, user_name);
		i = i + 1;
	end
	wait(5);
	
	i = 2;
	while i <= 5 do
	    cleanup(userList[i]);
		i = i + 1;
	end
end;

function TestCase.Login.StartupToDungeon()
    local user_name = "TSDungeou"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name, GROUP_ID, clsWarrior, cstMale, SERVER_PORT, 102);
    local oScene = role:GetScene();
    check(oScene:GetSceneTempID() == 102, "can't enter the right scene")

    wait(5);

    cleanup(user);
end;


function TestCase.Login.DeleteRole()
    local user_name = "delRole"..os.date("%H%M%S");
    
    local user = login(user_name);
    check(user, "failed to login");
    check(user:GetRoleCount() == 0, "error role count");
    local session_id = user:GetSessionID();

    ret = user:CreateRole(user_name, 1, 1, 1, 1, 1);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");
    check(user:GetRoleCount() == 1, "error role count");
    role = user:GetRoleByIndex(0);
    check(role, "failed to find created role");

    local roleID = role:GetObjID();
    check(roleID, "failed to Get roleID");

    local nRet = delete_role(user, roleID);
    check(nRet, "failed to delete role");

    cleanup(user);

    wait(5);

    user = login(user_name);
    check(user, "failed to login");
    check(user:GetRoleCount() == 1, "error role count");
    
    cleanup(user);
    
    wait(305);
    
    user = login(user_name);
    check(user, "failed to login");
    check(user:GetRoleCount() == 0, "error role count");
    
    cleanup(user);
end;

function TestCase.NpcSummon()
    local ret;
    local msg;
    local user_name = "npc"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    local session_id = user:GetSessionID();

    ret = user:GMCommand("SummonNpc(1)");
    check(ret, "failed to summon npc");
    
    msg = recv_msg(5, session_id, protocol.g2c_char_appear);
    check(msg, "failed to recv g2c_char_appear");
    
    cleanup(user);
end

function TestCase.Login.ClientVariable()
	local ret, msg;
	local user_name = "cv"..os.date("%H%M%S");
	
    local user, role = startup(user_name, user_name);

	for i = 0, MAX_CLIENT_VARIABLE_COUNT-1  do
		local value = role:GetClientVariable(i);
		check(value == 0, "error init client variable value "..i);

		ret = user:UpdateClientVariable(i, i);
		check(ret, "failed to update client value "..i);
    end
    
    cleanup(user);
    
    wait(5);

    user, role = startup(user_name, user_name);

	for i = 0, MAX_CLIENT_VARIABLE_COUNT-1 do
		local value = role:GetClientVariable(i);
		check(value == i, "error updated client variable value");
    end

	user:UpdateClientVariable(MAX_CLIENT_VARIABLE_COUNT, 0);
	recv_msg(30, user:GetSessionID(), protocol.t2c_robot_disconnected);
    
    cleanup(user);

    wait(5);

    user, role = startup(user_name, user_name);

	for i = 0, MAX_CLIENT_VARIABLE_COUNT-1 do
		local value = role:GetClientVariable(i);
		check(value == i, "error updated client variable value");
    end

	user:UpdateClientVariable(-1, 0);
	recv_msg(30, user:GetSessionID(), protocol.t2c_robot_disconnected);
    
    cleanup(user);
	    
end

function TestCase.Login.CancelLogout()
	local ret, msg;
	local user_name = "cL"..os.date("%H%M%S");
	
    local user, role = startup(user_name, user_name);
	wait(5);
	    
	ret = user:Logout();
    check(ret, "failed to logout");
        
	msg = recv_msg(10, user:GetSessionID(), protocol.g2c_logout_timer);
	check(msg, "failed to receive g2c_logout_timer");
	check(msg.byStart == 1, "failed byStart in msg");

	--//cancel logout
	ret = user:LogoutCancel();
	check(ret, "failed to logout Cancel");

	msg = recv_msg(10, user:GetSessionID(), protocol.g2c_logout_timer);
	check(msg, "failed to receive g2c_logout_timer");
	check(msg.byStart == 0, "failed byStart in msg");

    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_robot_disconnected);
    check(msg == nil, "failed to receive t2c_robot_disconnected");

	ret = user:Logout();
    check(ret, "failed to logout");
        
	msg = recv_msg(10, user:GetSessionID(), protocol.g2c_logout_timer);
	check(msg, "failed to receive g2c_logout_timer");
	check(msg.byStart == 1, "failed byStart in msg");

    msg = recv_msg(msg.byDelayTime + 5, user:GetSessionID(), protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_disconnected");
    
    cleanup(user);
end