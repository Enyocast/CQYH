{------------------------------------------------------------------------------}
{ SDOADx7.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ Unit description:                                                                    }
{ Unit author: Shanda Network Xie Bin (xiebin@snda.com)                                    }
{ References:                                                                    }
{ Created: 2009-12-16 16:50:03                                                }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx7;

interface

uses Windows, Direct3D7, DirectDraw;

const
  IID_ISDOADx7: TGUID = '{2724598A-63A9-413C-97D8-0E3EFEAB368F}';
  IID_ISDOADx7App: TGUID = '{E26A086F-A62B-4FCA-A624-4B2C8CD72F34}';


type
  PSDOADx7 = ^ISDOADx7;
  ISDOADx7 = interface(IUnknown)
    ['{2724598A-63A9-413C-97D8-0E3EFEAB368F}']
   { Initialize the D3D device }
    function Initialize(Dev7: IDirect3DDevice7;
      DirectDraw7: IDirectDraw7; FrontBuffer, BackBuffer: IDirectDrawSurface7;
      HookGameWnd: boolean; GameWnd: HWND): HRESULT; stdcall;
    // Rendering calls BeginScene and EndScene internally; call it after EndScene
    function Render(): HRESULT; stdcall;
    // Call RenderEx between BeginScene and EndScene
    function RenderEx(): HRESULT; stdcall;
    { Release D3D resources }
    function Finalize(): HRESULT; stdcall;

     { Reset the device }
    procedure OnDeviceReset(); stdcall;
     { Device lost }
    procedure OnDeviceLost(); stdcall;
     { Pass a message }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;
  
implementation

end.
