/********************************************************************
	created:	21:12:2013   12:59
	file:		gm_data.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_DATA_H_
#define _H_GM_DATA_H_


#include "string_def.h"
#include "gm_svr_def.h"
#include "item_def.h"
#include "quest_def.h"
#include <list>
#include "chat_def.h"
#include "money_def.h"
#include "mail_def.h"
#include "gm_def.h"


struct DBSetting
{
    char szServerAddr[DB_SETTING_STRING_LEN];
    char szLoginName[DB_SETTING_STRING_LEN];
    char szPassword[DB_SETTING_STRING_LEN];
    char szDBName[DB_SETTING_STRING_LEN];
    char szCharSet[DB_SETTING_STRING_LEN];
    UINT32 dwServerPort;
};



struct GM_ROLE_BASE_INFO 
{
    UINT32          dwRoleID;
    char            szRoleName[ROLE_NAME_LEN];
    UINT8			byGroup;
    UINT8           byLevel;
    UINT8           bySex;
    UINT8           byClass;
    char            szUserName[USER_NAME_LEN];
};


struct GM_ROLE_RES 
{
    char        szRoleName[ROLE_NAME_LEN];
    INT32       nResult;
};


struct GM_ITEM_DATA 
{
    UINT64      llGuid;
    UINT32      dwTemplateID;
    char        szItemName[MAX_ITEM_NAME_LEN];
    INT32       nConSlot;
    INT32       nItemSlot;
    INT32       nType;
    INT32       nNum;
};

struct GM_QUEST_DATA
{
    UINT32      dwTemplateID;
    char        szQuestName[COMMON_NAME_LEN];
};

struct GM_MAIL_DATA 
{
    UINT32      dwMailID;
    UINT32      dwMailTime;
    UINT8       byMailType;
    UINT8       byIsNew;
    char        szMailSubject[MAIL_SUBJECT_LEN];
    UINT8       byAttachType;
};

struct GM_ROLE_DATA 
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
    INT32	    nClass;
    INT32	    nSex;
    INT32	    nLevel;
    INT64	    llExp;
    INT32       nCurHp;
    INT32       nMaxHp;
    INT32       nPkValue;
    INT32       nPhyAtkHi;
    INT32       nPhyAtkLo;
    INT32       nMagAtkHi;
    INT32       nMagAtkLo;
    INT32       nPhyDef;
    INT32       nMagDef;
    INT32       nMapID;
    INT32       nMapSerialID;
    INT64       llX;
    INT64       llY;
    INT64       llZ;
    INT32       nFaction;
    INT32       nLastLoginTime;
    INT32       nLastLogoutTime;
    INT32       nForbiddenChatTime;
    INT32       nFreezeTime;
    UINT32      dwGuildID;
    INT32       arrMoney[MONEYTYPE_COUNT];

    INT32       nMailCount;
    GM_MAIL_DATA    mailData[MAX_MAIL_COUNT];

    INT32       nItemCount;
    GM_ITEM_DATA    itemData[GM_MAX_ITEM_COUNT];

    INT32       nQuestCount;
    GM_QUEST_DATA   questData[MAX_ACCEPTED_NORMAL_QUEST_COUNT];

};

class CTLUser;
struct CMD_DATA_BASE;
class CRole;
typedef BOOL(*CMD_FUNC)(CTLUser*, CMD_DATA_BASE*);

struct CMD_DATA_BASE
{
    virtual ~CMD_DATA_BASE()    {    }

    UINT32      dwSerialID;
    GM_COMMAND  eCmdType;
    INT32       eCmdState;
    UINT32      dwTLUserID;
    char        szUserName[ROLE_NAME_LEN];
    CMD_FUNC    pfunc;
    INT32       nTimeout;
    INT32       nResult;
    INT32       nGroupID;
};

struct CMD_MAIL_DATA 
{
    UINT32      dwMailID;
    UINT32      dwMailTime;
    UINT8       byMailType;
    UINT8       byIsNew;
    UINT8       byAttachLocked;
    char        szMailSubject[MAIL_SUBJECT_LEN];
    UINT8       byAttachType;
    UINT32      dwAttachBufferLen;
    char        AttachBuffer[BUFFER_ATTACH_LEN];
};

struct CMD_ROLE_DATA_BASE : CMD_DATA_BASE 
{
    CMD_ROLE_DATA_BASE()    
    {
        poRole = NULL;
        memset(szSaveTime, 0, sizeof(szSaveTime));
        memset(szForbidChat, 0, sizeof(szForbidChat));
        memset(szFreezeRole, 0, sizeof(szFreezeRole));
        memset(szFreezeCheatRole, 0, sizeof(szFreezeCheatRole));
        mailList.clear();
    }

    ~CMD_ROLE_DATA_BASE()
    {
        mailList.clear();
    }

    CRole       *poRole;
    char        szSaveTime[21];
    UINT32      dwActualDeleteTime;

    // guild
    UINT32      dwGuildID;

    // forbid
    char        szForbidChat[21];
    char        szFreezeRole[21];
    char        szFreezeCheatRole[21];

    // mail
    INT32       nMailCount;
    typedef std::list<CMD_MAIL_DATA>    CMD_MAIL_LIST;
    CMD_MAIL_LIST   mailList;
};

struct GM_ROLE_KEY 
{
    UINT32      dwRoleID;
    char        szRoleName[ROLE_NAME_LEN];
    char        szUserName[USER_NAME_LEN];
};

struct CMD_PRE_QUERY : CMD_DATA_BASE 
{
    UINT32  dwRoleID;
    char    szRoleName[ROLE_NAME_LEN];
};

struct CMD_QUERY_ROLE_ID : CMD_DATA_BASE 
{
    INT32       nQueryType;
    char        szName[USER_NAME_LEN];
    INT32       nCount;
    GM_ROLE_KEY RoleKey[MAX_GMSVR_ROLE_KEY_NUM];
};

struct CMD_QUERY_ROLE_DATA : CMD_ROLE_DATA_BASE 
{
    char            szRoleName[ROLE_NAME_LEN];
    UINT32          dwRoleID;
    UINT32          dwLogoutTime;
    BOOL            bIsOnline;
    GM_ROLE_DATA    roleData;
    INT32           nLength;
    char            szData[MAX_GM_ROLE_DATA_STR_LENGTH];
};

struct CMD_FORBIDDEN_CHAT : CMD_DATA_BASE 
{
    UINT32          dwRoleID;
    UINT32          dwTime;
};

struct CMD_FREEZE_ROLE : CMD_DATA_BASE 
{
    UINT32          dwRoleID;
    UINT32          dwTime;
};

struct CMD_KICK_ROLE : CMD_DATA_BASE 
{
    UINT32          dwRoleID;
};

struct CMD_ANNOUNCE : CMD_DATA_BASE 
{
    UINT32          dwBeginTime;
    INT32           nRepeatNum;
    INT32           dwIntervalTime;
    char            szText[GM_ANNOUNCE_LENGTH];
};

struct GMCMD_ANNOUNCE_DATA 
{
    INT32       nGroupID;
    UINT32      dwSerial;
    UINT32      dwIntervalTime;
    UINT32      dwRepeatNum;
    char        szText[GM_ANNOUNCE_LENGTH];
};

struct CMD_GET_ANNOUNCE_LIST : CMD_DATA_BASE 
{
    INT32           nCount;
    GMCMD_ANNOUNCE_DATA data[100];
};

struct CMD_DEL_ANNOUNCE : CMD_DATA_BASE 
{
    UINT32          dwAnnounceSerial;
};

struct CMD_SEND_MAIL : CMD_DATA_BASE
{
    UINT32          dwRoleID;
    char            szTitle[MAIL_SUBJECT_LEN];
    char            szContent[MAIL_CONTENT_LEN];
    char            szReason[GM_REASON_LEN];
    UINT32          dwItemID;
    INT32           nItemNum;
    UINT32          dwMailID;
};

#include "mysql.h"
struct CMD_LOG : CMD_DATA_BASE 
{
    INT32           nLogType;
    UINT32          dwBeginTime;
    UINT32          dwEndTime;
    char            szQueryStr[MAX_GM_COMMAND_LEN];
    BOOL            bTruncated;
    INT32           nLength;
    char            szBuffer[MAX_ITEM_BUFFER_SIZE];


    //UINT32          dwRoleID;
    //UINT32          dwItemID;
    //UINT64          qwItemGuid;
    //INT32           nCount;
    //INT32           nLength;
    //INT32           nMaxPackageLength;
    
};

struct CMD_EXE_GM_STR : CMD_DATA_BASE 
{
    char            szGMStr[MAX_GM_COMMAND_LEN];
};

struct CMD_LOAD_ROLE : CMD_ROLE_DATA_BASE
{
    UINT32          dwRoleID;
    GM_ROLE_DATA    roleData;
    INT32           nLength;
    char            szData[MAX_GM_ROLE_DATA_STR_LENGTH];
};

struct GM_LOG_BUFFER 
{
    char    szLog[GM_DATA_LOG_LENGTH];
};

class CRole;
struct CMD_MODIFY_ROLE : CMD_ROLE_DATA_BASE 
{
    CMD_MODIFY_ROLE()
    {
        logList.clear();
    }

    INT32           nType;
    BOOL            bClearTargetRoleCache;
    CRole           *poSelfRole;
    CRole           *poTargetRole;
    UINT32          dwRoleID;
    UINT32          dwTargetRoleID;
    INT32           nSlotCount;
    INT32           nMailCount;
    INT32           nLength;
    char            szData[MAX_GM_ROLE_DATA_STR_LENGTH];
    char            szReason[GM_REASON_LEN];
    INT32           nLogLength;
    char            szLog[MAX_GM_LOG_LENGTH];

    typedef std::list<GM_LOG_BUFFER>     LOG_LIST;
    LOG_LIST        logList;
};

struct CMD_QUERY_NAME_TO_ID : CMD_DATA_BASE 
{
    INT32           nIndex;
    UINT32          dwRoleID;
    char            szRoleName[ROLE_NAME_LEN];
};

struct CMD_ROLE_EXE_GM_CMD : CMD_ROLE_DATA_BASE
{
    UINT32          dwRoleID;
    char            szGM[MAX_GM_COMMAND_LEN];
    char            szReason[GM_REASON_LEN];
};





struct QUERY_SYSTEM_EXCHANGE_INFO : CMD_DATA_BASE 
{
    UINT8           byGroupID;
    UINT8           byFlag;
    UINT32          dwBeginDayTime;
    UINT32          dwEndDayTime;
    UINT32          dwBeginHourTime;
    UINT32          dwEndHourTime;

    INT64           llSysTotalMoney;
    INT64           llTotalMoney;
    INT64           llSysTotalExchangeMoney;
    INT64           llTotalExchangeMoney;
    INT64           llSysExchangeRMB;
    INT64           llExchangeRMB;
    INT32           nAveragePriceToday;
    INT32           nAveragePriceLastHour;
};


#endif //_H_GM_DATA_H_













