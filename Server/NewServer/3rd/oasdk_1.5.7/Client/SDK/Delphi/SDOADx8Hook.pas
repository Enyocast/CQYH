{------------------------------------------------------------------------------}
{ SDOADx8Hook.pas for gwCore                                                   }
{------------------------------------------------------------------------------}
{ Unit description: Allows external applications to hook D3D8 graphics                                    }
{ Unit author: Shanda Network Xie Bin (xiebin@snda.com)                                    }
{ References:                                                                    }
{ Created: 2009-11-19 10:09:15                                                }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOADx8Hook;

interface

uses Windows, Direct3D8;

const
  IID_ISDOADx8Hook: TGUID = '{C87C0531-B8EB-4D7B-A8B9-634E10B736B9}';
  IID_ISDOADx8AppHook: TGUID = '{69B736D9-1390-4018-89F0-B7B3FBD13093}';


type
  { DX8 graphics interface }
  PSDOADx8Hook = ^ISDOADx8Hook;
  ISDOADx8Hook = interface(IUnknown)
    ['{C87C0531-B8EB-4D7B-A8B9-634E10B736B9}']
    { Hook the D3D device }
    function Hook(Dev8: IDirect3DDevice8; HookGameWnd: HWND): HRESULT; stdcall;
    { Unhook the D3D device }
    function unHook(): HRESULT; stdcall;
  end;

implementation

end.
