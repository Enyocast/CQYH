#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_Mount);


void UMMOGFXPlayer_Mount::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Mount::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Mount);	

	MMOUI::GetUIManager()->SetRefreshMountDelegate(FScriptDelegate(this, TEXT("RefreshMount")));
	MMOUI::GetUIManager()->SetRefreshEquipedMountDelegate(FScriptDelegate(this, TEXT("RefreshEquipedMount")));

}

void UMMOGFXPlayer_Mount::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	MMOUI::GetUIManager()->SetRefreshMountDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetRefreshEquipedMountDelegate(nullDelgate);
}


//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Mount::PostAdvance ( FLOAT DeltaTime )
{
	UGFxMoviePlayer::PostAdvance(DeltaTime);
}

////------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_Mount::ASEquipMount(INT MountID)
{
	CMessageHandler::GetInstance().Send_EquipMount(MountID);
}

void UMMOGFXPlayer_Mount::ASUnEquipMount()
{
	CMessageHandler::GetInstance().Send_EquipMount(0);
}




