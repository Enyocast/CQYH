#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include <time.h>

IMPLEMENT_CLASS(UMMOUINewEventPanel)

void UMMOUINewEventPanel::Init()
{
	Super::Init();
}

void UMMOUINewEventPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
	}
}

void UMMOUINewEventPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
}

void UMMOUINewEventPanel::ShowNewEvent(INT type, const FString& text)
{
	Show(TRUE);
	eventCallShowNewEvent(type, text);
}