#ifndef _INET_H_
#define _INET_H_

#define MAX_MESSAGE_SIZE            (0xFFFF)

typedef char PACKET_BUFFER;
class ISocketSession;
class ISocketAcceptor;

class IPacketAllocator
{
public:
    virtual PACKET_BUFFER* Alloc(INT32 nSize) = 0;
//     virtual PACKET_BUFFER* AllocCopy(PACKET_BUFFER* pPacketBuffer) = 0;
    virtual void Free(PACKET_BUFFER* pPacketBuffer) = 0;
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

    virtual void* GetUserData(void) = 0;
    virtual void SetUserData(void* pUserData) = 0;

	virtual BOOL GetAddress(UINT32& dwAddr, UINT16& wPort) = 0;
	virtual BOOL GetRemoteAddress(UINT32& dwRemoteAddr, UINT16& wRemotePort) = 0;

    virtual BOOL Close(void) = 0;
};

class ISocketAcceptor
{
public:
    virtual BOOL Open(const char* pcszIPAddress, UINT16 wPort) = 0;
    virtual BOOL Close(void) = 0;
};

class INet
{
public:
	virtual BOOL Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam) = 0;
	virtual BOOL UnInit(void) = 0;

	virtual ISocketAcceptor* CreateAcceptor(void) = 0;
	virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocket) = 0;

    virtual ISocketSession* Connect(const char* pcszIPAddress, UINT16 wPort) = 0;
    virtual BOOL MainLoop(void) = 0;
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

#endif  // _INET_H_
