LoadPackage('ai.pkg');
LoadPackage('scene.pkg');

g_param_func_counter = 1;

function get_func_name(f)
    for k,v in pairs(_G) do
        if v == f then
            return k;
        end
    end
end

function create_node_from_table(parent, t)
    local node = nil;
    local error = false;
    local nodeType = btInvalid;
    local name;
    local param;
    local flag = 0;
    local bitflag = {1, 2, 4, 8};
    local children = {};

    if t.param then
		param = {};
		for i = 1, 4 do
			if type(t.param[i]) == 'string' then
				param[i] = g_param_func_counter;
				local f,s = loadstring("function ParamFunc"..param[i].."(o) return "..t.param[i].." end");
				if f then
					f();
				else
					print("function ParamFunc"..param[i].."(o) return "..t.param[i].." end");
					print('failed to load string '..s);
				end
				g_param_func_counter = g_param_func_counter + 1;
				flag = flag + bitflag[i];
				--print(flag);
			elseif type(t.param[i]) == 'boolean' then
				if t.param[i] then
					param[i] = 1;
				else
					param[i] = 0;
				end
			else
				param[i] = t.param[i];
			end
		end
    else
        param = {0, 0, 0, 0};
    end

    for k,v in pairs(t) do
    	if type(v) == 'string' and string.sub(v, 1, 3) == 'on_' then
    		v = _G[v];
    	end
        if k == 'param' then
        
		elseif type(v) == 'table' then
		    table.insert(children, v);
		else
			if type(v) == 'function' then
				name = get_func_name(v);
				nodeType = find_bt_action_id(name);
				if not nodeType then
				    nodeType = register_bt_action(name);
				end
			elseif type(v) == 'number' then
				nodeType = v;
				name = tostring(nodeType);
	        elseif v == nil then
	        
			else
			    print("unknown node k="..tostring(k)..", v="..tostring(v));
			end
		end
    end
    
    if #children == 0 and (nodeType == batSequencer or nodeType == batParallel or nodeType == batSelector) then
        return nil, false;
    end

    if nodeType ~= btInvalid then
        node = create_bt_node(parent, nodeType, name, param[1], param[2], param[3], param[4], flag);
    end
    
    if node then
        for k,v in ipairs(children) do
            local _, child_error = create_node_from_table(node, v);
            if child_error then
				if name then
					print('failed to create child node of node '..name);
				else
					print('failed to create child node of unknown name node ');
				end
				
                error = true;
                break;
            end
        end
    else
		if name then
			print('failed to create node '..name);
		else
			print('failed to create unknown name node ');
		end
        error = true;
    end
    
	return node, error;
end
  
load_ai_data();

function load_behavior_tree(tree_name)
	local node, error = create_node_from_table(nil, _G[tree_name]);
	if error then
	    print_bt(node);
	    destroy_behavior_tree(node);
	    print( "bt tree:"..tree_name.." error");
	    return;
	else
	    return node;
	end
end
