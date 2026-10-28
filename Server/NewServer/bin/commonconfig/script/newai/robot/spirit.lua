Include("script/include/btnod.lua")

LoadPackage("spirit_def.pkg")
LoadPackage("spirit.pkg")
LoadPackage("role.pkg")
LoadPackage("money_def.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("item.pkg")
LoadPackage("robot_message_handler.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("gameworld.pkg")

g_RobotMessageHandler = CRobotMessageHandler:GetInstance();

function performance_spirit_exp_change(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end
	
	if role:GetSpirit():GetNextExp2PtsTime() > CGameWorld:GetInstance():GetGameTime() then
		g_RobotMessageHandler:DoSpiritChangeExp(role, true, false);
	else
	    local rand_value = math.random(1);
		if rand_value > 0 then
			g_RobotMessageHandler:DoSpiritChangeExp(role, true, true);			
		end
	end
	
	return brvSuccess;
end

function performance_spirit_add_air(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end

	g_RobotMessageHandler:DoSpiritAddAir(role, 0, 1);		
	
	return brvSuccess;	
end

function performance_spirit_move_air(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end
	
	local srcindex = -1;
	local tarindex = -1;
	
	for bagindex = 0, (role:GetSpirit():GetBagContainerSize() -1) do
		if role:GetSpirit():GetAir(sasbtBag, bagindex).nTemplateID ~= 0 and srcindex == -1 then
			srcindex = bagindex;
		elseif role:GetSpirit():GetAir(sasbtBag, bagindex).nTemplateID ~= 0 and tarindex == -1 then
			tarindex = bagindex;
		end
	end
	
	if srcindex ~= -1 and tarindex ~= -1 then
		g_RobotMessageHandler:DoSpiritMoveAir(role, sasbtBag, srcindex, sasbtBag, tarindex);	
	end
	
	return brvSuccess;		
end

function performance_spirit_merge_air(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end
	
	local srcindex = -1;
	local tarindex = -1;
	
	for bagindex = 0, (role:GetSpirit():GetBagContainerSize() -1) do
		if role:GetSpirit():GetAir(sasbtBag, bagindex).nTemplateID ~= 0 and srcindex == -1 then
			srcindex = bagindex;
		elseif role:GetSpirit():GetAir(sasbtBag, bagindex).nTemplateID ~= 0 and tarindex == -1 then
			tarindex = bagindex;
		end
	end
	
	if srcindex ~= -1 and tarindex ~= -1 then
		g_RobotMessageHandler:DoSpiritMoveAir(role, sasbtBag, srcindex, sasbtBag, 1);
		g_RobotMessageHandler:DoSpiritMergeAir(role, tarindex);		
	end
	
	return brvSuccess;
end

function performance_spirit_buy_air_slot(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end

	if role:GetSpirit():GetBagContainerSize() < MAX_AIRSEA_BAG_CONTAINER_SIZE then
		g_RobotMessageHandler:DoSpiritBuyAirSlot(role, sasbtBag, 1);
	elseif role:GetSpirit():GetStallContainerSize() < MAX_AIRSEA_STALL_CONTAINER_SIZE then
		g_RobotMessageHandler:DoSpiritBuyAirSlot(role, sasbtStall, 1);
	elseif role:GetSpirit():GetEquipContainerSize() < MAX_AIRSEA_EQUIP_CONTAINER_SIZE then
		g_RobotMessageHandler:DoSpiritBuyAirSlot(role, sasbtEquip, 1);
	end
	
	return brvSuccess;	
end

function performance_spirit_exchange_air(owner)
	
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end
	
	g_RobotMessageHandler:DoSpiritExchangeAir(role, 101);	
		
	return brvSuccess;	
end

function performance_spirit_open_blood(owner)
	
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	
	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end
	
	local bloodpage = -1;
	
	for page = 0, MAX_BLOODSEA_PAGE-1 do
		print '-----------'
		print(page)
		if role:GetSpirit():IsBloodOpen(page+1) == 0 then
			bloodpage = page;
			break;
		end	
	end
	
	g_RobotMessageHandler:DoSpiritOpenBlood(role, bloodpage);

	return brvSuccess;	
end

function performance_spirit_brush_slot(owner)
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());

	if role:GetLevel() < SPIRIT_OPEN_LEVEL then
		return brvSuccess;
	end

	user:GMCommand("addmoney 10 10000");

	for page = 1, MAX_BLOODSEA_PAGE do
		if role:GetSpirit():IsBloodOpen(page) then
			for index = 1, MAX_BLOODSEA_SLOT_NUMBER do
				if role:GetSpirit():GetBlood(page-1, index-1) ~= 10 then
					g_RobotMessageHandler:DoSpiritBrushSlot(role, page, index);
				end
			end
		end	
	end

	return brvSuccess;	
end


















