#ifndef _ROLE_INL_H_
#define _ROLE_INL_H_

#include "string_ex.h"
#include "error_def.h"
#include "game_world_config.h"
#include "obj_pool_config.h"
#include "id_def.h"
#include "server_def.h"

void inline CRole::Prefetch(void)
{
	_mm_prefetch((char*)&m_llX, _MM_HINT_T1);
	_mm_prefetch((char*)&m_llDestX, _MM_HINT_T1);
	_mm_prefetch((char*)&m_eSpellState, _MM_HINT_T1);
	_mm_prefetch((char*)&m_eState, _MM_HINT_T1);
}

inline const char* CRole::GetUserName(void)
{
    return m_szUserName;
}

inline UINT8 CRole::GetHairType(void) const
{
    return m_byHairType;
}

inline UINT8 CRole::GetHairColor(void) const
{
    return m_byHairColor;
}

inline UINT8 CRole::GetFaceType(void) const
{
    return m_byFaceType;
}

inline UINT8 CRole::GetSkinColor(void) const
{
    return m_bySkinColor;
}

inline UINT32 CRole::GetSessionID(void)
{
	return m_dwSessionID;
}

inline INT32 CRole::GetServerGroup(void)
{
    return m_nServerGroupID;
}

inline UINT32 CRole::GetCreateTime(void)
{
	return m_dwCreateTime;
}

inline UINT32 CRole::GetPkValue(void)
{
	return m_dwPkValue;
}

inline INT32 CRole::GetComboKill(void)
{
	return m_nComboKill;
}

inline UINT32 CRole::GetVIPTime(INT32 nVIPLevel)
{
    LOG_PROCESS_ERROR(nVIPLevel > vlLevel0 && nVIPLevel < vlTotal);

    return m_dwVIPTime[nVIPLevel];
Exit0:
    return 0;
}


inline BOOL CRole::SetVIPTime(INT32 nVIPLevel, UINT32 dwVipTime)
{
	BOOL bResult = FALSE;

	LOG_PROCESS_ERROR(nVIPLevel > vlLevel0 && nVIPLevel < vlTotal);

	m_dwVIPTime[nVIPLevel] = dwVipTime;

	bResult = TRUE;

Exit0:
	return bResult;
}
inline BOOL CRole::IsHidden(void)
{
	return m_bHidden;
}

inline BASE_LIST_NODE& CRole::GetSceneListNode(void)
{
    return m_SceneListNode;
}

inline BASE_LIST_NODE& CRole::GetSaveListNode(void)
{
    return m_SaveListNode;
}

void CRole::SetSceneTempID(INT32 nSceneTempID)
{
    m_nSceneTempID = nSceneTempID;
}

void CRole::SetSceneID(INT32 nSceneID)
{
    m_nSceneID = nSceneID;
}

inline void CRole::SetName(const TCHAR* pcszName)
{
    strxcpy(m_szName, pcszName, ROLE_NAME_LEN);
}

inline INT32 CRole::GetSceneTempID(void)
{
	return m_nSceneTempID;
}

inline INT32 CRole::GetSceneID(void)
{
    return m_nSceneID;
}

inline INT32 CRole::GetExp(void)
{
	return m_nExp;
}

inline INT32 CRole::GetTodayExp(void)
{
    return m_nExpToday;
}

inline INT32 CRole::GetExtraExp(void)
{
    return m_nExtraExp;
}

inline void CRole::SubExtraExp(INT32 nExp)
{
	m_nExtraExp -= nExp;
}

inline INT32 CRole::GetActivity()
{
	return m_nActivity;
};

inline void CRole::AddActivityReward(INT32 nActivityRewardIndex)
{
    m_nActivityReward |= (1 << nActivityRewardIndex);
}

inline BOOL CRole::GetActivityRewardByIndex(INT32 nActivityRewardIndex)
{
    return m_nActivityReward & (1 << nActivityRewardIndex);
}

inline BOOL CRole::GetActivityReward()
{
	return m_nActivityReward;
}

inline void CRole::ClearActivity()
{
    m_nActivity = 0;
    m_nActivityReward = 0;
}

#ifdef _ROBOT
inline void CRole::SetExp(INT32 nExp)
{
    m_nExp = nExp;
}

inline void CRole::SetServerGroup(UINT8 byGroupID)
{
    m_nServerGroupID = byGroupID;
}

inline void CRole::SetBattleQueueState(BOOL bQueue)
{
	m_bInBattleQueue = bQueue;
}

inline BOOL	CRole::IsInBattleQueue()
{
	return m_bInBattleQueue;
}

inline void CRole::SetArenaQueueState(BOOL bQueue)
{
	m_bInArenaQueue = bQueue;
}

inline BOOL CRole::IsInArenaQueue()
{
	return m_bInArenaQueue;
}

inline UINT32 CRole::GetFirstMail() const
{
    if (m_lstMails.empty())
        return 0;
    else
        return *(m_lstMails.begin());
}

inline UINT32 CRole::GetFirstAttach() const
{
    if (m_lstAttachments.empty())
        return 0;
    else
        return *(m_lstAttachments.begin());
}

inline INT32 CRole::GetRandomAuctionItemID() const
{
    if (m_lstAuctionItemID.empty())
        return 0;
    else
    {
        INT32 rand_num = g_Random((INT32)m_lstAuctionItemID.size());
        std::set<INT32>::const_iterator it = m_lstAuctionItemID.begin();
        while (rand_num--)
            ++it;
        return *it;
    }
}

inline UINT32 CRole::GetFirstSellingAuction() const
{
    if (m_lstAuctionSellingItems.empty())
        return 0;
    else
        return *(m_lstAuctionSellingItems.begin());
}

inline UINT32 CRole::GetFirstBuyingAuction() const
{
    if (m_lstAuctionBuyingItems.empty())
        return 0;
    else
        return *(m_lstAuctionBuyingItems.begin());
}

#endif  // _ROBOT

//inline INT32 CRole::GetSide(void)
//{
//	return m_bySide;
//}
//
//inline void  CRole::SetSide(UINT8 bySide)
//{
//	m_bySide = bySide;
//}

inline CProMails* CRole::GetProMails(void)
{
    return &m_ProMails;
}

inline CItemBag* CRole::GetItemBag(void)
{
    return &m_ItemBag;
}

inline CTrade* CRole::GetTrade(void)
{
    return &m_Trade;
}

inline CStall* CRole::GetStall(void)
{
    return &m_Stall;
}

inline CFriend* CRole::GetFriend(void)
{
    return &m_Friend;
}

inline CShieldList* CRole::GetShieldList(void)
{
    return &m_ShieldList;
}

inline ERoleState CRole::GetState(void)
{
    return m_eState;
}

inline UINT8 CRole::GetFcmState(void)
{
    return m_eFcmState;
}

inline INT32 CRole::GetFcmRate(void)
{
	if (m_eFcmState == fcmsFull)
		return RATE_MAX;
	else if (m_eFcmState = fcmsHalf)
		return RATE_MAX / 2;
	else
		return 0;
}

inline INT32 CRole::GetFaction()
{
    return m_nFaction;
}

inline INT32 CRole::GetGMLevel()
{
    return m_nGMLevel;
}

inline void CRole::SetGMLevel(INT32 nGMLevel)
{
	m_nGMLevel = nGMLevel;
}

inline void CRole::SetState(ERoleState eState)
{
    m_eState = eState;
}

inline void CRole::SetFcmState(UINT8 eFcmState)
{
    m_eFcmState = eFcmState;
}

inline void CRole::SetFreeMode(UINT8 byFreeMode)
{
    m_bFreeMode = byFreeMode;
}

inline BOOL CRole::IsFreeMode(void)
{
    return m_bFreeMode;
}

inline void CRole::SetInJump(void)
{
    m_bInJump = TRUE;
}

inline void CRole::ClearInJump(void)
{
    m_bInJump = FALSE;
}

inline BOOL CRole::IsInJump(void)
{
    return m_bInJump;
}

inline void CRole::SetInLogin(void)
{
    m_bInLogin = TRUE;
}

inline void CRole::ClearInLogin(void)
{
    m_bInLogin = FALSE;
}

inline BOOL CRole::IsInLogin(void)
{
    return m_bInLogin;
}

inline CQuestList & CRole::GetQuestList()
{
    return m_QuestList;
}

inline CKillNpcQuest& CRole::GetKillNpcQuest(void)
{
	return m_KillNpcQuest;
}

inline CReputation& CRole::GetReputation(void)
{
    return m_Reputation;
}

inline CAchievementsList& CRole::GetAchievementList(void)
{
	return m_AchievementList;
}

inline CSpirit& CRole::GetSpirit(void)
{
	return m_Spirit;
}

inline UINT32 CRole::GetInteractNpc()
{
    return m_dwInteractNpcID;
}

inline CMaster& CRole::GetMaster(void)
{
    return m_Master;
}

inline CArena& CRole::GetArena(void)
{
    return m_Arena;
}

inline CAsimovRole* CRole::GetAsimovRole()
{
#ifdef _ROBOT
    return &m_AsimovRole;
#else
    return NULL;
#endif //_ROBOT
}

inline CTitle& CRole::GetTitle(void)
{
    return m_Title;
}

inline UINT32 CRole::GetGuildID(void)
{
    return m_dwGuildID;
}

inline CRoleGuildData& CRole::GetRoleGuildData()
{
    return m_Guild;
}

inline void CRole::SetGuildID(UINT32 dwGuildID)
{
    m_dwGuildID = dwGuildID;
}

inline CHero* CRole::GetHero(void)
{
	return m_poHero;
}

inline BOOL CRole::IsRobot()
{
    return (m_dwSessionID != 0);
}

inline void CRole::SetTeamID(UINT32 dwTeamID)
{
    m_dwTeamID = dwTeamID;
}

inline UINT32 CRole::GetTeamID()
{
    return m_dwTeamID;
}

inline void CRole::SetBattleTeamID(UINT32 dwTeamID)
{
	m_dwBattleTeamID = dwTeamID;
}

inline UINT32 CRole::GetBattleTeamID()
{
	return m_dwBattleTeamID;
}

inline void CRole::SetClientUploadTargetID(UINT32 dwTargetID)
{
	m_dwClientUploadTarget = dwTargetID;
}

inline UINT32 CRole::GetClientUploadTargetID(void)
{
	return m_dwClientUploadTarget;
}


//inline void CRole::SetArenaTeamID(UINT32 dwArenaTeamID)
//{
//	m_dwArenaTeamID = dwArenaTeamID;
//}
//
//inline UINT32 CRole::GetArenaTeamID()
//{
//	return m_dwArenaTeamID;
//}

//inline void CRole::SetPersonalArenaScore(INT32 nScore)
//{
//	m_nPersonalArenaScore = (nScore > 0 ? nScore : 0);
//}
//inline INT32 CRole::GetPersonalArenaScore(void)
//{
//	return m_nPersonalArenaScore;
//}

//inline void CRole::SetTeamArenaScore(INT32 nScore)
//{
//	m_nTeamArenaScore = nScore;
//}
//
//inline UINT32 CRole::GetTeamArenaScore(void)
//{
//	return m_nTeamArenaScore;
//}

inline void CRole::SetTeleportID(UINT32 dwTeleport)
{
    m_dwTeleportID = dwTeleport;
}

inline UINT32 CRole::GetTeleportID(void)
{
    return m_dwTeleportID;
}

inline ERoleNameColor CRole::GetNameColor(void)
{
    if (m_dwPkValue >= g_GWConfig.nRedNamePkValueLimit)
        return rncRed;
    if (m_dwPkValue >= g_GWConfig.nYellowNamePkValueLimit)
        return rncYellow;
    return rncWhite;
}

inline BOOL CRole::IsRedName(void)
{
    return m_dwPkValue >= g_GWConfig.nRedNamePkValueLimit;
}

inline UINT32 CRole::GetForbidChatTime()
{
    return m_dwForbidChatTime;
}

inline void CRole::SetForbidChatTime(UINT32 dwForbidChatTime)
{
    m_dwForbidChatTime = dwForbidChatTime;
}

inline UINT32 CRole::GetNormalChatTimer(void)
{
	return m_nNormalChatTimer;
}

inline void CRole::SetNormalChatTimer(INT32 nNormalChatTimer)
{
	m_nNormalChatTimer = nNormalChatTimer;
}

inline UINT32 CRole::GetGroupChatTimer(void)
{
	return m_nGroupChatTimer;
}

inline void CRole::SetGroupChatTimer(INT32 nGroupChatTimer)
{
	m_nGroupChatTimer = nGroupChatTimer;
}

inline UINT32 CRole::GetLastAdjacentNoTeamRoleFrame(void)
{
    return m_dwLastAdjacentNoTeamRoleFrame;
}

inline void	CRole::SetLastAdjacentNoTeamRoleFrame(UINT32 dwFrame)
{
    m_dwLastAdjacentNoTeamRoleFrame = dwFrame;
}

inline UINT32 CRole::GetLastAdjacentTeamFrame(void)
{
    return m_dwLastAdjacentTeamFrame;
}

inline void	CRole::SetLastAdjacentTeamFrame(UINT32 dwFrame)
{
    m_dwLastAdjacentTeamFrame = dwFrame;
}

inline INT32 CRole::GetPkMode(void)
{
	return m_nPkMode;
}

inline INT32 CRole::GetLogoutFrame()
{
	return m_nLogoutFrame;
}

inline void CRole::ClearLogoutFrame()
{
	m_nLogoutFrame = 0;
}

inline ERoleLogoutType CRole::GetLogoutType()
{
	return m_eLogoutType;
}

inline INT32 CRole::GetVariable(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_ROLE_VARIABLE_COUNT);

	return m_nVarList[nIndex];
Exit0:
    return 0;
}

inline INT32 CRole::GetClientVariable(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_CLIENT_VARIABLE_COUNT);

    return m_nClientVarList[nIndex];
Exit0:
    return 0;
}

inline void CRole::SetLastSlot(INT32 nSlotID)
{
	m_nLastCastSlotID = nSlotID;
}

inline INT32 CRole::GetLastSlot(void)
{
	return m_nLastCastSlotID;
}

inline void CRole::ClearSpellCache(void)
{
	m_SpellCache.m_nSpellID = 0;
	m_SpellCache.m_dwTargetID = 0;
	m_SpellCache.m_llX = 0;
	m_SpellCache.m_llY = 0;
	m_SpellCache.m_llZ = 0;
}

inline BOOL CRole::CacheSpell(INT32 nSpellID, INT32 nSpellSerial, UINT32 dwTargetID, INT64 llX, INT64 llY, INT64 llZ)
{
	PROCESS_ERROR(m_SpellCache.m_nSpellID == 0);

	m_SpellCache.m_nSpellID = nSpellID;
	m_SpellCache.m_nSpellSerial = nSpellSerial;
	m_SpellCache.m_dwTargetID = dwTargetID;
	m_SpellCache.m_llX = llX;
	m_SpellCache.m_llY = llY;
	m_SpellCache.m_llZ = llZ;

	return TRUE;
Exit0:
	return FALSE;
}

inline void CRole::SetSpellSerial(INT32 nSerial)
{
	m_nSpellSerial = nSerial;
}

inline void CRole::PushEquippingSpell(CSpell* poSpell)
{
	m_EquippingSpellStack.push(poSpell);
}

inline void CRole::PopEquippingSpell(void)
{
	m_EquippingSpellStack.pop();
}


inline INT32 CRole::GetLastSaveFrame(void)
{
    return m_nLastSaveFrame;
}

inline void CRole::SetLoadingSceneEndFrame(INT32 nFrame)
{
	m_nLoadingSceneEndFrame = nFrame;
}

inline INT32 CRole::GetLoadingSceneEndFrame(void)
{
	return m_nLoadingSceneEndFrame;
}

inline INT32 CRole::GetTryReviveFrm(INT32 nType)
{
	LOG_PROCESS_ERROR(nType > crtInvalid && nType < crtTotal);

	return m_nTryReviveFrm[nType];
Exit0:
	return -1;

}

inline INT32 CRole::GetNextReviveFrm(void)
{
	return m_nNextFreeReviveFrm;
}


inline INT32 CRole::GetTryReviveCount(INT32 nType)
{
	LOG_PROCESS_ERROR(nType > crtInvalid && nType < crtTotal);

	return m_nTryReviveCount[nType];
Exit0:
	return -1;
}

inline void CRole::SetBattleEnterPos(INT32 nSceneTempID, INT32 nSceneID, UINT8 bySide)
{
	m_EnterBattlePos.nSceneTempID = nSceneTempID;
	m_EnterBattlePos.nSceneID = nSceneID;
	m_EnterBattlePos.bySide = bySide;
}

inline const ENTER_POS& CRole::GetBattleEnterPos()
{
	return m_EnterBattlePos;
}

//inline void CRole::SetArenaEnterPos(INT32 nSceneTempID, INT32 nSceneID, UINT8 bySide)
//{
//	m_EnterArenaPos.nSceneTempID = nSceneTempID;
//	m_EnterArenaPos.nSceneID = nSceneID;
//	m_EnterArenaPos.bySide = bySide;
//}
//
//inline const ENTER_POS& CRole::GetArenaEnterPos()
//{
//	return m_EnterArenaPos;
//}

inline void CRole::BeginMount(void)
{
	m_MountItr = m_ActivedMountList.begin();
}

inline INT32 CRole::NextMount(void)
{
	INT32 nMountID = 0;
	PROCESS_ERROR(m_MountItr != m_ActivedMountList.end());

	nMountID = *m_MountItr;

	++m_MountItr;
Exit0:
	return nMountID;
}

inline INT32 CRole::GetMountCount(void)
{
	return (INT32)m_ActivedMountList.size();
}

inline INT32 CRole::GetConsecutiveKillNpcCount()
{
	return m_nConsecutiveKillNpcCount;
}

inline INT32 CRole::GetConsecutiveKillPlayerCount()
{
	return m_nConsecutiveKillPlayerCount;
}

inline UINT32 CRole::GetLastLineSceneTempID(void)
{
	return m_dwLastLineSceneTempID;
}

inline void CRole::SetLastLineSceneTempID(UINT32 dwSceneTempID)
{
	m_dwLastLineSceneTempID = dwSceneTempID;
}

inline UINT32 CRole::GetLastLineSceneID(void)
{
	return m_dwLastLineSceneID;
}

inline void CRole::SetLastLineSceneID(UINT32 dwSceneID)
{
	m_dwLastLineSceneID = dwSceneID;
}

inline INT32 CRole::GetPetState(void)
{
	return m_nPetState;
}

inline void CRole::SetPetState(INT32 nState)
{
	LOG_PROCESS_ERROR(nState > psInvalid && nState < psTotal);
	m_nPetState = nState;
Exit0:
	return;
}



inline INT32 CRole::GetPetCount(void)
{
	return m_nPetCount;
}

inline INT32 CRole::GetMaxPetCount(void)
{
    return MAX_PET_PER_ROLE;
}

inline INT32 CRole::GetPetIndex(UINT32 dwNpcID)
{
    for (INT32 nIndex = 0; nIndex < m_nPetCount; ++nIndex)
    {
        if (m_Pet[nIndex].dwNpcID == dwNpcID)
        {
            return nIndex;
        }
    }

    return MAX_PET_PER_ROLE;
}


inline UINT32 CRole::GetPetNpcID(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex < m_nPetCount);
    return m_Pet[nIndex].dwNpcID;
Exit0:
    return INVALID_OBJECT_ID;
}

inline UINT32 CRole::GetPetType(INT32 nIndex)
{
    LOG_PROCESS_ERROR(nIndex < m_nPetCount);
    return m_Pet[nIndex].nPetType;
Exit0:
    return INVALID_OBJECT_ID;
}

inline BOOL CRole::IsMyPet(UINT32 dwNpcID)
{
    LOG_PROCESS_ERROR(m_nPetCount <= GetMaxPetCount());

    for (INT32 i = 0; i < m_nPetCount; ++i)
        PROCESS_SUCCESS(dwNpcID == m_Pet[i].dwNpcID);

Exit0:
    return FALSE;
Exit1:
    return TRUE;
}

#ifndef _ROBOT
inline SGPK::IGPKCSAuth* CRole::GetGpkAuth(void)
{
	return m_poGpkAuth;
}
#endif

inline INT32 CRole::GetLastCheckInIndex(void)
{
	return m_LastCheckInInfo.nIndex;
}

inline INT32 CRole::GetJigsawAnswerIdx(void)
{
	return m_nJigsawAnswerIndex;
}

inline UINT32 CRole::GetJigsawSn(void)
{
	return m_dwJigsawSn;
}

inline void CRole::SetAntiCheatLevel(INT32 nLevel)
{
	m_nAntiCheatLevel = nLevel;
}

inline UINT32 CRole::GetTotalExerciseTime() const
{
    return m_dwTotalExerciseTime;
}

inline void CRole::SetTotalExerciseTime(UINT32 dwTime)
{
    m_dwTotalExerciseTime = dwTime;
}

inline UINT32 CRole::GetStartExerciseTime() const
{
    return m_dwStartExerciseTime;
}

inline void CRole::SetStartExerciseTime(UINT32 dwTime)
{
    m_dwStartExerciseTime = dwTime;
}

inline BOOL CRole::GetDoingSubTime() const
{
    return m_bDoingSubTime;
}

inline void CRole::SetDoingSubTime(BOOL bDoingSubTime)
{
    m_bDoingSubTime = bDoingSubTime;
}

inline void CRole::SetIpAddr(UINT32 dwIpAddr)
{
	m_dwIpAddr = dwIpAddr;
}

inline UINT32 CRole::GetIpAddr(void)
{
	return m_dwIpAddr;
}

inline void CRole::SetIpWhiteList(BOOL bIpWhiteList)
{
	m_bIpWhiteList = bIpWhiteList;
}

inline BOOL CRole::IsIpWhiteList(void)
{
	return m_bIpWhiteList;
}

inline void CRole::SetUserWhiteList(BOOL bUserWhiteList)
{
	m_bUserWhiteList = bUserWhiteList;
}

inline BOOL CRole::IsUserWhiteList(void)
{
	return m_bUserWhiteList;
}

#endif	// _ROLE_INL_H_
