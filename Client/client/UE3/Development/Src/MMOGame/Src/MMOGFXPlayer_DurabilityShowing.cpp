#include "stdafx.h"
#include "MMOGameUIClasses.h"
//#include "MMOFacade.h"
#include "EquipSlotManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_DurabilityShowing)


void UMMOGFXPlayer_DurabilityShowing::ASHintDurabilityDetail( UGFxObject *mc )
{
	if( _DurabilityShowing == NULL ){
		return;
	}

	UMMOUITips *tipsPanel = (UMMOUITips*)MMOUI::FindUIPanelEx( MMOUI::GetUIManager()->Panel_DynamicUI_Tips );
	if( tipsPanel != NULL ){
		INT curTotalEnhanceLevel = EquipSlotManager::getSingleton().GetCurEnhanceHoleLv();
		tipsPanel->ShowTipsHTML( TFT_EquipDurability, mc );
	}
}

void UMMOGFXPlayer_DurabilityShowing::ASHideDurabilityDetail()
{
	MMOUI::GetUIManager()->delegateHideTips();
}

void UMMOGFXPlayer_DurabilityShowing::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_DurabilityShowing::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_DurabilityShowing);
}