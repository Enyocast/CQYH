/*
 * 模型定义
 * 
 */

class AvatarData extends Object
	native
	hidecategories(Object);


struct native MeshList
{
	var() EBodyMeshType     MeshType; 
	var() array<EquipMesh> EquipMeshList;
};

var() string                AvatarName					<DisplayName="AvatarName">;
var() SkeletalMesh  SkeletalMesh						<DisplayName="SkeletalMesh">;
var() array<MaterialInterface>	Materials				<DisplayName="Materials">;
var() AnimTree      AnimationTree						<DisplayName="AnimationTree">;
var() editconst PhysicsAsset  PhysicAsset				<DisplayName="PhysicAsset">;
var() EBodyType     PhysicsBodyType						<DisplayName="PhysicsBodyType">;
var() array<WeaponTypeAnimSetPair> WeaponAnimSetPairs	<DisplayName="WeaponAnimSetPairs">;

var() array<EquipMesh>	DefaultMeshListTemplate			<DisplayName="DefaultMeshListTemplate">;

var() array<MeshList>   RandomMeshListTemplate          <DisplayName="RandomMeshListTemplate">; 
var() float AvatarDrawScale								<DisplayName="AvatarDrawScale"|ClampMin=0.1 | ClampMax=4.0>;
var() float HintNameOffsetZ                             <DisplayName="NameOffsetZ">;
var() float MeshScale;

// TRUE: 合并肩甲 FALSE: 合并脸部
var()	bool			MergeShoulder					<DisplayName="MergeShoulder">;

// TRUE: 使用合并的模型取代换装。新的策划方案取消了身体部件更换，仅仅保留头盔(头发)、脸部和身体可更换
var()	bool			UseMergedMesh					<DisplayName="UseMergedMesh">;

// 还是走老的DefaultMeshList吧，不然同时维护两套代码太容易出错
//// 默认的身体模型（什么装备都不穿的时候显示这个）
//var()	SkeletalMesh	DefaultBodyMesh					<DisplayName="DefaultBodyMesh">;
//
//// 可选的发型和脸型，新换装机制下使用
//var()	array<SkeletalMesh>	HairList					<DisplayName="HairList">;
//var()	array<SkeletalMesh>	FaceList					<DisplayName="FaceList">;

//only for sound effect
var(SoundFX) EBodyType BodyType							<DisplayName="BodyType">;
var(SoundFX) EItemMaterialType     TargetArmorMatType   <DisplayName="TargetArmorMatType">;
var(SoundFX) array<SoundCue> Sound_EnterBattle <DisplayName="Sound_EnterBattle">;

var(SoundFX) array<SoundCue> Sound_OpenDiag <DisplayName="Sound_OpenDiag">;
var(SoundFX) array<SoundCue> Sound_CloseDiag <DisplayName="Sound_CloseDiag">;
var(SoundFX) array<SoundCue> Sound_Spawn <DisplayName="Sound_Spawn">;
var(SoundFX) array<SoundCue> Sound_Talk <DisplayName="Sound_Talk">;
var(SoundFX) array<SoundCue> Sound_Idle <DisplayName="Sound_Idle">;
var(SoundFX) SoundCue QuestSoundAccept <DisplayName="QuestSoundAccept">;
var(SoundFX) SoundCue QuestSoundUnderway <DisplayName="QuestSoundUnderway">;
var(SoundFX) SoundCue QuestSoundSubmit <DisplayName="QuestSoundSubmit">;

var(Collision) float	CollisionHeight					<DisplayName="CollisionHeight">;	
var(Collision) float	CollisionRadius					<DisplayName="CollisionRadius">;

var(Movement) float RotatoDegreePerSecond;
var(Movement) float ToggleMoveAnimCriticalValue         <ClampMin=0.0 | ClampMax=1.0>;

var() float DefaultMoveSpeed                            <DisplayName="DefaultMoveSpeed">;

// 默认为0, 从原始资源计算得到,功能过度期内,如果没有可计算的正常资源,使用DefaultMoveSpeed
var float WalkSpeed;
var float RunSpeed;
var float FlySpeed;

//var bool bLoadedPhysicAsset;


// 初始时的可破坏部件列表
var(MMOAttach) editinline array<DestructablePartAttachInfo> InitAttachDestructableParts <DisplayName="InitAttachDestructableParts">;
// 当前绑定的粒子系统
//var(MMOAttach) array<ParticleSystemAttachInfo> InitAttachedParSys						<DisplayName="InitAttachedParSys">;
// 为了方便策划配置，改成struct列表的方式
struct native ParticleAttachInfo
{	
	// 用于标识的名字
	//var() Name AttachName <DisplayName="AttachName">;

	// 用于创建粒子特效并绑定上去
	var() Name AttachSocket <DisplayName="AttachSocket"|DynamicList="SocketList">;

	// 粒子特效模板
	var() ParticleSystem EmitterTemplate <DisplayName="EmitterTemplate">;

	// 缩放
	var() float		Scale <DisplayName="Scale">;

	structdefaultproperties
	{
		Scale=1.0
	}
};
var(MMOAttach) editinline array<ParticleAttachInfo> AttachedParticles		<DisplayName="AttachedParticles">;

var(MMOStatusProc) editinline array<IMMOStatusProc> AvatarSpawnProcList					<DisplayName="AvatarSpawnProcList">;

// the placement node tag for UI display
var(UI) name	PlacementNodeTag	<DisplayName="UINodeTag">;

struct native ExplosionData
{
	var() EElementaryType           Type;
	var() editinline array<AbilityComponent>   ExplosionComponents; 
};

var(Dead) array<ExplosionData>      OverrideExplosionEffects;

var(Lighting) bool	OverrideLightingChannels;
var(Lighting) LightingChannelContainer	LightingChannels;
var(Lighting) bool	UseSHLighting;

var() editconst AbilityAnimationComponent TurnLeftAction;
var() editconst AbilityAnimationComponent TurnRightAction;

//var(color) array<linearcolor>	SkinColorSet;
var(color) array<linearcolor>	HairColorSet;

var(color) transient editoronly int	TestSkinColorIdx;
var(color) transient editoronly int	TestHairColorIdx;

var(color) linearcolor	SkinSpecular;
var(color) linearcolor	SilhouetteColor;

// 合并属性,only for editor
var transient init array<Texture2D> SkinTextures;		// base textures of default meshes
var transient init array<Texture2D> SkinTexturesBase;
var transient MMOSkeletalMeshMerge	MergedMesh;		// use the merged mesh instead of separate meshes
var transient SkeletalMeshComponent	MergedComp;
var transient SkeletalMeshComponent BaseComponent;
var transient bool	bIsMerging;
var transient bool	bIsPreparing;

native final function float GetMoveSpeed(EActorMoveType InMoveType);
// if the return value <= 0.f, it means that there is some error, no need to toggle the move anim.
native final function float GetToggleMoveAnimCriticalSpeed();

native final function DynamicLoadPhysicAsset();

native function bool NeedToBeMerged();

event float GetWeightScale()
{
	switch(PhysicsBodyType)
	{
	case EBDT_Light:
		return 1.0f;
	case EBDT_Heavy:
		return 0.5f;
	case EBDT_SuperHeavy:
		return 0;
	default:
		return 0.75f;
	}
}

event string GetDetailedDescription( int InIndex )
{
	local string Description;
	switch( InIndex )
	{
	case 1:
		Description = AvatarName;
		break;
	default:
		break;
	}
	return( Description );
}
cpptext
{
	virtual FString GetDetailedDescription( INT InIndex )
	{
		return eventGetDetailedDescription(InIndex);
	}

	void RebulidMesh(USkeletalMeshComponent* BaseSMC, USkeletalMeshComponent* InMergedComponent);
	void TickMerge(FLOAT Delta);
	void PostRebuildMesh();
	UPhysicsAsset* LoadPhysicsAsset();
	
	static void ToogleBoneBreak(USkeletalMeshComponent* mesh, UBOOL breakWeight = TRUE);
}




// 绑定可破坏部件
function AttachDestructablePart(DestructablePartAttachInfo dpai , MMOActor actor)
{
	actor.AttachDestructablePart(dpai);
	dpai.AttachActor(actor);
}

// 解除可破坏部件
function DetachDestructablePart(DestructablePartAttachInfo dpai , MMOActor actor)
{
	actor.DetachDestructablePart(dpai);
}

event OnExecute(MMOActor Actor)
{
	local DestructablePartAttachInfo asm;
	//local ParticleSystemAttachInfo info;
	local ParticleAttachInfo info;
	local ParticleSystemAttachInfo psai;
	local int num;
	local int i;


	for(i = 0; i < AvatarSpawnProcList.Length;++i)
	{
		AvatarSpawnProcList[i].OnExecute(Actor);
	}


	if(InitAttachDestructableParts.Length>0)
	{

		num = actor.AttachedDestructableParts.Length;

		foreach InitAttachDestructableParts(asm)
		{
			asm = new asm.Class ( asm );
			AttachDestructablePart(asm,actor);
		}

		for(i=0;i<num;++i)
		{
			DetachDestructablePart(actor.AttachedDestructableParts[0]   ,actor );
		}
	}

	//if(InitAttachedParSys.Length>0)
	//{
	//	while(actor.AttachedParSys.Length > 0)
	//	{
	//		actor.DetachParticleSystem(actor.AttachedParSys[0] );
	//	}

	//	foreach InitAttachedParSys(info)
	//	{
	//		actor.AttachParticleSystem(info);
	//	}			
	//	
	//}

	// fix bug #23180
	while (Actor.AttachedParSys.Length > 0)
	{
		Actor.DetachParticleSystem(Actor.AttachedParSys[0]);
	}

	foreach AttachedParticles( info )
	{
		//`Log( "********AttachParticle"@info.EmitterTemplate );
		psai = new class'ParticleSystemAttachInfo';
		psai.AttachSocket = info.AttachSocket;
		psai.EmitterTemplate = info.EmitterTemplate;
		psai.EffectScale = info.Scale;
		Actor.AttachParticleSystem(psai);
	}
}

native function EquipMesh GetDefaultEquipMeshByType(EBodyMeshType type);

defaultproperties
{
	AvatarDrawScale=1.0
	PlacementNodeTag=Place01
	PhysicsBodyType=EBDT_Middle
	DefaultMoveSpeed=580.0
	OverrideLightingChannels=false
	UseSHLighting=false
	WalkSpeed=-1.f
	RunSpeed=-1.f
	FlySpeed=-1.f
	MeshScale=1.f
	//bLoadedPhysicAsset=false
	RotatoDegreePerSecond=360.f
	ToggleMoveAnimCriticalValue=0.5
	HintNameOffsetZ=0.0

	Begin Object Class=AbilityAnimationComponent Name=TurnLeft
		bLoop=true
	End Object
	TurnLeftAction=TurnLeft;

	Begin Object Class=AbilityAnimationComponent Name=TurnRight
		bLoop=true
	End Object
	TurnRightAction=TurnRight;

	SkinSpecular=(R=0.478,G=0.437,B=0.432)
	SilhouetteColor=(R=0.32,G=0.32,B=0.30)

	UseMergedMesh=false
	MergeShoulder=false
}