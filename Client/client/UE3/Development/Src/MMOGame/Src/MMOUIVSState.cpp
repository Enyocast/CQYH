#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOGameEvent.h"
#include "MMOFacade.h"
#include "MMOArenaManager.h"

IMPLEMENT_CLASS(UMMOUIVSState)

//========================================================================================================================================
void UMMOUIVSState::PreOnShow( UBOOL show )
{
	Super::PreOnShow( show );

	if( show ){
		UpdatePanel();
	}
	else{
		//ResetUI();
	}
}
//========================================================================================================================================
void UMMOUIVSState::OnNativeGameEvent( struct MMOGameEvent* evt )
{
	if( evt == NULL ){
		return;
	}

	switch( evt->GetEventType() )
	{
	case GameEvent_VSNotify:
		{
			if( IsVisible != TRUE ){
				break;
			}

			MMOGameEvent_OneInt *ntfEvt = (MMOGameEvent_OneInt*)evt;
			switch( ntfEvt->IntData )
			{
			case EVSNotify_SideUsedRecovery:
				{
					UpdateVSPkStateInfo();
				}
				break;
			case EVSNotify_SideInfo:
				{
					UpdateVSPkSideStaticInfo();
				}
				break;
			}
		}
		break;
	}
}
//========================================================================================================================================
void UMMOUIVSState::UpdatePanel()
{
	UpdateVSPkSideStaticInfo();

	UpdateVSPkStateInfo();
}
//========================================================================================================================================
void UMMOUIVSState::UpdateVSPkStateInfo()
{
	MMOArenaManager &arenaMgr = MMOArenaManager::getSingleton();
	UGFxObject* dataProvider = NULL;
	INT loopAddedCnt = 0;
	INT myVSSide = arenaMgr.GetMyVSSide();
	for( INT i = EVSSide_1; i < EVSSide_Total; ++i ){
		if( dataProvider == NULL ){
			dataProvider = GFXPlayer->CreateArray();
		}

		if( dataProvider != NULL ){
			INT usedRecovery = ( myVSSide == i ? arenaMgr.GetVSSideUsedRecovery( i ) : -1 );
			UGFxObject* itemSingleObj = GFXPlayer->CreateObject( TEXT("UI_VSResult.AS3.VSPkSideInfo") );
			if( itemSingleObj != NULL ){
				itemSingleObj->SetInt( TEXT("usedRecovery"), usedRecovery );
				dataProvider->SetElementObject( loopAddedCnt, itemSingleObj );
				++loopAddedCnt;
			}
		}
		eventCallAsSetVSSideInfo( dataProvider );
	}
}
//========================================================================================================================================
void UMMOUIVSState::UpdateVSPkSideStaticInfo()
{
	MMOArenaManager &arenaMgr = MMOArenaManager::getSingleton();
	for( INT i = EVSSide_1; i <= EVSSide_2; ++i ){
		VSPKInfo &sidePkInfo = arenaMgr.GetVSSidePkInfo( i );
		////
		//if( sidePkInfo._Name.IsEmpty() ){
		//	AMMOActor* actor = MMOFacade::getSingleton().GetCharacter( sidePkInfo._PerInfo._ActorID );
		//	if( actor != NULL ){
		//		sidePkInfo._Name = actor->GetActorName();
		//	}
		//}
		//
		eventCallAsSetVSSideName( i, sidePkInfo._Name );
	}
}
//========================================================================================================================================
void UMMOUIVSState::Init()
{
	Super::Init();

	//SetTitleName();

	//
	check( EventAdapter == NULL );
	TArray<EGameEvent> evts;
	evts.AddItem( GameEvent_VSNotify );
	EventAdapter = new TGameEventAdapter<UMMOUIVSState>( this, evts );
}
//========================================================================================================================================
void UMMOUIVSState::SetTitleName()
{
	TArray<struct FASValue> asFunArgs;
	FASValue asTitleName(EC_EventParm);
	asTitleName.Type = AS_String;

	asTitleName.S = TEXT("");

	asFunArgs.AddItem( asTitleName );
	this->Invoke( TEXT("SetWindowTitle"), asFunArgs );
}