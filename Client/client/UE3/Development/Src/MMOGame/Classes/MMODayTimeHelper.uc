
// zhangrui@snda
class MMODayTimeHelper extends Actor
	native
	placeable;

var(Display) const interp Color LightMapScale;
//shanling@snda
var(Display) const interp Color TorchLightcolor;
var(Display) const interp float TorchLightBrightness;
//zhaojun@snda
var(Display) const interp Color LuminanceThreshold;
//shanling@snda
var(Display,NewToneMaping,NewLuminanceParameter) const interp float NewLimitLuminance;
var(Display,NewToneMaping,NewLuminanceParameter) const interp float NewMiddleLuminance;
var(Display,NewToneMaping,NewLuminanceParameter) const interp float NewWhiteLuminance;
var(Display,NewToneMaping) const interp float  NewAvgLuminanceParameter;
//shanling@snda

// day and night
var transient DominantDirectionalLight MainLight;
var transient Color MainLightColor;
var transient float MainLightIntensity;
var transient init array<DirectionalLightToggleable> DirectionalLights;
var transient init array<Color> DirectionalLightColors;
var transient init array<float> DirectionalLightIntensities;

// list of mmoactors that needs to update their light environments during the day-night change
var transient init array<MMOActor>	DynamicActors;

//shanling@snda
var transient init array<MMOTorchLight>	TorchLights;
var transient float DefaultTorchLightBrightness;
cpptext
{
	void SetLightIntensity( FLOAT Intensity );

	void PostBeginPlay();
	void TickSpecial(FLOAT DeltaTime);
    void ForceUpdateComponents(UBOOL bCollisionUpdate=FALSE,UBOOL bTransformOnly=TRUE);

	void InsetTorchLight( AMMOTorchLight *plithgt );
	void GetTorchLights();
	void ClearTorchLights();
	void UpdateTorchLightsBrightness();
}

defaultproperties
{
	LightMapScale=(R=255,G=255,B=255,A=255)

	TorchLightcolor = (R=255,G=255,B=255,A=255)
	TorchLightBrightness = 1.0
	DefaultTorchLightBrightness = 1.0

	// zhaojun@snda
	LuminanceThreshold = (R=255,G=255,B=255,A=255)

	//shanling@snda
	NewLimitLuminance  = 0;
	NewMiddleLuminance = 0.5;
	NewWhiteLuminance  = 1.0;
	NewAvgLuminanceParameter = 0.5;

	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'MMOEditor.ServerTrigger'
		HiddenGame=True
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
		SpriteCategoryName="MMO"
		//Scale=0.2
	End Object
	Components.Add(Sprite);
}
