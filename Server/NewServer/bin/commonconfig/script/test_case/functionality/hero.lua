
TestCase.Hero = {};

function TestCase.Hero.Hire()
	local user_name = "FP_" .. os.date("%Y%m%d%H%M%S");
	local user;
	local role;
	local ret;
	local msg;
	local user_id;
	
	user, role = startup(user_name, user_name, nil, clsArcher, nil, 102);
	check(user, "failed to create user");
	check(role, "failed to create role");
	
	session_id = user:GetSessionID();
	user:GMCommand("HireHero(1, 0)");
	
	msg = recv_msg(1, session_id, protocol.g2c_hire_hero);
	check(msg, "failed to  recv g2c_hire_hero");
end

function TestCase.Hero.Fire()
	local user_name = "FP_" .. os.date("%Y%m%d%H%M%S");
	local user;
	local role;
	local ret;
	local msg;
	local user_id;
	
	user, role = startup(user_name, user_name, nil, clsArcher, nil, 102);
	check(user, "failed to create user");
	check(role, "failed to create role");
	
	session_id = user:GetSessionID();
	user:GMCommand("HireHero(1, 0)");
	
	msg = recv_msg(1, session_id, protocol.g2c_hire_hero);
	check(msg, "failed to  recv g2c_hire_hero");
	
	user:FireHero();
	
	msg = recv_msg(1, session_id, protocol.g2c_fire_hero);
	check(msg, "failed to  recv g2c_fire_hero");
end

function TestCase.Hero.Summon()
	local user_name = "FP_" .. os.date("%Y%m%d%H%M%S");
	local user;
	local role;
	local ret;
	local msg;
	local user_id;
	
	user, role = startup(user_name, user_name, nil, clsArcher, nil, 102);
	check(user, "failed to create user");
	check(role, "failed to create role");
	
	session_id = user:GetSessionID();
	user:GMCommand("HireHero(1, 0)");
	
	msg = recv_msg(1, session_id, protocol.g2c_hire_hero);
	check(msg, "failed to  recv g2c_hire_hero");
	
	user:SummonHero();
	
	msg = recv_msg(1, session_id, protocol.g2c_char_appear);
	check(msg, "failed to  recv g2c_char_appear");
end

function TestCase.Hero.Recall()
	local user_name = "FP_" .. os.date("%Y%m%d%H%M%S");
	local user;
	local role;
	local ret;
	local msg;
	local user_id;
	
	user, role = startup(user_name, user_name, nil, clsArcher, nil, 102);
	check(user, "failed to create user");
	check(role, "failed to create role");
	
	session_id = user:GetSessionID();
	user:GMCommand("HireHero(1, 0)");
	
	msg = recv_msg(1, session_id, protocol.g2c_hire_hero);
	check(msg, "failed to  recv g2c_hire_hero");
	
	user:SummonHero();
	
	msg = recv_msg(1, session_id, protocol.g2c_char_appear);
	check(msg, "failed to  recv g2c_char_appear");
	
	user:RecallHero();
	
	msg = recv_msg(1, session_id, protocol.g2c_object_disappear);
	check(msg, "failed to  recv g2c_object_disappear");
end