{------------------------------------------------------------------------------}
{ SDOADx9.pas for gwCore                                                      }
{------------------------------------------------------------------------------}
{ Unit description:  External DX9 graphics interface                                               }
{ Unit author: Shanda Network IGW team                                                 }
{ References:                                                                    }
{ Created: 2009-2-25 13:55:01                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx9;

interface

uses Windows, Direct3D9;

const
  IID_ISDOADx9: TGUID = '{59B789AB-BEE9-4C68-AA23-BCA9AB1A3E50}';
  IID_ISDOADx9App: TGUID = '{80CB27C2-1B78-4259-8458-B44F2B3AC756}';


type
  { DX9 graphics interface }
  PSDOADx9 = ^ISDOADx9;
  ISDOADx9 = interface(IUnknown)
    ['{59B789AB-BEE9-4C68-AA23-BCA9AB1A3E50}']
    { Initialize the D3D device }
    function Initialize(Dev9: IDirect3DDevice9;
      Params: PD3DPresentParameters; HookGameWnd: boolean): HRESULT; stdcall;
    // Rendering calls BeginScene and EndScene internally; call it after EndScene
    function Render(): HRESULT; stdcall;
    // Call RenderEx between BeginScene and EndScene
    function RenderEx(): HRESULT; stdcall;
    { Release D3D resources }
    function Finalize(): HRESULT; stdcall;

     { Reset the device }
    procedure OnDeviceReset(Params: PD3DPresentParameters); stdcall;
     { Device lost }
    procedure OnDeviceLost(); stdcall;
     { Pass a message }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
