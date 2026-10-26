#ifndef _SPIRITLEVEL_DEF_H_
#define _SPIRITLEVEL_DEF_H_    

// 境界总览
#define  MAX_EXT2PTS_MULTIPLE				20	// (魂转修炼点一键完成的)金币消耗最大倍数(跟每次转化次数有关)
#define  MAX_EXP2PTS_THRESHOLD				50	// (魂转修炼点一键完成的)日常最大完成次数

// 气海
#define  MAX_AIRSEA_CONTAINER_SIZE			24	// 气海包裹的大小1
#define  ORIGINAL_AIRSEA_CONTAINER_SIZE		12	// 初始气海包裹的大小
#define  MAX_SPIRIT_LEVEL					18	// 境界最大等级	

#define  MAX_AIR_PROCEDURE					5	// 练气阶段

#define  MAX_AIR_LEVEL						9	// 气的最大等级
#define  MAX_AIR_NODE						256	// 最大node数目
#define	 MAX_ATTR_PER_NODE					2	// 每个node所带最大属性数目

// 血海
#define  MAX_DAN_PER_LEVEL					1024 // 每一级丹最多能磕的数目
#define	 MAX_DAN_TYPE						5	 // 丹药类型种类
#define  MAX_DAN_LEVEL_PER_TYPE				7	 // 每一级丹的等级

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

#endif  //_SPIRITLEVEL_DEF_H_