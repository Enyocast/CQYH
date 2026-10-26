#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include <time.h>


IMPLEMENT_CLASS(UMMOUIGuildWarHintPanel)

void UMMOUIGuildWarHintPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildWarHintPanel>(this, evts);
}

void UMMOUIGuildWarHintPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		eventCallSetWindowTitle(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.GuideWar")));
	}
}

void UMMOUIGuildWarHintPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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

	switch(guildEvent->_EventType)
	{
	case MMOGameEvent_Guild::EGET_UpdateGuildWarReadyTime:
		{
			UpdateGuildWarHintTime(GUILD_WAR_STAGE_DECLARE);
		}
		break;
	case MMOGameEvent_Guild::EGET_UpdateGuildWarTime:
		{
			UpdateGuildWarHintTime(GUILD_WAR_STAGE_BEGIN);
		}
		break;
	}
}

void UMMOUIGuildWarHintPanel::UpdateGuildWarHintInfo(const FString& attackGuildName, const FString& defendGuildName, const FString& timeTitle, INT32 lastTime)
{
	FString timeString = TEXT("");
	MMOFacade::getSingleton().GetTimeString(lastTime, timeString);
	eventCallUpdateGuildWarHintInfo(attackGuildName, defendGuildName, timeTitle, timeString);
}

void UMMOUIGuildWarHintPanel::UpdateGuildWarHintTime(UINT8 state)
{
	FString timeString = TEXT("");
	if (state == GUILD_WAR_STAGE_DECLARE)
	{
		MMOFacade::getSingleton().GetTimeString(MMOGuildManager::getSingleton().GetGuildWarReadyTime(), timeString);
	} 
	else if (state == GUILD_WAR_STAGE_BEGIN)
	{
		MMOFacade::getSingleton().GetTimeString(MMOGuildManager::getSingleton().GetGuildWarTime(), timeString);
	}
	eventCallUpdateGuildWarHintTime(timeString);
}
