LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("char_def.pkg")
LoadPackage("character.pkg")
LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage("arena.pkg")
LoadPackage("money_def.pkg")
LoadPackage("scene.pkg")
LoadPackage("global_config.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("rank_list_def.pkg")

ET_ONLY_ONE_ROLE = 1;
ET_LEAVE_SCENE = 2;
ET_TIMEOUT	= 3;
ET_ROLE_DIE	= 4;




function GetCurrentTime(owner)
	return CGameWorld:GetInstance():GetGameTime();
end

function GetRoleID(owner)
	return get_ctx_role_id();
end

function SyncCountdown(scene)

	local 	role = CGameWorld:GetInstance():FindRole(get_ctx_role_id());


	local 	counttime = scene:GetVariable(AMVI_JJC_BEGIN_TIME) - os.time();
	if counttime > 0 then
		role:GetArena():SyncCountdown(0, counttime);
	end

end


function AddScore(role, moneycount)

	local arenatime = role:GetArena():GetArenaScoreTime();

	local old_month = os.date("%m", arenatime);
	local new_month = os.date("%m", os.time());

	if old_month == new_month then
		role:GetItemBag():AddMoney(MONEYTYPE_ARENA, moneycount, MONEYLOG_ARENA_REWARD, 0, 0);
	else
		role:GetItemBag():SetMoney(MONEYTYPE_ARENA, 0);
		role:GetItemBag():AddMoney(MONEYTYPE_ARENA, moneycount, MONEYLOG_ARENA_REWARD, 0, 0);
	end

	local  ranklisttype = 0;

	if role:GetClass() == clsWarrior then
		ranklisttype = rlArena1v1Warrior;
	elseif role:GetClass() == clsMage then
		ranklisttype = rlArena1v1Mage;
	elseif role:GetClass() == clsTaoist then
		ranklisttype = rlArena1v1Taoist;
	end

	if ranklisttype ~= 0 then
		role:UpdateRankListNode(ranklisttype, 0, role:GetItemBag():GetMoney(MONEYTYPE_ARENA));
	end

	role:UpdateRankListNode(rlArena1v1, 0, role:GetItemBag():GetMoney(MONEYTYPE_ARENA));
	role:GetArena():SetArenaScoreTime(os.time());
end



function JJCEnd(scene, end_type)

	--print("end type:"..end_type);

	if end_type == ET_ONLY_ONE_ROLE then
		if scene:GetVariable(AMVI_JJC_ROLE_ID_1) > 0 then
			CalcScore(scene, scene:GetVariable(AMVI_JJC_ROLE_ID_1), 0);
		else
			--
		end

	elseif end_type == ET_LEAVE_SCENE or end_type == ET_ROLE_DIE then

		local win_role_id = 0;
		local defeat_role_id = get_ctx_role_id();

		--print("defeat role "..defeat_role_id);

		if scene:GetVariable(AMVI_JJC_ROLE_ID_1) == defeat_role_id then
			win_role_id = scene:GetVariable(AMVI_JJC_ROLE_ID_2);
		else
			win_role_id = scene:GetVariable(AMVI_JJC_ROLE_ID_1);
		end

		CalcScore(scene, win_role_id, defeat_role_id);

	elseif end_type == ET_TIMEOUT then
		local role_id_1 = scene:GetVariable(AMVI_JJC_ROLE_ID_1);
		local role_id_2 = scene:GetVariable(AMVI_JJC_ROLE_ID_2);

		local role_dmg_1 = scene:GetRoleCombatStatValue(role_id_1, escsTotalDamage);
		local role_dmg_2 = scene:GetRoleCombatStatValue(role_id_2, escsTotalDamage);

		if role_dmg_1 > role_dmg_2 then

			CalcScore(scene, role_id_1, role_id_2);

		elseif role_dmg_1 < role_dmg_2 then
			CalcScore(scene, role_id_2, role_id_1);
		else
			NoWinCalcScore(scene, role_id_1, role_id_2);
		end
	end

	return brvSuccess;
end


function GetWinReward(b_reward, scene, role, dRole, target_role_level)

	local reward = 0;
	local score = 0;
	local dmg = scene:GetRoleCombatStatValue(role:GetObjID(), escsTotalDamage);

	local MoneyDmg = dmg;

	local maxMoneyDmg = target_role_level * 10 + 800;

	if dmg < 100 then
		MoneyDmg = 100;
	elseif dmg > maxMoneyDmg then
		MoneyDmg = maxMoneyDmg;
	end

	--print("dmg "..dmg.." maxScoreDmg "..maxScoreDmg.." score dmg "..scoreDmg.." MOneyDmg "..MoneyDmg);


	----------------------------------------------------------------
	local hurt = 0;
	local scoreDmg = dmg;
	local fightTime = os.time() - scene:GetVariable(AMVI_JJC_BEGIN_TIME);
	local scoreCoef = 0;

	if dRole ~= nil then
		hurt = scene:GetRoleCombatStatValue(dRole:GetObjID(), escsTotalDamage);
	end

	if hurt < 100 then
		hurt = 100;
	elseif hurt > (target_role_level * 10 + 800) then
		hurt = target_role_level * 10 + 800;
	end

	if dmg < 100 then
		scoreDmg = 100;
	elseif dmg > (target_role_level * 10 + 800) then
		scoreDmg = target_role_level * 10 + 800;
	end

	if fightTime < 60 then
		fightTime = 60;
	elseif fightTime > 180 then
		fightTime = 180;
	end

	if dRole == nil then
		scoreCoef = 0 - role:GetItemBag():GetMoney(MONEYTYPE_ARENA);
	else
		scoreCoef = dRole:GetItemBag():GetMoney(MONEYTYPE_ARENA) - role:GetItemBag():GetMoney(MONEYTYPE_ARENA);
	end

	if scoreCoef < -2000 then
		scoreCoef = -2000;
	elseif scoreCoef > 2000 then
		scoreCoef = 2000;
	end

	score = 2 * target_role_level * ( 1 + 0.01 * scoreDmg / fightTime + 0.005 * hurt / fightTime + 0.0001 * scoreCoef);

	----------------------------------------------------------------

	if b_reward == true then
		reward = math.sqrt(target_role_level) * math.sqrt(MoneyDmg) * 4000 / 10000;
		--score = target_role_level * scoreDmg / 666;

		if reward >= 1 then
			role:GetItemBag():AddMoney(MONEYTYPE_03, reward, MONEYLOG_ARENA_REWARD, 0, 0);
			print("arena: win role "..role:GetObjID().." add money "..reward);
		end

		if score >= 1 then
			AddScore(role, score);
			print("arena: win role "..role:GetObjID().." add score "..score);
		end

		role:AddActivityPts(25, aprYanWuChang);
	else
		reward = 0;
		score = 0;
	end

	return dmg, reward, score;
end

function GetDefeatReward(b_reward, scene, role, wRole, target_role_level)

	local reward = 0;
	local dmg = scene:GetRoleCombatStatValue(role:GetObjID(), escsTotalDamage);
	local MoneyDmg = dmg;

	local maxMoneyDmg = target_role_level * 10 + 800;

	if dmg < 100 then
		MoneyDmg = 100;
	elseif dmg > maxMoneyDmg then
		MoneyDmg = maxMoneyDmg;
	end

	----------------------------------------------------------------------
	local hurt = 0;
	local scoreDmg = dmg;
	local fightTime = os.time() - scene:GetVariable(AMVI_JJC_BEGIN_TIME);
	local scoreCoef = 0;

	if wRole ~= nil then
		hurt = scene:GetRoleCombatStatValue(wRole:GetObjID(), escsTotalDamage);
	end

	if hurt < 100 then
		hurt = 100;
	elseif hurt > (target_role_level * 10 + 800) then
		hurt = target_role_level * 10 + 800;
	end

	if dmg < 100 then
		scoreDmg = 100;
	elseif dmg > (target_role_level * 10 + 800) then
		scoreDmg = target_role_level * 10 + 800;
	end

	if fightTime < 60 then
		fightTime = 60;
	elseif fightTime > 180 then
		fightTime = 180;
	end

	if wRole == nil then
		scoreCoef = 0 - role:GetItemBag():GetMoney(MONEYTYPE_ARENA);
	else
		scoreCoef = wRole:GetItemBag():GetMoney(MONEYTYPE_ARENA) - role:GetItemBag():GetMoney(MONEYTYPE_ARENA);
	end

	if scoreCoef < -2000 then
		scoreCoef = -2000;
	elseif scoreCoef > 2000 then
		scoreCoef = 2000;
	end

	score = 0.2 * target_role_level * ( 1 + 0.01 * scoreDmg / fightTime + 0.005 * hurt / fightTime + 0.0001 * scoreCoef);

	----------------------------------------------------------------------

	if b_reward == true then
		reward = math.sqrt(target_role_level) * math.sqrt(MoneyDmg) * 2000 / 10000;
		--score = target_role_level * scoreDmg / 5000;

		if reward >= 1 then
			role:GetItemBag():AddMoney(MONEYTYPE_03, reward, MONEYLOG_ARENA_REWARD, 0, 0);
			print("arena: defeat role "..role:GetObjID().." add money "..reward);
		end

		if score >= 1 then
			AddScore(role, score);
			print("arena: defeat role "..role:GetObjID().." add score "..score);
		end

		role:AddActivityPts(5, aprYanWuChang);
	else
		reward = 0;
		score = 0;
	end

	return dmg, reward, score;
end



function CalcScore(scene, win_role_id, defeat_role_id)
	local wRole = nil;
	local dRole = nil;
	local dmg = 0;
	local reward = 0;
	local score = 0;
	local bReward = false;

	wRole = CGameWorld:GetInstance():FindRole(win_role_id);

	if wRole:GetVariable(196) < 5 then
		wRole:SetVariable(196, wRole:GetVariable(196) + 1);
	end

	if defeat_role_id > 0 then
		dRole = CGameWorld:GetInstance():FindRole(defeat_role_id);
	end

	local wLevel = wRole:GetLevel();
	local dLevel = 0;
	if dRole == nil then
		dLevel = wLevel;
	else
		dLevel = dRole:GetLevel();
	end

	-- reward win
	if wRole:GetVariable(195) < 6 then
		bReward = true;
	end

	dmg, reward, score = GetWinReward(bReward, scene, wRole, dRole, dLevel);
	wRole:GetArena():SyncArenaResToClient(ARENA_RES_WIN, scene:GetVariable(AMVI_JJC_BEGIN_TIME), dmg, reward, score);

	SendAddTicketsToMS(wRole:GetObjID());

	-- reward defeat
	dmg = 0;
	reward = 0;
	score = 0;
	bReward = false;

	if dRole ~= nil then
		if dRole:GetVariable(195) < 6 then
			bReward = true;
		end

		dmg, reward, score = GetDefeatReward(bReward, scene, dRole, wRole, wLevel);
		dRole:GetArena():SyncArenaResToClient(ARENA_RES_DEFEAT, scene:GetVariable(AMVI_JJC_BEGIN_TIME), dmg, reward, score);

		print("arena: role "..win_role_id.." and defeat role "..defeat_role_id);
	else
		print("arena: role "..win_role_id.." win with no competitor");
	end
end

function NoWinCalcScore(scene, role_id_1, role_id_2)
	local role_1 = nil;
	local role_2 = nil;
	local b_reward = false;

	local dmg = 0;
	local reward = 0;


	role_1 = CGameWorld:GetInstance():FindRole(role_id_1);
	role_2 = CGameWorld:GetInstance():FindRole(role_id_2);

	-- reward
	if role_1:GetVariable(195) < 6 then
		b_reward = true;
	end

	dmg, reward, score = GetDefeatReward(b_reward, scene, role_1, role_2, role_2:GetLevel());
	role_1:GetArena():SyncArenaResToClient(ARENA_RES_TIE, scene:GetVariable(AMVI_JJC_BEGIN_TIME), dmg, reward, score);

	--print(""..dmg.." "..reward);

	-- reward
	dmg = 0;
	reward = 0;
	score = 0;
	b_reward = false;

	if role_2:GetVariable(195) < 6 then
		b_reward = true;
	end

	dmg, reward, score = GetDefeatReward(b_reward, scene, role_2, role_1, role_1:GetLevel());
	role_2:GetArena():SyncArenaResToClient(ARENA_RES_TIE, scene:GetVariable(AMVI_JJC_BEGIN_TIME), dmg, reward, score);


	print("arena: role "..role_id_1.." and role "..role_id_2.."draw this match");

	--print(""..dmg.." "..reward);
end





function CanUseItem( scene, item, role )

	if item.m_pTemplate.m_bySubType == ITEMSUBTYPE_USABLE_POTION then
		if role:GetObjID() == scene:GetVariable(AMVI_JJC_ROLE_ID_1) then
			if scene:GetVariable(AMVI_JJC_POTION_STAT_1) < 12 then
				return errSuccess;
			else
				return errArenaUseItemLimit;
			end
		elseif role:GetObjID() == scene:GetVariable(AMVI_JJC_ROLE_ID_2) then
			if scene:GetVariable(AMVI_JJC_POTION_STAT_2) < 12 then
				return errSuccess;
			else
				return errArenaUseItemLimit;
			end
		else
			return errArenaCannotUseItem;
		end
	end

	return errSuccess;
end


function UseItemSuccess( scene, item, role )

	if item.m_pTemplate.m_bySubType == ITEMSUBTYPE_USABLE_POTION then
		if role:GetObjID() == scene:GetVariable(AMVI_JJC_ROLE_ID_1) then
			scene:SetVariable(AMVI_JJC_POTION_STAT_1, scene:GetVariable(AMVI_JJC_POTION_STAT_1) + 1);
		elseif role:GetObjID() == scene:GetVariable(AMVI_JJC_ROLE_ID_2) then
			scene:SetVariable(AMVI_JJC_POTION_STAT_2, scene:GetVariable(AMVI_JJC_POTION_STAT_2) + 1);
		end
	end

	return errSuccess;
end













Include("script/include/btnod.lua")
Include("script/scene/MirDg17_1/scene_bt.lua")

