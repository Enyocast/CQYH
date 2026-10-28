
--function TestCase.Drop()   没有测试掉落的gm指令了
function Drop()
    local user_name = "Drop" .. os.date("%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name, GROUP_ID, clsWarrior, cstMale, SERVER_PORT, 102);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
    --用GM指令产生掉落
    ret = user:GMCommand("TestDrop(1)");
    check(ret, "failed to send gm command");

    --检查掉落回包
    msg = recv_msg(5, session_id, protocol.g2c_sync_drop_list);
    check(msg, "failed to  recv g2c_sync_drop_list");
    check(msg.byIsNew==1, "failed to recv new drop");
    check(msg.byCount==1, "failed to recv only one drop");
    check(msg.astDrops[0].nTemplateID==13, "failed to recv correct drop");

    local dropid = msg.astDrops[0].dwDropID;

    --拾取掉落
    ret = user:PickUpItem(dropid);
    check(ret, "failed to send pick up item");

    --应当收到物品变化的回包
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.stItem.nTemplateID==13, "failed to create correct item");

    --应当收到掉落消失的回包
    msg = recv_msg(5, session_id, protocol.g2c_object_disappear);
    check(msg, "failed to recv g2c_object_disappear");
    check(msg.dwObjID==dropid, "failed to receive correct drop disappear msg");

    --再用GM指令产生一次掉落
    ret = user:GMCommand("TestDrop(1)");
    check(ret, "failed to send gm command");

    --检查掉落回包
    msg = recv_msg(5, session_id, protocol.g2c_sync_drop_list);
    check(msg, "failed to  recv g2c_sync_drop_list");
    check(msg.byIsNew==1, "failed to recv new drop");
    check(msg.byCount==1, "failed to recv only one drop");
    check(msg.astDrops[0].nTemplateID==13, "failed to recv correct drop");
    
    dropid = msg.astDrops[0].dwDropID;

    --等5分钟掉落消失
    msg = recv_msg(310, session_id, protocol.g2c_object_disappear);
    check(msg, "failed to recv g2c_object_disappear");
    check(msg.dwObjID==dropid, "failed to receive correct drop disappear msg");

    --测试完成，登出
    cleanup(user);
end

--function TestCase.OperateDoodad()   那个doodad可能也没有了
function OperateDoodad()
    local user_name = "Doodad" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --用GM指令召唤一个Doodad
    ret = user:GMCommand("SummonDoodad(1)");
    check(ret, "failed to send gm command");

    --检查召唤出的Doodad
    msg = recv_msg(30, session_id, protocol.g2c_sync_doodad_list);
    check(msg, "failed to recv sync doodad list msg");
    check(msg.astAppearData[0].nTemplateID==1, "failed to recv correct doodad list");

    local doodad_id = msg.astAppearData[0].dwDoodadID;

    --点Doodad
    ret = user:OperateDoodad(doodad_id);
    check(ret, "failed to operate doodad");

	msg = recv_msg(30, session_id, protocol.g2c_operate_doodad_begin);    
    check(msg, "failed to recv g2c_operate_doodad_begin");

    msg = recv_msg(30, session_id, protocol.g2c_sync_drop_list);
    check(msg, "failed to  recv g2c_sync_drop_list");
    check(msg.byIsNew==1, "failed to recv new drop");
    check(msg.wSize==4+20, "failed to recv only one drop");

	msg = recv_msg(30, session_id, protocol.g2c_operate_doodad_end);    
    check(msg, "failed to recv g2c_operate_doodad_end");

    ret = user:OperateDoodad(doodad_id);
    check(ret, "failed to operate doodad");
    
    ret = role:MoveTo(role:GetX(), role:GetY() + 1);
    check(ret, "failed to move");
    
    msg = recv_msg(30, session_id, protocol.g2c_operate_doodad_end);
    check(msg, "failed to recv g2c_operate_doodad_end");
    check(msg.byIsBreak == 1, "failed to recv g2c_operate_doodad_end break");

    ret = user:OperateDoodad(doodad_id);
    check(ret, "failed to operate doodad");

	msg = recv_msg(30, session_id, protocol.g2c_object_disappear);
	check(msg, "failed to recv g2c_object_disappear");
	check(msg.dwObjID == doodad_id, "error doodad id");

    --测试完成，登出
    cleanup(user);
end