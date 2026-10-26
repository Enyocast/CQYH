#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGuildManager.h"
#include <time.h>


IMPLEMENT_CLASS(UMMOUIGuildWarEndPanel)

void UMMOUIGuildWarEndPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Guild);
	EventAdapter = new TGameEventAdapter<UMMOUIGuildWarEndPanel>(this, evts);
}

void UMMOUIGuildWarEndPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		UpdateGuildWarEndList();
	}
}

void UMMOUIGuildWarEndPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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
	case MMOGameEvent_Guild::EGET_UpdateGuildWarEndTime:
		{
			UpdateGuildWarEndTime();
		}
		break;
	}
}

void UMMOUIGuildWarEndPanel::UpdateGuildWarEndList()
{
	UGFxObject* dataArray = GFXPlayer->CreateArray();
	if (!dataArray)
	{
		return;
	}
	
	GuildWarResultList guildWarResultList = MMOGuildData::getSingleton().GetGuildWarResultList();
	GuildWarResultList::iterator iter = guildWarResultList.begin();
	INT index = 0;
	for (; iter != guildWarResultList.end(); ++ iter)
	{
		UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
		object->SetString(TEXT("label"), TEXT(""));
		object->SetInt(TEXT("index"), index);
		object->SetInt(TEXT("type"), 0);
		object->SetInt(TEXT("deepth"), 0);
		object->SetBool(TEXT("visible"), true);

		object->SetInt(TEXT("member_id"), iter->dwRoleID);

		GuildFullMemberInfo memberInfo;
		MMOGuildData::getSingleton().GetGuildFullMemberInfo(iter->dwRoleID, memberInfo);
		object->SetString(TEXT("member_name"), memberInfo.Name);
		object->SetString(TEXT("member_level"), appItoa(memberInfo.Level));

		FString jobName = TEXT("");
		MMOGuildData::getSingleton().GetJobName(memberInfo.Job, jobName);
		object->SetString(TEXT("member_job"), jobName);

		object->SetInt(TEXT("member_dead_times"), iter->nDealCount);
		object->SetInt(TEXT("member_kill_count"), iter->nKillNum);
		object->SetInt(TEXT("member_achieve"), iter->nSalary);

		dataArray->SetElementObject(index, object);
		index ++;
	}

	eventCallUpdateGuildWarEndList(dataArray);
}

void UMMOUIGuildWarEndPanel::UpdateGuildWarEndTime()
{
	FString time = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.WarEndTime")),
		MMOGuildManager::getSingleton().GetGuildWarEndTime());
	eventCallUpdateGuildWarEndTime(time);
}
