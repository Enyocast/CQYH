LoadPackage("item_bag.pkg");
LoadPackage("item.pkg");
LoadPackage("role.pkg");
LoadPackage("attr_list.pkg")
LoadPackage("title.pkg")
LoadPackage("quest_list.pkg")
LoadPackage("error_def.pkg")
LoadPackage("char_def.pkg");
LoadPackage("hero.pkg");
LoadPackage("data_manager.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("global_config.pkg")
LoadPackage("scene_def.pkg")
LoadPackage("spell_book.pkg")
LoadPackage("spell.pkg")
LoadPackage("scene.pkg")
LoadPackage("master.pkg")
LoadPackage("character.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("doodad.pkg")

g_oGameWorld = CGameWorld:GetInstance();
g_oGuildMgr = CGuildMgr:GetInstance();

function OnOpenBaseWarDoodad(doodad, role)
	local scene = role:GetScene();
	if scene:GetVariable(1) > 0  then
		local guildid = role:GetGuildID();
		local guild = g_oGuildMgr:FindGuild(guildid);
		if guild then
			scene:Say(cctScene, cltLighting, '<#P0:'..doodad:GetDoodadData().szName..'><#P1:'..guild:GetName()..'><#T:666569>');
		else
			scene:Say(cctScene, cltLighting, '<#P0:'..doodad:GetDoodadData().szName..'><#T:666570>');
		end
		scene:SetVariable(2, guildid);
	end
end

function wmsm_doodad(doodad, role)
	OnOpenBaseWarDoodad(doodad, role);
end

function swxg_doodad(doodad, role)
	OnOpenBaseWarDoodad(doodad, role);
end

function sm_doodad(doodad, role)
	OnOpenBaseWarDoodad(doodad, role);
end

function zmsm_doodad(doodad, role)
	OnOpenBaseWarDoodad(doodad, role);
end
