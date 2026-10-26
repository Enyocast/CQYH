#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "attribute_def.h"
#include "ClientActionConditionCheck.h"
#include "LoginBase.h"
#include "MMOMsgBoxManager.h"
#include "WinDrv.h"
#include "MMOLoginManager.h"

IMPLEMENT_CLASS(UMMOUICreateRolePanel);


void UMMOUICreateRolePanel::Init()
{
	Super::Init();
}
void UMMOUICreateRolePanel::PostOnShow(UBOOL v)
{
	UBOOL bVisibleLast = GetVisible();
	Super::PostOnShow(v);
	if(v==TRUE){
		if (LoginBase::getSingleton().IsCreateOption)
		{
			LoginBase::getSingleton().EnterCreateRoleAppearance();
			eventCallShowCreateModule(CM_CREATE_APPERANCE);
			UGFxObject* obj = MMOLoginManager::getSingleton().CreateMeshItemListDataObject(GFXPlayer,LoginBase::getSingleton().CreateRoleClass,LoginBase::getSingleton().CreateRoleSex);
			if (obj)
			{
				eventCallUCSetAppearanceData(obj);
			}
			ASResetAll();
			//MMO::ActiveKismetRemoteEvent(TEXT("3-LOOP"));

			MMO::ActiveKismetRemoteEvent(TEXT("Select_Loop"));

		}
		else
		{

			LoginBase::getSingleton().EnterCreateRole();
			
			eventCallSetRoleName(LoginBase::getSingleton().CreateRoleName);

			eventCallShowCreateModule(CM_CREATE);
			eventCallSetCreateInfo(LoginBase::getSingleton().CreateRoleSex, LoginBase::getSingleton().CreateRoleClass);
			eventCallEffectshow();

			//if(LoginBase::getSingleton().IsChinaJoy){
			//	eventCallSetRoleEnable(2, FALSE);
			//	eventCallSetRoleEnable(3, FALSE);
			//	eventCallSetCreateSexGrpEx(LoginBase::getSingleton().CreateRoleSex, TRUE);
			//}
			//else
			//{
			//	eventCallSetRoleEnable(2, TRUE);
			//	eventCallSetRoleEnable(3, TRUE);
			//}
			DispatchChangeEvent(LoginBase::getSingleton().CreateRoleClass ,LoginBase::getSingleton().CreateRoleSex,LoginBase::getSingleton().CreateRoleClass ,LoginBase::getSingleton().CreateRoleSex);
			
			CreateRoleChanged(LoginBase::getSingleton().CreateRoleClass);
		}
	}
}

void UMMOUICreateRolePanel::ASRoleMove_Create(INT offX,INT offY)
{
	RotActor = MMOFacade::getSingleton().GetMainActor();
	if(RotActor){
		FRotator newRot;
		newRot = RotActor->Rotation;
		newRot.Yaw -= offX*100;
		RotActor->SetDesiredRotation(newRot, FALSE, TRUE, -1.f, TRUE);
		RotActor->SetRotation(newRot);
	}
}

//----------------------------------------------------------------------------
void UMMOUICreateRolePanel::CreateRole(const FString&  createName)
{
	if (!CheckCreateRoleNameInput(createName))
	{
		return;
	}

	if( !CheckRoleName( createName ) )
	{
		return;
	}

	//注意 本地0为错误代码 但是服务器从0开始
	LoginBase::getSingleton().CreateRoleName = createName;
	CMessageHandler::GetInstance().Send_CreateRole(*createName,
		LoginBase::getSingleton().CreateRoleClass,
		LoginBase::getSingleton().CreateRoleSex,
		LoginBase::getSingleton().CreateRoleHairModel,
		LoginBase::getSingleton().CreateRoleHairColor,
		LoginBase::getSingleton().CreateRoleFaceModel,
		LoginBase::getSingleton().CreateRoleSkinColor
		);
}

void UMMOUICreateRolePanel::DispatchChangeEvent(INT career,INT sex, INT careerLast,INT sexLast)
{
	FString EventName = TEXT("");
	switch(career)
	{
	case EPCT_PlayerClassB:
		EventName = EventName+TEXT("MA-");
		break;
	case EPCT_PlayerClassC:
		EventName = EventName+TEXT("AG-");
		break;
	case EPCT_PlayerClassD:
		EventName = EventName+TEXT("AR-");
		break;
	case EPCT_PlayerClassE:
		EventName = EventName+TEXT("TA-");
		break;
	default:
		EventName = EventName+TEXT("WA-");
		break;
	}

	if(sex==1)//男
	{
		EventName = EventName+TEXT("M");
	}
	else
	{
		EventName = EventName+TEXT("F");
	}

	MMO::ActiveKismetRemoteEvent(TEXT("StopAll"));
	MMO::ActiveKismetRemoteEvent(FName(*EventName));

}

void UMMOUICreateRolePanel::CreateSexChanged(INT sex)
{
	if(LoginBase::getSingleton().IsVersion2T)
	{
		return;
	}

	//AS： sex 0男 1女
	AMMOPlayerController* PC	= MMOFacade::getSingleton().GetMainController();
	AMMOPlayer* MainPlayer		= MMOFacade::getSingleton().GetMainPlayer();
	if( PC ==NULL || MainPlayer==NULL )
		return;

	INT lastSex = LoginBase::getSingleton().CreateRoleSex;
	LoginBase::getSingleton().CreateRoleSex = sex + 1 ;

	LoginBase::getSingleton().UpdateCreateRole();

	INT career = LoginBase::getSingleton().CreateRoleClass;
	DispatchChangeEvent(career ,LoginBase::getSingleton().CreateRoleSex, career,lastSex);
}

void UMMOUICreateRolePanel::CreateRoleChanged(INT career)
{	

	AMMOPlayerController* PC	= MMOFacade::getSingleton().GetMainController();
	AMMOPlayer* MainPlayer		= MMOFacade::getSingleton().GetMainPlayer();
	if( PC ==NULL || MainPlayer==NULL )
		return;
	
	INT lastCareer = LoginBase::getSingleton().CreateRoleClass;
	LoginBase::getSingleton().CreateRoleClass = career;

	INT sexLast = LoginBase::getSingleton().CreateRoleSex;
	if(LoginBase::getSingleton().IsVersion2T)
	{
		if(career==0)LoginBase::getSingleton().CreateRoleSex = 1;
		if(career==1)LoginBase::getSingleton().CreateRoleSex = 2;
		if(career==2)return;
		if(career==3)return;
		if(career==4)LoginBase::getSingleton().CreateRoleSex = 2;
		eventCallSetCreateSexGrpEx(LoginBase::getSingleton().CreateRoleSex, TRUE);
		//eventCallSetCreateInfo(LoginBase::getSingleton().CreateRoleSex, LoginBase::getSingleton().CreateRoleClass);
	}

	LoginBase::getSingleton().UpdateCreateRole();

	INT sex = LoginBase::getSingleton().CreateRoleSex;
	DispatchChangeEvent(career ,sex, lastCareer ,sexLast);
}

UBOOL UMMOUICreateRolePanel::CheckRoleName( const FString& createName )
{
	INT CreateRoleClass = LoginBase::getSingleton().CreateRoleClass;
	INT CreateRoleSex = LoginBase::getSingleton().CreateRoleSex;


	if( createName.Len() <= 0 ) 
	{
		FScriptDelegate funcNULL(EC_EventParm);
		MMOMsgBoxManager::getSingleton().AddModalMessageBox( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.MsgBox.text11")), 0 , funcNULL , funcNULL ,FALSE);
		return FALSE;
	}

    if(  createName.Len() > 16  ) 
    {
		FScriptDelegate funcNULL(EC_EventParm);
		MMOMsgBoxManager::getSingleton().AddModalMessageBox( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.MsgBox.text5")), 0 , funcNULL , funcNULL ,FALSE);
        return FALSE;
    }

    if( CreateRoleClass < 0 )
    {
        //ActiveMessageBox(12,true,false);
		FScriptDelegate funcNULL(EC_EventParm);
		MMOMsgBoxManager::getSingleton().AddModalMessageBox( MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.MsgBox.text12")), 0 , funcNULL , funcNULL ,FALSE);
        return FALSE;
    }

	bool isOpened =  true;
	
	if(LoginBase::getSingleton().IsVersion2T){
		switch( CreateRoleClass )
		{
		case EPCT_PlayerClassA:
			if( EGT_Female == CreateRoleSex )
			{
				isOpened =  false;
			}
			break;
		case EPCT_PlayerClassB:
			if( EGT_Male == CreateRoleSex )
			{
				isOpened =  false;
			}
			break;
		case EPCT_PlayerClassC:
				isOpened =  false;
			break;
		case EPCT_PlayerClassD:
				isOpened =  false;
			break;
		case EPCT_PlayerClassE:
			if( EGT_Male == CreateRoleSex )
			{
				isOpened =  false;
			}
			break;
		}
	}

    if( !isOpened )
    {
        FScriptDelegate funcNULL(EC_EventParm);
        MMOMsgBoxManager::getSingleton().AddModalMessageBox(
            MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Login.NotOpened") ),0,funcNULL,funcNULL,FALSE);
        return FALSE;
    }

    if( MMOUI::HasCensoredWord(createName) )
    {
        FScriptDelegate funcNULL(EC_EventParm);
        MMOMsgBoxManager::getSingleton().AddModalMessageBox(
            MMOUI::ParseLocalizedPropertyPath( TEXT("MMOErrorInfo.CensoredWord.HasCensoredWord") ),0,funcNULL,funcNULL,FALSE);
        return FALSE;
    }

    return TRUE;
}

void UMMOUICreateRolePanel::CreateTurnBtnUp()
{

}
void UMMOUICreateRolePanel::CreateTurnRightPress()
{

}
void UMMOUICreateRolePanel::CreateTurnLeftPress()
{

}

void UMMOUICreateRolePanel::ASRequestReturnRoleList()
{
	
}

void UMMOUICreateRolePanel::ASReturnCreatePanel()
{
	LoginBase::getSingleton().IsCreateOption = FALSE;
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Login_Create, TRUE, "");
}

void UMMOUICreateRolePanel::ASOnCreateRoleNameInput( const FString& roleName )
{
    CheckCreateRoleNameInput(roleName);
}

BOOL UMMOUICreateRolePanel::CheckCreateRoleNameInput(const FString& roleName)
{
	/*
    *hemu@snda
    *检测是否有非英文输入法打开
    *如不判断输入法打开时，Input最后一个汉字位时打入词组，
    *会过早调用SetCreateRoleName，清掉最后一个拼音,带掉最后一个汉字
    */
    if( GEngine && GEngine->Client )
    {
        UWindowsClient* Client = CastChecked<UWindowsClient>(GEngine->Client);
        for( INT ViewportIndex=0; ViewportIndex<Client->Viewports.Num(); ViewportIndex++ )
        {
            FWindowsViewport* Viewport = Client->Viewports(ViewportIndex);
            if( Viewport && Viewport->GetCurrentIMESize() > 0 )
            {
                return FALSE;
            }
        }
    }

	INT Count = 0;
	INT Size = 0;
	INT res = CheckName( roleName ,Count,Size);
	//if((Size>=20 || Count>=14) && roleName.Len()>LoginBase::getSingleton().CreateRoleName.Len())
	if (roleName !=LoginBase::getSingleton().CreateRoleName)
	{
		//陈凯新策略，中文字母全部按8个来限制
		UGFxObject* createMc = GetObject( TEXT("input_mc") );
		if(createMc)
		{
			UGFxObject* input = createMc->GetObject( TEXT("input_Name") );
			if(input)
			{
				input->SetInt( TEXT("maxChars") , 8 /*- nChineseNum*/);
				if(Count <= 8 )
				{
					LoginBase::getSingleton().CreateRoleName = roleName;
				}
				else
				{
					eventCallSetRoleName(LoginBase::getSingleton().CreateRoleName);
				}
			}
		}


#if 0   //去除此段
		//策划陈凯要求英文和数字的长度最大是12，  一个汉字算1.5个字符进行长度限制 大写字符按汉字处理

		INT nChineseNum = (INT)(Size - Count)*0.5;

		UGFxObject* createMc = GetObject( TEXT("input_mc") );
		if(createMc)
		{
			UGFxObject* input = createMc->GetObject( TEXT("input_Name") );
			if(input)
			{
				if(nChineseNum%2 == 0)
					nChineseNum = (INT)nChineseNum*0.505;
				else
					nChineseNum = (INT)nChineseNum*0.505 + 1;

				input->SetInt( TEXT("maxChars") , 8 /*- nChineseNum*/);

				if(Count <= 8 - nChineseNum)
				{
					LoginBase::getSingleton().CreateRoleName = roleName;
				}
				else
				{
					eventCallSetRoleName(LoginBase::getSingleton().CreateRoleName);
				}
			}
		}
#endif		

		//eventCallSetRoleName(LoginBase::getSingleton().CreateRoleName);
		//TArray<struct FASValue> Arguments;
		//FASValue ASValue(EC_EventParm);
		//ASValue.S= CreateRoleName;
		//ASValue.Type = AS_String;
		//Arguments.AddItem(ASValue);
		//if( GetVariableObject("root.CreateRole_mc") )
		//	GetVariableObject("root.CreateRole_mc")->Invoke("SetCreateRoleName", Arguments );

		/*if(roleName.Len() == LoginBase::getSingleton().CreateRoleName.Len()+1){
			FScriptDelegate func(EC_EventParm);
			func.Object = NULL;
			func.FunctionName = "";
			MMOMsgBoxManager::getSingleton().AddModalMessageBox(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MsgBox.text5") ),0,func,func,FALSE);
		}*/
	}

	res = CheckName( LoginBase::getSingleton().CreateRoleName ,Count,Size);
	if(res>0)
	{	
		eventCallUpdateInput(TRUE, TEXT(""));
		//eventCallUpdateInput(TRUE, MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Login.Script1")));
		 return TRUE;
	}
	else
	{
		eventCallUpdateInput(FALSE, MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Login.Script2")));
		 return FALSE;

	}

	if(roleName.Len()==0)
	{
		eventCallUpdateInput(FALSE, TEXT(""));
		 return FALSE;
	}
	return FALSE;
}
/*
	方便创建角色时判断 大写字母和汉字统一处理
*/
INT UMMOUICreateRolePanel::CheckName( const FString& InputName, INT &Count ,INT &Size)
{
	Count = 0;
	Size  = 0;
	static TCHAR   szRoleName[256];
	wcscpy_s(szRoleName, _countof(szRoleName), *InputName) ;
	size_t Length = InputName.Len();

	INT res = 1;
	for(size_t i=0;i<Length;i++)
	{
		TCHAR c = szRoleName[i];
		if(c>=TCHAR('0')&&c<=TCHAR('9'))
		{
			Count++;
			Size++;
		}
		else if(c>=TCHAR('a')&&c<=TCHAR('z'))
		{
			Count++;
			Size++;
		}
		
		else if(c>=TCHAR('A')&&c<=TCHAR('Z'))
		{
			//方便创建角色时判断 大写字母和汉字统一处理
			/*Count++;
			Size++;*/
			Count++;
			Size+=3;
		}
		else if(c>=0x4e00 && c<=0x9fa5)
		{
			Count++;
			Size+=3;
		}

		//新增，可以增加火星文
		else{
			Count++;
			Size+=2;
		}

		if(MMOUI::HasSpecialSymbol(InputName))
		{
			res = 0;
		}
		//else{
		//	res = 0;
		//}
	}

	return res;
}

void UMMOUICreateRolePanel::ASGetAppearanceData()
{
	LoginBase::getSingleton().IsCreateOption = TRUE;
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Login_Create, FALSE, "");

	INT nClass = LoginBase::getSingleton().CreateRoleClass;
	INT nSex   = LoginBase::getSingleton().CreateRoleSex;
	if(nClass==EPCT_PlayerClassA&&nSex==1)MMO::ActiveKismetRemoteEvent(TEXT("WA-M-END"));
	else if(nClass==EPCT_PlayerClassA&&nSex==2)MMO::ActiveKismetRemoteEvent(TEXT("WA-F-END"));
	else if(nClass==EPCT_PlayerClassB&&nSex==1)MMO::ActiveKismetRemoteEvent(TEXT("MA-M-END"));
	else if(nClass==EPCT_PlayerClassB&&nSex==2)MMO::ActiveKismetRemoteEvent(TEXT("MA-F-END"));
	else if(nClass==EPCT_PlayerClassC&&nSex==1)MMO::ActiveKismetRemoteEvent(TEXT("AG-M-END"));
	else if(nClass==EPCT_PlayerClassC&&nSex==2)MMO::ActiveKismetRemoteEvent(TEXT("AG-F-END"));
	else if(nClass==EPCT_PlayerClassD&&nSex==1)MMO::ActiveKismetRemoteEvent(TEXT("AR-M-END"));
	else if(nClass==EPCT_PlayerClassD&&nSex==2)MMO::ActiveKismetRemoteEvent(TEXT("AR-F-END"));
	else if(nClass==EPCT_PlayerClassE&&nSex==1)MMO::ActiveKismetRemoteEvent(TEXT("TA-M-END"));
	else if(nClass==EPCT_PlayerClassE&&nSex==2)MMO::ActiveKismetRemoteEvent(TEXT("TA-F-END"));
}

void UMMOUICreateRolePanel::ASCallUpdateAppearance(int type, int id)
{
	MMOLoginManager::getSingleton().UpdateAppearance(type, id, LoginBase::getSingleton().CreateRoleClass, LoginBase::getSingleton().CreateRoleSex);

}

void UMMOUICreateRolePanel::ASResetAll()
{
	ASCallUpdateAppearance(CMT_HAIR_MODEL,0);
	ASCallUpdateAppearance(CMT_HAIR_COLOR,0);
	ASCallUpdateAppearance(CMT_FACE_MODEL,0);
	ASCallUpdateAppearance(CMT_SKIN_COLOR,0);
}

void UMMOUICreateRolePanel::ASRandomCreate(const TArray<class UGFxObject*>& randomResult)
{
	PlayerAppearanceData data;

	data.Class = LoginBase::getSingleton().CreateRoleClass;
	data.Sex = LoginBase::getSingleton().CreateRoleSex;

	for(int i = 0; i < randomResult.Num(); i++)
	{
		INT type = randomResult(i)->GetInt(TEXT("type"));
		INT id = randomResult(i)->GetInt(TEXT("id"));

		switch(type)
		{
		case CMT_HAIR_MODEL:
			{
				LoginBase::getSingleton().CreateRoleHairModel = data.HairModel = id;
			}
			break;
		case CMT_HAIR_COLOR:
			{
				LoginBase::getSingleton().CreateRoleHairColor = data.HairColor = id;
			}
			break;
		case CMT_FACE_MODEL:
			{
				LoginBase::getSingleton().CreateRoleFaceModel = data.FaceModel = id;
			}
			break;
		case CMT_SKIN_COLOR:
			{
				LoginBase::getSingleton().CreateRoleSkinColor = data.SkinColor = id;
			}
			break;
		}
	}

	MMOLoginManager::getSingleton().UpdateAllAppearance(data);
}


void UMMOUICreateRolePanel::ASCheckFirstOnCreate(UGFxObject *mc)
{
	if(mc)
	{
		AMMOPlayerController* PC	= MMOFacade::getSingleton().GetMainController();
		if(PC && PC->RoleList.Num()==0 ){
			mc->SetBool("IsFirst",TRUE);
		}
		else
		{
			mc->SetBool("IsFirst",FALSE);
		}
	}	
}

void UMMOUICreateRolePanel::CreateRoleCancel()
{
	LoginBase::getSingleton().IsCreateOption = FALSE;
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Login_Create, FALSE, "");
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Login_Select, TRUE, "");
}

//---------------------------------------------------------------------------------------------------------------
void UMMOUICreateRolePanel::EnterScene()
{
}
void UMMOUICreateRolePanel::ChangeScene()
{
}
void UMMOUICreateRolePanel::EnterLogin()
{
}
