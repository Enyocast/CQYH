#ifndef _QUEST_LIST_H_
#define _QUEST_LIST_H_

#include "quest_def.h"
#include "variable_def.h"
#include "quest_data.h"

class CRole;
class CAuraList;
class CNpc;

struct ACCEPTED_QUEST 
{
    INT32   nQuestID;
    UINT32  dwAcceptTime;
	INT32   nKillDoodadCount[MAX_CONDITION_PER_QUEST];
	INT32   nKillNpcCount[MAX_CONDITION_PER_QUEST];
	INT32   nVariable[MAX_VARIABLE_PER_QUEST];
	INT32	nKillPlayerCount[CHECK_KILL_PLAYER_CONDITION];
	INT32	nKillBufPlayerCount[CHECK_KILL_PLAYER_CONDITION];
    INT32   nCheckItemCount[MAX_CONDITION_PER_QUEST];
};

struct CIRCLE_QUEST
{
	INT32	nQuestID;
	INT32	nCompleteCount;			// Total cycle quest rounds
	INT32	nCircleNumber;			// Current cycle number
	UINT32	nLastCompleteTime;		// Last completion time
};

class CQuestList
{
public:
	CQuestList();
	virtual ~CQuestList();

    BOOL Init(CRole* pOwner);
    BOOL UnInit(void);
    
	BOOL Load_v_1(const char* pData, UINT32 dwSize);
	BOOL Save(const char* pData, UINT32& rdwSize);

	BOOL DailyRefresh(void);
	BOOL WeeklyRefresh(void);

	/******************** normal *************************/
    
    INT32 CanAccept(INT32 nQuestID, INT32 nAcceptType, INT32 nSrcID);
    INT32 CanAccept(const QUEST_DATA* pQuestData, INT32 nAcceptType, INT32 nSrcID);
	INT32 Accept(INT32 nQuestID);

	INT32 CanComplete(INT32 nQuestID);
	INT32 Complete(INT32 nQuestID, INT32 nSelectedAwardIndex=0);

    INT32 CanAbandon(INT32 nQuestID);
	INT32 Abandon(INT32 nQuestID);

	const ACCEPTED_QUEST* GetAcceptedQuest(INT32 nQuestID);
	BOOL IsQuestCompleted(INT32 nQuestID);

	void SetQuestFailed(const ACCEPTED_QUEST* pAcceptedQuest);

	void SetVariable(const ACCEPTED_QUEST* pAcceptedQuest, INT32 nIndex, INT32 nValue);
	inline INT32 GetVariable(const ACCEPTED_QUEST* pAcceptedQuest, INT32 nIndex);

	inline INT32 GetItemRecycleVarIndex();
	inline INT32 SetItemRecycleVarIndex(INT32 nIndex);

	inline UINT32 GetRepeatQuestScanTime();
	BOOL CheckNpc(INT32 nNpcTemplateID, INT32 nAcceptType);

	BOOL  GetAcceptedQuestBegin();
	INT32 GetNextAcceptedQuest();
	
	inline BOOL IsRecodeKillPlayer();
	inline BOOL IsEmegencyQuest(const QUEST_DATA* pQuestData);

	INT32 GetRandomAcceptedQuest();

	/******************** special *************************/

	void OnKillDoodad(UINT32 dwDoodadId);
	void OnKillNpc(CNpc* pNpc);
    INT32 GetRequireItemCount(INT32 nItemID);
	void OnKillPlayer(INT32 nPlayerLevel, CAuraList* pAuraList);

	/******************** circle quest *************************/
	
	INT32 GenerateCircleQuest(INT32 nCircleID);
	INT32 GetCircleQuestID(INT32 nCircleID);

	inline UINT32 GetCircleIndex();
	inline void	  SetCircleIndex(UINT32 dwCircleIndex);

	/******************** reward quest *************************/

	INT32 GenerateRewardQuest(void);	
	inline UINT64 GetRewardQuest(void);
	inline UINT64 GetRewardAccepted(void);
	inline UINT64 GetRewardCompleted(void);

	INT32 BuyRewardBoughtTime(INT32 nRewardBoughtTime);
	inline void SetRewardBoughtTime(INT32 nRewardBoughtTime);
	inline UINT32 GetRewardBoughtTime(void);

	inline INT32 GetRewardQuestRemainCompleteTime();

	inline INT32 GetRewardIndex(void);

	inline UINT32 GetRewardBrushCDTime(void);
	inline void	 SetRewardBrushCDTime(UINT32 dwRewardBrushCDTime);

    ACCEPTED_QUEST* Begin();
    const ACCEPTED_QUEST* Next();

private:
    CRole*					m_pOwner;

	typedef std::list<ACCEPTED_QUEST>   ACCEPTED_QUEST_LIST;
	ACCEPTED_QUEST_LIST		m_AcceptedNormalQuestList;
	ACCEPTED_QUEST_LIST		m_AcceptedEmergencyQuestList;
	
	ACCEPTED_QUEST_LIST::iterator   m_AcceptedQuestCursor;
	ACCEPTED_QUEST_LIST		m_AcceptIteratQuestList;

	/******************** normal *************************/

	UINT32					m_dwRepeatQuestScanTime;

	UINT8					m_byNormalQuest[MAX_NORMAL_QUEST_COUNT / 8];
    UINT8					m_byRepeatQuest[MAX_REPEAT_QUEST_COUNT];

	BOOL					m_bRecodeKillPlayer;

	// quest recycle based
	INT32					m_nItemRecycleVarIndex;

	/******************** circle quest  *************************/

	UINT32					m_dwCircleIndex;
	UINT64					m_GroupMutex;
	CIRCLE_QUEST			m_stCircleQuest[MAX_CIRCLE_COUNT];

	/******************** reward quest  *************************/

	UINT64	m_qwRewardQuest;					// Current daily quests, stored as bits
	UINT64	m_qwRewardAccepted;					// Whether current quests have been accepted
	UINT64  m_qwRewardCompleted;				// Whether current quests are complete
	INT32	m_nRewardIndex;						// Current quest index (one index per five levels)

	INT32	m_dwRewardBoughtTime;				// Purchased increases to the quest completion limit
	INT32	m_nRewardQuestRemainCompleteTime;	// Remaining attempts per player per day
	UINT32	m_dwRewardQuestBrushCDTime;			// Refresh cooldown
	UINT32	m_nRewardCompleteCount;				// Completions today

	INT32	m_nDailyRewwardBoughtTime;			// Completion-limit increases purchased today (used to cap purchases)

	ACCEPTED_QUEST_LIST	m_AcceptedQuest;		// Expired unfinished quests for one-click daily quest completion

	UINT32	m_dwLastCompleteEmergencyQuestTime;
	INT32	m_nCompleteEmergencyQuestCount;
private:  
	/******************** normal *************************/

	BOOL _CheckType(INT32 nQuestType);
    ACCEPTED_QUEST_LIST::iterator _GetAcceptedQuest(INT32 nQuestID);
    BOOL _CheckVariable(const ACCEPTED_QUEST* pAcceptedQuest, INT32 nVariableID, INT32 nValue);	
	const QUEST_REWARD_DATA* _GetQuestReward(const QUEST_DATA* pQuestData);
	BOOL _CheckKillPlayer(ACCEPTED_QUEST* pAcceptQuest, INT32 nPlayerLevel, CAuraList* pAuraList);

	// item recycle 
	BOOL _SetItemRecycleVariable(INT32 nVariableID);
	BOOL _ClearItemRecycleVariable();

	/******************** reward *************************/
	BOOL _IsRewardQuestAllCompleted(void);
	INT32 _GetAcceptedRewardQuestCount(void);

	/******************** emergency *************************/
	inline BOOL _IsEmergencyQuest(INT32 nQuestID);
};

/******************** normal *************************/

inline INT32 CQuestList::GetVariable(const ACCEPTED_QUEST* pAcceptedQuest, INT32 nIndex)
{
    LOG_PROCESS_ERROR(pAcceptedQuest);
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < MAX_VARIABLE_PER_QUEST);

    return pAcceptedQuest->nVariable[nIndex];
Exit0:
    return 0;
}

inline UINT32 CQuestList::GetRepeatQuestScanTime()
{
	return m_dwRepeatQuestScanTime;
}

inline BOOL CQuestList::IsRecodeKillPlayer()
{
	return m_bRecodeKillPlayer;
}

inline INT32 CQuestList::GetItemRecycleVarIndex()
{
	return m_nItemRecycleVarIndex;
}

inline INT32 CQuestList::SetItemRecycleVarIndex(INT32 nIndex)
{
	m_nItemRecycleVarIndex = nIndex;
}

/******************** circle quest *************************/
inline UINT32 CQuestList::GetCircleIndex()
{
	return m_dwCircleIndex;
}

inline void	CQuestList::SetCircleIndex(UINT32 dwCircleIndex)
{
	m_dwCircleIndex = dwCircleIndex;
}

/******************** reward quest *************************/

inline UINT64 CQuestList::GetRewardQuest(void)
{
	return m_qwRewardQuest;
}

inline UINT64 CQuestList::GetRewardAccepted(void)
{
	return m_qwRewardAccepted;
}

inline UINT64 CQuestList::GetRewardCompleted(void)
{
	return m_qwRewardCompleted;
}

inline void CQuestList::SetRewardBoughtTime(INT32 nRewardBoughtTime)
{
	m_dwRewardBoughtTime = nRewardBoughtTime;
}

inline UINT32 CQuestList::GetRewardBoughtTime()
{
	return m_dwRewardBoughtTime;
}

inline INT32 CQuestList::GetRewardQuestRemainCompleteTime()
{
	return m_nRewardQuestRemainCompleteTime;
}

inline INT32 CQuestList::GetRewardIndex()
{
	return m_nRewardIndex;
}

inline UINT32 CQuestList::GetRewardBrushCDTime(void)
{
	return m_dwRewardQuestBrushCDTime;
}

inline void	 CQuestList::SetRewardBrushCDTime(UINT32 dwRewardBrushCDTime)
{
	m_dwRewardQuestBrushCDTime = dwRewardBrushCDTime;
}

inline BOOL CQuestList::_IsEmergencyQuest(INT32 nQuestID)
{
	return ((nQuestID >= EMERGENCY_QUEST_START_ID) && (nQuestID < EMERGENCY_QUEST_START_ID + MAX_EMERGENCY_QUEST_COUNT));
}

#endif	// _QUEST_LIST_H_
