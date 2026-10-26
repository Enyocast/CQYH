#ifndef _INTRANET_H_
#define _INTRANET_H_

#include "net.h"
#include "object_pool.h"

namespace Intranet
{

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
		inline void Init(ISocketAcceptor* poShareMemAcceptor, ISocketAcceptor* poSimpleNetAcceptor);

		inline ISocketAcceptor* GetShareMemAcceptor(void);
		inline ISocketAcceptor* GetSimpleNetAcceptor(void);

	private:
		ISocketAcceptor* m_poShareMemAcceptor;
		ISocketAcceptor* m_poSimpleNetAcceptor;
		void* m_pUserData;
	};

	inline void CSocketAcceptor::Init(ISocketAcceptor* poShareMemAcceptor, ISocketAcceptor* poSimpleNetAcceptor)
	{
		m_poShareMemAcceptor = poShareMemAcceptor;
		m_poSimpleNetAcceptor = poSimpleNetAcceptor;

		m_poShareMemAcceptor->SetUserData(this);
		m_poSimpleNetAcceptor->SetUserData(this);
	}

	inline ISocketAcceptor* CSocketAcceptor::GetShareMemAcceptor(void)
	{
		return m_poShareMemAcceptor;
	}

	inline ISocketAcceptor* CSocketAcceptor::GetSimpleNetAcceptor(void)
	{
		return m_poSimpleNetAcceptor;
	}

	class CIntranetEventHandler : public INetEventHandler
	{
	public:
		CIntranetEventHandler(void);
		virtual ~CIntranetEventHandler(void);

		virtual void OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession);
		virtual void OnConnected(ISocketSession* pSocketSession);
		virtual void OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize);
		virtual void OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown);

		void Init(INetEventHandler* pUserHandler);

	private:
		INetEventHandler* m_pUserEventHandler;
	};

	class CNet : public INet
	{
	public:
		CNet(void);
		virtual ~CNet(void);

		virtual BOOL Init(IPacketAllocator* pPacketAllocator, INetEventHandler* pNetEventHandler, void* pInitParam);
		virtual BOOL UnInit(void);

		virtual ISocketAcceptor* CreateAcceptor(void);
		virtual BOOL DestroyAcceptor(ISocketAcceptor* pSocket);

		virtual ISocketSession* Connect(UINT32 dwAddr, UINT16 wPort);

		virtual BOOL MainLoop(void);

		virtual INT64 PrintMemoryStat(void);

	private:
		INet* m_poShareMemNet;
		INet* m_poSimpleNet;
		CIntranetEventHandler m_Handler;

		CObjectPool<CSocketAcceptor> m_AcceptorPool;
	};
};

#endif // _intranet_h__
