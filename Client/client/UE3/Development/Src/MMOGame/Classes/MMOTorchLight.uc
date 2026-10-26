class MMOTorchLight extends PointLightToggleable
		native
  	    ClassGroup(Light,PointLight,__MMO__)
	    placeable;
var				  float CurrentParameter;
var				  float CurrentBrightness;
var				  float LastUpdateWindTime;
var(LightShining) float BrightnessFactor		<DisplayName="BrightnessFactor">;
var(LightShining) float BrightnessRange			<DisplayName="BrightnessRange">;
var(LightShining) float BrightnessFrequency		<DisplayName="BrightnessFrequency">;
var(LightShining) float WindAffect				<DisplayName="WindAffect">;
var(LightShining) float WindAffectTime				<DisplayName="WindAffectTime">;

cpptext
{
	void PostBeginPlay();
	void SetCurrentBrightness( float Brightness );
	void UpdateShining(FLOAT DeltaTime);
	UBOOL Tick( FLOAT DeltaTime, enum ELevelTick TickType );
}

DefaultProperties
{
	BrightnessFactor  = 1;
    CurrentParameter  = 0;
	LastUpdateWindTime = 0;
	CurrentBrightness = 0
	BrightnessRange = 0.2
	WindAffectTime  = 0.3
	WindAffect      = 0.4
	BrightnessFrequency = 1.2
}