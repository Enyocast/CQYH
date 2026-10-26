g_user = nil
g_role = nil

function TraverseUser(Func)
    for k, v in pairs(UserTable) do
        Func(k, v)
    end
end

function TraverseRole(Func)
    for k, v in pairs(RoleTable) do
        Func(k, v)
    end
end

function pk(offset, cnt)
    if offset < 0 or offset > 1000 or cnt > 1000 then
        return false;
    end

    addco('case' .. tostring(offset) .. '_' .. tostring(cnt),
	  add_pk, offset, cnt)
    return true;
end

function add_pk(offset, cnt)
    for idx = offset, offset + cnt - 1 do
        local uname = ''
        if idx < 10 then
            uname = 'asimov00'..idx
        elseif idx < 100 then
            uname = 'asimov0'..idx
        else
            uname = 'asimov'..idx
        end

        addco(uname, startup_pk, uname)
--	    wait(2)
    end

    return true;
end

function create_role(user, role_name, cls, sex)
    local ret;
    local msg;
    local user_name = user:GetUserName();

    if cls == nil then
		cls = clsWarrior;
    end

	if sex == nil then
		sex = cstMale;
	end

    ret = user:CreateRole(role_name, sex, 0, 0, 0, cls);
    check(ret, "failed to create role");

    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_create_role_ack);
    check(msg, "failed to  recv t2c_create_role_ack");

    local role_id = msg.RoleData.dwRoleID;

    print("user "..user_name.." created role ".. role_name .. " role id: " .. role_id);

    return role_id
end

function delete_role(user, role_id)
    local ret;
    local msg;

    local user_name = user:GetUserName();

    ret = user:DeleteRole(role_id);
    check(ret, "failed to delete role");

    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_delete_role_ack);
    check(msg, "failed to  recv t2c_delete_role_ack");

    print("user "..user_name.." deleted role "..role_id);

    return true;
end

function enter_scene(user, role_id)
    local ret;
    local msg;

    local user_name = user:GetUserName();

    ret = user:SelectRole(role_id);
    check(ret, "failed to select role");

    msg = recv_msg(30, user:GetSessionID(), protocol.t2c_select_role_ack);
    check(msg, "failed to recv t2c_select_role_ack");

    return true
end

robot_init_pos = 
{
	{x = 16000, y =  8100, z = 9500},
	{x = 20300, y =  4300, z = 9400},
	{x = 20300, y = 12000, z = 9400},
	{x = 12500, y = 12000, z = 9400},
	{x = 12500, y =  4300, z = 9400},
}

function startup_pk(user_name)
    local user, role = startup(user_name, user_name)
    
    ai = role:CreateAIProcessor()
    if not ai then
        print("Create AI fail for " .. user_name .. ".")
		return
    end

    if is_new then
		print("New user: " .. role:GetName())
		user:GMCommand("RobotEquipment()")
    end
    
    local pos = math.random(5);
    user:GMCommand("Jump(101, 0, "..robot_init_pos[pos].x..", "..
		robot_init_pos[pos].y..", "..robot_init_pos[pos].z..")");
    role:SetHome(101, robot_init_pos[pos].x * POINT_PER_CM, 
		robot_init_pos[pos].y * POINT_PER_CM, robot_init_pos[pos].z * POINT_PER_CM);
    
--    ai:SetAIScript('robot_role.lua')
end

function learn_and_equip_spell(user, role, spell_id, spell_level)
	local ret = 0;
	local session_id = user:GetSessionID();

	ret = user:LearnSpell(spell_id, spell_level, false);
	msg = recv_msg(5, session_id, protocol.g2c_role_learn_spell);
	check(ret, "failed to learn spell");

	ret = user:EquipSpell(3, spell_id);
    msg = recv_msg(5, session_id, protocol.g2c_equip_spell);
    check(msg, "failed to  recv g2c_equip_spell");
end

function learn_and_cast_spell(user, role, spell_id, spell_level, target_role, x, y, z)
	local ret = 0;
	local session_id = user:GetSessionID();

	learn_and_equip_spell(user, roll, spell_id, spell_level);

	ret = user:CastSpell(3, target_role:GetObjID(), x, y, z);
    check(ret, "failed to cast spell");
end
