

#ifndef _H_MS_GUILD_INL_H_
#define _H_MS_GUILD_INL_H_


inline UINT32 CMsGuild::GetID()
{
    return m_dwID;
}

inline INT32 CMsGuild::GetSvrGroup()
{
    return m_nSvrGroupID;
}


inline const char * CMsGuild::GetName()
{
    return m_szGuildName;
}

inline const char * CMsGuild::GetCreaterName()
{
    return m_szCreaterName;
}

inline UINT32 CMsGuild::GetLeaderID()
{
    return m_dwLeaderID;
}

inline UINT32 CMsGuild::GetCreateTime()
{
    return m_dwCreateTime;
}

inline const char * CMsGuild::GetAnnounce()
{
    return m_szAnnounce;
}

inline const char * CMsGuild::GetNotice()
{
    return m_szNotice;
}

inline INT32 CMsGuild::GetProsperity()
{
    return m_nProsperity;
}

inline INT32 CMsGuild::GetMoney()
{
    return m_nGuildMoney;
}

inline INT32 CMsGuild::GetWood()
{
    return m_nWood;
}

inline INT32 CMsGuild::GetHerb()
{
    return m_nHerb;
}

inline INT32 CMsGuild::GetCryStal()
{
    return m_nCrystal;
}

inline INT32 CMsGuild::GetSilver()
{
    return m_nSilver;
}

inline INT32 CMsGuild::GetState()
{
    return m_nState;
}


inline INT32 CMsGuild::GetMemberNum()
{
    return (INT32)m_memberList.size();
}

inline CMsGuildStorage &CMsGuild::GetStorage()
{
    return m_storage;
}

inline BASE_LIST_NODE &CMsGuild::GetLvlRankNode()
{
    return m_NodeSortByLvl;
}

inline BASE_LIST_NODE& CMsGuild::GetLadderNode()
{
    return m_LadderNode;
}

inline INT32 CMsGuild::GetEnemyNum()
{
    return m_nEnemyNum;
}

inline INT32 CMsGuild::GetAllianceNum()
{
    return m_nAllianceNum;
}

inline UINT32 CMsGuild::GetAimID()
{
    return m_dwAimID;
}

inline UINT32 CMsGuild::GetIntruder()
{
    return m_dwIntruderID;
}

inline UINT32 CMsGuild::GetRevengeObj()
{
    return m_dwRevengeGuildID;
}

inline UINT32 CMsGuild::GetProtectionTime()
{
    return m_dwProtectionTime;
}


inline UINT32 CMsGuild::GetWarAttackCD()
{
    return m_dwAttackCD;
}


inline void CMsGuild::SetMatchingGuild(UINT32 dwGuildID)
{
    m_dwMatchingGuild = dwGuildID;
}

inline UINT32 CMsGuild::GetMatchingGuild()
{
    return m_dwMatchingGuild;
}

inline DIPLOMAT_DATA *CMsGuild::GetEnemyDataByIndex(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < GUILD_MAX_ENEMY_NUM);
    return &m_arrEnemy[nIndex];
Exit0:
    return NULL;
}

inline DIPLOMAT_DATA *CMsGuild::GetAllianceDataByIndex(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < GUILD_MAX_ALLIANCE_NUM);
    return &m_arrAlliance[nIndex];
Exit0:
    return NULL;
}

inline INT32  CMsGuild::GetWelfareAuraLevelByType(INT32 nType)
{
    LOG_PROCESS_ERROR(0 < nType && nType < GUILD_MAX_WELFARE_AURA_COUNT);
    return m_arrWelfareAuraLvl[nType];
Exit0:
    return 1;
}


inline INT32 CMsGuild::GetStorageRightByPosition(INT32 nPosition)
{
    LOG_PROCESS_ERROR(nPosition > GUILD_POSITION_NONE && nPosition < GUILD_POSITION_TOTAL);
    return m_wStorageRight[nPosition - 1];
Exit0:
    return 0;
}

inline UINT32 CMsGuild::GetSabacEnrollTime(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_SABAC_ENROLL_COUNT);
	return m_dwSabacEnrollTime[nIndex];
Exit0:
	return 0;
}

inline BOOL CMsGuild::IsOccupiedSabac(void)
{
	return m_bOccupiedSabac;
}

inline const char* CMsGuild::GetAchievementData()
{
    return m_Achievement; 
}

// war
inline BOOL CMsGuild::CheckCharacter(INT32 nC)    
{
    return m_byWarCharacter & nC;
}

inline INT32 CMsGuild::GetWarCharacter()       
{
    return m_byWarCharacter;
}

inline INT32 CMsGuild::GetIntruderNum()
{
    return (INT32)m_IntruderSet.size();
}


#endif //_H_MS_GUILD_INL_H_
