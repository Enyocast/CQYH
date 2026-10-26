class SeqAct_BTNode extends SequenceAction
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
	BOOL ExportBTNode( FString& Buffer, INT32 nDepth );// for export in AI or Scene
	virtual void GetDynamicListValues(const DynamicListInfo& ListInfo, TArray<FString>& Values);
	virtual UBOOL CanConnectVarToLink(USequenceVariable *Var, INT LinkIdx);
#endif

protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
}

/** behavior tree node type **/
//var() EBT_ACTION_TYPE BTNodeType<autocomment=true>;

var editoronly EBTEditType EditType;

var() init string BTNodeType <DynamicList="BTNodeTypeList">; // <DynamicList="BTNodeTypeList"|autocomment=true>;
var() init string BTNodeCutomizeType;

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

static event int GetObjClassVersion()
{
	return Super.GetObjClassVersion() + 0;
}

DefaultProperties
{
	ObjName="BTNode"
	//ObjCategory="MMO Server"
	bSuppressAutoComment=false

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="In" )
	
	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SequenceVariable', LinkDesc="P0",PropertyName=P0 )   //bWriteable=true, MinVars=1,MaxVars=1
	VariableLinks(1)=( ExpectedType=class'SequenceVariable', LinkDesc="P1",PropertyName=P1 )
	VariableLinks(2)=( ExpectedType=class'SequenceVariable', LinkDesc="P2",PropertyName=P2 )
	VariableLinks(3)=( ExpectedType=class'SequenceVariable', LinkDesc="P3",PropertyName=P3 )
}
