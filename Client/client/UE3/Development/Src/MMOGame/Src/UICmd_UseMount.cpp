#include "stdafx.h"
#include "MMOFacade.h"
#include "net\message_handler.h"

IMPLEMENT_CLASS(UUICmd_UseMount);

void UUICmd_UseMount::Use()
{

	AMMOPlayer* pMainPlayer = MMOFacade::getSingleton().GetMainPlayer();
	if(pMainPlayer && pMainPlayer->ActorAttributes){
		if(CmdID == pMainPlayer->ActorAttributes->MountID)
		{
			CMessageHandler::GetInstance().Send_EquipMount(0);
		}
		else
		{
			CMessageHandler::GetInstance().Send_EquipMount(CmdID);
		}
	}
	MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( FALSE, CmdID,  SlotID);		
	
}

void UUICmd_UseMount::NativeRelease()
{

	MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( TRUE, CmdID,  SlotID);
	
}