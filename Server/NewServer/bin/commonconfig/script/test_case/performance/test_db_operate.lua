
function TestDBOperate(username, cls)
	
	local user = login(username);
    local session_id = user:GetSessionID();
    
    local role_name = {
        [1] = username, 
        [2] = username.."_1"..os.date("%H%M%S"),
        [3] = username.."_2"..os.date("%H%M%S"),
		[4] = username.."_3"..os.date("%H%M%S"),
    };
    
    if user:GetRoleCount() == 0 then
		ret = user:CreateRole(role_name[1], 1, 1, 1, 1, 0);
		if ret then
			local msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
			if msg then
				user:CreateRole(role_name[1], 1, 1, 1, 1, 0);

				msg = recv_msg(30, session_id, protocol.t2c_error_notify);
				if msg.nErrCode ~= error_code.errLoginCreateRoleDupeName then
					print("failed to  recv errLoginCreateRoleDupeName");
				end
			end
		end
	end
	
    local i = user:GetRoleCount() + 1;
    while i <= 4 do
        user:CreateRole(role_name[i], 1, 1, 1, 1, i-1);

		msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
		if msg == nil then
			print("failed to  recv t2c_create_role_ack");
			break;
		end
		
		i = i + 1;
    end
    
    if user:GetRoleCount() == 4 then
		i = 3;
		while i >= 1 do
			local role = user:GetRoleByIndex(i);
			if role == nil then
				break;
			end

			local roleID = role:GetObjID();
			if roleID == 0 then
				break;
			end

			user:DeleteRole(roleID);

			msg = recv_msg(30, session_id, protocol.t2c_delete_role_ack);
			if msg == nil then
				break;
			end

			i = i - 1;
		end
	else
		print("create role error username"..username);
	end
	
	if i ~= 0 then
		print("delete role error username"..username);
	end
	
	wait(8);	
	cleanup(user);
	
	wait(20);
	performanc_func_End(username);
end

function PerfTestCase.DBOperate()
	addco("PerfTest_DBOperate", Performanc_Start, 1, 'DBOperate', 10, TestDBOperate, clsWarrior);
end



