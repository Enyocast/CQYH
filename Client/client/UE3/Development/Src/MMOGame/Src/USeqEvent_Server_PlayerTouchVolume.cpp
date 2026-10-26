#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server_PlayerTouchVolume);

int USeqEvent_Server_PlayerTouchVolume::GetKismetObjectServerType() const
{
	return (INT)kotSeqEvent_PlayerTouchVolume;
}

void USeqEvent_Server_PlayerTouchVolume::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);

// 	TArray<UObject**> OutObjects;
// 	GetObjectVars(OutObjects);
// 
// 	INT Num = OutObjects.Num();
// 	inStream << Num;
// 
// 	for (INT i = 0; i < OutObjects.Num(); ++i)
// 	{
// 		UObject** ObjectRef = OutObjects(i);
// 		AMMOVolume_Trigger* Obj = Cast<AMMOVolume_Trigger>(*ObjectRef);
// 		if(Obj)
// 		{
// 			inStream << Obj->AreaID;
// 		}
// 		else if(*ObjectRef)
// 		{
// 			GWarn->MapCheck_Add(MCTYPE_ERROR, this,
// 				TEXT("Kismet referenced error object for SeqEvent_Server_PlayerTouchVolume"),
// 				NULL, MCGROUP_KISMET);
// 		}
// 	}
}
