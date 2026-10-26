{------------------------------------------------------------------------------}
{ SDOACfg.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ 单元描述:                                                                    }
{ 单元作者: 盛大网络 谢斌 (xiebin@snda.com)                                    }
{ 参考文档:                                                                    }
{ 创建日期: 2009-12-7 10:24:37                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOACfg;

interface

uses Windows;

const
  IID_ISDOACfg: TGUID = '{2F578A1F-1168-4D48-AC13-78A487AC5D4B}';
  IID_ISDOACfgApp: TGUID = '{19BA0946-62CC-4BE3-B2F4-22C30D912F15}';
  // 设置截图快键键时的功能按键常量定义
  SDOA_ssShift  = $00000001;
  SDOA_ssAlt    = $00000002;
  SDOA_ssCtrl   = $00000004;

type
  THLSChangeCallBack = procedure(const nHue, nLightness, nSaturation, nUserData: Integer); stdcall;  

type
  { 主题相关 }
  PSDOACfg = ^ISDOACfg;
  ISDOACfg = interface(IUnknown)
    ['{2F578A1F-1168-4D48-AC13-78A487AC5D4B}']
    // 色调
    function GetHue(): Integer; stdcall;
    procedure SetHue(const Value: Integer); stdcall;
    // 亮度
    function GetLightness(): Integer; stdcall;
    procedure SetLightness(const Value: Integer); stdcall;
    // 饱和合度
    function GetSaturation(): Integer; stdcall;
    procedure SetSaturation(const Value: Integer); stdcall;

    // 得到当前圈圈界面的相近颜色值
    function GetSkinColor(): Integer; stdcall;
    // 设置调色后与圈圈界面颜色相近的目标色
    procedure SetSkinColor(Value: DWORD); stdcall;

    // 调色变化回调
    procedure SetHLSChangeCallback(const HLSChangeCb: THLSChangeCallBack; const UserData: Integer); stdcall;

    // 得到当前主题名称
    function GetThemeName(out ThemeName: WideString): Boolean; stdcall;
    // 设置当前主题
    function SetThemeName(ThemeName: WideString): Boolean; stdcall;

    // 得到界面透明度
    function GetUITransparency(): Integer; stdcall;
    // 设置界面透明度值范围[5..100]
    procedure SetUITransparency(Value: Integer); stdcall;

    // 是否自动检测游戏鼠标缩放情况
    function GetAutoCheckMouseScale(): boolean; stdcall;
    procedure SetAutoCheckMouseScale(const Value: Boolean); stdcall;

    // 得到当前逻辑屏幕宽高，主要是限制圈圈可操作的范围，总是<=窗口大小的
    procedure GetLogicScreen(var sw, sh: integer); stdcall;
    // 设置逻辑屏幕宽高，全为-1则表面自动检测
    procedure SetLogicScreen(const sw, sh: Integer); stdcall;
    // 得到使用背景缓冲区的区域(0, 0, 0, 0)为默认值，使用全部区域 
    procedure GetUseBackBufferRect(var Rect: TRect); stdcall;
    // 设置使用背景缓冲区的区域 (0, 0, 0, 0)为默认值，使用全部区域，如果设置的区域无效返回false
    function SetUseBackBufferRect(Rect: TRect): Boolean; stdcall;
    // 当前是否记住盛大通行证
    function RememberAccount(): boolean; stdcall;

    function GetSnapshootScreenHotKey(var FunKey, NormalKey: Integer):Boolean; stdcall;
    function SetSnapshootScreenHotKey(const FunKey, NormalKey: Integer):Boolean; stdcall;
    
    // 用于特殊的扩展接口
    function GetProperty(const Key: WideString; out Value: WideString): Integer; stdcall;
    function SetProperty(const Key: WideString; const Value: WideString): Integer; stdcall;
  end;

implementation

end.
