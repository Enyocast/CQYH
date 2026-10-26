#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOStats.h"
#include "MasterStudentManager.h"

IMPLEMENT_CLASS(UMMOUIMasterInvite)
void UMMOUIMasterInvite::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_PlayerBaseInfo);
	evts.AddItem(GameEvent_MasterStudent);
	EventAdapter = new TGameEventAdapter<UMMOUIMasterInvite>(this, evts);
	roleId = 0;
}

void UMMOUIMasterInvite::UnInit()
{
	Super::UnInit();
}

void UMMOUIMasterInvite::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v)
	{
		UpdateMasterInfo();
	}
}

void UMMOUIMasterInvite::OnNativeGameEvent(struct MMOGameEvent* evt)
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
			case EMST_HelloStudent:
				{
					UpdateMasterInfo();
					//roleId = pEvt_MasterStudent->ID;
				}
				break;
			case EMST_MasterEnterGame:
				{
					BOOL show = MasterStudentManager::getSingleton().GetIsShowTwitterMasterInfo();
					if (show)
					{
						MasterStudentManager::getSingleton().AddHelloStudentBtnBall();
					}
					else
					{
						this->SetVisible(FALSE);
					}
					

				}
				break;
			}
		}
		break;
	}
}

void UMMOUIMasterInvite::UpdateMasterInfo(BOOL v)
{
	UGFxObject * data = GFXPlayer->CreateObject("Object");

	if (data)
	{
		TwitterInfo master = MasterStudentManager::getSingleton().GetMasterTwitterInfo();

		data->SetInt(TEXT("Id"),master.roleID);	
		//data->SetInt(TEXT("num"),master.masterExp);
		INT exp = MasterStudentManager::getSingleton().GetMasterExpByRatio(master.masterExp);
		data->SetInt(TEXT("num"),exp);

		data->SetInt(TEXT("Level"),master.level);
		roleId = master.roleID;

		PlayerBaseInfo *playerInfo = MMOFacade::getSingleton().RequestPlayerBaseInfo(master.roleID );
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
			data->SetString(TEXT("RoleName"),MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Guild.UnKnowRole")));
			data->SetString(TEXT("ClassName"), MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.UnKnowClass")));
		}

		eventCallUCUpdateHelloMasterInfo(data);
	}
	

	//if(v)
		//eventCallUCUpdateHelloMasterInfo(data);
	//else
		//eventCallUCUpdateHelloMasterName(data);
	
}

void UMMOUIMasterInvite::ASMasterInviteCheckBox(UBOOL v)
{
	//UINT8 twitter = v ? 1 : 0;
	CMessageHandler::GetInstance().Send_Twitter(0);
	HideUI();
	
}
void UMMOUIMasterInvite::ASMasterInviteSummit(int id)
{
	
	CMessageHandler::GetInstance().Send_AgreeMasterdApply(id);
	HideUI();
	
}

void UMMOUIMasterInvite::ASOnMasterInvitePanelClose(int id)
{
	CMessageHandler::GetInstance().Send_Ignore(id);
	HideUI();
}
void UMMOUIMasterInvite::HideUI()
{
	roleId = 0;
	this->SetVisible(FALSE);
	MasterStudentManager::getSingleton().SetIsShowTwitterMasterInfo(FALSE);
}

