
--如果手动增加NPC刷新, 并且NPC要设置为一直存在, 则time这里修改为 time = '0'
SPAWN_NPC = 
{
-- ***************** 刷Npc
	-- ***************** 出生点彩蝶Npc - 4791
	{ closed = false, npc = { 4791 }, count = 1, time = '0', pos = {
	{ scene = 142, x = 26700, y = 56200, z = 5000, range = 0 },
	}},
	-- ***************** 宝石雕色Npc - 6192 碧橙
	{ closed = false, npc = { 6192 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 39800, y = 54700, z = 5000, range = 0 },
	}},
	-- ***************** 宝石镶嵌Npc - 6772 盟容
	{ closed = false, npc = { 6772 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 39800, y = 54900, z = 5000, range = 0 },
	}},
	-- ***************** 秘境商人Npc - 6404
	-- { closed = false, npc = { 6404 }, count = 1, time = '0', pos = {
	-- { scene = 147, x = 39800, y = 54900, z = 5000, range = 0 },
	-- }},
	-- ***************** 魔虫窟Npc - 6167 玲音
	{ closed = false, npc = { 6167 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 39800, y = 55100, z = 5000, range = 0 },
	}},
	-- ***************** 幽冥海Npc - 6114 神秘法师
	{ closed = false, npc = { 6114 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 39800, y = 55300, z = 5000, range = 0 },
	}},
	-- ***************** 抉择之地卖药Npc - 6139
	{ closed = false, npc = { 6139 }, count = 1, time = '0', pos = {
	{ scene = 195, x = 20300, y = 24000, z = 5000, range = 0 },
	}},
	-- ***************** 魔龙BOSS地图的药店Npc - 6222
	{ closed = false, npc = { 6222 } , count = 1, time = '0', pos = {
	{ scene = 244, x = 30400, y = 28000, z = 5000, range = 0 },
	}},
	-- ***************** 传送员Npc - 6528-玛法通驿05 [盟重]
	{ closed = false, npc = { 6528 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 39000, y = 55300, z = 5000, range = 0 },
	}},
	-- ***************** 传送员Npc - 6528-玛法通驿05 [比奇]
	{ closed = false, npc = { 6528 }, count = 1, time = '0', pos = {
	{ scene = 143, x = 62800, y = 48000, z = 5000, range = 0 },
	}},


-- ******************* 刷Boss
	-- ******************* 行会战BOSS [暗月妖王] - 5241 
    --[[{ closed = false, npc = { 5241 }, count = 1, time = '2020-6-30 18:55:00 86400 3650', pos = {
	{ scene = 80, x = 22800, y = 26400, z = 5000, range = 0 },
	}},]]--
	
	-- ******************* 皇室宝库BOSS - 5101 
	{ closed = false, npc = { 5101 }, count = 1, time = '2020-05-18 20:15:00 86400 3650', pos = {
	{ scene = 184, x = 20100, y = 27400, z = 5000, range = 256 },
	}},
	{ closed = false, npc = { 5101 }, count = 1, time = '2020-05-18 20:30:00 86400 3650', pos = {
	{ scene = 184, x = 20100, y = 27400, z = 5000, range = 256 },
	}},
	{ closed = false, npc = { 5101 }, count = 1, time = '2020-05-18 20:45:00 86400 3650', pos = {
	{ scene = 184, x = 20100, y = 27400, z = 5000, range = 256 },
	}},
	
	-- ******************* 触龙神 - 5287
	{ closed = false, npc = { 5287 }, count = 1, time = '2020-6-30 01:00:00 86400 3650', pos = {
	{ scene = 203, x = 19000, y = 75800, z = 5000, range = 0 },
	}},
	{ closed = false, npc = { 5287 }, count = 1, time = '2020-6-30 13:00:00 86400 3650', pos = {
	{ scene = 203, x = 19000, y = 75800, z = 5000, range = 0 },
	}},
	{ closed = false, npc = { 5287 }, count = 1, time = '2020-6-30 16:00:00 86400 3650', pos = {
	{ scene = 203, x = 19000, y = 75800, z = 5000, range = 0 },
	}},
	{ closed = false, npc = { 5287 }, count = 1, time = '2020-6-30 18:00:00 86400 3650', pos = {
	{ scene = 203, x = 19000, y = 75800, z = 5000, range = 0 },
	}},
	{ closed = false, npc = { 5287 }, count = 1, time = '2020-6-30 23:00:00 86400 3650', pos = {
	{ scene = 203, x = 19000, y = 75800, z = 5000, range = 0 },
	}},

	-- ******************* 虹魔教主 - (真-5297, 假-5298)
	{ closed = false, npc = { 5297 }, count = 1, time = '2020-6-30 01:00:00 86400 3650', pos = {
	{ scene = 164, x = 32500, y = 41500, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5297 }, count = 1, time = '2020-6-30 13:00:00 86400 3650', pos = {
	{ scene = 164, x = 32500, y = 41500, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5297 }, count = 1, time = '2020-6-30 16:00:00 86400 3650', pos = {
	{ scene = 164, x = 32500, y = 41500, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5297 }, count = 1, time = '2020-6-30 18:00:00 86400 3650', pos = {
	{ scene = 164, x = 32500, y = 41500, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5297 }, count = 1, time = '2020-6-30 23:00:00 86400 3650', pos = {
	{ scene = 164, x = 32500, y = 41500, z = 5000, range = 1000 },
	}},

	-- ******************* 沃玛教主 - 5278
	{ closed = false, npc = { 5278 }, count = 1, time = '2020-6-30 01:00:00 86400 3650', pos = {
	{ scene = 156, x = 16700, y = 42600, z = 5000, range = 2000 },
	}},
	{ closed = false, npc = { 5278 }, count = 1, time = '2020-6-30 13:00:00 86400 3650', pos = {
	{ scene = 156, x = 16700, y = 42600, z = 5000, range = 2000 },
	}},
	{ closed = false, npc = { 5278 }, count = 1, time = '2020-6-30 16:00:00 86400 3650', pos = {
	{ scene = 156, x = 16700, y = 42600, z = 5000, range = 2000 },
	}},
	{ closed = false, npc = { 5278 }, count = 1, time = '2020-6-30 18:00:00 86400 3650', pos = {
	{ scene = 156, x = 16700, y = 42600, z = 5000, range = 2000 },
	}},
	{ closed = false, npc = { 5278 }, count = 1, time = '2020-6-30 23:00:00 86400 3650', pos = {
	{ scene = 156, x = 16700, y = 42600, z = 5000, range = 2000 },
	}},
	
	-- ******************* 祖玛教主 - (真-5301, 假-5302)
	{ closed = false, npc = { 5301 }, count = 1, time = '2020-6-30 14:30:00 86400 3650', pos = {
	{ scene = 173, x = 3100, y = 3100, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5301 }, count = 1, time = '2020-6-30 17:30:00 86400 3650', pos = {
	{ scene = 173, x = 3100, y = 3100, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5301 }, count = 1, time = '2020-6-30 19:30:00 86400 3650', pos = {
	{ scene = 173, x = 3100, y = 3100, z = 5000, range = 1000 },
	}},
	{ closed = false, npc = { 5301 }, count = 1, time = '2020-6-30 00:30:00 86400 3650', pos = {
	{ scene = 173, x = 3100, y = 3100, z = 5000, range = 1000 },
	}},

	-- ******************* 赤月恶魔 - 5306
	{ closed = false, npc = { 5306 }, count = 1, time = '2020-11-3 20:00:00 86400 3650', pos = {
	{ scene = 199, x = 10000, y = 12000, z = 5000, range = 0 },
	}},


-- 默认的NPC, 没啥用暂时屏蔽
--[[
	-- ********************** 新年活动年兽 - 5376 
	{ closed = false, npc = { 5376 }, count = 1, time = '2020-11-3 20:00:00 86400 3650', pos = {
	{ scene = 152, x = 40800, y = 47700, z = 6160, range = 0 },
	}},
	-- ********************** 传送进入行会战地图NPC - 7000 
	{ closed = false, npc = { 7000 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 38500, y = 55000, z = 5000, range = 0 },
	}},
	-- ******************* 大灰狼兑换 - 6161 
	{ closed = false, npc = { 6161 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 38500, y = 54500, z = 5000, range = 0 },
	}},
	-- ******************* 卧龙翁祈愿 - 6145 
	{ closed = false, npc = { 6145 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 38800, y = 54400, z = 5000, range = 0 },
	}},
	-- ******************* 天下第一 - 6179 
	{ closed = false, npc = { 6179 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 38200, y = 54600, z = 5000, range = 0 },
	}},
	-- ******************* 国庆大使 - 6439 
	{ closed = false, npc = { 6439 }, count = 1, time = '0', pos = {
	    --{ scene = 147, x = 39800, y = 55300, z = 5000, range = 0 },
	}},
	-- ******************* 经验炉子 - 4797 
	{ closed = false, npc = { 4797 }, count = 1, time = '0', pos = {
	{ scene = 147, x = 40300, y = 54200, z = 5000, range = 0 },
	}},

	-- ******************* 魔龙教主 - 5283
	{ closed = false, npc = { 5283 } , count = 1, time = '2019-6-19 20:00:00 86400 3650', pos = {
	{ scene = 244, x = 40900, y = 42200, z = 5000, range = 2000 },
	}},
	
	-- ******************* 黄泉教主 - 5273
	{ closed = false, npc = { 5273 }, count = 1, time = '2020-05-18 22:00:00 86400 3650', pos = {
	{ scene = 55, x = 16500, y = 37600, z = 5000, range = 256 },
	}},
	
	-- ******************* 牛魔王 - 5657
	{ closed = false, npc = { 5657 }, count = 1, time = '2020-05-18 22:00:00 86400 3650', pos = {
	{ scene = 66, x = 14100, y = 15200, z = 5000, range = 256 },
	}},
]]--


};
