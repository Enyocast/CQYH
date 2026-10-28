/********************************************************************
	created:	7:4:2013   15:21
	file:		guild_def.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GUILD_DEF_H_
#define _H_GUILD_DEF_H_

#include "variable_def.h"

#define GUILD_CREATER_LEVEL     (12)
#define GUILD_CREATE_MONEY      (200000)
#define GUILD_CREATE_ITEM_ID    (80002)
#define GUILD_CREATE_ITEM_NUM   (1)


// unused
#define MAX_GUILD_NUM_SYSTEM_LIMIT  (16384)
#define MAX_APPLY_GUILD_ROLE_NUM    (200)   // 帮派最多允许申请的玩家数量，暂定
#define GUILD_MAX_MEMBER_COUNT    (250)           // 最大成员数量
//#define GUILD_MEMBER_SYS_LIMIT      (250)       // 系统限制的最大玩家数量

#define MAX_VIEW_GUILD_LIST_COUNT (12)      // 帮派查看，一次发送帮派数量

#define ROLE_MAX_APPLICATION     (10)       // 角色一次最多可申请加入的帮派数量

#define GUILD_MAX_ALLIANCE_NUM      (10)     // 最大联盟帮派数量
#define GUILD_MAX_ENEMY_NUM          (64)    // 最大敌对帮派数量

#define GUILD_DATA_NTF_HISTORY_NUM   (10)
#define GUILD_MAX_CHEST_NTF_NUM     (50)

#define GUILD_MAX_HISTORY_EVENT_NUM (150)
#define GUILD_MAX_STORAGE_EVENT_NUM (100)
#define GUILD_MAX_CHEST_EVENT_NUM   (100)

#define GUILD_STORAGE_MAX_ITEM_NUM_PER_TAG  (56)
#define GUILD_STORAGE_MAX_TAG_NUM (6)
#define GUILD_STORAGE_LOW_LIMIT     (10000)

#define GUILD_MAX_APPLY_ALLIANCE_NUM    (250)           // 再大每次发送就不考虑了，这都是世界公敌了

#define GUILD_MAX_WELFARE_AURA_COUNT  (64)
#define GUILD_MAX_UPGRADE_AURA_COUNT (2)
#define GUILD_MAX_UPGRADE_BUILDING_COUNT (2)

#define GUILD_MAX_DUNGEON_COUNT     (32)

//#define WEEK_SECOND (604800)
#define ONE_DAY_SECOND      (86400)
//#define ROLE_APPLICATION_LAST_TIME  (300) // 申请存在时间
//#define GUILD_DISBAND_LEVEL_LIMIT   (3)     // 帮派解散的最高等级限制，低于这个等级才可以删除

#define GUILD_UPDATE_RANKLIST_STARTTIME		(3600*4)	// 帮派刷新排行榜开始时间，每天凌晨4点开始
#define GUILD_UPDATE_RANKLIST_ENDIME		(3600*4 + 128)	// 帮派刷新排行榜结束时间，持续128秒，1024桢内做完

#define GUILD_DUNGEON_AWARD_NUM (8)

#define GUILD_MAX_ITEM_BUFFER_LENGTH    (96)

#define GUILD_MAX_BUILDING_LEVEL    (6)
#define GUILD_MAX_BUILDING_NUM     (128)
//#define GUILD_MAIN_SINGLE_NPC_ID    (1)
#define GUILD_MAX_GATE_NUM      (8)

#define MAX_SABAC_ENROLL_COUNT (4)

#define GUILD_MAX_ACHIEVEMENT_NUM   (24)
#define GUILD_MAX_ACHI_ARRAY_LENGTH   (3)    // GUILD_MAX_ACHIEVEMENT_NUM / 8

#define GUILD_WAR_RECORD_NUM_PER_PAGE   (12)


//////////////////////////////////////////////////////////////////////////
// server use

#define MAX_TIME_DEVIATION      (10)            // 允许时间计算误差

#define MAX_GUILD_CORE_MEMBER   (20)

//////////////////////////////////////////////////////////////////////////


enum GUILD_NOTIFY_TYPE
{
    GUILD_NOTIFY_ROLE_APP           = 1,
    GUILD_NOTIFY_DIPLOMAT_APP,
    GUILD_NOTIFY_MATCH_WAR, 

};


enum GUILD_VIEW_TYPE
{
    GUILD_VIEW_UP = 1,
    GUILD_VIEW_DOWN = 2,
};


enum GUILD_POSITION_TYPE
{
    GUILD_POSITION_NONE         = 0,
    GUILD_POSITION_LEADER       = 1,
    GUILD_POSITION_SUBLEADER    = 2,
    GUILD_POSITION_ELDER        = 3,
    GUILD_POSITION_BISHOP       = 4,        // 主教 ， 殿主
    GUILD_POSITION_DEACON       = 5,        // 执事
    GUILD_POSITION_SUBDEACON    = 6,        // 副执事，主簿
    GUILD_POSITION_CIVILIAN     = 7,        // 帮众

    GUILD_POSITION_TOTAL        = 8,
};

#define GUILD_POSITION_COUNT  (GUILD_POSITION_TOTAL-1)       // GUILD_POSITION_TYPE 关联这个

enum GUILD_POSITION_RIGHT_FIELD
{
    G_POS_RIGHT_NONE                = 0,
    G_POS_RIGHT_INVITE              = 1 << 0,               // 邀请权限（觉得有重复）
    G_POS_RIGHT_RECRUIT             = 1 << 1,               // 拒绝或者接受的权限
    G_POS_RIGHT_FORBID_CHAT         = 1 << 2,
    G_POS_RIGHT_NOTICE              = 1 << 3,
    G_POS_RIGHT_SET_STORAGE_RIGHT   = 1 << 4,
    G_POS_RIGHT_OPEN_DUNGEON        = 1 << 5, 
    G_POS_RIGHT_UPGRADE_BUILDING    = 1 << 6,  
    G_POS_RIGHT_UPGRADE_WELFARE     = 1 << 7,
    G_POS_RIGHT_CHANGE_POS          = 1 << 8,
    G_POS_RIGHT_BANISH              = 1 << 9,
    G_POS_RIGHT_DIPLOMAT            = 1 << 10,      // 外交
    G_POS_RIGHT_ACTIVITY            = 1 << 11,

    //G_POS_RIGHT_MANAGE_MONEY = 1 << 8,
};

enum GUILD_STORAGE_RIGHT_FLAG
{
    G_STORAGE_1_POP     = 1 << 0,
    G_STORAGE_2_POP     = 1 << 1,
    G_STORAGE_3_POP     = 1 << 2,
    G_STORAGE_4_POP     = 1 << 3,
    G_STORAGE_5_POP     = 1 << 4,
    G_STORAGE_6_POP     = 1 << 5,
    G_STORAGE_1_PUSH    = 1 << 6,
    G_STORAGE_2_PUSH    = 1 << 7,
    G_STORAGE_3_PUSH    = 1 << 8,
    G_STORAGE_4_PUSH    = 1 << 9,
    G_STORAGE_5_PUSH    = 1 << 10,
    G_STORAGE_6_PUSH    = 1 << 11,
};

enum GUILD_FLAG_FIELD
{
    GUILD_FLAG_IS_CHAT_FORBIDDEN = 1 << 0,  // 是否被禁言
};

enum GUILD_DIPLOMATIC_TIME_TYPE
{
    G_DIPLOMATIC_TIME_1     = 1,    // 1天
    G_DIPLOMATIC_TIME_2     = 2,    // 3天
    G_DIPLOMATIC_TIME_3     = 3,    // 7天
    G_DIPLOMATIC_TIME_4     = 4,    // 30天
};

enum GUILD_REVERT_APPLY_ENUM
{
    GUILD_REVERT_REFUSE = 1,
    GUILD_REVERT_AGREE  = 2,
};


enum GUILD_FORBID_CHAT_ENUM
{
    GUILD_CHAT_FORBID       = 1,
    GUILD_CHAT_UNFORBID     = 2,
};

enum GUILD_RESOURCE_CHANGE_TYPE
{
    GUILD_RES_ADD_COUNT     = 1,
    GUILD_RES_DEC_COUNT     = 2,
    GUILD_RES_ADD_PERCENT   = 3,
    GUILD_RES_DEC_PERCENT   = 4,
};

enum GUILD_ATTR_ENUM
{
    // 前面的给guild variables 用的，相当于index Allan Tao[19.11.2013] 
    GUILD_ATTR_BEGIN = MAX_GUILD_VARIABLE_COUNT + 1,
    GUILD_ATTR_MONEY,
    GUILD_ATTR_LEVEL,
	GUILD_ATTR_SALARY,
	GUILD_ATTR_HERB,
    GUILD_ATTR_WOOD,
    GUILD_ATTR_CRYSTAL,
    GUILD_ATTR_SILVER,
    GUILD_ATTR_PROSPERITY,
    GUILD_ATTR_ATTACK_CD,
    GUILD_ATTR_PROTECTION_TIME,
};

enum GUILD_JOIN_AGREE_TYPE  /////////////////////////////////////////////////////////
{
    GUILD_AGREE_BY_APPLY = 1,
    GUILD_AGREE_BY_INVITE = 2,
};

enum GUILD_LEAVE_TYPE
{
    GUILD_LEAVE_ACTIVE  = 1,
    GUILD_LEAVE_PASSIVE = 2,
};

// diplomat
enum GUILD_DIPLOMAT_OP_TYPE
{
    GUILD_DIPLOMAT_NEUTRALLY = 0,
    GUILD_DIPLOMAT_ALLIANCE = 1,
    GUILD_DIPLOMAT_ENEMY     = 2,
};

enum GUILD_DIPLOMAT_TIME_TYPE
{
    GUILD_DIPLOMAT_TIME_BEGIN = 0,
    GUILD_DIPLOMAT_TIME_ONE     = 1,
    GUILD_DIPLOMAT_TIME_THREE   = 2,
    GUILD_DIPLOMAT_TIME_SEVEN   = 3,
    GUILD_DIPLOMAT_TIME_THIRTY  = 4,
    GUILD_DIPLOMAT_TIME_END,
};


enum GUILD_HISTORY_EVENT_TYPE
{
    GUILD_HE_TYPE_BEGIN             = 0,
    GUILD_HE_TYPE_CREATE            = 1,
    GUILD_HE_TYPE_JOIN              = 2,
    GUILD_HE_TYPE_LEAVE             = 3,
    GUILD_HE_TYPE_BANISH            = 4,
    GUILD_HE_TYPE_POSITION_CHANGE   = 5,
    GUILD_HE_TYPE_BUILDING_LVLUP    = 6,
    GUILD_HE_TYPE_SKILL_LVLUP       = 7,
    GUILD_HE_TYPE_DEMISE            = 8,
    GUILD_HE_TYPE_UNION             = 9,
    GUILD_HE_TYPE_ENEMY             = 10,

    GUILD_HE_TYPE_WAR               = 11,

    GUILD_HE_TYPE_BUILDING_CREATE   = 12,
    GUILD_HE_TYPE_BUILDING_DESTORY  = 13,
    GUILD_HE_TYPE_BUILDING_DEL      = 14,
    GUILD_HE_TYPE_BUILDING_REVIVE   = 15,           ///----
    GUILD_HE_TYPE_ATTACK_SUCC       = 16,
    GUILD_HE_TYPE_ATTACK_FAILED     = 17,
    GUILD_HE_TYPE_DEFEND_SUCC       = 18,
    GUILD_HE_TYPE_DEFEND_FAILED     = 19,

    GUILD_HE_TYPE_OPEN_ACTIVITY     = 20,
    GUILD_HE_CANCEL_ALLIANCE        = 21,


    GUILD_HE_TYPE_END               = 30,


    GUILD_CHEST_BEGIN               = 50,
    GUILD_CHEST_CREATE_BUILDING     = 50,
    GUILD_CHEST_ACTIVITY            = 51,
    GUILD_CHEST_CONTRIBUTE          = 52,
    GUILD_CHEST_B_UPGRADE           = 53,           // need to parse
    GUILD_CHEST_W_UPGRADE           = 54,           // need to parse
    GUILD_CHEST_ALLIANCE            = 55,
    GUILD_CHEST_ARMY                = 56,
    GUILD_CHEST_WAR_SACK_A_1        = 57,           // money
    GUILD_CHEST_WAR_SACK_A_2        = 58,           // rice,wood,stone,iron
    GUILD_CHEST_WAR_SACK_D_1        = 59,           // money
    GUILD_CHEST_WAR_SACK_D_2        = 60,           // rice,wood,stone,iron
    GUILD_CHEST_WAR_WIN             = 61,
    GUILD_CHEST_WAR_LOSE            = 62,

    // log
    GUILD_CHEST_CANCEL_BUILDING_UPGRADE = 63,
    GUILD_CHEST_CANCEL_WELFARE_UPGRADE = 64,
    GUILD_CHEST_DEL_BUILDING = 65,
    GUILD_CHEST_OPEN_DUNGEON = 66,
    GUILD_CHEST_COMPLETE_DUNGEON = 67,
    GUILD_CHEST_WAR_PLUNDER = 68,
    GUILD_CHEST_WAR_PLUNDER_EXTRA = 70,
    GUILD_CHEST_ROUTINE_CONSUME = 71,
    GUILD_CHEST_DECLARE_WAR = 72,
    GUILD_CHEST_MATCH_WAR = 73,
    GUILD_CHEST_BUILDING_DAMAGE = 74,
    
    GUILD_CHEST_GM = 75,

    GUILD_CHEST_END                 = 80,

    
    STORAGE_HE_TYPE_BEGIN           = 90,
    STORAGE_HE_TYPE_PUSH            = 91,
    STORAGE_HE_TYPE_POP             = 92,
};

enum GUILD_STORAGE_TAG
{
    GUILD_STORAGE_TAG_1     = 0,
    GUILD_STORAGE_TAG_2     = 1,
    GUILD_STORAGE_TAG_3     = 2,
    GUILD_STORAGE_TAG_4     = 3,
    GUILD_STORAGE_TAG_5     = 4,
    GUILD_STORAGE_TAG_6     = 5,
};

enum GUILD_REPLY
{
    GUILD_REPLY_REFUSE = 0,
    GUILD_REPLY_AGREE = 1,
};

// new version
enum GUILD_BUILDING_ENUM
{
    GUILD_B_NONE                = 0,
    GUILD_B_MAIN                = 1,    // 主殿
    GUILD_B_BUSINESS            = 2,    // 商会
    GUILD_B_DEITY               = 3,    // 神坛
    GUILD_B_HOUSE               = 4,    // 居所
    GUILD_B_STORAGE             = 5,    // 金库
    GUILD_B_STAFF               = 6,    // 战事厅
    GUILD_B_WONDER              = 7,    // 图腾
    GUILD_B_HERB                = 8,    // 农场
    GUILD_B_WOOD                = 9,    // 林场
    GUILD_B_CRYSTAL             = 10,   // 石场
    GUILD_B_SILVER              = 11,   // 矿场
    GUILD_B_HERB_STORAGE        = 12,   // 粮仓
    GUILD_B_WOOD_STORAGE        = 13,   // 木仓
    GUILD_B_CRYSTAL_STORAGE     = 14,   // 石仓
    GUILD_B_SILVER_STORAGE      = 15,   // 矿仓

    GUILD_B_FUNATIONAL_NUM      = 16,

    GUILD_B_GATE                = 16,   // 城门
    GUILD_B_WALL                = 17,   // 城墙

    GUILD_B_ARMSHOP             = 18,   // 兵工厂
    GUILD_B_ARROW               = 19,	// 箭塔
    GUILD_B_TURRET              = 20,	// 炮塔
    GUILD_B_GROUP_ATTACK        = 21,   // 群攻塔
    GUILD_B_MAGIC               = 22,   // 魔法塔
    GUILD_B_CURE                = 23,   // 加血塔
	
    GUILD_B_BLOCK               = 24,   // 路障

    GUILD_B_NUM,


    GUILD_B_PROTECTOR           = GUILD_B_NUM,          // 公会保护者




};

enum GUILD_CHANGE_WEATHER_TIME_TYPE
{
    GUILD_CW_TIME_NONE = 0,
    GUILD_CW_TIME_5M    = 1,
    GUILD_CW_TIME_10M   = 2,
    GUILD_CW_TIME_30M   = 3,
    GUILD_CW_TIME_END   ,
};

enum GUILD_STATE
{
    GUILD_STATE_NONE            = 0,
    GUILD_STATE_STOP_WELFARE    = 1 << 0,
};

enum GUILD_ENTER_MAP_TYPE 
{
    GUILD_ENTER_OWNER = 1,
    GUILD_ENTER_ALLIANCE = 2,
};
 

#define GUILD_MAX_INTRUDER_NUM      (256)
enum GUILD_WAR_CHARACTER
{
    GUILD_WAR_NONE      = 0,
    GUILD_WAR_INTRUDER  = 1 << 0,
    GUILD_WAR_DEFENDER  = 1 << 1,
};

enum GUILD_WAR_STAGE
{
    GUILD_WAR_STAGE_NONE      = 0,
    GUILD_WAR_STAGE_DECLARE   = 1,
    GUILD_WAR_STAGE_BEGIN     = 2,
    GUILD_WAR_STAGE_END       = 3,

};

enum GUILD_WAR_DEFENDER_RESULT
{
    GUILD_WAR_DEFENDER_NONE      = 0,
    GUILD_WAR_DEFENDER_WIN       = 1,
    GUILD_WAR_DEFENDER_LOSE      = 2,
};


enum UPGRADE_BUILDING_TYPE
{
    G_B_UPGRADE_BY_NPC      = 1,
    G_B_UPGRADE_BY_PANEL    = 2,
};

enum GUILD_BUILDING_STATE
{
    GUILD_BUILDING_ENABLE = 0, 
    GUILD_BUILDING_DISABLE = 1,
};

enum GUILD_CAST_SPELL_TYPE
{
    GUILD_CS_UPGRADING  = 1,
    GUILD_CS_UPDATE     = 2,
    GUILD_CS_DEL        = 3,
};

enum SABAC_STATE
{
	sabNotEnroll = 0,
	sabEnrolled,
	sabOccupied,
};


////////////////////////////// guild achievement begin ////////////////////////////////

enum GUILD_ACHIEVEMENT_TYPE
{
	GUILD_ACHI_BEGIN    = 0,
	GUILD_ACHI_NONE		= GUILD_ACHI_BEGIN,
    GUILD_ACHI_MEMBER,
    GUILD_ACHI_ENEMY,
    GUILD_ACHI_ALLIANCE,

    GUILD_ACHI_TAKE_POS_1,
    GUILD_ACHI_TAKE_POS_2,

    GUILD_ACHI_TYPE_NUM,
};

enum GUILD_ACHIEVEMENT_AWARD_TYPE
{
    GA_AWARD_NONE   = 0,
    GA_AWARD_POINT  = 1,
    GA_AWARD_EXP,
    GA_AWARD_ITEM,
    GA_AWARD_TITLE,
    GA_AWARD_NUM,
};

//enum GUILD_ACHIEVEMENT_ID
//{
//    GA_ID_NONE          = 0,
//    GA_MEMBER_50        = 1,
//    GA_MEMBER_100       ,
//    GA_MEMBER_150       ,
//    GA_MEMBER_200       ,
//    GA_MEMBER_250       ,
//
//    GA_ALLIANCE_1       ,
//    GA_ALLIANCE_5,
//    GA_ALLIANCE_10,
//    GA_ENEMY_1,
//    GA_ENEMY_5,
//};

////////////////////////////// guild achievement end //////////////////////////////////

 


enum GUILD_VARIABLE
{
    avGuildWarCanOpen = 1,         // main controller, gm use

};


// GUILD_MAX_MEMBER_COUNT
const static INT32 ARR_GUILD_POS_HUMAN_NUM[GUILD_POSITION_TOTAL] = {
    1,          // GUILD_POSITION_LEADER
    1,          // GUILD_POSITION_SUBLEADER
    4,          // GUILD_POSITION_ELDER
    4,          // GUILD_POSITION_BISHOP
    8,          // GUILD_POSITION_DEACON
    16,         // GUILD_POSITION_SUBDEACON
    216         // 116, GUILD_POSITION_CIVILIAN  
};

const   INT32   GUILD_STAT_TOP_NUM = 20;
const   INT32   MAX_GUILD_STAT_TOP_INDEX = GUILD_STAT_TOP_NUM - 1;

struct GUILD_RESOURCE_STAT
{
    UINT32      dwGuildID;
    UINT32      dwValue;
};

struct GUILD_STAT 
{
    INT32           nGuildNum;

    GUILD_RESOURCE_STAT      MoneyList[GUILD_STAT_TOP_NUM];
    GUILD_RESOURCE_STAT      RiceList[GUILD_STAT_TOP_NUM];
    GUILD_RESOURCE_STAT      WoodList[GUILD_STAT_TOP_NUM];
    GUILD_RESOURCE_STAT      StoneList[GUILD_STAT_TOP_NUM];
    GUILD_RESOURCE_STAT      MetalList[GUILD_STAT_TOP_NUM];

    INT32   BuildingStat[GUILD_B_NUM][GUILD_MAX_BUILDING_LEVEL + 1];
};

enum COOLDOWN_GUILD_ID 
{
    CD_GUILD_QUERY_WAR      = 0,
};


#define GUILD_SAVE_DELAY_TIME   (5)




#endif //_H_GUILD_DEF_H_




