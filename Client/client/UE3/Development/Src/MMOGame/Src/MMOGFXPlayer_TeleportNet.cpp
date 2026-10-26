#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMapDataManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_TeleportNet)

//
void UMMOGFXPlayer_TeleportNet::ASToThisTeleportNode( INT destNodeID )
{
	FTeleportNodeObj *pCurShowNode = MMOMapDataManager::getSingleton().GetLastOpendNode();
	if( pCurShowNode == NULL ){
		return;
	}

	INT scrNodeID = pCurShowNode->ServerID;
	//
	if( scrNodeID == destNodeID ){
		return;
	}
	//check money
	INT nowMny = MMOFacade::getSingleton().GetMainPlayer()->GetMoney( pCurShowNode->NeedMnyType );
	if( pCurShowNode->NeedMoney > nowMny ){
		//not enough money
		MMOUI::GetUIManager()->delegateAddScreenMessage( MMOUI::ParseLocalizedPropertyPath( "MMOGame.TradeP2P.ERROR25"),MsgInfoType_Table,TEXT("MMOGame.TradeP2P.ERROR25") );
		return;
	}
	//
	_TeleportNet->Show( FALSE );
	//
	CMessageHandler::GetInstance().Send_TeleportToNetNodes( (UINT8)scrNodeID, (UINT8)destNodeID );
}

//test
void UMMOGFXPlayer_TeleportNet::TestToTeleportNode( INT srcNodeID, INT destNodeID )
{
	CMessageHandler::GetInstance().Send_TeleportToNetNodes( (UINT8)srcNodeID, (UINT8)destNodeID );
};


void UMMOGFXPlayer_TeleportNet::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_TeleportNet::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_TeleportNet);
}

void UMMOGFXPlayer_TeleportNet::UnInit()
{
	Super::UnInit();

}