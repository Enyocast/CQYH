#include "stdafx.h"
#include "guild.h"
#include "sql_mgr.h"
#include "define.h"
#include "../../src/manageserver/guild/guild_db_def_v_5.h"
#include "zlib.h"
#include "guild_def.h"
//extern SQL_STMT_DATA g_SqlStmtList;


YY_GUILD_STAT  g_GuildStat;

#define EXPORT_GUILD_BUFFER_LENGTH      (4096)

void _LoadGuild(CSqlMgr& sqlmgr)
{
    INT32 nRetCode = 0;
    FILE    *pFile = NULL;
    char    *pBuffer = NULL;
    INT32   nLength = 0;

    nRetCode = sqlmgr.SyncExecSqlStmt(mysqlSelectGuild, CB_ExportGuild, NULL, "");
    LOG_PROCESS_ERROR(nRetCode);


    for (YY_GUILD_STAT::GUILD_LIST::iterator iter = g_GuildStat.GuildList.begin(); iter != g_GuildStat.GuildList.end(); ++iter)
    {
        nRetCode = sqlmgr.SyncExecSqlStmt(mysqlSelectGuildMemberCount, CB_ExportGuildMember, (void*)(&(*iter)->nMemberCount), "ud", (*iter)->dwGuildID);
        LOG_PROCESS_ERROR(nRetCode);
    }

    // export 
    pFile = fopen("guild_stat.txt", "wb");
    LOG_PROCESS_ERROR(pFile);

    pBuffer = new char[EXPORT_GUILD_BUFFER_LENGTH];
    memset(pBuffer, 0, EXPORT_GUILD_BUFFER_LENGTH);
    nLength = snprintf(pBuffer, EXPORT_GUILD_BUFFER_LENGTH, "GuildID\tGuildName\tGuildLevel\tGroupID\tLeaderID\tCreaterName\tCreateTime\tDeleteTime\tMemberCount\n");
    fwrite(pBuffer, 1, nLength, pFile);

    for (YY_GUILD_STAT::GUILD_LIST::iterator iter = g_GuildStat.GuildList.begin(); iter != g_GuildStat.GuildList.end(); ++iter)
    {
        memset(pBuffer, 0, EXPORT_GUILD_BUFFER_LENGTH);

        nLength = snprintf(pBuffer, EXPORT_GUILD_BUFFER_LENGTH, "%u\t%s\t%d\t%d\t%u\t%s\t%s\t%s\t%d\n", (*iter)->dwGuildID, (*iter)->szGuildName,
            (*iter)->nGuildLevel, (*iter)->nGroupID, (*iter)->dwLeaderID, (*iter)->szCreaterName,
            (*iter)->szCreateTime, (*iter)->szDeleteTime, (*iter)->nMemberCount);

        fwrite(pBuffer, 1, nLength, pFile);
    }

    fclose(pFile);

    // clear
    {
        YY_GUILD_STAT::GUILD_LIST::iterator iter = g_GuildStat.GuildList.begin();
        while (iter != g_GuildStat.GuildList.end())
        {
            YY_GUILD_STAT::GUILD_LIST::iterator old_iter = iter;
            ++iter;

            delete (*old_iter);
            g_GuildStat.GuildList.erase(old_iter);
        }

        g_GuildStat.GuildList.clear();
    }


Exit0:
    return;
}



BOOL CB_ExportGuild(std::list<void*>& rResult, void* pUserData)
{
    INT32       nRetCode = 0;
    INT32       nRecords = 0;

    for (std::list<void*>::iterator it = rResult.begin();
        it != rResult.end(); ++it)
    {
        YY_GUILD_DB* pLoadResult = (YY_GUILD_DB*)*it;

        YY_GUILD_DATA    *poGuild = new YY_GUILD_DATA;
        LOG_PROCESS_ERROR(poGuild);

        strxcpy(poGuild->szCreateTime, pLoadResult->szCreateTime, sizeof(poGuild->szCreateTime));
        strxcpy(poGuild->szDeleteTime, pLoadResult->szDeleteTime, sizeof(poGuild->szDeleteTime));

        poGuild->dwGuildID = pLoadResult->dwGuildID;
        poGuild->nGroupID = pLoadResult->byGroupID;
        poGuild->dwLeaderID = pLoadResult->dwLeaderID;
        strxcpy(poGuild->szCreaterName, pLoadResult->szCreaterName, ROLE_NAME_LEN);
        poGuild->dwCreateTime = pLoadResult->dwCreateTime;
        strxcpy(poGuild->szGuildName, pLoadResult->szGuildName, GUILD_NAME_LEN);

        nRetCode = poGuild->Load(pLoadResult->BlobBuffer);
        LOG_PROCESS_ERROR(nRetCode);

        g_GuildStat.GuildList.push_back(poGuild);

        nRecords++;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CB_ExportGuildMember(std::list<void*>& rResult, void* pUserData)
{
#pragma pack(push, 1)
    struct LOAD_RESULT
    {
        INT32      nMemberCount;
    };
#pragma pack(pop)

    INT32       nRetCode = 0;
    INT32* pMemberCount = (INT32 *)pUserData;
    LOG_PROCESS_ERROR(pMemberCount);

    for (std::list<void*>::iterator it = rResult.begin();
        it != rResult.end(); ++it)
    {
        LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;

        *pMemberCount = pLoadResult->nMemberCount;

        break;
    }

    return TRUE;
Exit0:
    return FALSE;
}


BOOL YY_GUILD_DATA::Load(const char *pcData)
{
    using namespace GUILD_DEF_VER_5;

    INT32       nRetCode = 0;
    const char *pcActualData = pcData;
    GUILD_DB_DATA       *pGuildData = NULL;
    UINT32      dwRealSize = 0;

    LOG_PROCESS_ERROR(pcData);
    pcActualData = pcData + sizeof(UINT32);
    pGuildData = (GUILD_DB_DATA *)pcActualData; // The four added bytes are the length prepended when saving the blob

    LOG_PROCESS_ERROR(pGuildData->dwLen >= 4 && pGuildData->dwLen < 60000);
    LOG_PROCESS_ERROR(pGuildData->dwCRC ==
        crc32(0, (const Bytef*)&pGuildData->dwVersion, pGuildData->dwLen - sizeof(pGuildData->dwLen) - sizeof(pGuildData->dwCRC)));

    if (pGuildData->dwVersion < 5)
        INF("load old guild %d db data %d %d", pGuildData->dwGuildID, pGuildData->dwVersion, pGuildData->dwLen);

    //////////////////////////////////////////////////////////////////////////
    // actual load

    pGuildData = (GUILD_DB_DATA *)pcActualData;
    dwRealSize = pGuildData->dwLen - sizeof(GUILD_DB_DATA);

    for (INT32 i = 0; i < gbtTotal; ++i)
    {
        GUILD_DB_DATA_BLOCK *pBlock = &pGuildData->BlockTable[i];

        const char *pcBlockData = &pGuildData->GuildData[pBlock->dwStartOffset];
        UINT32      dwBlockSize = pBlock->dwBlockSize;
        LOG_PROCESS_ERROR(dwBlockSize + pBlock->dwStartOffset <= dwRealSize);

        if (dwBlockSize == 0)
            continue;

        switch (pBlock->byBlockType)
        {
        case gbtBase:
        {
            const GUILD_DB_BASE   *pBase = (const GUILD_DB_BASE*)pcBlockData;

            LOG_PROCESS_ERROR(pBase);
            LOG_PROCESS_ERROR(GUILD_POSITION_COUNT >= sizeof(pBase->wStorageRight) / sizeof(pBase->wStorageRight[0]));
            LOG_PROCESS_ERROR(MAX_GUILD_VARIABLE_COUNT >= sizeof(pBase->nVariables) / sizeof(pBase->nVariables[0]));
            LOG_PROCESS_ERROR(GUILD_ACHI_TYPE_NUM == sizeof(pBase->byAchievement) / sizeof(pBase->byAchievement[0]));

            pBase->dwRoutineConsumeTime;
            pBase->nState;
            pBase->dwCalculateResourceTime;

            nGuildMoney = pBase->nMoney;
            nWood = pBase->nWood;
            nHerb = pBase->nHerb;
            nCrystal = pBase->nCrystal;
            nSilver = pBase->nSilver;

            LOG_PROCESS_ERROR(sizeof(GUILD_DB_BASE) == dwBlockSize);
        }
            break;
        case gbtWelfare:
        {
            const GUILD_DB_WELFARE    *pWelfare = (const GUILD_DB_WELFARE*)pcBlockData;
            const GUILD_DB_WELFARE_UPGRADE    *pUpgrade = NULL;
            LOG_PROCESS_ERROR(pWelfare);
            LOG_PROCESS_ERROR((sizeof(GUILD_DB_WELFARE) + pWelfare->byUpgradeWelfareNum * sizeof(GUILD_DB_WELFARE_UPGRADE)) == dwBlockSize);

            LOG_PROCESS_ERROR(GUILD_MAX_WELFARE_AURA_COUNT >= sizeof(pWelfare->WelfareAuraLevel) / sizeof(pWelfare->WelfareAuraLevel[0]));
        }
            break;
        case gbtBuilding:
        {
            const GUILD_DB_BUILDING           *pBuilding = (const GUILD_DB_BUILDING*)pcBlockData;
            const GUILD_DB_BUILDING_DATA      *pBuildingData = NULL;
            const GUILD_DB_BUILDING_UPGRADE   *pUpgrade = NULL;

            LOG_PROCESS_ERROR(pBuilding);
            LOG_PROCESS_ERROR((pBuilding->wBuildingBufferLength + pBuilding->wUpgradeBufferLength + sizeof(GUILD_DB_BUILDING)) == dwBlockSize);

            pBuildingData = (const GUILD_DB_BUILDING_DATA *)pBuilding->Building;
            LOG_PROCESS_ERROR(pBuildingData);
            for (INT32 i = 0; i < pBuilding->byBuildingNum; ++i)
            {
                if (pBuildingData[i].byType == GUILD_B_MAIN)
                    nGuildLevel = pBuildingData[i].byLevel;
            }
            LOG_PROCESS_ERROR(pBuilding->wBuildingBufferLength == pBuilding->byBuildingNum * sizeof(GUILD_DB_BUILDING_DATA));
        }
            break;
        case gbtDiplomat:
        {
            const GUILD_DB_DIPLOMAT_DATA    *pData = NULL;
            const GUILD_DB_DIPLOMAT *pDiplomat = (const GUILD_DB_DIPLOMAT*)pcBlockData;
            LOG_PROCESS_ERROR(pDiplomat);

            LOG_PROCESS_ERROR(GUILD_MAX_ALLIANCE_NUM >= pDiplomat->byAllianceNum);
            LOG_PROCESS_ERROR(GUILD_MAX_ENEMY_NUM >= pDiplomat->byEnemyNum);

            LOG_PROCESS_ERROR(dwBlockSize == (sizeof(GUILD_DB_DIPLOMAT) + (pDiplomat->byAllianceNum + pDiplomat->byEnemyNum) * sizeof(GUILD_DB_DIPLOMAT_DATA)));
        }
            break;
        case gbtDungeon:
        {
        }
            break;
        case gbtStorage:
        {

        }
            break;
        case gbtHistory:
        {

        }
            break;
        case gbtStorageHistory:
        {

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

MEMBER_LIST        g_MemberList;

void _LoadMember(CSqlMgr& sqlmgr)
{
    INT32       nRetCode = 0;
    FILE        *pFile = NULL;
    char    *pBuffer = NULL;
    INT32   nLength = 0;

    g_MemberList.clear();

    nRetCode = sqlmgr.SyncExecSqlStmt(mysqlSelectGuildMemberInfo, CB_ExportGuildMemberInfo, NULL, "");
    LOG_PROCESS_ERROR(nRetCode);


    // export 
    pFile = fopen("guild_member.txt", "wb");
    LOG_PROCESS_ERROR(pFile);

    pBuffer = new char[EXPORT_GUILD_BUFFER_LENGTH];
    memset(pBuffer, 0, EXPORT_GUILD_BUFFER_LENGTH);
    nLength = snprintf(pBuffer, EXPORT_GUILD_BUFFER_LENGTH, "RoleID\tGuildID\tGuildName\tRoleName\tUserName\n");
    fwrite(pBuffer, 1, nLength, pFile);

    for (MEMBER_LIST::iterator iter = g_MemberList.begin(); iter != g_MemberList.end(); ++iter)
    {
        memset(pBuffer, 0, EXPORT_GUILD_BUFFER_LENGTH);

        nLength = snprintf(pBuffer, EXPORT_GUILD_BUFFER_LENGTH, "%u\t%u\t%s\t%s\t%s\n", iter->dwRoleID, iter->dwGuildID, iter->szGuildName, iter->szRoleName, iter->szUserName);

        fwrite(pBuffer, 1, nLength, pFile);
    }

    fclose(pFile);


Exit0:
    return ;
}

BOOL CB_ExportGuildMemberInfo(std::list<void*>& rResult, void* pUserData)
{
#pragma pack(push, 1)
    struct LOAD_RESULT
    {
        UINT32      dwRoleID;
        UINT32      dwGuildID;
        char        szGuildName[GUILD_NAME_LEN];
        char        szRoleName[ROLE_NAME_LEN];
        char        szUserName[USER_NAME_LEN];
    };
#pragma pack(pop)

    INT32       nRetCode = 0;

    for (std::list<void*>::iterator it = rResult.begin();
        it != rResult.end(); ++it)
    {
        LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;

        YY_GUILD_MEMBER     member;
        member.dwGuildID = pLoadResult->dwGuildID;
        member.dwRoleID = pLoadResult->dwRoleID;
        strxcpy(member.szGuildName, pLoadResult->szGuildName, GUILD_NAME_LEN);
        strxcpy(member.szRoleName, pLoadResult->szRoleName, ROLE_NAME_LEN);
        strxcpy(member.szUserName, pLoadResult->szUserName, USER_NAME_LEN);

        g_MemberList.push_back(member);

    }

    return TRUE;
Exit0:
    return FALSE;
}





