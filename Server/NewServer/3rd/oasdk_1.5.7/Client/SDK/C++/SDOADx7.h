#ifndef SDOADX7_H
#define SDOADX7_H

#include <ddraw.h>
#include <d3d.h>
//#include <d3d7.h>

typedef interface ISDOADx7 ISDOADx7;
typedef ISDOADx7 *PSDOADx7, *LPSDOADx7;

MIDL_INTERFACE("2724598A-63A9-413C-97D8-0E3EFEAB368F")
ISDOADx7 : public IUnknown
{
public:
	/* Initialize the D3D device */
	STDMETHOD_(HRESULT,Initialize)(THIS_ IDirect3DDevice7* pDev7, IDirectDraw7* DirectDraw7, IDirectDrawSurface7* FrontBuffer, IDirectDrawSurface7* BackBuffer, bool bHookGameWnd, HWND hGameWnd) PURE;	
	/* The interface renderer calls BeginScene and EndScene internally; call it after EndScene */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* Call RenderEx between BeginScene and EndScene */
	STDMETHOD_(HRESULT,RenderEx)(THIS) PURE;	
	/* Release D3D resources */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* Reset the device */
	STDMETHOD_(void,OnDeviceReset)(THIS) PURE;
	/* Device lost */
	STDMETHOD_(void,OnDeviceLost)(THIS) PURE;
	/* Pass a message */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOADX7_H */