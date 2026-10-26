class CameraShakeComponent extends AbilityComponent
	editinlinenew
	hidecategories(Object)
	native;

var(CameraShake) CameraAnim AnimToPlay;
var(CameraShake) float Scale;
var(CameraShake) float Rate;
var(CameraShake) float BlendInTime;
var(CameraShake) float BlendOutTime;
var(CameraShake) bool bLoop;
var(CameraShake) bool bRandomStartTime;
var(CameraShake) ECameraAnimPlaySpace Space;
var(CameraShake) rotator CustomPlaySpace;
var(CameraShake) bool bPlayInThirdPersonView;

var(CameraShake) float MaxFadeDistance;

cpptext
{
	virtual FString GetResName();
	virtual struct BaseComponent* CreateCplusplusNode();
}

event Shake(PlayerController InController, float InScale)
{
	if(InController == none)
	{
		return;
	}
	InController.ClientPlayCameraAnim(
				AnimToPlay,
				InScale,
				Rate, 
				BlendInTime, 
				BlendOutTime, 
				bLoop, 
				bRandomStartTime, 
				Space, CustomPlaySpace
				);
}

event StopShake(PlayerController InController)
{
	InController.ClientStopCameraAnim(AnimToPlay, false);
}

DefaultProperties
{
	Scale=1.f
	Rate=1.f
	BlendInTime=0.1f
	BlendOutTime=0.3f
	Space=CAPS_UserDefined
	LineColor=(R=0.9294,G=0.1098,B=0.1412,A=1.0)
	TitleString="CameraAnim"
	bHaveTrail=false
	MaxFadeDistance=3000
	bPlayInThirdPersonView=false

}
