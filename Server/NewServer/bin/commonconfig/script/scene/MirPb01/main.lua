--[[LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("chat_def.pkg")
Include("script/include/btnod.lua")

SpawnDate_1 = 
{
	year = 2021,
 	month = 2,
 	day = 23,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_2 = 
{
	year = 2021,
 	month = 2,
 	day = 24,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_3 = 
{
	year = 2021,
 	month = 2,
 	day = 25,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_4 = 
{
	year = 2021,
 	month = 2,
 	day = 26,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_5 = 
{
	year = 2021,
 	month = 2,
 	day = 27,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_6 = 
{
	year = 2021,
 	month = 2,
 	day = 25,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};
SpawnDate_7 = 
{
	year = 2021,
 	month = 3,
 	day = 1,
 	hour = 19,
 	min = 50,
 	sec = 00,
 	isdst = false,
};



function get_wait_time(SpawnDate)
	local t1 = os.time();
	local t2 = os.time(SpawnDate);
	while t2 <= t1 do
			t2 = t2 + 86400;
	end
	print('remain time '..(t2-t1));
	return (t2 - t1) * 1000;
end
Include("script/scene/MirPb01/scene_bt.lua")]]--