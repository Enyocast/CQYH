#ifndef _MGATE_SERVER_H_
#define _MGATE_SERVER_H_

#include "server_def.h"
#include "mg_external_message_handler.h"
#include "mg_internal_message_handler.h"
#include "packet_allocator.h"

class INet;
class ISocketAcceptor;
struct CLIENT_SESSION;

class CMGateServer
{
public:
	CMGateServer();
	~CMGateServer();

	static CMGateServer& GetInstance(void);

	BOOL Init(INetEventHandler* poInterMessageHandler, INetEventHandler* poExternalMessageHandler);
	BOOL UnInit(void);

	BOOL MainLoop(void);
	BOOL Close(void);

	INet* GetExternalNet(void)                  { return m_pExternalNet; }
	INet* GetInternalNet(void)                  { return m_pInternalNet; }
	IPacketAllocator* GetPacketAllocator(void)  { return &m_PacketAllocator; }

	UINT32 GetInternalAddr(void)          { return m_dwInternalAddr; }
	UINT32 GetInternalPort(void)          { return m_dwInternalPort; }

	inline INT32 GetExternalAddrCount(void);
	inline UINT32 GetExternalAddr(INT32 nIndex);
	inline UINT32 GetExternalPort(INT32 nIndex);

private:
	static CMGateServer      ms_Instance;

	INet*                   m_pExternalNet;
	INet*                   m_pInternalNet;

	CPacketAllocator        m_PacketAllocator;

	INT32					m_nExternalAddrCount;
	ISocketAcceptor*        m_pClientSocketAcceptor[MAX_EXTERNAL_IP_COUNT];
	UINT32					m_dwExternalAddr[MAX_EXTERNAL_IP_COUNT];
	UINT32                  m_dwExternalPort[MAX_EXTERNAL_IP_COUNT];

	UINT32					m_dwInternalAddr;
	UINT32                  m_dwInternalPort;
};

inline INT32 CMGateServer::GetExternalAddrCount(void)
{
	return m_nExternalAddrCount;
}

inline UINT32 CMGateServer::GetExternalAddr(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nExternalAddrCount);
	return m_dwExternalAddr[nIndex];
Exit0:
	return 0;
}

inline UINT32 CMGateServer::GetExternalPort(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nExternalAddrCount);
	return m_dwExternalPort[nIndex];
Exit0:
	return 0;
}

extern void MGSysLogSuccess(MG_CLIENT_SESSION* pstSession, const char* szFucntionName);
extern void MGSysLogError(MG_CLIENT_SESSION* pstSession, const char* szFucntionName);

#define MG_SYS_LOG_SUCCESS(pstSession) MGSysLogSuccess(pstSession, __FUNCTION__)
#define MG_SYS_LOG_ERROR(pstSession) MGSysLogError(pstSession, __FUNCTION__)

#endif  // _MGATE_SERVER_H_