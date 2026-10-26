/**
*	ProceduralFoliage.cpp
*/

#include "stdafx.h"
#include "FileHelpers.h"

IMPLEMENT_CLASS(UProceduralFoliage)
IMPLEMENT_CLASS(UIProceduralFoliageLayerGenerator)
IMPLEMENT_CLASS(UProceduralFoliageLayerGenerator_Noise)
IMPLEMENT_CLASS(UProceduralFoliageLayerGenerator_Random)
IMPLEMENT_CLASS(UIProceduralFoliageMeshGenerator)
IMPLEMENT_CLASS(UProceduralFoliageMeshGenerator_Circular)
IMPLEMENT_CLASS(UProceduralFoliageMeshGenerator_Overlap)

IMPLEMENT_CLASS(AProceduralFoliageVolume)

//Bruce@snda

class PerlinNoise
{
public:
	//herein lies Perlin's original implementation
	/* coherent noise function over 1, 2 or 3 dimensions */
	/* (copyright Ken Perlin) */
	void init(void);
	float noise1( float arg );
	float noise2( float vec[2] );
	float noise3( float vec[3] );
	void normalize2( float v[2] );
	void normalize3( float v[3] );

	//hereafter lies MF's original extensions
	float sumHarmonics2( float vec[2], float persistence, float frequency, float nIterations, int NoiseTypeVal );
private:

};

#define B 0x100
#define BM 0xff

static int p[B + B + 2];
static float g3[B + B + 2][3];
static float g2[B + B + 2][2];
static float g1[B + B + 2];
static bool start = true;

#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3.0f - 2.0f * t) )

#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.0f;


float PerlinNoise::noise1( float arg )
{
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if ( start ) 
	{
		start = false;
		init();
	}

	setup( 0, bx0, bx1, rx0, rx1 );

	sx = s_curve( rx0 );

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

    return Lerp(u, v, sx);
}


float PerlinNoise::noise2( float vec[2] )
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	register int i, j;

	if ( start )
	{
		start = false;
		init();
	}

	setup( 0, bx0, bx1, rx0, rx1 );
	setup( 1, by0, by1, ry0, ry1 );

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = Lerp(u, v, sx);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = Lerp(u, v, sx);

	return Lerp(a, b, sy);
}


float PerlinNoise::noise3( float vec[3] )
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register int i, j;

	if (start) {
		start = false;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = Lerp(u, v, t);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = Lerp(u, v, t);

	c = Lerp(a, b, sy);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = Lerp(u, v, t);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = Lerp(u, v, t);

	d = Lerp(a, b, sy);

	return Lerp(c, d, sz);
}

void PerlinNoise::normalize2(float v[2])
{
	float s;

	s = sqrtf(v[0] * v[0] + v[1] * v[1]);
	v[0] /= s;
	v[1] /= s;
}

void PerlinNoise::normalize3( float v[3] )
{
	float s;

	s = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

void PerlinNoise::init( void )
{
	int i, j, k;

	for (i = 0 ; i < B ; i++) {
		p[i] = i;

		g1[i] = (float)((rand() % (B + B)) - B) / B;

		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (float)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (float)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[B + i][j] = g3[i][j];
	}
}


/**
 *	Produces a weighted sum of multiple harmonics of basic Perlin noise.
 *	It tries to return a value between 0.0 and 1.0
 *
 *	@param	vec				the input coordinates
 *	@param	persistence		the cumulative relative weighting for each harmonic.
 *	@param	frequency		the frequency of the harmonics
 *	@param	nIterations		the number of harmonics to blend
 */
float PerlinNoise::sumHarmonics2( float vec[2], float persistence, float frequency, float nIterations, int NoiseTypeVal )
{
	float curr[2], norm[2];
	curr[0] = vec[0];
	curr[1] = vec[1];
	curr[0] *= frequency;
	curr[1] *= frequency;
	norm[0] = vec[0];
	norm[1] = vec[1];
	normalize2(norm);
	norm[0] *= frequency;
	norm[1] *= frequency;

	float sum = 0.f;
	float scale = 1.f;
	float i = 0.f;

	while (i < nIterations)
	{
		switch ( NoiseTypeVal )
		{
			case 0:
				sum += (scale * this->noise1( curr[0] ));
				break;
			case 1:
				sum += (scale * this->noise2( curr ));
				break;
			default:
				sum += (scale * this->noise3( curr ));
				break;
		}
		scale *= persistence;
		norm[0] += norm[0];	//1, 2, 4, 8, 16 etc.
		norm[1] += norm[1];	//1, 2, 4, 8, 16 etc.
		i += 1.f;
		curr[0] += norm[0];
		curr[1] += norm[1];
	}

	return sum + 0.5f;
}

PerlinNoise	GNoise;
TArray<UProceduralFoliage*> GProceduralFoliage;
//------------------------------------------------------------------------
TArray<UProceduralFoliage*> UProceduralFoliage::Singleton()
{
	return GetSingleton();
}
//------------------------------------------------------------------------
void UProceduralFoliage::SavePackage()
{
	UPackage* PackageToSave = GetProceduralFoliagePackage();
	FString PackageName = PackageToSave->GetName();
	FString ExistingFile;
	FString SaveFileName;

	if( GPackageFileCache->FindPackageFile( *PackageName, NULL, ExistingFile ) )
	{
		// If the package already exists, save to the existing filename.
		SaveFileName = ExistingFile;
	}


	TArray<UPackage*> Packages;
	Packages.AddItem(PackageToSave);
	FEditorFileUtils::PromptForCheckoutAndSave(Packages, TRUE, TRUE);

}
//------------------------------------------------------------------------
const TArray<UProceduralFoliage*>& UProceduralFoliage::GetSingleton()
{
	UPackage* Package = GetProceduralFoliagePackage();
	
	GProceduralFoliage.Empty();

	TObjectIterator<UProceduralFoliage> It;
	for (; It; ++It)
	{
		GProceduralFoliage.AddItem(*It);
	}

	return GProceduralFoliage;
}
//------------------------------------------------------------------------
UPackage* UProceduralFoliage::GetProceduralFoliagePackage()
{
	FString PackageName = TEXT("ProceduralFoliageInfo.upk");
	FString ExistingFile, SaveFileName;

	if( GPackageFileCache->FindPackageFile( *PackageName, NULL, ExistingFile ) )
	{
		// If the package already exists, save to the existing filename.
		SaveFileName = ExistingFile;
	}

	UPackage* Package = LoadPackage( NULL, *PackageName, LOAD_NoWarn );
	if( !Package )
	{
		appErrorf( TEXT("Unable to load %s"), *PackageName );
	}

	if(!Package->IsFullyLoaded())
	{
		Package->FullyLoad();
	}

	return Package;
}
//------------------------------------------------------------------------

FLOAT UProceduralFoliageLayerGenerator_Noise::GetWeight(const FVector& WorldPoint) const
{
	FLOAT Vec[2];
	Vec[0] = WorldPoint.X;
	Vec[1] = WorldPoint.Y;	
	return GNoise.sumHarmonics2( Vec, Persistence, Frequency, 3.0f, NoiseType );
}

FLOAT UProceduralFoliageLayerGenerator_Random::GetWeight(const FVector& WorldPoint) const
{
	return appFrand();
}

void UProceduralFoliageMeshGenerator_Overlap::Generate(TArray<struct FSubProceduralFoliageInfo>& SubMeshAssetInfo, TArray<UStaticMesh*>& SubMeshAssets, TArray<FVector>& Offsets) const
{

}

void UProceduralFoliageMeshGenerator_Circular::Generate(TArray<struct FSubProceduralFoliageInfo>& SubMeshAssetInfo, TArray<UStaticMesh*>& SubMeshAssets, TArray<FVector>& Offsets) const
{
	INT Count = 0;
	INT TempNum;
	TArray<struct FSubProceduralFoliageInfo> MeshAssetsArrayTemp;

	for ( INT y = 0; y < SubMeshAsset.Num(); y++ )
	{
		TempNum = (INT)( RandRange( (FLOAT)( SubMeshAsset(y).QuantityMin ), (FLOAT)( SubMeshAsset(y).QuantityMax ) ) * SubMeshAsset(y).Probability );	

		for ( INT x = 0; x < TempNum; x++ )
		{
			MeshAssetsArrayTemp.AddItem( SubMeshAsset(y) );
		}

		Count += TempNum;
	}

	if ( MeshAssetsArrayTemp.Num() == 0 )
		return;

	TArray<struct FSubProceduralFoliageInfo> MeshAssetsArray;
	INT RandNum;
	do 
	{
		RandNum = RandHelper( ( MeshAssetsArrayTemp.Num() - 1 ) );
		MeshAssetsArray.Push( MeshAssetsArrayTemp( RandNum ) );
		MeshAssetsArrayTemp.Remove( RandNum );
	} while ( MeshAssetsArrayTemp.Num() );	
	
	FLOAT AngleYaw = 2 * PI / Count;
	FLOAT RadiusRand;
	FLOAT TempAngle = AngleYaw;
		
	for ( INT i = 0; i < Count; ++i )
	{
		FVector Offset;

		RadiusRand = RandRange( MeshAssetsArray( i ).InnerRadius, MeshAssetsArray( i ).OuterRadius );

		Offset.X = RadiusRand * cosf( TempAngle );
		Offset.Y = RadiusRand * sinf( TempAngle );

		SubMeshAssets.Push( MeshAssetsArray( i ).MeshAsset );
		SubMeshAssetInfo.Push( MeshAssetsArray( i ) );
		Offsets.Push( Offset );

		TempAngle += AngleYaw;
	}
}

//Bruce@snda

