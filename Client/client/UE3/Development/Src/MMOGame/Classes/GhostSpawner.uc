class GhostSpawner extends Object
	hidecategories(Object)
	native;

var() float SpawnNumPerPoint;
var() editinline AbilityEmitterComponent EmitterData;

final native function OnAction(int CreatorId, int TargetId, int InPoint);


DefaultProperties
{
	SpawnNumPerPoint=1.0
}
