#ifndef SDOADX9HOOK_H
#define SDOADX9HOOK_H


#include <d3d9.h>

typedef interface ISDOADx9Hook ISDOADx9Hook;
typedef ISDOADx9Hook *PSDOADx9Hook, *LPSDOADx9Hook;

MIDL_INTERFACE("2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3")
ISDOADx9Hook : public IUnknown
{
public:
	/* Initialize the D3D device */
	STDMETHOD_(HRESULT,Hook)(THIS_ IDirect3DDevice9* pDev9, HWND hHookGameWnd) PURE;	
	/* Release D3D resources */
	STDMETHOD_(HRESULT,unHook)(THIS) PURE;
};

#endif /* SDOADX9HOOK_H */