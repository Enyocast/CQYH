/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GM_H__
#define __GM_H__

#ifndef USING_GM
#if !CONSOLE && WITH_EDITOR && !FINAL_RELEASE && !SHIPPING_PC_GAME
#define	USING_GM 1
#else
#define USING_GM 0
#endif
#endif

#if USING_GM
#include "GMExec.h"
/**
 * Registers factories for the standard GM pages.
 */
void RegisterCoreGMPages();
#endif

#endif // __GM_H__
