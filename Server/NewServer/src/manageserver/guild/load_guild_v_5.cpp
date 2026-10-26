#include "stdafx.h"
#include "ms_guild.h"
#include "guild_db_def_v_5.h"

#include "ms_guild_mgr.h"
#include "manageserver.h"
#include "server_config.h"

using namespace GUILD_DEF_VER_5;

BOOL CMsGuild::LoadGuild_v5(const char *pcData)
{
    INT32       nRetCode = 0;
    GUILD_DB_DATA   *pData = NULL;
    UINT32      dwRealSize = 0;

    LOG_PROCESS_ERROR(pcData);
    pData = (GUILD_DB_DATA *)pcData;

    LOG_PROCESS_ERROR(pData->dwVersion == 5);

    dwRealSize = pData->dwLen - sizeof(GUILD_DB_DATA);

    for (INT32 i = 0; i < gbtTotal; ++i)
    {
        GUILD_DB_DATA_BLOCK *pBlock = &pData->BlockTable[i];

        const char *pcBlockData = &pData->GuildData[pBlock->dwStartOffset];
        UINT32      dwBlockSize = pBlock->dwBlockSize;
        LOG_PROCESS_ERROR(dwBlockSize + pBlock->dwStartOffset <= dwRealSize);

        if (dwBlockSize == 0)
            continue;

        switch (pBlock->byBlockType)
        {
        case gbtBase:
        {
            nRetCode = LoadBase_v4(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtWelfare:
        {
            nRetCode = LoadWelfare_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtBuilding:
        {
            nRetCode = LoadBuilding_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtDiplomat:
        {
            nRetCode = LoadDiplomat_v2(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtDungeon:
        {
            nRetCode = LoadDungeon_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtStorage:
        {
            nRetCode = m_storage.LoadStorage_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtHistory:
        {
            nRetCode = LoadHistory_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        case gbtStorageHistory:
        {
            nRetCode = m_storage.LoadStorageHistory_v1(pcBlockData, dwBlockSize);
            LOG_PROCESS_ERROR(nRetCode);
        }
            break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMsGuild::LoadDiplomat_v2(const char *pcData, UINT32 dwSize)
{
    const GUILD_DB_DIPLOMAT_DATA    *pData = NULL;
    const GUILD_DB_DIPLOMAT *pDiplomat = (const GUILD_DB_DIPLOMAT*)pcData;
    LOG_PROCESS_ERROR(pDiplomat);

    LOG_PROCESS_ERROR(GUILD_MAX_ALLIANCE_NUM >= pDiplomat->byAllianceNum);
    LOG_PROCESS_ERROR(GUILD_MAX_ENEMY_NUM >= pDiplomat->byEnemyNum);

    m_dwRevengeGuildID = pDiplomat->dwRevengeGuildID;
    m_dwAimID = pDiplomat->dwAimID;
    m_dwAttackCD = pDiplomat->dwAttackCD;
    m_dwIntruderID = pDiplomat->dwIntruderID;
    m_dwProtectionTime = pDiplomat->dwProtectionTime;
    m_nMatchWarCount = pDiplomat->byMatchWarCount;
    m_dwMatchWarTime = pDiplomat->dwMatchWarTime;

    m_nAllianceNum = 0;
    m_nEnemyNum = 0;

    pData = (const GUILD_DB_DIPLOMAT_DATA *)pDiplomat->Buffer;
    for (INT32 i = 0; i < pDiplomat->byAllianceNum; ++i)
    {
        m_arrAlliance[i].dwGuildID = pData[i].dwGuildID;
        m_arrAlliance[i].dwEndTime = pData[i].dwEndTime;
        ++m_nAllianceNum;
    }

    pData = (const GUILD_DB_DIPLOMAT_DATA *)(pDiplomat->Buffer + pDiplomat->byAllianceNum * sizeof(GUILD_DB_DIPLOMAT_DATA));
    for (INT32 i = 0; i < pDiplomat->byEnemyNum; ++i)
    {
        m_arrEnemy[i].dwGuildID = pData[i].dwGuildID;
        m_arrEnemy[i].dwEndTime = pData[i].dwEndTime;
        ++m_nEnemyNum;
    }

    LOG_PROCESS_ERROR(dwSize == (sizeof(GUILD_DB_DIPLOMAT) + (pDiplomat->byAllianceNum + pDiplomat->byEnemyNum) * sizeof(GUILD_DB_DIPLOMAT_DATA)));

    return TRUE;
Exit0:
    return FALSE;
}
