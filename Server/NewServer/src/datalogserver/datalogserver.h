#ifndef _DATALOG_SERVER_H_
#define _DATALOG_SERVER_H_

#include "dl_message_handler.h"
#include "packet_allocator.h"
#include "dl_message_notifier.h"
#include "logdata.h"
#include "sql_mgr.h"
#include "lua_script.h"

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

class CDatalogServer
{
public:
	CDatalogServer();
	~CDatalogServer();

	static CDatalogServer& GetInstance(void);

	BOOL Init(INetEventHandler* poMessageHandler);
	BOOL UnInit(void);

	BOOL MainLoop(void);
	BOOL Close(void);

	INet* GetInternalNet(void)                  {return m_pNet;}
	IPacketAllocator* GetPacketAllocator(void)  {return &m_PacketAllocator;}
	ISocketAcceptor*  GetGSSocketAcceptor(void) {return m_pGSSocketAcceptor;}
	CDLMessageNotifier* GetDLMessageNotifier(void) {return &m_DLMessageNotifier;} 

    inline CSqlMgr& GetSqlMgr(void)     { return m_SqlMgr; }
    inline CLuaScript& GetLuaScript(void)   { return m_LuaScript; }

    std::string GetEnumString(const char *pcszEnumName, INT32 nEnumKeyValue);

private:
    BOOL _InitLogDataBase(void);
    BOOL _InitMathTable(void);

    BOOL _InitScript(void);
    BOOL _UnInitScript(void);

private:
	static CDatalogServer   ms_Instance;

	INet*                   m_pNet;
	ISocketAcceptor*        m_pGSSocketAcceptor;
	CPacketAllocator        m_PacketAllocator;
	CDLMessageNotifier		m_DLMessageNotifier;
    DBSetting               m_dbsetting;

	INT32					m_nGameTime;

    CSqlMgr                 m_SqlMgr;
    CLuaScript              m_LuaScript;
};

#endif  // _DATALOG_SERVER_H_