{------------------------------------------------------------------------------}
{ SDOADx9Hook.pas for gwCore                                                   }
{------------------------------------------------------------------------------}
{ 单元描述:                                                                    }
{ 单元作者: 盛大网络 谢斌 (xiebin@snda.com)                                    }
{ 参考文档:                                                                    }
{ 创建日期: 2009-11-13 14:28:41                                                }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx9Hook;

interface

uses Windows, Direct3D9;

const
  IID_ISDOADx9Hook: TGUID = '{2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3}';
  IID_ISDOADx9AppHook: TGUID = '{B8BB82CD-1F14-4358-8FAC-04807645813F}';


type
  { dx9图形接口 }
  PSDOADx9Hook = ^ISDOADx9Hook;
  ISDOADx9Hook = interface(IUnknown)
    ['{2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3}']
    { Hook d3d设备 }
    function Hook(Dev9: IDirect3DDevice9; HookGameWnd: HWND): HRESULT; stdcall;
    { unHook d3d设备 }
    function unHook(): HRESULT; stdcall;
  end;

implementation

end.
