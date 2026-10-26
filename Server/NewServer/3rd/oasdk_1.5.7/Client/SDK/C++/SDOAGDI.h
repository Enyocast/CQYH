#ifndef SDOAGDI_H
#define SDOAGDI_H


#define SDOA_GDIMODE_DESKTOP  0 // 绘制渲染到桌面上
#define SDOA_GDIMODE_HOST     1 // 绘制到HOST的窗口上


typedef interface ISDOAGDI ISDOAGDI;
typedef ISDOAGDI *PSDOAGDI, *LPSDOAGDI;

MIDL_INTERFACE("85DE7C68-1D88-4FBF-AF20-6178813C8037")
ISDOAGDI : public IUnknown
{
public:
	/* 初始化GDI资源 */
	STDMETHOD_(HRESULT,Initialize)(THIS_ HWND hHostWnd, int nMode) PURE;	
	/* 渲染界面 */
	STDMETHOD_(HRESULT,Render)(THIS_ HWND hWnd, HDC hDC) PURE;	
	/* 释放GDI相关资源 */
	STDMETHOD_(HRESULT,Finalize)(THIS_ HWND hWnd) PURE;
	/* 传入消息 */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOAGDI_H */