LoadPackage("gameworld.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("spirit_def.pkg");

TestCase.Spirit = {};

function TestCase.Spirit.Soul2Pts()	-- 魂转修炼点
	-- 登陆
    local user_name1 = "spirit1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

   	local user1id = role1:GetObjID();
	local user1sessionid = user1:GetSessionID();

    ret = user1:ChangeSoul2Pts(false, true); --在线转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritNotOpen, "failed to recv errSpiritNotOpen");

    ret = user1:ChangeSoul2Pts(true, true); --立即转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritNotOpen, "failed to recv errSpiritNotOpen");

    local ret = user1:GMCommand("SetLevel(25)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

    ret = user1:ChangeSoul2Pts(false, true); --在线转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");	-- 魂不够

    ret = user1:ChangeSoul2Pts(false, true); --在线转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");

    -- 增加魂

   	ret = user1:GMCommand("AddMoney(6, 10000, MONEYLOG_GM_COMMAND)");
	check(ret, "failed to add money: soul");

	wait(2);

    ret = user1:ChangeSoul2Pts(false, true); --在线转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_exp_change);
    check(msg, "failed to recv g2c_spirit_exp_change");

    ret = user1:ChangeSoul2Pts(false, true); --在线转化
    check(ret, "fail to send changesoul2pts");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritChangeCDTime, "failed to recv errSpiritChangeCDTime");	-- 时间没到

    cleanup(user1);
end

function TestCase.Spirit.Air()	-- 气海
	-- 登陆
    local user_name1 = "spiritair1"..os.date("%H%M%S");
    local user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user");
    check(role1, "failed to create role");

   	local user1id = role1:GetObjID();
	local user1sessionid = user1:GetSessionID();

	-- 练气
    local ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritLevel, "failed to recv errSpiritLevel");	-- 等级没到

    ret = user1:GMCommand("SetLevel(25)");
    check(ret, "exec GMCommand SetLevel error: user1");

	wait(1);

    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritMoneyNotEnough, "failed to recv errSpiritMoneyNotEnough");	-- 魂不够

    -- 增加修炼点
    ret = user1:GMCommand("AddPts(100000)");
    check(ret, "exec GMCommand SetLevel error: user1");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_exp_change);
    check(msg, "failed to recv g2c_spirit_exp_change");

    -- 继续练气
    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");
   check(msg.nIndex == 0, "failed to recv g2c_spirit_air_change");	-- 出现在第0格

    -- 继续练气
    ret = user1:SpiritAddAir(false);
    check(ret, "fail to add spirit air");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");
   check(msg.nIndex == 1, "failed to recv g2c_spirit_air_change");	-- 出现在第1格

	-- 把气从第1格移到第0格
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritAirSlotNotEmpty, "failed to recv errSpiritAirSlotNotEmpty");	-- 气格子非空

	-- 把气从第1格移到第2格
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 2);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- 把气从第1格移到第3格
	ret = user1:MoveAir(sasbtBag, 1, sasbtBag, 3);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errSpiritAirSlotEmpty, "failed to recv errSpiritAirSlotEmpty");	-- 气格子为空

	-- 把气从背包第二格防入仓库 -- sasbtBag : 0 sasbtStall : 1
	ret = user1:MoveAir(0, 2, 1, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- 把气从仓库放入背包第二格
	--ret = user1:MoveAir(1, 0，0, 2);
	--check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- 把气从背包第二格装备到第0格
	ret = user1:MoveAir(sasbtBag, 2, sasbtEquip, 0);
	check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- 把气从第0格放到背包第二格
	--ret = user1:MoveAir(sasbtEquip, 0， sasbtBag, 2);
	--check(ret, "failed to MoveAir");

    msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
    check(msg, "failed to recv g2c_spirit_air_change");

	-- 合成气
	ret = user1:MergeAir(0);
	check(ret, "failed to MergeAir");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_air_change);
   check(msg, "failed to recv g2c_spirit_air_change");

	-- 买格子
	ret = user1:BuyAirSlot(sasbtBag);
	check(ret, "failed to BuyAirSlot");

    msg = recv_msg(30, user1sessionid, protocol.g2c_error_notify);
    check(msg.nErrCode == error_code.errNotEnoughMoney, "failed to recv errNotEnoughMoney");	-- 钱不够

	-- 增加钱
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

function TestCase.Spirit.Blood()	-- 天赋

   local user_name1 = "spiritblood1"..os.date("%H%M%S");
   local user1, role1 = startup(user_name1, user_name1);
   check(user1, "failed to create user");
   check(role1, "failed to create role");

   local user1sessionid = user1:GetSessionID();

   -- 没到境界开启等级
   local ret = user1:GMCommand("SetLevel(5)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(1);

   -- 刷新第1页
   ret = user1:BrushSlot(1, 1);
   check(ret, "failed to BuyAirSlot");

   local msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg == nil, "failed to test level");

   -- 开启等级
   local ret = user1:GMCommand("SetLevel(10)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(1);

   -- 刷新第0页
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

   -- 刷新第1页,境界等级不够
   ret = user1:BrushSlot(1, 2);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg.nErrCode == error_code.errSpiritLevel, "failed to test page index2")

   -- 提高境界等级
   local ret = user1:GMCommand("SetSpiritLevel(20)");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(5);

   -- 修炼点不够

   ret = user1:BrushSlot(1, 2);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(5, user1sessionid, protocol.g2c_error_notify);
   check(msg.nErrCode == error_code.errNotEnoughMoney, "failed to test page index3")

   -- 增加修炼点
   ret = user1:GMCommand("AddMoney 11 50000");
   check(ret, "exec GMCommand SetLevel error: user1");

   wait(3);

   ret = user1:BrushSlot(1, 3);
   check(ret, "failed to BuyAirSlot");

   msg = recv_msg(30, user1sessionid, protocol.g2c_spirit_brush_slot);
   check(msg, "failed to recv g2c_spirit_brush_slot");
end
