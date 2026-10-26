#include "stdafx.h"
#include "block_handler.h"
#include "scene.h"
#include "scene_file_mgr.h"
#include "game_world.h"
#include "message_handler.h"

//CBlockHandler::CBlockHandler(void)
//{
//	m_eBlockType = obtBlockNone;
//	m_eBlockShape = oosNone;
//}
//
//CBlockHandler::~CBlockHandler(void)
//{
//
//}
//
//
//BOOL CBlockHandler::Init(CSceneObject* poSceneObj)
//{
//	LOG_PROCESS_ERROR(m_eBlockType == obtBlockNone);
//	LOG_PROCESS_ERROR(m_BlockGridList.empty());
//
//	m_eBlockType = obtBlockNone;
//	m_eBlockShape = oosNone;
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//void CBlockHandler::UnInit(void)
//{
//	LOG_PROCESS_ERROR(m_BlockGridList.empty());
//
//	m_eBlockType = obtBlockNone;
//
//	CGameWorld::GetInstance().DelBlockHandler(this);
//Exit0:
//	return;
//}
//
//
//BOOL CBlockHandler::EnableBlock(CSceneObject* poSceneObj, INT32 eBlockType, INT32 eBlockShape, INT32 nBlockParam)
//{
//	INT32 nRetCode = 0;
//	CScene* poScene = NULL;
//
//	LOG_PROCESS_ERROR(poSceneObj);
//	LOG_PROCESS_ERROR(eBlockType > obtInvalid && eBlockType < obtTotal);
//	LOG_PROCESS_ERROR(eBlockShape > oosInvalid && eBlockShape < oosTotal);
//
//	poScene = poSceneObj->GetScene();
//	LOG_PROCESS_ERROR(poScene);
//
//	DisableBlock(poSceneObj);
//
//	m_eBlockType = eBlockType;
//	m_eBlockShape = eBlockShape;
//
//	if (eBlockShape == oosLine)
//	{
//		INT64 llSrcX = poSceneObj->GetX() + (INT64)nBlockParam * g_Sin(poSceneObj->GetFaceDirection()) / 2 / SIN_COS_NUMBER;
//		INT64 llSrcY = poSceneObj->GetY() - (INT64)nBlockParam * g_Cos(poSceneObj->GetFaceDirection()) / 2 / SIN_COS_NUMBER;
//		INT64 llSrcZ = poScene->GetLowerZ(llSrcX, llSrcY, poSceneObj->GetZ());
//
//		INT64 llDstX = poSceneObj->GetX() - (INT64)nBlockParam * g_Sin(poSceneObj->GetFaceDirection()) / 2 / SIN_COS_NUMBER;
//		INT64 llDstY = poSceneObj->GetY() + (INT64)nBlockParam * g_Cos(poSceneObj->GetFaceDirection()) / 2 / SIN_COS_NUMBER;
//		INT64 llDstZ = poScene->GetLowerZ(llDstX, llDstY, poSceneObj->GetZ());
//
//		nRetCode = _LineBlockMark(poScene, llSrcX, llSrcY, llSrcZ, llDstX, llDstY, llDstZ);
//		LOG_PROCESS_ERROR(nRetCode);
//
//#ifndef _ROBOT
//		if (CGameWorld::GetInstance().DrawDebugLine())
//		{
//			CCliMessageHandler::GetInstance().DoDrawDebugLine(poSceneObj, 0, llSrcX, llSrcY, llSrcZ, llDstX, llDstY, llDstZ);
//		}
//#endif
//
//	}
//	else if (eBlockShape == oosSquare)
//	{
//		nRetCode = _SquareBlockMark(poScene, poSceneObj->GetX(), poSceneObj->GetY(), poSceneObj->GetZ(), nBlockParam);
//		LOG_PROCESS_ERROR(nRetCode);
//	}
//	else if (eBlockShape == oosSingleGrid)
//	{
//		nRetCode = _ProcessGridBlock(poScene, poSceneObj->GetX(), poSceneObj->GetY(), poSceneObj->GetZ());
//		LOG_PROCESS_ERROR(nRetCode);
//	}
//
//	if (eBlockType == obtBlockAll)
//	{
//		CRegion* poRegion = poSceneObj->GetRegion();
//		LOG_PROCESS_ERROR(poRegion);
//
//		poRegion->IncBlockBulletGrid();
//	}
//
//
//	return TRUE;
//Exit0:
//
//	return FALSE;
//}
//
//void CBlockHandler::DisableBlock(CSceneObject* poSceneObj)
//{
//	INT32 nRetCode = 0;
//	INT32 eBlockType = m_eBlockType;
//	CRegion* poRegion = NULL;
//	CScene* poScene = NULL;
//
//	LOG_PROCESS_ERROR(poSceneObj);
//
//	poScene = poSceneObj->GetScene();
//	LOG_PROCESS_ERROR(poScene);
//
//	poRegion = poSceneObj->GetRegion();
//	LOG_PROCESS_ERROR(poRegion);
//
//	m_eBlockType = obtBlockNone;
//
//	if(m_eBlockShape == oosSingleGrid)
//	{
//		const ZONE_DATA* pZoneData = NULL;
//		const GRID_DATA* pCurGrid = NULL;
//		GRID_INSTANCE_DATA* pCurGridInstance = NULL;
//
//		nRetCode = poScene->GetLowerGrid(poSceneObj->GetX(), poSceneObj->GetY(), poSceneObj->GetZ(), pZoneData, pCurGrid);
//		LOG_PROCESS_ERROR(nRetCode);
//
//		pCurGridInstance = poScene->GetGridInstance(pZoneData, pCurGrid);
//		LOG_PROCESS_ERROR(pCurGridInstance);
//
//		if (eBlockType == obtBlockMoveOnly)
//		{
//			LOG_PROCESS_ERROR(pCurGridInstance->uBlockMoveOnly > 0);
//			pCurGridInstance->uBlockMoveOnly--;
//		}
//		else if (eBlockType == obtBlockAll)
//		{
//			LOG_PROCESS_ERROR(pCurGridInstance->uBlockAll > 0);
//			pCurGridInstance->uBlockAll--;
//		}
//	}
//	else
//	{
//		for (TGridList::iterator itr = m_BlockGridList.begin(); itr != m_BlockGridList.end(); ++itr)
//		{
//			GRID_INSTANCE_DATA* pGrid = *itr;
//			if (eBlockType == obtBlockMoveOnly)
//			{
//				LOG_PROCESS_ERROR(pGrid->uBlockMoveOnly > 0);
//				pGrid->uBlockMoveOnly--;
//			}
//			else if (eBlockType == obtBlockAll)
//			{
//				LOG_PROCESS_ERROR(pGrid->uBlockAll > 0);
//				pGrid->uBlockAll--;
//			}
//		}
//
//		m_BlockGridList.clear();
//	}
//
//	if (eBlockType == obtBlockAll)
//	{
//		poRegion->DecBlockBulletGrid();
//	}
//
//Exit0:
//	return;
//}
//
//BOOL CBlockHandler::_LineBlockMark(CScene* poScene, INT64 llSrcX, INT64 llSrcY, INT64 llSrcZ, INT64 llDstX, INT64 llDstY, INT64 llDstZ)
//{
//	INT32 nRetCode = 0;
//
//	const GRID_DATA* pSrcGrid = NULL;
//	const ZONE_DATA* pSrcZone = NULL;
//
//	const GRID_DATA* pDstGrid = NULL;
//	const ZONE_DATA* pDstZone = NULL;
//
//	const ZONE_DATA* pZoneData = NULL;
//
//	const GRID_DATA* pCurGrid = NULL;
//	GRID_INSTANCE_DATA* pCurGridInstance = NULL;
//
//	INT64 llStepX = 0, llStepY = 0, llStepZ = 0;
//	INT32 nSrcZoneX = 0, nSrcZoneY = 0, nDstZoneX = 0, nDstZoneY = 0;
//
//	llSrcX = llSrcX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//	llSrcY = llSrcY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//
//	llDstX = llDstX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//	llDstY = llDstY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//
//	INT64 nGridSrcXInZone = (llSrcX / GRID_WIDTH) % GRID_PER_ZONE;
//	INT64 nGridSrcYInZone = (llSrcY / GRID_WIDTH) % GRID_PER_ZONE;
//
//	INT64 nGridDstXInZone = (llDstX / GRID_WIDTH) % GRID_PER_ZONE;
//	INT64 nGridDstYInZone = (llDstY / GRID_WIDTH) % GRID_PER_ZONE;
//
//	INT64 llDetX = llDstX - llSrcX;
//	INT64 llDetY = llDstY - llSrcY;
//	INT64 llDetZ = llDstZ - llSrcZ;
//
//	if(llDetX == 0 && llDetY == 0)
//		return FALSE;
//
//	nSrcZoneX = (INT32)(llSrcX / ZONE_WIDTH);
//	nSrcZoneY = (INT32)(llSrcY / ZONE_WIDTH);
//
//	nDstZoneX = (INT32)(llDstX / ZONE_WIDTH);
//	nDstZoneY = (INT32)(llDstY / ZONE_WIDTH);
//
//	LOG_PROCESS_ERROR(poScene);
//	LOG_PROCESS_ERROR(poScene->GetStaticData());
//
//	pZoneData = poScene->GetStaticData()->GetZoneData(nSrcZoneX, nSrcZoneY);
//	LOG_PROCESS_ERROR(pZoneData != NULL);
//
//	pSrcGrid = &pZoneData->GridList[pZoneData->GroundGrid[nGridSrcXInZone][nGridSrcYInZone]];
//
//	pZoneData = poScene->GetStaticData()->GetZoneData(nDstZoneX, nDstZoneY);
//	PROCESS_ERROR(pZoneData != NULL);
//
//	pDstGrid = &pZoneData->GridList[pZoneData->GroundGrid[nGridDstXInZone][nGridDstYInZone]];
//
//	if(g_Abs(llDetX) >= g_Abs(llDetY))
//	{
//		llStepX = llDetX >= 0 ? GRID_WIDTH : -GRID_WIDTH;
//		llStepY = llDetY * llStepX / llDetX;
//
//		if(llDetZ != 0)
//			llStepZ = llDetZ * llStepX / llDetZ;
//	}
//	else
//	{
//		llStepY = llDetY >= 0 ? GRID_WIDTH : -GRID_WIDTH;
//		llStepX = llDetX * llStepY / llDetY;
//
//		if(llDetZ != 0)
//			llStepZ = llDetZ * llStepY / llDetY;
//	}
//
//	pCurGrid = pSrcGrid;
//
//	while(nSrcZoneX != nDstZoneX || nSrcZoneY != nDstZoneY || nGridSrcXInZone != nGridDstXInZone || nGridSrcYInZone != nGridDstYInZone)
//	{
//		INT64 llNextX = 0, llNextY = 0, llNextZ = 0;
//		if(nSrcZoneX == nDstZoneX && nSrcZoneY == nDstZoneY)
//		{
//			if(nGridSrcXInZone == nGridDstXInZone)
//				llStepX = 0;
//			if(nGridSrcYInZone == nGridDstYInZone)
//				llStepY = 0;
//		}
//
//		llSrcX += llStepX;
//		llSrcY += llStepY;
//		llSrcZ += llStepZ;
//
//
//		nSrcZoneX = (INT32)(llSrcX / ZONE_WIDTH);
//		nSrcZoneY = (INT32)(llSrcY / ZONE_WIDTH);
//
//		nGridSrcXInZone = (llSrcX / GRID_WIDTH) % GRID_PER_ZONE;
//		nGridSrcYInZone = (llSrcY / GRID_WIDTH) % GRID_PER_ZONE;
//
//		nRetCode = _ProcessGridBlock(poScene, llSrcX, llSrcY, llSrcZ);
//		LOG_CHECK_ERROR(nRetCode);
//
//		llNextX = llSrcX + llStepX;
//		llNextY = llSrcY + llStepY;
//		llNextZ = llSrcZ + llStepZ;
//
//		if(llNextX / GRID_WIDTH * GRID_WIDTH != llSrcX && llNextY / GRID_WIDTH * GRID_WIDTH != llSrcY)
//		{
//			nRetCode = _ProcessGridBlock(poScene, llNextX, llSrcY, llNextZ);
//			LOG_CHECK_ERROR(nRetCode);
//		}
//	}
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//BOOL CBlockHandler::_SquareBlockMark(CScene* poScene, INT64 llCenterX, INT64 llCenterY, INT64 llCenterZ, INT64 llWidth)
//{
//	INT32 nRetCode = 0;
//	const ZONE_DATA* pZoneData = NULL;
//	const GRID_DATA* pCurGrid = NULL;
//	GRID_INSTANCE_DATA* pCurGridInstance = NULL;
//
//	llCenterX = llCenterX / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//	llCenterY = llCenterY / GRID_WIDTH * GRID_WIDTH + GRID_WIDTH / 2;
//	llWidth = llWidth / GRID_WIDTH * GRID_WIDTH;
//
//	for(INT64 llX = llCenterX - llWidth / 2; llX <= llCenterX + llWidth / 2; llX += GRID_WIDTH)
//	{
//		nRetCode = _ProcessGridBlock(poScene, llX, llCenterY + llWidth / 2, llCenterZ + GRID_WIDTH);
//		LOG_CHECK_ERROR(nRetCode);
//
//		nRetCode = _ProcessGridBlock(poScene, llX, llCenterY - llWidth / 2, llCenterZ + GRID_WIDTH);
//		LOG_CHECK_ERROR(nRetCode);
//	}
//
//	for(INT64 llY = llCenterY - llWidth / 2 + GRID_WIDTH; llY <= llCenterY + llWidth / 2 - GRID_WIDTH; llY += GRID_WIDTH)
//	{
//		nRetCode = _ProcessGridBlock(poScene, llCenterX - llWidth / 2, llY, llCenterZ + GRID_WIDTH);
//		LOG_CHECK_ERROR(nRetCode);
//
//		nRetCode = _ProcessGridBlock(poScene, llCenterX + llWidth / 2, llY, llCenterZ + GRID_WIDTH);
//		LOG_CHECK_ERROR(nRetCode);
//	}
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//BOOL CBlockHandler::_ProcessGridBlock(CScene* poScene, INT64 llX, INT64 llY, INT64 llZ)
//{
//	INT32 nRetCode = 0;
//	const ZONE_DATA* pZoneData = NULL;
//	const GRID_DATA* pCurGrid = NULL;
//	GRID_INSTANCE_DATA* pCurGridInstance = NULL;
//
//	LOG_PROCESS_ERROR(poScene);
//
//	nRetCode = poScene->GetLowerGrid(llX, llY, llZ, pZoneData, pCurGrid);
//	LOG_PROCESS_ERROR(nRetCode);
//
//	pCurGridInstance = poScene->GetGridInstance(pZoneData, pCurGrid);
//	LOG_PROCESS_ERROR(pCurGridInstance);
//
//	if(m_eBlockType == obtBlockMoveOnly)
//	{
//		LOG_PROCESS_ERROR(pCurGridInstance->uBlockMoveOnly < MAX_BLOCK_PER_GRID);
//		pCurGridInstance->uBlockMoveOnly++;
//	}
//	else if (m_eBlockType == obtBlockAll)
//	{
//		LOG_PROCESS_ERROR(pCurGridInstance->uBlockAll < MAX_BLOCK_PER_GRID);
//		pCurGridInstance->uBlockAll++;
//	}
//
//	if(m_eBlockShape != oosSingleGrid)
//		m_BlockGridList.push_back(pCurGridInstance);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
