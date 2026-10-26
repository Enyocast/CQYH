#ifndef SDOLOGIN2
#define SDOLOGIN2
#include <objbase.h>


#define _SDOL_ERRORCODE_OK               0      // success
#define _SDOL_ERRORCODE_FAILED           -1     // fail
#define _SDOL_ERRORCODE_UNEXCEPT         -100   // unknown exception
#define _SDOL_ERRORCODE_LOGINCANCEL      -101   // login dialog closed by user click cancel button
#define _SDOL_ERRORCODE_INVALIDPARAM     -102   // invalid parameter
#define _SDOL_ERRORCODE_INVALIDBUFFER    -103   // buffer is not enough
#define _SDOL_LOGINRESULT_KEEP_SHOWN     0      // keep login dialog
#define _SDOL_LOGINRESULT_CLOSE          1      // close login dialog

struct _SDOLLoginResult
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
typedef int (CALLBACK *_LPSDOLLOGINCALLBACKPROC)(int nErrorCode, const _SDOLLoginResult* pLoginResult, int nUserData, int nReserved);

typedef int (* _LPSDOLInitialize)();
typedef int (* _LPSDOLGetModule)(REFIID riid, void** intf);
typedef int (* _LPSDOLTerminal)();

// {4CA7295D-6A97-466B-98F5-F6AB07100556}
static const IID IID_ISDOLogin2 = { 0x4ca7295d, 0x6a97, 0x466b, { 0x98, 0xf5, 0xf6, 0xab, 0x7, 0x10, 0x5, 0x56 } };

interface ISDOLogin2 : public IUnknown
{
public:
	virtual int __stdcall MoveLoginDialog(int x, int y)=NULL;
	virtual int __stdcall ShowLoginDialog(_LPSDOLLOGINCALLBACKPROC fnCallback, int nUserData, int nReserved, HWND hParent)=NULL;
	virtual int __stdcall CloseLoginDialog(void)=NULL;
};

#endif