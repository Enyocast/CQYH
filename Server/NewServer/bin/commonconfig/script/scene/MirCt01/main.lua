LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("score_def.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("variable.pkg")
LoadPackage("npc.pkg")

Include("script/include/btnod.lua")
Include("script/include/sabac.lh");

local g_oGameWorld = CGameWorld:GetInstance();

-- 沙巴克
function load_all_npc(scene)
	local serverGroup = scene:GetServerGroup();

	for i,v in ipairs(SABAC_NPC_ID_LIST) do
		local npc = scene:FindNpc(v.server_id);
		local hp = g_oGameWorld:GetServerVariable(serverGroup, v.server_var_idx);
		if npc then
			if hp ~= 0 then
				if hp == -1 then
					hp = 0;
				end
				npc:SetHp(hp);
				print("set sabac npc "..v.server_id.." hp to "..hp);
			end
		else
			print("failed to set sabac npc "..v.server_id.." hp");
		end
	end

	local npc = scene:FindNpc(28);    -- 默认写的"28", 没有这个ID的npc
	
	if npc ~= nil then
		npc:SetAlwaysRun(true);
	else
		print("don't find npc 28");
	end

	return brvSuccess
end

Include("script/scene/MirCt01/scene_bt.lua")
