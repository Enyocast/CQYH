Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("gamble.pkg")
LoadPackage("npc.pkg")
LoadPackage('gameworld.pkg');
LoadPackage("role.pkg");
LoadPackage("character.pkg");
Include("script/newai/sub_tree/sub_tree.lh");
Include("script/newai/6898_Rune/main.uh")

local g_oGameWorld = CGameWorld:GetInstance();

--[[
function Mingwenputong(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local class = role:GetClass();
	if class == 0 then
		local value = role:GetGamble():GetValue(12,0);
		return value;
	elseif class == 1 then	
		local value = role:GetGamble():GetValue(13,0);
		return value;
	elseif class == 4 then
		local value = role:GetGamble():GetValue(16,0);
		return value;
	end
	return 0;
end

function Mingwengaoji(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local class = role:GetClass();
	if class == 0 then
		local value = role:GetGamble():GetValue(12,1);
		return value;
	elseif class == 1 then	
		local value = role:GetGamble():GetValue(13,1);
		return value;
	elseif class == 4 then
		local value = role:GetGamble():GetValue(16,1);
		return value;
	end
	return 0;
end
]]--



ROLE_LEVEL_LIMIT = 25;

