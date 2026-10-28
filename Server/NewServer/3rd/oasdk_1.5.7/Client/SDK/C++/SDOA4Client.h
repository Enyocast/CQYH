#ifndef SDOA4CLIENT_H
#define SDOA4CLIENT_H


#include <objbase.h>
#include "windows.h"

#pragma pack(push,1)

// SDOA_SDK_VERSION identifies the integrated SDK version
#define SDOA_SDK_VERSION                 0x0200

// SDOA return values
#define SDOA_OK                      0
#define SDOA_FALSE                   1

// Out of memory
#define SDOA_INSUFFICIENT_BUFFER     122  

// Messages sent after SDOA starts
#define SDOA_WM_CLIENT_RUN			0xA604  // WM_USER + 0xA204
// Notification sent by IGW to the game client
#define SDOA_WM_CLIENT_NOTIFY		0xA610  // WM_USER + 0xA210
// wParam: notification event ID; lParam: additional information, or 0 if absent
#define SDOA_NOTIFY_SHOWLOGIN     1    // Show the login dialog
#define SDOA_NOTIFY_LOGINCLICK    2    // Login button clicked
// Notification sent by the game client to IGW
#define SDOA_WM_HOST_NOTIFY			0xA611	// WM_USER + 0xA211


// Game graphics engine type
#define SDOA_RENDERTYPE_UNKNOWN             0x00
#define SDOA_RENDERTYPE_GDI                 0x01
#define SDOA_RENDERTYPE_DDRAW               0x04
#define SDOA_RENDERTYPE_D3D7                0x08
#define SDOA_RENDERTYPE_D3D8                0x10
#define SDOA_RENDERTYPE_D3D9                0x20
#define SDOA_RENDERTYPE_D3D10               0x40
#define SDOA_RENDERTYPE_OPENGL              0x80

// Externally controlled screen state
#define SDOA_SCREEN_NONE				0		// Screen has not been created
#define SDOA_SCREEN_NORMAL				1		// Normally displayed
#define SDOA_SCREEN_MINI				2		// Minimized


// Internal IWidgetWindows state control
#define SDOA_WINDOWSSTATUS_NONE			0		// Window has not been created
#define SDOA_WINDOWSSTATUS_SHOW			1		// Window is visible
#define SDOA_WINDOWSSTATUS_HIDE			2		// Window is hidden
// Window type
#define SDOA_WINDOWSTYPE_NONE		0       // Unknown type
#define SDOA_WINDOWSTYPE_TOOLBAR	1		// Toolbar
#define SDOA_WINDOWSTYPE_WIDGET		2		// Widget window
#define SDOA_WINDOWSTYPE_WINDOWS	3		// Normal window

// Widget opening options
#define SDOA_OPENWIDGET_DEFAULT			0		// Default
#define SDOA_OPENWIDGET_NOBARICON		1		// Open the widget without automatically adding it to the toolbar

// Constants used by SetSelfCursor
#define SDOA_CURSOR_AUTO		0	// Automatically detect whether to draw the cursor
#define SDOA_CURSOR_SELF		1	// Always draw the cursor
#define SDOA_CURSOR_HIDESELF	2	// Never draw the cursor

// Login method
#define SDOA_LOGINMETHOD_SSO        0   // Login method: SSO
#define SDOA_LOGINMETHOD_SDO        1   // Login method: SDO (CAS)

// Login state
#define SDOA_LOGINSTATE_UNKNOWN     -1  // Unknown: invalid parameter or error getting state
#define SDOA_LOGINSTATE_NONE        0   // Login has not been called
#define SDOA_LOGINSTATE_OK          1   // Login succeeded
#define SDOA_LOGINSTATE_CONNECTING  2   // Logging in
#define SDOA_LOGINSTATE_FAILED      3   // Login failed
#define SDOA_LOGINSTATE_LOGOUT      4   // Logged out

// QuanQuan toolbar expansion mode
#define SDOA_BARMODE_ICONBOTTOM		0   // Toolbar below the QuanQuan icon
#define SDOA_BARMODE_ICONTOP		1   // Toolbar above the QuanQuan icon

struct AppInfo {
	DWORD		cbSize;				// = sizeof(AppInfo)
	int			nAppID;				// Shanda unified game ID
	LPCWSTR		pwcsAppName;		// Game name
	LPCWSTR		pwcsAppVer;		   	// Game version
	int			nRenderType;		// Game graphics engine type (SDOA_RENDERTYPE_UNKNOWN..SDOA_RENDERTYPE_OPENGL)
	int			nMaxUser;			// Maximum simultaneous players on one machine (usually 1; KOF uses 2)
	int			nAreaId;			// Game area ID (pass -1 when unavailable)
	int			nGroupId;           // Game group ID (pass -1 when unavailable)
};


struct RoleInfo{
	DWORD		cbSize;                 // sizeof(RoleInfo)
	LPCWSTR		pwcsRoleName;			// Nickname
	int			nSex;                   // Gender (0: female; 1: male)
	// more
};

struct SDOAWinProperty{
	int nWinType;				// Window type (identification only; setting has no effect)
	int nStatus;				// Window state
	// Position and dimensions follow
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;	
};


struct LoginResult {
	DWORD  cbSize;			// sizeof(LoginResult), allowing future extension
	LPCSTR szSessionId;		// Token string for backend validation
	LPCSTR szSndaid;		// User ID
	LPCSTR szIdentityState;	// Adult flag: 0 minor, 1 adult
	LPCSTR szAppendix;		// Additional field, reserved
	// Added 2009-09-02
	LPCSTR szAdditional;    // Additional information to pass back to LoginDirect
};

 struct LoginMessage {
   DWORD  dwSize;
   int    nErrorCode;   // Login component error code for reference; use pbstrContent for details
   BSTR*  pbstrTitle;	// Message title; use SysReallocString to modify it. IGW calls SysFreeString after the callback to release allocated memory.
   BSTR*  pbstrContent;	// Message content; use SysReallocString to modify it. IGW calls SysFreeString after the callback to release allocated memory.
 };

// ErrorCode values for LPLOGINCALLBACKPROC
#define SDOA_ERRORCODE_OK               0    // Login succeeded
#define SDOA_ERRORCODE_CANCEL           -1   // User cancelled and closed the login dialog
#define SDOA_ERRORCODE_UILOST           -2   // Login dialog UI file is missing or invalid
#define SDOA_ERRORCODE_FAILED           -3   // Login failed
#define SDOA_ERRORCODE_UNKNOWN          -4   // Unknown error
#define SDOA_ERRORCODE_INVALIDPARAM     -5   // Invalid parameter
#define SDOA_ERRORCODE_UNEXCEPT         -6   // Unknown exception
#define SDOA_ERRORCODE_ALREAYEXISTS     -7   // Already exists
#define SDOA_ERRORCODE_SHOWMESSAGE      -10  // Show the message dialog


// Login callback
// nErrorCode: Login error code
// pLoginResult: Login result, valid only when nErrorCode = SDOA_ERRORCODE_OK
// nUserData: User data passed to ShowLoginDialog
// nReserved: Reserved and currently always 0 (not the Reserved argument to ShowLoginDialog)
// Return: TRUE closes the dialog; FALSE leaves it open
//
// 2009.03.30
// Extension: when nErrorCode = ERRORCODE_SHOWMESSAGE, Reserved returns a LoginMessage*
// Return TRUE to suppress the IGW dialog so the game can display its own message
// Return FALSE to show the IGW dialog; use SysReallocString to customize Title and Content
//              IGW calls SysFreeString after the callback to release allocated memory
typedef BOOL (CALLBACK *LPLOGINCALLBACKPROC)(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved);

// Application interface
typedef interface ISDOAApp ISDOAApp;
typedef ISDOAApp *PSDOAApp, *LPSDOAApp;

MIDL_INTERFACE("C8187484-1C5F-48DF-8497-2136A72A5733")
ISDOAApp : public IUnknown
{
public:
	// Show the login dialog
	STDMETHOD_(int,ShowLoginDialog)(THIS_ LPLOGINCALLBACKPROC fnCallback, int nUserData, int nReserved) PURE;

	STDMETHOD_(void,ModifyAppInfo)(THIS_ const AppInfo* pAppInfo) PURE;
	STDMETHOD_(void,Logout)(THIS) PURE;
	STDMETHOD_(int,GetLoginState)(THIS_ int nLoginMethod) PURE;
	STDMETHOD_(void,SetRoleInfo)(THIS_ const RoleInfo* pRoleInfo) PURE;
	

	// Show the recharge dialog
	STDMETHOD_(int,ShowPaymentDialog)(THIS_ LPCWSTR pwcsSrc) PURE;

	// Configure SDOA UI
	STDMETHOD_(int,GetScreenStatus)(THIS) PURE;
	STDMETHOD_(void,SetScreenStatus)(THIS_ int nValue) PURE;
	STDMETHOD_(bool,GetScreenEnabled)(THIS) PURE;
	STDMETHOD_(void,SetScreenEnabled)(THIS_ bool bValue) PURE;
	STDMETHOD_(bool,GetTaskBarPosition)(THIS_ PPOINT ptPosition) PURE;
	STDMETHOD_(bool,SetTaskBarPosition)(THIS_ const PPOINT ptPosition) PURE;
	STDMETHOD_(bool,GetFocus)(THIS) PURE;
	STDMETHOD_(void,SetFocus)(THIS_ bool bValue) PURE;
	STDMETHOD_(bool,HasUI)(THIS_ const PPOINT ptPosition) PURE;
	
	STDMETHOD_(int,GetTaskBarMode)(THIS) PURE;
	STDMETHOD_(void,SetTaskBarMode)(THIS_ int nBarMode) PURE;
	STDMETHOD_(int,GetSelfCursor)(THIS) PURE;
	STDMETHOD_(void,SetSelfCursor)(THIS_ int nValue) PURE;

	// Features
	STDMETHOD_(int,OpenWidget)(THIS_ LPCWSTR pwcsWidgetNameSpace) PURE;
	STDMETHOD_(int,OpenWidgetEx)(THIS_ LPCWSTR pwcsWidgetNameSpace, LPCWSTR pwcsParam, int nFlag) PURE;
	STDMETHOD_(int,CloseWidget)(THIS_ LPCWSTR pwcsWidgetNameSpace) PURE;
	STDMETHOD_(int,ExecuteWidget)(THIS_ LPCWSTR pwcsWidgetNameSpaceOrGUID, LPCWSTR pwcsParam) PURE;
	STDMETHOD_(int,WidgetExists)(THIS_ LPCWSTR pwcsWidgetNameSpaceOrGUID) PURE;
	STDMETHOD_(int,OpenWindow)(THIS_ LPCWSTR pwcsWinType, LPCWSTR pwcsWinName, LPCWSTR pwcsSrc, int nLeft, int nTop, int nWidth, int nHeight, LPCWSTR pwcsMode) PURE;
	STDMETHOD_(int,CloseWindow)(THIS_ LPCWSTR pwcsWinName) PURE;

	STDMETHOD_(int,GetWinProperty)(THIS_ LPCWSTR pwcsWinName, SDOAWinProperty* pWinProperty) PURE;
	STDMETHOD_(int,SetWinProperty)(THIS_ LPCWSTR pwcsWinName, SDOAWinProperty* pWinProperty) PURE;
};


typedef interface ISDOAApp2 ISDOAApp2;
typedef ISDOAApp2 *PSDOAApp2, *LPSDOAApp2;

MIDL_INTERFACE("3F35136C-7061-4E69-BF3A-CC78D026F48F")
ISDOAApp2 : public ISDOAApp
{
public:
	STDMETHOD_(int,LoginDirect)(THIS_ LPCSTR szSessionId, LPCSTR szAdditional, int nReserved) PURE;
	STDMETHOD_(int,GetClientSignature)(THIS_ LPCWSTR szIndication, BSTR* Signature) PURE;
};


// Sound control callback implemented by the game
// Valid volume range is 0-100
typedef DWORD (CALLBACK *LPGETAUDIOSOUNDVOLUME)();
typedef void  (CALLBACK *LPSETAUDIOSOUNDVOLUME)(DWORD nNewVolume);
typedef DWORD (CALLBACK *LPGETAUDIOEFFECTVOLUME)();
typedef void  (CALLBACK *LPSETAUDIOEFFECTVOLUME)(DWORD nNewVolume);

// General data transfer interface
class ICommonChannel
{
public:
	// The next three methods support Delphi compatibility; C++ implementations must retain their positions but need not implement them
	virtual HRESULT _stdcall QueryInterface(REFIID riid, void **ppvObject) = 0;
	virtual ULONG _stdcall AddRef(void) = 0;
	virtual ULONG _stdcall Release(void) = 0;

	virtual void _stdcall SendData(BSTR Request, BSTR* Response) = 0;
	virtual void _stdcall Set_RevertChannel(ICommonChannel *pReverter) = 0;
	virtual ICommonChannel* _stdcall Get_RevertChannel(void) = 0;
	virtual void _stdcall Close(void) = 0;
	virtual void _stdcall Get_ChannelType(LPSTR szChannelType, DWORD nBufferLen) = 0; // max BufferLen = 64
};
typedef ICommonChannel *PCommonChannel;

typedef BOOL (WINAPI *LPCREATECHANNEL)(LPCSTR szChannelType, ICommonChannel **pChannel);


typedef interface ISDOAAppUtils ISDOAAppUtils;
typedef ISDOAAppUtils *PSDOAAppUtils, *LPSDOAAppUtils;

MIDL_INTERFACE("1170C2F9-28AD-4EA8-8392-E9A219C8FF65")
ISDOAAppUtils : public IUnknown
{
public:
	// Sound control
	// Set sound control callbacks
	STDMETHOD_(void,SetAudioSetting)(THIS_ 
		LPGETAUDIOSOUNDVOLUME  fnGetAudioSoundVolume,
		LPSETAUDIOSOUNDVOLUME  fnSetAudioSoundVolume,
		LPGETAUDIOEFFECTVOLUME fnGetAudioEffectVolume,
		LPSETAUDIOEFFECTVOLUME fnSetAudioEffectVolume ) PURE;
	// Notify SDOA that game sound has changed
	STDMETHOD_(void,NodifyAudioChanged)(THIS) PURE;	
	// Set the data channel creation callback
	STDMETHOD_(void,SetCreateChannelCallback)(THIS_ const LPCREATECHANNEL fnCreateChannel) PURE;	
};

// Asynchronous callback
typedef void (CALLBACK *LPQUERYCALLBACK)(int nRetCode, int nUserData);

typedef interface ISDOAClientService ISDOAClientService;
typedef ISDOAClientService *PSDOAClientService, *LPSDOAClientService;

MIDL_INTERFACE("AF56D291-823A-41AA-85A0-EBE5C6163425")
ISDOAClientService : public IUnknown
{
public:
	STDMETHOD_(int, SetValue)(THIS_ const BSTR bstrKey, const BSTR bstrValue ) PURE;
	STDMETHOD_(int, Query)(THIS_ const BSTR bstrService) PURE;	
	STDMETHOD_(int, AsyncQuery)(THIS_ const BSTR bstrService, LPQUERYCALLBACK fnCallback, int nUserData) PURE;	
	STDMETHOD_(int, GetValue)(THIS_ const BSTR bstrKey, BSTR* bstrValue) PURE;	
};

/* Use the SDOA_SDK_VERSION macro for the dwSdkVersion argument to igwInitialize. */
typedef int  (WINAPI* LPigwInitialize)(DWORD dwSdkVersion, const AppInfo* pAppInfo);
typedef bool (WINAPI* LPigwGetModule)(REFIID riid, void** intf);
typedef int  (WINAPI* LPigwTerminal)();

#pragma pack(pop)
#endif /* SDOA4CLIENT_H */