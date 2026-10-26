/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "GMPageFactory.h"
#include "GMFrame.h"

/**
 * The constructor registers this factory object with the GM frame.
 */
FGMPageFactory::FGMPageFactory()
{
	WxGMFrame::RegisterPageFactory( this );
}
