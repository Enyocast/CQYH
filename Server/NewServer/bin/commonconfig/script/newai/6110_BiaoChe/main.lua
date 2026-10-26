Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg");
LoadPackage("npc_def.pkg");
LoadPackage("scene.pkg");
LoadPackage("data_manager.pkg");
LoadPackage("drop_generator.pkg");
LoadPackage("error_def.pkg");
LoadPackage("quest_list.pkg");


Include("script/newai/sub_tree/sub_tree.lh")
Include("script/include/escort.lh")

BROCAST_LOSE_ESCORT_TIMER = nastCustom + 1;                -- 镖车丢失通知定时器
CHECK_ESCORT_DISTANCE_TIMER = nastCustom + 2;              -- 检测镖车距离定时器

g_GameWorld = CGameWorld:GetInstance();

Include("script/newai/6110_BiaoChe/main.uh")


