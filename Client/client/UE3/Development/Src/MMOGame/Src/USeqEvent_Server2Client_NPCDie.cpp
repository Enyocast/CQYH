#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server2Client_NPCDie);

int USeqEvent_Server2Client_NPCDie::GetKismetObjectServerType() const
{
	return (INT)kotSeqEvent_NpcDie;
}

void USeqEvent_Server2Client_NPCDie::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
