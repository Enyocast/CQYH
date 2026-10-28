#ifndef SDOADX8_H
#define SDOADX8_H


#include <d3d8.h>

typedef interface ISDOADx8 ISDOADx8;
typedef ISDOADx8 *PSDOADx8, *LPSDOADx8;

MIDL_INTERFACE("6469AE4A-4862-4248-913C-704179AFE43E")
ISDOADx8 : public IUnknown
{
public:
	/* 初始化d3d设备 */
	STDMETHOD_(HRESULT,Initialize)(THIS_ IDirect3DDevice8* pDev8, D3DPRESENT_PARAMETERS* pParams, bool bHookGameWnd) PURE;	
	/* 渲染界面内部已经调用BeginScene和EndScene，确认在EndScene之后调用它 */
	STDMETHOD_(HRESULT,Render)(THIS) PURE;	
	/* 确保在BeginScene、EndScene之间调用RenderEx */
	STDMETHOD_(HRESULT,RenderEx)(THIS) PURE;	
	/* 释放d3d相关资源 */
	STDMETHOD_(HRESULT,Finalize)(THIS) PURE;
	/* 重置设备 */
	STDMETHOD_(void,OnDeviceReset)(THIS_ D3DPRESENT_PARAMETERS* pParams) PURE;
	/* 设备丢失 */
	STDMETHOD_(void,OnDeviceLost)(THIS) PURE;
	/* 传入消息 */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOADX8_H */