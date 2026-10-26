//  Allan Tao[12.8.2014] 


#include "stdafx.h"
#include "asimov_guild.h"

#ifdef _ROBOT

CGSGuild::CGSGuild()
{
    m_dwID = 0;
    memset(m_szName, 0, sizeof(m_szName));
    m_nState = 0;
    m_dwLeaderID = 0;
    memset(m_szNotice, 0, sizeof(m_szNotice));
    m_nGuildMoney = 0;
    m_nProsperity = 0;
    m_nHerb = 0;
    m_nWood = 0;
    m_nCrystal = 0;
    m_nSilver = 0;
    
    m_listMember.clear();
    memset(m_wStorageRight, 0, sizeof(m_wStorageRight));

    m_nAllianceNum = 0;
    m_nEnemyNum = 0;
    memset(m_arrAlliance, 0, sizeof(m_arrAlliance));
    m_dwActiveEnemy = 0;
    memset(m_arrEnemy, 0, sizeof(m_arrEnemy));
    
    m_nAppNum = 0;
    memset(m_arrAppRoleID, 0, sizeof(m_arrAppRoleID));

    m_nMatchWarConsumption = 0;
    m_byMatchCount = 0;

    m_nUnionAppNum = 0;
    memset(m_UnionAppList, 0, sizeof(m_UnionAppList));
}

CGSGuild::~CGSGuild()
{
    m_dwID = 0;
    memset(m_szName, 0, sizeof(m_szName));
    m_nState = 0;
    m_dwLeaderID = 0;
    memset(m_szNotice, 0, sizeof(m_szNotice));
    m_nGuildMoney = 0;
    m_nProsperity = 0;
    m_nHerb = 0;
    m_nWood = 0;
    m_nCrystal = 0;
    m_nSilver = 0;

    m_listMember.clear();
    memset(m_wStorageRight, 0, sizeof(m_wStorageRight));

    m_nAllianceNum = 0;
    m_nEnemyNum = 0;
    memset(m_arrAlliance, 0, sizeof(m_arrAlliance));
    m_dwActiveEnemy = 0;
    memset(m_arrEnemy, 0, sizeof(m_arrEnemy));

    m_nAppNum = 0;
    memset(m_arrAppRoleID, 0, sizeof(m_arrAppRoleID));

    m_nMatchWarConsumption = 0;
    m_byMatchCount = 0;

    m_nUnionAppNum = 0;
    memset(m_UnionAppList, 0, sizeof(m_UnionAppList));
}

BOOL CGSGuild::Init()
{
    m_dwID = 0;
    memset(m_szName, 0, sizeof(m_szName));
    m_nState = 0;
    m_dwLeaderID = 0;
    memset(m_szNotice, 0, sizeof(m_szNotice));
    m_nGuildMoney = 0;
    m_nProsperity = 0;
    m_nHerb = 0;
    m_nWood = 0;
    m_nCrystal = 0;
    m_nSilver = 0;

    m_listMember.clear();
    memset(m_wStorageRight, 0, sizeof(m_wStorageRight));

    m_nAllianceNum = 0;
    m_nEnemyNum = 0;
    memset(m_arrAlliance, 0, sizeof(m_arrAlliance));
    m_dwActiveEnemy = 0;
    memset(m_arrEnemy, 0, sizeof(m_arrEnemy));

    m_nAppNum = 0;
    memset(m_arrAppRoleID, 0, sizeof(m_arrAppRoleID));

    m_nMatchWarConsumption = 0;
    m_byMatchCount = 0;

    m_nUnionAppNum = 0;
    memset(m_UnionAppList, 0, sizeof(m_UnionAppList));

    return TRUE;
}

BOOL CGSGuild::UnInit()
{
    m_dwID = 0;
    memset(m_szName, 0, sizeof(m_szName));
    m_nState = 0;
    m_dwLeaderID = 0;
    memset(m_szNotice, 0, sizeof(m_szNotice));
    m_nGuildMoney = 0;
    m_nProsperity = 0;
    m_nHerb = 0;
    m_nWood = 0;
    m_nCrystal = 0;
    m_nSilver = 0;

    m_listMember.clear();
    memset(m_wStorageRight, 0, sizeof(m_wStorageRight));

    m_nAllianceNum = 0;
    m_nEnemyNum = 0;
    memset(m_arrAlliance, 0, sizeof(m_arrAlliance));
    m_dwActiveEnemy = 0;
    memset(m_arrEnemy, 0, sizeof(m_arrEnemy));

    m_nAppNum = 0;
    memset(m_arrAppRoleID, 0, sizeof(m_arrAppRoleID));

    m_nMatchWarConsumption = 0;
    m_byMatchCount = 0;

    m_nUnionAppNum = 0;
    memset(m_UnionAppList, 0, sizeof(m_UnionAppList));

    return TRUE;
}

BOOL CGSGuild::Load(ASIMOV_GUILD_DATA &data)
{

    m_dwID = data.dwGuildID;
    strxcpy(m_szName, data.szGuildName, sizeof(m_szName));
    m_dwLeaderID = data.dwLeaderID;
    m_nLevel = data.byLevel;
    strxcpy(m_szNotice, data.szNotice, sizeof(m_szNotice));
    m_nGuildMoney = data.dwGuildMoney;
    m_nProsperity = data.nProsperity;
    m_nHerb = data.nHerb;
    m_nWood = data.nWood;
    m_nCrystal = data.nCrystal;
    m_nSilver = data.nSilver;

    for (INT32 i = 0; i < GUILD_POSITION_COUNT; ++i)
        m_wStorageRight[i] = data.wStorageRight[i];

    m_nAllianceNum = data.byAllianceCount;
    for (INT32 i = 0; i < GUILD_MAX_ALLIANCE_NUM; ++i)
    {
        m_arrAlliance[i].dwGuildID = data.stAlliance[i].dwGuildID;
        m_arrAlliance[i].dwEndTime = data.stAlliance[i].dwLastTime;
    }

    m_nEnemyNum = data.byEnemyCount;
    for (INT32 i = 0; i < GUILD_MAX_ENEMY_NUM; ++i)
    {
        m_arrEnemy[i].dwGuildID = data.stEnemy[i].dwGuildID;
        m_arrEnemy[i].dwEndTime = data.stEnemy[i].dwLastTime;
    }

    m_listMember.clear();
    for (INT32 i = 0; i < data.byMemberCount; ++i)
    {
        m_listMember.push_back(data.arrMemberData[i]);
    }


    return TRUE;
}


BOOL CGSGuild::SetName(const char* pcszName)
{
    LOG_PROCESS_ERROR(pcszName);

    strxcpy(m_szName, pcszName, sizeof(m_szName));

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSGuild::SetNotice(const char* pcszNotice)
{
    LOG_PROCESS_ERROR(pcszNotice);

    strxcpy(m_szNotice, pcszNotice, sizeof(m_szNotice));

    return TRUE;
Exit0:
    return FALSE;
}

ASIMOV_GUILD_MEMBER *CGSGuild::GetMemberByIndex(INT32 nIndex)
{
    INT32       nI = 0;
    for (MEMBER_LIST::iterator iter = m_listMember.begin(); iter != m_listMember.end(); ++iter, ++nI)
    {
        if (nI == nIndex)
        {
            return &(*iter);
        }
    }
    return NULL;
}

ASIMOV_GUILD_MEMBER* CGSGuild::GetMember(UINT32 dwRoleID)
{
    for (MEMBER_LIST::iterator iter = m_listMember.begin(); iter != m_listMember.end(); ++iter)
    {
        if (iter->dwRoleID == dwRoleID)
        {
            return &(*iter);
        }
    }

Exit0:
    return NULL;
}

BOOL CGSGuild::IsOfficeFull(INT32 nPosition)
{
    INT32       count = 0;
    MEMBER_LIST::iterator  iter = m_listMember.begin();
    MEMBER_LIST::iterator    end_iter = m_listMember.end();

    LOG_PROCESS_ERROR(nPosition > GUILD_POSITION_LEADER && nPosition < GUILD_POSITION_TOTAL);

    for (; iter != end_iter; ++iter)
    {
        if (iter->byPosition == nPosition)
        {
            ++count;
        }
    }
    
    return count >= ARR_GUILD_POS_HUMAN_NUM[nPosition - 1];
Exit0:
    return TRUE;
}

BOOL CGSGuild::AddMember(UINT32 dwRoleID, UINT8 byPosition, UINT8 byFlag, INT32 nSalary)
{
    ASIMOV_GUILD_MEMBER     data;
    data.dwRoleID = dwRoleID;
    data.byPosition = byPosition;
    data.byGuildFlag = byFlag;
    data.nSalary = nSalary;
    data.dwDrawSalaryTime = 0;

    m_listMember.push_back(data);

    return TRUE;
}

BOOL CGSGuild::DelMember(UINT32 dwRoleID)
{
    for (MEMBER_LIST::iterator iter = m_listMember.begin(); iter != m_listMember.end(); ++iter)
    {
        if (iter->dwRoleID == dwRoleID)
        {
            m_listMember.erase(iter);
            return TRUE;
        }
    }
    
    return TRUE;
}

BOOL CGSGuild::ChangeStorageRight(INT32 nPosition, UINT16 wRight)
{
    LOG_PROCESS_ERROR(nPosition > GUILD_POSITION_NONE && nPosition < GUILD_POSITION_TOTAL);

    m_wStorageRight[nPosition - 1] = wRight;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSGuild::IsAlliance(UINT32 dwGuildID)
{
    for (INT32 i = 0; i < m_nAllianceNum; ++i)
    {
        if (m_arrAlliance[i].dwGuildID == dwGuildID)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CGSGuild::IsEnemy(UINT32 dwGuildID)
{
    for (INT32 i = 0; i < m_nEnemyNum; ++i)
    {
        if (m_arrEnemy[i].dwGuildID == dwGuildID)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CGSGuild::AddAlliance(UINT32  dwGuildID, UINT32 dwEndTime)
{
    m_arrAlliance[m_nAllianceNum].dwGuildID = dwGuildID;
    m_arrAlliance[m_nAllianceNum++].dwEndTime = dwEndTime;

    return TRUE;
}

BOOL CGSGuild::DelAlliance(UINT32 dwGuildID)
{
    LOG_PROCESS_ERROR(m_nAllianceNum >= 0 && m_nAllianceNum <= GUILD_MAX_ALLIANCE_NUM);
    for (INT32 i = 0; i < m_nAllianceNum; ++i)
    {
        if (dwGuildID == m_arrAlliance[i].dwGuildID)
        {
            m_arrAlliance[i] = m_arrAlliance[--m_nAllianceNum];
            return TRUE;
        }
    }

Exit0:
    return FALSE;
}

BOOL CGSGuild::AddEnemy(UINT32 dwGuildID, UINT32 dwEndTime, BOOL bIsActive)
{
    INT32       nRetCode = 0;
    if (bIsActive)
    {
        m_dwActiveEnemy = dwGuildID;
    }
    m_arrEnemy[m_nEnemyNum].dwGuildID = dwGuildID;
    m_arrEnemy[m_nEnemyNum++].dwEndTime = dwEndTime;

    return TRUE;
}

BOOL CGSGuild::DelEnemy(UINT32 dwGuildID)
{
    LOG_PROCESS_ERROR(m_nEnemyNum >= 0 && m_nEnemyNum <= GUILD_MAX_ENEMY_NUM);

    for (INT32 i = 0; i < m_nEnemyNum; ++i)
    {
        if (dwGuildID == m_arrEnemy[i].dwGuildID)
        {
            m_arrEnemy[i] = m_arrEnemy[--m_nEnemyNum];
            return TRUE;
        }
    }
Exit0:
    return FALSE;
}


UINT32 CGSGuild::RandomApplyUnion()
{
    UINT32      dwRandIndex = 0;
    UINT32      dwGuildID = 0;
    PROCESS_ERROR(m_nUnionAppNum != 0);

    dwRandIndex = g_Random(m_nUnionAppNum);
    dwGuildID = m_UnionAppList[dwRandIndex];

    DelUnionApp(dwGuildID);

Exit0:
    return dwGuildID;
}

BOOL CGSGuild::AddUnionApp(UINT32 dwGuildID)
{
    INT32   nRetCode = 0;
    LOG_PROCESS_ERROR(m_nUnionAppNum < GUILD_MAX_APPLY_ALLIANCE_NUM);

    for (INT32 nIndex = 0; nIndex < m_nUnionAppNum; ++nIndex)
    {
        if (m_UnionAppList[nIndex] == dwGuildID)
            return TRUE;
    }

    m_UnionAppList[m_nUnionAppNum++] = dwGuildID;

Exit0:
    return TRUE;
}

BOOL CGSGuild::DelUnionApp(UINT32 dwGuildID)
{
    for (INT32 nIndex = 0; nIndex < m_nUnionAppNum; ++nIndex)
    {
        if (m_UnionAppList[nIndex] == dwGuildID)
        {
            m_UnionAppList[nIndex] = m_UnionAppList[m_nUnionAppNum - 1];
            --m_nUnionAppNum;
            return TRUE;
        }
    }
    return TRUE;
}

void CGSGuild::ClearUnionApp()
{
    m_nUnionAppNum = 0;
}






BOOL CGSGuild::ClearApp()
{
    m_nAppNum = 0;
    return TRUE;
}

BOOL CGSGuild::AddApp(UINT32 dwRoleID)
{
    INT32       nRetCode = 0;

    LOG_PROCESS_ERROR(GetAppNum() < MAX_APPLY_GUILD_ROLE_NUM);

    nRetCode = AlreadyExistInAppList(dwRoleID);
    PROCESS_SUCCESS(nRetCode);

    m_arrAppRoleID[m_nAppNum++] = dwRoleID;

Exit1:
    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSGuild::DelApp(UINT32 dwRoleID)
{
    for (INT32 i = 0; i < m_nAppNum; ++i)
    {
        if (m_arrAppRoleID[i] == dwRoleID)
        {
            m_arrAppRoleID[i] = m_arrAppRoleID[m_nAppNum - 1];
            --m_nAppNum;
            return TRUE;
        }
    }
    return TRUE;
}

BOOL CGSGuild::AlreadyExistInAppList(UINT32 dwRoleID)
{
    LOG_PROCESS_ERROR(m_nAppNum < MAX_APPLY_GUILD_ROLE_NUM);

    for (INT32 i = 0; i < m_nAppNum; ++i)
    {
        if (m_arrAppRoleID[i] == dwRoleID)
        {
            return TRUE;
        }
    }

    return FALSE;
Exit0:
    return TRUE;
}

INT32 CGSGuild::GetAppNum()
{
    return m_nAppNum;
}

UINT32 CGSGuild::GetRoleIDByIndexFromAppList(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < m_nAppNum && nIndex < MAX_APPLY_GUILD_ROLE_NUM);
    return m_arrAppRoleID[nIndex];
Exit0:
    return 0;
}


//void CGSGuild::ClearViewList()
//{
//    m_nValidViewGuildNum = 0;
//}
//
//BOOL CGSGuild::AddViewList(UINT32 dwGuildID)
//{
//    LOG_PROCESS_ERROR(m_nValidViewGuildNum < MAX_VIEW_GUILD_LIST_COUNT);
//
//    m_arrViewGuildIDList[m_nValidViewGuildNum++] = dwGuildID;
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}
//
//INT32 CGSGuild::GetViewListNum()
//{
//    DBG("asimov view list num %d", m_nValidViewGuildNum);
//    return m_nValidViewGuildNum;
//}
//
//UINT32 CGSGuild::GetViewListGuildIDByIndex(INT32 nIndex)
//{
//    LOG_PROCESS_ERROR(nIndex < m_nValidViewGuildNum);
//
//    return m_arrViewGuildIDList[nIndex];
//Exit0:
//    return 0;
//}




#endif //_ROBOT

