
g_cls = nil;
function OATestlogin_EnterScene(username, cls, nameBeginIndx)
	if( cls ) then
		g_cls = cls;
	end
	
	local rolename = username.."_"..g_cls; --.."_"..os.date("%H%M%S");
	--print("OATestlogin_EnterScene "..rolename);
	
	local flag, user, role = performance_startup(username, rolename, GROUP_ID, g_cls);
	
	if flag == true then
		local oScene = role:GetScene();
		check(oScene, "can't enter the scene")
		
		wait(4+math.random(8));
		performance_cleanup(user);
	else
		print("start up error user:"..username.." roleName:"..rolename);
		if user ~= nil then
			performance_cleanup(user);
		end
	end
	
	--wait(20);
	--performanc_func_End(username);
end

function OATestlogin_NoEnterScene(username, cls)
	
	local user = create_user(username, "pt", "1", GROUP_ID);
		    
	ret = user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, true);
	if ret then
		msg = recv_msg(30, user:GetSessionID(), protocol.t2c_sync_role_list);
		if(msg == nil) then
			print("can't login success:"..username);
		end
	end
			
	wait(10);
	performance_cleanup(user);
	
	wait(20);
	performanc_func_End(username);
end

function PerfTestCase.loginEnterScene()
	addco("PerfTest_Login", Performanc_Start, 10, 'OALogin_Enter', 1000, OATestlogin_EnterScene, clsWarrior, 9000);
end

function PerfTestCase.loginNoEnterScene()
	addco("PerfTest_Login", Performanc_Start, 2, 'OALogin_NoEnter', 150, OATestlogin_NoEnterScene, clsWarrior);
end



