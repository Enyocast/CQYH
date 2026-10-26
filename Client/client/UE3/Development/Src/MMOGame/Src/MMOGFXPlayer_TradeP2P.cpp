#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_TradeP2P)

void UMMOGFXPlayer_TradeP2P::PostAdvance(float DeltaTime)
{
	Super::PostAdvance(DeltaTime);
	//
	if( _TradeP2P ){
		_TradeP2P->UpdateCondition();
	}
}


void UMMOGFXPlayer_TradeP2P::Init()
{
	Super::Init();
	
	check(FALSE && "UMMOGFXPlayer_TradeP2P::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_TradeP2P);
}

void UMMOGFXPlayer_TradeP2P::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	MMOUI::GetUIManager()->SetApplyDoTradeDelegate( nullDelgate );
}