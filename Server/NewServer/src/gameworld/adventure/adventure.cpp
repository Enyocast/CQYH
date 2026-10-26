#include "stdafx.h"
#include "adventure.h"

#include "game_world.h"
#include "npc_data.h"
#include "doodad_data.h"
#include "adventure_data.h"
#include "message_handler.h"
#include "scene.h"
#include "chat_def.h"

CAdventure CAdventure::ms_Instance;

CAdventure::CAdventure()
{
    m_TraverseSceneSpawnNpc.pAdventureData = NULL;
    m_TraverseSceneSpawnDoodad.pAdventureData = NULL;
}

CAdventure::~CAdventure()
{
    UnInit();
}

BOOL CAdventure::Init(void)
{
    const ADVENTURE_DATA* pAdventureData = CDataManager<ADVENTURE_DATA>::GetInstance().GetFirstData();
    while (pAdventureData)
    {
        switch (pAdventureData->nTriggerType)
        {
        case attKillNpc:
        case attDestoryDoodad:
        case attServerTime:
            break;
        case attRefineEquip:
            m_RefindEquipList.push_back(pAdventureData);
            break;
        case attAddSoul:
            m_AddSoulList.push_back(pAdventureData);
            break;
        case attRandomizeEquip:
            m_RandomizeEquipList.push_back(pAdventureData);
            break;
        case att5MinOnlineTime:
            m_OnlineTimeList.push_back(pAdventureData);
            break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
        }

        pAdventureData = CDataManager<ADVENTURE_DATA>::GetInstance().GetNextData();
    }

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CAdventure::UnInit(void)
{
    m_OnlineTimeList.clear();
    m_RefindEquipList.clear();
    m_AddSoulList.clear();
    m_RandomizeEquipList.clear();

    return TRUE;
}

void CAdventure::OnMainLoop(CRole* poRole)
{
    INT32 nRetCode = 0;

    for (ADVENTURE_DATA_LIST::iterator it = m_OnlineTimeList.begin();
        it != m_OnlineTimeList.end(); ++it)
    {
        const ADVENTURE_DATA* pAdventureData = *it;
        LOG_PROCESS_ERROR(pAdventureData);

        _CheckTrigger(pAdventureData, poRole, 
            pAdventureData->Role5MinOnlineTime.nMaxCount,
            pAdventureData->RoleRefineEquip.nChance);
    }

Exit0:
    return;
}

void CAdventure::OnKillNpc(CRole* poRole, CNpc* poNpc)
{
    INT32 nRetCode = 0;
    const NPC_DATA* pNpcData = NULL;

    LOG_PROCESS_ERROR(poNpc);

    pNpcData = poNpc->GetNpcData();
    LOG_PROCESS_ERROR(pNpcData);

    PROCESS_ERROR(pNpcData->pAdventureData);

    nRetCode = _CheckTrigger(pNpcData->pAdventureData, poRole, 
        pNpcData->pAdventureData->KillNpc.nMaxCount,
        pNpcData->pAdventureData->KillNpc.nChance);
    PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CAdventure::OnDestoryDoodad(CRole* poRole, CDoodad* poDoodad)
{
    INT32 nRetCode = 0;
    const DOODAD_DATA* pDoodadData = NULL;

    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poDoodad);

    pDoodadData = poDoodad->GetDoodadData();
    LOG_PROCESS_ERROR(pDoodadData);

    PROCESS_ERROR(pDoodadData->pAdventureData);

    nRetCode = _CheckTrigger(pDoodadData->pAdventureData, poRole, 
        pDoodadData->pAdventureData->DestoryDoodad.nMaxCount,
        pDoodadData->pAdventureData->DestoryDoodad.nChance);
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return;
}

void CAdventure::OnRefineEquip(CRole* poRole)
{
    INT32 nRetCode = 0;

    for (ADVENTURE_DATA_LIST::iterator it = m_RefindEquipList.begin();
        it != m_RefindEquipList.end(); ++it)
    {
        const ADVENTURE_DATA* pAdventureData = *it;
        LOG_PROCESS_ERROR(pAdventureData);

        nRetCode = _CheckTrigger(pAdventureData, poRole, 
            pAdventureData->RoleRefineEquip.nMaxCount,
            pAdventureData->RoleRefineEquip.nChance);
        LOG_CHECK_ERROR(nRetCode);
    }

Exit0:
    return;
}

void CAdventure::OnAddSoul(CRole* poRole)
{
    INT32 nRetCode = 0;

    for (ADVENTURE_DATA_LIST::iterator it = m_AddSoulList.begin();
        it != m_AddSoulList.end(); ++it)
    {
        const ADVENTURE_DATA* pAdventureData = *it;
        LOG_PROCESS_ERROR(pAdventureData);

        nRetCode = _CheckTrigger(pAdventureData, poRole, 
            pAdventureData->RoleAddSoul.nMaxCount,
            pAdventureData->RoleAddSoul.nChance);
        LOG_CHECK_ERROR(nRetCode);
    }

Exit0:
    return;
}

void CAdventure::OnRandomizeEquip(CRole* poRole)
{
    INT32 nRetCode = 0;

    for (ADVENTURE_DATA_LIST::iterator it = m_RandomizeEquipList.begin();
        it != m_RandomizeEquipList.end(); ++it)
    {
        const ADVENTURE_DATA* pAdventureData = *it;
        LOG_PROCESS_ERROR(pAdventureData);

        _CheckTrigger(pAdventureData, poRole, 
            pAdventureData->RoleRandomizeEquip.nMaxCount,
            pAdventureData->RoleRandomizeEquip.nChance);
    }

Exit0:
    return;
}

inline BOOL CAdventure::_CheckTrigger(const ADVENTURE_DATA* pAdventureData, CRole* poRole, INT32 nMaxCount, INT32 nChance)
{
    INT32 nRetCode = 0;
    INT32 nVarID = 0;
    INT32 nVarIndex = 0;
    INT32 nVarValue = 0;
    const tm_ex& rcLocalTime = CGameWorld::GetInstance().GetLocalTime();
    INT32 nNum = 0;

    LOG_PROCESS_ERROR(pAdventureData);
    LOG_PROCESS_ERROR(poRole);

    nNum = (rcLocalTime.tm_mon) * 100 + rcLocalTime.tm_mday;
    PROCESS_ERROR(nNum >= pAdventureData->dwStartDate && nNum <= pAdventureData->dwEndDate);
    nNum = (rcLocalTime.tm_hour + 1) * 10000 + (rcLocalTime.tm_min + 1) * 100 + rcLocalTime.tm_sec;
    PROCESS_ERROR(nNum >= pAdventureData->dwStartTime && nNum <= pAdventureData->dwEndTime);

    nVarID = pAdventureData->nVariableID;
    switch (GetVarTypeFromID(nVarID))
    {
    case vtRole:
        {
            nVarIndex = GetVarIndexFromID(nVarID);
            nVarValue = poRole->GetVariable(nVarIndex) + 1;

            if (nVarValue >= nMaxCount)
            {
                if (g_Random(RATE_MAX) < nChance)
                    TriggerReward(pAdventureData, poRole);
                nVarValue = 0;
            }

            poRole->SetVariable(nVarIndex, nVarValue);
        }
        break;
    case vtGuild:
    case vtServer:
        {
#ifndef _ROBOT
            nRetCode = CCliMessageHandler::GetInstance().DoMSAdventureTrigger(
                poRole->GetObjID(), pAdventureData->nID, pAdventureData->nVariableID, nMaxCount, nChance);
            LOG_PROCESS_ERROR(nRetCode);
#endif  // not _ROBOT
        }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    return TRUE;
Exit0:
    return FALSE;
}

void CAdventure::TriggerReward(const ADVENTURE_DATA* pAdventureData, CRole* poRole)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pAdventureData);
    
    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poRole->GetScene());

    switch (pAdventureData->nRewardType)
    {
    case adrSpawnNpcNearby:
        {
            INT32 nNpcTemplateID = pAdventureData->SpawnNpcNearby.nNpcTemplateID;
            INT64 llX = poRole->GetX();
            INT64 llY = poRole->GetY();
            INT64 llZ = poRole->GetZ();
            INT32 nDistance = g_Random(pAdventureData->SpawnNpcNearby.nMinRange, pAdventureData->SpawnNpcNearby.nMaxRange);
            INT32 nDirection = g_Random(MAX_DIRECTION_COUNT);
            llX += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
            llY += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
            nDirection = g_GetDirection(llX, llY, poRole->GetX(), poRole->GetY());

            CNpc* poNpc = poRole->GetScene()->SpawnNpc(nNpcTemplateID, llX, llY, llZ, nDirection, 0, NULL);
            LOG_PROCESS_ERROR(poNpc);

			poNpc->SetExclusiveOwnerID(poRole->GetObjID());
        }
        break;
    case adrSpawnNpcSurround:
        {
            INT32 nNpcTemplateID = pAdventureData->SpawnNpcSurround.nNpcTemplateID;
            INT32 nDistance = pAdventureData->SpawnNpcSurround.nDistance;

            for (INT32 nIndex = 0; nIndex < pAdventureData->SpawnNpcSurround.nNpcCount; nIndex++)
            {
                INT32 nDirection = MAX_DIRECTION_COUNT * nIndex / pAdventureData->SpawnNpcSurround.nNpcCount;
                INT64 llX = poRole->GetX() + nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
                INT64 llY = poRole->GetY() + nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
                INT64 llZ = poRole->GetZ();
                nDirection = g_GetDirection(llX, llY, poRole->GetX(), poRole->GetY());

                CNpc* poNpc = poRole->GetScene()->SpawnNpc(nNpcTemplateID, llX, llY, llZ, nDirection, 0, NULL);
                LOG_CHECK_ERROR(poNpc);

				poNpc->SetExclusiveOwnerID(poRole->GetObjID());
            }
        }
        break;
    case adrSpawnDoodadNearby:
        {
            INT32 nDoodadTemplateID = pAdventureData->SpawnDoodadNearby.nDoodadTemplateID;
            INT64 llX = poRole->GetX();
            INT64 llY = poRole->GetY();
            INT64 llZ = poRole->GetZ();
            INT32 nDistance = g_Random(pAdventureData->SpawnDoodadNearby.nMinRange, pAdventureData->SpawnDoodadNearby.nMaxRange);
            INT32 nDirection = g_Random(MAX_DIRECTION_COUNT);
            llX += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
            llY += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
            nDirection = g_GetDirection(llX, llY, poRole->GetX(), poRole->GetY());

            CDoodad* poDoodad = poRole->GetScene()->SpawnDoodad(nDoodadTemplateID, llX, llY, llZ, nDirection, NULL);
            LOG_PROCESS_ERROR(poDoodad);
        }
        break;
    case adrSendMail:
        {
            nRetCode = poRole->SendMail(poRole->GetObjID(), pAdventureData->MailTemplate.nMailTemplateID);
            LOG_PROCESS_ERROR(nRetCode);
        }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

    if (pAdventureData->bNeedNotification)
    {
        const char* pcszMessage = NULL;
        char szMessage[256];

        if (pAdventureData->dwNotificationStringID < SERVER_STRING_START_ID)
        {
			snprintf(szMessage, 256, "<#P0:<#PN:%s>><#T:%d>", poRole->GetName(), pAdventureData->dwNotificationStringID);
            pcszMessage = szMessage;
        }
        else
        {
            pcszMessage = CGameWorld::GetInstance().GetString(pAdventureData->dwNotificationStringID);
            LOG_PROCESS_ERROR(pcszMessage);
        }

        poRole->Say(cctGroup, cltTvShow, pcszMessage);
    }

Exit0:
    return;
}

BOOL CAdventure::CTraverseSceneSpawnNpc::operator()(UINT64 qwSceneKey, CScene* poScene)
{
    UINT32 dwSceneTempID = (UINT32)(qwSceneKey >> 32);
    UINT32 dwSceneID = (UINT32)qwSceneKey;

    if (dwSceneTempID == pAdventureData->SpawnNpcAtPoint.nSceneTemplateID &&
        poScene->GetServerGroup() == nServerGroup)
    {
        INT32 nNpcTemplateID = pAdventureData->SpawnNpcAtPoint.nNpcTemplateID;
        INT64 llX = pAdventureData->SpawnNpcAtPoint.nX;
        INT64 llY = pAdventureData->SpawnNpcAtPoint.nY;
        INT64 llZ = pAdventureData->SpawnNpcAtPoint.nZ;
        INT32 nDistance = g_Random(pAdventureData->SpawnNpcAtPoint.nRange);
        INT32 nDirection = g_Random(MAX_DIRECTION_COUNT);
        llX += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
        llY += nDistance * g_Sin(nDirection) / SIN_COS_NUMBER;

        CNpc* poNpc = poScene->SpawnNpc(nNpcTemplateID, llX, llY, llZ, nDirection, 0, NULL);
        LOG_CHECK_ERROR(poNpc);
    }

    return TRUE;
}

void CAdventure::SpawnNpcAtPoint(INT32 nServerGroup, const ADVENTURE_DATA* pAdventureData)
{
    LOG_PROCESS_ERROR(pAdventureData);

    m_TraverseSceneSpawnNpc.pAdventureData = pAdventureData;
    m_TraverseSceneSpawnNpc.nServerGroup = nServerGroup;
    
    CGameWorld::GetInstance().TraverseScene(m_TraverseSceneSpawnNpc);

Exit0:
    return;
}

BOOL CAdventure::CTraverseSceneSpawnDoodad::operator()(UINT64 qwSceneKey, CScene* poScene)
{
    UINT32 dwSceneTempID = (UINT32)(qwSceneKey >> 32);
    UINT32 dwSceneID = (UINT32)qwSceneKey;

    if (dwSceneTempID == pAdventureData->SpawnDoodadAtPoint.nSceneTemplateID &&
        poScene->GetServerGroup() == nServerGroup)
    {
        INT32 nDoodadTemplateID = pAdventureData->SpawnDoodadAtPoint.nDoodadTemplateID;
        INT32 nX = pAdventureData->SpawnDoodadAtPoint.nX;
        INT32 nY = pAdventureData->SpawnDoodadAtPoint.nY;
        INT32 nZ = pAdventureData->SpawnDoodadAtPoint.nZ;
        INT32 nDistance = g_Random(pAdventureData->SpawnDoodadAtPoint.nRange);
        INT32 nDirection = g_Random(MAX_DIRECTION_COUNT);
        nX += nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
        nY += nDistance * g_Sin(nDirection) / SIN_COS_NUMBER;

        CDoodad* poDoodad = poScene->SpawnDoodad(nDoodadTemplateID, nX, nY, nZ, nDirection, NULL);
        LOG_CHECK_ERROR(poDoodad);
    }

    return TRUE;
}

void CAdventure::SpawnDoodadAtPoint(INT32 nServerGroup, const ADVENTURE_DATA* pAdventureData)
{
    LOG_PROCESS_ERROR(pAdventureData);

    m_TraverseSceneSpawnDoodad.pAdventureData = pAdventureData;
    m_TraverseSceneSpawnDoodad.nServerGroup = nServerGroup;

    CGameWorld::GetInstance().TraverseScene(m_TraverseSceneSpawnDoodad);

Exit0:
    return;
}
