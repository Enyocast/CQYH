Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("npc.pkg")
LoadPackage("scene.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage('gameworld.pkg');
LoadPackage("role.pkg");
LoadPackage("title.pkg");

	
local g_oGameWorld = CGameWorld:GetInstance();
local Top_Power = 0;

function get_power(owner)
	return Top_Power;
end

function Occupied_Top(owner)
	local role = g_oGameWorld:FindValidRole(get_ctx_role_id());
	local role_power = role:GetPow();
	if role_power > Top_Power then
		Top_Power = role_power;
		return brvSuccess;
	end
	return brvFail;
end

Include("script/newai/sub_tree/sub_tree.lh")
Include("script/newai/8611/main.uh")


