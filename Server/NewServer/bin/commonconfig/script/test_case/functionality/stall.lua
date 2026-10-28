

function TestCase.Stall()
    local user_name1 = "S1_" .. os.date("%Y%H%M%S");
    local user_name2 = "S2_" .. os.date("%Y%H%M%S");
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

    --user1: 用GM指令增加药水并检查
    ret = user1:GMCommand("AddItem(101,10, ITEMLOG_GM_COMMAND)");
    check(ret, "failed to send gm command");

    msg = recv_msg(5, session_id1, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.stItem.nTemplateID==101, "failed to create correct item");
    check(msg.stItem.nCurDur==10, "failed to create correct item");

    --user1: 准备摆摊
    ret = user1:OpenStall();
    check(ret, "failed to send move item msg");

    --user2: 收到附近有人摊位状态变化消息
    msg = recv_msg(5, session_id2, protocol.g2c_stall_state_change);
    check(msg, "failed to recv g2c_stall_state_change");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct stall msg");
    check(msg.btStallState==essPreparing, "failed to recv correct stall msg");

    --user1: 把药水上架，100/个，共5个
    ret = user1:AddStallItem(0, CONSLOT_DEFAULT, 0, 5, 100);
    check(ret, "failed to add stall item");

    --user1: 收到上架回复
    msg = recv_msg(5, session_id1, protocol.g2c_add_stall_item);
    check(msg, "failed to recv g2c_add_stall_item");
    check(msg.btStallSlot==0, "failed to recv correct add stall item msg");
    check(msg.wConSlot==CONSLOT_DEFAULT, "failed to recv correct add stall item msg");
    check(msg.wItemSlot==0, "failed to recv correct add stall item msg");
    check(msg.nItemCount==5, "failed to recv correct add stall item msg");
    check(msg.nPrice==100, "failed to recv correct add stall item msg");

    --user1: 真正开张
    ret = user1:RealOpenStall();
    check(ret, "failed to real open stall");

    --user2: 收到附近有人摊位状态变化消息
    msg = recv_msg(5, session_id2, protocol.g2c_stall_state_change);
    check(msg, "failed to recv g2c_stall_state_change");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct stall state change msg");
    check(msg.btStallState==essOpen, "failed to recv correct stall state change msg");

    --user2: 查看摊位物品列表
    ret = user2:ViewStallItem(role1:GetObjID());
    check(ret, "failed to view stall item");

    --user2: 收到摊位物品列表回复
    msg = recv_msg(5, session_id2, protocol.g2c_view_stall_item);
    check(msg, "failed to recv g2c_view_stall_item");
    check(msg.dwRoleID==role1:GetObjID(), "failed to recv correct view stall item msg");
    check(msg.btStallItemCount==1, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].btStallSlot==0, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].stItem.nTemplateID==1, "failed to recv correct view stall item msg");
    check(msg.stStallItem[0].nPrice==100, "failed to recv correct view stall item msg");
    local modifytime = msg.stStallItem[0].dwModifyTime;

    --user2: 用GM指令给自己加点钱，等下要买东西
    ret = user2:GMCommand("AddMoney(1, 1000, MONEYLOG_GM_COMMAND)");
    check(ret, "failed to send gm command");

    --user2: 买摊位物品
    ret = user2:BuyStallItem(role1:GetObjID(), 0, 1, modifytime);
    check(ret, "failed to buy stall item");

    --user2: 收到物品增加消息
    --user1: 收到物品减少消息
    --user2: 收到钱减少消息
    --user1: 收到钱增加消息
    --user2: 收到购买摊位物品成功消息
    --user1: 收到售出摊位物品成功消息
    msg = recv_msg_and(10,
        session_id1, protocol.g2c_item_change,
        session_id2, protocol.g2c_item_change,
        session_id1, protocol.g2c_money_change,
        session_id2, protocol.g2c_money_change,
        session_id1, protocol.g2c_sold_stall_item,
        session_id2, protocol.g2c_buy_stall_item);
    check(msg, "failed to recv some msgs");

    --登出
    cleanup(user1);
    cleanup(user2);
end
