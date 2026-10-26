#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "net/message_handler.h"
#include "MMOQuestManager.h"
#include "UITextParser.h"
#include "LinkManager.h"
#include "TeamManager.h"
#include "MMOMapDataManager.h"
#include "MMOMsgBoxManager.h"

IMPLEMENT_CLASS(UMMOUIQuestRewardPanel)

void UMMOUIQuestRewardPanel::Init()
{
	Super::Init();

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_Quest);
	EventAdapter = new TGameEventAdapter<UMMOUIQuestRewardPanel>(this, evts);

	_CurQuestId = INVALID_QUEST_ID;
}

void UMMOUIQuestRewardPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v)
	{
		AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
		if (mainPlayer)
		{
			UActorAttribute* attri = mainPlayer->ActorAttributes;
			if (attri && attri->LevelAttributes.Level < GENERATE_REWARD_QUEST_LEVEL)
			{
				FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.LevelLimit"));
				MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("MMOGame.RewardQuest.LevelLimit"));

				Show(FALSE);
				return;
			}
		}

		eventCallSetWindowTitle(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Quest.RewardQuest")));
		UpdateRewardQuestAvailableLimit();
		UpdateRewardQuestRefreshTime();
		UpdateRewardQuestDetail();
		UpdateRewardQuestList();

		MMOFacade::getSingleton().PlayUISound(TEXT("TaskSheet_Op"));
	}
	else
	{
		MMOFacade::getSingleton().PlayUISound(TEXT("TaskSheet_Cls"));
	}
}

void UMMOUIQuestRewardPanel::OnNativeGameEvent(struct MMOGameEvent* gameEvent)
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
	if (questEvent == NULL)
	{
		return;
	}

	switch(questEvent->EventType)
	{
	case MMOGameEvent_Quest::EQET_AcceptQuest:
	case MMOGameEvent_Quest::EQET_UpdateQuest:
	case MMOGameEvent_Quest::EQET_AbandonQuest:
	case MMOGameEvent_Quest::EQET_CompleteQuest:
	case MMOGameEvent_Quest::EQET_UpdateRewardQuestList:
		{
			UpdateRewardQuestList();
			UpdateRewardQuestDetail();
		}
		break;

	case MMOGameEvent_Quest::EQET_UpdateRewardQuestLimit:
		{
			UpdateRewardQuestAvailableLimit();
		}
		break;
	case MMOGameEvent_Quest::EQET_UpdateRewardQuestBrushTime:
		{
			UpdateRewardQuestRefreshTime();
		}
		break;
	case MMOGameEvent_Quest::EQET_ClearQuestDetail:
		{
			_CurQuestId = INVALID_QUEST_ID;
			UpdateRewardQuestDetail();
		}
		break;
	}
}

void UMMOUIQuestRewardPanel::ItemChange(INT ContainerID,INT SlotID)
{
	if (!IsVisible)
	{
		return;
	}
	UpdateRewardQuestList();
	UpdateRewardQuestDetail();
}

void UMMOUIQuestRewardPanel::ItemDelete(INT ContainerID, INT SlotID)
{
	if (!IsVisible)
	{
		return;
	}
	UpdateRewardQuestList();
	UpdateRewardQuestDetail();
}

void UMMOUIQuestRewardPanel::PlayerLevelChange( INT lastLv , INT newLv )
{
	if (!IsVisible)
	{
		return;
	}
	UpdateRewardQuestList();
	UpdateRewardQuestDetail();
}

void UMMOUIQuestRewardPanel::RefreshNowConfirm(UBOOL isAutoRefresh)
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeRefreshNow");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseRefreshNow");	

	FString text = TEXT("");
	if (isAutoRefresh)
	{
		text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.RefreshFiveStar")),
			*MMOUI::ParseLocalizedPropertyPath(TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_02")));
	} 
	else
	{
		text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.RefreshNow")), 
			*UITextParser::HTMLMoneyIconString(MONEYTYPE_02, REWARD_QUEST_BRUSH_COST));
	}
	RefreshNowConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, isAutoRefresh ? 1 : 0, funYes, funNo);
}

void UMMOUIQuestRewardPanel::CompleteAllConfirm()
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeCompleteAll");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseCompleteAll");	

	UINT32 canAcceptCount = 0;
	RewardQuestList questList = MMOQuestData::getSingleton().GetRewardQuestList();
	RewardQuestList::iterator iter = questList.begin();
	for (; iter != questList.end(); ++ iter)
	{
		const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(iter->QuestId);
		if (!quest)
		{
			continue;
		}

		if ((iter->QuestState == EQS_Available && MMOQuestData::getSingleton().IsQuestAvailable(iter->QuestId)) || iter->QuestState == EQS_Accept)
		{
			canAcceptCount ++;
		}
	}

	UINT32 canCompleteCount = MMOQuestData::getSingleton().GetRewardQuestAvailableLimit();

	FString text = TEXT("");
	if (canCompleteCount >= canAcceptCount)
	{
		text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.CompleteAll")),
			*UITextParser::HTMLMoneyIconString(MONEYTYPE_02, REWARD_QUEST_BUY_COMPLETE_ONSHOT_COST * canAcceptCount),
			canAcceptCount);
	}
	else
	{
		text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.CompleteAll")),
			*UITextParser::HTMLMoneyIconString(MONEYTYPE_02, REWARD_QUEST_BUY_COMPLETE_ONSHOT_COST * canCompleteCount),
			canCompleteCount);
	}

	CompleteAllConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, 0, funYes, funNo);
}

void UMMOUIQuestRewardPanel::UpgradeLimitConfirm()
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeUpgradeLimit");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseUpgradeLimit");	

	FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.UpgradeAcceptLimit")), 
		*UITextParser::HTMLMoneyIconString(MONEYTYPE_02, REWARD_QUEST_BUY_COMPLETE_ONETIME_COST));
	UpgradeLimitConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, 0, funYes, funNo);
}

void UMMOUIQuestRewardPanel::AbandonLowConfirm(INT questId)
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeAbandonLow");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseAbandonLow");	

	FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.GiveUpQuest"));
	AbandonLowConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, questId, funYes, funNo);

}

void UMMOUIQuestRewardPanel::AbandonHighConfirm(INT questId)
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("AgreeAbandonHigh");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("RefuseAbandonHigh");	

	FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.GiveUpQuest"));
	AbandonHighConfirmBox = MMOMsgBoxManager::getSingleton().AddMessageBox(text, questId, funYes, funNo);

}

void UMMOUIQuestRewardPanel::AgreeRefreshNow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if (mainPlayer)
	{
		if (mainPlayer->GetMoney(MONEYTYPE_02) < REWARD_QUEST_BRUSH_COST)
		{
			FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.NoMoneyForRefresh")), 
				*MMOUI::ParseLocalizedPropertyPath(TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_02")));
			MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_02"));
			return;
		}
	}

	INT isAutoRefresh = mc->GetInt(TEXT("iteminfoid"));
	MMOQuestManager::getSingleton().RefreshRewardQuestList(isAutoRefresh == 1);
	RefreshNowConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::RefuseRefreshNow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	RefreshNowConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::AgreeUpgradeLimit(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	CMessageHandler::GetInstance().Send_UpgradeAwardQuestLimit(1);
	UpgradeLimitConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::RefuseUpgradeLimit(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	UpgradeLimitConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::AgreeCompleteAll(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}
	
	AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if (mainPlayer)
	{
		if (mainPlayer->GetMoney(MONEYTYPE_02) < REWARD_QUEST_BUY_COMPLETE_ONSHOT_COST)
		{
			FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.RewardQuest.NoMoneyForCompleteAll")), 
				*MMOUI::ParseLocalizedPropertyPath(TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_02")));
			MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("Properties.EMONEY_TYPE.E_MONEYTYPE_02"));
			return;
		}
	}

	CMessageHandler::GetInstance().Send_CompleteAllRewardQuest();
	CompleteAllConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::RefuseCompleteAll(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	CompleteAllConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::AgreeAbandonLow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	INT questId = mc->GetInt(TEXT("iteminfoid"));
	CMessageHandler::GetInstance().Send_AbandonQuest(questId);
	AbandonLowConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::RefuseAbandonLow(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	AbandonLowConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::AgreeAbandonHigh(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	INT questId = mc->GetInt(TEXT("iteminfoid"));
	CMessageHandler::GetInstance().Send_AbandonQuest(questId);
	AbandonHighConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::RefuseAbandonHigh(UGFxObject *mc)
{
	if (!mc)
	{
		return;
	}

	AbandonHighConfirmBox = NULL;
}

void UMMOUIQuestRewardPanel::ShowCompleteQuest(UBOOL visible)
{
	_ShowCompleteQuest = visible;

	MMOGameEvent_Quest evt(MMOGameEvent_Quest::EQET_UpdateRewardQuestList);
	MMOUI::PostGameEvent(&evt);
}

void UMMOUIQuestRewardPanel::UpdateRewardQuestList()
{
	UGFxObject* objectArray = GFXPlayer->CreateArray();
	if (!objectArray)
	{
		return;
	}

	int index = 0;
	RewardQuestList questList = MMOQuestData::getSingleton().GetRewardQuestList();
	RewardQuestList::iterator iter = questList.begin();
	for (; iter != questList.end(); ++ iter)
	{
		const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(iter->QuestId);
		if (!quest)
		{
			continue;
		}

		if (iter->QuestState == EQS_Completed && !_ShowCompleteQuest)
		{
			continue;
		}

		UGFxObject* object = GFXPlayer->CreateObject(TEXT("ActionScript3.Quest.QuestData"));
		if (object)
		{
			FString questName = quest->QuestName;
			switch (quest->StarLevel)
			{
			case 1:
				questName = FString::Printf(TEXT("<font color='#DBDBDB'>%s</font>"), *questName);
				break;
			case 2:
				questName = FString::Printf(TEXT("<font color='#1EFF00'>%s</font>"), *questName);
				break;
			case 3:
				questName = FString::Printf(TEXT("<font color='#71D5FF'>%s</font>"), *questName);
				break;
			case 4:
				questName = FString::Printf(TEXT("<font color='#A335EE'>%s</font>"), *questName);
				break;
			case 5:
				questName = FString::Printf(TEXT("<font color='#FF8000'>%s</font>"), *questName);
				break;
			}

			object->SetString(TEXT("label"), questName);
			object->SetInt(TEXT("index"), index);
			object->SetInt(TEXT("type"), 0);
			object->SetInt(TEXT("deepth"), 0);
			object->SetBool(TEXT("visible"), true);

			object->SetInt(TEXT("quest_type"), E_qt_Reward);
			object->SetInt(TEXT("quest_id"), quest->QuestTempID);
			object->SetString(TEXT("quest_caption"), questName);
			object->SetInt(TEXT("quest_stars"), quest->StarLevel);
			object->SetBool(TEXT("quest_is_available"), iter->QuestState == EQS_Available && MMOQuestData::getSingleton().IsQuestAvailable(quest->QuestTempID));
			object->SetBool(TEXT("quest_is_accepted"), iter->QuestState == EQS_Accept);
			UBOOL isQuestCompassable = MMOQuestData::getSingleton().IsQuestCompassable(quest->GetTemplateID());
			object->SetBool(TEXT("quest_is_compassable"), isQuestCompassable);
			object->SetBool(TEXT("quest_is_completed"), iter->QuestState == EQS_Completed);
			
			objectArray->SetElementObject(index, object);
			++ index;
		}
	}

	eventCallUpdateRewardQuestList(objectArray);
}

void UMMOUIQuestRewardPanel::UpdateRewardQuestDetail()
{
	if (_CurQuestId == INVALID_QUEST_ID)
	{
		eventCallUpdateRewardQuestDetail(NULL);
		return;
	}

	const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(_CurQuestId);
	if (!quest)
	{
		eventCallUpdateRewardQuestDetail(NULL);
		return;
	}	

	UGFxObject* object = MMOQuestManager::getSingleton().GetQuestDetailData(_CurQuestId, GFXPlayer, FALSE);
	eventCallUpdateRewardQuestDetail(object);
}

void UMMOUIQuestRewardPanel::UpdateRewardQuestAvailableLimit()
{
	int completeCount = MMOQuestData::getSingleton().GetRewardQuestAvailableLimit();
	eventCallUpdateRewardQuestAvailableLimit(completeCount);
}

void UMMOUIQuestRewardPanel::UpdateRewardQuestRefreshTime()
{
	int brushLeftTime = MMOQuestManager::getSingleton().GetRewardQuestRefreshTime();
	
	int hour = 0;
	int min = 0;
	int sec = 0;

	if (brushLeftTime > 0)
	{
		hour = brushLeftTime / 3600;
		min = brushLeftTime % 3600 / 60;
		sec = brushLeftTime % 3600 % 60;
	}

	eventCallUpdateRewardQuestRefreshTime(hour, min, sec);
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIQuestRewardPanel::ASUpdateRewardQuestDetail(INT id)
{
	_CurQuestId = id;
	UpdateRewardQuestDetail();
}

void UMMOUIQuestRewardPanel::ASUpgradeAvailableLimit()
{
	Show(TRUE);
}

void UMMOUIQuestRewardPanel::ASRefreshRewardQuestList(UBOOL autoRefresh)
{
	RefreshNowConfirm(autoRefresh);
}

void UMMOUIQuestRewardPanel::ASCompleteAllRewardQuest()
{
	CompleteAllConfirm();
}

void UMMOUIQuestRewardPanel::ASShowCompletedRewardQuest(UBOOL show)
{
	ShowCompleteQuest(show);
}

void UMMOUIQuestRewardPanel::ASRefreshTopLevelRewardQuest(UBOOL refresh)
{
}

void UMMOUIQuestRewardPanel::ASAcceptRewardQuest(INT id)
{
	MMOQuestManager::getSingleton().AcceptQuest(id, FALSE, 0);
}

void UMMOUIQuestRewardPanel::ASAbandonRewardQuest(INT id)
{
	const UQuest* quest = MMOQuestData::getSingleton().GetQuestData(id);
	if (quest && quest->QuestType == E_qt_Reward)
	{
		if (quest->StarLevel < 4)
		{
			AbandonLowConfirm(id);
		}
		else
		{
			AbandonHighConfirm(id);
		}
	}
}