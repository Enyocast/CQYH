

function TestCase.Trade()
    local user_name1 = "tr1_" .. os.date("%Y%H%M%S");
    local user_name2 = "tr2_" .. os.date("%Y%H%M%S");
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;

    --Log in
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

    --user1: add money using a GM command for the trade
    ret = user1:GMCommand("AddMoney(2, 10000, MONEYLOG_GM_COMMAND)");
    check(ret, "failed to send gm command");

    msg = recv_msg(5, session_id1, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_money_change");
    check(msg.nMoney == 10000, "failed to get correct money");

    --user2: add an item using a GM command for the trade
    ret = user2:GMCommand("AddItem(101, 1)");
    check(msg, "failed to send gm command");

    msg = recv_msg(5, session_id2, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --user1: request trade
    ret = user1:AskTrade(role2:GetObjID());
    check(ret, "failed to ask trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: reject the trade
    ret = user2:CancelTrade();
    check(ret, "failed to cancel trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: request trade
    ret = user1:AskTrade(role2:GetObjID());
    check(ret, "failed to ask trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: accept trade
    ret = user2:AcceptTrade(role1:GetObjID());
    check(ret, "failed to cancel trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: offer 1,000
    ret = user1:SetTradeMoney(1000);
    check(ret, "failed to set trade money");

    --user2: receive user1 money offer notification
    msg = recv_msg(5, session_id2, protocol.g2c_trade_set_money);
    check(msg, "failed to recv g2c_trade_set_money");

    wait(2);

    --user2: offer an item
    ret = user2:SetTradeItem(0, 1, 2, 0);
    check(ret, "failed to set trade item");

    --user1: receive user2 item offer notification
    msg = recv_msg(5, session_id1, protocol.g2c_trade_set_item);
    check(msg, "failed to recv g2c_trade_set_item");

    wait(2);

    --user1: lock
    ret = user1:LockTrade();
    check(ret, "failed to lock trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: lock
    ret = user2:LockTrade();
    check(ret, "failed to lock trade");

    --user1: receive trade state change
    msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user1: confirm
    ret = user1:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user2: receive trade state change
    msg = recv_msg(5, session_id2, protocol.g2c_trade_state_change);
    check(msg, "failed to recv g2c_trade_state_change");

    wait(2);

    --user2: confirm
    ret = user2:ConfirmTrade();
    check(ret, "failed to lock trade");

    --user1: receive trade state change
    --msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
    --check(msg, "failed to recv g2c_trade_state_change");

    --user1: receive money
    --msg = recv_msg(5, session_id1, protocol.g2c_money_change);
    --check(msg, "failed to recv g2c_money_change");
    --check(msg.nMoney == 9950, "failed to recv correct money (user1)");

    --user1: receive the item
    msg = recv_msg(5, session_id1, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --user2: receive money
    msg = recv_msg(5, session_id2, protocol.g2c_money_change);
    check(msg, "failed to recv g2c_money_change");
    check(msg.nMoney == 1000, "failed to recv correct money (user2)");

    wait(2);

    --Log out
    cleanup(user1);
    cleanup(user2);
end
