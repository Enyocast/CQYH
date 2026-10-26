{------------------------------------------------------------------------------}
{ SDOADx8Hook.pas for gwCore                                                   }
{------------------------------------------------------------------------------}
{ 单元描述: 实现让外部可以hook d3d8图形功能                                    } 
{ 单元作者: 盛大网络 谢斌 (xiebin@snda.com)                                    }
{ 参考文档:                                                                    }
{ 创建日期: 2009-11-19 10:09:15                                                }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx8Hook;

interface

uses Windows, Direct3D8;

const
  IID_ISDOADx8Hook: TGUID = '{C87C0531-B8EB-4D7B-A8B9-634E10B736B9}';
  IID_ISDOADx8AppHook: TGUID = '{69B736D9-1390-4018-89F0-B7B3FBD13093}';


type
  { dx8图形接口 }
  PSDOADx8Hook = ^ISDOADx8Hook;
  ISDOADx8Hook = interface(IUnknown)
    ['{C87C0531-B8EB-4D7B-A8B9-634E10B736B9}']
    { Hook d3d设备 }
    function Hook(Dev8: IDirect3DDevice8; HookGameWnd: HWND): HRESULT; stdcall;
    { unHook d3d设备 }
    function unHook(): HRESULT; stdcall;
  end;

implementation

end.
