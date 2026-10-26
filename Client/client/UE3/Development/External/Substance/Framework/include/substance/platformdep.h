/** @file platformdep.h
	@brief Platform specific definitions
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance engine headers
	@date 20080108
	@copyright Allegorithmic. All rights reserved.

	Defines platform specific macros. One of these macros must already be
	defined (preprocessor #define):
	  - SUBSTANCE_PLATFORM_BLEND: generic platform, results in system memory
	  - SUBSTANCE_PLATFORM_D3D9PC: PC Direct3D9 API
	  - SUBSTANCE_PLATFORM_XBOX360: Xbox 360
	  - SUBSTANCE_PLATFORM_D3D10PC: PC Direct3D10 API
	  - SUBSTANCE_PLATFORM_D3D11PC: PC Direct3D11 API
	  - SUBSTANCE_PLATFORM_OGL2: OpenGL 2 API
	  - SUBSTANCE_PLATFORM_OGLES2: OpenGL ES 2 API
	  - SUBSTANCE_PLATFORM_PS3GCM: GCM PS3 API
	  etc. */

#ifndef _SUBSTANCE_PLATFORMDEP_H
#define _SUBSTANCE_PLATFORMDEP_H

#ifndef SUBSTANCE_WIN32
	#ifdef __WIN32__
		#define SUBSTANCE_WIN32 1
	#endif
	#ifdef _WIN32
		#define SUBSTANCE_WIN32 1
	#endif
#endif


/* Platform specific headers */

#if defined(SUBSTANCE_PLATFORM_XBOX360)
	
	/* 	Xbox 360 */
	#include <xtl.h>
	
	#define SUBSTANCE_API_PLATFORM 0x5
		
#elif defined(SUBSTANCE_PLATFORM_D3D9PC)

	/* PC Direct3D9 API */
	#ifndef D3D_DEBUG_INFO
		#define D3D_DEBUG_INFO 1
	#endif //D3D_DEBUG_INFO
	#pragma pack(push,8)
	#define D3D_OVERLOADS 1
	#include <d3d9.h>
	#pragma pack(pop)
	
	#define SUBSTANCE_API_PLATFORM 0x3

#elif defined(SUBSTANCE_PLATFORM_D3D10PC)

	/* PC Direct3D10 API */
	#include <d3d10.h>
	
	#define SUBSTANCE_API_PLATFORM 0x7
	
#elif defined(SUBSTANCE_PLATFORM_D3D11PC)

	/* PC Direct3D10 API */
	#include <d3d11.h>
	
	#define SUBSTANCE_API_PLATFORM 0x9
	
#elif defined(SUBSTANCE_PLATFORM_OGLES2)	

	/* OpenGL ES 2 platform */
	/* No header needed */
	
	#define SUBSTANCE_API_PLATFORM 0xD

#elif defined(SUBSTANCE_PLATFORM_OGL2)

	/* OpenGL GLSL platform */
	/* No header needed */
	
	#define SUBSTANCE_API_PLATFORM 0x1

#elif defined(SUBSTANCE_PLATFORM_PS3GCM)

	/* GCM PS3 platform */
	#include <cell/gcm.h>
	
	#define SUBSTANCE_API_PLATFORM 0x8
	
#elif defined(SUBSTANCE_PLATFORM_BLEND)
	
	/* Blend platform */
	/* No header needed */
	
	#define SUBSTANCE_API_PLATFORM 0x0
	
#else

	/* platform not supported / define not set */
	#error Platform NYI or proper SUBSTANCE_PLATFORM_xxx preprocessor macro not set
	
#endif


/* Base types defines */
#include <stddef.h>

/* C/C++ macros */
#ifndef SUBSTANCE_EXTERNC
	#ifdef __cplusplus
		#define SUBSTANCE_EXTERNC extern "C"
	#else
		#define SUBSTANCE_EXTERNC
	#endif
#endif

/* SUBSTANCE_EXPORT macros */
#ifndef SUBSTANCE_EXPORT
	#ifdef SUBSTANCE_DLL
		#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
			#define SUBSTANCE_EXPORT SUBSTANCE_EXTERNC __declspec(dllexport)
		#elif defined(__GNUC__)
			#if __GNUC__>=4
				#define SUBSTANCE_EXPORT SUBSTANCE_EXTERNC __attribute__((visibility("default")))
			#else
				#define SUBSTANCE_EXPORT SUBSTANCE_EXTERNC
			#endif
		#else
			#error Unknown compiler
		#endif
	#else
		#define SUBSTANCE_EXPORT SUBSTANCE_EXTERNC
	#endif
#endif

/* Callback functions */
#ifndef SUBSTANCE_CALLBACK
	#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
		#define SUBSTANCE_CALLBACK __stdcall
	#else
		#define SUBSTANCE_CALLBACK
	#endif
#endif


#endif /* ifndef _SUBSTANCE_PLATFORMDEP_H */
