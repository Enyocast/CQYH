#include "EnginePrivate.h"
#include "WaterShader.h"

#if WITH_WATER

IMPLEMENT_MATERIAL_SHADER_TYPE(,FWaterPixelShader,TEXT("WaterShader"),TEXT("MainPixelShader"),SF_Pixel,VER_IMPROVED_MOTIONBLUR2,0);
IMPLEMENT_MATERIAL_SHADER_TYPE(,FWaterVertexShader,TEXT("WaterShader"),TEXT("MainVertexShader"),SF_Vertex,0,0);
#if WITH_D3D11_TESSELLATION
IMPLEMENT_MATERIAL_SHADER_TYPE(,FWaterVertexShader_NoTess,TEXT("WaterShader"),TEXT("MainVertexShader_NoTess"),SF_Vertex,0,0);
IMPLEMENT_MATERIAL_SHADER_TYPE(,FWaterHullShader,TEXT("WaterShader"),TEXT("MainHull"),SF_Hull,0,0);
IMPLEMENT_MATERIAL_SHADER_TYPE(,FWaterDomainShader,TEXT("WaterShader"),TEXT("MainDomain"),SF_Domain,0,0);
#endif

//------------------------------------------------------------------------
// FWaterPixelShader
//------------------------------------------------------------------------
UBOOL FWaterPixelShader::ShouldCache( EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType )
{
	return (Material->IsUsedWithWater() || Material->IsSpecialEngineMaterial()) &&
		VertexFactoryType->GetFName() == TEXT("FWaterVertexFactory");
	//return FALSE;
	//Only compile the velocity shaders for the default material or if it's masked,
	//return (Material->IsSpecialEngineMaterial() || Material->IsMasked() 
	//	//or if the material is opaque and two-sided,
	//	|| (Material->IsTwoSided() && !IsTranslucentBlendMode(Material->GetBlendMode()))
	//	// or if the material modifies meshes
	//	|| Material->MaterialModifiesMeshPosition()) 
	//	//and exclude decal materials.
	//	&& !Material->IsDecalMaterial();
}
//------------------------------------------------------------------------
FWaterPixelShader::FWaterPixelShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer )
	: FGlobalShader( Initializer )
{
	MaterialParameters.Bind( Initializer.ParameterMap );
	//GameTime.Bind(Initializer.ParameterMap, TEXT("g_GameTime"), TRUE);
	WaterDeepColor.Bind( Initializer.ParameterMap, TEXT("g_WaterDeepColor"), TRUE);
	WaterScatterColor.Bind( Initializer.ParameterMap, TEXT("g_WaterScatterColor"), TRUE);		
	WaterScatterColorPower.Bind( Initializer.ParameterMap, TEXT("g_WaterScatterColorPower"), TRUE);		
	WaterSpecularColor.Bind( Initializer.ParameterMap, TEXT("g_WaterSpecularColor"), TRUE);
	WaterSpecularIntensity.Bind( Initializer.ParameterMap, TEXT("g_WaterSpecularIntensity"), TRUE);
	WaterSpecularPower.Bind( Initializer.ParameterMap, TEXT("g_WaterSpecularPower"), TRUE);
	
	WaterBumpTexcoordShift.Bind( Initializer.ParameterMap, TEXT("g_WaterBumpTexcoordShift"), TRUE);

	LightPosition.Bind( Initializer.ParameterMap, TEXT("g_LightPosition"), TRUE);	
	CameraPosition.Bind( Initializer.ParameterMap, TEXT("g_CameraPosition"), TRUE);
	CameraDirection.Bind( Initializer.ParameterMap, TEXT("g_CameraDirection"), TRUE );


	ScreenSizeInv.Bind( Initializer.ParameterMap, TEXT("g_ScreenSizeInv"), TRUE);

	ZNear.Bind( Initializer.ParameterMap, TEXT("g_ZNear"), TRUE);

	WaterColorIntensity.Bind( Initializer.ParameterMap, TEXT("g_WaterColorIntensity"), TRUE);
	
	ModelViewMatrix.Bind( Initializer.ParameterMap, TEXT("g_ModelViewMatrix"), TRUE);
	ModelViewProjectionMatrix.Bind( Initializer.ParameterMap, TEXT("g_ModelViewProjectionMatrix"), TRUE);

	LightModelViewMatrix.Bind( Initializer.ParameterMap, TEXT("g_LightModelViewProjectionMatrix"), TRUE);
	

	WaterBumpTexture.Bind(Initializer.ParameterMap, TEXT("g_WaterBumpTexture"), TRUE);
	FoamTexture.Bind(Initializer.ParameterMap, TEXT("g_FoamTexture"), TRUE);
	DepthTexture.Bind(Initializer.ParameterMap, TEXT("g_DepthTexture"), TRUE);

	DepthMapTexture.Bind(Initializer.ParameterMap, TEXT("g_DepthMapTexture"), TRUE);
		

	SceneTextureParameters.Bind(Initializer.ParameterMap);
	//ReflectionCubeTexture.Bind(Initializer.ParameterMap, TEXT("g_ReflectionCubeTexture"), TRUE);
	WaterScatterColorIntensity.Bind(Initializer.ParameterMap, TEXT("g_WaterScatterColorIntensity"), TRUE);
	ReflectionIntensity.Bind(Initializer.ParameterMap, TEXT("g_ReflectionIntensity"), TRUE);
	FogDensity.Bind(Initializer.ParameterMap, TEXT("g_FogDensity"), TRUE );
	AtmosphereBrightColor.Bind(Initializer.ParameterMap, TEXT("g_AtmosphereBrightColor"), TRUE);
	AtmosphereDarkColor.Bind(Initializer.ParameterMap, TEXT("g_AtmosphereDarkColor"), TRUE);
	ReflectionTexture.Bind(Initializer.ParameterMap, TEXT("g_ReflectionTexture"), TRUE);
	RefractionTexture.Bind(Initializer.ParameterMap, TEXT("g_RefractionTexture"), TRUE);
	RefractionDepthTextureResolved.Bind(Initializer.ParameterMap, TEXT("g_RefractionDepthTextureResolved"), TRUE);
	
}
//------------------------------------------------------------------------
FWaterPixelShader::FWaterPixelShader()
{

}
//------------------------------------------------------------------------
void FWaterPixelShader::SetParameters( const FVertexFactory* VertexFactory,const FMaterialRenderProxy* MaterialRenderProxy,const FViewInfo& View )
{
	FMaterialRenderContext MaterialRenderContext(MaterialRenderProxy, *MaterialRenderProxy->GetMaterial(), View.Family->CurrentWorldTime, View.Family->CurrentRealTime, &View);
	MaterialParameters.Set( this, MaterialRenderContext );
}
//------------------------------------------------------------------------
void FWaterPixelShader::SetMesh( const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh,INT BatchElementIndex,const FViewInfo& View,UBOOL bBackFace )
{
	MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View, bBackFace );

	UWaterComponent* water = static_cast<UWaterComponent*>(PrimitiveSceneInfo->Component);
	if(water)
	{		
		//SetShaderValue( GetPixelShader(), GameTime, GWorld->GetTimeSeconds() );
		if( water->GetOwner() )
		{
			FVector clr(((AWaterActor*)water->GetOwner())->WaterDeepColor.R,
				((AWaterActor*)water->GetOwner())->WaterDeepColor.G,
				((AWaterActor*)water->GetOwner())->WaterDeepColor.B);

			SetShaderValue( GetPixelShader(), WaterDeepColor,  clr);

			clr = FVector(((AWaterActor*)water->GetOwner())->WaterScatterColor.R,
				((AWaterActor*)water->GetOwner())->WaterScatterColor.G,
				((AWaterActor*)water->GetOwner())->WaterScatterColor.B);
			SetShaderValue( GetPixelShader(), WaterScatterColor, clr );

			SetShaderValue( GetPixelShader(), WaterScatterColorPower, ((AWaterActor*)water->GetOwner())->WaterScatterColorPower );
		
			clr = FVector(((AWaterActor*)water->GetOwner())->WaterSpecularColor.R,
				((AWaterActor*)water->GetOwner())->WaterSpecularColor.G,
				((AWaterActor*)water->GetOwner())->WaterSpecularColor.B);

			SetShaderValue( GetPixelShader(), WaterSpecularColor, clr );
			SetShaderValue( GetPixelShader(), WaterSpecularIntensity, ((AWaterActor*)water->GetOwner())->WaterSpecularIntensity );
			SetShaderValue( GetPixelShader(), WaterSpecularPower, ((AWaterActor*)water->GetOwner())->WaterSpecularPower);

			FVector2D waterColorIntensity(((AWaterActor*)water->GetOwner())->WaterColorIntensityX, ((AWaterActor*)water->GetOwner())->WaterColorIntensityY);
			SetShaderValue( GetPixelShader(), WaterColorIntensity, waterColorIntensity);

			SetShaderValue( GetPixelShader(), WaterScatterColorIntensity, ((AWaterActor*)water->GetOwner())->WaterScatterColorIntensity);
		}

		FVector2D waterBumpTexcoordShift(GWorld->GetTimeSeconds() * water->WaterBumpTexcoordShiftX,
			GWorld->GetTimeSeconds() * water->WaterBumpTexcoordShiftY);

		SetShaderValue( GetPixelShader(), WaterBumpTexcoordShift, waterBumpTexcoordShift );

		FVector lightPos = water->LightPosition;
		FVector lightDir = -lightPos.SafeNormal();
		FRotator lightRot = lightDir.Rotation();

		FMatrix lightViewMatrix = FTranslationMatrix(-lightPos) * FRotationMatrix(lightRot);
		lightViewMatrix = lightViewMatrix * FMatrix(
			FPlane(0,	0,	1,	0),
			FPlane(1,	0,	0,	0),
			FPlane(0,	1,	0,	0),			
			FPlane(0,	0,	0,	1));

		FMatrix lightProjectionMatrix;

		lightProjectionMatrix = FPerspectiveMatrix(
			45 * (FLOAT)PI / 360.0f,
			1024,
			1024,
			10.0,
			100000.0
			);

		lightViewMatrix = lightViewMatrix * lightProjectionMatrix;

		SetShaderValue( GetPixelShader(), LightPosition, lightPos ); // TODO:
		SetShaderValue( GetPixelShader(), LightModelViewMatrix, lightViewMatrix ); // TODO:		
		

		SetShaderValue( GetPixelShader(), CameraPosition, View.ViewOrigin);

		FVector camDir = View.GetViewDirection().SafeNormal();
		SetShaderValue( GetPixelShader(), CameraDirection, camDir );
		
		//FVector2D screenSizeInv(1.0f / (FLOAT)View.RenderTargetSizeX, 1.0f / (FLOAT)View.RenderTargetSizeY);
		FVector2D screenSizeInv( 
			1.f / (FLOAT)GSceneRenderTargets.GetBufferSizeX(),
			1.f / (FLOAT)GSceneRenderTargets.GetBufferSizeY() );
		SetShaderValue( GetPixelShader(), ScreenSizeInv, screenSizeInv );

		SetShaderValue( GetPixelShader(), ZNear, View.NearClippingDistance);

		SetShaderValue( GetPixelShader(), ModelViewMatrix, /*FTranslationMatrix(View.ViewOrigin) * */View.ViewMatrix);
		SetShaderValue( GetPixelShader(), ModelViewProjectionMatrix, /*FTranslationMatrix(water->GetOrigin()) * */View.ViewProjectionMatrix);

		// set fog parameters
		if( View.Family->ShowFlags & SHOW_Fog )
		{
			SetShaderValue( GetPixelShader(), FogDensity, water->FogDensity );
			SetShaderValue( GetPixelShader(), AtmosphereBrightColor, water->AtmosphereBrightColor );
			SetShaderValue( GetPixelShader(), AtmosphereDarkColor, water->AtmosphereDarkColor );
		}
		else
		{
			SetShaderValue( GetPixelShader(), FogDensity, 0.f );
		}

		SetTextureParameterDirectly( GetPixelShader(), WaterBumpTexture, water->WaterBumpTexture->Resource );
		SetTextureParameterDirectly( GetPixelShader(), FoamTexture, water->FoamTexture->Resource ); // TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap>::GetRHI()
		
		SetTextureParameterDirectly( GetPixelShader(), DepthTexture,
			TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap>::GetRHI(),
			GSceneRenderTargets.GetSceneDepthTexture() );

#if 1
		SetTextureParameterDirectly( GetPixelShader(), DepthMapTexture, water->WaterDepthMap->Resource );
#else  
		SetTextureParameterDirectly( GetPixelShader(), DepthMapTexture,
			TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap>::GetRHI(),
			GSceneRenderTargets.GetSceneDepthTexture() );
#endif

		//SceneTextureParameters.Set((FSceneView*)&View, this);


		//SetTextureParameterDirectly( GetPixelShader(), ReflectionCubeTexture, water->ReflectionCube->Resource);
		AWaterActor* waterActor = static_cast<AWaterActor*>(water->GetOwner());
		if(waterActor && waterActor->SceneCapture)
		{
			USceneCaptureReflectComponent* SceneCaptureReflect = Cast<USceneCaptureReflectComponent>(waterActor->SceneCapture);	

			if(SceneCaptureReflect && SceneCaptureReflect && SceneCaptureReflect->TextureTarget)
			{ 
				SetShaderValue( GetPixelShader(), ReflectionIntensity, ((AWaterActor*)water->GetOwner())->ReflectionIntensity);
				SetTextureParameterDirectly( GetPixelShader(), ReflectionTexture, SceneCaptureReflect->TextureTarget->Resource);
			}
			else
			{
				//SetTextureParameterDirectly( GetPixelShader(), ReflectionTexture, NULL);
			}
		}

		SetTextureParameterDirectly( GetPixelShader(), RefractionTexture,
			TStaticSamplerState<SF_Bilinear,AM_Clamp,AM_Clamp>::GetRHI(),
			GSceneRenderTargets.GetSceneColorTexture() );

		SetTextureParameterDirectly( GetPixelShader(), RefractionDepthTextureResolved,
			TStaticSamplerState<SF_Bilinear,AM_Clamp,AM_Clamp>::GetRHI(),
			GSceneRenderTargets.GetSceneDepthTexture() );

		

	}
}
//------------------------------------------------------------------------
UBOOL FWaterPixelShader::Serialize( FArchive& Ar )
{
	UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize( Ar );
	Ar << MaterialParameters;
	//Ar << GameTime;
	Ar << WaterDeepColor;
	Ar << WaterScatterColor;
	Ar << WaterScatterColorPower;

	Ar << WaterSpecularColor;
	Ar << WaterSpecularIntensity;
	Ar << WaterSpecularPower;


	Ar << LightPosition;
	Ar << CameraPosition;
	Ar << CameraDirection;

	Ar << ScreenSizeInv;
	Ar << ZNear;

	Ar << WaterColorIntensity;
	Ar << WaterScatterColorIntensity;
	Ar << ReflectionIntensity;

	// fog
	Ar << FogDensity;
	Ar << AtmosphereBrightColor;
	Ar << AtmosphereDarkColor;

	Ar << ModelViewMatrix;
	Ar << ModelViewProjectionMatrix;

	Ar << LightModelViewMatrix;

	Ar << WaterBumpTexcoordShift;

	Ar << WaterBumpTexture;
	Ar << FoamTexture;
	Ar << DepthTexture;

	Ar << DepthMapTexture;

	Ar << SceneTextureParameters;

	//Ar << ReflectionCubeTexture;
	Ar << ReflectionTexture;
	Ar << RefractionTexture;
	Ar << RefractionDepthTextureResolved;

	return bShaderHasOutdatedParameters;
}





//------------------------------------------------------------------------
// FWaterVertexShader
//------------------------------------------------------------------------
FWaterVertexShader::FWaterVertexShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer )
	: FGlobalShader( Initializer )
{
	MaterialParameters.Bind( Initializer.ParameterMap );

	LocalToWorld.Bind( Initializer.ParameterMap, TEXT("LocalToWorld") );
}
//------------------------------------------------------------------------
FWaterVertexShader::FWaterVertexShader()
{

}
//------------------------------------------------------------------------
UBOOL FWaterVertexShader::ShouldCache( EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType )
{
	return (Material->IsUsedWithWater() || Material->IsSpecialEngineMaterial()) &&
		VertexFactoryType->GetFName() == TEXT("FWaterVertexFactory");

//	//Only compile the velocity shaders for the default material or if it's masked,
//	return (Material->IsSpecialEngineMaterial() || Material->IsMasked() 
//		//or if the material is opaque and two-sided,
//		|| (Material->IsTwoSided() && !IsTranslucentBlendMode(Material->GetBlendMode()))
//		// or if the material modifies meshes
//		|| Material->MaterialModifiesMeshPosition()) 
//		//and exclude decal materials.
//		&& !Material->IsDecalMaterial();
}
//------------------------------------------------------------------------
 void FWaterVertexShader::SetParameters( const FVertexFactory* VertexFactory, const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View )
 {
 	FMaterialRenderContext MaterialRenderContext( MaterialRenderProxy, 
 		*MaterialRenderProxy->GetMaterial(),
 		View.Family->CurrentWorldTime,
 		View.Family->CurrentRealTime, &View );
 	MaterialParameters.Set( this, MaterialRenderContext );
 	//VertexFactoryParameters.Set( this, VertexFactory, View );
 }
//------------------------------------------------------------------------
void FWaterVertexShader::SetMesh( const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex, const FViewInfo& View )
{
	//VertexFactoryParameters.SetMesh(this,Mesh,BatchElementIndex,View);
	MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View ); 

	UWaterComponent* water = static_cast<UWaterComponent*>(PrimitiveSceneInfo->Component);
	if( water )
	{
		SetShaderValue( GetVertexShader(), LocalToWorld, FTranslationMatrix( water->GetOrigin() ) );	// no rotation
	}
}

//------------------------------------------------------------------------
UBOOL FWaterVertexShader::Serialize( FArchive& Ar )
{
	UBOOL bShaderHasOutdatedParameters = FGlobalShader::Serialize( Ar );
	//bShaderHasOutdatedParameters |= Ar << VertexFactoryParameters;
	Ar << MaterialParameters;
	Ar << LocalToWorld;
	return bShaderHasOutdatedParameters;
}

#if WITH_D3D11_TESSELLATION
//------------------------------------------------------------------------
// FWaterVertexShader_NoTess
//------------------------------------------------------------------------
FWaterVertexShader_NoTess::FWaterVertexShader_NoTess( const ShaderMetaType::CompiledShaderInitializerType& Initializer )
	: FWaterVertexShader( Initializer )
{
	if( GRHIShaderPlatform == SP_PCD3D_SM5 )
	{
		WaterBumpTexcoordShift.Bind( Initializer.ParameterMap, TEXT("g_WaterBumpTexcoordShift") );
		WaterMicroBumpTexcoordScale.Bind( Initializer.ParameterMap, TEXT("g_WaterMicroBumpTexcoordScale"));
		WaterBumpTexcoordScale.Bind( Initializer.ParameterMap, TEXT("g_WaterBumpTexcoordScale"));
		WaterHeightBumpScale.Bind( Initializer.ParameterMap, TEXT("g_WaterHeightBumpScale"));
		HeightFieldSize.Bind( Initializer.ParameterMap, TEXT("g_HeightFieldSize"));
		ModelViewProjectionMatrix.Bind( Initializer.ParameterMap, TEXT("g_ModelViewProjectionMatrix"));

		SamplerLinearWrap.Bind( Initializer.ParameterMap, TEXT("SamplerLinearWrap"), TRUE);
		WaterBumpTexture.Bind(Initializer.ParameterMap, TEXT("g_WaterBumpTexture"));
	}
}
//------------------------------------------------------------------------
UBOOL FWaterVertexShader_NoTess::ShouldCache( EShaderPlatform Platform,const FMaterial* Material,const FVertexFactoryType* VertexFactoryType )
{	// todo: check material usage!
	return (Material->IsUsedWithWater() || Material->IsSpecialEngineMaterial()) &&
		VertexFactoryType->GetFName() == TEXT("FWaterVertexFactory");
}
//------------------------------------------------------------------------
void FWaterVertexShader_NoTess::SetMesh( const FPrimitiveSceneInfo* PrimitiveSceneInfo, const FMeshBatch& Mesh, INT BatchElementIndex, const FViewInfo& View )
{
	FWaterVertexShader::SetMesh( PrimitiveSceneInfo, Mesh, BatchElementIndex, View );

	if( GRHIShaderPlatform == SP_PCD3D_SM5 )
	{
		UWaterComponent* water = static_cast<UWaterComponent*>(PrimitiveSceneInfo->Component);
		WaterComponentSceneProxy* proxy = static_cast<WaterComponentSceneProxy*>(PrimitiveSceneInfo->Proxy);
		if(water)
		{
			FVector2D waterBumpTexcoordShift(GWorld->GetTimeSeconds() * proxy->WaterBumpTexcoordShiftX,
				GWorld->GetTimeSeconds() * proxy->WaterBumpTexcoordShiftY);
			SetShaderValue( GetVertexShader(), WaterBumpTexcoordShift, waterBumpTexcoordShift );

			FVector2D waterMicroBumpTexcoordScale(proxy->WaterMicroBumpTexcoordScaleX, proxy->WaterMicroBumpTexcoordScaleY);
			SetShaderValue( GetVertexShader(), WaterMicroBumpTexcoordScale, waterMicroBumpTexcoordScale);
		
			FVector2D waterBumpTexcoordScale(proxy->WaterBumpTexcoordScaleX, proxy->WaterBumpTexcoordScaleY);
			SetShaderValue( GetVertexShader(), WaterBumpTexcoordScale, waterBumpTexcoordScale);
			SetShaderValue( GetVertexShader(), WaterHeightBumpScale, proxy->WaterHeightBumpScale);
			SetShaderValue( GetVertexShader(), HeightFieldSize, proxy->HeightFieldSize * WaterSizeScale);
			SetShaderValue( GetVertexShader(), ModelViewProjectionMatrix, View.ViewProjectionMatrix );
		
			if(proxy->WaterBumpTexture)
			{
				SetTextureParameterDirectly( GetVertexShader(), WaterBumpTexture, proxy->WaterBumpTexture->Resource );
			}
		}
	}
}

//------------------------------------------------------------------------
UBOOL FWaterVertexShader_NoTess::Serialize( FArchive& Ar )
{
	UBOOL bShaderHasOutdatedParameters = FWaterVertexShader::Serialize( Ar );

	if( GRHIShaderPlatform == SP_PCD3D_SM5 )
	{
		Ar << WaterBumpTexcoordShift;
		Ar << WaterMicroBumpTexcoordScale;
		Ar << WaterBumpTexcoordScale;
		Ar << WaterHeightBumpScale;
		Ar << HeightFieldSize;
		Ar << ModelViewProjectionMatrix;

		Ar << SamplerLinearWrap;
		Ar << WaterBumpTexture;
	}

	return bShaderHasOutdatedParameters;
}

//------------------------------------------------------------------------
// FWaterHullShader
//------------------------------------------------------------------------
FWaterHullShader::FWaterHullShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer )
	: FBaseHullShader( Initializer )
{
	//GameTime.Bind(Initializer.ParameterMap, TEXT("g_GameTime"), TRUE);

	FrustumCullInHS.Bind( Initializer.ParameterMap, TEXT("g_FrustumCullInHS") );

	UseDynamicLOD.Bind( Initializer.ParameterMap, TEXT("g_UseDynamicLOD"));
	DynamicTessFactor.Bind( Initializer.ParameterMap, TEXT("g_DynamicTessFactor"));
	StaticTessFactor.Bind( Initializer.ParameterMap, TEXT("g_StaticTessFactor"));


	CameraDirection.Bind( Initializer.ParameterMap, TEXT("g_CameraDirection") );
	CameraPosition.Bind( Initializer.ParameterMap, TEXT("g_CameraPosition"));

	ModelViewProjectionMatrix.Bind( Initializer.ParameterMap, TEXT("g_ModelViewProjectionMatrix"));

	//LocalToWorld.Bind( Initializer.ParameterMap, TEXT("LocalToWorld") );
}
//------------------------------------------------------------------------
FWaterHullShader::FWaterHullShader()
{

}
//------------------------------------------------------------------------
void FWaterHullShader::SetParameters( const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View )
{
	//FBaseHullShader::SetParameters( MaterialRenderProxy, View );
}
//------------------------------------------------------------------------
void FWaterHullShader::SetMesh( const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh,INT BatchElementIndex,const FViewInfo& View)
{
	//FBaseHullShader::SetMesh(PrimitiveSceneInfo, Mesh, BatchElementIndex, View);
	//MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View);

	UWaterComponent* water = static_cast<UWaterComponent*>(PrimitiveSceneInfo->Component);
	if(water)
	{
		//SetShaderValue( GetHullShader(), GameTime, GWorld->GetTimeSeconds() );
		
		SetShaderValue( GetHullShader(), FrustumCullInHS, water->FrustumCullInHS );

		FLOAT val = water->UseDynamicLOD;
		SetShaderValue( GetHullShader(), UseDynamicLOD, val);

		val = water->DynamicTessFactor;
		SetShaderValue( GetHullShader(), DynamicTessFactor, val);

		val = water->StaticTessFactor;
		SetShaderValue( GetHullShader(), StaticTessFactor, val);


		FVector camDir = View.GetViewDirection().SafeNormal();
		SetShaderValue( GetHullShader(), CameraDirection, camDir );
		SetShaderValue( GetHullShader(), CameraPosition, View.ViewOrigin);

		SetShaderValue( GetHullShader(), ModelViewProjectionMatrix, /*FTranslationMatrix(water->GetOrigin()) * */View.ViewProjectionMatrix);
		//SetShaderValue( GetHullShader(), LocalToWorld, FTranslationMatrix( water->GetOrigin() ) );	// no rotation
	}
}
//------------------------------------------------------------------------
UBOOL FWaterHullShader::Serialize( FArchive& Ar )
{
	UBOOL bShaderHasOutdatedParameters = FBaseHullShader::Serialize( Ar );

	//Ar << GameTime;

	Ar << FrustumCullInHS;

	Ar << UseDynamicLOD;
	Ar << DynamicTessFactor;
	Ar << StaticTessFactor;

	Ar << CameraDirection;
	Ar << CameraPosition;
	Ar << ModelViewProjectionMatrix;

	//Ar << LocalToWorld;

	return bShaderHasOutdatedParameters;
}
//------------------------------------------------------------------------
UBOOL FWaterHullShader::ShouldCache( EShaderPlatform Platform, const FMaterial* Material, const FVertexFactoryType* VertexFactoryType )
{
	return FBaseHullShader::ShouldCache( Platform, Material, VertexFactoryType )
		&& (Material->IsUsedWithWater() || Material->IsSpecialEngineMaterial())
		&& FWaterVertexShader::ShouldCache( Platform, Material, VertexFactoryType );
}





//------------------------------------------------------------------------
// FWaterDomainShader
//------------------------------------------------------------------------
FWaterDomainShader::FWaterDomainShader( const ShaderMetaType::CompiledShaderInitializerType& Initializer )
	: FBaseDomainShader( Initializer )
{
	//GameTime.Bind(Initializer.ParameterMap, TEXT("g_GameTime"), TRUE);
	WaterBumpTexcoordShift.Bind( Initializer.ParameterMap, TEXT("g_WaterBumpTexcoordShift") );

	CameraPosition.Bind( Initializer.ParameterMap, TEXT("g_CameraPosition"), TRUE);
	ModelViewProjectionMatrix.Bind( Initializer.ParameterMap, TEXT("g_ModelViewProjectionMatrix"));

	//UseDynamicLOD.Bind( Initializer.ParameterMap, TEXT("g_UseDynamicLOD"));
	//DynamicTessFactor.Bind( Initializer.ParameterMap, TEXT("g_DynamicTessFactor"));
	//StaticTessFactor.Bind( Initializer.ParameterMap, TEXT("g_StaticTessFactor"));

	WaterMicroBumpTexcoordScale.Bind( Initializer.ParameterMap, TEXT("g_WaterMicroBumpTexcoordScale"));
	WaterBumpTexcoordScale.Bind( Initializer.ParameterMap, TEXT("g_WaterBumpTexcoordScale"));
	WaterHeightBumpScale.Bind( Initializer.ParameterMap, TEXT("g_WaterHeightBumpScale"));

	HeightFieldSize.Bind( Initializer.ParameterMap, TEXT("g_HeightFieldSize"));

	//WaterSizeScale.Bind( Initializer.ParameterMap, TEXT("g_WaterSizeScale"), TRUE);
	SamplerLinearWrap.Bind( Initializer.ParameterMap, TEXT("SamplerLinearWrap"), TRUE);

	

	WaterBumpTexture.Bind(Initializer.ParameterMap, TEXT("g_WaterBumpTexture"));
	DepthMapTexture.Bind(Initializer.ParameterMap, TEXT("g_DepthMapTexture"), TRUE);

	//LocalToWorld.Bind( Initializer.ParameterMap, TEXT("LocalToWorld") );
}
//------------------------------------------------------------------------
FWaterDomainShader::FWaterDomainShader()
{

}
//------------------------------------------------------------------------
void FWaterDomainShader::SetParameters( const FMaterialRenderProxy* MaterialRenderProxy, const FViewInfo& View )
{
	//FBaseDomainShader::SetParameters( MaterialRenderProxy, View );
}
//------------------------------------------------------------------------
void FWaterDomainShader::SetMesh( const FPrimitiveSceneInfo* PrimitiveSceneInfo,const FMeshBatch& Mesh,INT BatchElementIndex,const FViewInfo& View )
{
	//FBaseDomainShader::SetMesh(PrimitiveSceneInfo, Mesh, BatchElementIndex, View);
	//MaterialParameters.SetMesh( this, PrimitiveSceneInfo, Mesh, BatchElementIndex, View );

	UWaterComponent* water = static_cast<UWaterComponent*>(PrimitiveSceneInfo->Component);
	WaterComponentSceneProxy* proxy = static_cast<WaterComponentSceneProxy*>(PrimitiveSceneInfo->Proxy);
	if(water)
	{
		//SetShaderValue( GetDomainShader(), GameTime, GWorld->GetTimeSeconds() );

		FVector2D waterBumpTexcoordShift(GWorld->GetTimeSeconds() * proxy->WaterBumpTexcoordShiftX,
			GWorld->GetTimeSeconds() * proxy->WaterBumpTexcoordShiftY);

		SetShaderValue( GetDomainShader(), WaterBumpTexcoordShift, waterBumpTexcoordShift );
		
		//debugf(TEXT("waterBumpTexcoordShift %.2f, %.2f"), waterBumpTexcoordShift.X, waterBumpTexcoordShift.Y);

		SetShaderValue( GetDomainShader(), CameraPosition, View.ViewOrigin/* - proxy->Origin*/);
		SetShaderValue( GetDomainShader(), ModelViewProjectionMatrix, View.ViewProjectionMatrix );

		//FLOAT val = proxy->UseDynamicLOD;
		//SetShaderValue( GetDomainShader(), UseDynamicLOD, val);

		//val = proxy->DynamicTessFactor;
		//SetShaderValue( GetDomainShader(), DynamicTessFactor, val);

		//val = proxy->StaticTessFactor;
		//SetShaderValue( GetDomainShader(), StaticTessFactor, val);

		FVector2D waterMicroBumpTexcoordScale(proxy->WaterMicroBumpTexcoordScaleX, proxy->WaterMicroBumpTexcoordScaleY);
		SetShaderValue( GetDomainShader(), WaterMicroBumpTexcoordScale, waterMicroBumpTexcoordScale);
		
		FVector2D waterBumpTexcoordScale(proxy->WaterBumpTexcoordScaleX, proxy->WaterBumpTexcoordScaleY);
		SetShaderValue( GetDomainShader(), WaterBumpTexcoordScale, waterBumpTexcoordScale);
		
		FVector& s = proxy->DrawScale3D;

		SetShaderValue( GetDomainShader(), WaterHeightBumpScale, proxy->WaterHeightBumpScale);

		SetShaderValue( GetDomainShader(), HeightFieldSize, proxy->HeightFieldSize * WaterSizeScale);

		//FVector2D sizeScale(s.X, s.Y);
		//SetShaderValue( GetDomainShader(), WaterSizeScale, sizeScale);

		if(proxy->WaterBumpTexture)
		{
			SetTextureParameterDirectly( GetDomainShader(), WaterBumpTexture, proxy->WaterBumpTexture->Resource );
			
			//SetTextureParameterDirectly( GetDomainShader(), WaterBumpTexture,
			//	TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap>::GetRHI(),
			//	 water->WaterBumpTexture->Resource );
		}
  	
#if 1
		if(proxy->WaterDepthMap)
		{
			SetTextureParameterDirectly( GetDomainShader(), DepthMapTexture, proxy->WaterDepthMap->Resource );
		}
#else  
		SetTextureParameterDirectly( GetDomainShader(), DepthMapTexture,
  				TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap>::GetRHI(),
				GSceneRenderTargets.GetSceneDepthTexture() );
#endif

		//RHISetSamplerState(
		//	GetDomainShader(), 
		//	WaterBumpTexture.GetBaseIndex(), 
		//	SamplerLinearWrap.GetSamplerIndex(), 
		//	TStaticSamplerState<SF_Bilinear,AM_Wrap,AM_Wrap,AM_Wrap>::GetRHI(),
		//	water->WaterBumpTexture->Resource, 0.0f, -1.0f, -1.0f, FALSE);

		//SetShaderValue( GetDomainShader(), LocalToWorld, FTranslationMatrix( water->GetOrigin() ) );	// no rotation

	}
}
//------------------------------------------------------------------------
UBOOL FWaterDomainShader::Serialize( FArchive& Ar )
{
	UBOOL bShaderHasOutdatedParameters = FBaseDomainShader::Serialize( Ar );
	
	//Ar << GameTime;

	Ar << WaterBumpTexcoordShift;

	Ar << CameraPosition;
	Ar << ModelViewProjectionMatrix;

	//Ar << UseDynamicLOD;
	//Ar << DynamicTessFactor;
	//Ar << StaticTessFactor;

	Ar << WaterMicroBumpTexcoordScale;
	Ar << WaterBumpTexcoordScale;
	Ar << WaterHeightBumpScale;

	Ar << HeightFieldSize;

	//Ar << WaterSizeScale;

	Ar << SamplerLinearWrap;
	Ar << WaterBumpTexture;
	//Ar << WaterBumpSampler;

// 	Ar << FoamTexture;
	Ar << DepthMapTexture;

	//Ar << LocalToWorld;

	return bShaderHasOutdatedParameters;
}
//------------------------------------------------------------------------
UBOOL FWaterDomainShader::ShouldCache( EShaderPlatform Platform, const FMaterial* Material, const FVertexFactoryType* VertexFactoryType )
{
	return FBaseDomainShader::ShouldCache( Platform, Material, VertexFactoryType )
		&& (Material->IsUsedWithWater() || Material->IsSpecialEngineMaterial())
		&& FWaterVertexShader::ShouldCache( Platform, Material, VertexFactoryType );
}
//------------------------------------------------------------------------
#endif

#endif // WITH_WATER