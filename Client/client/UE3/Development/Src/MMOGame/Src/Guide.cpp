#include "stdafx.h"
#include "MMOFacade.h"
#include "MMOGuideData.h"

IMPLEMENT_CLASS(UGuide)

void UGuide::GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values)
{
}

void UGuide::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

UBOOL UGuide::IsNeedArchetype()
{
	return false;
}

void UGuide::DataToExcel(TArray<FString>& Row)
{
}

void UGuide::ExportExcelHeaders(TArray<FString>& Header,TArray<FString>& DefaultValues)
{
}

void UGuide::ImportFromExcel(const TArray<FString>& Values)
{
}

void UGuide::InitDataToExcel()
{
}

INT UGuide::GetTemplateID() const
{
	return GuideId;
}

void UGuide::PostLoad()
{
	Super::PostLoad();
	
	GuideId = appAtoi(*(GetName()));

	if (Picture.Num() < MAX_PLAYER_CLASS_COUNT)
	{
		for (INT i = 0; i < MAX_PLAYER_CLASS_COUNT - Picture.Num(); ++ i)
		{
			FGuidePicture pic;
			pic.Picture = NULL;
			Picture.AddItem(pic);
		}
	}

	if (ItemReqNew.Num() < MAX_PLAYER_CLASS_COUNT)
	{
		for (INT i = 0; i < MAX_PLAYER_CLASS_COUNT - ItemReqNew.Num(); ++ i)
		{
			FGuideItem item;
			item.ItemId = 0;
			ItemReqNew.AddItem(item);
		}
	}

	if (SkillReq.Num() < MAX_PLAYER_CLASS_COUNT)
	{
		for (INT i = 0; i < MAX_PLAYER_CLASS_COUNT - SkillReq.Num(); ++ i)
		{
			FGuideSkill skill;
			skill.SkillId = 0;
			SkillReq.AddItem(skill);
		}
	}
}