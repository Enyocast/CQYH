LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("chat_def.pkg")

Include("script/include/btnod.lua")


--Test schedule requirements
--Monster siege: September 25 at 18:30, Woma leader; September 25 at 19:30, Demon Dragon leader
--Imperial City battle: September 25 at 17:00, Huang Bao spawn


-- SpawnDate_112 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 25,
-- 	hour = 17,
-- 	min = 0,
-- 	sec = 0,
-- 	isdst = false,
-- };


-- SpawnDate_111 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 25,
-- 	hour = 18,
-- 	min = 20,
-- 	sec = 0,
-- 	isdst = false,
-- };

-- SpawnDate_113 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 25,
-- 	hour = 19,
-- 	min = 20,
-- 	sec = 0,
-- 	isdst = false,
-- };


-- SpawnDate_111 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 11,
-- 	hour = 20,
-- 	min = 10,
-- 	sec = 0,
-- 	isdst = false,
-- };

-- SpawnDate_113 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 11,
-- 	hour = 20,
-- 	min = 20,
-- 	sec = 0,
-- 	isdst = false,
-- };

-- SpawnDate_112 = 
-- {
-- 	year = 2014,
-- 	month = 9,
-- 	day = 11,
-- 	hour = 20,
-- 	min = 25,
-- 	sec = 0,
-- 	isdst = false,
-- };



function get_wait_time(SpawnDate)
	local t1 = os.time();
	local t2 = os.time(SpawnDate);
	while t2 <= t1 do
			t2 = t2 + 86400;
	end
	print('remain time '..(t2-t1));
	return (t2 - t1) * 1000;
end

Include("script/scene/Mir_Pb02/scene_bt.lua")

