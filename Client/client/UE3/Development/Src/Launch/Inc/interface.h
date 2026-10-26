#ifndef SDOLOGIN_INTERFACE_H
#define SDOLOGIN_INTERFACE_H


#include <objbase.h>
#include <windows.h>

#pragma pack(push,1)

#define SDOL_ERRORCODE_OK               0      // success
#define SDOL_ERRORCODE_FAILED           -1     // fail
#define SDOL_ERRORCODE_UNEXCEPT         -100   // unknown exception
#define SDOL_ERRORCODE_LOGINCANCEL      -101   // login dialog closed by user click cancel button
#define SDOL_ERRORCODE_INVALIDPARAM     -102   // invalid parameter
#define SDOL_ERRORCODE_INVALIDBUFFER    -103   // buffer is not enough

#define SDOL_LOGINRESULT_KEEP_SHOWN     0      // keep login dialog
#define SDOL_LOGINRESULT_CLOSE          1      // close login dialog

#define 	NormalLoginMode				0
#define 	LauncherLoginMode			1
#define		AttachToLoginMode			2

struct SDOLAppInfo
{
	DWORD		Size;			// = sizeof(SDOLAppInfo)
	int			AppID;			// unique ID of APP, assigned by SDG
	LPCWSTR		AppName;		// APP name
	LPCWSTR		AppVer;		   	// version of game client
	int			AreaId;			// Area ID, assigned by SDG
	int			GroupId;        // Group ID, assigned by SDG
};

struct SDOLLoginResult
{
	DWORD       Size;			// sizeof(SDOLLoginResult)
	LPCWSTR     SessionId;		// token for sever verification
	LPCWSTR     Sndaid;		    // snda id of user
	LPCWSTR     IdentityState;	// reserved
	LPCWSTR     Appendix;		// reserved
};

// callback
// keep login dialog when SDOL_LOGINRESULT_KEEP_SHOWN returned, close login dialog when SDOL_LOGINRESULT_CLOSE returned.
// nErrorCode:     error code
// pLoginResult:   login result
// nUserData:      user data trasfered in ShowLoginDialog
// nReserved:      reserved
typedef int (CALLBACK *LPSDOLLOGINCALLBACKPROC)(int nErrorCode, const SDOLLoginResult* pLoginResult, int nUserData, int nReserved);

MIDL_INTERFACE("AD887932-2D1C-48ec-B3E0-535B609C12D6")
ISDOLLogin : public IUnknown
{
public:
	// set owner window of login dialog
	STDMETHOD_(int,SetOwnerWindow)(THIS_ HWND hWnd) PURE;
	// show login dialog
	STDMETHOD_(int,ShowLoginDialog)(THIS_ LPSDOLLOGINCALLBACKPROC fnCallback, int nUserData, int nReserved) PURE;
	// close login dialog
	STDMETHOD_(int,CloseLoginDialog)(THIS) PURE;
	// move login dialog to specified position, x and y is related to owner window. it's valid that login dialog is embedded in owner window.
	STDMETHOD_(int,MoveLoginDialog)(THIS_ int x, int y) PURE;
	// logout
	STDMETHOD_(int,Logout)(THIS) PURE;
};

MIDL_INTERFACE("7B06DAD6-6832-4455-AFC6-6C8BE902534B")
ISDOLLogin2 : public ISDOLLogin
{
public:
	// do login(this function same as click the "login" button on login dialog)
	STDMETHOD_(int,DoLogin)(THIS) PURE;
	// set login mode(in game client the "nLoginMode" parameter must set to "AttachToLoginMode")
	STDMETHOD_(int,SetLoginMode)(THIS_ int nLoginMode) PURE;
	// get token for sever verification
	STDMETHOD_(int,GetTicket)(THIS_ BSTR* bstrTicket, BSTR* bstrSndaid) PURE;
	// modify appinfo when some information changed. e.g. area id
	STDMETHOD_(int,ModifyAppInfo)(THIS_ const SDOLAppInfo* pAppInfo) PURE;
};

typedef int (WINAPI* LPSDOLInitialize)(const SDOLAppInfo* pAppInfo);
typedef int (WINAPI* LPSDOLGetModule)(REFIID riid, void** intf);
typedef int (WINAPI* LPSDOLTerminal)();

#pragma pack(pop)
#endif /* SDOLOGIN_INTERFACE_H */
