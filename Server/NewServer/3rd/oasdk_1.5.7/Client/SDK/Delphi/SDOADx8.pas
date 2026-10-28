{------------------------------------------------------------------------------}
{ SDOADx8.pas for gwCore                                                      }
{------------------------------------------------------------------------------}
{ Unit description:  External DX8 graphics interface                                               }
{ Unit author: Shanda Network IGW team                                                 }
{ References:                                                                    }
{ Created: 2009-2-25 13:55:25                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx8;

interface

uses Windows, Direct3D8;

const
  IID_ISDOADx8: TGUID = '{6469AE4A-4862-4248-913C-704179AFE43E}';
  IID_ISDOADx8App: TGUID = '{84938E0D-3539-47FF-B5E4-DF4323DDDF1D}';


type
  PSDOADx8 = ^ISDOADx8;
  ISDOADx8 = interface(IUnknown)
    ['{6469AE4A-4862-4248-913C-704179AFE43E}']
   { Initialize the D3D device }
    function Initialize(Dev8: IDirect3DDevice8;
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
