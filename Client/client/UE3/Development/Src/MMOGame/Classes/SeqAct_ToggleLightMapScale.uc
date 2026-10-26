//
// toggle LightMapScale value, for caves and indoor scenes
//
class SeqAct_ToggleLightMapScale extends SequenceAction;

event Activated()
{
	local SeqVar_Player TargetObject;
	local MMOPlayer actor;
	local bool toggleOn;


	if( InputLinks[0].bHasImpulse )
	{
		toggleOn = true;
	}
	else if( InputLinks[1].bHasImpulse )
	{
		toggleOn = false;
	}


	foreach LinkedVariables(class'SeqVar_Player', TargetObject, "TargetObject")
	{
		actor = MMOPlayer(TargetObject.GetObjectValue());
		if( actor != none && actor.WorldInfo != none )
		{
			actor.WorldInfo.DisableLightmapScale = !toggleOn;
		}
	}

	ActivateOutputLink(0);
}

DefaultProperties
{
	ObjName="Toggle LightMapScale"
	ObjCategory="MMO Client"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="On" )
	InputLinks(1)=( LinkDesc="Off" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
	VariableLinks(0)=(ExpectedType=class'SeqVar_Player',LinkDesc="TargetObject")
}
