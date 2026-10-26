function Create_Role_Func(name_prefix)
	for i=1, 50000 do 
		local username = name_prefix..'#'..i;
		local roleClass = math.random(0, 3);
		local flag, user, role = performance_startup(username, username, 1, roleClass);

   	    user:GMCommand("InitRobot(true)");
		
		performance_cleanup(user);

		wait(1);
	end
end

function PerfTestCase.CreateRole()
	for i=1,200 do
		local username = "cq"..os.date("%H%M%S").."#"..i;
		addco(username, Create_Role_Func, username);
	end
end

