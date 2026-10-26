#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "UITextParser.h"

IMPLEMENT_CLASS(UMMOUIKillRecordPanel)


void UMMOUIKillRecordPanel::Init()
{
	Super::Init();

}

void UMMOUIKillRecordPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if(v)
	{
		FVector2D scrSz = MMOFacade::GetScreenSize();
		SetPosition((scrSz.X - eventGetWidth())/2,(scrSz.Y*1.5 - eventGetHeight())/2);
	}
}