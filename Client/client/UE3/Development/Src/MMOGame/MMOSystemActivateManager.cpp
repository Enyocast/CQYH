#include "stdafx.h"
#include "MMOSystemActivateManager.h"
#include "MMOFacade.h"
#include "Inc\MMOGameUIClasses.h"
#include "MMOStats.h"

using namespace ExternalMessage;

MMOSystemActivateManager::MMOSystemActivateManager()
{
}

MMOSystemActivateManager::~MMOSystemActivateManager()
{
}

void MMOSystemActivateManager::Init()
{
}

void MMOSystemActivateManager::Shutdown()
{
}

void MMOSystemActivateManager::Clear()
{
	_ActivateSystemLevelMap.clear();
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Guild, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Schedule, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_GoldStore, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_LingXing, 100));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_LongWei, 100));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_NormalQuest, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_QiXi, 100));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Mall, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Repute, 100));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_MasterStudent, 1));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Enhance, 100));		
//	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Riding, 60));
	_ActivateSystemLevelMap.insert(std::make_pair(EAST_Handbook, 1));

	_ActivateSystemSet.clear();
	while (_ActivateSystemQueue.size() > 0)
	{
		_ActivateSystemQueue.pop();
	}
}

void MMOSystemActivateManager::Update(FLOAT deltaTime)
{
}

void MMOSystemActivateManager::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if (!evt)
	{
		return;
	}
}

void MMOSystemActivateManager::NotifyPlayerLevelChange(INT curLevel)
{
	_ActivateSystem(curLevel);
}

void MMOSystemActivateManager::_ActivateSystem(UINT32 level)
{
	UMMOUIManager* uiManager = MMOUI::GetUIManager();
	if (!uiManager)
	{
		return;
	}

	UMMOUIMenuBar* menuBar = Cast<UMMOUIMenuBar>(uiManager->FindUIPanel(uiManager->Panel_Skillbar_Menubar));
	if (!menuBar)
	{
		return;
	}

	if (MMO::GetCurrentGameState() == EGameState_InGame)
	{
		ActivateSystemLevelMap::iterator iter = _ActivateSystemLevelMap.begin();
		for (; iter != _ActivateSystemLevelMap.end(); ++ iter)
		{
			if ((UINT32)(iter->second) <= level)
			{
				ActivateSystemSet::iterator iterSet = _ActivateSystemSet.find(iter->first);
				if (iterSet == _ActivateSystemSet.end())
				{
					_PushNewSystem(iter->first);
					_ActivateSystemSet.insert(iter->first);
				}
			}
		}
	}
	else
	{
		ActivateSystemLevelMap::iterator iter = _ActivateSystemLevelMap.begin();
		for (; iter != _ActivateSystemLevelMap.end(); ++ iter)
		{
			if ((UINT32)(iter->second) <= level)
			{
				_ActivateSystemSet.insert(iter->first);
			}
		}
	}
}

void MMOSystemActivateManager::_PushNewSystem(INT systemType)
{
	_ActivateSystemQueue.push(systemType);

	if (_ActivateSystemQueue.size() == 1)
	{
		UMMOUIManager* uiManager = MMOUI::GetUIManager();
		if (uiManager)
		{
			UMMOUIMenuBar* menuBar = Cast<UMMOUIMenuBar>(uiManager->FindUIPanel(uiManager->Panel_Skillbar_Menubar));
			if (menuBar)
			{
				menuBar->ShowNewSystem(systemType);
			}
		}
	}
}

INT MMOSystemActivateManager::GetNextSystemType()
{
	if (_ActivateSystemQueue.size() > 0)
	{
		_ActivateSystemQueue.pop();
	}

	if (_ActivateSystemQueue.size() > 0)
	{
		return _ActivateSystemQueue.front();
	}

	return EAST_Tatol;
}

INT MMOSystemActivateManager::GetChildMenuType(INT systemType)
{
	INT childMenuType = EMenuType_MAX;
	switch (systemType)
	{
	case EAST_Guild:
		childMenuType = EMenuType_Child_Guild;
		break;
	case EAST_Schedule:
		childMenuType = EMenuType_Child_Schedule;
		break;
	case EAST_GoldStore:
		childMenuType = EMenuType_Child_GoldStore;
		break;
	case EAST_LongWei:
	case EAST_LingXing:
	case EAST_QiXi:
		childMenuType = EMenuType_Child_Heaven;
		break;
	case EAST_NormalQuest:
		childMenuType = EMenuType_Child_NormalQuest;
		break;
	case EAST_Mall:
		childMenuType = EMenuType_Child_Mall;
		break;
	case EAST_Repute:
		childMenuType = EMenuType_Child_Repute;
		break;
	case EAST_MasterStudent:
		childMenuType = EMenuType_Child_MasterStudent;
		break;
	case EAST_Enhance:
		childMenuType = EMenuType_Child_Charactor;
		break;
	case EAST_Riding:
		childMenuType = EMenuType_Child_Riding;
		break;
	case EAST_Handbook:
		childMenuType = EMenuType_Child_Handbook;
		break;
	}

	return childMenuType;
}

UBOOL MMOSystemActivateManager::GetSystemInfo(INT systemType, FString& icon, FString& name)
{
	icon = TEXT("");
	name = TEXT("");

	switch (systemType)
	{
	case EAST_Guild:
		{
			icon = TEXT("img://UI_SkillbarWidget.guild");
			name = TEXT("公会");
			return TRUE;
		}
		break;
	case EAST_Schedule:
		{
			icon = TEXT("img://UI_SkillbarWidget.activity");
			name = TEXT("活动");
			return TRUE;
		}
		break;
	case EAST_GoldStore:
		{
			icon = TEXT("img://UI_SkillbarWidget.goldstore");
			name = TEXT("金币交易行");
			return TRUE;
		}
		break;
	case EAST_LongWei:
		{
			icon = TEXT("img://UI_SkillbarWidget.longwei");
			name = TEXT("龙卫心法");
			return TRUE;
		}
	case EAST_LingXing:
		{
			icon = TEXT("img://UI_SkillbarWidget.lingxing");
			name = TEXT("灵性修炼");
			return TRUE;
		}
	case EAST_QiXi:
		{
			icon = TEXT("img://UI_SkillbarWidget.qixi");
			name = TEXT("气息修炼");
			return TRUE;
		}
		break;
	case EAST_NormalQuest:
		{
			icon = TEXT("img://UI_SkillbarWidget.normalquest");
			name = TEXT("普通任务");
			return TRUE;
		}
		break;
	case EAST_Mall:
		{
			icon = TEXT("img://UI_SkillbarWidget.mall");
			name = TEXT("商城");
			return TRUE;
		}
		break;
	case EAST_Repute:
		{
			icon = TEXT("img://UI_SkillbarWidget.repute");
			name = TEXT("声望");
			return TRUE;
		}
		break;
	case EAST_MasterStudent:
		{
			icon = TEXT("img://UI_SkillbarWidget.master");
			name = TEXT("师徒");
			return TRUE;
		}
		break;
	case EAST_Enhance:
		{
			icon = TEXT("img://UI_SkillbarWidget.enhance");
			name = TEXT("体格强化");
			return TRUE;
		}
		break;
	case EAST_Riding:
		{
			icon = TEXT("img://UI_SkillbarWidget.ride");
			name = TEXT("坐骑");
			return TRUE;
		}
		break;
	case EAST_Handbook:
		{
			icon = TEXT("img://UI_SkillbarWidget.normalquest");
			name = TEXT("百晓生");
			return TRUE;
		}
		break;
	}

	return FALSE;
}

