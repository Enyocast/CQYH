#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "net/message_handler.h"
#include "UILayout.h"
#include "UITextParser.h"
#include "WebHtmlManager.h"


IMPLEMENT_CLASS(UMMOUIDynamicPassword)

void UMMOUIDynamicPassword::Init()
{
	Super::Init();

	
}

void UMMOUIDynamicPassword::UnInit()
{
	Super::UnInit();
}

void UMMOUIDynamicPassword::NativeInitOnce()
{
	FString msg  = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.DynamicPwd.Msg"));
	eventCallUCSetData(msg);
}

void UMMOUIDynamicPassword::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	
}

void UMMOUIDynamicPassword::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	
}


void UMMOUIDynamicPassword::ASDynamicPwdData(class UGFxObject* dt)
{
	FString pwd = dt->GetString("key0")+dt->GetString("key1")+dt->GetString("key2")+dt->GetString("key3")+
				  dt->GetString("key4")+dt->GetString("key5")+dt->GetString("key6");
	CMessageHandler::GetInstance().Send_DynamicPassword(pwd);

	this->SetVisible(FALSE);
}

void UMMOUIDynamicPassword::ASLinkKeeperCallBack()
{
	WebHtmlManager::getSingleton().OpenGManagerByIE();
}

void UMMOUIDynamicPassword::ASLinkHelpCallBack()
{
	WebHtmlManager::getSingleton().OpenDynamicHelpByIE();
}
