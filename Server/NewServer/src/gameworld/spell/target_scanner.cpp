#include "stdafx.h"
#include "target_scanner.h"
#include "spell_data.h"
#include "character.h"
#include "region.h"
#include "game_world.h"

#include "doodad_def.h"
#include "doodad_data.h"
#include "doodad.h"
#include "message_handler.h"

CTargetScanner::SelectFunc CTargetScanner::m_SelectFuncs[] =
{
    NULL,								      // 0
    &CTargetScanner::_CircleSelector,	      // 1
    &CTargetScanner::_SectorSelector,	      // 2
    &CTargetScanner::_ArcSelector,		      // 3
    &CTargetScanner::_RectangleSelector,      // 4
    &CTargetScanner::_RearHalfCircle,	      // 5

    &CTargetScanner::_GridLineSelector,	      // 6
    &CTargetScanner::_GridRectSelector,	      // 7
    &CTargetScanner::_GridCrossSelector,      // 8
    &CTargetScanner::_GridXSelector,	      // 9
    &CTargetScanner::_GridUSelector,	      // 10
    &CTargetScanner::_GridSingleSelector,     // 11
    &CTargetScanner::_GridLineTransverse,     // 12
    &CTargetScanner::_GridMultiLineSelector,  // 13
};

CTargetScanner::DoodadSelectFunc CTargetScanner::m_DoodadSelectFuncs[] =
{
    NULL,										 // 0
    NULL,										 // 1
    NULL,										 // 2
    NULL,										 // 3
    NULL,										 // 4
    NULL,										 // 5

    &CTargetScanner::_DoodadGridLineSelector,	 // 6
    &CTargetScanner::_DoodadGridRectSelector,	 // 7
    &CTargetScanner::_DoodadGridCrossSelector,	 // 8
    &CTargetScanner::_DoodadGridXSelector,		 // 9
    &CTargetScanner::_DoodadGridUSelector,		 // 10
    &CTargetScanner::_DoodadGridSingleSelector,  // 11

    // Three functions may be missing here: 12, 13, and 14
    //...
};


CTargetScanner::CTargetScanner(void)
{
    m_llCenterX = 0;
    m_llCenterY = 0;
    m_llCenterZ = 0;

    m_llTargetX = 0;
    m_llTargetY = 0;
    m_llTargetZ = 0;

    m_nSceneID = 0;
    m_nSceneTemplateID = 0;

    m_eRangeType = 0;
    m_nParam1 = 0;
    m_nParam2 = 0;
    m_nParam3 = 0;
    m_bIgnoreObstacle = FALSE;
    m_bIgnoreTargetRadius = FALSE;

    m_nTargetCount = 0;
    m_nTargetObjTypeLimit = 0;
    m_nRelationshipLimit = 0;
    m_nStanceLimit = 0;
    m_nTargetCheckNode = 0;

    m_poCaster = NULL;
    m_pItrNode = NULL;
    m_pLockedTargetNode = NULL;

    m_nDirection = 0;
    m_bCorpseValid = FALSE;
    m_bUseWeaponRange = FALSE;

    m_TargetList.Clear();
    m_DoodadList.Clear();
    m_PlacedGridList.Clear();
}

CTargetScanner::~CTargetScanner(void)
{
    UnInit();
}

BOOL CTargetScanner::Init(CCharacter* poCaster, INT32 eType, INT32 nParam1, INT32 nParam2, INT32 nParam3, INT32 nDirection, INT32 nTargetObjTypeLimit, INT32 nRelationshipLimit, INT32 nStanceLimit, BOOL bTargetDeadLimit, BOOL bUseWeaponRange, BOOL bIgnoreObstacle, INT32 nTargetCheckNode)
{
    CScene* poScene = NULL;
    LOG_PROCESS_ERROR(poCaster);

    poScene = poCaster->GetScene();
    LOG_PROCESS_ERROR(poScene);

    ClearTarget();

    m_nSceneID = poScene->GetSceneID();
    m_nSceneTemplateID = poScene->GetSceneTempID();

    m_llCenterX = poCaster->GetX();
    m_llCenterY = poCaster->GetY();
    m_llCenterZ = poCaster->GetZ();

    m_llTargetX = 0;
    m_llTargetY = 0;
    m_llTargetZ = 0;

    SetDirection(nDirection);
    m_poCaster = NULL;
    m_pItrNode = NULL;
    m_pLockedTargetNode = NULL;
    m_nTargetCheckNode = nTargetCheckNode;
    m_nTargetCount = 0;

    m_eRangeType = eType;
    LOG_PROCESS_ERROR(m_eRangeType > sprtInvalid && m_eRangeType < sprtTotal);

    m_nParam1 = nParam1;
    m_nParam2 = nParam2;
    m_nParam3 = nParam3;

    m_nTargetObjTypeLimit = nTargetObjTypeLimit;
    m_nRelationshipLimit = nRelationshipLimit;
    m_nStanceLimit = nStanceLimit;
    m_bCorpseValid = bTargetDeadLimit;
    m_bUseWeaponRange = bUseWeaponRange;
    m_bIgnoreObstacle = bIgnoreObstacle;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTargetScanner::Init(CCharacter* poCaster, CSpell* poSpell, INT32 nDirection)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poCaster);
    LOG_PROCESS_ERROR(poSpell);

    m_bIgnoreTargetRadius = poSpell->GetAttr(satIgnoreTargetRadius);

    nRetCode = Init(poCaster, poSpell->GetAttr(satRangeType),
        poSpell->GetAttr(satRangeParam1), poSpell->GetAttr(satRangeParam2), poSpell->GetAngleAttr(satRangeParam3),
        nDirection, poSpell->GetAttr(satTargetObjType), poSpell->GetAttr(satTargetRelationship), poSpell->GetAttr(satTargetStance),
        poSpell->GetAttr(satTargetDeadLimit), poSpell->GetAttr(satUseWeaponRange), poSpell->GetAttr(satIgnoreObstacle), poSpell->GetAttr(satTargetCheckNode));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTargetScanner::Init(CCharacter* poCaster, CMissile* poMissile, CSpell* poSpell, INT32 nDirection, INT64 llTargetX, INT64 llTargetY, INT64 llTargetZ)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poCaster);
    LOG_PROCESS_ERROR(poMissile);
    LOG_PROCESS_ERROR(poSpell);

    m_bIgnoreTargetRadius = poSpell->GetAttr(satIgnoreTargetRadius);

    nRetCode = Init(poCaster, poMissile->GetAttr(matRangeType),
        poMissile->GetAttr(matRangeParam1), poMissile->GetAttr(matRangeParam2), poMissile->GetAttr(matRangeParam3),
        nDirection, poSpell->GetAttr(satTargetObjType), poSpell->GetAttr(satTargetRelationship), poSpell->GetAttr(satTargetStance),
        poSpell->GetAttr(satTargetDeadLimit), FALSE, poSpell->GetAttr(satIgnoreObstacle), poSpell->GetAttr(satTargetCheckNode));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

void CTargetScanner::AddSkippedGrid(INT64 llX, INT64 llY)
{
    PLACED_GRID* poGrid = CGameWorld::GetInstance().NewPlacedGrid();
    LOG_PROCESS_ERROR(poGrid);

    poGrid->llGridX = llX / GRID_WIDTH;
    poGrid->llGridY = llY / GRID_WIDTH;
    poGrid->pNext = NULL;
    poGrid->pPrev = NULL;

    m_PlacedGridList.PushRear(poGrid);
Exit0:
    return;
}

void CTargetScanner::ResetScanner(CSpellInstance* poSpell)
{
    ClearTarget();

    m_eRangeType = poSpell->GetAttr(satRangeType);
    LOG_PROCESS_ERROR(m_eRangeType > sprtInvalid && m_eRangeType < sprtTotal);

    if (m_eRangeType > sprtGridBegin && m_eRangeType < sprtGridEnd)
    {
        m_nParam1 = poSpell->GetAttr(satRangeParam1);
        m_nParam2 = poSpell->GetAttr(satRangeParam2);
        m_nParam3 = poSpell->GetAttr(satRangeParam3);
    }
    else
    {
        m_nParam1 = poSpell->GetLengthAttr(satRangeParam1);
        m_nParam2 = poSpell->GetLengthAttr(satRangeParam2);
        m_nParam3 = poSpell->GetAngleAttr(satRangeParam3);
    }

    m_nRelationshipLimit = poSpell->GetAttr(satTargetRelationship);
    m_bCorpseValid = poSpell->GetAttr(satTargetDeadLimit);
    m_bUseWeaponRange = poSpell->GetAttr(satUseWeaponRange);
    m_bIgnoreTargetRadius = poSpell->GetAttr(satIgnoreTargetRadius);

Exit0:
    return;
}

void CTargetScanner::UnInit(void)
{
    TARGET_NODE* pNode = (TARGET_NODE*)m_TargetList.Head().pNext;
    while (pNode != &(m_TargetList.Rear()))
    {
        TARGET_NODE* pRemoveNode = pNode;
        pNode = (TARGET_NODE*)pNode->pNext;

        CBaseList::Remove(pRemoveNode);
        CGameWorld::GetInstance().DelTargetNode(pRemoveNode);
    }

    m_TargetList.Clear();

    pNode = (TARGET_NODE*)m_DoodadList.Head().pNext;
    while (pNode != &(m_DoodadList.Rear()))
    {
        TARGET_NODE* pRemoveNode = pNode;
        pNode = (TARGET_NODE*)pNode->pNext;

        CBaseList::Remove(pRemoveNode);
        CGameWorld::GetInstance().DelTargetNode(pRemoveNode);
    }

    m_DoodadList.Clear();

    PLACED_GRID* pGridNode = (PLACED_GRID*)m_PlacedGridList.Head().pNext;
    while (pGridNode != &(m_PlacedGridList.Rear()))
    {
        PLACED_GRID* pRemoveNode = pGridNode;
        pGridNode = (PLACED_GRID*)pGridNode->pNext;

        CBaseList::Remove(pRemoveNode);
        CGameWorld::GetInstance().DelPlacedGrid(pRemoveNode);
    }

    m_PlacedGridList.Clear();
}

void CTargetScanner::ClearTarget(void)
{
    TARGET_NODE* pNode = (TARGET_NODE*)m_TargetList.Head().pNext;
    while (pNode != &(m_TargetList.Rear()))
    {
        if (pNode == m_pLockedTargetNode)
        {
            pNode = (TARGET_NODE*)pNode->pNext;
            continue;
        }

        TARGET_NODE* pRemoveNode = pNode;
        pNode = (TARGET_NODE*)pNode->pNext;

        CBaseList::Remove(pRemoveNode);
        CGameWorld::GetInstance().DelTargetNode(pRemoveNode);
    }

    if (m_pLockedTargetNode == NULL)
    {
        m_TargetList.Clear();
        m_pItrNode = NULL;
        m_nTargetCount = 0;
    }

    pNode = (TARGET_NODE*)m_DoodadList.Head().pNext;
    while (pNode != &(m_DoodadList.Rear()))
    {
        TARGET_NODE* pRemoveNode = pNode;
        pNode = (TARGET_NODE*)pNode->pNext;

        CBaseList::Remove(pRemoveNode);
        CGameWorld::GetInstance().DelTargetNode(pRemoveNode);
    }

    m_DoodadList.Clear();

}

void CTargetScanner::LockTarget(CCharacter* poTarget)
{
    if (poTarget != NULL)
    {
        SPL("LockTarget : %d", poTarget->GetObjID());

        m_pLockedTargetNode = NULL;

        TARGET_NODE* pNode = (TARGET_NODE*)m_TargetList.Head().pNext;

        while (pNode != &m_TargetList.Rear())
        {
            if (pNode->dwTargetID == poTarget->GetObjID())
            {
                m_pLockedTargetNode = pNode;
                break;
            }
            pNode = (TARGET_NODE*)pNode->pNext;
        }

        if (m_pLockedTargetNode == NULL)
        {
            m_pLockedTargetNode = AddTarget(poTarget->GetObjID(), 0, poTarget->GetX(), poTarget->GetY(), poTarget->GetZ());
        }

        PROCESS_ERROR(m_pLockedTargetNode);

        m_pLockedTargetNode->bIsLocked = TRUE;

        if (m_eRangeType == sprtCircle)
            SetCenterPt(poTarget->GetX(), poTarget->GetY(), poTarget->GetZ());
    }
    else if (m_nTargetCount > 0)
    {
        PROCESS_ERROR(m_pLockedTargetNode != NULL);

        CBaseList::Remove(m_pLockedTargetNode);
        CGameWorld::GetInstance().DelTargetNode(m_pLockedTargetNode);
        m_pLockedTargetNode = NULL;
        m_nTargetCount--;
    }

Exit0:
    return;
}


TARGET_NODE* CTargetScanner::AddTarget(UINT32 dwObjID, INT64 qwDistSq, INT64 llTargetX, INT64 llTargetY, INT64 llTargetZ)
{
    INT32 nRetCode = 0;
    TARGET_NODE* pNewNode = NULL;//CGameWorld::GetInstance().NewTargetNode();
    TARGET_NODE* pCurNode = NULL;

    CCharacter* poTargetChar = CGameWorld::GetInstance().FindValidCharacter(dwObjID);

    PROCESS_ERROR(poTargetChar);
    PROCESS_ERROR(!poTargetChar->GetFlag().CheckFlag(cfCanNotBeSelectedAsTarget));

    if (!m_bIgnoreObstacle)
    {
        CScene* poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(m_nSceneTemplateID, m_nSceneID));
        PROCESS_ERROR(poScene);

        nRetCode = poScene->IsObstacled(m_llCenterX, m_llCenterY, m_llCenterZ, llTargetX, llTargetY, llTargetZ, FALSE);
        PROCESS_ERROR(!nRetCode);
    }

    pNewNode = CGameWorld::GetInstance().NewTargetNode();
    LOG_PROCESS_ERROR(pNewNode);

    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;
    pNewNode->bIsLocked = FALSE;
    pNewNode->dwTargetID = dwObjID;
    pNewNode->qwTargetDist = qwDistSq;

    pCurNode = (TARGET_NODE*)m_TargetList.Head().pNext;

    while (true)
    {
        PROCESS_SUCCESS(pCurNode->dwTargetID == dwObjID);

        if (pCurNode == &(m_TargetList.Rear()))
        {
            m_TargetList.PushRear(pNewNode);
            break;
        }

        if (pNewNode->qwTargetDist < pCurNode->qwTargetDist)
        {
            m_TargetList.InsertBefore(pNewNode, pCurNode);
            break;
        }

        pCurNode = (TARGET_NODE*)pCurNode->pNext;
    }

    SPL("Add Target: %d", dwObjID);

    m_nTargetCount++;

    BeginTarget();

    return pNewNode;

Exit1:
    if (pNewNode != NULL)
        CGameWorld::GetInstance().DelTargetNode(pNewNode);

    return pCurNode;

Exit0:
    if (pNewNode != NULL)
        CGameWorld::GetInstance().DelTargetNode(pNewNode);

    return NULL;
}

BOOL CTargetScanner::AddDoodad(CDoodad* poDoodad)
{
    INT32 nRetCode = 0;
    TARGET_NODE* pNewNode = NULL;

    pNewNode = CGameWorld::GetInstance().NewTargetNode();
    LOG_PROCESS_ERROR(pNewNode);

    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;
    pNewNode->dwTargetID = poDoodad->GetObjID();
    pNewNode->qwTargetDist = 0;

    m_DoodadList.PushRear(pNewNode);

    return TRUE;
Exit0:
    if (pNewNode != NULL)
        CGameWorld::GetInstance().DelTargetNode(pNewNode);

    return FALSE;
}


// ==================== Separator

inline BOOL CheckPos(INT64 x, INT64 y, INT64 start_x, INT64 start_y, INT64 end_x, INT64 end_y)
{
    return ((end_y - start_y) * x + (start_x - end_x) * y + (end_x * start_y - start_x * end_y)) >= 0;
}

BOOL CTargetScanner::_CircleSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 param1 = GetConvertedParam1();
    INT32 nCollisionRadius = obj->GetRadius();

    if (IgnoreTargetRadius())
        nCollisionRadius = 0;

    INT64 r1 = param1 + nCollisionRadius;
    INT64 r2 = GetConvertedParam2();

    llRangeSq = g_GetDistance2D(m_llTargetX, m_llTargetY, obj->GetX(), obj->GetY());

    if (llRangeSq <= r1 * r1 && llRangeSq >= r2 * r2)
        return TRUE;

    return FALSE;
}

BOOL CTargetScanner::_SectorSelector(CCharacter* obj, INT64& llRangeSq)
{
    BOOL bInrange = FALSE;

    INT64 obj_radius = obj->GetRadius();

    INT32 param1 = GetConvertedParam1();
    INT32 angel = GetParam3();

    INT32 obj_direction = g_GetDirection(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY());
    llRangeSq = g_GetDistance2D(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY());

    INT32 angel_1 = NormalizeDirection(m_nDirection - angel / 2);
    INT32 angel_2 = NormalizeDirection(m_nDirection + angel / 2);

    if (IgnoreTargetRadius())
        obj_radius = 0;

    if (llRangeSq <= obj_radius * obj_radius)
        return TRUE;

    INT64 nSinNumber = llRangeSq > 0 ? obj_radius * obj_radius * SIN_COS_NUMBER / llRangeSq * SIN_COS_NUMBER : 0;

    INT32 offset_direction = g_GetAngle(nSinNumber);
    LOG_PROCESS_ERROR(offset_direction >= 0);

    if (llRangeSq <= (param1 + obj_radius) * (param1 + obj_radius))
    {
        INT32 dir_1 = NormalizeDirection(obj_direction - offset_direction);
        INT32 dir_2 = NormalizeDirection(obj_direction + offset_direction);

        if (angel_1 < angel_2)
        {
            if (dir_1 >= angel_1 && dir_1 <= angel_2)
                bInrange = TRUE;
            if (dir_2 >= angel_1 && dir_2 <= angel_2)
                bInrange = TRUE;
        }
        else
        {
            angel_1 = NormalizeDirection(angel_1 - MAX_DIRECTION_COUNT / 2);
            angel_2 = NormalizeDirection(angel_2 - MAX_DIRECTION_COUNT / 2);

            dir_1 = NormalizeDirection(dir_1 - MAX_DIRECTION_COUNT / 2);
            dir_2 = NormalizeDirection(dir_2 - MAX_DIRECTION_COUNT / 2);

            if (dir_1 >= angel_1 && dir_1 <= angel_2)
                bInrange = TRUE;
            if (dir_2 >= angel_1 && dir_2 <= angel_2)
                bInrange = TRUE;
        }

        if (bInrange)
        {
            return TRUE;
        }
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_ArcSelector(CCharacter* obj, INT64& llRangeSq)
{
    return TRUE;
}

BOOL CTargetScanner::_RectangleSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT64 obj_x = obj->GetX();
    INT64 obj_y = obj->GetY();
    INT64 obj_z = obj->GetZ();
    INT64 obj_r = obj->GetRadius();

    INT32 param1 = GetConvertedParam1();

    if (IgnoreTargetRadius())
        obj_r = 0;

    INT64 length = param1 + 2 * obj_r;
    INT64 width = GetConvertedParam2();
    INT64 width2 = width / 2 + obj_r;

    INT64 xe = m_llCenterX + length * g_Cos(m_nDirection) / SIN_COS_NUMBER;
    INT64 ye = m_llCenterY + length * g_Sin(m_nDirection) / SIN_COS_NUMBER;

    INT64 x1 = m_llCenterX + width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
    INT64 y1 = m_llCenterY - width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

    INT64 x2 = m_llCenterX - width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
    INT64 y2 = m_llCenterY + width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

    INT64 x3 = xe - width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
    INT64 y3 = ye + width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

    INT64 x4 = xe + width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
    INT64 y4 = ye - width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

    BOOL bRet1 = CheckPos(obj_x, obj_y, x1, y1, x2, y2);
    BOOL bRet2 = CheckPos(obj_x, obj_y, x2, y2, x3, y3);
    BOOL bRet3 = CheckPos(obj_x, obj_y, x3, y3, x4, y4);
    BOOL bRet4 = CheckPos(obj_x, obj_y, x4, y4, x1, y1);

    if (bRet1 && bRet2 && bRet3 && bRet4)
    {
        llRangeSq = g_GetDistance2D(obj_x, obj_y, m_llCenterX, m_llCenterY);
        return TRUE;
    }

    return FALSE;
}

BOOL CTargetScanner::_RearHalfCircle(CCharacter* obj, INT64& llRangeSq)
{
    INT32 param1 = GetConvertedParam1();
    INT32 nCollisionRadius = obj->GetRadius();

    if (IgnoreTargetRadius())
        nCollisionRadius = 0;

    INT64 r1 = param1 + nCollisionRadius;
    INT64 r2 = GetConvertedParam2();

    llRangeSq = g_GetDistance2D(m_llTargetX, m_llTargetY, obj->GetX(), obj->GetY());

    if (llRangeSq <= r1 * r1 && llRangeSq >= r2 * r2)
    {
        INT32 nDirection = g_GetDirection(m_llTargetX, m_llTargetY, obj->GetX(), obj->GetY());
        INT32 nDiffDirection = NormalizeDirection(nDirection - m_nDirection);

        if (nDiffDirection >= MAX_DIRECTION_COUNT / 4 && nDiffDirection <= 3 * MAX_DIRECTION_COUNT / 4)
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CTargetScanner::_GridLineSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nDirection8 = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nTargetDirection8 = 0;
    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTgGridX = m_llCenterX / GRID_WIDTH;
    llTgGridY = m_llCenterY / GRID_WIDTH;

    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    nDirection8 = ConvertToDir8(m_nDirection);
    nTargetDirection8 = ConvertToDir8(g_GetDirection(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY()));

    PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= nBodyOffset);

    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    if ((llDetGridX <= nBodyOffset && llDetGridY <= nOffsetLimit)
        || (llDetGridY <= nBodyOffset && llDetGridX <= nOffsetLimit)
        || (g_Abs(llDetGridX - llDetGridY) <= nBodyOffset && g_Min(llDetGridX, llDetGridY) <= nOffsetLimit))
    {
        llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), m_llCenterX, m_llCenterY);
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridRectSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 / 2 + nBodyOffset;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    if (g_Abs(llTgGridX - llObjGridX) <= nOffsetLimit && g_Abs(llTgGridY - llObjGridY) <= nOffsetLimit && g_Abs(llTgGridX - llObjGridX) >= m_nParam2 / 2 && g_Abs(llTgGridY - llObjGridY) >= m_nParam2 / 2)
    {
        llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), m_llTargetX, m_llTargetY);
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridCrossSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nRetCode = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;

    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    PROCESS_ERROR(llDetGridX <= nBodyOffset || llDetGridY <= nBodyOffset);

    if (llDetGridX <= nOffsetLimit && llDetGridY <= nOffsetLimit)
    {
        llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), m_llTargetX, m_llTargetY);
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridXSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    PROCESS_ERROR(llDetGridX <= nOffsetLimit && llDetGridY <= nOffsetLimit);

    if ((llDetGridX == 0 && llDetGridY >= nOffsetLimit) || (llDetGridY == 0 && llDetGridX >= nOffsetLimit))
        goto Exit0;

    llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), m_llTargetX, m_llTargetY);
    return TRUE;

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridUSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nDirection8 = 0;
    INT32 nTargetDirection8 = 0;

    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;

    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    nDirection8 = ConvertToDir8(m_nDirection);
    nTargetDirection8 = ConvertToDir8(g_GetDirection(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY()));

    PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= 2 + nBodyOffset);

    if (g_Abs(llTgGridX - llObjGridX) <= nOffsetLimit && g_Abs(llTgGridY - llObjGridY) <= nOffsetLimit)
    {
        llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), m_llTargetX, m_llTargetY);
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridSingleSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nDirection8 = 0;
    INT32 nTargetDirection8 = 0;

    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;

    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;
    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    llRangeSq = 0;

    if (llDetGridX <= nBodyOffset && llDetGridY <= nBodyOffset)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_GridLineTransverse(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nDirectionRev = 0;
    INT32 nRetCode = 0;
    INT64 llCenterX = 0, llCenterY = 0;
    INT32 nDirection = 0;

    llCenterX = m_llCenterX;
    llCenterY = m_llCenterY;
    nDirection = m_nDirection;

    m_nDirection = NormalizeDirection(m_nDirection + MAX_DIRECTION_COUNT / 4);
    nDirectionRev = NormalizeDirection(m_nDirection - MAX_DIRECTION_COUNT / 2);

    m_llCenterX = m_llTargetX + (INT64)(m_nParam1 + 1) / 2 * GRID_WIDTH * g_Cos(nDirectionRev) / SIN_COS_NUMBER;
    m_llCenterY = m_llTargetY + (INT64)(m_nParam1 + 1) / 2 * GRID_WIDTH * g_Sin(nDirectionRev) / SIN_COS_NUMBER;

    nRetCode = _GridLineSelector(obj, llRangeSq);

    m_nDirection = nDirection;
    m_llCenterX = llCenterX;
    m_llCenterY = llCenterY;

    return nRetCode;
}

BOOL CTargetScanner::_GridMultiLineSelector(CCharacter* obj, INT64& llRangeSq)
{
    INT32 nDirection8 = 0;
    INT64 llTargetX = 0, llTargetY = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nTargetDirection8 = 0;
    INT32 nBodyOffset = obj->GetRadius() / GRID_WIDTH;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    llTargetX = m_llCenterX;
    llTargetY = m_llCenterY;

    INT32 dir_1 = 0;
    INT32 v25 = 0;
    INT64 v30 = 0;
    INT64 v33 = 0;

    INT32 v26[11] = { 0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5 };
    INT32 v27[11] = { 0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5 };

    LOG_PROCESS_ERROR(m_nParam2 < sprtGridSingle);

    nDirection8 = ConvertToDir8(m_nDirection);

    for (INT32 i = 0; i < m_nParam2; i++)
    {
        // This calculates and modifies llTargetX and llTargetY
        GetOffsetedPos(m_llCenterX, m_llCenterY, m_nDirection, v27[i], 0, llTargetX, llTargetY);

        llTgGridX = llTargetX / GRID_WIDTH;
        llTgGridY = llTargetY / GRID_WIDTH;

        llObjGridX = obj->GetX() / GRID_WIDTH;
        llObjGridY = obj->GetY() / GRID_WIDTH;

        if (llTgGridX != llObjGridX || llTgGridY != llObjGridY)
        {
            nTargetDirection8 = ConvertToDir8(g_GetDirection(llTargetX, llTargetY, obj->GetX(), obj->GetY()));

            PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= nBodyOffset);

            llDetGridX = g_Abs(llTgGridX - llObjGridX);
            llDetGridY = g_Abs(llTgGridY - llObjGridY);

            if ((llDetGridX <= nBodyOffset && llDetGridY <= nOffsetLimit)
                || (llDetGridY <= nBodyOffset && llDetGridX <= nOffsetLimit)
                || (g_Abs(llDetGridX - llDetGridY) <= nBodyOffset && g_Min(llDetGridX, llDetGridY) <= nOffsetLimit))
            {
                llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), llTargetX, llTargetY);
                return TRUE;
            }
        }
    }

    if (nDirection8 % 2)
    {
        // The value 3072 was copied from IDA decompilation; its meaning is unclear
        // Probably a fixed direction-conversion offset; investigate other direction-adjustment code and formulas
        dir_1 = NormalizeDirection(m_nDirection + 3072);  

        v25 = ConvertToDir8(dir_1);

        v30 = m_llCenterX + g_nAdjacentX[v25] * GRID_WIDTH;
        v33 = m_llCenterY + g_nAdjacentY[v25] * GRID_WIDTH;

        for (INT32 i = 0; i < m_nParam2 - 1; i++)
        {
            // This calculates and modifies llTargetX and llTargetY
            GetOffsetedPos(v30, v33, m_nDirection, v26[i], 0, llTargetX, llTargetY);

            llTgGridX = llTargetX / GRID_WIDTH;
            llTgGridY = llTargetY / GRID_WIDTH;

            llObjGridX = obj->GetX() / GRID_WIDTH;
            llObjGridY = obj->GetY() / GRID_WIDTH;

            nTargetDirection8 = ConvertToDir8(g_GetDirection(llTargetX, llTargetY, obj->GetX(), obj->GetY()));

            PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= nBodyOffset);

            llDetGridX = g_Abs(llTgGridX - llObjGridX);
            llDetGridY = g_Abs(llTgGridY - llObjGridY);

            if ((llDetGridX <= nBodyOffset && llDetGridY <= nOffsetLimit)
                || (llDetGridY <= nBodyOffset && llDetGridX <= nOffsetLimit)
                || (g_Abs(llDetGridX - llDetGridY) <= nBodyOffset && g_Min(llDetGridX, llDetGridY) <= nOffsetLimit))
            {
                llRangeSq = g_GetDistance2D(obj->GetX(), obj->GetY(), llTargetX, llTargetY);
                return TRUE;
            }
        }
    }

Exit0:
    return FALSE;
}


// ==================== Separator

INT64 CTargetScanner::CheckTarget(CCharacter* poCaster, CCharacter* poTarget)
{
    INT32 nRetCode = 0;
    INT64 llRangeSq = 0;

    LOG_PROCESS_ERROR(m_eRangeType > sprtInvalid && m_eRangeType < sprtTotal);

    PROCESS_ERROR(m_SelectFuncs[m_eRangeType] != NULL);

    nRetCode = (this->*m_SelectFuncs[m_eRangeType])(poTarget, llRangeSq);
    PROCESS_ERROR(nRetCode);

    nRetCode = poCaster->CheckTarget(poTarget, m_nTargetObjTypeLimit, m_nRelationshipLimit, m_nStanceLimit, m_bCorpseValid, m_nTargetCheckNode);
    PROCESS_ERROR(nRetCode == errSuccess);

    return llRangeSq;
Exit0:
    return -1;
}

BOOL CTargetScanner::operator()(CCharacter* poObj)
{
    INT32 nRetCode = 0;
    BOOL bInRange = FALSE;
    PLACED_GRID* pGridNode = NULL;
    INT64 llObjGridX = poObj->GetX() / GRID_WIDTH;
    INT64 llObjGridY = poObj->GetY() / GRID_WIDTH;
    INT64 llDist = 0;
    TARGET_NODE* pNode = NULL;

    LOG_PROCESS_ERROR(m_eRangeType > sprtInvalid && m_eRangeType < sprtTotal);

    pGridNode = (PLACED_GRID*)m_PlacedGridList.Head().pNext;
    while (pGridNode != &(m_PlacedGridList.Rear()))
    {
        if (pGridNode->llGridX == llObjGridX && pGridNode->llGridY == llObjGridY)
        {
            bInRange = TRUE;
            break;
        }
        pGridNode = (PLACED_GRID*)pGridNode->pNext;
    }

    PROCESS_ERROR(!bInRange);

    llDist = CheckTarget(m_poCaster, poObj);
    PROCESS_ERROR(llDist >= 0);

    pNode = AddTarget(poObj->GetObjID(), llDist, poObj->GetX(), poObj->GetY(), poObj->GetZ());
    PROCESS_ERROR(pNode);

Exit0:
    return TRUE;
}

BOOL CTargetScanner::operator()(CDoodad* poDoodad)
{
    INT32 nRetCode = 0;
    const DOODAD_DATA* pData = poDoodad->GetDoodadData();
    LOG_PROCESS_ERROR(pData);

    PROCESS_ERROR(m_DoodadSelectFuncs[m_eRangeType] != NULL);

    if (pData->nType == dtDestrucible)
    {
        nRetCode = (this->*m_DoodadSelectFuncs[m_eRangeType])(poDoodad);
        if (nRetCode)
        {
            nRetCode = AddDoodad(poDoodad);
            LOG_PROCESS_ERROR(nRetCode);
        }
    }

Exit0:
    return TRUE;
}

BOOL CTargetScanner::operator()(CRegion* poRegion)
{
    INT32 nRetCode = 0;

    nRetCode = poRegion->TraverseCharacter(*this);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poRegion->TraverseDoodad(*this);
    PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

void CTargetScanner::BeginTarget(void)
{
    m_pItrNode = (TARGET_NODE*)m_TargetList.Head().pNext;
}

TARGET_NODE* CTargetScanner::NextTarget(void)
{
    TARGET_NODE* pNode = NULL;

    PROCESS_ERROR(m_pItrNode != &m_TargetList.Rear());

    pNode = m_pItrNode;

    m_pItrNode = (TARGET_NODE*)m_pItrNode->pNext;

    return pNode;
Exit0:
    return NULL;
}

TARGET_NODE* CTargetScanner::LoopNextTarget(void)
{
    TARGET_NODE* pNode = NULL;

    PROCESS_ERROR(!m_TargetList.IsEmpty());
    LOG_PROCESS_ERROR(m_pItrNode);

    if (m_pItrNode == &m_TargetList.Rear())
    {
        m_pItrNode = (TARGET_NODE*)m_TargetList.Head().pNext;
    }

    pNode = m_pItrNode;

    m_pItrNode = (TARGET_NODE*)m_pItrNode->pNext;

    return pNode;
Exit0:
    return NULL;
}

BOOL CTargetScanner::Scan(CRegion* poRegion, CCharacter* poCaster)
{
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poRegion);
    LOG_PROCESS_ERROR(poCaster);

    m_poCaster = poCaster;

    poRegion->Traverse9Region(*this);

#ifndef _ROBOT
    if (CGameWorld::GetInstance().DrawDebugLine())
    {
        switch (m_eRangeType)
        {
        case sprtCircle:
        {
            for (INT32 nDirection = 0; nDirection < MAX_DIRECTION_COUNT; nDirection += MAX_DIRECTION_COUNT / 16)
            {
                INT64 x = m_llTargetX + (INT64)m_nParam1 * g_Cos(nDirection) / SIN_COS_NUMBER;
                INT64 y = m_llTargetY + (INT64)m_nParam1 * g_Sin(nDirection) / SIN_COS_NUMBER;

#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, m_llTargetX, m_llTargetY, poCaster->GetZ(), x, y, poCaster->GetZ());
#endif
            }

            for (INT32 nDirection = 0; nDirection < MAX_DIRECTION_COUNT; nDirection += MAX_DIRECTION_COUNT / 128)
            {
                INT64 x = m_llTargetX + (INT64)m_nParam2 * g_Cos(nDirection) / SIN_COS_NUMBER;
                INT64 y = m_llTargetY + (INT64)m_nParam2 * g_Sin(nDirection) / SIN_COS_NUMBER;

#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, m_llTargetX, m_llTargetY, poCaster->GetZ(), x, y, poCaster->GetZ());
#endif
            }
        }
        break;
        case sprtSector:
        {
            for (INT32 nDirection = m_nDirection - m_nParam3 / 2; nDirection < m_nDirection + m_nParam3 / 2; nDirection += MAX_DIRECTION_COUNT / 16)
            {
                INT32 d = NormalizeDirection(nDirection);

                INT64 x = m_llCenterX + m_nParam1 * g_Cos(d) / SIN_COS_NUMBER;
                INT64 y = m_llCenterY + m_nParam1 * g_Sin(d) / SIN_COS_NUMBER;

#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, m_llCenterX, m_llCenterY, poCaster->GetZ(), x, y, poCaster->GetZ());
#endif
            }
        }
        break;
        case sprtRectangle:
        {
            INT64 length = m_nParam1;
            INT64 width = m_nParam2;
            INT64 width2 = width / 2;

            INT64 xe = m_llCenterX + length * g_Cos(m_nDirection) / SIN_COS_NUMBER;
            INT64 ye = m_llCenterY + length * g_Sin(m_nDirection) / SIN_COS_NUMBER;

            INT64 x1 = m_llCenterX + width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
            INT64 y1 = m_llCenterY - width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

            INT64 x2 = m_llCenterX - width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
            INT64 y2 = m_llCenterY + width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

            INT64 x3 = xe - width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
            INT64 y3 = ye + width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

            INT64 x4 = xe + width2 * g_Sin(m_nDirection) / SIN_COS_NUMBER;
            INT64 y4 = ye - width2 * g_Cos(m_nDirection) / SIN_COS_NUMBER;

#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, x1, y1, poCaster->GetZ(), x2, y2, poCaster->GetZ());
            CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, x2, y2, poCaster->GetZ(), x3, y3, poCaster->GetZ());
            CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, x3, y3, poCaster->GetZ(), x4, y4, poCaster->GetZ());
            CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, x4, y4, poCaster->GetZ(), x1, y1, poCaster->GetZ());
#endif
        }
        break;
        case sprtGridLineTransverse:
        {
            INT32 nDirection8 = ConvertToDir8(m_nDirection);
            nDirection8 = NormalizeDirection8(nDirection8 + 2);

            INT64 x1 = m_llTargetX + g_nAdjacentX[nDirection8] * GRID_WIDTH * m_nParam1 / 2;
            INT64 y1 = m_llTargetY + g_nAdjacentY[nDirection8] * GRID_WIDTH * m_nParam1 / 2;

            nDirection8 = NormalizeDirection8(m_nDirection - 2);

            INT64 x2 = x1 + g_nAdjacentX[nDirection8] * GRID_WIDTH * m_nParam1;
            INT64 y2 = y1 + g_nAdjacentY[nDirection8] * GRID_WIDTH * m_nParam1;

#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoDrawDebugLine(poCaster, 0, x1, y1, poCaster->GetZ(), x2, y2, poCaster->GetZ());
#endif
        }
        break;
        case sprtGridRect:
            break;
        case sprtGridLine:
            break;
        default:
            break;
        }
    }
#endif //_ROBOT

    m_poCaster = NULL;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridLineSelector(CDoodad* obj)
{
    INT32 nDirection8 = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nTargetDirection8 = 0;
    INT32 nBodyOffset = 0;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    LOG_PROCESS_ERROR(obj);

    nBodyOffset = obj->GetRadius() / GRID_WIDTH;

    llTgGridX = m_llCenterX / GRID_WIDTH;
    llTgGridY = m_llCenterY / GRID_WIDTH;

    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    nDirection8 = ConvertToDir8(m_nDirection);
    nTargetDirection8 = ConvertToDir8(g_GetDirection(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY()));

    PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= nBodyOffset);

    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    if ((llDetGridX <= nBodyOffset && llDetGridY <= nOffsetLimit)
        || (llDetGridY <= nBodyOffset && llDetGridX <= nOffsetLimit)
        || (g_Abs(llDetGridX - llDetGridY) <= nBodyOffset && g_Min(llDetGridX, llDetGridY) <= nOffsetLimit))
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridRectSelector(CDoodad* obj)
{
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT32 nBodyOffset = 0;
    INT32 nOffsetLimit = m_nParam1 / 2 + nBodyOffset;

    LOG_PROCESS_ERROR(obj);

    nBodyOffset = obj->GetRadius() / GRID_WIDTH;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    if (g_Abs(llTgGridX - llObjGridX) <= nOffsetLimit && g_Abs(llTgGridY - llObjGridY) <= nOffsetLimit && g_Abs(llTgGridX - llObjGridX) >= m_nParam2 / 2 && g_Abs(llTgGridY - llObjGridY) >= m_nParam2 / 2)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridCrossSelector(CDoodad* obj)
{
    INT32 nRetCode = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;
    INT32 nBodyOffset = 0;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    LOG_PROCESS_ERROR(obj);

    nBodyOffset = obj->GetRadius() / GRID_WIDTH;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;

    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    PROCESS_ERROR(llDetGridX <= nBodyOffset || llDetGridY <= nBodyOffset);

    if (llDetGridX <= nOffsetLimit && llDetGridY <= nOffsetLimit)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridXSelector(CDoodad* obj)
{
    INT32 nDirection8 = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT32 nTargetDirection8 = 0;

    LOG_PROCESS_ERROR(obj);

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    nDirection8 = ConvertToDir8(m_nDirection);
    nTargetDirection8 = ConvertToDir8(g_GetDirection(m_llTargetX, m_llTargetY, obj->GetX(), obj->GetY()));

    PROCESS_ERROR(g_Abs(nTargetDirection8 - nDirection8) % 2 != 0);

    if (g_Abs(llTgGridX - llObjGridX) <= m_nParam1 && g_Abs(llTgGridY - llObjGridY) <= m_nParam1)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridUSelector(CDoodad* obj)
{
    INT32 nDirection8 = 0;
    INT32 nTargetDirection8 = 0;
    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT32 nBodyOffset = 0;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    LOG_PROCESS_ERROR(obj);

    nBodyOffset = obj->GetRadius() / GRID_WIDTH;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;

    nDirection8 = ConvertToDir8(m_nDirection);
    nTargetDirection8 = ConvertToDir8(g_GetDirection(m_llCenterX, m_llCenterY, obj->GetX(), obj->GetY()));

    PROCESS_ERROR(OffsetDirection8(nDirection8, nTargetDirection8) <= 2 + nBodyOffset);

    if (g_Abs(llTgGridX - llObjGridX) <= nOffsetLimit && g_Abs(llTgGridY - llObjGridY) <= nOffsetLimit)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridSingleSelector(CDoodad* obj)
{
    INT32 nDirection8 = 0;
    INT32 nTargetDirection8 = 0;

    INT64 llTgGridX = 0, llTgGridY = 0;
    INT64 llObjGridX = 0, llObjGridY = 0;
    INT64 llDetGridX = 0, llDetGridY = 0;

    INT32 nBodyOffset = 0;
    INT32 nOffsetLimit = m_nParam1 + nBodyOffset;

    LOG_PROCESS_ERROR(obj);

    nBodyOffset = obj->GetRadius() / GRID_WIDTH;

    llTgGridX = m_llTargetX / GRID_WIDTH;
    llTgGridY = m_llTargetY / GRID_WIDTH;
    llObjGridX = obj->GetX() / GRID_WIDTH;
    llObjGridY = obj->GetY() / GRID_WIDTH;
    llDetGridX = g_Abs(llTgGridX - llObjGridX);
    llDetGridY = g_Abs(llTgGridY - llObjGridY);

    if (llDetGridX <= nBodyOffset && llDetGridY <= nBodyOffset)
    {
        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CTargetScanner::_DoodadGridLineTransverse(CDoodad* obj)
{

Exit0:
    return FALSE;
}


//BOOL CTargetScanner::_DoodadCircleSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* obj)
//{
//	INT64 x, y, z = 0;
//	INT32 param1 = inst->GetConvertedParam1();
//	inst->GetTargetPt(x, y, z);
//
////	if(inst->UseWeaponRange())
////		param1 += caster->GetAttr(catAttackRange);
//
//	INT64 r1 = param1 + obj->GetRadius();
//	INT64 r2 = inst->GetConvertedParam2();//inf->GetAttr(satRangeParam2);
//	//INT64 dist = g_GetDistance3D(x, y, z, obj->GetX(), obj->GetY(), obj->GetZ());
//	INT64 dist = g_GetDistance2D(x, y, obj->GetX(), obj->GetY());
//
//	if(dist <= r1*r1 && dist >= r2*r2)
//		inst->AddDoodad(obj->GetObjID());
//
//	return TRUE;
//}
//
//BOOL CTargetScanner::_DoodadRearHalfCircle(CTargetScanner* inst, CCharacter* caster, CDoodad* target)
//{
//	return TRUE;
//}
//
//BOOL CTargetScanner::_DoodadSectorSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* obj)
//{
//	INT64 x0, y0, z0 = 0;
//	inst->GetCenterPt(x0, y0, z0);
//
//	INT64 obj_radius = obj->GetRadius();
//	INT64 caster_radius = caster->GetRadius();
//
//	INT32 param1 = inst->GetConvertedParam1();
////	if(inst->UseWeaponRange())
////		param1 += caster->GetAttr(catAttackRange);
//
//	INT32 angel = inst->GetParam3();
//
//	INT32 obj_direction = g_GetDirection(x0, y0, obj->GetX(), obj->GetY());
//	INT64 dist = g_GetDistance2D(x0, y0, obj->GetX(), obj->GetY());
//
//	if(dist <= obj_radius * obj_radius)
//	{
//		inst->AddDoodad(obj->GetObjID());
//		return TRUE;
//	}
//
//	INT64 nSinNumber = dist > 0 ? obj_radius * obj_radius * SIN_COS_NUMBER / dist * SIN_COS_NUMBER: 0;
//
//	INT32 offset_direction = g_GetAngle(nSinNumber);
//	LOG_PROCESS_ERROR(offset_direction >= 0);
//
//	if(dist <= (caster_radius + param1)*(caster_radius + param1) + obj_radius*obj_radius)
//	{
//		INT32 nND = NormalizeDirection(abs(obj_direction - inst->m_nDirection));
//		if(nND <= angel/2 || angel/2 + offset_direction >= nND)
//		{
//			inst->AddDoodad(obj->GetObjID());
//			return TRUE;
//		}
//	}
//
//	return TRUE;
//Exit0:
//	return FALSE;
//
//}
//
//BOOL CTargetScanner::_DoodadArcSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* obj)
//{
//	return TRUE;
//}
//
//BOOL CTargetScanner::_DoodadRectangleSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* obj)
//{
//	INT64 x0, y0, z0 = 0;
//	inst->GetCenterPt(x0, y0, z0);
//
//	INT64 obj_x = obj->GetX();
//	INT64 obj_y = obj->GetY();
//	INT64 obj_z = obj->GetZ();
//	INT64 obj_r = obj->GetRadius();
//
//	INT32 nDirection = inst->GetDirection();
//	INT32 param1 = inst->GetConvertedParam1();
////	if(inst->UseWeaponRange())
////		param1 += caster->GetAttr(catAttackRange);
//
//	INT64 length = param1 + 2 * obj_r;
//	INT64 width = inst->GetConvertedParam2();
//	INT64 width2 = width / 2 + obj_r;
//
//	INT64 xe = x0 + length * g_Cos(nDirection) / SIN_COS_NUMBER;
//	INT64 ye = y0 + length * g_Sin(nDirection) / SIN_COS_NUMBER;
//
//	INT64 x1 = x0 + width2 * g_Sin(nDirection) / SIN_COS_NUMBER;
//	INT64 y1 = y0 - width2 * g_Cos(nDirection) / SIN_COS_NUMBER;
//
//	INT64 x2 = x0 - width2 * g_Sin(nDirection) / SIN_COS_NUMBER;
//	INT64 y2 = y0 + width2 * g_Cos(nDirection) / SIN_COS_NUMBER;
//
//	INT64 x3 = xe - width2 * g_Sin(nDirection) / SIN_COS_NUMBER;
//	INT64 y3 = ye + width2 * g_Cos(nDirection) / SIN_COS_NUMBER;
//
//	INT64 x4 = xe + width2 * g_Sin(nDirection) / SIN_COS_NUMBER;
//	INT64 y4 = ye - width2 * g_Cos(nDirection) / SIN_COS_NUMBER;
//
//	BOOL bRet1 = CheckPos(obj_x, obj_y, x1, y1, x2, y2);
//	BOOL bRet2 = CheckPos(obj_x, obj_y, x2, y2, x3, y3);
//	BOOL bRet3 = CheckPos(obj_x, obj_y, x3, y3, x4, y4);
//	BOOL bRet4 = CheckPos(obj_x, obj_y, x4, y4, x1, y1);
//
//	if(bRet1 && bRet2 && bRet3 && bRet4)
//		inst->AddDoodad(obj->GetObjID());
//
//	return TRUE;
//}

CBullet* CTargetScanner::DoSingleBullet(CSpellInstance* poSpell, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, INT32 nBulletType, BOOL bTargetLocked)
{
    INT32 nRetCode = 0;
    CBullet* poBullet = NULL;

    CSceneObject* poStartObj = poFromObj != NULL ? poFromObj : poCaster;

    LOG_PROCESS_ERROR(poSpell);
    LOG_PROCESS_ERROR(poCaster);
    LOG_PROCESS_ERROR(poTarget);

    poBullet = CGameWorld::GetInstance().NewBullet();
    LOG_PROCESS_ERROR(poBullet);

    poBullet->Init(nBulletType, poSpell->GetCastSerial(), poSpell->GetEffectSerial(), 0, poSpell->GetDelayFrm(poStartObj, poTarget));

    nRetCode = poBullet->OnCreate(poSpell, poCaster, poTarget, poFromObj, bTargetLocked);
    PROCESS_ERROR(nRetCode);

    if (poCaster->GetLastTargetID() == 0 && (poBullet->GetBulletType() == betDamage || (poBullet->GetBulletType() == betNone && poBullet->GetSpellAttr(satThreatValue) > 0)))
        poCaster->SetLastTargetID(poTarget->GetObjID());

    return poBullet;
Exit0:
    if (poBullet != NULL)
        poBullet->UnInit();
    return NULL;
}

CBullet* CTargetScanner::DoSingleBullet(CMissile* poMissile, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, INT32 nBulletType)
{
    INT32 nRetCode = 0;
    CBullet* poBullet = NULL;

    CSceneObject* poStartObj = poFromObj != NULL ? poFromObj : poCaster;

    LOG_PROCESS_ERROR(poMissile);
    LOG_PROCESS_ERROR(poCaster);
    LOG_PROCESS_ERROR(poTarget);

    poBullet = CGameWorld::GetInstance().NewBullet();
    LOG_PROCESS_ERROR(poBullet);

    SPL("do single bullet, missile id: %u, pos: (%d, %d)", poMissile->GetObjID(), poMissile->GetX() / GRID_WIDTH, poMissile->GetY() / GRID_WIDTH);

    poBullet->Init(nBulletType, poMissile->GetCastSerial(), poMissile->GetEffectSerial(), 0, 0);

    nRetCode = poBullet->OnCreate(poMissile, poMissile->GetSpellExParam(), poCaster, poTarget, poFromObj, 0);
    PROCESS_ERROR(nRetCode);

    if (poCaster->GetLastTargetID() == 0 && (poBullet->GetBulletType() == betDamage || (poBullet->GetBulletType() == betNone && poBullet->GetSpellAttr(satThreatValue) > 0)))
        poCaster->SetLastTargetID(poTarget->GetObjID());

    return poBullet;
Exit0:
    if (poBullet != NULL)
        poBullet->UnInit();
    return NULL;

}

INT32 CTargetScanner::DoBullet(CSpellInstance* poSpell, CCharacter* poCaster, INT32 nBulletType)
{
    INT32 nCount = 0;
    INT32 nRetCode = 0;

    CCharacter* poTarget = NULL;
    CSceneObject* poLastFromObj = NULL;
    TARGET_NODE* pTargetNode = NULL;
    TARGET_NODE* pDoodadNode = NULL;

    BeginTarget();

    poLastFromObj = CGameWorld::GetInstance().FindValidObj(poSpell->GetFromObjID());
    PROCESS_SUCCESS(poLastFromObj == NULL);

    while ((pTargetNode = NextTarget()) != NULL)
    {
        //		DBG("current target id : %d", dwTargetID);
        poTarget = CGameWorld::GetInstance().FindValidCharacter(pTargetNode->dwTargetID);
        if (poTarget == NULL)
            continue;

        if (nCount >= poSpell->GetAttr(satMaxTargetCount))
            break;

        DoSingleBullet(poSpell, poCaster, poTarget, poLastFromObj, nBulletType, pTargetNode->bIsLocked);

        if (poSpell->GetAttr(satChainEffect))
            poLastFromObj = poTarget;

        nCount++;
    }

    pDoodadNode = (TARGET_NODE*)m_DoodadList.Head().pNext;
    while (pDoodadNode != &(m_DoodadList.Rear()))
    {
        TARGET_NODE* pCurrentNode = pDoodadNode;
        pDoodadNode = (TARGET_NODE*)pDoodadNode->pNext;

        CDoodad* poDoodad = CGameWorld::GetInstance().FindDoodad(pCurrentNode->dwTargetID);
        if (poDoodad == NULL)
            continue;

        poCaster->OpenDoodad(poDoodad, poSpell->GetDelayFrm(poCaster, poDoodad));
    }

Exit1:
    return nCount;
Exit0:
    return -1;
}

INT32 CTargetScanner::DoBullet(CMissile* poMissile, CCharacter* poCaster, INT32 nBulletType)
{
    INT32 nRetCode = 0;
    INT32 nCount = 0;

    CSceneObject* poLastFromObj = NULL;
    TARGET_NODE* pTargetNode = NULL;
    TARGET_NODE* pDoodadNode = NULL;

    poLastFromObj = poMissile;


    BeginTarget();

    while ((pTargetNode = NextTarget()) != 0)
    {
        CCharacter* poCurrentTarget = CGameWorld::GetInstance().FindValidCharacter(pTargetNode->dwTargetID);

        if (poCurrentTarget != NULL && poCaster->CanAttack(poCurrentTarget))
        {
            if (!poMissile->AddAffectedTarget(pTargetNode->dwTargetID))
                continue;

            DoSingleBullet(poMissile, poCaster, poCurrentTarget, poLastFromObj, nBulletType);

            if (poMissile->GetSpellAttr(satChainEffect))
                poLastFromObj = poCurrentTarget;

            poMissile->AddCollisionCount();
            nCount++;

            PROCESS_SUCCESS(poMissile->GetCollisionCount() >= poMissile->GetAttr(matMaxCollisionCount));
            PROCESS_SUCCESS(nCount >= poMissile->GetAttr(matMaxTargetCountPerCollision));
        }
    }

    pDoodadNode = (TARGET_NODE*)m_DoodadList.Head().pNext;
    while (pDoodadNode != &(m_DoodadList.Rear()))
    {
        TARGET_NODE* pCurrentNode = pDoodadNode;
        pDoodadNode = (TARGET_NODE*)pDoodadNode->pNext;

        CDoodad* poDoodad = CGameWorld::GetInstance().FindDoodad(pCurrentNode->dwTargetID);
        if (poDoodad == NULL)
            continue;

        poCaster->OpenDoodad(poDoodad, 0);
    }

Exit1:
    return nCount;
Exit0:
    return -1;
}