#include "stdafx.h"
#include "reputation.h"

#include "role_def.h"
#include "init_reputation_data.h"
#include "message_handler.h"
#include "role.h"

CReputation::CReputation()
{
    m_poOwner = NULL;
    m_qwActiveState = 0;
	m_qwAwardState = 0;
}

CReputation::~CReputation()
{
    UnInit();
}

BOOL CReputation::Init(CRole* poOwner)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poOwner);

    m_poOwner = poOwner;
	m_qwActiveState = 0;
	m_qwAwardState = 0;

    nRetCode = _LoadInitData();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CReputation::UnInit(void)
{
    m_poOwner = NULL;

    return TRUE;
}

BOOL CReputation::_LoadInitData(void)
{
    for (INT32 nForceID = 0; nForceID < MAX_NPC_FORCE_ID; nForceID++)
    {
        const INIT_REPUTATION_DATA* pcData = CDataManager<INIT_REPUTATION_DATA>::GetInstance().GetData(nForceID);
        LOG_PROCESS_ERROR(pcData);

        m_nValueList[nForceID] = pcData->nInitValue;
		if (pcData->bActive)
			m_qwActiveState |= (UINT64)(1LL << nForceID);
    }

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CReputation::GetValue(INT32 nForceID)
{
    LOG_PROCESS_ERROR(nForceID >= 0 && nForceID < MAX_NPC_FORCE_ID);

    return m_nValueList[nForceID];
Exit0:
    return 0;
}

void CReputation::SetValue(INT32 nForceID, INT32 nNewValue)
{
    INT32 nRetCode = 0;
	const INIT_REPUTATION_DATA* pcData = NULL;

    LOG_PROCESS_ERROR(nForceID >= 0 && nForceID < MAX_NPC_FORCE_ID);

	pcData = CDataManager<INIT_REPUTATION_DATA>::GetInstance().GetData(nForceID);
	LOG_PROCESS_ERROR(pcData);

	if (nNewValue >= pcData->nMaxValue)
		nNewValue = pcData->nMaxValue;

	if (nNewValue < MIN_REPUTATION)
        nNewValue = MIN_REPUTATION;

    m_nValueList[nForceID] = nNewValue;
	m_qwActiveState |= (UINT64)(1LL << nForceID);

#ifndef _ROBOT
    nRetCode = CCliMessageHandler::GetInstance().DoModifyReputation(m_poOwner, nForceID, nNewValue);
    LOG_CHECK_ERROR(nRetCode);
#endif  // _ROBOT

Exit0:
    return;
}

void CReputation::ModifyValue(INT32 nForceID, INT32 nValue)
{
    LOG_PROCESS_ERROR(nForceID >= 0 && nForceID < MAX_NPC_FORCE_ID);

    if (nValue > 0)
    {
        PROCESS_ERROR(m_poOwner->GetFcmState() != fcmsNone);
        if (m_poOwner->GetFcmState() == fcmsHalf)
            nValue /= 2;
    }

	SetValue(nForceID, m_nValueList[nForceID] + nValue);
Exit0:
	return;
}

void CReputation::ActiveForce(INT32 nForceID)
{
	INT32 nRetCode = 0;

	m_qwActiveState |= (UINT64)(1LL << nForceID);

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoModifyReputation(m_poOwner, nForceID, m_nValueList[nForceID]);
	LOG_CHECK_ERROR(nRetCode);
#endif
}

INT32 CReputation::ReceiveAward(INT32 nForceID)
{
	INT32 nResult = errUnknownError;
	INT32 nRetCode = 0;
	const INIT_REPUTATION_DATA* pcData = NULL;
	INT32 nClass = m_poOwner->GetClass();

	LOG_PROCESS_ERROR(nForceID >= 0 && nForceID < MAX_NPC_FORCE_ID);

	pcData = CDataManager<INIT_REPUTATION_DATA>::GetInstance().GetData(nForceID);
	LOG_PROCESS_ERROR(pcData);

	PROCESS_ERROR_RET_CODE(m_nValueList[nForceID] >= pcData->nMaxValue, errRepNotEnoughReputation);
	PROCESS_ERROR_RET_CODE((m_qwAwardState & (UINT64)(1LL << nForceID)) == 0, errRepAlreadyReceived);
	PROCESS_ERROR_RET_CODE(m_poOwner->GetItemBag()->GetFreeSlots(CONSLOT_DEFAULT) >= pcData->nMaxAwardItemCount[nClass], errItemBagFull);

	LOG_PROCESS_ERROR(nClass >= clsPlayerBegin && nClass < clsPlayerEnd);

	for (INT32 nIndex = 0; nIndex < MAX_REPUTATION_AWARD_COUNT; nIndex++)
	{
		if (pcData->nAwardItemCount[nClass][nIndex] > 0)
		{
			if (pcData->nAwardItemID[nClass][nIndex] < MONEYTYPE_COUNT)
			{
				nRetCode = m_poOwner->GetItemBag()->AddMoney(pcData->nAwardItemID[nClass][nIndex],
					pcData->nAwardItemCount[nClass][nIndex], MONEYLOG_REPUTATION_AWARD, 0);
			}
			else
			{
				nRetCode = m_poOwner->GetItemBag()->AddItem(pcData->nAwardItemID[nClass][nIndex],
					pcData->nAwardItemCount[nClass][nIndex], ITEMLOG_REPUTATION_AWARD, 0, FALSE);
			}
			if (nRetCode != errSuccess)
			{
				CRI("failed to add reputation award item %d.%d to role %s:%d, error code %d", pcData->nAwardItemID[nClass][nIndex],
					pcData->nAwardItemCount[nClass][nIndex], m_poOwner->GetName(), m_poOwner->GetObjID(), nRetCode);
			}
		}
	}

	m_qwAwardState |= (UINT64)(1LL << nForceID);

	nResult = errRepReceiveAwardSuccess;

Exit0:

	return nResult;
}
