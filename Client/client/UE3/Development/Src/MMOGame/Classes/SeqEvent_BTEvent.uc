
class SeqEvent_BTEvent extends SequenceEvent
	native
	dependson(ServerEnum)
	dependson(TypeDefine);

cpptext
{
	virtual UBOOL IsServerKismetObject() const { return TRUE; }
	virtual int GetKismetObjectServerType() const;
	virtual void ExportServerData(FArchive& inStream);
#if WITH_EDITOR
	virtual FString GetAutoComment() const;
	BOOL ExportBTScript( FString& Buffer );// for export in AI or Scene
	virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	virtual UBOOL CanConnectVarToLink(USequenceVariable *Var, INT LinkIdx);
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
}

var editoronly EBTEditType EditType;
var() init string BTEventType<DynamicList="BTEventTypeList">;  //<DynamicList="BTEventTypeList"|autocomment=true>;

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

static event int GetObjClassVersion()
{
	return Super.GetObjClassVersion() + 0;
}

DefaultProperties
{	
	ObjName="BTEvent"
	BTEventType="evtInvalid"
	bSuppressAutoComment=false

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Event")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="Refer",MinVars=1)
}
