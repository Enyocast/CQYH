function TestCase.Reputation()
	local ret, msg;
    local user_name = "repu"..os.date("%Y%H%M%S");

    local user, role = startup(user_name, user_name);
	local session_id = user:GetSessionID();

    ret = user:GMCommand('SetReputation(1, 100)');
    check(ret, 'failed to set reputation');
    
    msg = recv_msg(30, session_id, protocol.g2c_modify_reputation);
    check(msg, 'failed to recv g2c_modify_reputation');
    check(msg.byForceID == 1, 'error repuation force id');
    check(msg.shReputation == 100, 'error reputation value');

    ret = user:GMCommand('SetReputation(1, 100000)');
    check(ret, 'failed to set reputation');
    
    msg = recv_msg(30, session_id, protocol.g2c_modify_reputation);
    check(msg, 'failed to recv g2c_modify_reputation');
    check(msg.byForceID == 1, 'error repuation force id');
    check(msg.shReputation == 100000, 'error reputation value');
    
    ret = user:GMCommand('SetReputation(1, MIN_REPUTATION)');
    check(ret, 'failed to set reputation');
    
    msg = recv_msg(30, session_id, protocol.g2c_modify_reputation);
    check(msg, 'failed to recv g2c_modify_reputation');
    check(msg.byForceID == 1, 'error repuation force id');
    check(msg.shReputation == MIN_REPUTATION, 'error reputation value');

    ret = user:GMCommand('SetReputation(1, MIN_REPUTATION - 1)');
    check(ret, 'failed to set reputation');
    
    msg = recv_msg(30, session_id, protocol.g2c_modify_reputation);
    check(msg, 'failed to recv g2c_modify_reputation');
    check(msg.byForceID == 1, 'error repuation force id');
    check(msg.shReputation == MIN_REPUTATION, 'error reputation value');

    cleanup(user);
end
