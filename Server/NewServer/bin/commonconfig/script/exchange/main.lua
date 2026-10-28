LoadPackage("exchange.pkg");
LoadPackage("online_role_data.pkg");
LoadPackage("global_config.pkg")

-- 配置表
ConfigList = 
{
--          最小比例     最大比例     最小盘口手数    单笔放弃上限       单笔放弃几率         最小刷新间隔          最大刷新间隔          是否允许撤单          是否使用平均下单间隔
	[1] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 5,  nMaxRefreshTime = 10, bAllowRemove = false, bUseAvgDelay = true },
	[2] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 6,  nMaxRefreshTime = 12, bAllowRemove = false, bUseAvgDelay = true },
	[3] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 7,  nMaxRefreshTime = 13, bAllowRemove = false, bUseAvgDelay = false },
	[4] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 8,  nMaxRefreshTime = 14, bAllowRemove = false, bUseAvgDelay = false },
	[5] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 9,  nMaxRefreshTime = 15, bAllowRemove = false, bUseAvgDelay = false },
	[6] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 15, nMaxRefreshTime = 30, bAllowRemove = true, bUseAvgDelay = false },
	[7] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 15, nMaxRefreshTime = 30, bAllowRemove = true, bUseAvgDelay = false },
	[8] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 15, nMaxRefreshTime = 30, bAllowRemove = true, bUseAvgDelay = false },
	[9] = { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 15, nMaxRefreshTime = 30, bAllowRemove = true, bUseAvgDelay = false },
	[10]= { fMin = 0.55, fMax = 0.65, nMinCount = 10, nIgnoreCount = 10, fIgnoreChance = 0.1, nMinRefreshTime = 15, nMaxRefreshTime = 30, bAllowRemove = true, bUseAvgDelay = false },
};

ActiveConfig = 
{
	-- 主动单比例
	fMinOrderPercent = 0.1,
	fMaxOrderPercent = 0.2,
	-- 最小盘口比例
	fMin = 0.1,
	-- 最大盘口比例
	fMax = 0.2,
	-- 最小盘口手数
	nMinCount = 50,
}

ORDER_STAT_DURATION = 60 * 10;

g_ExchangeMgr = CExchangeMgr:GetInstance();
g_OnlineRoleMgr = COnlineRoleDataMgr:GetInstance();
g_NextRefreshTimeList = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
g_nHighPriceLimit = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
g_nLowPriceLimit = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
g_nMaxSingleCount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
g_nMaxCountPerPrice = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

g_UserOrderList = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };

g_nActiveOrderCount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
g_nNextActiveOrderRefreshTime = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

function CheckConfigList()
	for i, v in ipairs(ConfigList) do
		if v.fMin < 0.1 then
			print('fixed '..i..' price percent from '..v.fMin..' to 0.1');
			v.fMin = 0.1;
		end
		if v.fMax > 0.9 then
			print('fixed '..i..' price percent from '..v.fMax..' to 0.9');
			v.fMax = 0.9;
		end
		if v.fMin > v.fMax then
			print('fixed '..i..' price percent from '..v.fMin..' to max '..v.fMax);
			v.fMin = v.fMax;
		end
		if v.nMinRefreshTime > v.nMaxRefreshTime then
			print('fixed '..i..' price refresh time from '..v.nMinRefreshTime..' to max '..v.nMaxRefreshTime);
			v.nMinRefreshTime = v.nMaxRefreshTime;
		end
--		print('price '..i..' min '..v.fMin..' max '..v.fMax..' mincount '..v.nMinCount..' ignorecount '..v.nIgnoreCount..
--			' ignorechance '..v.fIgnoreChance..' minrefreshtime '..v.nMinRefreshTime..' maxrefreshtime '..v.nMaxRefreshTime);
	end
end
CheckConfigList();

-- 撮合前
function BeforeMainLoop(nServerGroup)

end

function ProcessPrice(PriceInfo, PriceConfig, nServerGroup, nAverageDelay)
	-- 低于系统最低限价，或者高于系统最低限价，则返回
	if PriceInfo.nPrice < g_nLowPriceLimit[nServerGroup] or PriceInfo.nPrice > g_nHighPriceLimit[nServerGroup] then
		return
	end
	local fCountPercent = PriceInfo.nSystemHandCount / PriceInfo.nHandCount;
	if fCountPercent > PriceConfig.fMax and PriceConfig.bAllowRemove then
		-- 如果该档口的比例高于指定比例，且该档口允许撤单，则尝试撤单
		local OrderList = get_order_list(nServerGroup, eotSell, PriceInfo.nPrice);
		local nMinCount = 100000000;
		local szOrderID = nil;
		-- 找到手数最少的系统单
		for i, v in ipairs(OrderList) do
			if v.dwRoleID == 0 and v.nHandCount < nMinCount then
				nMinCount = v.nHandCount;
				szOrderID = v.szOrderID;
			end
		end
		local fNewCountPercent = (PriceInfo.nSystemHandCount - nMinCount) / (PriceInfo.nHandCount - nMinCount);
		-- 如果取消手数最少的系统单后，比例还高于该价位的最低比例，则取消该订单
--		if szOrderID and (fNewCountPercent >= PriceConfig.fMin or PriceInfo.nSystemHandCount == PriceInfo.nHandCount) then
		if szOrderID and (fNewCountPercent >= PriceConfig.fMin) then
			cancel_system_order(nServerGroup, szOrderID);
			print('removed system order price '..PriceInfo.nPrice..' count '..nMinCount..' group '..nServerGroup);
		else
--			print('cannot remove system order price '..PriceInfo.nPrice..' count '..nMinCount..' group '..nServerGroup);
		end
	elseif fCountPercent <= PriceConfig.fMin then 
		-- 如果该档口的比例低于指定比例

		-- 小于最小盘口数，则不加单
		if PriceInfo.nHandCount < PriceConfig.nMinCount then
--			print('price '..PriceInfo.nPrice..' has too few hand count to follow');
			return
		end

		if PriceInfo.nSystemHandCount > g_nMaxCountPerPrice[nServerGroup] then
--			print('price '..PriceInfo.nPrice..' has too many hand count to follow');
			return
		end

		-- 计算下单手数
		local nMinFollowCount = math.ceil(PriceInfo.nHandCount * PriceConfig.fMin - PriceInfo.nSystemHandCount);
		if nMinFollowCount <= 0  then
			nMinFollowCount = 0;
		elseif nMinFollowCount < 1 then
			nMinFollowCount = 1;
		end

		local nMaxFollowCount = math.ceil(PriceInfo.nHandCount * PriceConfig.fMax - PriceInfo.nSystemHandCount);
		if nMaxFollowCount <= 0  then
			nMaxFollowCount = 0;
		elseif nMaxFollowCount < 1 then
			nMaxFollowCount = 1;
		end

		local nFollowCount = math.random(nMinFollowCount, nMaxFollowCount);

		-- 高于盘口最大系统单手数，则调整为最大系统单手数
		if (nFollowCount + PriceInfo.nSystemHandCount) > g_nMaxCountPerPrice[nServerGroup] then
			local nOldFollowCount = nFollowCount;
			nFollowCount = (g_nMaxCountPerPrice[nServerGroup] - PriceInfo.nSystemHandCount) + math.random(0, 5);
			print('reduced follow count from '..nOldFollowCount..' to '..nFollowCount..' by sys max count');
		end

		-- 高于系统最高单笔手数，则调整为最高单笔手数
		if nFollowCount > g_nMaxSingleCount[nServerGroup] then
			print('reduced follow count from '..nFollowCount..' to '..g_nMaxSingleCount[nServerGroup]..' by single max count');
			nFollowCount = g_nMaxSingleCount[nServerGroup] - math.random(0, 5);
		end

		if nFollowCount > 0 then

			-- 小于最大可忽略跟单数，则随机放弃跟单
			if nFollowCount < PriceConfig.nIgnoreCount then
				if math.random() < PriceConfig.fIgnoreChance then
					print('ignore price '..PriceInfo.nPrice..' count '..nFollowCount);
					return
				end
			end

			-- 下单
			local nResult = 0;
			g_ExchangeMgr:AddSystemOrder(0, nServerGroup, PriceInfo.nPrice, nFollowCount, false, nResult);
			print('added system order price '..PriceInfo.nPrice..' count '..nFollowCount..
				' ('..nMinFollowCount..', '..nMaxFollowCount..') '..' group '..nServerGroup..
				' percent '.. fCountPercent..' avg '..nAverageDelay);
		end
	end
end

function get_average_delay(nServerGroup, CurrentTime)
	local nOrderTotal = 1;
	for k,v in pairs(g_UserOrderList[nServerGroup]) do
		if (CurrentTime - k) > ORDER_STAT_DURATION then
			g_UserOrderList[nServerGroup][k] = nil;
		else
			nOrderTotal = nOrderTotal + v;
		end
	end
	return math.ceil(ORDER_STAT_DURATION / nOrderTotal);
end

-- 处理主动单
function ProcessActiveOrder(nServerGroup, nAverageDelay)
	local BuyPriceList = get_price_list(nServerGroup, eotBuy);

	-- 没有买一的盘口，则不处理	
	if BuyPriceList[1] == nil then
		print('no buy order');
		return
	end

	-- 买一盘口手数小于最小单数，则不处理
	if BuyPriceList[1].nHandCount < ActiveConfig.nMinCount then
		print('too few buy order hand count');
		return
	end 

	-- 低于系统最低限价，或者高于系统最低限价，则返回
	if BuyPriceList[1].nPrice < g_nLowPriceLimit[nServerGroup] or BuyPriceList[1].nPrice > g_nHighPriceLimit[nServerGroup] then
		print('too low or too high price');
		return
	end

	-- 随机本次盘口比例
	local fPercent = math.random(ActiveConfig.fMin * 100, ActiveConfig.fMax * 100) / 100;
	local nFollowCount = math.floor(BuyPriceList[1].nHandCount * fPercent);

	-- 高于系统最高单笔手数，则调整为最高单笔手数
	if nFollowCount > g_nMaxSingleCount[nServerGroup] then
		print('reduced active order count from '..nFollowCount..' to '..g_nMaxSingleCount[nServerGroup]..' by single max count');
		nFollowCount = g_nMaxSingleCount[nServerGroup] - math.random(0, 5);
	end

	-- 高于主动单池的上限，则调整为上限
	local fOrderPercent = math.random(ActiveConfig.fMinOrderPercent * 100, ActiveConfig.fMaxOrderPercent * 100) / 100;
	local nMaxCount = math.floor(g_nActiveOrderCount[nServerGroup] * fOrderPercent);
	if nMaxCount < nFollowCount then
		print('reduce active order count from '.. nFollowCount..' to '..nMaxCount..' by max active order hand count');
		nFollowCount = nMaxCount;
	end

	-- 从累计的玩家主动单池中扣除
	g_nActiveOrderCount[nServerGroup] = g_nActiveOrderCount[nServerGroup] - math.floor(nFollowCount / fOrderPercent);
	if g_nActiveOrderCount[nServerGroup] < 0 then
		g_nActiveOrderCount[nServerGroup] = 0;
	end

	-- 下单
	if nFollowCount > 0 then
		local nResult = 0;
		g_ExchangeMgr:AddSystemOrder(0, nServerGroup, BuyPriceList[1].nPrice, nFollowCount, false, nResult);
		print('added active system order price '..BuyPriceList[1].nPrice..' count '..nFollowCount..
			' ('..fPercent..', '..fOrderPercent..', '..g_nActiveOrderCount[nServerGroup]..') '..' group '..nServerGroup..' avg '..nAverageDelay);
	end
end

-- 撮合后
function AfterMainLoop(nServerGroup)
	local CurrentTime = os.time();
	local PriceList = get_price_list(nServerGroup, eotSell);

	g_nHighPriceLimit[nServerGroup] = get_server_var(nServerGroup, esvtDefault, svtHighPrice);
	g_nLowPriceLimit[nServerGroup] = get_server_var(nServerGroup, esvtDefault, svtLowPrice);
	g_nMaxSingleCount[nServerGroup] = get_server_var(nServerGroup, esvtDefault, svtMaxSingleCount);
	g_nMaxCountPerPrice[nServerGroup] = get_server_var(nServerGroup, esvtDefault, svtMaxCountPerPrice);
	
	local nAverageDelay = get_average_delay(nServerGroup, CurrentTime);

	for i,v in ipairs(PriceList) do
		if ConfigList[i] then
			if ConfigList[i].bUseAvgDelay then
				if g_NextRefreshTimeList[i] + nAverageDelay <= CurrentTime then
					ProcessPrice(v, ConfigList[i], nServerGroup, nAverageDelay);
					g_NextRefreshTimeList[i] = CurrentTime + math.random(1, 5);
				end
			else
				if g_NextRefreshTimeList[i] <= CurrentTime then
					ProcessPrice(v, ConfigList[i], nServerGroup, nAverageDelay);
					g_NextRefreshTimeList[i] = CurrentTime + math.random(ConfigList[i].nMinRefreshTime, ConfigList[i].nMaxRefreshTime);
				end
			end
		end
	end

	local bActiveOrderEnabled = get_server_var(nServerGroup, esvtDefault, svtActiveOrderEnabled);
	if bActiveOrderEnabled > 0 then
		if g_nNextActiveOrderRefreshTime[nServerGroup] + nAverageDelay <= CurrentTime then
			ProcessActiveOrder(nServerGroup, nAverageDelay);
			g_nNextActiveOrderRefreshTime[nServerGroup] = CurrentTime + math.random(1, 5);
		end
	end
end

-- 用户下单后
function OnUserAddOrder(nRoleID, nServerGroup, nOrderType, nPrice, nCount)
	local CurrentTime = os.time();
	if nOrderType == eotSell and nRoleID > 0 then
		if g_UserOrderList[nServerGroup] == nil then
			g_UserOrderList[nServerGroup] = {};
		end
		if g_UserOrderList[nServerGroup][CurrentTime] then
			g_UserOrderList[nServerGroup][CurrentTime] = g_UserOrderList[nServerGroup][CurrentTime] + 1;
		else
			g_UserOrderList[nServerGroup][CurrentTime] = 1;
		end
	end
end

-- 成交后
function OnUserMakeDeal(nServerGroup, nSellerID, dwSellOrderTime, nBuyerID, dwBuyOrderTime, nPrice, nCount)
	local bActiveOrderEnabled = get_server_var(nServerGroup, esvtDefault, svtActiveOrderEnabled);
	
	if bActiveOrderEnabled > 0 then
		if dwSellOrderTime > dwBuyOrderTime and nSellerID > 0 then
			g_nActiveOrderCount[nServerGroup] = g_nActiveOrderCount[nServerGroup] + nCount;
			print('active order price '..nPrice..' count '..nCount..' total '..g_nActiveOrderCount[nServerGroup]);
		end
	else
		g_nActiveOrderCount[nServerGroup] = 0;
	end

end