
function do_chat_action(owner)
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local chance = math.random(10000);
    local ChatTargetID = owner:GetObjID();
    
	if chance < 100 then
		ChatTargetID = cctGroup;
	elseif chance < 3200 and role:GetTeamID() > 0 then
		ChatTargetID = role:GetTeamID();
	elseif chance < 5200 then
		ChatTargetID = cctScreen;
	else
		ChatTargetID = owner:GetObjID();
	end
	
	owner:Say(ChatTargetID, cltNormal, g_ChatString);
	
    return brvSuccess;
end
