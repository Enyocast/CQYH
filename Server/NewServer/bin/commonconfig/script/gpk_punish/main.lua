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
LoadPackage("character.pkg");
LoadPackage("chat_def.pkg")

g_oGameWorld = CGameWorld:GetInstance();

function main(role, kick_count, kick_count_max)
	print("gpk punish script: " .. role:GetName() .. ", " .. kick_count .. ", " .. kick_count_max);
end
