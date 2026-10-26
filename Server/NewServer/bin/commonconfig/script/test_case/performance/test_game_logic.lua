
--scene_type: 0 = prog island, 1 = normal
local g_test_scene_type = 1;
g_inited_robot = {};

function Test_Game_Logic(username)
	local sceneTempID = 113;
	local pos = {68431, 33987, 40198};
	local relogin = false;
	local g_nStartTryCount = 0;

	if g_test_scene_type == 0 then
	    sceneTempID = 1;
		pos = {1000, 1000, 20000};
	elseif g_test_scene_type == 1 then
		sceneTempID = 142;
		pos = random_pos(sceneTempID);
		--pos = {30800-250+math.random(500), 52300-250+math.random(500), 43700};
	end

	local roleClass = math.random(0,2);
	if (roleClass == 2) then
		roleClass = 4;
	end

	if string.sub(g_RunningCoName, 1, 8) == 'relogin_' then
	    wait(10);
	    relogin = true;
	end

	--local groupID = tonumber( string.sub(username,9) ) or 0;
	--groupID = groupID % 32;
	groupID = 1;
	local flag, user, role = performance_startup(username, username, groupID, roleClass);

	if flag then
		if not user:IsConnected() then
			print("user "..username.."performance_startup ok but disconnected!");
			return false;
		end

		local ai = role:SetAIProcessor(99) -- must prior protocol.g2c_enter_scene to run init tree
		if not ai then
			print("Create AI fail for " .. username .. ".")
		end

		local oScene = role:GetScene();
		check(oScene, "can't enter the scene")

		if oScene:GetSceneTempID() ~= sceneTempID then
			local session_id = user:GetSessionID();
			local role = user:GetPlayingRole();

			ret = user:GMCommand("Jump("..sceneTempID..",0,"..pos[1]..","..pos[2]..","..pos[3]..")");
			check(ret, "exec GMCommand JumpTo diff scene error");

--			msg = recv_msg(30, session_id, protocol.g2c_leave_scene);
--			check(msg, "failed to  recv g2c_leave_scene");

--			msg = recv_msg(30, session_id, protocol.g2c_changescene_enter);
--			check(msg, "failed to  recv g2c_changescene_enter");

			msg = recv_msg(30, session_id, protocol.g2c_enter_scene);
			check(msg, "failed to  recv g2c_enter_scene jump in the diff scene");
			check(msg.nSceneTempID == sceneTempID);

            role:SetHome(sceneTempID, role:GetX(), role:GetY(), role:GetZ());

--			msg = recv_msg(30, session_id, protocol.g2c_char_appear);
--			check(msg, "failed to  recv g2c_char_appear");
		else
			local session_id = user:GetSessionID();
			local role = user:GetPlayingRole();

			ret = user:GMCommand("Jump("..pos[1]..","..pos[2]..","..pos[3]..")");
			check(ret, "exec GMCommand JumpTo same scene error");

--			msg = recv_msg(30, session_id, protocol.g2c_leave_scene);
--			check(msg, "failed to  recv g2c_leave_scene");

--			msg = recv_msg(30, session_id, protocol.g2c_changescene_enter);
--			check(msg, "failed to  recv g2c_changescene_enter");

			msg = recv_msg(30, session_id, protocol.g2c_enter_scene);
			check(msg, "failed to  recv g2c_enter_scene when jump in the same scene");
			check(msg.nSceneTempID == sceneTempID);

            role:SetHome(sceneTempID, role:GetX(), role:GetY(), role:GetZ());

--			msg = recv_msg(30, session_id, protocol.g2c_char_appear);
--			check(msg, "failed to  recv g2c_char_appear");
		end

		local inited = g_inited_robot[username];
	    if not inited then
    	    user:GMCommand("InitRobot(true)");
			g_inited_robot[username] = true;
			print("user "..username.." has inited robot data");
			
		--[[
			local specify_spell_id = 2536;
			local specify_spell_rune = nil;
			
    	    user:GMCommand("LearnSpell("..specify_spell_id..")");
    	    user:GMCommand("EquipSpell("..specify_spell_id..", 1, true)");
			if( specify_spell_rune ~= nil ) then
				user:GMCommand("SetRune("..specify_spell_id..","..specify_spell_rune..")");	
			end
		--]]
	    end
	else
		print("start up error user:"..username.." username:"..username);
		if user ~= nil then
			performance_cleanup(user);
		end
	end
	print("user "..username.." coroutine finished");
end

function PerfTestCase.GameLogic()
	math.randomseed(os.time());
	local roleCount = 100;
	g_func = Test_Game_Logic;
	for i=1,roleCount do
		local username = "cq"..os.date("%H%M%S")..""..i;
		addco(username, Test_Game_Logic, username);
	end
end

