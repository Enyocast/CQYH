#include "stdafx.h"
#include "MMOFacade.h"
#include "net\message_handler.h"

IMPLEMENT_CLASS(UUICmd_UseItem);

void UUICmd_UseItem::Use()
{
	INT conID = -1;
	INT slotID = -1;

	MMOFacade::getSingleton().FindFirstItemPos( CmdID , &conID , &slotID );
	

	if( conID >= 0 && slotID >= 0 )
	{
		MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( FALSE, CmdID,  SlotID);
		CMessageHandler::GetInstance().Send_UseItem( conID , slotID , CmdID );
	}
}

void UUICmd_UseItem::NativeRelease()
{
	INT conID = -1;
	INT slotID = -1;

	MMOFacade::getSingleton().FindFirstItemPos( CmdID , &conID , &slotID );

	if( conID >= 0 && slotID >= 0 )
	{
		MMOUI::GetUIManager()->delegateUpdateSkillBarKeyDown( TRUE, CmdID,  SlotID);
	}
}