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
	/* 初始化d3d设备 */
	STDMETHOD_(HRESULT,Initialize)(THIS_ IDirect3DDevice7* pDev7, IDirectDraw7* DirectDraw7, IDirectDrawSurface7* FrontBuffer, IDirectDrawSurface7* BackBuffer, bool bHookGameWnd, HWND hGameWnd) PURE;	
	/* 渲染界面内部已经调用BeginScene和EndScene，确认在EndScene之后调用它 */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* 确保在BeginScene、EndScene之间调用RenderEx */
	STDMETHOD_(HRESULT,RenderEx)(THIS) PURE;	
	/* 释放d3d相关资源 */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* 重置设备 */
	STDMETHOD_(void,OnDeviceReset)(THIS) PURE;
	/* 设备丢失 */
	STDMETHOD_(void,OnDeviceLost)(THIS) PURE;
	/* 传入消息 */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOADX7_H */