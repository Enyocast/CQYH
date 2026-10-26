#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include <time.h>


IMPLEMENT_CLASS(UMMOUIGuildDungeonEndPanel)

void UMMOUIGuildDungeonEndPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildDungeonEndPanel>(this, evts);
}

void UMMOUIGuildDungeonEndPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		UpdateGuildDungeonAwardList();
	}
}

void UMMOUIGuildDungeonEndPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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
	if (!guildEvent)
	{
		return;
	}
}

void UMMOUIGuildDungeonEndPanel::UpdateGuildDungeonAwardList()
{
	UGFxObject* dataArray = GFXPlayer->CreateArray();
	if (!dataArray)
	{
		return;
	}
	
	GuildDungeonAwardList guildDungeonAwardList = MMOGuildData::getSingleton().GetGuildDungeonAwardList();
	GuildDungeonAwardList::iterator iter = guildDungeonAwardList.begin();
	UINT8 index = 0;
	for (; iter != guildDungeonAwardList.end(); ++ iter)
	{
		UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
		if (object)
		{
			UItem* item = MMOFacade::getSingleton().FindItemTemplate(iter->dwItemID);
			if (item)
			{
				object->SetInt(TEXT("guild_dun_award_id"), iter->dwItemID);
				object->SetInt(TEXT("guild_dun_award_index"), index);
				object->SetInt(TEXT("guild_dun_award_count"), iter->byCount);
				object->SetString(TEXT("guild_dun_award_icon_name"), MMOFacade::getSingleton().GetItemIconNamePersonalized( item ));
				object->SetString(TEXT("guild_dun_award_item_name"), item->GetDisplayName());

				dataArray->SetElementObject(index, object);	
				index ++;
			}
		}
	}
	
	eventCallUpdateGuildDungeonAwardList(dataArray);
}

void UMMOUIGuildDungeonEndPanel::SetGuildDungeonBoss(UINT32 bossId)
{
	FString name = TEXT("");
	PlayerBaseInfo* playerInfo = MMOFacade::getSingleton().RequestPlayerBaseInfo(bossId, TRUE);
	if (playerInfo)
	{
		name = playerInfo->_RoleName;
	}
	else
	{
		name = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.UnknownName"));
	}
	FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.AwardMail")), 
		*name);
	eventCallSetGuildDungeonBoss(text);
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIGuildDungeonEndPanel::ASLeaveGuildDungeon()
{
	CMessageHandler::GetInstance().Send_LeaveScene(); 
}
