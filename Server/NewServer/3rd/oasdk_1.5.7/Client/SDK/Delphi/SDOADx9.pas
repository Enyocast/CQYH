{------------------------------------------------------------------------------}
{ SDOADx9.pas for gwCore                                                      }
{------------------------------------------------------------------------------}
{ 单元描述:  外部dx9图形引擎接口                                               }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档:                                                                    }
{ 创建日期: 2009-2-25 13:55:01                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx9;

interface

uses Windows, Direct3D9;

const
  IID_ISDOADx9: TGUID = '{59B789AB-BEE9-4C68-AA23-BCA9AB1A3E50}';
  IID_ISDOADx9App: TGUID = '{80CB27C2-1B78-4259-8458-B44F2B3AC756}';


type
  { dx9图形接口 }
  PSDOADx9 = ^ISDOADx9;
  ISDOADx9 = interface(IUnknown)
    ['{59B789AB-BEE9-4C68-AA23-BCA9AB1A3E50}']
    { 初始化d3d设备 }
    function Initialize(Dev9: IDirect3DDevice9;
      Params: PD3DPresentParameters; HookGameWnd: boolean): HRESULT; stdcall;
    // 渲染界面内部已经调用BeginScene和EndScene，确认在EndScene之后调用它
    function Render(): HRESULT; stdcall;
    // 确保在BeginScene、EndScene之间调用RenderEx
    function RenderEx(): HRESULT; stdcall;
    { 释放d3d相关资源 }
    function Finalize(): HRESULT; stdcall;

     { 重置设备 }
    procedure OnDeviceReset(Params: PD3DPresentParameters); stdcall;
     { 设备丢失 }
    procedure OnDeviceLost(); stdcall;
     { 传入消息 }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
