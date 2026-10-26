class SeqAct_SendUseTrigger extends SequenceAction
	native;

native function SendUseTrigger(IServerTrigger trigger, int triggerID, int triggerType);

event Activated( )
{
	local SequenceVariable seqObj;
	local IServerTrigger trigger;

	`log("___________ SeqAct_SendUseTrigger Activated ");
	
	foreach VariableLinks[0].LinkedVariables(seqObj)
	{
		`log("___________ SeqAct_SendUseTrigger Activated " @SeqVar_Object(seqObj).GetObjectValue());
		trigger = IServerTrigger(SeqVar_Object(seqObj).GetObjectValue());
		if(trigger != none)
		{
			SendUseTrigger(trigger, trigger.GetTriggerID(), trigger.GetTriggerType());
		}
	}

	ActivateOutputLink(0);
}

DefaultProperties
{
	ObjName="Send Use Trigger"
	ObjCategory="MMO Server Old"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="In" )
	
	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Object', LinkDesc="Trigger" )
}

