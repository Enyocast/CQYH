#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIUnlockAOGString)

void UMMOUIUnlockAOGString::Init()
{
	Super::Init();

}

void UMMOUIUnlockAOGString::UnInit()
{
	Super::UnInit();
}

void UMMOUIUnlockAOGString::ASRenownUnlockAOGShowEnd()
{
	SetVisible(FALSE);
}