#include "stdafx.h"

IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange);
IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange_Scene);
IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange_Role);
IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange_Guild);
IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange_Quest);
IMPLEMENT_CLASS(USeqEvent_Server2Client_VarChange_KillNPCCount);

int USeqEvent_Server2Client_VarChange::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}



int USeqEvent_Server2Client_VarChange_Scene::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange_Scene::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}



int USeqEvent_Server2Client_VarChange_Role::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange_Role::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}



int USeqEvent_Server2Client_VarChange_Guild::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange_Guild::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}



int USeqEvent_Server2Client_VarChange_Quest::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange_Quest::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}



int USeqEvent_Server2Client_VarChange_KillNPCCount::GetKismetObjectServerType() const
{
	return (INT)kotEventBegin;
}

void USeqEvent_Server2Client_VarChange_KillNPCCount::ExportServerData(FArchive& inStream)
{
	Super::ExportServerData(inStream);
}
