#ifndef _SPIRIT_DEF_H_
#define _SPIRIT_DEF_H_    

// tolua_begin

// 境界总览
#define  SPIRIT_OPEN_LEVEL					1	// (境界开启等级)

#define  MAX_EXT2PTS_MULTIPLE				20	// (魂转修炼点一键完成的)金币消耗最大倍数(跟每次转化次数有关)
#define  MAX_EXP2PTS_THRESHOLD				50	// (魂转修炼点一键完成的)日常最大完成次数
#define  MAX_SPIRIT_LEVEL					70	// 境界最大等级	

#define  MAX_SPIRIT_NODE_PER_LEVEL			2	// 每个境界等级可以挂的node

// 气海
#define  MAX_AIRSEA_BAG_CONTAINER_SIZE		32	// 气海包裹的大小
#define	 MAX_AIRSEA_STALL_CONTAINER_SIZE	16  // 气海仓库的大小
#define  MAX_AIRSEA_EQUIP_CONTAINER_SIZE	9	// 气海装备栏大小

#define  MAX_AIR_PROCEDURE					5	// 练气阶段
#define	 MAX_DROP_AIR_COUNT					40	// 练期阶段可配置掉落数目

#define  MAX_AIR_LEVEL						10	// 气的最大等级
#define  MAX_AIR_NODE						256	// 最大node数目
#define	 MAX_ATTR_PER_NODE					2	// 每个node所带最大属性数目

#define  MAX_SPIRIT_BUY_SLOT_COST			100	// 买包裹消耗
#define  INVALID_AIR_ID						0	// 无效气id
#define  INVALID_AIR_INDEX					(-1)// 无效气位置

#define  MAX_EXP2PTS_LEVEL					32	// 魂转修炼点转化次数配置等级段

// 血海
#define  MAX_BLOODSEA_PAGE					4	// 血脉
#define  MAX_BLOODSEA_SLOT_PER_PAGE			10	// 每个血脉的孔数量
#define  MAX_BLOODSEA_SLOT_NUMBER			10	// 每个血脉孔出现的最大值
#define	 MAX_BLOODSEA_ATTR_PER_SLOT			2	// 每个血脉孔所带最大属性数量
#define  BLOODSEA_SLOT_INIT_SLOT			0	// 每个血脉孔开始的初始位置

enum SPIRIT_AIR_SEA_BAG_TYPE
{
	sasbtInvalid = -1,
	sasbtBag,
	sasbtStall,
	sasbtEquip,

	sasbtTotal,
};

enum SPIRIT_AIR_TYPE
{
	spiritInvalid = -1,
	spiritPower,	// 蛮力
	spiritSwift,	// 迅捷
	spiritWise,		// 睿智
	spiritBody,		// 刚体
	spiritDivine,	// 神圣
	spiritKing,		// 万法
};

inline INT32 MAKE_AIR_LEVEL_KEY(INT32 nLevel, INT32 nClass)
{
	return ((nLevel << 16) | nClass);
}

inline INT32 MAKE_BLOOD_KEY(INT32 nPage, INT32 nIndex, INT32 nNumber)
{
	return ((nPage << 24) | (nIndex << 16) | nNumber);
}

// tolua_end

static const INT8 INIT_SPIRIIT_AIR_SEA_BAG_SIZE[sasbtTotal] = {16, 8, 2};

#endif  //_SPIRITLEVEL_DEF_H_