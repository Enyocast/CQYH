#ifndef SDOACFG_H
#define SDOACFG_H

typedef void (CALLBACK *LPHLSCHANGECALLBACKPROC)(const int nHue, const int nLightness, const int nSaturation, const int nUserData);

// Modifier key constants for configuring the screenshot shortcut
#define	SDOA_ssShift	0x00000001
#define	SDOA_ssAlt		0x00000002
#define	SDOA_ssCtrl		0x00000004


typedef interface ISDOACfg ISDOACfg;
typedef ISDOACfg *PSDOACfg, *LPSDOACfg;

MIDL_INTERFACE("2F578A1F-1168-4D48-AC13-78A487AC5D4B")
ISDOACfg : public IUnknown
{
public:
	/* Hue */
	STDMETHOD_(int,GetHue)(THIS) PURE;
	STDMETHOD_(void,SetHue)(THIS_ const int nHue) PURE;
	/* Brightness */
	STDMETHOD_(int,GetLightness)(THIS) PURE;
	STDMETHOD_(void,SetLightness)(THIS_ const int nLightness) PURE;
	/* Saturation */
	STDMETHOD_(int,GetSaturation)(THIS) PURE;
	STDMETHOD_(void,SetSaturation)(THIS_ const int nSaturation) PURE;

	/* Get a color close to the current QuanQuan interface color */
	STDMETHOD_(DWORD,GetSkinColor)(THIS) PURE;
	/* Set the target color to match the QuanQuan interface after color adjustment */
	STDMETHOD_(void,SetSkinColor)(THIS_ DWORD nSkinColor) PURE;

	/* Color adjustment change callback */
	STDMETHOD_(void,SetHLSChangeCallback)(THIS_ LPHLSCHANGECALLBACKPROC fnHLSChangeCallback, const int nUserData) PURE;
	/* Get the current theme name */
	STDMETHOD_(bool,GetThemeName)(THIS_ BSTR* bstrThemeName) PURE;
	/* Set the theme name; changes take effect immediately before the first graphics initialization, otherwise on the next startup */
	STDMETHOD_(bool,SetThemeName)(THIS_ const BSTR bstrThemeName) PURE;

	/* Get interface opacity */
	STDMETHOD_(int,GetUITransparency)(THIS) PURE;
	/* Set interface opacity in the range [5..100] */
	STDMETHOD_(void,SetUITransparency)(THIS_ const int nUITransparency) PURE;


	/* Whether to automatically detect game mouse scaling */
	STDMETHOD_(bool,GetAutoCheckMouseScale)(THIS) PURE;
	STDMETHOD_(void,SetAutoCheckMouseScale)(THIS_ const bool bValue) PURE;

	/* Get logical screen dimensions, which limit the QuanQuan interaction area and are always no larger than the window */
	STDMETHOD_(void,GetLogicScreen)(THIS_  int* nSw, int* nSh) PURE;
	/* Set logical screen dimensions; -1 for both enables automatic detection */
	STDMETHOD_(void,SetLogicScreen)(THIS_  const int nSw, const int nSh) PURE;
	/* Get the background buffer area; (0, 0, 0, 0) is the default and uses the entire area */
	STDMETHOD_(void,GetUseBackBufferRect)(THIS_  PRECT pUseRect) PURE;
	/* Set the background buffer area; (0, 0, 0, 0) uses the entire area; returns false for an invalid area */
	STDMETHOD_(bool,SetUseBackBufferRect)(THIS_  RECT rUseRect) PURE;	

	/* Whether the Shanda account is currently remembered */
	STDMETHOD_(bool,RememberAccount)(THIS) PURE;

	STDMETHOD_(bool,GetSnapshootScreenHotKey)(THIS_ int* FunKey, int* NormalKey) PURE;
	STDMETHOD_(bool,SetSnapshootScreenHotKey)(THIS_ const int FunKey, const int NormalKey) PURE;

	STDMETHOD_(int, GetProperty)(THIS_ const BSTR bstrKey, BSTR* bstrValue) PURE;	
	STDMETHOD_(int, SetProperty)(THIS_ const BSTR bstrKey, const BSTR bstrValue ) PURE;
};
#endif /* SDOACFG_H */