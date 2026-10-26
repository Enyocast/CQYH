class AbilityDecalComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var() array<MaterialInterface> ImpactDecalMaterials;
var() float ImpactDecalSizeMin;
var() float ImpactDecalSizeMax;
var() float ImpactDecalDepth;
/** The Lifespan to give to the decal if it's not a MITV (otherwise Lifespan is automatically calculated from the MITV's keyframes) */
//var(DecalComp) float ImpactDecalLifespanNonMITV;

var() Vector RelativeLocation;
var() bool bScaleByStandardCollision;
var() float ScaleX;
var() float ScaleY;

var() bool bUseRandomRotation;
var() float Rotation;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}

event SpawnDecal(
	Actor InActor,
	MaterialInterface DecalMaterial,
	vector DecalLocation,
	rotator DecalOrientation,
	float Width,
	float Height,
	float Thickness,
	bool bNoClip,
	optional float DecalRotation = (FRand() * 360.0),
	optional PrimitiveComponent HitComponent
						)
{
	InActor.WorldInfo.MyDecalManager.SpawnDecal(DecalMaterial, DecalLocation, DecalOrientation, Width, Height, Thickness, bNoClip, DecalRotation, HitComponent);
}

/*
 event Play(Actor BaseActor, MMOAbility AbilityData, Actor Target, Vector TargetPoint, float InRate, optional int SerialId = 0)
{
	local Vector start, end, HitLocation, HitNormal;
	local Actor TracedActor;
	local Matrix mat;
	local int idx;
	//local LinearColor color;
	`log("DecalComponent::Play BaseActor="$BaseActor$"  Target="$Target$"  TargetPoint="$TargetPoint);
	if(BaseActor == none)
	{
		`log("error target is none");
		return;
	}

	RelativeLocation.Z = 0;


	Start = BaseActor.Location;
	//Start.Z +=500;

	mat = MakeRotationMatrix(BaseActor.Rotation);
	Start = Start + TransformVector(mat, RelativeLocation);

	end = Start;
	end.Z -= 1000;

	//Target.DrawDebugLine(Start, end, 255,0,0, true);
	

	TracedActor = BaseActor.Trace(HitLocation, HitNormal, end, Start, true, ,,8);
	if(TracedActor != none)
	{
		//color.A = 1.0;
		//color.R = 1.0;
		//color.G = 0;
		//color.B = 0;
		//Target.DrawDebugPoint(HitLocation, 5, color, true);
		//`log("TraceActor is "$TracedActor);
		if(ImpactDecalMaterials.Length > 0)
		{
			idx = Rand(ImpactDecalMaterials.Length);
			SpawnImpactDecal(BaseActor, ImpactDecalMaterials[idx], HitLocation, HitNormal);
		}
	}
}

function SpawnImpactDecal(Actor Target,  MaterialInterface impactMat, Vector HitLocation, Vector HitNormal)
{
   local float SizeChange;
   local MaterialInstanceTimeVarying MITV;
   local MaterialInterface theDecal;
   local float DecalLifespan;
   local float decalOrientation;
   local float ScaleRate;

	if(impactMat == none)
		return;

	decalOrientation = FRand() * 360.0;

	//`log("&&&&&&&&&&&&&&&" @HitNormal @HitLocation);

	SizeChange = ImpactDecalSizeMax;//RandRange(ImpactDecalSizeMin, ImpactDecalSizeMax);

	if(MMOActor(Target) != none)
	{
		ScaleRate = MMOActor(Target).CollisionRadiusRate;
	}
	else
	{
		ScaleRate = 1.0f;
	}

	SizeChange *= ScaleRate;

	theDecal = impactMat;
	DecalLifespan = ImpactDecalLifespanNonMITV;
	//if it's a MITV, create a new MIC of the MITV, use that for the Decal's Material, and calculate its lifespan from the MITV
	if(impactMat.IsA('MaterialInstanceTimeVarying'))
	{
		MITV = new class'MaterialInstanceTimeVarying';
		MITV.SetParent(impactMat);
		DecalLifespan = MITV.GetMaxDurationFromAllParameters();

		Target.WorldInfo.MyDecalManager.SpawnDecal(MITV, HitLocation, Rotator(Normal(-HitNormal + vect(0.01, 0, 0))),
			SizeChange, SizeChange, ImpactDecalDepth, true, decalOrientation, none, true, false, , , , DecalLifespan);

		MITV.SetDuration(DecalLifespan);
		MITV.SetScalarStartTime('DecalAlpha', 0);
		//`log("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	}
	else
	{
		//create a decal in the World with this handy helper function!
		Target.WorldInfo.MyDecalManager.SpawnDecal(theDecal, HitLocation, Rotator(Normal(-HitNormal + vect(0.01, 0, 0))),
			SizeChange, SizeChange, ImpactDecalDepth, true, decalOrientation, none, true, false, , , , DecalLifespan);
	}
}

*/


DefaultProperties
{
	ImpactDecalDepth=50.0f
	ImpactDecalSizeMax=150
	ImpactDecalSizeMin=80
	LineColor=(R=0.7255,G=0.4784,B=0.3412,A=1.0)
	TitleString="Decal"
	bHaveTrail=true
	bScaleByStandardCollision=true
	Duration=3.0
	ScaleX=1.0
	ScaleY=1.0
}

