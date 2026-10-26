#include "stdafx.h"
#include "message_handler.h"

#ifndef _ROBOT

#include "g2c_message.h"
#include "c2g_message.h"

#include "server_def.h"
#include "imessage_notifier.h"
#include "doodad_data.h"
#include "doodad.h"
#include "region.h"

using namespace ExternalMessage;

void CCliMessageHandler::OnOperateDoodad(CRole* pRole, const char* pData)
{
    INT32 nResult = errUnknownError;
    INT32 nRetCode = 0;
    C2G_OPERATE_DOODAD* pMsg = (C2G_OPERATE_DOODAD*)pData;

    nRetCode = pRole->OperateDoodad(pMsg->dwDoodadID);
    PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

    return;
Exit0:
    if (nResult == errUnknownError)
        KICK_ROLE(pRole, ktLogged);
    else
		pRole->ErrorCodeNotify(nResult, 0, 0);

    return;
}

struct CTraverseDoodad
{
    G2C_SYNC_DOODAD_LIST* SyncDoodadList;
    INT32 nCount;

    BOOL operator()(CDoodad* poDoodad)
    {
        LOG_PROCESS_ERROR(poDoodad);
        LOG_PROCESS_ERROR(nCount < MAX_SYNC_DOODAD_COUNT);
        {
            DOODAD_APPEAR_DATA& rAppearData = SyncDoodadList->astAppearData[nCount];

            rAppearData.dwDoodadID = poDoodad->GetObjID();
            rAppearData.nTemplateID = poDoodad->GetDoodadData()->nTemplateID;
            rAppearData.wCurrentX = ConvertCoordS2N(poDoodad->GetX());
            rAppearData.wCurrentY = ConvertCoordS2N(poDoodad->GetY());
            rAppearData.wCurrentZ = ConvertCoordS2N(poDoodad->GetZ());
            rAppearData.wFaceDirection = (UINT16)poDoodad->GetFaceDirection();
            rAppearData.byRemainOpenCount = (UINT8)poDoodad->GetOpenCount();

            nCount++;
        }

        return TRUE;
Exit0:
        return FALSE;
    }
};

BOOL CCliMessageHandler::DoSyncDoodadList(CRole* poRole, CRegion* poRegion)
{
    INT32 nRetCode = 0;
    G2C_SYNC_DOODAD_LIST* pMsg = NULL;
    CTraverseDoodad TraverseDoodad;

    LOG_PROCESS_ERROR(poRegion);
    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_SYNC_DOODAD_LIST*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_doodad_list;

    TraverseDoodad.SyncDoodadList = pMsg;
    TraverseDoodad.nCount = 0;

    nRetCode = poRegion->TraverseDoodad(TraverseDoodad);
    LOG_CHECK_ERROR(nRetCode);

    if (TraverseDoodad.nCount > 0)
    {
        pMsg->wSize = sizeof(G2C_SYNC_DOODAD_LIST) + sizeof(DOODAD_APPEAR_DATA) * TraverseDoodad.nCount;
        nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
        LOG_CHECK_ERROR(nRetCode);
    }
    else
    {
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    }

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoDoodadAppear(CDoodad* poDoodad)
{
    INT32 nRetCode = 0;
    G2C_DOODAD_APPEAR* pMsg = NULL;

    LOG_PROCESS_ERROR(poDoodad);

    LOG_PROCESS_ERROR(m_poPacketAllocator);
	pMsg = (G2C_DOODAD_APPEAR*)m_poPacketAllocator->Alloc(sizeof(G2C_DOODAD_APPEAR));
    LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_doodad_appear;
    pMsg->AppearData.dwDoodadID = poDoodad->GetObjID();
    pMsg->AppearData.nTemplateID = poDoodad->GetDoodadData()->nTemplateID;
    pMsg->AppearData.wCurrentX = ConvertCoordS2N(poDoodad->GetX());
    pMsg->AppearData.wCurrentY = ConvertCoordS2N(poDoodad->GetY());
    pMsg->AppearData.wCurrentZ = ConvertCoordS2N(poDoodad->GetZ());
	pMsg->AppearData.wFaceDirection = (UINT16)poDoodad->GetFaceDirection();
    pMsg->AppearData.byRemainOpenCount = (BYTE)poDoodad->GetOpenCount();

	nRetCode = _Broadcast9Region(poDoodad->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_DOODAD_APPEAR));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}


BOOL CCliMessageHandler::DoOperateDoodadBegin(CCharacter* poChar, UINT32 dwDoodadID, INT32 nDuration)
{
    INT32  nRetCode = 0;
    G2C_OPERATE_DOODAD_BEGIN* pMsg = NULL;

    LOG_PROCESS_ERROR(poChar);

    pMsg = (G2C_OPERATE_DOODAD_BEGIN*)m_poPacketAllocator->Alloc(sizeof(G2C_OPERATE_DOODAD_BEGIN));
    LOG_PROCESS_ERROR(pMsg); 

    pMsg->wMsg = g2c_operate_doodad_begin;
    pMsg->dwCharID = poChar->GetObjID();
    pMsg->dwDoodadID = dwDoodadID;
    pMsg->wDuration = nDuration;

    nRetCode = _Broadcast9Region(poChar->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_OPERATE_DOODAD_BEGIN));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoOperateDoodadEnd(CCharacter* poChar, UINT32 dwDoodadID, BOOL bIsBreak)
{
    INT32  nRetCode = 0;
    G2C_OPERATE_DOODAD_END* pMsg = NULL;

    LOG_PROCESS_ERROR(poChar);

    pMsg = (G2C_OPERATE_DOODAD_END*)m_poPacketAllocator->Alloc(sizeof(G2C_OPERATE_DOODAD_END));
    LOG_PROCESS_ERROR(pMsg); 

    pMsg->wMsg = g2c_operate_doodad_end;
    pMsg->dwCharID = poChar->GetObjID();
    pMsg->dwDoodadID = dwDoodadID;
    pMsg->byIsBreak = bIsBreak;

    nRetCode = _Broadcast9Region(poChar->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_OPERATE_DOODAD_END));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

#endif  // _ROBOT