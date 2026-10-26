#ifndef _SHARE_MEM_NET_H_
#define _SHARE_MEM_NET_H_

#if defined(WIN32)

#include "net.h"
#include "share_mem_io.h"
#include "object_pool.h"
#include "base_list.h"
#include "time_ex.h"

namespace ShareMem
{
	class CNet;

	enum EConnState
	{
		csDisconnected,
		csConnected,
	};

	struct SessionMemHeader
	{
		UINT32 dwSerial;
		INT32 nConnState;

		UINT64 qwTimeoutTick;
	};

	inline UINT64 GetSysTick(void)
	{
#if (defined(WIN32) || defined(WIN64))
		return GetTickCountEx();
#else
		struct timeval cateq_v;
		struct timezone cateq_z;

		gettimeofday(&cateq_v, &cateq_z);

		return (UINT32)(1000.0 * (double)(cateq_v.tv_sec) + (double)(cateq_v.tv_usec) / 1000.0);

#endif
	}

	class CSocketSession : public ISocketSession
	{
	public:
		CSocketSession(void);
		virtual ~CSocketSession(void);

		virtual INT32 Send(PACKET_BUFFER* pPacketBuffer, INT32 nSize, INT32 nOffset);
		virtual INT32 SendNoPackageHead(PACKET_BUFFER* pPacketBuffer, INT32 nSize){return 0;}


		virtual void* GetUserData(void);
		virtual void SetUserData(void* pUserData);

		virtual BOOL GetAddress(UINT32& dwAddr, UINT16& wPort);
		virtual BOOL GetRemoteAddress(UINT32& dwRemoteAddr, UINT16& wRemotePort);

		virtual BOOL Close(void);
	public:
		BOOL Init(INT32 nPingTimeout);
		BOOL UnInit(void);

		BOOL ReadyToUse(BOOL bIsClient, INT32 nPort, INT32 nSerialNo, INT32 nUploadBuffSize, INT32 nDownloadBuffSize);

		BOOL Recv(char* pPacketBuffer, INT32 nSize);

		BOOL Mainloop(CNet* pNet);

		inline void SetIndex(INT32 nIndex);
		inline INT32 GetIndex(void);
		inline void SetHandlerAndAllocator(INetEventHandler* poHandler, IPacketAllocator* poAllocator);
		inline BOOL IsDisconnected(void);

		inline void SetAddr(UINT32 dwAddr);

	private:
		BOOL m_bReady;
		BOOL m_bDisconnected;
		IPacketAllocator* m_poPacketAllocator;
		INetEventHandler* m_poHandler;
		INT32 m_nSerialNo;
		INT32 m_nIndex;
		void* m_pUserData;
		INT32 m_nSendDataSize;

		PACKET_BUFFER* m_pPackerBuffer;
		UINT16 m_wThisMessageSize;

		CShareMemBuffer m_SendBuf;
		CShareMemBuffer m_RecvBuf;

		UINT32 m_dwAddr;
		// for buffering data from connecting session.
		char m_pMaxSendBuf[MAX_MESSAGE_SIZE];
	};

	inline void CSocketSession::SetIndex(INT32 nIndex)
	{
		m_nIndex = nIndex;
	}

	inline INT32 CSocketSession::GetIndex(void)
	{
		return m_nIndex;
	}

	inline void CSocketSession::SetHandlerAndAllocator(INetEventHandler* poHandler, IPacketAllocator* poAllocator)
	{
		m_bDisconnected = FALSE;
		m_nSendDataSize = 0;
		m_poHandler = poHandler;
		m_poPacketAllocator = poAllocator;
	}

	inline void CSocketSession::SetAddr(UINT32 dwAddr)
	{
		m_dwAddr = dwAddr;
	}

	inline BOOL CSocketSession::IsDisconnected(void)
	{
		return m_bDisconnected;
	}

	enum EAcceptState
	{
		asFree,
		asRequested,
		asAccepted,
	};

	struct AcceptBufHeader
	{
		INT32 nNodeCount;
		BOOL bClosed;
	};

	struct AcceptNode
	{
		INT32 nAcceptState;
		INT32 nSerialNo;
	};

	class CSocketAcceptor : public ISocketAcceptor
	{
	public:
		CSocketAcceptor(void);
		virtual ~CSocketAcceptor(void);

		virtual BOOL Open(UINT32 dwAddr, UINT16 wPort);
		virtual BOOL Close(void);
		virtual void* GetUserData(void);
		virtual void SetUserData(void* pUserData);

	public:
		BOOL Init(CNet* pNet, INT32 nMaxConnCount, INT32 nIndex);
		BOOL Accept(void);

		inline INT32 GetIndex(void);

	private:
		CNet* m_poNet;
		MemPtr m_AcceptBuffer;
		INT32 m_nMaxConnCount;
		INT32 m_nPort;
		INT32 m_nSerialNo;
		INT32 m_nIndex;
		INT32* m_SessionIndex;

		void* m_pUserData;

		UINT32 m_dwAddr;
	};

	inline INT32 CSocketAcceptor::GetIndex(void)
	{
		return m_nIndex;
	}

	struct FREE_NODE : public BASE_LIST_NODE
	{
		INT32 nIndex;
	};

	struct CONNECTOR_NODE : public BASE_LIST_NODE
	{
		MemPtr Ptr;
		INT32 nPort;
		INT32 nAcceptSlot;
		INT32 nSessionSlot;
		//CSocketSession* poSession;
	};

	class CNet : public INet
	{
	public:
		CNet(void);
		virtual ~CNet(void);

		virtual BOOL Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEvent, void* pInitParam);
		virtual BOOL UnInit(void);

		virtual ISocketAcceptor* CreateAcceptor(void);
		virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocket);

		virtual ISocketSession* Connect(UINT32 dwAddr, UINT16 wPort);

		virtual BOOL MainLoop(void);

		virtual INT64 PrintMemoryStat(void);

	public:
		CSocketSession* CreateSession(void);
		BOOL DestroySession(CSocketSession* poSession);

		BOOL CloseSession(INT32 nIndex);

		inline INetEventHandler* GetEventHandler(void);
		inline IPacketAllocator* GetPacketAllocator(void);

		const SHMEM_INIT_PARAM& GetInitParam(void) const { return m_InitParam; }

	private:
		SHMEM_INIT_PARAM m_InitParam;

		IPacketAllocator* m_poPackAllocator;
		INetEventHandler* m_poNetEventHandler;

		CSocketAcceptor** m_pAcceptorSlot;
		CSocketSession** m_pSessionSlot;

		CBaseList m_AcceptorFreeList;
		CBaseList m_SessionFreeList;

		CObjectPool<FREE_NODE> m_AcceptorFreeNodePool;
		CObjectPool<FREE_NODE> m_SessionFreeNodePool;

		CObjectPool<CSocketAcceptor> m_AcceptorPool;
		CObjectPool<CSocketSession> m_SessionPool;

		CBaseList m_ConnectorList;
		CObjectPool<CONNECTOR_NODE> m_ConnectorPool;
	};

	inline INetEventHandler* CNet::GetEventHandler(void)
	{
		return m_poNetEventHandler;
	}

	inline IPacketAllocator* CNet::GetPacketAllocator(void)
	{
		return m_poPackAllocator;
	}
};

#endif //WIN32
#endif // _share_mem_net_h__
