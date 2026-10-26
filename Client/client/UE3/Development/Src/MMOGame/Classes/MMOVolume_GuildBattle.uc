class MMOVolume_GuildBattle extends Volume
	native
	placeable;

var() float StartTime <ClampMin = 0.0 | ClampMax = 24.0>;
var() float StopTime <ClampMin = 0.0 | ClampMax = 24.0>;

var() LinearColor AttackerColor;
var() LinearColor DefenceColor;

native final function OnActive(MMOActor actor, bool bOn);

simulated event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	Super.Touch(Other, OtherComp, HitLocation, HitNormal);
	if(MMOActor(Other) != none)
	{
		OnActive(MMOActor(Other), true);
	}
}

event UnTouch(Actor Other)
{
	super.UnTouch(Other);
	if(MMOActor(Other) != none)
	{
		OnActive(MMOActor(Other), false);
	}
}

defaultproperties
{
	StartTime=0
	StopTime=24
	AttackerColor=(R=1.0,G=0,B=0)
	DefenceColor=(R=1.0,G=1.0,B=0)
}
