#include "stdafx.h"
#include "RankListManager.h"

RankListManager::RankListManager()
	:eRankList(rlLevel),
	eRankTotal(rlLevel),
	_SelfLastRank(0)
{
	//GConfig->GetInt(TEXT("MaxLevel"),TEXT("maxLevel"),maxLevel,GDefaultGameIni);
	GConfig->GetInt(TEXT("HeroRankList"),TEXT("heroRankMaxTime"),heroRankMaxTime,GDefaultGameIni);
	
	bShowRank = TRUE;
	myHeroNum = 0;
}

RankListManager::~RankListManager()
{
	Clear();

	PageMap::iterator iter = _PageMap.begin();
	while (iter != _PageMap.end())
	{
		SAFE_DELETE(iter->second);
		++iter;
	}
	_PageMap.clear();
}

void RankListManager::AddData(INT64 Id, INT64 value,UINT8 lastRank)
{
	//ASSERT_CHECK_ERROR_RETURN(Id >= 0);
	if(Id <= 0)
		return;
	RankListData* pRankListData = new RankListData;
	pRankListData->Id = Id;
	pRankListData->Value = value;
	pRankListData->LastRank = lastRank;
	_RankVec.push_back(pRankListData);
	
}

const RankVec& RankListManager::GetRankVec() const
{
	return _RankVec;
}

void RankListManager::Clear()
{
	RankVec::iterator it = _RankVec.begin();
	while (it != _RankVec.end())
	{
		SAFE_DELETE(*it);
		++it;
	}
	_RankVec.clear();
}

void RankListManager::NotifyUpdateRankList()
{
	UMMOUIBase* pPanel = NULL;

	if(RankListManager::getSingleton().GetType() == rlActivity01)
	{
		
		pPanel = MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_HeroRank);
	}
	else
	{
		pPanel = MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_RankList);
	}
	
	if(NULL != pPanel && pPanel->GetVisible())
	{
		MMOGameEvent_RankList evt;
		MMOUI::PostGameEvent(&evt);
	}
}

void RankListManager::NotifyReFreshList()
{
	UMMOUIBase* pPanel = NULL;

	if(RankListManager::getSingleton().GetType() == rlActivity01)
	{

		pPanel = MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_HeroRank);
	}
	else
	{
		pPanel = MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_RankList);
	}

	if(NULL != pPanel && pPanel->GetVisible())
	{
		MMOGameEvent_Any evt( GameEvent_RankList_RefreshList);
		MMOUI::PostGameEvent(&evt);
	}
}
void RankListManager::SetPageIndex(RANK_LIST type, INT index)
{
	PageMap::iterator it = _PageMap.find(type);
	if (it == _PageMap.end())
	{
		PageInfo* pPageInfo = new PageInfo;
		pPageInfo->curPage = index;
		pPageInfo->totalPage = 0;
		_PageMap.insert(std::make_pair(eRankTotal, pPageInfo));
	}
	else
	{
		it->second->curPage = index;
	}
}

INT RankListManager::GetPageIndex() const
{
	PageMap::const_iterator it = _PageMap.find(eRankTotal);
	//ASSERT_CHECK_ERROR_0_RETURN(it != _PageMap.end());
	if (it != _PageMap.end())
	{
		return it->second->curPage;
	}
	return 0;
	
}

void RankListManager::SetPageTotal(INT total)
{
	PageMap::iterator it = _PageMap.find(eRankTotal);
	if (it == _PageMap.end())
	{
		PageInfo* pPageInfo = new PageInfo;
		pPageInfo->curPage = 0;
		pPageInfo->totalPage = total;
		_PageMap.insert(std::make_pair(eRankTotal, pPageInfo));
	}
	else
	{
		it->second->totalPage = total;
	}
}

INT RankListManager::GetPageTotal() const
{
	PageMap::const_iterator it = _PageMap.find(eRankTotal);
	//ASSERT_CHECK_ERROR_0_RETURN(it != _PageMap.end());
	if (it != _PageMap.end())
	{
		return it->second->totalPage;
	}
	return 1;
}

void RankListManager::SetType(RANK_LIST type)
{
	switch(type)
	{
	case rlActivity01:
		{
			eRankList = rlActivity01;
		}
		break;
	case rlActivity02:
	case rlActivity03:
	case rlActivity04:
		{
			eRankList = rlActivity02;
		}
		break;
	case rlArena1v1:
	case rlArena1v1Warrior:
	case rlArena1v1Mage:
	case rlArena1v1Taoist:
		{
			eRankList = rlArena1v1;
		}
		break;
	case rlLevel:					// 等级排行榜
	case rlLevelWarrior:
	case	rlLevelMage:
	case	rlLevelRogue:
	case	rlLevelArcher:
	case	rlLevelTaoist:
		{
			eRankList = rlLevel;
			break;
		}
	case rlPower:					// 战斗力排行榜
	case	rlPowerWarrior:
	case	rlPowerMage:
	case	rlPowerRogue:
	case	rlPowerArcher:
	case	rlPowerTaoist:
		{
			eRankList = rlPower;
			break;
		}
	//case	rlArmerPower:				// 装备战斗力排行榜
	//case	rlArmerPowerWarrior:
	//case rlArmerPowerMage:
	//case	rlArmerPowerRogue:
	//case	rlArmerPowerArcher:
	//	{
	//		eRankList = rlArmerPower;
	//		break;
	//	}
	//case	rlSpiritPower:				// 境界战斗力排行榜
	//case	rlSpiritPowerWarrior:
	//case	rlSpiritPowerMage:
	//case	rlSpiritPowerRogue:
	//case	rlSpiritPowerArcher:
	//	{
	//		eRankList = rlSpiritPower;
	//		break;
	//	}
	case	rlGuild_Resource_Wood:		// 家族资源01
	case	rlGuild_Resource_Herb:		// 家族资源02
	case	rlGuild_Resource_Crystal:	// 家族资源03
	case	rlGuild_Resource_Silver:	// 家族资源04
		{
			eRankList = rlGuild_Resource_Herb;
			break;
		}
	//case rlDungeonNormalScore:
	//case rlDungeonEasyScore:
	//case rlDungeonHardScore:
	//case rlDungeonHellScore:
	//	{
	//		eRankList = rlDungeonNormalScore;
	//		break;
	//	}
	//case rlItemPower:                   //体格战斗力
	//case rlItemPowerWarrior:
	//case rlItemPowerMage:
	//case rlItemPowerRogue:
	//case rlItemPowerArcher:	

	//	{
	//		eRankList = rlItemPower;
	//		break;
	//	}
	default:
		{
			eRankList = type;
			break;
		}
	}
}

INT RankListManager::GetRangeBtnIndex(int currentPage)
{
	INT nBtnIndex = -1;
	switch(currentPage)
	{
	case RP_Page1:
		nBtnIndex = RP_Rdo0;
		break;
	case RP_Page2:
		nBtnIndex = RP_Rdo1;
		break;
	case RP_Page3:
		nBtnIndex = RP_Rdo2;
		break;
	case RP_Page5 + 1:
		nBtnIndex = RP_Rdo3;
		break;
	case RP_Page10 + 1:
		nBtnIndex = RP_Rdo4;
		break;
	case RP_Page20 + 1:
		nBtnIndex = RP_Rdo5;
		break;
	case RP_Page30 + 1:
		nBtnIndex = RP_Rdo6;
		break;
	}
	return nBtnIndex;
}

INT RankListManager::getMaxRankListCount()
{
	switch(GetType())
	{
	case	rlLevel:					// 等级排行榜
	case	rlPower:					// 战斗力排行榜
	//case	rlArmerPower:				// 装备战斗力排行榜
	//case	rlSpiritPower:				// 境界战斗力排行榜
	//case	rlItemPower:                // 体格战斗力
	case	rlMoney:					// 财富排行榜
	case	rlAchievement:				// 成就点数排行榜
	case	rlMaster:					// 名师值排行榜
	case	rlPkValue:					// pk值排行榜
	case	rlTotalKillCount:			// 总杀人数
	//case rlExp:
		{
			return MAXRANKLISTCOUNT_PERSON;
			break;
		}
		// 家族排行榜
	case	rlGuild_Level:				// 家族等级排行榜
	case	rlGuild_Money:				// 家族金钱排行榜
	case	rlGuild_Resource_Herb:		// 家族资源01
	case	rlGuild_Pow:
	case    rlGuild_War:

		// 竞技场排行榜
	//case	rlRoleArenaScore:				
	//case	rlArenaScore:
	case	rlGuild_Resource_Wood:		    // 家族资源02
	case	rlGuild_Resource_Crystal:	    // 家族资源03
	case	rlGuild_Resource_Silver:	
		{
			return MAXRANKLISTCOUNT_GUILD;
			break;
		}
	}
	return MAXRANKLISTCOUNT_PERSON;
	
}

void RankListManager::NotifyUpdateCategoryButton()
{
	MMOGameEvent_RankList_UpdateCategoryButton evt;
	MMOUI::PostGameEvent(&evt);
}

void RankListManager::SetShowRank(UINT32 time)
{
	__time32_t localTime = time;
	struct tm *serverTimeTemp = _localtime32(&localTime);
	struct tm serverTime = *serverTimeTemp;

	showRankTime = *serverTimeTemp;

	__time32_t today;
	_time32(&today);
	struct tm *todayTimeTemp = _localtime32(&today);
	struct tm todayTime = *todayTimeTemp;


	if (serverTime.tm_year == todayTime.tm_year && serverTime.tm_mon == todayTime.tm_mon && serverTime.tm_mday == todayTime.tm_mday
		&& serverTime.tm_hour == 0 && serverTime.tm_min == 0 && serverTime.tm_sec == 0)
	{
		bShowRank = FALSE;
	}
	else
	{
		bShowRank = TRUE;
	}
	
}