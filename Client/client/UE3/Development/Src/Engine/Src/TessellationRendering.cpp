/*=============================================================================	TessellationRendering.cpp: Functions to support Tessellation Rendering.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "EnginePrivate.h"
#include "TessellationRendering.h"

#if WITH_D3D11_TESSELLATION

// [ NVCHANGE_BEGIN_JC - Adding DX11 HBAO
#if NV_ENABLE_HBAO
#include "AmbientOcclusionRendering.h"
#define NO_STEREO_D3D9 1
#define NO_STEREO_D3D10 1
#define NO_STEREO_D3D11 1
#include "ue3stereo.h"
#undef NO_STEREO_D3D9
#undef NO_STEREO_D3D10
#undef NO_STEREO_D3D11
#endif
// NVCHANGE_END_JC - Adding DX11 HBAO ]

// oscar@snda #if WITH_EDITOR
#include "nvtess.h"
// oscar@snda #endif // #if WITH_EDITOR

/** Returns TRUE if the Material and Vertex Factory combination require adjacency information. */
UBOOL FTessellationMaterialPolicy::RequiresAdjacencyInformation( UMaterialInterface* Material, const FVertexFactoryType* VertexFactoryType )
{
	EMaterialTessellationMode TessellationMode = MTM_NoTessellation;
	UBOOL bEnableCrackFreeDisplacement = FALSE;
	UBOOL bEnablePnAEN = FALSE;
	if ( GRHIShaderPlatform == SP_PCD3D_SM5 && VertexFactoryType->SupportsTessellationShaders() && Material )
	{
		if ( IsInGameThread() )
		{
			UMaterial* BaseMaterial = Material->GetMaterial();
			check( BaseMaterial );
			TessellationMode = (EMaterialTessellationMode)BaseMaterial->D3D11TessellationMode;
			bEnableCrackFreeDisplacement = BaseMaterial->bEnableCrackFreeDisplacement;
			bEnablePnAEN = BaseMaterial->bEnablePnAEN;
		}
		else
		{
			check( IsInRenderingThread() );
			FMaterialRenderProxy* MaterialRenderProxy = Material->GetRenderProxy( FALSE, FALSE );
			check( MaterialRenderProxy );
			const FMaterial* MaterialResource = MaterialRenderProxy->GetMaterial();
			check( MaterialResource );
			TessellationMode = MaterialResource->GetD3D11TessellationMode();
			bEnableCrackFreeDisplacement = MaterialResource->IsCrackFreeDisplacementEnabled();
			bEnablePnAEN = MaterialResource->IsPnAENEnabled();
		}
	}
// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH
	/// return TessellationMode == MTM_PNTriangles || ( TessellationMode == MTM_FlatTessellation && bEnableCrackFreeDisplacement );
	return TessellationMode == MTM_PNTriangles && bEnablePnAEN;
// NVCHANGE_END_JC - TESSELLATION PATCH ]
}

void FBaseHullShader::SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh, INT BatchElementIndex,const FSceneView& View)
{
	const FMeshBatchElement& BatchElement = Mesh.Elements(BatchElementIndex);
	MaterialParameters.SetMesh(this,PrimitiveSceneInfo,Mesh,BatchElementIndex,View);

	if(DisplacementNonUniformScaleParameter.IsBound())
	{
		// Extract per axis scales from LocalToWorld transform
		FVector4 WorldX = FVector4(BatchElement.LocalToWorld.M[0][0],BatchElement.LocalToWorld.M[0][1],BatchElement.LocalToWorld.M[0][2],0);
		FVector4 WorldY = FVector4(BatchElement.LocalToWorld.M[1][0],BatchElement.LocalToWorld.M[1][1],BatchElement.LocalToWorld.M[1][2],0);
		FVector4 WorldZ = FVector4(BatchElement.LocalToWorld.M[2][0],BatchElement.LocalToWorld.M[2][1],BatchElement.LocalToWorld.M[2][2],0);
		FLOAT ScaleX = FVector(WorldX).Size();
		FLOAT ScaleY = FVector(WorldY).Size();
		FLOAT ScaleZ = FVector(WorldZ).Size();
		FVector4 LocalScales = FVector4(ScaleX,ScaleX,ScaleX,0);

		// Now transform local scaling into world space
		FVector4 WorldScales = BatchElement.LocalToWorld.GetMatrixWithoutScale().TransformFVector4(LocalScales); WorldScales.W = 0;

		SetHullShaderValue(GetHullShader(),DisplacementNonUniformScaleParameter,WorldScales);
	}
// [ NVCHANGE_BEGIN_JC - TESSELLATION	Dominante-Data
	if (NeighbouringCoordsParameter.IsBound())
	{
		if (Mesh.NeighbouringCoordsTextureRHIRef)
		{
			RHISetSamplerState(
				GetHullShader(),
				NeighbouringCoordsParameter.GetBaseIndex(),
				0, // TODO: We don't need to bind any sampler state
				TStaticSamplerState<SF_Point,AM_Clamp,AM_Clamp,AM_Clamp,MIPBIAS_None>::GetRHI(),
				Mesh.NeighbouringCoordsTextureRHIRef,
				0.0f,
				-1.0f,
				-1.0f,
				FALSE
				);
		}
	}
// NVCHANGE_END_JC - TESSELLATION	Dominante-Data ]
// [ NVCHANGE_BEGIN_JC - TESSELLATION LOD
	if (TessFactorToCameraParameter.IsBound())
	{
		SetHullShaderValue(GetHullShader(),TessFactorToCameraParameter,Mesh.TessFactorToCamera);
	}
// NVCHANGE_END_JC - TESSELLATION LOD ]
}

// oscar@snda #if WITH_EDITOR
/**
 * Provides static mesh render data to the NVIDIA tessellation library.
 */
class FStaticMeshNvRenderBuffer : public nv::RenderBuffer
{
public:

	/** Construct from static mesh render buffers. */
	FStaticMeshNvRenderBuffer(
		const FPositionVertexBuffer& InPositionVertexBuffer,
		const FStaticMeshVertexBuffer& InVertexBuffer,
		const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices )
		: PositionVertexBuffer( InPositionVertexBuffer )
		, VertexBuffer( InVertexBuffer )
	{
		check( PositionVertexBuffer.GetNumVertices() == VertexBuffer.GetNumVertices() );
		mIb = new nv::IndexBuffer( (void*)Indices.GetTypedData(), nv::IBT_U16, Indices.Num(), false );
	}

	/** Retrieve the position and first texture coordinate of the specified index. */
	virtual nv::Vertex getVertex( unsigned int Index ) const
	{
		nv::Vertex Vertex;

		check( Index < PositionVertexBuffer.GetNumVertices() );

		const FVector& Position = PositionVertexBuffer.VertexPosition( Index );
		Vertex.pos.x = Position.X;
		Vertex.pos.y = Position.Y;
		Vertex.pos.z = Position.Z;

		if( VertexBuffer.GetNumTexCoords() )
		{
			const FVector2D UV = VertexBuffer.GetVertexUV( Index, 0 );
			Vertex.uv.x = UV.X;
			Vertex.uv.y = UV.Y;
		}
		else
		{
			Vertex.uv.x = 0.0f;
			Vertex.uv.y = 0.0f;
		}

		return Vertex;
	}

private:

	/** The position vertex buffer for the static mesh. */
	const FPositionVertexBuffer& PositionVertexBuffer;

	/** The vertex buffer for the static mesh. */
	const FStaticMeshVertexBuffer& VertexBuffer;

	/** Copying is forbidden. */
	FStaticMeshNvRenderBuffer( const FStaticMeshNvRenderBuffer& ); 
	FStaticMeshNvRenderBuffer& operator=( const FStaticMeshNvRenderBuffer& );
};

/**
 * Provides skeletal mesh render data to the NVIDIA tessellation library.
 */
// [ NVCHANGE_BEGIN_JC - TESSELLATION
class FSkeletalMeshNvRenderBuffer : public nv::RenderBuffer
{
private:
	// Will not change these.
	const FSkeletalMeshVertexBuffer* mVb;

	FSkeletalMeshNvRenderBuffer(const FSkeletalMeshNvRenderBuffer&); 
	FSkeletalMeshNvRenderBuffer& operator=(const FSkeletalMeshNvRenderBuffer&);

public:
	FSkeletalMeshNvRenderBuffer(const FSkeletalMeshVertexBuffer* posVb, const TArray<DWORD>& Indices) :
	  mVb(posVb)
	{
		  mIb = new nv::IndexBuffer((void*)(Indices.GetData()), nv::IBT_U32, Indices.Num(), false);
	}

	  virtual nv::Vertex getVertex(unsigned int index) const
	{
		  const FVector& vert = mVb->GetVertexPosition(index);

		  nv::Vertex retVal;
		  retVal.pos.x = vert.X;
		  retVal.pos.y = vert.Y;
		  retVal.pos.z = vert.Z;

		  if(mVb->GetNumTexCoords())
		{
			  const FVector2D uv = mVb->GetVertexUV(index,0);
			  retVal.uv.x = uv.X;
			  retVal.uv.y = uv.Y;
		}
		else
		{
			  retVal.uv.x = 0.f;
			  retVal.uv.y = 0.f;
		}

		  return retVal;
	}
};
// NVCHANGE_END_JC - TESSELLATION ]

void BuildStaticAdjacencyIndexBuffer( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& OutPnAenIndices )
{
	if ( Indices.Num() )
	{
		FStaticMeshNvRenderBuffer StaticMeshRenderBuffer( PositionVertexBuffer, VertexBuffer, Indices );
		nv::IndexBuffer* PnAENIndexBuffer = nv::tess::buildTessellationBuffer( &StaticMeshRenderBuffer, nv::DBM_PnAenOnly, true );
		check( PnAENIndexBuffer );
		const INT IndexCount = (INT)PnAENIndexBuffer->getLength();
		OutPnAenIndices.Empty( IndexCount );
		OutPnAenIndices.Add( IndexCount );
		for ( INT Index = 0; Index < IndexCount; ++Index )
		{
			OutPnAenIndices( Index ) = (*PnAENIndexBuffer)[Index];
		}
		delete PnAENIndexBuffer;
	}
	else
	{
		OutPnAenIndices.Empty();
	}
}

// [ NVCHANGE_BEGIN_JC - TESSELLATION
//void BuildSkeletalAdjacencyIndexBuffer( const TArray<FSoftSkinVertex>& VertexBuffer, const UINT TexCoordCount, const TArray<DWORD>& Indices, TArray<DWORD>& OutPnAenIndices )
void BuildSkeletalAdjacencyIndexBuffer( const FSkeletalMeshVertexBuffer& VertexBuffer, const TArray<DWORD>& Indices, TArray<DWORD>& OutPnAenIndices )
// NVCHANGE_END_JC - TESSELLATION ]
{
	if ( Indices.Num() )
	{
		// [ NVCHANGE_BEGIN_JC - TESSELLATION
		FSkeletalMeshNvRenderBuffer SkeletalMeshRenderBuffer( &VertexBuffer, Indices );
		// NVCHANGE_END_JC - TESSELLATION ]
		nv::IndexBuffer* PnAENIndexBuffer = nv::tess::buildTessellationBuffer( &SkeletalMeshRenderBuffer, nv::DBM_PnAenOnly, true );
		check( PnAENIndexBuffer );
		const INT IndexCount = (INT)PnAENIndexBuffer->getLength();
		OutPnAenIndices.Empty( IndexCount );
		OutPnAenIndices.Add( IndexCount );
		for ( INT Index = 0; Index < IndexCount; ++Index )
		{
			OutPnAenIndices( Index ) = (*PnAENIndexBuffer)[Index];
		}
		delete PnAENIndexBuffer;
	}
	else
	{
		OutPnAenIndices.Empty();
	}
}
// oscar@snda #endif // #if WITH_EDITOR

// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
//// void BuildStaticTessellationBuffers( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, 
////														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges)
void BuildStaticTessellationBuffers( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, 
														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges,
														UBOOL bCreateDBM, TessellationBufferMode destBufferMode )
{
	nv::TessellationBuffers nvBuffers;
	UINT attrs = 0;

	if ( Indices.Num() )
	{
		if (buffers.smoothNormals) attrs |= nv::TA_SmoothNormals;

		// [ NVCHANGE_BEGIN_JC - TESSELLATION Dominant data in texture
		// generate neighboring tex coords data
		if (buffers.neighbouringCoordinates) attrs |= nv::TA_Coordinates;
		// NVCHANGE_END_JC - TESSELLATION Dominant data in texture ]

		FStaticMeshNvRenderBuffer StaticMeshRenderBuffer( PositionVertexBuffer, VertexBuffer, Indices );
		// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH
		/// nv::tess::buildAdditionalTessellationBuffers( &StaticMeshRenderBuffer, nv::DBM_PnAenDominantCorner, true, attrs, nvBuffers, true, bIdentifyOpenEdges ? true : false);
		nv::tess::buildAdditionalTessellationBuffers( &StaticMeshRenderBuffer, (nv::DestBufferMode)destBufferMode, true, attrs, nvBuffers, bCreateDBM ? true : false, bIdentifyOpenEdges ? true : false);
		// NVCHANGE_END_JC - TESSELLATION PATCH ]

		// Smooth Normal
		if (nvBuffers.mSmoothNormals && buffers.smoothNormals)
		{
			INT elementsNum = nvBuffers.mSmoothNormals->getElementCount();
			buffers.smoothNormals->Empty(elementsNum);
			FVector* pSmoothNormalsData = (FVector*)nvBuffers.mSmoothNormals->GetData();
			for (INT i=0; i<elementsNum; ++i)
			{
				buffers.smoothNormals->AddItem(*(pSmoothNormalsData + i));
			}
		}

		// Dominant Data
		if (nvBuffers.mCoordinates && buffers.neighbouringCoordinates)
		{
			INT elementsNum = nvBuffers.mCoordinates->getElementCount();
			buffers.neighbouringCoordinates->Empty(elementsNum);
			FVector* pNeighbouringCoordsData = (FVector*)nvBuffers.mCoordinates->GetData();
			for (INT i=0; i<elementsNum; ++i)
			{
				buffers.neighbouringCoordinates->AddItem(*(pNeighbouringCoordsData + i));
			}
		}
		nvBuffers.Release();
	}
}
#endif
// NVCHANGE_END_JC - TESSELLATION ]

// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
void BuildSkeletalTessellationBuffers( const FSkeletalMeshVertexBuffer& VertexBuffer, const TArray<DWORD>& Indices, 
														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges,
														UBOOL bCreateDBM, TessellationBufferMode destBufferMode )
{
	nv::TessellationBuffers nvBuffers;
	UINT attrs = 0;

	if ( Indices.Num() )
	{
		if (buffers.smoothNormals) attrs |= nv::TA_SmoothNormals;

		// [ NVCHANGE_BEGIN_JC - TESSELLATION Dominant data in texture
		// generate neighboring tex coords data
		if (buffers.neighbouringCoordinates) attrs |= nv::TA_Coordinates;
		// NVCHANGE_END_JC - TESSELLATION Dominant data in texture ]

		// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH
		FSkeletalMeshNvRenderBuffer SkeletalMeshRenderBuffer( &VertexBuffer, Indices );
		nv::tess::buildAdditionalTessellationBuffers( &SkeletalMeshRenderBuffer, (nv::DestBufferMode)destBufferMode, true, attrs, nvBuffers, bCreateDBM ? true : false, bIdentifyOpenEdges ? true : false);
		// NVCHANGE_END_JC - TESSELLATION PATCH ]

		// smooth normal
		if (nvBuffers.mSmoothNormals && buffers.smoothNormals)
		{
			INT elementsNum = nvBuffers.mSmoothNormals->getElementCount();
			buffers.smoothNormals->Empty(elementsNum);
			FVector* pSmoothNormalsData = (FVector*)nvBuffers.mSmoothNormals->GetData();
			for (INT i=0; i<elementsNum; ++i)
			{
				buffers.smoothNormals->AddItem(*(pSmoothNormalsData + i));
			}
		}
		
		// dominant data
		if (nvBuffers.mCoordinates && buffers.neighbouringCoordinates)
		{
			INT elementsNum = nvBuffers.mCoordinates->getElementCount();
			buffers.neighbouringCoordinates->Empty(elementsNum);
			FVector* pNeighbouringCoordsData = (FVector*)nvBuffers.mCoordinates->GetData();
			for (INT i=0; i<elementsNum; ++i)
			{
				buffers.neighbouringCoordinates->AddItem(*(pNeighbouringCoordsData + i));
			}
		}

		nvBuffers.Release();
	}
}
#endif
// NVCHANGE_END_JC - TESSELLATION ]

// [ NVCHANGE_BEGIN_JC - TESSELLATION
void BeginEmptyAdjacencyIndexBuffer(FRawStaticIndexBuffer* inPnAenIndexBuffer)
{
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		EmptyPnAENIndexBufferCommand,
		FRawStaticIndexBuffer*,inPnAenIndexBuffer,inPnAenIndexBuffer,
	{
		inPnAenIndexBuffer->Indices.Empty();
	});
}
void BeginEmptyAdjacencyIndexBuffer(FRawStaticIndexBuffer16or32Interface* inPnAenIndexBuffer)
{
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		EmptyPnAENIndexBufferCommand,
		FRawStaticIndexBuffer16or32Interface*,inPnAenIndexBuffer,inPnAenIndexBuffer,
	{
		inPnAenIndexBuffer->Empty();
	});
}
// NVCHANGE_END_JC - TESSELLATION ]

void FTessellationMaterialPolicy::ModifyCompilationEnvironment(EShaderPlatform Platform, const FMaterial*Material, FShaderCompilerEnvironment& OutEnvironment)
{
	if (Platform != SP_PCD3D_SM5 || Material->GetD3D11TessellationMode() == MTM_NoTessellation)
	{
		OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("0"));
		return;
	}

	OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));
	// [ NVCHANGE_BEGIN_JC - TESSELLATION HULL CULLING
#if USING_TESSELLATION_HULL_CULLING
	OutEnvironment.Definitions.Set(TEXT("USING_TESSELLATION_HULL_CULLING"),TEXT("1"));
#endif
	// NVCHANGE_END_JC - TESSELLATION HULL CULLING ]
	switch(Material->GetD3D11TessellationMode())
	{
	case MTM_FlatTessellation:
		OutEnvironment.Definitions.Set(TEXT("TESSELLATION_TYPE_FLAT"),TEXT("1"));
		break;

	case MTM_PNTriangles:
		OutEnvironment.Definitions.Set(TEXT("TESSELLATION_TYPE_PNTRIANGLES"),TEXT("1"));
// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH
		OutEnvironment.Definitions.Set( TEXT("USING_PNAEN"), (Material->IsPnAENEnabled() ? TEXT("1") : TEXT("0")) );
// NVCHANGE_END_JC - TESSELLATION PATCH ]
		break;

	default:
		appErrorf(TEXT("Unknown shader type %d"), (INT)Material->GetD3D11TessellationMode());
		break;
	}

	// This is dominant vertex/edge information.  Note, mesh must have preprocessed neighbors IB of material will fallback to default.
	//  PN triangles needs preprocessed buffers regardless of c
// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH // We don't need it any more
/*	if(Material->IsCrackFreeDisplacementEnabled())
	{
		OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_ANTICRACK"),TEXT("1"));
	}
	else */
// NVCHANGE_END_JC - TESSELLATION PATCH ]
	{
		OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_ANTICRACK"),TEXT("0"));
		// [ NVCHANGE_BEGIN_JC - TESSELLATION Dominant data in texture
		if(Material->IsDominantDataTextureEnabled() )
		{
			OutEnvironment.Definitions.Set(TEXT("USING_NEIGHBOURING_COORDINATES"),TEXT("1"));
			OutEnvironment.Definitions.Set(TEXT("NEIGHBOURING_COORDS_TEXTURE_CAPACITY"),*FString::Printf(TEXT("%u"),NEIGHBOURING_COORDS_TEXTURE_CAPACITY));
		}
		else
		{
			OutEnvironment.Definitions.Set(TEXT("USING_NEIGHBOURING_COORDINATES"),TEXT("0"));
		}
		// NVCHANGE_END_JC - TESSELLATION Dominant data in texture ]
	}
// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
	if( /*Material->IsCrackFreeDisplacementEnabled() && */Material->IsCrackFreeSmoothNormalsEnabled() )
	{
		OutEnvironment.Definitions.Set(TEXT("USING_SMOOTH_NORMALS"),TEXT("1"));
		OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_NORMALS_TEXTURE_CAPACITY"),*FString::Printf(TEXT("%u"),DISPLACEMENT_NORMALS_TEXTURE_CAPACITY));
	}
	else
	{
		OutEnvironment.Definitions.Set(TEXT("USING_SMOOTH_NORMALS"),TEXT("0"));
		/// OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_NORMALS_TEXTURE_CAPACITY"),*FString::Printf(TEXT("%u"),DISPLACEMENT_NORMALS_TEXTURE_CAPACITY));
	}
#endif

	if(Material->IsAdaptiveTessellationDisabled())
	{
		OutEnvironment.Definitions.Set(TEXT("DISABLE_ADAPTIVE_TESSELLATION"),TEXT("1"));
	}
	else
	{
		OutEnvironment.Definitions.Set(TEXT("DISABLE_ADAPTIVE_TESSELLATION"),TEXT("0"));
	}

	if(Material->GetTessellationFactorToCamera())
	{
		OutEnvironment.Definitions.Set(TEXT("GET_TESSFACTOR_TO_CAMERA"),TEXT("1"));
	}
	else
	{
		OutEnvironment.Definitions.Set(TEXT("GET_TESSFACTOR_TO_CAMERA"),TEXT("0"));
	}
// NVCHANGE_END_JC - TESSELLATION ]
}
#endif // #if WITH_D3D11_TESSELLATION
