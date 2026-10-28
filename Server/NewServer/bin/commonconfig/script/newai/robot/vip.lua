function do_vip_action(owner)
	local processor = owner:GetAIProcessor();
    local role = Cast(processor:GetOwner(), 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:SubscribeVIP(math.random(vlLevel1, vlLevel3), math.random(1, MAX_VIP_MONTH - 1));

end