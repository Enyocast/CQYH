class MMOMapInfo extends MapInfo
	hidecategories(Object)
	native;

var() Vector2D Map2DExportSize;
//var() bool EnableActorPointLight;
var() PointLightMovable ActorPointLight;
//var() EServerMapType ServerMapType;

defaultproperties
{
	Map2DExportSize=(X=100,Y=100)
//	ServerMapType=SMT_Default
}
