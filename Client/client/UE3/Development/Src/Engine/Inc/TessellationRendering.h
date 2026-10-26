/*=============================================================================
	TessellationRendering.h: Tessellation rendering definitions.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __TESSELLATIONRENDERING_H__
#define __TESSELLATIONRENDERING_H__

#if WITH_D3D11_TESSELLATION

// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
//	#define BARYCENTRICS_TEXTURE_PATCH_CAPACITY		(4096 / 2)	// Patches per texture line, each patch is defined by two float3 values
	#define NEIGHBOURING_COORDS_TEXTURE_CAPACITY	(4096 / 2)	// Each vertex/index is assigned 3 exta texture coordinates, whcih are stored as two float3 values
	#define DISPLACEMENT_NORMALS_TEXTURE_CAPACITY	4096		// Normals per texture line, each normal is represented with a single float3 value
#endif
// NVCHANGE_END_JC - TESSELLATION ]

// [ NVCHANGE_BEGIN_JC - TESSELLATION PATCH
enum TessellationBufferMode
{
    TBM_DominantEdgeAndCorner = 0,
    TBM_PnAenOnly = 1,
    TBM_PnAenDominantCorner = 2,
    TBM_PnAenDominantEdgeAndCorner = 3,
	TessellationBufferMode_MAX
};
// NVCHANGE_END_JC - TESSELLATION PATCH ]

class FTessellationMaterialPolicy
{
public:

	/**
	 * This method is used to set any salient defines to turn on/off specific code related to tessellation and the particular tessellation policy
	 */
	static void ModifyCompilationEnvironment(EShaderPlatform Platform, const FMaterial*Material, FShaderCompilerEnvironment& OutEnvironment);
	// [ NVCHANGE_BEGIN_JC - TESSELLATION  Move the implementation to the .cpp
	/*{
		if (Platform != SP_PCD3D_SM5 || Material->GetD3D11TessellationMode() == MTM_NoTessellation)
		{
			OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("0"));
			return;
		}

		OutEnvironment.Definitions.Set(TEXT("USING_SM5_TESSELLATION"),TEXT("1"));

		switch(Material->GetD3D11TessellationMode())
		{
		case MTM_FlatTessellation:
			OutEnvironment.Definitions.Set(TEXT("TESSELLATION_TYPE_FLAT"),TEXT("1"));
			break;

		case MTM_PNTriangles:
			OutEnvironment.Definitions.Set(TEXT("TESSELLATION_TYPE_PNTRIANGLES"),TEXT("1"));
			break;

		default:
			appErrorf(TEXT("Unknown shader type %d"), (INT)Material->GetD3D11TessellationMode());
			break;
		}

		// This is dominant vertex/edge information.  Note, mesh must have preprocessed neighbors IB of material will fallback to default.
		//  PN triangles needs preprocessed buffers regardless of c
		if(Material->IsCrackFreeDisplacementEnabled())
		{
			OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_ANTICRACK"),TEXT("1"));
		}
		else
		{
			OutEnvironment.Definitions.Set(TEXT("DISPLACEMENT_ANTICRACK"),TEXT("0"));
		}
	}*/
	// NVCHANGE_END_JC - TESSELLATION ]

	/**
	 * This ShouldCache is used to determine is Hull/Domain shaders are required for the usage context.  Dictates whether the HS/DS will be compiled and cached.
	 */
	static UBOOL ShouldCache(EShaderFrequency ShaderFrequency, EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		if (ShaderFrequency == SF_Vertex || ShaderFrequency == SF_Pixel)
		{ 
			// always cache VS or PS
			return TRUE;	
		}
		
		// after this only testing HS or DS shaders
		if (Platform != SP_PCD3D_SM5)
		{
			// HS/DS only supported in SM5
			return FALSE;	
		}

		if (VertexFactoryType && !VertexFactoryType->SupportsTessellationShaders())
		{
			// VF can opt out of tessellation
			return FALSE;	
		}

		if (!Material || Material->GetD3D11TessellationMode() == MTM_NoTessellation) 
		{
			// Material controls use of tessellation
			return FALSE;	
		}

		return TRUE;
	}

	/** Returns TRUE if the Material and Vertex Factory combination require adjacency information. */
	static UBOOL RequiresAdjacencyInformation( UMaterialInterface* Material, const FVertexFactoryType* VertexFactoryType );
};

/** Base Hull shader for drawing policy rendering */
class FBaseHullShader : public FShader
{
	DECLARE_SHADER_TYPE(FBaseHullShader,MeshMaterial);
public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		if (!FTessellationMaterialPolicy::ShouldCache(SF_Hull,Platform,Material,VertexFactoryType))
		{
			return FALSE;
		}

		return TRUE;
	}

	FBaseHullShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
		FShader(Initializer)
	{
		MaterialParameters.Bind(Initializer.ParameterMap);
		DisplacementNonUniformScaleParameter.Bind(Initializer.ParameterMap,TEXT("DisplacementNonUniformScale"),TRUE);
// [ NVCHANGE_BEGIN_JC - TESSELLATION	Dominante-Data
		NeighbouringCoordsParameter.Bind(Initializer.ParameterMap, TEXT("NeighbouringCoordsTexture"), TRUE);
// NVCHANGE_END_JC - TESSELLATION Dominante-Data ]
// [ NVCHANGE_BEGIN_JC - TESSELLATION LOD
		TessFactorToCameraParameter.Bind(Initializer.ParameterMap, TEXT("TessFactorToCameraParameter"), TRUE);
// NVCHANGE_END_JC - TESSELLATION LOD ]
	}

	FBaseHullShader() {}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize(Ar);
		Ar << MaterialParameters;
		Ar << DisplacementNonUniformScaleParameter;
// [ NVCHANGE_BEGIN_JC - TESSELLATION	Dominante-Data
		Ar << NeighbouringCoordsParameter;
// NVCHANGE_END_JC - TESSELLATION	Dominante-Data ]
// [ NVCHANGE_BEGIN_JC - TESSELLATION LOD
		Ar << TessFactorToCameraParameter;
// NVCHANGE_END_JC - TESSELLATION LOD ]
		return bShaderHasOutdatedParameters;
	}
	void SetParameters(const FMaterialRenderProxy* MaterialRenderProxy,const FSceneView& View)
	{
		FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy, *MaterialRenderProxy->GetMaterial(), View.Family->CurrentWorldTime, View.Family->CurrentRealTime, &View);
		MaterialParameters.Set(this,MaterialRenderContext);
	}

	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex,const FSceneView& View);

	virtual UBOOL IsUniformExpressionSetValid(const FUniformExpressionSet& UniformExpressionSet) const 
	{ 
		return MaterialParameters.IsUniformExpressionSetValid(UniformExpressionSet); 
	}

private:
	FMaterialHullShaderParameters MaterialParameters;

	/** Used to scale displacement */
	FShaderParameter DisplacementNonUniformScaleParameter;
// [ NVCHANGE_BEGIN_JC - TESSELLATION	Dominante-Data
	FShaderResourceParameter NeighbouringCoordsParameter;
// NVCHANGE_END_JC - TESSELLATION	Dominante-Data ]
// [ NVCHANGE_BEGIN_JC - TESSELLATION LOD
	FShaderParameter TessFactorToCameraParameter;
// NVCHANGE_END_JC - TESSELLATION LOD ]
};

/** Base Domain shader for drawing policy rendering */
class FBaseDomainShader : public FShader
{
	DECLARE_SHADER_TYPE(FBaseDomainShader,MeshMaterial);
public:

	static UBOOL ShouldCache(EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType)
	{
		if (!FTessellationMaterialPolicy::ShouldCache(SF_Domain,Platform,Material,VertexFactoryType))
		{
			return FALSE;
		}

		return TRUE;		
	}

	FBaseDomainShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer):
		FShader(Initializer)
	{
		MaterialParameters.Bind(Initializer.ParameterMap);
	}

	FBaseDomainShader() {}

	virtual UBOOL Serialize(FArchive& Ar)
	{
		UBOOL bShaderHasOutdatedParameters = FShader::Serialize(Ar);
		Ar << MaterialParameters;
		return bShaderHasOutdatedParameters;
	}
	void SetParameters(const FMaterialRenderProxy* MaterialRenderProxy,const FSceneView& View)
	{
		FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy, *MaterialRenderProxy->GetMaterial(), View.Family->CurrentWorldTime, View.Family->CurrentRealTime, &View);
		MaterialParameters.Set(this,MaterialRenderContext);
	}
	void SetMesh(const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex,const FSceneView& View)
	{
		MaterialParameters.SetMesh(this,PrimitiveSceneInfo,Mesh,BatchElementIndex,View);
	}
	virtual UBOOL IsUniformExpressionSetValid(const FUniformExpressionSet& UniformExpressionSet) const 
	{ 
		return MaterialParameters.IsUniformExpressionSetValid(UniformExpressionSet); 
	}

private:
	FMaterialDomainShaderParameters MaterialParameters;
};

#if WITH_EDITOR
/** Generates a PN-AEN index buffer from the specified positions, texture coordinates, and indices. */
void BuildStaticAdjacencyIndexBuffer( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& OutPnAenIndices );
// [ NVCHANGE_BEGIN_JC - TESSELLATION
//void BuildSkeletalAdjacencyIndexBuffer( const TArray<FSoftSkinVertex>& VertexBuffer, const UINT TexCoordCount, const TArray<DWORD>& Indices, TArray<DWORD>& OutPnAenIndices );
void BuildSkeletalAdjacencyIndexBuffer( const FSkeletalMeshVertexBuffer& VertexBuffer, const TArray<DWORD>& Indices, TArray<DWORD>& OutPnAenIndices );
// NVCHANGE_END_JC - TESSELLATION ]
#endif // #if WITH_EDITOR

// [ NVCHANGE_BEGIN_JC - TESSELLATION
#if NV_SMOOTH_NORMALS
class FTessellationBuffersHost
{
public:
	TArray<INT>*		patchExpansions;
	TArray<FVector>*	smoothNormals;
	TArray<FVector>*	neighbouringCoordinates;

	FTessellationBuffersHost() :
		patchExpansions(0),
		smoothNormals(0),
		neighbouringCoordinates(0)
	{ }
};

////void BuildStaticTessellationBuffers( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, 
////														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges);
void BuildStaticTessellationBuffers( const FPositionVertexBuffer& PositionVertexBuffer, const FStaticMeshVertexBuffer& VertexBuffer, const TResourceArray<WORD, INDEXBUFFER_ALIGNMENT>& Indices, 
														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges,
														UBOOL bCreateDBM=FALSE, TessellationBufferMode destBufferMode=TBM_PnAenOnly );
// [ NVCHANGE_BEGIN_JC - TESSELLATION
void BuildSkeletalTessellationBuffers( const FSkeletalMeshVertexBuffer& VertexBuffer, const TArray<DWORD>& Indices, 
														FTessellationBuffersHost& buffers,UBOOL bIdentifyOpenEdges,
														UBOOL bCreateDBM = FALSE , TessellationBufferMode destBufferMode = TBM_PnAenOnly );
// NVCHANGE_END_JC - TESSELLATION ]

#endif
// NVCHANGE_END_JC - TESSELLATION ]

// [ NVCHANGE_BEGIN_JC - TESSELLATION
void BeginEmptyAdjacencyIndexBuffer(FRawStaticIndexBuffer* inPnAenIndexBuffer);
void BeginEmptyAdjacencyIndexBuffer(FRawStaticIndexBuffer16or32Interface* inPnAenIndexBuffer);
// NVCHANGE_END_JC - TESSELLATION ]

#endif //#if WITH_D3D11_TESSELLATION

#endif
