#include "stdafx.h"
#include "doodad.h"
#include "data_manager.h"

#include "id_def.h"
#include "doodad_data.h"
#include "game_world.h"
#include "scene.h"
#include "scene_file_mgr.h"
#include "message_handler.h"
#include "adventure.h"
#include "aura.h"
#include "spell_config.h"
#include "doodad_def.h"
#include "drop_group_data.h"
#include "drop_generator.h"

CDoodad::CDoodad()
{
    m_pDoodadData = NULL;
    m_eState = dsInvalid;
    m_pcSpawnPoint = NULL;
    m_nOpenCount = 0;
    m_nOpenTimer = INT_MAX;
    m_nReviveTimer = 0;
	m_nDestroyTimer = 0;
	m_dwOpenCharID = INVALID_OBJECT_ID;
}

CDoodad::~CDoodad()
{
    UnInit();
}

BOOL CDoodad::Init(UINT32 dwObjID, INT32 nTemplateID)
{
	INT32 nRetCode = 0;

	nRetCode = CSceneObject::Init(dwObjID);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = SetTemplateID(nTemplateID);
	LOG_PROCESS_ERROR(nRetCode);

	m_pcSpawnPoint = NULL;
	m_eState = dsAlive;
	m_nOpenTimer = INT_MAX;
	m_dwOpenCharID = INVALID_OBJECT_ID;

	if (m_pDoodadData->nLifeFrm != 0)
	{
		m_nDestroyTimer = CGameWorld::GetInstance().GetGameFrame() + m_pDoodadData->nLifeFrm;
	}
	else
		m_nDestroyTimer = INT_MAX;

    return TRUE;
Exit0:
    UnInit();

    return FALSE;
}

BOOL CDoodad::UnInit(void)
{
    INT32 nRetCode = 0;

    m_pDoodadData = NULL;

    nRetCode = CSceneObject::UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

BOOL CDoodad::MainLoop(void)
{
    INT32 nRetCode = 0;

    switch (m_eState)
    {
    case dsAlive:
        if (m_nOpenTimer < CGameWorld::GetInstance().GetGameFrame())
        {
            CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(m_dwOpenCharID);
			if (poChar && CanOpen(poChar))
			{
				_OnOpen(poChar);
			}
            m_nOpenTimer = INT_MAX;
        }
        break;
    case dsDead:
        if (m_nReviveTimer < CGameWorld::GetInstance().GetGameFrame())
        {
            nRetCode = m_poScene->RespawnDoodad(this);
            LOG_PROCESS_ERROR(nRetCode);

            m_eState = dsAlive;
        }
        break;
    }

	if (m_nDestroyTimer < CGameWorld::GetInstance().GetGameFrame())
		DeleteSelf();

	return TRUE;
Exit0:
    return FALSE;
}

BOOL CDoodad::SetTemplateID(INT32 nTemplateID)
{
    m_pDoodadData = CDataManager<DOODAD_DATA>::GetInstance().GetData(nTemplateID);
    LOG_PROCESS_ERROR(m_pDoodadData);

    m_nOpenCount = g_Random(m_pDoodadData->nMinOpenCount, m_pDoodadData->nMaxOpenCount);
	LOG_PROCESS_ERROR(m_nOpenCount > 0);

	SetBodyType(m_pDoodadData->nBodyType);

    return TRUE;
Exit0:
	CRI("failed to set doodad template id %d", nTemplateID);

    return FALSE;
}

BOOL CDoodad::CanOpen(CCharacter* poChar)
{
    LOG_PROCESS_ERROR(poChar);
    LOG_PROCESS_ERROR(m_pDoodadData);
	PROCESS_ERROR(m_nOpenCount > 0);
	PROCESS_ERROR(m_eState == dsAlive);

    if (poChar->GetObjType() == otRole)
    {
        CRole* poRole = (CRole*)poChar;
        if (m_pDoodadData->nRequireItemID != INVALID_OBJECT_ID)
        {
            PROCESS_ERROR(poRole->GetItemBag()->GetItemCount(m_pDoodadData->nRequireItemID, FALSE) > 0);
        }
        if (m_pDoodadData->nRequireVarID != 0)
        {
            INT32 nIndex = GetVarIndexFromID(m_pDoodadData->nRequireVarID);
            INT32 nValue = m_pDoodadData->nRequireVarValue;

            switch (GetVarTypeFromID(m_pDoodadData->nRequireVarID))
            {
            case vtRole:
                PROCESS_ERROR(poRole->GetVariable(nIndex) == nValue);
                break;
            case vtScene:
                LOG_PROCESS_ERROR(m_poScene);
                PROCESS_ERROR(m_poScene->GetVariable(nIndex) == nValue);
                break;
            case vtClient:
                PROCESS_ERROR(poRole->GetClientVariable(nIndex) == nValue);			
                break;
            default:
                LOG_PROCESS_ERROR(FALSE);
                break;
            }
        }
    }

    return TRUE;
Exit0:

    return FALSE;
}

void CDoodad::OnOpen(CCharacter* poChar, INT32 nDelayFrame)
{
    if (nDelayFrame > 0)
    {
        if (m_nOpenTimer > CGameWorld::GetInstance().GetGameFrame() + nDelayFrame)
        {
            LOG_PROCESS_ERROR(poChar);

            m_nOpenTimer = CGameWorld::GetInstance().GetGameFrame() + nDelayFrame;
            m_dwOpenCharID = poChar->GetObjID();
        }
    }
    else
    {
        _OnOpen(poChar);
    }
Exit0:
    return;
}

void CDoodad::_OnOpen(CCharacter* poChar)
{
    INT32 nRetCode = 0;
    const DOODAD_SPAWN_GROUP* pGroup = NULL;
    CRole* poRole = NULL;
	const DOODAD_DATA* pDoodadData = NULL;
	const DOODAD_DROP_DATA* pDropData = NULL;

    LOG_PROCESS_ERROR(poChar);
    LOG_PROCESS_ERROR(m_pDoodadData);
	LOG_PROCESS_ERROR(m_nOpenCount > 0);
	LOG_PROCESS_ERROR(m_eState == dsAlive);

	if (poChar->GetObjType() == otRole)
	{
		poRole = (CRole*)poChar;
		LOG_PROCESS_ERROR(poRole);

		if (m_pDoodadData->nRequireItemID != INVALID_OBJECT_ID && m_pDoodadData->bCostItem)
		{
			nRetCode = poRole->GetItemBag()->DeleteItemId(m_pDoodadData->nRequireItemID, 1, ITEMLOG_OPEN_DOODAD, FALSE, 0);
			LOG_PROCESS_ERROR(nRetCode);
		}

		switch (m_pDoodadData->nType)
		{
		case dtDestrucible:
			{
				poRole->GetQuestList().OnKillDoodad(m_pDoodadData->nTemplateID);
			}
			break;
		case dtCorpse:
			{
				poRole->GetAchievementList().AddVariable(avdKillNpcCorpse, 1);
			}
			break;
		default:
			break;
		}
	}

    pDropData = CDataManager<DOODAD_DROP_DATA>::GetInstance().GetData(m_pDoodadData->nTemplateID);
	if (pDropData)
	{
		nRetCode = CDropGenerator::GetInstance().GenerateDrops(poRole->GetServerGroup(),
            pDropData->DropChanceData, pDropData->nChanceCount,
            m_poScene, m_llX, m_llY, m_llZ,
            poChar->GetObjID(), m_dwObjID, MAX_ROLE_LEVEL, FALSE, FALSE);
		LOG_PROCESS_ERROR(nRetCode);
	}

    m_nOpenCount--;

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoSyncOpenDoodadCount(this, poChar);
	LOG_CHECK_ERROR(nRetCode);
#endif	// _ROBOT

    if (m_nOpenCount <= 0)
    {
        LOG_PROCESS_ERROR(m_poScene);
        LOG_PROCESS_ERROR(m_poScene->GetStaticData());

        if (poChar->GetObjType() == otRole)
        {
            CRole* poRole = (CRole*)poChar;
            CAdventure::GetInstance().OnDestoryDoodad(poRole, this);
            poRole->IncCombatStat(escsDoodadKillCount, 1);
        }

        if (m_pDoodadData->nSpawnNpcID != INVALID_OBJECT_ID && 
            g_Random(RATE_MAX) < m_pDoodadData->nSpawnNpcChance)
        {
            CNpc* poNpc = m_poScene->SpawnNpc(m_pDoodadData->nSpawnNpcID, m_llX, m_llY, m_llZ, m_nFaceDirection, 0, NULL);
            LOG_CHECK_ERROR(poNpc);
        }

        if (m_pDoodadData->nAuraID != INVALID_OBJECT_ID)
        {
            CAura* poAuraInfo = NULL;
            CAuraInstance* poAuraInstance = NULL;

            poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(m_pDoodadData->nAuraID);
            LOG_CHECK_ERROR(poAuraInfo);

            if (poAuraInfo)
            {
                poAuraInstance = poChar->AppendAura(poAuraInfo, poChar, poChar->GetObjID(), NULL, 0, 0, 0, 0);
                LOG_CHECK_ERROR(poAuraInstance);
            }
        }

        if (m_pcSpawnPoint)
        {
            pGroup = m_poScene->GetStaticData()->GetDoodadSpawnGroup(m_pcSpawnPoint->nGroupID);
            LOG_PROCESS_ERROR(pGroup);
        }

        if (pGroup && pGroup->IsAutoReSpawn)
        {
            nRetCode = m_poScene->AddDoodadToRespawnList(this);
            LOG_PROCESS_ERROR(nRetCode);

            m_nReviveTimer = CGameWorld::GetInstance().GetGameFrame() + pGroup->nRespawnInterval;
            m_eState = dsDead;
        }
        else
        {
            DeleteSelf();
        }
    }
    return;
Exit0:
    DeleteSelf();

    return;
}

INT32 CDoodad::GetObjType(void)
{
	return otDoodad;
}
