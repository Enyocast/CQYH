{------------------------------------------------------------------------------}
{ SDOADDraw.pas for gwCore                                                    }
{------------------------------------------------------------------------------}
{ 单元描述:  外部DDraw图形引擎接口                                             }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档:                                                                    }
{ 创建日期: 2009-2-25 13:55:31                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADDraw;

interface

uses Windows, DirectDraw;

const
  IID_ISDOADDraw: TGUID = '{B734270C-41CD-4E62-BE4F-CEC20841E367}';

const
  //DirectDraw版本常量
  SDOA_DIRECTDRAW  = $0001;
  SDOA_DIRECTDRAW2 = $0002;
  SDOA_DIRECTDRAW3 = $0003;
  SDOA_DIRECTDRAW4 = $0004;
  SDOA_DIRECTDRAW7 = $0005;  
  
type
  PSDOADDraw = ^ISDOADDraw;
  ISDOADDraw = interface(IUnknown)
    ['{B734270C-41CD-4E62-BE4F-CEC20841E367}']
    { 初始化图形系统 }
    function Initialize(AWnd: HWND; const ADirectDraw: IDirectDraw;
      const AMainSurface: IDirectDrawSurface; AVersion: Integer;
      AHookWndProc: Boolean): HRESULT; stdcall;
    { 渲染 }
    function Render(const ATargetSurface: IDirectDrawSurface): HRESULT; stdcall;
    { 释放图形系统相关资源 }
    function Finalize(): HRESULT; stdcall;
     { 传入消息 }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
