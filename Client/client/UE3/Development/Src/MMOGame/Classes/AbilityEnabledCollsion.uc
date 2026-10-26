/*
 * MMOACTOR类型角色,材质颜色修改器,半透明修改组件
 * 
 * */
class AbilityEnabledCollsion extends AbilityComponent
	dependson(TypeDefine)
	editinlinenew
	native;

var() bool   Enabled;

event Play(Actor BaseActor, MMOAbility AbilityData, Actor Target, Vector TargetPoint, float InRate, optional int SerialId = 0)
{
	if(BaseActor == none)
	{
		return;
	}
	BaseActor.bEnabledCollsion = Enabled;
}



DefaultProperties
{
	Enabled = true
}
