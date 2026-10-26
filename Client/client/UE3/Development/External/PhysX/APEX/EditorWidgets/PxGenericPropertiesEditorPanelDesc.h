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

#ifndef PX_GENERIC_PROPERTIES_EDITOR_PANEL_DESC_H
#define PX_GENERIC_PROPERTIES_EDITOR_PANEL_DESC_H

#include <PxEditorPanelDesc.h>

PX_PUSH_PACK_DEFAULT

namespace physx
{

class PxGenericPropertiesEditorCallback;

class PxGenericPropertiesEditorPanelDesc : public PxEditorPanelDesc
{
public:
	PxGenericPropertiesEditorPanelDesc(void)
	{
		callback = 0;
		mTitleBar = "Generic Properties Editor : NVIDIA Corporation, Copyright (c) 2011";
		mWindowStartPosX = 0;
		mWindowStartPosY = 0;
		mWindowWidth = 800;
		mWindowHeight = 600;
	}

	virtual bool isValid(void) const
	{
		bool ok = PxEditorPanelDesc::isValid();
		if (!callback)
		{
			ok = false;
		}
		return ok;
	}

public:
	const char					*mTitleBar;
	PxGenericPropertiesEditorCallback* callback;
	PxU32				mWindowStartPosX;
	PxU32				mWindowStartPosY;
	PxU32				mWindowWidth;
	PxU32				mWindowHeight;
};

} // namespace physx

PX_POP_PACK

#endif
