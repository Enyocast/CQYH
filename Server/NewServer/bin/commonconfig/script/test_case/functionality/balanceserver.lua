local gtnum = 2;
local usernum = 10;

------------------------------------------------------------------------------------------------------
--Test case for the load-balancing server scheduling algorithm
--Distribute sessions evenly across the configured GT servers
--By default, test with two GT servers; change gtnum to test more
------------------------------------------------------------------------------------------------------

function TestCase.BalanceServer()
	local username = {};
	local user = {};
	local role = {};
	
	local gt = {};
	
	for i = 1, gtnum do
		username[i] = "testbs"..i..os.date("%H%M%S");
		
		gt[i] = {};
		user[i], role[i], gt[i].ip, gt[i].port = startupfrombs(username[i], username[i]);
		
		check(user[i], "failed to create user");
		check(role[i], "failed to create role");
		wait(2);
	end	
	
	local index = 1;
	
	for i = gtnum + 1, usernum do
		username[i] = "testbs"..i..os.date("%H%M%S");
		
		gt[i] = {};
		user[i], role[i], gt[i].ip, gt[i].port = startupfrombs(username[i], username[i]);
		
		check(user[i], "failed to create user");
		check(role[i], "failed to create role");
	
		check(gt[i].ip == gt[index].ip, "failed to receive correct ip");
		check(gt[i].port == gt[index].port, "failed to receive correct port");
		wait(2);
		
		index = index + 1;
		if index > gtnum  then 
			index = index % gtnum;		
		end
	end
	
	
	--Test complete; log out
	for i = 1,usernum do
	   cleanup(user[i]);
    end
    
end
