LoadPackage("chat_def.pkg")
LoadPackage("global_config.pkg")
LoadPackage("arena_mgr.pkg")
LoadPackage("ranklist.pkg")

Include("script/include/activity.lh")
Include("script/final_gm/ms.lua")
Include("script/activity/spawn_npc.lua")
Include("script/arena/main.lua");
Include("script/guild/main.lua");


-- Heavenly Fortune: double experience and drops
--[[
function enable_exp_drop_rate()
	SetExpRate(20000);
	SetDropRate(20000);

	local message = "天降鸿福活动已经开启，活动期间全服开启双倍经验和双倍掉落";
	for i = 1 , 3 do
		say(cctServer, cltLighting, message);
		wait(60);
	end
end
function disable_exp_drop_rate()
	local message = "天降鸿福活动即将结束";
	for i = 1 , 3 do
		say(cctServer, cltLighting, message);
		wait(60);
	end

	SetExpRate(10000);
	SetDropRate(10000);
end
]]--

--Bichon Arena
--[[
--Bichon Arena opens
function enable_bqlt()
	local msg = "比奇省【龙飞】已设下擂台，激烈的比拼将在20点正式开始，各位勇士赶快前往报名一展身手吧！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
--Bichon Arena ends
function disable_bqlt()
	local msg = "本期擂台比拼即将于20点40分结束，参赛者可前去比奇省演武场内寻找【吉叔】抽取奖金！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
-- Bichon Arena rewards
function enable_bqltlj()
	local msg = "通往幽冥海的传送阵即将开启，使者【神秘法师】在盟重码头附近等待勇士们前去相助！"
	for i =1 , 3 do
		say(cctServer, cltNormal, msg);
		wait(15)
	end
end
function disable_bqltlj()
	local msg = "擂台奖金的抽取即将于24点结束，勇士们不要错失良机！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
]]--

-- Streamer brawl
--[[
function zhubo_luandouop()
	local msg = "主播乱斗活动将于 20：00 开启，请各位参赛的主播在随机长廊做好准备，通过传送员阿贵即可进入活动地图"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
function zhubo_luandoucl()
	local msg = "主播乱斗活动将于 21：00 结束，请勇士们做好退出准备"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
]]--


--Big Gray Wolf
--[[
function enable_dhl()
	-- say(cctServer, cltLighting, message);
	local msg = "巧辨真假大灰狼活动将于19点00分正式开启，【大灰狼】将在沙巴克刷新，赶快找到他！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

function disable_dhl()
	-- say(cctServer, cltLighting, message);
	local msg = "巧辨真假大灰狼活动将于19点15分正式关闭，【大灰狼】将停止刷新，赶快找到他！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

function spawn_dhl()
	-- say(cctServer, cltLighting, message);
	local msg = "巧辨真假大灰狼活动正在进行中，【大灰狼】刚刚空降到沙巴克，赶快找到他！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
]]--


-- Experience Arena opens in 5 minutes
function enable_exp_arena()
	local msg = "经验武斗场的大门5分钟后开启，盟重一位【神秘剑客】邀你前往，机不可失！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
-- Experience Arena closes in 5 minutes
function disable_exp_arena()
	local msg = "经验武斗场将在5分钟后关闭，请武斗场内的勇士们做好退出准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

-- Royal Treasury opens in 5 minutes
function enable_treasure_arena()
	local msg = "皇室宝库将在5分钟后开启，勇士们可前往盟重安全区寻找【讲古老人】报名参与！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
-- Royal Treasury closes in 5 minutes
function disable_treasure_arena()
	local msg = "皇室宝库将在5分钟后关闭，请宝库内的勇士们做好退出准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
-- Greed Demon King appears in Royal Treasury
function spawn_treasure_boss()
	local msg = "贪婪魔王即将出现在皇室宝库内，勇士们可在盟重安全区寻找【讲古老人】前往讨伐！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

function guild_war()
	local msg = "行会战活动将在十分钟之后开启，请前往盟重安全区内的工会使者处进入地图！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

function new_year()
	local msg = "牛年活动将于十分钟后开启，请玩家前往沙巴克地图参加活动！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

--Guild stronghold battle starts in 5 minutes
function enable_jdz()
	local msg = "公会据点争夺战5分钟后开始，各位勇士可以前往沃玛寺庙二层、死亡峡谷虫巢、石墓四层、祖玛四层进行争夺！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
--Guild stronghold battle ends in 5 minutes
function disable_jdz()
	local msg = "公会据点争夺战5分钟后结束！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end


---------------------------------------------------------Boss spawn--------------------------------


-- Zhulong God/Hongmo Leader/Woma Leader 30 minutes
function spawn_cl_hm_wm()
	local msg = "[触龙神]将于30分钟后出现在[死亡峡谷六层]、[虹魔教主]将于30分钟后出现在[虹魔教坛]、[沃玛教主]将出现在[沃玛寺庙三层]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Zhulong God/Hongmo Leader/Woma Leader 10 minutes
function spawn_cl_hm_wm_2()
	local msg = "[触龙神]将于10分钟后出现在[死亡峡谷六层]、[虹魔教主]将于10分钟后出现在[虹魔教坛]、[沃玛教主]将出现在[沃玛寺庙三层]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end

-- Zuma Leader 30 minutes
function spawn_zm()
	local msg = "30分钟后，[祖玛教主]将出现在[祖玛教主之家]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Zuma Leader 10 minutes
function spawn_zm_2()
	local msg = "10分钟后，[祖玛教主]将出现在[祖玛教主之家]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end

-- Chiyue Demon 30 minutes
function spawn_cyem()
	local msg = "[赤月恶魔]将于30分钟后出现在[赤月魔穴]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Chiyue Demon 10 minutes
function spawn_cyem_2()
	local msg = "[赤月恶魔]将于10分钟后出现在[赤月魔穴]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end

-- Flame Demon 30 minutes
function spawn_lyem()
	local msg = "[烈焰恶魔]将于30分钟后出现在[赤月魔穴]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Flame Demon 10 minutes
function spawn_lyem_2()
	local msg = "[烈焰恶魔]将于10分钟后出现在[赤月魔穴]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end


-- Huangquan Leader/Bull Demon King 30 minutes
function spawn_hq_nm()
	local msg = "[黄泉教主]将于30分钟后出现在[骨魔洞五层]、[牛魔王]将于30分钟后出现在[牛魔寺庙大厅]，勇士们前往讨伐！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end
-- Huangquan Leader/Bull Demon King 10 minutes
function spawn_hq_nm_2()
	local msg = "[黄泉教主]将于10分钟后出现在[骨魔洞五层]、[牛魔王]将于10分钟后出现在[牛魔寺庙大厅]，勇士们前往讨伐！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(15)
	end
end

-- Demon Dragon Leader 30 minutes
function spawn_mljz()
	local msg = "[魔龙教主]将于30分钟后出现在[魔龙血域]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Demon Dragon Leader 10 minutes
function spawn_mljz2()
	local msg = "[魔龙教主]将于10分钟后出现在[魔龙血域]，请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end

-- Fortune Golden Pig 30 minutes
function spawn_zcjz()
	local msg = "30分钟后，[招财金猪]将出现在[盟重安全区]附近,请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Fortune Golden Pig 10 minutes
function spawn_zcjz2()
	local msg = "10分钟后，[招财金猪]将出现在[盟重安全区]附近,请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end
-- Fortune Golden Pig appears
function spawn_zcjz3()
	local msg = "[招财金猪]出现在[盟重安全区]附近,请勇士们做好讨伐准备！"
	for i =1 , 3 do
		say(cctServer, cltLighting, msg);
		wait(20)
	end
end



---------------------------------------------------------------------------------------------------



-----------------------------------------------------Spawn  Sabac Greed Demon King-----------------------------

--[[
function enable_sbk_tlmw()
	local msg = "贪婪魔王将于22点入侵玛法大陆，请诸位勇士前往沙巴克皇宫门前（529，461 附近），迎战魔王！"
	for i =1 , 5 do
		say(cctServer, cltLighting, msg);
		wait(100)
	end

end


function spawn_sbk_tlmw()
	local msg = "贪婪魔王已经现身沙巴克皇宫门前（529，461 附近），请众玛法勇士前往除魔！"
	for i =1 , 5 do
		say(cctServer, cltLighting, msg);
		wait(30)
	end

end

function ChunJie_Boss()
	local message = "2020年春节活动将于十分钟后开始，请前往盟重城寻找携带财宝的金猪，击杀即可获得丰厚奖励哦";
	for i =1 , 5 do
		say(cctServer, cltLighting, message);
		wait(30);
 	end
end
]]--


------------------------------------------------------------------------------------------------------------
--Divine item drawing
function open_dice()
	--local message = "神物行开奖播报";
	--say(cctServer, cltLighting, message);
	-- dice_open();
end

function RankListAward()--Award and clear donation rankings
	SendRankListAward(1, rlActivity01, 1, 1, 8001);
	SendRankListAward(1, rlActivity01, 2, 2, 8002);
	SendRankListAward(1, rlActivity01, 3, 3, 8003);
	SendRankListAward(1, rlActivity01, 4, 10, 8004);
	SendRankListAward(1, rlActivity01, 10, 1000, 8005);

	g_RankListMgr:ClearRankList(1, rlActivity01);

end



SCENE_LIST = {
	-- { id = 3, open = '2015-05-25 15:54:00 86400 3650', close = '2015-05-25 15:59:00 86400 3650' },   -- Programmer Sanctuary
	
	{ id = 183, open = '2020-05-18 21:00:00 86400 3650', close = '2020-05-18 22:00:00 86400 3650' },    -- Experience Arena
	{ id = 184, open = '2020-05-18 20:00:00 86400 3650', close = '2020-05-18 21:00:00 86400 3650' },    -- Royal Treasury
	
	--{ id = 81, open = '2020-06-23 20:00:00 86400 3650', close = '2020-06-23 21:00:00 86400 3650' },   -- Hall of Fame
	--{ id = 81, open = '2020-06-23 21:05:00 86400 3650', close = '2020-06-23 22:00:00 86400 3650' },
};

function main()
	clear_timer();
	
	------------------------------- Code examples
	-- register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "xxxxx");
	-- register_timer({ year = 2015, month = 6, day = 31, hour = 0, min = 10, sec = 0, interval = 86400, maxcount = 365 * 10 }, "xxxxx");
	-------------------------------

	------------------------------- Arena
	register_timer({ year = 2020, month = 11, day = 2, hour = 20, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_exp_arena");
	register_timer({ year = 2020, month = 11, day = 2, hour = 21, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_exp_arena");

	register_timer({ year = 2020, month = 11, day = 4, hour = 20, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_exp_arena");
	register_timer({ year = 2020, month = 11, day = 4, hour = 21, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_exp_arena");

	register_timer({ year = 2020, month = 11, day = 6, hour = 20, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_exp_arena");
	register_timer({ year = 2020, month = 11, day = 6, hour = 21, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_exp_arena");
	
	------------------------------- Royal Treasury open / close
	-- register_timer({ year = 2020, month = 05, day = 18, hour = 19, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "enable_treasure_arena");
	-- register_timer({ year = 2020, month = 05, day = 18, hour = 20, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "disable_treasure_arena");
	
	------------------------------- Royal Treasury boss spawn
	-- register_timer({ year = 2020, month = 05, day = 18, hour = 20, min = 10, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_treasure_boss");
	-- register_timer({ year = 2020, month = 05, day = 18, hour = 20, min = 25, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_treasure_boss");
	-- register_timer({ year = 2020, month = 05, day = 18, hour = 20, min = 40, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_treasure_boss");
	
	------------------------------- Zhulong God/Hongmo Leader/Woma Leader (01:00 - 13:00 - 16:00 - 18:00 - 23:00)
	register_timer({ year = 2020, month = 6, day = 30, hour = 00, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 00, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 12, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 12, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 15, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 15, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 17, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 17, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 22, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 22, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm_2");
	------------------------------- 

	------------------------------- Zuma Leader (14:30 - 17:30 - 19:30 - 00:30)
	register_timer({ year = 2020, month = 6, day = 30, hour = 14, min = 00, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 14, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 17, min = 00, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 17, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 00, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm_2");
	
	register_timer({ year = 2020, month = 6, day = 30, hour = 00, min = 00, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm");
	register_timer({ year = 2020, month = 6, day = 30, hour = 00, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zm_2");
	------------------------------- 

	------------------------------- Chiyue Demon (20:00)
	register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cyem");
	register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cyem_2");
	------------------------------- 
	
	------------------------------- Flame Demon (20:00)
	-- register_timer({ year = 2020, month = 6, day = 30, hour = 20, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_lyem");
	-- register_timer({ year = 2020, month = 6, day = 30, hour = 20, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_lyem_2");
	------------------------------- 

	------------------------------- Huangquan Leader/Bull Demon King
	--register_timer({ year = 2020, month = 6, day = 30, hour = 21, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_hq_nm");
	--register_timer({ year = 2015, month = 6, day = 30, hour = 21, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_hq_nm_2");

	------------------------------- Demon Dragon Leader
	--register_timer({ year = 2020, month = 6, day = 30, hour = 10, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_mljz");
	--register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_mljz");
	------------------------------- Demon Dragon Leader
	--register_timer({ year = 2015, month = 6, day = 30, hour = 10, min = 45, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_mljz2");
	--register_timer({ year = 2020, month = 6, day = 30, hour = 19, min = 45, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_mljz2");
	
	------------------------------- Fortune Golden Pig
	--register_timer({ year = 2020, month = 6, day = 30, hour = 22, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zcjz");
	--register_timer({ year = 2015, month = 6, day = 30, hour = 22, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zcjz2");
	--register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 00, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_zcjz3");

	------------------------------- Spawn Sabac Greed Demon King
	-- register_timer({ year = 2016, month = 6, day = 19, hour = 21, min = 50, sec = 0, interval = 86400, maxcount = 9  }, "enable_sbk_tlmw");
	-- register_timer({ year = 2016, month = 6, day = 19, hour = 22, min = 0, sec = 0, interval = 86400, maxcount = 9  }, "spawn_sbk_tlmw");


	-------------------------------------------- arena Experience Arena
	-- monday Monday
	register_timer({ year = 2016, month = 5, day = 9, hour = g_GWConfig.stArena.nArenaBeginHour, min = g_GWConfig.stArena.nArenaBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_begin");
	register_timer({ year = 2016, month = 5, day = 9, hour = g_GWConfig.stArena.nArenaEndHour, min = g_GWConfig.stArena.nArenaEndMin, sec = 0, interval = 604800, maxcount = 365 * 10}, "arena_end");

	register_timer({ year = 2016, month = 5, day = 9, hour = g_GWConfig.stArena.nArenaRewardBeginHour, min = g_GWConfig.stArena.nArenaRewardBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_begin");
	register_timer({ year = 2016, month = 5, day = 10, hour = g_GWConfig.stArena.nArenaRewardEndHour, min = g_GWConfig.stArena.nArenaRewardEndMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_end");

	-- Tuesday Tuesday
	register_timer({ year = 2016, month = 5, day = 11, hour = g_GWConfig.stArena.nArenaBeginHour, min = g_GWConfig.stArena.nArenaBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_begin");
	register_timer({ year = 2016, month = 5, day = 11, hour = g_GWConfig.stArena.nArenaEndHour, min = g_GWConfig.stArena.nArenaEndMin, sec = 0, interval = 604800, maxcount = 365 * 10}, "arena_end");

	register_timer({ year = 2016, month = 5, day = 11, hour = g_GWConfig.stArena.nArenaRewardBeginHour, min = g_GWConfig.stArena.nArenaRewardBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_begin");
	register_timer({ year = 2016, month = 5, day = 12, hour = g_GWConfig.stArena.nArenaRewardEndHour, min = g_GWConfig.stArena.nArenaRewardEndMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_end");

	-- Friday Friday
	register_timer({ year = 2016, month = 5, day = 13, hour = g_GWConfig.stArena.nArenaBeginHour, min = g_GWConfig.stArena.nArenaBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_begin");
	register_timer({ year = 2016, month = 5, day = 13, hour = g_GWConfig.stArena.nArenaEndHour, min = g_GWConfig.stArena.nArenaEndMin, sec = 0, interval = 604800, maxcount = 365 * 10}, "arena_end");

	register_timer({ year = 2016, month = 5, day = 13, hour = g_GWConfig.stArena.nArenaRewardBeginHour, min = g_GWConfig.stArena.nArenaRewardBeginMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_begin");
	register_timer({ year = 2016, month = 5, day = 14, hour = g_GWConfig.stArena.nArenaRewardEndHour, min = g_GWConfig.stArena.nArenaRewardEndMin, sec = 0, interval = 604800, maxcount = 365 * 10 }, "arena_reward_end");
	--------------------------------------------

	
	
	--[[
	-- Default code temporarily disabled; likely events from a previous server launch
	-- register_timer({ year = 2020, month = 7, day = 24, hour = 0, min = 0, sec = 0, interval = 600, maxcount = 365 * 144 }, "open_dice");
	-- register_timer({ year = 2020, month = 2, day = 12, hour = 12, min = 0, sec = 0, interval = 86400, maxcount = 365 * 10 }, "enable_exp_drop_rate");
	-- register_timer({ year = 2020, month = 2, day = 12, hour = 12, min = 57, sec = 0, interval = 86400, maxcount = 365 * 10 }, "disable_exp_drop_rate");
	-- register_timer({ year = 2020, month = 2, day = 12, hour = 19, min = 0, sec = 0, interval = 86400, maxcount = 365 * 10 }, "enable_exp_drop_rate");
	-- register_timer({ year = 2020, month = 2, day = 12, hour = 19, min = 57, sec = 0, interval = 86400, maxcount = 365 * 10 }, "disable_exp_drop_rate");
	
	-------Guild war start announcement
	--register_timer({ year = 2020, month = 2, day = 12, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "guild_war");
	-------New Year event
	--register_timer({ year = 2020, month = 2, day = 12, hour = 19, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "new_year");

	-------------------------Streamer brawl
	--register_timer({ year = 2020, month = 06, day = 23, hour = 19, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "zhubo_luandouop");
	--register_timer({ year = 2020, month = 06, day = 23, hour = 20, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "zhubo_luandoucl");

	--------------------------------------------Training Ground Arena
	-- register_timer({ year = 2020, month = 11, day = 2, hour = 19, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 2, hour = 20, min = 35, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 2, hour = 23, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqltlj");

	-- register_timer({ year = 2020, month = 11, day = 4, hour = 19, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 4, hour = 20, min = 35, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 4, hour = 23, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqltlj");


	-- register_timer({ year = 2020, month = 11, day = 6, hour = 19, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "enable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 6, hour = 20, min = 35, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqlt");
	-- register_timer({ year = 2020, month = 11, day = 6, hour = 23, min = 55, sec = 0, interval = 604800, maxcount = 365 * 10 }, "disable_bqltlj");
	--------------------------------------------

	--Guild stronghold battle announcement
	--------------------------------------------
	-- register_timer({ year = 2020, month = 6, day = 11, hour = 13, min = 55, sec = 0, interval = 86400, maxcount = 365 * 10 }, "enable_jdz");
	-- register_timer({ year = 2020, month = 6, day = 11, hour = 14, min = 25, sec = 0, interval = 86400, maxcount = 365 * 10 }, "disable_jdz");
	--------------------------------------------
	
	--2020 Spring Festival bosses
	--------------------------------------------
	-- register_timer({ year = 2020, month = 1, day = 24, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 1 }, "ChunJie_Boss");
	-- register_timer({ year = 2020, month = 1, day = 25, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 1 }, "ChunJie_Boss");
	-- register_timer({ year = 2020, month = 1, day = 26, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 1 }, "ChunJie_Boss");
	--------------------------------------------

	--------------------------------------------Big Gray Wolf--------------------------------------------
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 18, min = 55, sec = 0, interval = 86400, maxcount = 14  }, "enable_dhl");

	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 0, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 3, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 6, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 9, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 12, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");
	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 15, sec = 0, interval = 86400, maxcount = 14  }, "spawn_dhl");

	-- register_timer({ year = 2016, month = 6, day = 6, hour = 19, min = 15, sec = 0, interval = 86400, maxcount = 14 }, "disable_dhl");
	-----------------------------------------------------------------------------------------------------------------------------------------------

	-------------------Boss Spawn - Announce 30 minutes in advance
	register_timer({ year = 2015, month = 6, day = 30, hour = 0, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_wm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 0, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm");

	register_timer({ year = 2015, month = 6, day = 30, hour = 12, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 12, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm");

	register_timer({ year = 2015, month = 6, day = 30, hour = 14, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 14, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm");

	register_timer({ year = 2015, month = 6, day = 30, hour = 16, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 16, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm");

	register_timer({ year = 2015, month = 6, day = 30, hour = 18, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 18, min = 30, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm");

	register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 0, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm");
	register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 0, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm");

	-------------------Boss Spawn - Announce 10 minutes in advance
	register_timer({ year = 2020, month = 6, day = 30, hour = 0, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	--register_timer({ year = 2020, month = 6, day = 30, hour = 0, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	register_timer({ year = 2015, month = 6, day = 30, hour = 12, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	register_timer({ year = 2015, month = 6, day = 30, hour = 12, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	register_timer({ year = 2015, month = 6, day = 30, hour = 14, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	register_timer({ year = 2015, month = 6, day = 30, hour = 15, min = 5, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	register_timer({ year = 2015, month = 6, day = 30, hour = 16, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	register_timer({ year = 2015, month = 6, day = 30, hour = 16, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	register_timer({ year = 2015, month = 6, day = 30, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	register_timer({ year = 2015, month = 6, day = 30, hour = 18, min = 50, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_cl_hm_2");
	register_timer({ year = 2015, month = 6, day = 30, hour = 23, min = 20, sec = 0, interval = 86400, maxcount = 365 * 10 }, "spawn_wm_zm_2");

	-------------------------------------------- guild
	-- register_timer({ year = 2016, month = 5, day = 9, hour = g_GuildConfig.nGuildWarReadyHour, min = g_GuildConfig.nGuildWarReadyMin, sec = 0, interval = 86400, maxcount = 365 * 10 }, "GuildWarReady");
	-- register_timer({ year = 2016, month = 5, day = 9, hour = g_GuildConfig.nGuildWarBeginHour, min = g_GuildConfig.nGuildWarBeginMin, sec = 0, interval = 86400, maxcount = 365 * 10}, "GuildWarBegin");

	-- register_timer({ year = 2016, month = 5, day = 9, hour = g_GuildConfig.nGuildWar10TipHour, min = g_GuildConfig.nGuildWar10TipMin, sec = 0, interval = 86400, maxcount = 365 * 10 }, "GuildWar10Tps");
	-- register_timer({ year = 2016, month = 5, day = 10, hour = g_GuildConfig.nGuildWarEndHour, min = g_GuildConfig.nGuildWarEndMin, sec = 0, interval = 86400, maxcount = 365 * 10 }, "GuildWarEnd");
	--------------------------------------------
	
	-------------------------------------------- function RankListAward()--Award and clear donation rankings
	--register_timer({ year = 2020, month = 10, day = 1, hour = 0, min = 0, sec = 0, interval = 86400, maxcount = 365 * 10 }, "RankListAward");
	]]--

	for k,v in ipairs(SPAWN_NPC) do
		if not v.closed then
			local func_name = "spawn_npc_"..k;
			local y,m,d,h,mm,s,i,c;
			
			if v.time == '0' then
				timer = os.time();
				tab = os.date("*t",timer)
				y = tab.year;        -- Year
				m = tab.month;       -- Month
				d = tab.day;         -- Day
				h = tab.hour;        -- Hour
				mm = tab.min + 1;    -- Minute (trigger minute = current minute + 1)
			    s = tab.sec;         -- Second
				i = 86400;           -- Lifetime, default 86400 seconds (1 day)
				c = 3650;            -- Maximum count, default 3650
			else
				y,m,d,h,mm,s,i,c = string.match(v.time, "(%d+)%-(%d+)%-(%d+)%s+(%d+):(%d+):(%d+)%s+(%d+)%s+(%d+)");
			end 
				_G[func_name] = function ()
				local npcid = v.npc[math.random(#(v.npc))];
				local pos = v.pos[math.random(#(v.pos))];
				spawn_npc(pos.scene, pos.x, pos.y, pos.z, pos.range, npcid, v.count, i - 60);
			end
			
			register_timer({ year = y, month = m, day = d, hour = h, min = mm, sec = s, interval = i, maxcount = c}, func_name);
		else
			print("spawn npc "..k.." is closed");
		end
	end

	for k,v in ipairs(SCENE_LIST) do
		if not v.closed then
			local func_name = "open_scene_"..k;
			_G[func_name] = function ()
				create_scene(MAX_SERVER_GROUP_COUNT, v.id);
			end
			local y,m,d,h,mm,s,i,c = string.match(v.open, "(%d+)%-(%d+)%-(%d+)%s+(%d+):(%d+):(%d+)%s+(%d+)%s+(%d+)");
			local tStartTime = { year = tonumber(y), month = tonumber(m), day = tonumber(d), hour = tonumber(h),
				min = tonumber(mm), sec = tonumber(s), interval = tonumber(i), maxcount = tonumber(c)};
			register_timer(tStartTime, func_name);

			func_name = "close_scene_"..k;
			_G[func_name] = function ()
				close_scene(MAX_SERVER_GROUP_COUNT, v.id, 1);
			end
			local y,m,d,h,mm,s,i,c = string.match(v.close, "(%d+)%-(%d+)%-(%d+)%s+(%d+):(%d+):(%d+)%s+(%d+)%s+(%d+)");
			local tEndTime = { year = tonumber(y), month = tonumber(m), day = tonumber(d), hour = tonumber(h),
				min = tonumber(mm), sec = tonumber(s), interval = tonumber(i), maxcount = tonumber(c)};
			register_timer(tEndTime, func_name);

			local start_time = os.time(tStartTime);
			local end_time = os.time(tEndTime);
			local current_time = os.time();

			while end_time < current_time and tStartTime.maxcount > 0 and tEndTime.maxcount > 0 do
				start_time = start_time + tStartTime.interval;
				tStartTime.maxcount = tStartTime.maxcount - 1;
				end_time = end_time + tEndTime.interval;
				tEndTime.maxcount = tEndTime.maxcount - 1;
			end

			if current_time >= start_time and (current_time + 600) < end_time then
				local t = os.date("*t", current_time + 600)
				t.maxcount = 1;
				t.interval = 1;
				register_timer(t, "open_scene_"..k);
			end
		else
			print("scene "..v.id.." is closed");
		end
	end
	
end

--[[
function OnMonthlyMainLoop(nServerGroup)--Arena ranking rewards
	SendRankListAward(nServerGroup, rlArena1v1, 1, 5, 7001);
	SendRankListAward(nServerGroup, rlArena1v1Warrior, 1, 3, 7001);
	SendRankListAward(nServerGroup, rlArena1v1Mage, 1, 3, 7001);
	SendRankListAward(nServerGroup, rlArena1v1Taoist, 1, 3, 7001);

	g_RankListMgr:ClearRankList(nServerGroup, rlArena1v1);
	g_RankListMgr:ClearRankList(nServerGroup, rlArena1v1Warrior);
	g_RankListMgr:ClearRankList(nServerGroup, rlArena1v1Mage);
	g_RankListMgr:ClearRankList(nServerGroup, rlArena1v1Taoist);
end
]]--

main();
