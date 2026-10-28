
TestCase.Spell = {};
TestCase.Aura = {};

function TestCase.Spell.Formular()
    local ret;
    local msg;

    local user_name = "F" .. os.date("%H%M%S");
    local user;
    local role;
    local session_id;

	local user_name_target = "FT" .. os.date("%H%M%S");
	local user_target;
	local role_target;
	local session_id_target;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

	user_target, role_target = startup(user_name_target, user_name_target);
    check(user_target, "failed to create user_target");
    check(role_target, "failed to create role_target");

    session_id = user:GetSessionID();
	session_id_target = user_target:GetSessionID();

	learn_and_cast_spell(user, role, 2002, 1, role_target, 0, 0, 0);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_passive_move");

    msg = recv_msg(5, session_id, protocol.g2c_char_spell_pre_effect);
    check(msg, "failed to  recv g2c_char_cast_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_spell_effect);
    check(msg, "failed to  recv g2c_char_cast_spell");

    cleanup(user);

end

function TestCase.Spell.Charge()
    local user_name = "Charge" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsWarrior);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 2021, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_passive_move);
    check(msg, "failed to  recv g2c_char_passive_move");

    msg = recv_msg(10, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

	wait(5);

    cleanup(user);
end

function TestCase.Spell.Missile()
    local user_name = "Missile" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsWarrior);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 2025, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(10, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

    msg = recv_msg(10, session_id, protocol.g2c_missile_appear);
    check(msg, "failed to  recv g2c_char_cast_spell");

	wait(5);
    cleanup(user);
end

function TestCase.Spell.Spell_3000()
    local user_name = "Sp3000" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsMage);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 3000, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(10, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

    msg = recv_msg(10, session_id, protocol.g2c_missile_appear);
    check(msg, "failed to  recv g2c_char_cast_spell");

	wait(5);
    cleanup(user);

end

function TestCase.Spell.Spell_3002()
    local user_name = "Sp3002" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsMage);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 3002, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(10, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell 1");

	wait(5);
    cleanup(user);

end

function TestCase.Spell.Spell_3005()
    local user_name = "Sp3005" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsMage);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 3005, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

    cleanup(user);
end

function TestCase.Spell.ActivateRune()
    local user_name = "ActiRune" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsMage);
    check(user, "failed to create user");
    check(role, "failed to create role");

	learn_and_equip_spell(user, role, 101, 1);

	for i = 1, 5 do
	    ret = user:GMCommand("AddItem(111, 1)");
	    check(ret, "failed to send gm command");
	    ret = user:GMCommand("AddItem(119, 1)");
	    check(ret, "failed to send gm command");
	    ret = user:GMCommand("AddItem(110, 1)");
	    check(ret, "failed to send gm command");
	    ret = user:GMCommand("AddItem(101, 1)");
	    check(ret, "failed to send gm command");
	    ret = user:GMCommand("AddItem(109, 1)");
	    check(ret, "failed to send gm command");
	end

	user:ActivateRune(1001);
    msg = recv_msg(5, session_id, protocol.g2c_rune_activate);
    check(msg, "failed to  recv g2c_rune_activate");
	check(msg.nErrCode == errSuccess, "process error");

	user:ActivateRune(1002);
    msg = recv_msg(5, session_id, protocol.g2c_rune_activate);
    check(msg, "failed to  recv g2c_rune_activate");
	check(msg.nErrCode == errRuneLackOfItem, "process error");
end

function TestCase.Spell.Spell_Archer()
    local user_name = "SpArcher" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsArcher);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 4120, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

    cleanup(user);
end

function TestCase.Spell.Spell_Rogue()
    local user_name = "SpRoger" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsRogue);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

	learn_and_cast_spell(user, role, 5001, 1, nil, 0, 0, 0);
    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);

    msg = recv_msg(5, session_id, protocol.g2c_char_prepare_spell);
    check(msg, "failed to  recv g2c_char_prepare_spell");

    msg = recv_msg(5, session_id, protocol.g2c_char_cast_spell);
    check(msg, "failed to  recv g2c_char_cast_spell");

    cleanup(user);
end

function TestCase.Aura.Remain()
    local user_name = "AR_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsRogue);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
	wait(2);

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);
	user:DirectlyCastSpell(2, 1, role:GetObjID(), 0, 0, 0);
end

function TestCase.Aura.Stack()
    local user_name = "AS_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsRogue);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
	wait(2);

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);

    msg = recv_msg(3, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 1, "aura error");

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);

    msg = recv_msg(3, session_id, protocol.g2c_aura_change);
    check(msg, "failed to  recv g2c_aura_change");
    check(msg.byStackCount == 2, "aura stack error, stack count:"..msg.byStackCount);

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);

    msg = recv_msg(3, session_id, protocol.g2c_aura_change);
    check(msg, "failed to  recv g2c_aura_change");
    check(msg.byStackCount == 3, "aura stack error, stack count:"..msg.byStackCount);

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);

    msg = recv_msg(3, session_id, protocol.g2c_aura_change);
    check(msg == nil, "failed to  recv g2c_aura_change");
end

function TestCase.Aura.Substitute()
    local user_name = "ASu" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsRogue);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
	wait(2);

	user:DirectlyCastSpell(1, 1, role:GetObjID(), 0, 0, 0);
    msg = recv_msg(1, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 1, "aura error");
	local aura_id_1 = msg.dwInstanceID;

	user:DirectlyCastSpell(3, 1, role:GetObjID(), 0, 0, 0);
    msg = recv_msg(1, session_id, protocol.g2c_del_aura);
    check(msg, "failed to  recv g2c_del_aura");
    check(msg.dwInstanceID == aura_id_1, "aura error");

    msg = recv_msg(1, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 3, "aura error");
end

function TestCase.Aura.Cover()
    local user_name = "AC_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    --Log in
    user, role = startup(user_name, user_name, nil, clsRogue);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
	wait(2);

	user:DirectlyCastSpell(4, 1, role:GetObjID(), 0, 0, 0);

    msg = recv_msg(1, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 4, "aura error");
	local aura_id_4 = msg.dwInstanceID;

	user:DirectlyCastSpell(5, 1, role:GetObjID(), 0, 0, 0);
    msg = recv_msg(1, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 5, "aura error");
	local aura_id_5 = msg.dwInstanceID;

	user:DirectlyCastSpell(6, 1, role:GetObjID(), 0, 0, 0);
    msg = recv_msg(1, session_id, protocol.g2c_del_aura);
    check(msg, "failed to  recv g2c_del_aura");
    check(msg.dwInstanceID == aura_id_4, "aura error");

    msg = recv_msg(1, session_id, protocol.g2c_new_aura);
    check(msg, "failed to  recv g2c_new_aura");
    check(msg.wAuraID == 6, "aura error");
end

function TestCase.Spell.NormalPractice()
    local user_name = "NP_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    user, role = startup(user_name, user_name, nil, clsArcher);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    user:GMCommand("AddAbilityPts(100000)");

	user:NormalPractice(2001, 3);

	msg = recv_msg(1, session_id, protocol.g2c_start_practice);
    check(msg, "failed to  recv g2c_start_practice");

	msg = recv_msg(60, session_id, protocol.g2c_spell_level_up);
    check(msg, "failed to  recv g2c_start_practice");
end

function TestCase.Spell.FastPractice()
    local user_name = "FP_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local user_id;

    user, role = startup(user_name, user_name, nil, clsArcher);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    user:GMCommand("AddAbilityPts(100000)");
    user:GMCommand("AddMoney(1, 100000, MONEYLOG_GM_COMMAND)");

	user:FastPractice(2001);

	msg = recv_msg(1, session_id, protocol.g2c_start_practice);
    check(msg, "failed to  recv g2c_start_practice");

	msg = recv_msg(60, session_id, protocol.g2c_spell_level_up);
    check(msg, "failed to  recv g2c_start_practice");
end
