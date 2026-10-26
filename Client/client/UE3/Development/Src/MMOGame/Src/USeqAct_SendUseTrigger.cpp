#include "stdafx.h"
#include "net/message_handler.h"

IMPLEMENT_CLASS(USeqAct_SendUseTrigger);

void USeqAct_SendUseTrigger::SendUseTrigger(const TScriptInterface<class IIServerTrigger>& Trigger,INT TriggerID,INT TriggerType)
{
	//CMessageHandler::GetInstance().Send_UserTrigger(TriggerID);
}