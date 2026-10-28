#ifndef SDOADDRAW_H
#define SDOADDRAW_H

#include <ddraw.h>

#define SDOA_DIRECTDRAW		0x0001
#define SDOA_DIRECTDRAW2	0x0002
#define SDOA_DIRECTDRAW3	0x0003
#define SDOA_DIRECTDRAW4	0x0004
#define SDOA_DIRECTDRAW7	0x0005  

typedef interface ISDOADDraw ISDOADDraw;
typedef ISDOADDraw *PSDOADDraw, *LPSDOADDraw;

MIDL_INTERFACE("B734270C-41CD-4E62-BE4F-CEC20841E367")
ISDOADDraw : public IUnknown
{
public:
	/* Initialize the graphics engine */
	STDMETHOD_(HRESULT,Initialize)(THIS_ HWND hWnd, IDirectDraw* pDirectDraw, IDirectDrawSurface* pMainSurface, 
		int nDDrawVersion, bool bHookWndProc) PURE;	
	/* Render the interface after rendering the game scene */
	STDMETHOD_(HRESULT,Render)(THIS_ IDirectDrawSurface* pTargetSurface) PURE;	
	/* Release graphics engine resources */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* Pass a message */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOADDRAW_H */