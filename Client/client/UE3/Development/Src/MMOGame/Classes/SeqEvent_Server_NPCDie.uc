
class SeqEvent_Server_NPCDie extends SequenceEvent
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
	ObjName="NPC Die"
	ObjCategory="MMO Server"
	bPlayerOnly=true

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Dead")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="NPCServerInstance Object",MinVars=1,MaxVars=1)
}
