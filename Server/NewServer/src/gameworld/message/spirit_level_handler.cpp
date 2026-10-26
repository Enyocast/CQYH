#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "game_world.h"

#ifndef _ROBOT

using namespace ExternalMessage;   

void CCliMessageHandler::OnSpiritExpChange(CRole *poRole, const char *pData)
{
	INT32 err = 0;
	INT32 nResult = errUnknownError;

    C2G_SPIRIT_EXP_CHANGE* pMsg = (C2G_SPIRIT_EXP_CHANGE*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	err = poRole->GetSpirit().ChangeSoul2Pts(pMsg->bUseMoney, pMsg->bIsOnline);
	LOG_PROCESS_ERROR_RET_CODE(err == errSuccess, err);

	return;
Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;
}

void CCliMessageHandler::OnSpiritAddAir(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_ADD_AIR* pMsg = (C2G_SPIRIT_ADD_AIR*)pData;
	LOG_PROCESS_ERROR(pMsg);

	if (pMsg->bQuick)
	{
		while(1)
		{
			nResult = poRole->GetSpirit().AddAir();
			if (nResult != errSuccess)
			{
				break;
			}
		}
	}
	else
	{
		nResult = poRole->GetSpirit().AddAir();
		LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);	
	}
	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;
}

void CCliMessageHandler::OnSpiritMergeAir(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_MERGE_AIR* pMsg = (C2G_SPIRIT_MERGE_AIR*)pData;
	LOG_PROCESS_ERROR(pMsg);

	nResult = poRole->GetSpirit().MergeAir(pMsg->nSrcCon);
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);	

	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;
}

void CCliMessageHandler::OnSpiritMoveAir(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_MOVE_AIR* pMsg = (C2G_SPIRIT_MOVE_AIR*)pData;
	LOG_PROCESS_ERROR(pMsg);

	nResult = poRole->GetSpirit().MoveAir(pMsg->nSrcBagType, pMsg->nSrcIndex, pMsg->nTarBagType, pMsg->nTarIndex);
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;
}

void CCliMessageHandler::OnSpiritExchangeAir(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_EXCHANGE_AIR* pMsg = (C2G_SPIRIT_EXCHANGE_AIR*)pData;
	LOG_PROCESS_ERROR(pMsg);

 	nResult = poRole->GetSpirit().ExchangeAir(pMsg->wAirID);
 	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;	
}

void CCliMessageHandler::OnSpiritBuySlot(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_BUY_AIR_SLOT* pMsg = (C2G_SPIRIT_BUY_AIR_SLOT*)pData;
	LOG_PROCESS_ERROR(pMsg);

	LOG_PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= MAX_SPIRIT_BUY_SLOT_COST, errNotEnoughMoney);

	nResult = poRole->GetSpirit().AddSlot(pMsg->nBagType);
	LOG_PROCESS_ERROR(nResult == errSuccess);

	nResult = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, MAX_SPIRIT_BUY_SLOT_COST, CItemBag::MONEYLOG_SPIRIT_BUYSLOT);
	LOG_PROCESS_ERROR(nResult == errSuccess);

	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;	
}

void CCliMessageHandler::OnSpiritBrushSlot(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;

	C2G_SPIRIT_BRUSH_SLOT* pMsg = (C2G_SPIRIT_BRUSH_SLOT*)pData;
	LOG_PROCESS_ERROR(pMsg);

	nResult = poRole->GetSpirit().BrushSlot(pMsg->nPage, pMsg->nIndex);
	LOG_PROCESS_ERROR(nResult == errSuccess);

	return;

Exit0:
	if (nResult != errUnknownError)
		CCliMessageHandler::GetInstance().DoErrorCodeNotify(poRole, nResult, 0, 0);

	return;	
}


BOOL CCliMessageHandler::DoSyncSpirit(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_SYNC_SPIRIT* pMsg = NULL;
	UINT32 dwSize = 0;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_SPIRIT*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_spirit;

	nRetCode = poRole->GetSpirit().Save(pMsg->szData, dwSize);
	LOG_PROCESS_ERROR(nRetCode);

	pMsg->wSize = (UINT16)dwSize + sizeof(G2C_SYNC_SPIRIT);

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritChange(CRole* poRole, INT32 nExp, INT32 nPts)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_EXP_CHANGE* pMsg = NULL;
	
	pMsg = (G2C_SPIRIT_EXP_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_EXP_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg		= g2c_spirit_exp_change;
	pMsg->nPts		= nPts;
	pMsg->nExp		= nExp;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_EXP_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritUp(CRole* poRole, INT32 nLevel)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_UP* pMsg = NULL;

	pMsg = (G2C_SPIRIT_UP*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_UP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg		 = g2c_spirit_up;
	pMsg->nLevel	 = nLevel;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_UP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritAirChange(CRole* poRole, INT32 nBagType, INT32 nIndex, INT32 nTemplateID, INT32 nExp)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_AIR_CHANGE* pMsg = NULL;

	pMsg = (G2C_SPIRIT_AIR_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_AIR_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_spirit_air_change;

	pMsg->nAirID = nTemplateID;
	pMsg->nExp = nExp;
	pMsg->nIndex = nIndex;
		
	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_AIR_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritAirLevelUP(CRole* poRole, INT32 nLevel)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_AIR_LEVELUP* pMsg = NULL;

	pMsg = (G2C_SPIRIT_AIR_LEVELUP*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_AIR_LEVELUP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_spirit_air_levelup;

	pMsg->byLevel = nLevel;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_AIR_LEVELUP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritBrushSlot(CRole* poRole, INT32 nPage, INT32 nIndex, INT32 nNumber)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_BRUSH_SLOT* pMsg = NULL;

	pMsg = (G2C_SPIRIT_BRUSH_SLOT*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_BRUSH_SLOT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_spirit_brush_slot;

	pMsg->nPage = nPage;
	pMsg->nIndex = nIndex;
	pMsg->nNumber = nNumber;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_BRUSH_SLOT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSpiritSlotSizeChange(CRole* poRole, INT32 nBagType, INT32 nSize)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_SLOT_SIZE_CHANGE* pMsg = NULL;

	pMsg = (G2C_SPIRIT_SLOT_SIZE_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_SPIRIT_SLOT_SIZE_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_spirit_slot_size_change;

	pMsg->nType = nBagType;
	pMsg->nSize = nSize;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPIRIT_SLOT_SIZE_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

#endif