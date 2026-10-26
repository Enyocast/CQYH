#include "stdafx.h"
#include "adventure_data.h"

BOOL ADVENTURE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ADVENTURE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
    READ_START();

    READ_INT("ID", nID);

    READ_INT_EXPR("TriggerType", nTriggerType);
    READ_INT_EXPR("VariableID", nVariableID);
    READ_INT("StartTime", dwStartTime);
    READ_INT("EndTime", dwEndTime);
    READ_INT("StartDate", dwStartDate);
    READ_INT("EndDate", dwEndDate);

    for (INT32 nIndex = 0; nIndex < MAX_ADVENTURE_TRIGGER_PARAM; nIndex++)
    {
        char szField[256];

        snprintf(szField, 256, "TriggerParam%d", nIndex);
        READ_INT_EXPR(szField, nTriggerParam[nIndex]);
    }

    READ_INT_EXPR("RewardType", nRewardType);
    for (INT32 nIndex = 0; nIndex < MAX_ADVENTURE_REWARD_PARAM; nIndex++)
    {
        char szField[256];

        snprintf(szField, 256, "RewardParam%d", nIndex);
        READ_INT_EXPR(szField, nRewardParam[nIndex]);
    }

    switch (pData->nRewardType)
    {
    case adrSpawnNpcAtPoint:
		ConvertCoordO2N(pData->SpawnNpcAtPoint.nX, pData->SpawnNpcAtPoint.nY, pData->SpawnNpcAtPoint.nZ);
        pData->SpawnNpcAtPoint.nX = CONVERT_LENGTH(pData->SpawnNpcAtPoint.nX);
        pData->SpawnNpcAtPoint.nY = CONVERT_LENGTH(pData->SpawnNpcAtPoint.nY);
        pData->SpawnNpcAtPoint.nZ = CONVERT_LENGTH(pData->SpawnNpcAtPoint.nZ);
        break;
    case adrSpawnNpcNearby:
        pData->SpawnNpcNearby.nMinRange = CONVERT_LENGTH(pData->SpawnNpcNearby.nMinRange);
        pData->SpawnNpcNearby.nMaxRange = CONVERT_LENGTH(pData->SpawnNpcNearby.nMaxRange);
        break;
    case adrSpawnNpcSurround:
        pData->SpawnNpcSurround.nDistance = CONVERT_LENGTH(pData->SpawnNpcSurround.nDistance);
        break;
    case adrSpawnDoodadNearby:
        pData->SpawnDoodadNearby.nMinRange = CONVERT_LENGTH(pData->SpawnDoodadNearby.nMinRange);
        pData->SpawnDoodadNearby.nMaxRange = CONVERT_LENGTH(pData->SpawnDoodadNearby.nMaxRange);
        break;
    case adrSpawnDoodadAtPoint:
		ConvertCoordO2N(pData->SpawnDoodadAtPoint.nX, pData->SpawnDoodadAtPoint.nY, pData->SpawnDoodadAtPoint.nZ);
		pData->SpawnDoodadAtPoint.nX = CONVERT_LENGTH(pData->SpawnDoodadAtPoint.nX);
        pData->SpawnDoodadAtPoint.nY = CONVERT_LENGTH(pData->SpawnDoodadAtPoint.nY);
        pData->SpawnDoodadAtPoint.nZ = CONVERT_LENGTH(pData->SpawnDoodadAtPoint.nZ);
        break;
    }

    READ_INT("NeedNotification", bNeedNotification);
    READ_INT_EXPR("NotificationStringID", dwNotificationStringID);

    READ_END(nID);
}
