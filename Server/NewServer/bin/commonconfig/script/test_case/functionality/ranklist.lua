LoadPackage("gameworld.pkg");
LoadPackage("role.pkg");
LoadPackage("rank_list_def.pkg");

TestCase.Ranklist = {};

function TestCase.Ranklist.AddRanklist()

	-- 登陆	
	-- 用户1 2 5都登陆到ServerGroup1
    local user_name1 = "ranklist1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");
    
    local user_name2 = "ranklist2"..os.date("%H%M%S");
    local user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user");
    check(role2, "failed to create role"); 

    local user_name5 = "ranklist5"..os.date("%H%M%S");
    local user5, role5 = startup(user_name5, user_name5);
    check(user5, "failed to create user");
    check(role5, "failed to create role"); 

	-- 用户3 4 6都登陆到ServerGroup2（默认）
    local user_name3 = "ranklist3"..os.date("%H%M%S");
    local user3, role3 = startup(user_name3, user_name3);
    check(user3, "failed to create user");
    check(role3, "failed to create role"); 
	
    local user_name4 = "ranklist4"..os.date("%H%M%S");
    local user4, role4 = startup(user_name4, user_name4);
    check(user4, "failed to create user");
    check(role4, "failed to create role"); 

    local user_name6 = "ranklist6"..os.date("%H%M%S");
    local user6, role6 = startup(user_name6, user_name6);
    check(user6, "failed to create user");
    check(role6, "failed to create role"); 
    	
    local session_id1 = user1:GetSessionID();
    local session_id2 = user2:GetSessionID();
    local session_id3 = user3:GetSessionID(); 
    local session_id4 = user4:GetSessionID();           
    local session_id5 = user5:GetSessionID();           
    local session_id6 = user6:GetSessionID();           	
	
	local userid1 = role1:GetObjID();
	local userid2 = role2:GetObjID();
	local userid3 = role3:GetObjID();
	local userid4 = role4:GetObjID();		
	local userid5 = role5:GetObjID();
	local userid6 = role6:GetObjID();
	
    ---- 用户2 4都升到10级
    
   	local ret = user2:GMCommand("SetLevel(10)");
    check(ret, "exec GMCommand SetLevel error: user2");
	
	local ret = user4:GMCommand("SetLevel(10)");
	check(ret, "exec GMCommand SetLevel error: user4");

	wait(2);

	-- 用户2 4 下线，刷新身上的排行榜
    cleanup(user2);
    cleanup(user4);

	-- 用户5 6都升到20级
   	local ret = user5:GMCommand("SetLevel(20)");
    check(ret, "exec GMCommand SetLevel error: user5");
	
	local ret = user6:GMCommand("SetLevel(20)");
	check(ret, "exec GMCommand SetLevel error: user6");

	wait(2);

	-- 用户5 6 下线，刷新身上的排行榜
    cleanup(user5);
    cleanup(user6);

	wait(10);

    -- 用户1 3询问等级排行榜情况
    ret = user1:QueryRanklist(0, 0); -- rlLevel
    check(ret, "fail to query ranklist");    
    
    local msg = recv_msg(30, session_id1, protocol.m2c_query_ranklist);
    check(msg, "failed to  recv m2c_query_ranklist");
	check(msg.nServerGroupID == 1, "wrong ServerGroupID in m2c_query_ranklist");
	check(msg.nRanklistID == 0, "wrong nRanklistID in m2c_query_ranklist");    
    
    -- 按照预计结果 排行榜中应该是5 20级排第一， 2 10级排第二（用户1由于未下线，排行榜中无他的位置）
	check(msg.llKey[0] == userid5, "wrong llkey0 in m2c_query_ranklist");    
	check(msg.llValue[0] == 20, "wrong llvalue0 in m2c_query_ranklist");		
	
	check(msg.llKey[1] == userid2, "wrong llkey1 in m2c_query_ranklist");    
	check(msg.llValue[1] == 10, "wrong llvalue1 in m2c_query_ranklist");		
		
	local ranklistindex = 0;
	for	ranklistindex = 2,9 do
		check(msg.llKey[ranklistindex] == 0, "wrong llkey in m2c_query_ranklist");    
		check(msg.llValue[ranklistindex] == 0, "wrong llvalue in m2c_query_ranklist");			
	end
    
    ret = user3:QueryRanklist(0, 0);	-- rlLevel
    check(ret, "fail to query ranklist");    
    
    local msg = recv_msg(30, session_id3, protocol.m2c_query_ranklist);
    check(msg, "failed to  recv m2c_query_ranklist");    
	
    -- 按照预计结果 排行榜中应该是6 20级排第一 ， 4 10级排第2（用户3由于未下线，排行榜中无他的位置）
	check(msg.llKey[0] == userid6, "wrong llkey1 in m2c_query_ranklist");    
	check(msg.llValue[0] == 20, "wrong llvalue1 in m2c_query_ranklist");		
	
	check(msg.llKey[1] == userid4, "wrong llkey2 in m2c_query_ranklist");    
	check(msg.llValue[1] == 10, "wrong llvalue2 in m2c_query_ranklist");		

	ranklistindex = 0;
	for	ranklistindex = 2,9 do
		check(msg.llKey[ranklistindex] == 0, "wrong llkey in m2c_query_ranklist");    
		check(msg.llValue[ranklistindex] == 0, "wrong llvalue in m2c_query_ranklist");			
	end
end

function TestCase.Ranklist.TestRankList()
	-- 登陆
	
	local i, ret;
	
	-- 陆续登陆
	
	local user_name = {};
	local user = {};
	local role = {};	
	
	for i = 1,1000 do
		user_name[i] = "ranklist"..i..os.date("%H%M%S");
		print '---------------------'
		print (user_name[i]);
		user[i], role[i] = startup(user_name[i], user_name[i]);
		check(user[i], "failed to create user index :" ..i);
		check(role[i], "failed to create role index : "..i);
	end

	-- 纷纷升级
	
	for i = 1, 100 do
		ret = user[i]:GMCommand("SetLevel(10)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end	

	wait(1);

	for i = 101, 200 do
		ret = user[i]:GMCommand("SetLevel(15)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end

	wait(1);

	for i = 201, 300 do
		ret = user[i]:GMCommand("SetLevel(20)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end

	wait(1);

	for i = 301, 400 do
		ret = user[i]:GMCommand("SetLevel(25)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end

	wait(1);

	for i = 401, 500 do
		ret = user[i]:GMCommand("SetLevel(30)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end
	
	wait(1);

	for i = 501, 600 do
		ret = user[i]:GMCommand("SetLevel(35)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end

	wait(1);
	
	for i = 601, 700 do
		ret = user[i]:GMCommand("SetLevel(40)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end

	wait(1);

	for i = 701, 800 do
		ret = user[i]:GMCommand("SetLevel(45)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end
	
	wait(1);

	for i = 801, 900 do
		ret = user[i]:GMCommand("SetLevel(50)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end
	
	wait(1);
	
	for i = 901, 1000 do
		ret = user[i]:GMCommand("SetLevel(55)");
		check(ret, "exec GMCommand SetLevel user index : "..i);
	end
	
	wait(1);

	-- 纷纷下线, 刷新自己身上的排行榜
	
	for i = 1, 1000 do
		cleanup(user[i]);	
	end
	
	user1, role1 = startup(user_name[i], user_name[i]);
	check(user1, "failed to create user1");
	check(role1, "failed to create role1");

    local session_id1 = user1:GetSessionID();
		
	-- 1号用户查询排行榜信息

    ret = user1:QueryRanklist(0, 0); -- rlLevel
    check(ret, "fail to query ranklist");    
    
    local msg = recv_msg(30, session_id1, protocol.m2c_query_ranklist);
    check(msg, "failed to  recv m2c_query_ranklist");
	check(msg.nServerGroupID == 1, "wrong ServerGroupID in m2c_query_ranklist");
	check(msg.nRanklistID == 0, "wrong nRanklistID in m2c_query_ranklist");    
    
    -- 按照预计结果 排行榜中第0页全是55
    
    for ranklistindex = 0,9 do
	   	check(msg.llValue[ranklistindex] == 55, "wrong llvalue0 in m2c_query_ranklist");		 
    end
    	
	ret = user1:QueryRanklist(0, 99); -- rlLevel
    check(ret, "fail to query ranklist");    
    
    local msg = recv_msg(30, session_id1, protocol.m2c_query_ranklist);
    check(msg, "failed to  recv m2c_query_ranklist");
	check(msg.nServerGroupID == 1, "wrong ServerGroupID in m2c_query_ranklist");
	check(msg.nRanklistID == 0, "wrong nRanklistID in m2c_query_ranklist");    
	
    -- 按照预计结果 排行榜中第99页应该是1
	
    for ranklistindex = 0,9 do
	   	check(msg.llValue[ranklistindex] == 1, "wrong llvalue0 in m2c_query_ranklist");		 
    end
	
	-- 再上1个用户，升级到60级

	username = "ranklist"..os.date("%H%M%S");	
	user2, role2 = startup(user_name[i], user_name[i]);
	check(user1, "failed to create user1");
	check(role1, "failed to create role1");

	ret = user2:GMCommand("SetLevel(60)");
	check(ret, "exec GMCommand SetLevel user");
	
	-- 1号用户查询排行榜信息
			
	ret = user1:QueryRanklist(0, 0); -- rlLevel
    check(ret, "fail to query ranklist");    
    
    local msg = recv_msg(30, session_id1, protocol.m2c_query_ranklist);
    check(msg, "failed to  recv m2c_query_ranklist");
	check(msg.nServerGroupID == 1, "wrong ServerGroupID in m2c_query_ranklist");
	check(msg.nRanklistID == 0, "wrong nRanklistID in m2c_query_ranklist");    
		
	userid2 = role2:GetObjID();
	
	-- 按照预计结果 排名第1的应该是2号用户 60级，其他9个都是55级
	
	check(msg.llKey[0] == userid2, "wrong llkey1 in m2c_query_ranklist");   	
   	check(msg.llValue[0] == 60, "wrong llvalue0 in m2c_query_ranklist");		 
	
    for ranklistindex = 0,9 do
	   	check(msg.llValue[ranklistindex] == 55, "wrong llvalue0 in m2c_query_ranklist");		 
    end
	
	-- 1号用户升级到65 下线刷新排行榜
	
	ret = user1:GMCommand("SetLevel(65)");
	check(ret, "exec GMCommand SetLevel user");

    cleanup(user1);
	
	-- 用户2来查询排行榜，第一是user1 第二是user2
	check(msg.llKey[0] == userid1, "wrong llkey1 in m2c_query_ranklist");   	
   	check(msg.llValue[0] == 65, "wrong llvalue0 in m2c_query_ranklist");		 
	
	check(msg.llKey[1] == userid2, "wrong llkey1 in m2c_query_ranklist");   	
   	check(msg.llValue[1] == 60, "wrong llvalue0 in m2c_query_ranklist");		 

    for ranklistindex = 3,9 do
	   	check(msg.llValue[ranklistindex] == 55, "wrong llvalue0 in m2c_query_ranklist");		 
    end	
		
end