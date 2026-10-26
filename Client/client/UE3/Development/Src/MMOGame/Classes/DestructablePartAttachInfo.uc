//
// 可破坏部件绑定的信息
//
class DestructablePartAttachInfo extends Object
	editinlinenew
	hidecategories(Object)
	native;

// 可破坏部件破坏方式
enum EDestructResultType
{
	EDRT_Hide	    <DisplayName="Hide">,
	EDRT_Replace	<DisplayName="Replace">,
	EDRT_Drop	    <DisplayName="Drop">
};

// 如果是静态模型则绑定到绑定点上，否则与主骨架共享动画
var() bool IsStaticMeshComponent;

// 只有可破坏的对象才会创建视觉表现，如爆炸特效、掉落等
var() bool IsDestructable;

var() EDestructResultType DestructType;

// 只有在动画通知时才掉落
var() bool DropByNotify;

// 当角色的血量少于这个值时会被破坏
var() float ExplodeHPPercent;

// 用于标识的名字
var() Name AttachName;

// 用于创建特效或是将静态模型绑定上去的Socket
var() Name AttachSocket <DynamicList="SocketList">;

// 用于绑定或是掉落的静态模型
var() StaticMesh MeshAsset;

// 用于组合绑定的骨架模型,changed by jimzhang 20122.7.14,用component替代Skeletal,为了能使用SkeletalMesh自己的动画
//var()   SkeletalMesh SkelMeshAsset;
var()   SkeletalMeshComponent SkelMeshComponent;

// 当装备破坏时产生的粒子效果
var() Emitter ExplodeEmitter;

// 破坏后替换显示模型的数据配置，可以递归指定不同的数据实现多级破坏
var() editinline DestructablePartAttachInfo ReplaceArmorTemplateOnDestruct;

// 是否是武器
var() bool IsWeapon;

//在角色跑动时会隐藏
var() bool HideWhenRun;

//var(MMOSFX) ParticleSystem BrokenEmitterTemplate <DisplayName="破坏时的粒子特效">;;

var public StaticMeshComponent MeshComponent;
//var public SkeletalMeshComponent SkelMeshComponent;

var MMOActorMaterialController RootMaterialController;

var MMOActorAT ActorAT;

function Init()
{
	RootMaterialController = new(self) class'MMOActorMaterialController';
	if(SkelMeshComponent != none)
	{
		RootMaterialController.Init( SkelMeshComponent );
	}
	else if( MeshComponent != none)
	{
		RootMaterialController.Init( MeshComponent );
	}

	`log("_____________ DestructablePartAttachInfo Init, Sk:" @ SkelMeshComponent @ MeshComponent);
}

function AttachActor(MMOActor actor)
{
	if(SkelMeshComponent==none && MeshComponent==none)
	{
		return;
	}
	if(ActorAT ==none ){
		ActorAT = new class'MMOActorAT';
	}
	ActorAT.InitAnim(SkelMeshComponent,actor);
}

DefaultProperties
{
	ActorAT = none;
	IsDestructable=true
	IsStaticMeshComponent=true
	DropByNotify=true
	IsWeapon=false
}
