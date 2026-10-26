#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOUIBuffPanel)

UBOOL UMMOUIBuffPanel::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
    return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace );
}

//====================================================================================
void UMMOUIBuffPanel::Init()
{
	Super::Init();

	MMOUI::GetUIManager()->SetAddBuffPanelDelegate(FScriptDelegate(this, TEXT("AddBuffPanel")));
	MMOUI::GetUIManager()->SetDeleteBuffPanelDelegate(FScriptDelegate(this, TEXT("DeleteBuffPanel")));
}
//==============================================================================================================
void UMMOUIBuffPanel::UnInit()
{
	Super::UnInit();

	MMOUI::GetUIManager()->SetAddBuffPanelDelegate(FScriptDelegate(EC_EventParm));
	MMOUI::GetUIManager()->SetDeleteBuffPanelDelegate(FScriptDelegate(EC_EventParm));
}
void UMMOUIBuffPanel::PostOnShow(UBOOL show)
{
	Super::PostOnShow(show);

	if(show)
	{
	}
	else
	{
	}
}