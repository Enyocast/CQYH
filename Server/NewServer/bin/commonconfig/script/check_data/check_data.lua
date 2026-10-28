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

-- Type values include number, string, link, object, and union
-- number: numeric field not referencing other tables; nonzero count denotes an array; omitted min/max bounds are not checked
-- string: text field not referencing other tables; nonzero count denotes an array; maxlen specifies maximum length
-- link: non-struct field referencing another table; nonzero count denotes an array; refertable names that table and referfield names its corresponding field
-- rule: custom validation expression evaluated with the data
-- item: special type requiring the value to appear in the item or equip table

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
	
	for row = 0, rowcount - 1 do	-- Iterate each row
		local error = false;
		for col = 0, colcount - 1 do	-- Iterate each row
		
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

	if v.type == 'link' then	-- A link references a field in another table
		local data = CCheckData:GetInstance():GetNumber(tabconfig, fieldname, row);	
		if v.invalidvalue == nil or data ~= v.invalidvalue then					--	Skip invalid values
			local object_data = GetDataFromTable( v.refertable, data, v.referfield)  	-- data[k], where k may be nTemplateID, szName, etc.
			if object_data == nil then -- The corresponding table entry is not configured
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'所引用的值在配置表'..v.refertable..'的'..v.referfield..'字段中无法找到，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
		end
		
	elseif v.type == 'number' then											-- number checks numeric range without referencing other tables
		local data = CCheckData:GetInstance():GetNumber(tabconfig, fieldname, row);
		if v.invalidvalue == nil or data ~= v.invalidvalue then					--	Skip invalid values
			if v.min ~= nil and data < v.min then 								-- Configured value is out of range
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的数值小于了设定的最小值'..tostring(v.min)..'，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
			if v.max ~= nil and data > v.max then 								-- Configured value is out of range
				CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的数值大于了设定的最大值'..tostring(v.max)..'，请找'.._G[tablename..'_define'].owner..'修正');
				return false;
			end
		end
	elseif v.type == 'string' then											-- string checks length without referencing other tables
		local data = CCheckData:GetInstance():GetString(tabconfig, fieldname, row);
		if v.maxlen ~= nil and string.len(data) > v.maxlen then											-- Configured value exceeds the length limit
			CCheckData:GetInstance():PrintWrn('配置表'..tablename..'第'..row..'行字段'..fieldname..'的字符串长度大于了设定的最大值'..tostring(v.maxlen)..'，请找'.._G[tablename..'_define'].owner..'修正');
			return false;
		end
	elseif v.type == 'item' then	-- item must appear in at least one of the item (referfield1) or equip (referfield2) tables
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

function GetDataFromTable(tablename, value, tablefield, value1, tablefield1)	-- Each DATA_MANAGER GetData() uses a different key; find value in the tablefield field of tablename

	local tabconfig1 = CCheckData:GetInstance():GetDataByName(tablename);
	
	if  tabconfig1 == nil then
		CCheckData:GetInstance():PrintWrn("无法找到引用的配置表" ..tablename);
		return false;
	end
	
	local rowcount1 = CCheckData:GetInstance():GetTabRowCount(tabconfig1);
	
	if value1 then
		for row1 = 0, rowcount1 - 1 do	-- Iterate each row
			if CCheckData:GetInstance():GetNumber(tabconfig1, tablefield1, row1) == value then
				return true;
			end
		end
	end
	
	if  value then	
		for row1 = 0, rowcount1 - 1 do	-- Iterate each row
			if CCheckData:GetInstance():GetNumber(tabconfig1, tablefield, row1) == value then
				return true;
			end
		end
	end
	
	return false;
end



















