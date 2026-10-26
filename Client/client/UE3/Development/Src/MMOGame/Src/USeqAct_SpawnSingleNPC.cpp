#include "stdafx.h"

IMPLEMENT_CLASS(USeqAct_SpawnSingleNPC);

int USeqAct_SpawnSingleNPC::GetKismetObjectServerType() const
{
	return (INT)kotSeqAct_SpawnSingleNpc;
}

void USeqAct_SpawnSingleNPC::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
