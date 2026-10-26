#include "stdafx.h"

IMPLEMENT_CLASS(USeqAct_ActiveSpawnGroup);

int USeqAct_ActiveSpawnGroup::GetKismetObjectServerType() const
{
	return (INT)kotSeqAct_ActiveSpawnGroup;
}

void USeqAct_ActiveSpawnGroup::ExportServerData(FArchive& inStream)
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
// 		AMMONPCSpawnGroup* SpawnGrp = Cast<AMMONPCSpawnGroup>(*ObjectRef);
// 		if(SpawnGrp)
// 		{
// 			inStream << SpawnGrp->AutoServerID;
// 		}
// 		else if(*ObjectRef)
// 		{
// 			GWarn->MapCheck_Add(MCTYPE_ERROR, this,
// 				TEXT("Kismet referenced error object for SeqAct_ActiveSpawnGroup"),
// 				NULL, MCGROUP_KISMET);
// 		}
// 	}
}
