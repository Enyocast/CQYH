#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server_NPCDie);

int USeqEvent_Server_NPCDie::GetKismetObjectServerType() const
{
	return (INT)kotSeqEvent_NpcDie;
}

void USeqEvent_Server_NPCDie::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
