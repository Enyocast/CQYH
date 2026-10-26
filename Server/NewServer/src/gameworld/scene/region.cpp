#include "stdafx.h"
#include "region.h"

#include "server_def.h"
#include "ai_def.h"
#include "message_handler.h"
#include "game_world.h"
#include "scene.h"
#include "role.h"
#include "npc_data.h"
#include "npc.h"
#include "doodad.h"
#include "missile.h"
#include "ai_signal.h"
#include "scene_file_mgr.h"
#include "item_mgr.h"
#include "message_handler.h"
#include "dump.h"
#include "statis_info.h"

CRegion::CRegion()
{
	m_poScene = NULL;
	m_nRegionX = 0;
	m_nRegionY = 0;
	m_nActive = 0;
    m_nLastActiveFrame = INT_MIN;
	m_nBlockBulletGridRef = 0;
	memset(m_poConnectedRegion, 0, sizeof(m_poConnectedRegion));

	m_lstRole.Clear();
	m_lstNpc.Clear();
	m_lstDoodad.Clear();
	m_lstMissile.Clear();
	m_lstDrop.Clear();
    m_lstHero.Clear();
    m_lstSignal.Clear();

    m_qwSignalBitMask = 0;
}

CRegion::~CRegion()
{
	UnInit();
}

BOOL CRegion::Init(CScene* poScene, INT32 nRegionX, INT32 nRegionY)
{
	LOG_PROCESS_ERROR(poScene);

	m_poScene = poScene;
	m_nRegionX = nRegionX;
	m_nRegionY = nRegionY;

	for (INT32 nDirection = 0; nDirection < DT_DIRECTION_8_COUNT; nDirection++)
	{
		CRegion* poConnectedRegion = m_poScene->GetRegion(
			m_nRegionX + g_nAdjacentX[nDirection], m_nRegionY + g_nAdjacentY[nDirection]);
		m_poConnectedRegion[nDirection] = poConnectedRegion;
	}

	m_lstRole.Clear();
	m_lstNpc.Clear();
	m_lstDoodad.Clear();
	m_lstMissile.Clear();
	m_lstDrop.Clear();
    m_lstHero.Clear();
    m_qwSignalBitMask = 0LL;
    m_lstSignal.Clear();

	m_nActive = 0;
    m_nLastActiveFrame = INT_MIN;
	m_nBlockBulletGridRef = 0;

	return TRUE;
Exit0:

	return FALSE;
}

BOOL CRegion::UnInit(void)
{
	INT32 nRetCode = 0;
	BASE_LIST_NODE* pNextNode = NULL;

	if (!m_lstRole.IsEmpty())
	{
		CRI("there is role in scene %d-%d region %d-%d", 
			m_poScene->GetSceneTempID(), m_poScene->GetSceneID(), m_nRegionX, m_nRegionY);

		for (BASE_LIST_NODE* pNode = m_lstRole.Head().pNext;
			pNode != &(m_lstRole.Rear()); pNode = pNextNode)
		{
			CRole* poRole = node_cast(CRole*, GetRegionListNode(), pNode);
			pNextNode = pNode->pNext;

			nRetCode = m_poScene->RemoveRole(poRole);
			LOG_CHECK_ERROR(nRetCode);

			CRI("removed role %s:%d", poRole->GetName(), poRole->GetObjID());
		}
	}

	for (BASE_LIST_NODE* pNode = m_lstNpc.Head().pNext;
		pNode != &(m_lstNpc.Rear()); pNode = pNextNode)
	{
		CNpc* poNpc = node_cast(CNpc*, GetRegionListNode(), pNode);
		pNextNode = pNode->pNext;

		nRetCode = m_poScene->RemoveNpc(poNpc);
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = poNpc->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelNpc(poNpc);
		LOG_CHECK_ERROR(nRetCode);
	}

	for (BASE_LIST_NODE* pNode = m_lstHero.Head().pNext;
		pNode != &(m_lstHero.Rear()); pNode = pNextNode)
	{
		CHero* poHero = node_cast(CHero*, GetRegionListNode(), pNode);
		pNextNode = pNode->pNext;

        nRetCode = m_poScene->RemoveHero(poHero);
        LOG_CHECK_ERROR(nRetCode);

		nRetCode = poHero->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelHero(poHero);
		LOG_CHECK_ERROR(nRetCode);
	}

	for (BASE_LIST_NODE* pNode = m_lstDoodad.Head().pNext;
		pNode != &(m_lstDoodad.Rear()); pNode = pNextNode)
	{
		CDoodad* poDoodad = node_cast(CDoodad*, GetRegionListNode(), pNode);
		pNextNode = pNode->pNext;

        nRetCode = m_poScene->RemoveDoodad(poDoodad);
        LOG_CHECK_ERROR(nRetCode);

		nRetCode = poDoodad->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelDoodad(poDoodad);
		LOG_CHECK_ERROR(nRetCode);
	}

	for (BASE_LIST_NODE* pNode = m_lstMissile.Head().pNext;
		pNode != &(m_lstMissile.Rear()); pNode = pNextNode)
	{
		CMissile* poMissile = node_cast(CMissile*, GetRegionListNode(), pNode);
		pNextNode = pNode->pNext;

        nRetCode = m_poScene->RemoveMissile(poMissile);
        LOG_CHECK_ERROR(nRetCode);

		nRetCode = poMissile->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelMissile(poMissile);
		LOG_CHECK_ERROR(nRetCode);
	}

	for (BASE_LIST_NODE* pNode = m_lstDrop.Head().pNext;
		pNode != &(m_lstDrop.Rear()); pNode = pNextNode)
	{
		CDrop* poDrop = node_cast(CDrop*, GetRegionListNode(), pNode);
		pNextNode = pNode->pNext;

        nRetCode = m_poScene->RemoveDrop(poDrop);
        LOG_CHECK_ERROR(nRetCode);

		nRetCode = poDrop->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelDrop(poDrop);
		LOG_CHECK_ERROR(nRetCode);
	}

    for (BASE_LIST_NODE* pNode = m_lstSignal.Head().pNext;
        pNode != &(m_lstSignal.Rear()); pNode = pNextNode)
    {
        stSignal* poSignal = node_cast(stSignal*, ListNode, pNode);
        pNextNode = pNode->pNext;

        nRetCode = CGameWorld::GetInstance().DelSignal( poSignal );
        LOG_CHECK_ERROR( nRetCode );
    }

	LOG_CHECK_ERROR(m_lstRole.IsEmpty());

	m_lstRole.Clear();
	m_lstNpc.Clear();
	m_lstHero.Clear();
	m_lstDoodad.Clear();
	m_lstMissile.Clear();
	m_lstDrop.Clear();
    m_qwSignalBitMask = 0LL;
    m_lstSignal.Clear();

	memset(m_poConnectedRegion, 0, sizeof(m_poConnectedRegion));
	m_poScene = NULL;

	return TRUE;
}

BOOL CRegion::MainLoop(void)
{
	INT32 nRetCode = FALSE;
	INT32 nTemp = 0;
	BASE_LIST_NODE* pNode = NULL;
	BASE_LIST_NODE* pNextNode = NULL;

    if (m_nActive > 0)
        m_nLastActiveFrame = CGameWorld::GetInstance().GetGameFrame();

	pNode = m_lstRole.Head().pNext;
	while (pNode != &(m_lstRole.Rear()))
	{
		CRole* poRole = node_cast(CRole*, GetRegionListNode(), pNode);
		poRole->Prefetch();

		if (poRole->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poRole->MainLoop();
			LOG_CHECK_ERROR(nRetCode);
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{
			CRI("detected exception, kick role %s, session %08X", poRole->GetName(), poRole->GetSessionID()); 
			KICK_ROLE(poRole, ktLogged);
		}
#elif defined(__linux__)
		nRetCode = poRole->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif
		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}

	pNode = m_lstNpc.Head().pNext;
	while (pNode != &(m_lstNpc.Rear()))
	{
		CNpc* poNpc = node_cast(CNpc*, GetRegionListNode(), pNode);
		if (poNpc->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poNpc->MainLoop();
			LOG_CHECK_ERROR(nRetCode);        
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{
		}
#elif defined(__linux__)
		nRetCode = poNpc->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif
        
		if (poNpc->IsDeleteSelf())
		{
			LOG_PROCESS_ERROR(poNpc->GetScene());
			nRetCode = poNpc->GetScene()->RemoveNpc(poNpc);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poNpc->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelNpc(poNpc);
			LOG_CHECK_ERROR(nRetCode);
		}

		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}


	pNode = m_lstHero.Head().pNext;
	while (pNode != &(m_lstHero.Rear()))
	{
		CHero* poHero = node_cast(CHero*, GetRegionListNode(), pNode);
		if (poHero->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poHero->MainLoop();
			LOG_CHECK_ERROR(nRetCode);        
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{
		}
#elif defined(__linux__)
		nRetCode = poHero->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif 

		if (poHero->IsDeleteSelf())
		{
			LOG_PROCESS_ERROR(poHero->GetScene());
			nRetCode = poHero->GetScene()->RemoveHero(poHero);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poHero->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelHero(poHero);
			LOG_CHECK_ERROR(nRetCode);
		}

		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}


	pNode = m_lstDoodad.Head().pNext;
	while (pNode != &(m_lstDoodad.Rear()))
	{
		CDoodad* poDoodad = node_cast(CDoodad*, GetRegionListNode(), pNode);
		if (poDoodad->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poDoodad->MainLoop();
			LOG_CHECK_ERROR(nRetCode);
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{

		}
#elif defined(__linux__)
		nRetCode = poDoodad->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif

		if (poDoodad->IsDeleteSelf())
		{
			LOG_PROCESS_ERROR(poDoodad->GetScene());
			nRetCode = poDoodad->GetScene()->RemoveDoodad(poDoodad);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poDoodad->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelDoodad(poDoodad);
			LOG_CHECK_ERROR(nRetCode);
		}

		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}

	pNode = m_lstMissile.Head().pNext;
	while (pNode != &(m_lstMissile.Rear()))
	{
		CMissile* poMissile = node_cast(CMissile*, GetRegionListNode(), pNode);
		if (poMissile->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poMissile->MainLoop();
			LOG_CHECK_ERROR(nRetCode);
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{

		}
#elif defined(__linux__)
		nRetCode = poMissile->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif

		if (poMissile->IsDeleteSelf())
		{
			LOG_PROCESS_ERROR(poMissile->GetScene());
			nRetCode = poMissile->GetScene()->RemoveMissile(poMissile);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poMissile->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelMissile(poMissile);
			LOG_CHECK_ERROR(nRetCode);
		}

		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}

	pNode = m_lstDrop.Head().pNext;
	while (pNode != &(m_lstDrop.Rear()))
	{
		CDrop* poDrop = node_cast(CDrop*, GetRegionListNode(), pNode);
		if (poDrop->GetRegion() != this)
		{
			//INT3_DBG();
			break;
		}

		pNextNode = pNode->pNext;

#if defined(WIN32) | defined(WIN64)
		__try
		{
			nRetCode = poDrop->MainLoop();
			LOG_CHECK_ERROR(nRetCode);
		}
		__except(DumpExceptionFilter(GetExceptionInformation()))
		{
		}
#elif defined(__linux__)
		nRetCode = poDrop->MainLoop();
		LOG_CHECK_ERROR(nRetCode);
#endif  

		if (poDrop->IsDeleteSelf())
		{
			LOG_PROCESS_ERROR(poDrop->GetScene());
			nRetCode = poDrop->GetScene()->RemoveDrop(poDrop);
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = poDrop->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelDrop(poDrop);
			LOG_CHECK_ERROR(nRetCode);
		}

		if (pNextNode->pNext == NULL || pNextNode->pPrev == NULL)
			break;

		pNode = pNextNode;
	}

    if ( m_qwSignalBitMask )
    {
        UINT64 qwCheckSignalMask = 0LL;

        pNode = m_lstSignal.Head().pNext;
        while (pNode != &(m_lstSignal.Rear()))
        {
            stSignal* poSignal = node_cast(stSignal*, ListNode, pNode);
            LOG_PROCESS_ERROR( poSignal );
            pNextNode = pNode->pNext;

            if (poSignal->nRemainTimes <= 0 ||
                poSignal->nExpiredFrame <= CGameWorld::GetInstance().GetGameFrame() )
            {
                nRetCode = CBaseList::Remove(&poSignal->ListNode);
                LOG_PROCESS_ERROR(nRetCode);

                nRetCode = CGameWorld::GetInstance().DelSignal( poSignal );
                LOG_PROCESS_ERROR( nRetCode );

                CCharacter* pIssuer = CGameWorld::GetInstance().FindCharacter( poSignal->dwIssuerID );
                if( NULL == pIssuer || NULL == pIssuer->GetAIProcessor() )
                    continue;

                LOG_PROCESS_ERROR( pIssuer->GetAIProcessor() );
                pIssuer->GetAIProcessor()->DecreaseSignalNum();

            }
            else
            {
                qwCheckSignalMask |= ( 1LL << poSignal->nType );
            }
            pNode = pNextNode;
        }

        m_qwSignalBitMask = qwCheckSignalMask;
    }

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::IsInactiving(void)
{
    return m_nActive == 0 && m_nLastActiveFrame + REGION_INACTIVE_DELAY > CGameWorld::GetInstance().GetGameFrame();
}

BOOL CRegion::InsertSignal( UINT32 dwIssuerID, INT32 nSignalType, INT32 nSignalParam, INT32 nExpiredFrame, INT32 nProcessTimes )
{
    BOOL nRetCode = FALSE;
    stSignal* poNewSignal = NULL;

    BASE_LIST_NODE* pNode = NULL;

    LOG_PROCESS_ERROR( nSignalType > 0 && nSignalType < sigEnd );

    if ( m_qwSignalBitMask & (1LL << nSignalType) )// check duplicated signal type
    {
        INT32  nSignalCounter = 0;
        pNode = m_lstSignal.Head().pNext;
        while (pNode != &(m_lstSignal.Rear()))
        {
            stSignal* poSignal = node_cast(stSignal*, ListNode, pNode);
            BASE_LIST_NODE* pNextNode = pNode->pNext;

            LOG_PROCESS_ERROR( nSignalCounter < SIGNAL_MAX_NUM_PER_REGION - 1 );

            if( poSignal->nRemainTimes > 0 &&
                poSignal->nExpiredFrame > CGameWorld::GetInstance().GetGameFrame() &&    // ignore if mainloop process first 
                poSignal->nType == nSignalType && 
                dwIssuerID == poSignal->dwIssuerID )
            {
//                DBG("issuer %d has already have a signal %d", poSignal->dwIssuerID, poSignal->nType);
                //poSignal->nExpiredFrame = CGameWorld::GetInstance().GetGameFrame() + nLiveFrames;
                //poSignal->nRemainTimes = nProcessTimes;
                PROCESS_ERROR(FALSE);
            }
            pNode = pNextNode;

            ++nSignalCounter;
        }
    }

    // create new
    poNewSignal = CGameWorld::GetInstance().NewSignal();    //new stSignal;
    LOG_PROCESS_ERROR( poNewSignal );

    poNewSignal->nType = nSignalType;
    poNewSignal->nParam = nSignalParam;
    poNewSignal->nRemainTimes = nProcessTimes;
    poNewSignal->nExpiredFrame = nExpiredFrame;

    poNewSignal->dwIssuerID = dwIssuerID;
    poNewSignal->ListNode.pPrev = poNewSignal->ListNode.pNext = NULL;

    m_lstSignal.PushRear( &poNewSignal->ListNode );
    m_qwSignalBitMask |= (1LL << nSignalType);

//    DBG("character %d new add a signal %d", poNewSignal->dwIssuerID, poNewSignal->nType);

    return TRUE;
Exit0:
    if ( poNewSignal )
    {
        CGameWorld::GetInstance().DelSignal( poNewSignal );
    }
    return FALSE;
}
//
//BOOL CRegion::ReduceSignal( INT32 nSignalType, UINT32 dwIssuerID )
//{
//    BOOL nRetCode = FALSE;
//    BASE_LIST_NODE* pNode = NULL;
//
//    if ( m_qwSignalBitMask &(1<<nSignalType) )
//    {
//        pNode = m_lstSignal.Head().pNext;
//        while (pNode != &(m_lstSignal.Rear()))
//        {
//            stSignal* poSignal = node_cast(stSignal*, ListNode, pNode);
//            BASE_LIST_NODE* pNextNode = pNode->pNext;
//
//            if( poSignal->nRemainTimes > 0 &&
//                poSignal->nExpiredFrame > CGameWorld::GetInstance().GetGameFrame() &&    // ignore if mainloop process first
//                poSignal->dwIssuerID == dwIssuerID && 
//                poSignal->nType == nSignalType)
//            {
//                --poSignal->nRemainTimes;
//                nRetCode = TRUE;
//
//                DBG("ReduceSignal %d, reminTimes %d", nSignalType, poSignal->nRemainTimes);
//            }
//
//            pNode = pNextNode;
//        }
//    }
//
//Exit0:
//    return nRetCode;
//}

BOOL CRegion::AddRole(CRole* poRole)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poRole);
	poRole->SetRegion(this);
	m_lstRole.PushHead(&poRole->GetRegionListNode());

	IncrActiveCount(poRole);

	for (INT32 nIndex = 0; nIndex < DT_DIRECTION_8_COUNT; nIndex++)
	{
		if ( NULL != m_poConnectedRegion[nIndex] )
		{
			m_poConnectedRegion[nIndex]->IncrActiveCount(poRole);
		}
	}


	return TRUE;
Exit0:
	return FALSE;
}


BOOL CRegion::RemoveRole(CRole* poRole)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poRole);

	CBaseList::Remove(&poRole->GetRegionListNode());
	poRole->SetRegion(NULL);

	DecrActiveCount(poRole);

	for (INT32 nIndex = 0; nIndex < DT_DIRECTION_8_COUNT; nIndex++)
	{
		if ( NULL != m_poConnectedRegion[nIndex] )
		{
			m_poConnectedRegion[nIndex]->DecrActiveCount(poRole);
		}
	}


	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::AddNpc(CNpc* poNpc)
{
	INT32 nRetCode = 0;
	const NPC_DATA* pNpcData = NULL;

	LOG_PROCESS_ERROR(poNpc);

	poNpc->SetRegion(this);
	m_lstNpc.PushHead(&poNpc->GetRegionListNode());

    if (poNpc->GetNpcData() && poNpc->GetAlwaysRun())
		IncrActiveCount(poNpc);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::RemoveNpc(CNpc* poNpc)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poNpc);

	CBaseList::Remove(&poNpc->GetRegionListNode());
	poNpc->SetRegion(NULL);

    if (poNpc->GetNpcData() && poNpc->GetAlwaysRun())
		DecrActiveCount(poNpc);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::AddDoodad(CDoodad* poDoodad)
{
	LOG_PROCESS_ERROR(poDoodad);

	poDoodad->SetRegion(this);
	m_lstDoodad.PushHead(&poDoodad->GetRegionListNode());

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::RemoveDoodad(CDoodad* poDoodad)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poDoodad);

	CBaseList::Remove(&poDoodad->GetRegionListNode());
	poDoodad->SetRegion(NULL);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::AddMissile(CMissile* poMissile)
{
	LOG_PROCESS_ERROR(poMissile);

	poMissile->SetRegion(this);
	m_lstMissile.PushHead(&poMissile->GetRegionListNode());
	IncrActiveCount(poMissile);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::RemoveMissile(CMissile* poMissile)
{
	LOG_PROCESS_ERROR(poMissile);

	CBaseList::Remove(&poMissile->GetRegionListNode());
	poMissile->SetRegion(NULL);
	DecrActiveCount(poMissile);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::AddDrop(CDrop* poDrop)
{
	LOG_PROCESS_ERROR(poDrop);

	poDrop->SetRegion(this);
	m_lstDrop.PushHead(&poDrop->GetRegionListNode());

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::RemoveDrop(CDrop* poDrop)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poDrop);

	CBaseList::Remove(&poDrop->GetRegionListNode());
	poDrop->SetRegion(NULL);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::AddHero(CHero* poHero)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poHero);

	poHero->SetRegion(this);
	m_lstHero.PushHead(&poHero->GetRegionListNode());

	IncrActiveCount(poHero);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::RemoveHero(CHero* poHero)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(poHero);

	CBaseList::Remove(&poHero->GetRegionListNode());
	poHero->SetRegion(NULL);

	DecrActiveCount(poHero);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::IncrActiveCount(CSceneObject* poObj)
{
//	m_TestSet.insert(poObj);
//	DBG("++%d%d", m_nRegionX, m_nRegionY);
	LOG_PROCESS_ERROR(m_nActive >= 0);
	m_nActive++;
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRegion::DecrActiveCount(CSceneObject* poObj)
{
//	TTestSet::iterator itr = m_TestSet.find(poObj);
//	LOG_PROCESS_ERROR(itr != m_TestSet.end());

//	DBG("--%d%d", m_nRegionX, m_nRegionY);
	LOG_PROCESS_ERROR(m_nActive > 0);
	m_nActive--;
	return TRUE;
Exit0:
	return FALSE;
}

