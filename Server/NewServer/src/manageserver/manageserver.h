#ifndef _MANAGER_SERVER_H_
#define _MANAGER_SERVER_H_

#include <list>

#include "server_def.h"
#include "packet_allocator.h"
#include "db/ms_worker_thread.h"
#include "message_handler.h"
#include "time_ex.h"
#include "sql_mgr.h"

class INet;
class ISocketAcceptor;
struct TRIE_NODE;

struct DBSetting
{
    char szServerAddr[DB_SETTING_STRING_LEN];
    char szLoginName[DB_SETTING_STRING_LEN];
    char szPassword[DB_SETTING_STRING_LEN];
    char szDBName[DB_SETTING_STRING_LEN];
    char szCharSet[DB_SETTING_STRING_LEN];
    //char szDBNameLogData[DB_SETTING_STRING_LEN];
    UINT32 dwServerPort;
};

class CManageServer
{
public:
    CManageServer();
    ~CManageServer();

    static CManageServer& GetInstance(void);

    BOOL Init(INetEventHandler* poNetEventHandler);
    BOOL UnInit(void);
    BOOL Open(void);

    BOOL Close();
    BOOL MainLoop(void);
    VOID SetForceClose()                            {m_bForceClose = TRUE;}
	BOOL Reload(const char* pcszModule);

    const char* GetString( UINT32 dwID );
	inline UINT32 GetGameTime(void) { return m_dwCurrentTime; }
	inline UINT64 GetGameFrame(void) { return m_qwGameFrame; }
	inline UINT64 GetGameTick(void) { return m_qwCurrentTick; }
	inline UINT64 GetStartTick(void) { return m_qwStartTick; }
	inline const tm_ex* GetLocalTime(void) { return &m_LocalTime; }
	inline INT32 GetTimeZone(void) { return m_nTimeZone; }

    inline CSqlMgr& GetSqlMgr(void)     { return m_SqlMgr; }

	INet* GetNetInterface(void)                     { return m_pNet; }
	IPacketAllocator* GetPacketAllocator(void)      { return &m_PacketAllocator; }
	ISocketAcceptor* GetGTSocketAcceptor(void)      { return m_pGTSocketAcceptor; }
	ISocketAcceptor* GetGSSocketAcceptor(void)      { return m_pGSSocketAcceptor; }
	ISocketAcceptor* GetLSSocketAcceptor(void)      { return m_pLSSocketAcceptor; }
	ISocketAcceptor* GetDBSocketAcceptor(void)      { return m_pDBSocketAcceptor; }
	ISocketAcceptor* GetBSSocketAcceptor(void)		{ return m_pBSSocketAcceptor; }
	ISocketAcceptor* GetDLSocketAcceptor(void)		{ return m_pDLSocketAcceptor; }
	ISocketAcceptor* GetMMSocketAcceptor(void)		{ return m_pMMSocketAcceptor; }
	ISocketAcceptor* GetMonitorForRoleNumberAcceptor(void)		{ return m_pMonitorForRoleNumberAcceptor; }
    
    const DBSetting* GetDBSetting() { return &m_dbsetting; }

	BOOL CheckCensoredWord(const char* pcszText);
	BOOL ReplaceCensoredWord(char* pszText);

	inline UINT32 GetSabacGuildID(INT32 nServerGroupID);
	inline void SetSabacGuildID(INT32 nServerGroupID, UINT32 dwGuildID);

private:
    BOOL _RegisterGroupInfo(void);
    BOOL _UnRegisterGroupInfo(void);
	static BOOL _SelectGroup(std::list<void*>& rResult, void* pUserData);

    BOOL _InitDataBase(void);
    BOOL _InitMathTable(void);

    BOOL _MainLoop(void);
    void _On1SecMainLoop(void);
    void _On1MinMainLoop(void);
	void _OnDailyMainLoop(void);

private:
    static CManageServer    ms_Instance;

    INet*                   m_pNet;
    ISocketAcceptor*        m_pGTSocketAcceptor;
    ISocketAcceptor*        m_pGSSocketAcceptor;
    ISocketAcceptor*        m_pLSSocketAcceptor;
    ISocketAcceptor*        m_pDBSocketAcceptor;
	ISocketAcceptor*		m_pBSSocketAcceptor;
	ISocketAcceptor*		m_pDLSocketAcceptor;
	ISocketAcceptor*		m_pMMSocketAcceptor;
	ISocketAcceptor*		m_pMonitorForRoleNumberAcceptor;

    CPacketAllocator        m_PacketAllocator;

    BOOL                    m_bForceClose;
    UINT32                  m_dwCurrentTime;
    UINT64                  m_qwCurrentTick;
	UINT32					m_dwNextDailyTime;

    UINT64                  m_qwStartTick;
    UINT64                  m_qwGameFrame;
	tm_ex					m_LocalTime;
	INT32					m_nTimeZone;

    CSqlMgr                 m_SqlMgr;
	TRIE_NODE*				m_pTrieRoot;
	BOOL					m_bUpdateLastRank;
	INT32					m_nUpdateLastRankServerGroup;
	INT32					m_nUpdateLastRankType;

	static UINT32			ms_dwDBGroup;

	UINT32					m_dwSabacGuildID[MAX_SERVER_GROUP_COUNT];

public:
    UINT32                  m_dwThreadCount;
    DBSetting               m_dbsetting;
};

inline UINT32 CManageServer::GetSabacGuildID(INT32 nServerGroupID)
{
	LOG_PROCESS_ERROR(nServerGroupID >= 0 && nServerGroupID < MAX_SERVER_GROUP_COUNT);
	return m_dwSabacGuildID[nServerGroupID];
Exit0:
	return 0;
}

inline void CManageServer::SetSabacGuildID(INT32 nServerGroupID, UINT32 dwGuildID)
{
	LOG_PROCESS_ERROR(nServerGroupID >= 0 && nServerGroupID < MAX_SERVER_GROUP_COUNT);
	m_dwSabacGuildID[nServerGroupID] = dwGuildID;
Exit0:
	return;
}

extern void MSSysLogSuccess(MS_USER* poUser, const char* szFucntionName);
extern void MSSysLogError(MS_USER* poUser, const char* szFucntionName);

#define MS_SYS_LOG_SUCCESS(poUser) MSSysLogSuccess(poUser, __FUNCTION__)
#define MS_SYS_LOG_ERROR(poUser) MSSysLogError(poUser, __FUNCTION__)

#endif  // _GATE_SERVER_H_