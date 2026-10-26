// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


extern void InitializePak();
extern void FinalizePak();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//::MessageBox(NULL, "DLL_PROCESS_ATTACH", "a", MB_OK);
		InitializePak();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FinalizePak();
		break;
	}
	return TRUE;
}

