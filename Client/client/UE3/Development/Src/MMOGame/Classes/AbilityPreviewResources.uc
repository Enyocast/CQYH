class AbilityPreviewResources extends Object
	hidecategories(Object)
	editinlinenew
	native;

var(Target) Vector          PositionOffset;

var(Caster) AvatarData      Attacker;
var(Target) AvatarData      Target;
var(Caster) bool            bMale;
var(Caster) array<Equip>    WeaponList;
var(Caster) EElementaryType OverriddenElementaryType;

var(Floor)  StaticMesh PreviewFloor;
var(Floor)  Vector      FloorPosition;

var(Hit) EDamageResultType ResultType;

var(Throw) float ThrowDistance;

var(Movement) bool bShowMovement;
var(Movement) Vector Velocity;


var transient init array<Texture2D> SkinTextures;		// base textures of default meshes
var transient init array<Texture2D> SkinTexturesBase;
var transient MMOSkeletalMeshMerge	AttackerMergedMesh;		// use the merged mesh instead of separate meshes
var transient SkeletalMeshComponent	AttackerMergedComp;
var transient SkeletalMeshComponent BaseComponent;
var transient bool	bIsMerging;
var transient bool	bIsPreparing;

cpptext
{
	void RebulidMesh(USkeletalMeshComponent* BaseSMC, USkeletalMeshComponent* MergedComponent);
	void Tick(FLOAT Delta);
	void PostRebuildMesh();
}

DefaultProperties
{
	PositionOffset=(X=300, Y=0, Z=0)
	FloorPosition=(X=0, Y=0, Z=-150)
	bMale=true
	ResultType=DRT_Result6
	ThrowDistance=500
	bShowMovement=false
	Velocity=(X=600, Y=0, Z=0)
	OverriddenElementaryType=0
	bIsMerging=false
	bIsPreparing=false
}
