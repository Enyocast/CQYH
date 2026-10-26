//***
//	MMORainStreakActor.uc
//	rain effect actor, could also be used for snow effect
//***

class MMOUIHudLevel extends Object implements (IMMOActorHUD)
	native(UI);
	
var bool draw;
var float fAlpha;
var Texture2D textBg;

native function LoadBg();
native function ClearBg();

native function bool DrawMyHUD( MMOHud H );
//event bool DrawMyHUD( MMOHud H )
//{
//	if( textBg != none )
//	{
//		H.Canvas.DrawTexture( textBg , 1 );
//	}
//	return true;
//}

native function DrawHUDPostGFx( HUD H);

function bool OnlyDrawHUDForOwner()
{
	return false;
}

defaultproperties
{
	draw=false
	fAlpha=1.0
}