#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUILevelUp)

void UMMOUILevelUp::PlayerLevelUp(INT NewLv)
{
	if(TipsText)
	{
		TipsText->SetText(FString::Printf(TEXT("%d"), NewLv));
	}
}