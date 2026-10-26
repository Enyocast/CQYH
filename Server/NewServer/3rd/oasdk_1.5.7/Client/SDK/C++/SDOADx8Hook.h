#ifndef SDOADX8HOOK_H
#define SDOADX8HOOK_H


#include <d3d8.h>

typedef interface ISDOADx8Hook ISDOADx8Hook;
typedef ISDOADx8Hook *PSDOADx8Hook, *LPSDOADx8Hook;

MIDL_INTERFACE("C87C0531-B8EB-4D7B-A8B9-634E10B736B9")
ISDOADx8Hook : public IUnknown
{
public:
	/* 初始化d3d设备 */
	STDMETHOD_(HRESULT,Hook)(THIS_ IDirect3DDevice8* pDev8, HWND hHookGameWnd) PURE;		
	/* 释放d3d相关资源 */
	STDMETHOD_(HRESULT,unHook)(THIS) PURE;
};

#endif /* SDOADX8HOOK_H */