#ifndef SDOACFG_H
#define SDOACFG_H

typedef void (CALLBACK *LPHLSCHANGECALLBACKPROC)(const int nHue, const int nLightness, const int nSaturation, const int nUserData);

// 设置截图快键键时的功能按键常量定义
#define	SDOA_ssShift	0x00000001
#define	SDOA_ssAlt		0x00000002
#define	SDOA_ssCtrl		0x00000004


typedef interface ISDOACfg ISDOACfg;
typedef ISDOACfg *PSDOACfg, *LPSDOACfg;

MIDL_INTERFACE("2F578A1F-1168-4D48-AC13-78A487AC5D4B")
ISDOACfg : public IUnknown
{
public:
	/* 色调*/
	STDMETHOD_(int,GetHue)(THIS) PURE;
	STDMETHOD_(void,SetHue)(THIS_ const int nHue) PURE;
	/* 亮度 */
	STDMETHOD_(int,GetLightness)(THIS) PURE;
	STDMETHOD_(void,SetLightness)(THIS_ const int nLightness) PURE;
	/* 饱和度 */
	STDMETHOD_(int,GetSaturation)(THIS) PURE;
	STDMETHOD_(void,SetSaturation)(THIS_ const int nSaturation) PURE;

	/* 得到当前圈圈界面的相近颜色值 */
	STDMETHOD_(DWORD,GetSkinColor)(THIS) PURE;
	/* 设置调色后与圈圈界面颜色相近的目标色 */
	STDMETHOD_(void,SetSkinColor)(THIS_ DWORD nSkinColor) PURE;

	/* 调色变化回调 */
	STDMETHOD_(void,SetHLSChangeCallback)(THIS_ LPHLSCHANGECALLBACKPROC fnHLSChangeCallback, const int nUserData) PURE;
	/* 得到当前主题名称 */
	STDMETHOD_(bool,GetThemeName)(THIS_ BSTR* bstrThemeName) PURE;
	/* 设置当前主题名称，在第一次初始化图形引擎前设置则立即生效，否则将在下次启动时生效 */
	STDMETHOD_(bool,SetThemeName)(THIS_ const BSTR bstrThemeName) PURE;

	/* 得到界面透明度 */
	STDMETHOD_(int,GetUITransparency)(THIS) PURE;
	/* 设置界面透明度值范围[5..100] */
	STDMETHOD_(void,SetUITransparency)(THIS_ const int nUITransparency) PURE;


	/* 是否自动检测游戏鼠标缩放情况 */
	STDMETHOD_(bool,GetAutoCheckMouseScale)(THIS) PURE;
	STDMETHOD_(void,SetAutoCheckMouseScale)(THIS_ const bool bValue) PURE;

	/* 得到当前逻辑屏幕宽高，主要是限制圈圈可操作的范围，总是<=窗口大小的 */
	STDMETHOD_(void,GetLogicScreen)(THIS_  int* nSw, int* nSh) PURE;
	/* 设置逻辑屏幕宽高，全为-1则表面自动检测 */
	STDMETHOD_(void,SetLogicScreen)(THIS_  const int nSw, const int nSh) PURE;
	/* 得到使用背景缓冲区的区域(0, 0, 0, 0)为默认值，使用全部区域 */
	STDMETHOD_(void,GetUseBackBufferRect)(THIS_  PRECT pUseRect) PURE;
	/* 设置使用背景缓冲区的区域 (0, 0, 0, 0)为默认值，使用全部区域，如果设置的区域无效返回false  */
	STDMETHOD_(bool,SetUseBackBufferRect)(THIS_  RECT rUseRect) PURE;	

	/* 当前是否记住盛大通行证 */
	STDMETHOD_(bool,RememberAccount)(THIS) PURE;

	STDMETHOD_(bool,GetSnapshootScreenHotKey)(THIS_ int* FunKey, int* NormalKey) PURE;
	STDMETHOD_(bool,SetSnapshootScreenHotKey)(THIS_ const int FunKey, const int NormalKey) PURE;

	STDMETHOD_(int, GetProperty)(THIS_ const BSTR bstrKey, BSTR* bstrValue) PURE;	
	STDMETHOD_(int, SetProperty)(THIS_ const BSTR bstrKey, const BSTR bstrValue ) PURE;
};
#endif /* SDOACFG_H */