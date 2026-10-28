#ifndef SDOADX9_H
#define SDOADX9_H


#include <d3d9.h>

typedef interface ISDOADx9 ISDOADx9;
typedef ISDOADx9 *PSDOADx9, *LPSDOADx9;

MIDL_INTERFACE("59B789AB-BEE9-4C68-AA23-BCA9AB1A3E50")
ISDOADx9 : public IUnknown
{
public:
	/* Initialize the D3D device */
	STDMETHOD_(HRESULT,Initialize)(THIS_ IDirect3DDevice9* pDev9, D3DPRESENT_PARAMETERS* pParams, bool bHookGameWnd) PURE;	
	/* The interface renderer calls BeginScene and EndScene internally; call it after EndScene */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* Call RenderEx between BeginScene and EndScene */
	STDMETHOD_(HRESULT,RenderEx)(THIS) PURE;	
	/* Release D3D resources */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* Reset the device */
	STDMETHOD_(void,OnDeviceReset)(THIS_ D3DPRESENT_PARAMETERS* pParams) PURE;
	/* Device lost */
	STDMETHOD_(void,OnDeviceLost)(THIS) PURE;
	/* Pass a message */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOADX9_H */