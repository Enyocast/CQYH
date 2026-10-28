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

BROCAST_LOSE_ESCORT_TIMER = nastCustom + 1;                -- Escort cart lost notification timer
CHECK_ESCORT_DISTANCE_TIMER = nastCustom + 2;              -- Escort cart distance check timer

g_GameWorld = CGameWorld:GetInstance();

Include("script/newai/6110_BiaoChe/main.uh")


