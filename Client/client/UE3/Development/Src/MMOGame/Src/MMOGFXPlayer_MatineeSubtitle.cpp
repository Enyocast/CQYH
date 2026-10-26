#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_MatineeSubtitle)

void UMMOGFXPlayer_MatineeSubtitle::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_MatineeSubtitle);
	evts.AddItem(GameEvent_LeaveGame);
	EventAdapter = new TGameEventAdapter<UMMOGFXPlayer_MatineeSubtitle>(this, evts);

	FVector2D scrSz = MMOFacade::GetScreenSize();
	eventCallUCShow(false, scrSz.X, scrSz.Y);
}

void UMMOGFXPlayer_MatineeSubtitle::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_MatineeSubtitle::OnNativeGameEvent (struct MMOGameEvent* evt)
{
	FVector2D scrSz = MMOFacade::GetScreenSize();
	INT scrW = (INT)scrSz.X;
	INT scrH = (INT)scrSz.Y;

	switch(evt->GetEventType())
	{
	case GameEvent_MatineeSubtitle:
		{
			MMOGameEvent_MatineeSubtitle* e = (MMOGameEvent_MatineeSubtitle*)evt;
			switch(e->SubtitleEventType)
			{
			case MMOGameEvent_MatineeSubtitle::EMSET_Show:
				{
					eventCallUCShow(e->ShowSubtitle ? TRUE : FALSE, scrW, scrH);
					debugf(TEXT("************** Show Matinee Subtitle:%d"), (INT)e->ShowSubtitle);
				}
				break;

			case MMOGameEvent_MatineeSubtitle::EMSET_UpdateSubtitle:
				{
					eventCallUCUpdateSubtitle(e->Subtitle);
					debugf(TEXT("************** Update Matinee Subtitle:%s"), *e->Subtitle);
				}
				break;
			}
		}
		break;

	case GameEvent_LeaveGame:
		{
			eventCallUCShow(FALSE, scrW, scrH);
			debugf(TEXT("************** Update Matinee Subtitle:GameEvent_LeaveGame"));
		}
		break;
	}
}
