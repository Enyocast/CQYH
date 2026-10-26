Include("script/stringtable/stringtable.lh");

clear_string_table();

for k,v in ipairs(STRING_ENUM_TABLE) do
	local ret_code = register_string(_G[v.enum], v.str);
	if( ret_code == FALSE ) then
		print( "read string table error, string: k=".._G[v.enum]..", v="..v.str);
	end
end
