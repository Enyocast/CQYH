{------------------------------------------------------------------------------}
{ SDOACfg.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ Unit description:                                                                    }
{ Unit author: Shanda Network Xie Bin (xiebin@snda.com)                                    }
{ References:                                                                    }
{ Created: 2009-12-7 10:24:37                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOACfg;

interface

uses Windows;

const
  IID_ISDOACfg: TGUID = '{2F578A1F-1168-4D48-AC13-78A487AC5D4B}';
  IID_ISDOACfgApp: TGUID = '{19BA0946-62CC-4BE3-B2F4-22C30D912F15}';
  // Modifier key constants for the screenshot shortcut
  SDOA_ssShift  = $00000001;
  SDOA_ssAlt    = $00000002;
  SDOA_ssCtrl   = $00000004;

type
  THLSChangeCallBack = procedure(const nHue, nLightness, nSaturation, nUserData: Integer); stdcall;

type
  { Theme settings }
  PSDOACfg = ^ISDOACfg;
  ISDOACfg = interface(IUnknown)
    ['{2F578A1F-1168-4D48-AC13-78A487AC5D4B}']
    // Hue
    function GetHue(): Integer; stdcall;
    procedure SetHue(const Value: Integer); stdcall;
    // Brightness
    function GetLightness(): Integer; stdcall;
    procedure SetLightness(const Value: Integer); stdcall;
    // Saturation
    function GetSaturation(): Integer; stdcall;
    procedure SetSaturation(const Value: Integer); stdcall;

    // Get a color close to the current Quanquan interface color
    function GetSkinColor(): Integer; stdcall;
    // Set the target color for matching the adjusted Quanquan interface
    procedure SetSkinColor(Value: DWORD); stdcall;

    // Color adjustment callback
    procedure SetHLSChangeCallback(const HLSChangeCb: THLSChangeCallBack; const UserData: Integer); stdcall;

    // Get the current theme name
    function GetThemeName(out ThemeName: WideString): Boolean; stdcall;
    // Set the current theme
    function SetThemeName(ThemeName: WideString): Boolean; stdcall;

    // Get interface opacity
    function GetUITransparency(): Integer; stdcall;
    // Set interface opacity in the range [5..100]
    procedure SetUITransparency(Value: Integer); stdcall;

    // Whether to detect game mouse scaling automatically
    function GetAutoCheckMouseScale(): boolean; stdcall;
    procedure SetAutoCheckMouseScale(const Value: Boolean); stdcall;

    // Get logical screen dimensions, which limit the Quanquan interaction area and are always <= the window size
    procedure GetLogicScreen(var sw, sh: integer); stdcall;
    // Set logical screen dimensions; -1 for both enables automatic detection
    procedure SetLogicScreen(const sw, sh: Integer); stdcall;
    // Get the back-buffer region; the default (0, 0, 0, 0) uses the entire area
    procedure GetUseBackBufferRect(var Rect: TRect); stdcall;
    // Set the back-buffer region; (0, 0, 0, 0) uses the entire area, and an invalid region returns false
    function SetUseBackBufferRect(Rect: TRect): Boolean; stdcall;
    // Whether the Shanda account is currently remembered
    function RememberAccount(): boolean; stdcall;

    function GetSnapshootScreenHotKey(var FunKey, NormalKey: Integer):Boolean; stdcall;
    function SetSnapshootScreenHotKey(const FunKey, NormalKey: Integer):Boolean; stdcall;
    
    // For special extension interfaces
    function GetProperty(const Key: WideString; out Value: WideString): Integer; stdcall;
    function SetProperty(const Key: WideString; const Value: WideString): Integer; stdcall;
  end;

implementation

end.
