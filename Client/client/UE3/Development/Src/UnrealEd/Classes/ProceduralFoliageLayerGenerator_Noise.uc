
class ProceduralFoliageLayerGenerator_Noise extends Object implements(IProceduralFoliageLayerGenerator)
	native
	editinlinenew
	hidecategories(Object);

enum FoliageNoiseType
{
	Noise_Constant,
	Noise_Linear,
	Noise_Interpolate,
};

var() float Frequency;
var() float Persistence;
var()	FoliageNoiseType NoiseType;

cpptext
{
	virtual FLOAT GetWeight(const FVector& WorldPoint) const;
}

defaultproperties
{
	Frequency=10.0f
	Persistence=0.75f
	NoiseType=Noise_Interpolate
}