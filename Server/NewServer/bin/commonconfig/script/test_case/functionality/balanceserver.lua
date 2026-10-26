local gtnum = 2;
local usernum = 10;

------------------------------------------------------------------------------------------------------
--case测试负载平衡服务器的调度算法
--依照已配gt server的数量，将session平均分配到gt上
--默认情况下是开2个gt测，如果要测多个gt的话需要修改gtnum
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
	
	
	--测试完成，登出
	for i = 1,usernum do
	   cleanup(user[i]);
    end
    
end
