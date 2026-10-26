
class SeqEvent_Server_NPCGroupDie extends SequenceEvent
	native;

cpptext
{
	virtual UBOOL IsServerKismetObject() const { return TRUE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
}

function bool IsDesiredInstigator(IServerTrigger obj)
{
	
	return false;
}

DefaultProperties
{	
	ObjName="NPC Group Die"
	ObjCategory="MMO Server"
	bPlayerOnly=true

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="All Dead")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="MMONPCSpawnGroup Object",MinVars=1,MaxVars=1)
}
