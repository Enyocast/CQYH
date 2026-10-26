//
// 动画通知生成地面贴花
//
class AnimNotify_SpawnDecal extends AnimNotify_ScriptedEx
	;

var(MMOSFX) MaterialInterface ImpactDecalMaterial;
var(MMOSFX) float ImpactDecalSizeMin;
var(MMOSFX) float ImpactDecalSizeMax;
var(MMOSFX) float ImpactDecalDepth;

// 如果是MITV则用帧时间自动计算，静态的贴花用这个时间
var(MMOSFX) float ImpactDecalLifespanNonMITV;

// 用于创建贴花位置的参考绑定点(Socket)，如果没有指定则使用角色的当前位置
var(MMO) name SocketName <DynamicList="SocketList">;

function SpawnImpactDecal(Actor actor, MaterialInterface impactMat,
	Vector HitLocation, Vector HitNormal, optional float decalOrientation = FRand() * 360.0)
{
   local float SizeChange;
   local MaterialInstanceTimeVarying MITV;
   local MaterialInterface theDecal;
   local float DecalLifespan;

	if(impactMat == none)
		return;

	//`log("&&&&&&&&&&&&&&&" @HitNormal @HitLocation);

	SizeChange = ImpactDecalSizeMax;//RandRange(ImpactDecalSizeMin, ImpactDecalSizeMax);

	theDecal = impactMat;
	DecalLifespan = ImpactDecalLifespanNonMITV;
	//if it's a MITV, create a new MIC of the MITV, use that for the Decal's Material, and calculate its lifespan from the MITV
	if(impactMat.IsA('MaterialInstanceTimeVarying'))
	{
		MITV = new class'MaterialInstanceTimeVarying';
		MITV.SetParent(impactMat);
		DecalLifespan = MITV.GetMaxDurationFromAllParameters();

		actor.WorldInfo.MyDecalManager.SpawnDecal(MITV, HitLocation, Rotator(Normal(-HitNormal + vect(0.01, 0, 0))),
			SizeChange, SizeChange, ImpactDecalDepth, true, decalOrientation, none, true, false, , , , DecalLifespan);

		MITV.SetDuration(DecalLifespan);
		//MITV.SetScalarStartTime('DecalAlpha', 1);
		//`log("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
	}
	else
	{
		//create a decal in the World with this handy helper function!
		actor.WorldInfo.MyDecalManager.SpawnDecal(theDecal, HitLocation, Rotator(Normal(-HitNormal + vect(0.01, 0, 0))),
			SizeChange, SizeChange, ImpactDecalDepth, true, decalOrientation, none, true, false, , , , DecalLifespan);
	}
}

event Notify( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
	local Vector pos;
	local Rotator rot;
	
	GetWorldPosRot(Owner, SocketName, pos, rot);
	SpawnImpactDecal(Owner, ImpactDecalMaterial, pos, vect(0, 0, 1), Owner.Rotation.Yaw * UnrRotToDeg);
}

event NotifyEnd( Actor Owner, AnimNodeSequence AnimSeqInstigator )
{
}


DefaultProperties
{
	ImpactDecalSizeMin=150
	ImpactDecalSizeMax=150
	ImpactDecalDepth=200
	ImpactDecalLifespanNonMITV=5
}
