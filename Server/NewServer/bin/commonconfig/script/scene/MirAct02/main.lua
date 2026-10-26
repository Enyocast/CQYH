LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("item_bag.pkg")

Include("script/include/btnod.lua")

local g_oGameWorld = CGameWorld:GetInstance();

function send_kill_info(owner)
	local role =  g_oGameWorld:FindValidRole(get_ctx_role_id());
	local killer = g_oGameWorld:FindValidRole(role:GetLastCasterID());
	if role and killer then
		local message = "您已成功击杀了"..role:GetName().."，获得7000金币奖励";
		local ret = role:Say(killer:GetObjID(), cltNormal, message);
		if ret then
			return brvSuccess;
		end
	end

	return brvFail;
end

Include("script/scene/MirAct02/scene_bt.lua")

