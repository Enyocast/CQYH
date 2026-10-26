#ifndef _INET_H_
#define _INET_H_

#define MAX_ADAPTER_COUNT           (32)
#define MAX_MESSAGE_SIZE            (0xFFFF)
#define LARGE_PACKET_SIZE			(64 * 1024)
#define SMALL_PACKET_SIZE			(1024)
#define PACKET_OVERHEAD_SIZE		(256)

static const char* g_szLocalAddress = "127.0.0.1";

typedef char PACKET_BUFFER;
class ISocketSession;
class ISocketAcceptor;

class IPacketAllocator
{
public:
    virtual PACKET_BUFFER* Alloc(INT32 nSize) = 0;
    virtual void Free(PACKET_BUFFER* pPacketBuffer) = 0;
    virtual BOOL IsAllocated(PACKET_BUFFER* pPacketBuffer) = 0;
	virtual UINT32 PrintMemoryStat(void) = 0;
	virtual void CheckError(void) = 0;
};

class INetEventHandler
{
public:
    virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession) = 0;
    virtual void OnConnected(ISocketSession* pSocketSession) = 0;
    virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize) = 0;
    virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown) = 0;
};

class ISocketSession
{
public:
    virtual INT32 Send(PACKET_BUFFER* pPacketBuffer, INT32 nSize, INT32 nOffset) = 0;
	virtual INT32 SendNoPackageHead(PACKET_BUFFER* pPacketBuffer, INT32 nSize) = 0;

    virtual void* GetUserData(void) = 0;
    virtual void SetUserData(void* pUserData) = 0;

    virtual BOOL GetAddress(UINT32& dwAddr, UINT16& wPort) = 0;
    virtual BOOL GetRemoteAddress(UINT32& dwRemoteAddr, UINT16& wRemotePort) = 0;

    virtual BOOL Close(void) = 0;
};

class ISocketAcceptor
{
public:
    virtual BOOL Open(UINT32 dwAddr, UINT16 wPort) = 0;
    virtual BOOL Close(void) = 0;
    virtual void* GetUserData(void) = 0;
    virtual void SetUserData(void* pUserData) = 0;
};

class INet
{
public:
	virtual BOOL Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam) = 0;
	virtual BOOL UnInit(void) = 0;

	virtual ISocketAcceptor* CreateAcceptor(void) = 0;
	virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocket) = 0;

    virtual ISocketSession* Connect(UINT32 dwAddr, UINT16 wPort) = 0;
    virtual BOOL MainLoop(void) = 0;

	virtual INT64 PrintMemoryStat(void) = 0;
};

enum NET_TYPE
{
    netInvalid,

    netSimple,
    netShareMemory,
    netEpoll,
    netIocp,
	netIntranet,

    netTotal
};

struct IOCP_INIT_PARAM
{
    INT32   nMaxSessionCount;
    INT32   nThreadCount;

	INT32	nMaxOperationPerLoop;
	INT32	nSendLoopBufferSize;
	INT32	nRecvLoopBufferSize;

    INT32*  pnMessageSizeList;
};

struct SIMPLE_INIT_PARAM
{
    INT32 nMaxAcceptor;
    INT32 nMaxConnector;
	INT32 nMaxSessionCount;
	INT32 nSendBufSize;
	INT32 nRecvBufSize;
	INT32 nPacketBufferSize;
};

struct EPOLL_INIT_PARAM
{
    INT32 nMaxAcceptor;
    INT32 nMaxConnector;
    INT32 nMaxSessionCount;
    INT32 nSendBufSize;
    INT32 nRecvBufSize;
    INT32 nPacketBufferSize;
    INT32*  pnMessageSizeList;
};

struct SHMEM_INIT_PARAM
{
    INT32 nMaxAcceptor;
    INT32 nMaxConnector;
	INT32 nMaxSessionCount;
	INT32 nSendBufSize;
	INT32 nRecvBufSize;
	INT32 nPacketBufferSize;
	INT32 nDisconnectTimeout;
};

struct INTRANET_INIT_PARAM
{
    INT32 nMaxAcceptor;
    INT32 nMaxConnector;
	INT32 nMaxSessionCount;
	INT32 nSendBufSize;
	INT32 nRecvBufSize;
	INT32 nPacketBufferSize;
	INT32 nDisconnectTimeout;
};
INet* g_CreateNetInterface(INT32 eNetType, IPacketAllocator* pPacketAllocator, 
                           INetEventHandler* pNetEventHandler, void* pInitParam);
BOOL g_DestroyNetInterface(INT32 eNetType, INet* pNet);

UINT32 GetIp(const char* pcszIntranetAddr, const char* pcszIntranetMask, BOOL bIntranet, INT32 nIndex);


// for struct in_addr
#if defined(WIN32)
    #include "winsock2.h"
#elif defined(__linux__)       
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif 

#endif  // _INET_H_
