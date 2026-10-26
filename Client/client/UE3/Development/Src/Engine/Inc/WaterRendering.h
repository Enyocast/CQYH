#ifndef __WATERRENDERING_H__
#define __WATERRENDERING_H__

#include "WaterConfig.h"

#if WITH_WATER

#include "..\Src\DrawingPolicy.h"

#define WATER_NEIGHBOR_NUM	4

#define WATER_LOD_LEVELS 8
// Do we need this define?
#define WATER_MAX_SUBSECTION_NUM 2

#define WATER_LOD_DISTANCE_FACTOR 2.f
#define WATER_MAX_COMPONENT_SIZE 64

#define WaterSizeScale 100


//------------------------------------------------------------------------
// FWaterVertexBuffer
//------------------------------------------------------------------------
class FWaterVertexBuffer : public FVertexBuffer, public FRefCountedObject
{
	INT SizeVerts;
public:
	struct FWaterVertex
	{
		FVector Position;
	};
	
	/** Constructor. */
	FWaterVertexBuffer(INT InSizeVerts)
	: 	SizeVerts(InSizeVerts)
	{
		InitResource(); // BeginInitResource(this);
	}

	/** Destructor. */
	virtual ~FWaterVertexBuffer()
	{
		ReleaseResource();
	}

	/** 
	* Initialize the RHI for this rendering resource 
	*/
	virtual void InitRHI();
};


//------------------------------------------------------------------------
// FWaterVertexBuffer_NoTess
//------------------------------------------------------------------------
class FWaterVertexBuffer_NoTess : public FVertexBuffer, public FRefCountedObject
{
	INT SizeVerts;
public:
	struct FWaterVertex
	{
		FVector Position;
	};
	
	/** Constructor. */
	FWaterVertexBuffer_NoTess(INT InSizeVerts)
	: 	SizeVerts(InSizeVerts)
	{
		InitResource(); // BeginInitResource(this);
	}

	/** Destructor. */
	virtual ~FWaterVertexBuffer_NoTess()
	{
		ReleaseResource();
	}

	/** 
	* Initialize the RHI for this rendering resource 
	*/
	virtual void InitRHI();
};


//------------------------------------------------------------------------
// FWaterIndexBuffer
//------------------------------------------------------------------------
class FWaterIndexBuffer : public FRawStaticIndexBuffer, public FRefCountedObject
{
public:
	FWaterIndexBuffer(INT SizeQuads, INT VBSizeVertices);

	/** Destructor. */
	virtual ~FWaterIndexBuffer()
	{
		ReleaseResource();
	}
};




//------------------------------------------------------------------------
// FWaterDrawingPolicy
//------------------------------------------------------------------------
class FWaterDrawingPolicy : public FMeshDrawingPolicy
{
public:
	FWaterDrawingPolicy(
		const FVertexFactory* InVertexFactory,
		const FMaterialRenderProxy* InMaterialRenderProxy,
		const FMaterial& InMaterialResource
		);

	UBOOL Matches( const FWaterDrawingPolicy& Other ) const
	{
		return FMeshDrawingPolicy::Matches( Other ) &&
#if WITH_D3D11_TESSELLATION
			HullShader == Other.HullShader &&
			DomainShader == Other.DomainShader &&
#endif
			VertexShader == Other.VertexShader &&
			PixelShader == Other.PixelShader;
	}

	void DrawShared( const FSceneView* View, FBoundShaderStateRHIRef ShaderState ) const;
	void SetMeshRenderState(
		const FViewInfo&			View,
		const FPrimitiveSceneInfo*	PrimitiveSceneInfo,
		const FMeshBatch&			Mesh,
		INT							BatchElementIndex,
		UBOOL						bBackFace,
		const ElementDataType&		ElementData ) const;

	FBoundShaderStateRHIRef CreateBoundShaderState( DWORD DynamicStride = 0 );

	UBOOL SupportsWater() const;

private:
	class FWaterVertexShader*	VertexShader;
	class FWaterPixelShader*	PixelShader;

#if WITH_D3D11_TESSELLATION
	class FWaterHullShader*	HullShader;
	class FWaterDomainShader*	DomainShader;
#endif
};




//------------------------------------------------------------------------
// WaterComponentSceneProxy
//------------------------------------------------------------------------
class WaterComponentSceneProxy : public FPrimitiveSceneProxy
{
public:
	WaterComponentSceneProxy(UWaterComponent* InComponent);

	virtual ~WaterComponentSceneProxy();

	void SetIndexSource(INT LODIndex, INT ElementIndex, INT FragmentIndex, FMeshBatch& OutMeshElement, UBOOL bWireframe, UBOOL bRequiresAdjacencyInformation) const;
	UBOOL GetMeshElement(INT LODIndex,INT ElementIndex,INT FragmentIndex,BYTE InDepthPriorityGroup,const FMatrix& WorldToLocal,FMeshBatch& OutMeshElement, const UBOOL bUseSelectedMaterial, const UBOOL bUseHoveredMaterial) const;
	virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI);
	virtual void DrawDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags = 0);

	virtual DWORD GetMemoryFootprint( void ) const { return( sizeof( *this ) + GetAllocatedSize() ); }
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View);
	virtual UBOOL CreateRenderThreadResources();

protected:

	UWaterComponent* WaterComponent;

	// only one ocean in a scene, no need to share buffers
	class FWaterVertexFactory* VertexFactory;
	FWaterVertexBuffer* VertexBuffer;
	FWaterVertexBuffer_NoTess* VertexBuffer_NoTess;
	FWaterIndexBuffer* IndexBuffer;
	FWaterIndexBuffer** IndexBuffers;

	void DrawManualWithTessellation( FMeshBatch &Mesh, const FViewInfo& SView);
	void DrawWithDrawingPolicy( FMeshBatch &Mesh, const FViewInfo& SView );
	void DrawStaticWaterMesh(const FViewInfo& SView, INT DPGIndex);
	void DrawWithOnlyVSPS( const FMeshBatch& Mesh, const FViewInfo& SView );

public:

	BITFIELD FrustumCullInHS:1;
	BITFIELD UseDynamicLOD:1;
	BITFIELD RenderFoam:1;
	BITFIELD RenderCaustics:1;
	BITFIELD RenderReflection:1;
	BITFIELD RenderRefraction:1;
	BITFIELD RenderFog:1;
	BITFIELD DoTessellation:1;

	BYTE DynamicTessFactor;
	BYTE StaticTessFactor;
	FLOAT WaterBumpTexcoordShiftX;
	FLOAT WaterBumpTexcoordShiftY;
	FLOAT WaterMicroBumpTexcoordScaleX;
	FLOAT WaterMicroBumpTexcoordScaleY;
	FLOAT WaterBumpTexcoordScaleX;
	FLOAT WaterBumpTexcoordScaleY;
	FLOAT WaterHeightBumpScale;
	FLOAT HeightFieldSize;
	FLOAT ZFar;
	FLinearColor WaterDeepColor;
	FLOAT WaterColorIntensityX;
	FLOAT WaterColorIntensityY;
	FLinearColor WaterScatterColor;
	FLOAT WaterScatterColorPower;
	FLinearColor WaterSpecularColor;
	FLOAT WaterSpecularIntensity;
	FLOAT WaterSpecularPower;
 	class UTexture2D* WaterBumpTexture;
 	class UTexture2D* WaterDepthMap;
// 	class UTexture2D* FoamTexture;
// 	class UTexture2D* CausticsTexture;
// 	class UTextureCube* ReflectionCube;
	FLOAT FogDensity;
	FLinearColor AtmosphereBrightColor;
	FLinearColor AtmosphereDarkColor;
// 	class UMaterialInterface* DefaultMaterial;

	FVector Origin;
	FVector DrawScale3D;

};
#endif


#endif // WITH_WATER