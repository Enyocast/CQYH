LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("score_def.pkg")

Include("script/include/btnod.lua")

local g_oGameWorld = CGameWorld:GetInstance();
function Check_V1(owner)
	local role =  g_oGameWorld:FindValidRole(get_ctx_role_id());
 -- local killer = g_oGameWorld:FindValidRole(role:GetLastCasterID());
	local TI = role:GetVariable(1004);
	local a = math.fmod(TI,2);
	if a == 0 then 
		return brvSuccess
	end	
	return brvFail
end

function Check_V2(owner)
	local role =  g_oGameWorld:FindValidRole(get_ctx_role_id());
 -- local killer = g_oGameWorld:FindValidRole(role:GetLastCasterID());
	local TI = role:GetVariable(1004);
	local a = math.fmod(TI,2);
	if a == 0 then 
		return brvFail
	end	
	return brvSuccess
end
Include("script/scene/MirDg25/scene_bt.lua")

