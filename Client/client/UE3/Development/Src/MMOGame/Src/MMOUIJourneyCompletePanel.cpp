#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOQuestManager.h"
#include "UITextParser.h"
#include "LinkManager.h"
#include "MMOMapDataManager.h"
#include "DoodadManager.h"
#include "MMOJourneyManager.h"

IMPLEMENT_CLASS(UMMOUIJourneyCompletePanel)

void UMMOUIJourneyCompletePanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Journey);
	EventAdapter = new TGameEventAdapter<UMMOUIJourneyCompletePanel>(this, evts);
}

void UMMOUIJourneyCompletePanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v)
	{
	}
}

void UMMOUIJourneyCompletePanel::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if (!IsVisible)
	{
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_Journey:
		{
			MMOGameEvent_Journey* journeyEvent = (MMOGameEvent_Journey*)evt;
			if (journeyEvent)
			{
			}
		}
		break;
	}
}

void UMMOUIJourneyCompletePanel::ASJourneyComplete()
{
	Show(FALSE);
}
