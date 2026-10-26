/*
 * MMOACTOR类型角色,材质颜色修改器,半透明修改组件
 * 
 * */
class AbilityComp_MaterialEffect extends AbilityComponent
	dependson(TypeDefine)
	editinlinenew
	native;

var(Common) ESourceType SourceType;
var(Common) EMaterialEffectType EffectType;
var(ChangeMaterialProperty) int EffectTemplateId;
var(ChangeMaterialEffect) MaterialInstance EffectMaterialInstance;
var(ChangeMaterial) bool CanBeDeleteWhenSetNewMaterial;
var(ChangeMaterial) int Priority;



var transient float LeftTime;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}



DefaultProperties
{
	CanBeDeleteWhenSetNewMaterial=true
	Priority=0
}
