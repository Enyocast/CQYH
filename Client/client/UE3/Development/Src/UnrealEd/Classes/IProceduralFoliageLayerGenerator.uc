
interface IProceduralFoliageLayerGenerator
	native;

cpptext
{
	virtual FLOAT GetWeight(const FVector& WorldPoint) const = 0;
}
