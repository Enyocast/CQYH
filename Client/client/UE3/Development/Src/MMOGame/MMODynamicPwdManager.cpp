#include "stdafx.h"
#include "MMODynamicPwdManager.h"
#include "MMOFacade.h"
#include "MMOGameClasses.h"
#include "CommonGameEvents.h"
#include "net/message_handler.h"
#include "UITextParser.h"
#include "client_option_def.h"
MMODynamicPwdManager::MMODynamicPwdManager()
{

}


MMODynamicPwdManager::~MMODynamicPwdManager()
{
}

void MMODynamicPwdManager::Init()
{

}

void MMODynamicPwdManager::NotifyShowDynamicPassword()
{
	if (CMessageHandler::GetInstance().GetClientOption() & CLIENT_OPTION_BIT_DYNAMIC_PASSWORD)
	{
		MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_DynamicPwd,TRUE, "");
	}
	
}

void MMODynamicPwdManager::OnNativeGameEvent(struct MMOGameEvent* evt)
{

}