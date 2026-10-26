#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include <time.h>


IMPLEMENT_CLASS(UMMOUIGuildWeatherPanel)

void UMMOUIGuildWeatherPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildWeatherPanel>(this, evts);
}

void UMMOUIGuildWeatherPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		UpdateGuildWeatherInfo();
	}
}

void UMMOUIGuildWeatherPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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

void UMMOUIGuildWeatherPanel::UpdateGuildWeatherInfo()
{
	UGFxObject* object = GFXPlayer->CreateObject("Object");
	if (!object)
	{
		return;
	}

	GuildBaseInfo baseInfo = MMOGuildData::getSingleton().GetGuildBaseInfo();
	object->SetInt(TEXT("guild_id"), baseInfo.Id);
	object->SetInt(TEXT("guild_weather_type"), 1);
	object->SetInt(TEXT("guild_weather_time"), 10);
	object->SetInt(TEXT("guild_weather_money"), 0);

	eventCallUpdateGuildWeatherInfo(object);
}
//////////////////////////////////////////////////////////////////////////

void UMMOUIGuildWeatherPanel::ASChangeWeather(INT weatherType, INT durationType)
{
	CMessageHandler::GetInstance().Send_ChangeWeather(weatherType, durationType); 
}
