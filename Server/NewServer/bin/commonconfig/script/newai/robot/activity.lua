Include("script/include/btnod.lua")
Include("role.pkg")
Include("robot_message_handler.pkg")

function performance_activity_reward(owner)

	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
	local session_id = user:GetSessionID();		

	for acrivity_index = 1, 32 do
		local activityrewarddata = CDataManager_ACTIVITY_REWARD_DATA_:GetInstance():GetData(acrivity_index);	
		if activityrewarddata ~= nil then
			if role:GetActivityRewardByIndex(acrivity_index) == false and role:GetActivity() >= activityrewarddata.nActivityValue then
				local ret = g_RobotMessageHandler:DoActivityReward(role, acrivity_index);
				check(ret, "failed to send activity reward");					
			
				msg = recv_msg(5, session_id, protocol.g2c_activity_reward);
				check(msg, "failed to recv g2c_activity_reward");			
			end
		end
	end
	
	return brvSuccess;
end