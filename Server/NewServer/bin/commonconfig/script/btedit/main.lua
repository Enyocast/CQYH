LoadPackage("enum.pkg")

function create_tree(parent, t)
    local node = nil;
    local error = false;
    local name;
    local param = {};
    local children = {};

    if t.param then
		for i = 1, 4 do
			if type(t.param[i]) == 'string' then
				param[i] = t.param[i];
			elseif t.param[i] then
				print("error param "..tostring(t.param[i]));
			end
		end
    end

    for k,v in ipairs(t) do
		if type(v) == 'table' then
			if type(k) == 'number' then
			    table.insert(children, v);
			elseif type(k) == 'string' then
				name = k;
			else
			    print("unknown node k="..tostring(k)..", v="..tostring(v));
			end
		else
			if type(v) == 'string' then
				name = v;
			else
			    print("unknown node k="..tostring(k)..", v="..tostring(v));
			end
		end
    end

    if name then
        node = create_bt_edit_node(parent, name, param[1], param[2], param[3], param[4]);
    end
    
    if node then
        for k,v in ipairs(children) do
            local _, child_error = create_tree(node, v);
            if child_error then
				print('failed to create child node of node '..name);
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

function read_tree(file_name)
	print('read tree'..file_name);
	local text = read_tree_file(file_name);

--	new_text = string.gsub(text, "Include%(\"(.-)\"%)", function (s)
--			return read_tree(s);
--		end
--	);

	return text
end

function load_tree_file(file_name)
	local text = read_tree(file_name);
	
	if text then
		text = string.gsub(text, "param%s*=%s*{(.-)}", function (s)
				return "param = {"..string.gsub(s..",", "%s*([_%w]-)%s*,", "\"%1\", ").."}";
			end
		);
		text = string.gsub(text, "{%s*([_%w]-)%s*,", function (s)
				return "{ '"..s.."',";
			end
		);
		text = string.gsub(text, "{%s*([_%w]-)%s*}", function (s)
				return "{ '"..s.."'}";
			end
		);
		text = string.gsub(text, "('\")", "'");
		text = string.gsub(text, "(\"')", "'");
		print_content(text);
	else
		print('cannot read tree file '..file_name);
		return false;
	end
	
	local f, msg = loadstring(text);
	if not f then
		print('failed to load string '..msg);
		return false;
	end
	
	f();
	
	for k,v in pairs(_G) do
		if type(v) == 'table' then
			if k == "evtAIIdle" then
				print("found ")
				for kk,vv in pairs(v) do
					print("kk="..tostring(kk)..", vv="..tostring(vv));
				end
			end
			local node, error = create_tree(nil, v);

			if error then
				if node then
					print_tree(node);
					destroy_tree(node);
				end
			else
				add_tree(k, node);
				print( "created tree "..k);
				print_tree(node);
			end
		end
	end
	
end

function get_enum_values(enum)
	if _G[enum] and type(_G[enum]) == 'table' then
		local s = '';
		
		for k,v in pairs(_G[enum]) do
			s = s..k..",";		
		end
		return s
	end
end