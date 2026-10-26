#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "role.h"
#include "game_world.h"
#include "server_def.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnOpenStall(CRole* pRole, const char* pData)
{
    C2G_OPEN_STALL* msg = (C2G_OPEN_STALL*)pData;

    INT32 err = pRole->GetStall()->Open();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnCloseStall(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetStall()->Close();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnRealOpenStall(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetStall()->RealOpen();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnRealCloseStall(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetStall()->RealClose();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnAddStallItem(CRole* pRole, const char* pData)
{
    C2G_ADD_STALL_ITEM* msg = (C2G_ADD_STALL_ITEM*)pData;

    INT32 err = pRole->GetStall()->AddGood(msg->btStallSlot, msg->byConSlot, msg->byItemSlot, msg->shItemCount, msg->nPrice);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnRemoveStallItem(CRole* pRole, const char* pData)
{
    C2G_REMOVE_STALL_ITEM* msg = (C2G_REMOVE_STALL_ITEM*)pData;

    INT32 err = pRole->GetStall()->RemoveGood(msg->btStallSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnChangeStallName(CRole* pRole, const char* pData)
{
    C2G_CHANGE_STALL_NAME* msg = (C2G_CHANGE_STALL_NAME*)pData;

    INT32 err = pRole->GetStall()->ChangeName(msg->szStallName);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnUpgradeStall(CRole* pRole, const char* pData)
{
    C2G_UPGRADE_STALL* msg = (C2G_UPGRADE_STALL*)pData;

    INT32 err = pRole->GetStall()->Upgrade(msg->btUpgradeCostType);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify( err, 0, 0);
    }
}

void CCliMessageHandler::OnViewStallItem(CRole* pRole, const char* pData)
{
    C2G_VIEW_STALL_ITEM* msg = (C2G_VIEW_STALL_ITEM*)pData;

    CRole* pStallOwner = CGameWorld::GetInstance().FindValidRole(msg->dwRoleID);
    if (pStallOwner == NULL)
    {
        pRole->ErrorCodeNotify( errStallNotFound, 0, 0);
    }
    else
    {
        INT32 err = pStallOwner->GetStall()->ViewGood(pRole);
        if (err != errSuccess)
        {
            pRole->ErrorCodeNotify( err, 0, 0);
        }
    }
}

void CCliMessageHandler::OnBuyStallItem(CRole* poRole, const char* pData)
{
    C2G_BUY_STALL_ITEM* msg = (C2G_BUY_STALL_ITEM*)pData;

    if (poRole->GetObjID() == msg->dwRoleID)
    {
        KICK_ROLE(poRole, ktLogged);
        return;
    }

    CRole* pStallOwner = CGameWorld::GetInstance().FindValidRole(msg->dwRoleID);
    if (pStallOwner == NULL)
    {
        poRole->ErrorCodeNotify( errStallNotFound, 0, 0);
        return;
    }

    INT32 err = pStallOwner->GetStall()->BuyGood(poRole, msg->btStallSlot, msg->shItemCount, msg->llModfiyFrame);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify( err, 0, 0);
    }
}

BOOL CCliMessageHandler::DoBroadcastStallStateChange(CRole* poRole, UINT8 stallstate)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(G2C_STALL_STATE_CHANGE);

    G2C_STALL_STATE_CHANGE* pMsg = (G2C_STALL_STATE_CHANGE*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_stall_state_change;
    pMsg->dwRoleID = poRole->GetObjID();
    pMsg->btStallState = stallstate;

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoBroadcastStallNameChange(CRole* poRole, const char* stallname)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(G2C_CHANGE_STALL_NAME);
    G2C_CHANGE_STALL_NAME* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_CHANGE_STALL_NAME*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_change_stall_name;
    pMsg->dwRoleID = poRole->GetObjID();
    strxcpy(pMsg->szStallName, stallname, STALL_NAME_LEN);

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoBroadcastStallLevelChange(CRole* poRole, UINT8 stalllevel)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(G2C_CHANGE_STALL_LEVEL);
    G2C_CHANGE_STALL_LEVEL* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_CHANGE_STALL_LEVEL*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_change_stall_level;
    pMsg->dwRoleID = poRole->GetObjID();
    pMsg->byStallLevel = stalllevel;

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendAddStallItem(CRole* poRole, UINT8 stallslot, UINT8 conslot, UINT8 itemslot, INT16 itemcount, INT32 price)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(G2C_ADD_STALL_ITEM);
    G2C_ADD_STALL_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_ADD_STALL_ITEM*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_add_stall_item;
    pMsg->btStallSlot = stallslot;
    pMsg->byConSlot = conslot;
    pMsg->byItemSlot = itemslot;
    pMsg->shItemCount = itemcount;
    pMsg->nPrice = price;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRemvoeStallItem(CRole* poRole, UINT8 stallslot)
{
    INT32 nRetCode = 0;
    INT32 nSize = sizeof(G2C_REMOVE_STALL_ITEM);
    G2C_REMOVE_STALL_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_REMOVE_STALL_ITEM*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_remove_stall_item;
    pMsg->btStallSlot = stallslot;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendStallItemList(CRole* poViewer, CRole* poOwner)
{
    INT32 nRetCode = 0;
    CStall* pStall = NULL;
    G2C_VIEW_STALL_ITEM* pMsg = NULL;
    char* stallbuf = NULL;
    UINT32 itemlen = 0;
    INT16 original_count = 0;
    BOOL switch_count = FALSE;

    LOG_PROCESS_ERROR(poViewer);
    LOG_PROCESS_ERROR(poOwner);

    pStall = poOwner->GetStall();
    LOG_PROCESS_ERROR(pStall);

    pMsg = (G2C_VIEW_STALL_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_view_stall_item;
    pMsg->wSize = sizeof(G2C_VIEW_STALL_ITEM);
    pMsg->dwRoleID = poOwner->GetObjID();
    pMsg->btStallItemCount = 0;

    stallbuf = pMsg->acStallItems;

    for (CStall::Goods::const_iterator it=pStall->GetGoods().begin(); it!=pStall->GetGoods().end(); ++it)
    {
        const CStall::Good& good = it->second;

        STALL_ITEM_INFO* sinfo = (STALL_ITEM_INFO*)stallbuf;
        sinfo->btStallSlot = it->first;
        sinfo->nPrice = good.price;
        sinfo->llModifyFrame = good.lastmodifyframe;

        if (good.item->m_pTemplate->m_byDurType == DURTYPE_STACK && good.item->m_iteminfo.m_nCurDur != good.count)
        {
            switch_count = TRUE;
            original_count = good.item->m_iteminfo.m_nCurDur;
            good.item->m_iteminfo.m_nCurDur = good.count;
        }
        else
            switch_count = FALSE;

        itemlen = good.item->m_iteminfo.Save(sinfo->acItem);

        if (switch_count)
            good.item->m_iteminfo.m_nCurDur = original_count;


        stallbuf += (sizeof(STALL_ITEM_INFO) + itemlen);
        pMsg->wSize += (UINT16)(sizeof(STALL_ITEM_INFO) + itemlen);
        pMsg->btStallItemCount++;
    }

    nRetCode = m_poNotifier->SendToUser(poViewer->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendBuyStallItem(CRole* poBuyer, UINT32 sellerid, UINT8 stallslot, INT32 leftcount)
{
    INT32 nRetCode = 0;
    G2C_BUY_STALL_ITEM* pMsg = NULL;
    INT32 nSize = sizeof(G2C_BUY_STALL_ITEM);

    LOG_PROCESS_ERROR(poBuyer);

    pMsg = (G2C_BUY_STALL_ITEM*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_buy_stall_item;
    pMsg->dwRoleID = sellerid;
    pMsg->btStallSlot = stallslot;
    pMsg->nLeftItemCount = leftcount;

    nRetCode = m_poNotifier->SendToUser(poBuyer->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendSoldStallItem(CRole* poSeller, UINT8 stallslot, INT32 itemcount, INT32 totalincome)
{
    INT32 nRetCode = 0;
    G2C_SOLD_STALL_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(poSeller);

    pMsg = (G2C_SOLD_STALL_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_SOLD_STALL_ITEM));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sold_stall_item;
    pMsg->btStallSlot = stallslot;
    pMsg->nItemCount = itemcount;
    pMsg->nTotalIncome = totalincome;

    nRetCode = m_poNotifier->SendToUser(poSeller->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SOLD_STALL_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncStall(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_STALL* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_SYNC_STALL*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_STALL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_stall;
    pMsg->dwUpgradeExpireTime = poRole->GetStall()->GetStallLevelUpExpireTime();

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_STALL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

#endif  // _ROBOT
