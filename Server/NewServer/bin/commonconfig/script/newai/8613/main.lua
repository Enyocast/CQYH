LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("scene.pkg")
LoadPackage("variable.pkg")
LoadPackage("npc.pkg")
LoadPackage("ai.pkg")

Include("script/newai/sub_tree/sub_tree.lh");
Include("script/include/sabac.lh");

local g_oGameWorld = CGameWorld:GetInstance();


function save_all_npc(owner)
	local scene = owner:GetScene();
	local serverGroup = scene:GetServerGroup();
	for i,v in ipairs(SABAC_NPC_ID_LIST) do
		local npc = scene:FindNpc(v.server_id);
		if npc then
			local hp = npc:GetHp();
			if hp == 0 then
				hp = -1;
			end
			g_oGameWorld:SetServerVariable(serverGroup, v.server_var_idx, true, hp);
		else
			g_oGameWorld:SetServerVariable(serverGroup, v.server_var_idx, true, -1);
		end
	end
	return brvSuccess
end

Include("script/newai/8613/main.uh")
