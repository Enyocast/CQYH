
TestCase.Adventure = {};

function temp()
    -- adventure 1
    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);
    
    user:GMCommand("Jump(2, 0, 1000, 1000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    for i=1, 2 do
        user:GMCommand("Kill(SummonNpc(101):GetObjID());");
        msg = recv_msg(30, user:GetSessionID(), protocol.g2c_sync_npc_data);
        check(msg, "failed to recv g2c_sync_npc_data");
        check(msg.nTemplateID == 101, "error npc template id");
    end
    
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_sync_npc_data);
    check(msg, "failed to recv g2c_sync_npc_data");
    check(msg.nTemplateID == 102, "error npc template id");
    check(msg.byLevel == 20, "error npc level");
    check(msg.byQuality == nqElite, "error npc quality");

    cleanup(user);
    wait(5);

    -- adventure 2
    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

    user:GMCommand("SetLevel(9)");
    user:GMCommand("Jump(1, 0, 1000, 1000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    for i=1, 3 do
        user:GMCommand("Kill(SummonDoodad(101):GetObjID());");
    end

    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_sync_npc_data);
    check(msg, "failed to recv g2c_sync_npc_data");
    check(msg.nTemplateID == 102, "error npc template id");
    check(msg.byLevel == role:GetLevel(), "error npc level");
    check(msg.byQuality == nqNormal1, "error npc quality");

    cleanup(user);
    wait(5);

    -- adventure 3
    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

    CreateGuild(role, user, user:GetSessionID(), user_name, user_name, user_name);
    user:GMCommand("Jump(1, 0, 10000, 10000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    user:GMCommand("SetLevel(40);AddMoney(MONEYTYPE_01, 1000000);AddMoney(MONEYTYPE_02, 1000000);AddItem(125, 99);AddItem(126, 99);AddItem(127, 99);");

    for i=1, 4 do
        user:GMCommand("TargetRole:GetItemBag():Refine(NES_HEAD);");
    end
    
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_sync_doodad_list);
    check(msg, "failed to recv g2c_sync_doodad_list");
    check(msg.astAppearData[0].nTemplateID == 102, "error doodad template id");

    cleanup(user);
    wait(5);

    -- adventure 5
    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

    user:GMCommand("Jump(2, 0, 1000, 1000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    user:GMCommand("SetLevel(40);AddMoney(MONEYTYPE_01, 1000000);AddMoney(MONEYTYPE_02, 1000000);AddItem(1012035, 1);");

    for i=1, 4 do
        user:GMCommand("local pos = FindItemPosInEquipBag(1012035);TargetRole:GetItemBag():RandomizeItem(CONSLOT_DEFAULT, pos);");
    end

    cleanup(user);
    wait(5);

    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

    user:GMCommand("Jump(2, 0, 1000, 1000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    user:GMCommand("SetLevel(40);AddMoney(MONEYTYPE_01, 1000000);AddMoney(MONEYTYPE_02, 1000000);AddItem(1012035, 1);");

    for i=1, 2 do
        user:GMCommand("local pos = FindItemPosInEquipBag(1012035);TargetRole:GetItemBag():RandomizeItem(CONSLOT_DEFAULT, pos);");
    end
    
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_sync_doodad_list);
    check(msg, "failed to recv g2c_sync_doodad_list");
    check(msg.astAppearData[0].nTemplateID == 102, "error doodad template id");

    cleanup(user);
    wait(5);
    
end

function TestCase.Adventure.Adventure()
    local msg, ret;

    -- adventure 6
    local user_name = "adve"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

    CreateGuild(role, user, user:GetSessionID(), user_name, user_name, user_name);
    user:GMCommand("Jump(2, 0, 1000, 1000)");
    msg = recv_msg(30, user:GetSessionID(), protocol.g2c_enter_scene);
    check(msg, "failed to recv g2c_enter_scene");
    wait(5);

    msg = recv_msg(5 * 60, user:GetSessionID(), protocol.m2c_mail_new_count);
    check(msg, "failed to recv m2c_mail_new_count");
    check(msg.dwMailNewCount > 0, "error new mail count");

    cleanup(user);
    wait(5);

end