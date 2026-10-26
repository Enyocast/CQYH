
class SeqEvent_Server2Client_VarChange extends SequenceEvent
	native;

var() int VarType;
var() int VarIndex;
var() int VarReferID;
var() int VarValue;

cpptext
{
	virtual UBOOL IsServerKismetObject() const { return FALSE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
}

function bool IsDesiredInstigator(IServerTrigger obj)
{
	
	return false;
}


DefaultProperties
{	
	ObjName="Server Var Change"
	ObjCategory="MMO Server To Client"
	
	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Int',LinkDesc="Var Type",PropertyName=VarType)
	VariableLinks(1)=(ExpectedType=class'SeqVar_Int',LinkDesc="Var Index",PropertyName=VarIndex)
	VariableLinks(2)=(ExpectedType=class'SeqVar_Int',LinkDesc="Var ReferID",PropertyName=VarReferID)
	VariableLinks(3)=(ExpectedType=class'SeqVar_Int',LinkDesc="Var Value",PropertyName=VarValue)
}
