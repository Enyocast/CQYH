class MMOCameraAnchorPoint extends Actor
	placeable
	native;

var( ) int   AnchorId           <DisplayName="AnchorId">;

event PostBeginPlay( )
{
	/*local int CurrentCount;
	local MMOCameraAnchorPoint pt;
	foreach AllActors(class'MMOCameraAnchorPoint',pt)
		++CurrentCount;
	AnchorId=++CurrentCount;*/
}
DefaultProperties
{
	Begin Object Class=SpriteComponent Name=Sprite
		Sprite=Texture2D'EditorResources.S_NavP'
		HiddenGame=true
		HiddenEditor=false
		AlwaysLoadOnClient=False
		AlwaysLoadOnServer=False
	End Object
	Components.Add(Sprite)

	AnchorId=0
}
