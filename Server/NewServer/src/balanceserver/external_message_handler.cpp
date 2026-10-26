#include "stdafx.h"
#include "external_message_handler.h"
#include "b2c_message.h"

#include "server_config.h"
#include "net.h"

CBSExternalMessageHandler CBSExternalMessageHandler::ms_Instance;

INT32 _GetMatchCount(UINT32 dwA, UINT32 dwB)
{
	INT32 nResult = 0;

	for (INT32 i = 0; i < 32; i++)
	{
		if ((dwA & 1) == (dwB & 1))
		{
			nResult++;
			dwA >>= 1;
			dwB >>= 1;
		}
		else
		{
			break;
		}
	}
	return nResult;
}

BOOL _GetProperAddress(UINT32 dwLocalAddr, const SGTInfo* pGTInfo, UINT32& rdwAddr, UINT16& rwPort)
{
	INT32 nMaxMatchCount = -1;

	for (INT32 i = 0; i < pGTInfo->nAddrCount; i++)
	{
		INT32 nMatchCount = _GetMatchCount(dwLocalAddr, pGTInfo->dwAddr[i]);
		if (nMatchCount > nMaxMatchCount)
		{
			rdwAddr = pGTInfo->dwAddr[i];
			rwPort = pGTInfo->wPort[i];
			nMaxMatchCount = nMatchCount;
		}
	}


	return TRUE;
Exit0:
	rdwAddr = 0;
	rwPort = 0;

	return FALSE;
}

void CBSExternalMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;
    INT32 nStartIndex = 0;
	UINT32 dwLocalAddr = 0;
	UINT16 wLocalPort = 0;

    PROCESS_ERROR(CBSSessionMgr::GetInstance().GetServerState() == sgsAllReady);

	nRetCode = pSocketSession->GetAddress(dwLocalAddr, wLocalPort);
	LOG_PROCESS_ERROR(nRetCode);

    nStartIndex = CBSSessionMgr::GetInstance().GetCurPointerIndex();
    nStartIndex = (++nStartIndex) % MAX_GT_SESSION_COUNT;
    for(INT32 i = nStartIndex; i < nStartIndex + MAX_GT_SESSION_COUNT; ++i)
    {
        INT32 dwGTSessionID = i % MAX_GT_SESSION_COUNT;
        SGTInfo* pGTInfo = CBSInternalMessageHandler::GetInstance().GetGTInfo(dwGTSessionID);
		if (pGTInfo && pGTInfo->nAddrCount > 0)
        {
			UINT32 dwAddr;
			UINT16 wPort;

			nRetCode = _GetProperAddress(dwLocalAddr, pGTInfo, dwAddr, wPort);
			LOG_PROCESS_ERROR(nRetCode);

			nRetCode = DoQueryGateAck(dwAddr, wPort, pSocketSession);
            LOG_PROCESS_ERROR(nRetCode);

            CBSSessionMgr::GetInstance().SetCurPointerIndex(i);
            break;
        }
    }

Exit0:
	if (pSocketSession)
		pSocketSession->Close();
	return;
}

void CBSExternalMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	LOG_PROCESS_ERROR(FALSE);

Exit0:
	if (pSocketSession)
		pSocketSession->Close();
	return;
}

void CBSExternalMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(pSocketSession);

Exit0:
    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CBSExternalMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bPassiveShutdown)
{
	LOG_PROCESS_ERROR(pSocketSession);

	return;
Exit0:
	return;
}

CBSExternalMessageHandler::CBSExternalMessageHandler()
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;
}

CBSExternalMessageHandler::~CBSExternalMessageHandler()
{
	UnInit();
}

BOOL CBSExternalMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
	LOG_PROCESS_ERROR(pNet);
	LOG_PROCESS_ERROR(pPacketAllocator);

	m_pNet = pNet;
	m_pPacketAllocator = pPacketAllocator;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBSExternalMessageHandler::UnInit(void)
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;

	return TRUE;
}

CBSExternalMessageHandler& CBSExternalMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

BOOL CBSExternalMessageHandler::DoQueryGateAck(UINT32 dwAddr, UINT16 wPort, ISocketSession* pSession)
{
	INT32 nRetCode = 0;

	B2C_QUERY_GATE_ACK* pMsg = (B2C_QUERY_GATE_ACK*) m_pPacketAllocator->Alloc(sizeof(B2C_QUERY_GATE_ACK));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pSession);

	pMsg->wMsg  = b2c_query_gate_ack;
	pMsg->dwAddr = dwAddr;
	pMsg->wPort  = wPort;

	nRetCode = _Send(pSession, (PACKET_BUFFER*)pMsg, sizeof(B2C_QUERY_GATE_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CBSExternalMessageHandler::_Send(ISocketSession* pCliSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pCliSession);
	LOG_PROCESS_ERROR(pPacketBuffer);

	nRetCode = pCliSession->Send(pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);
	
	return TRUE;
Exit0:
	if (pCliSession)
		pCliSession->Close();
	return FALSE;
}