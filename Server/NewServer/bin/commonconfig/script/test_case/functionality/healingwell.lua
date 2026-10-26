function TestCase.HealingWell()
    local msg, ret;
    local user_name = "heal"..os.date("%H%M%S");

    local user, role = startup(user_name, user_name, GROUP_ID, nil, nil, nil, 1);
    local session_id = user:GetSessionID();

    user:GMCommand("SummonNpc(3005)");
    msg = recv_msg(5, session_id, protocol.g2c_char_appear);
    check(msg, "failed to summon npc");
    local npc_id = msg.stAppearData.dwCharID;

    ret = user:InteractWithNpc(npc_id);
    check(ret, "failed to interact with npc");

    msg = recv_msg(5, session_id, protocol.g2c_char_spell_effect);
    check(msg, "failed to recv cast spell msg");
    check(msg.dwCasterID == npc_id, "error caster id");
    check(msg.dwTargetID == role:GetObjID(), "error target id");
    check(msg.wSpellID == 7020, "error spell id");
    check(msg.bySpellLevel == 1, "error spell level");
    check(msg.byRuneSlot == 0, "error rune slot");
   
    msg = recv_msg(5, session_id, protocol.g2c_play_animation);
    check(msg, "failed to recv g2c_play_animation");   
    check(msg.dwCharID == npc_id, "error char id");
    check(msg.wAnimationID == 18, "error animation id");
    check(msg.shStartFrame == 0, "error start frame");
   
    ret = user:InteractWithNpc(npc_id);
    check(ret, "failed to interact with npc");

    msg = recv_msg(5, session_id, protocol.g2c_char_spell_effect);
    check(msg == nil, "healing spell cd is wrong");

    msg = recv_msg(60, session_id, protocol.g2c_play_animation);
    check(msg, "failed to recv g2c_play_animation");   
    check(msg.dwCharID == npc_id, "error char id");
    check(msg.wAnimationID == 19, "error animation id");
    check(msg.shStartFrame == 0, "error start frame");
    
    cleanup(user);
end