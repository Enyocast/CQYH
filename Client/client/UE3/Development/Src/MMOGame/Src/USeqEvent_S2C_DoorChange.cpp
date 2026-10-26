#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_S2C_DoorChange);

int USeqEvent_S2C_DoorChange::GetKismetObjectServerType() const
{
	return (INT)kotSeqAct_Door;
}

void USeqEvent_S2C_DoorChange::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
