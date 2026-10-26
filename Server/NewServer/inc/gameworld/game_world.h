#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "id_object_pool.h"
#include "object_pool.h"

#include "id_def.h"
#include "role.h"
#include "scene.h"
#include "region.h"
#include "grid_def.h"
#include "npc.h"
#include "hero.h"
#include "doodad.h"
#include "missile.h"
#include "threat_list.h"
#include "spell_set.h"
#include "spell_instance.h"
#include "spell_book.h"
#include "spell_bullet.h"
#include "spell_slot.h"
#include "aura_instance.h"
#include "drop.h"
#include "team.h"
#include "btnod.h"
#include "bt_manager.h"
#include "ai_signal.h"
#include "ai_processor.h"

#if defined(__linux__)
    #define SPL(__message__, ...)   if(g_GWConfig.DebugOption.debugsp) CLog::GetInstance().WriteLog(lltSpell, __message__, ##__VA_ARGS__)
#else   // __linux__
    #define SPL    if(g_GWConfig.DebugOption.debugsp) CLog::GetInstance().SplLog
#endif

class IMessageNotifier;
class IPacketAllocator;

struct TRIE_NODE;
struct COLLISION_NODE;

class CGameWorld
{
public:
	CGameWorld();
	virtual ~CGameWorld();

	static CGameWorld& GetInstance(void);

    BOOL Init(void);
    BOOL UnInit(void);
    BOOL CleanUpScenes(void);

	BOOL MainLoop(void);
    void Reload(const char* pcszModule);
    void CheckConfig();
	BOOL IsProgrammer(void);
	BOOL IsInLixjList(void);

    inline void SetGsSessionID(UINT32 dwGsSessionID);
    inline UINT32 GetGsSessionID(void);

	inline INT64 GetGameFrame(void);
	inline void SetGameFrame(INT64 llGameFrame);

    inline void SetStartTime(UINT32 dwTime);
    inline UINT32 GetStartTime(void);

    inline void SetStartTick(UINT64 qwTick);
    inline UINT64 GetStartTick(void);

    inline void SetGameTick(UINT64 qwTick);
    inline UINT64 GetGameTick(void);

	inline void SetGameTime(UINT32 dwGameTime);
    inline UINT32 GetGameTime(void);
    inline INT32 GetTimeZone(void);

    inline const tm_ex& GetLocalTime(void);

	inline void SetFreezeTime(BOOL bFreezeTime);
	inline BOOL IsFreezeTime(void);

	BOOL IsDaytime(void);

	inline void SetCanCast(BOOL bCanCast);
	inline BOOL CanCast(void);

	inline void SetCheckConsume(BOOL bCheck);
	inline BOOL CheckConsume(void);

	inline void SetDrawDebugLine(BOOL bDraw);
	inline BOOL DrawDebugLine(void);


	inline CScene* NewScene(UINT64 qwSceneID);
	inline BOOL DelScene(CScene* poScene);
	inline CScene* FindScene(UINT64 qwSceneID);
    template<class TFunc>
    inline BOOL TraverseScene(TFunc& rFunc);

	inline CRegion* NewRegion(void);
	inline BOOL DelRegion(CRegion* poRegion);

	inline CRole* NewRole(UINT32 dwRoleID);
	inline BOOL DelRole(CRole* poRole);
	inline CRole* FindRole(UINT32 dwRoleID);
    inline INT32 GetRoleCount(void);
    template<class TFunc>
    inline BOOL TraverseRole(TFunc& rFunc);

	inline CNpc* NewNpc(UINT32 dwNpcID);
	inline BOOL DelNpc(CNpc* poNpc);
    inline CNpc* FindNpc(UINT32 dwNpcID);
    inline UINT32 GetNpcID(CNpc* poNpc);
    template<class TFunc>
    inline BOOL TraverseNpc(TFunc& rFunc);

    inline CAIProcessor* NewAIProcessor(void);
    inline BOOL DelAIProcessor(CAIProcessor* poAIProcessor);

	inline CDoodad* NewDoodad(void);
	inline BOOL DelDoodad(CDoodad* poDoodad);
	inline CDoodad* FindDoodad(UINT32 dwDoodadID);
    inline UINT32 GetDoodadID(CDoodad* poDoodad);

	inline CMissile* NewMissile(void);
	inline BOOL DelMissile(CMissile* poMissile);
	inline CMissile* FindMissile(UINT32 dwMissileID);
    inline UINT32 GetMissileID(CMissile* poMissile);

	inline CHero* NewHero(UINT32 dwHeroID);
	inline BOOL DelHero(CHero* poHero);
	inline CHero* FindHero(UINT32 dwHeroID);
    inline UINT32 GetHeroID(CHero* poHero);

	inline CSceneObject* FindObj(UINT32 dwObj);
	inline CCharacter* FindCharacter(UINT32 dwCharID);

	inline CRole* FindValidRole(UINT32 dwRoleID);
	inline CCharacter* FindValidCharacter(UINT32 dwCharID);
	inline CSceneObject* FindValidObj(UINT32 dwObj);

	inline THREAT_NODE* NewThreatNode(void);
	inline BOOL DelThreatNode(THREAT_NODE* pThreatNode);

	inline TARGET_NODE* NewTargetNode(void);
	inline BOOL DelTargetNode(TARGET_NODE* pNode);

	inline PLACED_GRID* NewPlacedGrid(void);
	inline BOOL DelPlacedGrid(PLACED_GRID* pNode);

	inline CSpellCopy* NewSpellCopy(void);
	inline BOOL DelSpellCopy(CSpellCopy* pSpellInstance);

	inline CSpellSet* NewSpellSet(void);
	inline BOOL DelSpellSet(CSpellSet* pSpellSet);

	inline CSpellInstance* NewSpellInstance(void);
	inline BOOL DelSpellInstance(CSpellInstance* pSpellInstance);

	inline NextSpell* NewNextSpell(void);
	inline BOOL DelNextSpell(NextSpell* sp);

	inline CAuraInstance* NewAuraInstance(void);
	inline BOOL DelAuraInstance(CAuraInstance* pAuraInstance);

	inline CBullet* NewBullet(void);
	inline BOOL DelBullet(CBullet* poBullet);

	inline BTNod* NewBTNod(void);
	inline BOOL DelBTNod( BTNod* poNod );

    inline CDrop* NewDrop(UINT32 dwDropID);
    inline BOOL DelDrop(CDrop* poDrop);
    inline CDrop* FindDrop(UINT32 dwDropID);
    inline UINT32 GetDropID(CDrop* poDrop);

    inline CTeamInGS* NewTeam(UINT32 dwTeamID);
    inline BOOL DelTeam(CTeamInGS* poTeam);
    inline CTeamInGS* FindTeam(UINT32 dwTeamID);

    inline BTCustomCtx* NewBTCtx(void);
    inline BOOL DelBTCtx(BTCustomCtx* pCtx);

    inline COMBAT_STAT_NODE* NewSceneCombatStatNode(void);
    inline BOOL DelSceneCombatStatNode(COMBAT_STAT_NODE* pNode);

    inline Item* NewItem(UINT64 guid);
    inline BOOL DelItem(Item* pItem);
    inline Item* FindItem(UINT64 guid);

	inline ItemSpellLevelNode* NewItemSpellLevelNode(void);
	inline BOOL DelItemSpellLevelNode(ItemSpellLevelNode* pNode);

	inline ItemSpellRuneNode* NewItemSpellRuneNode(void);
	inline BOOL DelItemSpellRuneNode(ItemSpellRuneNode* pNode);

    inline stSignal* NewSignal();
    inline BOOL DelSignal(stSignal* pSignal);

	inline TeamAuctionItem* NewTeamAuctionItem(void);
	inline BOOL DelTeamAutionItem(TeamAuctionItem* poAuctionItem);

    BOOL JumpTo(CRole* poRole, INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, INT32 nFaceDirection);
    BOOL JumpTo(CNpc* poNpc, INT32 nSceneTempID, INT32 nSceneID, INT32 nX, INT32 nY, INT32 nZ, INT32 nFaceDirection);
    BOOL JumpToRole(CRole* poRole, const char* pcszRoleName);
    BOOL TakeRole(CRole* poRole, const char* pcszRoleName);

    inline const CHAR* GetConfigPath();
    UINT32 GenerateID(INT32 eType);
    const char* GetString( UINT32 dwID );

    BOOL AddToSaveList(CRole* poRole);
    BOOL PushToSaveListRear(CRole* poRole);

    BOOL CheckCensoredWord(const char* pcszText);
	BOOL ReplaceCensoredWord(char* pszText);

    INT64 PrintMemoryStat(void);
	void PrintNpcPool(void);
	void PrintRolePool(void);
	void PrintScenePool(BOOL bDetail = FALSE);

    void ToggleGlobalDropMax();
    void SetGlobalDropRate(INT32 nDropRate);
    INT32 GetGlobalDropRate();
    void SetGlobalExpRate(INT32 nExpRate);
    INT32 GetGlobalExpRate();

	INT32 SendItemToRole(UINT32 dwRoleID, INT32 nMailTemplateID, Item* pItem, EItemLog reason);
	INT32 SendMoneyToRole(UINT32 dwRoleID, INT32 nMailTemplateID, INT32 nMoneyType, UINT32 dwMoneyCount, EMoneyLog reason);

	BOOL SendItemMail(UINT32 dwRoleID, INT32 nMailTemplateID, Item* pItem, EItemLog reason);
	BOOL SendItemMail(UINT32 dwRoleID, INT32 nMailTemplateID, Item* pItem, EItemLog reason, INT32 nMoneyCost);
	BOOL SendMoneyMail(UINT32 dwRoleID, INT32 nMailTemplateID, INT32 nMoneyType, UINT32 dwMoneyCount, EMoneyLog reason);

	INT32 GetServerVariable(INT32 nServerGroup, UINT64 qwKey);
	void SetServerVariable(INT32 nServerGroup, UINT64 qwKey, BOOL bAbsoluteValue, INT32 nVarValue);
	void _SetServerVariable(INT32 nServerGroup, UINT64 qwKey, INT32 nVarValue);

	inline INT32 GetAverageLevel(INT32 nServerGroup);
	inline void SetAverageLevel(INT32 nServerGroup, INT32 nAverageLevel);

    typedef std::map<INT32, INT32> MS_BM_LIMIT_MAP;
    inline const MS_BM_LIMIT_MAP& GetMSBMLimitMap() const { return m_msBlackMarketLimitMap; }
    inline BOOL NeedUpdateMSBMLimitMap() const{ return m_qwCurrentTick - m_qwMsBlackeMarketLimitMapUpdateTime > 2000; };
    void UpdateMSBMLimitMap(INT32 nBlackMarketProductID, INT32 nCount) { m_msBlackMarketLimitMap[nBlackMarketProductID] = nCount; };
    void UpdateMSBMTime() { m_qwMsBlackeMarketLimitMapUpdateTime = m_qwCurrentTick; }


#ifndef _ROBOT
	inline SGPK::IGPKSvrDynCode* GetGPK(void);
#endif

private:
    BOOL _InitPool(void);
    BOOL _UnInitPool(void);

    BOOL _SaveRoleData(void);

    void _On1SecMainLoop(void);

    struct CTraverseRole
    {
        BOOL operator()(UINT32 dwRoleID, CRole* poRole);
    };

	struct CTraverseTeam
	{
		BOOL operator()(UINT32 dwTeamID, CTeamInGS* poTeam);
	};

    struct CTraverseScene
    {
        BOOL operator()(UINT64 qwSceneID, CScene* poScene);
    };

    struct CDeleteAllScene
    {
        BOOL operator()(UINT64 qwSceneID, CScene* poScene);
    };

private:
    UINT32                              m_dwGSSessionID;
	INT64	                            m_llGameFrame;
    UINT64                              m_qwStartTick;
	UINT64	                            m_qwCurrentTick;
    UINT32                              m_dwStartTime;
	UINT32	                            m_dwCurrentTime;
    INT32                               m_nTimeZone;
    tm_ex                               m_LocalTime;
	BOOL								m_bProgrammer;
	BOOL								m_bIsCheck;
	BOOL								m_bIsInLixjList;

	BOOL								m_bFreezeTime;
	BOOL								m_bCanCast;
	BOOL								m_bDrawDebugLine;
	BOOL								m_bCheckConsume;

    static CGameWorld                   ms_Instance;
    CBaseList                           m_lstSaveRole;

	CIDObjectPool<CScene, UINT64>	    m_ScenePool;
	CIDObjectPool<CRole, UINT32>		m_RolePool;
	CIDObjectPool<CNpc, UINT32>			m_NpcPool;
	CIDObjectPool<CDoodad, UINT32>		m_DoodadPool;
	CIDObjectPool<CMissile, UINT32>		m_MissilePool;
	CIDObjectPool<CHero, UINT32>		m_HeroPool;
    CIDObjectPool<CDrop, UINT32>        m_DropPool;
    CIDObjectPool<CTeamInGS, UINT32>    m_TeamPool;

	CObjectPool<CRegion>		        m_RegionPool;
	CObjectPool<THREAT_NODE>	        m_ThreatNodePool;
	CObjectPool<TARGET_NODE>	        m_TargetNodePool;
	CObjectPool<PLACED_GRID>	        m_PlacedGridPool;
	CObjectPool<CSpellCopy>		        m_SpellCopyPool;
	CObjectPool<CSpellSet>		        m_SpellSetPool;
	CObjectPool<CSpellInstance>         m_SpellInstancePool;
	CObjectPool<NextSpell>		        m_NextSpellPool;
	CObjectPool<CAuraInstance>	        m_AuraInstancePool;
	CObjectPool<CBullet>		        m_BulletPool;
    CObjectPool<BTNod>			        m_BTNodPool;
    CObjectPool<BTCustomCtx>            m_BTCtxPool;
    CObjectPool<stSignal>               m_SignalPool;
    CObjectPool<CAIProcessor>	        m_AIProcessorPool;
    CObjectPool<COMBAT_STAT_NODE>       m_SceneCombatStatNodePool;
    CIDObjectPool<Item, UINT64>         m_ItemPool;
	CObjectPool<ItemSpellLevelNode>	    m_ItemSpellLevelNodePool;
	CObjectPool<ItemSpellRuneNode>	    m_ItemSpellRuneNodePool;
	CObjectPool<TeamAuctionItem>			m_TeamAuctionItemPool;

    CHAR                                m_szConfigPath[PATH_LEN];
    UINT32                              m_dwIndexGenerator[otTotal];
	BOOL						        m_bCooldownAvailable;
    UINT8                               m_byRelationTable[rpmTotal][gptTotal][gptTotal][2][2][3][2];

	UINT32								m_dwBattleTeamIDGenerate;

    TRIE_NODE*                          m_pTrieRoot;

	typedef std::map<UINT64, INT32>		SERVER_VAR_MAP;
	SERVER_VAR_MAP						m_ServerVarList[MAX_SERVER_GROUP_COUNT];
	INT32								m_nAverageLevel[MAX_SERVER_GROUP_COUNT];

    MS_BM_LIMIT_MAP                     m_msBlackMarketLimitMap;
    UINT64                              m_qwMsBlackeMarketLimitMapUpdateTime;

#ifndef _ROBOT
	SGPK::IGPKSvrDynCode*						m_poGPK;
#endif

#ifdef _ROBOT
public:
    inline UINT32 GetTeamCount();
    template<class TFunc>
    inline BOOL TraverseTeam(TFunc& rFunc);
#endif

};

BOOL g_InitGameWorldLib(UINT64 qwStartTime, void* poMessageNotifier, IPacketAllocator* poPacketAllocator);
BOOL g_UnInitGameWorldLib(void);

extern void GSSysLogSuccess(CRole* poRole, const char* szFucntionName);
extern void GSSysLogError(CRole* poRole, const char* szFucntionName);

#define GS_SYS_LOG_SUCCESS(poRole) GSSysLogSuccess(poRole, __FUNCTION__)
#define GS_SYS_LOG_ERROR(poRole) GSSysLogError(poRole, __FUNCTION__)

#include "game_world_inl.h"

#endif	// _GAME_WORLD_H_
