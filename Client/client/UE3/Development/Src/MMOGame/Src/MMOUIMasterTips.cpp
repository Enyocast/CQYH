#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOStats.h"
#include "MasterStudentManager.h"

IMPLEMENT_CLASS(UMMOUIMasterTips)
	void UMMOUIMasterTips::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_PlayerBaseInfo);
	evts.AddItem(GameEvent_MasterStudent);
	EventAdapter = new TGameEventAdapter<UMMOUIMasterTips>(this, evts);

	roleId = 0;

}

void UMMOUIMasterTips::UnInit()
{
	Super::UnInit();
}

void UMMOUIMasterTips::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);
}

void UMMOUIMasterTips::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

	switch(evt->GetEventType())
	{
	case GameEvent_PlayerBaseInfo:
		{
			MMOGameEvent_PlayerBaseInfo* infoEvt = (MMOGameEvent_PlayerBaseInfo*)evt;
			if(infoEvt == NULL){
				return;
			}
			if (roleId == infoEvt->_RoldID)
			{
				UpdateMasterInfo(FALSE);
			}
			
		}
		break;
	case GameEvent_MasterStudent:
		{
			MMOGameEvent_MasterStudent* pEvt_MasterStudent = (MMOGameEvent_MasterStudent*)evt;
			if(NULL == pEvt_MasterStudent)
			{
				break;
			}

			switch(pEvt_MasterStudent->EventType)
			{
				case EMST_HelloTeacher:
					{
						UpdateMasterInfo();
						//roleId = pEvt_MasterStudent->ID;
					}
					break;
				case EMST_MasterEnterGame:
					{
						BOOL show = MasterStudentManager::getSingleton().GetIsShowTwitterStudentInfo();
						this->SetVisible(show);
						if (show)
						{
							UpdateMasterInfo();
						}
						
					}
					break;
			}
		}
		break;
	}
}

void UMMOUIMasterTips::UpdateMasterInfo(BOOL v)
{
	UGFxObject * data = GFXPlayer->CreateObject("Object");

	if (data)
	{
		TwitterInfo student = MasterStudentManager::getSingleton().GetStudentTwitterInfo();

		roleId = student.roleID;
		data->SetInt(TEXT("Id"),student.roleID);
		data->SetInt(TEXT("Level"),student.level);

		PlayerBaseInfo *playerInfo = MMOFacade::getSingleton().RequestPlayerBaseInfo(student.roleID );
		if (playerInfo)
		{
			data->SetString(TEXT("RoleName"),playerInfo->_RoleName);

			FString sProfession = MMOUI::ParseLocalizedPropertyPath( FString("MMOGame.School.SchoolName") + FString::Printf(TEXT("%d"),playerInfo->_RoleClass));
			data->SetString(TEXT("ClassName"),sProfession);

			FString icon = MMOFacade::getSingleton().GetPlayerIcon(playerInfo->_RoleClass,playerInfo->_Sex);
			data->SetString(TEXT("HeadIcon"),icon);
		}
		else
		{
			FString name = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.UnKnowRole"));
			data->SetString(TEXT("RoleName"),name);
			data->SetString(TEXT("ClassName"),"");
		}

		if (v)
			eventCallUCUpdatePlayerInfo(data);
		else
			eventCallUCUpdatePlayerName(data);


	}
	
}

void UMMOUIMasterTips::ASRectivedMaster(int id)
{
	CMessageHandler::GetInstance().Send_SubmitApplyToStudent(id,1);
	MasterStudentManager::getSingleton().UpdateSTudentAppleState(id);
	HideUI();
	
}
void UMMOUIMasterTips::ASHideStudentTwitter(int id)
{
	CMessageHandler::GetInstance().Send_Ignore(id);
	MasterStudentManager::getSingleton().ClearStudentTwitterInfo(id);
	HideUI();
}

void UMMOUIMasterTips::HideUI()
{
	roleId = 0;
	this->SetVisible(FALSE);
	MasterStudentManager::getSingleton().SetIsShowTwitterStudentInfo(FALSE);
	
}
