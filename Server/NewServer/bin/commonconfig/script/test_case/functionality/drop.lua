
--function TestCase.Drop()   There is no longer a GM command for testing drops
function Drop()
    local user_name = "Drop" .. os.date("%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name, GROUP_ID, clsWarrior, cstMale, SERVER_PORT, 102);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();
    --Create a drop using a GM command
    ret = user:GMCommand("TestDrop(1)");
    check(ret, "failed to send gm command");

    --Check the drop response
    msg = recv_msg(5, session_id, protocol.g2c_sync_drop_list);
    check(msg, "failed to  recv g2c_sync_drop_list");
    check(msg.byIsNew==1, "failed to recv new drop");
    check(msg.byCount==1, "failed to recv only one drop");
    check(msg.astDrops[0].nTemplateID==13, "failed to recv correct drop");

    local dropid = msg.astDrops[0].dwDropID;

    --Pick up the drop
    ret = user:PickUpItem(dropid);
    check(ret, "failed to send pick up item");

    --Expect an item-change response
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
    check(msg.stItem.nTemplateID==13, "failed to create correct item");

    --Expect a drop-disappeared response
    msg = recv_msg(5, session_id, protocol.g2c_object_disappear);
    check(msg, "failed to recv g2c_object_disappear");
    check(msg.dwObjID==dropid, "failed to receive correct drop disappear msg");

    --Create another drop using a GM command
    ret = user:GMCommand("TestDrop(1)");
    check(ret, "failed to send gm command");

    --Check the drop response
    msg = recv_msg(5, session_id, protocol.g2c_sync_drop_list);
    check(msg, "failed to  recv g2c_sync_drop_list");
    check(msg.byIsNew==1, "failed to recv new drop");
    check(msg.byCount==1, "failed to recv only one drop");
    check(msg.astDrops[0].nTemplateID==13, "failed to recv correct drop");
    
    dropid = msg.astDrops[0].dwDropID;

    --Wait five minutes for the drop to disappear
    msg = recv_msg(310, session_id, protocol.g2c_object_disappear);
    check(msg, "failed to recv g2c_object_disappear");
    check(msg.dwObjID==dropid, "failed to receive correct drop disappear msg");

    --Test complete; log out
    cleanup(user);
end

--function TestCase.OperateDoodad()   That doodad may no longer exist
function OperateDoodad()
    local user_name = "Doodad" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");

    session_id = user:GetSessionID();

    --Spawn a doodad using a GM command
    ret = user:GMCommand("SummonDoodad(1)");
    check(ret, "failed to send gm command");

    --Check the spawned doodad
    msg = recv_msg(30, session_id, protocol.g2c_sync_doodad_list);
    check(msg, "failed to recv sync doodad list msg");
    check(msg.astAppearData[0].nTemplateID==1, "failed to recv correct doodad list");

    local doodad_id = msg.astAppearData[0].dwDoodadID;

    --Select the doodad
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

    --Test complete; log out
    cleanup(user);
end