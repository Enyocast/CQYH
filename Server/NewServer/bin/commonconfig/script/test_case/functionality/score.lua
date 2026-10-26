TestCase.DungeonScore = {};

function TestCase.TreeTest()
	local msg;
    local ret = 0;
    local user_name = "Tm_Score"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");
    
    if oScene:GetSceneTempID() ~= 1 then
		JumpToStartMap(user);
    end

	ret = user:GMCommand("Jump 2 0 1000 1000");
    check(ret, "exec GMCommand Jump error");

	msg = recv_msg(30, session_id_1, protocol.g2c_leave_scene);
	check(msg, "failed to  recv g2c_leave_scene teleport:");

	msg = recv_msg(30, session_id_1, protocol.g2c_enter_scene);
	check(msg, "failed to  recv g2c_enter_scene teleport:");

	msg = recv_msg(30, session_id_1, protocol.g2c_char_appear);
	check(msg, "failed to  recv g2c_char_appear teleport:");

    oScene = role:GetScene();
    check(oScene, "can't get Scene");
	check(oScene:GetSceneTempID() == 2, "can't jump to Dungeon");
	
	ret = user:GMCommand("SummonNpc(5126)");
    check(ret, "exec GMCommand SummonNpc error");

    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
    check(msg, "failed to received g2c_sync_npc_data");
    
    while msg.nTemplateID ~= 5126 do
	    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
		check(msg, "failed to received g2c_sync_npc_data");
    end
    local targetNpcID = msg.dwNpcID;
	
	ret = user:GMCommand("Kill "..targetNpcID);
    check(ret, "exec GMCommand KillNpc error");
    
    msg = recv_msg(10, session_id_1, protocol.g2c_scene_finish);
    check(msg, "failed to received g2c_scene_finish");

    msg = recv_msg(40, session_id_1, protocol.g2c_dungeon_finish_data);
    check(msg, "failed to received g2c_dungeon_finish_data");

    msg = recv_msg(40, session_id_1, protocol.g2c_dungeon_finish_score);
    check(msg, "failed to received g2c_dungeon_finish_score");
	    
    wait(5);
    
    ret = g_RobotMessageHandler:DoSelectReward(role, edrFirst);
    check(ret, "DoSelectReward error");

    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_reward);
    check(msg, "failed to received g2c_dungeon_reward");
    
    wait(5);
    
    retMsg = recv_msg_and(160, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_1, protocol.g2c_char_appear);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	wait(5);
    cleanup(user);
end

function TestCase.DungeonScore.RoleScore()
    local msg;
    local nSceneType;
    local ret = 0;
    local user_name = "Tm_Score"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");
    
    if oScene:GetSceneTempID() ~= 100 then
		JumpToStartMap(user);
    end

	oScene = role:GetScene();
    check(oScene, "can't get Scene");
    check(oScene:GetSceneTempID() == 1, "can't get Scene");
    
    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
		 oTeleport = oStaticData:FindTeleportPoint(i);
		 if oTeleport then
			nSceneType = get_scene_type(oTeleport.TargetSceneID);
		 end 
		 if(oTeleport ~= nil and oTeleport.TargetSceneID == 102 and nSceneType == estDungeon) then
			break;
		 end
		 i = i + 1;
    end
    check(oTeleport, "the scene isn't have teleport other static scene "..oScene:GetSceneTempID());
    
    JumpToTelportInScene(user, i);

    ret = user:Teleport(i);
    check(ret, "failed to telport");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");
    check(msg.byMaxSceneDifficulty == esdNormal, "failed to received g2c_query_scene_difficulty");

    ret = user:SelectDungeonDifficulty(esdNormal);
    check(ret, "exec SelectDungeonDifficulty error");

    ret = user:EnterDungeon(esdHard);
    check(ret, "exec EnterDungeon error");
	
	msg = recv_msg(30, session_id_1, protocol.t2c_robot_disconnected);
	check(msg, "failed to received t2c_robot_disconnected");

	cleanup(user);    
	wait(5);
	
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id_1 = user:GetSessionID();
    role_id_1 = role:GetObjID();
    
    ret = user:Teleport(i);
    check(ret, "failed to telport");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");
    check(msg.byMaxSceneDifficulty == esdNormal, "failed to received g2c_query_scene_difficulty");

    ret = user:SelectDungeonDifficulty(esdNormal);
    check(ret, "exec SelectDungeonDifficulty error");

    ret = user:EnterDungeon(esdNormal);
    check(ret, "exec EnterDungeon error");

    local retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
    
    local k, v;
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    role = user:GetPlayingRole();
    check(role, "not role in Scene");
    check(role:GetSceneTempID()==oTeleport.TargetSceneID, "can't jump to the suceese");
    
    wait(2);
	
	ret = user:GMCommand("SummonNpc(5001)");
    check(ret, "exec GMCommand SummonNpc error");

    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
    check(msg, "failed to received g2c_sync_npc_data");
    
    while msg.nTemplateID ~= 5001 do
	    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
		check(msg, "failed to received g2c_sync_npc_data");
    end
    local targetNpcID = msg.dwNpcID;
	
	ret = user:GMCommand("KillNpc("..targetNpcID..")");
    check(ret, "exec GMCommand KillNpc error");
    
    msg = recv_msg(30, session_id_1, protocol.g2c_scene_finish);
    check(msg, "failed to received g2c_scene_finish");

    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_finish_data);
    check(msg, "failed to received g2c_dungeon_finish_data");

    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_finish_score);
    check(msg, "failed to received g2c_dungeon_finish_score");
	    
    wait(5);
    
    ret = g_RobotMessageHandler:DoSelectReward(role, edrFirst);
    check(ret, "DoSelectReward error");

    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_reward);
    check(msg, "failed to received g2c_dungeon_reward");
    
    wait(5);
    
    ret = g_RobotMessageHandler:DoReplayDungeon(role);
    check(ret, "DoReplayDungeon error");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");
    check(msg.byMaxSceneDifficulty == 4, "failed to received g2c_query_scene_difficulty");


    ret = user:SelectDungeonDifficulty(esdHard);
    check(ret, "exec SelectDungeonDifficulty error");

    ret = user:EnterDungeon(esdHard);
    check(ret, "exec EnterDungeon error");

    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_1, protocol.g2c_char_appear);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	wait(5);
	
	ret = user:GMCommand("SummonNpc(5001)");
    check(ret, "exec GMCommand JumpTo error");

    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
    check(msg, "failed to received g2c_sync_npc_data");
    
    while msg.nTemplateID ~= 5001 do
	    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
		check(msg, "failed to received g2c_sync_npc_data");
    end
    
    local targetNpcID = msg.dwNpcID;
	
	ret = user:GMCommand("KillNpc("..targetNpcID..")");
    check(ret, "exec GMCommand KillNpc error");
    
    msg = recv_msg(30, session_id_1, protocol.g2c_scene_finish);
    check(msg, "failed to received g2c_scene_finish");
    
    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_finish_data);
    check(msg, "failed to received g2c_scene_finish");

    msg = recv_msg(30, session_id_1, protocol.g2c_dungeon_finish_score);
	check(msg, "failed to received g2c_dungeon_finish_score");

    retMsg = recv_msg_and(160, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_1, protocol.g2c_char_appear);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	wait(5);
    cleanup(user);
    
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id_1 = user:GetSessionID();
    role_id_1 = role:GetObjID();
    
    ret = user:Teleport(i);
    check(ret, "failed to telport");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");
    check(msg.byMaxSceneDifficulty == esdHell, "failed to received g2c_query_scene_difficulty");
    
    wait(5);
    cleanup(user);
end;


function TestCase.DungeonScore.TeamScore()
    local msg;
    local nSceneType;
    local ret = 0;
    local user_name = "Tm_Score1"..os.date("%H%M%S");
    local user_name_2 = "Tm_Score2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();

    local user_2, role_2 = startup(user_name_2, user_name_2);
    check(user_2, "failed to create user");
    check(role_2, "failed to create role");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    if oScene:GetSceneTempID() ~= 100 then
		JumpToStartMap(user);
		JumpToStartMap(user_2);
    end
    
    oScene = role:GetScene();
    check(oScene, "can't get Scene");
    check(oScene:GetSceneTempID() == 100, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
		 oTeleport = oStaticData:FindTeleportPoint(i);
		 if oTeleport then
			nSceneType = get_scene_type(oTeleport.TargetSceneID);
		 end
		 if(oTeleport ~= nil and oTeleport.TargetSceneID == 102 and nSceneType == estDungeon) then
			break;
		 end
		 i = i + 1;
    end
    check(oTeleport, "the scene isn't have teleport other static scene "..oScene:GetSceneTempID());
    
    JumpToTelportInScene(user, i);
    JumpToTelportInScene(user_2, i);
    
	InviteToTeam(user, role, user_2, role_2, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_join, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    ret = user:Teleport(i);
    check(ret, "failed to telport");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");

    ret = user:SelectDungeonDifficulty(esdNormal);
    check(ret, "exec SelectDungeonDifficulty error");

    ret = user:EnterDungeon(esdNormal);
    check(ret, "exec EnterDungeon error");

    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene,session_id_2, protocol.g2c_leave_scene, 
			  session_id_2, protocol.g2c_changescene_enter, session_id_2, protocol.g2c_enter_scene);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");

    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    role = user:GetPlayingRole();
    check(role, "not role in Scene");
    check(role:GetSceneTempID()==oTeleport.TargetSceneID, "can't jump to the suceese");
    
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");
    check(role_2:GetSceneTempID() == oTeleport.TargetSceneID, "can't jump to the suceese");
    check(role_2:GetSceneID() == role:GetSceneID(), "can't jump to the suceese");

    wait(2);
	
	ret = user:GMCommand("SummonNpc(5001)");
    check(ret, "exec GMCommand SummonNpc error");

    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
    check(msg, "failed to received g2c_sync_npc_data");
    
    while msg.nTemplateID ~= 5001 do
	    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
		check(msg, "failed to received g2c_sync_npc_data");
    end
    local targetNpcID = msg.dwNpcID;
	
	ret = user_2:GMCommand("KillNpc("..targetNpcID..")");
    check(ret, "exec GMCommand KillNpc error");
    
    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_scene_finish, session_id_2, protocol.g2c_scene_finish,
						session_id_1, protocol.g2c_dungeon_finish_data, session_id_2, protocol.g2c_dungeon_finish_data,
						session_id_1, protocol.g2c_dungeon_finish_score, session_id_2, protocol.g2c_dungeon_finish_score);
    check(retMsg, "failed to received g2c_scene_finish or g2c_dungeon_finish_score");
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end
	    
    wait(5);
    
    ret = g_RobotMessageHandler:DoSelectReward(role, edrFirst);
    check(ret, "DoSelectReward error");

    retMsg = recv_msg(30, session_id_1, protocol.g2c_dungeon_reward, session_id_2, protocol.g2c_dungeon_reward);
    check(msg, "failed to received g2c_dungeon_reward");
    
    ret = g_RobotMessageHandler:DoSelectReward(role_2, edrFirst);
    check(ret, "DoSelectReward error");

    retMsg = recv_msg(30, session_id_1, protocol.g2c_dungeon_reward, session_id_2, protocol.g2c_dungeon_reward);
    check(msg, "failed to received g2c_dungeon_reward");

    wait(5);
    
    ret = g_RobotMessageHandler:DoReplayDungeon(role);
    check(ret, "DoReplayDungeon error");

    msg = recv_msg(10, session_id_1, protocol.g2c_query_scene_difficulty);
    check(msg, "failed to received g2c_query_scene_difficulty");

    ret = user:SelectDungeonDifficulty(esdNormal);
    check(ret, "exec SelectDungeonDifficulty error");

    ret = user:EnterDungeon(esdNormal);
    check(ret, "exec EnterDungeon error");

    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene,session_id_2, protocol.g2c_leave_scene, 
			  session_id_2, protocol.g2c_changescene_enter, session_id_2, protocol.g2c_enter_scene);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
	
	for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	wait(5);
	
	ret = user:GMCommand("SummonNpc(5001)");
    check(ret, "exec GMCommand SummonNpc error");

    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
    check(msg, "failed to received g2c_sync_npc_data");
    
    while msg.nTemplateID ~= 5001 do
	    msg = recv_msg(30, session_id_1, protocol.g2c_sync_npc_data);
		check(msg, "failed to received g2c_sync_npc_data");
    end
    
    local targetNpcID = msg.dwNpcID;
	
	ret = user_2:GMCommand("KillNpc("..targetNpcID..")");
    check(ret, "exec GMCommand KillNpc error");
    
	retMsg = recv_msg_and(30, session_id_1, protocol.g2c_scene_finish, session_id_2, protocol.g2c_scene_finish,
						session_id_1, protocol.g2c_dungeon_finish_data, session_id_2, protocol.g2c_dungeon_finish_data,
						session_id_1, protocol.g2c_dungeon_finish_score, session_id_2, protocol.g2c_dungeon_finish_score);
    check(retMsg, "failed to received g2c_scene_finish or g2c_dungeon_finish_score");
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

    retMsg = recv_msg_and(160, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_2, protocol.g2c_leave_scene, 
			  session_id_2, protocol.g2c_changescene_enter, session_id_2, protocol.g2c_enter_scene);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");
    
    for k,v in pairs(retMsg) do
		check(v.msg, "fail to recv allserver msg");
	end

	wait(5);

    cleanup(user);    
	cleanup(user_2);    

end;

function TestCase.AreanScore()
    local ret = 0;

	local KValue = 64;
	local ScoreArea = 100;
	local ResultScore = 1700;
	local CurrentScore = 900;
	local wScoreRate = {};

	for i = 1,1200,1 do
		wScoreRate[i] = 1 / (1 + math.pow(10, i/400));
	end	
	
	math.randomseed(os.time());
	print("init end");
	
	local i = 0;
	--while (ResultScore - CurrentScore) > 5 or (CurrentScore - ResultScore) > 5 do
	for i = 1,1000,1 do
		local currentCompetitor = math.random(CurrentScore - ScoreArea, CurrentScore + ScoreArea);
		
		if(currentCompetitor < 0) then
			currentCompetitor = 0;
		end
		--print(currentCompetitor);
		
		local winRate = 0;
		if ResultScore > currentCompetitor then
			winRate = 1 - wScoreRate[ResultScore-currentCompetitor];
		elseif  currentCompetitor > ResultScore then
			winRate = wScoreRate[currentCompetitor-ResultScore];
		else
			winRate = 0.5;
		end
		--print("plan win rate:"..winRate);

		local realWinRate = 0;
		if CurrentScore > currentCompetitor then
			realWinRate = 1 - wScoreRate[CurrentScore-currentCompetitor];
		elseif  currentCompetitor > CurrentScore then
			realWinRate = wScoreRate[currentCompetitor-CurrentScore];
		else
			realWinRate = 0.5;
		end
		--print("real win rate:"..realWinRate);

		local randValue = math.random();
		--print("randValue:"..randValue);
		
		if winRate >= randValue then
			CurrentScore = CurrentScore + KValue * (1 - realWinRate);
		else
			CurrentScore = CurrentScore - KValue * realWinRate;
			print("lose");
		end
		
		--i = i + 1;
		
		CurrentScore = math.floor(CurrentScore);
		--print("current score:"..CurrentScore);
		
		if i % 10 == 0 then
			print(""..i.." times, current score:"..CurrentScore);
		end
	end
	
	print("target count()"..i);

end;