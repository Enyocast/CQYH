#include "stdafx.h"
#include "message_handler.h"
#include "external_message_header.h"

#include "g2m_message.h"
#include "g2c_message.h"

#include "imessage_notifier.h"
#include "game_world.h"
#include "team.h"

#include <set>

#ifndef _ROBOT

using namespace ExternalMessage;

BOOL CCliMessageHandler::DoMSTeamSyncMember(CRole* poRole)
{
    INT32 nRetCode = 0;

    InternalMessage::G2M_TEAM_SYNC_MEMBER* pMsg = (InternalMessage::G2M_TEAM_SYNC_MEMBER*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_TEAM_SYNC_MEMBER));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = InternalMessage::g2m_team_sync_member;
    pMsg->dwRoleID = poRole->GetObjID();
    pMsg->nCurHp = poRole->GetHp();
    pMsg->nCurMp = poRole->GetMp();
    pMsg->nMaxHp = poRole->GetAttrList().GetAttr(catMaxHp);
    pMsg->nMaxMp = poRole->GetAttrList().GetAttr(catMaxMp);
    pMsg->nLevel = poRole->GetLevel();
	pMsg->nX = (INT32)poRole->GetX();
	pMsg->nY = (INT32)poRole->GetY();
	pMsg->nZ = (INT32)poRole->GetZ();

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_TEAM_SYNC_MEMBER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoClientTeamSyncMember(CRole* poRole)
{
	INT32 nRetCode = 0;

	G2C_TEAM_SYNC_MEMBER* pMsg = (G2C_TEAM_SYNC_MEMBER*)m_poPacketAllocator->Alloc(sizeof(G2C_TEAM_SYNC_MEMBER));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2c_team_sync_member;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->nCurHp = poRole->GetHp();
	pMsg->nCurMp = poRole->GetMp();
	pMsg->nMaxHp = poRole->GetAttrList().GetAttr(catMaxHp);
	pMsg->nMaxMp = poRole->GetAttrList().GetAttr(catMaxMp);
	pMsg->nLevel = poRole->GetLevel();
	pMsg->wX = ConvertCoordS2N(poRole->GetX());
	pMsg->wY = ConvertCoordS2N(poRole->GetY());
	pMsg->wZ = ConvertCoordS2N(poRole->GetZ());

	nRetCode = _BroadcastTeamToSameSceneMember(poRole, (PACKET_BUFFER*)pMsg, sizeof(G2C_TEAM_SYNC_MEMBER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoTeamAuctionAddItem(CTeamInGS* poTeam, TeamAuctionItem* poAuctionItem)
{
	INT32 nRetCode = 0;
	G2C_TEAM_AUCTION_ADD_ITEM* pMsg = NULL;

	LOG_PROCESS_ERROR(poTeam);
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->poScene);
	LOG_PROCESS_ERROR(poAuctionItem->poItem);

	pMsg = (G2C_TEAM_AUCTION_ADD_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_team_auction_add_item;
	pMsg->dwAuctionIndex = poAuctionItem->dwIndex;
	pMsg->wSize = sizeof(G2C_TEAM_AUCTION_ADD_ITEM) + poAuctionItem->poItem->m_iteminfo.Save(pMsg->acItemInfo);	

	nRetCode = _BroadcastTeamToInSceneMember(poTeam, poAuctionItem->poScene, (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoTeamAuctionBegin(CTeamInGS* poTeam, TeamAuctionItem* poAuctionItem)
{
	INT32 nRetCode = 0;
	G2C_TEAM_AUCTION_BEGIN* pMsg = NULL;

	LOG_PROCESS_ERROR(poTeam);
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->poScene);

	pMsg = (G2C_TEAM_AUCTION_BEGIN*)m_poPacketAllocator->Alloc(sizeof(G2C_TEAM_AUCTION_BEGIN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_team_auction_begin;
	pMsg->dwAuctionIndex = poAuctionItem->dwIndex;
	pMsg->byBidderCount = poAuctionItem->BidRoleList.size();
	pMsg->dwBottomPrice = poAuctionItem->dwCurrentPrice;
	pMsg->dwRemainTime = g_GWConfig.nTeamAuctionTimeout;

	nRetCode = _BroadcastTeamToInSceneMember(poTeam, poAuctionItem->poScene, (PACKET_BUFFER*)pMsg, sizeof(G2C_TEAM_AUCTION_BEGIN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoTeamAuctionEnd(CTeamInGS* poTeam, TeamAuctionItem* poAuctionItem, UINT32 dwTax)
{
	INT32 nRetCode = 0;
	G2C_TEAM_AUCTION_END* pMsg = NULL;

	LOG_PROCESS_ERROR(poTeam);
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->poScene);

	pMsg = (G2C_TEAM_AUCTION_END*)m_poPacketAllocator->Alloc(sizeof(G2C_TEAM_AUCTION_END));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_team_auction_end;
	pMsg->dwAuctionIndex = poAuctionItem->dwIndex;
	pMsg->dwWinnerRoleID = poAuctionItem->dwWinnerID;
	pMsg->dwTax = dwTax;

	nRetCode = _BroadcastTeamToInSceneMember(poTeam, poAuctionItem->poScene, (PACKET_BUFFER*)pMsg, sizeof(G2C_TEAM_AUCTION_END));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoTeamAuctionAbandon(CTeamInGS* poTeam, TeamAuctionItem* poAuctionItem, UINT32 dwBidderID)
{
	INT32 nRetCode = 0;
	G2C_TEAM_AUCTION_ABANDON* pMsg = NULL;

	LOG_PROCESS_ERROR(poTeam);
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->poScene);

	pMsg = (G2C_TEAM_AUCTION_ABANDON*)m_poPacketAllocator->Alloc(sizeof(G2C_TEAM_AUCTION_ABANDON));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_team_auction_abandon;
	pMsg->dwRoleID = dwBidderID;
	pMsg->dwAuctionIndex = poAuctionItem->dwIndex;

	nRetCode = _BroadcastTeamToInSceneMember(poTeam, poAuctionItem->poScene, (PACKET_BUFFER*)pMsg, sizeof(G2C_TEAM_AUCTION_ABANDON));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoTeamAuctionNotify(CTeamInGS* poTeam, TeamAuctionItem* poAuctionItem)
{
	INT32 nRetCode = 0;
	G2C_TEAM_AUCTION_NOTIFY* pMsg = NULL;

	LOG_PROCESS_ERROR(poTeam);
	LOG_PROCESS_ERROR(poAuctionItem);
	LOG_PROCESS_ERROR(poAuctionItem->poScene);

	pMsg = (G2C_TEAM_AUCTION_NOTIFY*)m_poPacketAllocator->Alloc(sizeof(G2C_TEAM_AUCTION_NOTIFY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_team_auction_notify;
	pMsg->dwBidderRoleID = poAuctionItem->dwWinnerID;
	pMsg->dwAuctionIndex = poAuctionItem->dwIndex;
	pMsg->dwOfferPrice = poAuctionItem->dwCurrentPrice;
	pMsg->dwRemainTime = g_GWConfig.nTeamAuctionTimeout;

	nRetCode = _BroadcastTeamToInSceneMember(poTeam, poAuctionItem->poScene, (PACKET_BUFFER*)pMsg, sizeof(G2C_TEAM_AUCTION_NOTIFY));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoMSLeaveTeam(CRole* poRole)
{
    INT32 nRetCode = 0;

    InternalMessage::G2M_LEAVE_TEAM* pMsg = (InternalMessage::G2M_LEAVE_TEAM*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_LEAVE_TEAM));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = InternalMessage::g2m_leave_team;
    pMsg->dwRoleID = poRole->GetObjID();

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_LEAVE_TEAM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSClearTeamDungeon(CRole* poRole)
{
    INT32 nRetCode = 0;

    InternalMessage::G2M_CLEAR_TEAM_DUNGEON* pMsg = (InternalMessage::G2M_CLEAR_TEAM_DUNGEON*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_CLEAR_TEAM_DUNGEON));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = InternalMessage::g2m_clear_team_dungeon;
    pMsg->dwRoleID = poRole->GetObjID();

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_CLEAR_TEAM_DUNGEON));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

//BOOL CCliMessageHandler::DoClientSyncTeamInfo(CRole* poRole)
//{
//    INT32 nRetCode = 0;
//    GS_TEAM* pstTeam = NULL;
//    LOG_PROCESS_ERROR(poRole);
//    PROCESS_SUCCESS(poRole->GetTeamID() == 0);
//    
//    pstTeam = CGameWorld::GetInstance().FindTeam(poRole->GetTeamID());
//    if(pstTeam == NULL)
//    {
//        poRole->SetTeamID(0);
//        PROCESS_SUCCESS(TRUE);
//    }
//
//    INT32 nSize = sizeof(G2C_SYNC_TEAMINFO) + pstTeam->nMemberCount * sizeof(GS_TEAM_MEMBER);
//    G2C_SYNC_TEAMINFO* pMsg = (G2C_SYNC_TEAMINFO*)m_poPacketAllocator->Alloc(nSize);
//    LOG_PROCESS_ERROR(pMsg);
//
//    pMsg->wMsg = g2c_sync_teaminfo;
//    pMsg->wSize = nSize;
//    pMsg->dwLeader = pstTeam->dwLeader;
//    pMsg->dwRoomID = pstTeam->dwRoomID;
//    pMsg->dwTeamID = pstTeam->dwTeamID;
//    strxcpy(pMsg->szTeamName, pstTeam->szTeamName, TEAM_NAME_LEN);
//    pMsg->byAssignType = pstTeam->byAssignType;
//    pMsg->nMaxMemberCount = pstTeam->nMaxMemberCount;
//    pMsg->nMemberCount = 0;
//
//    for(INT32 i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
//    {
//        if(pstTeam->MemberTable[i].dwRoleID != 0)
//        {
//            pMsg->stMemberTable[pMsg->nMemberCount].dwRoleID = pstTeam->MemberTable[i].dwRoleID;
//            pMsg->stMemberTable[pMsg->nMemberCount].btLevel = pstTeam->MemberTable[i].btLevel;
//            pMsg->stMemberTable[pMsg->nMemberCount].btClass = pstTeam->MemberTable[i].btClass;
//            pMsg->stMemberTable[pMsg->nMemberCount].btSex = pstTeam->MemberTable[i].btSex;
//            strxcpy(pMsg->stMemberTable[pMsg->nMemberCount++].szRoleName, pstTeam->MemberTable[i].szRoleName, ROLE_NAME_LEN);
//        }
//    }
//    LOG_PROCESS_ERROR(pMsg->nMemberCount == pstTeam->nMemberCount);
//
//    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
//    LOG_PROCESS_ERROR(nRetCode);
//Exit1:
//    return TRUE;
//Exit0:
//    return FALSE;
//}

struct CTraverseNoTeamRole
{
    G2C_SYNC_ADJACENT_ROLE_NOTEAM* pstRoleNoTeam;
    BOOL operator()(CRole* poRole)
    {
        LOG_PROCESS_ERROR(poRole);
        PROCESS_SUCCESS(pstRoleNoTeam->byCount == MAX_ADJACENT_ROLE_NOTEAM_COUNT);
        {
            if(poRole->GetTeamID() == 0)
            {
                pstRoleNoTeam->stRoleList[pstRoleNoTeam->byCount].dwRoleID = poRole->GetObjID();
                pstRoleNoTeam->stRoleList[pstRoleNoTeam->byCount].btSex = poRole->GetSex();
                pstRoleNoTeam->stRoleList[pstRoleNoTeam->byCount].btClass = poRole->GetClass();
                strxcpy(pstRoleNoTeam->stRoleList[pstRoleNoTeam->byCount].szRoleName, poRole->GetName(), ROLE_NAME_LEN);
                pstRoleNoTeam->byCount++;
            }
        }
Exit1:
        return TRUE;
Exit0:
        return FALSE;
    }
};

struct CTraverseAdjacentNoTeamRole
{
    G2C_SYNC_ADJACENT_ROLE_NOTEAM* pstRoleNoTeam;

    BOOL operator()(CRegion* poRegion)
    {
        INT32 nRetCode = 0;
        LOG_PROCESS_ERROR(poRegion);
        {
            CTraverseNoTeamRole stTraverseNoTeamRole;
            stTraverseNoTeamRole.pstRoleNoTeam = pstRoleNoTeam;
            
            nRetCode = poRegion->TraverseRole(stTraverseNoTeamRole);
            LOG_CHECK_ERROR(nRetCode);
        }
Exit1:
        return TRUE;
Exit0:
        return FALSE;
    }
};

struct CTraverseRegionTeam
{
    std::set<UINT32>* pSetTeamID;

    BOOL operator()(CRole* poRole)
    {
        LOG_PROCESS_ERROR(poRole);
        LOG_PROCESS_ERROR(pSetTeamID);
        {
            if(poRole->GetTeamID() > 0)
            {
                pSetTeamID->insert(poRole->GetTeamID());
            }
        }

        return TRUE;
Exit0:
        return FALSE;
    }
};

struct CTraverseAdjacentTeam
{
    CTraverseRegionTeam stTraverseRegionTeam;
    std::set<UINT32>* pSetTeamID;
    
    BOOL operator()(CRegion* poRegion)
    {
        INT32 nRetCode = 0;
        LOG_PROCESS_ERROR(poRegion);
        {
            stTraverseRegionTeam.pSetTeamID = pSetTeamID;
            nRetCode = poRegion->TraverseRole(stTraverseRegionTeam);
            LOG_CHECK_ERROR(nRetCode);
        }
        return TRUE;
Exit0:
        return FALSE;
    }
};

BOOL CCliMessageHandler::DoClientSyncAdjacentRoleNoTeam(CRole* poRole)
{
    INT32 nRetCode = 0;
    CRegion* poRegion;
    G2C_SYNC_ADJACENT_ROLE_NOTEAM* pMsg = NULL;
    CTraverseAdjacentNoTeamRole stTraverseAdjacentNoTeamRole;

    LOG_PROCESS_ERROR(poRole);
    poRegion = poRole->GetRegion();
    LOG_PROCESS_ERROR(poRegion);
    
    pMsg = (G2C_SYNC_ADJACENT_ROLE_NOTEAM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_adjacent_role_noteam;
    pMsg->byCount = 0;

    stTraverseAdjacentNoTeamRole.pstRoleNoTeam = pMsg;
    nRetCode = poRegion->Traverse9Region(stTraverseAdjacentNoTeamRole);
    LOG_PROCESS_ERROR(nRetCode);

    pMsg->wSize = sizeof(G2C_SYNC_ADJACENT_ROLE_NOTEAM) + pMsg->byCount * sizeof(ADJACENT_ROLE);

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if(pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoClientSyncAdjacentTeam(CRole* poRole)
{
    INT32 nRetCode = 0;
    CRegion* poRegion;
    G2C_SYNC_ADJACENT_TEAM* pMsg = NULL;
    std::set<UINT32> setTeamID;
    CTraverseAdjacentTeam stTraverseAdjacentTeam;
    CTeamInGS* pstTeam = NULL;
    LOG_PROCESS_ERROR(poRole);

    poRegion = poRole->GetRegion();
    LOG_PROCESS_ERROR(poRegion);

    pMsg = (G2C_SYNC_ADJACENT_TEAM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_adjacent_team;
    pMsg->byCount = 0;

    stTraverseAdjacentTeam.pSetTeamID = &setTeamID;
    nRetCode = poRegion->Traverse9Region(stTraverseAdjacentTeam);
    LOG_PROCESS_ERROR(nRetCode);
    
    for(std::set<UINT32>::iterator itr = setTeamID.begin(); itr != setTeamID.end(); ++itr)
    {
        pstTeam = CGameWorld::GetInstance().FindTeam(*itr);
        if(!pstTeam || !(pstTeam->GetLeaderID()) || !(pstTeam->GetMemberCount()))
            continue;

        TeamMember* pstLeader = NULL;
        for(INT32 i = 0; i < pstTeam->GetMaxMemberCount(); ++i)
        {
            if(pstTeam->GetMemberTable(i).dwRoleID == pstTeam->GetLeaderID())
            {
                pstLeader = &pstTeam->GetMemberTable(i);
                break;
            }
        }
        if(!pstLeader)
            continue;

        pMsg->stTeamList[pMsg->byCount].dwTeamID = pstTeam->GetTeamID();
        pMsg->stTeamList[pMsg->byCount].btCaptainClass = pstLeader->nClass;
        pMsg->stTeamList[pMsg->byCount].btCaptainLevel = pstLeader->nLevel;
        strxcpy(pMsg->stTeamList[pMsg->byCount].szTeamName, pstTeam->GetTeamName(), TEAM_NAME_LEN);
		if (g_GWConfig.bFilterCensoredWord)
		{
			nRetCode = CGameWorld::GetInstance().ReplaceCensoredWord(pMsg->stTeamList[pMsg->byCount].szTeamName);
			LOG_CHECK_ERROR(nRetCode);
		}
        strxcpy(pMsg->stTeamList[pMsg->byCount].szCaptainName, pstLeader->szRoleName, ROLE_NAME_LEN);
        pMsg->stTeamList[pMsg->byCount].dwCaptainID = pstLeader->dwRoleID;
        pMsg->stTeamList[pMsg->byCount].btMaxCount = pstTeam->GetMaxMemberCount();
        pMsg->stTeamList[pMsg->byCount].btMemberCount = pstTeam->GetMemberCount();
		pMsg->stTeamList[pMsg->byCount].btActivityType = (UINT8)pstTeam->GetActivityType();
		pMsg->stTeamList[pMsg->byCount].dwActivityID = pstTeam->GetActivityID();

        pMsg->byCount++;

        if(pMsg->byCount == MAX_ADJACENT_TEAM_COUNT)
            break;
    }
    pMsg->wSize = sizeof(G2C_SYNC_ADJACENT_TEAM) + pMsg->byCount * sizeof(ADJACENT_TEAM_ITEM);

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if(pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

void CCliMessageHandler::OnAdjacentRoleNoTeam(CRole* pRole, const char* pData)
{
    INT32 nRetCode = 0;
    UINT32 dwFrame = CGameWorld::GetInstance().GetGameFrame();
    LOG_PROCESS_ERROR(pRole);
    
    if(pRole->GetLastAdjacentNoTeamRoleFrame() + (g_GWConfig.nAdjacentDataTimeLimit * GAME_FPS / 1000) > dwFrame)
	{
		pRole->ErrorCodeNotify(errAdjacentDataTimeLimit, 0, 0);
		PROCESS_ERROR(FALSE);
	}

    nRetCode = DoClientSyncAdjacentRoleNoTeam(pRole);
    LOG_PROCESS_ERROR(nRetCode);
    
    pRole->SetLastAdjacentNoTeamRoleFrame(dwFrame);

Exit0:
    return;
}

void CCliMessageHandler::OnAdjacentTeam(CRole* pRole, const char* pData)
{
    INT32 nRetCode = 0;
    UINT32 dwFrame = CGameWorld::GetInstance().GetGameFrame();
    LOG_PROCESS_ERROR(pRole);

    if(pRole->GetLastAdjacentTeamFrame() + (g_GWConfig.nAdjacentDataTimeLimit * GAME_FPS / 1000) > dwFrame)
	{
		pRole->ErrorCodeNotify(errAdjacentDataTimeLimit, 0, 0);
		PROCESS_ERROR(FALSE);
	}

    nRetCode = DoClientSyncAdjacentTeam(pRole);
    LOG_PROCESS_ERROR(nRetCode);

    pRole->SetLastAdjacentTeamFrame(dwFrame);
Exit0:
    return;
}

void CCliMessageHandler::OnTeamAuctionBid(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;

	CTeamInGS* pTeam = NULL;
	C2G_TEAM_AUCTION_BID* pMsg = NULL;

	pMsg = (C2G_TEAM_AUCTION_BID*) pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);
	
	pTeam = CGameWorld::GetInstance().FindTeam(poRole->GetTeamID());
	LOG_PROCESS_ERROR(pTeam);

	nRetCode = pTeam->Bid(poRole, pMsg->dwAuctionIndex, pMsg->dwOfferPrice);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

	return;
Exit0:
	if (nResult != errUnknownError)
	{
		poRole->ErrorCodeNotify(nResult, 0, 0);
	}

	return;
}

void CCliMessageHandler::OnTeamAuctionAbandon(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* pTeam = NULL;
	C2G_TEAM_AUCTION_ABANDON* pMsg = NULL;

	pMsg = (C2G_TEAM_AUCTION_ABANDON*) pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pTeam = CGameWorld::GetInstance().FindTeam(poRole->GetTeamID());
	LOG_PROCESS_ERROR(pTeam);

	nRetCode = pTeam->BidAbandon(poRole, pMsg->dwAuctionIndex);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;	
}

BOOL CCliMessageHandler::DoClientSyncRoleTeam(CRole* poRole)
{
    INT32 nRetCode = 0;

    G2C_SYNC_ROLE_TEAM* pMsg = (G2C_SYNC_ROLE_TEAM*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_ROLE_TEAM));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_sync_role_team;
    pMsg->dwRoleID = poRole->GetObjID();
    pMsg->dwTeamID = poRole->GetTeamID();

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_ROLE_TEAM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSUpdateRoleInfo(CRole* poRole)
{
	INT32 nRetCode = 0;
    InternalMessage::G2M_UPDATE_ROLE_INFO* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

	pMsg = (InternalMessage::G2M_UPDATE_ROLE_INFO*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_UPDATE_ROLE_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = InternalMessage::g2m_update_role_info;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->byLevel = (UINT8)poRole->GetLevel();
    pMsg->byVIPLevel = poRole->GetVIPLevel();

	nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_UPDATE_ROLE_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoClientBattleTeamJoin(CRole* poRole, CTeamInGS* pstBattleTeam)
{
	INT32 nRetCode = 0;
	INT32 nSize = 0;
    G2C_BATTLE_TEAM_JOIN* pMsg = NULL;

    LOG_PROCESS_ERROR(pstBattleTeam);

	nSize = sizeof(G2C_BATTLE_TEAM_JOIN) + sizeof(GS_TEAM_MEMBER_BASEINFO) * pstBattleTeam->GetMemberCount();

    pMsg = (G2C_BATTLE_TEAM_JOIN*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_battle_team_join;
	pMsg->wSize = nSize;
	pMsg->dwBattleTeamID = pstBattleTeam->GetTeamID();
	pMsg->byMemberCount = 0;
	
	for(INT32 i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if(pstBattleTeam->GetMemberTable(i).dwRoleID > 0)
		{
			pMsg->lstRoleMember[pMsg->byMemberCount].dwRoleID = pstBattleTeam->GetMemberTable(i).dwRoleID;
			pMsg->lstRoleMember[pMsg->byMemberCount].byClass = pstBattleTeam->GetMemberTable(i).nClass;
			pMsg->lstRoleMember[pMsg->byMemberCount].bySex = pstBattleTeam->GetMemberTable(i).nSex;
			pMsg->lstRoleMember[pMsg->byMemberCount].byLevel = pstBattleTeam->GetMemberTable(i).nLevel;
			strxcpy(pMsg->lstRoleMember[pMsg->byMemberCount].szRoleName, pstBattleTeam->GetMemberTable(i).szRoleName, ROLE_NAME_LEN);
			pMsg->byMemberCount++;
		}
	}
	
	LOG_PROCESS_ERROR(pMsg->byMemberCount == pstBattleTeam->GetMemberCount());
	
	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoClientBattleTeamAdd(CTeamInGS* pstBattleTeam, CRole* poNewMember)
{
	INT32 nRetCode = 0;

	G2C_BATTLE_TEAM_ADD* pMsg = (G2C_BATTLE_TEAM_ADD*)m_poPacketAllocator->Alloc(sizeof(G2C_BATTLE_TEAM_ADD));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poNewMember);

	pMsg->wMsg = g2c_battle_team_add;
	pMsg->dwBattleTeamID = pstBattleTeam->GetTeamID();
	pMsg->stMember.dwRoleID = poNewMember->GetObjID();
	pMsg->stMember.byClass = poNewMember->GetClass();
	pMsg->stMember.byLevel = poNewMember->GetLevel();
	pMsg->stMember.bySex = poNewMember->GetSex();
	strxcpy(pMsg->stMember.szRoleName, poNewMember->GetName(), ROLE_NAME_LEN);

	nRetCode = _BroadcastTeam(pstBattleTeam, (PACKET_BUFFER*)pMsg,  sizeof(G2C_BATTLE_TEAM_ADD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoClientBattleTeamRemove(CTeamInGS* pstBattleTeam, UINT32 dwRemoveMemberID)
{
	INT32 nRetCode = 0;

	G2C_BATTLE_TEAM_REMOVE* pMsg = (G2C_BATTLE_TEAM_REMOVE*)m_poPacketAllocator->Alloc(sizeof(G2C_BATTLE_TEAM_REMOVE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_battle_team_remove;
	pMsg->dwBattleTeamID = pstBattleTeam->GetTeamID();
	pMsg->dwRoleID = dwRemoveMemberID;

	nRetCode = _BroadcastTeam(pstBattleTeam, (PACKET_BUFFER*)pMsg,  sizeof(G2C_BATTLE_TEAM_REMOVE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoClientBattleTeamLeaderChange(CTeamInGS* pstBattleTeam, UINT32 dwNewLeaderID)
{
	INT32 nRetCode = 0;

	G2C_BATTLE_TEAM_CHANGE_LEADER* pMsg = (G2C_BATTLE_TEAM_CHANGE_LEADER*)m_poPacketAllocator->Alloc(sizeof(G2C_BATTLE_TEAM_CHANGE_LEADER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_battle_team_change_leader;
	pMsg->dwNewLeader = dwNewLeaderID;

	nRetCode = _BroadcastTeam(pstBattleTeam, (PACKET_BUFFER*)pMsg,  sizeof(G2C_BATTLE_TEAM_CHANGE_LEADER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

#endif
