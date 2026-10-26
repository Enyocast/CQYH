/**
 * 材质效果数据结点
 */
class MaterialInstanceTimeVaryingEffectNode extends Object
	native(Material)
	editinlinenew;


// 效果模版ID
var() int EffectTemplateId;

// 效果描述
var() string EffectDescribe;

var() array<ScalarParameterValueOverTime>		ScalarParameterValues;
var() array<VectorParameterValueOverTime>		VectorParameterValues;
var() array<LinearColorParameterValueOverTime>  LinearColorParameterValues;
var() array<TextureParameterValueOverTime>	    TextureParameterValues;

cpptext
{
	// UObject interface.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
}


defaultproperties
{

}
