// 默认代码
#include "stdafx.h"
#include "role.h"
#include "server_config.h"
#include "level_data.h"
#include "mount_data.h"
#include "refine_data.h"
#include "spirit_data.h"
#include "spell_config.h"
#include "attribute_data.h"
#include "game_world.h"
#include "item_mgr.h"
#include "modifier_tree.h"
#include "message_handler.h"

// 抄代码
//#include "stdafx.h"
//#include "role.h"
//#include "item_bag.h"
//#include "item_mgr.h"
//#include "refine_data.h"
//#include "modifier_tree.h"
//#include "game_world.h"

#include "role_db_def_v_3.h"
using namespace ROLE_DB_DEF_V_3;

// 玩家登录计算属性
BOOL CRole::_Load_v_3(const char* pcData, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	ROLE_DB_DATA* pRoleData = (ROLE_DB_DATA*)pcData;
	UINT32 dwRealDataSize = 0;

	LOG_PROCESS_ERROR(pcData);
	LOG_PROCESS_ERROR(pRoleData->dwVersion == 3);
	LOG_PROCESS_ERROR(pRoleData->BlockTable[rbtBase].dwStartOffset == 0);

	dwRealDataSize = pRoleData->dwLen - sizeof(ROLE_DB_DATA);

	// block table
	for (UINT32 i = 0; i < rbtTotal; i++)
	{
		ROLE_DB_DATA_BLOCK* pBlock = &pRoleData->BlockTable[i];

		const char* pcBlockData = &pRoleData->RoleData[pBlock->dwStartOffset];
		UINT32 dwBlockSize = pBlock->dwBlockSize;
		LOG_PROCESS_ERROR(pBlock->dwStartOffset + pBlock->dwBlockSize <= dwRealDataSize);

		if (pBlock->dwBlockSize == 0)
			continue;

		switch (pBlock->btBlockType)
		{
		case rbtBase:
			nRetCode = _LoadBaseData(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtProcessedMails:
			nRetCode = m_ProMails.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtItem:
			nRetCode = m_ItemBag.Load_v_2(pcBlockData, dwBlockSize);    // V2 新增代码
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtSpell:
			nRetCode = _LoadSpell_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtQuest:
			nRetCode = m_QuestList.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtReputation:
			nRetCode = m_Reputation.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtSpellSlot:
			nRetCode = _LoadSpellSlot_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtStall:
			nRetCode = m_Stall.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtFriend:
			nRetCode = m_Friend.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtVariable:
			nRetCode = _LoadVariable_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtTitle:
			nRetCode = m_Title.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtAchievement:
			nRetCode = m_AchievementList.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtDungeonRecord:
			nRetCode = _LoadDungeonRecord_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtTeleportPlatform:
			nRetCode = _LoadTeleportPlatform_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtActivatedMount:
			nRetCode = _LoadMount_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtSpirit:
			nRetCode = m_Spirit.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtHero:
			nRetCode = _LoadHero_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtShield:
			nRetCode = m_ShieldList.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtMaster:
			nRetCode = m_Master.OnLoadByGS_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtAura:
			nRetCode = _LoadAura_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtGuild:
			nRetCode = m_Guild.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtMisc:
			nRetCode = _LoadMisc_v_3(pcBlockData, dwBlockSize);    // V3 新增代码
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtArena:
			nRetCode = m_Arena.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtPet:
			nRetCode = _LoadPet_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtKillNpcQuest:
			nRetCode = m_KillNpcQuest.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtCoolDown:
			nRetCode = _LoadCoolDown_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtCheckIn:
			nRetCode = _LoadCheckIn_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtBlackMarketLimit:
			nRetCode = m_ItemBag.LoadBlackMarketLimit_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtBlackMarketCooldown:
			nRetCode = m_ItemBag.LoadBlackMarketCooldown_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case rbtGamble:    // 补充
			nRetCode = m_Gamble.Load_v_1(pcBlockData, dwBlockSize);
			LOG_PROCESS_ERROR(nRetCode);
			break;
		default:
			LOG_PROCESS_ERROR(FALSE);
			break;
		}
	}
	
	if (m_dwSaveTime <= 1464588376)
	{
		m_Gamble.Clear();
	}

	return TRUE;
Exit0:
	return FALSE;
}

// ========== 抄的代码 begin ==========

// 找函数 m_pOwner->GetFixRoleCallback()
BOOL CItemBag::Load_v_2(const char* pcData, UINT32 dwSize)
{
	const ROLE_DB_ITEM_DATA* pItemData = (const ROLE_DB_ITEM_DATA*)pcData;
	UINT32 buflen = 0;
	ItemInfo iteminfo;
	Item* item = NULL;

	LOG_PROCESS_ERROR(pcData);
	LOG_PROCESS_ERROR(sizeof(ROLE_DB_ITEM_DATA) + pItemData->dwItemInfoBufLen == dwSize);

	Clear();

	memcpy(m_refine_levels, pItemData->wRefineLevels, sizeof(m_refine_levels));

	for (INT32 i = 0; i < MONEYTYPE_COUNT; i++)
	{
		m_moneys[i] = pItemData->llMoneys[i];
		m_moneys_daily_earned[i] = pItemData->nMoneyDailyEarned[i];
		m_moneys_daily_used[i] = pItemData->nMoneyDailyUsed[i];
		m_moneys_weekly_earned[i] = pItemData->nMoneyWeekleEarned[i];
		m_moneys_weekly_used[i] = pItemData->nMoneyWeekleUsed[i];
	}
	UpdateMoneyLimits();

	m_use_moneytype01_only = pItemData->byUseMoneytype01Only;
	m_gold_pool = pItemData->nGoldPool;

	m_con_sizes[CONSLOT_DEFAULT] = pItemData->byDefaultSlotSize;
	m_con_sizes[CONSLOT_BANK] = pItemData->byBankSlotSize;
	m_con_sizes[CONSLOT_RESOURCE] = pItemData->byResourceSlotSize;    // 新增代码
	
	m_dwWeaponLevelUpStartTime = pItemData->dwWeaponLevelUpStartTime;
	m_nWeaponDur = pItemData->nWeaponDur;
	m_nWeaponPhy = pItemData->nWeaponPhy;
	m_nWeaponMag = pItemData->nWeaponMag;
	m_nWeaponTao = pItemData->nWeaponTao;
	m_byMailNotified = pItemData->byMailNotified;
	m_nExpBottleTimes = pItemData->nExpBottleTimes;

	for (UINT32 i = 0; i < pItemData->dwItemInfoCount; i++)
	{
		UINT32 this_buflen = iteminfo.Load(pItemData->acItemInfos + buflen);
		LOG_PROCESS_ERROR(this_buflen > 0);
		
		buflen += this_buflen;
		
		if (iteminfo.m_byConSlot == CONSLOT_WEAPON_LEVEL_UP)
		{
			LOG_PROCESS_ERROR(iteminfo.m_byItemSlot == 0);
		}
		else
		{
			// 抄的代码 - 暂时屏蔽
			//if (m_pOwner->GetFixRoleCallback())
			//{
			//	if (iteminfo.m_byConSlot >= CONSLOT_COUNT ||
			//	    iteminfo.m_byItemSlot >= m_con_sizes[iteminfo.m_byConSlot])
			//	{
			//		CRI("delete wrong item %d %d @ (%d, %d)", iteminfo.m_nTemplateID, iteminfo.m_nCurDur,
			//		    iteminfo.m_byConSlot, iteminfo.m_byItemSlot);
			//		
			//		INT32 nItemCount = 0;
			//		const ITEM_DATA* pTemplateData = GetItemData(iteminfo.m_nTemplateID);
			//		LOG_PROCESS_ERROR(pTemplateData);
			//		
			//		if (pTemplateData->m_byDurType != DURTYPE_STACK)
			//			nItemCount = 1;
			//		else
			//			nItemCount = iteminfo.m_nCurDur;
			//		
			//		m_pOwner->GetFixRoleCallback()(m_pOwner->GetServerGroup(), m_pOwner->GetObjID(),
			//			iteminfo.m_llGuid, iteminfo.m_nTemplateID, nItemCount);
			//		continue;
			//	}
			//}
			//else
			//{
			//	LOG_PROCESS_ERROR(iteminfo.m_byConSlot < CONSLOT_COUNT);
			//	LOG_PROCESS_ERROR(iteminfo.m_byItemSlot < m_con_sizes[iteminfo.m_byConSlot]);
			//}

			LOG_PROCESS_ERROR(iteminfo.m_byConSlot < CONSLOT_COUNT);
			LOG_PROCESS_ERROR(iteminfo.m_byItemSlot < m_con_sizes[iteminfo.m_byConSlot]);
		}

		//item = CItemMgr::GetInstance().LoadItem(iteminfo, __FILE__, __LINE__);
		item = CItemMgr::GetInstance().LoadItem(iteminfo);
		if (item == NULL)
		{
			CRI("LoadItem Failed: RoleID:%u, GUID:%I64u, TemplateID:%d, Dur:%d", m_pOwner->GetObjID(), iteminfo.m_llGuid, iteminfo.m_nTemplateID, iteminfo.m_nCurDur);
			continue;
		}

		if (iteminfo.m_byConSlot == CONSLOT_WEAPON_LEVEL_UP)
		{
			LOG_PROCESS_ERROR(m_WeaponItem == NULL);
			m_WeaponItem = item;
		}
		else
		{
			m_cons[iteminfo.m_byConSlot].insert(Container::value_type(iteminfo.m_byItemSlot, item));
			if (iteminfo.m_byConSlot == CONSLOT_EQUIPPED && iteminfo.m_nCurDur > 0)
				item->OnEquip(m_pOwner, m_refine_levels[iteminfo.m_byItemSlot], m_pOwner->GetClass(), iteminfo.m_byItemSlot);
		}
	}

	LOG_PROCESS_ERROR(buflen == pItemData->dwItemInfoBufLen);

	//计算强化激活属性
	{
		const REFINE_ATTR_DATA* cur_data = NULL;
		UINT16 cur_min_level = MAX_REFINE_LEVEL;
		for (INT32 i = 0; i < NES_TOTAL; i++)
		{
			if (m_refine_levels[i] < cur_min_level)
				cur_min_level = m_refine_levels[i];
		}

		// 暂时屏蔽
		cur_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(cur_min_level, m_pOwner->GetClass(), NES_TOTAL));
		if (cur_data)
		{
			for (INT32 i = 0; i < cur_data->m_nNodeCount; i++)
				CModifierTree::GetInstance().RollBackExtraNode(cur_data->m_pAttrData[i]->m_nNodeID, m_pOwner, NULL);
		}
	}
	
	// 魔血石, 回复道具
	{
		// 暂时屏蔽
		//Item* RecoverItem = GetItem(CONSLOT_RECOVER, 0);
		//if (RecoverItem && RecoverItem->m_pTemplate->m_nTemplateID >= 2800265 && RecoverItem->m_pTemplate->m_nTemplateID <= 2800272)
		//{
		//	const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(2001 + 10 * (RecoverItem->m_pTemplate->m_nTemplateID - 2800265));
		//	LOG_PROCESS_ERROR(attr_data);
		//	CModifierTree::GetInstance().ApplyExtraNode(attr_data->m_NodeID, m_pOwner, NULL);
		//	
		//	attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(4001 + 10 * (RecoverItem->m_pTemplate->m_nTemplateID - 2800265));
		//	LOG_PROCESS_ERROR(attr_data);
		//	CModifierTree::GetInstance().ApplyExtraNode(attr_data->m_NodeID, m_pOwner, NULL);
		//	
		//	attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(6001 + 10 * (RecoverItem->m_pTemplate->m_nTemplateID - 2800265));
		//	LOG_PROCESS_ERROR(attr_data);
		//	CModifierTree::GetInstance().ApplyExtraNode(attr_data->m_NodeID, m_pOwner, NULL);
		//}
	}

	CheckWeight();

	return TRUE;

Exit0:
	return FALSE;
}

BOOL CRole::_LoadMisc_v_3(const char* pcData, UINT32 dwSize)
{
	const ROLE_DB_MISC_DATA* pcMiscData = (const ROLE_DB_MISC_DATA*)pcData;

	m_nExp = pcMiscData->nExp;
	m_nExtraExp = pcMiscData->nExtraExp;
	m_nExpToday = pcMiscData->nExpToday;

	m_nActivity = pcMiscData->nActivity;
	m_nActivityReward = pcMiscData->nActivityReward;

	m_dwTeamID = 0;
	if (pcMiscData->dwTeamID > 0)
	{
		CTeamInGS* pstTeam = CGameWorld::GetInstance().FindTeam(pcMiscData->dwTeamID);
		
		if (pstTeam)
		{
			for (INT32 i = 0; i < pstTeam->GetMaxMemberCount(); ++i)
			{
				if (pstTeam->GetMemberTable(i).dwRoleID == m_dwObjID)
				{
					m_dwTeamID = pcMiscData->dwTeamID;
					
					if (pstTeam->GetCreateTime() > m_dwSaveTime)
						INF(">>> time error: [tid: %u][rid: %u][ct: %u][st: %u]", pcMiscData->dwTeamID, m_dwObjID, pstTeam->GetCreateTime(), m_dwSaveTime);
					else
						INF(">>> done.");
					break;
				}
			}
		}
	}

	m_nPkMode = pcMiscData->byPkMode;
	m_dwPkValue = pcMiscData->dwPkValue;
	memcpy(m_dwVIPTime, pcMiscData->dwVIPTime, sizeof(m_dwVIPTime));
	m_nCurrentHp = pcMiscData->nCurrentHp;
	m_nCurrentMp = pcMiscData->nCurrentMp;

	m_dwLastCasterID = pcMiscData->dwLastCasterID;
	m_nKilledByPlayer = pcMiscData->nKilledByPlayer;

	{
		// 暂时用 默认代码
		INT32 nTimeDiff = (INT32)pcMiscData->dwNextFreeReviveTime - (INT32)CGameWorld::GetInstance().GetGameTime();
		m_nNextFreeReviveFrm = nTimeDiff * GAME_FPS + CGameWorld::GetInstance().GetGameFrame();

		// 暂时屏蔽
		//m_dwNextFreeReviveTime = pcMiscData->dwNextFreeReviveTime;
	}

	{
		INT32 nTimeDiff = (INT32)pcMiscData->dwNextResetKilledByPlayerTime - (INT32)CGameWorld::GetInstance().GetGameTime();
		m_nNextResetKilledTimesByPlayerFrm = nTimeDiff * GAME_FPS + CGameWorld::GetInstance().GetGameFrame();
	}

	m_nGMLevel = pcMiscData->byGMLevel;
	//if (strncmp(m_szUserName, g_ServerConfig.Common.szSuperGMUserName, USER_NAME_LEN) == 0)
	//	m_nGMLevel = MAX_GM_LEVEL;

	m_dwLastDailyRefreshTime = pcMiscData->dwLastDailyRefreshTime;
	m_dwLastWeeklyRefreshTime = pcMiscData->dwLastWeeklyRefreshTime;
	m_dwLastLineSceneTempID = pcMiscData->dwLastLineSceneTempID;
	m_dwLastLineSceneID = pcMiscData->dwLastLineSceneID;
	m_dwTotalExerciseTime = pcMiscData->dwTotalExerciseTime;
	m_dwStartExerciseTime = pcMiscData->dwStartExerciseTime;

	if (pcMiscData->cAntiCheatLevel < MAX_ROLE_ANTI_CHEAT_LEVEL)
		m_nAntiCheatLevel = pcMiscData->cAntiCheatLevel;
	else
		m_nAntiCheatLevel = 0;

	m_nAntiCheatPunishLevel = pcMiscData->cAntiCheatPunishLevel;
	m_nJigsawRemainTime = pcMiscData->nRemainJigsawTime;
	//	m_dwJigsawTimeoutTime = pcMiscData->dwJigsawTimeoutTime;
	m_dwJigsawSn = pcMiscData->dwJigsawSn;

	if (m_nJigsawRemainTime <= 0)
		StartAntiCheat();
	
	// 暂时屏蔽
	/*
	m_dwChatRecoverTime = pcMiscData->dwChatRecoverTime;
	m_nChatFoulTimes = pcMiscData->nChatFoulTimes;
	
	if (pcMiscData->dwPunishExpTime == 0)
		m_dwPunishExpTime = 0;
	else
		m_dwPunishExpTime = CGameWorld::GetInstance().GetGameTime() + pcMiscData->dwPunishExpTime;
	
	m_nGpkAuthLostCount = pcMiscData->byGpkAuthLostCount;
	m_nGpkKickCount = pcMiscData->byGpkAuthLostKickCount;
	
	m_Guild.DB_SetGuild(pcMiscData->dwTempGuildID);
	m_dwLastGetJigsawExpTime = pcMiscData->dwLastGetJigsawExpTime;
	
	m_nDailyOnlineTime = pcMiscData->nDailyOnlineTime;
	m_dwPKProtect = pcMiscData->dwPKProtect;
	*/

	// 新增代码
	m_dwGameTimeCard = pcMiscData->dwGameTimeCard;
	m_nRuneNormal_Warrior   = pcMiscData->nRuneNormal_Warrior;
	m_nRuneNormal_Mage      = pcMiscData->nRuneNormal_Mage;
	m_nRuneNormal_Taoist    = pcMiscData->nRuneNormal_Taoist;
	m_nRuneAdvanced_Warrior = pcMiscData->nRuneAdvanced_Warrior;
	m_nRuneAdvanced_Mage    = pcMiscData->nRuneAdvanced_Mage;
	m_nRuneAdvanced_Taoist  = pcMiscData->nRuneAdvanced_Taoist;
	m_nLuckRootCount        = pcMiscData->nLuckRootCount;



	return TRUE;
}


// ========== 抄的代码 end ==========

