
Include("guardconfig/guardconfig.lua");
Include("guardconfig/guard_area_config.lua");

table_stack = {};
function get_table_stack()
    local s = '';
    for i, tn in ipairs(table_stack) do
        s = s..tn..'.'
    end
    return s;
end

function LoadAreaConfig(src, dst)
    for k,v in pairs(src) do
        if dst[k] == nil then
            print('area config '..get_table_stack()..k.." is nil");
        else
            if type(v) == 'table' then
                table.insert(table_stack, k);
				LoadAreaConfig(src[k], dst[k]);
				table.remove(table_stack);
            else
                dst[k] = v;
            end        
        end
    end
end

LoadAreaConfig(GuardAreaConfig, GuardConfig);

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

function LoadFile(config, config_name)
    print('loading '..config_name);
	LoadTraverseTable(config, _G[config_name]);
end

