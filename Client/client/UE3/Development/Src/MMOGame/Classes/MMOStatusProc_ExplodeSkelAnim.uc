//
// 通过骨架动画来表现
//
class MMOStatusProc_ExplodeSkelAnim extends Object implements(IMMOStatusProc)
	native
	editinlinenew
	hidecategories(Object);

var() SkeletalMesh Mesh;
var() AnimSet AnimSet;
var() name AnimToPlay;

var() Vector2d PositionOffsetRange;

// 如果不随机朝向则与角色朝向一致
var() bool EnableRandomRotation;

// 模型生存时间(秒)
var() float SpawnMeshLifeSpan;

// 是否在动画完成后就销毁（如果是，则不用SpawnMeshLifeSpan参数）
var() bool DestroyWhenAnimEnd;

var() PhysicsAsset PhysicsAsset;
var() AnimTree AnimTree;

event OnExecute(MMOActor actor)
{	
	local Vector spawnLocationt;
	local float ofx, ofy;
	local Rotator oyaw;
	local SkeletalMeshActorSpawnable sma;
	local AnimNodeSequence animNode;


	ofx = RandRange(-PositionOffsetRange.X, PositionOffsetRange.X);
	ofy = RandRange(-PositionOffsetRange.Y, PositionOffsetRange.Y);
	spawnLocationt = actor.Location;
	spawnLocationt.X += ofx;
	spawnLocationt.Y += ofy;
	
	if(EnableRandomRotation)
	{
		oyaw.Yaw = FRand() * 360.0 * DegToUnrRot;
	}
	else
	{
		oyaw.Yaw = actor.Rotation.Yaw;
	}

	sma = actor.Spawn(class'SkeletalMeshActorSpawnable',,, spawnLocationt, oyaw, , true);
	sma.SkeletalMeshComponent.AnimSets.AddItem(AnimSet);
	sma.SkeletalMeshComponent.SetSkeletalMesh(Mesh);
	sma.SkeletalMeshComponent.SetAnimTreeTemplate(AnimTree);
	
	if(PhysicsAsset != none)
	{
		sma.SkeletalMeshComponent.SetPhysicsAsset(PhysicsAsset, true);
	}

	//sma.PostBeginPlay();
	animNode = AnimNodeSequence(sma.SkeletalMeshComponent.Animations.FindAnimNode('Default'));	
	animNode.SetAnim(AnimToPlay);
	//animNode.StopAnim();
	animNode.bPlaying = true;
	animNode.PlayAnim(false, 1, 0.0f);
		
	if(DestroyWhenAnimEnd)
	{
		sma.LifeSpan = animNode.GetAnimPlaybackLength();
	}
	else
	{
		sma.LifeSpan = SpawnMeshLifeSpan;
	}

	`log("_________ sma.LifeSpan" @sma.LifeSpan @AnimToPlay @animNode @animNode.AnimSeq @animNode.AnimSeq.SequenceLength);
}
native function Update(MMOActor actor);

defaultproperties
{
	PositionOffsetRange=(X=0,Y=0)
	EnableRandomRotation=false
	SpawnMeshLifeSpan=3
	DestroyWhenAnimEnd=true
	// TODO: use the right animtree
//	AnimTree=AnimTree'AnimationTreeTemplate.AT_OneNode'
}