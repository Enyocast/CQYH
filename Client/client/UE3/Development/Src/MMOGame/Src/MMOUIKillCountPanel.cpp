#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "UITextParser.h"

IMPLEMENT_CLASS(UMMOUIKillCountPanel)


void UMMOUIKillCountPanel::Init()
{
	Super::Init();
 
}

void UMMOUIKillCountPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if(v)
	{
		FVector2D scrSz = MMOFacade::GetScreenSize();
		SetPosition((scrSz.X*0.5- eventGetWidth())*0.5 + 80,(scrSz.Y*0.5 - eventGetHeight())*0.5 - 80);
	}
}