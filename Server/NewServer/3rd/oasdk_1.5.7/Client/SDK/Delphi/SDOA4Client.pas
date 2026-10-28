{------------------------------------------------------------------------------}
{ SDOA4Client.pas for gwCore                                                }
{------------------------------------------------------------------------------}
{ Unit description: External interface type definitions                                                   }
{ Unit author: Shanda Network IGW team                                                 }
{ References: IGWInterface.pas
            The original interface system is retained for compatibility and ease of use.
            Wrapped external types and interfaces are also defined; internal implementation may change,
            but the external interface must remain consistent.

  Important: this unit is not exposed directly and includes explanatory comments for maintenance.
            Remove comments about internal details before external release.

                                                                               }
{ Created: 2009-2-25 9:36:35                                                  }
{------------------------------------------------------------------------------}
{ Usage:                                                                    }
{------------------------------------------------------------------------------}
{ Revision history:                                                                    }
{------------------------------------------------------------------------------}
unit SDOA4Client;

interface

uses Windows;

const
  {
    SDOA_SDK_VERSION identifies the integration SDK version
  }
  SDOA_SDK_VERSION = $0200;

const
  SDOA_OK      = 0;
  SDOA_FALSE   = 1;
  SDOA_INSUFFICIENT_BUFFER = 122;  // Insufficient memory

  // Message sent after SDOA starts
  SDOA_WM_CLIENT_RUN     = $A604;  // WM_USER + $A204
  // Notifications sent by IGW to the game client
  SDOA_WM_CLIENT_NOTIFY  = $A610;  // WM_USER + $A210;
    // wParam: notification event ID; lParam: additional information, or 0 if absent
    SDOA_NOTIFY_SHOWLOGIN   =  1;  // Open the login dialog; lParam is the security token type
    SDOA_NOTIFY_LOGINCLICK  =  2;  // Login button clicked; lParam is the security token type
  // Notifications sent by the game client to IGW
  SDOA_WM_HOST_NOTIFY    = $A611;  // WM_USER + $A211;

  // Security token types
  SDOA_EKEY_NONE            =  0;  // No security token or static authentication
  SDOA_EKEY_D6              =  1;  // D6 security token
  SDOA_EKEY_A8              =  2;  // A8 security token (challenge code)
  SDOA_EKEY_ECARD           =  3;  // Security card
  SDOA_EKEY_USB             =  4;  // USB security token
  SDOA_EKEY_SIM             =  5;  // SIM security token

const
  IID_ISDOAApp: TGUID = '{C8187484-1C5F-48DF-8497-2136A72A5733}';
  IID_ISDOAApp2: TGUID = '{3F35136C-7061-4E69-BF3A-CC78D026F48F}';
  IID_ISDOAAppUtils: TGUID = '{1170C2F9-28AD-4EA8-8392-E9A219C8FF65}';
  IID_ISDOAClientService: TGUID = '{AF56D291-823A-41AA-85A0-EBE5C6163425}';
  IID_ISDOALoginByGame: TGUID = '{EEC79425-397C-4E5A-951C-3260BF97BBB3}';

const
  // Game type
  SDOA_RENDERTYPE_UNKNOWN            = $0;
  SDOA_RENDERTYPE_GDI                = $1;
  SDOA_RENDERTYPE_DDRAW              = $4;
  SDOA_RENDERTYPE_D3D7               = $8;
  SDOA_RENDERTYPE_D3D8               = $10;
  SDOA_RENDERTYPE_D3D9               = $20;
  SDOA_RENDERTYPE_D3D10              = $40;
  SDOA_RENDERTYPE_OPENGL             = $80;

const
  { External Screen state control }
  SDOA_SCREEN_NONE   = 0;      // Screen has not been created
  SDOA_SCREEN_NORMAL = 1;      // Normally displayed
  SDOA_SCREEN_MINI   = 2;      // Minimized

const
   { Internal IWidgetWindows state control }
  SDOA_WINDOWSSTATUS_NONE   = 0;      // Window has not been created
  SDOA_WINDOWSSTATUS_SHOW   = 1;      // Window is displayed
  SDOA_WINDOWSSTATUS_HIDE   = 2;      // Window is hidden
  // Window type
  SDOA_WINDOWSTYPE_NONE = 0;     // Unknown type
  SDOA_WINDOWSTYPE_TOOLBAR = 1;  // Toolbar
  SDOA_WINDOWSTYPE_WIDGET = 2;   // Widget window
  SDOA_WINDOWSTYPE_WINDOWS = 3;  // Normal window

  // Widget opening options
  SDOA_OPENWIDGET_DEFAULT     = 0;  // Default
  SDOA_OPENWIDGET_NOBARICON   = 1;  // Open the Widget without adding it to the toolbar

  // Constants used by SetSelfCursor
  SDOA_CURSOR_AUTO     = 0;    // Automatically detect whether to draw the cursor
  SDOA_CURSOR_SELF     = 1;    // Always draw the cursor
  SDOA_CURSOR_HIDESELF = 2;    // Never draw the cursor

// Login method
  SDOA_LOGINMETHOD_SSO  =      0;   // Login method: SSO
  SDOA_LOGINMETHOD_SDO  =      1;   // Login method: SDO(CAS)

// Login state
  SDOA_LOGINSTATE_UNKNOWN    = -1;  // Unknown: invalid parameter or error retrieving state
  SDOA_LOGINSTATE_NONE       = 0;   // Login has not been called
  SDOA_LOGINSTATE_OK         = 1;   // Login succeeded
  SDOA_LOGINSTATE_CONNECTING = 2;   // Login in progress
  SDOA_LOGINSTATE_FAILED     = 3;   // Login failed
  SDOA_LOGINSTATE_LOGOUT     = 4;   // Logged out

// Quanquan toolbar expansion mode
  SDOA_BARMODE_ICONBOTTOM = 0;   // Toolbar below the Quanquan icon
  SDOA_BARMODE_ICONTOP    = 1;   // Toolbar above the Quanquan icon



type
  PAppInfo = ^TAppInfo;
  TAppInfo = packed record
    Size       : DWORD;       // = SizeOf(TAppInfo)
    AppID        : LongInt;     // Shanda unified game ID
    AppName      : PWideChar;   // Game name
    AppVer       : PWideChar;   // Game version
    RenderType   : LongInt;     // Game type (RENDERTYPE_UNKNOWN..RENDERTYPE_OPENGL)
    MaxUser      : LongInt;     // Maximum simultaneous players on one machine (usually 1; for example, 2 for KOF)
    AreaId       : Integer;     // Game area ID (pass -1 if unavailable)
    GroupId      : Integer;     // Game group ID (pass -1 if unavailable)
  end;// TAppInfo
    
type
  PRoleInfo = ^TRoleInfo;
  TRoleInfo = packed record
    Size       : DWORD;                   // = SizeOf(TUserDetailInfo)
    RoleName     : PWideChar;             // Nickname
    Sex          : LongInt;               // Sex (0: female; 1: male)
    // more
  end;
  
  PSDOAWinProperty = ^TSDOAWinProperty;
  TSDOAWinProperty = packed record
    WinType: integer;          // Window type (identification only)
    Status: integer;           // Window state
    Left: integer;
    Top: integer;
    Width: integer;
    Height: integer;
  end;// TSDOAWinProperty

  PLoginResult_V1 = ^TLoginResult_V1;
  TLoginResult_V1 = packed record
    Size           : DWORD;        // = SizeOf(TLoginResult), allowing future extensions
    SessionId      : PAnsiChar;    // Token used for backend validation
    SndaId         : PAnsiChar;    // User ID
    IdentityState  : PAnsiChar;    // Adult indicator: 0 minor, 1 adult
    Appendix       : PAnsiChar;    // Reserved additional field
  end;

  PLoginResult_V2 = ^TLoginResult_V2;
  TLoginResult_V2 = packed record
    Size           : DWORD;        // = SizeOf(TLoginResult), allowing future extensions
    SessionId      : PAnsiChar;    // Token used for backend validation
    SndaId         : PAnsiChar;    // User ID
    IdentityState  : PAnsiChar;    // Adult indicator: 0 minor, 1 adult
    Appendix       : PAnsiChar;    // Reserved additional field
    // Added 2009-09-02
    Additional     : PAnsiChar;    // Additional information to pass back to LoginDirect
  end;

  PLoginResult = ^TLoginResult;
  TLoginResult = TLoginResult_V2;

  PLoginMessage = ^TLoginMessage;
  TLoginMessage = packed record
    dwSize       : DWORD;
    nErrorCode   : Integer;        // Login error code; 0 indicates an informational message
    pbstrTitle   : PPWideChar;     // Message title; SysReallocString may modify it. IGW frees the allocated memory with SysFreeString after the callback.
    pbstrContent : PPWideChar;     // Message text; SysReallocString may modify it. IGW frees the allocated memory with SysFreeString after the callback.
  end;

  PLoginDataPacket = ^TLoginDataPacket;
  TLoginDataPacket = packed record
    dwSize       : DWORD;
    DataPacket   : PWideChar;      // Login data packet to send to LoginServer
    Appendix     : PWideChar;      // Reserved additional field
  end;

const
  // ErrorCode values for the TLoginCallback callback
  SDOA_ERRORCODE_OK              = 0;    // Login succeeded
  SDOA_ERRORCODE_CANCEL          = -1;   // The user canceled the login dialog
  SDOA_ERRORCODE_UILOST          = -2;   // The dialog UI file is missing or invalid
  SDOA_ERRORCODE_FAILED          = -3;   // Login failed
  SDOA_ERRORCODE_UNKNOWN         = -4;   // Unknown error
  SDOA_ERRORCODE_INVALIDPARAM    = -5;   // Invalid parameter
  SDOA_ERRORCODE_UNEXCEPT        = -6;   // Unknown exception
  SDOA_ERRORCODE_ALREAYEXISTS    = -7;   // Already exists
  SDOA_ERRORCODE_SHOWMESSAGE     = -10;  // Display a message dialog
  SDOA_ERRORCODE_LOGINPACKET     = -11;  // Login using a game data packet

type
  //============================================================================
  // Login callback
  // ErrorCode:     Login error code
  // LoginResult:   Login result; valid only when ErrorCode = SDOA_ERRORCODE_OK
  // UserData:      User data passed to ShowLoginDialog
  // Reserved:      Reserved and unused; currently always 0 (not the Reserved argument passed to ShowLoginDialog)
  // Return value:        True closes the dialog; False leaves it open
  //
  // 2009.03.30
  // When ErrorCode = ERRORCODE_SHOWMESSAGE, Reserved returns a PLoginMessage result
  // If True is returned, IGW does not show the dialog and the game may show its own prompt
  // If False is returned, IGW shows the dialog; SysReallocString can modify Title and Content for a custom error message
  //              Note: IGW frees the allocated memory with SysFreeString after the callback
  //
  // 2009.12.31
  // When ErrorCode = SDOA_ERRORCODE_LOGINPACKET, Reserved returns a PLoginDataPacket structure

  TLoginCallback = function(ErrorCode: Integer; LoginResult: PLoginResult;
    UserData: Integer; Reserved: Integer): BOOL; stdcall;

const
  // ShowLoginDialog Reserved parameter options
  SDOA_LOGIN_DEFAULT             = 0;    // Default login mode
  SDOA_LOGIN_BYGAME              = 5;    // Game login mode

type
  { Base SDOA application interface }
  PSDOAApp = ^ISDOAApp;
  ISDOAApp = interface(IUnknown)
    ['{C8187484-1C5F-48DF-8497-2136A72A5733}']
    // Show the login dialog
    function ShowLoginDialog(Callback: TLoginCallback; UserData: Integer;
                             Reserved: Integer): Integer; stdcall;
    procedure ModifyAppInfo(const AppInfo: PAppInfo); stdcall;
    procedure Logout(); stdcall;
    function GetLoginState(LoginMethod: Integer): Integer; stdcall;
    procedure SetRoleInfo(const RoleInfo: PRoleInfo); stdcall;

    // Show the top-up dialog
    function ShowPaymentDialog(ASrc: PWideChar): Integer; stdcall;

    // SDOA UI configuration
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

    // Functions
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

  // ISDOAApp2  New interface added 2009-09-02
  PSDOAApp2 = ^ISDOAApp2;
  ISDOAApp2 = interface(ISDOAApp)
    ['{3F35136C-7061-4E69-BF3A-CC78D026F48F}']
    function LoginDirect(SessionId, Additional: PAnsiChar; Reserved: Integer): Integer; stdcall;
    function GetClientSignature(Indication: PWideChar; out Signature: WideString): Integer; stdcall;
  end;
          
  PSDOALoginByGame = ^ISDOALoginByGame;
  ISDOALoginByGame = interface(IUnknown)
    ['{EEC79425-397C-4E5A-951C-3260BF97BBB3}']
    { Set OrderId }
    function SetOrderId(const OrderId: PWideChar; Reserved: Integer): Integer; stdcall;
    { Report the login result }
    function NotifyLoginResult(const DataPacket: PWideChar; Reserved: Integer): Integer; stdcall;
    { Report an error }
    function NotifyError(const AErrorMsg: PWideChar; Reserved: Integer): Integer; stdcall;
  end;

type
  //============================================================================
  // Valid volume is 0-100 (0 is silent and 100 is maximum)
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
    procedure Close; stdcall;  //Notify that this channel can close.
    function  Get_ChannelType(var ChannelType: PChar; BufferLen:DWORD):Integer; // max 64
      stdcall;
  end;
  TCreateChannel = function (ChannelType: PChar; out Channel: ISDOACommonChannel): LongBool; stdcall;

  PSDOAAppUtils = ^ISDOAAppUtils;
  ISDOAAppUtils = interface(IUnknown)
    ['{1170C2F9-28AD-4EA8-8392-E9A219C8FF65}']
    // Audio control
    // Set audio control callbacks
    procedure SetAudioSetting(AGetAudioSoundVolume: TGetAudioSoundVolume;
                              ASetAudioSoundVolume: TSetAudioSoundVolume;
                              AGetAudioEffectVolume: TGetAudioEffectVolume;
                              ASetAudioEffectVolume: TSetAudioEffectVolume); stdcall;
    // Notify SDOA that game audio has changed
    procedure NodifyAudioChanged(); stdcall;

    // Set the data channel creation callback
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
  { Use SDOA_SDK_VERSION for the dwSdkVersion argument to igwInitialize }
  TigwInitialize = function(dwSdkVersion: DWORD; const pAppInfo: PAppInfo): Integer; stdcall;
  { Get an interface by ID }
  TigwGetModule = function(const IID: TGUID; out Intf): Boolean; stdcall;
  TigwTerminal = function: Integer; stdcall;


implementation

end.
