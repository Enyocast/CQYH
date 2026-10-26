#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server_NPCGroupDie);

int USeqEvent_Server_NPCGroupDie::GetKismetObjectServerType() const
{
	return (INT)kotSeqEvent_NPCGroupDie;
}

void USeqEvent_Server_NPCGroupDie::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);

// 	TArray<UObject**> VarObjects;
// 	GetObjectVars(VarObjects);
// 
// 	INT Num = VarObjects.Num();
// 	inStream << Num;
// 
// 	for (INT i = 0; i < VarObjects.Num(); ++i)
// 	{
// 		UObject** ObjectRef = VarObjects(i);
// 		AMMONPCSpawnGroup* Obj = Cast<AMMONPCSpawnGroup>(*ObjectRef);
// 		if(Obj)
// 		{
// 			inStream << Obj->AutoServerID;
// 		}
// 		else if(*ObjectRef)
// 		{
// 			GWarn->MapCheck_Add(MCTYPE_ERROR, this,
// 				TEXT("Kismet referenced error object for SeqEvent_Server_NPCGroupDie"),
// 				NULL, MCGROUP_KISMET);
// 		}
// 	}
}
