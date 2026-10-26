/********************************************************************
	created:	7:4:2013   15:23
	file:		ms_guild_mgr.h
	author:		Allan Tao
	
	purpose:	∞Ôª·œ‡πÿ¬ﬂº≠£¨∞Ô≈…listº∞≈≈–Ú≤È—Ø¬ﬂº≠
*********************************************************************/

#ifndef _H_MS_GUILD_MGR_H_
#define _H_MS_GUILD_MGR_H_

#include "ms_guild.h"
#include "id_object_pool.h"
#include <map>
#include "object_pool.h"
#include "../gameworld/item.h"

#define GUILD_NAME_HASH_TABLE_SIZE (1024*64)
#define GUILD_BUFFER_SIZE (65535)

struct MS_ONLINE_ROLE_DATA;
struct ItemInfo;
struct APP_NODE;

class CMsGuildMgr
{  
public:
    CMsGuildMgr();
    ~CMsGuildMgr();

public:
    static CMsGuildMgr &GetInstance();
private:
    static CMsGuildMgr  ms_Instance_;

public: // sync
    BOOL SyncAllGuildDataToGS(UINT32 dwGSSessionID);
    BOOL SyncGuildDataToClient(MS_ONLINE_ROLE_DATA* pstOnlineRole, UINT32 dwGuildID);

public:
    BOOL    Init();
    BOOL    Uninit();

	BOOL    LoadGuild(GUILD_DB& db_data);

    BOOL    MainLoop();

    // create first step
    INT32	PreCreateGuild(UINT32 dwNewGuildID, MS_ONLINE_ROLE_DATA &onlineRoleData, const char *pcszGuildName, const char *pcszAnnounce, INT32 nIsNeedToConsume);
    // create second step
    INT32   CreateGuild(MS_ONLINE_ROLE_DATA &onlineRoleData, const char *pcszGuildName);
    BOOL    DestroyGuild(CMsGuild *pMsGuild);

    CMsGuild * FindGuildByID(UINT32 dwGuildID);
    CMsGuild * FindGuildByName(const char *pcszGuildName);

    BOOL    InsertGuildIntoLvlRank(CMsGuild *pMsGuild);
    BOOL    RemoveGuildFromLvlRank(CMsGuild *pMsGuild);

    // diplomat
    BOOL    DelAlliance(INT32 dwGuildID, INT32 dwAllianceID);
    BOOL    DelEnemy(INT32 dwGuildID, INT32 dwEnemyID);

    //////////////////////////////////////////////////////////////////////////
    // ºŸ∂®time…˝–ÚÕ˘∫Û≤Â
    BOOL    AddWarData(INT32 nGroupID, UINT32 dwIntruderID, UINT32 dwDefenderID, UINT32 dwTime);
    BOOL    DeclareWar(INT32 nGroupID, UINT32 dwIntruderID, UINT32 dwDefenderID);

    BOOL    WarBegin();
    BOOL    WarEnd(UINT32 dwDefenderID, INT32 nWarDefenderResult);

    BOOL    IsWarToday(UINT32 dwDefender);
    BOOL    IsWarRelation(UINT32 dwGuildID1, UINT32 dwGuildID2);
    BOOL    ClearWarData();
    BOOL    ClearOldWarData();

    MS_GUILD_WAR_DATA   *FirstWarData();
    MS_GUILD_WAR_DATA   *NextWarData();

    //////////////////////////////////////////////////////////////////////////

    // iterator
    CMsGuild *GetFirstGuildOnLvlRank();
    CMsGuild *GetNextGuildOnLvlRank(CMsGuild *pMsGuild);
    CMsGuild *GetPrevGuildOnLvlRank(CMsGuild *pMsGuild);

    // memory allocate
    APP_NODE *CreateGuildApp();
    BOOL    DeleteGuildApp(APP_NODE *pNode);
    DIPLOMAT_APP_NODE *CreateDiplomatApp();
    BOOL    DeleteDiplomatApp(DIPLOMAT_APP_NODE *pNode);

    EVENT_DATA *CreateEventData();
    BOOL    DeleteEventData(EVENT_DATA *pData);

    STORAGE_EVENT_DATA *CreateStorageEventData();
    BOOL    DeleteStorageEventData(STORAGE_EVENT_DATA *pData);

    GUILD_UPGRADE_TRIGGER *CreateUpgradeTriggerData();
    BOOL    DeleteUpgradeTriggerData(GUILD_UPGRADE_TRIGGER *pData);

    G_B_REVIVE_TRIGGER *NewBGReviveTrigger();
    BOOL    DeleteBGReviveTrigger(G_B_REVIVE_TRIGGER *pTrigger);

    // guild match war
    UINT32  MatchGuild(CMsGuild *poThis);
    BOOL    InsertGuildIntoLadder(CMsGuild *poMsGuild);
    BOOL    RemoveGuildFromLadder(CMsGuild *poMsGuild);
    BOOL    AjustGuild(CMsGuild *poMSGuild);

protected:
    MS_GUILD_WAR_DATA *CreateWarTriggerData();
    BOOL    DeleteWarTriggerData(MS_GUILD_WAR_DATA* pData);

protected:
    BOOL    _AfterLoadGuild();

    BOOL    _SqlInsertGuild(CMsGuild *poMsGuild);

    inline UINT16 _GetHashValue(GUILD_NAME_KEY& rRoleNameKey);

    struct CDeleteAllGuild
    {
        bool operator() (UINT32 dwGuildID, CMsGuild* pMsGuild);
    };

    BOOL _SortLadder();

    BOOL _Stat();
protected:



private:
    CIDObjectPool<CMsGuild, UINT32>     m_GuildPool;
    LM_MAP_NODE<GUILD_NAME_KEY>*         m_pRoot[GUILD_NAME_HASH_TABLE_SIZE];

    CBaseList   m_GuildLvlRank;
    CBaseList   m_Ladder;

    //////////////////////////////////////////////////////////////////////////
    CBaseList   m_WarList;
    BASE_LIST_NODE  *m_pWarListCursor;
    //////////////////////////////////////////////////////////////////////////



    CObjectPool<APP_NODE>   m_GuildAppPool;
    CObjectPool<DIPLOMAT_APP_NODE>  m_DiplomatAppPool;
    CObjectPool<EVENT_DATA>   m_GuildEventDataPool;
    CObjectPool<GUILD_UPGRADE_TRIGGER>    m_UpgradeTriggerPool;
    CObjectPool<STORAGE_EVENT_DATA>    m_StorageEventPool;
    CObjectPool<MS_GUILD_WAR_DATA>  m_GuildWarPool;
    CObjectPool<G_B_REVIVE_TRIGGER>     m_GBRevivePool;

    struct SYNC_GS_GUILD_DATA
    {
        UINT32      dwGSSessionID;
        UINT32      dwGuildID;
    };
    typedef std::list<SYNC_GS_GUILD_DATA>   GS_SYNC_LIST;
    GS_SYNC_LIST        m_GSSyncList;
};

BOOL LoadGuild(std::list<void*>& rResult, void* pUserData);
BOOL LoadGMember(std::list<void*>& rResult, void* pUserData);
BOOL LoadGuildWar(std::list<void*>& rResult, void* pUserData);


INT32 CB_GuildWarBegin(BASE_TRIGGER_NODE *pNode);
BOOL GuildWarEnd(UINT32 dwDefenderID, INT32 nWarDefenderResult);
BOOL GuildSyncWarRelation(UINT32 dwIntruderID, UINT32 dwDefenderID);
BOOL GuildSyncResChange(UINT32 dwNpcID, UINT32 dwGuildID, BOOL bAdd, INT32 nResType, INT32 nChangeCount, INT32 nCtxType);

#endif //_H_MS_GUILD_MGR_H_
























