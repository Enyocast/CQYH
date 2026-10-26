#include "stdafx.h"
#include "net/message_handler.h"

IMPLEMENT_CLASS(USeqAct_SendClientAreaEventComplete);

void USeqAct_SendClientAreaEventComplete::SendAreaEventComplete(const TScriptInterface<class IIServerArea>& Trigger,INT AreaID)
{
	//CMessageHandler::GetInstance().Send_ClientAreaEventComplete(AreaID);
}