#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include <time.h>

IMPLEMENT_CLASS(UMMOUIGuildInstructionPanel)

void UMMOUIGuildInstructionPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildInstructionPanel>(this, evts);
}

void UMMOUIGuildInstructionPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		eventCallSetWindowTitle(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.About")));
	}
}

void UMMOUIGuildInstructionPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
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

void UMMOUIGuildInstructionPanel::SetInstruction(const FString& key)
{
	FString content = TEXT("MMOGame.Instruction.");
	content += key;
	eventCallSetContent(MMOUI::ParseLocalizedPropertyPath(content));
}