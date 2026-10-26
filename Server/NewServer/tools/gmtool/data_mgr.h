/********************************************************************
	created:	19:2:2014   10:38
	file:		data_mgr.h
	author:		Allan Tao
	
	purpose:	role data and so on.
*********************************************************************/


#ifndef _H_DATA_MGR_H_
#define _H_DATA_MGR_H_

#include "string_def.h"
#include "id_object_pool.h"
#include "item_def.h"
#include "quest_def.h"
#include "mail_def.h"
#include "money_def.h"
#include "server_def.h"
#include "gm_def.h"


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
    INT32       nLength;
    char        szData[MAX_GM_ROLE_DATA_STR_LENGTH];
};


struct ITEM_TEMPLATE_DATA
{
    UINT32      dwTempID;
    char        szName[MAX_ITEM_NAME_LEN];
};


struct TL_ANNOUNCE_DATA
{
    INT32       nGroupID;
    INT32       nSvrID;
    UINT32      dwSerial;
    UINT32      dwIntervalTime;
    UINT32      dwRepeatNum;
    char        szText[GM_ANNOUNCE_LENGTH];
};

struct TL_ANNOUNCE_LIST
{
    INT32       nCount;
    TL_ANNOUNCE_DATA    data[100];
};



class CDataMgr
{
protected:
    static CDataMgr     m_Instance;

    CDataMgr();
    ~CDataMgr();

public:
    static CDataMgr&       GetInstance();

    BOOL Init();
    BOOL UnInit();

    // role data
    GM_ROLE_DATA*   NewRole(UINT32 dwRoleID);
    BOOL            DeleteRole(GM_ROLE_DATA*);
    BOOL            ClearRole();
    GM_ROLE_DATA*   FindRole(UINT32 dwRoleID);

    // item template
    void        ClearItemMap(UINT32 dwSessionID);
    BOOL        AddItem(UINT32 dwSessionID, UINT32 dwItemID, const char *pcszName);
    void        ItemMapBegin(UINT32 dwSessionID);
    ITEM_TEMPLATE_DATA  *ItemMapNext(UINT32 dwSessionID);

    // announce
    TL_ANNOUNCE_LIST &GetAnnounceList()     { return m_AnnounceList; }
    void        ClearAnnounceList()         { memset(&m_AnnounceList, 0, sizeof(m_AnnounceList)); }
    BOOL        DelAnnounceFromList(UINT32 dwAnnounceSerial);

private:
    // role data
    CIDObjectPool<GM_ROLE_DATA, UINT32>       m_RolePool;



    // item template
    typedef     std::map<UINT32, ITEM_TEMPLATE_DATA>    ITEM_MAP;
    ITEM_MAP    m_ItemMap[MAX_GM_SESSION_COUNT];
    ITEM_MAP::iterator  m_ItemMap_Cursor[MAX_GM_SESSION_COUNT];

    // announce 
    TL_ANNOUNCE_LIST        m_AnnounceList;

};














#endif //_H_DATA_MGR_H_






