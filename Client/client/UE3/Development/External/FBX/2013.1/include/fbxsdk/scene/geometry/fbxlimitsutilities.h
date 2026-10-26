/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxlimitsutilities.h
#ifndef _FBXSDK_SCENE_GEOMETRY_LIMIT_UTILS_H_
#define _FBXSDK_SCENE_GEOMETRY_LIMIT_UTILS_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/math/fbxvector4.h>
#include <fbxsdk/core/math/fbxtransforms.h>
#include <fbxsdk/scene/geometry/fbxnode.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

/** \brief This class represent a utility of limits for transforms.
* \nosubgrouping
*/
class FBXSDK_DLL FbxLimitsUtilities
{
public:
    /** \enum ELimitType    Limit Type.
    * - \e eT               Translation type
    * - \e eR               Rotation type
    * - \e eS               Scale type
    */
	typedef enum 
	{
		eT,
		eR,
		eS,
	} ELimitType;

    /** \enum ERotationType            Rotation type.
    * - \e eROTATION_TYPE_QUATERNION   Quaternion rotation type
    * - \e eROTATION_TYPE_EULER        Euler rotation type
    */
	typedef enum 
	{ 
		eROTATION_TYPE_QUATERNION, 
		eROTATION_TYPE_EULER, 
	} ERotationType ;

    /** \enum ERotationClampType              Rotation clamp type.
    * - \e eROTATION_CLAMP_TYPE_RECTANGULAR   Rectangular clamp type
    * - \e eROTATION_CLAMP_TYPE_ELIPSOID      Ellipsoid clamp type
    */
	typedef enum 
	{ 
		eROTATION_CLAMP_TYPE_RECTANGULAR, 
		eROTATION_CLAMP_TYPE_ELIPSOID, 
	} ERotationClampType ;


	FbxLimitsUtilities(FbxNode* pNode);

    /**
      * \name Getter/Setter functions
      */
    //@{
		void SetAuto(ELimitType pType, bool pAuto);
		bool GetAuto(ELimitType pType) const;

		void SetEnable(ELimitType pType, bool pEnable);
		bool GetEnable(ELimitType pType) const;

		void SetDefault(ELimitType pType, FbxVector4 pDefault);
		FbxVector4 GetDefault(ELimitType pType) const;

		void SetMin(ELimitType pType, FbxVector4 pMin);
		FbxVector4 GetMin(ELimitType pType) const;

		void SetMax(ELimitType pType, FbxVector4 pMax);
		FbxVector4 GetMax(ELimitType pType) const;

		void SetRotationType(ERotationType pType);
		ERotationType GetRotationType() const;

		ERotationClampType GetRotationClampType() const;

		void SetRotationAxis(FbxVector4 pRotationAxis);
		FbxVector4 GetRotationAxis() const;

		void SetAxisLength(double pLength);
		double GetAxisLength() const;

		void UpdateAutomatic(FbxNode* pNode);
		FbxVector4 GetEndPointTranslation(FbxNode* pNode) const;
		FbxVector4 GetEndSite(FbxNode* pNode) const;
    //@}

	FbxNode*	mNode;
	double		mAxisLength; 
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_GEOMETRY_LIMIT_UTILS_H_ */
