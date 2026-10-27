/*=============================================================================
	WxImageShims.cpp: The prebuilt wxWidgets DLL was built before C++11 and has no wxImage move constructor or move
	assignment, but code compiled with a newer compiler asks for them (implicitly declared, imported from the DLL).
	Both are redirected here to the copy operations the DLL does provide. Win32 only.
=============================================================================*/

#include "UnrealEd.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && defined(_M_IX86)

#include <new>

namespace
{
	wxImage* __fastcall ShimWxImageMoveConstruct( wxImage* Self, void* /*Unused EDX*/, wxImage* Other )
	{
		return ::new( (void*)Self ) wxImage( *(const wxImage*)Other );
	}

	wxImage* __fastcall ShimWxImageMoveAssign( wxImage* Self, void* /*Unused EDX*/, wxImage* Other )
	{
		*Self = *(const wxImage*)Other;
		return Self;
	}
}

extern "C" void* ue3_imp_wximage_move_ctor = (void*)&ShimWxImageMoveConstruct;
extern "C" void* ue3_imp_wximage_move_assign = (void*)&ShimWxImageMoveAssign;
#pragma comment(linker, "/alternatename:__imp_??0wxImage@@QAE@$$QAV0@@Z=_ue3_imp_wximage_move_ctor")
#pragma comment(linker, "/alternatename:__imp_??4wxImage@@QAEAAV0@$$QAV0@@Z=_ue3_imp_wximage_move_assign")

#endif // _MSC_VER >= 1900 && _M_IX86
