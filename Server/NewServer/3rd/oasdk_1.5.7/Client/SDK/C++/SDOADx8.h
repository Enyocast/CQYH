#ifndef SDOADX8_H
#define SDOADX8_H


#include <d3d8.h>

typedef interface ISDOADx8 ISDOADx8;
typedef ISDOADx8 *PSDOADx8, *LPSDOADx8;

MIDL_INTERFACE("6469AE4A-4862-4248-913C-704179AFE43E")
ISDOADx8 : public IUnknown
{
public:
	/* Initialize the D3D device */
	STDMETHOD_(HRESULT,Initialize)(THIS_ IDirect3DDevice8* pDev8, D3DPRESENT_PARAMETERS* pParams, bool bHookGameWnd) PURE;	
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

#endif /* SDOADX8_H */