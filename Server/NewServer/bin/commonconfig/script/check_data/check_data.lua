LoadPackage("check_data.pkg")

Include("setting/item.lua")
Include("setting/item_armor.lua")
Include("setting/refine.lua")
Include("setting/shop.lua")
Include("setting/scene.lua")
Include("setting/npc.lua")
Include("setting/doodad.lua")
Include("setting/spell_var.lua")
Include("setting/spell.lua")
Include("setting/spell_node.lua")
Include("setting/rune.lua")
Include("setting/aura.lua")
Include("setting/missile.lua")
Include("setting/ai.lua")
Include("setting/drop_group.lua")
Include("setting/level.lua")
Include("setting/attributes1.lua")
Include("setting/attributes2.lua")
Include("setting/quest.lua")
Include("setting/reputation.lua")
Include("setting/npc_relation.lua")
Include("setting/role_relation.lua")
Include("setting/achievement.lua")
Include("setting/master_gift.lua")
Include("setting/title.lua")
Include("setting/doodad_drop_data.lua")
Include("setting/equip_attribute.lua")
Include("setting/mount.lua")
Include("setting/air.lua")
Include("setting/air_level.lua")
Include("setting/spirit.lua")
Include("setting/set.lua")
Include("setting/attribute.lua")
Include("setting/soul.lua")

-- 说明：type的类型有 number, string, link, object, union
-- number		表示不与其他表交互的数字数据项，若其count字段不为0则表明为数组,其max或者min字段如果没有则默认不查
-- string		表示不与其他表交互的字符数据项，若其count字段不为0则表明为数组,其maxlen字段表示最大的字符串长度
-- link			表示与其他表单交互的非结构体数据项，若其count字段不为0则表明为数组,其refertable表明与其交互表的名字,　referfield表示交互表对应的交互项
-- rule			表示此项的检验规则自己制定，rule项为表达式，只用带入数据查看是否满足
-- item			特种类型，表示此数据项必须要在item表或者equip表出现

function check(Data)
	local passcount = 0;
	local tabledata = _G[Data..'_define'];
	local missed_field = {};
	
	if tabledata == nil then
		CCheckData:GetInstance():PrintWrn('配置表'..Data..'没有配置检查脚本，请找张敬轩确定该表格的负责人');
		return false;
	end
	
	if tabledata.owner == nil then
		CCheckData:GetInstance():PrintWrn('配置表'..Data..'没有设置负责人，请找张敬轩确定该表格的负责人');
		return false;
	end
	
	local tabconfig = CCheckData:GetInstance():GetDataByName(Data);
	local rowcount = CCheckData:GetInstance():GetTabRowCount(tabconfig);
	local colcount = CCheckData:GetInstance():GetTabColCount(tabconfig);
	ruletable = {};
	
	for row = 0, rowcount - 1 do	-- 遍历每一行
		local error = false;
		for col = 0, colcount - 1 do	-- 遍历每一行
		
			local colname = CCheckData:GetInstance():GetColName(tabconfig, col);

			if not tabledata[colname] then
				if not missed_field[colname] then
					CCheckData:GetInstance():PrintWrn('配置表'..Data..'缺少字段'..colname..'的检查项配置，请找'..tabledata.owner..'修正');
					missed_field[colname] = colname;
				end
				error = true;
			end

			if type(tabledata[colname]) ~= "table" then
				if not missed_field[colname] then
					CCheckData:GetInstance():PrintWrn('配置表'..Data..'字段'..colname..'的检查项配置错误，请找'..tabledata.owner..'修正');
					missed_field[colname] = colname;
				end
				error = true;
			end

			if not error then
				error = not check_data(tabconfig, tabledata[colname], Data, colname, row);
			end
		end
		if not error then
			passcount = passcount + 1;
		end
	end
	
	CCheckData:GetInstance():PrintInfo("check table "..Data.." "..passcount.."/"..rowcount.." successfully!");
	return true;
end

function check_data(tabconfig, v, tablename, fieldname, row)

	if v.type == 'link' then	-- link类型单纯引用其他表格的某个字段
		local data = CCheckData:GetInstance():GetNumber(tabconfig, fieldname, row);	
		if v.invalidvalue == nil or data ~= v.invalidvalue then					--	如果是无效值, 则跳过
			local object_data = GetDataFromTable( v.refertable, data, v.referfield)  	-- data[k] k的取值为nTemplateID,szName...
			if object_data == nil then -- 说明对应的表没有配
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'所引用的值在配置表'..v.refertable..'的'..v.referfield..'字段中无法找到，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
		end
		
	elseif v.type == 'number' then											-- number类型单纯为数字范围检查，不关联其他表格
		local data = CCheckData:GetInstance():GetNumber(tabconfig, fieldname, row);
		if v.invalidvalue == nil or data ~= v.invalidvalue then					--	如果是无效值, 则跳过
			if v.min ~= nil and data < v.min then 								-- 说明所配数据超出范围
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的数值小于了设定的最小值'..tostring(v.min)..'，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
			if v.max ~= nil and data > v.max then 								-- 说明所配数据超出范围
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的数值大于了设定的最大值'..tostring(v.max)..'，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
		end
	elseif v.type == 'string' then											-- string 类型单纯为字符串长度检查，不关联其他表格
		local data = CCheckData:GetInstance():GetString(tabconfig, fieldname, row);
		if v.maxlen ~= nil and string.len(data) > v.maxlen then											-- 说明所配数据超出长度
			CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的字符串长度大于了设定的最大值'..tostring(v.maxlen)..'，请找'.._G[tablename..'_define'].owner..'修正');
			return false;
		end
	elseif v.type == 'item' then	-- item类型指定查询item表(referfield1)和equip(referfield2)表中至少有一出现
		local data = CCheckData:GetInstance():GetNumber(tabconfig, fieldname, row);
		
		if data ~= v.default then
			local object_data = GetDataFromTable('item', data, 'ID')
			if object_data == nil then
				object_data = GetDataFromTable('item_armor',  data, 'ID')
				if object_data == nil then
					CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的道具ID '..data..'无法找到，请找'.._G[tablename..'_define'].owner..'修正');
					return false;
				end	
			end
		end
	
	elseif v.type == 'rule' then
		local func = nil;	
		local k1,v1;
		
		for k1,v1 in pairs(ruletable) do
			if v1.rule ==  v.rule then
				func = v1.func;
			end
		end

		if func == nil then 
			local f, msg = loadstring('function CheckRule(tab, rownumber) '.. v.rule .. ' end');
			if f == nil then
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'字段'..fieldname..'的自定义规则脚本无法解析，请找'.._G[tablename..'_define'].owner..'修正');
				return 0;
			end	
								
			local kk = {};
			kk.rule = v.rule;
			kk.func = f;
			table.insert(ruletable, kk);
			func = f;
		end
						
		func();	
		local ret = CheckRule(tabconfig, row);
		if not ret then
			CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的自定义规则检查失败，请找'.._G[tablename..'_define'].owner..'修正');
			return false;
		end
	else
		CCheckData:GetInstance():PrintWrn('配置表'..tablename..'字段'..fieldname..'的检查类型错误，请找'.._G[tablename..'_define'].owner..'修正');
		return false;
	end
	
	return true;
end

function GetDataFromTable(tablename, value, tablefield, value1, tablefield1)	-- 每个DATA_MANAGER GetData()时的key不同,用此函数来在表格tablename的tablefield字段中查找是否有value值

	local tabconfig1 = CCheckData:GetInstance():GetDataByName(tablename);
	
	if  tabconfig1 == nil then
		CCheckData:GetInstance():PrintWrn("无法找到引用的配置表" ..tablename);
		return false;
	end
	
	local rowcount1 = CCheckData:GetInstance():GetTabRowCount(tabconfig1);
	
	if value1 then
		for row1 = 0, rowcount1 - 1 do	-- 遍历每一行	
			if CCheckData:GetInstance():GetNumber(tabconfig1, tablefield1, row1) == value then
				return true;
			end
		end
	end
	
	if  value then	
		for row1 = 0, rowcount1 - 1 do	-- 遍历每一行
			if CCheckData:GetInstance():GetNumber(tabconfig1, tablefield, row1) == value then
				return true;
			end
		end
	end
	
	return false;
end



















