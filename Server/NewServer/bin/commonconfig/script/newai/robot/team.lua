
function do_team_action(owner)
	local processor = owner:GetAIProcessor();
    
    g_RobotMessageHandler:SetTeamAuto(true);
    
    local role = tolua.cast(processor:GetOwner(), 'CRole');
    local role_id = role:GetObjID();
    local scene = role:GetScene();
    local team;
	if role:GetTeamID() > 0 then
		team = g_GameWorld:FindTeam(role:GetTeamID());
	end

	if team then
		local rand_value = math.random(1, 2);

		if rand_value == 1 then
			g_RobotMessageHandler:DoTeamLeave(role, role_id);
		elseif rand_value == 2 then
			local leader_id = team:GetLeaderID();
			if leader_id == role_id then
				local team_member = team:GetMemberTable(math.random(0, team:GetMemberCount() - 1));
				if team_member then
					leader_id = team_member.dwRoleID;
				end
				local member_count = math.random(team:GetMemberCount(), MAX_TEAM_MEMBER_COUNT);
				local assign_type = math.random(etaInvalid + 1, etaTotal - 1);
				local color_limit = team:GetAuctionItemColorLimit();

				g_RobotMessageHandler:DoTeamChangeInfo(role, member_count, assign_type, leader_id, color_limit);
			end
		end

	else
	    local rand_value = math.random(1, 4);
	
		if rand_value == 1 then
			g_RobotMessageHandler:DoTeamJoin(role, role_id);
		elseif rand_value == 2 then
			g_RobotMessageHandler:DoTeamJoinRand(role);
		elseif rand_value == 3 then
			g_RobotMessageHandler:DoAdjacentNoTeamRole(role);
		elseif rand_value == 4 then
			g_RobotMessageHandler:DoAdjacentTeam(role);
		end
	end

    return brvSuccess;
end
