#include "stdafx.h"
#include "trade.h"
#include "item_bag.h"
#include "role.h"
#include "game_world.h"
#include "message_handler.h"
#include "server_def.h"
#include "scene_data.h"

#define NO_ITEM 0xFFFF

CTrade::CTrade()
{
    m_pOwner = NULL;
    m_pTradeTarget = NULL;
    m_state = etsFree;
    m_money = 0;
    memset(m_slots, 0xFF, sizeof(m_slots));
}

void CTrade::Clear(BOOL bClearTarget/*=true*/)
{
    if (m_state != etsFree)
    {
        LOG_CHECK_ERROR(m_pTradeTarget);
        LOG_CHECK_ERROR(m_pTradeTarget->GetTrade()->m_state != etsFree);

        if (bClearTarget && m_pTradeTarget)
        {
            m_pTradeTarget->GetTrade()->Clear(FALSE);
        }
        m_state = etsFree;
        m_pTradeTarget = NULL;
        m_money = 0;
        memset(m_slots, 0xFF, sizeof(m_slots));

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSendTradeStateChange(m_pOwner, m_pOwner->GetObjID(), etsFree);
#endif
    }
}

void CTrade::SetOwner(CRole* role)
{
    m_pOwner = role;
}

INT32 CTrade::AskTrade(UINT32 dwRoleID)
{
    INT32 nResult = errTradeUnknown;
    CRole* pTargetRole = CGameWorld::GetInstance().FindValidRole(dwRoleID);
    CTrade* pTargetTrade = NULL;
    UINT32 dwOwnerSessionID, dwTargetSessionID;

    PROCESS_ERROR_RET_CODE(m_state == etsFree, errTradeWrongState);
    LOG_PROCESS_ERROR_RET_CODE(m_pTradeTarget == NULL, errTradeUnknown);
    PROCESS_ERROR_RET_CODE(pTargetRole, errTradeTargetNotFound);
    LOG_PROCESS_ERROR_RET_CODE(pTargetRole != m_pOwner, errTradeUnknown);
	LOG_PROCESS_ERROR(m_pOwner->GetScene());
	LOG_PROCESS_ERROR(m_pOwner->GetScene()->GetSceneData());
	LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetScene()->GetSceneData()->bCannotTrade, errTradeSceneFobidden);

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(pTargetRole->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_DIE, errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(pTargetRole->GetMoveState() != CMS_DIE, errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetFlag().CheckFlag(cfInCombat) == FALSE, errItemRoleCombat);
    LOG_PROCESS_ERROR_RET_CODE(pTargetRole->GetFlag().CheckFlag(cfInCombat) == FALSE, errItemRoleCombat);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsFreeMode(), errFreeMode);
    LOG_PROCESS_ERROR_RET_CODE(!pTargetRole->IsFreeMode(), errFreeMode);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetLevel() >= g_GWConfig.nRoleLowLevel, errRoleLowLevel);
    LOG_PROCESS_ERROR_RET_CODE(pTargetRole->GetLevel() >= g_GWConfig.nRoleLowLevel, errRoleLowLevel);

    dwOwnerSessionID = m_pOwner->GetSessionID();
    dwTargetSessionID = pTargetRole->GetSessionID();
    LOG_PROCESS_ERROR_RET_CODE(GET_GROUP_INDEX_FROM_SESSION_ID(dwOwnerSessionID) == GET_GROUP_INDEX_FROM_SESSION_ID(dwTargetSessionID), errTradeDifferentGroup);

    if (!m_pOwner->CheckDistance(pTargetRole))
        return errTradeTargetFaraway;

    pTargetTrade = pTargetRole->GetTrade();
    if (pTargetTrade->m_state != etsFree)
        return errTradeTargetBusy;

    m_pTradeTarget = pTargetRole;
    pTargetTrade->m_pTradeTarget = m_pOwner;
    
    m_state = etsAsking;
    _BroadcastStateChange();

    pTargetTrade->m_state = etsBeingAsked;
    pTargetTrade->_BroadcastStateChange();

    return errSuccess;

Exit0:
    return nResult;
}

INT32 CTrade::AcceptTrade(UINT32 dwRoleID)
{
    INT32 nResult = errTradeUnknown;
    CRole* pTargetRole = CGameWorld::GetInstance().FindValidRole(dwRoleID);
    CTrade* pTargetTrade = NULL;

    PROCESS_ERROR_RET_CODE(m_state == etsBeingAsked, errTradeWrongState);
    LOG_PROCESS_ERROR_RET_CODE(m_pTradeTarget, errTradeUnknown);
    PROCESS_ERROR_RET_CODE(m_pTradeTarget == pTargetRole, errTradeTargetNotFound);

    if (!m_pOwner->CheckDistance(pTargetRole))
        return errTradeTargetFaraway;

    pTargetTrade = pTargetRole->GetTrade();
    LOG_PROCESS_ERROR_RET_CODE(pTargetTrade->m_state == etsAsking, errTradeUnknown);
    LOG_PROCESS_ERROR_RET_CODE(pTargetTrade->m_pTradeTarget == m_pOwner, errTradeUnknown);

    m_state = etsTrading;
    _BroadcastStateChange();
    
    pTargetTrade->m_state = etsTrading;
    pTargetTrade->_BroadcastStateChange();

    return errSuccess;

Exit0:
    return nResult;
}

INT32 CTrade::SetItem(UINT8 byTradeSlot, UINT8 bAdd, UINT8 byConSlot, UINT8 byItemSlot)
{
    Item* item = NULL;

    if (m_state != etsTrading)
        return errTradeWrongState;

    LOG_PROCESS_ERROR(m_pTradeTarget);
    PROCESS_ERROR(byTradeSlot < MAX_TRADE_SLOT);

    if (bAdd)
    {
        PROCESS_ERROR(byConSlot == CONSLOT_DEFAULT);

        item = m_pOwner->GetItemBag()->GetItem(byConSlot, byItemSlot);
        if (item == NULL)
            return errItemNotFound;

        if (item->m_iteminfo.m_byBindType == BINDTYPE_BINDED)
            return errItemBinded;

        if (item->m_iteminfo.m_dwRoleID && item->m_iteminfo.m_dwRoleID != m_pTradeTarget->GetObjID())
            return errItemAlreadySigned;

        //Check whether already traded
        for (UINT8 i=0; i<MAX_TRADE_SLOT; i++)
        {
            if (m_slots[i] == MAKEWORD(byConSlot, byItemSlot))
                return errTradeUnknown;
        }

        m_slots[byTradeSlot] = MAKEWORD(byConSlot, byItemSlot);
    }
    else
    {
        m_slots[byTradeSlot] = NO_ITEM;
    }

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendTradeItem(m_pOwner, m_pOwner->GetObjID(), byTradeSlot, bAdd, item);
    CCliMessageHandler::GetInstance().DoSendTradeItem(m_pTradeTarget, m_pOwner->GetObjID(), byTradeSlot, bAdd, item);
#endif
    return errSuccess;

Exit0:
    return errTradeUnknown;
}

INT32 CTrade::SetMoney(INT32 nCount)
{
    INT32 tax = 0;

    LOG_PROCESS_ERROR(nCount >= 0);
    LOG_PROCESS_ERROR(nCount <= MAX_MONEY);

    if (m_state != etsTrading)
        return errTradeWrongState;

    LOG_PROCESS_ERROR(m_pTradeTarget);

    tax = (INT32)(((INT64)nCount * TRADE_TAX + 9999) / 10000);

    if (m_pOwner->GetItemBag()->GetMoney(MONEYTYPE_02) < nCount + tax)
        return errNotEnoughMoney;

    m_money = nCount;

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendTradeMoney(m_pOwner, m_pOwner->GetObjID(), nCount);
    CCliMessageHandler::GetInstance().DoSendTradeMoney(m_pTradeTarget, m_pOwner->GetObjID(), nCount);
#endif
    return errSuccess;

Exit0:
    return errTradeUnknown;
}

INT32 CTrade::LockTrade()
{
    if (m_state != etsTrading)
        return errTradeWrongState;

    LOG_PROCESS_ERROR(m_pTradeTarget);

    m_state = etsLocked;
    _BroadcastStateChange();

    return errSuccess;

Exit0:
    return errTradeUnknown;
}

INT32 CTrade::ConfirmTrade()
{
    CTrade* pTragetTrade = NULL;

    if (m_state != etsLocked)
        return errTradeWrongState;

    LOG_PROCESS_ERROR(m_pTradeTarget);

    pTragetTrade = m_pTradeTarget->GetTrade();
    if (pTragetTrade->m_state != etsLocked && pTragetTrade->m_state != etsConfirmed)
        return errTradeWrongState;

    m_state = etsConfirmed;
    _BroadcastStateChange();

#ifndef _ROBOT
	if (m_state == etsConfirmed && pTragetTrade->m_state == etsConfirmed)
	{
		INT32 nRet = _CommitTrade();

		if (nRet == errSuccess)
			Clear(true);

		return nRet;
	}
#endif //_ROBOT

    return errSuccess;

Exit0:
    return errTradeUnknown;
}

INT32 CTrade::UnlockTrade()
{
    if (m_state != etsLocked && m_state != etsConfirmed)
        return errTradeWrongState;

    LOG_PROCESS_ERROR(m_pTradeTarget);

    m_state = etsTrading;
    _BroadcastStateChange();

    m_pTradeTarget->GetTrade()->m_state = etsTrading;
    m_pTradeTarget->GetTrade()->_BroadcastStateChange();

    return errSuccess;

Exit0:
    return errTradeUnknown;
}

INT32 CTrade::CancelTrade()
{
    if (m_state == etsFree)
        return errTradeWrongState;

    Clear(true);

    return errSuccess;
}

BOOL CTrade::IsTradeItem(UINT8 byContainerSlot, UINT8 byItemSlot) const
{
    UINT16 dst = MAKEWORD(byContainerSlot, byItemSlot);

    if (m_state == etsFree)
        return FALSE;

    for (UINT8 i=0; i<MAX_TRADE_SLOT; i++)
    {
        if (m_slots[i] == dst)
            return TRUE;
    }

    return FALSE;
}

INT32 CTrade::_CommitTrade()
{
    CTrade* pTargetTrade = NULL;
    INT32 tax, target_tax;
    std::list<Item*> items, target_items;
    INT32 item_count_diff;
    INT32 nRetCode = errUnknownError;

    LOG_PROCESS_ERROR(m_state == etsConfirmed);
    LOG_PROCESS_ERROR(m_pTradeTarget);
    pTargetTrade = m_pTradeTarget->GetTrade();
    LOG_PROCESS_ERROR(pTargetTrade->m_state == etsConfirmed);

    //Check money
    tax = (INT32)(((INT64)m_money * TRADE_TAX + 9999) / 10000);
    if (m_money && m_pOwner->GetItemBag()->GetMoney(MONEYTYPE_02) < m_money + tax)
	{
		m_pOwner->ErrorCodeNotify(errNotEnoughMoney, 0, 0);
		m_pTradeTarget->ErrorCodeNotify(errNotEnoughMoney, m_pOwner->GetObjID(), 0);
        return errSuccess;
    }

    target_tax = (INT32)((INT64)pTargetTrade->m_money * TRADE_TAX + 9999) / 10000;
    if (pTargetTrade->m_money && m_pTradeTarget->GetItemBag()->GetMoney(MONEYTYPE_02) < pTargetTrade->m_money + target_tax)
	{
		m_pOwner->ErrorCodeNotify(errNotEnoughMoney, m_pTradeTarget->GetObjID(), 0);
		m_pTradeTarget->ErrorCodeNotify(errNotEnoughMoney, 0, 0);
        return errSuccess;
    }

    //Check items
    item_count_diff = 0;
    for (INT32 i=0; i<MAX_TRADE_SLOT; i++)
    {
        if (m_slots[i] != NO_ITEM)
        {
            UINT8 conslot = LOBYTE(m_slots[i]);
            UINT8 itemslot = HIBYTE(m_slots[i]);
            Item* item = m_pOwner->GetItemBag()->GetItem(conslot, itemslot);
            LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT);
            LOG_PROCESS_ERROR(item);
            LOG_PROCESS_ERROR(item->m_iteminfo.m_byBindType != BINDTYPE_BINDED);
            items.push_back(item);
            item_count_diff++;
        }
    }
    for (INT32 i=0; i<MAX_TRADE_SLOT; i++)
    {
        if (pTargetTrade->m_slots[i] != NO_ITEM)
        {
            UINT8 conslot = LOBYTE(pTargetTrade->m_slots[i]);
            UINT8 itemslot = HIBYTE(pTargetTrade->m_slots[i]);
            Item* item = m_pTradeTarget->GetItemBag()->GetItem(conslot, itemslot);
            LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT);
            LOG_PROCESS_ERROR(item);
            LOG_PROCESS_ERROR(item->m_iteminfo.m_byBindType != BINDTYPE_BINDED);
            target_items.push_back(item);
            item_count_diff--;
        }
    }

    if (item_count_diff > 0)
    {
        if (item_count_diff > (INT32)m_pTradeTarget->GetItemBag()->GetFreeSlots(CONSLOT_DEFAULT))
		{
			m_pOwner->ErrorCodeNotify(errTradeBagFull, m_pTradeTarget->GetObjID(), 0);
			m_pTradeTarget->ErrorCodeNotify(errTradeBagFull, m_pTradeTarget->GetObjID(), 0);
            return errTradeBagFull;
        }
    }
    if (item_count_diff < 0)
    {
        if (-item_count_diff > (INT32)m_pOwner->GetItemBag()->GetFreeSlots(CONSLOT_DEFAULT))
		{
			m_pOwner->ErrorCodeNotify(errTradeBagFull, m_pOwner->GetObjID(), 0);
			m_pTradeTarget->ErrorCodeNotify(errTradeBagFull, m_pOwner->GetObjID(), 0);
            return errTradeBagFull;
        }
    }

    m_state = etsSuccess;
    _BroadcastStateChange();

    pTargetTrade->m_state = etsSuccess;
    pTargetTrade->_BroadcastStateChange();

    //Debit and credit money
    if (m_money)
    {
        nRetCode = m_pOwner->GetItemBag()->SubMoney(MONEYTYPE_02, m_money, MONEYLOG_PLAYER_TRADE, m_pTradeTarget->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);

        nRetCode = m_pOwner->GetItemBag()->SubMoney(MONEYTYPE_02, tax, MONEYLOG_PLAYER_TRADE_TAX, 0);
        LOG_CHECK_ERROR(nRetCode == errSuccess);

        nRetCode = m_pTradeTarget->GetItemBag()->AddMoney(MONEYTYPE_02, m_money, MONEYLOG_PLAYER_TRADE, m_pOwner->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }
    if (pTargetTrade->m_money)
    {
        nRetCode = m_pTradeTarget->GetItemBag()->SubMoney(MONEYTYPE_02, pTargetTrade->m_money, MONEYLOG_PLAYER_TRADE, m_pOwner->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);

        nRetCode = m_pTradeTarget->GetItemBag()->SubMoney(MONEYTYPE_02, target_tax, MONEYLOG_PLAYER_TRADE_TAX, 0);
        LOG_CHECK_ERROR(nRetCode == errSuccess);

        nRetCode = m_pOwner->GetItemBag()->AddMoney(MONEYTYPE_02, pTargetTrade->m_money, MONEYLOG_PLAYER_TRADE, m_pTradeTarget->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }

    //Exchange items
    for (std::list<Item*>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        nRetCode = m_pOwner->GetItemBag()->RemoveItem((*it)->m_iteminfo.m_byConSlot, (*it)->m_iteminfo.m_byItemSlot, ITEMLOG_PLAYER_TRADE);
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }
    for (std::list<Item*>::iterator it=target_items.begin(); it!=target_items.end(); ++it)
    {
        nRetCode = m_pTradeTarget->GetItemBag()->RemoveItem((*it)->m_iteminfo.m_byConSlot, (*it)->m_iteminfo.m_byItemSlot, ITEMLOG_PLAYER_TRADE);
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }
    for (std::list<Item*>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        nRetCode = m_pTradeTarget->GetItemBag()->AddItem(*it, ITEMLOG_PLAYER_TRADE, m_pOwner->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }
    for (std::list<Item*>::iterator it=target_items.begin(); it!=target_items.end(); ++it)
    {
        nRetCode = m_pOwner->GetItemBag()->AddItem(*it, ITEMLOG_PLAYER_TRADE, m_pTradeTarget->GetObjID());
        LOG_CHECK_ERROR(nRetCode == errSuccess);
    }

    return errSuccess;

Exit0:
    return errTradeUnknown;
}

void CTrade::_BroadcastStateChange()
{
#ifndef _ROBOT

    CCliMessageHandler::GetInstance().DoSendTradeStateChange(m_pOwner, m_pOwner->GetObjID(), m_state);
    if (m_pTradeTarget)
		CCliMessageHandler::GetInstance().DoSendTradeStateChange(m_pTradeTarget, m_pOwner->GetObjID(), m_state);
#endif // _ROBOT
}

