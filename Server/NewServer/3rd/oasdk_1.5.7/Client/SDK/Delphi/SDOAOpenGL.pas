{------------------------------------------------------------------------------}
{ SDOAOpenGL.pas for gwCore                                                    }
{------------------------------------------------------------------------------}
{ 单元描述:  外部OpenGL图形引擎接口                                            }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档:                                                                    }
{ 创建日期: 2009-2-25 13:55:36                                                 }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
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
    { 初始化图形系统 }
    function Initialize(DC: HDC; RC: HGLRC; AHookWnd: Boolean): HRESULT; stdcall;
    { 渲染 }
    function Render(): HRESULT; stdcall;
    { 释放图形系统相关资源 }
    function Finalize(): HRESULT; stdcall;
     { 传入消息 }
    function OnWindowProc(hWnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM;
      var lResult: LRESULT): HRESULT; stdcall;
  end;

implementation

end.
