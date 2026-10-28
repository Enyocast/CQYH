LoadPackage("gameworld.pkg");
LoadPackage("scene.pkg");
LoadPackage("character.pkg");
LoadPackage("role.pkg");
LoadPackage("npc.pkg");
LoadPackage("item.pkg");
LoadPackage("item_bag.pkg");
LoadPackage("teleport.pkg");
LoadPackage("attr_list.pkg");
LoadPackage("attribute_def.pkg");
LoadPackage("ai.pkg")
LoadPackage("char_def.pkg")
LoadPackage("math_ex.pkg")
LoadPackage("quest_list.pkg")
LoadPackage("title.pkg")
LoadPackage("master.pkg")
LoadPackage("data_manager.pkg")
LoadPackage("achievement_list.pkg")
LoadPackage("friend.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("hero.pkg")
LoadPackage("money_def.pkg")
LoadPackage("master.pkg")
LoadPackage("string_table.pkg")
LoadPackage("spell.pkg")
LoadPackage("spell_book.pkg")
LoadPackage("id_def.pkg")
LoadPackage("doodad.pkg")
LoadPackage("spirit.pkg")
LoadPackage("spirit_def.pkg")
LoadPackage("global_config.pkg")
LoadPackage("drop_manager.pkg")
LoadPackage("gamble.pkg")

Include("script/include/jump_table.lh")

g_oGameWorld = CGameWorld:GetInstance();
g_oSceneFileMgr = CSceneFileMgr:GetInstance();

command_cache = {};

function echo(text)
	role:GetScene():Say(role:GetObjID(), cltNormal, text);
end

function OnGSCommand(fstr)

	if command_cache[fstr] then
		local f = command_cache[fstr];
		f();
		print(fstr);--echo(fstr);
		return true;
	else
		local f, msg = loadstring(fstr);
		if f then
			command_cache[fstr] = f;
			f();
			print(fstr);--echo(fstr);
			return true;
		elseif msg then
			print('错误的GM指令 '..msg);--echo('错误的GM指令 '..msg);
		end
	end

	return false;
end

function OnRunScript(command)
	local f, msg = loadstring(command);
	if f then
		print(command);--echo(command);
		command_cache[command] = f;
		f();
		return true;
	elseif msg then
		print('error script '..msg);
	end
	return false;
end

function GetFocusRole(roleName)
	local focus = g_oGameWorld:FindValidRole(role:GetFocusID());
	if focus then
		if focus:GetName() == roleName then
			return focus;
		else
			echo('输入的玩家名称与选定的玩家不符，请检查');
		end
	else
		if role:GetName() == roleName then
			return role;
		else
			echo('请先选定目标再执行指令');
		end
	end
end

function SetSpeed(v)
	role:GetAttrList():SetAttrBase(role, catRunSpeed, v * GAME_FPS / 1000)
	echo('当前移动速度设置为'..v..'毫秒');
end

function Jump(...)
    local param = {...}
    local paramCount = #param;
	local scene = role:GetScene();
	local staticData;

	if paramCount == 1 and jump_table[param[1]] then
		local scene_name = param[1];
		paramCount = #(jump_table[scene_name].pos);
		param = {};
		for i=1, paramCount do
			param[i] = jump_table[scene_name].pos[i];
		end
	end

    if paramCount == 1 then
        g_oGameWorld:JumpToRole(role, param[1]);
		echo('跳转到玩家'..param[1]..'身边');
    elseif paramCount == 2 then
		param[1], param[2], _ = ConvertCoordO2N(param[1], param[2], 0);

        local posList = get_near_pos(role:GetSceneTempID(),
            param[1] * POINT_PER_CM, param[2] * POINT_PER_CM, 1000000 * POINT_PER_CM, 256, 1)
        g_oGameWorld:JumpTo(role, role:GetSceneTempID(), role:GetSceneID(),
			posList[1].x, posList[1].y, posList[1].z,
		role:GetFaceDirection());
		echo('跳转到当前场景指定坐标处');
    elseif paramCount == 3 then
		param[1], param[2], _ = ConvertCoordO2N(param[1], param[2], 0);
        local posList = get_near_pos(role:GetSceneTempID(),
            param[1] * POINT_PER_CM, param[2] * POINT_PER_CM, param[3] * POINT_PER_CM, 256, 1)
        g_oGameWorld:JumpTo(role, role:GetSceneTempID(), role:GetSceneID(),
			posList[1].x, posList[1].y, posList[1].z, role:GetFaceDirection());
		echo('跳转到当前场景指定坐标处');
    elseif paramCount == 4 then
		param[3], param[4], _ = ConvertCoordO2N(param[3], param[4], 0);
        local posList = get_near_pos(param[1],
            param[3] * POINT_PER_CM, param[4] * POINT_PER_CM, 1000000 * POINT_PER_CM, 256, 1)
        g_oGameWorld:JumpTo(role, param[1], param[2],
            posList[1].x, posList[1].y, posList[1].z, role:GetFaceDirection());
		echo('跳转到场景'..param[1]..'的指定坐标处');
    elseif paramCount == 5 then
		param[3], param[4], param[5] = ConvertCoordO2N(param[3], param[4], param[5]);
        local posList = get_near_pos(param[1],
            param[3] * POINT_PER_CM, param[4] * POINT_PER_CM, param[5] * POINT_PER_CM, 256, 1)
        g_oGameWorld:JumpTo(role, param[1], param[2],
            posList[1].x, posList[1].y, posList[1].z, role:GetFaceDirection());
		echo('跳转到场景'..param[1]..'的指定坐标处');
    else
        print("错误的跳转指令")
    end
end

function TakeRole(role_name)
    g_oGameWorld:TakeRole(role, role_name);
	echo('将玩家'..role_name..'拉到身边');
end

function TransferRole(x, y, z, range, count)
	x, y, z = ConvertCoordO2N(x, y, z);
	role:TransferRole(x * POINT_PER_CM, y * POINT_PER_CM, z * POINT_PER_CM, range * POINT_PER_CM, count);
	echo('将身边的玩家拉到指定坐标处');
end

function Hide()
	role:Hide(not role:IsHidden());
	if role:IsHidden() then
		echo('已经进入隐身状态');
	else
		echo('已经离开隐身状态');
	end
end

function God()
	if role:GetControlCount(cclInvincible) > 0 then
	    while role:GetControlCount(cclInvincible) > 0 do
    	    role:DecControlCount(cclInvincible);
    	end
		echo('已经解除无敌状态');
	else
	    role:IncControlCount(cclInvincible);
		echo('已经进入无敌状态');
	end
end

function Recover()
	local attrlist = role:GetAttrList();
	local maxhp = attrlist:GetAttr(catMaxHp);
	local maxmp = attrlist:GetAttr(catMaxMp);

	role:ChangeHp(maxhp, 0);
	role:ChangeMp(maxmp);
	echo('满血满蓝');
end

function Revive()
	role:Revive(0, 10000);
	echo('已复活');
end

function SummonNpc(nTemplateID, nCount)
	if type(nTemplateID) == 'string' then
		nTemplateID = CDataManager_NPC_DATA_:GetInstance():GetID(nTemplateID);
	end
	if nCount == nil then
		nCount = 1;
	end
	if nCount > 99 then
		nCount = 99;
	end
    local oScene = role:GetScene();

	local oNpc;
	for i = 1, nCount do
	    oNpc = oScene:SpawnNpc(nTemplateID, role:GetX(), role:GetY(),
			role:GetZ() + GRID_WIDTH, role:GetFaceDirection(), 0, nil);
	end
	echo('召怪成功');
    return;
end

function Kill(roleName)
	dwObjectID = role:GetFocusID();
	local nObjectType = GetTypeFromID(dwObjectID);
	if nObjectType == otNpc or nObjectType == otHero then
		local oChar = g_oGameWorld:FindCharacter(dwObjectID);
		oChar:SetLastCasterID(role:GetObjID());
		oChar:SetDropOwnerID(role:GetObjID());
		oChar:SetHp(0);
		echo('已杀死选定目标');
	elseif nObjectType == otRole then
		local oChar = g_oGameWorld:FindValidRole(dwObjectID);
		if oChar:GetName() == roleName then
			oChar:SetHp(0);
			echo('已杀死选定目标');
		else
			echo('输入的玩家名称与选定的玩家不符，请检查');
		end
	elseif nObjectType == otDoodad then
		local oDoodad = g_oGameWorld:FindDoodad(dwObjectID);
		while oDoodad:GetOpenCount() > 0 do
			oDoodad:OnOpen(role);
		end
		echo('已杀死选定目标');
	end
end

function SummonDoodad(nTemplateID)
    local oScene = role:GetScene();
    local oDoodad = oScene:SpawnDoodad(nTemplateID, role:GetX(), role:GetY(), role:GetZ(), role:GetFaceDirection());
	echo('召物件成功');
    return;
end

function AcceptQuest(roleName, questID)
	local focus = GetFocusRole(roleName);
	if focus then
		local ret = focus:GetQuestList():Accept(questID);
		if ret == errSuccess then
			echo('接受任务'..questID..'成功');
		else
			echo('接受任务失败，错误码: '..ret);
		end
	end
end

function CompleteQuest(roleName, questID)
	local focus = GetFocusRole(roleName);
	if focus then
		local ret = focus:GetQuestList():Complete(questID);
		if ret == errSuccess then
			echo('完成任务'..questID..'成功');
		else
			echo('完成任务失败，错误码: '..ret);
		end
	end
end

function AbandonQuest(roleName, questID)
	local focus = GetFocusRole(roleName);
	if focus then
		if type(questID) == 'number' then
			local ret = focus:GetQuestList():Abandon(questID);
			if ret == errSuccess then
				echo('放弃任务'..questID..'成功');
			else
				echo('放弃任务失败，错误码: '..ret);
			end
		elseif questID == 'all' then
			echo("暂时不支持");
		end
	end
end

function AddTitle(roleName, id)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetTitle():AddTitle(id)
	end
end

function DelTitle(roleName, id)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetTitle():DeleteTitle(id, 0)
	end
end

function AddItem(id, count)
	local name = id;
    if type(id) == 'string' then
		local newid = CDataManager_ITEM_DATA_:GetInstance():GetID(id);
		if newid == 0 then
		    newid = CDataManager_EQUIP_DATA_:GetInstance():GetID(id);
		end
		id = newid;
		echo('道具'..name..'的ID为'..id);
    end
    if not count then
        count = 1;
		echo('未指定道具堆叠数量，默认设置为1');
    end
	role:GetItemBag():AddItem(id, count, ITEMLOG_GM_COMMAND, 0, false)
	echo('添加道具'..id..'成功');
end

function FocusInfo()
    local char = g_oGameWorld:FindValidCharacter(role:GetFocusID());

	echo("id="..char:GetObjID());
	echo("name="..char:GetName());
	echo("level="..char:GetLevel());
	echo("hp="..char:GetHp().."/"..char:GetAttrList():GetAttr(catMaxHp));
	echo("mp="..char:GetMp().."/"..char:GetAttrList():GetAttr(catMaxMp));

    if char:GetObjType() == otNpc then
	    local npc = Cast(char, "CNpc");
    	echo("id="..npc:GetNpcData().nTemplateID);
    	echo("ai="..npc:GetAIProcessor():GetAIID());
    	echo("quality="..npc:GetQuality());
    elseif char:GetObjType() == otRole then
        local role = Cast(char, "CRole");
        echo("pkvalue="..role:GetPkValue());
		echo("session="..role:GetSessionID());
		echo("svrgroup="..role:GetServerGroup());

		local remainTime = role:GetCoolDown():GetRemainFrm(MakeCoolDownID(COOLDOWN_MISC, COOLDOWN_MISC_ARREST)) / GAME_FPS;
		if remainTime > 0 then
			echo("arresttime="..math.floor(remainTime)..'秒');
		end
    end

	local rx = role:GetX();
	local ry = role:GetY();
	local rz = role:GetZ();
	local fx = char:GetX();
	local fy = char:GetY();
	local fz = char:GetZ();
	local d = math.sqrt((rx-fx)*(rx-fx)+(ry-fy)*(ry-fy)+(rz-fz)*(rz-fz));

	local xx, yy, zz = ConvertCoordN2O(fx/POINT_PER_CM, fy/POINT_PER_CM, fz/POINT_PER_CM);
	echo("pos=("..math.ceil(xx)..", "..math.ceil(yy)..", "..math.ceil(zz)..")");

	echo("dir="..(char:GetFaceDirection() * 8 / MAX_DIRECTION_COUNT));

	echo("distance="..(d/POINT_PER_CM));
end

function SelfInfo()
	echo("name="..role:GetName());
	echo("level="..role:GetLevel());
	echo("hp="..role:GetHp().."/"..role:GetAttrList():GetAttr(catMaxHp));
	echo("mp="..role:GetMp().."/"..role:GetAttrList():GetAttr(catMaxMp));

	local fx = role:GetX();
	local fy = role:GetY();
	local fz = role:GetZ();
	fx, fy, fz = ConvertCoordN2O(fx/POINT_PER_CM, fy/POINT_PER_CM, fz/POINT_PER_CM);
	echo("pos=("..math.ceil(fx)..", "..math.ceil(fy)..", "..math.ceil(fz)..")");

    echo("pkvalue="..role:GetPkValue());
    echo("vip="..role:GetVIPLevel()..", "..math.ceil((role:GetVIPTime(TargetRole:GetVIPLevel()) - g_oGameWorld:GetGameTime()) / 86400).." day");
end

function SceneInfo()
    local scene = role:GetScene();

    echo("天气="..scene:GetWeather());
    echo("当前地图Npc总数="..scene:GetNpcCount());
end

function GMLevel(roleName, level)
	local focus = GetFocusRole(roleName);
	if focus then
		if role:GetFocusID() ~= role:GetObjID() and role:GetGMLevel() > focus:GetGMLevel() and level < role:GetGMLevel() then
			focus:SetGMLevel(level);
			echo('玩家 '..focus:GetName()..' 的GM等级设定为'..level);
		else
			echo('权限不足');
		end
	end
end

function Level(roleName, level)
	local focus = g_oGameWorld:FindValidRole(role:GetFocusID());
	if focus then
		if focus:GetName() == roleName then
			focus:SetLevel(level);
			echo('玩家 '..focus:GetName()..' 的等级设定为'..level);
		else
			echo('输入的玩家名称与选定的玩家不符，请检查');
		end
	else
		level = roleName;
		role:SetLevel(level);
		echo('玩家 '..role:GetName()..' 的等级设定为'..level);
	end
end

function AddMoney(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_02, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加金币'..amount);
end

function AddArenaScore(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_ARENA, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加擂台积分'..amount);
end

function AddArenaMoney(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_03, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加擂台币'..amount);
end

function AddMasterExp(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_MASTER_EXP, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加名师值'..amount);
end

function AddGuildExp(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_GUILD, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加帮贡'..amount);
end

function AddMoralValue(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_MORAL, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加道义值'..amount);
end

function AddAchievementPts(amount)
	role:GetItemBag():AddMoney(MONEYTYPE_ACHIEVEMENTPTS, amount, MONEYLOG_GM_COMMAND, 0, 0);
	echo('增加成就点数'..amount);
end

function GiveMoney(roleName, amount)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetItemBag():AddMoney(MONEYTYPE_02, amount, MONEYLOG_GM_COMMAND, 0, 0);
		echo('玩家'..roleName..'获得金币'..amount);
	end
end

function GiveMasterExp(amount)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetItemBag():AddMoney(MONEYTYPE_MASTER_EXP, amount, MONEYLOG_GM_COMMAND, 0, 0);
		echo('玩家'..roleName..'获得名师值'..amount);
	end
end

function GiveGuildExp(amount)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetItemBag():AddMoney(MONEYTYPE_GUILD, amount, MONEYLOG_GM_COMMAND, 0, 0);
		echo('玩家'..roleName..'获得帮贡'..amount);
	end
end

function GiveMoralValue(amount)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetItemBag():AddMoney(MONEYTYPE_MORAL, amount, MONEYLOG_GM_COMMAND, 0, 0);
		echo('玩家'..roleName..'获得道义值'..amount);
	end
end

function GiveAchievementPts(amount)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetItemBag():AddMoney(MONEYTYPE_ACHIEVEMENTPTS, amount, MONEYLOG_GM_COMMAND, 0, 0);
		echo('玩家'..roleName..'获得成就点数'..amount);
	end
end

function SetSpiritLevel(level)
	role:GetSpirit():SetLevel(level);
	echo('境界等级设定为'..level);
end

function AddSpellPts(id, pts)
	role:AddSpellPts(id, pts);
	echo('技能'..id..'的熟练度增加'..pts..'点');
end

function AddExp(n)
	role:AddExp(n, false, false);
	echo('获得'..n..'经验');
end

function ClearRedName(roleName)
	local focus = GetFocusRole(roleName);
	if focus then
		focus:SetPkValue(0);
		echo('玩家'..roleName..'的PK值已清零');
	end
end

function ArrestTime(roleName)
	local focus = GetFocusRole(roleName);
	if focus then
		local frame = focus:GetCoolDown():GetRemainFrm(MakeCoolDownID(COOLDOWN_MISC, COOLDOWN_MISC_ARREST));
		echo('玩家'..roleName..'的囚禁时间还剩'..(frame / GAME_FPS)..'秒');
	end
end

function DelSpell(roleName, id)
	local focus = GetFocusRole(roleName);
	if focus then
		local name = id;
		if type(id) == 'string' then
			id = CDataManager_SPELL_ENTRY_:GetInstance():GetID(id);
			if id and id ~= 0 then
				echo('技能'..name..'的ID为'..id);
			else
				echo('技能'..name..'不存在');
			end
		end
		if id then
			focus:GetSpellBook():RemoveSpell(id);
		end
	end
end

function SetRune(nSpellID, nRuneSlot)
	role:EquipRune(nSpellID, nRuneSlot);
end

function StartDate(group)
	if not group then
		group = role:GetServerGroup();
	end
	echo("服务器组"..group.."的开服时间是"..os.date("%Y-%m-%d", g_ServerConfig.GroupConfig[group].dwStartDate));
end

function DeleteNpc()
	dwObjectID = role:GetFocusID();
	local nObjectType = GetTypeFromID(dwObjectID);
	if nObjectType == otNpc then
		local oNpc = g_oGameWorld:FindNpc(dwObjectID);
		oNpc:SetLastCasterID(role:GetObjID());
		oNpc:SetDropOwnerID(role:GetObjID());
		oNpc:SetGenerateDrop(false);
		oNpc:DeleteSelf();
		echo('已删除选定Npc');
	else
		echo('请选定要删除的Npc');
	end
end

function EnableClientGPK(enabled)
	if enabled == 'on' then
		g_GWConfig.GpkPunishOption.bEnableGpkKeepAlive = true;
		echo('客户端gpk上报开启');
	elseif enabled == 'off' then
		g_GWConfig.GpkPunishOption.bEnableGpkKeepAlive = false;
		echo('客户端gpk上报关闭');
	end
end

function EnableClientGPKTimeoutKick(enabled)
	if enabled == 'on' then
		g_GWConfig.GpkPunishOption.bEnableKeepAliveTimeoutKick = true;
		echo('客户端gpk上报超时踢人开启');
	elseif enabled == 'off' then
		g_GWConfig.GpkPunishOption.bEnableKeepAliveTimeoutKick = false;
		echo('客户端gpk上报超时踢人关闭');
	end
end

function EnableClientGPKReturn4Kick(enabled)
	if enabled == 'on' then
		g_GWConfig.GpkPunishOption.bEnableKeepAliveReturn4Kick = true;
		echo('客户端gpk上报异常错误4踢人开启');
	elseif enabled == 'off' then
		g_GWConfig.GpkPunishOption.bEnableKeepAliveReturn4Kick = false;
		echo('客户端gpk上报异常错误4踢人关闭');
	end
end

function GetGambleTypeFromString(typeString)
	if typeString == '武器' then
		return egtEquipWeapon;
	elseif typeString == '头盔' then
		return egtEquipHat;
	elseif typeString == '肩甲' then
		return egtEquipShoulderArmor;
	elseif typeString == '衣服' then
		return egtEquipChestArmor;
	elseif typeString == '护腕' then
		return egtEquipWristArmor;
	elseif typeString == '腰带' then
		return egtEquipBelt;
	elseif typeString == '鞋子' then
		return egtEquipShoes;
	elseif typeString == '披风' then
		return egtEquipCloak;
	elseif typeString == '项链' then
		return egtEquipNecklace;
	elseif typeString == '戒指' then
		return egtEquipRing;
	elseif typeString == '手镯' then
		return egtEquipBracelet;
	elseif typeString == '技能书' then
		return egtSpellBook;
	elseif typeString == '战士铭文' then
		return egtRuneWarrior;
	elseif typeString == '法师铭文' then
		return egtRuneMage;
	elseif typeString == '盗贼铭文' then
		return egtRuneRogue;
	elseif typeString == '弓手铭文' then
		return egtRuneArcher;
	elseif typeString == '道士铭文' then
		return egtRuneTaoist;
	else
		return egtInvalid;
	end
end

function GetTotalGambleCount(roleName, typeString, level)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	local focus = GetFocusRole(roleName);
	if focus then
		echo(typeString .. '总次数: ' .. focus:GetGamble():GetTotalValue(gambletype, level));
	end
end

function GetGambleCount(roleName, typeString, level)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	local focus = GetFocusRole(roleName);
	if focus then
		echo(typeString .. '次数: ' .. focus:GetGamble():GetValue(gambletype, level));
	end
end

function SetGambleCount(roleName, typeString, level, value)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetGamble():SetValue(gambletype, level, value)
		echo(typeString .. '设置为: ' .. value);
	end
end

function SetNextGambleID(roleName, typeString, level, id)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	local focus = GetFocusRole(roleName);
	if focus then
		focus:GetGamble():SetNextID(gambletype, level, id)
		echo('下次赌博' .. typeString .. '设置为: ' .. id);
	end
end

function SendMails()
	if not role then
		print('skipped');
		return;
	end
	local group = role:GetServerGroup();
	if sended == 0 then
		local succcount = 0;
		local failcount = 0;
		for roleid, money in pairs(ROLE_LIST[group]) do
			local ret = role:SendMail(roleid, 4, MONEYTYPE_02, money);
			if ret then
				succcount = succcount + 1;
				print('sended a mail to role '..roleid..' with money '..money);
			else
				failcount = failcount + 1;
				print('failed to send a mail to role '..roleid..' with money '..money);
			end
		end
		echo(succcount..' mail success and '..failcount..' mail fail');
	else
		echo('已发送过邮件');
	end
end

function AddActivityPts(pts, reason)
	role:AddActivityPts(pts, reason);
	echo("now activity pts: ".. role:GetActivityPts());
end

function Version()
	echo("服务器版本："..g_oGameWorld:GetVersion())
end