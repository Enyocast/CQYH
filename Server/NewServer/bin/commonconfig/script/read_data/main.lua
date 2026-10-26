Include("script/stringtable/stringtable.lh");

cache_list = {};

function b(...)
	local ret = 0;
	local param = {...};

	for i,v in ipairs(param) do
		ret = ret + 2 ^ v;
	end

	return ret;
end

function read_int_expr(expr)
    local f, msg;
    local s = 'result = '..expr;
    if not cache_list[s] then
    	f, msg = loadstring(s);
    	if f == nil then
	    	print(msg)
	    end
		f();
	    cache_list[s] = result;
	else
		result = cache_list[s];
	end
	
	return result;
end

function read_str_expr(expr)
    local f, msg;
    local s = 'result = '..expr;
    if not cache_list[s] then
    	f, msg = loadstring(s);
    	if f == nil then
	    	print(msg)
	    end
		f();
	    cache_list[s] = result;
	else
	    result = cache_list[s];
	end
	
	return result;
end


function read_bit_mask(expr)
    local f, msg;
    local s = 'result = b('..expr..')';
    if not cache_list[s] then
    	f, msg = loadstring(s);
    	if f == nil then
	    	print(msg)
	    end
		f();
	    cache_list[s] = result;
	else
	    result = cache_list[s];
	end
	
	return result;
end

function read_quest_var(type, index)
	if index == -1 or type == 0 then
		return -1;
	end
		
	if (type < vtTotal) then	
		return MakeVariableID(type, index);
	else
		return 0;
	end
end

error_list = {};
for k,v in pairs(_G) do
    if string.sub(k,1,3) == 'err' then
        error_list[v] = k;
    end
end

function get_error_name(code)
    if error_list[code] then
        return error_list[code];
    else
        return "unknown error code"
    end
end
