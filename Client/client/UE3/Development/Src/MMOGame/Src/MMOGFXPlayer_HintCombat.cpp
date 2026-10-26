#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_HintCombat)


void UMMOGFXPlayer_HintCombat::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_HintCombat::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_HintCombat);	

	MMOUI::GetUIManager()->SetUpdateBossQTEDelegate(FScriptDelegate(this, TEXT("UpdateBossQTE")));

}

void UMMOGFXPlayer_HintCombat::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm) ;
	MMOUI::GetUIManager()->SetUpdateBossQTEDelegate(nullDelgate);
}

void UMMOGFXPlayer_HintCombat::AsCloseBossQTEPanel()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_HintCombat_BossQTE,FALSE, "");
}
