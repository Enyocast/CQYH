#ifndef __LOGINBASE_H__
#define __LOGINBASE_H__

#include "stdafx.h"
#include "MMOSingleton.h"

class LoginBase: public SingletonMeyers<LoginBase>
{
public:
	//INT		IsChinaJoy;
	INT		IsVersion2T;
public:
	INT		SelectRoleIndex;
	FString SelectedRoleName;

	INT		CreateRoleClass;
	INT		CreateRoleSex;
	FString CreateRoleName;
	FName	CreateShowName;
	INT     CreateRoleHairColor;
	INT		CreateRoleHairModel;
	INT		CreateRoleSkinColor;
	INT		CreateRoleFaceModel;

public:
	UBOOL	IsFromLogin;
	UBOOL   IsCreateOption;
private:
	class AMMOPlayer* MainPlayer;
	class AMMOPlayerController* PC;

	FRotator PlayerStartRotation;
	FVector  PlayerStartPostion;
	FVector  HiddenPostion;
	FVector  SelectCameraNormalPostion;

	class ASceneCapture2DActor* SelectionCapture;
	class ASceneCapture2DActor* CreationCapture;
	class ANPC* CreateShowCharacter;
	TArrayNoInit<class ANPC*> CreateShowActors;

			

public:
	LoginBase();
	virtual ~LoginBase();

	TArray<FString> GetLoginIPList();

	TArray<FString> GetLoginIPNameList();

	void GetIPSelected( const FString& serverName,FString& ip );

	INT GetLoginPort();

	void EnterSelectRole();
	void EnterCreateRole();
	void EnterCreateRoleAppearance();
	void UpdateCreateRole();

	void HideAllCreateShowActors();
	void SetHiddenInLogin( class AMMOActor* actor,UBOOL hiddden );

	void CreateListRoleIni();

	void SelectRole( INT id );

	void SetCreateApperance();

	void ResetApperance();

};

#endif