#include "..\stdafx.h"
#include "net/message_handler.h"
#include "..\MMOFacade.h"

void AMMOLoadingTrigger::RegisterToFacade()
{
	MMOFacade::getSingleton().RegisterTrigger(TScriptInterface<IIServerTrigger>(this));
}

void AMMOLoadingTrigger::OpenTriggerReq()
{
	//CMessageHandler::GetInstance().Send_UserTrigger(TriggerID);
}

void AMMOLoadingTrigger::OpenTriggerCompleteReq()
{
	//CMessageHandler::GetInstance().Send_UserTrigger(TriggerID);
}
