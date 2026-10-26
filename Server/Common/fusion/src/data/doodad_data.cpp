#include "stdafx.h"
#include "doodad_data.h"

#include "script_mgr.h"

BOOL DOODAD_DATA::ReadLine(INT32& rnID, const char*& rpcszName, DOODAD_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ID", nTemplateID);
    READ_STR("DisplayName", szName);
	READ_INT("Level", nLevel);
    READ_INT("DoodadType", nType);
    READ_INT("DoodadSubType", nSubType);
	READ_INT_EXPR("BodyType", nBodyType);
    READ_TIME("OperateDuration", nOperateDuration);
    READ_INT("MaxOperateCount", nMaxOpenCount);
    READ_INT("MinOperateCount", nMinOpenCount);
    READ_STR("ScriptName", szScriptName);

	LOG_PROCESS_ERROR(pData->nMinOpenCount > 0 && pData->nMaxOpenCount > 0 && pData->nMaxOpenCount >= pData->nMinOpenCount);

    READ_INT("RequireItemID", nRequireItemID);
    READ_INT("CostItem", bCostItem);
    READ_INT("RequireVarID", nRequireVarID);
    READ_INT("RequireVarValue", nRequireVarValue);
    READ_INT("SpawnNpcID", nSpawnNpcID);
    READ_INT("SpawnNpcChance", nSpawnNpcChance);
    READ_INT("RequireItemID", nRequireItemID);
    READ_INT("AuraID", nAuraID);

	READ_TIME("LifeTime", nLifeFrm);

    pData->pAdventureData = NULL;

    rpcszName = pData->szName;
    READ_END(nTemplateID);
}
