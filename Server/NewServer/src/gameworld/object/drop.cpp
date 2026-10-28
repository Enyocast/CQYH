#include "stdafx.h"
#include "drop.h"

#include "item.h"
#include "item_mgr.h"
#include "id_def.h"
#include "error_def.h"
#include "game_world.h"
#include "role.h"
#include "message_handler.h"
#include "statistic.h"

CDrop::CDrop()
:m_state(DS_INVALID)
,m_state_frame(0)
{
    memset(&m_content, 0, sizeof(m_content));
}

CDrop::~CDrop()
{
    UnInit();
}

BOOL CDrop::Init(UINT32 dwObjID, const DropContent& content, DropState drop_state)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(content.m_type == DropContent::DROP_ITEM || content.m_type == DropContent::DROP_MONEY);
    LOG_PROCESS_ERROR(drop_state == DS_PROTECT || drop_state == DS_PUBLIC || drop_state == DS_PLAYER);

    nRetCode = CSceneObject::Init(dwObjID);
    LOG_PROCESS_ERROR(nRetCode);

    m_content = content;

    _SetState(drop_state);

    return TRUE;

Exit0:
    UnInit();

    return FALSE;
}

BOOL CDrop::UnInit()
{
    DestroyContent();
    m_state = DS_INVALID;
    m_state_frame = 0;
    m_owners.clear();

    return TRUE;
}

BOOL CDrop::MainLoop()
{
    //Protected for 2 minutes, public for 2 minutes, then disappears
    switch (m_state)
    {
    case DS_PROTECT:
        if (CGameWorld::GetInstance().GetGameFrame() - m_state_frame >= 4 * 60 * GAME_FPS)
        {
            DeleteSelf();
        }
        else if (CGameWorld::GetInstance().GetGameFrame() - m_state_frame >= 2 * 60 * GAME_FPS)
        {
            _SetState(DS_PUBLIC, m_state_frame + 2 * 60 * GAME_FPS);
        }
        break;
    case DS_PUBLIC:
        if (CGameWorld::GetInstance().GetGameFrame() - m_state_frame >= 2 * 60 * GAME_FPS)
        {
            DeleteSelf();
        }
        break;
    case DS_PLAYER:
        LOG_PROCESS_ERROR(m_content.m_type == DropContent::DROP_ITEM);
        if (CGameWorld::GetInstance().GetGameFrame() - m_state_frame >= m_content.m_item->m_pTemplate->m_nPlayerDropTime * GAME_FPS)
        {
            DeleteSelf();
        }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
    }
    return TRUE;

Exit0:
    return FALSE;
}

INT32 CDrop::GetObjType()
{
    return otDrop;
}

void CDrop::AddOwner(UINT32 dwRoleID)
{
    m_owners.insert(dwRoleID);
}

BOOL CDrop::IsOwner(UINT32 dwRoleID) const
{
    return m_owners.find(dwRoleID) != m_owners.end();
}

UINT32 CDrop::PopOwner()
{
	if (m_owners.empty())
	{
		return INVALID_OBJECT_ID;
	}
	else
	{
		iterowner iter = m_owners.begin();
		UINT32 nOwnerID = *iter;
		m_owners.erase(iter);

		return nOwnerID;
	}
}

INT32 CDrop::OnPickUp(CRole* pRole)
{
    INT32 nRetCode = 0;
    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(m_state == DS_PROTECT || m_state == DS_PUBLIC || m_state == DS_PLAYER);
    LOG_PROCESS_ERROR(m_content.m_type == DropContent::DROP_ITEM || m_content.m_type == DropContent::DROP_MONEY);

    if (m_state == DS_PROTECT && !IsOwner(pRole->GetObjID()))
    {
        return errDropProtected;
    }

    if (m_state == DS_PLAYER &&
        m_content.m_type == DropContent::DROP_ITEM &&
        m_content.m_item->m_iteminfo.m_byBindType == BINDTYPE_BINDED &&
        !IsOwner(pRole->GetObjID()))
    {
        return errDropBindied;
    }

    // Pick up item
    if (m_content.m_type == DropContent::DROP_ITEM)
    {
		CTeamInGS* pTeam = NULL;

		if (pRole->GetTeamID())
		{
			pTeam = CGameWorld::GetInstance().FindTeam(pRole->GetTeamID());
			LOG_PROCESS_ERROR(pTeam);
		}

        // Trigger team auction
		if (pTeam && pTeam->CanBeAddedtoBidAuction(m_content.m_item) && m_state == DS_PROTECT)
		{
			nRetCode = pTeam->AddAuctionItem(this);
			LOG_PROCESS_ERROR(nRetCode);
		}
        // Pick up directly into the bag
		else
		{
	        nRetCode = pRole->GetItemBag()->AddItem(m_content.m_item, ITEMLOG_LOOT, 0);
 			LOG_PROCESS_ERROR(nRetCode);
 		}
    }
    // Pick up currency
    else
    {
        // Additional code: check whether the character’s time card has expired (active card doubles gold rewards); temporarily disabled
        {
//            if (m_content.m_money.moneytype == MONEYTYPE_02)
//            {
//                INT32 nAddCount = pRole->GetGameTimeCard_HaveTime() == FALSE ? m_content.m_money.count * 2 : m_content.m_money.count;
//                pRole->GetItemBag()->AddMoney(m_content.m_money.moneytype, nAddCount, MONEYLOG_LOOT, 0);
//
//#ifndef _ROBOT
//                CStatistic::GetInstance().OnAddMoney(pRole, avdPickMoneyTotal, m_content.m_money.moneytype, nAddCount);
//
//                CCliMessageHandler::GetInstance().DoPickUpMoney(pRole, m_content.m_money.moneytype, nAddCount);
//#endif
//            }
//            // Other currencies are handled normally
//            else
//            {
//                pRole->GetItemBag()->AddMoney(m_content.m_money.moneytype, m_content.m_money.count, MONEYLOG_LOOT, 0);
//
//#ifndef _ROBOT
//                CStatistic::GetInstance().OnAddMoney(pRole, avdPickMoneyTotal, m_content.m_money.moneytype, m_content.m_money.count);
//
//                CCliMessageHandler::GetInstance().DoPickUpMoney(pRole, m_content.m_money.moneytype, m_content.m_money.count);
//#endif
//            }
        }

        // Original code: pick up currency normally
        {
            pRole->GetItemBag()->AddMoney(m_content.m_money.moneytype, m_content.m_money.count, MONEYLOG_LOOT, 0);

#ifndef _ROBOT
            CStatistic::GetInstance().OnAddMoney(pRole, avdPickMoneyTotal, m_content.m_money.moneytype, m_content.m_money.count);

            CCliMessageHandler::GetInstance().DoPickUpMoney(pRole, m_content.m_money.moneytype, m_content.m_money.count);
#endif
        }

        nRetCode = errSuccess;
    }

    if (nRetCode == errSuccess)
    {
        memset(&m_content, 0, sizeof(m_content));
        DeleteSelf();
        return errSuccess;
    }
    else
        return nRetCode;

Exit0:
    return errUnknownError;
}

void CDrop::DestroyContent()
{
    if (m_content.m_type == DropContent::DROP_ITEM)
    {
        LOG_PROCESS_ERROR(m_content.m_item);
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(m_content.m_item);
        LOG_CHECK_ERROR(bItemRet);
        m_content.m_type = DropContent::DROP_INVALID;
    }
    else if (m_content.m_type == DropContent::DROP_MONEY)
    {
        m_content.m_type = DropContent::DROP_INVALID;
    }
    else if (m_content.m_type != DropContent::DROP_INVALID)
    {
        LOG_PROCESS_ERROR(FALSE);
    }

Exit0:
    return;
}

void CDrop::_SetState(DropState estate, INT64 frame/*=0*/)
{
    m_state = estate;
    if (frame)
        m_state_frame = frame;
    else
        m_state_frame = CGameWorld::GetInstance().GetGameFrame();
}
