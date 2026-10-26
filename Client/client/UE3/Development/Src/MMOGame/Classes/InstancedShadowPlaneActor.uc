/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
class InstancedShadowPlaneActor extends Actor
	native
	hidecategories(Object);

var string    MeshPatchName;
var transient InstancedStaticMeshComponent instancedShadowPlane;
var	transient native Map_Mirror FoliageMeshes{TMap<int, int>};
var transient array<int> InstanceList;
var transient int       currentIndex;
var transient Matrix initMatrix;
var transient float  zOffset;
var transient float  fixedScale;

// struct native EquipNode
// {
// 	var EBodyMeshType BodyMeshType;
// 	var Object ComponentOrActor;
// 	var bool bVisible;
// };



native function int AddInstance( Vector InstanceTransform, float Scale ); 
native function Refresh( int index, Vector InstanceTransform );
native function ReleaseInstance( int index );
native function UpdateComponentsInternal(bool bCollisionUpdate = FALSE);
native function ApplySeting();
//native function PostBeginPlay();
native function BeginDestroy();
cpptext
{
	static AInstancedShadowPlaneActor* g_pInstance;	
	virtual void PostBeginPlay();
	//virtual UBOOL Tick( FLOAT DeltaTime, enum ELevelTick TickType );
	static AInstancedShadowPlaneActor* GetInstancedShadowPlaneActor(UBOOL bCreateIfNone=TRUE);
	static void ReleaseAllShadowPlaneActor();
	static void InitAllShadowPlaneActor();
	static void NotifyOptionChange();
}
defaultproperties
{
	bStatic=false
	MeshPatchName="MMO_PlaneShow.PlaneShow.PlaneShowMesh"
	currentIndex=0
	zOffset=10
	fixedScale=1.2f
}