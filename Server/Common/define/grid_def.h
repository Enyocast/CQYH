#ifndef _GRID_DEF_H_
#define _GRID_DEF_H_

#define GRID_LAYER_HEIGHT_BIT   (12)
#define NEXT_GRID_BIT           (7)
#define MAX_NEXT_GRID			(1 << NEXT_GRID_BIT)
#define GRID_VOLUME_BIT			(2)
#define GRID_DOOR_BIT			(2)
#define EDGE_INDEX_BIT			(4)
#define MAX_DOOR_PER_ZONE       (1 << GRID_DOOR_BIT)
#define MAX_VOLUME_PER_ZONE		(1 << GRID_VOLUME_BIT)
#define MAX_EDGE_INDEX_PER_ZONE	(1 << EDGE_INDEX_BIT)
#define MAX_CHAR_PER_GRID		(15)
#define MAX_DROP_PER_GRID       (3)
#define MAX_QUEST_PER_ZONE		(4)

enum GRID_PK_TYPE
{
    gptInvalid = -1,

	gptNormal,  // 普通区域（默认PK规则）
	gptFree,    // 自由PK区（允许无限制PK）
	gptSafe,    // 安全区（禁止PK）

    gptTotal
};


// GRID_DATA 决定网格的规则（能否行走、是否安全区）。
// GRID_INSTANCE_DATA 记录网格的实时变化（当前有多少角色、是否有技能特效）。

#pragma pack(push, 1)

struct GRID_DATA
{
	// 基础属性
	unsigned uNextGrid				: NEXT_GRID_BIT;    // 下一层网格索引（用于多层结构）
	unsigned uNoObstacle			: 6;				// 无障碍标记（可能用于快速判断）
	unsigned uVolume				: GRID_VOLUME_BIT;  // 体积区域索引
	unsigned uDoor					: GRID_DOOR_BIT;    // 若值非0，可能表示门的状态影响通行

	// 其他功能
	unsigned uPkType				: 2;    // 门状态（0=无门）
	unsigned bBorder				: 1;

	// 摆摊区 - 标识网格是否属于摆摊区域及其等级 (0=普通区域(不可摆摊), 1/2/3=不同等级的摆摊区(例如：初级摆摊区、高级摆摊区))
	unsigned uStallLevel			: 2;

	unsigned bQuest					: 1;    // 任务点?

	// 阻挡标记
	unsigned bBlockMove				: 1;    // 1=阻挡移动（障碍点）
	unsigned bBlockLeap				: 1;	// 1=阻挡跳跃
	unsigned bBlockMissile			: 1;	// 1=阻挡导弹
	unsigned bBlockBullet			: 1;	// 1=阻挡子弹


	unsigned bNotBlockChar			: 1;
	unsigned bMine                  : 1;    // 是否是矿点
	unsigned bCannotTeleport		: 1;    // 是否禁止传送(1=禁止，0=允许)
	unsigned bRoleCannotLoseItem	: 1;    // 玩家死亡时, 在此网格是否不会掉落物品(例如安全区)(1=禁止，0=允许)
	unsigned bRoleCannotDropItem	: 1;    // 角色不能丢弃物品区(1=禁止，0=允许)
	// 第1个 32位结束

	unsigned bSlayerArea			: 1;    // 红名区
	unsigned bCannotDropItem		: 1;	// 是否禁止丢弃物品（1=禁止，0=允许）
	unsigned uMineLevel				: 2;	// 矿点等级?
	unsigned bTeleportPoint			: 1;    // 是否是传送点
	unsigned uReserved1				: 27;	// 预定占位27位
	// 第2个 32位结束

	unsigned uReserved2				: 32;	// 预定占位32位
	// 第3个 32位结束

	// 高度
	unsigned uLowLayer				: GRID_LAYER_HEIGHT_BIT;    // 底层高度
	unsigned uHighLayer				: GRID_LAYER_HEIGHT_BIT;    // 高层高度
	unsigned uEdge					: EDGE_INDEX_BIT;

	// 逻辑标记
	unsigned bOutOfPoly				: 1;    // 1=在多边形区域外（不可行走）
	unsigned bInServerPointRange	: 1;	// 是否在服务器点范围内
	unsigned uReserved3				: 2;	// 预定占位2位
	// 第4个 32位结束
};

// 网格实例数据
struct GRID_INSTANCE_DATA
{
	unsigned char uCharRef			: 4;    // 当前网格中 角色引用数量
	unsigned char uDropRef			: 2;    // 当前网格中 掉落物引用数量
	unsigned char uMissileTag1		: 1;    // 当前网格是否有 导弹/投射物 存在
	unsigned char uMissileTag2		: 1;
	unsigned short uReserved		: 8;    // 预定占位8位
};

#pragma pack(pop)

#endif  // _GRID_DEF_H_