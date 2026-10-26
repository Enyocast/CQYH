#include "stdafx.h"
#include "cert_message_handler.h"

#include "math_ex.h"
#include "zlib.h"
#include "cer_message.h"
#include "packet_allocator.h"

CCertMessageHandler CCertMessageHandler::ms_Instance;
CCertMessageHandler g_MessageHandler;

char                g_szMathTableData[1024 * 1024 * 16];
UINT32              g_dwMathTableSize = 0;

using namespace InternalMessage;

void CCertMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    UINT32 dwAddr;
    UINT16 wPort;
    struct in_addr addr;

    LOG_PROCESS_ERROR(pSocketSession);

    pSocketSession->GetRemoteAddress(dwAddr, wPort);
    addr.S_un.S_addr = dwAddr;
    INF("connected from %s:%d", inet_ntoa(addr), wPort);

    CER_SYNC_CERTIFICATION* pMsg = (CER_SYNC_CERTIFICATION*)m_pPacketAllocator->Alloc(sizeof(CER_SYNC_CERTIFICATION) + g_dwMathTableSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = cer_sync_certification;
    pMsg->byKey = 206;
    memcpy(pMsg->szMathTable, &g_szMathTableData, g_dwMathTableSize);

    nRetCode = pSocketSession->Send((PACKET_BUFFER*)pMsg, sizeof(CER_SYNC_CERTIFICATION) + g_dwMathTableSize, 0);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CCertMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
    if (pSocketSession)
        pSocketSession->Close();
}

void CCertMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    if (pSocketSession)
        pSocketSession->Close();
}

void CCertMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{ 
}

CCertMessageHandler::CCertMessageHandler()
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;
}

CCertMessageHandler::~CCertMessageHandler()
{
    UnInit();
}

BOOL CCertMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);

    m_pNet = pNet;
    m_pPacketAllocator = pPacketAllocator;

    g_dwMathTableSize = sizeof(g_szMathTableData);
    nRetCode = compress((Bytef*)g_szMathTableData, (uLongf*)&g_dwMathTableSize, (const Bytef*)&g_MathTable, sizeof(g_MathTable));
    LOG_PROCESS_ERROR(g_dwMathTableSize < MAX_MESSAGE_SIZE);

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CCertMessageHandler::UnInit(void)
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;

    return TRUE;
}

CCertMessageHandler& CCertMessageHandler::GetInstance(void)
{
    return ms_Instance;
}
