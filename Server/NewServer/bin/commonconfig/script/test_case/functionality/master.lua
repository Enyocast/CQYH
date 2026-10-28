LoadPackage("robot_message_handler.pkg")
LoadPackage("master.pkg")


TestCase.Master = {};

function BecomeMasterByMyself(user, role)
	ret = user:GMCommand("SetLevel(40)");
	check(ret, "failed to send gm command");

	ret = user:GMCommand("Master()");
	check(ret, "failed to send gm command");
end

function TestRecruit(role, user, session_id, byCount)
	local msg;
	local recruitListCount = 0;
	local ret;

	-- 前置拉取
	g_RobotMessageHandler:DoMstGetRecruit(role);
	msg = recv_msg(50, session_id, protocol.m2c_master_recruit_list);
	check(msg, "failed to recv m2c_master_recruit_list");
	--if byCount == 0 then
		--check(msg.byCount == 0, "m2c_master_recruit_list value error!");
	--else
		recruitListCount = msg.byCount;
	--end

	print(recruitListCount);
	-- 申请
	g_RobotMessageHandler:DoMstApplyRecruit(role);
	msg = recv_msg(50, session_id, protocol.m2c_master_recruit_ack);
	check(msg, "failed to recv m2c_master_recruit_ack");
	check(msg.dwType == 1, "m2c_master_recruit_ack value error");

	wait(1);
	-- 再次拉取，确认数量
	g_RobotMessageHandler:DoMstGetRecruit(role);
	msg = recv_msg(50, session_id, protocol.m2c_master_recruit_list);
	check(msg, "failed to recv m2c_master_recruit_list");
	print(recruitListCount);
	print(msg.byCount);
	check(msg.byCount == recruitListCount + 1, "m2c_master_recruit_list value error");

	-- 取消
	g_RobotMessageHandler:DoMstCancelRecruit(role);
	msg = recv_msg(50, session_id, protocol.m2c_master_recruit_ack);
	check(msg, "failed to recv m2c_master_recruit_ack");
	check(msg.dwType == 2, "m2c_master_recruit_ack value error");

	-- 再次拉取，确认数量
	g_RobotMessageHandler:DoMstGetRecruit(role);
	msg = recv_msg(50, session_id, protocol.m2c_master_recruit_list);
	check(msg, "failed to recv m2c_master_recruit_list");
	check(msg.byCount == recruitListCount, "m2c_master_recruit_list value error");
end



function TestSubmitApp(role, session_id, s_role, s_session_id)
	local msg;

	g_RobotMessageHandler:DoMstSubmitStudApp(s_role, role:GetObjID());

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_add_applicant,
						s_session_id, protocol.m2c_master_submit_stud_app);
	check(msg_arr, "failed to recv SubmitApp msg");

	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_add_applicant then
			check(v.msg, "failed to recv m2c_master_add_applicant");
			check(v.msg.dwRoleID == s_role:GetObjID(), "m2c_master_add_applicant value error");
		elseif v.msgID == protocol.m2c_master_submit_stud_app then
			check(v.msg, "failed to recv m2c_master_submit_stud_app");
			check(v.msg.dwMasterID == role:GetObjID(), "m2c_master_submit_stud_app value error");
		else
			check(nil, "failed to recv SubmitApp msg");
		end
	end
end

function TestCancelApp(role, session_id, s_role, s_session_id)
	g_RobotMessageHandler:DoMstCancelStudApp(s_role, role:GetObjID());

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_cancel_stud_app,
							s_session_id, protocol.m2c_master_cancel_stud_app);
	check(msg_arr, "failed to recv CancelStudApp msg");

	for k, v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_cancel_stud_app then
			check(v.msg, "failed to recv m2c_master_cancel_stud_app");
			check(v.msg.dwRoleID == s_role:GetObjID() or v.msg.dwRoleID == role:GetObjID(), "m2c_master_cancel_stud_app value error");
		else
			check(nil, "failed to recv m2c_master_cancel_stud_app");
		end
	end
end

function TestRefuseApp(role, session_id, s_role, s_session_id)
	local msg;

	g_RobotMessageHandler:DoMstRefuseStudApp(role, s_role:GetObjID());

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_cancel_stud_app,
							s_session_id, protocol.m2c_master_refuse_stud_app);
	check(msg_arr, "failed to recv refuseApp msg");

	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_cancel_stud_app then
			check(v.msg, "failed to recv m2c_master_cancel_stud_app");
			check(v.msg.dwRoleID == s_role:GetObjID(), "m2c_master_cancel_stud_app value error");
		elseif v.msgID == protocol.m2c_master_refuse_stud_app then
			check(v.msg, "failed to recv m2c_master_refuse_stud_app");
			check(v.msg.dwRoleID == role:GetObjID(), "m2c_master_refuse_stud_app value error");
		else
			check(nil, "failed to recv refuseApp msg");
		end
	end
end

function TestRefuseAllApp(role, session_id, s_role, s_session_id)
	local name = "MstStud" .. os.date("%Y%H%M%S");
	local temp_user, temp_role = startup(name, name);
    check(temp_user, "failed to create user");
    check(temp_role, "failed to create role");
	local temp_session_id = temp_user:GetSessionID();

	-- 再次申请
	TestSubmitApp(role, session_id, temp_role, temp_session_id);

	g_RobotMessageHandler:DoMstRefuseStudApp(role, 0);

	local msg_arr = recv_msg_and(50, temp_session_id, protocol.m2c_master_refuse_stud_app,
						session_id, protocol.m2c_master_cancel_stud_app,
						s_session_id, protocol.m2c_master_refuse_stud_app);
	check(msg_arr, "failed to recv RefuseAllApp Msg");

	for k, v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_refuse_stud_app then
			check(v.msg, "failed to recv m2c_master_refuse_stud_app");
			check(v.msg.dwRoleID == role:GetObjID(), "m2c_master_refuse_stud_app value error");
		elseif v.msgID == protocol.m2c_master_cancel_stud_app then
			check(v.msg, "failed to recv m2c_master_cancel_stud_app");
			check(v.msg.dwRoleID == 0, "m2c_master_refuse_stud_app value error");
		else
			check(nil, "failed to recv RefuseAllApp Msg");
		end
	end

	cleanup(temp_user);
	wait(1);
end

function TestAgreeApp(role, session_id, s_role, s_session_id)

	g_RobotMessageHandler:DoMstAgreeStudApp(role, s_role:GetObjID());

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_agree_stud_app,
						s_session_id, protocol.m2c_master_add_master);
	check(msg_arr, "failed to recv AgreeApp");

	for k, v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_agree_stud_app then
			check(v.msg, "failed to recv m2c_master_agree_stud_app");
			check(v.msg.dwStudentID == s_role:GetObjID(), "m2c_master_agree_stud_app value error");
		elseif v.msgID == protocol.m2c_master_add_master then
			check(v.msg, "failed to recv m2c_master_add_master");
			check(v.msg.dwMasterID == role:GetObjID(), "m2c_master_add_master value error");
		else
			check(nil, "failed to recv AgreeApp");
		end
	end
end

function TestLeaveMaster(role, session_id, s_role, s_session_id)

	g_RobotMessageHandler:DoMstLeaveMaster(s_role);

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_leave_master,
							s_session_id, protocol.m2c_master_leave_master);
	check(msg_arr, "failed to recv LeaveMaster");

	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_leave_master then
			check(v.msg, "failed to recv m2c_master_leave_master");
			check(v.msg.byDealType == 3 or v.msg.byDealType == 4, "m2c_master_leave_master value error");

			if v.msg.byDealType == 3 then
				check(v.msg.dwOtherID == s_role:GetObjID(), "m2c_master_leave_master value error");
			else
				check(v.msg.dwOtherID == role:GetObjID(), "m2c_master_leave_master value error");
			end
		else
			check(nil, "failed to recv LeaveMaster");
		end
	end
end

function TestFireStudent(role, session_id, s_role, s_session_id)

	g_RobotMessageHandler:DoMstFireStudent(role, s_role:GetObjID());

	local msg_arr = recv_msg_and(50, session_id, protocol.m2c_master_leave_master,
							s_session_id, protocol.m2c_master_leave_master);
	check(msg_arr, "failed to recv FireStudent msg");

	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_leave_master then
			check(v.msg, "failed to recv m2c_master_leave_master");
			check(v.msg.byDealType == 5 or v.msg.byDealType == 6, "m2c_master_leave_master value error");

			if v.msg.byDealType == 5 then
				check(v.msg.dwSelfID == role:GetObjID(), "m2c_master_leave_master value error");
				check(v.msg.dwOtherID == s_role:GetObjID(), "m2c_master_leave_master value error");
			else
				check(v.msg.dwSelfID == s_role:GetObjID(), "m2c_master_leave_master value error");
				check(v.msg.dwOtherID == role:GetObjID(), "m2c_master_leave_master value error");
			end
		else
			check(nil, "failed to recv FireStudent");
		end
	end
end

function TestCongLevelUp(role, session_id, s_role, s_session_id)

	g_RobotMessageHandler:DoMstCongLevelUp(role, s_role:GetObjID(), 3);

	local msg = recv_msg(50, session_id, protocol.m2c_master_cong_lvl_up);
	check(msg, "failed to recv m2c_master_cong_lvl_up");
	check(msg.dwStudentID == s_role:GetObjID(), "m2c_master_cong_lvl_up value error");
end


function TestCase.Master.MasterRecruit()
    local ret;
    local msg;

    local teacher_name = {};
    local teacher_user = {};
    local teacher_role = {};
    local teacher_session = {};

    local teacher_num  = 40;
	local check_teacher_num = 40;
	if check_teacher_num > 30 then
		check_teacher_num = 30;
	end

    for i = 1, teacher_num, 1 do
		teacher_name[i] = "Tea"..os.date("%Y%H%M%S");

		teacher_user[i], teacher_role[i] = startup(teacher_name[i], teacher_name[i]);
		check(teacher_user[i], "failed to create user");
		check(teacher_role[i], "failed to create role");
		teacher_session[i] = teacher_user[i]:GetSessionID();

		wait(1);
    end

    -- 变成师傅
    for i = 1, teacher_num, 1 do
		BecomeMasterByMyself(teacher_user[i], teacher_role[i]);
		wait(1);
	end

	wait(3);

	-- 申请
	for i = 1, teacher_num, 1 do
		g_RobotMessageHandler:DoMstApplyRecruit(teacher_role[i]);
		msg = recv_msg(10, teacher_session[i], protocol.m2c_master_recruit_ack);
		check(msg, "failed to recv m2c_master_recruit_ack");
		check(msg.dwType == 1, "m2c_master_recruit_ack value error");
	end


	local stud_name = "stud"..os.date("%Y%H%M%S");
	local stud_user;
	local stud_role;
	local stud_session;

	stud_user, stud_role = startup(stud_name, stud_name);
	check(stud_user, "failed to create user");
	check(stud_role, "failed to create role");
	stud_session = stud_user:GetSessionID();

	wait(30);

	ret = stud_user:GMCommand("SetLevel(20)");
	check(ret, "failed to send gm command");

	g_RobotMessageHandler:DoMstGetRecruit(stud_role);
	msg = recv_msg(10, stud_session, protocol.m2c_master_recruit_list);
	check(msg, "failed to recv m2c_master_recruit_list");
	check(msg.byCount == check_teacher_num, "m2c_master_recruit_list count error");

	for i = 1, teacher_num, 1 do
		g_RobotMessageHandler:DoMstCancelRecruit(teacher_role[i]);
		msg = recv_msg(10, teacher_session[i], protocol.m2c_master_recruit_ack);
		check(msg, "failed to recv m2c_master_recruit_ack");
		check(msg.dwType == 2, "m2c_master_recruit_ack value error");
	end

	g_RobotMessageHandler:DoMstGetSoloList(teacher_role[1]);
	msg = recv_msg(10, teacher_session[1], protocol.m2c_master_get_solo_list_ack);
	check(msg, "failed to recv m2c_master_get_solo_list_ack");
	check(msg.byCount == 1, "m2c_master_get_solo_list_ack count error");

	for i = 1, teacher_num, 1 do
		cleanup(teacher_user[i]);
	end

	cleanup(stud_user);
end

function TestCase.Master.MasterApply()
	local ret;
    local msg;

	local teacher_name = {};
    local teacher_user = {};
    local teacher_role = {};
    local teacher_session = {};

	local stud_name = {};
	local stud_user = {};
	local stud_role = {};
	local stud_session = {};

	local teacher_num = 5;
	local stud_num = 5;


	for i = 1, teacher_num, 1 do
		teacher_name[i] = "Tea"..os.date("%Y%H%M%S");

		teacher_user[i], teacher_role[i] = startup(teacher_name[i], teacher_name[i]);
		check(teacher_user[i], "failed to create user");
		check(teacher_role[i], "failed to create role");
		teacher_session[i] = teacher_user[i]:GetSessionID();

		wait(1);

		BecomeMasterByMyself(teacher_user[i], teacher_role[i]);
    end

	for i = 1, stud_num, 1 do
		stud_name[i] = "Stud"..os.date("%Y%H%M%S");

		stud_user[i], stud_role[i] = startup(stud_name[i], stud_name[i]);
		check(stud_user[i], "failed to create user");
		check(stud_role[i], "failed to create role");
		stud_session[i] = stud_user[i]:GetSessionID();

		wait(1);

		ret = stud_user[i]:GMCommand("SetLevel(20)");
		check(ret, "failed to send gm command");
    end

	-- check student application
	local  TempCount = 0;
	for i = 1, 4, 1 do
		g_RobotMessageHandler:DoMstSubmitStudApp(stud_role[1], teacher_role[i]:GetObjID());
		msg = recv_msg_and(10, stud_session[1], protocol.m2c_master_stud_submit_app_ack,
							teacher_session[i], protocol.m2c_master_stud_submit_app_ntf);
		check(msg, "failed to recv m2c_master_stud_submit_app");
		for k,v in pairs(msg) do
			if v.msg ~= nil then
				TempCount = TempCount + 1;
			end
		end

		if i <= 3 then
			check(TempCount == 2, "fail to recv msg");
		elseif i == 4 then
			check(TempCount == 0, "recv msg error");
		else
			check(nil, "recv msg error");
		end

		TempCount = 0;

		wait(0.5);
	end

	-- check teacher recv application
	for i = 1,9,1 do


	end




	for i = 1, teacher_num, 1 do
		cleanup(teacher_user[i]);
	end

	for i = 1, stud_num, 1 do
		cleanup(stud_user[i]);
	end


end

function TestCase.Master.MasterBase()
    local user_name = "Master" .. os.date("%Y%H%M%S");
    local ret;
    local msg;
    local session_id;

	local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
	session_id = user:GetSessionID();

	-- 变成师傅
	BecomeMasterByMyself(user, role);

	wait(5);

	-- 验证招徒列表
	TestRecruit(role, user, session_id, 0);

	wait(2);

	local student_name = "student" .. os.date("%Y%H%M%S");
	local s_user, s_role = startup(student_name, student_name);
    check(s_user, "failed to create user");
    check(s_role, "failed to create role");
	local s_session_id = s_user:GetSessionID();

	-- 提交申请
	TestSubmitApp(role, session_id, s_role, s_session_id);

	-- 取消申请
	TestCancelApp(role, session_id, s_role, s_session_id);

	-- 提交申请
	TestSubmitApp(role, session_id, s_role, s_session_id);

	-- 拒绝申请
	TestRefuseApp(role, session_id, s_role, s_session_id);

	-- 提交申请
	TestSubmitApp(role, session_id, s_role, s_session_id);
	-- 拒绝所有
	TestRefuseAllApp(role, session_id, s_role, s_session_id);

	-- 提交申请
	TestSubmitApp(role, session_id, s_role, s_session_id);
	-- 同意拜师
	TestAgreeApp(role, session_id, s_role, s_session_id);

	-- 恭喜升级
	ret = s_user:GMCommand("AddExp(3000)");
	check(ret, "failed to send gm command");
	wait(5);
	TestCongLevelUp(role, session_id, s_role, s_session_id);


	-- 主动叛师
	TestLeaveMaster(role, session_id, s_role, s_session_id);

	-- 开除
	--TestFireStudent(role, session_id, s_role, s_session_id);
	--check(role:GetMaster():GetStudentCount() == 0, "student num error!");


    wait(6);
    cleanup(user);
	wait(2);
	cleanup(s_user);
end



function NewUser()
	local user_name = "Master" .. os.date("%Y%H%M%S");
	local user, role = startup(user_name, user_name, 1);
    check(user, "failed to create user");
    check(role, "failed to create role");
	local session_id = user:GetSessionID();

	return user, role, session_id, user_name;
end


function TestRecruitAdvanced(byCount)
	local msg;
	local recruitListCount = 0;
	local ret;

	local master_table = {};

	local i = 0;
	for i = 1,35,1 do
		master_table[i] = {};
		master_table[i].user, master_table[i].role, master_table[i].session_id = NewUser();
		wait(2);
	end

	-- 前置拉取
	g_RobotMessageHandler:DoMstGetRecruit(master_table[1].role);
	msg = recv_msg(50, master_table[1].session_id, protocol.m2c_master_recruit_list);
	check(msg, "failed to recv m2c_master_recruit_list");
	if byCount == 0 then
		check(msg.byCount == 0, "m2c_master_recruit_list value error!");
		recruitListCount = 0;
	else
		recruitListCount = msg.byCount;
	end

	for k,v in pairs(master_table) do
		-- 变成师傅
		BecomeMasterByMyself(v.user, v.role);
		wait(1);
	end


	local bcheck = 1;
	local old_recruit_list_num = recruitListCount;

	print("--------------------".. recruitListCount);
	for k,v in pairs(master_table) do
		-- 申请
		g_RobotMessageHandler:DoMstApplyRecruit(v.role);
		msg = recv_msg(50, v.session_id, protocol.m2c_master_recruit_ack);
		check(msg, "failed to recv m2c_master_recruit_ack");
		check(msg.dwType == 1, "m2c_master_recruit_ack value error");

		-- 再次拉取，确认数量
		g_RobotMessageHandler:DoMstGetRecruit(v.role);
		msg = recv_msg(50, v.session_id, protocol.m2c_master_recruit_list);
		check(msg, "failed to recv m2c_master_recruit_list");

		print(recruitListCount);
		if msg.byCount == 30 and bcheck then
			check(msg.byCount == 30, "m2c_master_recruit_list value error");
			if msg.byCount == 30 then
				print("--------------------------------- nil ---------------------");
				bcheck = nil;
			end
		else
			check(1, "recruit test success!");
		end

		recruitListCount = recruitListCount + 1;
	end

	wait(30000);

	-- logout
	for i,v in ipairs(master_table) do
		cleanup(master_table[i].user);
	end


	-- 取消
	--g_RobotMessageHandler:DoMstCancelRecruit(role);
	--msg = recv_msg(50, session_id, protocol.m2c_master_recruit_ack);
	--check(msg, "failed to recv m2c_master_recruit_ack");
	--check(msg.dwType == 2, "m2c_master_recruit_ack value error");

	-- 再次拉取，确认数量
	--g_RobotMessageHandler:DoMstGetRecruit(role);
	--msg = recv_msg(50, session_id, protocol.m2c_master_recruit_list);
	--check(msg, "failed to recv m2c_master_recruit_list");
	--check(msg.byCount == recruitListCount, "m2c_master_recruit_list value error");
end



function SubmitAppAdvanced()
	local msg;
	local 	master_table = {};
	local 	student_table = {};

	local i = 0;
	for i = 1,4,1 do
		master_table[i] = {};
		master_table[i].user, master_table[i].role, master_table[i].session_id = NewUser();
		wait(2);
	end

	for i = 1,9,1 do
		student_table[i] = {};
		student_table[i].user, student_table[i].role, student_table[i].session_id = NewUser();
		wait(2);
	end

	for k,v in pairs(master_table) do
		-- 变成师傅
		BecomeMasterByMyself(v.user, v.role);
		wait(1);
	end

	-- student's application list
	print("student's application list");
	for i = 1,4,1 do
		g_RobotMessageHandler:DoMstSubmitStudApp(student_table[1].role, master_table[i].role:GetObjID());
		if i < 4 then
			local msg_arr = recv_msg_and(50, master_table[i].session_id, protocol.m2c_master_add_applicant,
					student_table[1].session_id, protocol.m2c_master_submit_stud_app);
			check(msg_arr, "failed to recv SubmitApp msg");
			for k,v in pairs(msg_arr) do
				if v.msgID == protocol.m2c_master_add_applicant then
					check(v.msg, "failed to recv m2c_master_add_applicant");
					check(v.msg.dwRoleID == student_table[1].role:GetObjID(), "m2c_master_add_applicant value error");
				elseif v.msgID == protocol.m2c_master_submit_stud_app then
					check(v.msg, "failed to recv m2c_master_submit_stud_app");
					check(v.msg.dwMasterID == master_table[i].role:GetObjID(), "m2c_master_submit_stud_app value error");
				else
					check(nil, "failed to recv SubmitApp msg");
				end
			end
		else
			local msg_arr = recv_msg_and(20, master_table[i].session_id, protocol.m2c_master_add_applicant,
					student_table[1].session_id, protocol.m2c_master_submit_stud_app);
			for k,v in pairs(msg_arr) do
				check(v.msg == nil, "recv SubmitApp msg error");
			end
		end
	end

	--1号学生需要取消一个，才能继续
	TestCancelApp(master_table[1].role, master_table[1].session_id, student_table[1].role, student_table[1].session_id);

	wait(3);
	print("master's application list");
	-- master's application list
	for i = 1, 9, 1 do
		g_RobotMessageHandler:DoMstSubmitStudApp(student_table[i].role, master_table[1].role:GetObjID());
		if i < 9 then
			print(i);
			local msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_add_applicant,
					student_table[i].session_id, protocol.m2c_master_submit_stud_app);
			check(msg_arr, "failed to recv SubmitApp msg");
			for k,v in pairs(msg_arr) do
				if v.msgID == protocol.m2c_master_add_applicant then
					check(v.msg, "failed to recv m2c_master_add_applicant");
					check(v.msg.dwRoleID == student_table[i].role:GetObjID(), "m2c_master_add_applicant value error");
				elseif v.msgID == protocol.m2c_master_submit_stud_app then
					check(v.msg, "failed to recv m2c_master_submit_stud_app");
					check(v.msg.dwMasterID == master_table[1].role:GetObjID(), "m2c_master_submit_stud_app value error");
				else
					check(nil, "failed to recv SubmitApp msg");
				end
			end
		else
			local msg_arr = recv_msg_and(20, master_table[1].session_id, protocol.m2c_master_add_applicant,
					student_table[i].session_id, protocol.m2c_master_submit_stud_app);
			for k,v in pairs(msg_arr) do
				check(v.msg == nil, "recv SubmitApp msg error");
			end
		end
	end

	-- refuse all test
	g_RobotMessageHandler:DoMstRefuseStudApp(master_table[1].role, 0);
	local msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_cancel_stud_app,
							student_table[1].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[2].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[3].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[4].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[5].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[6].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[7].session_id, protocol.m2c_master_refuse_stud_app,
							student_table[8].session_id, protocol.m2c_master_refuse_stud_app);
	check(msg_arr, "failed to recv CancelStudApp msg");
	local 	recv_count = 0;
	for k, v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_cancel_stud_app then
			check(v.msg, "failed to recv m2c_master_cancel_stud_app");
			check(v.msg.dwRoleID == 0, "m2c_master_cancel_stud_app value error");
			recv_count = recv_count + 1;
		elseif v.msgID == protocol.m2c_master_refuse_stud_app then
			check(v.msg, "failed to recv m2c_master_refuse_stud_app");
			recv_count = recv_count + 1;
		else
			check(nil, "failed to recv m2c_master_cancel_stud_app");
		end
	end
	check(recv_count == 9, "recv refuse all ack failed!");



	print("--------------------------------------------------------- master's application list");
	-- master's application list  retest
	for i = 1, 9, 1 do
		g_RobotMessageHandler:DoMstSubmitStudApp(student_table[i].role, master_table[1].role:GetObjID());
		if i < 9 then
			print(i);
			local msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_add_applicant,
					student_table[i].session_id, protocol.m2c_master_submit_stud_app);
			check(msg_arr, "failed to recv SubmitApp msg");
			for k,v in pairs(msg_arr) do
				if v.msgID == protocol.m2c_master_add_applicant then
					check(v.msg, "failed to recv m2c_master_add_applicant");
					check(v.msg.dwRoleID == student_table[i].role:GetObjID(), "m2c_master_add_applicant value error");
				elseif v.msgID == protocol.m2c_master_submit_stud_app then
					check(v.msg, "failed to recv m2c_master_submit_stud_app");
					check(v.msg.dwMasterID == master_table[1].role:GetObjID(), "m2c_master_submit_stud_app value error");
				else
					check(nil, "failed to recv SubmitApp msg");
				end
			end
		else
			local msg_arr = recv_msg_and(20, master_table[1].session_id, protocol.m2c_master_add_applicant,
					student_table[i].session_id, protocol.m2c_master_submit_stud_app);
			for k,v in pairs(msg_arr) do
				check(v.msg == nil, "recv SubmitApp msg error");
			end
		end
	end

	-- logout
	for i,v in ipairs(master_table) do
		cleanup(master_table[i].user);
	end

	for i,v in ipairs(student_table) do
		cleanup(student_table[i].user);
	end

end

function SubmitApp(s_role, m_role, s_session_id, m_session_id)
	g_RobotMessageHandler:DoMstSubmitStudApp(s_role, m_role:GetObjID());

	local msg_arr = recv_msg_and(50, m_session_id, protocol.m2c_master_add_applicant,
			s_session_id, protocol.m2c_master_submit_stud_app);
	check(msg_arr, "failed to recv SubmitApp msg");
	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_add_applicant then
			check(v.msg, "failed to recv m2c_master_add_applicant");
			check(v.msg.dwRoleID == s_role:GetObjID(), "m2c_master_add_applicant value error");
		elseif v.msgID == protocol.m2c_master_submit_stud_app then
			check(v.msg, "failed to recv m2c_master_submit_stud_app");
			check(v.msg.dwMasterID == m_role:GetObjID(), "m2c_master_submit_stud_app value error");
		else
			check(nil, "failed to recv SubmitApp msg");
		end
	end
end

function AgreeAllAppAdvanced()
	local student_table = {};
	local master_table = {};

	local i = 0;
	for i = 1,2,1 do
		master_table[i] = {};
		master_table[i].user, master_table[i].role, master_table[i].session_id = NewUser();
		wait(2);
	end

	for i = 1,4,1 do
		student_table[i] = {};
		student_table[i].user, student_table[i].role, student_table[i].session_id = NewUser();
		wait(2);
	end

	for k,v in pairs(master_table) do
		-- 变成师傅
		BecomeMasterByMyself(v.user, v.role);
		wait(1);
	end

	print("student's application list");
	for i = 1,4,1 do
		SubmitApp(student_table[i].role, master_table[1].role, student_table[i].session_id, master_table[1].session_id);
	end

	for i = 1,4,1 do
		g_RobotMessageHandler:DoMstAgreeStudApp(master_table[1].role, student_table[i].role:GetObjID());
		print(i);
		if i < 4 then
			local msg_arr;
			if i < 3 then
				msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_agree_stud_app,
							student_table[i].session_id, protocol.m2c_master_add_master);
			elseif i == 3 then
				msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_agree_stud_app,
							student_table[i].session_id, protocol.m2c_master_add_master,
							student_table[4].session_id, protocol.m2c_master_refuse_stud_app);
			end

			check(msg_arr, "failed to recv ");
			for k,v in pairs(msg_arr) do
				if v.msgID == protocol.m2c_master_agree_stud_app then
					check(v.msg, "failed to recv m2c_master_agree_stud_app");
					check(v.msg.dwStudentID == student_table[i].role:GetObjID(), "m2c_master_agree_stud_app value error!");
				elseif v.msgID == protocol.m2c_master_add_master then
					check(v.msg, "failed to recv m2c_master_add_master");
					check(v.msg.dwMasterID == master_table[1].role:GetObjID(), "m2c_master_add_master value error!");
				elseif v.msgID == protocol.m2c_master_refuse_stud_app then
					check(v.msg, "failed to recv m2c_master_cancel_stud_app");
					check(v.msg.dwRoleID == master_table[1].role:GetObjID(), "m2c_master_cancel_stud_app value error!");
				else
					check(nil, "failed to recv AgreeApp msg");
				end
			end
		else
			local msg = recv_msg(15, student_table[4].session_id, protocol.m2c_master_add_master);
			check(msg == nil, "failed, recv m2c_master_add_master");
		end
	end

	print(master_table[1].role:GetMaster():GetStudentCount());
	check(master_table[1].role:GetMaster():GetStudentCount() == 3, "add student error!");

	-- logout
	for i,v in ipairs(master_table) do
		cleanup(master_table[i].user);
	end

	for i,v in ipairs(student_table) do
		cleanup(student_table[i].user);
	end

end


function AgreeApplication(s_role, s_session_id, m_role, m_session_id)
	g_RobotMessageHandler:DoMstAgreeStudApp(m_role, s_role:GetObjID());
	local msg_arr = recv_msg_and(50, m_session_id, protocol.m2c_master_agree_stud_app, s_session_id, protocol.m2c_master_add_master);
	check(msg_arr, "failed to recv ");
	for k,v in pairs(msg_arr) do
		if v.msgID == protocol.m2c_master_agree_stud_app then
			check(v.msg, "failed to recv m2c_master_agree_stud_app");
			check(v.msg.dwStudentID == s_role:GetObjID(), "m2c_master_agree_stud_app value error!");
		elseif v.msgID == protocol.m2c_master_add_master then
			check(v.msg, "failed to recv m2c_master_add_master");
			check(v.msg.dwMasterID == m_role:GetObjID(), "m2c_master_add_master value error!");
		else
			check(nil, "failed to recv AgreeApp msg");
		end
	end
end


function MasterWholeAdvanced()
	local 	master_table = {};
	local 	student_table = {};

	local i = 0;
	for i = 1,2,1 do
		master_table[i] = {};
		master_table[i].user, master_table[i].role, master_table[i].session_id, master_table[i].user_name = NewUser();
		wait(2);
	end

	for i = 1,4,1 do
		student_table[i] = {};
		student_table[i].user, student_table[i].role, student_table[i].session_id, student_table[i].user_name = NewUser();
		wait(2);
	end

	for k,v in pairs(master_table) do
		-- 变成师傅
		BecomeMasterByMyself(v.user, v.role);
		wait(1);
	end

	-- 申请
	print("student's application list");
	for i = 1,3,1 do
		SubmitApp(student_table[i].role, master_table[1].role, student_table[i].session_id, master_table[1].session_id);
	end

	-- 同意
	for i = 1,3,1 do
		AgreeApplication(student_table[i].role, student_table[i].session_id, master_table[1].role, master_table[1].session_id);
	end
	wait(5);
	print(master_table[1].role:GetMaster():GetStudentCount());
	check(master_table[1].role:GetMaster():GetStudentCount() == 3, "add student error!");

	-- 升级出师
	for i = 1, 3, 1 do
		print("role:"..i);
		ret = student_table[i].user:GMCommand("AddExp(30000000)");
		check(ret, "failed to send gm command");
		wait(5);
		for k = 1, 39, 1 do
			print(k);
			g_RobotMessageHandler:DoMstCongLevelUp(master_table[1].role, student_table[i].role:GetObjID(), 1);
			if k < 39 then
				local msg = recv_msg(50, master_table[1].session_id, protocol.m2c_master_cong_lvl_up);
				check(msg, "failed to recv m2c_master_cong_lvl_up");
				check(msg.dwStudentID == student_table[i].role:GetObjID(), "m2c_master_cong_lvl_up value error!");
			else
				local msg_arr = recv_msg_and(50, master_table[1].session_id, protocol.m2c_master_cong_lvl_up,
						student_table[i].session_id, protocol.m2c_master_state_change_ntf);
				for k,v in pairs(msg_arr) do
					if v.msgID == protocol.m2c_master_cong_lvl_up then
						check(v.msg, "failed to recv m2c_master_cong_lvl_up");
						check(v.msg.dwStudentID == student_table[i].role:GetObjID(), "m2c_master_cong_lvl_up value error!");
					elseif v.msgID == protocol.m2c_master_state_change_ntf then
						check(v.msg, "failed to recv m2c_master_add_master");
						check(v.msg.byMasterState == 3, "m2c_master_add_master value error!");
					else
						check(nil, "failed to recv AgreeApp msg");
					end
				end
			end
			--wait(1);
		end
	end

	-- add new student
	SubmitApp(student_table[4].role, master_table[1].role, student_table[4].session_id, master_table[1].session_id);
	AgreeApplication(student_table[4].role, student_table[4].session_id, master_table[1].role, master_table[1].session_id);


	-- logout
	for i,v in ipairs(master_table) do
		cleanup(master_table[i].user);
	end

	for i,v in ipairs(student_table) do
		cleanup(student_table[i].user);
	end

	--wait(10);


	--master_table[1].user, master_table[1].role = startup(master_table[1].user_name, master_table[1].user_name);
    --check(user, "failed to create user");
    --check(role, "failed to create role");
	--master_table[1].session_id = master_table[1].user:GetSessionID();

	--wait(60);
	--cleanup(master_table[1].user);

	wait(30);

	master_table[1].user, master_table[1].role = startup(master_table[1].user_name, master_table[1].user_name);
    check(master_table[1].user, "failed to create user");
    check(master_table[1].role, "failed to create role");
	master_table[1].session_id = master_table[1].user:GetSessionID();

	wait(60);

	cleanup(master_table[1].user);

end

function TestCase.Master.MasterAdvanced()
	local ret;
    local msg;


	for i = 1, 10,1 do
		print(i);
	end

	-- check recurit
	TestRecruitAdvanced(0);


	SubmitAppAdvanced();

	AgreeAllAppAdvanced();

--	local master_user, master_role, m_session_id = NewUser();

	-- 变成师傅
	--BecomeMasterByMyself(master_user, master_role);



	-- 手动testcase
	MasterWholeAdvanced();
end














