LoadPackage("common.pkg")
LoadPackage("ms_guild.pkg")
LoadPackage("ms_guild_mgr.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("ms_chat.pkg")

--Include("script/include/activity.lh")

g_MSGuildMgr = CMsGuildMgr:GetInstance();


--------------------------------------------------------------------------------------
-- 功能：发送固定内容
-- 参数说明：
-- 第一参数，第二参数，第三参数， 固定拷贝即可
-- 第四参数, 公告对象：
--			guild_id:  对公会
--          cctGroup：全服
-- 第五参数，公告显示的位置
--			cltLighting: 走马灯
-- 			cltTvShow: 电视机
--          cltTrumpet: 喇叭

function TrySay(group_id, guild_level, lighting_id, targetID, location)
	local text = "<#T:"..lighting_id..">";
	local ret = CMSChatMgr:GetInstance():Say(0, targetID, location, text, group_id);
end
--------------------------------------------------------------------------------------


--------------------------------------------------------------------------------------
-- 功能：发送包括公会名在内的内容
-- 参数说明：
-- 第一参数，第二参数，第三参数，第四参数 固定拷贝即可
-- 第五参数, 公告对象：
--			guild_id:  对公会
--          cctGroup：全服
-- 第六参数，公告显示的位置
--			cltLighting: 走马灯
-- 			cltTvShow: 电视机
--          cltTrumpet: 喇叭

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

---运镖
function OpenActivity_1(group_id, guild_id, guild_level, lighting_id)
	TrySayWithGuild(group_id, guild_id, guild_level, lighting_id, cctGroup, cltLighting);
end


---妖兽
function OpenActivity_2(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end


---温泉
function OpenActivity_3(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end


---祈祷
function OpenActivity_4(group_id, guild_id, guild_level, lighting_id)
	TrySay(group_id, guild_level, lighting_id, guild_id, cltLighting);
end









