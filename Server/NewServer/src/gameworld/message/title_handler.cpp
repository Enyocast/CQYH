#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "game_world.h"
#include "chat_def.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnEquipTitle(CRole* pRole, const char* pData)
{
    C2G_TITLE_EQUIP* pMsg = (C2G_TITLE_EQUIP*)pData;

    INT32 err = pRole->GetTitle().EquipTile(pMsg->nTemplateTitleID);
    if (err != errSuccess)
    {
		pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnUnEquipTitle(CRole* pRole, const char* pData)
{
    pRole->GetTitle().UnEquipTitle();

    return;
}

BOOL CCliMessageHandler::DoSyncTitle(CRole* pRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_TITLE* pMsg =NULL;

    LOG_PROCESS_ERROR(pRole);
    
    LOG_PROCESS_ERROR(sizeof(G2C_SYNC_TITLE) + sizeof(TITLE_DATA) * MAX_TITLE_LIST_NUM < MAX_MESSAGE_SIZE);
    pMsg = (G2C_SYNC_TITLE*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_title;
    pMsg->wSize = sizeof(G2C_SYNC_TITLE);
    pMsg->nTitleCount = 0;
    pMsg->nEquipedTitleID = pRole->GetTitle().GetEquipedTitleID();
    
    pRole->GetTitle().fill(pMsg->stTitleList, pMsg->nTitleCount);

    pMsg->wSize = sizeof(G2C_SYNC_TITLE) + pMsg->nTitleCount * sizeof(TITLE_DATA);

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoAddTitle(CRole* pRole, UINT8 nTitleID, INT32 nExpireTime)
{
    INT32 nRetCode = 0;
    G2C_ADD_TITLE* pMsg =NULL;
    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_ADD_TITLE*)m_poPacketAllocator->Alloc(sizeof(G2C_ADD_TITLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_add_title;
    pMsg->nTitleID = nTitleID;
    pMsg->nExpireTime = nExpireTime;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_ADD_TITLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoDelTitle(CRole* pRole, UINT8 nTitleID, UINT8 nDelType)
{
    INT32 nRetCode = 0;
    G2C_DEL_TITLE* pMsg =NULL;
    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_DEL_TITLE*)m_poPacketAllocator->Alloc(sizeof(G2C_DEL_TITLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_del_title;
    pMsg->nTitleID = nTitleID;
    pMsg->nDelType = nDelType;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_DEL_TITLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}




#endif
