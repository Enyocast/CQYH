/**
 *
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */

class ProceduralFoliage
	extends Object
	hidecategories(Object)
	native;

struct native ProceduralFoliageInfo
{
	var() StaticMesh MeshAsset;
	var() editinline IProceduralFoliageLayerGenerator LayerGenerator;

	var() int WeightPow <ClampMin=1.0 | ClampMax=10.0>;
	var(Painting) float Probability	<ClampMin=-1.0 | ClampMax=1.0>;
	var(Painting) float ScaleMinX	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMinY	    <ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMinZ	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxX	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxY	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxZ	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float GroundSlope	<ClampMin=0.0 | ClampMax=90.0>;
	var(Painting) float HeightMin;
	var(Painting) float HeightMax;
	var(Painting) bool AlignToNormal;
	var(Painting) bool RandomYaw;
	var(Painting) bool UniformScale;
	var(Painting) float RandomPitchAngle;
	var(Painting) float ZOffsetMin	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ZOffsetMax	<ClampMin=0.1 | ClampMax=10.0>;

	structdefaultproperties
	{
		WeightPow=1
		Probability=0.0
		ScaleMinX=1.0
		ScaleMinY=1.0
		ScaleMinZ=1.0
		ScaleMaxX=1.0
		ScaleMaxY=1.0
		ScaleMaxZ=1.0
		GroundSlope=45.0
		HeightMin=-262144.0
		HeightMax=262144.0
		AlignToNormal=true
		RandomYaw=true
		UniformScale=true
		RandomPitchAngle=0.0
		ZOffsetMin=0.0
		ZOffsetMax=0.0
	}
};

struct native SubProceduralFoliageInfo
{
	var() StaticMesh MeshAsset;

	var(Painting) float ScaleMinX	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMinY	    <ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMinZ	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxX	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxY	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ScaleMaxZ	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float GroundSlope	<ClampMin=0.0 | ClampMax=90.0>;
	var(Painting) float HeightMin;
	var(Painting) float HeightMax;
	var(Painting) bool AlignToNormal;
	var(Painting) bool RandomYaw;
	var(Painting) bool UniformScale;
	var(Painting) float RandomPitchAngle;
	var(Painting) float ZOffsetMin	<ClampMin=0.1 | ClampMax=10.0>;
	var(Painting) float ZOffsetMax	<ClampMin=0.1 | ClampMax=10.0>;

	var() float Probability	<ClampMin=0.0 | ClampMax=20.0>;
	var() int QuantityMin  <ClampMin=0 | ClampMax=100>;
	var() int QuantityMax  <ClampMin=1 | ClampMax=100>;
	var() float InnerRadius  <ClampMin=0.0 | ClampMax=1000.0>;
	var() float OuterRadius  <ClampMin=10.0 | ClampMax=1000.0>;

	structdefaultproperties
	{
		ScaleMinX=1.0
		ScaleMinY=1.0
		ScaleMinZ=1.0
		ScaleMaxX=1.0
		ScaleMaxY=1.0
		ScaleMaxZ=1.0
		GroundSlope=45.0
		HeightMin=-262144.0
		HeightMax=262144.0
		AlignToNormal=true
		RandomYaw=true
		UniformScale=true
		RandomPitchAngle=0.0
		ZOffsetMin=0.0
		ZOffsetMax=0.0

		Probability=1.0
		QuantityMin=3
		QuantityMax=6
		InnerRadius=50.0
		OuterRadius=100.0
	}
};

struct native ProceduralFoliageLayerInfo
{
	var() Texture2D LayerTexture;
	var() editinline array<ProceduralFoliageInfo> FoliageInfos;
};

struct native ProceduralFoliageMeshInfo
{
	var() StaticMesh MeshAsset;
	var() editinline IProceduralFoliageMeshGenerator MeshGenerator;
};

var() editinline array<ProceduralFoliageLayerInfo> ProceduralFoliageLayerInfos;
var() editinline array<ProceduralFoliageMeshInfo> ProceduralFoliageMeshInfos;

static native function array<ProceduralFoliage> Singleton();
native final function SavePackage();

cpptext
{
	static const TArray<UProceduralFoliage*>& GetSingleton();
	static UPackage* GetProceduralFoliagePackage();
}

defaultproperties
{

}
