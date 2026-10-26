#ifndef _UQUEST_H_
#define _UQUEST_H_

public:
	virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	virtual void PostLoad();

#if WITH_EDITOR
	virtual FString GetDetailedDescription( INT InIndex )
	{
		switch( InIndex )
		{
		case 0:
			return FString::Printf(TEXT("%d"), GetTemplateID());
			break;

		case 1:
			return FString::Printf(TEXT("%s"), *QuestName);
			break;

		case 2:
			return FString::Printf(TEXT("%s"), StartNPCNew ? *StartNPCNew->GetDisplayName() : TEXT(""));
			break;

		case 3:
			return FString::Printf(TEXT("%s"), *QuestDescript);
			break;

		case 4:
			return FString::Printf(TEXT("%s"), CanShare ? TEXT("Share") : TEXT(""));
			break;
		}

		return TEXT("");
	}
#endif

	UNPCTemplate* GetStartNpc();
	UNPCTemplate* GetFinishNpc();
	UNPCTemplate* GetCheckKillNpc(int index);
	UNPCTemplate* GetAutoStartDialogHeadIcon();
	UNPCTemplate* GetAutoFinishDialogHeadIcon();

	UItem* GetLimitItem(int index);
	UItem* GetCheckItem(int index);
	UItem* GetAwardItem(int index);
	UItem* GetSelectableAwardItem(int index);
	UItem* GetStartItem();
	UItem* GetFinishItem();

	USoundCue* GetQuestPageSoundAccept(int index);
	USoundCue* GetQuestPageSoundSubmit(int index);
	USoundCue* GetQuestSoundAccept();
	USoundCue* GetQuestSoundAccepted();
	USoundCue* GetQuestSoundUnderway();
	USoundCue* GetQuestSoundSubmit();
	USoundCue* GetQuestSoundComplete();

	UTexture2D* GetQuestSoundAcceptedIcon();
	UTexture2D* GetQuestSoundCompleteIcon();

#endif