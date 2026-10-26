#include "stdafx.h"
#include "missile.h"
#include "math_ex.h"
#include "id_def.h"
#include "missile_data.h"
#include "scene.h"
#include "region.h"
#include "npc.h"
#include "role.h"
#include "doodad.h"
#include "scene.h"
#include "game_world.h"
#include "level_data.h"
#include "modifier_tree.h"
#include "message_handler.h"
#include "scene_file_mgr.h"
#include "spell_config.h"

CMissile::CMissile()
{
	m_llDestX = 0;
	m_llDestY = 0;
	m_llDestZ = 0;
	m_nMoveTimer = 0;
	m_nLifeTimeFrm = 0;
	m_nCollisionCount = 0;
	m_MoveFunc[mmtLine] = &CMissile::_LineMove;
	m_MoveFunc[mmtAccordingToTerrain] = &CMissile::_AccordingToTerrainMove;
	m_MoveFunc[mmtStatic] = &CMissile::_NoMove;
	m_MoveFunc[mmtLockTarget] = &CMissile::_LockTargetMove;
	m_dwOwnerID = 0;

	m_nSpellSerial = 0;
	m_nCastSerial = 0;
	m_nEffectSerial = 0;
	m_bHitTarget = FALSE;
	m_dwLockedTargetID = 0;
	m_dwLastTargetID = 0;
	m_poPendingChar = NULL;

	memset(&m_MissileData, 0, sizeof(m_MissileData));
	memset(&m_SpellData, 0, sizeof(m_SpellData));
}

CMissile::~CMissile()
{
	UnInit();
}

BOOL CMissile::Init(const MISSILE_DATA* poMissileData, CCharacter* poOwner, CSpellInstance* poSpell, INT64 llInitX, INT64 llInitY, INT64 llInitZ, CSceneObject* poTarget, INT32 nLifeFrm)
{
	INT32 nRetCode = 0;
	INT32 nDirection = 0;
	
	LOG_PROCESS_ERROR(poTarget);

	nDirection = g_GetDirection(llInitX, llInitY, poTarget->GetX(), poTarget->GetY());

	nRetCode = Init(poMissileData, poOwner, poSpell, llInitX, llInitY, llInitZ, nDirection, nLifeFrm);
	LOG_PROCESS_ERROR(nRetCode);

	m_dwLockedTargetID = poTarget->GetObjID();
	m_nMoveTimer = 0;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::Init(const MISSILE_DATA* poMissileData, CCharacter* poOwner, CSpellInstance* poSpell, INT64 llInitX, INT64 llInitY, INT64 llInitZ, INT32 nDirection, INT32 nNewLifeFrm)
{
	INT32 nRetCode = 0;
	INT32 nIntervalFrm = 0;
	INT32 nDelayFrm = 0;
	INT64 llMoveDist = 0;
	m_bHitTarget = FALSE;

	m_dwLastTargetID = 0;
	m_nLifeTimeFrm = 0;
	
	CScene* poScene = NULL;
	LOG_PROCESS_ERROR(poMissileData);
	LOG_PROCESS_ERROR(poSpell);

	m_AffectedList.clear();

	nRetCode = CSceneObject::Init(CGameWorld::GetInstance().GetMissileID(this));
	LOG_PROCESS_ERROR(nRetCode);

	m_dwOwnerID = poOwner->GetObjID();
	m_dwLockedTargetID = 0;
	m_nCollisionCount = 0;
	m_poScene = poOwner->GetScene();

	m_nSpellSerial = poSpell->GetSpellSerial();
	m_nCastSerial = poSpell->GetCastSerial();
	m_nEffectSerial = poSpell->GetEffectSerial();

	memcpy(&m_MissileData, poMissileData, sizeof(MISSILE_DATA));
	poSpell->CopyData(&m_SpellData);
	m_ExtraSpellParam = *poSpell->GetExParam();

	m_nFaceDirection = nDirection;
	llInitX = llInitX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	llInitY = llInitY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;

	if (m_MissileData.m_nAttr[matMoveType] == mmtStatic)
	{
		llInitZ = m_poScene->GetLowerZ(llInitX, llInitY, llInitZ + GRID_WIDTH);
	}

	GetOffsetedPos(llInitX, llInitY, nDirection, GetAttr(matHOffsetGrids), GetAttr(matVOffsetGrids), llInitX, llInitY);

	SetX(llInitX);
	SetY(llInitY);
	SetZ(llInitZ);

	if (poMissileData->m_nAttr[matMoveSpeed] != 0)
		llMoveDist = CONVERT_TIME(poMissileData->m_nAttr[matLifeTime]) * GRID_WIDTH / poMissileData->m_nAttr[matMoveSpeed];
	else
		llMoveDist = 0;

	m_llDestX = llInitX + llMoveDist * g_Cos(nDirection) / SIN_COS_NUMBER;
	m_llDestY = llInitY + llMoveDist * g_Sin(nDirection) / SIN_COS_NUMBER;
	m_llDestZ = llInitZ + GRID_WIDTH;
	m_llDestX = m_llDestX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	m_llDestY = m_llDestY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
	m_nMoveTimer = 0;

	poScene = poOwner->GetScene();
	LOG_PROCESS_ERROR(poScene);

	nRetCode = CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnInit], this, &m_ExtraSpellParam);
	LOG_PROCESS_ERROR(nRetCode >= 0);

	m_nLifeTimeFrm = CONVERT_TIME(m_MissileData.m_nAttr[matLifeTime]);//GetLifeTimeFrm();
	if(nNewLifeFrm != 0)
	{
		m_nLifeTimeFrm = nNewLifeFrm;
	}

	nRetCode = poScene->AddMissile(this);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = m_Scanner.Init(poOwner, this, poSpell, m_nFaceDirection, llInitX, llInitY, llInitZ);
	LOG_PROCESS_ERROR(nRetCode);

#ifndef _ROBOT
	if (m_MissileData.m_nAttr[matMoveType] == mmtStatic)
	{
		nRetCode = _ProcessPlacedGrid();
		PROCESS_ERROR(nRetCode);
	}
#endif //_ROBOT

	nRetCode = CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnCreate], this, &m_ExtraSpellParam);
	LOG_PROCESS_ERROR(nRetCode >= 0);

	nIntervalFrm = GetIntervalFrm();
	nDelayFrm = GetDelayFrm();

	m_LifeTimeTimer.Enable(m_nLifeTimeFrm, 1, CGameWorld::GetInstance().GetGameFrame(), m_nLifeTimeFrm);

	if(nIntervalFrm > 0)
		m_IntervalTimer.Enable(nIntervalFrm, m_nLifeTimeFrm / nIntervalFrm, CGameWorld::GetInstance().GetGameFrame(), nDelayFrm);

	m_poPendingChar = NULL;

	//DBG("init missile id: %u, pos: (%d, %d)", GetObjID(), m_llX / GRID_WIDTH, m_llY / GRID_WIDTH);

	m_dwInitFrm = CGameWorld::GetInstance().GetGameFrame();

	return TRUE;
Exit0:
	if (m_poScene)
		DeleteSelf();
	else
	{
		UnInit();
		CGameWorld::GetInstance().DelMissile(this);
	}

	return FALSE;
}

BOOL CMissile::UnInit(void)
{
	INT32 nRetCode = 0;


	m_PlacedGridList.clear();

	m_LifeTimeTimer.Disable();

	m_Scanner.UnInit();

	nRetCode = CSceneObject::UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
}

BOOL CMissile::MainLoop(void)
{
	INT32 nRetCode = 0;

	CCharacter* poOwner = CGameWorld::GetInstance().FindValidCharacter(m_dwOwnerID);
	PROCESS_ERROR(poOwner && m_poScene == poOwner->GetScene()/* && poOwner->GetDistance3D(m_llX, m_llY, m_llZ) < MAX_SPELL_EFFECT_DISTANCE * MAX_SPELL_EFFECT_DISTANCE*/);

	if (m_IntervalTimer.Trig(CGameWorld::GetInstance().GetGameFrame()))
	{
		CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnTimeup], this, &m_ExtraSpellParam);
	}

	nRetCode = m_LifeTimeTimer.Trig(CGameWorld::GetInstance().GetGameFrame());
	PROCESS_ERROR(!nRetCode);

	m_BulletList.clear();

	LOG_PROCESS_ERROR(m_MissileData.m_nAttr[matMoveType] > mmtInvalid && m_MissileData.m_nAttr[matMoveType] < mmtTotal);

	if (m_nMoveTimer <= CGameWorld::GetInstance().GetGameFrame())
	{
		nRetCode = (this->*m_MoveFunc[m_MissileData.m_nAttr[matMoveType]])();
		LOG_PROCESS_ERROR(nRetCode);
	}

	goto Exit1;
Exit0:
	DeleteSelf();
Exit1:
	if(IsDeleteSelf())
	{
		_OnRemove();
	}

	return TRUE;
}

INT32 CMissile::GetObjType(void)
{
	return otMissile;
}

BOOL CMissile::_LineMove(void)
{
	return FALSE;
}

BOOL CMissile::_NoMove(void)
{
	INT32 nRetCode = 0;
	INT32 nFrm = CGameWorld::GetInstance().GetGameFrame();

	if(nFrm % (GAME_FPS/4) == 0)
	{
		nRetCode = _CheckCollision();
		LOG_PROCESS_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::_LockTargetMove(void)
{
	INT32 nRetCode = 0;

	CCharacter* poTarget = CGameWorld::GetInstance().FindValidCharacter(m_dwLockedTargetID);

	PROCESS_ERROR(!IsDeleteSelf());

	if (poTarget != NULL && !poTarget->IsDead())
	{
		INT64 llGridX = m_llX / GRID_WIDTH;
		INT64 llGridY = m_llY / GRID_WIDTH;

		INT64 llTargetGridX = poTarget->GetX() / GRID_WIDTH;
		INT64 llTargetGridY = poTarget->GetY() / GRID_WIDTH;

		INT64 llGridDiffX = llTargetGridX - llGridX;
		INT64 llGridDiffY = llTargetGridY - llGridY;

		INT64 llDestX = 0, llDestY = 0, llDestZ = m_llZ;

		if (llGridDiffX != 0 || llGridDiffY != 0)
		{
			if (llGridDiffX == 0 || llGridDiffY == 0 || (llGridDiffX == llGridDiffY && llGridDiffX != 0))
			{
				llDestX = poTarget->GetX();
				llDestY = poTarget->GetY();
			}
			else
			{
				INT32 nDirection8 = ConvertToDir8(g_GetDirection(m_llX, m_llY, poTarget->GetX(), poTarget->GetY()));

				INT64 nDiffMin = g_Abs(llGridDiffX) < g_Abs(llGridDiffY) ? g_Abs(llGridDiffX) : g_Abs(llGridDiffY);

				llDestX = m_llX + g_nAdjacentX[nDirection8] * GRID_WIDTH * nDiffMin;
				llDestY = m_llY + g_nAdjacentY[nDirection8] * GRID_WIDTH * nDiffMin;
			}

			if (llDestX / GRID_WIDTH != m_llDestX / GRID_WIDTH || llDestY / GRID_WIDTH != m_llDestY / GRID_WIDTH)
			{
				m_llDestX = llDestX;
				m_llDestY = llDestY;
#ifndef _ROBOT
				CCliMessageHandler::GetInstance().DoMissileMove(this);

//				DBG("missile [%u] target: (%u, %u), role: (%u, %u)", m_dwObjID, m_llDestX / GRID_WIDTH, m_llDestY / GRID_WIDTH, poTarget->GetX() / GRID_WIDTH, poTarget->GetY() / GRID_WIDTH);
#endif	// _ROBOT
			}

		}
	}

	nRetCode = _AccordingToTerrainMove();
	PROCESS_ERROR(nRetCode);

	if (m_MissileData.m_nAttr[matNotHitLastTarget] && m_dwLockedTargetID == m_dwLastTargetID)
	{
		m_dwLockedTargetID = 0;
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::_AccordingToTerrainMove(void)
{
	INT32 nRetCode = 0;

	if (m_llX / GRID_WIDTH != m_llDestX / GRID_WIDTH || m_llY / GRID_WIDTH != m_llDestY / GRID_WIDTH)
	{
		INT32 nDirection8 = ConvertToDir8(g_GetDirection(m_llX, m_llY, m_llDestX, m_llDestY));
		INT64 llDestX = m_llX + g_nAdjacentX[nDirection8] * GRID_WIDTH;
		INT64 llDestY = m_llY + g_nAdjacentY[nDirection8] * GRID_WIDTH;

		nRetCode = _GridMove(llDestX, llDestY);
		PROCESS_ERROR(nRetCode);

//		DBG("missile [%u] pos: (%u, %u)", m_dwObjID, m_llX / GRID_WIDTH, m_llY / GRID_WIDTH);
	}
//	else
//		DBG("missile [%u] reached dest, pos: (%u, %u)", m_dwObjID, m_llX / GRID_WIDTH, m_llY / GRID_WIDTH);

	nRetCode = _CheckCollision();
	PROCESS_ERROR(nRetCode);

	m_nMoveTimer = CGameWorld::GetInstance().GetGameFrame() + m_MissileData.m_nAttr[matMoveSpeed];

	return TRUE;
Exit0:
	DeleteSelf();

	return FALSE;
}

BOOL CMissile::_CheckCollision(void)
{
	CCharacter* caster = NULL;
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(m_poRegion);

	CModifierTree::GetInstance().ApplyGlobalNode(GetAttr(matOnScan), this, &m_ExtraSpellParam);

	if(m_nCollisionCount >= m_MissileData.m_nAttr[matMaxCollisionCount])
	{
//		DBG("collision max: (%u, %u), id: %u", m_llX / GRID_WIDTH, m_llY / GRID_WIDTH, m_dwObjID);
		DeleteSelf();
		return TRUE;
	}

	return TRUE;
Exit0:
	return FALSE;
}

//void CMissile::SetAttack(INT32 x1, INT32 x2)
//{
//	m_nAttackX1 = x1;
//	m_nAttackX2 = x2;
//}

BOOL CMissile::TrigSubSpell(INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ)
{
	INT32 nResult = 0;
	CSpell* poSpell = NULL;

	CCharacter* poOwner = CGameWorld::GetInstance().FindValidCharacter(m_dwOwnerID);
	PROCESS_ERROR(poOwner);

	poSpell = CSpellConfig::GetInstance().FindSpellTemplate(nSpellID, m_SpellData.m_nLevel, 0);
	LOG_PROCESS_ERROR(poSpell);

	nResult = poOwner->CastInstantSpell(this, poSpell, poTarget, nTargetX, nTargetY, nTargetZ);
	PROCESS_ERROR(nResult == errSuccess);

	return TRUE;
Exit0:
	return FALSE;
}

void CMissile::SetLockedTargetID(UINT32 dwTargetID)
{
	if(m_MissileData.m_nAttr[matNotHitLastTarget])
	{
		PROCESS_ERROR(dwTargetID != m_dwLastTargetID);
	}

	m_dwLockedTargetID = dwTargetID;
//	IncrCollisionCount();
Exit0:
	return;
}

BOOL CMissile::AddAffectedTarget(UINT32 dwTargetID)
{
//	SPL("AddAffectedTarget : %d", dwTargetID);

	if(m_dwLastTargetID != dwTargetID)
		m_dwLastTargetID = dwTargetID;
	else
		PROCESS_ERROR(!m_MissileData.m_nAttr[matNotHitLastTarget]);

	if(m_AffectedList.empty() || !m_MissileData.m_nAttr[matNotMultiEffect])
	{
		m_AffectedList.push_back(dwTargetID);
		return TRUE;
	}

	for(TAffectedList::iterator itr = m_AffectedList.begin(); itr != m_AffectedList.end(); ++itr)
	{
		PROCESS_ERROR(*itr != dwTargetID);
	}

	m_AffectedList.push_back(dwTargetID);

	return TRUE;
Exit0:
	SPL("Failed.");
	return FALSE;
}

void CMissile::_OnRemove(void)
{
	CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnRemove], this, &m_ExtraSpellParam);
	UINT32 dwElapseFrm = CGameWorld::GetInstance().GetGameFrame() - m_dwInitFrm;

//	DBG("remove missile pos: (%d, %d), id: %u, elapse: %u, lifefrm: %d", m_llX / GRID_WIDTH, m_llY / GRID_WIDTH, GetObjID(), dwElapseFrm, m_nLifeTimeFrm);

	for (TGridList::iterator itr = m_PlacedGridList.begin(); itr != m_PlacedGridList.end(); ++itr)
	{
		MISSILE_PLACED_GRID& grid = *itr;
		LOG_CHECK_ERROR(grid.pGridInstance);

#ifndef _ROBOT
		m_poScene->RemoveMissilePlacedGrid(grid.llX / GRID_WIDTH, grid.llY / GRID_WIDTH);
#endif //_ROBOT

		if (m_MissileData.m_nAttr[matRangeType] == sprtGridRect)
			grid.pGridInstance->uMissileTag1 = 0;
		else if (m_MissileData.m_nAttr[matRangeType] == sprtGridSingle)
			grid.pGridInstance->uMissileTag2 = 0;
	}

}

void CMissile::AdjustTargetPt(INT64 llDestX, INT64 llDestY, INT64 llDestZ)
{
	m_llDestX = llDestX;
	m_llDestY = llDestY;
	m_llDestZ = llDestZ;

	m_nFaceDirection = g_GetDirection(m_llX, m_llY, llDestX, llDestY);

#ifndef _ROBOT
	CCliMessageHandler::GetInstance().DoMissileMove(this);
#endif // _ROBOT
}

BOOL CMissile::_ChangeRegion(CRegion* poDestRegion)
{
	INT32	nRetCode = 0;
	INT32	nTryDirection = 0;
	INT32	nOldDirection = 0;

	static const INT32 s_nRegionList[DT_DIRECTION_8_COUNT][6] =
	{
		{3,	DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST},								// DT_EAST,
		{5, DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST},	// DT_SOUTH_EAST,
		{3, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST},							// DT_SOUTH,
		{5, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST},	// DT_SOUTH_WEST,
		{3, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST},								// DT_WEST,
		{5, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST},	// DT_NORTH_WEST,
		{3, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST},							// DT_NORTH,
		{5, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST},	// DT_NORTH_EAST,
	};

	LOG_PROCESS_ERROR(poDestRegion);
	LOG_PROCESS_ERROR(m_poRegion);

	nTryDirection = g_GetDirection(m_poRegion->GetRegionX(), m_poRegion->GetRegionY(),
		poDestRegion->GetRegionX(), poDestRegion->GetRegionY()) * DT_DIRECTION_8_COUNT / MAX_DIRECTION_COUNT;

	for (INT32 nIndex = 1; nIndex <= s_nRegionList[nTryDirection][0]; nIndex++)
	{
		CRegion* poOldRegion;
		CRegion* poNewRegion;

		poNewRegion = poDestRegion->GetConnectedRegion(s_nRegionList[nTryDirection][nIndex]);

		nOldDirection = (s_nRegionList[nTryDirection][nIndex] + DT_DIRECTION_8_COUNT / 2) % DT_DIRECTION_8_COUNT;
		poOldRegion = m_poRegion->GetConnectedRegion(nOldDirection);

#ifndef _ROBOT
		if(poNewRegion)
		{
			nRetCode = CCliMessageHandler::GetInstance().DoMissileAppear(this, poNewRegion);
			LOG_CHECK_ERROR(nRetCode);
		}

		if(poOldRegion)
		{
			nRetCode = CCliMessageHandler::GetInstance().DoObjectDisappear(this, poOldRegion, sodtOutOfRange);
			LOG_CHECK_ERROR(nRetCode);
		}
#endif  // _ROBOT
	}

	nRetCode = m_poRegion->RemoveMissile(this);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = poDestRegion->AddMissile(this);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;

}

#ifndef _ROBOT
BOOL CMissile::_ProcessPlacedGrid(void)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(m_poScene);

	if (m_MissileData.m_nAttr[matRangeType] == sprtGridCross)
	{
		nRetCode = _PlacedGridCross();
		PROCESS_ERROR(nRetCode);
	}
	else if (m_MissileData.m_nAttr[matRangeType] == sprtGridSingle)
	{
		nRetCode = _PlacedGridSingle();
		PROCESS_ERROR(nRetCode);
	}

//	switch(m_MissileData.m_nAttr[matRangeType])
//	{
//	case sprtGridLine:
//		nRetCode = _PlacedGridLine();
//		break;
//	case sprtGridRect:
//		nRetCode = _PlacedGridRect();
//		break;
//	case sprtGridCross:
//		nRetCode = _PlacedGridCross();
//		break;
//	case sprtGridX:
//		nRetCode = _PlacedGridX();
//		break;
//	case sprtGridU:
//		nRetCode = _PlacedGridU();
//		break;
//	default:
//		break;
//	}


	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::_PlacedGridLine(void)
{

Exit0:
	return FALSE;
}

BOOL CMissile::_PlacedGridRect(void)
{
	INT32 nRetCode = 0;

	for (INT64 x = m_llX - GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; x < m_llX + GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; x += GRID_WIDTH)
	{
		for (INT64 y = m_llY - GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; y < m_llY + GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; y += GRID_WIDTH)
		{
			_TryPlaceSingleGrid(x, y);
		}
	}

	return TRUE;
}

BOOL CMissile::_PlacedGridCross(void)
{
	INT32 nRetCode = 0;

	for (INT64 x = m_llX - GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; x <= m_llX + GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; x += GRID_WIDTH)
	{
		_TryPlaceSingleGrid(x, m_llY);
	}

	for (INT64 y = m_llY - GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; y <= m_llY + GRID_WIDTH * m_MissileData.m_nAttr[matRangeParam1]; y += GRID_WIDTH)
	{
		if (y == m_llY)
			continue;

		_TryPlaceSingleGrid(m_llX, y);
	}

	return TRUE;
}

BOOL CMissile::_PlacedGridSingle(void)
{
	return _TryPlaceSingleGrid(m_llX, m_llY);
}

BOOL CMissile::_PlacedGridX(void)
{

Exit0:
	return FALSE;
}

BOOL CMissile::_PlacedGridU(void)
{

Exit0:
	return FALSE;
}

BOOL CMissile::_TryPlaceSingleGrid(INT64 x, INT64 y)
{
	INT32 nRetCode = 0;
	const ZONE_DATA* pZoneData = NULL;
	const GRID_DATA* pCurGrid = NULL;
	GRID_INSTANCE_DATA* pCurGridInstance = NULL;
	MISSILE_PLACED_GRID mpg;

	nRetCode = m_poScene->GetLowerGrid(x, y, m_llZ + GRID_WIDTH, pZoneData, pCurGrid);
	LOG_PROCESS_ERROR(nRetCode);

	PROCESS_ERROR(!pCurGrid->bBlockMissile);

	pCurGridInstance = m_poScene->GetGridInstance(pZoneData, pCurGrid);
	LOG_PROCESS_ERROR(pCurGridInstance);

	if(m_MissileData.m_nAttr[matRangeType] == sprtGridRect)
	{
		PROCESS_ERROR(pCurGridInstance->uMissileTag1 == 0);
		pCurGridInstance->uMissileTag1 = 1;
	}

	if(m_MissileData.m_nAttr[matRangeType] == sprtGridSingle)
	{
		PROCESS_ERROR(pCurGridInstance->uMissileTag2 == 0);
		pCurGridInstance->uMissileTag2 = 1;
	}

	nRetCode = m_poScene->AddMissilePlacedGrid(x / GRID_WIDTH, y / GRID_WIDTH, this);
	LOG_PROCESS_ERROR(nRetCode);

	mpg.pGridInstance = pCurGridInstance;
	mpg.llX = x;
	mpg.llY = y;

	m_PlacedGridList.push_back(mpg);

	return TRUE;
Exit0:
	m_Scanner.AddSkippedGrid(x, y);
	return FALSE;
}
#endif //_ROBOT

BOOL CMissile::DoBullet(CCharacter* poOwner, INT32 eBulletType)
{
	LOG_PROCESS_ERROR(m_poScene);

	for (TGridList::iterator itr = m_PlacedGridList.begin(); itr != m_PlacedGridList.end(); ++itr)
	{
		CRegion* poRegion = NULL;

		MISSILE_PLACED_GRID& grid = *itr;
		LOG_PROCESS_ERROR(grid.pGridInstance);

		poRegion = m_poScene->GetRegion(grid.llX / REGION_WIDTH, grid.llY / REGION_WIDTH);
		LOG_PROCESS_ERROR(poRegion);

	}

Exit0:
	return FALSE;
}

BOOL CMissile::OnCharEnter(CCharacter* poChar)
{
	INT32 nRetCode = 0;

	m_poPendingChar = poChar;
	nRetCode = CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnCharEnter], this, &m_ExtraSpellParam);
	m_poPendingChar = NULL;

	PROCESS_ERROR(nRetCode >= 0);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::OnCharLeave(CCharacter* poChar)
{
	INT32 nRetCode = 0;

	m_poPendingChar = poChar;
	nRetCode = CModifierTree::GetInstance().ApplyGlobalNode(m_MissileData.m_nAttr[matOnCharLeave], this, &m_ExtraSpellParam);
	m_poPendingChar = NULL;

	PROCESS_ERROR(nRetCode >= 0);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMissile::_GridMove(INT64 llDestX, INT64 llDestY)
{
	INT32 nRetCode = 0;
	INT32 nDestRegionX;
	INT32 nDestRegionY;
	CRegion* poDestRegion = NULL;
	const ZONE_DATA* pcDestZone = NULL;
	const GRID_DATA* pcDestGrid = NULL;
	GRID_INSTANCE_DATA* pGridInstance = NULL;

	GRID_INSTANCE_DATA* pOldGridInstance = NULL;
	INT64 llOldX = m_llX, llOldY = m_llY;

	LOG_PROCESS_ERROR(m_poScene);

	nRetCode = m_poScene->GetLowerGrid(llDestX, llDestY, m_llZ + GRID_WIDTH, pcDestZone, pcDestGrid);
	PROCESS_ERROR(nRetCode);
	PROCESS_ERROR(!pcDestGrid->bOutOfPoly);

	if (pcDestGrid == m_pcGrid)
	{
		m_llX = llDestX;
		m_llY = llDestY;
	}
	else
	{
#ifndef _ROBOT
		if (pcDestGrid->uDoor > 0)
			PROCESS_ERROR(!m_poScene->IsDoorClosed(pcDestZone->byDoor[pcDestGrid->uDoor]));
#endif	// _ROBOT

		pGridInstance = m_poScene->GetGridInstance(pcDestZone, pcDestGrid);
		LOG_PROCESS_ERROR(pGridInstance);

		switch (m_nBodyType)
		{
		case body0x0:
			break;
		case body1x1:
			PROCESS_ERROR(pGridInstance->uCharRef < MAX_CHAR_PER_GRID);
			if (!pcDestGrid->bNotBlockChar)
				PROCESS_ERROR(pGridInstance->uCharRef == 0);
			break;
		case body3x3:
			nRetCode = CheckAdjGridCharRef(llDestX, llDestY, m_llZ);
			PROCESS_ERROR(nRetCode);
			break;
		}

		nDestRegionX = (INT32)(llDestX / REGION_WIDTH);
		nDestRegionY = (INT32)(llDestY / REGION_WIDTH);

		poDestRegion = m_poScene->GetRegion(nDestRegionX, nDestRegionY);
		LOG_PROCESS_ERROR(poDestRegion);

		nRetCode = ClearGridCharRef();
		LOG_CHECK_ERROR(nRetCode);

		m_llX = llDestX;
		m_llY = llDestY;
		m_llZ = pcDestGrid->uHighLayer * GRID_LAYER_HEIGHT;

		m_pcGrid = pcDestGrid;
		m_pcZone = pcDestZone;

		pOldGridInstance = m_pGridInstance;
		m_pGridInstance = pGridInstance;

		nRetCode = SetGridCharRef();
		LOG_CHECK_ERROR(nRetCode);

		if (poDestRegion != m_poRegion)
		{
			nRetCode = _ChangeRegion(poDestRegion);
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

	return TRUE;
Exit0:
	return FALSE;

}


