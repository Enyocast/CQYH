Include("script/stringtable/stringtable.lh")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
Include("script/newai/sub_tree/sub_tree.lh");
LoadPackage("chat_def.pkg")
LoadPackage('variable.pkg')

function get_role_var(owner, index)
	local roleid = get_ctx_role_id();
	local role = CGameWorld:GetInstance():FindValidRole(roleid);
	return role:GetVariable(index);
end


Include("script/newai/6156_Baozang/main.uh")


