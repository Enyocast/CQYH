/**
* MMORenderOnlyActor.uc
* a rendering-only clone of MMOActors
*/

class MMORenderOnlyActor extends Actor
	native;

var SkeletalMeshComponent	MainMesh;
var init array<EquipMesh>	EquipMeshList;

native function	Clone( MMOActor baseActor );

cpptext
{
	void AddEquipMeshByTemplate( UEquipMesh* temp, INT idx );

	void MergeEquipMeshes();

	void TakeOn( UEquipMesh* em );
	void TakeOff( UEquipMesh* em );
}

defaultproperties
{
}