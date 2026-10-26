#include "stdafx.h"
#include "missile_data.h"
#include "scene_def.h"
#include "spell_def.h"
#include "modifier_def.h"
#include "script_mgr.h"

BOOL MISSILE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, MISSILE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("ID", m_nTemplateID);
	READ_INT("MoveType", m_nAttr[matMoveType]);
	READ_SPEED("Speed", m_nAttr[matMoveSpeed]);
	READ_LENGTH("Height", m_nAttr[matHeight]);
	READ_INT("LifeTime", m_nAttr[matLifeTime]);
	READ_INT("MaxCollisionCount", m_nAttr[matMaxCollisionCount]);
	READ_INT("MaxTargetCountPerCollision", m_nAttr[matMaxTargetCountPerCollision]);
	READ_INT("RangeType", m_nAttr[matRangeType]);
	READ_INT("RangeParam1", m_nAttr[matRangeParam1]);
	READ_INT("RangeParam2", m_nAttr[matRangeParam2]);
	READ_INT("RangeParam3", m_nAttr[matRangeParam3]);
	//READ_INT("ObstacleShape", m_nAttr[matBlockShape]);
	//READ_LENGTH("ObstacleParam", m_nAttr[matBlockParam]);
	READ_INT("OffsetDirection", m_nAttr[matOffsetDirection]);
	READ_LENGTH("OffsetDistance", m_nAttr[matOffsetDistance]);

	READ_INT("HOffsetGrids", m_nAttr[matHOffsetGrids]);
	READ_INT("VOffsetGrids", m_nAttr[matVOffsetGrids]);

	READ_INT("Interval", m_nAttr[matInterval]);
	READ_INT("Delay", m_nAttr[matDelay]);
	READ_INT("OnInitID", m_nAttr[matOnInit]);
	READ_INT("OnCreateID", m_nAttr[matOnCreate]);
	READ_INT("OnCollisionID", m_nAttr[matOnScan]);
	READ_INT("OnTimeupID", m_nAttr[matOnTimeup]);
	READ_INT("OnRemoveID", m_nAttr[matOnRemove]);
	READ_INT("OnCharEnterID", m_nAttr[matOnCharEnter]);
	READ_INT("OnCharLeaveID", m_nAttr[matOnCharLeave]);

	READ_INT("NotMultiEffeect", m_nAttr[matNotMultiEffect]);
	READ_INT("NotHitLastTarget", m_nAttr[matNotHitLastTarget]);
//	READ_INT("BlockType", m_nAttr[matBlockType]);

//	READ_END(m_nTemplateID);
	rnID = pData->m_nTemplateID;
	return TRUE;
Exit0:
	rnID = pData->m_nTemplateID;
	return FALSE;
}

