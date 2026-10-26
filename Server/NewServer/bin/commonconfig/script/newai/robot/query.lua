
function do_query_role_detail_data(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());
	local another_user = CUserMgr:GetInstance():RandAnotherUser(user);
	if another_user == nil then
		return
	end

	local role = another_user:GetPlayingRole();
	if role then
		local ret = user:QueryRoleDetailData(role:GetObjID());
		if ret then
			return brvSuccess;
		end
	end

	return brvFail;
end

function do_query_role_pow(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());
	local target_id = processor:GetTargetID();
	if target_id ~= 0 then
		local ret = user:QueryRolePow(target_id);
		if ret then
			return brvSuccess;
		end
	end

	return brvFail;
end

function do_update_client_variable(owner)
	local processor = owner:GetAIProcessor();
    local role = tolua.cast(processor:GetOwner(), 'CRole');
    local user =  CUserMgr:GetInstance():FindUser(role:GetSessionID());

	user:UpdateClientVariable(math.random(0, MAX_CLIENT_VARIABLE_COUNT), math.random(0, 100000000));

end