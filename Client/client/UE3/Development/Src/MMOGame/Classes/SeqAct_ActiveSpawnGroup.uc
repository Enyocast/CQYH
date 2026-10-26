class SeqAct_ActiveSpawnGroup extends SequenceAction
	native;

cpptext
{
	virtual UBOOL IsServerKismetObject() const { return TRUE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
}

event Activated( )
{
	// for server use do nothing


	//local SequenceVariable seqObj;
	//local IServerTrigger trigger;

	//`log("___________ SeqAct_SendUseTrigger Activated ");
	
	//foreach VariableLinks[0].LinkedVariables(seqObj)
	//{
	//	`log("___________ SeqAct_SendUseTrigger Activated " @SeqVar_Object(seqObj).GetObjectValue());
	//	trigger = IServerTrigger(SeqVar_Object(seqObj).GetObjectValue());
	//	if(trigger != none)
	//	{
	//		SendUseTrigger(trigger, trigger.GetTriggerID(), trigger.GetTriggerType());
	//	}
	//}

	//ActivateOutputLink(0);
}

DefaultProperties
{
	ObjName="Active Spawn Group"
	ObjCategory="MMO Server"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="In" )
	
	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Object', LinkDesc="MMONPCSpawnGroup Object" )
}

