
TestCase.TeamJump = {};

function TeamJumpByTelport(user_1, user_2, nTeleportIndex)
    local role_1 = user_1:GetPlayingRole();
    check(role_1, "not role in Scene");
    local session_id_1 = user_1:GetSessionID();
    local team_id = role_1:GetTeamID();
    check(team_id > 0, "role_1 not in the team")
    local oScene = role_1:GetScene();

    local role_2 = user_2:GetPlayingRole();
    check(role_2, "not role in Scene");
    local session_id_2 = user_2:GetSessionID();
    check(team_id == role_2:GetTeamID(), "role_2 not in the same team");
    check(oScene:GetSceneTempID() == role_2:GetScene():GetSceneTempID(), "role_2 not in tht same scene");
    check(oScene:GetSceneID() == role_2:GetScene():GetSceneID(), "role_2 not in tht same scene");

    local oStaticData = oScene:GetStaticData();
    local nCurSceneTempID = oScene:GetSceneTempID();
    check(oStaticData, "static Data is error"..nCurSceneTempID);
    local nCurSceneType = get_scene_type(nCurSceneTempID);

    oTeleport = oStaticData:FindTeleportPoint(nTeleportIndex);
    check(oTeleport, "the teleport is not exist"..nTeleportIndex);
    local nTargetSceneTempID = oTeleport.TargetSceneID;
    local nTargetSceneType = get_scene_type(nTargetSceneTempID);

    JumpToTelportInScene(user_1, nTeleportIndex);
    JumpToTelportInScene(user_2, nTeleportIndex);

    ret = user_1:Teleport(nTeleportIndex);
    check(ret, "failed to telport");

    if(oTeleport.SrcSceneID ~= nTargetSceneTempID and nTargetSceneType == estDungeon) then
	    local retMsg = recv_msg_and(10, session_id_1, protocol.g2c_query_scene_difficulty, session_id_2, protocol.g2c_query_scene_difficulty);
	    check(retMsg, "failed to received g2c_query_scene_difficulty");

	    ret = user_1:SelectDungeonDifficulty(1);
	    check(ret, "exec SelectDungeonDifficulty error");

	    retMsg = recv_msg_and(10, session_id_1, protocol.g2c_select_scene_difficulty, session_id_2, protocol.g2c_select_scene_difficulty);
        check(retMsg, "failed to received g2c_select_scene_difficulty");

	    ret = user_1:EnterDungeon(2);
        check(ret, "exec EnterDungeon error");

	    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_1, protocol.g2c_char_appear,
			  session_id_2, protocol.g2c_leave_scene, session_id_2, protocol.g2c_changescene_enter,
			  session_id_2, protocol.g2c_enter_scene, session_id_2, protocol.g2c_char_appear);
	    check(ret, "failed to receive g2c_leave_scene or g2c_enter_scene");
    else
	    JumpToByTeleport(user_2, nTeleportIndex);
	    JumpToByTeleport(user_1, nTeleportIndex);	    
    end

    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");
	    
    role_1 = user_1:GetPlayingRole();
    check(role_1, "not role_2 in Scene");

    check(role_1:GetSceneTempID()==nTargetSceneTempID, "role["..role_1:GetSceneTempID().. "]can't jump to right scene["..nTargetSceneTempID.."]");
    check(role_2:GetSceneTempID()==nTargetSceneTempID, "role can't jump to right scene");
    check(role_1:GetSceneID()==role_2:GetSceneID(), "role can't jump to other scene");

    wait(1);
end

function TestCase.TeamJump.Normal()
    local msg;
    local nSceneType;
    local ret = 0;
    local user_name = "Tm_JpNor1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_JpNor2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
    JumpToStartMap(user);
    role = user:GetPlayingRole();
    check(role, "not role in Scene");

    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to create team");
    wait(1);

    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    JumpToStartMap(user_2);
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");

	InviteToTeam(user_2, role_2, user, role, 0);

	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    check(role:GetSceneTempID()==role_2:GetSceneTempID(), "two role not in same scene");
    check(role:GetSceneID()==role_2:GetSceneID(), "two role not in same scene");

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
	 oTeleport = oStaticData:FindTeleportPoint(i);
	 if oTeleport ~= nil then
		nSceneType = get_scene_type(oTeleport.TargetSceneID);
		if (oTeleport.SrcSceneID ~= oTeleport.TargetSceneID and nSceneType == estStatic) then
			break;
		end
	 end
	 i = i + 1;
    end

    check(oTeleport, "the scene isn't have teleport other static scene "..oScene:GetSceneTempID());
    JumpToByTeleport(user, i);
    role = user:GetPlayingRole();
    check(role, "not role in Scene");

    check(role:GetSceneTempID()~=role_2:GetSceneTempID(), "role can't jump to other scene");
    wait(1);

    JumpToByTeleport(user_2, i);
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");

    check(role:GetSceneTempID()==role_2:GetSceneTempID(), "role_2 can't jump to other scene");
    wait(1);
	
    check(role:GetTeamID()== team_id, "the team info have errors");
    check(role:GetTeamID()==role_2:GetTeamID(), "the team info have errors");

    ret = LeaveTeam(user, role);
    check(ret == team_id, "failed to leave team");
    check(role:GetTeamID()==0, "the team info have errors");

    ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");
    check(role_2:GetTeamID()==0, "the team info have errors");

    cleanup(user);
    cleanup(user_2);
end;

function TestCase.TeamJump.Dungeon()

    local msg;
    local nSceneType;
    local ret = 0;
    local user_name = "Tm_JpDg1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "Tm_JpDg2"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id_1 = user:GetSessionID();
    local role_id_1 = role:GetObjID();
    JumpToStartMap(user);
    role = user:GetPlayingRole();
    check(role, "not role in Scene");

    local team_id = CreateTeam(team_name, user, role);
    check(team_id, "failed to create team");
    wait(1);

    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    JumpToStartMap(user_2);
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");

	InviteToTeam(user_2, role_2, user, role, 0);
	
	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");


    check(role:GetSceneTempID()==role_2:GetSceneTempID(), "two role not in same scene");
    check(role:GetSceneID()==role_2:GetSceneID(), "two role not in same scene");

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
		 oTeleport = oStaticData:FindTeleportPoint(i);
		 
		 if oTeleport ~= nil then
			nSceneType = get_scene_type(oTeleport.TargetSceneID);
		 end
		 
		 if(oTeleport ~= nil and oTeleport.SrcSceneID ~= oTeleport.TargetSceneID and nSceneType == estDungeon) then
			break;
		 end
		 i = i + 1;
    end
    check(oTeleport, "the scene isn't have teleport other static scene "..oScene:GetSceneTempID());
    JumpToTelportInScene(user, i);
    JumpToTelportInScene(user_2, i);

    ret = user_2:Teleport(i);
    check(ret, "failed to telport");

    msg = recv_msg(10, session_id_2, protocol.g2c_error_notify);
    check(msg, "failed to  recv g2c_error_notify");
    check(msg.nErrCode == error_code.errSceneNotTeamLeader, "the errorcode["..msg.nErrCode.."]of g2c_error_notify is error");

    ret = user:Teleport(i);
    check(ret, "failed to telport");

    local retMsg = recv_msg_and(10, session_id_1, protocol.g2c_query_scene_difficulty, session_id_2, protocol.g2c_query_scene_difficulty);
    check(retMsg, "failed to received g2c_query_scene_difficulty");

    local k, v;
    for k,v in pairs(retMsg) do
		print(v.msgID);
		check(v.msg.byMaxSceneDifficulty == esdNormal, "err g2c_query_scene_difficulty value");
    end

    ret = user_2:SelectDungeonDifficulty(2);
    check(ret, "exec SelectDungeonDifficulty error");

    msg = recv_msg(10, session_id_2, protocol.g2c_error_notify);
    check(msg, "failed to  recv g2c_error_notify");
    check(msg.nErrCode == error_code.errSceneNotTeamLeader, "the errorcode of g2c_error_notify is error");

    ret = user:SelectDungeonDifficulty(2);
    check(ret, "exec SelectDungeonDifficulty error");

    retMsg = recv_msg_and(10, session_id_1, protocol.g2c_select_scene_difficulty, session_id_2, protocol.g2c_select_scene_difficulty);
    check(retMsg, "failed to received g2c_select_scene_difficulty");

    for k,v in pairs(retMsg) do
		check(v.msg.bySelectedDifficulty == 2, "err g2c_query_scene_difficulty value");
    end

    ret = user_2:EnterDungeon(2);
    check(ret, "exec EnterDungeon error");

    msg = recv_msg(10, session_id_2, protocol.g2c_error_notify);
    check(msg, "failed to  recv g2c_error_notify");
    check(msg.nErrCode == error_code.errSceneNotTeamLeader, "the errorcode of g2c_error_notify is error");

    ret = user:EnterDungeon(2);
    check(ret, "exec EnterDungeon error");

    retMsg = recv_msg_and(30, session_id_1, protocol.g2c_leave_scene, session_id_1, protocol.g2c_changescene_enter, 
			  session_id_1, protocol.g2c_enter_scene, session_id_1, protocol.g2c_char_appear,
			  session_id_2, protocol.g2c_leave_scene, session_id_2, protocol.g2c_changescene_enter,
			  session_id_2, protocol.g2c_enter_scene, session_id_2, protocol.g2c_char_appear);
    check(retMsg, "failed to receive g2c_leave_scene or g2c_enter_scene");

    role = user:GetPlayingRole();
    check(role, "not role in Scene");

    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");

    check(role:GetSceneTempID()==oTeleport.TargetSceneID, "can't jump to the suceesee");
    check(role:GetSceneTempID()==role_2:GetSceneTempID(), "role_2 can't jump to other scene");
    check(role:GetSceneID()==role_2:GetSceneID(), "role_1 and role_2 don't jump to same scene");
    wait(1);
	
    check(role:GetTeamID()== team_id, "the team info have errors");
    check(role:GetTeamID()==role_2:GetTeamID(), "the team info have errors");

    JumpToStartMap(user_2);
	wait(2);
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role in Scene");

    JumpToStartMap(user);
	wait(2);
    role = user:GetPlayingRole();
    check(role, "not role in Scene");

    cleanup(user);
    cleanup(user_2);
end;


function TestCase.TeamJump.DungeonExit()

    local msg;
    local nSceneType;
    local ret = 0;
    local user_name = "TmDg1"..os.date("%H%M%S");
    local team_name = user_name.."team";

    local user_name2 = "TmDg2"..os.date("%H%M%S");

    local user_1, role_1 = startup(user_name, user_name);
    check(user_1, "failed to create user");
    check(role_1, "failed to create role");
    local session_id_1 = user_1:GetSessionID();
    local role_id_1 = role_1:GetObjID();
    JumpToStartMap(user_1);
    role_1 = user_1:GetPlayingRole();
    check(role_1, "not role in Scene");

    local team_id = CreateTeam(team_name, user_1, role_1);
    check(team_id, "failed to create team");
    wait(1);

    local user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    local session_id_2 = user_2:GetSessionID();
    local role_id_2 = role_2:GetObjID();
    JumpToStartMap(user_2);
    role_2 = user_2:GetPlayingRole();
    check(role_2, "not role_2 in Scene");

	InviteToTeam(user_2, role_2, user_1, role_1, 0);
	
	local retMsg = recv_msg_and(30, session_id_1, protocol.m2c_team_add_member, session_id_2, protocol.m2c_team_join);
    check(retMsg, "failed to received m2c_team_add_member or m2c_team_join");

    check(role_1:GetSceneTempID()==role_2:GetSceneTempID(), "two role not in same scene");
    check(role_1:GetSceneID()==role_2:GetSceneID(), "two role not in same scene");

    local oScene = role_1:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
	 oTeleport = oStaticData:FindTeleportPoint(i);
	 
	 if oTeleport then
		nSceneType = get_scene_type(oTeleport.TargetSceneID);
	 end 
	 
	 if(oTeleport ~= nil and oTeleport.SrcSceneID ~= oTeleport.TargetSceneID and nSceneType == estDungeon) then
	    break;
	 end
	 i = i + 1;
    end
    check(oTeleport, "the scene isn't have teleport in the scene "..oScene:GetSceneTempID());

    TeamJumpByTelport(user_1, user_2, i);

    role_1 = user_1:GetPlayingRole();
    role_id_1 = role_1:GetObjID();
    check(role_1, "not role in Scene");
    
    wait(2);
    cleanup(user_2);
    wait(5);

    user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();
    check(role_1:GetSceneTempID()==role_2:GetSceneTempID(), "role_2 can't start to right scene");
    check(role_1:GetSceneID()==role_2:GetSceneID(), "role can't jump to other scene");
    wait(2);

    cleanup(user_2);
    cleanup(user_1);
    wait(5);
 
    user_1, role_1 = startup(user_name, user_name);
    check(user_1, "failed to create user");
    check(role_1, "failed to create role");
    session_id_1 = user_1:GetSessionID();
    role_id_1 = role_1:GetObjID();

    user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();

    check(role_1:GetSceneTempID()==oTeleport.TargetSceneID, "role_2 leave team can't start to the right scene");
    check(role_2:GetSceneTempID()==oTeleport.TargetSceneID, "role_2 can't start to right scene");
    check(role_2:GetTeamID()==team_id, "the team info have errors");
    check(role_1:GetTeamID()==team_id, "the team info have errors");

    cleanup(user_2);
    cleanup(user_1);
    wait(60);

    user_1, role_1 = startup(user_name, user_name);
    check(user_1, "failed to create user");
    check(role_1, "failed to create role");
    session_id_1 = user_1:GetSessionID();
    role_id_1 = role_1:GetObjID();

    user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();

    check(role_1:GetSceneTempID()==oTeleport.SrcSceneID, "role_2 leave team can't start to the right scene");
    check(role_2:GetSceneTempID()==oTeleport.SrcSceneID, "role_2 can't start to right scene");
    check(role_2:GetTeamID()==team_id, "the team info have errors");
    check(role_1:GetTeamID()==team_id, "the team info have errors");

    TeamJumpByTelport(user_1, user_2, i);
	wait(5);

	ret = g_RobotMessageHandler:DoLeaveScene(role_1);
    check(ret, "DoLeaveScene error");
	wait(5);

    role = user_1:GetPlayingRole();
    check(role, "not role in Scene");
    check(role:GetTeamID()==0, "the team info have errors");
	
	cleanup(user_2);
	wait(60);
	
	user_2, role_2 = startup(user_name2, user_name2);
    check(user_2, "failed to create user2");
    check(role_2, "failed to create role2");
    session_id_2 = user_2:GetSessionID();
    role_id_2 = role_2:GetObjID();
    
	check(role_2:GetSceneTempID()==oTeleport.SrcSceneID, "role_2 can't start to right scene");
    check(role_2:GetTeamID()==team_id, "the team info have errors");

	ret = LeaveTeam(user_2, role_2);
    check(ret == team_id, "failed to leave team");
    check(role_2:GetTeamID()==0, "the team info have errors");
	wait(2);

    cleanup(user_1);
    cleanup(user_2);
end;
