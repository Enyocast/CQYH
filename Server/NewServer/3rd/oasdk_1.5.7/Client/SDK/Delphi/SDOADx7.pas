{------------------------------------------------------------------------------}
{ SDOADx7.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ 单元描述:                                                                    }
{ 单元作者: 盛大网络 谢斌 (xiebin@snda.com)                                    }
{ 参考文档:                                                                    }
{ 创建日期: 2009-12-16 16:50:03                                                }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
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
   { 初始化d3d设备 }
    function Initialize(Dev7: IDirect3DDevice7;
      DirectDraw7: IDirectDraw7; FrontBuffer, BackBuffer: IDirectDrawSurface7;
      HookGameWnd: boolean; GameWnd: HWND): HRESULT; stdcall;
    // 渲染界面内部已经调用BeginScene和EndScene，确认在EndScene之后调用它
    function Render(): HRESULT; stdcall;
    // 确保在BeginScene、EndScene之间调用RenderEx
    function RenderEx(): HRESULT; stdcall;
    { 释放d3d相关资源 }
    function Finalize(): HRESULT; stdcall;

     { 重置设备 }
    procedure OnDeviceReset(); stdcall;
     { 设备丢失 }
    procedure OnDeviceLost(); stdcall;
     { 传入消息 }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;
  
implementation

end.
