Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
Include("script/newai/sub_tree/sub_tree.lh")
LoadPackage("npc.pkg")
LoadPackage("scene.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("item.pkg")
LoadPackage("item_bag.pkg")
LoadPackage('gameworld.pkg');
LoadPackage("global_config.pkg")
LoadPackage("role.pkg");
LoadPackage("title.pkg");
local g_oGameWorld = CGameWorld:GetInstance();

function check_time(owner)
	local hour = os.date("%H",os.time());
	if 19 <= tonumber(hour) and tonumber(hour)< 23  then
		return brvSuccess;
	else
		return brvFail;
	end
end
Include("script/newai/200_Teleport/main.uh")