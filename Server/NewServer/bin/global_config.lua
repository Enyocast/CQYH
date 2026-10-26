
Include("globalconfig/commonconfig.lua");
Include("globalconfig/gsconfig.lua");
Include("globalconfig/msconfig.lua");
Include("globalconfig/dbconfig.lua");
Include("globalconfig/lsconfig.lua");
Include("globalconfig/gtconfig.lua");
Include("globalconfig/bsconfig.lua");
Include("globalconfig/dlconfig.lua");
Include("globalconfig/nsconfig.lua");
Include("globalconfig/mmconfig.lua");
Include("globalconfig/mgconfig.lua");
Include("globalconfig/gmconfig.lua");
Include("globalconfig/obj_pool_config.lua");
Include("globalconfig/group_config.lua");

Include("globalconfig/gameworldconfig.lua");
Include("globalconfig/guildconfig.lua");
Include("globalconfig/newroleconfig.lua");

Include("globalconfig/asimovconfig.lua");

Include("globalconfig/area_config.lua");

Include("globalconfig/gmsecurityconfig.lua");


-- 自定义配置, 自己新加配置

Include("globalconfig/additional_spawn_npc.lua");

--


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

LoadAreaConfig(AreaConfig, ServerConfig);

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

for i = 0, MAX_SERVER_GROUP_COUNT - 1 do
	local y, m , d = string.match(ServerConfig.GroupConfig[i].szStartDate, "(%d+)%-(%d+)%-(%d+)"); 
	ServerConfig.GroupConfig[i].dwStartDate = os.time({year = y, month = m, day = d, hour = 0});
--	print("loaded group "..i.." start date "..y.."-"..m.."-"..d.." "..ServerConfig.GroupConfig[i].dwStartDate);
end