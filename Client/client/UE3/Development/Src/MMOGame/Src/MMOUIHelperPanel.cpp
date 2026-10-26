#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOAchievementManager.h"
//#include "MMOScreenMsgMgr.h"
#include "ScreenMsgQueue.h"
#include <time.h>
#include "MMOHelperData.h"

IMPLEMENT_CLASS(UMMOUIHelperPanel)

void UMMOUIHelperPanel::Init()
{
	Super::Init();
}

void UMMOUIHelperPanel::PostOnShow(UBOOL v)
{
	Super::PostOnShow(v);

	if (v)
	{
		UpdateHelperPos();
	}
}

void UMMOUIHelperPanel::UpdateHelperPos()
{
	UMMOUIBase* panel = MMOUI::FindUIPanelEx(FName(*_TargetPanelName));
	if (panel && panel->IsVisible)
	{
		FVector2D panelPos;
		panel->GetPosition(panelPos.X, panelPos.Y);

		FVector2D panelSize;
		panelSize.X = panel->eventGetWidth();
		panelSize.Y = panel->eventGetHeight();

		FVector2D newPos;
		newPos.X = panelPos.X + panelSize.X / 2.0f - eventGetWidth() / 2.0f;
		newPos.Y = panelPos.Y + panelSize.Y / 4.0f;
		SetPosition(newPos.X, newPos.Y);
	}
}

void UMMOUIHelperPanel::UpdateHelperList(INT base, INT sub)
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	INT objectIndex = 0;
	
	INT baseClass = 0;
	UBOOL findLoc = FALSE;
	FString baseClassName = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Class")) + 
		appItoa(baseClass) + FString(TEXT("_")) + appItoa(0), 
		findLoc);

	while (findLoc)
	{
		UGFxObject* baseClassObject = GFXPlayer->CreateObject(TEXT("Object"));
		baseClassObject->SetString(TEXT("label"), baseClassName);
		baseClassObject->SetInt(TEXT("index"), objectIndex);
		baseClassObject->SetInt(TEXT("type"), 1);
		baseClassObject->SetInt(TEXT("deepth"), 0);
		baseClassObject->SetBool(TEXT("visible"), true);
		baseClassObject->SetInt(TEXT("baseClass"), baseClass);
		baseClassObject->SetInt(TEXT("subClass"), 0);
		baseClassObject->SetString(TEXT("helper_class"), baseClassName);
		dataProvider->SetElementObject(objectIndex, baseClassObject);
		objectIndex ++;

		INT subClass = 1;
		FString subClassName = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Class")) + 
			appItoa(baseClass) + FString(TEXT("_")) + appItoa(subClass),
			findLoc);

		while (findLoc)
		{
			UGFxObject* subClassObject = GFXPlayer->CreateObject(TEXT("Object"));

			subClassObject->SetString(TEXT("label"), subClassName);
			subClassObject->SetInt(TEXT("index"), objectIndex);
			subClassObject->SetInt(TEXT("type"), 1);
			subClassObject->SetInt(TEXT("deepth"), 1);
			subClassObject->SetBool(TEXT("visible"), true);
			subClassObject->SetInt(TEXT("baseClass"), baseClass);
			subClassObject->SetInt(TEXT("subClass"), subClass);
			subClassObject->SetString(TEXT("helper_title"), subClassName);
			dataProvider->SetElementObject(objectIndex, subClassObject);
			objectIndex ++;

			subClass ++;
			subClassName = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Class")) + 
				appItoa(baseClass) + FString(TEXT("_")) + appItoa(subClass),
				findLoc);
		}

		baseClass ++;
		baseClassName = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Class")) + 
			appItoa(baseClass) + FString(TEXT("_")) + appItoa(0), 
			findLoc);
	}

	eventCallUpdateHelperList(dataProvider);
}

void UMMOUIHelperPanel::UpdateHelperDetail(INT base, INT sub)
{
	UGFxObject* dataProvider = GFXPlayer->CreateArray();
	INT objectIndex = 0;

	FString title = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Class")) + 
		appItoa(base) + FString(TEXT("_")) + appItoa(sub));

	FString desc = MMOUI::ParseLocalizedPropertyPath(FString(TEXT("MMOGame.Helper.Desc")) + 
		appItoa(base) + FString(TEXT("_")) + appItoa(sub));

	UGFxObject* object = GFXPlayer->CreateObject(TEXT("Object"));
	if (object)
	{
		object->SetString(TEXT("helper_title"), title);
		object->SetString(TEXT("helper_desc"), desc);
		eventCallUpdateHelperDetail(object);
	}

}

void UMMOUIHelperPanel::ShowHelperPanel(const FString& panelName)
{
	HelperData data;
	if (MMOHelperData::getSingleton().GetHelperData(panelName, data))
	{
		_TargetPanelName = panelName;

		Show(TRUE);

		//UpdateHelperList(data.BaseClass, data.SubClass);
		UpdateHelperDetail(data.BaseClass, data.SubClass);
	}
}

//////////////////////////////////////////////////////////////////////////

void UMMOUIHelperPanel::ASUpdateHelperDetail(INT baseClass, INT subClass)
{
	UpdateHelperDetail(baseClass, subClass);
}
