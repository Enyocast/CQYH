function TestCase.PkValue()
	local ret, msg;
    local user_name1 = "pk1"..os.date("%Y%H%M%S");
    local user_name2 = "pk2"..os.date("%Y%H%M%S");

    local user1, role1 = startup(user_name1, user_name1);
	local session_id1 = user:GetSessionID();

    local user2, role2 = startup(user_name2, user_name2);
	local session_id2 = user:GetSessionID();
	
	user1:GMCommand('SetHp(1)');
	
	user2:GMCommand('');

    cleanup(user);
end
