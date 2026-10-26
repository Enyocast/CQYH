/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#include "UnrealEd.h"
#include "GMPageFactory.h"
#include "GMCommandPage.h"
#include "GM.h"

/**
 * Registers factories for the standard GM pages.
 */
void RegisterCoreGMPages()
{
	static TGMPageFactory<WxGMCommandPage> Obj1;
}
