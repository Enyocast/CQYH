#ifndef SDOAOPENGL_H
#define SDOAOPENGL_H

#include <windows.h>

typedef interface ISDOAOpenGL ISDOAOpenGL;
typedef ISDOAOpenGL *PSDOAOpenGL, *LPSDOAOpenGL;

MIDL_INTERFACE("E6DCDBF9-6058-4210-9979-766B9E56C9C9")
ISDOAOpenGL : public IUnknown
{
public:
	/* 初始化图形引擎 */
	STDMETHOD_(HRESULT,Initialize)(THIS_ HDC hDC, HGLRC hRC, bool bHookWnd) PURE;	
	/* 渲染界面 */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* 释放图形引擎相关资源 */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* 传入消息 */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};


#endif /* SDOAOPENGL_H */
