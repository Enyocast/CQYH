#include "stdafx.h"

IMPLEMENT_CLASS(UBuff);

UBOOL UBuff::IsNeedArchetype()
{
	return false;
}
//------------------------------------------------------------------------
void UBuff::DataToExcel(TArray<FString>& Row)
{
	//Row.AddItem(FString::Printf( TEXT("%d"), TemplateID));
	//Row.AddItem(BuffName.ToString());
	//Row.AddItem(FString::Printf( TEXT("%d"), Level));
	//Row.AddItem(FString::Printf( TEXT("%d"), Category));
	//Row.AddItem(FString::Printf( TEXT("%d"), EffectType));
	//Row.AddItem(FString::Printf( TEXT("%d"), Duration));
	//Row.AddItem(FString::Printf( TEXT("%d"), interval));
	//Row.AddItem(FString::Printf( TEXT("%d"), InitStackCount));
	//Row.AddItem(FString::Printf( TEXT("%d"), MaxStackCount));
	//
	//Row.AddItem(FString::Printf( TEXT("%d"), LevelParam1));
	//Row.AddItem(FString::Printf( TEXT("%d"), LevelParam2));
	//Row.AddItem(FString::Printf( TEXT("%d"), LevelParam3));
	//Row.AddItem(FString::Printf( TEXT("%d"), LevelParam4));

	//int nOnAppendID = 0;
	//int nOnTimeupID = 0;
	//int nOnDispelID = 0;
	//int nOnRemoveID = 0;

	//if(OnAppend)
	//	nOnAppendID = OnAppend->Id;
	//if(OnTimeup)
	//	nOnTimeupID = OnTimeup->Id;
	//if(OnDispel)
	//	nOnDispelID = OnDispel->Id;
	//if(OnRemove)
	//	nOnRemoveID = OnRemove->Id;

	//Row.AddItem(FString::Printf( TEXT("%d"), nOnAppendID));
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnTimeupID));
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnDispelID));
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnRemoveID));

}
//------------------------------------------------------------------------
void UBuff::ExportExcelHeaders(TArray<FString>& Header,TArray<FString>& DefaultValues)
{
}
void UBuff::InitDataToExcel()
{
	OnAppendID = 0;
	OnTimeupID = 0;
	OnDispelID = 0;
	OnRemoveID = 0;
	OnEx1ID = 0;
	OnEx2ID = 0;
	BeforeStackID = 0;
	AfterStackID = 0;

	if(OnAppend)
		OnAppendID = OnAppend->Id;
	if(OnTimeup)
		OnTimeupID = OnTimeup->Id;
	if(OnDispel)
		OnDispelID = OnDispel->Id;
	if(OnRemove)
		OnRemoveID = OnRemove->Id;
	if(OnEx1)
		OnEx1ID = OnEx1->Id;
	if(OnEx2)
		OnEx2ID = OnEx2->Id;
	if(BeforeStack)
		BeforeStackID = BeforeStack->Id;
	if(AfterStack)
		AfterStackID = AfterStack->Id;
}

//------------------------------------------------------------------------
void UBuff::ImportFromExcel(const TArray<FString>& Values)
{

}
//------------------------------------------------------------------------
int UBuff::GetTemplateID() const
{
	return TemplateID;
}
//-------------------------------------------------------------------------
FString UBuff::GetBuffIconName()
{
	FString FullName;

	UObject* Obj = DisplayIcon;
	if( Obj )
	{
		FullName = FString(Obj->GetPureName().ToString() );
		while( Obj && Obj->GetOuter() )
		{
			FullName = FString(Obj->GetOuter()->GetPureName().ToString()) + TEXT(".") + FullName;
			Obj= Obj->GetOuter();
		}
	}
	//int i = 0;
	//FString str = FString( DisplayIcon->GetOutermost() ->GetOut());// ->TextureFileCacheName.ToString() );
	return FullName;
}

