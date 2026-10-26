/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxlight.h
#ifndef _FBXSDK_SCENE_GEOMETRY_LIGHT_H_
#define _FBXSDK_SCENE_GEOMETRY_LIGHT_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/scene/geometry/fbxnodeattribute.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxColor;
class FbxManager;
class FbxTexture;

/** \brief This node attribute contains methods for accessing the properties of a light.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxLight : public FbxNodeAttribute
{
	FBXSDK_OBJECT_DECLARE(FbxLight, FbxNodeAttribute);

public:
	/**
	  * \name Light Properties
	  */
	//@{
		/** \enum ELightType Light types.
		  * - \e ePOINT
		  * - \e eDIRECTIONAL
		  * - \e eSPOT
		  * - \e eAREA
		  * - \e eVOLUME
		  */
		enum ELightType
		{
			ePOINT, 
			eDIRECTIONAL, 
			eSPOT,
			eAREA,
			eVOLUME
		};

		/** \enum EDecayType     Decay types. Used for setting the attenuation of the light.
		  * - \e eNONE          No decay. The light's intensity will not diminish with distance.		
		  * - \e eLINEAR        Linear decay. The light's intensity will diminish linearly with the distance from the light.
		  * - \e eQUADRATIC     Quadratic decay. The light's intensity will diminish with the squared distance from the light.
		  *                     This is the most physically accurate decay rate.
		  * - \e eCUBIC         Cubic decay. The light's intensity will diminish with the cubed distance from the light.
		  */
		typedef enum  
		{
			eNONE = 0,
			eLINEAR,
			eQUADRATIC,
			eCUBIC
		} EDecayType;

		/** \enum EAreaLightShape	Supported area light types.
		  * - \e eRECTANGLE			Rectangle (or often called a plane) area light type.
		  * - \e eSPHERE			Area light that illuminate all directions.
		  */
		typedef enum
		{
			eRECTANGLE = 0,
			eSPHERE
		} EAreaLightShape;

		/** Set the shadow texture for the light.
		* \param pTexture     The texture cast by the light shadow.
		*/
		void SetShadowTexture(FbxTexture* pTexture);

		/** Get the light state.
		* \return     Pointer to the texture cast by the light shadow, or \c NULL if the shadow texture has not been set.
		*/
		FbxTexture* GetShadowTexture() const;
	//@}

	/**
	* \name Properties
	*/
	//@{	
		/** This property handles the light type.
		  *
		  * Default value is ePOINT
		  */
		FbxPropertyT<ELightType> LightType;

		/** This property handles the cast light on object flag.
		  *
		  * Default value is true
		  */
		FbxPropertyT<FbxBool> CastLight;

		/** This property handles the draw volumetric light flag.
		  *
		  * Default value is true
		  */
		FbxPropertyT<FbxBool> DrawVolumetricLight;

		/** This property handles the draw ground projection flag.
		  *
		  * Default value is true
		  */
		FbxPropertyT<FbxBool> DrawGroundProjection;

		/** This property handles the draw facing volumetric projection flag.
		  *
		  * Default value is false
		  */
		FbxPropertyT<FbxBool> DrawFrontFacingVolumetricLight;

		/** This property handles the light color.
		  *
		  * Default value is (1.0, 1.0, 1.0)
		  */
		FbxPropertyT<FbxDouble3> Color;

		/** This property handles the light intensity.
		  *
		  * Default value is 100.0
		  */
		FbxPropertyT<FbxDouble> Intensity;

		/** This property handles the light inner cone angle (in degrees). Also know as the HotSpot
		  *
		  * Default value is 45.0
		  */
		FbxPropertyT<FbxDouble> InnerAngle;

		/** This property handles the light outer cone angle (in degrees). Also known as the Falloff
		  *
		  * Default value is 45.0
		  */
		FbxPropertyT<FbxDouble> OuterAngle;

		/** This property handles the light fog intensity
		  *
		  * Default value is 50.0
		  */
		FbxPropertyT<FbxDouble> Fog;

		/** This property handles the decay type 
		  *
		  * Default value is eNONE
		  */
		FbxPropertyT<EDecayType> DecayType;

		/** This property handles the decay start distance
		  *
		  * Default value is 0.0
		  */
		FbxPropertyT<FbxDouble> DecayStart;

		/** This property handles the gobo file name
		  *
		  * Default value is ""
		  */
		FbxPropertyT<FbxString> FileName;

		/** This property handles the enable near attenuation flag
		  *
		  * Default value is false
		  */
		FbxPropertyT<FbxBool> EnableNearAttenuation;

		/** This property handles the near attenuation start distance
		  *
		  * Default value is 0.0
		  */
		FbxPropertyT<FbxDouble> NearAttenuationStart;

		/** This property handles the near end attenuation 
		  *
		  * Default value is 0.0
		  */
		FbxPropertyT<FbxDouble> NearAttenuationEnd;

		/** This property handles the enable far attenuation flag
		  *
		  * Default value is false
		  */
		FbxPropertyT<FbxBool> EnableFarAttenuation;

		/** This property handles the far attenuation start distance
		  *
		  * Default value is 0.0
		  */
		FbxPropertyT<FbxDouble> FarAttenuationStart;

		/** This property handles the attenuation end distance
		  *
		  * Default value is 0.0
		  */
		FbxPropertyT<FbxDouble> FarAttenuationEnd;

		/** This property handles the cast shadow flag
		  *
		  * Default value is false
		  */
		FbxPropertyT<FbxBool> CastShadows;

		/** This property handles the shadow color
		  *
		  * Default value is (0.0, 0.0, 0.0)
		  */
		FbxPropertyT<FbxDouble3> ShadowColor;

		/** This property handles type when LightType is eAREA
		  *
		  * Default value is eRECTANGLE
		  */
		FbxPropertyT<EAreaLightShape> AreaLightShape;

		/** This property handles the left barn door angle
		  *
		  * Default value is 20.0
		  */
		FbxPropertyT<FbxFloat> LeftBarnDoor;

		/** This property handles the right barn door angle
		  *
		  * Default value is 20.0
		  */
		FbxPropertyT<FbxFloat> RightBarnDoor;

		/** This property handles the top barn door angle
		  *
		  * Default value is 20.0
		  */
		FbxPropertyT<FbxFloat> TopBarnDoor;

		/** This property handles the bottom barn door angle
		  *
		  * Default value is 20.0
		  */
		FbxPropertyT<FbxFloat> BottomBarnDoor;

		/** This property handles active status of barn doors
		  *
		  * Default value is false
		  */
		FbxPropertyT<FbxBool> EnableBarnDoor;
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
	virtual EAttributeType GetAttributeType() const;

protected:
	FbxLight(FbxManager& pManager, char const* pName);
	virtual bool ConstructProperties(bool pForceSet);
	virtual FbxStringList	GetTypeFlags() const;
#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

inline FbxTypeEnum FbxTypeOf(const FbxLight::ELightType&){ return eFbxEnum; }
inline FbxTypeEnum FbxTypeOf(const FbxLight::EDecayType&){ return eFbxEnum; }
inline FbxTypeEnum FbxTypeOf(const FbxLight::EAreaLightShape&){ return eFbxEnum; }

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_GEOMETRY_LIGHT_H_ */
