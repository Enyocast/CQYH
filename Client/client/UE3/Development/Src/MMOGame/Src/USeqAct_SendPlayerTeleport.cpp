#include "stdafx.h"
//#include "net/message_handler.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(USeqAct_SendPlayerTeleport);


void USeqAct_SendPlayerTeleport::SendPlayerMove()
{
	AMMOPlayerController* pc = MMOFacade::getSingleton().GetMainController();
	pc->SendRequest_MoveTo(pc->Pawn->Location,TRUE);
}