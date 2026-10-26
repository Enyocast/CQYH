#include "stdafx.h"
#include "ms_guild.h"
#include "guild_db_def_v_4.h"

#include "ms_guild_mgr.h"
#include "manageserver.h"
#include "server_config.h"

using namespace GUILD_DEF_VER_4;

BOOL CMsGuild::LoadGuild_v4(const char *pcData)
{
    INT32       nRetCode = 0;
    GUILD_DB_DATA   *pData = NULL;
    UINT32      dwRealSize = 0;

    LOG_PROCESS_ERROR(pcData);
    pData = (GUILD_DB_DATA *)pcData;

    LOG_PROCESS_ERROR(pData->dwVersion == 4);

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
            nRetCode = LoadDiplomat_v1(pcBlockData, dwBlockSize);
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

BOOL CMsGuild::LoadBase_v4(const char *pcData, UINT32 dwSize)
{
    const GUILD_DB_BASE   *pBase = (const GUILD_DB_BASE*)pcData;

    LOG_PROCESS_ERROR(pBase);
    LOG_PROCESS_ERROR(GUILD_POSITION_COUNT >= sizeof(pBase->wStorageRight) / sizeof(pBase->wStorageRight[0]));
    LOG_PROCESS_ERROR(MAX_GUILD_VARIABLE_COUNT >= sizeof(pBase->nVariables) / sizeof(pBase->nVariables[0]));
    LOG_PROCESS_ERROR(GUILD_ACHI_TYPE_NUM == sizeof(pBase->byAchievement) / sizeof(pBase->byAchievement[0]));

    m_dwRoutineConsumeTime = pBase->dwRoutineConsumeTime;
    m_nState = pBase->nState;
    m_nGuildMoney = pBase->nMoney;
    m_nWood = pBase->nWood;
    m_nHerb = pBase->nHerb;
    m_nCrystal = pBase->nCrystal;
    m_nSilver = pBase->nSilver;
    m_dwCalculateResourceTime = pBase->dwCalculateResourceTime;
    for (INT32 i = 0; i < GUILD_POSITION_COUNT; ++i)
        m_wStorageRight[i] = pBase->wStorageRight[i];
    for (INT32 i = 0; i < MAX_GUILD_VARIABLE_COUNT; ++i)
        m_arrVariables[i] = pBase->nVariables[i];
    for (INT32 i = 0; i < MAX_SABAC_ENROLL_COUNT; ++i)
        m_dwSabacEnrollTime[i] = pBase->dwSabacEnrollTime[i];
	m_bOccupiedSabac = (BOOL)pBase->byOccupiedSabac;

	if (g_ServerConfig.GroupConfig[m_nSvrGroupID].bClearGlobalData)
		m_bOccupiedSabac = FALSE;

	if (m_bOccupiedSabac)
        CManageServer::GetInstance().SetSabacGuildID(m_nSvrGroupID, m_dwID);

    memset(m_Achievement, 0, GUILD_ACHI_TYPE_NUM);
    for (INT32 i = 0; i < 6; i++)
        m_Achievement[i] = pBase->byAchievement[i];

    LOG_PROCESS_ERROR(sizeof(GUILD_DB_BASE) == dwSize);

    return TRUE;
Exit0:
    return FALSE;
}
