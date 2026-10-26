
class ProceduralFoliageMeshGenerator_Overlap extends Object implements(IProceduralFoliageMeshGenerator)
	native
	editinlinenew
	hidecategories(Object);

var() editinline array<SubProceduralFoliageInfo> SubMeshAsset;

cpptext
{
	virtual void Generate(TArray<struct FSubProceduralFoliageInfo>& SubMeshAssetInfo, TArray<UStaticMesh*>& SubMeshAssets, TArray<FVector>& Offsets) const;
}

defaultproperties
{

}
