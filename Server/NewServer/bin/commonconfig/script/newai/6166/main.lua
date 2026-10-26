Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("npc.pkg")
LoadPackage("scene.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")

g_oGuildMgr = CGuildMgr:GetInstance();

function say_end_text(owner)
	local scene = owner:GetScene();
	local guildid = scene:GetVariable(2);
	local guild = g_oGuildMgr:FindGuild(guildid);
	if guild then
		print(guild:GetName());
		scene:Say(cctServer, cltLighting, '<#P0:'..guild:GetName()..'><#T:666574>');
	end
	return brvSuccess;
end

Include("script/newai/sub_tree/sub_tree.lh");
Include("script/newai/6166/main.uh");
