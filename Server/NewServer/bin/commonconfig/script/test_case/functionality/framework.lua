
TestCase.FrameWork = {};

--function TestCase.FrameWork.LoginError()
--
    --local msg;
    --local user_name = "frm_LoginError";
--
    --check(g_user_mgr, "nil user mgr");
--
    --local user = create_user(user_name, "not pt", "LoginErr", GROUP_ID);
    --check(user, "nil user");
--
    --local session_id = user:GetSessionID();
--
    --ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    --check(ret, "failed to connect server");
--
    --msg = recv_msg(30, session_id, protocol.t2c_robot_connected);
    --check(msg, "failed to receive t2c_robot_connected");
--
    --ret = user:Login();
    --check(ret, "failed to login");
--
    --msg = recv_msg(30, session_id, protocol.t2c_error_notify);
    --check(msg, "failed to recv t2c_error_notify");
    --check(msg.nErrCode == error_code.errLoginErrorUserNameOrPassword, "invalid error code");
--
    --cleanup(user);
    --wait(5);
--
    --local user = create_user(user_name, "pt", "LoginErr", GROUP_ID);
    --check(user, "nil user");
    --session_id = user:GetSessionID();
--
    --ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    --check(ret, "failed to connect server");
--
    --msg = recv_msg(30, session_id, protocol.t2c_robot_connected);
    --check(msg, "failed to receive t2c_robot_connected");
--
    --ret = user:Login();
    --check(ret, "failed to login");
--
    --msg = recv_msg(30, session_id, protocol.t2c_error_notify);
    --check(msg, "failed to recv t2c_error_notify");
    --check(msg.nErrCode == error_code.errLoginErrorUserNameOrPassword, "invalid error code");
--
    --cleanup(user);
--end;
--
function TestCase.FrameWork.LoginRepeat()

    local msg;
    local user_name = "frm_RptLs"..os.date("%H%M%S");
    local ret = 0;

    check(g_user_mgr, "nil user mgr");

    local user = create_user(user_name, "pt", "123456", GROUP_ID);
    check(user, "nil user");
    local session_id = user:GetSessionID();

    ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");

    msg = recv_msg(30, session_id, protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    ret = user:Login();
    check(ret, "failed to login");

    msg = recv_msg(30, session_id, protocol.t2c_login_ack);
    check(msg, "normal login error");

    local userRepeat = create_user(user_name, "pt", "123456", GROUP_ID);
    check(userRepeat, "nil userRepeat");
    local user_id_repeat = userRepeat:GetSessionID();

    ret = userRepeat:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");

    msg = recv_msg(30, user_id_repeat, protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    ret = userRepeat:Login();
    check(ret, "failed to login");
	
	local retMsgInfo;
	retMsgInfo = recv_msg_and(30, session_id, protocol.m2c_error_notify, 
		session_id, protocol.t2c_robot_disconnected, 
		user_id_repeat, protocol.t2c_error_notify, 
		user_id_repeat, protocol.t2c_robot_disconnected);
	check(retMsgInfo, "don't receive successMessage");

	local k, v;
	for k,v in pairs(retMsgInfo) do
		if(v.msgID == protocol.t2c_error_notify) then
			check(v.msg, "receive nil msg");
			check(v.msg.nErrCode == error_code.errLoginRepeat, "received invalid error code");
		elseif (v.msgID == protocol.t2c_error_notify) then
			check(v.msg, "receive nil msg");
			check(v.msg.nErrorCode == error_code.errLoginRepeat, "received invalid error code");
		end
	end


	wait(5);

	local userThird = create_user(user_name, "pt", "123456", GROUP_ID);
	check(userThird, "nil user");

	ret = userThird:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
	check(ret, "failed to connect server");

	local user_id_3 = userThird:GetSessionID();
	msg = recv_msg(30, user_id_3, protocol.t2c_robot_connected);
	check(msg, "failed to receive t2c_robot_connected");

	ret = userThird:Login();
	check(ret, "third user failed to login");

	msg = recv_msg(30, user_id_3, protocol.t2c_login_ack);
	check(msg, "third login error");

	cleanup(user);
	cleanup(userRepeat);
	cleanup(userThird);
end;

function TestCase.FrameWork.LoginOffine1()
    local msg;
    local user_name = "frm_off1Ls"..os.date("%H%M%S");
    local ret = 0;

    check(g_user_mgr, "nil user mgr");

    local user = create_user(user_name, "pt", "123456", GROUP_ID);
    check(user, "nil user");
    local session_id = user:GetSessionID();

    ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, false);
    check(ret, "failed to connect server");

    msg = recv_msg(30, session_id, protocol.t2c_robot_connected);
    check(msg, "failed to receive t2c_robot_connected");

    ret = user:Login();
    check(ret, "failed to login");

    msg = recv_msg(30, session_id, protocol.t2c_login_ack);
    check(msg, "normal login error");

    cleanup(user);
    wait(5);

    user = login(user_name);
    check(user, "can't login after off line");

    cleanup(user);
end;

function TestCase.FrameWork.LoginOffine2()
    local msg;
    local user_name = "frm_of2"..os.date("%H%M%S");
    local ret = 0;

    user = login(user_name);
    check(user, "login normal");

    ret = create_role(user, user_name, 1);
    check(ret, "failed to create role");

    cleanup(user);
    wait(5);

    user = login(user_name);
    check(user, "login normal");

    local role_id = 0;
    local role = user:GetRoleByIndex(0);
    if role == nil then
	role_id = create_role(user, user_name);
    else
	role_id = role:GetObjID();
    end

    check(role_id, "failed to createRole after offline");

    ret = delete_role(user, role_id);
    check(ret, "failed to delete role");

    cleanup(user);
    wait(5);

    user = login(user_name);
    check(user, "login normal");
    
    role_id = 0;
    role = user:GetRoleByIndex(0);
    if role ~= nil then
		role_id = role:GetObjID();
		ret = delete_role(user, role_id);
		check(ret, "failed to delete role after offline");
    end
    
    cleanup(user);
end;

function TestCase.FrameWork.LoginOffine3()
    local msg;
    local user_name = "frm_off3Ls"..os.date("%H%M%S");
    local ret = 0;

    local user = login(user_name);
    check(user, "can't login normal");

    local role_id = create_role(user, user_name);
    check(role_id, "can't create role");

    ret = enter_scene(user, role_id);
    check(ret, "can't select role");

    cleanup(user);
    wait(5);

	local user, role = startup(user_name, user_name);
	check(user, "can't enter scene after offline");
	check(role, "can't enter scene after offline");

	cleanup(user);
end;


function TestCase.FrameWork.SeleceRoleNotExist()
    local msg;
    local user_name = "frm_RoleSel"..os.date("%H%M%S");
    local ret = 0;

    user = login(user_name);
    check(user, "login normal");
    local session_id = user:GetSessionID();


    ret = user:SelectRole(1);
    check(ret, "failed to select role");

    msg = recv_msg(30, session_id, protocol.t2c_robot_disconnected);
    check(msg, "failed to receive t2c_robot_connected");

    cleanup(user);
end;

