{------------------------------------------------------------------------------}
{ SDOADDraw.pas for gwCore                                                    }
{------------------------------------------------------------------------------}
{ Unit description:  External DDraw graphics interface                                             }
{ Unit author: Shanda Network IGW team                                                 }
{ References:                                                                    }
{ Created: 2009-2-25 13:55:31                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADDraw;

interface

uses Windows, DirectDraw;

const
  IID_ISDOADDraw: TGUID = '{B734270C-41CD-4E62-BE4F-CEC20841E367}';

const
  //DirectDraw version constants
  SDOA_DIRECTDRAW  = $0001;
  SDOA_DIRECTDRAW2 = $0002;
  SDOA_DIRECTDRAW3 = $0003;
  SDOA_DIRECTDRAW4 = $0004;
  SDOA_DIRECTDRAW7 = $0005;  
  
type
  PSDOADDraw = ^ISDOADDraw;
  ISDOADDraw = interface(IUnknown)
    ['{B734270C-41CD-4E62-BE4F-CEC20841E367}']
    { Initialize the graphics system }
    function Initialize(AWnd: HWND; const ADirectDraw: IDirectDraw;
      const AMainSurface: IDirectDrawSurface; AVersion: Integer;
      AHookWndProc: Boolean): HRESULT; stdcall;
    { Render }
    function Render(const ATargetSurface: IDirectDrawSurface): HRESULT; stdcall;
    { Release graphics system resources }
    function Finalize(): HRESULT; stdcall;
     { Pass a message }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
