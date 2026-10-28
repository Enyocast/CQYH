Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg");
LoadPackage("npc_def.pkg");
LoadPackage("scene.pkg");
LoadPackage("data_manager.pkg");


Include("script/newai/sub_tree/sub_tree.lh")

BROCAST_LOSE_ESCORT_TIMER = nastCustom + 1;                -- Escort cart lost notification timer
CHECK_ESCORT_DISTANCE_TIMER = nastCustom + 2;              -- Escort cart distance check timer
BROCAST_LOSE_ESCORT_INTERVAL = 20000;                      -- Escort cart lost notification interval (ms)
CHECK_ESCORT_DISTANCE_INTERVAL = 1000;                     -- Interval for checking the distance between the cart and player (ms)

ESCORT_CAR_VALID_FOLLOW_DISTANCE = 6 * GRID_WIDTH;         -- Valid follow distance between the cart and player

g_GameWorld = CGameWorld:GetInstance();

Include("script/newai/6131_BiaoChe2/main.uh")


