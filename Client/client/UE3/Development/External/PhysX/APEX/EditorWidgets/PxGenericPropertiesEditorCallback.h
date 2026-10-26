// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
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
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.
#ifndef PX_GENERIC_PROPERTIES_EDITOR_CALLBACK_H
#define PX_GENERIC_PROPERTIES_EDITOR_CALLBACK_H

namespace NxParameterized
{
class Handle;
class Definition;
}

using namespace physx;

PX_PUSH_PACK_DEFAULT

#pragma warning(push)
#pragma warning(disable:4100)

namespace physx
{
class PxGenericPropertiesEditorCallback
{
public:
	enum RefreshAction
	{
		REFRESH_NONE,
		REFRESH_ARRAY_TREE_VIEW,
		REFRESH_ARRAY_FLAT_VIEW,
		REFRESH_REFERENCES
	};
	//! called just after a property has been editted by the user.
	virtual PxGenericPropertiesEditorCallback::RefreshAction onPostPropertyEdit(NxParameterized::Handle& handle, const char* tweakable, NxParameterized::Interface* parentInterface) = 0;

	virtual PxGenericPropertiesEditorCallback::RefreshAction onPostPropertyDelete(NxParameterized::Handle& handle, const char* tweakable, NxParameterized::Interface* parentInterface)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	}

	virtual PxGenericPropertiesEditorCallback::RefreshAction onPostPropertyAdd(NxParameterized::Handle& handle, const char* tweakable, NxParameterized::Interface* parentInterface)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	}


	//! query the application to find a named reference for us.
	virtual const char* onFindNamedReference(const char *&variant,physx::PxU32 numVariants,const char **variantNames) = 0;

	virtual PxGenericPropertiesEditorCallback::RefreshAction onArraySelectElement(NxParameterized::Handle& handle, physx::PxU32 arrayIndex)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	};
	virtual PxGenericPropertiesEditorCallback::RefreshAction onCustomMenuArrayElement(NxParameterized::Handle& handle, physx::PxU32 arrayIndex, const char* choice)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	};
	virtual PxGenericPropertiesEditorCallback::RefreshAction onCustomMenuStruct(NxParameterized::Handle& handle, const char* choice)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	};
	virtual PxGenericPropertiesEditorCallback::RefreshAction onStructSelect(NxParameterized::Handle& handle)
	{
		return PxGenericPropertiesEditorCallback::REFRESH_NONE;
	};

	virtual const char ** getCustomEnumeration(const char *customEnum,PxU32 &count) = 0;

	virtual void menuCommand(PxU32 menuCommand)
	{

	}

	virtual void onClose(void)
	{

	}

	virtual bool getCustomColor(const NxParameterized::Handle &handle,PxU32 &customColor) = 0;

};

} // namespace physx

#pragma warning(pop)

PX_POP_PACK

#endif
