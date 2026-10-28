Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
Include("script/newai/sub_tree/sub_tree.lh")


--[[    --check time
function check_time()
	local t = os.date('*t');
	if t.hour >= 17 and t.hour < 18 then
		return brvFail;
	end
	
	return brvSuccess;
end
]]--
Include("script/newai/6863_Guild/main.uh")