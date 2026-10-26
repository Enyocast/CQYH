TestCase.Move = {};

function JumpToTelportInScene(user, index)
    
    local session_id = user:GetSessionID();
    
    local oRole = user:GetPlayingRole();
    check(oRole, "not role in Scene");

    local oScene = oRole:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local oTeleport = oStaticData:FindTeleportPoint(index);
    check(oTeleport, "oTeleport is not exist index:"..index);
    
    if(oTeleport ~= nil) then
	 ret = user:GMCommand("Jump("..index..")");
	 check(ret, "exec GMCommand JumpTo error(sceneTempID, nTeleport) ".."("..oScene:GetSceneTempID()..", "..index..")");
	
	 msg = recv_msg(30, session_id, protocol.g2c_leave_scene);
	 check(msg, "failed to  recv g2c_leave_scene teleport:"..index);

         msg = recv_msg(30, session_id, protocol.g2c_enter_scene);
         check(msg, "failed to  recv g2c_enter_scene teleport:"..index);

         msg = recv_msg(30, session_id, protocol.g2c_char_appear);
         check(msg, "failed to  recv g2c_char_appear teleport:"..index);
    end
end


function JumpToByTeleport(user, index)
    
    if(g_oGameWorld == nil) then
	g_oGameWorld = CGameWorld:GetInstance();
    end

    local session_id = user:GetSessionID();

    local oRole = user:GetPlayingRole();
    check(oRole, "not role in Scene");

    local oScene = oRole:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local oTeleport = oStaticData:FindTeleportPoint(index);    
    if(oTeleport == nil) then
	return;
    end

    local nSceneType = get_scene_type(oTeleport.TargetSceneID);

    JumpToTelportInScene(user, index);
    
    ret = user:Teleport(index);
    check(ret, "failed to teleport");

    if (nSceneType == estDungeon and oTeleport.SrcSceneID ~= oTeleport.TargetSceneID) then
		msg = recv_msg(10, session_id, protocol.g2c_query_scene_difficulty);
		check(msg, "failed to  recv g2c_query_scene_difficulty");

		ret = user:SelectDungeonDifficulty(2);
		check(ret, "exec SelectDungeonDifficulty error");

		msg = recv_msg(10, session_id, protocol.g2c_select_scene_difficulty);
		check(msg, "failed to  recv g2c_select_scene_difficulty");
		check(msg.bySelectedDifficulty == 2, " the g2c_select_scene_difficulty vlue is error");

		ret = user:EnterDungeon(2);
		check(ret, "exec EnterDungeon error");
    end

    msg = recv_msg(100, session_id, protocol.g2c_leave_scene);
    check(msg, "failed to  recv g2c_leave_scene err Index:"..index);

    if(oTeleport.SrcSceneID ~= oTeleport.TargetSceneID) then
	msg = recv_msg(10, session_id, protocol.g2c_changescene_enter);
	check(msg, "failed to  recv g2c_changescene_enter");
    end

    msg = recv_msg(30, session_id, protocol.g2c_enter_scene);
    check(msg, "failed to  recv g2c_enter_scene");

    msg = recv_msg(30, session_id, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_char_appear");
end


function JumpToProIsLand(user)
    
    local session_id = user:GetSessionID();
    local role = user:GetPlayingRole();
    check(role, "not role in Scene");

    if(role:GetSceneTempID() == 2) then
		return;
    end
    
    ret = user:GMCommand("Jump(2, 1, 9300, 7563, 4356)");
    check(ret, "exec GMCommand JumpTo error");

    msg = recv_msg(10, session_id, protocol.g2c_leave_scene);
    check(msg, "failed to  recv g2c_leave_scene");

    msg = recv_msg(10, session_id, protocol.g2c_changescene_enter);
    check(msg, "failed to  recv g2c_changescene_enter");

    msg = recv_msg(10, session_id, protocol.g2c_enter_scene);
    check(msg, "failed to  recv g2c_enter_scene");

    msg = recv_msg(10, session_id, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_char_appear");
end

function JumpToStartMap(user)
    
    local session_id = user:GetSessionID();
    local role = user:GetPlayingRole();
    check(role, "not role in Scene");

    if(role:GetSceneTempID() == 1) then
		return;
    end
    
    ret = user:GMCommand("Jump(1, 1, 1000, 1000)");
    check(ret, "exec GMCommand JumpTo error");

    msg = recv_msg(10, session_id, protocol.g2c_leave_scene);
    check(msg, "failed to  recv g2c_leave_scene");

    msg = recv_msg(10, session_id, protocol.g2c_changescene_enter);
    check(msg, "failed to  recv g2c_changescene_enter");

    msg = recv_msg(10, session_id, protocol.g2c_enter_scene);
    check(msg, "failed to  recv g2c_enter_scene");

    msg = recv_msg(10, session_id, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_char_appear");
end

function JumpToNextSceneTelport(user, nSceneTempID, nTelport)

    local session_id = user:GetSessionID();
    local role = user:GetPlayingRole();
    check(role, "not role in Scene");

    local oSceneFileMg = CSceneFileMgr:GetInstance();
    check(oSceneFileMg, "can't get static ScenefileMgr");

    local oStaticData = oSceneFileMg:GetStaticData(nSceneTempID);
    check(oStaticData, "static Data is error");

    local oTeleport = oStaticData:FindTeleportPoint(nTelport);    
    check(oTeleport, "oTeleport is not exist. sceneID:"..nSceneTempID.." teleport:"..nTelport);

    local cmd = "Jump("..nSceneTempID..", 0, "..oTeleport.SrcSceneX/POINT_PER_CM..","..oTeleport.SrcSceneY/POINT_PER_CM..","..oTeleport.SrcSceneZ/POINT_PER_CM..")";
    print(cmd);
    ret = user:GMCommand(cmd);
    check(ret, "exec GMCommand JumpTo error");

    msg = recv_msg(20, session_id, protocol.g2c_leave_scene);
    check(msg, "failed to  recv g2c_leave_scene");

    msg = recv_msg(10, session_id, protocol.g2c_changescene_enter);
    check(msg, "failed to  recv g2c_changescene_enter");

    msg = recv_msg(10, session_id, protocol.g2c_enter_scene);
    check(msg, "failed to  recv g2c_enter_scene");

    msg = recv_msg(10, session_id, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_char_appear");
end

function JumpToSceneBySceneTempID(user, nSceneTempID, nSceneID)
    local session_id = user:GetSessionID();
    local role = user:GetPlayingRole();
    check(role, "not role in Scene");

    local oSceneFileMg = CSceneFileMgr:GetInstance();
    check(oSceneFileMg, "can't get static ScenefileMgr");

    local oStaticData = oSceneFileMg:GetStaticData(nSceneTempID);
    check(oStaticData, "static Data is error");

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
		oTeleport = oStaticData:FindTeleportPoint(i);
		if(oTeleport ~= nil) then
			break;
		end
		i = i + 1;
    end

    check(oTeleport, "the scene()"..nSceneTempID.."is not have right pos");

    local cmd = "Jump("..nSceneTempID..","..nSceneID..","..oTeleport.SrcSceneX/POINT_PER_CM..","..
        oTeleport.SrcSceneY/POINT_PER_CM..","..oTeleport.SrcSceneZ/POINT_PER_CM..")";
    print(cmd);
    ret = user:GMCommand(cmd);
    check(ret, "exec GMCommand JumpTo error");

    msg = recv_msg(20, session_id, protocol.g2c_leave_scene);
    check(msg, "failed to  recv g2c_leave_scene");

    if(oTeleport.SrcSceneID ~= oTeleport.TargetSceneID) then
		msg = recv_msg(10, session_id, protocol.g2c_changescene_enter);
		check(msg, "failed to  recv g2c_changescene_enter");
    end

    msg = recv_msg(30, session_id, protocol.g2c_enter_scene);
    check(msg, "failed to  recv g2c_enter_scene");

    msg = recv_msg(10, session_id, protocol.g2c_char_appear);
    check(msg, "failed to  recv g2c_char_appear");
end

function TestCase.Move.DestMove()
    local ret, msg;
    local user_name = "DestMove"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    local session_id = user:GetSessionID();
    local pos_table = {
		{x = 512 * POINT_PER_CM, y = 0 * POINT_PER_CM},
		{x = 0 * POINT_PER_CM, y = 512 * POINT_PER_CM},
		{x = -512 * POINT_PER_CM, y = -512 * POINT_PER_CM},
		{x = 512 * POINT_PER_CM, y = 512 * POINT_PER_CM},
    };

	for i, p in ipairs(pos_table) do
		local destx = role:GetX() + p.x;
		local desty = role:GetY() + p.y;
		print('x='..math.floor(role:GetX()/POINT_PER_CM)..' y='..math.floor(role:GetY()/POINT_PER_CM)..
			' dx='..math.floor(destx/POINT_PER_CM)..' dy='..math.floor(desty/POINT_PER_CM));
		user:MoveTo(destx, desty);
		msg = recv_msg(30, session_id, protocol.g2c_char_move);
		check(msg and msg.nDestX == destx and msg.nDestY == desty, "failed to recv g2c_char_move");
		wait(2);
		print('x='..math.floor(role:GetX()/POINT_PER_CM)..' y='..math.floor(role:GetY()/POINT_PER_CM));
		check(role:GetX() == destx and role:GetY() == desty, "failed to move to destination")
	end

    cleanup(user);
end