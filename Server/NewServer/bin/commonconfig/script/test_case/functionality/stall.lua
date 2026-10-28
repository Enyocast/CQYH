

function TestCase.Stall()
    local user_name1 = "S1_" .. os.date("%Y%H%M%S");
    local user_name2 = "S2_" .. os.date("%Y%H%M%S");
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

    --user1: add potions using a GM command and check them
    ret = user1:GMCommand("AddItem(101,10, ITEMLOG_GM_COMMAND)");
    check(ret, "failed to send gm command");

    msg = recv_msg(5, session_id1, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.stItem.nTemplateID==101, "failed to create correct item");
    check(msg.stItem.nCurDur==10, "failed to create correct item");

    --user1: prepare the stall
    ret = user1:OpenStall();
    check(ret, "failed to send move item msg");

    --user2: receive a nearby stall state change notification
    msg = recv_msg(5, session_id2, protocol.g2c_stall_state_change);
    check(msg, "failed to recv g2c_stall_state_change");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct stall msg");
    check(msg.btStallState==essPreparing, "failed to recv correct stall msg");

    --user1: list five potions at 100 each
    ret = user1:AddStallItem(0, CONSLOT_DEFAULT, 0, 5, 100);
    check(ret, "failed to add stall item");

    --user1: receive the listing response
    msg = recv_msg(5, session_id1, protocol.g2c_add_stall_item);
    check(msg, "failed to recv g2c_add_stall_item");
    check(msg.btStallSlot==0, "failed to recv correct add stall item msg");
    check(msg.wConSlot==CONSLOT_DEFAULT, "failed to recv correct add stall item msg");
    check(msg.wItemSlot==0, "failed to recv correct add stall item msg");
    check(msg.nItemCount==5, "failed to recv correct add stall item msg");
    check(msg.nPrice==100, "failed to recv correct add stall item msg");

    --user1: open the stall
    ret = user1:RealOpenStall();
    check(ret, "failed to real open stall");

    --user2: receive a nearby stall state change notification
    msg = recv_msg(5, session_id2, protocol.g2c_stall_state_change);
    check(msg, "failed to recv g2c_stall_state_change");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct stall state change msg");
    check(msg.btStallState==essOpen, "failed to recv correct stall state change msg");

    --user2: view stall items
    ret = user2:ViewStallItem(role1:GetObjID());
    check(ret, "failed to view stall item");

    --user2: receive the stall item list
    msg = recv_msg(5, session_id2, protocol.g2c_view_stall_item);
    check(msg, "failed to recv g2c_view_stall_item");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct view stall item msg");
    check(msg.btStallItemCount==1, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].btStallSlot==0, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].stItem.nTemplateID==1, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].nPrice==100, "failed to recv correct view stall item msg");
    local modifytime = msg.stStallItem[0].dwModifyTime;

    --user2: add money with a GM command for the purchase
    ret = user2:GMCommand("AddMoney(1, 1000, MONEYLOG_GM_COMMAND)");
    check(ret, "failed to send gm command");

    --user2: buy a stall item
    ret = user2:BuyStallItem(role1:GetObjID(), 0, 1, modifytime);
    check(ret, "failed to buy stall item");

    --user2: receive the item-added message
    --user1: receive the item-removed message
    --user2: receive the money deduction message
    --user1: receive the money increase message
    --user2: receive the successful stall purchase message
    --user1: receive the successful stall sale message
    msg = recv_msg_and(10,
        session_id1, protocol.g2c_item_change,
        session_id2, protocol.g2c_item_change,
        session_id1, protocol.g2c_money_change,
        session_id2, protocol.g2c_money_change,
        session_id1, protocol.g2c_sold_stall_item,
        session_id2, protocol.g2c_buy_stall_item);
    check(msg, "failed to recv some msgs");

    --Log out
    cleanup(user1);
    cleanup(user2);
end
