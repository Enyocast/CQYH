
interface IProceduralFoliageMeshGenerator
	native;

cpptext
{
	virtual void Generate(TArray<struct FSubProceduralFoliageInfo>& SubMeshAssetInfo, TArray<UStaticMesh*>& SubMeshAssets, TArray<FVector>& Offsets) const = 0;
}
