#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOMsgButtonManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_MsgBall)



//===================================================================
void UMMOGFXPlayer_MsgBall::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_MsgBall::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_MsgBall);


	
}

void UMMOGFXPlayer_MsgBall::ASOnPanelClose(const FString& PanelName)
{
	//	MMOUI::GetUIManager()->ToggleShowPanelEx(MMOUI::GetUIManager()->Panel_Option_InGameMenu);
	//MMOUI::GetUIManager()->delegateShowInGameMenu();
}

//void UMMOGFXPlayer_MsgBall::OnDragDrop(class UGFxObject* SrcSlotMC,class UGFxObject* DestSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,BYTE DestSlotType,BYTE DestContainerID,INT DestSlotID)
//{
//	
//}

void UMMOGFXPlayer_MsgBall::UnInit()
{
	Super::UnInit();
	
}


void UMMOGFXPlayer_MsgBall::ASMsgButtonClick( INT type )
{
	MMOMsgButtonManager::getSingleton().ClickButton(type);
}

void UMMOGFXPlayer_MsgBall::ASMsgListClick( INT pos , INT type )
{
	MMOMsgButtonManager::getSingleton().ClickMsgLine( pos , type );
}