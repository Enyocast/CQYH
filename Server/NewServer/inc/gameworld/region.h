#ifndef _REGION_H_
#define _REGION_H_

#include "math_ex.h"
#include "base_list.h"

#include "role.h"
#include "npc.h"
#include "hero.h"
#include "doodad.h"
#include "missile.h"
#include "drop.h"
#include "ai_signal.h"

#define REGION_INACTIVE_DELAY   (GAME_FPS * 4)

class CScene;

class CRegion
{
public:
	CRegion();
	virtual ~CRegion();

	BOOL Init(CScene* poScene, INT32 nRegionX, INT32 nRegionY);
	BOOL UnInit(void);
	BOOL MainLoop(void);

    BOOL AddRole(CRole* poRole);
	BOOL RemoveRole(CRole* poRole);

	BOOL AddNpc(CNpc* poNpc);
	BOOL RemoveNpc(CNpc* poNpc);

	BOOL AddHero(CHero* poHero);
	BOOL RemoveHero(CHero* poHero);

	BOOL AddDoodad(CDoodad* poDoodad);
	BOOL RemoveDoodad(CDoodad* poDoodad);

    BOOL AddMissile(CMissile* poMissile);
    BOOL RemoveMissile(CMissile* poMissile);

    BOOL AddDrop(CDrop* poDrop);
    BOOL RemoveDrop(CDrop* poDrop);

	inline BOOL IsActive(INT32 nGameFrame);
    BOOL IsInactiving(void);

	inline INT32 GetRegionX(void);
	inline INT32 GetRegionY(void);
	inline CRegion* GetConnectedRegion(INT32 nDirection);

	template<class TFunc>
	inline BOOL TraverseRole(TFunc& rFunc);
	template<class TFunc>
	inline BOOL TraverseHero(TFunc& rFunc);
	template<class TFunc>
	inline BOOL TraverseNpc(TFunc& rFunc);
	template<class TFunc>
	inline BOOL TraverseDoodad(TFunc& rFunc);
	template<class TFunc>
	inline BOOL TraverseMissile(TFunc& rFunc);
    template<class TFunc>
    inline BOOL TraverseDrop(TFunc& rFunc);
	template<class TFunc>
    inline BOOL TraverseCharacter(TFunc& rFunc);

	template<class TFunc>
    inline BOOL Traverse9Region(TFunc& rFunc);

    template<class TFunc>
    inline BOOL TraverseSignal(TFunc& rFunc);

    BOOL InsertSignal( UINT32 dwIssuerID, INT32 nSignalType, INT32 nSignalParam, INT32 nExpiredFrame, INT32 nProcessTimes);
    BOOL ReduceSignal( INT32 nSignalType, UINT32 dwIssuerID );

	BOOL IncrActiveCount(CSceneObject* poObj);
	BOOL DecrActiveCount(CSceneObject* poObj);

private:
	CScene*		m_poScene;
	INT32		m_nRegionX;
	INT32		m_nRegionY;
	CRegion*	m_poConnectedRegion[DT_DIRECTION_8_COUNT];

	INT32	    m_nActive;
    INT32       m_nLastActiveFrame;
    INT32		m_nBlockBulletGridRef;

    CBaseList   m_lstRole;
    CBaseList   m_lstNpc;
    CBaseList   m_lstHero;
    CBaseList   m_lstDoodad;
    CBaseList   m_lstMissile;
    CBaseList   m_lstDrop;

    UINT64      m_qwSignalBitMask;  // bits length = sigEnd
    CBaseList   m_lstSignal;

//	typedef std::set<CSceneObject*> TTestSet;
//	TTestSet m_TestSet;

//	typedef std::set<CNpc*> T155Set;
//	T155Set m_155Set;
};

inline INT32 CRegion::GetRegionX(void)
{
	return m_nRegionX;
}

inline INT32 CRegion::GetRegionY(void)
{
	return m_nRegionY;
}

inline CRegion* CRegion::GetConnectedRegion(INT32 nDirection)
{
	LOG_PROCESS_ERROR(nDirection >= DT_EAST && nDirection < DT_DIRECTION_8_COUNT);

	return m_poConnectedRegion[nDirection];
Exit0:
	return NULL;
}

template<class TFunc>
inline BOOL CRegion::TraverseRole(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstRole.Head().pNext;
    while (pNode != &(m_lstRole.Rear()))
    {
        CRole* poRole = node_cast(CRole*, GetRegionListNode(), pNode);
		if (poRole->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc(poRole);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseHero(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstHero.Head().pNext;
    while (pNode != &(m_lstHero.Rear()))
    {
        CHero* poHero = node_cast(CHero*, GetRegionListNode(), pNode);
		if (poHero->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}

        pNextNode = pNode->pNext;

        nRetCode = rFunc(poHero);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseNpc(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstNpc.Head().pNext;
    while (pNode != &(m_lstNpc.Rear()))
    {
        CNpc* poNpc = node_cast(CNpc*, GetRegionListNode(), pNode);
		if (poNpc->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc(poNpc);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseSignal(TFunc& rFunc)
{
    INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    if ( m_qwSignalBitMask & (1LL << rFunc.nFindSignalType) )
    {
        pNode = m_lstSignal.Head().pNext;
        while (pNode != &(m_lstSignal.Rear()))
        {
            stSignal* poSignal = node_cast(stSignal*, ListNode, pNode);
            BASE_LIST_NODE* pNextNode = pNode->pNext;

            nRetCode = rFunc(poSignal);
            PROCESS_ERROR(nRetCode);

            pNode = pNextNode;
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}
template<class TFunc>
inline BOOL CRegion::TraverseCharacter(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstRole.Head().pNext;
    while (pNode != &(m_lstRole.Rear()))
    {
        CRole* poRole = node_cast(CRole*, GetRegionListNode(), pNode);
		if (poRole->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc((CCharacter*)poRole);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

    pNode = m_lstHero.Head().pNext;
    while (pNode != &(m_lstHero.Rear()))
    {
        CHero* poHero = node_cast(CHero*, GetRegionListNode(), pNode);
		if (poHero->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}

        pNextNode = pNode->pNext;

        nRetCode = rFunc((CCharacter*)poHero);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

    pNode = m_lstNpc.Head().pNext;
    while (pNode != &(m_lstNpc.Rear()))
    {
        CNpc* poNpc = node_cast(CNpc*, GetRegionListNode(), pNode);
		if (poNpc->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc((CCharacter*)poNpc);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }

	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseDoodad(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstDoodad.Head().pNext;
    while (pNode != &(m_lstDoodad.Rear()))
    {
        CDoodad* poDoodad = node_cast(CDoodad*, GetRegionListNode(), pNode);
		if (poDoodad->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc(poDoodad);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }


	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseMissile(TFunc& rFunc)
{
	INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstMissile.Head().pNext;
    while (pNode != &(m_lstMissile.Rear()))
    {
        CMissile* poMissile = node_cast(CMissile*, GetRegionListNode(), pNode);
		if (poMissile->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc(poMissile);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }


	return TRUE;
Exit0:
	return FALSE;
}

template<class TFunc>
inline BOOL CRegion::TraverseDrop(TFunc& rFunc)
{
    INT32 nRetCode = 0;
    BASE_LIST_NODE* pNode = NULL;
    BASE_LIST_NODE* pNextNode = NULL;

    pNode = m_lstDrop.Head().pNext;
    while (pNode != &(m_lstDrop.Rear()))
    {
        CDrop* poDrop = node_cast(CDrop*, GetRegionListNode(), pNode);
		if (poDrop->GetRegion() != this)
		{
			INT3_DBG();
			break;
		}
		pNextNode = pNode->pNext;

        nRetCode = rFunc(poDrop);
        PROCESS_ERROR(nRetCode);

        pNode = pNextNode;
    }


    return TRUE;
Exit0:
    return FALSE;
}

template<class TFunc>
inline BOOL CRegion::Traverse9Region(TFunc& rFunc)
{
	INT32 nRetCode = 0;

	nRetCode = rFunc(this);
	PROCESS_ERROR(nRetCode);

	for (INT32 nIndex = 0; nIndex < DT_DIRECTION_8_COUNT; nIndex++)
	{
		if(!m_poConnectedRegion[nIndex])
            continue;
        nRetCode = rFunc(m_poConnectedRegion[nIndex]);
		PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CRegion::IsActive(INT32 nGameFrame)
{
	return m_nActive > 0 || m_nLastActiveFrame + REGION_INACTIVE_DELAY > nGameFrame;
}

#endif	// _REGION_H_
