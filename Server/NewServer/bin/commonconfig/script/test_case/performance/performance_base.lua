
g_runflag = true;
g_runing = false;
g_userlist = {};
g_loginCount = 0;
g_loginfailCount = 0;

g_nRound = 0;  
g_func = nil; -- for on_role_delete eg. used to relogin to make up role number 

function performance_createrole(user, role_name, cls)
    local ret;
    local msg;
    local user_name = user:GetUserName();
    
    local nSex = 2;
    
	if cls ~= 0 and cls ~= 1 and cls ~= 4 then
		print("user "..user_name.." get wrong class "..cls);
		return 0;
	end
    if cls == 0 then
		nSex = 1;
	end

	print("user "..user_name.." try to create role "..role_name );
    user:CreateRole(role_name, nSex, 1, 1, 1, cls);

    msg = recv_msg(60, user:GetSessionID(), protocol.t2c_create_role_ack);
    if msg == nil then
		print("user failed to recv t2c_create_role_ack "..user_name);
		return 0;
    end

    local role_id = msg.RoleData.dwRoleID;
    print("user "..user_name.." created role ".. role_name .. " role id: " .. role_id);

    return role_id;
end

function performance_startup(user_name, role_name, group_id, cls)
    local ret;
    local msg = nil;
    local role_id = 0;
    
	local new_user = create_user(user_name, "pt", "1", group_id);
	if(new_user == nil) then
		print("new User failed"..user_name);
		return false;
	end
			
	ret = new_user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, true);
	if(ret == 0) then
		print("new User ConnectServer failed:"..user_name);
		return false;
	else	
		print("User "..user_name.." start to connect server");
	end

	msg = recv_msg(60, new_user:GetSessionID(), protocol.t2c_sync_role_list);
	if(msg == nil) then
		print("new User Receive t2c_sync_role_list failed:"..user_name);
		return false, new_user;
	else
		print("User "..user_name.." rolelist num="..msg.byCount);
		for i = 0, (msg.byCount - 1) do
            role_id = msg.RoleData[i].dwRoleID;
			print("User "..user_name.." rolelist["..i.."].id="..msg.RoleData[i].dwRoleID..";name="..msg.RoleData[i].szRoleName);
		end
	end

    for i = 0, (msg.byCount - 1) do
        if msg.RoleData[i].szRoleName == role_name then
            role_id = msg.RoleData[i].dwRoleID;
            print("get role "..role_name..", id="..role_id..", no need create");
            break;
        end
    end

    if role_id == 0 then
        role_id = performance_createrole(new_user, role_name, cls);
        if role_id == 0 then
			print("new User "..user_name.." create role failed rolename:"..role_name);
			return false;
        end
    end
    
    ret = new_user:SelectRole(role_id);
    if ret == 0 then
		print("new User select role failed"..user_name.." role_id:"..role_id);
		return false;
    end

    msg = recv_msg(30, new_user:GetSessionID(), protocol.t2c_select_role_ack);
    if msg == nil then
		print("new User Recive t2c_select_role_ack failed "..user_name.." role_id:"..role_id);
		return false;
    end

	msg = recv_msg(60, new_user:GetSessionID(), protocol.g2c_char_appear)
	if msg == nil then
		print("new User Recive g2c_char_appear failed"..user_name.." role_id:"..role_id);
		return false;
    end

	local role = new_user:GetPlayingRole();
	if role == nil then
		print("new User Get PlayingRole failed"..user_name.." role_id:"..role_id);
		return false;
	end

    return true, new_user, role;
end

function performance_cleanup(user)
    local user_name = user:GetUserName();
    local session_id = user:GetSessionID();

    if (user:IsConnected()) then
        
        user:Logout();
        msg = recv_msg(10, session_id, protocol.t2c_robot_disconnected);
        if(msg == nil) then
        	print("user failed to receive t2c_robot_disconnected "..user_name);
		end
    end

    destory_user(user);
end

function Performanc_Start(nTotalRound, name, nUserCount, func, cls, nameBeginIndex)
    
    g_userlist = {};
    g_runflag = true;
    g_runing = false;
    g_nRound = 0;
    g_func = func; -- nil; --func;	// for relogin 

--    while g_runflag do
    	while g_runing do
			wait(32);
		end

		g_runing = true;
		local nameIndex = nameBeginIndex;
		if( nameIndex == nil ) then
			nameIndex = 2;
		end
		addco(name, add_robot_user, nTotalRound, nameIndex, nUserCount, func, cls);
--    end
end

function add_robot_user(nRound, startIndex, nUserCount, func, cls)
    
    g_nRound = g_nRound + 1;
    if(g_nRound > nRound) then
		g_runflag = false;
		return;
    end
         
    print("start Round:"..g_nRound);

    if startIndex < 0 or startIndex > 10000 or nUserCount > 10000 then
        return;
    end
    
    -- username consider nRound to avoid repeat login in the same username
    --[[
    if( nRound > 9 or nRound < 1 ) then
		print("nRound="..nRound..", must within the range [1,9]");
		return;
    end	
    --]]
    
    local idx_begin = startIndex;
    local idx_end = startIndex + nUserCount - 1;
	
	local username_pref = "gmjy"..os.date("%H%M%S").."#";
    for idx = idx_begin, idx_end do		
		local username = username_pref;
		if idx < 10 then
			username = username.."000"..idx;
		elseif idx < 100 then
			username = username.."00"..idx;
		elseif idx < 1000 then
			username = username.."0"..idx;
		else
			username = username..idx;
		end
		
    	g_userlist[username] = 1;
    end
   
	for k,v in pairs(g_userlist) do		
		addco(k, func, k, cls);
	end

    return true;
end

function performanc_func_End(username)
	
	g_userlist[username] = nil;
	
	for k,v in pairs(g_userlist) do
		return;
	end
	
	g_runing = false;
end

function on_role_delete(user)	
	if( g_func ) then	
		local name = user:GetUserName();
		if( nil == name) then
			return 0;
		end
		
		print( "on_role_delete user "..name );
		
		addco("relogin_"..name, g_func, name);
	end	  
			
	return 1;
end

---------------------------------------------------------------------------
g_scene = {};

function add_jump_point(scene_id, x, y, z)
    local scene_data = CDataManager_SCENE_DATA_:GetInstance():GetData(scene_id)
    if scene_data == nil then
		print("can't find scene_data "..scene_id);
        return
    end
	    
    local pos = get_near_pos(scene_id, x, y, z, 16, 1);
	if pos == nil then
		print("cannot find near pos for ["..x..","..y..","..z.."]@"..scene_id);
		return;
	end
    if #pos > 0 then
        local scene_pos = {};
        scene_pos.sceneTempID = scene_id;
        scene_pos.X = pos[1].x / POINT_PER_CM;
        scene_pos.Y = pos[1].y / POINT_PER_CM;
        scene_pos.Z = pos[1].z / POINT_PER_CM;
				
		local sx, sy, sz = ConvertCoordN2O(scene_pos.X,scene_pos.Y,scene_pos.Z);
        scene_pos.X = sx;
        scene_pos.Y = sy;
        scene_pos.Z = sz;
		
        if not g_scene[scene_id] then
			g_scene[scene_id] = {};
		end
		table.insert(g_scene[scene_id], scene_pos);
    end
end

local SCENE_SCAN_CHUNK_WIDTH = 50;
function performance_init()		 --copy from newai\robot\main.lua
	for i = 50, 256 do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(i);
		if sceneData ~= nil then
			local oStaticData = CSceneFileMgr:GetInstance():GetStaticData(i);
			if oStaticData ~= nil then
				local oTeleport;
				for j = 1, 31 do
					oTeleport = oStaticData:FindTeleportPoint(j);
				    if oTeleport ~= nil then
				        add_jump_point(oTeleport.SrcSceneID, oTeleport.SrcSceneX, oTeleport.SrcSceneY, oTeleport.SrcSceneZ);
				        add_jump_point(oTeleport.TargetSceneID, oTeleport.TargetSceneX, oTeleport.TargetSceneY, oTeleport.TargetSceneZ);
					end
				end
				
				for x = 100 * POINT_PER_METER, oStaticData:GetMaxZoneX() * ZONE_WIDTH, SCENE_SCAN_CHUNK_WIDTH * POINT_PER_METER do
				    for y = 100 * POINT_PER_METER, oStaticData:GetMaxZoneY() * ZONE_WIDTH, SCENE_SCAN_CHUNK_WIDTH * POINT_PER_METER do
				        add_jump_point(i, x, y, 100000 * POINT_PER_CM);
				    end
				end
			end
		end	
	end

	for k,v in pairs(g_scene) do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(k);
		if sceneData.nType == estDungeon then
			print("dungeon scene "..k.." pos "..#v);
		end
	end

	for k,v in pairs(g_scene) do
		local sceneData = CDataManager_SCENE_DATA_:GetInstance():GetData(k);
		if sceneData.nType ~= estDungeon then
			print("no-estDungeon scene "..k.." pos "..#v);
		end
	end
	
    return true;
end
performance_init();

function random_pos(nSceneTempID)

	if g_scene[nSceneTempID] then
		local randIndex = math.random(1, #g_scene[nSceneTempID]);
		local pos = g_scene[nSceneTempID][randIndex];
		
		local X = pos.X - SCENE_SCAN_CHUNK_WIDTH/2 + math.random(SCENE_SCAN_CHUNK_WIDTH); 
		local Y = pos.Y - SCENE_SCAN_CHUNK_WIDTH/2 + math.random(SCENE_SCAN_CHUNK_WIDTH); 
		local Z = pos.Z - SCENE_SCAN_CHUNK_WIDTH/2 + math.random(SCENE_SCAN_CHUNK_WIDTH);
	
		--print("random_pos ["..X..","..Y..","..Z.."]@"..nSceneTempID);
		return { X, Y, Z};
	end
	
	return nil;
end

-------------------------------------------------------------------------------------------------------