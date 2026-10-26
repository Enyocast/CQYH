/********************************************************************
	created:	13:11:2013   16:27
	file:		gs_guild_inl.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GS_GUILD_INL_H_
#define _H_GS_GUILD_INL_H_

inline UINT32 CGSGuild::GetID()
{
    return m_dwID;
}

inline INT32 CGSGuild::GetLevel()
{
    return m_FunBuildingList[GUILD_B_MAIN].nLevel;
}

inline const char *CGSGuild::GetName()
{
    return m_szName;
}

inline INT32 CGSGuild::GetState()
{
    return m_nState;
}

inline void CGSGuild::SetState(INT32 nState)
{
    m_nState = nState;
}

inline UINT32 CGSGuild::GetLeaderID()
{
    return m_dwLeaderID;
}

inline void CGSGuild::SetLeaderID(UINT32 dwRoleID)
{
    m_dwLeaderID = dwRoleID;
}

inline INT32 CGSGuild::GetMoney()
{
    return m_nMoney;
}

inline void CGSGuild::SetMoney(INT32 nMoney)
{
    LOG_PROCESS_ERROR(nMoney > 0);
    m_nMoney = nMoney;
Exit0:
    return;
}

inline INT32 CGSGuild::GetHerb()
{
    return m_nHerb;
}

inline void CGSGuild::SetHerb(INT32 nHerb)
{
    LOG_PROCESS_ERROR(nHerb > 0);
    m_nHerb = nHerb;
Exit0:
    return;
}

inline INT32 CGSGuild::GetWood()
{
    return m_nWood;
}

inline void CGSGuild::SetWood(INT32 nWood)
{
    LOG_PROCESS_ERROR(nWood > 0);
    m_nWood = nWood;
Exit0:
    return;
}

inline INT32 CGSGuild::GetCrystal()
{
    return m_nCrystal;
}

inline void CGSGuild::SetCrystal(INT32 nCrystal)
{
    LOG_PROCESS_ERROR(nCrystal > 0);
    m_nCrystal = nCrystal;
Exit0:
    return;
}

inline INT32 CGSGuild::GetSilver()
{
    return m_nSilver;
}

inline void CGSGuild::SetSilver(INT32 nSilver)
{
    LOG_PROCESS_ERROR(nSilver > 0);
    m_nSilver = nSilver;
Exit0:
    return;
}

inline UINT32 CGSGuild::GetSabacEnrollTime(INT32 nIndex)
{
	LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_SABAC_ENROLL_COUNT);
	return m_dwSabacEnrollTime[nIndex];
Exit0:
	return 0;
}

inline BOOL CGSGuild::IsOccupiedSabac(void)
{
	return m_bOccupiedSabac;
}

inline void CGSGuild::OccupySabac(BOOL bOccupied)
{
	m_bOccupiedSabac = bOccupied;
}

inline INT32 CGSGuild::GetServerGroup(void)
{
	return m_nServerGroup;
}

inline BOOL CGSGuild::IsWarTime()
{
    return m_nWarCharacter != GUILD_WAR_NONE;
}

inline void CGSGuild::SetWarCharacter(INT32 nCharacter)
{
    m_nWarCharacter = nCharacter;
}

inline INT32 CGSGuild::GetWarCharacter()
{
    return m_nWarCharacter;
}

#endif //_H_GS_GUILD_INL_H_


