/********************************************************************
	created:	5:3:2014   10:49
	file:		gm_def.h
	author:		Allan Tao
	
	purpose:	gmserver和gmtool共用头文件
*********************************************************************/


#ifndef _H_GM_DEF_H_
#define _H_GM_DEF_H_

#include "string_def.h"


#define FOREVER_TIME (2082729600)

#define MAX_GM_ROLE_KEY_NUM        (480)

#define GM_SVR_TIMEOUT          (10)
#define GM_SVR_LONG_TIMEOUT     (60)
#define TL_CMD_TIMEOUT_TIME     (30)
#define TL_CMD_LONG_TIMEOUT     (70)

#define GM_TYPE_CLIENT_CS       (1)

#define MSG_LOG_ITEM_COUNT      (600)

#define MAX_GM_GAMELOG_LENGTH   (1024 * 32)
#define MAX_GM_ROLE_DATA_STR_LENGTH     ( 1024 * 32 )
#define MAX_GM_LOG_LENGTH       (1024*32)
#define GM_DATA_LOG_LENGTH      (256)



//enum GM_ERR_DEF
//{
//
//
//};


enum GM_QUERY_ROLE_ID_TYPE
{
    GM_QUERY_BY_ROLE_NAME = 1,
    GM_QUERY_BY_USER_NAME = 2,
};



enum GM_LOG_TYPE
{
    GM_LOG_QUERY_NONE           = -1,
    GM_LOG_QUERY_ROLE_LOGIN     = 0,
    GM_LOG_QUERY_ROLE_LOGOUT    = 1,
    GM_LOG_QUERY_ITEM           = 2,
    GM_LOG_QUERY_MONEY          = 3,
    GM_LOG_QUERY_QUEST          = 4,
    GM_LOG_QUERY_GM             = 5,

    GM_QUERY_NUM,
};

enum GM_MODIFY_ROLE_TYPE
{
    //GM_DEL_ROLE_QUEST         = 1,
    //GM_DEL_ROLE_ITEM            = 2,
    //GM_DEL_MAIL             = 3,
};

enum GM_ROLE_TYPE
{
    GM_ROLE_NONE = 0,
    GM_ROLE_BASE_DATA,
    GM_ROLE_TITLE,
    GM_ROLE_SPELL,
    GM_ROLE_ITEM,
    GM_ROLE_QUEST,
    GM_ROLE_MAIL,

    GM_ROLE_TAKE_ITEM,

    GM_RBD_NONE     = 100,
    GM_RBD_ID       = 101,
    GM_RBD_NAME     = 102,
    GM_RBD_GROUPID, 
    GM_RBD_DELETETIME ,
    GM_RBD_CLASS,
    GM_RBD_SEX,
    GM_RBD_LEVEL,
    GM_RBD_EXP,
    GM_RBD_PKVALUE,
    GM_RBD_GMLEVEL,
    GM_RBD_MAP_ID,
    GM_RBD_MAP_SERIAL_ID,
    GM_RBD_X,
    GM_RBD_Y,
    GM_RBD_Z,
    GM_RBD_LAST_LOGIN_TIME,     //
    GM_RBD_LAST_LOGOUT_TIME,    //
    GM_RBD_FORBIDDEND_CHAT_TIME,    
    GM_RBD_FREEZE_ROLE_TIME,    //
    GM_RBD_FREEZE_CHEAT_ROLE,
    GM_RBD_GUILD_ID,            //
    GM_RBD_MONEY_1,
    GM_RBD_MONEY_2,
    GM_RBD_MONEY_3,
    GM_RBD_MONEY_4,
    GM_RBD_MONEY_5,
    GM_RBD_MONEY_6,
    GM_RBD_MONEY_7,
    GM_RBD_MONEY_8,
    GM_RBD_MONEY_9,
    GM_RBD_MONEY_10,
    GM_RBD_MONEY_11,
    GM_RBD_MONEY_12,
    GM_RBD_MONEY_13,
    GM_RBD_MONEY_14,

};

//
struct GM_ROLE_SLOT 
{
    UINT16      wLength;
    UINT16      wRoleType;
    UINT16      wBaseDataType;
    char        szData[0];
};

struct GM_ROLE_SPELL_SLOT 
{
    INT32       nSpellID;
    INT32       nRuneID;
    INT32       nEquipedIndex;
    char        szName[MAX_SPELL_NAME_LEN];
};

struct GM_ROLE_TITLE_SLOT
{
    INT32       nTemplateID;
    UINT32      dwExpireTime;
    char        szName[MAX_TITLE_NAME_LEN];
};

struct GM_ROLE_ITEM_SLOT 
{
    UINT32      dwItemID;
    UINT64      qwGuid;
    UINT16      wConSlot;
    UINT16      wItemSlot;
    INT32       nType;
    INT32       nSubType;
    INT32       nNum;

    UINT8       byBindType;

    //以下属性仅限装备
    //是否已鉴定
    UINT8       byIdentified;
    //随机属性
    UINT16      wRandomAttrID[4];
    //签名
    UINT32      dwRoleID;
    //已消费金币
    UINT32      dwCostMoney;

    //以下属性仅限武器
    //幸运值
    INT8        byLuck;
    //武器升级
    UINT8       byLevelupTimes;
    UINT8       byLevelupPhyPoint;
    UINT8       byLevelupMagPoint;
    UINT8       byLevelupTaoPoint;
    UINT8       byLevelupTypeHidden;
    UINT8       byLevelupPointHidden;
    //铸魂
    UINT16      wRune[6];

    //以下属性仅限防具
    //融灵
    UINT32      dwSocketCombination;
    INT32       nSoulID[3];

    char        szData[0];
};

struct GM_ROLE_MAIL_SLOT 
{
    UINT32      dwMailID;
    INT32       nMailType;
    INT32       nAttachType;
    INT32       nState;
    INT32       nAttachLocked;
    INT32       nItemID;
    INT32       nItemCount;
    char        szData[0];
};

// todo
#define MAX_QUEST_NAME_LENGTH   (61)
#define MAX_ACTION_TYPE_LENGTH  (9)
#define MAX_GAME_LOG_COUNT      (40)

struct GM_LOG_DATA
{
    char            szBuffer[MAX_GM_GAMELOG_LENGTH];
};

struct ITEM_LOG_DATA 
{
    INT32       nLogTime;
    INT8        byGroupID;
    INT8        byAreaID;
    char        szActionType[MAX_ACTION_TYPE_LENGTH];
    UINT32      dwTemplateID;
    UINT64      qwGuid;
    INT8        byCount;
    UINT32      dwSrcRoleID;
    UINT32      dwTargetRoleID;
    char        szReason[31];
};

struct ROLE_LOGINOUT_DATA
{
    INT32       nLogTime;
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
    char        szIP[16];
};

struct QUEST_LOG_DATA 
{
    INT32       nLogTime;
    UINT32      dwRoleID;
    UINT32      dwQuestID;
    char        szActionType[MAX_ACTION_TYPE_LENGTH];
    char        szQuestType[MAX_ACTION_TYPE_LENGTH];
    char        szQuestName[MAX_QUEST_NAME_LENGTH];
};

struct DUNGEON_LOG_DATA 
{
    INT32       nLogTime;
    UINT32      dwSceneID;
    UINT32      dwTemplateID;
    UINT32      dwRoleID;
    char        szType[MAX_ACTION_TYPE_LENGTH];
};

// cmd data

#define MAX_GET_ROLE_LIST_NAME_NUM       (32)       // to be del



// exchange

#define MAX_EXCHANGE_LOG_NUM            (1024)
#define MAX_EXCHANGE_HISTORY_NUM        (768)        // 往前数32天的记录，每小时一条，刚好768
#define MAX_EXCHANGE_BUFFER_SIZE        (0xFFFF)

struct GM_EXCHANGE_PRICE_LOG
{
    UINT8       byGroupID;
    UINT32      dwExchangeTime;
    char        szExchangeTime[21];
    UINT32      dwSellerID;
    UINT32      dwSellerOrderID;
    UINT32      dwBuyerRoleID;
    UINT32      dwBuyerOrderID;
    INT32       nPrice;
    INT32       nCount;
};

struct GM_EXCHANGE_PRICE_HISTORY
{
    UINT8       byGroupID;
    UINT32      dwHistoryTime;
    char        szHistoryTime[21];
    INT32       nOpen;
    INT32       nClose;
    INT32       nHigh;
    INT32       nLow;
    INT32       nVolume;
    INT64       llTotalPrice;
};



#endif //_H_GM_DEF_H_



