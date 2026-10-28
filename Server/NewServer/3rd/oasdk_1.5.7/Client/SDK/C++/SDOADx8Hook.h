#ifndef SDOADX8HOOK_H
#define SDOADX8HOOK_H


#include <d3d8.h>

typedef interface ISDOADx8Hook ISDOADx8Hook;
typedef ISDOADx8Hook *PSDOADx8Hook, *LPSDOADx8Hook;

MIDL_INTERFACE("C87C0531-B8EB-4D7B-A8B9-634E10B736B9")
ISDOADx8Hook : public IUnknown
{
public:
	/* Initialize the D3D device */
	STDMETHOD_(HRESULT,Hook)(THIS_ IDirect3DDevice8* pDev8, HWND hHookGameWnd) PURE;		
	/* Release D3D resources */
	STDMETHOD_(HRESULT,unHook)(THIS) PURE;
};

#endif /* SDOADX8HOOK_H */