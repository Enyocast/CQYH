{------------------------------------------------------------------------------}
{ SDOA4Client.pas for gwCore                                                }
{------------------------------------------------------------------------------}
{ 单元描述: 对外接口类型定义                                                   }
{ 单元作者: 盛大网络 IGW项目组                                                 }
{ 参考文档: IGWInterface.pas
            为使外部接口更易理解，易使用，这里保留原系统接口体系兼容
            同时定义包装一套对外使用的类型和接口，将来内部体系变化，
            但对外接口必须一致

  严重注意：该单元不直接对外，内容会有方便理解的注释，便于代码维护
            对外发布时去掉内部细节相关注释

                                                                               }
{ 创建日期: 2009-2-25 9:36:35                                                  }
{------------------------------------------------------------------------------}
{ 使用说明:                                                                    }
{------------------------------------------------------------------------------}
{ 修改历史:                                                                    }
{------------------------------------------------------------------------------}
unit SDOA4Client;

interface

uses Windows;

const
  {
    SDOA_SDK_VERSION 表示一套接入的SDK版本号
  }
  SDOA_SDK_VERSION = $0200;

const
  SDOA_OK      = 0;
  SDOA_FALSE   = 1;
  SDOA_INSUFFICIENT_BUFFER = 122;  // 内存不足

  // SDOA开始工作后发出的消息
  SDOA_WM_CLIENT_RUN     = $A604;  // WM_USER + $A204
  // IGW发送给游戏客户端的通知消息
  SDOA_WM_CLIENT_NOTIFY  = $A610;  // WM_USER + $A210;
    // wParam: 通知事件ID; lParam: 扩展信息，无内容为0
    SDOA_NOTIFY_SHOWLOGIN   =  1;  // 呼出登录对话框，lParam为密宝类型
    SDOA_NOTIFY_LOGINCLICK  =  2;  // 点击了“登录”按钮，lParam为密宝类型
  // 游戏客户端发送给IGW的通知消息
  SDOA_WM_HOST_NOTIFY    = $A611;  // WM_USER + $A211;

  // 密宝类型
  SDOA_EKEY_NONE            =  0;  // 无密宝或静态认证
  SDOA_EKEY_D6              =  1;  // D6密宝
  SDOA_EKEY_A8              =  2;  // A8密宝(挑战码)
  SDOA_EKEY_ECARD           =  3;  // 安全卡
  SDOA_EKEY_USB             =  4;  // USB密宝
  SDOA_EKEY_SIM             =  5;  // SIM卡密宝

const
  IID_ISDOAApp: TGUID = '{C8187484-1C5F-48DF-8497-2136A72A5733}';
  IID_ISDOAApp2: TGUID = '{3F35136C-7061-4E69-BF3A-CC78D026F48F}';
  IID_ISDOAAppUtils: TGUID = '{1170C2F9-28AD-4EA8-8392-E9A219C8FF65}';
  IID_ISDOAClientService: TGUID = '{AF56D291-823A-41AA-85A0-EBE5C6163425}';
  IID_ISDOALoginByGame: TGUID = '{EEC79425-397C-4E5A-951C-3260BF97BBB3}';

const
  // 游戏类型
  SDOA_RENDERTYPE_UNKNOWN            = $0;
  SDOA_RENDERTYPE_GDI                = $1;
  SDOA_RENDERTYPE_DDRAW              = $4;
  SDOA_RENDERTYPE_D3D7               = $8;
  SDOA_RENDERTYPE_D3D8               = $10;
  SDOA_RENDERTYPE_D3D9               = $20;
  SDOA_RENDERTYPE_D3D10              = $40;
  SDOA_RENDERTYPE_OPENGL             = $80;

const
  { 外部控制Screen状态 }
  SDOA_SCREEN_NONE   = 0;      // Screen没有被创建
  SDOA_SCREEN_NORMAL = 1;      // 正常显示状态
  SDOA_SCREEN_MINI   = 2;      // 最小化状态

const
   { 内部IWidgetWindows状态控制 }
  SDOA_WINDOWSSTATUS_NONE   = 0;      // 窗口没有被创建
  SDOA_WINDOWSSTATUS_SHOW   = 1;      // 窗口显示状态
  SDOA_WINDOWSSTATUS_HIDE   = 2;      // 窗口隐藏
  // 窗口类型
  SDOA_WINDOWSTYPE_NONE = 0;     // 未知类型
  SDOA_WINDOWSTYPE_TOOLBAR = 1;  // 工具栏
  SDOA_WINDOWSTYPE_WIDGET = 2;   // Widget窗口
  SDOA_WINDOWSTYPE_WINDOWS = 3;  // 普通窗口

  // 打开Widget的选项
  SDOA_OPENWIDGET_DEFAULT     = 0;  // 默认
  SDOA_OPENWIDGET_NOBARICON   = 1;  // 仅打开Widget，不自动添加到工具栏上

  // 接口SetSelfCursor用到的常量
  SDOA_CURSOR_AUTO     = 0;    // 自动检测是否自绘鼠标指针
  SDOA_CURSOR_SELF     = 1;    // 始终自绘制鼠标指针
  SDOA_CURSOR_HIDESELF = 2;    // 始终不自绘制鼠标指针

// 登录方法
  SDOA_LOGINMETHOD_SSO  =      0;   // 登录方法：SSO
  SDOA_LOGINMETHOD_SDO  =      1;   // 登录方法：SDO(CAS)

// 登录状态
  SDOA_LOGINSTATE_UNKNOWN    = -1;  // 未知，参数不正确或获取状态异常
  SDOA_LOGINSTATE_NONE       = 0;   // 还没有调用过登录方法
  SDOA_LOGINSTATE_OK         = 1;   // 登录成功
  SDOA_LOGINSTATE_CONNECTING = 2;   // 正在登录
  SDOA_LOGINSTATE_FAILED     = 3;   // 登录失败
  SDOA_LOGINSTATE_LOGOUT     = 4;   // 已登出

// 圈圈工具条展开模式
  SDOA_BARMODE_ICONBOTTOM = 0;   // 工具条在圈圈图标下面
  SDOA_BARMODE_ICONTOP    = 1;   // 工具条在圈圈图标上面



type
  PAppInfo = ^TAppInfo;
  TAppInfo = packed record
    Size       : DWORD;       // = SizeOf(TAppInfo)
    AppID        : LongInt;     // 盛大统一游戏ID
    AppName      : PWideChar;   // 游戏名称
    AppVer       : PWideChar;   // 游戏版本
    RenderType   : LongInt;     // 游戏类型            (取值 RENDERTYPE_UNKNOWN..RENDERTYPE_OPENGL)
    MaxUser      : LongInt;     // 游戏可同时在一台机器上游戏的最大人数（通常为1，例如:KOF应该是2）
    AreaId       : Integer;     // 游戏区ID	(注意：不可用时传-1)
    GroupId      : Integer;     // 游戏组ID  (注意：不可用时传-1)
  end;// TAppInfo
    
type
  PRoleInfo = ^TRoleInfo;
  TRoleInfo = packed record
    Size       : DWORD;                   // = SizeOf(TUserDetailInfo)
    RoleName     : PWideChar;             // 昵称
    Sex          : LongInt;               // 性别(0: 女; 1: 男)
    // more
  end;
  
  PSDOAWinProperty = ^TSDOAWinProperty;
  TSDOAWinProperty = packed record
    WinType: integer;          // 窗口类型(只用于标识)
    Status: integer;           // 窗口状态
    Left: integer;
    Top: integer;
    Width: integer;
    Height: integer;
  end;// TSDOAWinProperty

  PLoginResult_V1 = ^TLoginResult_V1;
  TLoginResult_V1 = packed record
    Size           : DWORD;        // = SizeOf(TLoginResult)，为以后扩充提供可能
    SessionId      : PAnsiChar;    // 用于后台验证的token串
    SndaId         : PAnsiChar;    // 用户ID
    IdentityState  : PAnsiChar;    // 是否成年标识，0未成年，1成年
    Appendix       : PAnsiChar;    // 附加字段，保留
  end;

  PLoginResult_V2 = ^TLoginResult_V2;
  TLoginResult_V2 = packed record
    Size           : DWORD;        // = SizeOf(TLoginResult)，为以后扩充提供可能
    SessionId      : PAnsiChar;    // 用于后台验证的token串
    SndaId         : PAnsiChar;    // 用户ID
    IdentityState  : PAnsiChar;    // 是否成年标识，0未成年，1成年
    Appendix       : PAnsiChar;    // 附加字段，保留
    // 2009.09.02新增
    Additional     : PAnsiChar;    // 附加信息，需要调用LoginDirect时传回
  end;

  PLoginResult = ^TLoginResult;
  TLoginResult = TLoginResult_V2;

  PLoginMessage = ^TLoginMessage;
  TLoginMessage = packed record
    dwSize       : DWORD;
    nErrorCode   : Integer;        // 登录错误码，为0时仅提示信息
    pbstrTitle   : PPWideChar;     // 提示标题，可以调用SysReallocString修改其中的内容，注意，回调结果后IGW将调用SysFreeString释放已分配的内存
    pbstrContent : PPWideChar;     // 提示内容，可以调用SysReallocString修改其中的内容，注意，回调结果后IGW将调用SysFreeString释放已分配的内存
  end;

  PLoginDataPacket = ^TLoginDataPacket;
  TLoginDataPacket = packed record
    dwSize       : DWORD;
    DataPacket   : PWideChar;      // 需要发送给LoginServer登录用的数据包
    Appendix     : PWideChar;      // 附加字段，保留
  end;

const
  // TLoginCallback中回调参数ErrorCode值定义
  SDOA_ERRORCODE_OK              = 0;    // 登录成功
  SDOA_ERRORCODE_CANCEL          = -1;   // 用户按取消关闭了登录对话框
  SDOA_ERRORCODE_UILOST          = -2;   // 加载对话框UI文件缺失或无效
  SDOA_ERRORCODE_FAILED          = -3;   // 登录失败
  SDOA_ERRORCODE_UNKNOWN         = -4;   // 未知错误
  SDOA_ERRORCODE_INVALIDPARAM    = -5;   // 参数无效
  SDOA_ERRORCODE_UNEXCEPT        = -6;   // 未知异常
  SDOA_ERRORCODE_ALREAYEXISTS    = -7;   // 已经存在
  SDOA_ERRORCODE_SHOWMESSAGE     = -10;  // 显示对示对话框
  SDOA_ERRORCODE_LOGINPACKET     = -11;  // 通过游戏登录数据包

type  
  //============================================================================
  // 登录回调函数
  // ErrorCode:     登录返回错误代码
  // LoginResult:   登录返回结果，只在 ErrorCode = SDOA_ERRORCODE_OK 时才有效
  // UserData:      在调用ShowLoginDialog时传入的用户数据
  // Reserved:      保留，暂不使用，目前总是为0(不等于ShowLoginDialog中传入的Reserved参数)
  // 返回值:        为True将关闭对话框，为False不关闭
  //
  // 2009.03.30
  // 扩展功能，当ErrorCode = ERRORCODE_SHOWMESSAGE时，Reserved返回PLoginMessage结果
  // 返回True时，IGW将不再弹出对话框，游戏可以自行弹出提示对话框等
  // 返回False时，IGW继续弹出对话框，可以调用SysReallocString修改Title,Content其中的内容，以便游戏显示自定义的错误提示
  //              注意：回调结果后IGW将调用SysFreeString释放已分配的内存
  //
  // 2009.12.31
  // 当 ErrorCode = SDOA_ERRORCODE_LOGINPACKET 时, Reserved 返回 PLoginDataPacket 结构

  TLoginCallback = function(ErrorCode: Integer; LoginResult: PLoginResult;
    UserData: Integer; Reserved: Integer): BOOL; stdcall;

const
  // ShowLoginDialog Reserved参数选项
  SDOA_LOGIN_DEFAULT             = 0;    // 默认登录模式
  SDOA_LOGIN_BYGAME              = 5;    // 通过游戏登录模式

type
  { 整个SDOA基础应用接口 }
  PSDOAApp = ^ISDOAApp;
  ISDOAApp = interface(IUnknown)
    ['{C8187484-1C5F-48DF-8497-2136A72A5733}']
    // 显示登录对话框
    function ShowLoginDialog(Callback: TLoginCallback; UserData: Integer;
                             Reserved: Integer): Integer; stdcall;
    procedure ModifyAppInfo(const AppInfo: PAppInfo); stdcall;
    procedure Logout(); stdcall;
    function GetLoginState(LoginMethod: Integer): Integer; stdcall;
    procedure SetRoleInfo(const RoleInfo: PRoleInfo); stdcall;

    // 显示充值对话框 
    function ShowPaymentDialog(ASrc: PWideChar): Integer; stdcall;

    // 配置SDOA UI相关
    function GetScreenStatus(): integer; stdcall;
    procedure SetScreenStatus(Value: integer); stdcall;
    function GetScreenEnabled(): boolean; stdcall;
    procedure SetScreenEnabled(Value: boolean); stdcall;
    function GetTaskBarPosition(P: PPoint): boolean; stdcall;
    function SetTaskBarPosition(const P: PPoint): boolean; stdcall;
    function GetFocus(): boolean; stdcall;
    procedure SetFocus(Value: Boolean); stdcall;
    function HasUI(const P: PPoint): boolean; stdcall;
    function GetTaskBarMode(): Integer; stdcall;
    procedure SetTaskBarMode(iBarMode: integer); stdcall;
    function GetSelfCursor(): Integer; stdcall;
    procedure SetSelfCursor(Value: Integer); stdcall;

    // 功能相关
    function OpenWidget(AWidgetNameSpace: PWideChar): integer; stdcall;
    function OpenWidgetEx(AWidgetNameSpace, AParam: PWideChar;
                          Flag: Cardinal): integer; stdcall;
    function CloseWidget(AWidgetNameSpace: PWideChar): integer; stdcall;
    function ExecuteWidget(AWidgetNameSpaceOrGUID: PWideChar;
                           AParam: PWideChar): Integer; stdcall;
    function WidgetExists(AWidgetNameSpaceOrGUID: PWideChar): Integer; stdcall;
    
    function OpenWindow(WinType, WinName, Src: PWideChar;
      Left, Top, Width, Height: Integer; Mode: PWideChar): Integer; stdcall;
    function CloseWindow(WinName: PWideChar): Integer; stdcall;

    function GetWinProperty(AWinName: PWideChar; AWinProperty: PSDOAWinProperty): integer; stdcall;
    function SetWinProperty(AWinName: PWideChar; AWinProperty: PSDOAWinProperty): integer; stdcall;
  end;

  // ISDOAApp2  2009.09.02增加新接口
  PSDOAApp2 = ^ISDOAApp2;
  ISDOAApp2 = interface(ISDOAApp)
    ['{3F35136C-7061-4E69-BF3A-CC78D026F48F}']
    function LoginDirect(SessionId, Additional: PAnsiChar; Reserved: Integer): Integer; stdcall;
    function GetClientSignature(Indication: PWideChar; out Signature: WideString): Integer; stdcall;
  end;
          
  PSDOALoginByGame = ^ISDOALoginByGame;
  ISDOALoginByGame = interface(IUnknown)
    ['{EEC79425-397C-4E5A-951C-3260BF97BBB3}']
    { 设置OrderId }
    function SetOrderId(const OrderId: PWideChar; Reserved: Integer): Integer; stdcall;
    { 通知登录结果 }
    function NotifyLoginResult(const DataPacket: PWideChar; Reserved: Integer): Integer; stdcall;
    { 通知错误 }
    function NotifyError(const AErrorMsg: PWideChar; Reserved: Integer): Integer; stdcall;
  end;

type
  //============================================================================
  // 音量值的有效范围在0-100（0为无声，100为最大）
  TGetAudioSoundVolume  = function(): DWORD; stdcall;
  TGetAudioEffectVolume = function(): DWORD; stdcall;
  TSetAudioSoundVolume  = procedure (NewVolume: DWORD); stdcall;
  TSetAudioEffectVolume = procedure (NewVolume: DWORD); stdcall;

type
  ISDOACommonChannel = interface
    ['{45FBC99C-E36E-4413-B27D-F268E192747E}']
    procedure SendData(const Request: PWideChar; out Response: PWideChar); stdcall;
    procedure Set_RevertChannel(Reverter: ISDOACommonChannel); stdcall;
    function  Get_RevertChannel: ISDOACommonChannel; stdcall;
    procedure Close; stdcall;  //通知这个管道可以关闭了。
    function  Get_ChannelType(var ChannelType: PChar; BufferLen:DWORD):Integer; // max 64
      stdcall;
  end;
  TCreateChannel = function (ChannelType: PChar; out Channel: ISDOACommonChannel): LongBool; stdcall;

  PSDOAAppUtils = ^ISDOAAppUtils;
  ISDOAAppUtils = interface(IUnknown)
    ['{1170C2F9-28AD-4EA8-8392-E9A219C8FF65}']
    // 声音控制
    // 设置声音控制相关回调
    procedure SetAudioSetting(AGetAudioSoundVolume: TGetAudioSoundVolume;
                              ASetAudioSoundVolume: TSetAudioSoundVolume;
                              AGetAudioEffectVolume: TGetAudioEffectVolume;
                              ASetAudioEffectVolume: TSetAudioEffectVolume); stdcall;
    // 通知SDOA游戏声音有变化
    procedure NodifyAudioChanged(); stdcall;

    // 设置创建数据通道的回调
    procedure SetCreateChannelCallback(const CreateChannel: TCreateChannel); stdcall;
  end;

  TQueryCallback = procedure(RetCode: Integer; UserData: Integer); stdcall;
  
  PSDOAClientService = ^ISDOAClientService;
  ISDOAClientService = interface(IUnknown)
    ['{AF56D291-823A-41AA-85A0-EBE5C6163425}']
    function SetValue(const Key: WideString; const Value: WideString): Integer; stdcall;
    function Query(const Service: WideString): Integer; stdcall;
    function AsyncQuery(const Service: WideString; Callback: TQueryCallback; UserData: Integer): Integer; stdcall;
    function GetValue(const Key: WideString; out Value: WideString): Integer; stdcall;
  end;


type
  { 注意igwInitialize中dwSdkVersion参数使用常量 SDOA_SDK_VERSION }
  TigwInitialize = function(dwSdkVersion: DWORD; const pAppInfo: PAppInfo): Integer; stdcall;
  { 接口ID得到接口 }
  TigwGetModule = function(const IID: TGUID; out Intf): Boolean; stdcall;
  TigwTerminal = function: Integer; stdcall;


implementation

end.
