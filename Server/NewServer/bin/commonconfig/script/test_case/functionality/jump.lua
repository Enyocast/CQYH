LoadPackage("gameworld.pkg");

TestCase.Jump = {};

function TestCase.Jump.ToStartMap()

    local msg;
    local user_name = "JmpByServer"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    local session_id = user:GetSessionID();
    
    JumpToStartMap(user);

    cleanup(user);
end;

function TestCase.Jump.Teleport()

    local msg;
    local user_name = "Jump"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    local session_id = user:GetSessionID();
    
    JumpToStartMap(user);

    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
		local oTeleport = oStaticData:FindTeleportPoint(i);
		if(oTeleport ~= nil) then
			JumpToTelportInScene(user, i);
			wait(1);
		end

		i = i + 1;
    end
    
    cleanup(user);
end;

function TestCase.Jump.TestJumpScene()

    local msg;
    local user_name = "JumpScene"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    
    JumpToStartMap(user);

    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    local JumpResult = {};

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
        oTeleport = oStaticData:FindTeleportPoint(i);
        if(oTeleport ~= nil) then
            break;
        end
        i = i + 1;
    end

    while(oTeleport ~= nil and JumpResult[oScene:GetSceneTempID()]==nil) do
        JumpResult[oScene:GetSceneTempID()] = 1;
        JumpToByTeleport(user, i);

        role = user:GetPlayingRole();
        check(role, "can't get playing role");

        oScene = role:GetScene();
        check(oScene, "can't get Scene");

        oStaticData = oScene:GetStaticData();
        check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

        i = 1;
        while(i < MAX_TELEPORT_POINT_PER_SCENE) do
            oTeleport = oStaticData:FindTeleportPoint(i);
            if(oTeleport ~= nil) then
                break;
            end
            i = i + 1;
        end
	end
    
    cleanup(user);
end;

function TestCase.Jump.TestJumpLoop()
    
    local msg;
    local user_name = "JumpLoop"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();

    JumpToStartMap(user);

    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local nSceneTempID = oScene:GetSceneTempID();
    local JumpResult = {};
    JumpResult[nSceneTempID] = {};

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
        oTeleport = oStaticData:FindTeleportPoint(i);
        if(oTeleport ~= nil) then
            JumpResult[nSceneTempID][i] = 0;
        end
        i = i + 1;
    end

    while(1) do
        local index = 1;
        while(index < MAX_TELEPORT_POINT_PER_SCENE) do
            if(JumpResult[nSceneTempID][index] ~= nil and JumpResult[nSceneTempID][index] == 0) then
                JumpResult[nSceneTempID][index] = 1;
                break;
            end
            index = index + 1;
        end

        oTeleport = oStaticData:FindTeleportPoint(index);
	    if(oTeleport == nil) then
	        local value;
	        for k, v in pairs(JumpResult) do
		        local value1;
		        for k1, v1 in pairs(v) do
			        if(v1 == 0) then
			            JumpToNextSceneTelport(user, k, k1);
			            value1 = k1;
			            value = k;
			            print("[nSceneTempID, nTelport]"..k..","..k1);
			            break;
			        end
		        end

		        if(value1 ~= nil) then
			        break;
    		    end
	        end

	        if(value == nil) then
		        break;
	        end
        else
		    JumpToByTeleport(user, index);
    	end
	 	 
        role = user:GetPlayingRole();
        check(role, "can't get playing role");

        oScene = role:GetScene();
        check(oScene, "can't get Scene");

        oStaticData = oScene:GetStaticData();
        check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

        nSceneTempID = oScene:GetSceneTempID();
        if(JumpResult[nSceneTempID] == nil) then
		    JumpResult[nSceneTempID] = {};
    	       
		    i = 1;
		    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
			    oTeleport = oStaticData:FindTeleportPoint(i);
			    if(oTeleport ~= nil) then
			        JumpResult[nSceneTempID][i] = 0;
			    end
		        i = i + 1;
		    end
	    end 
    end
    
    for k, v in pairs(JumpResult) do
	    for k1, v1 in pairs(v) do
		    if v1 == 1 then
		        print("success jump test (sceneTempID,nTeleport]".."("..k..","..k1..")");
		    elseif v1 == 0 then
		        print("errors, can't jump test (sceneTempID,nTeleport]".."("..k..","..k1..")");	
		    end
	    end
    end

    cleanup(user);
end;

function TestCase.Jump.TestJumpDungeonExit()

    local msg;
    local user_name = "JpDn"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    local session_id = user:GetSessionID();
    
    JumpToStartMap(user);

    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    local oScene = role:GetScene();
    check(oScene, "can't get Scene");

    local oStaticData = oScene:GetStaticData();
    check(oStaticData, "static Data is error"..oScene:GetSceneTempID());

    local i = 1;
    local oTeleport;
    while(i < MAX_TELEPORT_POINT_PER_SCENE) do
	 oTeleport = oStaticData:FindTeleportPoint(i);
	 if(oTeleport ~= nil) then
	    local nSceneType = get_scene_type(oTeleport.TargetSceneID);
	    if (nSceneType == estDungeon and oTeleport.SrcSceneID ~= oTeleport.TargetSceneID) then
			break;
	    end
	 end
	 i = i + 1;
    end

    if oTeleport == nil then
	print("the map haven't teleport to the Dungeon");
	return;
    end
    
    local nSrcTempID = oTeleport.SrcSceneID;
    local nSceneTempID = oTeleport.TargetSceneID;
    JumpToByTeleport(user, i);
    
    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    oScene = role:GetScene();
    check(oScene, "can't get right scene");

    local nCurSceneID = oScene:GetSceneID();
    check(oScene, "can't get Scene");
    check(oScene:GetSceneTempID() == nSceneTempID, "can't jump to the right Dungeon");
 
    wait(2);
    cleanup(user);
    wait(5);

    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    oScene = role:GetScene();
    check(oScene, "can't get Scene");
    check(oScene:GetSceneTempID() == nSceneTempID, "exit Dungeon, can't enter right static scene");

    JumpToStartMap(user);
	wait(5);

	JumpToByTeleport(user, i);
    
    role = user:GetPlayingRole();
    check(role, "can't get playing role");

    oScene = role:GetScene();
    check(oScene, "can't get right scene");
    
    check(oScene:GetSceneTempID() == nSceneTempID, "can't jump to the right Dungeon");
    check(oScene:GetSceneID() ~= nCurSceneID, "can't jump to the right Dungeon");
	cleanup(user);

	wait(60);

	user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    oScene = role:GetScene();
    check(oScene, "can't get Scene");
    check(oScene:GetSceneTempID() ~= nSceneTempID, "exit Dungeon, can't enter right static scene");

	wait(2);
    cleanup(user);
end;
