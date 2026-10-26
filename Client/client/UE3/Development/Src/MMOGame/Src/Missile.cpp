#include "stdafx.h"

IMPLEMENT_CLASS(UMissile);

UBOOL UMissile::IsNeedArchetype()
{
	return false;
}
//------------------------------------------------------------------------
void UMissile::DataToExcel(TArray<FString>& Row)
{
	//Row.AddItem(FString::Printf( TEXT("%d"), Id));
	//Row.AddItem(FString::Printf( TEXT("%d"), LockType));
	//Row.AddItem(FString::Printf( TEXT("%d"), MoveType));
	//Row.AddItem(FString::Printf( TEXT("%d"), Speed));
	//Row.AddItem(FString::Printf( TEXT("%d"), LifeTime));
	//Row.AddItem(FString::Printf( TEXT("%d"), MaxCollisionCount));
	//Row.AddItem(FString::Printf( TEXT("%d"), RangeType));

	//Row.AddItem(FString::Printf( TEXT("%d"), RangeParam1));
	//Row.AddItem(FString::Printf( TEXT("%d"), RangeParam2));
	//Row.AddItem(FString::Printf( TEXT("%d"), RangeParam3));
	//Row.AddItem(FString::Printf( TEXT("%d"), OffsetDirection));
	//Row.AddItem(FString::Printf( TEXT("%d"), OffsetDistance));

	//int nOnCollision = 0;
	//int nOnRemove = 0;
	//int nOnCreate = 0;
	//if(OnCollision)
	//	nOnCollision = OnCollision->Id;
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnCollision));
	//if(OnRemove)
	//	nOnRemove = OnRemove->Id;
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnRemove));
	//if(OnCreate)
	//	nOnCreate = OnCreate->Id;
	//Row.AddItem(FString::Printf( TEXT("%d"), nOnCreate));

}
//------------------------------------------------------------------------
void UMissile::ExportExcelHeaders(TArray<FString>& Header,TArray<FString>& DefaultValues)
{
}
void UMissile::InitDataToExcel()
{
	OnCollisionID = 0;
	OnRemoveID = 0;
	OnInitID = 0;
	OnCreateID = 0;
	OnTimeupID = 0;
	OnCharEnterID = 0;
	OnCharLeaveID = 0;

	if(OnCollision)
		OnCollisionID = OnCollision->Id;
	if(OnRemove)
		OnRemoveID = OnRemove->Id;
	if(OnCreate)
		OnCreateID = OnCreate->Id;
	if(OnInit)
		OnInitID = OnInit->Id;
	if(OnTimeup)
		OnTimeupID = OnTimeup->Id;
	if(OnCharEnter)
		OnCharEnterID = OnCharEnter->Id;
	if(OnCharLeave)
		OnCharLeaveID = OnCharLeave->Id;

}

//------------------------------------------------------------------------
void UMissile::ImportFromExcel(const TArray<FString>& Values)
{	
}
//------------------------------------------------------------------------
