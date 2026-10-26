Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("npc.pkg");
LoadPackage("npc_def.pkg");
LoadPackage("scene.pkg");
LoadPackage("data_manager.pkg");


Include("script/newai/sub_tree/sub_tree.lh")

BROCAST_LOSE_ESCORT_TIMER = nastCustom + 1;                -- 镖车丢失通知定时器
CHECK_ESCORT_DISTANCE_TIMER = nastCustom + 2;              -- 检测镖车距离定时器
BROCAST_LOSE_ESCORT_INTERVAL = 20000;                      -- 镖车丢失通知时间间隔（单位/ms）
CHECK_ESCORT_DISTANCE_INTERVAL = 1000;                     -- 检测镖车与角色的距离时间间隔（单位/ms）

ESCORT_CAR_VALID_FOLLOW_DISTANCE = 6 * GRID_WIDTH;         -- 镖车与角色的有效的距离

g_GameWorld = CGameWorld:GetInstance();

Include("script/newai/6131_BiaoChe2/main.uh")


