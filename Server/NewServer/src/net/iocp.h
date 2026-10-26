#ifndef _IOCP_H_
#define _IOCP_H_

#if defined(WIN32)

#include <WinSock2.h>
#include <MSWSock.h>
#include <list>

#include "net.h"
#include "external_message_header.h"
#include "free_object_pool.h"
#include "base_list.h"

using namespace ExternalMessage;

namespace IOCP
{

//#ifndef	_ROBOT
//	#define SEND_LOOP_BUFFER_SIZE   (64 * 1024)
//	#define RECV_LOOP_BUFFER_SIZE   (16 * 1024)
//#else
//	#define SEND_LOOP_BUFFER_SIZE   (16 * 1024)
//	#define RECV_LOOP_BUFFER_SIZE   (512 * 1024)
//#endif

    enum IO_OPERATION
    {
        ioConnect   = 0x0001,
        ioAccept    = 0x0002,
        ioSend      = 0x0004,
        ioRecv      = 0x0008,
        ioQuit      = 0x0010,
    };

    enum SESSION_STATE
    {
        ssInvalid           = 0,

        ssAccepted          = 0x0001,  // 新接受连接，等待主线程初始化
        ssConnecting        = 0x0002,  // 连接建立中，不能收发数据
        ssNormal            = 0x0004,  // 正常通信状态，完整的数据收发
        ssDisconnecting     = 0x0008,  // 正在断开，只接收剩余数据，不发送新数据
        ssCleanup           = 0x0010,  // 准备销毁，不进行任何I/O操作
        ssDisconnected      = 0x0020,  // 

        ssTotal             = 0xFFFF
    };

    class CSocketSession;
    class CSocketAcceptor;
    class CNet;

    struct IO_DATA : OVERLAPPED
    {
        INT32           nIoOperation;  // 操作类型标识
        WSABUF          wsabuf;        // 数据缓冲区
        CSocketSession* pSession;      // 关联会话
    };

    class CSocketSession : public ISocketSession
    {
    public:
        virtual INT32 Send(PACKET_BUFFER* pPacketBuffer, INT32 nSize, INT32 nOffset);
		virtual INT32 SendNoPackageHead(PACKET_BUFFER* pPacketBuffer, INT32 nSize){return 0;}

        virtual void* GetUserData(void);
        virtual void SetUserData(void* pUserData);

        virtual BOOL GetAddress(UINT32& dwAddr, UINT16& wPort);
        virtual BOOL GetRemoteAddress(UINT32& dwRemoteAddr, UINT16& wRemotePort);

        virtual BOOL Close(void);

    public:
        CSocketSession();
        virtual ~CSocketSession();

        BOOL Init(CNet* pNet, CSocketAcceptor* pSocketAcceptor);
        BOOL UnInit(void);

        inline void* GetAcceptBuffer(void);
        inline SOCKET GetSocket(void);
        inline IO_DATA* GetSendIoData(void);
        inline IO_DATA* GetRecvIoData(void);
        inline IO_DATA* GetCommonIoData(void);
        inline CSocketAcceptor* GetSocketAcceptor(void);

        INT32 Recv(void);
        BOOL CompleteSend(INT32 nIoSize);
        BOOL CompleteRecv(INT32 nIoSize);
        BOOL Shutdown(void);
        BOOL CheckCleanup(void);
        void TrySend(UINT64 qwCurrentTick);

		inline BOOL StartSend(void);
		inline BOOL StopSend(void);
		inline BOOL StartRecv(void);
		inline BOOL StopRecv(void);

        inline SESSION_STATE GetState(void);
        inline void SetState(SESSION_STATE eState);
        inline BASE_LIST_NODE& GetListNode(void);
        inline UINT64 GetShutdownTimer(void);

    private:
        SESSION_STATE       m_eState;
        CSocketAcceptor*    m_pSocketAcceptor;

		char*                m_pSendLoopBuffer;
		char*                m_pRecvLoopBuffer;

        struct LOOP_INDEX
        {
            volatile INT32	Head;
            volatile INT32	Rear;
        };

        LOOP_INDEX          m_SendIndex;
        LOOP_INDEX          m_RecvIndex;
		volatile BOOL		m_bSending;
		volatile BOOL		m_bRecving;

        CNet*               m_pNet;
        IPacketAllocator*   m_pPacketAllocator;

        SOCKET              m_Socket;
        BYTE                m_AcceptBuffer[sizeof(sockaddr_in) * 2 + 16 * 2];
        IO_DATA             m_SendIoData;
        IO_DATA             m_RecvIoData;
        IO_DATA             m_CommonIoData;

        BASE_LIST_NODE      m_ListNode;
        void*               m_pUserData;
        UINT64              m_qwShutdownTimer;
        UINT64              m_qwSendTimer;
    };


    class CSocketAcceptor : public ISocketAcceptor
    {
    public:
        virtual BOOL Open(UINT32 dwAddr, UINT16 wPort);
        virtual BOOL Close(void);
		virtual void* GetUserData(void);
		virtual void SetUserData(void* pUserData);

    public:
        CSocketAcceptor();
        virtual ~CSocketAcceptor();

        BOOL Init(CNet* pNet);
        BOOL UnInit(void);

        inline BOOL OnAccept(BOOL bOperateResult, CSocketSession* pSocketSession);

        BOOL CreateAcceptSocket(void);
        inline SOCKET GetSocket(void);

    private:
        CNet*                           m_pNet;
        volatile SOCKET                 m_sockListen;
        LPFN_ACCEPTEX                   m_fnAcceptEx;

        volatile INT32                  m_nAcceptSocketCount;
        INT32                           m_nThreadCount;

		void*							m_pUserData;
    };

    class CNet : public INet
    {
    public:
        virtual ISocketAcceptor* CreateAcceptor(void);
        virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocketAcceptor);

        virtual ISocketSession* Connect(UINT32 dwAddr, UINT16 wPort);
        virtual BOOL MainLoop(void);

		virtual INT64 PrintMemoryStat(void);

	public:
        CNet();
        virtual ~CNet();

        virtual BOOL Init(IPacketAllocator* pPacketAllocator,  
            INetEventHandler* pNetEventHandler, void* pInitParam);
        virtual BOOL UnInit(void);

        CSocketSession* CreateSession(void);
        void DestroySession(CSocketSession* pSession);

        inline IOCP_INIT_PARAM& GetInitParam(void);
        inline IPacketAllocator* GetPacketAllocator(void);
        inline HANDLE GetIOCPHandle(void);
        inline INetEventHandler* GetEventHandler(void);

        BOOL PushSessionToMainThread(CSocketSession* pSocketSession);

    private:
        static DWORD WINAPI _IocpThreadFunc(void* pParam);

        inline BOOL _OnConnect(BOOL bOperateResult, CSocketSession* pSocketSession);
        inline BOOL _OnSend(BOOL bOperateResult, CSocketSession* pSocketSession, DWORD dwIoSize);
        inline BOOL _OnRecv(BOOL bOperateResult, CSocketSession* pSocketSession, DWORD dwIoSize);

    private:
        IOCP_INIT_PARAM                 m_InitParam;
        IPacketAllocator*               m_pPacketAllocator;
        INetEventHandler*               m_pEventHandler;

        CFreeObjectPool<CSocketSession> m_SessionPool;
        CFreeStack                      m_SessionStack;
        CBaseList                       m_SessionList;

        typedef std::list<CSocketAcceptor*>     ACCEPTOR_LIST;
        ACCEPTOR_LIST                   m_AcceptorList;

        HANDLE                          m_hIOCP;
        HANDLE*                         m_pThreadHandle;
        IO_DATA                         m_QuitIoData;

        LPFN_CONNECTEX                  m_fnConnectEx;
    };

#include "iocp.inl"
}

#endif //WIN32

#endif  // _IOCP_H_
