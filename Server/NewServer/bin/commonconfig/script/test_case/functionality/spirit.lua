LoadPackage("gameworld.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("spirit_def.pkg");

TestCase.Spirit = {};

function TestCase.Spirit.Soul2Pts()	-- Convert soul to cultivation points
	-- Log in
    local user_name1 = "spirit1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

   	local user1id = role1:GetObjID();
	local user1sessionid = user1:GetSessionID();

    ret = user1:ChangeSoul2Pts(false, true); --Online conversion
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritNotOpen, "failed to recv errSpiritNotOpen");

    ret = user1:ChangeSoul2Pts(true, true); --Convert immediately
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritNotOpen, "failed to recv errSpiritNotOpen");

    local ret = user1:GMCommand("SetLevel(25)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

    ret = user1:ChangeSoul2Pts(false, true); --Online conversion
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");	-- Insufficient soul

    ret = user1:ChangeSoul2Pts(false, true); --Online conversion
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");

    -- Add soul

   	ret = user1:GMCommand("AddMoney(6, 10000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money: soul");

	wait(2);

    ret = user1:ChangeSoul2Pts(false, true); --Online conversion
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_exp_change);
    check(msg, "failed to recv g2c_spirit_exp_change");

    ret = user1:ChangeSoul2Pts(false, true); --Online conversion
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritChangeCDTime, "failed to recv errSpiritChangeCDTime");	-- Cooldown has not elapsed

    cleanup(user1);
end

function TestCase.Spirit.Air()	-- Qi Sea
	-- Log in
    local user_name1 = "spiritair1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

   	local user1id = role1:GetObjID();
	local user1sessionid = user1:GetSessionID();

	-- Cultivate qi
    local ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritLevel, "failed to recv errSpiritLevel");	-- Level requirement not met

    ret = user1:GMCommand("SetLevel(25)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");	-- Insufficient soul

    -- Add cultivation points
    ret = user1:GMCommand("AddPts(100000)");
    check(ret, "exec GMCommand SetLevel error: user1");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_exp_change);
    check(msg, "failed to recv g2c_spirit_exp_change");

    -- Continue cultivating qi
    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");
   check(msg.nIndex == 0, "failed to recv g2c_spirit_air_change");	-- Appears in slot 0

    -- Continue cultivating qi
    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");
   check(msg.nIndex == 1, "failed to recv g2c_spirit_air_change");	-- Appears in slot 1

	-- Move qi from slot 1 to slot 0
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritAirSlotNotEmpty, "failed to recv errSpiritAirSlotNotEmpty");	-- Qi slot is not empty

	-- Move qi from slot 1 to slot 2
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 2);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- Move qi from slot 1 to slot 3
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 3);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritAirSlotEmpty, "failed to recv errSpiritAirSlotEmpty");	-- Qi slot is empty

	-- Move qi from the second inventory slot into storage -- sasbtBag : 0 sasbtStall : 1
	ret = user1:MoveAir(0, 2, 1, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- Move qi from storage to the second inventory slot
	--ret = user1:MoveAir(1, 0，0, 2);
	--check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- Equip qi from the second inventory slot in slot 0
	ret = user1:MoveAir(sasbtBag, 2, sasbtEquip, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- Move qi from slot 0 to the second inventory slot
	--ret = user1:MoveAir(sasbtEquip, 0， sasbtBag, 2);
	--check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- Combine qi
	ret = user1:MergeAir(0);
	check(ret, "failed to MergeAir");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");

	-- Buy a slot
	ret = user1:BuyAirSlot(sasbtBag);
	check(ret, "failed to BuyAirSlot");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errNotEnoughMoney, "failed to recv errNotEnoughMoney");	-- Insufficient money

	-- Add money
	ret = user:GMCommand("AddMoney(2, 1000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money");

	wait(1);

	ret = user1:BuyAirSlot(sasbtBag);
	check(ret, "failed to BuyAirSlot");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_slot_size_change);
   check(msg, "failed to recv g2c_spirit_slot_size_change");

	ret = user1:BuyAirSlot(sasbtStall);
	check(ret, "failed to BuyAirSlot");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_slot_size_change);
   check(msg, "failed to recv g2c_spirit_slot_size_change");

	ret = user1:BuyAirSlot(sasbtEquip);
	check(ret, "failed to BuyAirSlot");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_slot_size_change);
   check(msg, "failed to recv g2c_spirit_slot_size_change");

end

function TestCase.Spirit.Blood()	-- Talent

   local user_name1 = "spiritblood1"..os.date("%H%M%S");
   local user1, role1 = startup(user_name1, user_name1);
   check(user1, "failed to create user");
   check(role1, "failed to create role");

   local user1sessionid = user1:GetSessionID();

   -- Realm unlock level not reached
   local ret = user1:GMCommand("SetLevel(5)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(1);

   -- Refresh page 1
   ret = user1:BrushSlot(1, 1);
   check(ret, "failed to BuyAirSlot");

   local msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg == nil, "failed to test level");

   -- Unlock level
   local ret = user1:GMCommand("SetLevel(10)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(1);

   -- Refresh page 0
   ret = user1:BrushSlot(1, 0);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg == nil, "failed to test page index1")

   ret = user1:BrushSlot(0, 1);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg == nil, "failed to test slot index")

   ret = user1:BrushSlot(0, 1);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg == nil, "failed to test slot index")

   -- Refresh page 1 with insufficient realm level
   ret = user1:BrushSlot(1, 2);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg.nErrCode == error_code.errSpiritLevel, "failed to test page index2")

   -- Increase realm level
   local ret = user1:GMCommand("SetSpiritLevel(20)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(5);

   -- Insufficient cultivation points

   ret = user1:BrushSlot(1, 2);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg.nErrCode == error_code.errNotEnoughMoney, "failed to test page index3")

   -- Add cultivation points
   ret = user1:GMCommand("AddMoney 11 50000");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(3);

   ret = user1:BrushSlot(1, 3);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_brush_slot);
   check(msg, "failed to recv g2c_spirit_brush_slot");
end
