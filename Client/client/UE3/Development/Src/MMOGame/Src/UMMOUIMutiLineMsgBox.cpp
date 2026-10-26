#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
//#include "MMOPowerManager.h"

IMPLEMENT_CLASS(UMMOUIMutiLineMsgBox)

//================================================================================================
void UMMOUIMutiLineMsgBox::PreOnShow(UBOOL show)
{
	Super::PreOnShow( show );

	if( IsInitialized == FALSE ){
		return;
	}

	//
	if( show ){
		FVector2D scrSz = MMOFacade::GetScreenSize();

		INT panelX = scrSz.X / 2;
		FLOAT curPosX;
		FLOAT curPosY;
		GetPosition( curPosX, curPosY );

		SetPosition( panelX - PanelHalfWidth, curPosY );

	}
	else{
	}
}
//========================================================================================
void UMMOUIMutiLineMsgBox::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL){
		return;
	}

//	switch(evt->GetEventType())
//	{
//	}
}
//===================================================================================================================================
void UMMOUIMutiLineMsgBox::ShowContent( INT boxType, const FString &titleText, const FString &contentText )
{
	UGFxObject *initData = GFXPlayer->CreateObject( TEXT("UI_EquipLevelUp.AS3.UpgradeResultData") );
	if( initData == NULL ){
		return;
	}
	initData->SetInt( TEXT("resultType"), boxType );
	initData->SetString( TEXT("messageTitle"), titleText );
	initData->SetString( TEXT("messageContent"), contentText );

	eventCallASSetPopUpBox( initData );

	Show( TRUE );
}
//===================================================================================================================================
void UMMOUIMutiLineMsgBox::Init()
{
	Super::Init();

	InitMc();
}

//
void UMMOUIMutiLineMsgBox::InitMc()
{
	PanelHalfWidth = eventGetWidth() / 2;
	PanelHalfHeight = eventGetHeight() / 2;
}
