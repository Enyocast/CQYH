#ifndef WEBHTMLMANAGER_H_
#define WEBHTMLMANAGER_H_

#include "MMOSingleton.h"


class WebHtmlManager : public SingletonMeyers<WebHtmlManager>
{
public:
	WebHtmlManager(void);
	virtual ~WebHtmlManager(void);

	void Init();
	void Shutdown();

	void NotifyOpenSurveyPage(TArray<FString>& arrPath);
	void SetOpenGmBallDelegate(FScriptDelegate fun);

	void OpenGameQuitWeb();
	void OpenRechargeYuanBao();
	void OpenRechargeYuanBaoByIE();
	void OpenSellYuanBao();
	void OpenSurveyUrl();
	void OpenBugSubmitUrl();
	void OpenGameService( FString roleName, INT roleLv );
	void OpenGManagerByIE();
	void OpenDynamicHelpByIE();

	void CloseWebPage();
	void OpenNewSurvey();
	void OpenUrl(FString strUrl, INT w = 920, INT h = 580);
	void OpenUrlByBrowser(FString strUrl,FString strStyle,INT w=1024,INT h=768);
	void OpenUrlByIE(FString strUrl);
	void RedrawWebWindow();
	bool AddNewUrlMessageBox(FString url);
private:
	static LRESULT APIENTRY StaticWebWndProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam );	
	FString   GetWholePath(const FString& path);
	static unsigned char QURL_ToHex(unsigned char x);

public:
	static std::string QURL_UrlEncode(const std::string& str);
	static BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);
	static BOOL UrlDecode(const char* szSrc, char* pBuf, int cbBufLen);
	BOOL LoadGameServiceEncrypt();
	void UnloadGameServiceEncrypt();

private:

	typedef HWND ( *FunInitWebWindowDll)(HWND,UINT,UINT);
	typedef BOOL ( *FunInitWebWindowTitle)(const TCHAR*,const TCHAR*,const TCHAR*);
	typedef void ( *FunRedrawWebWindow)();
	typedef void ( *FunOpenWebUrl)(const TCHAR*);
	typedef void ( *FunShutDownWebDll)();

	FunInitWebWindowDll		pFunInitWebWindowDll;
	FunInitWebWindowTitle   pFunInitWebWindowTitle;
	FunRedrawWebWindow		pFunRedrawWindow;
	FunOpenWebUrl			pFunOpenUrl;
	FunShutDownWebDll		pFunShutDownDll;

	FScriptDelegate _OpenGmBallDelegate;
	FString			_newWebUrl;

	HMODULE					_webDll;
	HWND					_webHwnd;
private:
	typedef char* ( *FunSDRS_EncryptDll)( const char* szSrc, int &pnLen );
	typedef char* ( *FunSDRS_DecryptDll)( const char* szSrc, int &pnLen );
	typedef void ( *FunSDRS_ReleaseDll)( char * buff );

	FunSDRS_EncryptDll			pFunSDRS_Encrypt;
	FunSDRS_DecryptDll			pFunSDRS_Decrypt;
	FunSDRS_ReleaseDll			pFunSDRS_Release;
	HMODULE					_GameServiceEncryptDll;

};
#endif