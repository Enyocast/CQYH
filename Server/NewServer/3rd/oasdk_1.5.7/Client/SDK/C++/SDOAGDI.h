#ifndef SDOAGDI_H
#define SDOAGDI_H


#define SDOA_GDIMODE_DESKTOP  0 // Render to the desktop
#define SDOA_GDIMODE_HOST     1 // Render to the host window


typedef interface ISDOAGDI ISDOAGDI;
typedef ISDOAGDI *PSDOAGDI, *LPSDOAGDI;

MIDL_INTERFACE("85DE7C68-1D88-4FBF-AF20-6178813C8037")
ISDOAGDI : public IUnknown
{
public:
	/* Initialize GDI resources */
	STDMETHOD_(HRESULT,Initialize)(THIS_ HWND hHostWnd, int nMode) PURE;	
	/* Render the interface */
	STDMETHOD_(HRESULT,Render)(THIS_ HWND hWnd, HDC hDC) PURE;	
	/* Release GDI resources */
	STDMETHOD_(HRESULT,Finalize)(THIS_ HWND hWnd) PURE;
	/* Pass a message */
	STDMETHOD_(HRESULT,OnWindowProc)(THIS_ HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult) PURE;
};

#endif /* SDOAGDI_H */