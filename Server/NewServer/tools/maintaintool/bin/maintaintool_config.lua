
Include("toolconfig/maintainconfig.lua");

table_stack = {};
function get_table_stack()
    local s = '';
    for i, tn in ipairs(table_stack) do
        s = s..tn..'.'
    end
    return s;
end

function LoadTraverseTable(d, t)
    for k,v in pairs(t) do
		if d[k] == nil then
  			print("variable "..get_table_stack()..k.." is nil");
		else
			if type(v) == "table" then
                table.insert(table_stack, k);
				LoadTraverseTable(d[k], v)
				table.remove(table_stack);
			else
				d[k] = t[k];
			end
		end
    end
end

function SaveTraverseTable(d, t)
    for k,v in pairs(t) do
		if d[k] == nil then
			print("variable "..k.." is nil")
		else
			if type(v) == "table" then
				SaveTraverseTable(d[k], v)
			else
				t[k] = d[k];
			end
		end
    end
end

function LoadFile(config, config_name)
    print('loading '..config_name);
	LoadTraverseTable(config, _G[config_name]);
end

function SaveFile()
    
end


