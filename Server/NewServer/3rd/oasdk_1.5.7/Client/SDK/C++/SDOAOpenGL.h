#ifndef SDOAOPENGL_H
#define SDOAOPENGL_H

#include <windows.h>

typedef interface ISDOAOpenGL ISDOAOpenGL;
typedef ISDOAOpenGL *PSDOAOpenGL, *LPSDOAOpenGL;

MIDL_INTERFACE("E6DCDBF9-6058-4210-9979-766B9E56C9C9")
ISDOAOpenGL : public IUnknown
{
public:
	/* Initialize the graphics engine */
	STDMETHOD_(HRESULT,Initialize)(THIS_ HDC hDC, HGLRC hRC, bool bHookWnd) PURE;	
	/* Render the interface */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* Release graphics engine resources */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* Pass a message */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};


#endif /* SDOAOPENGL_H */
