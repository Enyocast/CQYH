//
// 粒子系统绑定的信息
//
class ParticleSystemAttachInfo extends Object
	editinlinenew
	hidecategories(Object);

// 用于标识的名字
var() Name AttachName <DisplayName="AttachName">;

// 用于创建粒子特效并绑定上去
var() Name AttachSocket <DisplayName="AttachSocket"|DynamicList="SocketList">;

// 粒子特效模板
var() ParticleSystem EmitterTemplate <DisplayName="EmitterTemplate">;

var() bool BindToWeapon;
var() EWeaponType WeaponType<EditCondition=BindToWeapon>;
var() float EffectScale;
var() name VertSurfaceActorParameterName;

// 临时存储对象的变量
var ParticleSystemComponent EmitterInstance;

DefaultProperties
{
	BindToWeapon=FALSE
	EffectScale=1
	VertSurfaceActorParameterName=VertSurfaceActor
}
