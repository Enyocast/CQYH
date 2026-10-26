Include("script/include/command_table.lua");

MAX_ECHO_COUNT = 20

help = {};

function command_help(command)
	for k,v in ipairs(gm[command]) do
		if type(v) == 'string' then
			echo(v);
		end
	end
end

function gm_help(command, ...)
	if command then
		command = string.lower(command);
		if help[command] == command_help then
			help[command](command);
		elseif help[command] then
			help[command](...);
		else
			echo('错误的帮助指令参数');
		end
	else
		echo('输入.help list查看所有GM指令列表');
		echo('输入.help command查看具体指令的帮助');
		echo('帮助信息中，[]包含的是可选参数，{}包含的参数支持help指令');
		echo('{}中的参数，后可以再跟一个参数，可以是ID或名字，名字支持模糊匹配');
		echo('例如.help quest 师门，可以列出所有任务名中包含师门的任务');
	end
end

--function help.list(role_id)
--	for k,v in pairs(gm) do
--		if v[3] then
--			echo(role_id, v[3]);
--		else
--			echo(role_id, k);
--		end
--	end
--end

function help.list()
	for k,v in pairs(gm) do
		if v[2] then
			echo(v[4]);
		else
			echo(k);
		end
	end
end


function help.jump_point()
	echo('jump point table:');
	for k, v in pairs(jump_table) do
		echo(v.name..' : '..k);
	end
end;

function help.teleport_id(id)
	local scene = TargetRole:GetScene();
	local staticData = scene:GetStaticData();
	for i = 1, MAX_TELEPORT_POINT_PER_SCENE-1 do
		local teleport = staticData:FindTeleportPoint(i);
		if teleport and (id == nil or id == i) then
			echo('teleport_id '..i..' : from ('..
				math.floor(teleport.SrcSceneX/POINT_PER_CM)..', '..
				math.floor(teleport.SrcSceneY/POINT_PER_CM)..', '..
				math.floor(teleport.SrcSceneZ/POINT_PER_CM)..') to ('..
				math.floor(teleport.TargetSceneX/POINT_PER_CM)..', '..
				math.floor(teleport.TargetSceneY/POINT_PER_CM)..', '..
				math.floor(teleport.TargetSceneZ/POINT_PER_CM)..') ');
		end
	end
end;

function help.bt_action()
	echo('bt action enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 3) == 'bat' then
			echo(k..' : '..v);
		end
	end
end

function help.quality()
	echo('npc quality enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 2) == 'nq' then
			echo(k..' : '..v);
		end
	end
end

function help.money()
	echo('money type enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 9) == 'MONEYTYPE' then
			echo(k..' : '..v);
		end
	end
end

function help.pkmode()
	echo('pk mode enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 3) == 'rpm' then
			echo(k..' : '..v);
		end
	end
end

function help.weather()
	echo('weather enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 3) == 'swt' then
			echo(k..' : '..v);
		end
	end
end

function help.hero_ai()
	echo('hero ai enum : ');
	for k,v in pairs(_G) do
		if string.sub(k, 1, 3) == 'hat' then
			echo(k..' : '..v);
		end
	end
end

function help.object()
	local module_list = {};
	for k,v in pairs(gm) do
		for kk,vv in ipairs(v) do
			if type(vv) == 'string' then
				print(vv);
				local name = string.match(vv, '%s*{[_%w]+}%s*');
				if name and not module_list[name] then
					echo(name);
					module_list[name] = 1;
				end
			end
		end
	end
end

function help.quest(condition)
	print("quest begin");
	local count = 0;
	local data = CDataManager_QUEST_DATA_:GetInstance():GetFirstData();
	while data do
		print("quest: "..data.szName);
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.nQuestID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			if string.find(data.szName, condition) then
				need = true
			end
		end
		if need then
			echo('ID:'..data.nQuestID..' 名称:'..data.szName);
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_QUEST_DATA_:GetInstance():GetNextData();
	end
end

function help.item(condition)
	local count = 0;
	local data = CDataManager_ITEM_DATA_:GetInstance():GetFirstData();
	while data do
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.m_nTemplateID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			if string.find(data.m_szName, condition) then
				need = true
			end
		end
		if need then
			echo('ID:'..data.m_nTemplateID..' 名称:'..data.m_szName);
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_ITEM_DATA_:GetInstance():GetNextData();
	end

	data = CDataManager_EQUIP_DATA_:GetInstance():GetFirstData();
	while data do
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.m_nTemplateID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			if string.find(data.m_szName, condition) then
				need = true
			end
		end
		if need then
			echo('ID:'..data.m_nTemplateID..' 名称:'..data.m_szName);
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_EQUIP_DATA_:GetInstance():GetNextData();
	end

end

function help.doodad(condition)
	local count = 0;
	local data = CDataManager_DOODAD_DATA_:GetInstance():GetFirstData();
	while data do
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.nTemplateID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			if string.find(data.szName, condition) then
				need = true
			end
		end
		if need then
			echo('ID:'..data.nTemplateID..' 名称:'..data.szName);
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_DOODAD_DATA_:GetInstance():GetNextData();
	end
end


function help.npc(condition)
	local count = 0;
	local data = CDataManager_NPC_DATA_:GetInstance():GetFirstData();
	while data do
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.nTemplateID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			if string.find(data.szName, condition) then
				need = true
			end
		end
		if need then
			echo('ID:'..data.nTemplateID..' 名称:'..data.szName);
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_NPC_DATA_:GetInstance():GetNextData();
	end
end

function help.spell(condition)
	local count = 0;
	local data = CDataManager_SPELL_ENTRY_:GetInstance():GetFirstData();
	while data do
		local need = false;
		if condition == nil then
			need = true
		elseif type(condition) == 'number' then
			if data.m_nID == condition then
				need = true
			end
		elseif type(condition) == 'string' then
			echo('暂不支持技能名查找，等李星佳修改代码');
			return
		end
		if need then
			echo('ID:'..data.m_nID..' 名称: N/A');
			count = count + 1;
			if count > MAX_ECHO_COUNT then
				return
			end
		end
		data = CDataManager_SPELL_ENTRY_:GetInstance():GetNextData();
	end
end


command_cache = {};

--function OnNewGMCommand(command)
--	print("command: "..command);
--	if command_cache[command] then
--		local f = command_cache[command];
--		echo(command);
--		f();
--		return true;
--	else
--		local f, msg = loadstring(command);
--		if f then
--			echo(command);
--			command_cache[command] = f;
--			f();
--			return true;
--		elseif msg then
--			echo('错误的GM指令 '..msg);
--		end
--	end

--	return false;
--end

function OnNewGMCommand(command)
	local fstr = command;
	
	echo(fstr);
	if command_cache[fstr] then
		local f = command_cache[fstr];
		echo(command);
		f();
		return true;
	else
		local f, msg = loadstring(fstr);
		if f then
			echo(command);
			command_cache[fstr] = f;
			f();
			return true;
		elseif msg then
			echo('错误的GM指令 '..msg);
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

--- register help strings
for k,v in pairs(gm) do
	help[k] = command_help;
end
