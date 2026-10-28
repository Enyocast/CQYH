{------------------------------------------------------------------------------}
{ SDOAGDI.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ Unit description:  GDI graphics interface                                                  }
{ Unit author: Shanda Network IGW team                                                 }
{ References:                                                                    }
{ Created: 2009-9-03 13:55:01                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOAGDI;

interface

uses Windows;

const
  IID_ISDOAGDI: TGUID = '{85DE7C68-1D88-4FBF-AF20-6178813C8037}';
  IID_ISDOAGDIApp: TGUID = '{9793A409-4912-419A-81F7-A9F27E89929A}';

const
  SDOA_GDIMODE_DESKTOP = 0; // Render to the desktop
  SDOA_GDIMODE_HOST    = 1; // Render to the host window

type
  { GDI graphics interface }
  PSDOAGDI = ^ISDOAGDI;
  ISDOAGDI = interface(IUnknown)
    ['{85DE7C68-1D88-4FBF-AF20-6178813C8037}']
    { Initialize the GDI device }
    function Initialize(AHostWnd: HWND; AMode: Integer): HRESULT; stdcall;
    // Render the interface
    function Render(AWnd: HWND; ADC: HDC): HRESULT; stdcall;
    { Release GDI resources }
    function Finalize(AWnd: HWND): HRESULT; stdcall;
     { Pass a message }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
