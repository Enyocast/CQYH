#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include <time.h>

IMPLEMENT_CLASS(UMMOUIWeatherChangePanel)

void UMMOUIWeatherChangePanel::Init()
{
	Super::Init();
}

void UMMOUIWeatherChangePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
	}
}

void UMMOUIWeatherChangePanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
}

void UMMOUIWeatherChangePanel::SetWeatherChangeTip(const FString& content)
{
	eventCallSetWeatherChangeString(content);
}

void UMMOUIWeatherChangePanel::ASWeatherChangePlayEnd()
{
	SetVisible(FALSE);
}