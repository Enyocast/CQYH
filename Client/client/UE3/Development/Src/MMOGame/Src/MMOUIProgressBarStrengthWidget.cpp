#include "stdafx.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMMOUIProgressBarStrengthWidget)

void UMMOUIProgressBarStrengthWidget::Init()
{
	Super::Init();

}

void UMMOUIProgressBarStrengthWidget::UnInit()
{
	Super::UnInit();
}

UBOOL UMMOUIProgressBarStrengthWidget::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	if( IsVisible )
	{
		if(strHoverControllerName==TEXT("_StrengthBar"))
		{
			return TRUE;
		}
	}
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

void UMMOUIProgressBarStrengthWidget::ShowProgressBarStrength(INT time, INT max)
{
	eventOpen(time, max);
}
void UMMOUIProgressBarStrengthWidget::CloseProgressBarStrength(INT closeType)
{
	eventClose(closeType);
}