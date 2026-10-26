// NormalGDIWin.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "NormalGDIWin.h"
#include <strsafe.h>        // StringCch相关用
#include "SDOA4Client.h"
#include "SDOAGDI.h"

#define MAX_LOADSTRING 100

/* 接入相关全局变量  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOAGDI*			g_SDOAGDI = NULL;
ISDOAApp2*			g_SDOAApp = NULL;
char				g_szSessionID[128];
char				g_szAdditional[128];


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND g_hWnd;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/* 加载IGW */
void OpenIGW();
/* 释放IGW */
void CloseIGW();
/* 登录回调 */
BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NORMALGDIWIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NORMALGDIWIN));

	/* 加载IGW */
	OpenIGW();
	if (igwInitialize)
	{	// 说明加载成功，表示下......			
		SetWindowText(g_hWnd, L"NormalGDIWin [加载IGW组件成功]");
	}

	if (g_SDOAGDI)
	{
		g_SDOAGDI->Initialize(g_hWnd, SDOA_GDIMODE_DESKTOP);
	}

	
	

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (g_SDOAGDI)
	{
		g_SDOAGDI->Finalize(g_hWnd);
	}

	/* 释放IGW */
	CloseIGW();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORMALGDIWIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NORMALGDIWIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // Store instance handle in our global variable

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   0, 0, 640, 480, NULL, NULL, hInstance, NULL);


   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case SDOA_WM_CLIENT_RUN:
		/* 注意在加载GameWidget.dll成功后会收到一次该消息，之后任意时刻都可以再次调用ShowLoginDialog */
		if (g_SDOAApp)
		{// 收到该消息时可以显示登录对话框了
			g_SDOAApp->ShowLoginDialog(OnLogin, 0, 0);
		}

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


/* 释放IGW */
void CloseIGW()
{
	if (g_SDOAApp)
	{
		g_SDOAApp->Release();
		g_SDOAApp = NULL;
	}

	if (g_SDOAGDI)
	{
		g_SDOAGDI->Release();
		g_SDOAGDI = NULL;
	}
	if (igwTerminal)
	{  // 释放DLL前总是先调用igwTerminal
		igwTerminal();
		igwTerminal = NULL;
	}
	if (g_hInstIGWDll)
	{
		FreeLibrary(g_hInstIGWDll);
		g_hInstIGWDll = 0;
	}
	igwInitialize = NULL;
}

/* 加载IGW */
void OpenIGW()
{
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileNameW( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{	// 得到EXE所在路径
		StringCchCopyW( strExeName, MAX_PATH, &strLastSlash[1] );
		*strLastSlash = 0;
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	WCHAR strGameWidgetDll[MAX_PATH] = {0};
	StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\GameWidget.dll", strExePath );

	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}
	
	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}	

	CloseIGW();

	if ( GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF )
	{	// 找到组件则加载	
		g_hInstIGWDll = LoadLibraryW(strGameWidgetDll);
		if (g_hInstIGWDll)
		{
			igwInitialize = (LPigwInitialize)GetProcAddress( g_hInstIGWDll, "igwInitialize" );
			igwGetModule = (LPigwGetModule)GetProcAddress( g_hInstIGWDll, "igwGetModule" );
			igwTerminal = (LPigwTerminal)GetProcAddress( g_hInstIGWDll, "igwTerminal" );
			if ( igwInitialize && igwGetModule && igwTerminal)
			{
				// 加载成功

				// 注意AppInfo类型所有字段必须填
				AppInfo tmpAppInfo = {
					sizeof(AppInfo),       // 结构体大小，方便扩展
					9999,                  // 接入应用ID，从开发者网站中申请
					L"龙潭虎穴OnLine",     // 应用名称
					L"0.1.2.0",            // 应用客户端当前版本号
					SDOA_RENDERTYPE_GDI,   // 客户端支持的图形引擎类型，这里同时支持d3d9和d3d8
					1,                     // 可同时在一台机器上游戏的最大人数（通常为1，例如:KOF应该是2）
					-1,                    // 游戏区ID，不可用时传入-1
					-1                     // 游戏组ID，不可用时传入-1

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// 初始化组件成功

					// 获取组件接口
					igwGetModule(__uuidof(ISDOAGDI), (void**)&g_SDOAGDI);
					igwGetModule(__uuidof(ISDOAApp2), (void**)&g_SDOAApp);
					if ( (!g_SDOAGDI) || (!g_SDOAApp))
						CloseIGW();						

				}
				else // 初始化失败清除环境
					CloseIGW();
			}
			else  // 加载DLL失败清除环境
				CloseIGW();
		}
	}
}

BOOL isSDOLogin = false; // 注意一定要是BOOL类型，不能为bool否则可能会导致问题
LoginResult loginResult;

BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved)
{ // 注意该回调返回true则关闭登录对话框，否则登录对话框仍然显示

	isSDOLogin = (SDOA_OK == nErrorCode); 
	if (isSDOLogin) 
	{ 
		loginResult = *pLoginResult; 
		// 总是先清零
		::ZeroMemory(g_szSessionID, sizeof(g_szSessionID));
		::ZeroMemory(g_szAdditional, sizeof(g_szAdditional));
		// 复制一份
		StringCchCopyA(g_szSessionID, sizeof(g_szSessionID), pLoginResult->szSessionId);
		StringCchCopyA(g_szAdditional, sizeof(g_szAdditional), pLoginResult->szAdditional);

		// 登录成功后,把用户使用的游戏角色信息传入IGW
		if (g_SDOAApp)
		{
			RoleInfo tmpRoleInfo = { sizeof(RoleInfo), L"美貌仙子", 0 } ;
			g_SDOAApp->SetRoleInfo(&tmpRoleInfo);  // 设置角色信息，可多次调用，只要用户切换了角色就调用通知IGW
		}
	}

	if (SDOA_ERRORCODE_SHOWMESSAGE == nErrorCode)
	{ // 登录错误消息处理
		if (nReserved != 0)
		{
			LoginMessage* pCurLoginMsg = (LoginMessage*)nReserved;
			if (pCurLoginMsg->dwSize >= sizeof(LoginMessage))
			{ // 兼容性处理 
				// 修改错误提示对话框标题
				//SysReAllocString(pCurLoginMsg->pbstrTitle, L"[测试游戏错误提示]");

				// 此时返回FALSE则使用默认提示

				// 此时返回TRUE则使用自定义的提示
				//isSDOLogin = TRUE;
				//::MessageBox(0, *pCurLoginMsg->pbstrContent, *pCurLoginMsg->pbstrTitle, MB_OK);
			}
		}
	}
	return isSDOLogin; // 常规逻辑，登录成功则关闭登录对话框
} 
