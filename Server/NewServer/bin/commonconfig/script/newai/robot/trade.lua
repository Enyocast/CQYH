LoadPackage("trade.pkg")
LoadPackage("role.pkg")
LoadPackage("asimov_user.pkg")

function do_role_trade_action(owner)
	local processor = owner:GetAIProcessor();   
    local role = Cast(processor:GetOwner(), 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
 
    local role_id = role:GetObjID();   
	if role_id % 10 < 5 then
		return brvFail;
	end
 							
	if not role:GetTrade():IsTrading() then
		print("role "..role_id.." is not trading");
		g_RobotMessageHandler:SetTradeTendency(10000);
		
		for i = 1, 100, 1 do
			local trade_user = CUserMgr:GetInstance():RandAnotherUser(user);
			if trade_user then
				local trade_role = trade_user:GetPlayingRole();
				if trade_role and 
				   ( not trade_role:GetTrade():IsTrading() ) and 
				   ( not trade_role:GetFlag():CheckFlag(cfInCombat) ) then
					local sx, sy, sz = ConvertCoordN2O(trade_role:GetX()/POINT_PER_CM, trade_role:GetY()/POINT_PER_CM, trade_role:GetZ()/POINT_PER_CM);
					JumpToScene(user, role, trade_role:GetSceneTempID(), trade_role:GetSceneID(), sx, sy, sz);
		
					print("role "..role_id.." start to ask trading with target role "..trade_role:GetObjID());
					g_RobotMessageHandler:DoTradeAsk(role, trade_role:GetObjID());
					
					return brvSuccess;
				end
			end
		end

	else
		-- do things in c code;
		--print("role "..role_id.." is trading, process in c code");
		print("role "..role_id.." is trading, random issue relevant msg");
	--[[	
		local rand_value = math.random(1, 10);
		if rand_value == 1 then
			print("role "..role_id.." cancel trading");
			g_RobotMessageHandler:DoTradeCancel(role);
		else
	--]]
	--[[
			local rand_value = math.random(1, 2);
			if rand_value == 1 then
				print("role "..role_id.." trade set money ");
				g_RobotMessageHandler:DoTradeSetMoney(role, 1);
			elseif rand_value == 2 then
				print("role "..role_id.." trade set item");
				g_RobotMessageHandler:DoTradeSetItem(role, 1, 1, 1, 1);
			end
			
			rand_value = math.random(1, 10);
			if rand_value < 10 then
				print("role "..role_id.." trade lock");
				g_RobotMessageHandler:DoTradeLock(role);
			end
			
			rand_value = math.random(1, 10);
			if rand_value < 10 then
				print("role "..role_id.." trade confirm");
				g_RobotMessageHandler:DoTradeConfirm(role);
			end
	--]]
	--[[
		end
	--]]
	end  
   
    return brvFail;
end

trade_tree = 
{ batSequencer,
    { batCheckCDTimer, param = { COOLDOWN_AI, TRADE_CD_TIMER } },
    { batSetCDTimer, param  = { COOLDOWN_AI, TRADE_CD_TIMER, TRADE_INTERVAL } },
        { batSequencer,
            { do_role_trade_action },
            { batWait, param = { TRADE_INTERVAL } },
		},
};


-----------------trade function---------------------------------------------
function performance_trade(owner)
	local processor = owner:GetAIProcessor();
	local role = Cast(owner, 'CRole');
	local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	local npctemplateid = 8464; --比奇戒指店老板
	local itemid = 99930001; --古铜戒指
	local numbercount = 1;

	if role:GetItemBag():GetMoney(MONEYTYPE_02) <= 10000 then
		--owner:AddMoney(MONEYTYPE_01, 10000, CItemBag:MONEYLOG_GM_COMMAND);	
		user:GMCommand("AddMoney "..MONEYTYPE_02.." 10000"); -- MONEYTYPE_02 == 1
	end

	local chance = math.random(1);
	if chance == 0 then	-- summon npc and buy
		local ret = performance_trade_summonnpc_buy(user, npctemplateid, itemid)
	end

	if chance == 1 then -- trade money
		--local targeruser = CUserMgr:GetInstance():RandAnotherUser(user);
		--performance_trade_with_role(user, targeruser, itemid);
		local ret = do_role_trade_action(owner);
		
	end
end

function performance_trade_summonnpc_buy(user, npctemplateid, itemid)
	print("user "..user:GetUserName().."trade with npc "..npctemplateid.." to buy item "..itemid);

    local session_id = user:GetSessionID();

	ret = user:GMCommand("SummonNpc("..npctemplateid..")");
	check(ret, "failed to summon npc");

	local msg = recv_msg(30, session_id, protocol.g2c_char_appear);
	check(msg, "failed to recv g2c_char_appear");

	local npc_id = msg.stAppearData.dwCharID;

    ret = user:InteractWithNpc(npc_id);
    check(ret, "failed to interact with npc");

    msg = recv_msg(10, session_id, protocol.g2c_interact_result);
    check(msg, "Fail to recv g2c_interact_result.")

	ret = user:BuyItem(itemid);
    check(ret, "failed to send buy item msg");

    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");
end

--[[
function performance_trade_with_role(user, targetuser, itemid)
	local srcrole = user:GetPlayingRole()
	if srcrole == nil then
		return;
	end

	local targetrole = targetuser:GetPlayingRole()
	if targetrole == nil then
		return;
	end

	local session_id1 = user:GetSessionID();
	--local session_id2 = targetuser:GetSessionID();

	local chance = math.random(1);
	if chance == 0 then
		print("user "..user:GetUserName().."actively trade with role "..targetuser:GetUserName().." to give money ");

		--user: 请求交易
    		ret = user:AskTrade(targetrole:GetObjID());
    		check(ret, "trade: failed to ask trade");

		--user1: 请求交易 state sync
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsAsking, "trade: failed to recv g2c_trade_state_change etsAsking");

		--user1: 收到交易状态改变 state sync
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsBeingAsked, "trade: failed to recv g2c_trade_state_change etsBeingAsked");

		--user1: 收到交易状态改变 target user accept 交易
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsTrading, "trade: failed to recv g2c_trade_state_change etsTrading");

		wait(2);

		--user: 出1000块钱
		ret = user:SetTradeMoney(1000);
		check(ret, "trade: failed to set trade money");

		wait(2);

		--user: 锁定
		ret = user:LockTrade();
		check(ret, "trade: failed to lock trade");

		wait(2);

		--user: 收到交易状态改变 target user 锁定
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");

		wait(2);

		--user: 确认
		ret = user:ConfirmTrade();
		check(ret, "trade: failed to lock trade");

		wait(2);

		--user: 收到交易状态改变 target user 确认
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
	
	else
		--targetuser: 请求交易 state sync
		msg = recv_msg(10, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsAsking, "trade: failed to recv g2c_trade_state_change etsAsking");

		local srcRoleID = msg.dwRoleID;
		print("user "..user:GetUserName().."passively trade with role "..srcRoleID.." to get money ");

		--targetuser: 收到交易状态改变
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsBeingAsked, "failed to recv g2c_trade_state_change etsBeingAsked");

		wait(2);

		--targetuser: 接受交易
		ret = targetuser:AcceptTrade(srcRoleID);
		check(ret, "trade: failed to accept trade");

		--targetuser: 交易状态改变 target user accept 交易
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");
		check(msg.byTradeState == etsTrading, "trade: failed to recv g2c_trade_state_change etsTrading");

		wait(2);

		--targetuser: 收到user出钱的消息
		msg = recv_msg(5, session_id1, protocol.g2c_trade_set_money);
		check(msg, "trade: failed to recv g2c_trade_set_money");

		wait(2);

		--targetuser: 收到交易状态改变 user 锁定
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");

		wait(2);

		--targetuser: 锁定
		ret = targetuser:LockTrade();
		check(ret, "trade: failed to lock trade");

		--targetuser: 收到交易状态改变 user 确认
		msg = recv_msg(5, session_id1, protocol.g2c_trade_state_change);
		check(msg, "trade: failed to recv g2c_trade_state_change");

		wait(2);

		--targetuser: 确认
		ret = targetuser:ConfirmTrade();
		check(ret, "trade: failed to lock trade");

		wait(2);

		--targetuser: 收到钱
		msg = recv_msg(5, session_id1, protocol.g2c_money_change);
		check(msg, "trade: failed to recv g2c_money_change");
		check(msg.nMoney == 1000, "trade: failed to recv correct money (user2)");

	end


end

---]]
