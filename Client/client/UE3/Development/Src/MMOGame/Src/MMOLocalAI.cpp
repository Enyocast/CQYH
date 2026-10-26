

#include "stdafx.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOLocalAI)

 
UMMOLocalAI* UMMOLocalAI::Instance()
{
    return Cast<UMMOLocalAI>(UMMOLocalAI::StaticClass()->GetDefaultObject());
}


void UMMOLocalAI::Run()
{
    if (!AIWorking)
        return;
}

void UMMOLocalAI::OnNetClose()
{
}

void UMMOLocalAI::OnLogoEnd()
{
    AIWorking = FALSE;
    if (UserName.IsEmpty())
        return;
    
	if (MMO::GetCurrentGameState() != EGameState_Login)
        return;

    UMMOGameState_Login* login_st = Cast<UMMOGameState_Login>(MMO::FindGameStateObject(EGameState_Login));
    if (!login_st)
        return;
    //login_st->LoginMovie->GetVariableObject("root.LoginPanel_mc.LoginField_mc.textInput_Name.textField")->SetText(UserName);
    //login_st->LoginMovie->GetVariableObject("root.LoginPanel_mc.LoginField_mc.textInput_Pwd.textField")->SetText(Password);
    //login_st->LoginMovie->eventLoginGame_cpp();
}

void UMMOLocalAI::OnLoginResult(UBOOL ret)
{
    if (!AIWorking)
        return;
    if (ret)
    {
        if (NewPlayer)
        {
        }
        else
        {
        }
    }
    else
    {
        AIWorking = FALSE;
    }
}

void UMMOLocalAI::OnCreateRole()
{
    if (!AIWorking)
        return;
}

void UMMOLocalAI::OnMapLoaded()
{
    if (!AIWorking)
        return;
}

void UMMOLocalAI::OnTaskState()
{
    if (!AIWorking)
        return;
}