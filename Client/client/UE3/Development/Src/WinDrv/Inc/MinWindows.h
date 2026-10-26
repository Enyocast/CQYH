/*=============================================================================
	MinWindows.h: Minimal includes from Windows.h
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef _MIN_WINDOWS_H
#define _MIN_WINDOWS_H

#ifdef _WINDOWS_
#pragma message ( " " )
#pragma message ( "You have included windows.h before MinWindows.h" )
#pragma message ( "All useless stuff from the windows headers won't be excluded !!!" )
#pragma message ( " " )
#endif // _WINDOWS_

// Define the following to exclude some unused services from the windows headers.
// For information on what the following defenitions will exclude, look in the windows.h header file.
// #define NOGDICAPMASKS
// #define NOMENUS
// #define NOATOM
// #define NODRAWTEXT
// #define NOKERNEL
// #define NOMEMMGR
// // oscar@snda #define NOMETAFILE // need for gdi+
//#define NOMINMAX
// #define NOOPENFILE
// #define NOSCROLL
// #define NOSERVICE
// #define NOSOUND
// #define NOCOMM
// #define NOKANJI
// #define NOHELP
// #define NOPROFILER
// #define NODEFERWINDOWPOS
// #define NOMCX
// #define NOCRYPT
// 
// // Define these for MFC projects
// #define NOTAPE
// #define NOIMAGE
// #define NOPROXYSTUB
// #define NORPC
// 
// // Also define WIN32_LEAN_AND_MEAN to exclude rarely-used services from windows headers.
//#define WIN32_LEAN_AND_MEAN


// Finally now we can include windows.h
//#define _WS2DEF_
#define _WINSOCKAPI_
#include <windows.h>

#include <algorithm>
// #define min std::min
// #define max std::max
#include <GdiPlus.h> // oscar@snda
//using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") // oscar@snda

#define NOMINMAX
#undef min
#undef max
// For GetSaveFileName, GetOpenFileName and OPENFILENAME
// commdlg.h is included in windows.h but doesn't get included with WIN32_LEAN_AND_MEAN
// We still use WIN32_LEAN_AND_MEAN because we can include commdlg.h here and WIN32_LEAN_AND_MEAN
// excludes much more than commdlg.h
//#include <commdlg.h> 

#endif // _MIN_WINDOWS_H 

