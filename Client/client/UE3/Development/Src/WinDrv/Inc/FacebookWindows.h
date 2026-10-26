/*=============================================================================
	WindFacebook.h: Windows specific Facebook integration.
	Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
=============================================================================*/
#ifndef _INC_FACEBOOKWINDOWS
#define _INC_FACEBOOKWINDOWS
#pragma once

#include "EnginePlatformInterfaceClasses.h"

/**
 * Facebook interface implementation for windows.
 */
class UFacebookWindows : public UFacebookIntegration
{
	DECLARE_CLASS_INTRINSIC(UFacebookWindows, UFacebookIntegration, 0, WinDrv)

	virtual UBOOL Init();
	virtual void BeginDestroy();
	virtual UBOOL Authorize();
	virtual UBOOL IsAuthorized();
	virtual void Disconnect();
	void WebRequest(const FString& URL, const FString& Verb, const FString& Payload, INT Tag, UBOOL bRetrieveHeaders,UBOOL bForceBinaryResponse);
	void FacebookRequest(const FString& GraphRequest);

protected:
	UBOOL HACK_IsAuthorized;
};

#endif
