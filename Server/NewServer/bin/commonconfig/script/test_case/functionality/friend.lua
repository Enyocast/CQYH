LoadPackage("robot_message_handler.pkg")

TestCase.friend = {}

function TestCase.friend.Friend()
    local user_name1 = "F1_" .. os.date("%Y%H%M%S");
    local user_name2 = "F2_" .. os.date("%Y%H%M%S");
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;

    --登录
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

    --user1: 加user2为好友(以RoleID为根据)
    ret = user1:AddFriend(role2:GetObjID(), "");
    check(ret, "failed to add friend");

    --user1: 收到加好友回复
    msg = recv_msg(5, session_id1, protocol.m2c_friend_add);
    check(msg, "faield to recv m2c_friend_add");
    check(msg.dwRoleID == role2:GetObjID(), "failed to recv correct friend add msg");
    check(msg.szRoleName == user_name2, "failed to recv correct friend add msg");

    --user1: 删掉好友user2
    ret = user1:DelFriend(role2:GetObjID());
    check(ret, "failed to del friend");

    --user1: 收到删好友回复
    msg = recv_msg(5, session_id1, protocol.m2c_friend_del);
    check(msg, "faield to recv m2c_friend_del");
    check(msg.dwRoleID == role2:GetObjID(), "failed to recv correct friend del msg");

    --user1: 加user2为好友(以RoleName为根据)
    ret = user1:AddFriend(0, user_name2);
    check(ret, "failed to add friend");

    --user1: 收到加好友回复
    msg = recv_msg(5, session_id1, protocol.m2c_friend_add);
    check(msg, "faield to recv m2c_friend_add");
    check(msg.dwRoleID == role2:GetObjID(), "failed to recv correct friend add msg");
    check(msg.szRoleName == user_name2, "failed to recv correct friend add msg");

    --user2: 收到被加好友回复
    msg = recv_msg(5, session_id2, protocol.m2c_friend_added_by);
    check(msg, "faield to recv m2c_friend_added_by");
    check(msg.dwRoleID == role1:GetObjID(), "failed to recv correct friend add msg");
    check(msg.szRoleName == user_name1, "failed to recv correct friend add msg");

    --user1: 改变好友分组
    ret = user1:ChangeFriendGroup(role2:GetObjID(), 3);
    check(ret, "failed to change friend group");

    --user1: 删掉好友user2
    ret = user1:DelFriend(role2:GetObjID());
    check(ret, "failed to del friend");

    --登出
    cleanup(user1);
    cleanup(user2);
end

function TestCase.friend.FriendFull()
	for i=1,50 do
		local new_user = create_user("fr_"..i, "pt", "1", GROUP_ID);
		local ret = new_user:ConnectServer(SERVER_IP_ADDR, SERVER_PORT, true, true);
		check(ret, "failed to connect server");
		
		msg = recv_msg(60, new_user:GetSessionID(), protocol.t2c_sync_role_list);
		check(msg, "failed to  recv t2c_sync_role_list");
		
		for j = 1,4 do
			create_role(new_user, "fr_"..i.."_"..j, 0);
		end
		cleanup(new_user);
	end
	
	local user1;
	local role1;
	user1, role1 = startup("friend", "friend");
	check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    for i=1,50 do
		for j = 1,4 do
			user1:AddFriend(0, "fr_"..i.."_"..j);
		end
	end
end

function TestCase.friend.ShieldList()
    --local user_name1 = "fs1" .. os.date("%Y%H%M%S");
    --local user_name2 = "fs2" .. os.date("%Y%H%M%S");
	local user_name1 = "gaga";
	local user_name2 = "hehe";
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;

    --登录
    user1, role1 = startup(user_name1, user_name1,1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2,1);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

	g_RobotMessageHandler:DoShieldRole(role1, role2:GetObjID());
	msg = recv_msg(50, session_id1, protocol.g2c_shield_ack);
	check(msg, "failed to recv protocol.g2c_shield_ack");

	--登出
    cleanup(user1);
    cleanup(user2);


    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

	cleanup(user1);




end


function TestCase.friend.PersonalEnemy()
    local user_name1 = "pe1" .. os.date("%Y%H%M%S");
    local user_name2 = "pe2" .. os.date("%Y%H%M%S");
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;

    --登录
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

	ret = user1:GMCommand("AddPersonalEnemyByGM(" ..role2:GetObjID()..")");
	check(ret, "failed to send gm command");

	msg = recv_msg(50, session_id1, protocol.m2c_personal_enemy_add);
	check(msg, "failed to recv protocol.m2c_personal_enemy_add");

	--登出
    cleanup(user1);
    cleanup(user2);

	user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

	cleanup(user1);

end



