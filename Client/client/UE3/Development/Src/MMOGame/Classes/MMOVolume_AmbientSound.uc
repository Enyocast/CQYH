class MMOVolume_AmbientSound extends Volume
	native
	placeable;

var() array<SoundCue> SoundCueList;
var() array<SoundCue> NightSoundCueList;
var() float MaxRandX;
var() float MaxRandY;
var() float FadeInTime;
var() float FadeOutTime;


var transient array<AudioComponent> AudioComponentList;
var transient MMOActor MainActor;
var transient float RelativeX;
var transient float RelativeY;

native final function OnActive(Pawn P, bool bOn);

cpptext
{
	virtual void TickSpecial( FLOAT DeltaSeconds );
}

simulated event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{
	Super.Touch(Other, OtherComp, HitLocation, HitNormal);
	if(Pawn(Other) != none)
	{
		OnActive(Pawn(Other), true);
	}
}

event UnTouch(Actor Other)
{
	super.UnTouch(Other);
	if(Pawn(Other) != none)
	{
		OnActive(Pawn(Other), false);
	}
}


//simulated event PawnEnteredVolume(Pawn P)
//{
//	super.PawnEnteredVolume(P);
//	OnActive(P, true);
//}

//simulated event PawnLeavingVolume(Pawn P)
//{	
//	super.PawnLeavingVolume(P);
//	OnActive(P, false);
//}

defaultproperties
{
	FadeInTime=0.5
	FadeOutTime=0.5
}
