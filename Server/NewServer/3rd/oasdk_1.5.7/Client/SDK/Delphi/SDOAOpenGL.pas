{------------------------------------------------------------------------------}
{ SDOAOpenGL.pas for gwCore                                                    }
{------------------------------------------------------------------------------}
{ Unit description:  External OpenGL graphics interface                                            }
{ Unit author: Shanda Network IGW team                                                 }
{ References:                                                                    }
{ Created: 2009-2-25 13:55:36                                                 }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOAOpenGL;

interface

uses Windows;

const
  IID_ISDOAOpenGL: TGUID = '{E6DCDBF9-6058-4210-9979-766B9E56C9C9}';


type
  PSDOAOpenGL = ^ISDOAOpenGL;
  ISDOAOpenGL = interface(IUnknown)
    ['{E6DCDBF9-6058-4210-9979-766B9E56C9C9}']
    { Initialize the graphics system }
    function Initialize(DC: HDC; RC: HGLRC; AHookWnd: Boolean): HRESULT; stdcall;
    { Render }
    function Render(): HRESULT; stdcall;
    { Release graphics system resources }
    function Finalize(): HRESULT; stdcall;
     { Pass a message }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
