#ifndef _SCENE_DEF_H_
#define _SCENE_DEF_H_

/// @file scene_def.h
/// @brief basic definition of game scene

// tolua_begin

#define POINT_PER_CM			                (1LL << 10)									///< @line (unit: point)
#define POINT_PER_METER                         (POINT_PER_CM * 100)						///< @line (unit: point)
#define GAME_FPS	                            (16)										///< @line (unit: frame/second)
#define GRID_WIDTH                              (POINT_PER_CM * 128)						///< @line (unit: point)
#define GRID_LAYER_HEIGHT		                (POINT_PER_CM * 16)							///< @line (unit: point)
#define ZONE_WIDTH                              (POINT_PER_CM * 512)						///< @line (unit: point)
#define REGION_WIDTH			                (POINT_PER_CM * 2048)						///< @line (unit: point)
#define MAX_SCENE_WIDTH			                (POINT_PER_CM * 128 * 2048)					///< @line (unit: point)
#define MAX_REGION_PER_SCENE	                (MAX_SCENE_WIDTH / REGION_WIDTH)			///< @line (unit: N/A)
#define MAX_ZONE_PER_SCENE                      (MAX_SCENE_WIDTH / ZONE_WIDTH)				///< @line (unit: N/A)
#define GRID_PER_ZONE                           (ZONE_WIDTH / GRID_WIDTH)					///< @line (unit: N/A)
#define MAX_MOVE_SPEED                          (1600 * POINT_PER_CM / 1000)				///< @line (unit: point/ms)

#define MAX_NPC_SPAWN_POINT_PER_SMALL_GROUP     (1024)										///< @line 
#define MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP    (4)											///< @line 
#define MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP    (128)										///< @line 
#define MAX_NPC_MEDIUM_GROUP_COUNT              (1024)										///< @line 
#define MAX_NPC_LARGE_GROUP_COUNT               (16)										///< @line 
#define MAX_NPC_TEMPLATE_COUNT                  (4)											///< @line 
#define MAX_SINGLE_NPC_COUNT                    (1024)										///< @line

#define MAX_DOODAD_SPAWN_GROUP_COUNT            (64)										///< @line
#define MAX_DOODAD_SPAWN_POINT_COUNT            (512)										///< @line
#define MAX_DOODAD_COUNT_PER_GROUP              (8)											///< @line

#define MAX_SCENE_ENTER_DISTANCE                (REGION_WIDTH * REGION_WIDTH >> 4L)
#define MAX_DOOR_ID                             (64)										///< @line

#define MAX_SCENE_TEMPLATE_COUNT                (256)										///< @line
#define MAX_VOLUME_COUNT                        (256)										///< @line
#define MAX_RANDOM_WEATHER_COUNT				(4)											///< @line

#define MAX_SYNC_CHAR_COUNT		                (256)										///< @line
#define MAX_SYNC_DOODAD_COUNT	                (128)										///< @line

#define MAX_VELOCITY_Z                          (-2048 * POINT_PER_CM) / GAME_FPS                   ///< @line (unit: point/frame)
#define GLOBAL_GRAVITY                          ((2048 * POINT_PER_CM) / (GAME_FPS * GAME_FPS))     ///< @line (unit: point/frame^2)

#define SCENE_READY_TIME                        (GAME_FPS * 60)
#define MAX_SIDE_COUNT		                    (4)
#define MAX_FACTION_COUNT	                    (3)

#define ROLE_HEIGHT			                    200 * POINT_PER_CM							///< @line
#define SYNC_BATTLE_MEMBER_TIME				    (5 * GAME_FPS)	

#define MAX_LINE_SCENE_NUMBER					(32)

#define DAYTIME_HOURS							(2)

#define DL_RECORD_ROLET_INTERVAL				(3600*GAME_FPS)

#define MAX_MINE_DROP_GROUP						(8)
#define MAX_MINE_LEVEL							(4)

///@enum SCENE_WEATHER_TYPE
enum SCENE_WEATHER_TYPE
{
	swtInvalid,			        ///< @line

	swtNormal,					///< @line
	swtFog,						///< @line
	swtThunder,					///< @line
	swtRain,					///< @line
	swtSnow,					///< @line
	swtStorm,					///< @line
	swtEclipse,					///< @line

	swtTotal					///< @line
};

///@enum SCENE_DAYTIME_TYPE
enum SCENE_DAYTIME_TYPE
{
    sdtInvalid = -1,			///< @line

    sdtDay,                     ///< @line
    sdtNight,                   ///< @line

    sdtTotal					///< @line
};

//enum ESceneVarType
//{
//	esvtInvalid = -1,
//	esvtSceneLostFaction,
//	esvtTotal
//};

///@enum ENUM_SCENE_VA
enum ENUM_SCENE_VA
{
    estInvalid = 0,				///< @line

    estStatic,					///< @line
    estDungeon,					///< @line
    estBattleField,				///< @line
    estArena,					///< @line
    estLine,					///< @line
	estBirth,					///< @line
    estGuild,					///< @line
	estGuildDungeon,			///< @line
	estUnique,					///< @line
	estSoloDungeon,				///< @line

    estTotal                    ///< @line
};

enum LINE_SCENE_STATE
{
	lssInvalid,

	lssNormal,
	lssBusy,
	lssFull,

	lssTotal
};

enum OBJ_BODY_TYPE
{
	bodyInvalid,
	
	body0x0,
	body1x1,
	body3x3,

	bodyTotal
};
struct ABSOLUTE_SCENE_POS
{
    INT32           nSceneTempID;
    INT32           nSceneID;
    INT32           nX;
    INT32           nY;
    INT32           nZ;
    INT32           nFaceDirection;
};

struct ENTER_POS
{
	INT32           nSceneTempID;
	INT32           nSceneID;
	UINT8			bySide;
};

// 不知道干啥用的函数, lua脚本里也没调用过
inline double I64_2_Double(INT64 llPos)
{
	return (double)llPos / POINT_PER_CM;
}

// 服务器坐标 转 协议坐标
/*
// 调用例子
pMsg->drop.wDestX = ConvertCoordS2N(poDrop->GetX());
pMsg->drop.wDestY = ConvertCoordS2N(poDrop->GetY());
pMsg->drop.wDestZ = ConvertCoordS2N(poDrop->GetZ());
*/
inline UINT16 ConvertCoordS2N(INT64 llCoordination)
{
    return (UINT16)(llCoordination / POINT_PER_CM / 4);
}

// 协议坐标 转 服务器坐标 (转换之后, 需要修正坐标)
/*
// 调用例子
nRetCode = poRole->WalkTo(ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
PROCESS_ERROR(nRetCode);

// 在 WalkTo 函数里面, 再计算一次, 修正坐标
m_llDestX = llDestX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
m_llDestY = llDestY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
*/
inline INT32 ConvertCoordN2S(UINT16 wCoordination)
{
    return (INT32)wCoordination * POINT_PER_CM * 4;
}

// 客户端内存坐标 转 服务器坐标 (转换之后, 再 乘以 POINT_PER_CM, 才是真正的服务器坐标)
/*
// 调用例子
ConvertCoordO2N(pData->nLoginJumpX, pData->nLoginJumpY, pData->nLoginJumpZ);
pData->nLoginJumpX = pData->nLoginJumpX * POINT_PER_CM;
pData->nLoginJumpY = pData->nLoginJumpY * POINT_PER_CM;
pData->nLoginJumpZ = pData->nLoginJumpZ * POINT_PER_CM;
*/
inline void ConvertCoordO2N(INT32& rnX, INT32& rnY, INT32& rnZ)
{
	const INT64 k = 70710;
	const INT64 b = 100000;
	INT64 llX = rnX;
	INT64 llY = rnY;
	rnX = (INT32)((llX * k - llY * k + (MAX_SCENE_WIDTH / POINT_PER_CM) * b / 2) / b);
	rnY = (INT32)((llX * k + llY * k) / b);
}

// 服务器坐标 转 客户端内存坐标 (转换之前, 先 除以 POINT_PER_CM)
/*
// 调用例子
INT32 nX = pSpawnPoint->nX / POINT_PER_CM;
INT32 nY = pSpawnPoint->nY / POINT_PER_CM;
INT32 nZ = pSpawnPoint->nZ / POINT_PER_CM;
ConvertCoordN2O(nX, nY, nZ);
*/
inline void ConvertCoordN2O(INT32& rnX, INT32& rnY, INT32& rnZ)
{
	const INT64 k = 70710;
	const INT64 b = 100000;
	INT64 llX = rnX - MAX_SCENE_WIDTH / POINT_PER_CM / 2;
	INT64 llY = rnY;
	rnX = (INT32)((llX * k + llY * k) / b);
	rnY = (INT32)((-llX * k + llY * k) / b);
}


// tolua_end

#endif	// _SCENE_DEF_H_