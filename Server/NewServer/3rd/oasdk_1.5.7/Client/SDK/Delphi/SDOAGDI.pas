{------------------------------------------------------------------------------}
{ SDOAGDI.pas for gwCore                                                       }
{------------------------------------------------------------------------------}
{ 单元描述:  GDI 图形引擎接口                                                  }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档:                                                                    }
{ 创建日期: 2009-9-03 13:55:01                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOAGDI;

interface

uses Windows;

const
  IID_ISDOAGDI: TGUID = '{85DE7C68-1D88-4FBF-AF20-6178813C8037}';
  IID_ISDOAGDIApp: TGUID = '{9793A409-4912-419A-81F7-A9F27E89929A}';

const
  SDOA_GDIMODE_DESKTOP = 0; // 绘制渲染到桌面上
  SDOA_GDIMODE_HOST    = 1; // 绘制到HOST的窗口上

type
  { GDI图形接口 }
  PSDOAGDI = ^ISDOAGDI;
  ISDOAGDI = interface(IUnknown)
    ['{85DE7C68-1D88-4FBF-AF20-6178813C8037}']
    { 初始化 GDI 设备 }
    function Initialize(AHostWnd: HWND; AMode: Integer): HRESULT; stdcall;
    // 渲染界面
    function Render(AWnd: HWND; ADC: HDC): HRESULT; stdcall;
    { 释放 GDI 相关资源 }
    function Finalize(AWnd: HWND): HRESULT; stdcall;
     { 传入消息 }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
