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

#ifndef PX_EDITOR_PANEL_DESC_H
#define PX_EDITOR_PANEL_DESC_H

#include "foundation/Px.h"
#include "foundation/PxSimpleTypes.h"

#if defined(PX_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h> // for HWND and IsWindow()
#endif

PX_PUSH_PACK_DEFAULT

namespace physx
{

class PxEditorPanelDesc
{
public:
	PxEditorPanelDesc(void)
	{
#if defined(PX_WINDOWS)
		parentWindow = 0;
#endif
		GameScale = 1.0f; // the default game scale for units
		mNeedSetSize = false;
		mX1 = 40;
		mY1 = 40;
		mWidth = 900;
		mHeight = 600;
	}

	virtual bool isValid(void) const
	{
		bool ok = true;
#if defined(PX_WINDOWS)
		if (!parentWindow || !IsWindow(parentWindow))
		{
			ok = false;
		}
#endif
		return ok;
	}

public:
#if defined(PX_WINDOWS)
	//! REQUIRED: parent window or panel place the widgets in.
	HWND parentWindow;
#endif
	physx::PxF32	GameScale;
	bool			mNeedSetSize;
	physx::PxU32	mX1;
	physx::PxU32	mY1;
	physx::PxU32	mWidth;
	physx::PxU32	mHeight;
};

} // namespace physx

PX_POP_PACK

#endif
