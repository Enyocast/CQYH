
g_runflag = true;
g_runing = false;
g_user = {};
g_count = 0;
g_loginfail = 0;


g_lst_CursceneID = {};
g_lst_SceneCount = {};
g_startCount = 0;

function add_asimovUser(count, offset, cnt, testFunc, cls, nSceneTempID, nRoleCountPerScene)
    
    g_count = g_count + 1;
    if(g_count > count) then
		g_runflag = false;
		return;
    end

    if offset < 0 or offset > 20000 or cnt > 20000 then
        return false;
    end

	local testName = "gmjy";
	
    local idx_begin = offset;
    local idx_end = offset + cnt - 1;
    for idx = idx_begin, idx_end do
		local uname = testName;
		if idx < 10 then
			uname = uname.."000"..idx;
		elseif idx < 100 then
			uname = uname.."00"..idx;
		elseif idx < 1000 then
			uname = uname.."0"..idx;
		else
			uname = uname..idx;
		end
		
    	g_user[uname] = 1;
    end
   
	local nTargetSceneType = get_scene_type(nSceneTempID);
	local nCurSceneID = 1;
	
	if nTargetSceneType == estStatic or nRoleCountPerScene == nil then
		for k,v in pairs(g_user) do
			addco(k, testFunc, k, cls, nSceneTempID, 1);
		end
	elseif nTargetSceneType == estDungeon then
		local nRoleCount = 0;
		
		local nGroupCount = math.floor((cnt - 1)/nRoleCountPerScene) + 1;
		local nIndex = 1;
		
		while nIndex <= nGroupCount do
			g_lst_CursceneID[nIndex] = 0;
			g_lst_SceneCount[nIndex] = 0;
			nIndex = nIndex + 1;
		end
				
		for k,v in pairs(g_user) do
			nRoleCount = nRoleCount + 1;
			
			local nGroupIndex = (nRoleCount % nGroupCount) + 1;
			
			while (g_lst_CursceneID[nGroupIndex] == 0 and (nRoleCount > nGroupCount)) do
				wait(2);
			end
			
			addco(k, testFunc, k, cls, nSceneTempID, g_lst_CursceneID[nGroupIndex], nGroupIndex, nRoleCountPerScene);
			g_startCount = g_startCount + 1;
			
			while g_startCount > 256 do
				wait(5);
			end
			
		end
    end

    return true;
end


function Performanc(nTotalRound, name, nUserCount, func, cls, nSceneTempID, nRoleCountPerScene)
    
    g_user = {};
    g_runflag = true;
    g_runing = false;
    g_count = 0;

    while g_runflag do
    	while g_runing do
			wait(32);
		end

		g_runing = true;
		addco(name, add_asimovUser, nTotalRound, 2, nUserCount, func, cls, nSceneTempID, nRoleCountPerScene);
    end
end



function testlogin(username,...)
	
	local user = create_user(username, "pt", "1", GROUP_ID);
		    
	ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, true);
	check(ret, "failed to connected to server");

	msg = recv_msg(30, user:GetSessionID(), protocol.t2c_sync_role_list);
	if(msg == nil) then
		print("can't login success:"..username);
		g_loginfail = g_loginfail + 1;
	else
		wait(2);
	end
	
	cleanup(user);
	g_user[username] = nil;

	for k,v in pairs(g_user) do
		return;
	end
	
	g_runing = false;
end

function testGameLogic(username, cls, nSceneTempID, nSceneID, nGroupIndex, nRoleCountPerScene)

    local ret;
    local msg;
    local role_id = 0;
    
    local user, role = startup(username, username, nil, cls);
    check(user, "failed to get user");
	check(role, "failed to get role");

	local oScene = role:GetScene();
	if oScene:GetSceneTempID() ~= nSceneTempID or oScene:GetSceneID() ~= nSceneID then
		JumpToSceneBySceneTempID(user, nSceneTempID, nSceneID);
	end
	
	g_startCount = g_startCount - 1;
	if g_lst_CursceneID[nGroupIndex] == 0 then
		oScene = role:GetScene();
		g_lst_CursceneID[nGroupIndex] = oScene:GetSceneID();
	end
	
	if nGroupIndex ~= nil then
		g_lst_SceneCount[nGroupIndex] = g_lst_SceneCount[nGroupIndex] + 1;
		if nRoleCountPerScene ~= nil then
			while g_lst_SceneCount[nGroupIndex] < nRoleCountPerScene do
				wait(5);
			end
		end
	end
	
    ai = role:SetAIProcessor(99)
    if not ai then
        print("Create AI fail for " .. username .. ".")
		return
    end
   
    wait(72000);

    cleanup(user);
    g_user[username] = nil;

    for k,v in pairs(g_user) do
		return;
    end

    g_runing = false;
end

function testDBLoad(username, cls, nSceneTempID, nSceneID, nGroupIndex,...)

    local ret;
    local msg;
    local role_id = 0;
    
    local user, role = startup(username, username, nil, cls);
    check(user, "failed to get user");
	check(role, "failed to get role");

	local oScene = role:GetScene();
	if oScene:GetSceneTempID() ~= nSceneTempID or oScene:GetSceneID() ~= nSceneID then
		JumpToSceneBySceneTempID(user, nSceneTempID, nSceneID);
	end
	
	g_startCount = g_startCount - 1;
	if g_lst_CursceneID[nGroupIndex] == 0 then
		oScene = role:GetScene();
		g_lst_CursceneID[nGroupIndex] = oScene:GetSceneID();
	end
	
    wait(16);

    cleanup(user);
    g_user[username] = nil;

    for k,v in pairs(g_user) do
		return;
    end

    g_runing = false;
end

function testDBOperate(username,...)
		
	local user = login(username);
    local session_id = user:GetSessionID();
    
    local role_name = {
        [1] = username.."_0", 
        [2] = username.."_1",
        [3] = username.."_2",
		[4] = username.."_3",
    };
    
    ret = user:CreateRole(role_name[1], 1, 1, 1, 1, 0);
	check(ret, "failed to create role");

	local msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
	check(msg, "failed to  recv t2c_create_role_ack");
    
    ret = user:CreateRole(role_name[1], 1, 1, 1, 1, 0);
    check(ret, "failed to create role");

    msg = recv_msg(30, session_id, protocol.t2c_error_notify);
    check(msg.nErrCode == error_code.errLoginCreateRoleDupeName, "failed to  recv errLoginCreateRoleDupeName");

    local i = 2;
    while i <= 4 do
        ret = user:CreateRole(role_name[i], 1, 1, 1, 1, i-1);
		check(ret, "failed to create role");

		msg = recv_msg(30, session_id, protocol.t2c_create_role_ack);
		check(msg, "failed to  recv t2c_create_role_ack");
		
		i = i + 1;
    end
        
    check(user:GetRoleCount() == 4, "error role count");
	
	i = 3;
	while i >= 0 do
		local role = user:GetRoleByIndex(i);
		check(role, "failed to find created role");

		local roleID = role:GetObjID();
		check(roleID, "failed to Get roleID");

	    ret = user:DeleteRole(roleID);
		check(ret, "failed to delete role");

		msg = recv_msg(30, session_id, protocol.t2c_delete_role_ack);
		check(msg, "failed to  recv t2c_delete_role_ack");

		i = i - 1;
	end
	
	wait(8);
	
	cleanup(user);
	g_user[username] = nil;

	for k,v in pairs(g_user) do
		return;
	end
	
	g_runing = false;
end

function Command_Login(nCount)
	addco("Command_Login", Performanc, nCount, 'serverLogin', 500, testlogin, clsWarrior, 100, 64);
end

function Command_GameLogic(nCount)
	addco("Command_GameLogic", Performanc, nCount, 'gameLogic1', 96, testGameLogic, clsWarrior, 102, 32);
end

function Command_DBLoad(nCount)
	addco("Performanc_DBLoad", Performanc, nCount, 'testDBLoad', 5000, testDBLoad, clsWarrior, 102, 64);
end 

function Command_DBOperate(nCount)
	addco("Performanc_DBOperate", Performanc, nCount, 'testDBOperate', 5000, testDBOperate, clsWarrior, 100, 120);
end 

g_ShutdownUserName = {};
function TestShutdownBegin()
    for i=1, 16 do
        g_ShutdownUserName[i] = "shut"..tostring(i).."_"..os.date("%H%M%S");

        local user, role = startup(g_ShutdownUserName[i], g_ShutdownUserName[i]);
        user:LearnSpell(8888, 1, false);
    end

end

function TestChat(nRoundCount, nTotalUserCount,nUserCountPerScene)
	addco("TestChat", _TestChat, nRoundCount, nTotalUserCount,nUserCountPerScene);
end

function _TestChat(nRoundCount, nTotalUserCount,nUserCountPerScene)

	TestString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
	g_bRunFlag = false;
	g_ChatUserList = {};
	g_nTotalUserCount = nTotalUserCount;

	local nRoundTime;	
	for nRoundTime = 1,nRoundCount do
		print("===============round"..nRoundTime.."========================");
		if g_bRunFlag == false then
			g_bRunFlag = true;
			addco('TestChat'..nRoundTime, _TestChatPerRound, nTotalUserCount, nUserCountPerScene, clsWarrior);
		end

		while g_bRunFlag do	
			wait(20);
		end	
	end
end

function _TestChatPerRound(nTotalUserCount,nUserCountPerScene, cls)
	local nStartSceneTempID = 100;
	local j;
	local user_name;
	local nCount = 0;	
	g_TestChatSceneID = 0;
		
	for j = 1 , nTotalUserCount do                  
		user_name = "robot"..tostring(j).."_"..os.date("%H%M%S");
		g_ChatUserList[j] = true;				
		if j <= nUserCountPerScene * 5 then
			addco('_TestChatPerRound'..j, _TestChatPerUser, j, user_name, nStartSceneTempID , 1, cls);	
			if j%nUserCountPerScene == 0  then
				nStartSceneTempID = nStartSceneTempID + 1;							
				if nStartSceneTempID == 102 then
					nStartSceneTempID = nStartSceneTempID + 1;
				end	
			end			
		else
			if nCount%nUserCountPerScene ~= 0 then		
				while g_TestChatSceneID == 0 do				
					wait(1);
				end
			else
				g_TestChatSceneID = 0;
			end
			
			addco('_TestChatPerRound'..j, _TestChatPerUser, j, user_name, 102 , g_TestChatSceneID, cls);						
			nCount = nCount + 1;			
		end
	end
end	
	
function _TestChatPerUser(index, username, nSceneTmpID, nSceneID, cls)

	local user, role = startup(username, username);	
	check(user, "failed to get user");   
	check(role, "failed to get role");	
	local oScene = role:GetScene();	

	if oScene:GetSceneTempID() ~= nSceneTmpID or oScene:GetSceneID() ~= nSceneID then
		JumpToSceneBySceneTempID(user, nSceneTmpID, nSceneID);
	end

	if(nSceneID == 0) then
		g_TestChatSceneID = oScene:GetSceneID();
	end

	local chattype = 0;
	local targetid = 0;	
	local nTime = 0;
	while(nTime < 6) do
		--chattype = math.random(3); -- 世界 场景 区域 
		--if chattype == 1 then
			targetid = MakeObjectID(otChannel,cctServer);
		--elseif chattype == 2 then
		--	targetid = MakeObjectID(otChannel,cctScene);
		--else	
		--	targetid = MakeObjectID(otChannel,cctScreen);
		--end
		role:Say(targetid, TestString);
		
		wait(20);
		nTime = nTime + 1;
	end	
	
	cleanup(user);
	g_ChatUserList[index] = nil;

	local i;
	for i=1,g_nTotalUserCount do
		if g_ChatUserList[i] ~= nil then
			return;
		end	
	end
	
	print("-----------once time-----------------");	
	g_bRunFlag = false;
end

function TestShutdownEnd()
    for i=1, 16 do
        addco('shut'..i, _TestShutdownEnd, i);
    end
end

function _TestShutdownEnd(i)
    local user, role = startup(g_ShutdownUserName[i], g_ShutdownUserName[i]);

    local oSpell = role:GetSpellBook():GetSpell(8888);
    check(oSpell, "failed to get learnt spell");
   
    cleanup(user);
end

function TestRobot(count)
    for i=1, count do
        addco('robot'..i, _TestRobot, i);
    end
end

function _TestRobot(i)
    local user_name = "robot"..tostring(i).."_"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);
    wait(4);
    
    cleanup(user);
end
