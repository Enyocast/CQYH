//=============================================================================
// DunDefEmitterSpawnable: An Actor used for one-off spawning dynamic particle effects. 
// Supports sound effects and dynamic lighting that fade in & out with the particle lifespan.
// Not particularly efficient (haha), DO NOT use for static particles, would be a waste.
//
// Author: Jeremy Stieglitz, December 2009
//=============================================================================

class MMORadialBlurActor extends RadialBlurActor;


var(MMO) float FadeInTime;
var(MMO) float FadeInScale;
var(MMO) float FadeOutTime;

var bool IsFadeIn;
var bool IsFadeOut;

simulated event PostBeginPlay()
{
	super.PostBeginPlay();

}

event Tick(float DeltaTime)
{
	local float scale;

	super.Tick(DeltaTime);
	
	if(IsFadeIn)
	{
		if(RadialBlur.BlurScale < FadeInScale)
		{
			scale = RadialBlur.BlurScale + FadeInScale * DeltaTime / FadeInTime;
			RadialBlur.SetBlurScale(scale);
			//`log("OSCAR:_____ in blur scale:" @scale);
		}
		else
		{
			RadialBlur.SetBlurScale(FadeInScale);
			IsFadeIn = false;
		}
	}
	else if(IsFadeOut)
	{
		if(RadialBlur.BlurScale > 0)
		{
			scale = RadialBlur.BlurScale - FadeInScale * DeltaTime / FadeOutTime;
			RadialBlur.SetBlurScale(scale);
			//`log("OSCAR:_____ out blur scale:" @scale);
		}
		else
		{
			RadialBlur.SetBlurScale(0);
			IsFadeOut = false;
			RadialBlur.SetEnabled(false);
		}
	}
}

function FadeIn(float fadeTime, float fadeScale)
{
	RadialBlur.SetEnabled(true);
	FadeInTime = fadeTime;
	FadeInScale = fadeScale;
	RadialBlur.SetBlurScale(0);
	IsFadeIn = true;
	//`log("OSCAR:Blur _________ true");
}

function FadeOut(float fadeTime)
{
	FadeOutTime = fadeTime;
	RadialBlur.SetBlurScale(FadeInScale);
	IsFadeOut = true;
}

DefaultProperties
{
	FadeInTime=0.3
	FadeOutTime=0.1
	FadeInScale=1
}