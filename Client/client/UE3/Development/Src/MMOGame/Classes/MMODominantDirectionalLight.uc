class MMODominantDirectionalLight extends DominantDirectionalLightMovable
	implements( ITimeEffectObj );

var(MMOLight) float   BrightnessMax;
var(MMOLight) float   BrightnessMin;
var(MMOLight) Color   ColorWeak;
var(MMOLight) Color   ColorStrong;

event PostBeginPlay( )
{
	Register( );
}

event Destroyed()
{
	UnRegister();
}

//simulated function OnDestroy( SeqAct_Destroy Action )
//{
//	UnRegister( );
//}

function Register( )
{
	MMOGame(WorldInfo.Game).MyTimeManager.RegisterObject( self );
}

function UnRegister( )
{
	MMOGame(WorldInfo.Game).MyTimeManager.UnRegisterObject( self );
}

function UpdateByTime( int d, int h, float m )
{
	local float brightness;
	local Color clr;
	if( h < 1 )
	{
		brightness = BrightnessMin;
		clr = ColorWeak;
	}
	else if( h < 11 )
	{
		brightness = BrightnessMax - ( BrightnessMax - BrightnessMin ) * ( ( 11 - h ) * 0.1f + ( 60 - m ) * 0.001666f - 0.1f );
		clr = ColorStrong - ( ColorStrong - ColorWeak ) * ( ( 11 - h ) * 0.1f + ( 60 - m ) * 0.001666f - 0.1f );
	}
	else if( h < 13 )
	{
		brightness = BrightnessMax;
		clr = ColorStrong;
	}
	else if( h < 23 )
	{
		brightness = BrightnessMax - ( BrightnessMax - BrightnessMin ) * ( ( h - 13 ) * 0.1f - ( 60 - m ) * 0.001666f + 0.1f );
		clr = ColorStrong - ( ColorStrong - ColorWeak ) * ( ( h - 13 ) * 0.1f - ( 60 - m ) * 0.001666f + 0.1f );
	}
	else
	{
		brightness = BrightnessMin;
		clr = ColorWeak;
	}
	LightComponent.SetLightProperties( brightness, clr );
}

DefaultProperties
{
	BrightnessMin=0.5f
	BrightnessMax=2.0f
	ColorWeak=(R=128,G=128,B=255)
	ColorStrong=(R=255,G=255,B=255)
}
