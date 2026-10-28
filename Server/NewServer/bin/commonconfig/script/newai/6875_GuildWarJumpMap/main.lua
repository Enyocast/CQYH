LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("npc.pkg")
LoadPackage("role.pkg")
LoadPackage("guild_mgr.pkg")
LoadPackage("gs_guild.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("guild_config.pkg")
Include("script/newai/sub_tree/sub_tree.lh")
Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("guild_def.pkg")
LoadPackage("global_config.pkg")


gameworld = CGameWorld:GetInstance();
guildmgr = CGuildMgr:GetInstance();


SceneTemplateID = g_GuildConfig.dwSceneTemplateID;
ServerPoint = g_GuildConfig.dwServerPoint;

function GetTargetGuildSceneID(owner)
	local processor = owner:GetAIProcessor();
	local npc = Cast(processor:GetOwner(), 'CNpc');

	local role_id = get_ctx_role_id();
	local role = gameworld:FindRole(role_id);

	local war_data = guildmgr:FindWarByAttackGuildID(role:GetGuildID());

	return war_data.dwDefenderID;
end


Include("script/newai/6875_GuildWarJumpMap/main.uh")

