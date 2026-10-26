class SeqAct_ToggleVolume extends SequenceAction;

event Activated( )
{
	local SeqVar_Object volObj;
	local DynamicTriggerVolume vol;
	local bool bToggleOn;
	if( InputLinks[0].bHasImpulse )
		bToggleOn = true;
	else
		bToggleOn = false;
	foreach LinkedVariables( class'SeqVar_Object', volObj, "Volume" )
	{
		vol = DynamicTriggerVolume( volObj.GetObjectValue( ) );
		if( vol != none )
		{
			if( bToggleOn )
			{
				vol.SetCollisionType( COLLIDE_TouchAllButWeapons );
			}
			else
				vol.SetCollisionType( COLLIDE_NoCollision );
		}
	}
}

DefaultProperties
{
	ObjName="Toggle Volume"
	ObjCategory="MMO Client"

	InputLinks.Empty
	InputLinks(0)=( LinkDesc="Enable" )
	InputLinks(1)=( LinkDesc="Disable" )

	OutputLinks.Empty
	OutputLinks(0)=( LinkDesc="Out" )

	VariableLinks.Empty
	VariableLinks(0)=( ExpectedType=class'SeqVar_Object', LinkDesc="Volume" )
}

