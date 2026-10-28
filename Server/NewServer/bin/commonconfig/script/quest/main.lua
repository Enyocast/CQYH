LoadPackage("master.pkg");
LoadPackage("role.pkg");
LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("npc.pkg");
LoadPackage("npc_def.pkg");
LoadPackage("quest_list.pkg");
LoadPackage("id_def.pkg");
LoadPackage("character.pkg");
LoadPackage("guild_def.pkg");
LoadPackage("guild_mgr.pkg");
LoadPackage("gs_guild.pkg");
LoadPackage("math_ex.pkg");
LoadPackage("gs_team.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("money_def.pkg");
LoadPackage("char_def.pkg");
LoadPackage("error_def.pkg");
LoadPackage("chat_def.pkg");
LoadPackage("ai.pkg");

Include("script/include/escort.lh")

function Master(cRole)
	call_ms_func("script/master/main.lua", "MakeOneToBeMaster", cRole:GetObjID(), 0, 0);
end

function QuestAddGuildMoney(cRole)
    if cRole:GetGuildID() ~= 0 then
		call_ms_func("script/guild/main.lua", "AddGuildResource", cRole:GetGuildID(), GUILD_ATTR_MONEY, 100, GUILD_CHEST_TASK);
	end
end

function convert(pos)
	pos.x, pos.y, pos.z = ConvertCoordO2N(pos.x, pos.y, pos.z);
end

-- Get coordinates relative to the current player
function _GetRelativeCoord(nSrcX, nSrcY, nFaceDirection, nOffsetX, nOffsetY)
	local Direction = nFaceDirection * 2 * math.pi / MAX_DIRECTION_COUNT;
	local nX = nSrcX + nOffsetX * math.sin(Direction) + nOffsetY * math.cos(Direction);
	local nY = nSrcY + nOffsetX * math.cos(Direction) + nOffsetY * math.sin(Direction);
	return nX, nY;
end

function SummonNpc6212(cRole)
	local oScene = cRole:GetScene();
    local oNpc = oScene:SpawnNpc(6212, cRole:GetLevel(), 1, cRole:GetX(), cRole:GetY(), cRole:GetZ() + GRID_WIDTH, cRole:GetFaceDirection(), cRole:GetObjID(), nil);
	local oacceptedquest = cRole:GetQuestList():GetAcceptedQuest(283);
	cRole:GetQuestList():SetVariable(oacceptedquest, 3, oNpc:GetObjID());
	return oNpc;
end

function KillNpc6212(cRole)
	local oQuestList = cRole:GetQuestList();
	local oAcceptedQuest = oQuestList:GetAcceptedQuest(283);
	local npcid = oQuestList:GetVariable(oAcceptedQuest, 3);
	local oNpc = CGameWorld:GetInstance():FindNpc(npcid);
	if (not oNpc) then
		return nil;
	end

	return oNpc:Die(0);
end

function PreCheckIsCanGetMasterTask(cRole)

	if cRole:GetLevel() < GRADUATE_LEVEL then
		return 0;
	end

	if cRole:GetMaster() ~= nil then
		if cRole:GetMaster():GetState() == MASTER_NONE then
			return 1;
		end
	end

	return 0;

	--if cRole:GetMaster():GetMasterID() == 0 then
	--	-- no master
	--	if cRole:GetLevel() > (GRADUATE_LEVEL - 1) then
	--		return 1;
	--	else
	--		return 0;
	--	end
	--else
	--	-- have master
	--	if cRole:GetMaster():GetSelfMstState() == MASTER_STATE_GRADUATED then
	--		return 1;
	--	else
	--		return 0;
	--	end
	--end

end



function WarDg01_SummonBigBrother(cRole)
		--local InterActNpcId = cRole:GetInteractNpc();
		--local oNpc = CGameWorld:GetInstance():FindNpc(npcid);
		--if (not oNpc) then
		--return nil;
		--end

		--oNpc:Die(0);

		--local oScene = cRole:GetScene();
		--oScene:SetVariable(9, 1);
		--print ("woshishabi...");

		--return oScene:SpawnNpcMediumGroup(1);

		--return oNpc;--

		--local InterActNpcId = cRole:GetInteractNpc();
		--local oNpc = CGameWorld:GetInstance():FindNpc(InterActNpcId);
		--print oNpc:GetObjID();
		--if (not oNpc) then
		--return nil;
		--end

		--oNpc:Die(0);

		--local oScene = cRole:GetScene();
		--oScene:SetVariable(9, 2);
		--return oScene:SpawnNpcMediumGroup(1);
end

function RemoveAura(cRole)
	oAuraInstance = cRole:GetFirstAura(2500);
	if oAuraInstance then
		cRole:RemoveAura(oAuraInstance, true);
	end

end


function OpenJidaoCutscene(cRole)
	local InterActNpcId = cRole:GetInteractNpc();
	local oNpc = CGameWorld:GetInstance():FindNpc(InterActNpcId);
	--print oNpc:GetObjID();
	if (not oNpc) then
	return nil;
	end

	oNpc:Die(0);

	local oScene = cRole:GetScene();
	oScene:SetVariable(9, 2);

end

function CloseJidaoCutscene(cRole)
	local oScene = cRole:GetScene();
	oScene:SetVariable(9, 0);

end




---------------------------Boundary---------------------------

function Qst1441Cinematic(cRole)     --Trigger cinematic 1.2
	cRole:SetVariable(132, 1);
	--cRole:SetInCutScene(true, 50 * GAME_FPS);
end


function Qst1445Cinematic(cRole)     --Trigger cinematic 1.2
	local g_oGameWorld = CGameWorld:GetInstance();
	local oScene = cRole:GetScene();

	local pos = { x = 43664, y = 48270, z = 4477 };
	convert(pos);

	g_oGameWorld:JumpTo(cRole, cRole:GetSceneTempID(),cRole:GetSceneID(), 
		pos.x * POINT_PER_CM, pos.y * POINT_PER_CM, pos.z * POINT_PER_CM, cRole:GetFaceDirection());

	cRole:SetVariable(133, 1);
	cRole:SetInCutScene(true, 33 * GAME_FPS);
end


function Qst1454Cinematic(cRole)     --Trigger cinematic 1.3
	cRole:SetVariable(134, 1);
	cRole:SetInCutScene(true, 33 * GAME_FPS);
end


function Qst1456AcceptCinematic(cRole)     --Return to Border Village
	local g_oGameWorld = CGameWorld:GetInstance();
	local oScene = cRole:GetScene();

	local pos = { x = 25989, y = 56905, z = 4731 };
	convert(pos);

	g_oGameWorld:JumpTo(cRole, cRole:GetSceneTempID(),cRole:GetSceneID(), 
		pos.x * POINT_PER_CM, pos.y * POINT_PER_CM, pos.z * POINT_PER_CM, cRole:GetFaceDirection());
	
end

function Qst1456CompleteCinematic(cRole)     --Trigger cinematic 1.4
	cRole:SetVariable(135, 1);
	cRole:SetInCutScene(true, 50 * GAME_FPS);
end


---------------------------------------------------------------

function Qst1480Cinematic(cRole)     --Trigger cinematic 2.1
	cRole:SetVariable(122, 1);
	cRole:SetInCutScene(true, 55 * GAME_FPS);
	--Change scene variable on quest acceptance
	local oScene = cRole:GetScene();
	oScene:SetVariable(1, 2);
end

function Qst1481Cinematic(cRole)     --Trigger cinematic 2.2
	-- cRole:SetVariable(123, 1);	--Teleport player: 43,70732,55859,43754

	local g_oGameWorld = CGameWorld:GetInstance();
	local oScene = cRole:GetScene();

	local pos = { x = 70732, y = 55859, z = 43754 };
	convert(pos);

	g_oGameWorld:JumpTo(cRole, cRole:GetSceneTempID(),cRole:GetSceneID(), 
		pos.x * POINT_PER_CM, pos.y * POINT_PER_CM, pos.z * POINT_PER_CM, cRole:GetFaceDirection());

	cRole:SetVariable(123, 1);
	cRole:SetInCutScene(true, 50 * GAME_FPS);

end

function Qst1482Cinematic(cRole)     --Trigger cinematic 2.3
	cRole:SetVariable(124, 1);
	cRole:SetInCutScene(true, 39 * GAME_FPS);

end


function Qst1511Cinematic(cRole)     --Trigger cinematic 2.3-b
	cRole:SetVariable(140, 1);
	cRole:SetInCutScene(true, 45 * GAME_FPS);

end

function Qst1522Cinematic(cRole)     --Trigger cinematic 2.4
	cRole:SetVariable(125, 1);
	cRole:SetInCutScene(true, 36 * GAME_FPS);

end

function Qst1524Cinematic(cRole)     --Trigger cinematic 2.5
	cRole:SetVariable(126, 1);
	cRole:SetInCutScene(true, 20 * GAME_FPS);

end

function Qst1527Cinematic(cRole)     --Trigger cinematic 2.6
	cRole:SetVariable(127, 1);
	cRole:SetInCutScene(true, 29 * GAME_FPS);

end

function Qst1531Cinematic(cRole)     --Enable the character variable for opening the door
	cRole:SetVariable(131, 1);

end


function Qst1532Cinematic(cRole)     --Trigger cinematic 2.8
	cRole:SetVariable(128, 1);
	cRole:SetVariable(131, 0);	--Clear the character variable for opening the door
	cRole:SetInCutScene(true, 42 * GAME_FPS);

end


-----------------------------New Bichon content----------------------------------
function Qst1510Cinematic(cRole)     --Trigger cinematic 1-2-4
	cRole:SetVariable(161, 1);
	cRole:SetInCutScene(true, 86 * GAME_FPS);
	local oScene = cRole:GetScene();
	oScene:SetVariable(2, 1);
end
-----------------------------Woma Forest----------------------------------
function Qst1560Cinematic(cRole)     --Trigger cinematic 1-2-5
	cRole:SetVariable(162, 1);
	cRole:SetInCutScene(true, 20 * GAME_FPS);

end

function Qst1561Cinematic(cRole)     --Trigger cinematic 1-2-6
	local g_oGameWorld = CGameWorld:GetInstance();
	local oScene = cRole:GetScene();

	local pos = { x = 58208, y = 42336, z = 12672 };
	convert(pos);

	g_oGameWorld:JumpTo(cRole, cRole:GetSceneTempID(),cRole:GetSceneID(), 
		pos.x * POINT_PER_CM, pos.y * POINT_PER_CM, pos.z * POINT_PER_CM, cRole:GetFaceDirection());

	cRole:SetVariable(163, 1);
	cRole:SetInCutScene(true, 94 * GAME_FPS);

end
-----------------------------Mengzhong----------------------------------
function Qst1645Cinematic(cRole)     --Trigger cinematic 2-1-1
	cRole:SetVariable(164, 1);
	cRole:SetInCutScene(true, 21 * GAME_FPS);

end

function Qst1648Cinematic(cRole)     --Trigger cinematic 2-1-2
	cRole:SetVariable(165, 1);
	cRole:SetInCutScene(true, 23 * GAME_FPS);

end
-----------------------------Woma Temple----------------------------------
function Qst1602Cinematic(cRole)     --Trigger cinematic 3-2-1
	cRole:SetVariable(166, 1);
	cRole:SetInCutScene(true, 19 * GAME_FPS);

end

function Qst1605Cinematic(cRole)     --Trigger cinematic 3-2-2
	cRole:SetVariable(167, 1);
	cRole:SetInCutScene(true, 28 * GAME_FPS);

end

function Qst1607Cinematic(cRole)     --Trigger cinematic 3-2-3
	cRole:SetVariable(168, 1);
	cRole:SetInCutScene(true, 33 * GAME_FPS);

end
-----------------------------Death Canyon----------------------------------
function Qst1656Cinematic(cRole)     --Trigger cinematic 4-1-1
	cRole:SetVariable(169, 1);
	cRole:SetInCutScene(true, 19 * GAME_FPS);

end

function Qst1682Cinematic(cRole)     --Trigger cinematic 4-1-2
	cRole:SetVariable(170, 1);
	cRole:SetInCutScene(true, 15 * GAME_FPS);

end

function Qst1684Cinematic(cRole)     --Trigger cinematic 4-1-3
	cRole:SetVariable(171, 1);
	cRole:SetInCutScene(true, 29 * GAME_FPS);

end

function Qst1685Cinematic(cRole)     --Trigger cinematic 4-1-4
	cRole:SetVariable(172, 1);
	cRole:SetInCutScene(true, 29 * GAME_FPS);

end
-----------------------------Stone Tomb----------------------------------
function Qst1654Cinematic(cRole)     --Trigger cinematic 4-2-1
	cRole:SetVariable(173, 1);
	cRole:SetInCutScene(true, 46 * GAME_FPS);

end

function Qst1720Cinematic(cRole)     --Trigger cinematic 4-2-2
	local g_oGameWorld = CGameWorld:GetInstance();
	local oScene = cRole:GetScene();

	local pos = { x = 30625, y = 41770, z = 7360 };
	convert(pos);

	g_oGameWorld:JumpTo(cRole, cRole:GetSceneTempID(),cRole:GetSceneID(), 
		pos.x * POINT_PER_CM, pos.y * POINT_PER_CM, pos.z * POINT_PER_CM, cRole:GetFaceDirection());
	cRole:SetVariable(174, 1);
	cRole:SetInCutScene(true, 59 * GAME_FPS);

end

function Qst1723Cinematic(cRole)     --Trigger cinematic 4-2-3
	cRole:SetVariable(175, 1);
	cRole:SetInCutScene(true, 19 * GAME_FPS);

end

function Qst1726Cinematic(cRole)     --Trigger cinematic 4-2-4
	cRole:SetVariable(176, 1);
	cRole:SetInCutScene(true, 39 * GAME_FPS);

end


function Qst1455Sence(cRole)     --Complete quest 1455
	cRole:SetVariable(177, 1);
end




function Qst1485Sence(cRole)     --Change scene 143 variable 3
	local oScene = cRole:GetScene();
	oScene:SetVariable(3, 1);

end

function Qst1486Sence(cRole)     --Change scene 144 variable 1
	local oScene = cRole:GetScene();
	oScene:SetVariable(1, 1);

end




function CheckTeamMaster(cRole)

	local oMaster =  cRole:GetMaster();
	if not oMaster or oMaster:GetTeacherID() == 0 then
		return 1;
	end

	local cTeacher = CGameWorld:GetInstance():FindRole(oMaster:GetTeacherID());
	if not cTeacher and cTeacher:GetSceneID() ~= cRole:GetSceneID() then
		return 1;
	end

	local oTeam = CGameWorld:GetInstance():FindTeam(cRole:GetTeamID());
	if cRole:GetTeamID() == 0 or not oTeam then
		return 1;
	end

	for memberindex = 0, (oTeam:GetMemberCount()-1) do
		local oMember = oTeam:GetMemberTable(memberindex);
		if oMember.dwRoleID == oMaster:GetTeacherID() then
			cRole:AddExp(100, false, true);
			local oItembag = cTeacher:GetItemBag();
			oItembag:AddMoney(MONEYTYPE_MORAL, 50, MONEYLOG_SCRIPT, 0, 0);	--MONEYTYPE_MORAL
			return 1;
		end
	end
end

function beforeAcceptQst_2049(cRole)

    local timezone = CGameWorld:GetInstance():GetTimeZone();
    local gametime = CGameWorld:GetInstance():GetGameTime();

    local oldDay = 0;
	local today = math.ceil((gametime + timezone) / 86400);
	
	--Check character level
	local level = cRole:GetLevel();
    if level < 20 then
        return errGuildEscortLevelNotEnough;
    end
	
	--Check guild membership
	local guild = CGuildMgr:GetInstance():FindGuild(cRole:GetGuildID());
    if guild == nil then
        return errGuildNotMember;
    end
    
    local guildBuildingData = guild:GetFunBuildingDataByType(GUILD_B_BUSINESS);
    if guildBuildingData == nil or guildBuildingData.nLevel <= 0 then
        return errGuildBuildingNpcIDError;
    end

	--Check whether an escort quest was already accepted today
	local roleVariable = cRole:GetVariable(VAR_ROLE_LAST_ESCORT_TIME);
	local oldAcceptDay = math.ceil((roleVariable + timezone) / 86400);
    if oldAcceptDay == today then
        return errGuildTodayAlreadyAcceptEscort;
    end
    local guildBusinessLevel = guildBuildingData.nLevel;

    --Check whether the guild has enabled escort
    local bEscortActivityOpen = guild:IsActivityOpen(ESCORT_ACTIVITY_ID);
    if not bEscortActivityOpen then
        return errGuildTodayNotOpenEscort;
    end

	local car_info;
	--Check escort document
	if cRole:GetItemBag():GetItemCount(ESCORT_ACCEPT_BASE_ITEM_A) > 0 then
		    car_info = random_car_info(ESCORT_ACCEPT_BASE_ITEM_A);
	elseif cRole:GetItemBag():GetItemCount(ESCORT_ACCEPT_BASE_ITEM_S) > 0 then
		    car_info = random_car_info(ESCORT_ACCEPT_BASE_ITEM_S);
	elseif cRole:GetItemBag():GetItemCount(ESCORT_ACCEPT_BASE_ITEM_SS) > 0 then
		    car_info = random_car_info(ESCORT_ACCEPT_BASE_ITEM_SS);
	else
		return errGuildNoItem;
	end
    --Preselect the escort cart template ID

    if not car_info then
        return errUnknownError;
    end

    --Check gold
    local accept_money_cost = cal_accept_escort_cost(car_info.accept_base_money_cost, guildBusinessLevel);
    if cRole:GetItemBag():GetMoney(MONEYTYPE_02) < accept_money_cost then
        return errItemNotEnoughMoneytype02;
    end

    --Check guild contribution
    local accept_bg_cost = cal_accept_escort_cost(car_info.accept_base_bg_cost, guildBusinessLevel);
    if cRole:GetItemBag():GetMoney(MONEYTYPE_GUILD) < accept_bg_cost then
        return errGuildNotEnoughContribution;
    end


    -- Set the cart template ID and commerce hall level at acceptance
	cRole:SetVariable(VAR_ROLE_ESCORT_CAR_TEMP_ID, car_info.id);
	cRole:SetVariable(VAR_ROLE_ESCORT_BUSINESS_LEVEL, guildBusinessLevel);
    
    return errSuccess;
end

function afterAcceptQst_2049(cRole)

    local guildBusinessLevel = cRole:GetVariable(VAR_ROLE_ESCORT_BUSINESS_LEVEL);
    local car_info = find_escort_car_info(cRole:GetVariable(VAR_ROLE_ESCORT_CAR_TEMP_ID));
    if not car_info then
        print("afterAcceptQst_2049 find_escort_car_info nil " .. cRole:GetName() .. "@" ..  cRole:GetObjID());
        return;
    end

    --Deduct escort cost
    local accept_money_cost = cal_accept_escort_cost(car_info.accept_base_money_cost, guildBusinessLevel);
    local accept_bg_cost = cal_accept_escort_cost(car_info.accept_base_bg_cost, guildBusinessLevel);
    if errSuccess ~= cRole:GetItemBag():SubMoney(MONEYTYPE_02, accept_money_cost, MONEYLOG_ESCORT, 0, 0) then
        print("afterAcceptQst_2049 SubMoney accept_money_cost=" .. accept_money_cost .. " fail " .. cRole:GetName() .. "@" ..  cRole:GetObjID());
        return;
    end
    if errSuccess ~= cRole:GetItemBag():SubMoney(MONEYTYPE_GUILD, accept_bg_cost, MONEYLOG_ESCORT, 0, 0) then
        print("afterAcceptQst_2049 SubMoney accept_bg_cost=" .. accept_bg_cost .. " fail " .. cRole:GetName() .. "@" ..  cRole:GetObjID());
        return;
    end
    if errSuccess ~= cRole:GetItemBag():DeleteItemId(car_info.accept_base_item_id, 1, ITEMLOG_COMPLETE_QUEST, 0, 0) then
        print("afterAcceptQst_2049 DelItem accept_base_item_id fail" .. cRole:GetName() .. "@" ..  cRole:GetObjID());
        return;
    end

    --Spawn escort cart
	local escort_car = cRole:GetScene():SpawnNpc(car_info.id, cRole:GetX(), cRole:GetY(), cRole:GetZ(), cRole:GetFaceDirection(), cRole:GetObjID(), NULL);
	escort_car:GetAIProcessor():SetFollowParam(cRole:GetObjID(), 0, ESCORT_FOLLOW_Y_POS, FALSE);
    escort_car:SetAlwaysRun(true);
    escort_car:GetAIProcessor():SetVariable(VAR_AI_ESCORT_BUSINESS_LEVEL, guildBusinessLevel);
    
    print(cRole:GetObjID() .. "@" .. cRole:GetName() .. "@" .. escort_car:GetObjID() .. "@" .. car_info.id .. ": "
            .. "accept_money_cost=" .. accept_money_cost .. ", car_info.accept_base_money_cost=" .. car_info.accept_base_money_cost
            .. ", accept_bg_cost=" .. accept_bg_cost .. ", car_info.accept_base_bg_cost=" .. car_info.accept_base_bg_cost 
            .. ", guildBusinessLevel=" .. guildBusinessLevel);
   
    --Set variable
	cRole:SetVariable(VAR_ROLE_LAST_ESCORT_TIME, CGameWorld:GetInstance():GetGameTime());
	cRole:SetVariable(VAR_ROLE_ESCORT_CAR_ID, escort_car:GetObjID());
    
end

function beforeCompleteQst_2049(cRole)

    return errSuccess;
end

function afterCompleteQst_2049(cRole)
    
    local guildBusinessLevel = cRole:GetVariable(VAR_ROLE_ESCORT_BUSINESS_LEVEL);
    local car_info = find_escort_car_info(cRole:GetVariable(VAR_ROLE_ESCORT_CAR_TEMP_ID));
    if not car_info then
        print("afterCompleteQst_2049 find_escort_car_info nil " .. cRole:GetName() .. "@" ..  cRole:GetObjID());
        return;
    end
    
    -- Grant reward
	local accept_money_cost = cal_accept_escort_cost(car_info.accept_base_money_cost, guildBusinessLevel);
	local award_money = car_info.award_multi * accept_money_cost;

	cRole:GetItemBag():AddMoney(MONEYTYPE_02, award_money, MONEYLOG_ESCORT, 0, 0);
	cRole:GetItemBag():AddItem(car_info.award_item, car_info.award_multi - 1, ITEMLOG_COMPLETE_QUEST, 0, 0);
 
end