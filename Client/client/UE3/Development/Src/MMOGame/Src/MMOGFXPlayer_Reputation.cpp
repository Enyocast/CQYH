#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_Reputation);


void UMMOGFXPlayer_Reputation::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Reputation::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Reputation);	
	
	MMOUI::GetUIManager()->SetUpdateReputationDataDelegate(FScriptDelegate(this, TEXT("UpdateReputationData")));
	MMOUI::GetUIManager()->SetRefreshReputationSelectedDelegate(FScriptDelegate(this, TEXT("RefreshReputationSelected")));
	//MMOUI::GetUIManager()->SetRefreshEquipedMountDelegate(FScriptDelegate(this, TEXT("RefreshEquipedMount")));

}

void UMMOGFXPlayer_Reputation::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	MMOUI::GetUIManager()->SetUpdateReputationDataDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetRefreshReputationSelectedDelegate(nullDelgate);
	//MMOUI::GetUIManager()->SetRefreshEquipedMountDelegate(nullDelgate);
}

//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Reputation::PostAdvance ( FLOAT DeltaTime )
{
	UGFxMoviePlayer::PostAdvance(DeltaTime);
}



