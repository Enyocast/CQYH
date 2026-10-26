#ifndef SDOADX9HOOK_H
#define SDOADX9HOOK_H


#include <d3d9.h>

typedef interface ISDOADx9Hook ISDOADx9Hook;
typedef ISDOADx9Hook *PSDOADx9Hook, *LPSDOADx9Hook;

MIDL_INTERFACE("2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3")
ISDOADx9Hook : public IUnknown
{
public:
	/* 初始化d3d设备 */
	STDMETHOD_(HRESULT,Hook)(THIS_ IDirect3DDevice9* pDev9, HWND hHookGameWnd) PURE;	
	/* 释放d3d相关资源 */
	STDMETHOD_(HRESULT,unHook)(THIS) PURE;
};

#endif /* SDOADX9HOOK_H */