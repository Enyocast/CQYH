#ifndef _GAMESERVER_H_
#define _GAMESERVER_H_

#include "net.h"
#include "packet_allocator.h"
#include "imessage_notifier.h"
#include "message_notifier.h"

class CGtSession;

class CGameServer
{
public:
	CGameServer(void);
	~CGameServer(void);

	static CGameServer& GetInstance(void);

    BOOL Init(INetEventHandler* poNetEventHandler);
	BOOL UnInit(void);

    BOOL MainLoop(void);
    BOOL Close(void);
    void SetForceClose(void);

    INet* GetNetInterface(void)                 {return m_poNet;}
    IPacketAllocator* GetPacketAllocator(void)  {return &m_PacketAllocator;}
    IMessageNotifier* GetMessageNotifier(void)  {return &m_MessageNotifier;} 
    UINT64 GetStartTick(void)                   {return m_qwStartTick;}

private:
    struct CKickAllRole
    {
        bool operator()(UINT32 dwRoleID, CRole* poRole);
    };

    BOOL _InitMathTable(void);

private:
	static CGameServer  ms_Instance;

	INet*               m_poNet;
	CPacketAllocator    m_PacketAllocator;
	CMessageNotifier    m_MessageNotifier;

    UINT32              m_dwIndex;
    UINT64              m_qwStartTick;
    BOOL                m_bForceClose;
};

#endif // _gameserver_h__
