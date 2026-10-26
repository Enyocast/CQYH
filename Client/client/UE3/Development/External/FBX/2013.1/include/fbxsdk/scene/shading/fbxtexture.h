/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxtexture.h
#ifndef _FBXSDK_SCENE_SHADING_TEXTURE_H_
#define _FBXSDK_SCENE_SHADING_TEXTURE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/fbxobject.h>
#include <fbxsdk/core/base/fbxerror.h>
#include <fbxsdk/core/math/fbxvector2.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

// Forward declaration
class FbxVector4;
class FbxLayerContainer;

/** This class is the base class for textures, ie classes FbxFileTexture, FbxLayeredTexture and FbxProceduralTexture. 
  * It describes image mapping on top of a geometry.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxTexture : public FbxObject
{
	FBXSDK_OBJECT_DECLARE(FbxTexture,FbxObject);

	public:
	/**
	  * \name Texture Properties
	  */
	//@{

	  /** \enum EUnifiedMappingType      Internal enum for texture mapping types.
	    * Includes mapping types and planar mapping normal orientations.
		* Use SetMappingType(), GetMappingType(), SetPlanarMappingNormal() 
		* and GetPlanarMappingNormal() to access these values.
	    */
		typedef enum
		{ 
			//! Maps to EMappingType::eUV.
			eUMT_UV, 
			//! Maps to EMappingType::ePLANAR and EPlanarMappingNormal::ePLANAR_NORMAL_Z.
			eUMT_XY, 
			//! Maps to EMappingType::ePLANAR and EPlanarMappingNormal::ePLANAR_NORMAL_X.
			eUMT_YZ, 
			//! Maps to EMappingType::ePLANAR and EPlanarMappingNormal::ePLANAR_NORMAL_Y.
			eUMT_XZ, 
			//! Maps to EMappingType::eSPHERICAL.
			eUMT_SPHERICAL,
			//! Maps to EMappingType::eCYLINDRICAL.
			eUMT_CYLINDRICAL,
			//! Maps to EMappingType::eENVIRONMENT.
			eUMT_ENVIRONMENT,
			//! Unused.
			eUMT_PROJECTION,
			//! Maps to EMappingType::eBOX. Deprecated.
			eUMT_BOX, // deprecated
			//! Maps to EMappingType::eFACE. Deprecated.
			eUMT_FACE, // deprecated
			//! Maps to EMappingType::eNULL.
			eUMT_NO_MAPPING,
		} EUnifiedMappingType;


	  /** \enum ETextureUse6         Internal enum for texture usage.
		* For example, the texture might be used as a standard texture, as a shadow map, as a bump map, etc.
	    * Use SetTextureUse() and GetTextureUse() to access these values.	
	    */
		typedef enum 
		{
			//! Maps to ETextureUse::eSTANDARD.
			eTEXTURE_USE_6_STANDARD,
			//! Maps to ETextureUse::eSPHERICAL_REFLEXION_MAP.
			eTEXTURE_USE_6_SPHERICAL_REFLEXION_MAP,
			//! Maps to ETextureUse::eSPHERE_REFLEXION_MAP.
			eTEXTURE_USE_6_SPHERE_REFLEXION_MAP,
			//! Maps to ETextureUse::eSHADOW_MAP.
			eTEXTURE_USE_6_SHADOW_MAP,
			//! Maps to ETextureUse::eLIGHT_MAP.
			eTEXTURE_USE_6_LIGHT_MAP,
			//! Maps to ETextureUse::eBUMP_NORMAL_MAP.
			eTEXTURE_USE_6_BUMP_NORMAL_MAP
		} ETextureUse6;

		/** \enum EWrapMode Wrap modes.
		  * Use SetWrapMode(), GetWrapModeU() and GetWrapModeV() to access these values.
		  */
		typedef enum 
		{
			//! Apply the texture over and over on the model's surface until the model is covered. This is the default setting.
			eREPEAT,
			//! Apply the texture to a model only once, using the color at the ends of the texture as the "filter".
			eCLAMP
		} EWrapMode;

		/** \enum BlendMode Blend modes.
		  */
		typedef enum 
		{
			//! The texture is transparent, depending on the Alpha settings.
			eTRANSLUCENT,
			//! The color of the texture is added to the previous texture.
			eADDITIVE,
			//! The color value of the texture is multiplied by the color values of all previous layers of texture.
			eMODULATE,
			//! The color value of the texture is multiplied by two and then multiplied by the color values of all previous layers of texture.
			eMODULATE2,
			//! The texture is opaque.
			eOVER
        } BlendMode;

        /** \enum EAlignMode Align indices for cropping.
          */
        typedef enum  
        {
			//! Left cropping.
            eLEFT = 0,
			//! Right cropping.
            eRIGHT,
			//! Top cropping.
            eTOP,
			//! Bottom cropping.
            eBOTTOM
        } EAlignMode;

        /** \enum ECoordinates Texture coordinates.
          */
        typedef enum 
        {
			//! U axis.
            eU = 0,
			//! V axis.
            eV,
			//! W axis.
            eW
        } ECoordinates;

		// Type description

        /** This property handles the use of textures.
          * Default value is eTEXTURE_USE_6_STANDARD.
          */
		FbxPropertyT<ETextureUse6>			TextureTypeUse;

        /** This property handles the default alpha value for textures.
          * Default value is 1.0
          */
		FbxPropertyT<FbxDouble>			Alpha;


		// Mapping information

        /** This property handles the texture mapping types.
          * Default value is eUMT_UV.
          */
		FbxPropertyT<EUnifiedMappingType>	CurrentMappingType;

        /** This property handles the texture wrap modes in U.
          * Default value is eREPEAT.
          */
		FbxPropertyT<EWrapMode>			WrapModeU;

        /** This property handles the texture wrap modes in V.
          * Default value is eREPEAT.
          */
		FbxPropertyT<EWrapMode>			WrapModeV;

        /** This property handles the swap UV flag.
          * If swap UV flag is enabled, the texture's width and height are swapped.
          * Default value is false.
          */
		FbxPropertyT<FbxBool>				UVSwap;

        /** This property handles the PremultiplyAlpha flag.
          * If PremultiplyAlpha flag is true, the R, G, and B components you store have already been multiplied in with the alpha.
          * Default value is true.
          */
		FbxPropertyT<FbxBool>				PremultiplyAlpha;

		// Texture positioning

        /** This property handles the default translation vector.
          * Default value is FbxDouble3(0.0,0.0,0.0).
          */
		FbxPropertyT<FbxDouble3>			Translation;

        /** This property handles the default rotation vector.
          * Default value is FbxDouble3(0.0,0.0,0.0).
          */
		FbxPropertyT<FbxDouble3>			Rotation;

        /** This property handles the default scale vector.
          * Default value is FbxDouble3(1.0,1.0,1.0).
          */
		FbxPropertyT<FbxDouble3>			Scaling;

        /** This property handles the rotation pivot vector.
          * Default value is FbxDouble3(0.0,0.0,0.0).
          */
		FbxPropertyT<FbxDouble3>			RotationPivot;

        /** This property handles the scaling pivot vector.
          * Default value is FbxDouble3(0.0,0.0,0.0).
          */
		FbxPropertyT<FbxDouble3>			ScalingPivot;

		// Blend mode
        /** This property handles the texture blend mode.
          * Default value is eADDITIVE.
          */
		FbxPropertyT<BlendMode>	CurrentTextureBlendMode;

		// UV set to use.
        /** This property handles the use of UV sets.
          * Default value is default.
          */
		FbxPropertyT<FbxString>			UVSet;

        /** This property only used by Vector Displacement Texture so it is not added to FbxTexture.
          * It is a dynamic enum property which has values : "World", "Object" and "Tangent"
          * Default value is "Object".
          */
        static const char* sVectorSpace        ;
        static const char* sVectorSpaceWorld   ;
        static const char* sVectorSpaceObject  ;
        static const char* sVectorSpaceTangent ;

        /** This property only used by Vector Displacement Texture so it is not added to FbxTexture.
          * It is a dynamic enum property which has values : "Floating-point Absolute" and "Signed Encoding"
          * Default value is "Floating-point Absolute".
          */
        static const char* sVectorEncoding     ;
        static const char* sVectorEncodingFP   ;
        static const char* sVectorEncodingSE   ;


	/** Resets the default texture values.
	  */
	virtual void Reset();

    /** Sets the swap UV flag.
	  * \param pSwapUV      Set to \c true if the swap UV flag is enabled.
	  * \remarks            If the swap UV flag is enabled, the texture's width and height are swapped.
	  */
    void SetSwapUV(bool pSwapUV);

    /** Returns the swap UV flag.
	  * \return             \c True if the swap UV flag is enabled.
	  * \remarks            If the swap UV flag is enabled, the texture's width and height are swapped.
	  */
    bool GetSwapUV() const;

    /** Sets the PremultiplyAlpha flag.
	  * \param pPremultiplyAlpha       Set to \c true if the method of storing alpha is PremultiplyAlpha.
	  * \remarks                        If PremultiplyAlpha flag is true, the R, G, and B components you store have already been multiplied in with the alpha.
	  */
    void SetPremultiplyAlpha(bool pPremultiplyAlpha);

    /** Returns the PremultiplyAlpha flag.
	  * \return             \c True if the method of storing alpha is PremultiplyAlpha.
	  * \remarks            If PremultiplyAlpha flag is true, the R, G, and B components you store have already been multiplied in with the alpha.
	  */
    bool GetPremultiplyAlpha() const;

	/** \enum EAlphaSource Controls if the Alpha computation of the current texture comes from the Alpha channel, RGB Intensity channel, or if there is No Alpha.
	  */
    typedef enum    
    { 
		//! No Alpha.
        eNONE, 
		//! RGB Intensity (computed).
        eRGB_INTENSITY, 
		//! Alpha channel. Black is 100% transparency, white is opaque.
        eBLACK 
    } EAlphaSource;

    /** Sets the alpha source.
	  * \param pAlphaSource The alpha source identifier.
	  */
    void SetAlphaSource(EAlphaSource pAlphaSource);

    /** Returns the alpha source.
      * \return             The alpha source identifier for this texture.
	  */
	EAlphaSource GetAlphaSource() const;

    /** Sets cropping.
	  * \param pLeft        Left cropping value.
	  * \param pTop         Top cropping value.
	  * \param pRight       Right cropping value.
	  * \param pBottom      Bottom cropping value.
	  * \remarks            The defined rectangle is not checked for invalid values.
	  *                     The caller must verify that the rectangle
	  *                     is meaningful for this texture.
	  */
    void SetCropping(int pLeft, int pTop, int pRight, int pBottom);

    /** Returns left cropping.
	  * \return             The left side of the cropping rectangle.
	  */
    int GetCroppingLeft() const;

    /** Returns top cropping.
	  * \return             The top side of the cropping rectangle.
	  */
    int GetCroppingTop() const;

    /** Returns right cropping.
	  * \return             The right side of the cropping rectangle.
	  */
    int GetCroppingRight() const;

    /** Returns bottom cropping.
	  * \return             The bottom side of the cropping rectangle.
	  */
    int GetCroppingBottom() const;
	
	/** \enum EMappingType Texture mapping types.
	  */
    typedef enum    
    { 
		//! No texture mapping defined.
        eNULL, 
		//! Apply texture to the model viewed as a plane.
        ePLANAR, 
		//! Wrap texture around the model as if it was a sphere.
        eSPHERICAL, 
		//! Wrap texture around the model as if it was a cylinder.
        eCYLINDRICAL, 
		//! Wrap texture around the model as if it was a box.
        eBOX, 
		//! Apply texture to the model viewed as a face.
        eFACE,
		//! Apply texture to the model according to UVs.
        eUV,
		//! Texture is an environment map.
		eENVIRONMENT
    } EMappingType;

    /** Sets the mapping type.
	  * \param pMappingType The mapping type identifier.
	  */
    void SetMappingType(EMappingType pMappingType);

    /** Returns the mapping type.
	  * \return             The mapping type identifier.
	  */
    EMappingType GetMappingType() const;

	/** \enum EPlanarMappingNormal Planar mapping normal orientations.
	  */
    typedef enum   
    { 
		//! Normals are in the direction of the X axis, mapping plan is in the YZ axis.
        ePLANAR_NORMAL_X, 
		//! Normals are in the direction of the Y axis, mapping plan is in the XZ axis.
        ePLANAR_NORMAL_Y, 
		//! Normals are in the direction of the Z axis, mapping plan is in the XY axis.
        ePLANAR_NORMAL_Z 
    } EPlanarMappingNormal;

    /** Sets the normal orientations for planar mapping.
	  * \param pPlanarMappingNormal The identifier for planar mapping normal orientation.
	  */
    void SetPlanarMappingNormal(EPlanarMappingNormal pPlanarMappingNormal);

    /** Returns the normal orientations for planar mapping.
	  * \return                     The identifier for planar mapping normal orientation.
	  */
    EPlanarMappingNormal GetPlanarMappingNormal() const;

	/** \enum ETextureUse           Texture uses.
	  */
	typedef enum 
	{
		//! Standard texture use (ex. image)
		eSTANDARD,
		//! Shadow map
		eSHADOW_MAP,
		//! Light map
		eLIGHT_MAP,
		//! Spherical reflection map: Object reflects the contents of the scene
		eSPHERICAL_REFLEXION_MAP,
		//! Sphere reflection map: Object reflects the contents of the scene from only one point of view
		eSPHERE_REFLEXION_MAP,
		//! Bump map: Texture contains two direction vectors, that are used to convey relief in a texture.
		eBUMP_NORMAL_MAP
	} ETextureUse;

	/** Sets the texture use.
	  * \param pTextureUse          The texture use identifier.
	  */
    void SetTextureUse(ETextureUse pTextureUse);

    /** Returns the texture use.
	  * \return                     The texture use identifier.
	  */
    ETextureUse GetTextureUse() const;


	/** Sets the U and V wrap mode.
	  * \param pWrapU               Wrap mode identifier.
	  * \param pWrapV               Wrap mode identifier.
	  */
    void SetWrapMode(EWrapMode pWrapU, EWrapMode pWrapV);

    /** Returns the U wrap mode.
	  * \return                     U wrap mode identifier.
	  */
    EWrapMode GetWrapModeU() const;

	/** Returns the V wrap mode.
	  * \return                     V wrap mode identifier.
	  */
	EWrapMode GetWrapModeV() const;


	/** Sets the blend mode.
	  * \param pBlendMode           Blend mode identifier.
	  */
	void SetBlendMode(BlendMode pBlendMode);

	/** Returns the blend mode.
	  * \return                     Blend mode identifier.
	  */
	BlendMode GetBlendMode() const;

	//@}

	/**
	  * \name Default Values Management By Vectors
	  * This set of functions provides direct access to the default values in vector base. 
	  */
	//@{

	/** Sets the default translation vector. 
	  * \param pT           The first element is the U translation applied to 
	  *                     the texture. A displacement of one unit is equal to the texture
	  *                     width after the U scaling is applied. The second element is the
	  *                     V translation applied to the texture. A displacement of one unit is 
	  *                     equal to the texture height after the V scaling is applied.
	  *                     The third and fourth elements have no effect on texture 
	  *                     translation.
	  */
	inline void SetDefaultT(const FbxVector4& pT) { Translation.Set( pT ); }

	/** Returns the default translation vector. 
	  * \param pT           The first element is the U translation applied to 
	  *                     the texture. A displacement of one unit is equal to the texture
	  *                     width after the U scaling is applied. The second element is the
	  *                     V translation applied to the texture. A displacement of one unit is 
	  *                     equal to the texture height after the V scaling is applied.
	  *                     The third and fourth elements have no effect on texture 
	  *                     translation.
	  * \return             The input parameter completed with appropriate data.
	  */
	FbxVector4& GetDefaultT(FbxVector4& pT) const;

	/** Sets the default rotation vector. 
	  * \param pR           The first element is the texture rotation around the 
	  *                     U axis in degrees. The second element is the texture rotation 
	  *                     around the V axis in degrees. The third element is the texture 
	  *                     rotation around the W axis in degrees.
	  * \remarks            The W axis is oriented toward the result of the 
	  *                     vector product of the U and V axes that is W = U x V.
      */
	inline void SetDefaultR(const FbxVector4& pR) { Rotation.Set( FbxDouble3(pR[0],pR[1],pR[2]) ); }

	/** Returns the default rotation vector. 
	  * \param pR           First element is the texture rotation around the 
	  *                     U axis in degrees. Second element is the texture rotation 
	  *                     around the V axis in degrees. Third element is the texture 
	  *                     rotation around the W axis in degrees.
	  * \return             Input parameter filled with appropriate data.
	  * \remarks            The W axis is oriented towards the result of the 
	  *                     vector product of the U axis and V axis i.e. W = U x V.
	  */
	FbxVector4& GetDefaultR(FbxVector4& pR) const;

	/** Sets the default scale vector. 
	  * \param pS           The first element is scale applied to the texture width. 
	  *                     The second element is scale applied to the texture height. The third 
	  *                     and fourth elements have no effect on the texture. 
	  * \remarks            A scale value less than 1 stretches the texture.
	  *                     A scale value greater than 1 compresses the texture.
	  */
	inline void SetDefaultS(const FbxVector4& pS) { Scaling.Set( FbxDouble3(pS[0],pS[1],pS[2]) ); }

	/** Returns the default scale vector. 
	  * \param pS           The first element is scale applied to the texture width. 
	  *                     The second element is scale applied to the texture height. The third 
	  *                     and fourth elements have no effect on the texture. 
	  * \remarks            A scale value less than 1 stretches the texture.
	  *                     A scale value greater than 1 compresses the texture.
	  */
	FbxVector4& GetDefaultS(FbxVector4& pS) const;

	//@}

	/**
	  * \name Default Alpha Value
	  */
	//@{

	/** Sets the default alpha.
	  *	\param pAlpha       A value on a scale from 0 to 1, with 0 being transparent.
      */
	void SetDefaultAlpha(double pAlpha);

	/** Returns the default alpha.
	  *	\return             A value on a scale from 0 to 1, with 0 being transparent.
	  */
	double GetDefaultAlpha() const;

	//@}

	/**
	  * \name Default Values Management By Numbers
	  * This set of functions provides direct access to the default values in number base.
      * U, V and W coordinates are mapped to the X, Y and Z coordinates of the default vectors
      * found in the "Default Values By Vector" section.
	  */
	//@{

    /** Sets translation.
	  * \param pU       Horizontal translation applied to a texture. A displacement 
	  *                 of one unit is equal to the texture's width after applying U scaling.
	  * \param pV       Vertical translation applied to a texture. A displacement 
	  *                 of one unit is equal to the texture's height after applying V scaling.
	  */
	void SetTranslation(double pU,double pV);

    /** Returns translation applied to the texture width.
      * \remarks        A displacement of one unit is equal to the texture's width 
	  *                 after applying U scaling.
	  */
    double GetTranslationU() const;

    /** Returns translation applied to the texture height.
      * \remarks        A displacement of one unit is equal to the texture's height 
	  *                 after applying V scaling.
	  */
    double GetTranslationV() const;

    /** Sets rotation.
	  * \param pU       Texture rotation around the U axis in degrees.
	  * \param pV       Texture rotation around the V axis in degrees.
	  * \param pW       Texture rotation around the W axis in degrees.
	  * \remarks        The W axis is oriented toward the result of the vector product of 
	  *                 the U and V axes that is W = U x V.
	  */
    void SetRotation(double pU, double pV, double pW = 0.0);

    //! Returns the texture rotation around the U axis in degrees.
    double GetRotationU() const;

    //! Returns the texture rotation around the V axis in degrees.
    double GetRotationV() const;

    //! Returns the texture rotation around the W axis in degrees.
    double GetRotationW() const;

    /** Sets scale.
	  * \param pU       Scale applied to the texture width. 
	  * \param pV       Scale applied to the texture height. 
	  * \remarks        A scale value less than 1 stretches the texture.
	  *                 A scale value greater than 1 compresses the texture.
	  */
	void SetScale(double pU,double pV);

    /** Returns scale applied to the texture width. 
	  * \remarks        A scale value less than 1 stretches the texture.
	  *                 A scale value greater than 1 compresses the texture.
	  */
    double GetScaleU() const;

    /** Returns scale applied to the texture height. 
	  * \remarks        A scale value less than 1 stretches the texture.
	  *                 A scale value greater than 1 compresses the texture.
	  */
    double GetScaleV() const;
	//@}

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//	Anything beyond these lines may not be documented accurately and is 
// 	subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	virtual FbxObject& Copy(const FbxObject& pObject);

	virtual bool operator==(FbxTexture const& pTexture) const;

	void SetUVTranslation(FbxVector2& pT);
	FbxVector2& GetUVTranslation();
	void SetUVScaling(FbxVector2& pS);
	FbxVector2& GetUVScaling();

	FbxString GetTextureType();

protected:
    FbxTexture(FbxManager& pManager, char const* pName);  

	virtual void Construct(const FbxTexture* pFrom);
	virtual bool ConstructProperties(bool pForceSet);

    virtual bool PropertyNotify(PropertyNotifyType pType, FbxProperty* pProperty);

	void Init();

	int mCropping[4]; // not a prop

    EAlphaSource mAlphaSource; // now unused in MB (always set to None); not a prop
	EMappingType mMappingType; // CurrentMappingType
	EPlanarMappingNormal mPlanarMappingNormal; // CurrentMappingType
	static FbxError smError;

	// Unsupported parameters in the FBX SDK, these are declared but not accessible.
	// They are used to keep imported and exported data identical.

	FbxVector2 mUVScaling; // not a prop
	FbxVector2 mUVTranslation; // not a prop

	friend class FbxLayerContainer;

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS

};

inline FbxTypeEnum FbxTypeOf(const FbxTexture::EUnifiedMappingType&){ return eFbxEnum; }
inline FbxTypeEnum FbxTypeOf(const FbxTexture::ETextureUse6&){ return eFbxEnum; }
inline FbxTypeEnum FbxTypeOf(const FbxTexture::EWrapMode&){ return eFbxEnum; }
inline FbxTypeEnum FbxTypeOf(const FbxTexture::BlendMode&){ return eFbxEnum; }

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_SHADING_TEXTURE_H_ */
