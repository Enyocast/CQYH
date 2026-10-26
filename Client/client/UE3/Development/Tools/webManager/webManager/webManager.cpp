// webManager.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "resource1.h"
#include <atlbase.h>
#include <atlwin.h>
#include <atlimage.h>
#include <ExDisp.h>
#include <ExDispid.h>
#include <time.h>
#include "webManager.h"

#define   DLLWEB_STATIC_TITLETEXT			 0
#define   DLLWEB_STATIC_TITLEICON			 1
#define   DLLWEB_BUTTON_CLOSEICON			 2
#define   DLLWEB_BUTTON_MAXICON				 3
#define   DLLWEB_BUTTON_MINICON				 4
#define   DLLWEB_OUTWINDOW					 5
#define   DLLWEB_INWINDOW					 6

static  struct IWebBrowser2*		dllWebBrower = NULL;
static  class CComModule*			dllWebpComModule = NULL; 
HWND								dllWebHwnd[7]	= {0};
const   INT							nTitleHeight = 27;
BOOL								g_bSetWebTimeOut = FALSE;
BOOL								g_bTimeLimited = FALSE;

class dllWebBrowerEvent:public DWebBrowserEvents2
{
public:
	dllWebBrowerEvent();
	~dllWebBrowerEvent();

protected:
	DWORD m_dwRef;
	STDMETHODIMP QueryInterface(REFIID riid,void** ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP GetTypeInfoCount(UINT *pctinfo);
	STDMETHODIMP GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo);
	STDMETHODIMP GetIDsOfNames(REFIID riid,LPOLESTR *rgszNames,UINT cNames,LCID lcid,DISPID *rgDispId );
	STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS * pDispParams,VARIANT *pVarReslut, EXCEPINFO *pExcepInfo,UINT *puArgErr );
};

BOOL CALLBACK EnumChildProWeb(HWND hwnd,LPARAM lParam)
{
	TCHAR buffer[128] = {0};
	GetClassName(hwnd,buffer,sizeof(buffer)/sizeof(TCHAR));
	if(0 == StrCmpC(buffer,__T("Internet Explorer_Server")))
	{
		int nHtmlGetObject = RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
		DWORD_PTR dwRes;
		LRESULT LRes = SendMessageTimeout(hwnd,nHtmlGetObject,0,0,SMTO_ABORTIFHUNG,500,&dwRes);
		if(LRes)
		{
			g_bSetWebTimeOut = TRUE;
			return FALSE;
		}
	}
	return TRUE;
}
dllWebBrowerEvent::dllWebBrowerEvent()
{
	m_dwRef = 1;
}
dllWebBrowerEvent::~dllWebBrowerEvent()
{

}

STDMETHODIMP dllWebBrowerEvent::QueryInterface(REFIID riid,void** ppvObject)
{
	if(IsBadWritePtr(ppvObject,sizeof(void*)))
		return E_POINTER;
	*ppvObject = NULL;
	if(IsEqualIID(riid,IID_IUnknown) || IsEqualIID(riid,IID_IDispatch) || IsEqualIID(riid,DIID_DWebBrowserEvents2))
	{
		AddRef();
		*ppvObject = this;
		return S_OK;
	}
	return E_NOINTERFACE;
}
STDMETHODIMP_(ULONG) dllWebBrowerEvent::AddRef()
{
	InterlockedIncrement(&m_dwRef);
	return m_dwRef;
}
STDMETHODIMP_(ULONG) dllWebBrowerEvent::Release()
{
	InterlockedDecrement(&m_dwRef);
	if(m_dwRef == 0)
		delete this;

	return m_dwRef;
}

STDMETHODIMP dllWebBrowerEvent::GetTypeInfoCount(UINT *pctinfo)
{
	UNREFERENCED_PARAMETER(pctinfo);
	*pctinfo = 0;

	return S_OK;
}
STDMETHODIMP dllWebBrowerEvent::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo)
{
	UNREFERENCED_PARAMETER(iTInfo);
	UNREFERENCED_PARAMETER(lcid);
	UNREFERENCED_PARAMETER(ppTInfo);
	*ppTInfo = NULL;

	return E_NOTIMPL;
}
STDMETHODIMP dllWebBrowerEvent::GetIDsOfNames(REFIID riid,LPOLESTR *rgszNames,UINT cNames,LCID lcid,DISPID *rgDispId )
{
	UNREFERENCED_PARAMETER(riid);
	UNREFERENCED_PARAMETER(rgszNames);
	UNREFERENCED_PARAMETER(cNames);
	UNREFERENCED_PARAMETER(lcid);
	UNREFERENCED_PARAMETER(rgDispId);

	return E_NOTIMPL;
}
//避免网页异常导致阻塞 超时3秒没回应就关闭
static time_t static_Time = 0;
DWORD WINAPI dllListenTimeThread(LPVOID lpParam)
{
	OutputDebugString(TEXT("dllListenTimeThread  start\n"));
	while(g_bTimeLimited)
	{
		OutputDebugString(TEXT("-----dllListenTimeThread Excuting\n"));

		if(!g_bTimeLimited)
		{
			OutputDebugString(TEXT("-----dllListenTimeThread  End\n"));
			return 0;
		}
		Sleep(1000);
		time_t timeTmp;
		time(&timeTmp);
		if(timeTmp - static_Time >= 5)
		{
			OutputDebugString(TEXT("-----dllListenTimeThread  TimeOut \n"));
			if(g_bTimeLimited)	
			{
				OutputDebugString(TEXT("-----dllListenTimeThread  TimeOut Send Close\n"));
				LRESULT lRes = SendMessage(dllWebHwnd[DLLWEB_OUTWINDOW],WM_SYSCOMMAND,SC_CLOSE,0);
				OutputDebugString(TEXT("-----dllListenTimeThread  TimeOut Excuting Close \n"));
			}
				
			{
				OutputDebugString(TEXT("-----dllListenTimeThread  End TimeOut\n"));
				return 0;
			}
		}
	}
	{
		OutputDebugString(TEXT("-----dllListenTimeThread  End\n"));
		return 0;
	}
}
STDMETHODIMP dllWebBrowerEvent::Invoke(DISPID dispIdMember, REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS * pDispParams,VARIANT *pVarReslut, EXCEPINFO *pExcepInfo,UINT *puArgErr )
{
	UNREFERENCED_PARAMETER(lcid);
	UNREFERENCED_PARAMETER(wFlags);
	UNREFERENCED_PARAMETER(pVarReslut);
	UNREFERENCED_PARAMETER(pExcepInfo);
	UNREFERENCED_PARAMETER(puArgErr);

	if(!IsEqualIID(riid ,IID_NULL))
		return DISP_E_UNKNOWNINTERFACE;

	if(!g_bSetWebTimeOut)
	{
		if(dllWebHwnd[DLLWEB_INWINDOW] != NULL)
			EnumChildWindows(dllWebHwnd[DLLWEB_INWINDOW],EnumChildProWeb,NULL);
	}

	switch(dispIdMember)
	{
	case DISPID_BEFORENAVIGATE2:
		{
			if(!g_bTimeLimited)
			{				
				g_bTimeLimited = TRUE;
				time(&static_Time);
				HANDLE hThread = CreateThread(NULL,0,dllListenTimeThread,NULL,0,NULL);
				CloseHandle(hThread);
			}
			break;
		}
	case DISPID_NAVIGATECOMPLETE2:
		{
			SendMessage(dllWebHwnd[DLLWEB_OUTWINDOW],WM_SYSCOMMAND,1,0);
			g_bTimeLimited = FALSE;
			break;
		}
	case DISPID_NEWWINDOW3:
		{
			break;
		}
	}
	return S_OK;
}

dllWebBrowerEvent  m_webEvent;

DLL_EXPORT void dllReleaseWeb()
{
	if(dllWebBrower)
	{
		dllWebBrower->Release();
	}
	if(dllWebpComModule)
	{
		delete dllWebpComModule;
		dllWebpComModule = NULL;
	}
}

DLL_EXPORT HWND dllCreatWebWindow(HWND hnd)
{
	if(dllWebpComModule == NULL)
	{
		dllWebpComModule = new CComModule();
		if(dllWebpComModule == NULL)
			return NULL;
	}
	CAxWindow		wincAx;
	CAxWindow		wincAxEX;
	RECT clientRc;
	GetClientRect(hnd,&clientRc);
	
	/*
	 窗体居中 800*600 改成900*600
	*/
	INT nWidth = clientRc.right - clientRc.left;
	INT nHeight = clientRc.bottom - clientRc.top;
	clientRc.left = (nWidth - 920)/2;
	clientRc.top  = (nHeight - 580)/2;
	clientRc.bottom = clientRc.top + 580;  
	clientRc.right  = clientRc.left + 920;

	HWND hWinEx = wincAxEX.Create(hnd,&clientRc,0,WS_CHILD|WS_CLIPCHILDREN|WS_VISIBLE/*|WS_DLGFRAME*//*|WS_SIZEBOX*/);

	if(hWinEx == NULL)
		return NULL;
	GetClientRect(hWinEx,&clientRc);
	clientRc.top += nTitleHeight;

	HWND hWin = wincAx.Create(hWinEx,&clientRc,0,WS_CHILD|WS_VISIBLE);

	if(hWin == NULL)
		return NULL;
	dllWebHwnd[DLLWEB_OUTWINDOW] = hWinEx;
	dllWebHwnd[DLLWEB_INWINDOW]  = hWin;

	HRESULT hr = wincAx.CreateControl(OLESTR("shell.Explorer.2"));

	if(hr == S_OK)
	{
		hr = wincAx.QueryControl(__uuidof(IWebBrowser2),(void**)&dllWebBrower);

		if(hr == S_OK)
		{
			dllWebBrower->put_Silent(TRUE);
			dllWebBrower->put_RegisterAsBrowser(TRUE);
			return hWinEx;
		}
	}
	return NULL;
}

DLL_EXPORT  BOOL dllCreatWebWindowTitle(const TCHAR* szTitleName,const TCHAR* szTitleIcon,const TCHAR* szCloseIcon)
{
	RECT rcWin;
	GetClientRect(dllWebHwnd[DLLWEB_OUTWINDOW],&rcWin);
	//HINSTANCE hinst = (HINSTANCE)::GetWindowLong(dllWebHwnd[DLLWEB_OUTWINDOW],GWL_HINSTANCE);
	HINSTANCE hinst = (HINSTANCE)::GetWindowLongPtr(dllWebHwnd[DLLWEB_OUTWINDOW],GWLP_HINSTANCE);
	if(szTitleName)
	{
		dllWebHwnd[DLLWEB_STATIC_TITLETEXT] = CreateWindow(TEXT("static"),szTitleName,WS_CHILD|WS_VISIBLE|SS_CENTER,rcWin.left,rcWin.top ,rcWin.right - rcWin.left,nTitleHeight,dllWebHwnd[DLLWEB_OUTWINDOW],0,hinst,NULL);
	}
	HBITMAP hBmp;
	CImage img;
	if(szTitleIcon)
	{		
		/*HRESULT ret = img.Load(szTitleIcon);
		if(ret == S_OK)
			hBmp = img.Detach();*/
 
		hBmp = LoadBitmap(hinst,MAKEINTRESOURCE(IDB_BITMAP1));
		//hBmp = (HBITMAP)::LoadImage(NULL,TEXT("titlebg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		dllWebHwnd[DLLWEB_STATIC_TITLEICON] = CreateWindow(TEXT("static"),TEXT(""),WS_CHILD|WS_VISIBLE|SS_BITMAP|SS_CENTERIMAGE,rcWin.left,rcWin.top ,rcWin.right - rcWin.left,nTitleHeight,dllWebHwnd[DLLWEB_OUTWINDOW],0,hinst,NULL);
		SendMessage(dllWebHwnd[DLLWEB_STATIC_TITLEICON],STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBmp);
	}
	LONG btnStyle = WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP;
	if(szCloseIcon)
	{
		hBmp = LoadBitmap(hinst,MAKEINTRESOURCE(IDB_BITMAP2));
		dllWebHwnd[DLLWEB_BUTTON_CLOSEICON] = CreateWindow(TEXT("button"),TEXT(""),btnStyle,rcWin.right - 20,rcWin.top + 5,17,17,dllWebHwnd[DLLWEB_OUTWINDOW],(HMENU)SC_CLOSE,hinst,NULL);
		SendMessage(dllWebHwnd[DLLWEB_BUTTON_CLOSEICON],BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBmp);
	}
	return TRUE;
}
DLL_EXPORT  void dllReDrawWebWindow()
{
	RECT rcWin;
	GetClientRect(dllWebHwnd[DLLWEB_OUTWINDOW],&rcWin);
	MoveWindow(dllWebHwnd[DLLWEB_STATIC_TITLETEXT],rcWin.left,rcWin.top ,rcWin.right - rcWin.left,nTitleHeight,TRUE);
	MoveWindow(dllWebHwnd[DLLWEB_STATIC_TITLEICON],rcWin.left,rcWin.top ,rcWin.right - rcWin.left,nTitleHeight,TRUE);
	MoveWindow(dllWebHwnd[DLLWEB_BUTTON_CLOSEICON],rcWin.right - 20,rcWin.top + 5,17,17,TRUE);
	rcWin.top += nTitleHeight;
	MoveWindow(dllWebHwnd[DLLWEB_INWINDOW],rcWin.left,rcWin.top ,rcWin.right - rcWin.left,rcWin.bottom - rcWin.top,TRUE);
}

DLL_EXPORT void dllOpenUrl(const TCHAR*  szUrl)
{
	if(dllWebBrower == NULL)
		return;
	VARIANT url;
	VariantInit(&url);
	url.vt = VT_BSTR;
	url.bstrVal = SysAllocString(szUrl);
	
	DWORD m_dwCookie;
	DWORD nRes = AtlAdvise(dllWebBrower,(IUnknown*)&m_webEvent,DIID_DWebBrowserEvents2,&m_dwCookie);
	if(nRes >= 0)
	{
		g_bSetWebTimeOut = FALSE;
		dllWebBrower->Navigate2(&url,0,0,0,0);
	}
}
