/********************************************************************
	created:	20:11:2013   13:23
	file:		gmserver.h
	author:		Allan Tao
	
	purpose:	gm server
*********************************************************************/

#ifndef _H_GM_SERVER_H_
#define _H_GM_SERVER_H_


#include "net.h"
#include "packet_allocator.h"
#include "imessage_notifier.h"
#include "gm_query_thread.h"
#include "message_notifier.h"
#include "gm_data.h"
#include "lua_script.h"


class CGmServer
{
public:
    CGmServer();
    ~CGmServer();

    static CGmServer &GetInstance();

    BOOL Init(INetEventHandler *poNetEventHandler);
    BOOL UnInit();

    const char *GetErrString(INT32 nErr);
    const char *GetEnumString(const char *pcszEnumName, INT32 nEnumKeyValue);

    BOOL MainLoop();
    BOOL Close();

    CLuaScript *GetLuaScript()      { return &m_LuaScript; }
    
    INet *GetNetInterface()                     { return m_poNet; }
    IPacketAllocator *GetPacketAllocator()      { return &m_PacketAllocator; }
    ISocketAcceptor  *GetMSSocketAcceptor()     { return m_pMSSocketAcceptor; }
    ISocketAcceptor  *GetTLSocketAcceptor()     { return m_pTLSocketAcceptor; }
    CMessageNotifier *GetNotifier()               { return &m_Notifier; }

    CGMQueryThread&     GetDBThread()           { return m_DBThread; }

protected:
    BOOL _InitMathTable(void);

private:

    static  CGmServer   ms_Instance;

    INet                *m_poNet;
    CPacketAllocator    m_PacketAllocator;
    CMessageNotifier    m_Notifier;
    ISocketAcceptor     *m_pTLSocketAcceptor;
    ISocketAcceptor     *m_pMSSocketAcceptor;

    UINT32              m_dwCurrentTime;
    UINT64              m_qwCurrentTick;
    UINT64              m_qwStartTick;
    UINT64              m_qwGameFrame;

    CGMQueryThread      m_DBThread;  

    CLuaScript          m_LuaScript;
};






#endif //_H_GM_SERVER_H_



