/********************************************************************
	created:	12:8:2013   10:14
	file:		gm_manager.h
	author:		Allan Tao
	
	purpose:	lock user name 管理类
*********************************************************************/

#ifndef _H_GM_MANAGER_H_
#define _H_GM_MANAGER_H_

#include "string_def.h"
#include "./timer/time_trigger.h"
#include "gm_def.h"


struct GM_ANNOUNCE_TRIGGER : BASE_TRIGGER_NODE
{
    INT32       nGroupID;
    UINT32      dwSerial;
    INT32       nIntervalTime;
    INT32       nRepeatNum;
    char        szText[GM_ANNOUNCE_LENGTH];
};

struct GM_ANNOUNCE_DATA 
{
    UINT32                  dwSerial;
    GM_ANNOUNCE_TRIGGER     *pTrigger;
};

class CGMManager
{
protected:
    CGMManager();
    ~CGMManager();

public:
    static CGMManager       m_Instance;
    static CGMManager &GetInstance();

    BOOL    Init();
    BOOL    UnInit();

public:
    BOOL    AddLockUser(UINT32 dwTLUserID, const char *pcszName);
    BOOL    DelLockUser(const char *pcszName);
    // true is locked,
    BOOL    IsUserLocked(const char *pcszName);
    UINT32  GetTLUserID(const char *pcszName);


    UINT32  GetGMSerialID()         { return dwGMSerialID++; }

    void            BeginAnnounce();
    GM_ANNOUNCE_DATA    *NextAnnounce();

    BOOL    AddAnnounce(INT32 nGroupID, UINT32 dwBeginTime, INT32 nRepeatNum, INT32 nIntervalTime, const char *pcszText);
    BOOL    DelAnnounceTrigger(INT32 nGroupID, UINT32 dwSerialID);
    BOOL    DelAnnounceRecord(INT32 nGroupID, UINT32 dwSerialID);

private:
#define MAX_LOCK_ROLE (128)

    UINT32  dwGMSerialID;



    struct GM_LOCK_ROLE_DATA 
    {
        BOOL    bIsBlank;
        UINT32  dwTLUserID;
        char    szUserName[USER_NAME_LEN];
    };
    GM_LOCK_ROLE_DATA   m_listLockData[MAX_LOCK_ROLE];

    typedef     std::map<UINT32, GM_ANNOUNCE_DATA>  ANNOUNCE_MAP;
    ANNOUNCE_MAP    m_AnnounceMap;
    ANNOUNCE_MAP::iterator  m_AnnounceMapCursor;
};


INT32 CB_BroadcastGMAnnounce(BASE_TRIGGER_NODE *pTriggerNode);

BOOL g_GM_CheckRoleName(CHAR* RoleName);



#endif //_H_GM_MANAGER_H_



