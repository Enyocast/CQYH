#include "stdafx.h"

IMPLEMENT_CLASS(USeqAct_Server_ToggleTriggerRequest);

int USeqAct_Server_ToggleTriggerRequest::GetKismetObjectServerType() const
{
	return (INT)kotSeqAct_ActiveSpawnGroup;
}

void USeqAct_Server_ToggleTriggerRequest::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
