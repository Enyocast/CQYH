{------------------------------------------------------------------------------}
{ SDOADx8.pas for gwCore                                                      }
{------------------------------------------------------------------------------}
{ 单元描述:  外部dx8图形引擎接口                                               }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档:                                                                    }
{ 创建日期: 2009-2-25 13:55:25                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
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
   { 初始化d3d设备 }
    function Initialize(Dev8: IDirect3DDevice8;
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
