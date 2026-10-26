#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server2Client_NPCGroupDie);

int USeqEvent_Server2Client_NPCGroupDie::GetKismetObjectServerType() const
{
	return (INT)kotSeqEvent_NPCGroupDie;
}

void USeqEvent_Server2Client_NPCGroupDie::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
