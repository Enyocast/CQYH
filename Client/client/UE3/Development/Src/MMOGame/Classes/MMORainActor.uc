class MMORainActor extends Actor
	config(Rain)
	placeable
	native;

var()	int		Count;
var()	int		SpeedMin;
var()	int		SpeedMax;
var()	int		BoundSize;
var()	int		Height;

var()	MaterialInstanceTimeVarying	RainMaterial;

var		ParticleSystemComponent		RainPS;

//native function OnPSComponentAttached();

defaultproperties
{
	Count=1000
	SpeedMin=4000
	SpeedMax=6000
	BoundSize=3000
	Height=5000
}