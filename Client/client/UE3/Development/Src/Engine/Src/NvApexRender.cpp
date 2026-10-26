/*=============================================================================
	NvApexRender.cpp : Implements the APEX rendering system.
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/


// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright 2009-2010 NVIDIA Corporation. All rights reserved.
// Copyright 2002-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright 2001-2006 NovodeX. All rights reserved.

#include "EnginePrivate.h"
#include "ScenePrivate.h"
#include "EngineMeshClasses.h"
#include "UnParticleHelper.h"

// even if apex is disabled, we still need the vertex factories
#include "NvApexRenderClasses.h"

#if WITH_NOVODEX
#include "NvApexManager.h"
#endif

#if WITH_CUDA_INTEROP
#include <D3D9.h>
#include "D3D9Resources.h"

#include <D3D11.h>
#include "D3D11Resources.h"
#endif

IMPLEMENT_VERTEX_FACTORY_TYPE(FLocalInstancedVertexFactoryApex, "MeshInstancedVertexFactoryPacked", TRUE, FALSE, TRUE, TRUE, TRUE, VER_SM2_BLENDING_SHADER_FIXES, 0);
IMPLEMENT_VERTEX_FACTORY_TYPE(FLocalVertexFactoryApex, "LocalVertexFactory", TRUE, TRUE, TRUE, TRUE, TRUE, VER_DEPRECATED_EDITOR_POSITION, 0);
IMPLEMENT_VERTEX_FACTORY_TYPE(FGPUSkinVertexFactoryApexDestructible, "ApexGpuSkinVertexFactory_1Bone", TRUE, FALSE, TRUE, FALSE, TRUE, VER_MOTIONBLURSKINNING, 0);
IMPLEMENT_VERTEX_FACTORY_TYPE(FGPUSkinVertexFactoryApexClothing, "ApexGpuSkinVertexFactory", TRUE, FALSE, TRUE, FALSE, TRUE, VER_REMOVE_MAXBONEINFLUENCE, 0);
// WARNING: We should get rid of the licensee version # and just use an engine version # when merging to Epic.
IMPLEMENT_VERTEX_FACTORY_TYPE(FVTFVertexFactoryApexSpriteVTF, "ApexSpriteVTFVertexFactory", TRUE, FALSE, FALSE, FALSE, TRUE, VER_MOTIONBLURSKINNING, 0);

#if WITH_APEX
// high speed sprite rendering pipeline
/*
This constructor is used to initialize a static VB/IB encoding a max instances for VTF particle rendering
*/
FVTFVertexFactoryApexSpriteVTF::FVTFVertexFactoryApexSpriteVTF(const FApexRenderResource &InApexRenderResource) : FLocalVertexFactoryApex(InApexRenderResource)
{
	SpriteBuffer = static_cast<ApexRenderSpriteBuffer*>(InApexRenderResource.getSpriteBuffer());
} 
#endif

#if WITH_APEX
/* Create shared static VB used by all render groups */
void ApexRenderSpriteBuffer::InitStaticVB()
{
	// --------- STATIC VB ------------------------
	// float2 position, float4 uvs (regular texture, and custom VTF coords for expansion in shader)
	StaticVertex staticVerts[4] = 
	{
		StaticVertex(FVector2D(0.5f,-0.5f),FVector2D(1,1)),	// 0
		StaticVertex(FVector2D(0.5f,0.5f),FVector2D(1,0)),	// 1
		StaticVertex(FVector2D(-0.5f,-0.5f),FVector2D(0,1)),// 2
		StaticVertex(FVector2D(-0.5f,0.5f),FVector2D(0,0))	// 3
	};

	UINT BufferSize = MaxSprites * 4 * sizeof(StaticVertex);	// 4 verts per instance
	VTFVertexBuffer.InitResource();
	VTFVertexBuffer.VertexBufferRHI = RHICreateVertexBuffer(BufferSize, 0, RUF_Static);

	const UINT SizeX = GetVTFWidth();
	const UINT SizeY = GetVTFHeight();

	StaticVertex *vbData = (StaticVertex*)RHILockVertexBuffer(VTFVertexBuffer.VertexBufferRHI, 0, BufferSize, FALSE);
	check(vbData);
	if(vbData)
	{
		// replicate
		for(UINT i=0;i<MaxSprites;i++)
		{
			UINT texRow = i / SizeX;
			UINT texCol = i % SizeX; 
			FVector2D VTFCoords = FVector2D(((FLOAT)texCol + 0.5f)/SizeX,((FLOAT)texRow + 0.5f)/SizeY);
			for(UINT j=0;j<4;j++)
			{
				vbData[4*i + j] = staticVerts[j];
				vbData[4*i + j].VTFCoords = VTFCoords;	// override vtf coords per instance
			}
		}
	}
	RHIUnlockVertexBuffer(VTFVertexBuffer.VertexBufferRHI);

	BufferSize = MaxSprites * 6 * sizeof(UINT);	// 2 tris per instance
	VTFIndexBuffer.InitResource();
	VTFIndexBuffer.IndexBufferRHI = RHICreateIndexBuffer(sizeof(UINT),BufferSize,0,RUF_Static);
	UINT *ibData = (UINT*)RHILockIndexBuffer(VTFIndexBuffer.IndexBufferRHI, 0, BufferSize);
	check(ibData);
	if(ibData)
	{
		for(UINT i=0;i<MaxSprites;i++)
		{
			// CW
			ibData[i*6 + 0] = i*4+0;ibData[i*6 + 1] = i*4+2;ibData[i*6 + 2] = i*4+1;
			ibData[i*6 + 3] = i*4+1;ibData[i*6 + 4] = i*4+2;ibData[i*6 + 5] = i*4+3;

		}
	}
	RHIUnlockIndexBuffer(VTFIndexBuffer.IndexBufferRHI);
}

void ApexRenderSpriteBuffer::ReleaseStaticVB()
{
	VTFIndexBuffer.ReleaseResource();
	VTFVertexBuffer.ReleaseResource();
}

/** Textures to hold VTF instancing data */
void ApexRenderSpriteBuffer::InitVTFTextures(DWORD Flags)
{
	// Data loading wants no interpolation! 
	VTFSamplerStateRHI = TStaticSamplerState<SF_Point,AM_Clamp,AM_Clamp,AM_Clamp>::GetRHI();

	Flags |= TexCreate_Uncooked;

	// POSITIONS
	{
		FTexture2DRHIRef tex = RHICreateTexture2D(
			TextureDescs[0].width, TextureDescs[0].height,
			PF_A32B32G32R32F, //EPixelFormat::PF_A32B32G32R32F
			1,
			Flags,
			NULL);
		VTFPositionsTexture = tex;
	}


	// SCALE and ROTATION
	{
		FTexture2DRHIRef tex = RHICreateTexture2D(
			TextureDescs[1].width, TextureDescs[1].height,
			PF_A32B32G32R32F, //EPixelFormat::PF_A32B32G32R32F
			1,
			Flags,
			NULL);
		VTFScaleAndRotationTexture = tex;
	}

	// ARGB color
	{
		FTexture2DRHIRef tex = RHICreateTexture2D(
			TextureDescs[2].width, TextureDescs[2].height,
			UseFloat4Color ?  PF_A32B32G32R32F : PF_A8R8G8B8,
			1,
			Flags,
			NULL);
		VTFColorTexture = tex;
	}
}

void ApexRenderSpriteBuffer::ReleaseVTFTextures()
{
	VTFPositionsTexture.SafeRelease();
	VTFPositionsTexture = 0;
	VTFScaleAndRotationTexture.SafeRelease();
	VTFScaleAndRotationTexture = 0;
	VTFColorTexture.SafeRelease();
	VTFColorTexture = 0;
	VTFSamplerStateRHI.SafeRelease();
}
#endif

// VTF uses a fixed declaration
void FVTFVertexFactoryApexSpriteVTF::InitRHI()
{
	FVertexDeclarationElementList Elements;
#if WITH_APEX
	// $$ BED AccessStreamComponent has side effects of adding the vb pointers to a Stream list.... thus necessary
	Elements.AddItem(AccessStreamComponent(FVertexStreamComponent(SpriteBuffer->GetVTFVertexBuffer(), 0, sizeof(StaticVertex), VET_Float2, FALSE), VEU_Position, 0));
	Elements.AddItem(AccessStreamComponent(FVertexStreamComponent(SpriteBuffer->GetVTFVertexBuffer(), sizeof(FVector2D), sizeof(StaticVertex), VET_Float4, FALSE), VEU_TextureCoordinate,0));
	InitDeclaration(Elements, Data);
#endif
}

#if WITH_APEX
void FVTFVertexFactoryApexSpriteVTF::InitMesh(FMeshBatch& MeshElement, const FSceneView* View, const ApexRenderSpriteBuffer* SpriteBuffer,INT TurbRenderGroup, UBOOL bUpdateVTFTextures, const FApexRenderResource& Resource)
{
	UINT NumSprites = Resource.GetNumSprites();

	GApexRender->addParticleCount(NumSprites);

	UMaterialInterface *Material = Resource.GetMaterial();

	check(Material);
	FMeshBatchElement& BatchElement = MeshElement.Elements(0);
	BatchElement.IndexBuffer                = SpriteBuffer->GetVTFIndexBuffer();
	BatchElement.FirstIndex                 = Resource.GetFirstSprite()*6;
	BatchElement.NumPrimitives              = NumSprites*2;

	MeshElement.VertexFactory              = this;
	MeshElement.DynamicVertexData          = 0;
	MeshElement.MaterialRenderProxy        = Material->GetRenderProxy(FALSE);
	MeshElement.LCI                        = &LightCache;

	BatchElement.MinVertexIndex             = 0;
	BatchElement.MaxVertexIndex             = appTrunc(this->GetMaxInstances()*4); 

	MeshElement.UseDynamicData             = FALSE;
	MeshElement.ReverseCulling             = TRUE;
	MeshElement.CastShadow                 = FALSE;
	MeshElement.Type                       = PT_TriangleList;
	MeshElement.DepthPriorityGroup         = SDPG_World;
	MeshElement.bUsePreVertexShaderCulling = TRUE;

	BatchElement.LocalToWorld               = FMatrix::Identity;	// The "mesh" for spriteVTF particles needs to be always placed at the origin.  Particles are positioned independently in shaders..
	BatchElement.WorldToLocal               = FMatrix::Identity;
}
#endif


/**
* Bind shader constants by name
* @param	ParameterMap - mapping of named shader constants to indices
*/
void FVertexFactoryShaderParametersApexSpriteVTF::Bind(const FShaderParameterMap &ParameterMap)
{
	InvNumVerticesPerInstanceParameter.Bind(ParameterMap,TEXT("InvNumVerticesPerInstance"),TRUE);
	NumVerticesPerInstanceParameter.Bind(ParameterMap,TEXT("NumVerticesPerInstance"),TRUE);
	LocalToWorldParameter.Bind(ParameterMap,TEXT("LocalToWorld"),TRUE);
	InvViewParameter.Bind(ParameterMap, TEXT("InvView"),TRUE);
	ViewParameter.Bind(ParameterMap, TEXT("View"),TRUE);
	SubUVTableParameter.Bind(ParameterMap,TEXT("SubUVTable"),TRUE);
	ScaleXSubUVParameter.Bind(ParameterMap,TEXT("ScaleXSubUV"),TRUE);
	ScaleYSubUVParameter.Bind(ParameterMap,TEXT("ScaleYSubUV"),TRUE);
	BlendSubUVParameter.Bind(ParameterMap,TEXT("BlendSubUV"),TRUE);
	MaxInstancesParameter.Bind(ParameterMap, TEXT("MaxInstances"),TRUE);

	VTFInstancingPositionParameter.Bind(ParameterMap, TEXT("VTFInstancePositionDataSampler"),TRUE);
	VTFInstancingScaleAndRotationParameter.Bind(ParameterMap, TEXT("VTFInstanceScaleAndRotationDataSampler"),TRUE);
	VTFInstancingColorParameter.Bind(ParameterMap, TEXT("VTFInstanceColorDataSampler"),TRUE);
}


/* FVertexFactoryShaderParametersApexSpriteVTF */

/**
* Serialize shader params to an archive
* @param	Ar - archive to serialize to
*/
void FVertexFactoryShaderParametersApexSpriteVTF::Serialize(FArchive &Ar)
{
	Ar << InvNumVerticesPerInstanceParameter;
	Ar << NumVerticesPerInstanceParameter;
	Ar << LocalToWorldParameter;
	Ar << InvViewParameter;
	Ar << ViewParameter;
	Ar << SubUVTableParameter;
	Ar << ScaleXSubUVParameter;
	Ar << ScaleYSubUVParameter;
	Ar << BlendSubUVParameter;
	Ar << MaxInstancesParameter;

	Ar << VTFInstancingPositionParameter;
	Ar << VTFInstancingScaleAndRotationParameter;
	Ar << VTFInstancingColorParameter;
}

static void computeSubUV(INT wid,INT hit,INT index,FLOAT &u,FLOAT &v,FLOAT recipWid,FLOAT recipHit)
{
	INT x = index%wid;
	INT y = index/wid;
	u = (FLOAT)x*recipWid;
	v = (FLOAT)y*recipHit;
}
/**
* Set any shader data specific to this vertex factory
*/
void FVertexFactoryShaderParametersApexSpriteVTF::Set(FShader *VertexShader, const FVertexFactory *VertexFactory, const FSceneView &View) const
{
	SetVertexShaderValue(VertexShader->GetVertexShader(),InvNumVerticesPerInstanceParameter,1.0f / (FLOAT)VertexFactory->GetNumVerticesPerInstance());
	SetVertexShaderValue(VertexShader->GetVertexShader(),NumVerticesPerInstanceParameter,(FLOAT)VertexFactory->GetNumVerticesPerInstance());

	FVTFVertexFactoryApexSpriteVTF *spriteVTFFactory = (FVTFVertexFactoryApexSpriteVTF*)VertexFactory;

	SetVertexShaderValue(VertexShader->GetVertexShader(),MaxInstancesParameter,spriteVTFFactory->GetMaxInstances());
#if WITH_APEX
	const ApexSpriteSubUV &subUV = GApexRender->GetApexSpriteSubUV();
	if ( subUV != mApexSpriteSubUV )
	{
		// unfortunately, need to cast a non-const version so we can avoid recomputing these tables every frame.
		FVertexFactoryShaderParametersApexSpriteVTF *VTF = (FVertexFactoryShaderParametersApexSpriteVTF *)this;
		VTF->mApexSpriteSubUV = subUV;

		INT wid = subUV.Width;
		INT hit = subUV.Height;

		INT frameCount = wid*hit;

		INT StartSubUV = subUV.StartFrame;
		if ( StartSubUV )
		{
			StartSubUV--; // from 1 based indexing back to 0 based indexing
		}
		if ( StartSubUV >= frameCount )
		{
			StartSubUV = 0;
		}
		frameCount-=StartSubUV;
		if ( subUV.FrameCount >0 && subUV.FrameCount < frameCount )
		{
			frameCount = subUV.FrameCount;
		}

		VTF->mScaleXSubUV = 1.0f / (FLOAT)wid;
		VTF->mScaleYSubUV = 1.0f / (FLOAT)hit;

		for (INT i=0; i<MAX_APEX_SPRITE_SUBUV; i++)
		{
			FVector4 &v = VTF->mSubUV[i];
			INT index1 = (i%frameCount)+StartSubUV;
			check( index1 < (wid*hit) );
			computeSubUV(wid,hit,index1,v.X,v.Y,mScaleXSubUV,mScaleYSubUV);
			INT index2 = ((i+1)%frameCount)+StartSubUV;
			check( index2 < (wid*hit) );
			computeSubUV(wid,hit,index2,v.Z,v.W,mScaleXSubUV,mScaleYSubUV);
		}
	}
	SetVertexShaderValues<FVector4>(VertexShader->GetVertexShader(), SubUVTableParameter, mSubUV, 32);
	SetVertexShaderValue(VertexShader->GetVertexShader(),ScaleXSubUVParameter, mScaleXSubUV );
	SetVertexShaderValue(VertexShader->GetVertexShader(),ScaleYSubUVParameter, mScaleYSubUV );
	FLOAT blendSubUV = mApexSpriteSubUV.Blend ? 1.0f : 0.0f;
	SetVertexShaderValue(VertexShader->GetVertexShader(),BlendSubUVParameter, blendSubUV );
#endif
}

void FVertexFactoryShaderParametersApexSpriteVTF::SetMesh(FShader* VertexShader, const FMeshBatch& Mesh, INT BatchElementIndex, const FSceneView& View) const
{
#if WITH_APEX
	const FMeshBatchElement& BatchElement = Mesh.Elements(BatchElementIndex);
	FMatrix LocalToWorld = BatchElement.LocalToWorld;

	SetVertexShaderValue(
		VertexShader->GetVertexShader(),
		LocalToWorldParameter,
		LocalToWorld.ConcatTranslation(View.PreViewTranslation)
		);

	SetVertexShaderValue(VertexShader->GetVertexShader(),
		InvViewParameter,
		View.ViewMatrix.Inverse()
		);

	SetVertexShaderValue(VertexShader->GetVertexShader(),
		ViewParameter,
		View.ViewMatrix
		);

	const FVTFVertexFactoryApexSpriteVTF *SpriteVTFFactory = static_cast<const FVTFVertexFactoryApexSpriteVTF*>(Mesh.VertexFactory);
	const ApexRenderSpriteBuffer *SpriteBuffer = SpriteVTFFactory->GetSpriteBuffer();

	FTexture2DRHIRef tex1 = SpriteBuffer->GetVTFPositionTexture();

	SetTextureParameterVTF(VertexShader->GetVertexShader(),
		VTFInstancingPositionParameter,
		SpriteBuffer->GetVTFSamplerState(),
		(FTextureRHIRef&)tex1,
		0
		);

	FTexture2DRHIRef tex2 = SpriteBuffer->GetVTFScaleAndRotationTexture();
	SetTextureParameterVTF(VertexShader->GetVertexShader(),
		VTFInstancingScaleAndRotationParameter,
		SpriteBuffer->GetVTFSamplerState(),
		(FTextureRHIRef&)tex2,
		0
		);

	FTexture2DRHIRef tex3 = SpriteBuffer->GetVTFColorTexture();
	SetTextureParameterVTF(VertexShader->GetVertexShader(),
		VTFInstancingColorParameter,
		SpriteBuffer->GetVTFSamplerState(),
		(FTextureRHIRef&)tex3,
		0
		);
#endif
}



#if WITH_APEX

#include "UnNovodexSupport.h"
#include "NvApexRender.h"
#include "NvApexCommands.h"

#include "NvApexRenderClasses.h"

enum EnqueType
{
	ET_CREATE_VERTEX_BUFFER,
	ET_CREATE_INDEX_BUFFER,
	ET_CREATE_INSTANCE_BUFFER,
	ET_CREATE_RENDER_RESOURCE,
	ET_WRITE_VERTEX_BUFFER,
	ET_WRITE_INDEX_BUFFER,
	ET_WRITE_INSTANCE_BUFFER,
	ET_LAST
};

/**
* This class is used to enque rendering requests from the game thread that must be processed by the rendering thread
*/
class FEnqueData
{
public:
	FEnqueData(void)
	{
		mSemaphore = FALSE; // This semaphore indicates that the rendering thread has completed processing of this request.
	}

	virtual ~FEnqueData(void)
	{
		// TODO: check if we can clear the semaphore before deleting in FApexRenderResourceManager::FlushFEnqueDataGameThread
		// instead of removing this check
		//check(!mSemaphore); // Check that the semaphore has always been cleared by the rendering thread before this class can be destructed.
	}

	virtual UBOOL IsUnused(void) // By default this data item is currently unused
	{
		return TRUE;
	}

	EnqueType mType; // Defines the type of request.

	/**
	* A pure virtual method to indicate that the parent buffer for this data request has been destructed.
	*/
	virtual UBOOL NotifyBufferGone(void *buffer) = 0;

	/***
	* Returns true if the rendering thread is finished processing this data item.
	*/
	UBOOL  ProcessGameThread(void)  // return true of the data item should be killed.
	{
		return IsSemaphoreUsed() ? FALSE : TRUE;
	}

	/***
	* Defines the virtual method that performs the specific request in the rendering thread.
	*/
	virtual void  ProcessRenderingThread(void) = 0; // return true of the data item should be killed.

	/***
	* Returns the current state of the rendering semaphore.
	*/
	UBOOL IsSemaphoreUsed(void) const
    {
    	return mSemaphore;
    };

	/***
	* Sets the rendering thread semaphore to true.  Asserts that it was previously false.
	*/
	void  SetSemaphore(void)
	{
		check(!mSemaphore);
		mSemaphore = TRUE;
	}

	/***
	* Clears the rendering thread semaphore.  Asserts that it was previously set to true.
	*/
	void ClearSemaphore(void)
	{
		check(mSemaphore);
		mSemaphore = FALSE;
	}

private:
	UBOOL	mSemaphore; // The rendering thread semaphore

};

/***
* Holds a create vertex buffer request
*/
class EnqueCreateVertexBuffer : public FEnqueData
{
public:
	EnqueCreateVertexBuffer(FApexRenderVertexBuffer *buffer,const physx::NxUserRenderVertexBufferDesc &desc)
	{
		mType   = ET_CREATE_VERTEX_BUFFER;
		mBuffer = buffer;
		mDesc   = desc;
	}

	virtual ~EnqueCreateVertexBuffer()
	{
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer->Init(mDesc);
			mBuffer = NULL;
		}
		ClearSemaphore();
	}

	FApexRenderVertexBuffer 		*mBuffer;
	physx::NxUserRenderVertexBufferDesc 	 mDesc;
};

/****
* Holds a create index buffer request
*/
class EnqueCreateIndexBuffer : public FEnqueData
{
public:
	EnqueCreateIndexBuffer(FApexRenderIndexBuffer *buffer,const NxUserRenderIndexBufferDesc &desc)
	{
		mType   = ET_CREATE_INDEX_BUFFER;
		mBuffer = buffer;
		mDesc   = desc;
	}

	virtual ~EnqueCreateIndexBuffer()
	{
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer->Init(mDesc);
			mBuffer = NULL;
		}
		ClearSemaphore();
	}

	FApexRenderIndexBuffer 		*mBuffer;
	NxUserRenderIndexBufferDesc 	 mDesc;

};

/****
* Holds a create instance buffer request
*/
class EnqueCreateInstanceBuffer : public FEnqueData
{
public:
	EnqueCreateInstanceBuffer(FApexRenderInstanceBuffer *buffer,const NxUserRenderInstanceBufferDesc &desc)
	{
		mType   = ET_CREATE_INSTANCE_BUFFER;
		mBuffer = buffer;
		mDesc   = desc;
	}

	virtual ~EnqueCreateInstanceBuffer()
	{
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer = NULL;
		}
		ClearSemaphore();
	}

	FApexRenderInstanceBuffer 		*mBuffer;
	NxUserRenderInstanceBufferDesc 	 mDesc;

};

/****
* Holds a create render resource request.
*/
class EnqueCreateRenderResource : public FEnqueData
{
public:
#define MAX_NUM_VERTEX_BUFFERS 16 // can't imagine ever having more than 16!
	EnqueCreateRenderResource(FApexRenderResource *buffer,const physx::NxUserRenderResourceDesc &desc)
	{
		mType   = ET_CREATE_RENDER_RESOURCE;
		mBuffer = buffer;
		check( desc.numVertexBuffers < MAX_NUM_VERTEX_BUFFERS );
		mDesc   = desc;
		for (physx::PxU32 i=0; i<desc.numVertexBuffers; i++)
		{
			mBuffers[i] = desc.vertexBuffers[i];
		}
		mDesc.vertexBuffers = mBuffers;
	}

	virtual ~EnqueCreateRenderResource()
	{
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer->Init(mDesc);
			mBuffer = NULL;
		}
		ClearSemaphore();
	}

	FApexRenderResource 				*mBuffer;
	physx::NxUserRenderResourceDesc 	mDesc;
	physx::NxUserRenderVertexBuffer		*mBuffers[MAX_NUM_VERTEX_BUFFERS];

};


UBOOL	GReverseCulling=TRUE;

/****
* Holds a write to vertex buffer request
*/
class EnqueWriteVertexBuffer : public FEnqueData
{
public:
	EnqueWriteVertexBuffer(FApexRenderVertexBuffer *buffer,const NxApexRenderVertexBufferData &data, physx::PxU32 firstVertex, physx::PxU32 numVertices)
	{
		mNormalSign = GApexNormalSign;
		mType   = ET_WRITE_VERTEX_BUFFER;
		mBuffer = buffer;

		mFirstVertex = firstVertex;
		mNumVertices = numVertices;

		mData = NULL;
		UpdateWithData(data);

		mFlushCount = 0;
	}

	virtual ~EnqueWriteVertexBuffer()
	{
		appFree(mData);
	}

	virtual UBOOL IsUnused(void)
	{
		mFlushCount++;
		return mFlushCount > 1 ? TRUE : FALSE;
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer->writeBuffer(mData);
		}
		ClearSemaphore();
	}

	/***
	* Returns true if this new write buffer request exactly matches the previous one.
	*/
	UBOOL VertexBufferMatch(FApexRenderVertexBuffer *buffer, const NxApexRenderVertexBufferData &data, physx::PxU32 firstVertex, physx::PxU32 numVertices)
	{
		UBOOL ret = FALSE;
		return ret;

		check( !IsSemaphoreUsed() );

		if ( buffer == mBuffer && firstVertex == mFirstVertex && numVertices == mNumVertices )
		{
			mFlushCount = 0;
			UpdateWithData(data);
			ret = TRUE;
		}
		return ret;
	}

private:

	/*
	process the vb data and update our internal copy (via utility methods on the vertex buffer class)
	*/
	void UpdateWithData(const NxApexRenderVertexBufferData &data)
	{
		check(mBuffer);

		if(!mData)
		{
			// alloc a buffer to hold all semantics
			mData = (BYTE*)appMalloc(mBuffer->GetBufferSize());
		}

		// copy it over
		for(physx::PxU32 i=0; i<NxRenderVertexSemantic::NUM_SEMANTICS; i++)
		{
			NxRenderVertexSemantic::Enum semantic = (NxRenderVertexSemantic::Enum)i;
			const NxApexRenderSemanticData &semanticData = data.getSemanticData(semantic);

			if ( semantic == NxRenderVertexSemantic::NORMAL )
				GApexNormalSign = mNormalSign;

			mBuffer->writeBufferSemantic(mData,semantic,semanticData.data,semanticData.stride,semanticData.format,mFirstVertex,mNumVertices);
			
			GApexNormalSign = 1;
		}
	}


	FApexRenderVertexBuffer *mBuffer;
	BYTE *							mData;	// contains a full copy of the VB updates with the data from all the semantics.
	physx::PxU32					mBufferSize;
	
	physx::PxU32					mFirstVertex;
	physx::PxU32					mNumVertices;

	physx::PxU32					mFlushCount;
	physx::PxF32					mNormalSign;
};

/****
* Handles a write index buffer request.
*/
class EnqueWriteIndexBuffer : public FEnqueData
{
public:
	EnqueWriteIndexBuffer(FApexRenderIndexBuffer *buffer,
							const void *SrcData,
							physx::PxU32 SrcStride,
							physx::PxU32 FirstDestElement,
							physx::PxU32 NumElements)
	{
		mType   = ET_WRITE_VERTEX_BUFFER;
		mBuffer = buffer;
		mSrcData = appMalloc(SrcStride*NumElements);
		mSrcStride = SrcStride;
		memcpy(mSrcData,SrcData,SrcStride*NumElements);
		mFirstDestElement = FirstDestElement;
		mNumElements = NumElements;
		mFlushCount = 0;
	}

	virtual ~EnqueWriteIndexBuffer()
	{
		if ( mSrcData )
		{
			appFree(mSrcData);
		}
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer  )
		{
			mBuffer->writeBuffer(mSrcData,mSrcStride,mFirstDestElement,mNumElements);
		}
		ClearSemaphore();
	}

	FApexRenderIndexBuffer			*mBuffer;
	void 							*mSrcData;
	physx::PxU32					mSrcStride;
	physx::PxU32					mFirstDestElement;
	physx::PxU32					mNumElements;
	physx::PxU32					mFlushCount;
};

/****
* Handles a write instance buffer request.
*/
class EnqueWriteInstanceBuffer : public FEnqueData
{
public:
	EnqueWriteInstanceBuffer(FApexRenderInstanceBuffer *buffer,
							physx::NxRenderInstanceSemantic::Enum Semantic,
							const void *SrcData,
							physx::PxU32 SrcStride,
							physx::PxU32 FirstDestElement,
							physx::PxU32 NumElements)
	{
		mType   = ET_WRITE_VERTEX_BUFFER;
		mBuffer = buffer;
		mSemantic = Semantic;

		mSrcData = appMalloc(SrcStride*NumElements);
		mSrcStride = SrcStride;
		memcpy(mSrcData,SrcData,SrcStride*NumElements);
		mFirstDestElement = FirstDestElement;
		mNumElements = NumElements;
		mFlushCount = 0;
	}

	virtual ~EnqueWriteInstanceBuffer()
	{
		appFree(mSrcData);
	}

	virtual UBOOL IsUnused(void)
	{
		mFlushCount++;
		return mFlushCount > 1 ? TRUE : FALSE;
	}

	virtual UBOOL NotifyBufferGone(void *buffer)
	{
		UBOOL ret = FALSE;
		if ( buffer == mBuffer )
		{
			ClearSemaphore();
			ret = TRUE;
		}
		return ret;
	}

	virtual void  ProcessRenderingThread(void)
	{
		if ( mBuffer )
		{
			mBuffer->writeBuffer(mSemantic,mSrcData,mSrcStride,mFirstDestElement,mNumElements);
		}
		ClearSemaphore();
	}

	UBOOL InstanceBufferMatch(FApexRenderInstanceBuffer *buffer,
							physx::NxRenderInstanceSemantic::Enum Semantic,
							const void *SrcData,
							physx::PxU32 SrcStride,
							physx::PxU32 FirstDestElement,
							physx::PxU32 NumElements)
	{
		UBOOL ret = FALSE;

		check( !IsSemaphoreUsed() );

		if ( buffer == mBuffer &&
			 Semantic == mSemantic &&
			 SrcStride == mSrcStride &&
			 FirstDestElement == mFirstDestElement &&
			 NumElements == mNumElements )
		{
			mFlushCount = 0;
			memcpy(mSrcData,SrcData,SrcStride*NumElements);
			ret = TRUE;
		}
		return ret;
	}

	FApexRenderInstanceBuffer				*mBuffer;
	physx::NxRenderInstanceSemantic::Enum	mSemantic;
	void 									*mSrcData;
	physx::PxU32							mSrcStride;
	physx::PxU32							mFirstDestElement;
	physx::PxU32							mNumElements;
	physx::PxU32							mFlushCount;
};



// Adds a create vertex buffer request to the queue
void FApexRenderResourceManager::Enque(FApexRenderVertexBuffer *buffer,const physx::NxUserRenderVertexBufferDesc &desc)
{
	check(IsInGameThread());

	EnqueCreateVertexBuffer *e = new EnqueCreateVertexBuffer(buffer,desc);
	PostFEnqueDataGameThread(e);

	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		EnqueCreateVertexBuffer *, e, e,
		{
			GApexRender->PostFEnqueDataRenderingThread(e);
		}
	);

}

void FApexRenderResourceManager::Enque(FApexRenderVertexBuffer *buffer,const NxApexRenderVertexBufferData &data, physx::PxU32 firstVertex, physx::PxU32 numVertices)
{
	check(IsInGameThread());

	// See if this write buffer request matches any buffer in our 'reuse' queue.
	EnqueWriteVertexBuffer *e = NULL;
	for (TFEnqueDataArray::iterator i=EnqueDataReuse.begin(); i!=EnqueDataReuse.end(); ++i)
	{
		FEnqueData *ed = (*i);
		if (ed && ed->mType == ET_WRITE_VERTEX_BUFFER )
		{
			EnqueWriteVertexBuffer *found = static_cast< EnqueWriteVertexBuffer *>(ed);
			if ( found->VertexBufferMatch(buffer,data,firstVertex,numVertices) )
			{
				(*i) = NULL;
				e = found;
				break;
			}
		}
	}

	if ( e == NULL )
	{
		e = new EnqueWriteVertexBuffer(buffer,data,firstVertex,numVertices);
	}

	PostFEnqueDataGameThread(e);

	// Enque this post request on the rendering thread
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
		FEnqueData,
		EnqueWriteVertexBuffer *, e, e,
	{
		GApexRender->PostFEnqueDataRenderingThread(e);
	}
	);
}

// Add a create index buffer request to the queue
void FApexRenderResourceManager::Enque(FApexRenderIndexBuffer *buffer,const NxUserRenderIndexBufferDesc &desc)
{
	check(IsInGameThread());

	EnqueCreateIndexBuffer *e = new EnqueCreateIndexBuffer(buffer,desc);
	PostFEnqueDataGameThread(e);

	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		EnqueCreateIndexBuffer *, e, e,
		{
			GApexRender->PostFEnqueDataRenderingThread(e);
		}
	);
}

// Add a write index buffer request to the queue
void FApexRenderResourceManager::Enque(FApexRenderIndexBuffer *buffer,const void *SrcData, physx::PxU32 SrcStride, physx::PxU32 FirstDestElement, physx::PxU32 NumElements)
{
	check(IsInGameThread());
	EnqueWriteIndexBuffer *e = new EnqueWriteIndexBuffer(buffer,SrcData,SrcStride,FirstDestElement,NumElements);
	PostFEnqueDataGameThread(e);
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		EnqueWriteIndexBuffer *, e, e,
		{
			GApexRender->PostFEnqueDataRenderingThread(e);
		}
	);
}

// Add a create instance buffer request to the queue
void FApexRenderResourceManager::Enque(FApexRenderInstanceBuffer *buffer,const NxUserRenderInstanceBufferDesc &desc)
{
	check(IsInGameThread());

	EnqueCreateInstanceBuffer *e = new EnqueCreateInstanceBuffer(buffer,desc);
	PostFEnqueDataGameThread(e);

	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		EnqueCreateInstanceBuffer *, e, e,
		{
			GApexRender->PostFEnqueDataRenderingThread(e);
		}
	);

}

// Add a write instance buffer request to the queue
void FApexRenderResourceManager::Enque(FApexRenderInstanceBuffer *buffer,physx::NxRenderInstanceSemantic::Enum Semantic,const void *SrcData,physx::PxU32 SrcStride,physx::PxU32 FirstDestElement,physx::PxU32 NumElements)
{
	check(IsInGameThread());

	EnqueWriteInstanceBuffer *e = NULL;
	for (TFEnqueDataArray::iterator i=EnqueDataReuse.begin(); i!=EnqueDataReuse.end(); ++i)
	{
		FEnqueData *ed = (*i);
		if (ed && ed->mType == ET_WRITE_INSTANCE_BUFFER )
		{
			EnqueWriteInstanceBuffer *found = static_cast< EnqueWriteInstanceBuffer *>(ed);
			if ( found->InstanceBufferMatch(buffer,Semantic,SrcData,SrcStride,FirstDestElement,NumElements) )
			{
				(*i) = NULL;
				e = found;
				break;
			}
		}
	}

	if ( e == NULL )
	{
    	e = new EnqueWriteInstanceBuffer(buffer,Semantic,SrcData,SrcStride,FirstDestElement,NumElements);
	}

	PostFEnqueDataGameThread(e);
   	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
   	(
   		FEnqueData,
   		EnqueWriteInstanceBuffer *, e, e,
   		{
   			GApexRender->PostFEnqueDataRenderingThread(e);
   		}
   	);
}

// Add a create render resource request to the queue
void FApexRenderResourceManager::Enque(FApexRenderResource *buffer,const physx::NxUserRenderResourceDesc &desc)
{
	check(IsInGameThread());

	EnqueCreateRenderResource *e = new EnqueCreateRenderResource(buffer,desc);
	PostFEnqueDataGameThread(e);

	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
	(
		FEnqueData,
		EnqueCreateRenderResource *, e, e,
		{
			GApexRender->PostFEnqueDataRenderingThread(e);
		}
	);

}

using namespace physx::apex;

FIApexRender*	GApexRender = NULL;
physx::PxF32	GApexNormalSign = 1;

/* FApexDynamicRenderer */

void FApexDynamicRenderer::renderResource(const NxApexRenderContext &Context)
{
	if (Context.renderResource)
	{
		FApexRenderResource& Mesh = *static_cast<FApexRenderResource*>(Context.renderResource);
		UStaticMesh* StaticMesh = (UStaticMesh*)Mesh.GetOpaqueMesh();

		if (StaticMesh)
		{
			// Render using a UE3 StaticMesh object!
			UINT InstancesNum = Mesh.GetNumInstances();

			GApexRender->addParticleCount(InstancesNum);
			
			if (!InstancesNum)
			{
				return;
			}

			FApexRenderInstanceBuffer* InstanceBuffer = Mesh.GetInstanceBuffer();
			
			Mesh.InitInstancedResources();

			const FStaticMeshRenderData& LODModel = StaticMesh->LODModels(0);
			const FStaticMeshElement& Element = LODModel.Elements(0);

			FMeshEmitterMaterialInstanceResource AutoMIRes;
			FMeshEmitterMaterialInstanceResource* MIRes = &AutoMIRes;

			MIRes->Param_MeshEmitterVertexColor = FLinearColor(1.0f, 1.0f, 1.0f);

			// Use default material if 'MATUSAGE_InstancedMeshParticles' flag is not set
			if (Element.Material)
			{
				UMaterial* Material = Element.Material->GetMaterial();

				if (Material->GetUsageByFlag(MATUSAGE_InstancedMeshParticles))
				{
					MIRes->Parent = Element.Material->GetRenderProxy(bSelected);
				}
				else
				{
					MIRes->Parent = GEngine->DefaultMaterial->GetRenderProxy(bSelected);
				}
			}
			else
			{
				// NVCHANGE_BEGIN: LRR - Don't access Element.Material if it is NULL

				MIRes->Parent = GEngine->DefaultMaterial->GetRenderProxy(bSelected);
				
				// NVCHANGE_END: LRR - Don't access Element.Material if it is NULL
			}

			UBOOL bWireframe = ((View->Family->ShowFlags & SHOW_Wireframe) && !(View->Family->ShowFlags & SHOW_Materials));

			FMeshBatch MeshElement;
			FMeshBatchElement& BatchElement = MeshElement.Elements(0);

			MeshElement.VertexFactory  = Mesh.GetVertexFactory();
			MeshElement.DynamicVertexData = NULL;
			MeshElement.LCI = NULL;

			BatchElement.FirstIndex     = Element.FirstIndex;
			BatchElement.MinVertexIndex = Element.MinVertexIndex;
			BatchElement.MaxVertexIndex = Element.MaxVertexIndex;
			MeshElement.UseDynamicData = FALSE;
			MeshElement.ReverseCulling = FALSE;
			MeshElement.CastShadow     = FALSE;
			MeshElement.DepthPriorityGroup = (ESceneDepthPriorityGroup)DPGIndex;
			MeshElement.bWireframe     = bWireframe;
			MeshElement.bUsePreVertexShaderCulling = FALSE;
			MeshElement.PlatformMeshData = NULL;

			if (bWireframe && LODModel.WireframeIndexBuffer.IsInitialized())
			{
				BatchElement.IndexBuffer    = &LODModel.WireframeIndexBuffer;
				MeshElement.MaterialRenderProxy = MIRes;
				MeshElement.Type           = PT_LineList;
				BatchElement.NumPrimitives  = LODModel.WireframeIndexBuffer.Indices.Num() / 2;
			}
			else
			{
				BatchElement.IndexBuffer    = &LODModel.IndexBuffer;
				MeshElement.MaterialRenderProxy = MIRes;
				MeshElement.Type           = PT_TriangleList;
				BatchElement.NumPrimitives  = LODModel.IndexBuffer.Indices.Num() / 3;
			}

			PDI.DrawMesh(MeshElement);
		}
		else
		{
			FMeshBatch MeshElement;
			if (Mesh.loadMeshElement(MeshElement, Context, bSelected, NULL))
			{
				MeshElement.DepthPriorityGroup	= DPGIndex;

				MeshElement.CastShadow = bCastShadow;
				if (bWireframe)
				{
					MeshElement.bWireframe = TRUE;
				}
				FApexRenderInstanceBuffer *InstanceBuffer = Mesh.GetInstanceBuffer();
				if (InstanceBuffer)
				{
					// this code path no longer supported!
					check(0);
				}
				else
				{
					PDI.DrawMesh(MeshElement);
				}
			}
		}
	}
}


/* FApexRenderResourceManager */

NxUserRenderVertexBuffer *FApexRenderResourceManager::createVertexBuffer(const physx::NxUserRenderVertexBufferDesc &Desc)
{
	check(GIsRHIInitialized);
	FApexRenderVertexBuffer *VB = NULL;
#if !ENABLE_NULL_VB
	check(Desc.isValid()); // Commented out for now because sometimes APEX asks for a zero sized VB.
#endif
	if(Desc.isValid())
	{
		VB = new FApexRenderVertexBuffer(Desc);
	}
	check(VB);
	return VB;
}

NxUserRenderIndexBuffer *FApexRenderResourceManager::createIndexBuffer(const NxUserRenderIndexBufferDesc &Desc)
{
	check(GIsRHIInitialized);
	FApexRenderIndexBuffer *IB = NULL;
	check(Desc.isValid());
	if(Desc.isValid())
	{
		IB = new FApexRenderIndexBuffer(Desc);
	}
	return IB;
}

NxUserRenderBoneBuffer *FApexRenderResourceManager::createBoneBuffer(const NxUserRenderBoneBufferDesc &Desc)
{
	check(GIsRHIInitialized);
	FApexRenderBoneBuffer *BB = NULL;
	check(Desc.isValid());
	if(Desc.isValid())
	{
		BB = new FApexRenderBoneBuffer(Desc);
	}
	return BB;
}

NxUserRenderInstanceBuffer *FApexRenderResourceManager::createInstanceBuffer(const NxUserRenderInstanceBufferDesc &Desc)
{
	check(GIsRHIInitialized);
	FApexRenderInstanceBuffer *IB = NULL;
	check(Desc.isValid());
	if(Desc.isValid())
	{
		IB = new FApexRenderInstanceBuffer(Desc);
	}
	return IB;
}

NxUserRenderSpriteBuffer *FApexRenderResourceManager::createSpriteBuffer( const NxUserRenderSpriteBufferDesc &Desc )
{
	ApexRenderSpriteBuffer *buffer = new ApexRenderSpriteBuffer(Desc);
	return static_cast< NxUserRenderSpriteBuffer *>(buffer);
}

NxUserRenderResource *FApexRenderResourceManager::createResource(const physx::NxUserRenderResourceDesc &Desc)
{
	check(GIsRHIInitialized);
	NxUserRenderResource *RenderResource = NULL;
	check(Desc.isValid());
	if(Desc.isValid())
	{
		RenderResource = new FApexRenderResource(Desc);
	}
	return RenderResource;
}

void FApexRenderResourceManager::releaseVertexBuffer(NxUserRenderVertexBuffer &InBuffer)
{
	if(IsInRenderingThread())
	{
		delete static_cast<FApexRenderVertexBuffer*>(&InBuffer);
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseVertexBuffer,
			NxUserRenderVertexBuffer*, Buffer, &InBuffer,
			{
				delete static_cast<FApexRenderVertexBuffer*>(Buffer);
			}
		);
	}
}

void FApexRenderResourceManager::releaseIndexBuffer(NxUserRenderIndexBuffer &InBuffer)
{
	if(IsInRenderingThread())
	{
		delete static_cast<FApexRenderIndexBuffer*>(&InBuffer);
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseIndexBuffer,
			NxUserRenderIndexBuffer*, Buffer, &InBuffer,
			{
				delete static_cast<FApexRenderIndexBuffer*>(Buffer);
			}
		);
	}
}

void FApexRenderResourceManager::releaseBoneBuffer(NxUserRenderBoneBuffer &InBuffer)
{
	if(IsInRenderingThread())
	{
		delete static_cast<FApexRenderBoneBuffer*>(&InBuffer);
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseBoneBuffer,
			NxUserRenderBoneBuffer*, Buffer, &InBuffer,
			{
				delete static_cast<FApexRenderBoneBuffer*>(Buffer);
			}
		);
	}
}

void FApexRenderResourceManager::releaseInstanceBuffer(NxUserRenderInstanceBuffer &InBuffer)
{
	if(IsInRenderingThread())
	{
		delete static_cast<FApexRenderInstanceBuffer*>(&InBuffer);
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseInstanceBuffer,
			NxUserRenderInstanceBuffer*, Buffer, &InBuffer,
			{
				delete static_cast<FApexRenderInstanceBuffer*>(Buffer);
			}
		);
	}
}

void FApexRenderResourceManager::releaseSpriteBuffer( NxUserRenderSpriteBuffer &InBuffer )
{
	if (IsInRenderingThread())
	{
		delete static_cast<ApexRenderSpriteBuffer*>(&InBuffer);
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseSpriteBuffer,
			NxUserRenderSpriteBuffer*, Buffer, &InBuffer,
			{
				delete static_cast<ApexRenderSpriteBuffer*>(Buffer);
			}
		);
	}
}

void FApexRenderResourceManager::releaseResource(NxUserRenderResource &RenderResource)
{
	if (IsInRenderingThread())
	{
		delete &RenderResource;
	}
	else
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			ReleaseResource,
			NxUserRenderResource*, Resource, &RenderResource,
			{
				delete Resource;
			}
		);
	}
}

physx::PxU32 FApexRenderResourceManager::getMaxBonesForMaterial(void *Material)
{
	return APEX_MAX_BONES;
}


/* FApexDynamicResources */

FApexDynamicResources::FApexDynamicResources(INT /* NumBones */)
{
	// Unimplemented
}


/*	UApexStaticComponent */

FPrimitiveSceneProxy *UApexStaticComponent::CreateSceneProxy()
{
	return new FApexStaticSceneProxy(*this);
}


/* FApexBaseSceneProxy */

FApexBaseSceneProxy::FApexBaseSceneProxy(const UApexComponentBase &Component):
FPrimitiveSceneProxy(&Component, Component.Asset->GetFName()),
Owner(Component.GetOwner()),
TotalScale3D(1.0f,1.0f,1.0f),
bCastShadow(Component.CastShadow),
bShouldCollide(Component.ShouldCollide()),
bBlockZeroExtent(Component.BlockZeroExtent),
bBlockNonZeroExtent(Component.BlockNonZeroExtent),
bBlockRigidBody(Component.BlockRigidBody),
bForceStaticDecal(TRUE),	// Not using Component.bForceStaticDecals
MaterialViewRelevance(Component.GetMaterialViewRelevance()),
WireframeColor(FColor(255,128,64,255))	// Not using Component.WireframeColor
{
	bMovable            = TRUE;
	bApexUpdateRequired = FALSE;
}

FApexBaseSceneProxy::FApexBaseSceneProxy(const UApexRenderVolumeComponent &Component):
FPrimitiveSceneProxy(&Component),
Owner(Component.GetOwner()),
TotalScale3D(1.0f,1.0f,1.0f),
bCastShadow(Component.CastShadow),
bShouldCollide(Component.ShouldCollide()),
bBlockZeroExtent(Component.BlockZeroExtent),
bBlockNonZeroExtent(Component.BlockNonZeroExtent),
bBlockRigidBody(Component.BlockRigidBody),
bForceStaticDecal(TRUE),	// Not using Component.bForceStaticDecals
MaterialViewRelevance(Component.GetMaterialViewRelevance()),
WireframeColor(FColor(255,128,64,255))	// Not using Component.WireframeColor
{
	bMovable            = TRUE;
	bApexUpdateRequired = FALSE;
}


/* FPrimitiveSceneProxy interface. */
void FApexBaseSceneProxy::DrawStaticElements(FStaticPrimitiveDrawInterface* PDI)
{
}

/**
* Draw the scene proxy as a dynamic element
*
* @param	PDI - draw interface to render to
* @param	View - current view
* @param	DPGIndex - current depth priority
* @param	Flags - optional set of flags from EDrawDynamicElementFlags
*/
void FApexBaseSceneProxy::DrawDynamicElements(FPrimitiveDrawInterface *PDI, const FSceneView *View, UINT DPGIndex, DWORD Flags)
{
	// Bool that defines how we should draw the collision for this mesh.
	const UBOOL bIsCollisionView      = IsCollisionView(View);
	const UBOOL bDrawCollision        = bIsCollisionView;	// Not using && ShouldDrawCollision(View)
	const UBOOL bDrawSimple           = FALSE;	// Not using ShouldDrawSimpleCollision(View, StaticMesh)
	const UBOOL bDrawComplexCollision = (bDrawCollision && !bDrawSimple);
	const UBOOL bDrawSimpleCollision  = (bDrawCollision && bDrawSimple);
	const UBOOL bDrawMesh             = bIsCollisionView ? bDrawComplexCollision : IsRichView(View) || HasViewDependentDPG() || IsMovable();

	check(PDI && View && View->Family && PrimitiveSceneInfo);
	if(PDI && View && View->Family && PrimitiveSceneInfo)
	{
		EShowFlags ShowFlags = View->Family->ShowFlags;
		if(DPGIndex == SDPG_Foreground && (ShowFlags & SHOW_Bounds) && (ShowFlags & SHOW_StaticMeshes) && (GIsGame || !Owner || bSelected))
		{
			// Draw the static mesh's bounding box and sphere.
			DrawWireBox(PDI, PrimitiveSceneInfo->Bounds.GetBox(), FColor(72,72,255), SDPG_Foreground);
			DrawCircle( PDI, PrimitiveSceneInfo->Bounds.Origin, FVector(1,0,0), FVector(0,1,0), FColor(255,255,0), PrimitiveSceneInfo->Bounds.SphereRadius, 32, SDPG_Foreground);
			DrawCircle( PDI, PrimitiveSceneInfo->Bounds.Origin, FVector(1,0,0), FVector(0,0,1), FColor(255,255,0), PrimitiveSceneInfo->Bounds.SphereRadius, 32, SDPG_Foreground);
			DrawCircle( PDI, PrimitiveSceneInfo->Bounds.Origin, FVector(0,1,0), FVector(0,0,1), FColor(255,255,0), PrimitiveSceneInfo->Bounds.SphereRadius, 32, SDPG_Foreground);
		}
	}
}

void FApexBaseSceneProxy::OnTransformChanged()
{
	// Update the cached scaling.
	TotalScale3D.X = FVector(LocalToWorld.TransformNormal(FVector(1,0,0))).Size();
	TotalScale3D.Y = FVector(LocalToWorld.TransformNormal(FVector(0,1,0))).Size();
	TotalScale3D.Z = FVector(LocalToWorld.TransformNormal(FVector(0,0,1))).Size();
}

FPrimitiveViewRelevance FApexBaseSceneProxy::GetViewRelevance(const FSceneView* View)
{
	FPrimitiveViewRelevance Result;

	// Signal that we need to call NxApexRenderable::updateRenderResources()
	bApexUpdateRequired = TRUE;
	bRewriteBuffersRequired = GApexRender->GetRequireRewriteBuffers();

#if 1 // Force UE3 to render APEX actors as Dynamic.

	EShowFlags ShowFlags = (View && View->Family) ? View->Family->ShowFlags : 0;
	if(ShowFlags & SHOW_StaticMeshes)
	{
	#if ENABLE_STATIC_RENDER
		Result.bStaticRelevance  = TRUE;
	#else
		Result.bStaticRelevance  = FALSE;
	#endif
		Result.bDynamicRelevance = TRUE;
		Result.SetDPG(GetDepthPriorityGroup(View), TRUE);

		MaterialViewRelevance.SetPrimitiveViewRelevance(Result);

		EShowFlags ShowFlags = View->Family->ShowFlags;
		if(ShowFlags & SHOW_Bounds)
		{
			Result.SetDPG(SDPG_Foreground, TRUE);
		}

		if(IsShadowCast(View))
		{
			Result.bShadowRelevance = TRUE;
		}
	}

#else

	if(View->Family->ShowFlags & SHOW_StaticMeshes)
	{
		if(IsShown(View))
		{
#if !FINAL_RELEASE
			if(IsCollisionView(View))
			{
				Result.bDynamicRelevance = TRUE;
				Result.bForceDirectionalLightsDynamic = TRUE;
			}
			else
#endif
			if(
#if !FINAL_RELEASE
				IsRichView(View) ||
#endif
				HasViewDependentDPG() ||
				IsMovable()	)
			{
				Result.bDynamicRelevance = TRUE;
			}
			else
			{
				Result.bStaticRelevance = TRUE;
			}
			Result.SetDPG(GetDepthPriorityGroup(View),TRUE);
		}

#if !FINAL_RELEASE
		if(View->Family->ShowFlags & (SHOW_Bounds|SHOW_Collision))
		{
			Result.bDynamicRelevance = TRUE;
		}

		// only add to foreground DPG for debug rendering
		if(View->Family->ShowFlags & SHOW_Bounds)
		{
			Result.SetDPG(SDPG_Foreground,TRUE);
		}
#endif
		if(IsShadowCast(View))
		{
			Result.bShadowRelevance = TRUE;
		}

		MaterialViewRelevance.SetPrimitiveViewRelevance(Result);

		Result.bDecalStaticRelevance = HasRelevantStaticDecals(View);
		Result.bDecalDynamicRelevance = HasRelevantDynamicDecals(View);
	}

#endif
	return Result;
}


/**
 *	Determines the relevance of this primitive's elements to the given light.
 *	@param	LightSceneInfo			The light to determine relevance for
 *	@param	bDynamic (output)		The light is dynamic for this primitive
 *	@param	bRelevant (output)		The light is relevant for this primitive
 *	@param	bLightMapped (output)	The light is light mapped for this primitive
 */
void FApexBaseSceneProxy::GetLightRelevance(const FLightSceneInfo* LightSceneInfo, UBOOL& bDynamic, UBOOL& bRelevant, UBOOL& bLightMapped) const
{
	bDynamic = TRUE;
	bRelevant = TRUE;
	bLightMapped = FALSE;
}


/* FApexDynamicSceneProxy */

FApexDynamicSceneProxy::FApexDynamicSceneProxy(const UApexDynamicComponent &Component):
FApexBaseSceneProxy(Component),
ComponentDynamicResources(Component.ComponentDynamicResources)
{
}

void FApexDynamicSceneProxy::DrawDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags)
{
}


/* FApexStaticSceneProxy */

/** Constructor - called from the game thread, initializes the proxy's copies of the component's data */
FApexStaticSceneProxy::FApexStaticSceneProxy(const UApexStaticComponent &Component) :
FApexBaseSceneProxy(Component),
ApexComponent(Component)
{
	check( IsInGameThread() );
	ApexRenderable = ApexComponent.GetApexRenderable();
	// NVCHANGE_BEGIN: JCAO - Remove OverrideMats
	// NVCHANGE_END: JCAO - Remove OverrideMats
}

// FPrimitiveSceneProxy interface.
void FApexStaticSceneProxy::DrawStaticElements(FStaticPrimitiveDrawInterface *PDI)
{
	check(PDI);
	if(PDI && ApexRenderable && GApexCommands->IsShowApex() )
	{
	#if ENABLE_STATIC_RENDER // this gets called from game thread... DrawDynamicElements gets called from rendering thread though.
		FApexStaticRenderer ApexRenderer(*PDI, bSelected, bCastShadow);
		ApexRenderable->dispatchRenderResources(ApexRenderer, 1.0f);
		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER
		(
			DrawApexRenderable,
			NxApexRenderable*, ApexRenderable, ApexRenderable,
			{
				ApexRenderable->updateRenderResources();
			}
		);
	#endif
	}
	FApexBaseSceneProxy::DrawStaticElements(PDI);
}

/**
 * Draw the scene proxy as a dynamic element
 *
 * @param	PDI - draw interface to render to
 * @param	View - current view
 * @param	DPGIndex - current depth priority
 * @param	Flags - optional set of flags from EDrawDynamicElementFlags
 */
void FApexStaticSceneProxy::DrawDynamicElements(FPrimitiveDrawInterface *PDI, const FSceneView *View, UINT DPGIndex, DWORD Flags)
{
	check(PDI);
	if( PDI && ApexRenderable && DPGIndex != SDPG_Foreground && GApexCommands->IsShowApex() )
	{
	#if !ENABLE_STATIC_RENDER
		UBOOL bWireframe = (View && View->Family && (View->Family->ShowFlags & SHOW_Wireframe)) ? TRUE : FALSE;
		FApexDynamicRenderer ApexRenderer(*PDI, bSelected, bCastShadow, bWireframe,View,DPGIndex);
		if(bApexUpdateRequired)
		{
			// NVCHANGE_BEGIN: JCAO - Remove OverrideMats
			// NVCHANGE_END: JCAO - Remove OverrideMats
			ApexRenderable->lockRenderResources();
			// NVCHANGE_BEGIN: JCAO - Remove OverrideMats
			ApexRenderable->updateRenderResources( bRewriteBuffersRequired, NULL );
			// NVCHANGE_END: JCAO - Remove OverrideMats
			ApexRenderable->unlockRenderResources();
			bApexUpdateRequired = FALSE;
			bRewriteBuffersRequired = FALSE;
		}
		ApexRenderable->dispatchRenderResources(ApexRenderer);
	#endif
	}
	FApexBaseSceneProxy::DrawDynamicElements(PDI, View, DPGIndex, Flags);
}

/* FApexRenderVolumeSceneProxy */

/** Constructor - called from the game thread, initializes the proxy's copies of the component's data */
FApexRenderVolumeSceneProxy::FApexRenderVolumeSceneProxy(const UApexRenderVolumeComponent &Component) :
FApexBaseSceneProxy(Component),
ApexComponent(Component)
{
	check( IsInGameThread() );
	ApexRenderable = ApexComponent.GetApexRenderable();
}


// FPrimitiveSceneProxy interface.
void FApexRenderVolumeSceneProxy::DrawStaticElements(FStaticPrimitiveDrawInterface *PDI)
{
}

/**
 * Draw the scene proxy as a dynamic element
 *
 * @param	PDI - draw interface to render to
 * @param	View - current view
 * @param	DPGIndex - current depth priority
 * @param	Flags - optional set of flags from EDrawDynamicElementFlags
 */
void FApexRenderVolumeSceneProxy::DrawDynamicElements(FPrimitiveDrawInterface *PDI, const FSceneView *View, UINT DPGIndex, DWORD Flags)
{
	check(PDI);
	ApexRenderable = ApexComponent.GetApexRenderable();
	if( PDI && ApexRenderable )
	{
		UBOOL bWireframe = (View && View->Family && (View->Family->ShowFlags & SHOW_Wireframe)) ? TRUE : FALSE;
		FApexDynamicRenderer ApexRenderer(*PDI, bSelected, bCastShadow, bWireframe,View,DPGIndex);
		void* ApexUserData = NULL;
		ApexRenderable->lockRenderResources();
		ApexRenderable->updateRenderResources( false, ApexUserData );
		ApexRenderable->unlockRenderResources();
		ApexRenderable->dispatchRenderResources(ApexRenderer);
	}
	FApexBaseSceneProxy::DrawDynamicElements(PDI, View, DPGIndex, Flags);
}


NxUserRenderer	* FApexRenderResourceManager::CreateDynamicRenderer(void *InPDI, UBOOL Selected, UBOOL CastShadow, UBOOL WireFrame, const FSceneView *View, UINT DPGIndex)
{
	NxUserRenderer *Ret = NULL;
	if ( InPDI )
	{
		physx::PxMat44 v;
		FMatrixToPxMat44(View->ViewMatrix,v);
		GApexRender->SetViewMatrix(v);
		FPrimitiveDrawInterface *PDI = (FPrimitiveDrawInterface *)InPDI;
		FApexDynamicRenderer *Renderer = new FApexDynamicRenderer(*PDI,Selected,CastShadow,WireFrame,View,DPGIndex);
		Ret = static_cast< NxUserRenderer *>(Renderer);
	}
	return Ret;
}

void FApexRenderResourceManager::ReleaseDynamicRenderer(NxUserRenderer *UserRenderer)
{
	FApexDynamicRenderer *Renderer = static_cast< FApexDynamicRenderer *>(UserRenderer);
	delete Renderer;
}

FIApexRender * CreateApexRender(void)
{
	FApexRenderResourceManager *Manager = new FApexRenderResourceManager;
	return static_cast< FIApexRender *>(Manager);
}

void          ReleaseApexRender(FIApexRender *Renderer)
{
	FApexRenderResourceManager *Manager = static_cast< FApexRenderResourceManager *>(Renderer);
	delete Manager;
}

// Post this rendering request to the rendering thread queue
void FApexRenderResourceManager::PostFEnqueDataRenderingThread(FEnqueData *e)
{
	check(IsInRenderingThread());
	check( e != NULL );
	check( e->IsSemaphoreUsed() );
	e->ProcessRenderingThread();
}

// Post this rendering request to the game thread queue
void FApexRenderResourceManager::PostFEnqueDataGameThread(FEnqueData *e)
{
	check(IsInGameThread());
	check( !e->IsSemaphoreUsed() );
	e->SetSemaphore();
	EnqueDataGameThread.push_back(e);
}

// Notification that a buffer has been released.  This always happens in the rendering thread.
// If this buffer was actively in the rendering thread queue, its semaphore is cleared so that it can
// be properly released by the game thread.
void FApexRenderResourceManager::NotifyEnqueBufferGone(void *buffer)
{
	check(IsInRenderingThread());
	for (TFEnqueDataArray::iterator i=EnqueDataRenderingThread.begin(); i!=EnqueDataRenderingThread.end(); ++i)
	{
		FEnqueData *e = (*i);
		if ( e )
		{
			UBOOL gone = (*i)->NotifyBufferGone(buffer);
			if ( gone )
			{
				(*i) = NULL;
			}
		}
	}
}

// Process all pending rendering requests from inside the rendering thread
void FApexRenderResourceManager::ProcessFEnqueDataRenderingThread(void)
{
	check(IsInRenderingThread());
	if ( !EnqueDataRenderingThread.empty() )
	{
		for (TFEnqueDataArray::iterator i=EnqueDataRenderingThread.begin(); i!=EnqueDataRenderingThread.end(); ++i)
		{
			FEnqueData *e = (*i);
			if ( e )
			{
				check( e->IsSemaphoreUsed() );
				e->ProcessRenderingThread();
			}
		}
		EnqueDataRenderingThread.clear();
	}
}

// Process all pending requests in the game thread.
void FApexRenderResourceManager::ProcessFEnqueDataGameThread(void)
{
	check(IsInGameThread());

	// See if any of the objects in the 'reuse' thread were not re-used by additional requests.
	// If the were not reused, then delete them.
	for (TFEnqueDataArray::iterator i=EnqueDataReuse.begin(); i!=EnqueDataReuse.end(); ++i)
	{
		FEnqueData *e = (*i);
		if ( e && e->IsUnused() )
		{
			(*i) = 0;
			delete e;
			EnqueDataReuseCount = 2;
		}
	}

	// If it has been several frames since the last time we deleted an object from the 'resue' queue, then clean up the list.
	if ( EnqueDataReuseCount )
	{
		EnqueDataReuseCount--;
		if ( EnqueDataReuseCount == 0 )
		{
			TFEnqueDataArray temp;
        	for (TFEnqueDataArray::iterator i=EnqueDataReuse.begin(); i!=EnqueDataReuse.end(); ++i)
        	{
        		FEnqueData *e = (*i);
        		if ( e )
        		{
        			temp.push_back(e);
        		}
        	}
        	EnqueDataReuse = temp;
		}
	}

	// If we have objects in the game thread queue
	if ( !EnqueDataGameThread.empty() )
	{
		UBOOL dead = FALSE;
		UBOOL alive = FALSE;
		for (TFEnqueDataArray::iterator i=EnqueDataGameThread.begin(); i!=EnqueDataGameThread.end(); ++i)
		{
			FEnqueData *e = (*i);
			if ( e )
			{
				UBOOL kill = e->ProcessGameThread();
				if ( kill )
				{
					if ( e->mType == ET_WRITE_VERTEX_BUFFER )
					{
						for (TFEnqueDataArray::iterator j=EnqueDataReuse.begin(); j!=EnqueDataReuse.end(); ++j)
						{
							if ( (*j) == NULL )
							{
								(*j) = e;
								e = NULL;
								break;
							}
						}
						if ( e )
						{
							check( !e->IsSemaphoreUsed() );
							EnqueDataReuse.push_back(e);
						}
					}
					else
					{
						delete e;
					}
					(*i) = NULL;
					dead = TRUE;
				}
				else
				{
					alive = TRUE; // not that at least
				}
			}
			else
			{
				dead = TRUE;
			}
		}
		if ( dead && !alive ) // if all items are dead, and none are alive, we clear the queue
		{
			EnqueDataGameThread.clear();
		}
		else if ( dead && alive ) // if some are dead and some are alive, we need to rebuild the queue with only the alive ones.
		{
			TFEnqueDataArray aliveData;
			for (TFEnqueDataArray::iterator i=EnqueDataGameThread.begin(); i!=EnqueDataGameThread.end(); ++i)
			{
				FEnqueData *e = (*i);
				if ( e )
				{
					aliveData.push_back(e);
				}
			}
			EnqueDataGameThread = aliveData;
		}
	}
}


void FApexRenderResourceManager::FlushFEnqueDataGameThread(void)
{
	check(IsInGameThread());

	if ( !EnqueDataGameThread.empty() )
	{
		for (TFEnqueDataArray::iterator i=EnqueDataGameThread.begin(); i!=EnqueDataGameThread.end(); ++i)
		{
			FEnqueData *e = (*i);
			if ( e )
			{
				delete e;
			}
		}
		EnqueDataGameThread.clear();
	}
	if ( !EnqueDataReuse.empty() )
	{
		for (TFEnqueDataArray::iterator i=EnqueDataReuse.begin(); i!=EnqueDataReuse.end(); ++i)
		{
			FEnqueData *e = (*i);
			if ( e )
			{
				delete e;
			}
		}
		EnqueDataReuse.clear();
	}
}

void FApexRenderResourceManager::FlushFEnqueDataRenderingThread(void)
{
	check(IsInRenderingThread());
	for (TFEnqueDataArray::iterator i=EnqueDataRenderingThread.begin(); i!=EnqueDataRenderingThread.end(); ++i)
	{
		FEnqueData *e = (*i);
		if( e != NULL)
		{
			e->ClearSemaphore();
		}
	}
	EnqueDataRenderingThread.clear();
}

FApexRenderResourceManager::FApexRenderResourceManager(void)
{
	mView = physx::PxMat44::createIdentity();
	mParticleCount = 0;
	GApexRender = this;
	EnqueDataReuseCount = 0;
	GApexManager->SetRenderResourceManager(this);
}

FApexRenderResourceManager::~FApexRenderResourceManager(void)
{
	FlushFEnqueDataGameThread();
	GApexRender = NULL;
	GApexManager->SetRenderResourceManager(0);
}

//**** InstanceBuffer implementation

// NVCHANGE_BEGIN: LRR - instance buffer class is now an FRenderResource so that "device lost" is handled
FApexRenderInstanceBuffer::FApexRenderInstanceBuffer(const NxUserRenderInstanceBufferDesc &Desc) :
	pInstanceBuffer(NULL),
	pTemporaryWriteBuffer(NULL),
	bRegisteredInCUDA(false),
	bAttemptToRegisterInCUDA(false)
{
	MaxInstances	= Desc.maxInstances;
	ElementStride	= Desc.stride;

#if WITH_CUDA_INTEROP
	bAttemptToRegisterInCUDA = Desc.registerInCUDA;
	if (bAttemptToRegisterInCUDA)
	{
		pInteropContext	= Desc.interopContext;
	}
	else
	{
		pInteropContext	= NULL;
	}
#endif

	// float3 - POSITION
	// float3x3 - ROTATION_SCALE
	const UINT DefaultStride = 48;

	if (!ElementStride)
	{
		ElementStride = DefaultStride;
	}

	// The base class will call InitDynamicRHI()
	InitResource();
}

FApexRenderInstanceBuffer::~FApexRenderInstanceBuffer()
{
	ReleaseResource();

#if WITH_CUDA_INTEROP
	pInteropContext = NULL;
	bAttemptToRegisterInCUDA = false;
#endif
}

void FApexRenderInstanceBuffer::InitDynamicRHI(void)
{
	// Create HW instance buffer
	UINT BufferSize = ElementStride * MaxInstances;

	if (BufferSize)
	{
		check(!pInstanceBuffer);

		pInstanceBuffer = new FVertexBuffer;
		check(pInstanceBuffer);

		pInstanceBuffer->InitResource();
		pInstanceBuffer->VertexBufferRHI = RHICreateVertexBuffer(BufferSize, NULL, RUF_Dynamic | RUF_WriteOnly);
		
#if WITH_CUDA_INTEROP
		if (bAttemptToRegisterInCUDA && pInteropContext)
		{
			FVertexBufferRHIParamRef Ref = pInstanceBuffer->VertexBufferRHI;

			if (pInteropContext->getInteropMode() == physx::pxtask::CudaInteropMode::D3D9_INTEROP)
			{
				bRegisteredInCUDA = pInteropContext->registerResourceInCudaD3D( InteropHandle,
					static_cast<IDirect3DResource9*>(static_cast<FD3D9VertexBuffer*>(Ref)) );
			}
			else if (pInteropContext->getInteropMode() == physx::pxtask::CudaInteropMode::D3D11_INTEROP)
			{
				bRegisteredInCUDA = pInteropContext->registerResourceInCudaD3D( InteropHandle,
					static_cast<ID3D11Resource*>(static_cast<FD3D11VertexBuffer*>(Ref)->Resource) );
			}
		}
#endif
	}
}

void FApexRenderInstanceBuffer::ReleaseDynamicRHI(void)
{
#if WITH_CUDA_INTEROP
	if (bRegisteredInCUDA && InteropHandle)
	{
		pInteropContext->unregisterResourceInCuda(InteropHandle);
		bRegisteredInCUDA = false;
		bAttemptToRegisterInCUDA = false;
	}
#endif
	if (pInstanceBuffer)
	{
		pInstanceBuffer->ReleaseResource();
		delete pInstanceBuffer;
		pInstanceBuffer = NULL;
	}

	ReleaseDynamicBuffer();
}

// NVCHANGE_END: LRR - instance buffer class is now an FRenderResource so that "device lost" is handled

bool FApexRenderInstanceBuffer::getInteropResourceHandle(CUgraphicsResource &handle)
{
#if WITH_CUDA_INTEROP
	if (bRegisteredInCUDA && InteropHandle)
	{
		handle = InteropHandle;
		ReleaseDynamicBuffer();

		return true;
	}
#endif
	return false;
}

void FApexRenderInstanceBuffer::writeBuffer(const NxApexRenderInstanceBufferData &data, physx::PxU32 firstInstance, physx::PxU32 numInstances)
{
	// Normally shouldn't be called with registered CUDA resource
	if (!numInstances)
	{
		return;
	}

	BYTE* PositionsData = NULL;
	UINT PositionsStride = 0;
	BYTE* RotationsData = NULL;
	UINT RotationsStride = 0;
	FVertexBuffer* pWriteBuffer = GetBuffer();

	for (physx::PxU32 i=0; i<NxRenderInstanceSemantic::NUM_SEMANTICS; ++i)
	{
		NxRenderInstanceSemantic::Enum Semantic = (NxRenderInstanceSemantic::Enum)i;
		const NxApexRenderSemanticData &SemanticData = data.getSemanticData(Semantic);
		
		if (Semantic == NxRenderInstanceSemantic::POSITION)
		{
			PositionsData = (BYTE*)SemanticData.data;
			PositionsStride = SemanticData.stride;
		}
		else if (Semantic == NxRenderInstanceSemantic::ROTATION_SCALE)
		{
			RotationsData = (BYTE*)SemanticData.data;
			RotationsStride = SemanticData.stride;
		}
	}

	if (PositionsData && RotationsData)
	{
		UINT Bounds[] = {firstInstance * ElementStride, (firstInstance + numInstances) * ElementStride};
		
		if (bRegisteredInCUDA)
		{
			AllocateDynamicBuffer();
			pWriteBuffer = pTemporaryWriteBuffer;
		}
		
		BYTE* InstanceData = (BYTE*)RHILockVertexBuffer(pWriteBuffer->VertexBufferRHI, Bounds[0], Bounds[1], FALSE);

		for (UINT i=0; i<numInstances; ++i)
		{
			memcpy(InstanceData, PositionsData + PositionsStride * i, sizeof(float) * 3);
			memcpy(InstanceData + sizeof(float) * 3, RotationsData + RotationsStride * i, sizeof(float) * 9);
			
			InstanceData += ElementStride;
		}

		RHIUnlockVertexBuffer(pWriteBuffer->VertexBufferRHI);
	}
}

void FApexRenderInstanceBuffer::writeBuffer( physx::NxRenderInstanceSemantic::Enum Semantic, const void *SrcData, physx::PxU32 SrcStride, physx::PxU32 FirstDestElement, physx::PxU32 NumElements)
{
	// Normally shouldn't be called with registered CUDA resource
	if (!NumElements)
	{
		return;
	}

	UINT Bounds[] = {FirstDestElement * ElementStride, (FirstDestElement + NumElements) * ElementStride};
	const UINT PositionSize = sizeof(float) * 3;
	const UINT RotationSize = sizeof(float) * 9;
	FVertexBuffer* pWriteBuffer = GetBuffer();
	
	if (Semantic == NxRenderInstanceSemantic::POSITION)
	{
		if (bRegisteredInCUDA)
		{
			AllocateDynamicBuffer();
			pWriteBuffer = pTemporaryWriteBuffer;
		}
		
		BYTE* InstanceData = (BYTE*)RHILockVertexBuffer(pWriteBuffer->VertexBufferRHI, Bounds[0], Bounds[1], FALSE);
		BYTE* SourceData = (BYTE*)SrcData;
		
		for (UINT i=0; i<NumElements; ++i)
		{
			memcpy(InstanceData + ElementStride * i, SourceData + SrcStride * i, PositionSize);
		}

		RHIUnlockVertexBuffer(pWriteBuffer->VertexBufferRHI);
	}
	else if(Semantic == NxRenderInstanceSemantic::ROTATION_SCALE)
	{
		if (bRegisteredInCUDA)
		{
			AllocateDynamicBuffer();
			pWriteBuffer = pTemporaryWriteBuffer;
		}

		BYTE* InstanceData = (BYTE*)RHILockVertexBuffer(pWriteBuffer->VertexBufferRHI, Bounds[0], Bounds[1], FALSE);

		BYTE* SourceData = (BYTE*)SrcData;
		InstanceData += PositionSize;
		
		for (UINT i=0; i<NumElements; ++i)
		{
			memcpy(InstanceData + ElementStride * i, SourceData + SrcStride * i, RotationSize);
		}
		
		RHIUnlockVertexBuffer(pWriteBuffer->VertexBufferRHI);
	}
}


//**** SpriteBuffer implementation

physx::PxU32 FApexRenderResourceManager::getSpriteTextureData(physx::PxU32 spriteCount, physx::PxU32 spriteSemanticsBitmap, NxUserRenderSpriteTextureDesc* textureDescArray)
{
	UINT SizeX = (UINT)appCeil(appSqrt((FLOAT)spriteCount));
	//make SizeX >= 32 [32 is WARP_SIZE in CUDA]
	SizeX = Max(SizeX, 32U);
	//compute the next highest power of 2
	SizeX--;
	SizeX |= SizeX >> 1;
	SizeX |= SizeX >> 2;
	SizeX |= SizeX >> 4;
	SizeX |= SizeX >> 8;
	SizeX |= SizeX >> 16;
	SizeX++;

	UINT SizeY = (spriteCount + SizeX-1) / SizeX;
	check( SizeX * SizeY >= spriteCount );

	textureDescArray[0].layout = NxRenderSpriteTextureLayout::POSITION_FLOAT4;
	textureDescArray[1].layout = NxRenderSpriteTextureLayout::SCALE_ORIENT_SUBTEX_FLOAT4;
	textureDescArray[2].layout = (spriteSemanticsBitmap & (1 << NxRenderSpriteSemantic::COLOR_FLOAT4)) ? NxRenderSpriteTextureLayout::COLOR_FLOAT4 : NxRenderSpriteTextureLayout::COLOR_BGRA8;

	const physx::PxU32 TextureCount = 3;
	for (int i = 0; i < TextureCount; ++i)
	{
		textureDescArray[i].width = SizeX;
		textureDescArray[i].height = SizeY;

		const UINT ElemSize = NxRenderDataFormat::getFormatDataSize( NxRenderSpriteTextureLayout::getLayoutFormat(textureDescArray[i].layout) );
		textureDescArray[i].pitchBytes = ElemSize * textureDescArray[i].width;

		textureDescArray[i].arrayIndex = 0;
		textureDescArray[i].mipLevel = 0;
	}
	return TextureCount;
}

// NVCHANGE_BEGIN: LRR - sprite buffer class is now an FRenderResource so that "device lost" is handled
ApexRenderSpriteBuffer::ApexRenderSpriteBuffer(const NxUserRenderSpriteBufferDesc& Desc)
	: bRegisteredInCUDA(false),
	  bAttemptToRegisterInCUDA(false)
{
	MaxSprites = Desc.maxSprites;

	TextureCount = Desc.textureCount;
	appMemcpy(TextureDescs, Desc.textureDescs, sizeof(NxUserRenderSpriteTextureDesc) * TextureCount);

	InitStaticVB();

#if WITH_CUDA_INTEROP
	bAttemptToRegisterInCUDA = Desc.registerInCUDA;
	if (bAttemptToRegisterInCUDA)
	{
		pInteropContext	= Desc.interopContext;
	}
	else
	{
		pInteropContext	= NULL;
	}
#endif

	UseFloat4Color = (Desc.semanticFormats[NxRenderSpriteSemantic::COLOR_FLOAT4] != NxRenderDataFormat::UNSPECIFIED);

	// The base class will call InitDynamicRHI()
	InitResource();
}

ApexRenderSpriteBuffer::~ApexRenderSpriteBuffer()
{
	ReleaseResource();

#if WITH_CUDA_INTEROP
	pInteropContext = NULL;
	bAttemptToRegisterInCUDA = false;
#endif

	ReleaseStaticVB();
}

void ApexRenderSpriteBuffer::InitDynamicRHI(void)
{
	InitVTFTextures(bAttemptToRegisterInCUDA ? TexCreate_ResolveTargetable : 0);

#if WITH_CUDA_INTEROP
	if (bAttemptToRegisterInCUDA && pInteropContext)
	{
		for (int i = 0; i < NxUserRenderSpriteBufferDesc::MAX_SPRITE_TEXTURES; ++i)
		{
			VTFInteropHandleList[i] = 0;
		}

#define REGISTER_TEXTURES() \
			bRegisteredInCUDA  = pInteropContext->registerResourceInCudaD3D( VTFInteropHandleList[0], GET_TEX_REF(VTFPositionsTexture) ); \
			bRegisteredInCUDA &= pInteropContext->registerResourceInCudaD3D( VTFInteropHandleList[1], GET_TEX_REF(VTFScaleAndRotationTexture) ); \
			bRegisteredInCUDA &= pInteropContext->registerResourceInCudaD3D( VTFInteropHandleList[2], GET_TEX_REF(VTFColorTexture) ); \

		if (pInteropContext->getInteropMode() == physx::pxtask::CudaInteropMode::D3D9_INTEROP)
		{
#define GET_TEX_REF(obj) static_cast<IDirect3DResource9*>(static_cast<FD3D9Texture2D*>(static_cast<FTexture2DRHIParamRef>(obj))->GetReference())
			REGISTER_TEXTURES()
#undef GET_TEX_REF
		}
		else if (pInteropContext->getInteropMode() == physx::pxtask::CudaInteropMode::D3D11_INTEROP)
		{
#define GET_TEX_REF(obj) static_cast<ID3D11Resource*>(static_cast<FD3D11Texture2D*>(static_cast<FTexture2DRHIParamRef>(obj))->Resource.GetReference())
			REGISTER_TEXTURES()
#undef GET_TEX_REF
		}
#undef REGISTER_TEXTURES

		if (!bRegisteredInCUDA)
		{
			ReleaseVTFTextures();
			InitVTFTextures(0);
		}
	}
#endif
}

void ApexRenderSpriteBuffer::ReleaseDynamicRHI(void)
{
#if WITH_CUDA_INTEROP
	if (bRegisteredInCUDA && pInteropContext)
	{
		for (int i = 0; i < NxUserRenderSpriteBufferDesc::MAX_SPRITE_TEXTURES; ++i)
		{
			if (VTFInteropHandleList[i] != 0)
				pInteropContext->unregisterResourceInCuda(VTFInteropHandleList[i]);
		}
		bRegisteredInCUDA = false;
		bAttemptToRegisterInCUDA = false;
	}
#endif

	ReleaseVTFTextures();
}
// NVCHANGE_END: LRR - sprite buffer class is now an FRenderResource so that "device lost" is handled

bool ApexRenderSpriteBuffer::getInteropTextureHandleList(CUgraphicsResource* handleList)
{
#if WITH_CUDA_INTEROP
	if (bRegisteredInCUDA)
	{
		for (int i = 0; i < NxUserRenderSpriteBufferDesc::MAX_SPRITE_TEXTURES; ++i)
		{
			handleList[i] = VTFInteropHandleList[i];
		}
		return true;
	}
#endif
	return false;
}

UBOOL FApexRenderResource::loadMeshElement(FMeshBatch &MeshElement,const NxApexRenderContext &Context,UBOOL bSelected,const FSceneView *View)
{
	UBOOL OK = FALSE;

	if (!VertexBuffers && !SpriteBuffer)
	{
		return FALSE;
	}

	FMeshBatchElement& BatchElement = MeshElement.Elements(0);
	MeshElement.MaterialRenderProxy = Material ? Material->GetRenderProxy(bSelected) : GEngine->DefaultMaterial->GetRenderProxy(bSelected);

	if (SpriteBuffer)
	{
		if ( MeshElement.MaterialRenderProxy )
		{
			const FMaterial *mat = MeshElement.MaterialRenderProxy->GetMaterial();
			if ( mat->IsUsedWithApexSprites() )
			{
				((FMaterial*)mat)->CheckMaterialUsage(MATUSAGE_VTF); // oscar@snda
				FVTFVertexFactoryApexSpriteVTF *VTF = static_cast<FVTFVertexFactoryApexSpriteVTF*>(VertexFactory);
				VTF->InitMesh(MeshElement,View,SpriteBuffer,0,TRUE,*this);
				OK = TRUE;
			}
		}
	}
	else
	{
		VertexFactory->UpdateRHI();
		VertexFactory->InitRHIWithAPEXBuffers(VertexBuffers, NumVertexBuffers, InstanceBuffer, SpriteBuffer);

    	BatchElement.IndexBuffer                = IndexBuffer;
    	BatchElement.FirstIndex                 = FirstIndex;
    	BatchElement.NumPrimitives              = GetNumPrimitives();

    	MeshElement.VertexFactory              = VertexFactory;
    	MeshElement.DynamicVertexData          = NULL;
    	MeshElement.LCI                        = &LightCache;

    	BatchElement.MinVertexIndex             = FirstVertex;
    	BatchElement.MaxVertexIndex             = NumVertices ? FirstVertex+NumVertices-1 : 0;
    	MeshElement.UseDynamicData             = FALSE;

    	const FApexRenderResource *RenderResource = static_cast<const  FApexRenderResource *>(Context.renderResource);

    	MeshElement.ReverseCulling             = RenderResource->GetReverseCulling();

    	MeshElement.CastShadow                 = FALSE;
    	MeshElement.Type                       = PrimitiveType;
    	MeshElement.DepthPriorityGroup         = SDPG_World;
    	MeshElement.bUsePreVertexShaderCulling = TRUE;

    	if(BoneBuffer || InstanceBuffer)
    	{
    		BatchElement.LocalToWorld           = FMatrix::Identity;
    		BatchElement.WorldToLocal           = FMatrix::Identity;
    	}
    	else
    	{
    		BatchElement.LocalToWorld           = N2UTransformApex(Context.local2world);
    		BatchElement.WorldToLocal           = N2UTransformApex(Context.world2local);
    	}
    }

	if(BatchElement.IndexBuffer && BatchElement.NumPrimitives > 0 && MeshElement.VertexFactory && MeshElement.MaterialRenderProxy)
	{
		OK = TRUE;
	}

	return OK;
}

void ApexRenderSpriteBuffer::writeBuffer(const NxApexRenderSpriteBufferData &data, physx::PxU32 firstSprite, physx::PxU32 numSprites)
{
	// NVCHANGE_BEGIN: LRR - no need to do anything if there are no indices to update (prevent a d3d lock failure too)
	if ( 0 == numSprites )
	{
		return;
	}
	// NVCHANGE_END: LRR - no need to do anything if there are no indices to update (prevent a d3d lock failure too)

	if (bRegisteredInCUDA)
		return; //disable in case of INTEROP

	SCOPE_CYCLE_COUNTER(STAT_ApexParticleWriteBuffer);

	const NxApexRenderSemanticData &semanticDataPosition = data.getSemanticData(NxRenderSpriteSemantic::POSITION);

	if (semanticDataPosition.data)
	{
		// particle position goes to one texture
		UINT stride = 0;
		FTexture2DRHIRef& Texture = (FTexture2DRHIRef&)VTFPositionsTexture;
		FVector4* VTFPositionData = (FVector4*)RHILockTexture2D(Texture,0,TRUE,stride,TRUE);
		check((stride / sizeof(FVector4)) == TextureDescs[0].width);
		const BYTE *pPositions = (const BYTE *)semanticDataPosition.data;
		physx::PxU32 *dest = (physx::PxU32 *)&VTFPositionData[firstSprite].X;
		physx::PxU32 pStride = semanticDataPosition.stride;
		physx::PxF32 floatOne = 1;
		const physx::PxU32 *s = (const physx::PxU32 *)&floatOne;
		for(UINT i=0; i<numSprites; i++)
		{
			const physx::PxU32 *pPosition = (const physx::PxU32*)(pPositions);
			dest[0] = pPosition[0];
			dest[1] = pPosition[1];
			dest[2] = pPosition[2];
			dest[3] = *s;
			pPositions+=pStride;
			dest+=4;
		}
		RHIUnlockTexture2D(Texture,0,FALSE);
	}

	{
		const NxApexRenderSemanticData &semanticDataScale		= data.getSemanticData(NxRenderSpriteSemantic::SCALE);
		const NxApexRenderSemanticData &semanticDataRotation	= data.getSemanticData(NxRenderSpriteSemantic::ORIENTATION);
		const NxApexRenderSemanticData &semanticDataSubTexture	= data.getSemanticData(NxRenderSpriteSemantic::SUBTEXTURE);
		UINT stride = 0;
		FTexture2DRHIRef& Texture = (FTexture2DRHIRef&)VTFScaleAndRotationTexture;
		FVector4*  VTFRotationScaleData = (FVector4* )RHILockTexture2D(Texture,0,TRUE,stride,TRUE);
		check((stride / sizeof(FVector4)) == TextureDescs[1].width);
		const BYTE *pScales = (const BYTE *)semanticDataScale.data;
		const BYTE *pRotations = (const BYTE *)semanticDataRotation.data;
		const BYTE *pSubTextures = (const BYTE *)semanticDataSubTexture.data;
		physx::PxF32 defaultScale[2] = { 1, 1 };
		physx::PxF32 defaultRotation = 0;
		physx::PxF32 defaultSubTexture = 0; 
		physx::PxU32 pScalesStride = semanticDataScale.stride;
		physx::PxU32 pRotationsStride = semanticDataRotation.stride;
		physx::PxU32 pSubTexturesStride = semanticDataSubTexture.stride;
		if ( pScales == NULL )
		{
			pScales = (const BYTE *)defaultScale;
			pScalesStride = 0;
		}
		if ( pRotations == NULL )
		{
			pRotations = (const BYTE *)&defaultRotation;
			pRotationsStride = 0;
		}
		if ( pSubTextures == NULL )
		{
			pSubTextures = (const BYTE *)&defaultSubTexture;
			pSubTexturesStride = 0;
		}
		physx::PxU32 *dest = (physx::PxU32 *)&VTFRotationScaleData[firstSprite];
		for(UINT i=0;i<numSprites;i++)
		{
			const physx::PxU32 *scales = (const physx::PxU32 *)pScales;
			dest[0] = scales[0];
			dest[1] = scales[1];
			dest[2] = *(const physx::PxU32 *)(pRotations);
			dest[3] = *(const physx::PxU32 *)(pSubTextures);
			pScales+=pScalesStride;
			pRotations+=pRotationsStride;
			pSubTextures+=pSubTexturesStride;
			dest+=4;
		}
		RHIUnlockTexture2D(Texture,0,FALSE);
	}

	// particle colors goes to one texture
	if (UseFloat4Color)
	{
		const NxApexRenderSemanticData &semanticDataColor = data.getSemanticData(NxRenderSpriteSemantic::COLOR_FLOAT4);
		UINT stride = 0;
		FTexture2DRHIRef& Texture = (FTexture2DRHIRef&)VTFColorTexture;
		FVector4* VTFColorData = (FVector4*)RHILockTexture2D(Texture,0,TRUE,stride,TRUE);
		check((stride / sizeof(FVector4)) == TextureDescs[2].width);
		const BYTE *pColors = (const BYTE *)semanticDataColor.data;
		if ( pColors )
		{
			physx::PxU32 pStride = semanticDataColor.stride;
			physx::PxF32* dest = (physx::PxF32*)&VTFColorData[firstSprite].X;
			for(UINT i=0; i<numSprites; i++)
			{
				const physx::PxF32* pColor = (const physx::PxF32*)(pColors);
				dest[0] = pColor[0];
				dest[1] = pColor[1];
				dest[2] = pColor[2];
				dest[3] = pColor[3];
				dest += 4;
				pColors += pStride;
			}
		}
		else
		{
			physx::PxF32* dest = (physx::PxF32*)&VTFColorData[firstSprite].X;
			for(UINT i=0; i<numSprites; i++)
			{
				dest[0] = 1.0f;
				dest[1] = 1.0f;
				dest[2] = 1.0f;
				dest[3] = 1.0f;
				dest += 4;
			}
		}
		RHIUnlockTexture2D(Texture,0,FALSE);
	}
	else
	{
		const NxApexRenderSemanticData &semanticDataColor = data.getSemanticData(NxRenderSpriteSemantic::COLOR);
		UINT stride = 0;
		FTexture2DRHIRef& Texture = (FTexture2DRHIRef&)VTFColorTexture;
		physx::PxU32* VTFColorData = (physx::PxU32 *)RHILockTexture2D(Texture,0,TRUE,stride,TRUE);
		check((stride / sizeof(physx::PxU32)) == TextureDescs[2].width);
		const BYTE *pColors = (const BYTE *)semanticDataColor.data;
		if ( pColors )
		{
			physx::PxU32 pStride = semanticDataColor.stride;
			physx::PxU32 *dest = &VTFColorData[firstSprite];
			for(UINT i=0; i<numSprites; i++)
			{
				*dest++ = *(const physx::PxU32 *)pColors;
				pColors+=pStride;
			}
		}
		else
		{
			physx::PxU32 *dest = &VTFColorData[firstSprite];
			for(UINT i=0; i<numSprites; i++)
			{
				*dest++ = 0xFFFFFFFF;
			}

		}
		RHIUnlockTexture2D(Texture,0,FALSE);
	}
}

void ApexRenderSpriteBuffer::writeTexture(physx::PxU32 textureId, physx::PxU32 numSprites, const void* srcData, size_t srcSize)
{
	SCOPE_CYCLE_COUNTER(STAT_ApexParticleWriteBuffer);

	FTexture2DRHIRef VTFTexture;
	switch(textureId)
	{
	case 0: VTFTexture = VTFPositionsTexture; break;
	case 1: VTFTexture = VTFScaleAndRotationTexture; break;
	case 2: VTFTexture = VTFColorTexture; break;
	default: check(0); return;
	}

	UINT TexturePitch = 0;
	void* TextureData = RHILockTexture2D(VTFTexture, 0, TRUE, TexturePitch, TRUE);

	// This check shouldn't fail, but if it does, we must copy by texture length instead.
	check(TextureDescs[textureId].pitchBytes == TexturePitch);
	appMemcpy(TextureData, srcData, srcSize);

	RHIUnlockTexture2D(VTFTexture, 0, FALSE);
}


void FVTFVertexFactoryApexSpriteVTF::InitRHIWithAPEXBuffers(const FApexRenderVertexBuffer *const*VertexBuffers,
										UINT NumVertexBuffers,
										const FApexRenderInstanceBuffer *InstanceBuffer,
										const ApexRenderSpriteBuffer *SpriteBuffer)
{
}


void FApexRenderResource::InitInstancedResources()
{
	const FStaticMeshRenderData& LODModel = OpaqueMesh->LODModels(0);
	FLocalInstancedVertexFactoryApex::DataType VertexFactoryData;

	VertexFactoryData.PositionComponent = FVertexStreamComponent(
		&LODModel.PositionVertexBuffer,
		STRUCT_OFFSET(FPositionVertex,Position),
		LODModel.PositionVertexBuffer.GetStride(),
		VET_Float3
		);

	VertexFactoryData.TangentBasisComponents[0] = FVertexStreamComponent(
		&LODModel.VertexBuffer,
		STRUCT_OFFSET(FStaticMeshFullVertex,TangentX),
		LODModel.VertexBuffer.GetStride(),
		VET_PackedNormal
		);
	VertexFactoryData.TangentBasisComponents[1] = FVertexStreamComponent(
		&LODModel.VertexBuffer,
		STRUCT_OFFSET(FStaticMeshFullVertex,TangentZ),
		LODModel.VertexBuffer.GetStride(),
		VET_PackedNormal
		);

	if( LODModel.ColorVertexBuffer.GetNumVertices() > 0 )
	{
		VertexFactoryData.ColorComponent = FVertexStreamComponent(
			&LODModel.ColorVertexBuffer,
			0,	// Struct offset to color
			LODModel.ColorVertexBuffer.GetStride(),
			VET_Color
			);
	}

	if( !LODModel.VertexBuffer.GetUseFullPrecisionUVs() )
	{
		VertexFactoryData.TextureCoordinateComponent = FVertexStreamComponent(
			&LODModel.VertexBuffer,
			STRUCT_OFFSET(TStaticMeshFullVertexFloat16UVs<MAX_TEXCOORDS>,UVs[0]),
			LODModel.VertexBuffer.GetStride(),
			VET_Half2
			);
	}
	else
	{
		VertexFactoryData.TextureCoordinateComponent = FVertexStreamComponent(
			&LODModel.VertexBuffer,
			STRUCT_OFFSET(TStaticMeshFullVertexFloat32UVs<MAX_TEXCOORDS>,UVs[0]),
			LODModel.VertexBuffer.GetStride(),
			VET_Float2
			);
	}

	UINT InstanceBufferOffset = FirstInstance * InstanceBuffer->GetElementStride();
	InstanceBuffer->GetBuffer()->SetByteOffset(InstanceBufferOffset);

	// Per mesh instance data with fixed layout
	// float3 - POSITION
	// float3x3 - ROTATION_SCALE
	VertexFactoryData.InstanceOffsetComponent = FVertexStreamComponent(
		InstanceBuffer->GetBuffer(),
		0,
		InstanceBuffer->GetElementStride(),
		VET_Float3,
		TRUE
		);
	VertexFactoryData.InstanceAxisComponents[0] = FVertexStreamComponent(
		InstanceBuffer->GetBuffer(),
		12,
		InstanceBuffer->GetElementStride(),
		VET_Float3,
		TRUE
		);
	VertexFactoryData.InstanceAxisComponents[1] = FVertexStreamComponent(
		InstanceBuffer->GetBuffer(),
		24,
		InstanceBuffer->GetElementStride(),
		VET_Float3,
		TRUE
		);
	VertexFactoryData.InstanceAxisComponents[2] = FVertexStreamComponent(
		InstanceBuffer->GetBuffer(),
		36,
		InstanceBuffer->GetElementStride(),
		VET_Float3,
		TRUE
		);

	VertexFactoryData.NumVerticesPerInstance = LODModel.NumVertices;
	VertexFactoryData.NumInstances = NumInstances;

	FLocalInstancedVertexFactoryApex *InstancedVertexFactory = static_cast<FLocalInstancedVertexFactoryApex*>(VertexFactory);
	InstancedVertexFactory->SetData(VertexFactoryData);
	InstancedVertexFactory->InitResource();
}

void FLocalInstancedVertexFactoryApex::InitRHI()
{
	FVertexDeclarationElementList Elements;

	Elements.AddItem(AccessStreamComponent(Data.PositionComponent,VEU_Position));

	EVertexElementUsage TangentBasisUsages[2] = { VEU_Tangent, VEU_Normal };
	for(INT AxisIndex = 0;AxisIndex < 2;AxisIndex++)
	{
		if(Data.TangentBasisComponents[AxisIndex].VertexBuffer != NULL)
		{
			Elements.AddItem(AccessStreamComponent(Data.TangentBasisComponents[AxisIndex],TangentBasisUsages[AxisIndex]));
		}
	}

	if(Data.ColorComponent.VertexBuffer)
	{
		Elements.AddItem(AccessStreamComponent(Data.ColorComponent,VEU_Color,1));
	}
	else
	{
		//If the mesh has no color component, set the null color buffer on a new stream with a stride of 0.
		//This wastes 4 bytes of bandwidth per vertex, but prevents having to compile out twice the number of vertex factories.
		FVertexStreamComponent NullColorComponent(&GNullColorVertexBuffer, 0, 0, VET_Color);
		Elements.AddItem(AccessStreamComponent(NullColorComponent,VEU_Color,1));
	}

	if(Data.TextureCoordinateComponent.VertexBuffer)
	{
		Elements.AddItem(AccessStreamComponent(Data.TextureCoordinateComponent,VEU_TextureCoordinate));
	}

	Elements.AddItem(AccessStreamComponent(Data.InstanceOffsetComponent,VEU_TextureCoordinate,1));
	Elements.AddItem(AccessStreamComponent(Data.InstanceAxisComponents[0],VEU_TextureCoordinate,2));
	Elements.AddItem(AccessStreamComponent(Data.InstanceAxisComponents[1],VEU_TextureCoordinate,3));
	Elements.AddItem(AccessStreamComponent(Data.InstanceAxisComponents[2],VEU_TextureCoordinate,4));

	InitDeclaration(Elements,Data);
}
#else // #if WITH_APEX


/** NULL implementation for non-APEX build */
class FPrimitiveSceneProxy *UApexStaticComponent::CreateSceneProxy()
{
	return NULL;
}


#endif // #if WITH_APEX
