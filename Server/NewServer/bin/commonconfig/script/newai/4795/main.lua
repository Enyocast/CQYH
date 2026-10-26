LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
Include("script/stringtable/stringtable.lh")
Include("script/newai/sub_tree/sub_tree.lh");
LoadPackage("chat_def.pkg")

function check_time()
	local t = os.date('*t');
	if t.hour >= 03 and t.hour < 24 then
		return brvSuccess;
	end
	
	return brvFail;
end

Include("script/newai/4795/main.uh")


