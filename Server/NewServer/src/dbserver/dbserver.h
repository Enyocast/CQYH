#ifndef _DB_SERVER_H_
#define _DB_SERVER_H_

#include "db_message_handler.h"
#include "packet_allocator.h"
#include "logic/mem_mgr.h"
#include "logic/db_worker_thread.h"
#include "logic/dbrole_mgr.h"
#include "logic/dbuser_mgr.h"

class INet;
class ISocketAcceptor;

struct DBSetting
{
    char szServerAddr[DB_SETTING_STRING_LEN];
    char szLoginName[DB_SETTING_STRING_LEN];
    char szPassword[DB_SETTING_STRING_LEN];
    char szDBName[DB_SETTING_STRING_LEN];
    char szCharSet[DB_SETTING_STRING_LEN];
    UINT32 dwServerPort;
};

class CDBServer
{
public:
    CDBServer();
    ~CDBServer();

    static CDBServer& GetInstance()
    {
        return ms_Instance;
    }

    BOOL Init(INetEventHandler* poNetEventHandler);
    BOOL UnInit(void);

    BOOL InitDataBaseAndWorkerThread(const char* serveraddr,
        const char* loginname,
        const char* password,
        const char* dbname,
        const char* charset,
        UINT32 serverport);

    BOOL MainLoop(void);
    BOOL Close(void);

    const DBSetting* GetDBSetting() { return &m_dbsetting; }

    CMemMgr                 m_memmgr;
    CDBRoleMgr              m_rolemgr;
    CDBUserMgr              m_usermgr;
    UINT32                  m_dwThreadCount;
    CDBWorkerThread*        m_threads;
    DBSetting               m_dbsetting;
    INT32                   m_nOnlineUserCount;

    INet*                   m_pNet;
    ISocketAcceptor*        m_pSocketAcceptor;
    CPacketAllocator        m_PacketAllocator;
    BOOL                    m_bForceClose;

private:
    static CDBServer        ms_Instance;
};

extern void DBSysLogSuccess(CDBUser* poDBuser, const char* szFucntionName);
extern void DBSysLogError(CDBUser* poDBuser, const char* szFucntionName);

#define DB_SYS_LOG_SUCCESS(poDBuser) DBSysLogSuccess(poDBuser, __FUNCTION__)
#define DB_SYS_LOG_ERROR(poDBuser) DBSysLogError(poDBuser, __FUNCTION__)

#endif  // _DB_SERVER_H_
