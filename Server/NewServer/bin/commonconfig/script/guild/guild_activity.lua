LoadPackage("common.pkg")
LoadPackage("ms_guild.pkg")
LoadPackage("ms_guild_mgr.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("ms_chat.pkg")

--Include("script/include/activity.lh")

g_MSGuildMgr = CMsGuildMgr:GetInstance();


--------------------------------------------------------------------------------------
-- Function: send fixed content
-- Parameters:
-- Copy the first three parameters unchanged
-- Fourth parameter: announcement audience
--			guild_id: guild audience
--          cctGroup: entire server
-- Fifth parameter: announcement display location
--			cltLighting: scrolling announcement
-- 			cltTvShow: screen announcement
--          cltTrumpet: trumpet

function TrySay(group_id, guild_level, lighting_id, targetID, location)
	local text = "<#T:"..lighting_id..">";
	local ret = CMSChatMgr:GetInstance():Say(0, targetID, location, text, group_id);
end
--------------------------------------------------------------------------------------


--------------------------------------------------------------------------------------
-- Function: send content containing the guild name
-- Parameters:
-- Copy the first four parameters unchanged
-- Fifth parameter: announcement audience
--			guild_id: guild audience
--          cctGroup: entire server
-- Sixth parameter: announcement display location
--			cltLighting: scrolling announcement
-- 			cltTvShow: screen announcement
--          cltTrumpet: trumpet

function TrySayWithGuild(group_id, guild_id, guild_level, lighting_id, targetID, location)
	local guild = g_MSGuildMgr:FindGuildByID(guild_id);
	local text = "<#T:"..lighting_id.."><#P0:"..guild:GetName()..">";
	local ret = CMSChatMgr:GetInstance():Say(0, targetID, location, text, group_id);
end
--------------------------------------------------------------------------------------


------------------example----------------
function example(group_id, guild_id, guild_level, lighting_id)
	TrySayWithGuild(group_id, guild_id, guild_level, lighting_id, guild_id, cltLighting);
end
-----------------------------------------


-- common

---Escort
function OpenActivity_1(group_id, guild_id, guild_level, lighting_id)
	TrySayWithGuild(group_id, guild_id, guild_level, lighting_id, cctGroup, cltLighting);
end


---Demon beast
function OpenActivity_2(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end


---Hot spring
function OpenActivity_3(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end


---Prayer
function OpenActivity_4(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end









