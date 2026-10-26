#ifndef _GAME_WORLD_INL_H_
#define _GAME_WORLD_INL_H_

inline void CGameWorld::SetGsSessionID(UINT32 dwGsSessionID)
{
    m_dwGSSessionID = dwGsSessionID;
}

inline UINT32 CGameWorld::GetGsSessionID(void)
{
    return m_dwGSSessionID;
}

inline INT64 CGameWorld::GetGameFrame(void)
{
	return m_llGameFrame;
}

inline void CGameWorld::SetGameFrame(INT64 llGameFrame)
{
	m_llGameFrame = llGameFrame;
}

inline void CGameWorld::SetStartTime(UINT32 dwTime)
{
	m_dwStartTime = dwTime;
}

inline UINT32 CGameWorld::GetStartTime(void)
{
	return m_dwStartTime;
}

inline void CGameWorld::SetGameTick(UINT64 qwTick)
{
	m_qwCurrentTick = qwTick;
}

inline void CGameWorld::SetStartTick(UINT64 qwTick)
{
	m_qwStartTick = qwTick;
}

inline UINT64 CGameWorld::GetStartTick(void)
{
	return m_qwStartTick;
}

inline UINT64 CGameWorld::GetGameTick(void)
{
	return m_qwCurrentTick;
}

inline void CGameWorld::SetGameTime(UINT32 dwGameTime)
{
	m_dwCurrentTime = dwGameTime;
}

inline UINT32 CGameWorld::GetGameTime(void)
{
	return m_dwCurrentTime;
}

inline INT32 CGameWorld::GetTimeZone(void)
{
    return m_nTimeZone;
}

inline const tm_ex& CGameWorld::GetLocalTime(void)
{
    return m_LocalTime;
}

inline void CGameWorld::SetFreezeTime(BOOL bFreezeTime)
{
	m_bFreezeTime = bFreezeTime;
}

inline BOOL CGameWorld::IsFreezeTime(void)
{
	return m_bFreezeTime;
}

inline CScene* CGameWorld::NewScene(UINT64 qwSceneID)
{
	return m_ScenePool.New(qwSceneID);
}

inline BOOL CGameWorld::DelScene(CScene* poScene)
{
	return m_ScenePool.Delete(poScene);
}

inline CScene* CGameWorld::FindScene(UINT64 qwSceneID)
{
	return m_ScenePool.Find(qwSceneID);
}

template<class TFunc>
inline BOOL CGameWorld::TraverseScene(TFunc& rFunc)
{
    return m_ScenePool.Traverse(rFunc);
}

inline CRegion* CGameWorld::NewRegion(void)
{
	return m_RegionPool.New();
}

inline BOOL CGameWorld::DelRegion(CRegion* poRegion)
{
	return m_RegionPool.Delete(poRegion);
}

inline CRole* CGameWorld::NewRole(UINT32 dwRoleID)
{
	return m_RolePool.New(dwRoleID);
}

inline BOOL CGameWorld::DelRole(CRole* poRole)
{
	return m_RolePool.Delete(poRole);
}

inline CRole* CGameWorld::FindRole(UINT32 dwRoleID)
{
	return m_RolePool.Find(dwRoleID);
}

inline CRole* CGameWorld::FindValidRole(UINT32 dwRoleID)
{
	CRole* poRole = FindRole(dwRoleID);
	PROCESS_ERROR(poRole);
	PROCESS_ERROR(poRole->GetScene());

	return poRole;
Exit0:
	return NULL;
}

inline INT32 CGameWorld::GetRoleCount(void)
{
	return m_RolePool.GetSize() - m_RolePool.GetFreeSize();
}

template<class TFunc>
inline BOOL CGameWorld::TraverseRole(TFunc& rFunc)
{
	return m_RolePool.Traverse(rFunc);
}

inline CNpc* CGameWorld::NewNpc(UINT32 dwNpcID)
{
	if (dwNpcID == 0)
		return m_NpcPool.New(GenerateID(otNpc));
	else
		return m_NpcPool.New(dwNpcID);
}

inline BOOL CGameWorld::DelNpc(CNpc* poNpc)
{
	return m_NpcPool.Delete(poNpc);
}

inline CAIProcessor* CGameWorld::NewAIProcessor(void)
{
    return m_AIProcessorPool.New();
}

inline BOOL CGameWorld::DelAIProcessor(CAIProcessor* poAIProcessor)
{
    return m_AIProcessorPool.Delete(poAIProcessor);
}

inline CNpc* CGameWorld::FindNpc(UINT32 dwNpcID)
{
	return m_NpcPool.Find(dwNpcID);
}

inline UINT32 CGameWorld::GetNpcID(CNpc* poNpc)
{
	return m_NpcPool.GetObjID(poNpc);
}

template<class TFunc>
inline BOOL CGameWorld::TraverseNpc(TFunc& rFunc)
{
	return m_NpcPool.Traverse(rFunc);
}

inline CDoodad* CGameWorld::NewDoodad(void)
{
	return m_DoodadPool.New(GenerateID(otDoodad));
}

inline BOOL CGameWorld::DelDoodad(CDoodad* poDoodad)
{
	return m_DoodadPool.Delete(poDoodad);
}

inline CDoodad* CGameWorld::FindDoodad(UINT32 dwDoodadID)
{
	return m_DoodadPool.Find(dwDoodadID);
}

inline UINT32 CGameWorld::GetDoodadID(CDoodad* poDoodad)
{
	return m_DoodadPool.GetObjID(poDoodad);
}

inline CMissile* CGameWorld::NewMissile(void)
{
	return m_MissilePool.New(GenerateID(otMissile));
}

inline BOOL CGameWorld::DelMissile(CMissile* poMissile)
{
	return m_MissilePool.Delete(poMissile);
}

inline CMissile* CGameWorld::FindMissile(UINT32 dwMissileID)
{
	return m_MissilePool.Find(dwMissileID);
}

inline UINT32 CGameWorld::GetMissileID(CMissile* poMissile)
{
	return m_MissilePool.GetObjID(poMissile);
}

inline CHero* CGameWorld::NewHero(UINT32 dwHeroID)
{
	LOG_PROCESS_ERROR(dwHeroID != 0);

	return m_HeroPool.New(dwHeroID);
Exit0:
	return NULL;
}

inline BOOL CGameWorld::DelHero(CHero* poHero)
{
	return m_HeroPool.Delete(poHero);
}

inline CHero* CGameWorld::FindHero(UINT32 dwHeroID)
{
	return m_HeroPool.Find(dwHeroID);
}

inline UINT32 CGameWorld::GetHeroID(CHero* poHero)
{
	return m_HeroPool.GetObjID(poHero);
}

inline CSceneObject* CGameWorld::FindObj(UINT32 dwObjID)
{
	INT32 nIdType = GetTypeFromID(dwObjID);

	switch(nIdType)
	{
	case otRole:
		return m_RolePool.Find(dwObjID);
		break;
	case otNpc:
		return m_NpcPool.Find(dwObjID);
		break;
	case otDoodad:
		return m_DoodadPool.Find(dwObjID);
		break;
	case otMissile:
		return m_MissilePool.Find(dwObjID);
		break;
	case otDrop:
		return m_DropPool.Find(dwObjID);
		break;
	case otHero:
		return m_HeroPool.Find(dwObjID);
	default:
		break;
	}

	return NULL;
}

inline CCharacter* CGameWorld::FindCharacter(UINT32 dwCharID)
{
    CCharacter* pResult = NULL;

    switch (GetTypeFromID(dwCharID))
    {
    case otRole:
        pResult = m_RolePool.Find(dwCharID);
        break;
    case otNpc:
        pResult = m_NpcPool.Find(dwCharID);
        break;
    case otHero:
        pResult =m_HeroPool.Find(dwCharID);
        break;
    default:
#ifndef _ROBOT
		LOG_PROCESS_ERROR(FALSE);
#else
		PROCESS_ERROR(FALSE);
#endif
    }

    return pResult;
Exit0:
    return NULL;
}

inline CCharacter* CGameWorld::FindValidCharacter(UINT32 dwCharID)
{
    CCharacter* pResult = NULL;

	switch (GetTypeFromID(dwCharID))
    {
    case otRole:
        pResult = m_RolePool.Find(dwCharID);
        break;
    case otNpc:
        pResult = m_NpcPool.Find(dwCharID);
        break;
    case otHero:
        pResult = m_HeroPool.Find(dwCharID);
        break;
    default:
		break;
    }
    PROCESS_ERROR(pResult);
    PROCESS_ERROR(pResult->GetScene());

    return pResult;
Exit0:
	return NULL;
}

inline CSceneObject* CGameWorld::FindValidObj(UINT32 dwObjID)
{
	INT32 nIdType = GetTypeFromID(dwObjID);

	switch(nIdType)
	{
	case otRole:
		return FindValidRole(dwObjID);
		break;
	case otNpc:
		return m_NpcPool.Find(dwObjID);
		break;
	case otDoodad:
		return m_DoodadPool.Find(dwObjID);
		break;
	case otMissile:
		return m_MissilePool.Find(dwObjID);
		break;
	case otDrop:
		return m_DropPool.Find(dwObjID);
		break;
	case otHero:
		return m_HeroPool.Find(dwObjID);
	default:
		break;
	}

	return NULL;
}

inline THREAT_NODE* CGameWorld::NewThreatNode(void)
{
	return m_ThreatNodePool.New();
}

inline BOOL CGameWorld::DelThreatNode(THREAT_NODE* pThreatNode)
{
	return m_ThreatNodePool.Delete(pThreatNode);
}

inline TARGET_NODE* CGameWorld::NewTargetNode(void)
{
	return m_TargetNodePool.New();
}

inline BOOL CGameWorld::DelTargetNode(TARGET_NODE* pNode)
{
	return m_TargetNodePool.Delete(pNode);
}

inline PLACED_GRID* CGameWorld::NewPlacedGrid(void)
{
	return m_PlacedGridPool.New();
}

inline BOOL CGameWorld::DelPlacedGrid(PLACED_GRID* pNode)
{
	return m_PlacedGridPool.Delete(pNode);
}

inline CSpellCopy* CGameWorld::NewSpellCopy(void)
{
	return m_SpellCopyPool.New();
}

inline BOOL CGameWorld::DelSpellCopy(CSpellCopy* pSpellCopy)
{
	return m_SpellCopyPool.Delete(pSpellCopy);
}

inline CSpellSet* CGameWorld::NewSpellSet(void)
{
	return m_SpellSetPool.New();
}

inline BOOL CGameWorld::DelSpellSet(CSpellSet* pSpellSet)
{
	return m_SpellSetPool.Delete(pSpellSet);
}

inline CSpellInstance* CGameWorld::NewSpellInstance(void)
{
	return m_SpellInstancePool.New();
}

inline BOOL CGameWorld::DelSpellInstance(CSpellInstance* pSpellInstance)
{
	return m_SpellInstancePool.Delete(pSpellInstance);
}

inline NextSpell* CGameWorld::NewNextSpell(void)
{
	return m_NextSpellPool.New();
}

BOOL CGameWorld::DelNextSpell(NextSpell* sp)
{
	return m_NextSpellPool.Delete(sp);
}

inline CBullet* CGameWorld::NewBullet(void)
{
	return m_BulletPool.New();
}

inline BOOL CGameWorld::DelBullet(CBullet* poBullet)
{
	return m_BulletPool.Delete(poBullet);
}

inline ItemSpellLevelNode* CGameWorld::NewItemSpellLevelNode(void)
{
	return m_ItemSpellLevelNodePool.New();
}

inline BOOL CGameWorld::DelItemSpellLevelNode(ItemSpellLevelNode* pNode)
{
	return m_ItemSpellLevelNodePool.Delete(pNode);
}

ItemSpellRuneNode* CGameWorld::NewItemSpellRuneNode(void)
{
	return m_ItemSpellRuneNodePool.New();
}

BOOL CGameWorld::DelItemSpellRuneNode(ItemSpellRuneNode* pNode)
{
	return m_ItemSpellRuneNodePool.Delete(pNode);
}


inline BTNod* CGameWorld::NewBTNod(void)
{
	return m_BTNodPool.New();
}

inline BOOL CGameWorld::DelBTNod( BTNod* poNod )
{
	return m_BTNodPool.Delete( poNod );
}

inline CDrop* CGameWorld::NewDrop(UINT32 dwDropID)
{
	return m_DropPool.New(GenerateID(otDrop));
}

inline BOOL CGameWorld::DelDrop(CDrop* poDrop)
{
	return m_DropPool.Delete(poDrop);
}

inline CDrop* CGameWorld::FindDrop(UINT32 dwDropID)
{
	return m_DropPool.Find(dwDropID);
}

inline UINT32 CGameWorld::GetDropID(CDrop* poDrop)
{
	return m_DropPool.GetObjID(poDrop);
}

inline CAuraInstance* CGameWorld::NewAuraInstance(void)
{
	return m_AuraInstancePool.New();
}

inline BOOL CGameWorld::DelAuraInstance(CAuraInstance* pAuraInstance)
{
	return m_AuraInstancePool.Delete(pAuraInstance);
}

inline CTeamInGS* CGameWorld::NewTeam(UINT32 dwTeamID)
{
    if (dwTeamID == 0)
        return m_TeamPool.New(GenerateID(otBattleTeam));
    else
    	return m_TeamPool.New(dwTeamID);
}

inline BOOL CGameWorld::DelTeam(CTeamInGS* poTeam)
{
	return m_TeamPool.Delete(poTeam);
}

inline CTeamInGS* CGameWorld::FindTeam(UINT32 dwTeamID)
{
	return m_TeamPool.Find(dwTeamID);
}

inline BTCustomCtx* CGameWorld::NewBTCtx(void)
{
	return m_BTCtxPool.New();
}

inline BOOL CGameWorld::DelBTCtx(BTCustomCtx* pCtx)
{
	return m_BTCtxPool.Delete(pCtx);
}

inline COMBAT_STAT_NODE* CGameWorld::NewSceneCombatStatNode(void)
{
	return m_SceneCombatStatNodePool.New();
}

inline BOOL CGameWorld::DelSceneCombatStatNode(COMBAT_STAT_NODE* pNode)
{
	return m_SceneCombatStatNodePool.Delete(pNode);
}

inline Item* CGameWorld::NewItem(UINT64 guid)
{
    Item* item = m_ItemPool.New(guid);
    if (item == NULL)
        ERR("NewItem Failed, GUID=%I64u", guid);
    return item;
}

inline BOOL CGameWorld::DelItem(Item* pItem)
{
    return m_ItemPool.Delete(pItem);
}

inline Item* CGameWorld::FindItem(UINT64 guid)
{
    return m_ItemPool.Find(guid);
}

inline stSignal* CGameWorld::NewSignal()
{
    return m_SignalPool.New();
}

inline BOOL CGameWorld::DelSignal(stSignal* pSignal)
{
    return m_SignalPool.Delete(pSignal);
}

inline TeamAuctionItem* CGameWorld::NewTeamAuctionItem(void)
{
	return m_TeamAuctionItemPool.New();
}

inline BOOL CGameWorld::DelTeamAutionItem(TeamAuctionItem* poAuctionItem)
{
	return m_TeamAuctionItemPool.Delete(poAuctionItem);
}


#ifdef _ROBOT
inline UINT32 CGameWorld::GetTeamCount()
{
	return m_TeamPool.GetSize() - m_TeamPool.GetFreeSize();
}

template<class TFunc>
inline BOOL CGameWorld::TraverseTeam(TFunc& rFunc)
{
	return m_TeamPool.Traverse(rFunc);
}
#endif

inline const CHAR* CGameWorld::GetConfigPath()
{
	return m_szConfigPath;
}

inline void CGameWorld::SetCanCast(BOOL bCanCast)
{
	m_bCanCast = bCanCast;
}

inline BOOL CGameWorld::CanCast(void)
{
	return m_bCanCast;
}

inline void CGameWorld::SetDrawDebugLine(BOOL bDraw)
{
	m_bDrawDebugLine = bDraw;
}

inline BOOL CGameWorld::DrawDebugLine(void)
{
	return m_bDrawDebugLine;
}

inline void CGameWorld::SetCheckConsume(BOOL bCheck)
{
	m_bCheckConsume = bCheck;
}

inline BOOL CGameWorld::CheckConsume(void)
{
	return m_bCheckConsume;
}

#ifndef _ROBOT
inline SGPK::IGPKSvrDynCode* CGameWorld::GetGPK(void)
{
	return m_poGPK;
}
#endif

inline INT32 CGameWorld::GetAverageLevel(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	return m_nAverageLevel[nServerGroup];
Exit0:
	return 0;
}

inline void CGameWorld::SetAverageLevel(INT32 nServerGroup, INT32 nAverageLevel)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);
	m_nAverageLevel[nServerGroup] = nAverageLevel;
Exit0:
	return;
}

#endif	// _GAME_WORLD_INL_H_
