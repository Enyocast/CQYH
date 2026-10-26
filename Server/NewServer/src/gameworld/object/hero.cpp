#include "stdafx.h"
#include "hero.h"
#include "id_def.h"
#include "hero_attr_data.h"
#include "attr_conversion_data.h"
#include "role.h"
#include "scene.h"
#include "region.h"
#include "message_handler.h"
#include "level_data.h"
#include "spell_def.h"
#include "game_world.h"
#include "ai_processor.h"
#include "script_mgr.h"

#define MAX_FIND_TIMER	(2 * REGION_WIDTH / GRID_WIDTH)

CHero::CHero(void)
{
	m_nGrowth = 0;
	m_nExp = 0;
	m_bIsNameChanged = FALSE;
	m_szName[0] = 0;
	m_nAiType = hatInvalid;
	m_bIsSummoned = FALSE;
}

CHero::~CHero(void)
{

}

BOOL CHero::Init(CRole* poOwner, UINT32 dwHeroID, UINT32 dwExp, INT32 nSex, const HERO_ATTR_DATA* pHeroData)
{
	INT32 nRetCode = 0;
	INT32 nMoveSpeed = 0;

	LOG_PROCESS_ERROR(pHeroData);
	LOG_PROCESS_ERROR(nSex > cstInvalid && nSex < cstTotal);

	nRetCode = CCharacter::Init(dwHeroID);
	LOG_PROCESS_ERROR(pHeroData);

	m_dwHostID = poOwner->GetObjID();

	SetClass(pHeroData->m_nClass);
	m_nExp = dwExp;
	m_nSex = nSex;
	m_nLevel = 0;

	nRetCode = _ComputeAttribute(pHeroData->m_nLevel);
	LOG_PROCESS_ERROR(nRetCode);

	m_nLevel = pHeroData->m_nLevel;

	m_nCurrentHp = m_AttrList.GetAttr(catMaxHp);
	m_nCurrentMp = m_AttrList.GetAttr(catMaxMp);

	m_nGrowth = 0;
	m_bIsNameChanged = FALSE;
	m_nAiType = hatFollow;
	m_bIsSummoned = FALSE;

	strxcpy(m_szName, g_GWConfig.HeroDefaultName[m_nClass].Sex[m_nSex].szName, ROLE_NAME_LEN);

	return TRUE;
Exit0:
	UnInit();
	return FALSE;
}

BOOL CHero::UnInit(void)
{
	CCharacter::UnInit();

	m_SpellBook.UnInit();

	return TRUE;
}

INT32 CHero::GetObjType(void)
{
	return otHero;
}

const TCHAR* CHero::GetName(void)
{
	return m_szName;
}

INT32 CHero::GetSpecies(void)
{
	return spcHuman; 
}

ISpellBook& CHero::GetSpellBook(void)
{
	return m_SpellBook;
}

BOOL CHero::_ChangeRegion(CRegion* poDestRegion)
{
	INT32	nRetCode = 0;
	INT32	nDirection = 0;
	INT32	nOldDirection = 0;

	LOG_PROCESS_ERROR(poDestRegion);
	LOG_PROCESS_ERROR(m_poRegion);

	nDirection = g_GetDirection(m_poRegion->GetRegionX(), m_poRegion->GetRegionY(),
		poDestRegion->GetRegionX(), poDestRegion->GetRegionY()) * DT_DIRECTION_8_COUNT / MAX_DIRECTION_COUNT;

	for (INT32 nIndex = 1; nIndex <= g_nAdjList[nDirection][0]; nIndex++)
	{
		CRegion* poOldRegion;
		CRegion* poNewRegion;

		poNewRegion = poDestRegion->GetConnectedRegion(g_nAdjList[nDirection][nIndex]);

		nOldDirection = (g_nAdjList[nDirection][nIndex] + DT_DIRECTION_8_COUNT / 2) % DT_DIRECTION_8_COUNT;
		poOldRegion = m_poRegion->GetConnectedRegion(nOldDirection);

#ifndef _ROBOT
		if(poNewRegion)
		{
			nRetCode = CCliMessageHandler::GetInstance().DoCharAppear(this, poNewRegion, soatInRange);
			LOG_CHECK_ERROR(nRetCode);
		}

		if(poOldRegion)
		{
			nRetCode = CCliMessageHandler::GetInstance().DoObjectDisappear(this, poOldRegion, sodtOutOfRange);
			LOG_CHECK_ERROR(nRetCode);
		}
#endif  // _ROBOT
	}

	nRetCode = m_poRegion->RemoveHero(this);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = poDestRegion->AddHero(this);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CHero::MainLoop(void)
{
	INT32 nRetCode = 0;

	nRetCode = CSceneObject::CheckLoop();
	PROCESS_SUCCESS(!nRetCode);

	nRetCode = CCharacter::MainLoop();
	LOG_PROCESS_ERROR(nRetCode);

	if(!IsDead())
	{
		if (m_poAIProcessor)
		{
			nRetCode = m_poAIProcessor->MainLoop();
			LOG_PROCESS_ERROR(nRetCode);
		}
	}


Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

void CHero::AddExp(UINT32 nExp)
{
	INT32 nRetCode = 0;
	const HERO_LEVEL_DATA* poLevel = NULL;
	const HERO_LEVEL_DATA* poNextLevel = NULL;
	BOOL bLevelUp = FALSE;
	INT32 nLevel = m_nLevel;

	CRole* poOwner = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
	LOG_PROCESS_ERROR(poOwner);

	PROCESS_ERROR(!IsDead());

	m_nExp += nExp;

	if(m_nExp < 0)
		m_nExp = INT_MAX;

	poLevel = CDataManager<HERO_LEVEL_DATA>::GetInstance().GetData(nLevel);
	LOG_PROCESS_ERROR(poLevel);

	while(m_nExp >= poLevel->m_nMaxExp && nLevel < poOwner->GetLevel())
	{
		if (poLevel->m_nMaxExp == 0)
		{
			m_nExp = 0;
			break;
		}

		poNextLevel = CDataManager<HERO_LEVEL_DATA>::GetInstance().GetData(nLevel + 1);
		if (poNextLevel)
		{
			m_nExp -= poLevel->m_nMaxExp;
			nLevel++;
			poLevel = poNextLevel;
			bLevelUp = TRUE;
		}
		else
		{
			m_nExp = 0;
			break;
		}
	}

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoHeroExpChange(poOwner, nExp, poLevel->m_nMaxExp);
	LOG_CHECK_ERROR(nRetCode);
#endif  // _ROBOT

	if(bLevelUp)
		SetLevel(poLevel->m_nLevel);

Exit0:
	return;
}

void CHero::SubExp(UINT32 nExp)
{
	INT32 nRetCode = 0;

	CRole* poOwner = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
	LOG_PROCESS_ERROR(poOwner);

	LOG_PROCESS_ERROR(m_nExp >= nExp);

	m_nExp -= nExp;

#ifndef _ROBOT
	{
		const HERO_LEVEL_DATA* poLevel = CDataManager<HERO_LEVEL_DATA>::GetInstance().GetData(GetLevel());
		LOG_PROCESS_ERROR(poLevel);
	
		nRetCode = CCliMessageHandler::GetInstance().DoHeroExpChange(poOwner, -(INT32)(nExp), poLevel->m_nMaxExp);
		LOG_CHECK_ERROR(nRetCode);

	}

#endif  // _ROBOT

Exit0:
	return;
}

BOOL CHero::SetLevel(INT32 nNewLevel)
{
	CRole* poHostRole = NULL;
	INT32 nRetCode = 0;
	CLuaScript* poScript = NULL;

	INT32 nOldLevel = m_nLevel;
	PROCESS_SUCCESS(m_nLevel == nNewLevel);

	nRetCode = CCharacter::SetLevel(nNewLevel);
	LOG_PROCESS_ERROR(nRetCode);

	poHostRole = GetHostRole();
	LOG_PROCESS_ERROR(poHostRole);

	LOG_PROCESS_ERROR(nNewLevel <= poHostRole->GetLevel());

	_ComputeAttribute(nNewLevel);

	poScript = CScriptMgr::GetInstance().FindScript(HERO_LEVEL_SCRIPT_NAME);
	LOG_PROCESS_ERROR(poScript);

	m_nLevel = nNewLevel;

	nRetCode = poScript->CallFunction("main", "odd", this, "CHero", nOldLevel, nNewLevel);
	LOG_PROCESS_ERROR(nRetCode);


#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoHeroLevelUp(poHostRole);
	LOG_CHECK_ERROR(nRetCode);
#endif

Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CHero::Die(INT32 nParam)
{
	INT32 nMaxExp = 0;
	INT32 nSubExp = 0;
	CRole* poOwner = NULL;
	INT32 nCoolDownFrm = 0;

	INT32 nRetCode = CCharacter::Die(nParam);
	LOG_PROCESS_ERROR(nRetCode);

	poOwner = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
	LOG_PROCESS_ERROR(poOwner);

	poOwner->GetItemBag()->LoseHeroAllDur(5, ITEMLOG_DEATH);

	nMaxExp = GetMaxExp(otHero, m_nLevel);
	LOG_PROCESS_ERROR(nMaxExp >= 0);

	nSubExp = nMaxExp * g_GWConfig.nHeroExpSubRate / RATE_MAX;

	if(nSubExp > m_nExp)
		nSubExp = m_nExp;

	SubExp(nSubExp);

	nCoolDownFrm = CONVERT_TIME(m_nLevel * 10 * 1000);

	poOwner->AddCooldown(MakeCoolDownID(COOLDOWN_MISC, COOLDOWN_MISC_HERO_REVIVE), nCoolDownFrm);

Exit0:
	return FALSE;
}

INT32 CHero::CastSpell(CSpell* poSpell, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ)
{
	INT32 nResult = CCharacter::CastSpell(poSpell, poTarget, nTargetX, nTargetY, nTargetZ);
	PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

Exit0:
	return nResult;

}

BOOL CHero::SetAiType(INT32 nAiType)
{
	CRole* poOwner = NULL;
	INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(nAiType > hatInvalid && nAiType < hatTotal);

	nRetCode = SetAIProcessor(g_GWConfig.HeroAiId[m_nClass].AiId[nAiType]);
	LOG_PROCESS_ERROR(nRetCode);

	m_nOriginAiID = g_GWConfig.HeroAiId[m_nClass].AiId[nAiType];

	m_nAiType = nAiType;

	poOwner = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
	if(poOwner != NULL)
	{
#ifndef _ROBOT
		nRetCode = CCliMessageHandler::GetInstance().DoChangeHeroAi(poOwner, nAiType);
		LOG_PROCESS_ERROR(nRetCode);
#endif 
	}
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CHero::ChangeName(TCHAR* szNewName)
{
	PROCESS_ERROR(!m_bIsNameChanged);

	strxcpy(m_szName, szNewName, sizeof(m_szName));

	m_bIsNameChanged = TRUE;

	return TRUE;
Exit0:
	return FALSE;
}

CRole* CHero::GetHostRole(void)
{
	CRole* poRole = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
	PROCESS_ERROR(poRole);

	return poRole;
Exit0:
	return NULL;
}

BOOL CHero::ReachMaxExp()
{
    CRole* poOwner = CGameWorld::GetInstance().FindValidRole(m_dwHostID);
    const HERO_LEVEL_DATA* poLevel = CDataManager<HERO_LEVEL_DATA>::GetInstance().GetData(m_nLevel);

    LOG_PROCESS_ERROR(poOwner);
    LOG_PROCESS_ERROR(poLevel);

    return m_nLevel >= poOwner->GetLevel() && m_nExp >= poOwner->GetExp();

Exit0:
    return FALSE;
}

void CHero::SetFaction(INT32 nFaction)
{
    m_nFaction = nFaction;
}


BOOL CHero::_ComputeAttribute(INT32 nNewLevel)
{
    const HERO_ATTR_DATA* pNewAttr = NULL;
    const HERO_ATTR_DATA* pOldAttr = NULL;

	pNewAttr = CDataManager<HERO_ATTR_DATA>::GetInstance().GetData(MakeHeroAttrKey(nNewLevel, GetClass()));
	LOG_PROCESS_ERROR(pNewAttr);

	pOldAttr = CDataManager<HERO_ATTR_DATA>::GetInstance().GetData(MakeHeroAttrKey(m_nLevel, GetClass()));
	LOG_PROCESS_ERROR(pOldAttr);

	for(INT32 i = catDefault; i < catTotal; i++)
	{
		m_AttrList.AddAttrBase(this, i, pNewAttr->m_nMainAttr[i] - pOldAttr->m_nMainAttr[i]);
	}

//	for(INT32 i = catBeginExAttr; i < catEndExAttr; i++)
//	{
//		const ATTR_CONV* pConvData = CDataManager<ATTR_CONV>::GetInstance().GetData(MakeAttrKey(i, m_nClass));
//		if(pConvData == NULL)
//			continue;
//
//		if(!pConvData->m_bAffectedByMainAttr)
//			m_AttrList.SetAttrBase(this, i, pConvData->m_nConstParam);
//	}

	return TRUE;
Exit0:
	return FALSE;

}

BOOL CHero::DoSyncAttrChange(INT32 eAttrType)
{
	INT32 nRetCode = 0;

	CRole* poHostRole = GetHostRole();
	PROCESS_ERROR(poHostRole);

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoHeroAttrChange(poHostRole, eAttrType);
	LOG_CHECK_ERROR(nRetCode);
#endif

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CHero::JumpTo(INT64 llX, INT64 llY, INT64 llZ, INT32 nFaceDirection)
{
	INT32 nRetCode = 0;
	INT64 llSrcX = 0, llSrcY = 0, llSrcZ = 0;
	INT32 nSrcFaceDirection = 0;
	CScene* poSrcScene = NULL;

	LOG_PROCESS_ERROR(m_poScene);

	llSrcX = m_llX;
	llSrcY = m_llY;
	llSrcZ = m_llZ;
	nSrcFaceDirection = GetFaceDirection();
	poSrcScene = m_poScene;

	nRetCode = m_poScene->RemoveHero(this);
	LOG_PROCESS_ERROR(nRetCode);

	SetX(llX);
	SetY(llY);
	SetZ(llZ);
	SetFaceDirection(nFaceDirection);

	nRetCode = poSrcScene->AddHero(this, soatInRange);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if(m_poScene == NULL && poSrcScene != NULL)
	{
		SetX(llSrcX);
		SetY(llSrcY);
		SetZ(llSrcZ);
		SetFaceDirection(nSrcFaceDirection);

		nRetCode = poSrcScene->AddHero(this, soatInRange);
		LOG_CHECK_ERROR(nRetCode);
	}

	return FALSE;

}

BOOL CHero::_GridMove(INT64 llDestX, INT64 llDestY)
{
	INT32 nRetCode = 0;
	INT32 nDestRegionX;
	INT32 nDestRegionY;
	CRegion* poDestRegion = NULL;
	const ZONE_DATA* pcDestZone = NULL;
	const GRID_DATA* pcDestGrid = NULL;
	GRID_INSTANCE_DATA* pGridInstance = NULL;

	GRID_INSTANCE_DATA* pOldGridInstance = NULL;
	INT64 llOldX = m_llX, llOldY = m_llY;

	LOG_PROCESS_ERROR(m_poScene);
	LOG_PROCESS_ERROR(m_eMoveState != CMS_DIE);

	nRetCode = m_poScene->GetLowerGrid(llDestX, llDestY, m_llZ + GRID_WIDTH, pcDestZone, pcDestGrid);
	PROCESS_ERROR(nRetCode);
	PROCESS_ERROR(!pcDestGrid->bOutOfPoly);

	if (pcDestGrid == m_pcGrid)
	{
		m_llX = llDestX;
		m_llY = llDestY;
	}
	else
	{
#ifndef _ROBOT
		if (pcDestGrid->uDoor > 0)
			PROCESS_ERROR(!m_poScene->IsDoorClosed(pcDestZone->byDoor[pcDestGrid->uDoor]));
#endif	// _ROBOT

		pGridInstance = m_poScene->GetGridInstance(pcDestZone, pcDestGrid);
		LOG_PROCESS_ERROR(pGridInstance);

		switch (m_nBodyType)
		{
		case body0x0:
			break;
		case body1x1:
			PROCESS_ERROR(pGridInstance->uCharRef < MAX_CHAR_PER_GRID);
			if (!pcDestGrid->bNotBlockChar)
				PROCESS_ERROR(pGridInstance->uCharRef == 0);
			break;
		case body3x3:
			nRetCode = CheckAdjGridCharRef(llDestX, llDestY, m_llZ);
			PROCESS_ERROR(nRetCode);
			break;
		}

		PROCESS_ERROR(pGridInstance->uMissileTag1 == 0);

		nDestRegionX = (INT32)(llDestX / REGION_WIDTH);
		nDestRegionY = (INT32)(llDestY / REGION_WIDTH);

		poDestRegion = m_poScene->GetRegion(nDestRegionX, nDestRegionY);
		LOG_PROCESS_ERROR(poDestRegion);

		nRetCode = ClearGridCharRef();
		LOG_CHECK_ERROR(nRetCode);

		m_llX = llDestX;
		m_llY = llDestY;
		m_llZ = pcDestGrid->uHighLayer * GRID_LAYER_HEIGHT;

		m_pcGrid = pcDestGrid;
		m_pcZone = pcDestZone;

		pOldGridInstance = m_pGridInstance;
		m_pGridInstance = pGridInstance;

		nRetCode = SetGridCharRef();
		LOG_CHECK_ERROR(nRetCode);

		if (poDestRegion != m_poRegion)
		{
			nRetCode = _ChangeRegion(poDestRegion);
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

	return TRUE;
Exit0:
	return FALSE;


}

