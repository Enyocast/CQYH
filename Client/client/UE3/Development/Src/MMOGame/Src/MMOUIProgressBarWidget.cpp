#include "stdafx.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMMOUIProgressBarWidget)

void UMMOUIProgressBarWidget::Init()
{
	Super::Init();
}

void UMMOUIProgressBarWidget::UnInit()
{
	Super::UnInit();
}

UBOOL UMMOUIProgressBarWidget::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	if( IsVisible )
	{
		if(strHoverControllerName==TEXT("_ProgressBar"))
		{
			return TRUE;
		}
	}
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

void UMMOUIProgressBarWidget::ShowProgressBar(INT countDownTime,const FString& strTitle, INT type )
{
	eventOpen(countDownTime,strTitle,type);
}
void UMMOUIProgressBarWidget::CloseProgressBar(INT closeType)
{
	eventClose(closeType);
}