class MMOVolume_WaterVolume extends WaterVolume
	hidecategories(WaterVolume)
	placeable;

simulated event Touch( Actor Other, PrimitiveComponent OtherComp, vector HitLocation, vector HitNormal )
{}

event untouch(Actor Other)
{}

defaultproperties
{
}
