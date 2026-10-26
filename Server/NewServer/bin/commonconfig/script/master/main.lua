LoadPackage("role_data.pkg")
LoadPackage("master_mgr.pkg")
LoadPackage("role_data_mgr.pkg")


g_MasterMgr = CMasterMgr:GetInstance();
g_RoleDataMgr = CRoleDataMgr:GetInstance();



function MakeOneToBeMaster(role_id)
	local pRoleData = g_RoleDataMgr:FindRole(role_id);
	g_MasterMgr:BeMaster(pRoleData);
end



