#ifndef _BT_ACTION_H_
#define _BT_ACTION_H_

/// @file bt_action.h 
/// @brief Behavior Tree Action List
#include "btnod.h"

// tolua_begin

enum BT_OPERATOR
{
    boLT,   ///< less than                 少于
    boLTE,  ///< less than or equal to     小于或等于
    boGT,   ///< greater than              大于
    boGTE,  ///< greater than or equal to  大于或等于
    boEQ,   ///< equal to                  等于
    boNEQ,  ///< not equal to              不等于
};

enum BT_TARGET_TYPE
{
    tarInvalid = 0,

    tarSelf,            			        ///< self target type, the owner

    tarAITarget,                            ///< a enemy target which was attacked in last ai loop
    tarHost,                                ///< the host char who summons the ai owner
    tarNearestEnemy,                        ///< nearest opponent character
    tarFarthestEnemy,                       ///< farthest opponent character
    tarCastingEnemy,                        ///< opponent character who is casting a spell
    tarCorpse,                              ///< dead character which is in corpse state
    tarAuraChar,                            ///< character with specified aura
    tarNearestFriend,                       ///< nearest friendly
    tarSignalIssuer,                        ///< latest checked signal issuer
    tarSignalIssuerTarget,                  ///< ai target of latest checked signal issuer
	tarNearestEnemyRole,

    tarRole,                                ///< related role object
	tarRoleKiller,							///< who killed related role
	tarRolePet1,							///< related role's 1st pet
	tarRolePet2,							///< related role's 2nd pet
	tarRolePet3,							///< related role's 3rd pet
	tarRolePet4,							///< related role's 4th pet
	tarRolePet5,							///< related role's 5th pet
	tarRolePet6,							///< related role's 6th pet

    tarDirection,                           ///< direction target type, only be effective in #batCastSpell, #batRotateTo and #batSyncRotateTo actions
    tarPosition,                            ///< position target type, only be effective in actions #batCastSpell, #batMoveTo and #batSyncMoveTo
    tarRelativePosition,                    ///< relative position target type, only be effective in actions #batMoveTo and #batSyncMoveTo
    tarHome,                                ///< npc spawn position, only be effective in actions #batMoveTo and #batSyncMoveTo

    tarTotal
};

enum BT_ACTION_TYPE
{
    /************************************************************************/
    /* Common                                                               */
    /************************************************************************/

    batInvalid  = btInvalid,        ///< invalid action
                                    ///< @note do not use this action

                                    ///< 选择器，如果任何子节点返回true，则立即返回true；否则，返回false
    batSelector = btSelector,       ///< selector, if any child node returns true, it returns true immediately; otherwise, it returns false

                                    ///< 序列器，如果任何子节点返回false，则立即返回false；否则，它将返回true
    batSequencer= btSequencer,      ///< sequencer, if any child node returns false, it returns false immediately; otherwise, it returns true

                                    ///< 并行，无论其子节点返回什么，它总是返回true
    batParallel = btParallel,       ///< parallel, it always returns true whatever its child nodes return

                                    ///< 只有一个子节点；如果其子节点返回true，则返回false；否则，它将返回true
    batNot      = btNot,            ///< only one child node; if its child node returns true, it returns false; otherwise, it returns true

                                    ///< 调试节点仅供程序员使用，注意：只允许一个子节点
    batDebug    = btDebug,          ///< debug node for programmer only, note: just one child allowed

                                    ///< 随机选择一个子节点，最多4个子节点
    batRandom   = btRandom,         ///< btRandom choose a child node, 4 children at most
                                    ///< @param p0 child0 weight
                                    ///< @param p1 child1 weight
                                    ///< @param p2 child2 weight
                                    ///< @param p3 child3 weight
                                    
                                    ///< 反复选择子节点，注意：只允许一个子节点
    batRepeat   = btRepeat,         ///< repeatly choose the only child, note: just one child allowed
                                    ///< @param p0 repeat times (at most BT_REPEAT_MAX_TIMES 16)  // 重复次数, 最多16

    batBegin = btUserDefine,        ///< the beginning of user defined action in game world

    batReturnSuccess,               ///< always return true
    batReturnFail,                  ///< always return false
    batPrint,                       ///< print a debug message
                                    ///< @param p0 number

    batCheckDice,                   ///< roll a dice
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 chance (unit:1/10000)
    batCheckSceneVariable,          ///< check scene variable
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable index [0, #MAX_SCENE_VARIABLE_COUNT)
                                    ///< @param p2 variable value
                                    ///< @see #batSetSceneVariable, #batCompareSceneVariable
	batCheckServerVariable,			///< check server variable
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable index [0, #MAX_SERVER_VARIABLE_COUNT)
                                    ///< @param p2 variable value
                                    ///< @see #batSetServerVariable
	batCheckDateTime,				///< check date and time whether meet conditions
									///< @param p0 weekday [0, 7] (0 means any weekday)
									///< @param p1 min time (format : HHMMSS)
									///< @param p2 max time (format : HHMMSS)
	batCheckWeather,                ///< check scene Weather 
                                    ///< @param p0 isDaytime 0 or 1, -1 if no need
                                    ///< @param p1 #SCENE_WEATHER_TYPE, 0 if no need
                                    ///< @param p2 #SCENE_WEATHER_TYPE, 0 if no need
                                    ///< @param p3 #SCENE_WEATHER_TYPE, 0 if no need
                                    ///< @note check daytime meets p0 and weather meets ( p1 or p2 or p3 ), at least one valid
    batCompareSceneVariable,        ///< compare two scene variables
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable1 index [0, #MAX_SCENE_VARIABLE_COUNT)
                                    ///< @param p2 variable2 index [0, #MAX_SCENE_VARIABLE_COUNT)
                                    ///< @see #batCheckSceneVariable, #batSetSceneVariable
    batCheckDoorState,              ///< check door state
                                    ///< @param p0 door id [0 - #MAX_DOOR_ID)
                                    ///< @param p1 closed
                                    ///< @see #batOpenDoor, #batCloseDoor, #batToggleDoor
    batWait,                        ///< wait several frames synchronously
                                    ///< @param p0 interval (unit:ms) 
                                    ///< @param p1 max interval (unit:ms)
                                    ///< @note p0 interval will be rounded down by (1000/#GAME_FPS)
    batOpenDoor,                    ///< open a door
                                    ///< @param p0 door id [0, #MAX_DOOR_ID)
                                    ///< @see #batCheckDoorState, #batCloseDoor, #batToggleDoor
    batCloseDoor,                   ///< close a door
                                    ///< @param p0 door id [0, #MAX_DOOR_ID)
                                    ///< @see #batCheckDoorState, #batOpenDoor, #batToggleDoor
    batToggleDoor,                  ///< toggle a door
                                    ///< @param p0 door id [0, #MAX_DOOR_ID)
                                    ///< @see #batCheckDoorState, #batOpenDoor, #batCloseDoor
    batSay,                         ///< send a message by system sender id
                                    ///< @param p0 target id (refer #CHAT_CHANNEL_TYPE)
                                    ///< @param p1 string id (client string id is less than #SERVER_STRING_START_ID; otherwise, it is a server string id)
                                    ///< @param p2 #CHAT_LOCATION_TYPE
									///< @param p3 string param
                                    ///< @note target id may be role id, team id, guild id, channel id (#CHAT_CHANNEL_TYPE)
    batSetSceneVariable,            ///< set scene variable                         设置场景变量
                                    ///< @param p0 variable index                   @参数p0变量索引
                                    ///< @param p1 absolute value (optional)        @参数p1绝对值（可选）
                                    ///< @param p2 relative value (optional)        @参数p2相对值（可选）
                                    ///< @note p1 is effective only when p2 is zero @注意：p1仅在p2为零时有效
                                    ///< @see #batCheckSceneVariable, #batCompareSceneVariable
    batSetServerVariable,           ///< set server variable
                                    ///< @param p0 variable index
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
                                    ///< @note p1 is effective only when p2 is zero
                                    ///< @see #batCheckServerVariable
    batSpawnNpc,                    ///< spawn a npc at specified coordination
                                    ///< @param p0 npc template id
                                    ///< @param p1 x (unit:cm)
                                    ///< @param p2 y (unit:cm)
                                    ///< @param p3 z (unit:cm)
                                    ///< @note when called this action in AI, the face direction of spawned npc is same as AI owner
                                    ///< @note when called this action in scene, the face direction of spawned npc is always 225 degree
                                    ///< @see #batSpawnNpcAtPoint, #batSpawnSingleNpc, #batSpawnMediumGroup, #batSpawnLargeGroup
    batSpawnNpcAtPoint,             ///< spawn a npc at specified point
                                    ///< @param p0 npc template id
                                    ///< @param p1 point id (object link)
                                    ///< @param p2 face direction (unit:degree)
                                    ///< @see #batSpawnNpc, #batSpawnSingleNpc, #batSpawnMediumGroup, #batSpawnLargeGroup
    batSpawnSingleNpc,              ///< spawn a single npc 
                                    ///< @param p0 single npc id (object link)
                                    ///< @note single npc can be spawned once and once again
                                    ///< @see #batSpawnNpc, #batSpawnNpcAtPoint, #batSpawnMediumGroup, #batSpawnLargeGroup
    batSpawnMediumGroup,            ///< spawn a medium npc group
                                    ///< @param p0 medium group id (object link)
                                    ///< @note a medium group can be spawned only once
                                    ///< @see #batSpawnNpc, #batSpawnNpcAtPoint, #batSpawnSingleNpc, #batSpawnLargeGroup
    batSpawnLargeGroup,             ///< spawn a large npc group 
                                    ///< @param p0 large group id (object link)
                                    ///< @note a large group can be spawned only once
                                    ///< @see #batSpawnNpc, #batSpawnNpcAtPoint, #batSpawnSingleNpc, #batSpawnMediumGroup
    batSpawnDoodad,                 ///< spawn a doodad at specified coordination
                                    ///< @param p0 doodad template id
                                    ///< @param p1 x (unit:cm)
                                    ///< @param p2 y (unit:cm)
                                    ///< @param p3 z (unit:cm)
                                    ///< @note when called this action in AI, the face direction of spawned doodad is same as AI owner
                                    ///< @note when called this action in scene, the face direction of spawned doodad is always 225 degree
                                    ///< @see #batSpawnDoodadAtPoint, #batSpawnDoodadGroup
    batSpawnDoodadAtPoint,          ///< spawn a doodad at specified point
                                    ///< @param p0 doodad template id
                                    ///< @param p1 point id (object link)
                                    ///< @param p2 face direction (unit:degree)
                                    ///< @see #batSpawnDoodad, #batSpawnDoodadGroup
    batSpawnDoodadGroup,            ///< spawn a doodad group
                                    ///< @param p0 doodad group id (object link)
                                    ///< @note a doodad group can be spawned only once
                                    ///< @see #batSpawnDoodad, #batSpawnDoodadAtPoint
	batCheckSceneRuning,			///< check the scene is runing
	batFinishScene,                 ///< close current scene in specified duration
									///< @param p0 delay duration (unit:ms)
	batCalculateDungeonScore,		///< default calculate the score in scenefinish

    batSetReputationToFaction,      ///< set role's reputation in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 npc force id
                                    ///< @param p2 relative value
    batAddMoneyToFaction,           ///< add role's money in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 #MONEY_TYPE
                                    ///< @param p2 money amount
									///< @param p3 reason type #EMoneyLog
    batSubMoneyToFaction,           ///< subtract role's money in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 #MONEY_TYPE
                                    ///< @param p2 money amount
									///< @param p3 reason type #EMoneyLog
    batAddAuraToFaction,            ///< add an aura to role in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 aura id
                                    ///< @see #batRemoveAuraToFaction
    batRemoveAuraToFaction,         ///< remove an aura to role in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 aura id
                                    ///< @param p2 trigger remove event
                                    ///< @see #batAddAuraToFaction
                                    ///< @note if p2 is true, remove aura event will be triggered; otherwise, won't be triggered
    batAddItemToFaction,            ///< add an item to role in specified faction in current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 item id
                                    ///< @param p2 item amount
    batSetCombatStatToFaction,      ///< set role's combat stat in specified faction of current scene
                                    ///< @param p0 faction id
                                    ///< @param p1 #ENUM_COMBAT_STAT_ENTRY
                                    ///< @param p2 absolute value (optional)
                                    ///< @param p3 relative value (optional)
                                    ///< @note p2 is effective only when p3 is zero
    batGuildEndWar,                 ///< guild battle end, can call by scene or npc
                                    ///< @param p0 #GUILD_WAR_RESULT
    batCloseGuildDungeon,           ///< delete the guild dungeon commission
                                    ///< no param
    batGuildWarTime,                ///< check is guild war begin

    /************************************************************************/
    /* Role                                                                 */
    /************************************************************************/
    batRoleCheckRoleVariable,       ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable index [0, #MAX_ROLE_VARIABLE_COUNT)
                                    ///< @param p2 variable value
                                    ///< @see #batRoleSetRoleVariable
    batRoleCheckGuildVariable,      ///< check role's guild vairable 
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable index [0, #MAX_GUILD_VARIABLE_COUNT)
                                    ///< @param p2 variable value
                                    ///< @see #batRoleSetGuildVariable
    batRoleCheckHasQuest,           ///< check role if has specific quest
                                    ///< @param p0 quest id
                                    ///< @see #batRoleCheckQuestVariable #batRoleSetQuestVariable
    batRoleCheckQuestVariable,      ///< check role's quest variable
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 quest id
                                    ///< @param p2 variable index [0, #MAX_VARIABLE_PER_QUEST)
                                    ///< @param p3 variable value
                                    ///< @see #batRoleSetQuestVariable #batRoleCheckHasQuest
    batRoleCheckFaction,            ///< check whether role faction is equal to the given number
                                    ///< @param p0 faction id [0, #MAX_ROLE_FRACTION_ID)
    batCheckInTeam,					///< check role is in team
    batRoleCheckInteractOption,     ///< check whether interact option value is equal to given number
                                    ///< @param p0  option value
    batRoleCheckVIP,                ///< check whether role is greater than given level
                                    ///< @param p0 VIP level
	batRoleCheckLevel,				///< check role level
									///< @param p0 #BT_OPERATOR
									///< @param p1 level
	batRoleIsSabacGuildMember,		///< return true while role is Sabac guild member
	batRoleIsSabacGuildLeader,		///< return true while role is Sabac guild leader

    batRoleSetRoleVariable,         ///< set role variable 
                                    ///< @param p0 variable index [0, #MAX_ROLE_VARIABLE_COUNT)
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
                                    ///< @note p1 is effective only when p2 is zero
                                    ///< @see #batRoleCheckRoleVariable
    batRoleSetGuildVariable,        ///< set role's guild variable
                                    ///< @param p0 variable index [0, #MAX_GUILD_VARIABLE_COUNT)
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
                                    ///< @note p1 is effective only when p2 is zero
                                    ///< @see #batRoleCheckGuildVariable
    batRoleSetQuestVariable,        ///< set role's quest variable
                                    ///< @param p0 quest id
                                    ///< @param p1 variable index [0, #MAX_VARIABLE_PER_QUEST)
                                    ///< @param p2 absolute value (optional)
                                    ///< @param p3 relative value (optional)
                                    ///< @note p2 is effective only when p3 is zero
                                    ///< @see #batRoleCheckQuestVariable
    batRoleSetCombatStat,           ///< set role's combat statistics
                                    ///< @param p0 #ENUM_COMBAT_STAT_ENTRY
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
                                    ///< @note p1 is effective only when p2 is zero
    batRoleTeleportToPoint,         ///< role teleport to specified scenetemplateID, sceneID and server point
                                    ///< @param p0 scene template id
                                    ///< @param p1 scene id
                                    ///< @param p2 server point id
    batRoleTeleport,                ///< role teleport to a specified coordination
                                    ///< @param p0 x (unit:cm)
                                    ///< @param p1 y (unit:cm)
                                    ///< @param p2 z (unit:cm)
                                    ///< @param p3 scene id (optional)
    batRoleReturnStaticScene,       ///< role returns static scene
                                    ///< @note this action should be used in a non-static scene
    batRoleSetReputation,           ///< set role's reputation
                                    ///< @param p0 npc force id
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
    batRoleCheckMoney,              ///< check money
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 money type
                                    ///< @param p2 money
    batRoleAddMoney,                ///< add role's money
									///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #MONEY_TYPE
                                    ///< @param p2 money amount
									///< @param p3 reason type #EMoneyLog
    batRoleSubMoney,                ///< subtract role's money
									///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #MONEY_TYPE
                                    ///< @param p2 money amount
									///< @param p3 reason type #EMoneyLog
    batRoleCheckItemCount,          ///< check specific item count
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 item template id
                                    ///< @param p2 item count
                                    ///< @param p3 whether items in bank are included
    batRoleAddItem,                 ///< add specified item into role's bag
                                    ///< @param p0 item template id
                                    ///< @param p1 item stack count
									///< @param p2 user defined id
    batRoleDelItem,                 ///< del specified item from role's bag
                                    ///< @param p0 item template id
                                    ///< @param p1 item stack count
                                    ///< @param p2 whether items in bank are included
                                    ///< @param p3 user defined id
    batRoleOpenDialog,              ///< open dialog on client
                                    ///< @param p0 string id
                                    ///< @param p1 timeout (unit:ms)
									///< @param p2 string param
	batRoleLeaveTeam,				///< make role leave his team
    batRoleSetFaction,              ///< set role faction #BATTLE_FACTION
                                    ///< @param p0  #BATTLE_FACTION
    batRoleCheckSelfScene,          ///< check the scene belongs to the guild 
    batRoleCheckAllianceScene,      ///< check the scene belongs to guild alliance, 
    batRoleJumpToTargetGuildScene,  ///< jump to guild map
                                    ///< @param p0 x
                                    ///< @param p1 y
                                    ///< @param p2 z
                                    ///< @param p3 guild id
    batRoleCheckDailyVariable,      ///< check whether time of variable is older than today's date
									///< @param p0 role variable index [0, #MAX_ROLE_VARIABLE)
									///< @param p1 day difference (unit:day, optional)
    batRoleUpdateDailyVariable,     ///< update time of variable to current time (UTC)
									///< @param p0 role variable index [0, #MAX_ROLE_VARIABLE)
									///< @param p1 update mode (0:daily reset; 1:weekly reset)
	batRoleEnterCutScene,
	batRoleEnrollSabac,				///< enroll sabac
	batRoleViewSabacEnrollList,		///< sync sabac enroll list to client
	batRoleErectStatue,				/// erect a statue for sabac winner
	batRoleAddDailyExtraExp,		///< add daily extra exp
	batRoleCheckCDTimer,			///< check role cd timer
									///< @param p0 #COOLDOWN_TYPE
									///< @param p1 cd timer index [0, 65535]
	batRoleSetCDTimer,				///< set role cd timer
									///< @param p0 #COOLDOWN_TYPE
									///< @param p1 cd timer index [0, 65535]
									///< @param p2 cd interval (unit:ms)
									///< @param p3 max cd interval (unit:ms, optional)
	batRoleJumpToRevivePos,			/// jump to role's revive position
	batRoleErrorCodeNotify,			///< notify role error code
									///< @param p0 ERROR_CODE_DEF
									///< @param p1 reserve param1
									///< @param p2 reserve param2
    batRoleCheckGuild,              ///< check role is guild member
    batRoleCheckPosition,           ///< check guild member position, if no guild return brvError
                                    ///< @param p0 , enum BT_OPERATOR, compare position not enum number. 
                                    ///< @param p1 position , enum GUILD_POSITION_TYPE.
    batRoleCheckGuildActivity,      ///< check guild activity is open
                                    ///< @param p0 activity id
	batRoleTemporaryCharge,			///< temporary charge (To be deleted)


    /************************************************************************/
    /* Char                                                                 */
    /************************************************************************/
    batCheckCharMoveState,          ///< check move state of the specified target 
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #CHAR_MOVE_STATE
    batCheckDirection,              ///< check whether difference between owner's face direction and given direction is in the given range
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p2 range (unit:degree)
    batCheckCharHp,                 ///< check hp of the specified target 
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #BT_OPERATOR
                                    ///< @param p2 hp percent (unit:1/10000, optional)
                                    ///< @param p3 hp point (optional)
                                    ///< @note p3 is effective only when p2 is below zero (such as -1)
                                    ///< @see #batSetCharHp, batCheckCharHpMeet
    batAddAura,                     ///< add an aura to the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 aura id
                                    ///< @see #batReduceAura, #batRemoveAura, #batCopyAura
    batReduceAura,                  ///< reduce aura stack count 
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 aura id
                                    ///< @param p2 aura stack count
                                    ///< @see #batAddAura, #batRemoveAura, #batCopyAura
    batRemoveAura,                  ///< remove an aura from the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 aura id
                                    ///< @param p2 trigger remove event
                                    ///< @note if p2 is true, remove aura event will be triggered; otherwise, won't be triggered
                                    ///< @see #batAddAura, #batReduceAura, #batCopyAura
    batCopyAura,                    ///< copy an aura from the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 aura id
                                    ///< @param p2 aura type (todo)
                                    ///< @see #batAddAura, #batReduceAura, #batRemoveAura

    batCheckAura,                   ///< check specified aura on the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 aura id
                                    ///< @see #batReduceAura, #batRemoveAura, #batCopyAura

    batRotateTo,                    ///< owner starts to rotate to the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 direction difference (unit:degree)
                                    ///< @param p2 duration (unit:ms)
                                    ///< @param p3 speed (unit:degree/s)
                                    ///< @note if #BT_TARGET_TYPE is tarDirection, p1 is absolute direction
                                    ///< @note if p3 is not zero, p2 is ignored
    batSyncRotateTo,                ///< owner rotates to the specified target synchronously
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 direction difference (unit:degree)
                                    ///< @param p2 duration (unit:ms)
                                    ///< @note if #BT_TARGET_TYPE is tarDirection, p1 is absolute direction
    batMoveTo,                      ///< begin to move to a specified position asynchronously
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 x (unit: cm, optional)
                                    ///< @param p2 y (unit: cm, optional)
    batSyncMoveTo,                  ///< move to a specified position synchronously 
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 x (unit: cm, optional)
                                    ///< @param p2 y (unit: cm, optional)
	batTeleportTo,					///< teleport to a specified position immediately
									///< @param p0 x (unit: cm)
									///< @param p1 y (unit: cm)
									///< @param p2 z (unit: cm)
    batSuicide,                     ///< owner kills himself immediately
									///< @param p0 drop items while p0 is true and owner type is NPC
									///< @param p1 remove from scene directly and skip death process while p1 is true
                                    ///< @note do not call any sync action after suiciding, it will not be executed
    batSetCharHp,                   ///< set hp of the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 hp points (optional)
                                    ///< @param p2 hp percent (unit:1/10000, optional)
                                    ///< @note p2 is effective only when p1 is below zero (such as -1)
                                    ///< @see #batCheckCharHp, batCheckCharHpMeet
    batSendMail,                    ///< send system mail to somebody, item count: 1.
                                    ///< @param p0  dwRoleID
                                    ///< @param p1  essMailSubjectID
                                    ///< @param p2  essMailContentID
                                    ///< @param p3  ItemTemplateID
    batSummonNpc,                   ///< spawn a NPC at relative coordination point
                                    ///< @param p0 NPC template id
                                    ///< @param p1 relative x (unit:cm)
                                    ///< @param p2 relative y (unit:cm)
                                    ///< @param p3 face direction relative to summonner (unit:degree)
    batSummonDoodad,                ///< spawn a doodad at relative coordination point
                                    ///< @param p0 doodad template id
                                    ///< @param p1 relative x (unit:cm)
                                    ///< @param p2 relative y (unit:cm)
                                    ///< @param p3 face direction relative to summonner (unit:degree)
	batSendAwardInfo,				///< send award info to ump platform
									///< @param p0 batch id
	batDistributeExp,				///< distribute exp to all roles in the scene
									///< @param p0 config table index
									///< @param p1 aura id (zero means no matter)
    batClearThreatList,             ///< clear threat list & threaten list
	batAddExp,						///< @param p0 #BT_TARGET_TYPE
									///< @param p1 exp value

    /************************************************************************/
    /* AI                                                                   */
    /************************************************************************/
	batRecvMsg,						///< wait for receiving message
									///< @param p0 message id
									///< @note	this action is only available in robot ai
	batCheckCCFlag,
    batCheckFlag,                   ///< check owner's char flag
                                    ///< @param p0 #CHAR_FLAG
                                    ///< @see #batSetFlag, batClearFlag
    batCheckInCombat,               ///< check whether owner is in combat state
    batCheckHostInCombat,           ///< check whether owner's host is in combat state
    batCheckCharOutOfHomeRange,     ///< check whether the specified target is out of range from home point
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 range (unit:cm)
                                    ///< @see batGoHome, batSetHome
    batCheckCharHpMeet,             ///< check whether the specified target's hp is below given percent
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #BT_OPERATOR
                                    ///< @param p2 hp percent
                                    ///< @param p3 ai variable index [0, MAX_AI_VARIABLE_COUNT)
                                    ///< @see #batCheckCharHp, #batSetCharHp
    batCheckCharCasting,            ///< check whether the specified target is casting a spell
                                    ///< @param p0 #BT_TARGET_TYPE
    batCheckBossState,              ///< check boss state value
                                    ///< @param p0 state value
                                    ///< @see #batSetBossState
    batCheckDistance,               ///< check the distance between ai owner and the specified target
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #BT_OPERATOR
                                    ///< @param p2 distance (cm)

                                    ///< 检查ai所有者的cd时间
    batCheckCDTimer,                ///< check ai owner's cd timer
                                    ///< @param p0 #COOLDOWN_TYPE
                                    ///< @param p1 cd timer index [0, 65535]
                                    ///< @see #batSetCDTimer

                                    ///< 检查 processor 的变量
    batCheckAIVariable,             ///< check ai processor's variable
                                    ///< @param p0 #BT_OPERATOR
                                    ///< @param p1 variable index [0, #MAX_AI_VARIABLE_COUNT)
                                    ///< @param p2 variable value
                                    ///< @see #batSetAIVariable

                                    ///< 
    batCheckHeroWeaponEquipped,		///< check whether hero has weapon equipped.

    batCheckTarget,                 ///< check whether specified target exists
                                    ///< @param p0 #BT_TARGET_TYPE

    batCheckTargetType,             ///< check specified target type
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 #OBJECT_TYPE

    batWander,                      ///< owner starts to wander
                                    ///< @param p0 range (unit:cm)
                                    ///< @param p1 interval (unit:ms)
    batGoHome,                      ///< owner starts to go back home
                                    ///< @see batSetHome, batCheckCharOutOfHomeRange
    batSetHome,                     ///< set current pos as home point
                                    ///< @see batGoHome, batCheckCharOutOfHomeRange
    batFlee,                        ///< owner starts to flee from its target enemy
                                    ///< @param p0 time (unit:ms)
    batChase,                       ///< owner starts to chase its target
                                    ///< @param p0 prefer distance (unit:cm)
                                    ///< @param p1 chase threshold distance (unit:cm)
                                    ///< @param p2 delay time (unit:ms)
    batWithdraw,                    ///< withdraw to preferred distance
                                    ///< @param p0 prefer distance (unit:cm)
                                    ///< @param p1 chase threshold distance (unit:cm)
    batSetFollowParam,              ///< set follow parameters
                                    ///< @param p0 follow host character id
                                    ///< @param p1 offset x (unit:cm)
                                    ///< @param p2 offset y (unit:cm)
                                    ///< @param p3 use host speed or not, if not use ai table RunSpeed & WalkSpeed (BOOL value, 0 or 1)
                                    ///< @see #batFollow
    batFollow,                      ///< owner starts to follow its host
                                    ///< @see #batSetFollowParam

	batInvincible,					///< @param p0 true/false

    batEnterIdle,                   ///< ai processor changes to idle tree
                                    ///< @see #batEnterFight
    batEnterFight,                  ///< ai processor changes to fight tree
                                    ///< @see #batEnterIdle
    batCastSpell,                   ///< owner starts to cast a spell
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 spell id
                                    ///< @param p2 x (unit:cm, optional for #tarPosition)
                                    ///< @param p2 direction (unit:degree, optional for #tarDirection)
                                    ///< @param p3 y (unit:cm, optional for #tarPosition)
    batSetTarget,                   ///< set target enemy
                                    ///< @param p0 target id
                                    ///< @param p1 #BT_TARGET_TYPE (optional, only valid while p0 is equal to zero)
    batSetRoleAsTarget,             ///< set role as owner's target
    batSetTargetAsRole,             ///< set owner's target to bt context role
    batSetLastCaster,               ///< set last caster
                                    ///< @param p0 #BT_TARGET_TYPE
    batSetScanEnemyParam,           ///< set scan enemy parameters
                                    ///< @param p0 scan enemy range (unit: cm)
    batSetScanFriendParam,          ///< set scan friend parameters
                                    ///< @param p0 scan friend range (unit: cm)
                                    ///< @param p1 NPC template id
    batSetScanCorpseParam,          ///< set scan corpse parameters
                                    ///< @param p0 NPC template id
                                    ///< @param p1 friendly corpse or not
    batSetScanAuraCharParam,        ///< set scan aura character parameters
                                    ///< @param p0 aura id
    batScanEnemy,                   ///< scan nearest enemy and set its as AI target
    batScanNearby,                  ///< scan nearby character and pick out suitable targets
	batScanRedName,                 ///< scan nearest role with red name and set it as AI target
									///< @param p0 whether only attack red name role
	batScanSabacWinner,				///< scan sabac winner and set it as AI target
	batScanSabacEnemy,				///< scan sabac enemy and set it as AI target
    batGetTargetFromThreatList,     ///< get target from owner's threat list within chase range
                                    ///< @param p0 chase range (unit:cm)
                                    ///< @note change target if already have one; or set target if have no target yet;
                                    ///< @see #batScanThreatList
    batPetGetTargetFromThreatList,  ///< pet get target from owner's threat list within chase range
                                    ///< @param p0 chase range (unit:cm)
                                    ///< @note change target if already have one; or set target if have no target yet;
                                    ///< @see #batScanThreatList
    batScanHostThreatList,          ///< get the nearest enemy target in owner's host's threat list
                                    ///< @param p0 scan range (unit:cm)
    batAddTargetThreat,             ///< add the given threat value to target enemy
                                    ///< @param p0 threat value 
    batSetBossState,                ///< set boss state value
                                    ///< @param p0 boss state value
    batSetFlag,                     ///< set owner's char flag 
                                    ///< @param p0 #CHAR_FLAG
                                    ///< @see #batCheckFlag, #batClearFlag
    batClearFlag,                   ///< clear owner's char flag
                                    ///< @param p0 #CHAR_FLAG
                                    ///< @see #batCheckFlag, #batSetFlag
    batPlayAction,					///< owner plays an action
                                    ///< @param p0 action id
    batSetCDTimer,                  ///< set cd timer
                                    ///< @param p0 #COOLDOWN_TYPE
                                    ///< @param p1 cd timer index [0, 65535]
                                    ///< @param p2 cd interval (unit:ms)
                                    ///< @param p3 max cd interval (unit:ms, optional)
                                    ///< @see #batCheckCDTimer
    batSetAIVariable,               ///< set ai processor's variable
                                    ///< @param p0 variable index
                                    ///< @param p1 absolute value (optional)
                                    ///< @param p2 relative value (optional)
                                    ///< @note p1 is effective only when p2 is zero
                                    ///< @see #batCheckAIVariable
    batStepAroundTarget,            ///< move some small steps around target
                                    ///< @param p0 prefer distance (unit:cm)
                                    ///< @param p1 chase threshold distance (unit:cm)
                                    ///< @note step distance should small enough to avoid interrupt normal fight 
    batCheckNeedChase,              ///< check if need chase
                                    ///< @param p0 chase threshold distance (unit:cm)
                                    ///< @see #batChase
    batCheckNeedWithdraw,           ///< check if need withdraw
                                    ///< @param p0 withdraw threshold distance (unit:cm)
                                    ///< @see #batWithdraw
    batCheckCanMove,                ///< check if can move

                                    ///< 检查是否可以施法（不考虑CD时间）
    batCheckCanCastSpell,           ///< check if can cast spell (without regard to CD time)

                                    ///< 对目标施展指定法术
    batCastSpellToTarget,           ///< cast specified spell to target
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE

    batCastSlotSpellToTarget,		///< cast specified spell to target, then wait until spell finish
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 slotid

    batCastSpellToPos,              ///< cast specified spell to position
                                    ///< @param p0 spell id
                                    ///< @param p1 x
                                    ///< @param p2 y
                                    ///< @param p3 z
    batCastSpellToTargetPos,        ///< cast specified spell to a pos with a offset base on target's position and face direction
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE
                                    ///< @param p2 direction offset
                                    ///< @param p3 distance offset
                                    ///< @note direction offset base on a direction from self to home position if param0 #BT_TARGET_TYPE be set tarHome
    batCastSpellToDir,              ///< cast specified  spell to a direction from self to target
                                    ///< @param p0 spell id
                                    ///< @param p1 direction
    batCastSpellToTargetDir,        ///< cast specified spell to a direction with a direction offset base on direction from self to target
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE
                                    ///< @param p2 direction offset
    batSyncCastSpellToTarget,       ///< cast specified spell to target, then wait until spell finish
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE
    batSyncCastSpellToPos,          ///< cast specified spell to position, then wait until spell finish
                                    ///< @param p0 spell id
                                    ///< @param p1 x
                                    ///< @param p2 y
                                    ///< @param p3 z
    batSyncCastSpellToTargetPos,    ///< cast specified spell to a pos with a offset base on target's position and face direction, then wait until spell finish
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE
                                    ///< @param p2 direction offset
                                    ///< @param p3 distance offset
                                    ///< @note direction offset base on a direction from self to home position if param0 #BT_TARGET_TYPE be set tarHome
    batSyncCastSpellToDir,          ///< cast specified  spell to a direction from self to target, then wait until spell finish
                                    ///< @param p0 spell id
                                    ///< @param p1 direction
    batSyncCastSpellToTargetDir,    ///< cast specified spell to a direction with a direction offset base on direction from self to target, then wait until spell finish
                                    ///< @param p0 spell id
                                    ///< @param p1 #BT_TARGET_TYPE
                                    ///< @param p2 direction offset

    batSyncCastSlotSpellToTarget,	///< cast specified spell to target, then wait until spell finish
                                    ///< @param p0 #BT_TARGET_TYPE
                                    ///< @param p1 slotid
	batWaitCastSpell,				///< wait until casting spell ends
	batSyncBreakCast,				///

                                    ///< 向当前区域发出特定信号
    batIssueSignal,                 ///< issue a specific signal to current region
                                    ///< @param p0 #SIGNAL_TYPE
                                    ///< @param p1 signal TTL (unit: ms)
                                    ///< @param p2 signal process times
                                    ///< @param p3 signal param (default 0)
                                    ///< @see batPickSignal

                                    ///< 尝试在特定距离内拾取特定信号，记录下来并减少停留时间
    batPickSignal,                  ///< try to pick a specific signal in a specific distance, record it and reduce remain times.
                                    ///< @param p0 #SIGNAL_TYPE
                                    ///< @param p1 distance(unit: cm)
                                    ///< @param p2 whether check signal param
                                    ///< @param p3 signal param value
									///< @see batIssueSignal

                                    ///< 改变 tarAITarget 从 Signal Issuer 的 tarAITarget
    batGetTargetFromSignal,         ///< change tarAITarget from Signal Issuer's tarAITarget
                                    ///< @note must invoke batPickSignal first  // 注意必须先调用batPickSignal

                                    ///< 设置巡逻参数
    batSetPatrolParam,              ///< set patrol parameters
                                    ///< @param p0 path id
                                    ///< @param p1 #PATROL_STYLE
                                    ///< @see #batPatrol

                                    ///< 根据给定路径
    batPatrol,                      ///< patrol in accordance with a given path (a origin server point whose dwNameID just like "p3.1")
                                    ///< @see #batSetPatrolParam

                                    ///< 获取信号发布者的tarAITarget，并将其添加到威胁列表中
    batAddThreatListFromSignal,     ///< get signal issuer's tarAITarget, and add it to threat list
                                    ///< @param p0 threat value of tarAITarget
                                    ///< @note must invoke batPickSignal first, usually used to respond signal sigSpreadHate

	batCheckIntValue,				///

    batGBuildingDead,               ///< when guild building dead, the action will spawn treasure in front of the killer who kill the building 
                                    ///< then say msg to defend guild and intruder guild
    
    batCheckHost,                   ///< check ai owner hostID
                                    ///< @param p0 is target type ( tarSelf, tarAITarget), tarSelf check host is NULL, not NULL return brvSuccess
                                    ///< @tarAITarget check AI target is my host, true return brvSuccess
    batMagePetCastSpellToTarget,    ///< use for mage pet, cast spell to target, then wait until spell finish, target type always tarAITarget
                                    ///< no param
    batPetScanEnemy,                ///< for pet. first,check host target. second, scan host threat list. third, scan 9 region.
                                    ///< @param p0 scan enemy(npc only) level limit
                                    ///< @param p1 scan enemy(npc only) range
    batJumpToHost,                  ///< no param
    batPetFollow,                   ///< owner starts to follow its host
                                    ///< @see #batSetFollowParam
    batPetCheckHostDirection,       ///< check host change direction
    batCheckThreatList,             ///< check whether target is in the threat list. return value: true means target is in threat list. false means not.
                                    ///< no param
    batPetChangeChaseTarget,        ///< pet change target in the chase
                                    ///< @param p0 is pet view range
    batPetChangeFightTarget,        ///< pet change target in fighting
                                    ///< @param p0 is pet view range
    batPetGetCaster,                ///< pet set caster as it's target
                                    ///< @param p0 is pet view range
    batCheckThreatFadeTime,         ///< check the target is disappeared in the threat list
                                    ///< @param p0 AI type, threat list owner
                                    ///< @param p1 AI type, target
                                    ///< @param p2 fade time
    batCheckThreatenFadeTime,       ///< check the target is disappeared in the threaten list
                                    ///< @param p0 AI type, threaten list owner
                                    ///< @param p1 AI type, target
                                    ///< @param p2 fade time
    batPetWander,                   ///< owner starts to wander
                                    ///< @param p0 range (unit:cm)
                                    ///< @param p1 interval (unit:ms)
    batPetCheckValidTarget,         ///< check pet ai target is valid
    batPetCheckNeedChase,           ///< check if need chase
                                    ///< @param p0 chase threshold distance (unit:cm)
                                    ///< @see #batChase
    batPetChase,                    ///< owner starts to chase its target
                                    ///< @param p0 prefer distance (unit:cm)
                                    ///< @param p1 chase threshold distance (unit:cm)
                                    ///< @param p2 delay time (unit:ms)
    batPetCheckRoleState,           ///< check pet host (host GetObjType == otRole)
    batPetStopMove,                 ///< set pet stop
    batPetDelSbFromThreatenList,    ///< remove target from pet's threaten list
    batPetDelSbFromThreatList,      ///< remove target from pet's & host's threat list
    batPetCheckHostTarget,          ///< check pet host target type
                                    ///< @param p0 object type 
    batPetClearHostTarget,          ///< set host cast target 0
	batSetAvoidGroundEffect,		///< avoid ground effect while moving, only valid for npc
									///< @param p0 enabled(default:false)
    batChangeGuildResource,         ///< send msg to ms & wait for result
                                    ///< @param p0 GUILD_RESOURCE_CHANGE_TYPE
                                    ///< @param p1, resource type(GUILD_ATTR_ENUM). 
                                    ///< @param p2 resource count
	batSetAlwaysRun,				///< set ai always run or not.
                                    ///< @param p0 TRUE/FALSE

    /************************************************************************/
    /* Scene                                                                */
    /************************************************************************/
    batTeleportSceneRoleToReturnPos,///< estGuildDungeon, estGuild, estBattleField and so on, code copy from CCliMessageHandler::OnLeaveScene
    batTpOtherGuildRoleToReturnPos, ///< estGuild, code copy from CCliMessageHandler::OnLeaveScene      for redmine bug : 6987
    batSceneRoleSetFaction,         ///< traverse role to set faction #BATTLE_FACTION
                                    ///< @param p0  #BATTLE_FACTION
    batSceneEndArena,               ///< special action, for arena , end arena, all role be defeated, teleport
   
									
    batEnd
};

//tolua_end

#endif // _BT_ACTION_H_
