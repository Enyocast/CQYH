class SeqAct_ToggleUI extends SequenceAction;

event Activated( )
{
	//local SeqVar_Bool volBool;
	local SeqVar_Object volObj;
	//local bool bToggleOn;
	local MMOPlayer player;

	//if( InputLinks[0].bHasImpulse )
	//	bToggleOn = true;
	//else
	//	bToggleOn = false;

	//`log("ToggleUI_________________"@bToggleOn);

	foreach LinkedVariables( class'SeqVar_Object', volObj, "Instigator" )
	{
		player = MMOPlayer(volObj.GetObjectValue( ));
		if( player != none)
		{
			//MMOHud(MMOPlayerController(player.Controller).myHUD).HudMovie.SetUIPlayerVisible(bToggleOn);
		}
	}
}

DefaultProperties
{
	ObjName = "Toggle UI"
	ObjCategory = "MMO Client"

		InputLinks.Empty
	InputLinks(0) = ( LinkDesc = "Enable" )
	InputLinks(1) = ( LinkDesc = "Disable" )

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Finished")

	VariableLinks.Empty
	//VariableLinks(0)=(ExpectedType=class'SeqVar_Bool',LinkDesc="OpenOrClose")
	VariableLinks(0) = ( ExpectedType = class'SeqVar_Object', LinkDesc = "Instigator" )
}

