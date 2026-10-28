{------------------------------------------------------------------------------}
{ SDOADx9Hook.pas for gwCore                                                   }
{------------------------------------------------------------------------------}
{ Unit description:                                                                    }
{ Unit author: Shanda Network Xie Bin (xiebin@snda.com)                                    }
{ References:                                                                    }
{ Created: 2009-11-13 14:28:41                                                }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx9Hook;

interface

uses Windows, Direct3D9;

const
  IID_ISDOADx9Hook: TGUID = '{2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3}';
  IID_ISDOADx9AppHook: TGUID = '{B8BB82CD-1F14-4358-8FAC-04807645813F}';


type
  { DX9 graphics interface }
  PSDOADx9Hook = ^ISDOADx9Hook;
  ISDOADx9Hook = interface(IUnknown)
    ['{2449B1FC-DDD6-44CB-AD23-CD8BFAB14CA3}']
    { Hook the D3D device }
    function Hook(Dev9: IDirect3DDevice9; HookGameWnd: HWND): HRESULT; stdcall;
    { Unhook the D3D device }
    function unHook(): HRESULT; stdcall;
  end;

implementation

end.
