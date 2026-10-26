#ifndef _NPC_H_
#define _NPC_H_

#include "npc_def.h"
#include "character.h"
#include "spell_book_npc.h"
#include "string_def.h"

struct NPC_DATA;

class CRole;
class CNpc;
struct NPC_PATTERN_DATA;
struct NPC_SPAWN_POINT;
class CTeamInGS;

class CNpc : public CCharacter
{
public:
	CNpc();
	virtual ~CNpc();

	virtual const TCHAR* GetName(void);
	virtual INT32 GetObjType(void);
	virtual INT32 GetSpecies(void);

	virtual BOOL MainLoop(void);

	virtual BOOL Die(INT32 nParam);
	virtual void OnHurt(CCharacter* poDealer, CBullet* poBullet, INT32 nEffectValue);

	virtual ISpellBook& GetSpellBook(void);

	virtual BOOL JumpTo(INT64 llX, INT64 llY, INT64 llZ, INT32 nFaceDirection);

	virtual BOOL Revive(INT32 nParam, INT32 nHpPercent);

	virtual INT32 ChangeHp(INT32 nValue, INT32 nReason);

public:
	BOOL Init(UINT32 dwObjID, const NPC_SPAWN_POINT* pSpawnPoint, UINT32 dwHostID);
	BOOL SetTemplateData(INT32 nTemplateID);
	BOOL UnInit(void);

	inline const NPC_DATA* GetNpcData(void);
	inline const NPC_SPAWN_POINT* GetSpawnPoint(void);
	inline INT32 GetQuality(void);

	BOOL SetAlwaysRun(BOOL bAlwaysRun);
	inline BOOL GetAlwaysRun();

	inline BOOL NeverBeHit(void);

	inline void SetHighestSpellLevel(INT32 nLevel);
	inline void SetGenerateDrop(BOOL bGenerateDrop);

    inline void SetNpcTimer(INT32 nNpcTimer);

	inline void SetIsSummoned(BOOL bSummoned);
	inline BOOL IsSummoned(void);

	BOOL ResetFlags(void);
    inline BOOL RemoveCorpse(void);

    BOOL TransformToPet(INT32 nPetType, INT32 nCurLevel, INT32 nSpellLevel, INT32 nMaxPetLevel, UINT32 dwAliveFrm, INT32 nPetExp);
    BOOL TransformToNpc(void);

    inline BOOL IsPet(void);
    inline INT32 GetPetType(void);
	inline void SetPetType(INT32 nPetType);
    BOOL ChangePetAI(INT32 nPetState);

	inline INT32 GetPetLevel(void);
	BOOL SetPetLevel(INT32 nPetLevel, BOOL bDecOldAttr);

    inline INT32 GetPetInitLevel(void);

    inline INT32 GetPetMaxLevel(void);
    inline void SetMaxPetLevel(INT32 nMaxPetLevel);

    UINT32 GetPetAliveFrm(void);

	inline INT32 GetPetExp(void);
	void AddPetExp(INT32 nPetExp);

	inline void SetPetHpRestore(INT32 nValue);
	inline INT32 GetPetHpRestore(void);

	inline void SetAvoidGroundEffect(BOOL bEnabled);

#ifdef _ROBOT
	inline void AddStartQuest(INT32 nQuestID);
	inline void AddEndQuest(INT32 nQuestID);

	inline INT32 GetFirstStartQuestID(void);
	inline INT32 GetNextStartQuestID(void);

	inline INT32 GetFirstEndQuestID(void);
	inline INT32 GetNextEndQuestID(void);
#endif

protected:
	virtual BOOL _GridMove(INT64 llDestX, INT64 llDestY);

	virtual BOOL _ComputeAttribute(INT32 nNewLevel);
    BOOL _ComputePetExtraAttribute(INT32 nNewPetLevel, BOOL bDecOldAttr);

	virtual void _Recovery(void);

	virtual BOOL _ChangeRegion(CRegion* poDestRegion);
	BOOL _NpcLoop(void);

	BOOL _DistributeRegionBonus(CRole* poRole, CTeamInGS* poTeam, CRole* poKiller);
	BOOL _DistributeSceneBonus(CRole* poRole, CTeamInGS* poTeam);

	void _On1SecMainLoop(void);

private:
	CNpcSpellBook			m_SpellBook;
	const NPC_DATA*		    m_pNpcData;
	const NPC_PATTERN_DATA*	m_pNpcPattern;

	const NPC_SPAWN_POINT*  m_pSpawnPoint;
	INT32                   m_nQuality;
	INT32                   m_nNpcState;
	INT32					m_nSpawnFrame;
	INT32                   m_nNpcTimer;

	INT32					m_nFindState;
	INT32					m_nFindTimer;
	INT32					m_nFindTimes;
	INT32					m_nPathSide;
	BOOL					m_bAvoidGroundEffect;

	BOOL					m_bGenerateDrop;
	BOOL					m_bIsSummoned;
    BOOL                    m_bAlwaysRun;
	BOOL					m_bNeverBeHit;

    INT32					m_nPetType;
	INT32					m_nPetLevel;
    INT32                   m_nPetInitLevel;
	INT32					m_nPetMaxLevel;
	INT32					m_nPetExp;
    UINT32                  m_dwPetAliveFrm;
	INT32					m_nPetHpRestore;



	INT32					m_nLastRecoveryFrm;

#ifdef _ROBOT
	typedef std::set<INT32> TQuestList;
	TQuestList m_StartQuestList;
	TQuestList m_EndQuestList;

	TQuestList::iterator m_QuestItr;
#endif
};

inline const NPC_DATA* CNpc::GetNpcData(void)
{
	return m_pNpcData;
}

inline const NPC_SPAWN_POINT* CNpc::GetSpawnPoint(void)
{
	return m_pSpawnPoint;
}

inline INT32 CNpc::GetQuality(void)
{
	return m_nQuality;
}

inline void CNpc::SetHighestSpellLevel(INT32 nLevel)
{
	m_SpellBook.SetHighestSpellLevel(nLevel);
}

inline void CNpc::SetGenerateDrop(BOOL bGenerateDrop)
{
	m_bGenerateDrop = bGenerateDrop;
}

inline void CNpc::SetNpcTimer(INT32 nNpcTimer)
{
    m_nNpcTimer = nNpcTimer;
}

inline void CNpc::SetIsSummoned(BOOL bSummoned)
{
	m_bIsSummoned = bSummoned;
}

inline BOOL CNpc::IsSummoned(void)
{
	return m_bIsSummoned;
}

inline BOOL CNpc::RemoveCorpse(void)
{
    LOG_PROCESS_ERROR(m_nNpcState == npcCorpse);
    m_nNpcTimer = 0;
    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL CNpc::IsPet(void)
{
    return m_nPetType != 0;
}

inline INT32 CNpc::GetPetType(void)
{
    return m_nPetType;
}

inline void CNpc::SetPetType(INT32 nPetType)
{
    m_nPetType = nPetType;
}

inline INT32 CNpc::GetPetLevel(void)
{
	return m_nPetLevel;
}

inline INT32 CNpc::GetPetExp(void)
{
	return m_nPetExp;
}

inline INT32 CNpc::GetPetInitLevel(void)
{
    return m_nPetInitLevel;
}

inline INT32 CNpc::GetPetMaxLevel(void)
{
    return m_nPetMaxLevel;
}

inline void CNpc::SetMaxPetLevel(INT32 nMaxPetLevel)
{
    m_nPetMaxLevel = nMaxPetLevel;
}

inline BOOL CNpc::GetAlwaysRun()
{
    return m_bAlwaysRun;
}

inline void CNpc::SetPetHpRestore(INT32 nValue)
{
	m_nPetHpRestore = nValue;
}

inline INT32 CNpc::GetPetHpRestore(void)
{
	return m_nPetHpRestore;
}

inline void CNpc::SetAvoidGroundEffect(BOOL bEnabled)
{
	m_bAvoidGroundEffect = bEnabled;
}

inline BOOL CNpc::NeverBeHit(void)
{
	return m_bNeverBeHit;
}


#ifdef _ROBOT

inline void CNpc::AddStartQuest(INT32 nQuestID)
{
	m_StartQuestList.insert(nQuestID);
}

inline void CNpc::AddEndQuest(INT32 nQuestID)
{
	m_EndQuestList.insert(nQuestID);
}

inline INT32 CNpc::GetFirstStartQuestID(void)
{
	m_QuestItr = m_StartQuestList.begin();

	if (m_QuestItr == m_StartQuestList.end())
		return 0;

	return *m_QuestItr;
}

inline INT32 CNpc::GetNextStartQuestID(void)
{
	if (m_QuestItr == m_StartQuestList.end())
		return 0;

	++m_QuestItr;

	if (m_QuestItr == m_StartQuestList.end())
		return 0;

	return *m_QuestItr;
}

inline INT32 CNpc::GetFirstEndQuestID(void)
{
	m_QuestItr = m_EndQuestList.begin();

	if (m_QuestItr == m_EndQuestList.end())
		return 0;

	return *m_QuestItr;

}

inline INT32 CNpc::GetNextEndQuestID(void)
{
	if (m_QuestItr == m_EndQuestList.end())
		return 0;

	++m_QuestItr;

	if (m_QuestItr == m_EndQuestList.end())
		return 0;

	return *m_QuestItr;
}

#endif // _ROBOT

#endif	// _NPC_H_

