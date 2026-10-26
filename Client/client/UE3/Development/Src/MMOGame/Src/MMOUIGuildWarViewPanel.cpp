#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include "MMOGuideManager.h"

#include <time.h>


IMPLEMENT_CLASS(UMMOUIGuildWarViewPanel)

void UMMOUIGuildWarViewPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildWarViewPanel>(this, evts);
}

void UMMOUIGuildWarViewPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		eventCallSetWindowTitle(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.ViewPanel")));
	}
}

void UMMOUIGuildWarViewPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
	if (!IsVisible)
	{
		return;
	}

	if (gameEvent->GetEventType() != GameEvent_Guild)
	{
		return;
	}

	MMOGameEvent_Guild* guildEvent = (MMOGameEvent_Guild*)gameEvent;
	if (guildEvent == NULL)
	{
		return;
	}
}

void UMMOUIGuildWarViewPanel::UpdateGuildViewInfo()
{
	UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
	if (object)
	{
		GuildViewInfo info;
		if (MMOGuildManager::getSingleton().GetCurGuildWarViewInfo(info))
		{
			object->SetInt(TEXT("guild_id"), info.Id);
			object->SetString(TEXT("guild_name"), info.Name);
			object->SetString(TEXT("guild_leader_name"), info.LeaderName);
			object->SetInt(TEXT("guild_level"), info.level);
			object->SetInt(TEXT("guild_prosperity"), info.Prosperity);

			if (info.Announce.IsEmpty())
			{
				object->SetString(TEXT("guild_announce"), MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.GuildAnnounceEmpty")));
			}
			else
			{
				object->SetString(TEXT("guild_announce"), info.Announce);
			}

			eventCallUpdateGuildViewInfo(object);
		}
	}
}

void UMMOUIGuildWarViewPanel::UpdateGuildBuildingList()
{
	UGFxObject* objectArray = GFXPlayer->CreateArray();
	if (objectArray)
	{
		GuildViewInfo info;
		if (MMOGuildManager::getSingleton().GetCurGuildWarViewInfo(info))
		{
			INT index = 0;
			for (INT i = GUILD_B_MAIN; i < GUILD_B_NUM; ++ i)
			{
				if (i == GUILD_B_GATE ||
					i == GUILD_B_WALL)
				{
					continue;
				}

				UINT32 buildingType = i;
				UINT32 buildingLv = info.BuildingLevel[i];
				GuildBuildingData buildingData;
				if (MMOGuildData::getSingleton().GetGuildBuildingData(buildingType, buildingLv > 0 ? buildingLv : 1, buildingData))
				{
					UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
					if (object)
					{
						object->SetInt(TEXT("guild_building_type"), buildingType);
						object->SetString(TEXT("guild_building_name"), buildingData.Name);
						FString buildingIcon = FString::Printf(TEXT("img://UI_GuildTerritoryWidget.%d"), buildingData.BuildingType);
						object->SetString(TEXT("guild_building_icon"), buildingIcon);
						object->SetInt(TEXT("guild_building_level"), buildingLv);

						objectArray->SetElementObject(index, object);
						index ++;
					}
				}
			}

			eventCallUpdateGuildBuildingList(objectArray);
		}
	}
}

void UMMOUIGuildWarViewPanel::ShowGuildWarInfoPanel()
{
	Show(TRUE);
	UpdateGuildViewInfo();
	UpdateGuildBuildingList();
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIGuildWarViewPanel::ASMatchChallenge(INT id)
{
	CMessageHandler::GetInstance().Send_MatchChallenge(id);
}

