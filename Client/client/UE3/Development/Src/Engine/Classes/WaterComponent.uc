
class WaterComponent extends PrimitiveComponent
	native
	hidecategories(Object)
	editinlinenew;

var const StaticMesh StaticMesh;

var(Mesh) bool FrustumCullInHS;
var(Mesh) bool UseDynamicLOD;
var(Mesh) byte DynamicTessFactor<ClampMin=0 | ClampMax=100 | UIMin=1 | UIMax=100>;
var(Mesh) byte StaticTessFactor<ClampMin=0 | ClampMax=63 | UIMin=1 | UIMax=63>;

var(Mesh) float WaterBumpTexcoordShiftX<UIMin=0 | UIMax=10>;
var(Mesh) float WaterBumpTexcoordShiftY<UIMin=0 | UIMax=10>;

var(Mesh) float WaterMicroBumpTexcoordScaleX<UIMin=1 | UIMax=512>;
var(Mesh) float WaterMicroBumpTexcoordScaleY<UIMin=1 | UIMax=512>;

var(Mesh) float WaterBumpTexcoordScaleX<UIMin=1 | UIMax=20>;
var(Mesh) float WaterBumpTexcoordScaleY<UIMin=1 | UIMax=20>;


//var(Mesh) float WaterSizeScaleX<UIMin=1 | UIMax=100>;
//var(Mesh) float WaterSizeScaleY<UIMin=1 | UIMax=100>;

// var(Mesh) float WaterHeightBumpScale<UIMin=0 | UIMax=100>;
// var(Mesh) float HeightFieldSize<UIMin=12800 | UIMax=819200>;
// 
// var(WaterColor) LinearColor WaterDeepColor;
// var(WaterColor) float WaterColorIntensityX<UIMin=0 | UIMax=1>;
// var(WaterColor) float WaterColorIntensityY<UIMin=0 | UIMax=1>;
// 
// var(WaterColor) LinearColor WaterScatterColor;
// var(WaterColor) float WaterScatterColorPower<UIMin=1 | UIMax=64>;
// 
// var(WaterColor) LinearColor WaterSpecularColor;
// var(WaterColor) float WaterSpecularIntensity<UIMin=0 | UIMax=10>;
// var(WaterColor) float WaterSpecularPower<UIMin=1 | UIMax=4096>;

var(WaterColor) Texture2D WaterBumpTexture;
var(WaterColor) Texture2D WaterDepthMap;

var(Light) Vector LightPosition;

var(Foam) bool RenderFoam;
var(Foam) Texture2D FoamTexture<editcondition=RenderFoam>;

var(Caustics) bool RenderCaustics;
var(Caustics) Texture2D CausticsTexture<editcondition=RenderCaustics>;

var(Reflection) bool RenderReflection;
var(Reflection) bool RenderRefraction;
var(Reflection) TextureCube ReflectionCube;

var(Fog) bool	RenderFog;
var(Fog) float	FogDensity;
var(Fog) LinearColor      AtmosphereBrightColor;
var(Fog) LinearColor      AtmosphereDarkColor;

var MaterialInterface DefaultMaterial;


cpptext
{
	/**
	 * Creates a new scene proxy for the path rendering component.
	 * @return	Pointer to the ServerTriggerSceneProxy
	 */
	virtual FPrimitiveSceneProxy* CreateSceneProxy();
};

defaultproperties
{
	StaticMesh=StaticMesh'MMO_MaterialTemplateMesh.Mesh.SM_Ocean'
	FoamTexture=Texture2D'Water.Texture.T_Foam'
	WaterBumpTexture=Texture2D'Water.Texture.T_WaterNormal'
	//DefaultMaterial=MaterialInstanceConstant'Water.Materials.MT_DefaultWater_INST'
	WaterDepthMap=Texture2D'Water.Texture.T_Water_depth'

	RenderFoam=true
	RenderCaustics=true
	RenderReflection=true
	RenderRefraction=true
	RenderFog=true

// 	WaterDeepColor=(R=0.1,G=0.4,B=0.7,A=1)
// 	WaterScatterColor=(R=0.3,G=0.7,B=0.6,A=1)
// 	WaterScatterColorPower=8
// 
// 	WaterSpecularColor=(R=1,G=1,B=1,A=1)
// 	WaterSpecularIntensity=100
// 	WaterSpecularPower=1000
// 
// 	WaterColorIntensityX=0.1
// 	WaterColorIntensityY=0.2

	FogDensity=1.0f/700.0f
	AtmosphereBrightColor=(R=1.0,G=1.1,B=1.4,A=1)
	AtmosphereDarkColor=(R=0.6,G=0.6,B=0.7,A=1)

	FrustumCullInHS=true
	UseDynamicLOD=false
	DynamicTessFactor=20
	StaticTessFactor=10


	WaterMicroBumpTexcoordScaleX=225
	WaterMicroBumpTexcoordScaleY=225

	WaterBumpTexcoordScaleX=7
	WaterBumpTexcoordScaleY=7

// 	WaterHeightBumpScale=1
// 	HeightFieldSize=512

	WaterBumpTexcoordShiftX=1.5
	WaterBumpTexcoordShiftY=0.75

	LightPosition=(x=1000000,y=1000000,z=600000)


	//WaterSizeScaleX=1
	//WaterSizeScaleY=1

	ReflectionCube=TextureCube'MMO_MaterialTemplateTextureOld.Skybox.T_Cube_Clouds_Noon'
}