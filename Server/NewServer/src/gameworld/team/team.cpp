#include "stdafx.h"
#include "team.h"
#include "message_handler.h"
#include "item.h"
#include "game_world.h"
#include "mail_template_data.h"
#include "statistic.h"
#include "item_mgr.h"
#include "master.h"

CTeamInGS::CTeamInGS()
{
	m_nGroupID = 0;
	m_dwTeamID = 0;
	m_dwRoomID = 0;
	m_eAssignType = etaFreeForAll;
	m_nAuctionItemColorLimit = 0;
	m_dwLeader = INVALID_OBJECT_ID;
	m_nMaxMemberCount = 0;
	m_nMemberCount = 0;
	m_dwTgtSceneTempID = 0;
	m_dwTgtSceneID = 0;
	m_nTgtX = 0;
	m_nTgtY = 0;
	m_nTgtZ = 0;
	m_dwCreateTime = 0;
	m_dwAuctionItemIndex = 0;
	m_dwAcitivtyType = 0;
	m_dwAcitivtyID = 0;

	memset(m_szTeamName, 0, sizeof(m_szTeamName));
	memset(m_MemberTable, 0, sizeof(m_MemberTable));
}

CTeamInGS::~CTeamInGS()
{
	UnInit();
}

INT32 CTeamInGS::Init(void)
{
	INT32 nRetCode = 0;

	m_dwAuctionItemIndex = TEAM_AUCTION_ITEM_INIT_INDEX;
	m_dwCreateTime = 0;

	m_dwAcitivtyType = etaatInvalid;
	m_dwAcitivtyID = 0;

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CTeamInGS::UnInit(void)
{
	INT32 nRetCode = 0;

	for (TAuctionItemList::iterator itr = m_AuctionItemList.begin(); itr != m_AuctionItemList.end(); ++itr)
	{
		TeamAuctionItem* poAuctionItem = *itr;
		if (poAuctionItem != NULL)
		{
			CGameWorld::GetInstance().DelTeamAutionItem(poAuctionItem);
		}
	}
	m_AuctionItemList.clear();

	return TRUE;
}

INT32 CTeamInGS::Mainloop(void)
{
	INT32 nRetCode = 0;
	TeamAuctionItem* poAuctionItem = NULL;

	PROCESS_SUCCESS(m_AuctionItemList.empty());

	// Get the first entry
	poAuctionItem = *(m_AuctionItemList.begin());
	LOG_PROCESS_ERROR(poAuctionItem);

	// Start the auction if it has not begun
	if (!poAuctionItem->bInBidding)
	{
#ifndef _ROBOT
		nRetCode = CCliMessageHandler::GetInstance().DoTeamAuctionBegin(this, poAuctionItem);
		LOG_CHECK_ERROR(nRetCode);
#endif

		DBG("--- Auction Begin index: %u", poAuctionItem->dwIndex);

		poAuctionItem->bInBidding = TRUE;
		if (poAuctionItem->BidRoleList.empty())
			poAuctionItem->dwEndFrm = CGameWorld::GetInstance().GetGameFrame();
		else
			poAuctionItem->dwEndFrm = CGameWorld::GetInstance().GetGameFrame() + CONVERT_TIME(g_GWConfig.nTeamAuctionTimeout);
	}

	// End the auction when time expires or no characters can bid (everyone has passed)
	//if (poAuctionItem->dwEndFrm <= CGameWorld::GetInstance().GetGameFrame()    // Original code checks only the time
	if (poAuctionItem->dwEndFrm <= CGameWorld::GetInstance().GetGameFrame() ||   // New code checks both time and the number of eligible bidders
		poAuctionItem->BidRoleList.empty() == TRUE)
	{
		UINT32 dwTax = 0;

		if (poAuctionItem->dwWinnerID != 0)
		{
			TeamAuctionItem::TDepositeMap::iterator itr = poAuctionItem->DepositeMap.find(poAuctionItem->dwWinnerID);
			if (itr == poAuctionItem->DepositeMap.end())
			{
				poAuctionItem->dwWinnerID = 0;
				LOG_PROCESS_ERROR(FALSE);
			}
			else
			{
				if(itr->second < poAuctionItem->dwCurrentPrice)
				{
					poAuctionItem->dwWinnerID = 0;
					LOG_PROCESS_ERROR(FALSE);
				}

				itr->second -= poAuctionItem->dwCurrentPrice;
				if (itr->second == 0)
					poAuctionItem->DepositeMap.erase(itr);
			}

			dwTax = poAuctionItem->dwCurrentPrice * g_GWConfig.nTeamAuctionTax / RATE_MAX;
			dwTax = dwTax < 1 ? 1 : dwTax;

			UINT32 dwRewardMoneyCount = poAuctionItem->dwCurrentPrice - dwTax;

			for (TeamAuctionItem::TIDList::iterator itr = poAuctionItem->RewardRoleList.begin(); itr != poAuctionItem->RewardRoleList.end(); )
			{
				if (*itr == poAuctionItem->dwWinnerID)
				{
					itr = poAuctionItem->RewardRoleList.erase(itr);
					break;
				}

				++itr;
			}

			if (dwRewardMoneyCount >= poAuctionItem->RewardRoleList.size() && poAuctionItem->RewardRoleList.size() > 0)
			{
				for (TeamAuctionItem::TIDList::iterator itr = poAuctionItem->RewardRoleList.begin(); itr != poAuctionItem->RewardRoleList.end(); ++itr)
				{
					UINT32 dwRoleID = *itr;
					nRetCode = CGameWorld::GetInstance().SendMoneyMail(dwRoleID, mtiTeamAuctionSendBonus, MONEYTYPE_02, dwRewardMoneyCount / poAuctionItem->RewardRoleList.size(), MONEYLOG_TEAM_AUCTION_BONUS);
					LOG_CHECK_ERROR(nRetCode);
				}
			}

			nRetCode = CGameWorld::GetInstance().SendItemMail(poAuctionItem->dwWinnerID, mtiTeamAuctionSendItemtoWinner, poAuctionItem->poItem, ITEMLOG_TEAM_AUCTION, poAuctionItem->dwCurrentPrice);
			LOG_CHECK_ERROR(nRetCode);
		}
		else
		{
			// auction failed:
			nRetCode = CGameWorld::GetInstance().SendItemMail(m_dwLeader, mtiTeamAuctionSendItemtoLeader, poAuctionItem->poItem, ITEMLOG_TEAM_AUCTION_FAILED);
			LOG_CHECK_ERROR(nRetCode);
		}

		for (TeamAuctionItem::TDepositeMap::iterator itr = poAuctionItem->DepositeMap.begin(); itr != poAuctionItem->DepositeMap.end(); ++itr)
		{
			nRetCode = CGameWorld::GetInstance().SendMoneyMail(itr->first, mtiTeamAuctionReturnDeposite, MONEYTYPE_02, itr->second, MONEYLOG_TEAM_AUCTION_RETURN);
			LOG_CHECK_ERROR(nRetCode);
		}

		poAuctionItem->DepositeMap.clear();

		DBG("--- Auction End index: %u", poAuctionItem->dwIndex);

#ifndef _ROBOT
		nRetCode = CCliMessageHandler::GetInstance().DoTeamAuctionEnd(this, poAuctionItem, dwTax);
		LOG_CHECK_ERROR(nRetCode);
#endif

		// Remove the first entry
		m_AuctionItemList.pop_front();
		CGameWorld::GetInstance().DelTeamAutionItem(poAuctionItem);
	}

Exit1:
	return TRUE;
Exit0:
	if (poAuctionItem)
		poAuctionItem->dwWinnerID = 0;
	return FALSE;
}

BOOL CTeamInGS::AddNewMember(UINT32 dwMemberID, char* szRoleName, INT32 nLevel, INT32 nSex, INT32 nClass)
{
	INT32 nRetCode = 0;
	CRole* poRole = NULL;

	LOG_PROCESS_ERROR(szRoleName);

	for (INT32 i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if (m_MemberTable[i].dwRoleID == 0)
		{
			m_MemberTable[i].dwRoleID = dwMemberID;
			strxcpy(m_MemberTable[i].szRoleName, szRoleName, ROLE_NAME_LEN);
			m_MemberTable[i].nClass = nClass;
			m_MemberTable[i].nLevel = nLevel;
			m_MemberTable[i].nSex = nSex;
			m_MemberTable[i].eBidState = etbsInvalid;
			m_nMemberCount++;

			break;
		}
	}

	poRole = CGameWorld::GetInstance().FindValidRole(dwMemberID);
	if (poRole == NULL)
		return TRUE;

	poRole->SetTeamID(m_dwTeamID);

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoClientSyncRoleTeam(poRole);
	LOG_PROCESS_ERROR(nRetCode);
#endif  // _ROBOT

	poRole->GetAchievementList().AddVariable(avdJoinTeamCount, 1);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CTeamInGS::RemoveMember(UINT32 dwMemberID)
{
	INT32 nRetCode = 0;

	for (INT32 i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if (m_MemberTable[i].dwRoleID == dwMemberID)
		{
			memset(&m_MemberTable[i], 0, sizeof(TeamMember));
			m_nMemberCount--;

			CRole* poRole = CGameWorld::GetInstance().FindRole(dwMemberID);
			if (poRole)
			{
				poRole->SetTeamID(0);

#ifndef _ROBOT
				nRetCode = CCliMessageHandler::GetInstance().DoClientSyncRoleTeam(poRole);
				LOG_CHECK_ERROR(nRetCode);
#endif // _ROBOT
			}
			break;
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CTeamInGS::AddAuctionItem(CDrop* poDrop)
{
	INT32 nRetCode = 0;
	TeamAuctionItem* poAuctionItem = NULL;

	LOG_PROCESS_ERROR(poDrop);
	LOG_PROCESS_ERROR(poDrop->GetScene());
	LOG_PROCESS_ERROR(poDrop->m_content.m_type == DropContent::DROP_ITEM);
	LOG_PROCESS_ERROR(poDrop->m_content.m_item);

	poAuctionItem = CGameWorld::GetInstance().NewTeamAuctionItem();
	LOG_PROCESS_ERROR(poAuctionItem);

	poAuctionItem->BidRoleList.clear();
	poAuctionItem->RewardRoleList.clear();
	poAuctionItem->dwWinnerID = 0;
	poAuctionItem->poItem = poDrop->m_content.m_item;
	poAuctionItem->dwIndex = m_dwAuctionItemIndex++;    // Assign the auction index, starting at 1
	poAuctionItem->poScene = poDrop->GetScene();
	poAuctionItem->bInBidding = FALSE;
	poAuctionItem->dwEndFrm = 0;

	while (TRUE)
	{
		UINT32 dwOwnerID = poDrop->PopOwner();
		if (dwOwnerID == INVALID_OBJECT_ID)
			break;

		poAuctionItem->RewardRoleList.push_back(dwOwnerID);
	}

	for (INT32 i = 0; i < MAX_TEAM_MEMBER_COUNT; i++)
	{
		CRole* poRole = CGameWorld::GetInstance().FindValidRole(m_MemberTable[i].dwRoleID);
		if (poRole == NULL)
			continue;

		if (poRole->GetScene() == poDrop->GetScene())
			poAuctionItem->BidRoleList.push_back(m_MemberTable[i].dwRoleID);
	}

	poAuctionItem->dwCurrentPrice = poAuctionItem->poItem->m_pTemplate->m_nSellPrice;

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoTeamAuctionAddItem(this, poAuctionItem);
	LOG_CHECK_ERROR(nRetCode);
#endif

	DBG("AddAuctionItem itemid: %d, index: %u", poAuctionItem->poItem->m_iteminfo.m_nTemplateID, poAuctionItem->dwIndex);

	m_AuctionItemList.push_back(poAuctionItem);

	return TRUE;
Exit0:
	if (poAuctionItem)
		CGameWorld::GetInstance().DelTeamAutionItem(poAuctionItem);

	return FALSE;
}

INT32 CTeamInGS::DelAuctionItem(TeamAuctionItem* poAuctionItem)
{
	return TRUE;
Exit0:
	return FALSE;
}

INT32 CTeamInGS::CanBeAddedtoBidAuction(Item* pItem)
{
	LOG_PROCESS_ERROR(pItem);
	PROCESS_ERROR(m_eAssignType == etaTeamAuction);
	PROCESS_ERROR(pItem->m_pTemplate->m_byColor >= GetAuctionItemColorLimit());
	PROCESS_ERROR(pItem->m_pTemplate->m_bTeamAuction);

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CTeamInGS::Bid(CRole* poRole, UINT32 dwAuctionIndex, UINT32 dwOfferPrice)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	TeamAuctionItem* poAuctionItem = NULL;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(!m_AuctionItemList.empty());

	poAuctionItem = *(m_AuctionItemList.begin());
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->dwIndex = dwAuctionIndex);

	nResult = _CanBid(poRole, poAuctionItem, dwOfferPrice);
	PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	nResult = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, dwOfferPrice, MONEYLOG_TEAM_AUCTION_DEPOSITE, 0);
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	nRetCode = _AddDeposite(poAuctionItem, poRole->GetObjID(), dwOfferPrice);
	LOG_PROCESS_ERROR(nRetCode);

	poAuctionItem->dwEndFrm = CGameWorld::GetInstance().GetGameFrame() + CONVERT_TIME(g_GWConfig.nTeamAuctionTimeout);

	poAuctionItem->dwCurrentPrice = dwOfferPrice;
	poAuctionItem->dwWinnerID = poRole->GetObjID();

	DBG("Bid index: %u, roleid: %u, offerprice: %u", poAuctionItem->dwIndex, poRole->GetObjID(), dwOfferPrice);

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoTeamAuctionNotify(this, poAuctionItem);
	LOG_CHECK_ERROR(nRetCode);
#endif

	return errSuccess;
Exit0:
	return nResult;
}

INT32 CTeamInGS::BidAbandon(CRole* poRole, UINT32 dwAuctionIndex)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	TeamAuctionItem* poAuctionItem = NULL;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(!m_AuctionItemList.empty());

	for (TAuctionItemList::iterator itr = m_AuctionItemList.begin(); itr != m_AuctionItemList.end(); ++itr)
	{
		TeamAuctionItem* m = *itr;

		if (m->dwIndex == dwAuctionIndex)
		{
			poAuctionItem = m;
			break;
		}
	}

	LOG_PROCESS_ERROR(poAuctionItem);

	for (TeamAuctionItem::TIDList::iterator itr = poAuctionItem->BidRoleList.begin(); itr != poAuctionItem->BidRoleList.end(); ++itr)
	{
		if (*itr == poRole->GetObjID())
		{
			poAuctionItem->BidRoleList.erase(itr);
			break;
		}
	}

	DBG("Bid abandon index: %u, roleid: %u", poAuctionItem->dwIndex, poRole->GetObjID());

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoTeamAuctionAbandon(this, poAuctionItem, poRole->GetObjID());
	LOG_CHECK_ERROR(nRetCode);
#endif

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CTeamInGS::_CanBid(CRole* poRole, TeamAuctionItem* poAuctionItem, UINT32 dwOfferPrice)
{
	INT32 nResult = errUnknownError;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poAuctionItem);

	LOG_PROCESS_ERROR(poAuctionItem->poItem);
	PROCESS_ERROR_RET_CODE(poAuctionItem->bInBidding, errTeamAuctionNotBegin);

	if (poAuctionItem->dwWinnerID != 0)
		PROCESS_ERROR_RET_CODE(dwOfferPrice > poAuctionItem->dwCurrentPrice + poAuctionItem->dwCurrentPrice / 100 + 1, errTeamAuctionBidTooLow);

	PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= dwOfferPrice, errTeamAuctionNotEnoughMoney);

	for (TeamAuctionItem::TIDList::iterator itr = poAuctionItem->BidRoleList.begin(); itr != poAuctionItem->BidRoleList.end(); ++itr)
	{
		if (*itr == poRole->GetObjID())
			return errSuccess;
	}

Exit0:
	return nResult;
}

BOOL CTeamInGS::HasMasterRelationShip(CRole* poRole, INT64 llDist2)
{
	for (INT32 nMemberIndex = 0; nMemberIndex < GetMaxMemberCount(); nMemberIndex++)
	{
		CRole* poTeamMember = CGameWorld::GetInstance().FindValidRole(GetMemberTable(nMemberIndex).dwRoleID);

		if (poTeamMember && poTeamMember->GetScene() == poRole->GetScene())
		{
			if (poRole->GetDistance3D(poTeamMember) <= llDist2)
			{
				PROCESS_SUCCESS(poRole->IsMasterRelationship(poTeamMember));
			}
		}
	}

	return FALSE;
Exit1:
	return TRUE;
}

BOOL CTeamInGS::_AddDeposite(TeamAuctionItem* poItem, UINT32 dwRoleID, UINT32 dwDeposite)
{
	INT32 nRetCode = 0;
	TeamAuctionItem::TDepositeMap::iterator itr;

	LOG_PROCESS_ERROR(poItem);

	itr = poItem->DepositeMap.find(dwRoleID);
	if (itr != poItem->DepositeMap.end())
	{
		itr->second += dwDeposite;
	}
	else
	{
		nRetCode = poItem->DepositeMap.insert(std::make_pair(dwRoleID, dwDeposite)).second;
		LOG_PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}
