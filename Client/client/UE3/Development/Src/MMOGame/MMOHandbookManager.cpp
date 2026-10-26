#include "stdafx.h"
#include "Inc\MMOGameUIClasses.h"
#include "MMOHandbookManager.h"
#include "MMOHandbookData.h"
#include "EngineAudioDeviceClasses.h"
#include "MMOFacade.h"

using namespace ExternalMessage;

//////////////////////////////////////////////////////////////////////////
MMOHandbookManager::MMOHandbookManager()
{
	MMOUI::RegisterEventHandler(this, GameEvent_Handbook);
}

MMOHandbookManager::~MMOHandbookManager()
{
	MMOUI::UnRegisterEventHandler(this, GameEvent_Handbook);
}

void MMOHandbookManager::Init()
{
	MMOHandbookData::getSingleton().Init();
}

void MMOHandbookManager::Shutdown()
{
	MMOHandbookData::getSingleton().Shutdown();
}

void MMOHandbookManager::Clear()
{
	MMOHandbookData::getSingleton().Clear();
}

void MMOHandbookManager::Update(FLOAT deltaTime)
{
}

void MMOHandbookManager::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if (!evt)
	{
		return;
	}

	if (evt->GetEventType() == GameEvent_Handbook)
	{
		MMOGameEvent_Handbook* evtHandbook = (MMOGameEvent_Handbook*)evt;
		if (evtHandbook)
		{
		}
	}
}

void MMOHandbookManager::PlayHandbookSound(UINT32 type, UINT32 index)
{
	HandbookData data;
	if (MMOHandbookData::getSingleton().GetHandbookData(type, index, data))
	{
		if (data.Sound != TEXT(""))
		{
			USoundCue* sound = LoadUEObject<USoundCue>(data.Sound, TEXT("handbook.txt"));
			if (sound)
			{
				MMOFacade::getSingleton().GetMainActor()->PlaySound(sound);
			}
		}
	}
}

void MMOHandbookManager::StopHandbookSound(UINT32 type, UINT32 index)
{
	HandbookData data;
	if (MMOHandbookData::getSingleton().GetHandbookData(type, index, data))
	{
		if (data.Sound != TEXT(""))
		{
			INT startIndex = data.Sound.InStr(TEXT("SoundCue'"), FALSE, TRUE);
			INT endIndex = data.Sound.InStr(TEXT("'"), TRUE, TRUE);
			if (startIndex >= 0 && endIndex >= 0)
			{
				startIndex = startIndex + FString(TEXT("SoundCue'")).Len();
				INT count = endIndex - startIndex;
				FString soundName = data.Sound.Mid(startIndex, count > 0 ? count : MAXINT);
				MMOFacade::getSingleton().StopVoiceSound(soundName, FALSE, 1.0, 0.0);
			}
		}
	}
}

void MMOHandbookManager::NotifySyncHandbookInfo(ROLE_DB_ACHIEVEMENT_DATA* list)
{
	MMOHandbookData::getSingleton().SyncHandbookInfo(list);
}

void MMOHandbookManager::NotifyUpdateHandbookInfo(INT32 type, INT32 index)
{
	MMOHandbookData::getSingleton().UpdateHandbookInfo(type, index);

	MMOGameEvent_Handbook evtHandbook(MMOGameEvent_Handbook::EHET_UpdateHandbookInfo, type, index);
	MMOUI::PostGameEvent(&evtHandbook);
}

void MMOHandbookManager::NotifyUseStoryScroll(INT itemId)
{
	if (MMOUI::GetUIManager() == NULL)
	{
		return;
	}

	UINT32 type = 0;
	UINT32 index = 0;
	if (MMOHandbookData::getSingleton().GetStoryHandbookInfoById(itemId, type, index))
	{
		UMMOUIHandbookPanel* panel = (UMMOUIHandbookPanel*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Handbook);
		if (panel)
		{
			panel->_CurClass = HC_Item;
			panel->_CurType = type;
			panel->_CurIndex = index;
			panel->Show(TRUE);
		}
	}
} 