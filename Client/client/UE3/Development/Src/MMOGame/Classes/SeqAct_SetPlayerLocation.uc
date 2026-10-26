class SeqAct_SetPlayerLocation extends SequenceAction;

event Activated()
{
	local SeqVar_Object TargetObject;
	local MMOPlayer player;

	foreach LinkedVariables(class'SeqVar_Object', TargetObject, "Target")
	{
		player = MMOPlayer(TargetObject.GetObjectValue());
		if(player != none)
		{
			if( VariableLinks[0].LinkedVariables.Length != 0 )
			{
				player.SetLocation( SeqVar_Vector(VariableLinks[0].LinkedVariables[0]).vectValue );
			}
			if( VariableLinks[1].LinkedVariables.Length != 0 )
			{
				player.SetRotation( Rotator(SeqVar_Vector(VariableLinks[1].LinkedVariables[0]).vectValue) );
			}
		}
	}

	ActivateOutputLink(0);
}

DefaultProperties
{
	ObjName="Set Player Location"
	ObjCategory="MMO Client"

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Vector',LinkDesc="Location")
	VariableLinks(1)=(ExpectedType=class'SeqVar_Vector',LinkDesc="Rotation")
	VariableLinks(2)=(ExpectedType=class'SeqVar_Object',LinkDesc="Target")
}
