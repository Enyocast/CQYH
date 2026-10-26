Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage('gameworld.pkg')
Include("script/newai/sub_tree/sub_tree.lh")

ROLE_KillNpcValue = 150  ;

function check_time()
	local t = os.date('*t');
	if t.hour >= 17 and t.hour < 18 then
		return brvSuccess;
	end
	
	return brvFail;
end

Include("script/newai/6101_Teleport/main.uh")