#include "stdafx.h"
#include "role.h"
#include "gamble.h"
#include "game_world.h"

#include "role_db_def_v_2.h"
using namespace ROLE_DB_DEF_V_2;

BOOL CRole::_Load_v_2(const char* pcData, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	ROLE_DB_DATA* pRoleData = (ROLE_DB_DATA*)pcData;
	UINT32 dwRealDataSize = 0;

	LOG_PROCESS_ERROR(pcData);
	LOG_PROCESS_ERROR(pRoleData->dwVersion == 2);
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
			nRetCode = m_ItemBag.Load_v_1(pcBlockData, dwBlockSize);
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
			nRetCode = _LoadMisc_v_2(pcBlockData, dwBlockSize);    // V2 抄代码
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
		case rbtGamble:    // 新增代码
			nRetCode = m_Gamble.Load_v_1(pcBlockData, dwBlockSize);
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

// 新增函数 抄代码
BOOL CGamble::Load_v_1(const char* pcData, UINT32 dwSize)
{
	Clear();
	
	ROLE_DB_GAMBLE_DATA* pGambleData = (ROLE_DB_GAMBLE_DATA*)pcData;
	for (INT32 i = 0; i < egtTotal; i++)
	{
		for (INT32 j = 0; j < GAMBLE_LEVEL_COUNT; j++)
		{
			dwValue[i][j] = pGambleData->dwValue[i][j];
			dwTotalValue[i][j] = pGambleData->dwTotalValue[i][j];
		}
	}
	
	return TRUE;
}

BOOL CRole::_LoadMisc_v_2(const char* pcData, UINT32 dwSize)
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
		//INT32 nTimeDiff = (INT32)pcMiscData->dwNextFreeReviveTime - (INT32)CGameWorld::GetInstance().GetGameTime();
		//m_nNextFreeReviveFrm = nTimeDiff * GAME_FPS + CGameWorld::GetInstance().GetGameFrame();
		//m_dwNextFreeReviveTime = pcMiscData->dwNextFreeReviveTime;    // 暂时屏蔽
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
	*/
	
	return TRUE;
}

