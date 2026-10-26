#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "attribute_def.h"
#include "ClientActionConditionCheck.h"


IMPLEMENT_CLASS(UMMOUIBossQTE)


void UMMOUIBossQTE::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if(MMOFacade::getSingleton().GetMainController()){
		MMOFacade::getSingleton().GetMainController()->bIsInBossQTE = v;
	}
}

//===============================================================================================================
//===============================================================================================================
UBOOL UMMOUIBossQTE::SkipCaptureInputKey(const FString& key,BYTE eIE,const FString& strHoverControllerName,FVector2D ClickPosInMovieSpace)
{
	return Super::SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

void UMMOUIBossQTE::AsCloseBossQTEPanel()
{
	Show( FALSE );
	//MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_HintCombat_BossQTE,FALSE, "");
}

//===============================================================================================================
//===============================================================================================================