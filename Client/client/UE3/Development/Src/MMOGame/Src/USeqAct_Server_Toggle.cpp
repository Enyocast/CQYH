#include "stdafx.h"

IMPLEMENT_CLASS(USeqAct_Server_Toggle);

/*
keDoorOpen = kepBegin,
keDoorClose,
keDoorToggle,
*/
int USeqAct_Server_Toggle::GetKismetObjectServerType() const
{
	return (INT)kotSeqAct_Door;
}

void USeqAct_Server_Toggle::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
