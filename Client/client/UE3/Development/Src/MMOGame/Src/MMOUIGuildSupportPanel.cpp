#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include "MMOMsgBoxManager.h"
#include <time.h>

IMPLEMENT_CLASS(UMMOUIGuildSupportPanel)

void UMMOUIGuildSupportPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildSupportPanel>(this, evts);
}

void UMMOUIGuildSupportPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		UpdateGuildSupportList();
	}
	else
	{
	}
}

void UMMOUIGuildSupportPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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

	switch(guildEvent->_EventType)
	{
	case MMOGameEvent_Guild::EGET_UpdateGuildAllyList:
		{
			UpdateGuildSupportList();
		}
		break;
	}
}

void UMMOUIGuildSupportPanel::ShowGuildSupportPanel()
{
	if (!IsVisible)
	{
		Show(TRUE);
	}
}

void UMMOUIGuildSupportPanel::UpdateGuildSupportList()
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	if (!dataProvider)
	{
		return;
	}

	GuildAllyInfoList guildAllyInfoList = MMOGuildData::getSingleton().GetGuildAllyInfoList();
	GuildAllyInfoList::iterator iter = guildAllyInfoList.begin();
	INT index = 0;
	for (; iter != guildAllyInfoList.end(); ++iter)
	{
		if (iter->LeftTime <= 0)
		{
			continue;
		}

		UGFxObject* object = GFXPlayer->CreateObject("Object");
		object->SetString(TEXT("label"), iter->Name);
		object->SetInt(TEXT("index"), index);
		object->SetInt(TEXT("type"), 0);
		object->SetInt(TEXT("deepth"), 0);
		object->SetBool(TEXT("visible"), true);

		object->SetInt(TEXT("Id"), iter->Id);
		object->SetString(TEXT("guild_name"), iter->Name);
		object->SetInt(TEXT("guild_level"), iter->Level);
		object->SetInt(TEXT("Num"), iter->MemberCount);

		FString timeString = TEXT("");
		MMOFacade::getSingleton().GetTimeString(iter->LeftTime, timeString);
		object->SetString(TEXT("timer"), timeString);

		object->SetBool(TEXT("status"), TRUE);

		dataProvider->SetElementObject(index, object);
		index++;
	}

	eventCallUpdateGuildSupportList(dataProvider);
}

//////////////////////////////////////////////////////////////////////////
void UMMOUIGuildSupportPanel::ASEnterTerritory(INT id)
{
	if (id <= 0)
	{
		FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.GuildWarehouse.NoGuild"));
		MMOUI::GetUIManager()->delegateAddScreenMessage(text, MsgInfoType_Table, TEXT("MMOGame.GuildWarehouse.NoGuild"));
		return;
	}
	
	CMessageHandler::GetInstance().Send_EnterGuildMap(GUILD_ENTER_ALLIANCE, id);
}