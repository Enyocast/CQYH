#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOQuestManager.h"
#include "UITextParser.h"

IMPLEMENT_CLASS(UMMOUIQuestRewardBuyTimesPanel)

void UMMOUIQuestRewardBuyTimesPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Quest);
	EventAdapter = new TGameEventAdapter<UMMOUIQuestRewardBuyTimesPanel>(this, evts);
}

void UMMOUIQuestRewardBuyTimesPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
	if (v)
	{
		UINT32 leftTimes = MAX_REWARD_QUEST_DAILY_COMPLETE_TIME - MMOQuestData::getSingleton().GetRewardQuestCostCount();
		eventCallUpdateRewardQuestBuyLeftTimes(leftTimes);
	}
}

void UMMOUIQuestRewardBuyTimesPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
{
	if (!IsVisible)
	{
		return;
	}

	if (gameEvent->GetEventType() != GameEvent_Quest)
	{
		return;
	}

	MMOGameEvent_Quest* questEvent = (MMOGameEvent_Quest*)gameEvent;
	if (!questEvent)
	{
		return;
	}
}

void UMMOUIQuestRewardBuyTimesPanel::UpdateRewardQuestBuyTimesConsume(INT times)
{
	UINT32 totalMoney = 0;
	UINT32 alreadyHasTimes = MMOQuestData::getSingleton().GetRewardQuestCostCount();
	for (UINT i = alreadyHasTimes + 1; i <= alreadyHasTimes + times; ++ i)
	{
		totalMoney += MMOQuestData::getSingleton().GetRewardQuestCost(i);
	}
	FString consume = UITextParser::HTMLMoneyIconString(MONEYTYPE_02, totalMoney);
	eventCallUpdateRewardQuestBuyTimesConsume(consume);
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIQuestRewardBuyTimesPanel::ASUpdateRewardQuestBuyTimes(INT times)
{
	UpdateRewardQuestBuyTimesConsume(times);
}

void UMMOUIQuestRewardBuyTimesPanel::ASBuyTimes(INT times)
{
	CMessageHandler::GetInstance().Send_UpgradeAwardQuestLimit(times);
}
