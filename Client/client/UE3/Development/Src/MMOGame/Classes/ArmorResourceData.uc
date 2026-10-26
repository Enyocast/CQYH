class ArmorResourceData extends Object
	EditInlineNew
	hidecategories(Object)
	native;


enum EArmorActorResourceType
{
	EAART_StaticMesh,
	EAART_SkeletalMesh,
	EAART_Particle,
};

struct native ParticleAttachNode
{
	var() Vector RelativeLocation;
	var() Rotator RelativeRotation;
	var() ParticleSystem Particles;
};

// add by zhangrui05@sndas
struct native SkeletalMeshParticleAttachNode
{
	var() name BoneName;
	var() ParticleSystem Particle;
};

var() EArmorActorResourceType Type;
var() float Scale;
var() array<ParticleAttachNode> AttachList;
var() ParticleSystem MeshSurfaceParticle;
var() name AttachSocket0    <DynamicList="SocketList">;//default attach socket
var() name AttachSocket1    <DynamicList="SocketList">;



var(StaticMesh) StaticMesh StaticMeshTemplate;
var(StaticMesh) StaticMesh StaticMeshShellTemplate;

var(SkeletalMesh) SkeletalMesh SkeletalMeshTemplate;
var(SkeletalMesh) AnimSet WeaponAnimSet; 
var(SkeletalMesh) name OverrideIdleAnim;
var(SkeletalMesh) array<SkeletalMeshParticleAttachNode> ParticleAttachList;

var(Particle) ParticleSystem ParticleSystemTemplate;






DefaultProperties
{
	Scale=1.0
}
