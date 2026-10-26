
class SeqEvent_S2C_DoorChange extends SequenceEvent
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
	ObjName="SeqEvent_S2C_DoorChange"
	ObjCategory="MMO Server To Client"
	bPlayerOnly=true

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Open")
	OutputLinks(1)=(LinkDesc="Close")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="MMOToggleDoorActor Object",MinVars=1,MaxVars=1)
}
