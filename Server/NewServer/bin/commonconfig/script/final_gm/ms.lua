LoadPackage("chat_def.pkg")
LoadPackage("role_data.pkg")
LoadPackage("ms_guild.pkg")
LoadPackage("ms_guild_mgr.pkg")
LoadPackage("role_data_mgr.pkg")
LoadPackage("ms_guild_member.pkg")
LoadPackage("error_def.pkg")
LoadPackage("online_role_data.pkg")
LoadPackage("global_config.pkg")
LoadPackage("user.pkg")
LoadPackage("ranklist.pkg")
LoadPackage("master_mgr.pkg")
LoadPackage("scene.pkg")
LoadPackage("variable.pkg")
LoadPackage("arena_mgr.pkg")

Include("script/final_gm/final_gm_command_table.lua");

command_cache = {};
g_self_id = 0;
g_gm_from = 0;

g_RoleMgr = COnlineRoleDataMgr:GetInstance();
-- g_SceneMgr = CSceneMgr:GetInstance();
g_RankListMgr = CRankListMgr:GetInstance();

function echo(message)
	if g_gm_from == stGD then
		print(message);
		notify_guard(0, message);
	elseif g_gm_from == stGM then
		print(messsage);
		--return false; --TODO: to report gm tool
	elseif g_self_id ~= 0 then
		say(g_self_id, cltNormal, message, 0);
	end
end

function OnMSCommand(command, gm_level, gm_from, self_id, self_name)
	local fstr;

	g_self_id = self_id;
	g_gm_from = gm_from;
	command = command..' ';
	local func = string.lower(string.match(command, "%s*(.-)%s"));

	if command_table[func] == nil then
		echo('GM指令不存在');
		return false;
	end

	if gm_level < command_table[func][2] then
		echo('没有权限执行该指令');
		return false;
	end

	local index = 1;
	fstr = command_table[func][3]..'(';
	for w in string.gmatch(command, "[%s]*(.-)[%s]+") do
		if index == 1 then

		elseif index == 2 then
			if tostring(tonumber(w)) == w then
				print('1')
				fstr = fstr..w;
			elseif w:byte(1) == 0x27 then
				fstr = fstr..w;
			else
				fstr = fstr.."'"..w.."'";
			end
		else
			if tostring(tonumber(w)) == w then
				fstr = fstr..','..w;
			elseif w:byte(1) == 0x27 then
				fstr = fstr..','..w;
			else
				fstr = fstr..','.."'"..w.."'";
			end
		end
		index = index + 1;
	end
	fstr = fstr..');';

	print(fstr);

	if command_table[func][1] == MS_COMMAND or command_table[func][1] == (MS_COMMAND + GS_COMMAND) then
		if command_cache[fstr] then
			local f = command_cache[fstr];
			local result = f();
			if result then
				echo(tostring(result));
			end
		else
			local f, msg = loadstring(fstr);
			if f then
				command_cache[fstr] = f;
				local result = f();
				if result then
					echo(tostring(result));
				end
			elseif msg then
				echo('错误的GM指令 '..msg);
			end
		end
	end

	if command_table[func][1] == GS_COMMAND or command_table[func][1] == (MS_COMMAND + GS_COMMAND) then
		-- send to gs to execute
		local ret = call_gs_gm_func(self_id, fstr);
		if not ret then
			echo("无法将GM指令发送到GS");
			return false;
		end
	end

	return true;
end

function OnRunScript(command, gm_from)
	g_gm_from = gm_from;
	local f, msg = loadstring(command);
	if f then
		print(command);
		command_cache[command] = f;
		local result = f();
		echo(tostring(result));
		return true;
	elseif msg then
		echo('error script '..msg);
	end
	return false;
end

function KickAll(server_group)
	local ret = kickall(server_group);
	if ret then
		echo('成功踢下所有玩家');
	else
		echo('踢下所有玩家失败');
	end
end

function Switch(server_group, opened)
	local ret = switch_server_state(server_group, opened);
	if ret then
		if opened > 0 then
			echo('服务器组'..server_group..'切换为开启状态');
		else
			echo('服务器组'..server_group..'切换为关闭状态');
		end
	else
		echo('切换服务器组状态失败');
	end
end

function Kick(name)
	local ret = kick_role(name);
	if ret then
		echo('成功踢下玩家'..name);
	else
		echo('踢下玩家'..name..'失败');
	end
end


g_MSGuildMgr = CMsGuildMgr:GetInstance();
g_MSRoleDataMgr = CRoleDataMgr:GetInstance();
g_MSOnlineRoleMgr = COnlineRoleDataMgr:GetInstance();


function CreateGuild(role_name, guild_name, announce)
	local onlineRole = COnlineRoleDataMgr:GetInstance():FindOnlineRoleByName(role_name);

	echo("dfa");
	create_guild(onlineRole.pRoleData.dwRoleID, guild_name, announce);

	echo("创建公会成功");
	return true;
end

function JoinGuild(role_name, guild_name)
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);
	if guild == nil then
	    echo("没有找到公会");
		return false;
	end

	local role = g_MSRoleDataMgr:FindRoleByName(role_name);
	if role == nil then
		echo("未找到对应的角色");
		return false;
	end

	local ret  = guild:AddMember(role, GUILD_POSITION_CIVILIAN);
	if ret ~= errSuccess then
		echo("添加公会成员失败");
		return false;
	end

	return true;
end

-- leave_type default: GUILD_LEAVE_PASSIVE
function LeaveGuild(role_name, leave_type)		-- GUILD_LEAVE_TYPE
	local role = g_MSRoleDataMgr:FindRoleByName(role_name);
	if role == nil then
		echo("未找到角色");
		return false;
	end
	if 0 == role.dwGuildID then
		echo("角色没有公会");
		return false;
	end

	local 	guild = g_MSGuildMgr:FindGuildByID(role.dwGuildID);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	if leave_type == nil then
		leave_type = GUILD_LEAVE_PASSIVE;
	end

	if guild:GetLeaderID() == role.dwRoleID then
		echo("公会会长不能离开");
		return false;
	end

	local ret = guild:LuaLeaveGuild(leave_type, role.dwRoleID);
	if ret == false then
		echo("强制离开公会失败");
		return false;
	end

	return true;
end

--
function SetGuildPosition(role_name, position)		-- GUILD_LEAVE_TYPE
	local role = g_MSRoleDataMgr:FindRoleByName(role_name);
	if role == nil then
		echo("未找到角色");
		return false;
	end
	if 0 == role.dwGuildID then
		echo("角色没有公会");
		return false;
	end

	print(1);

	local 	guild = g_MSGuildMgr:FindGuildByID(role.dwGuildID);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	local  member = guild:GetMember(role.dwRoleID);
	if member == nil then
		echo("该角色不在指定公会");
		return false;
	end

	print(2);

	if position < GUILD_POSITION_LEADER or position >= GUILD_POSITION_TOTAL then
		echo("非法职位");
		return false;
	end

	if guild:GetMemberNumInAPost(position) >= GetMaxOfferInPosition(position) then
		echo("该职位人数过多");
		return false;
	end

	member:SetPosition(position);

	return true;
end

function DelGuild(guild_name)
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	ret = CRankListMgr:GetInstance():DelGuildRankNode(guild:GetSvrGroup(), guild:GetID());
	if ret == false then
		echo("删除排行榜数据出错");
		return false;
	end

	ret = g_MSGuildMgr:DestroyGuild(guild);
	if ret == false then
		echo("删除公会数据失败");
		return false;
	end

	local ret = guild:BroadcastMail("公会解散", "GM强制解散了您所在的公会!");
	if ret == false then
		echo("发送邮件失败，但不影响公会的解散流程");
	end

	return true;
end

function AddGuildFund(guild_name, money_type, num)
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	if money_type == 1 then
		guild:AddMoney(num, GUILD_CHEST_GM, true);
	elseif money_type == 2 then
		guild:AddWood(num);
	elseif money_type == 3 then
		guild:AddHerb(num);
	elseif money_type == 4 then
		guild:AddCrystal(num);
	elseif money_type == 5 then
		guild:AddSilver(num);
	end

	return true;
end

function DelAllEnemy(guildid)
	local 	guild = CMsGuildMgr:GetInstance():FindGuildByID(guildid);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	local enemy_table = {};
	local enemy_num = guild:GetEnemyNum();

	for i = 1, enemy_num do
		enemy_table[i-1] = guild:GetEnemyDataByIndex(i-1);
	end

	for i = 1, enemy_num do
		CMsGuildMgr:GetInstance():DelEnemy(guild:GetID(), enemy_table[i-1].dwGuildID);
	end

	return true;
end


function DelAllAlliance(guild_name)
	local 	guild = g_MSGuildMgr:FindGuildByName(guild_name);
	if guild == nil then
		echo("未找到公会");
		return false;
	end

	local alliance_table = {};
	local alliance_num = guild:GetAllianceNum();

	for i = 1, alliance_num do
		alliance_table[i-1] = guild:GetAllianceDataByIndex(i-1);
	end

	for i = 1, alliance_num do
		g_MSGuildMgr:DelAlliance(guild:GetID(), alliance_table[i-1].dwGuildID);
	end

	return true;
end

function DelMasterRelation(teacher_name, student_name)
	local teacher = g_MSRoleDataMgr:FindRoleByName(teacher_name);
	if teacher == nil then
		echo("未找到师傅的角色数据");
		return false;
	end

	local student = g_MSRoleDataMgr:FindRoleByName(student_name);
	if student == nil then
		echo("未找到徒弟的角色数据");
		return false;
	end

	local ret = CMasterMgr:GetInstance():DelMasterRelation(teacher.dwRoleID, student, false);
	if ret ~= errSuccess then
		echo("删除师徒数据失败,错误码："..ret);
		return false;
	end

	return true;
end

function AddMasterRelation(teacher_name, student_name)
	local teacher = g_MSOnlineRoleMgr:FindOnlineRoleByName(teacher_name);
	if teacher == nil then
		echo("未找到师傅的角色数据");
		return false;
	end

	local student = g_MSOnlineRoleMgr:FindOnlineRoleByName(student_name);
	if student == nil then
		echo("未找到徒弟的角色数据");
		return false;
	end


	local ret = CMasterMgr:GetInstance():CreateMasterRelation(teacher, student);
	if ret ~= errSuccess then
		echo("创建师徒师徒失败,错误码："..ret);
		return false;
	end

	return true;
end

function BeMaster(role_name)
	local role = g_MSRoleDataMgr:FindRoleByName(role_name);
	if role == nil then
		echo("未找到角色数据");
		return false;
	end

	local ret = CMasterMgr:GetInstance():BeMaster(role);
	if ret == false then
		echo("建立师傅数据失败");
		return false;
	end

	return true;
end



function Announce(message, location, server_group)
	if not server_group then
		local role = CRoleDataMgr:GetInstance():FindRole(g_self_id);
		server_group = role.byGroup;
	end
	say(cctGroup, location, message, server_group);
end

function AnnounceLighting(message, server_group)
	Announce(message, cltLighting, server_group);
end

function AnnounceTvShow(message, server_group)
	Announce(message, cltTvShow, server_group);
end

function AnnounceTrumpet(message, server_group)
	Announce(message, cltTrumpet, server_group);
end

function SetDropRate(rate)
	if rate < 8000 or rate > 20000 then
		echo("掉落倍率必须在万分之8000-20000之间");
		return;
	end
	if rate then
		call_gs_gm_func(0, "run CGameWorld:GetInstance():SetGlobalDropRate("..rate..");");
		echo("整个服务器所有分组的物品掉落率设置为万分之"..rate);
	else
		echo("请输入物品掉落率");
	end
end

function SetExpRate(rate)
	if rate < 8000 or rate > 20000 then
		echo("经验倍率必须在万分之8000-20000之间");
		return;
	end
	if rate then
		call_gs_gm_func(0, "run CGameWorld:GetInstance():SetGlobalExpRate("..rate..");");
		echo("整个服务器所有分组的打怪经验倍率设置为万分之"..rate);
	else
		echo("请输入经验倍率");
	end
end

function Arrest(name, duration)
	arrest_role(name, duration);
end

function RoleCount(group)
	if group then
		local count = CUserMgr:GetInstance():GetCountPerGroup(group);
		echo(group.."服在线人数为"..count);
	else
		local count = CUserMgr:GetInstance():Count();
		echo("总在线人数为"..count);
	end
end

function IPRoleCount(ip)
	local count = CUserMgr:GetInstance():GetCountByIP(ip);
	echo("IP地址为"..ip.."的玩家数量为"..count);
end

function EnrollSabac(guildid, t)
	while(guildid > 0)
	do
		local guild;
		if type(guildid) == 'number' then
			guild = CMsGuildMgr:GetInstance():FindGuildByID(guildid + 1610612935);
		elseif type(guildid) == 'string' then
			guild = CMsGuildMgr:GetInstance():FindGuildByName(guildid);
		end

		if guild then
			local y,m,d = string.match(t, "(%d+)%-(%d+)%-(%d+)");
			local tTime = { year = tonumber(y), month = tonumber(m), day = tonumber(d), hour = 8, min = 0, sec = 0};
			guild:EnrollSabac(os.time(tTime));
			echo('公会'..guild:GetName()..'报名成功');
		else
			echo('找不到公会');
		end
		guildid = guildid - 1;
	end
end

function CollectLogNow()
	collect_log_now();
end
function EnableGPKPunish(enabled)
	if enabled == 'on' then
		g_GWConfig.GpkPunishOption.bEnableSidewayPunish = true;
		echo('gpk旁路惩罚系统开启');
	elseif enabled == 'off' then
		g_GWConfig.GpkPunishOption.bEnableSidewayPunish = false;
		echo('gpk旁路惩罚系统关闭');
	end
end

function GPKCatchLimit(min_count, max_count)
	if min_count > max_count then
		echo('参数错误');
		return;
	end

	g_GWConfig.GpkPunishOption.nCatchMin = min_count;
	g_GWConfig.GpkPunishOption.nCatchMax = max_count;

	echo('监狱人数低于'..min_count..'开始抓人, 高于'..max_count..'停止抓人');
end

function GPKDelayLimit(queue_len, timeout)
	g_GWConfig.GpkPunishOption.nCatchDelayQueueLen = queue_len;
	g_GWConfig.GpkPunishOption.nCatchDelayTimeout = timeout;

	echo('存满'..queue_len..'人,或超过'..timeout..'秒执行抓人');
end

function TestGpk(name)
	test_gpk(name);
end


-- Temporarily disabled
--function SceneInfo()
--	local role = g_RoleMgr:FindOnlineRoleByRoleID(g_self_id);
--	local nSceneTempID = role.pRoleData.nSceneTempID;
--	local nSceneID = role.pRoleData.nSceneID;
--
--	local scene = g_SceneMgr:FindScene(nSceneTempID, nSceneID);
--
--    echo("场景ID="..nSceneTempID);
--    echo("实例ID="..string.format("0x%X", nSceneID));
--
--	if scene.nSceneType == estStatic then
--		echo("场景类型=静态地图")
--	elseif scene.nSceneType == estDungeon then
--		echo("场景类型=副本地图")
--	elseif scene.nSceneType == estBattleField then
--		echo("场景类型=战场地图")
--	elseif scene.nSceneType == estArena then
--		echo("场景类型=竞技场地图")
--	elseif scene.nSceneType == estLine then
--		echo("场景类型=分线地图")
--	    echo("分线总数="..g_SceneMgr:GetSceneLineCount(role.pRoleData.byGroup, nSceneTempID));
--	elseif scene.nSceneType == estBirth then
--		echo("场景类型=出生地图")
--	elseif scene.nSceneType == estGuild then
--		echo("场景类型=公会地图")
--	elseif scene.nSceneType == estGuildDungeon then
--		echo("场景类型=公会副本地图")
--	elseif scene.nSceneType == estUnique then
--		echo("场景类型=全区唯一地图")
--	elseif scene.nSceneType == estSoloDungeon then
--		echo("场景类型=单人副本地图")
--	end
--
--	echo("当前地图总玩家数="..scene.nRoleCount);
--	echo("所有该地图总玩家数="..g_SceneMgr:GetSceneTempRoleCount(role.pRoleData.byGroup, nSceneTempID));
--end


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

function GetWorldGambleCount(server_group, typeString, level)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	echo(typeString .. '世界次数为: ' .. get_server_var(server_group, esvtWorldGambleCount, gambletype * 65536 + level));
end

function SetWorldGambleCount(server_group, typeString, level, value)
	local gambletype = GetGambleTypeFromString(typeString);
	if (gambletype) == egtInvalid then
		echo('未知类型');
		return;
	end

	set_server_var(server_group, esvtWorldGambleCount, gambletype * 65536 + level, value);
	echo(typeString .. '世界次数设置为: ' .. value);
end


-- Temporarily disabled
--function SendRankListAward(nServerGroup, nRankListType, nStart, nEnd, nMailID, nMailCDTime)
--	local nNodeCount = g_RankListMgr:GetMirrorRankNodeCount(nServerGroup, nRankListType);
--	if nEnd > nNodeCount then
--		nEnd = nNodeCount;
--	end
--	if not nMailCDTime then
--		nMailCDTime = 0;
--	end
--
--	print('send award mail '..nMailID..' cd '..nMailCDTime..' to server group '..nServerGroup..' rank list '..nRankListType..' from '..nStart..' to '..nEnd);
--
--	for i = nStart, nEnd do
--		local rank_node = g_RankListMgr:GetMirrorRankListNode(nServerGroup, nRankListType, i - 1);
--		send_mail(rank_node.llKey, nMailID, nMailCDTime);
--	end
--end


function ArenaOpen()
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtArena, avArenaCanOpen, 1);

			echo("arena open "..i);
		end
	end
end

function ArenaClose()
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtArena, avArenaCanOpen, 0);
			echo("arena close "..i);
		end
	end
end


function GuildWarOpen()
	print("guild war open");
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtGuild, avGuildWarCanOpen, 1);

			echo("guild war open "..i);
		end
	end
end


function GuildWarClose()
	print("guild war close");
	for i= 0, MAX_SERVER_GROUP_COUNT,1 do
		local bValidGroup = IsValidGroup(i);
		if bValidGroup then
			set_server_var(i, esvtGuild, avGuildWarCanOpen, 0);

			echo("guild war close "..i);
		end
	end
end

