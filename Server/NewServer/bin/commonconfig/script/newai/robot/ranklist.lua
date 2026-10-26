Include("script/include/btnod.lua")
LoadPackage("role.pkg")
LoadPackage("robot_message_handler.pkg")
LoadPackage("gameworld.pkg")

function performance_ranklist_query(owner)

	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
	local ranktype = math.random(24);	-- role ranklist total type
	local rankpage = math.random(20);
	
	g_RobotMessageHandler:DoQueryRanklist(role, ranktype, rankpage);
	
	return brvSuccess;
end