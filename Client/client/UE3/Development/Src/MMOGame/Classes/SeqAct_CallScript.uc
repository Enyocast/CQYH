class SeqAct_CallScript extends SequenceAction;

var() float TimeDelay;
event Activated()
{
	local SeqVar_Object TargetObject;
	local Actor actor;
	local SeqVar_String funcObj;
	local name func;

	foreach LinkedVariables(class'SeqVar_Object', TargetObject, "TargetObject")
	{
		actor = Actor(TargetObject.GetObjectValue());
		if(actor != none)
		{   
			foreach LinkedVariables(class'SeqVar_String', funcObj, "Function")
			{
				func = name(funcObj.StrValue);
				actor.SetTimer( TimeDelay, false, func );
			}
		}
	}

	ActivateOutputLink(0);
}

DefaultProperties
{
	TimeDelay=0.1
	ObjName="Call Script"
	ObjCategory="MMO Client"
	InputLinks.Empty
	InputLinks(0)=(LinkDesc="Call")
	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Object',LinkDesc="TargetObject")
	VariableLinks(1)=(ExpectedType=class'SeqVar_String',LinkDesc="Function")
}
