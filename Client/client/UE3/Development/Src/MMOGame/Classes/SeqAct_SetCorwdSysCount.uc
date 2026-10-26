
// change the count of crowd syste actor

class SeqAct_SetCorwdSysCount extends SequenceAction;

var(MMO) int Count;

event Activated()
{
	local SeqVar_Object TargetObject;
	local MMOCrowdSystem actor;

	foreach LinkedVariables(class'SeqVar_Object', TargetObject, "TargetObject")
	{
		actor = MMOCrowdSystem(TargetObject.GetObjectValue());
		if(actor != none)
		{
			actor.InstanceCount = Count;
		}
		actor.ResetAllInstances();
	}

	ActivateOutputLink(0);
}

DefaultProperties
{	
	ObjName="Set CorwdSys Count"
	ObjCategory="MMO Client"
	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Finished")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="TargetObject")

	Count=1000
}
