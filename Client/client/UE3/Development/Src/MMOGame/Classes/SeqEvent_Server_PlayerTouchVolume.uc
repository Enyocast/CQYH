
class SeqEvent_Server_PlayerTouchVolume extends SequenceEvent
	native;

cpptext
{
	virtual UBOOL IsServerKismetObject() const { return TRUE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
}

function bool IsDesiredInstigator(IServerTrigger obj)
{
	//local Object val;
	//local SequenceVariable seqObj;
	////local SequenceObject parentSeq;

	////parentSeq = self.ParentSequence;
	////while(parentSeq != none)
	////{
	////	`log("OSCAR:_________ SeqEvent_Server_UseTrigger" @parentSeq @parentSeq.Outer);
	////	parentSeq = parentSeq.ParentSequence;
	////}

	//if(VariableLinks.Length <= 0)
	//{
	//	`log("OSCAR:_________ SeqEvent_Server_UseTrigger IsDesiredInstigator Empty Link Variable, TriggerID:"
	//		@obj.GetTriggerID() @self @self.Outer);
	//	return false;
	//}

	//foreach VariableLinks[0].LinkedVariables(seqObj)
	//{
	//	//`log("OSCAR:_________ SeqEvent_Server_UseTrigger IsDesiredInstigator:" @seqObj @obj);
	//	val = SeqVar_Object(seqObj).GetObjectValue();
	//	if(val != none)
	//	{
	//		//`log("OSCAR:_________ SeqEvent_Server_AreaChange:" @val @obj);
	//		if( val == obj)
	//		{
	//			return true;
	//		}
	//	}
	//}

	//`log("OSCAR:_________ SeqEvent_Server_AreaChange: false " @obj);
	return false;
}

DefaultProperties
{	
	ObjName="Player Touch Volume"
	ObjCategory="MMO Server"
	bPlayerOnly=true

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Touched")
	OutputLinks(1)=(LinkDesc="UnTouched")
	OutputLinks(2)=(LinkDesc="Empty")


	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="MMOVolume_Trigger Object",MinVars=1)
}
