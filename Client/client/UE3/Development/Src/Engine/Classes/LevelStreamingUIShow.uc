/**
 * LevelStreamingUIShow
 * ming@snda
 */
class LevelStreamingUIShow extends LevelStreamingAlwaysLoaded
	native;

var Actor						ShowActor;
//var SceneCapture2DActor		CaptureActor;
var array<SceneCapture2DActor>	CaptureActors;
var SceneCapture2DActor			CurrentCaptureActor;
//var array<PlayerStart>		PlacementNodes;
var PlayerStart					PlacementNode;
var TextureRenderTarget2D		RenderTarget;

native function bool Init();
native function SetEnabled( bool isEnabled );
native function SetShowActor( Actor a, name CameraTag/*PlacementTagName*/ );

cpptext
{
	/**
	*
	*/
}